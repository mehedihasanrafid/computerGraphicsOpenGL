#include "App.hpp"

#include "Audio.hpp"
#include "GraphicsPrimitives.hpp"
#include "scenes/BeachScene.hpp"
#include "scenes/CityScene.hpp"
#include "scenes/HarborScene.hpp"
#include "scenes/MountainsScene.hpp"

#if defined(_WIN32)
#define NOMINMAX
#include <windows.h>
#endif
#include <GL/glut.h>

#include <algorithm>
#include <cstdlib>
#include <string>

namespace yacht {
namespace {
constexpr int kTimerIntervalMs = 16;
constexpr float kTargetAspect = 16.0F / 9.0F;
constexpr float kYachtRightBoundary = 1.95F;
constexpr float kYachtLeftReset = -1.95F;

constexpr int kMenuTogglePause = 1;
constexpr int kMenuToggleFlag = 2;
constexpr int kMenuNextScene = 3;
constexpr int kMenuPreviousScene = 4;
constexpr int kMenuToggleDay = 5;
constexpr int kMenuReset = 6;
constexpr int kMenuToggleHelp = 7;
constexpr int kMenuToggleSound = 8;
constexpr int kMenuExit = 9;
}

App* App::instance_ = nullptr;

App::App() {
    if (instance_ != nullptr) {
        std::abort();
    }
    instance_ = this;
}

int App::run(int argc, char** argv) {
    initializeGlut(argc, argv);
    initializeScenes();
    createMenu();

    lastFrameTimeMs_ = glutGet(GLUT_ELAPSED_TIME);
    glutTimerFunc(kTimerIntervalMs, timerCallback, 0);
    glutMainLoop();
    return 0;
}

void App::initializeGlut(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(state_.windowWidth, state_.windowHeight);
    glutInitWindowPosition(100, 60);
    glutCreateWindow("Yacht Journey - Multi-Scene OpenGL Animation");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.04F, 0.08F, 0.14F, 1.0F);

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialKeyboardCallback);
    glutMouseFunc(mouseCallback);
}

void App::initializeScenes() {
    scenes_[0] = std::make_unique<BeachScene>();
    scenes_[1] = std::make_unique<MountainsScene>();
    scenes_[2] = std::make_unique<CityScene>();
    scenes_[3] = std::make_unique<HarborScene>();
}

void App::createMenu() {
    glutCreateMenu(menuCallback);
    glutAddMenuEntry("Pause / Resume yacht", kMenuTogglePause);
    glutAddMenuEntry("Start / Stop flag", kMenuToggleFlag);
    glutAddMenuEntry("Next scene", kMenuNextScene);
    glutAddMenuEntry("Previous scene", kMenuPreviousScene);
    glutAddMenuEntry("Toggle day / night", kMenuToggleDay);
    glutAddMenuEntry("Reset yacht", kMenuReset);
    glutAddMenuEntry("Show / Hide help", kMenuToggleHelp);
    glutAddMenuEntry("Enable / Disable sound", kMenuToggleSound);
    glutAddMenuEntry("Exit", kMenuExit);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void App::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    scenes_.at(static_cast<std::size_t>(state_.sceneIndex()))->draw(state_);
    yacht_.draw(state_);
    drawOverlay();

    glutSwapBuffers();
}

void App::reshape(const int width, const int height) {
    state_.windowWidth = std::max(width, 1);
    state_.windowHeight = std::max(height, 1);

    const float currentAspect = static_cast<float>(state_.windowWidth) / static_cast<float>(state_.windowHeight);
    if (currentAspect > kTargetAspect) {
        state_.viewportHeight = state_.windowHeight;
        state_.viewportWidth = static_cast<int>(static_cast<float>(state_.windowHeight) * kTargetAspect);
        state_.viewportX = (state_.windowWidth - state_.viewportWidth) / 2;
        state_.viewportY = 0;
    } else {
        state_.viewportWidth = state_.windowWidth;
        state_.viewportHeight = static_cast<int>(static_cast<float>(state_.windowWidth) / kTargetAspect);
        state_.viewportX = 0;
        state_.viewportY = (state_.windowHeight - state_.viewportHeight) / 2;
    }

    glViewport(state_.viewportX, state_.viewportY, state_.viewportWidth, state_.viewportHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        AppState::kWorldLeft,
        AppState::kWorldRight,
        AppState::kWorldBottom,
        AppState::kWorldTop,
        -1.0,
        1.0
    );
    glMatrixMode(GL_MODELVIEW);
}

