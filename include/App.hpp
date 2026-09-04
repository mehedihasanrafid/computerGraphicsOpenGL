#pragma once

#include "AppState.hpp"
#include "Scene.hpp"
#include "Yacht.hpp"

#include <array>
#include <memory>

namespace yacht {

class App {
public:
    App();
    int run(int argc, char** argv);

private:
    static App* instance_;

    AppState state_{};
    Yacht yacht_{};
    std::array<std::unique_ptr<Scene>, 4> scenes_{};
    int lastFrameTimeMs_{0};

    void initializeGlut(int argc, char** argv);
    void initializeScenes();
    void createMenu();

    void display();
    void reshape(int width, int height);
    void update();
    void keyboard(unsigned char key, int x, int y);
    void specialKeyboard(int key, int x, int y);
    void mouse(int button, int buttonState, int x, int y);
    void menu(int value);

    void switchToScene(int index);
    void nextScene();
    void previousScene();
    void drawOverlay() const;
    [[nodiscard]] bool screenToWorld(int x, int y, float& worldX, float& worldY) const;

    static void displayCallback();
    static void reshapeCallback(int width, int height);
    static void timerCallback(int value);
    static void keyboardCallback(unsigned char key, int x, int y);
    static void specialKeyboardCallback(int key, int x, int y);
    static void mouseCallback(int button, int buttonState, int x, int y);
    static void menuCallback(int value);
};

} // namespace yacht
