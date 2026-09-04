#pragma once

#include <algorithm>
#include <array>
#include <string>

namespace yacht {

enum class SceneId : int {
    Beach = 0,
    Mountains,
    City,
    Harbor,
    Count
};

struct AppState {
    SceneId scene{SceneId::Beach};

    float elapsedSeconds{0.0F};
    float yachtX{-1.75F};
    float yachtY{-0.28F};
    float yachtSpeed{0.32F};

    bool paused{false};
    bool dayMode{true};
    bool flagAnimating{true};
    bool showHelp{true};
    bool soundEnabled{true};

    int windowWidth{1280};
    int windowHeight{720};
    int viewportX{0};
    int viewportY{0};
    int viewportWidth{1280};
    int viewportHeight{720};

    static constexpr float kWorldLeft = -1.6F;
    static constexpr float kWorldRight = 1.6F;
    static constexpr float kWorldBottom = -0.9F;
    static constexpr float kWorldTop = 0.9F;

    [[nodiscard]] int sceneIndex() const noexcept {
        return static_cast<int>(scene);
    }

    [[nodiscard]] std::string sceneName() const {
        static constexpr std::array<const char*, 4> names{
            "Beach Escape",
            "Mountain Passage",
            "Coastal City",
            "Cargo Harbor"
        };
        return names.at(static_cast<std::size_t>(sceneIndex()));
    }

    void nextScene() noexcept {
        const int next = (sceneIndex() + 1) % static_cast<int>(SceneId::Count);
        scene = static_cast<SceneId>(next);
    }

    void previousScene() noexcept {
        const int count = static_cast<int>(SceneId::Count);
        const int previous = (sceneIndex() - 1 + count) % count;
        scene = static_cast<SceneId>(previous);
    }

    void setScene(int index) noexcept {
        const int count = static_cast<int>(SceneId::Count);
        index = std::clamp(index, 0, count - 1);
        scene = static_cast<SceneId>(index);
    }

    void resetYacht() noexcept {
        yachtX = -1.75F;
        yachtY = -0.28F;
        yachtSpeed = 0.32F;
        paused = false;
    }
};

} // namespace yacht