void App::update() {
    const int now = glutGet(GLUT_ELAPSED_TIME);
    float deltaSeconds = static_cast<float>(now - lastFrameTimeMs_) / 1000.0F;
    lastFrameTimeMs_ = now;
    deltaSeconds = std::clamp(deltaSeconds, 0.0F, 0.05F);

    state_.elapsedSeconds += deltaSeconds;
    if (!state_.paused) {
        state_.yachtX += state_.yachtSpeed * deltaSeconds;
        if (state_.yachtX > kYachtRightBoundary) {
            state_.yachtX = kYachtLeftReset;
            nextScene();
        }
    }

    glutPostRedisplay();
}

void App::keyboard(const unsigned char key, int, int) {
    switch (key) {
        case 27:
            std::exit(EXIT_SUCCESS);
        case ' ':
            state_.paused = !state_.paused;
            break;
        case 'w':
        case 'W':
            state_.yachtY = std::clamp(state_.yachtY + 0.05F, -0.62F, 0.15F);
            break;
        case 's':
        case 'S':
            state_.yachtY = std::clamp(state_.yachtY - 0.05F, -0.62F, 0.15F);
            break;
        case 'a':
        case 'A':
            state_.yachtX = std::max(state_.yachtX - 0.08F, kYachtLeftReset);
            break;
        case 'd':
        case 'D':
            state_.yachtX = std::min(state_.yachtX + 0.08F, kYachtRightBoundary);
            break;
        case 'n':
        case 'N':
            state_.dayMode = !state_.dayMode;
            break;
        case 'f':
        case 'F':
            state_.flagAnimating = !state_.flagAnimating;
            break;
        case 'h':
        case 'H':
            state_.showHelp = !state_.showHelp;
            break;
        case 'm':
        case 'M':
            state_.soundEnabled = !state_.soundEnabled;
            break;
        case 'r':
        case 'R':
            state_.resetYacht();
            break;
        case 'q':
        case 'Q':
            previousScene();
            break;
        case 'e':
        case 'E':
            nextScene();
            break;
        case '1':
        case '2':
        case '3':
        case '4':
            switchToScene(static_cast<int>(key - '1'));
            break;
        case '+':
        case '=':
            state_.yachtSpeed = std::min(state_.yachtSpeed + 0.05F, 1.20F);
            break;
        case '-':
        case '_':
            state_.yachtSpeed = std::max(state_.yachtSpeed - 0.05F, 0.05F);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void App::specialKeyboard(const int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT:
            state_.yachtSpeed = std::max(state_.yachtSpeed - 0.05F, 0.05F);
            break;
        case GLUT_KEY_RIGHT:
            state_.yachtSpeed = std::min(state_.yachtSpeed + 0.05F, 1.20F);
            break;
        case GLUT_KEY_UP:
            state_.yachtY = std::clamp(state_.yachtY + 0.05F, -0.62F, 0.15F);
            break;
        case GLUT_KEY_DOWN:
            state_.yachtY = std::clamp(state_.yachtY - 0.05F, -0.62F, 0.15F);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void App::mouse(const int button, const int buttonState, const int x, const int y) {
    if (button != GLUT_LEFT_BUTTON || buttonState != GLUT_DOWN) {
        return;
    }

    float worldX = 0.0F;
    float worldY = 0.0F;
    if (!screenToWorld(x, y, worldX, worldY)) {
        return;
    }

    scenes_.at(static_cast<std::size_t>(state_.sceneIndex()))->handleClick(worldX, worldY, state_);
    glutPostRedisplay();
}

void App::menu(const int value) {
    switch (value) {
        case kMenuTogglePause:
            state_.paused = !state_.paused;
            break;
        case kMenuToggleFlag:
            state_.flagAnimating = !state_.flagAnimating;
            break;
        case kMenuNextScene:
            nextScene();
            break;
        case kMenuPreviousScene:
            previousScene();
            break;
        case kMenuToggleDay:
            state_.dayMode = !state_.dayMode;
            break;
        case kMenuReset:
            state_.resetYacht();
            break;
        case kMenuToggleHelp:
            state_.showHelp = !state_.showHelp;
            break;
        case kMenuToggleSound:
            state_.soundEnabled = !state_.soundEnabled;
            break;
        case kMenuExit:
            std::exit(EXIT_SUCCESS);
        default:
            break;
    }
    glutPostRedisplay();
}

void App::switchToScene(const int index) {
    if (index == state_.sceneIndex()) {
        return;
    }
    state_.setScene(index);
    audio::notifySceneChange(state_.soundEnabled);
}

void App::nextScene() {
    state_.nextScene();
    audio::notifySceneChange(state_.soundEnabled);
}

void App::previousScene() {
    state_.previousScene();
    audio::notifySceneChange(state_.soundEnabled);
}

void App::drawOverlay() const {
    glDisable(GL_BLEND);
    gfx::setColor({0.02F, 0.04F, 0.08F, 0.80F});
    gfx::rectangle(-1.58F, 0.72F, 1.14F, 0.145F);
    gfx::setColor({1.0F, 1.0F, 1.0F});
    gfx::text(-1.53F, 0.81F, "Scene " + std::to_string(state_.sceneIndex() + 1) + "/4 - " + state_.sceneName(), GLUT_BITMAP_HELVETICA_18);
    gfx::text(-1.53F, 0.755F, "Speed: " + std::to_string(static_cast<int>(state_.yachtSpeed * 100.0F)) + "%  |  " + (state_.paused ? "PAUSED" : "RUNNING"), GLUT_BITMAP_8_BY_13);

    if (state_.showHelp) {
        gfx::setColor({0.02F, 0.04F, 0.08F, 0.82F});
        gfx::rectangle(-1.58F, -0.87F, 3.16F, 0.16F);
        gfx::setColor({1.0F, 1.0F, 1.0F});
        gfx::text(-1.53F, -0.77F, "WASD/Arrows: move & speed | N: day/night | F: flag | Q/E or 1-4: scenes | Space: pause | H: help | Right-click: menu");
        gfx::text(-1.53F, -0.83F, "Tip: left-click the sun or moon to change time of day.");
    }
    glEnable(GL_BLEND);
}

bool App::screenToWorld(const int x, const int y, float& worldX, float& worldY) const {
    const int localX = x - state_.viewportX;
    const int localY = (state_.windowHeight - y) - state_.viewportY;
    if (localX < 0 || localY < 0 || localX >= state_.viewportWidth || localY >= state_.viewportHeight) {
        return false;
    }

    const float nx = static_cast<float>(localX) / static_cast<float>(state_.viewportWidth);
    const float ny = static_cast<float>(localY) / static_cast<float>(state_.viewportHeight);
    worldX = AppState::kWorldLeft + nx * (AppState::kWorldRight - AppState::kWorldLeft);
    worldY = AppState::kWorldBottom + ny * (AppState::kWorldTop - AppState::kWorldBottom);
    return true;
}

void App::displayCallback() {
    instance_->display();
}

void App::reshapeCallback(const int width, const int height) {
    instance_->reshape(width, height);
}

void App::timerCallback(int) {
    instance_->update();
    glutTimerFunc(kTimerIntervalMs, timerCallback, 0);
}

void App::keyboardCallback(const unsigned char key, const int x, const int y) {
    instance_->keyboard(key, x, y);
}

void App::specialKeyboardCallback(const int key, const int x, const int y) {
    instance_->specialKeyboard(key, x, y);
}

void App::mouseCallback(const int button, const int buttonState, const int x, const int y) {
    instance_->mouse(button, buttonState, x, y);
}

void App::menuCallback(const int value) {
    instance_->menu(value);
}

} // namespace yacht
