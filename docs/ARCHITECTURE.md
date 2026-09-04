# Architecture

## Overview

The application uses classic immediate-mode OpenGL through GLUT/FreeGLUT. The design separates framework callbacks from application state, reusable geometry, object composition, and scene rendering.

```text
main
└── App
    ├── AppState
    ├── Scene[4]
    │   ├── BeachScene
    │   ├── MountainsScene
    │   ├── CityScene
    │   └── HarborScene
    ├── Yacht
    ├── GraphicsPrimitives
    └── Audio
```

## Modules

### `App`

Owns the application state, scene objects, yacht renderer, GLUT callback routing, menus, fixed-interval update loop, coordinate conversion, viewport management, and heads-up display.

### `AppState`

Stores scene selection, yacht position and speed, elapsed time, day/night mode, pause state, flag animation state, help visibility, sound preference, and viewport geometry.

### `GraphicsPrimitives`

Provides reusable wrappers for rectangles, circles, ellipses, polygons, lines, stars, clouds, text, gradients, and color interpolation.

### `Yacht`

Builds the yacht hierarchically from a hull, cabin, mast, sails, wake, and Bangladesh flag. The flag surface is generated from cubic Bézier curves and animated through time-dependent control points.

### Scene classes

Each scene is responsible only for its environment. It reads shared state but does not own the timer or input callbacks.

### `Audio`

Contains the only platform-specific notification code. On Windows, scene transitions can invoke a system notification sound. Other platforms remain silent without breaking the build.

## Rendering flow

1. GLUT calls `App::display`.
2. The active scene renders its background and environment.
3. `Yacht` renders above the scene.
4. `App` renders the HUD.
5. The back buffer is swapped.

## Update flow

1. A 16 ms GLUT timer invokes `App::update`.
2. Elapsed time is calculated and clamped.
3. The yacht moves when not paused.
4. Crossing the right boundary resets the yacht and advances the scene.
5. Redisplay is requested.

## Input design

A single keyboard callback, special-key callback, mouse callback, and menu callback are registered. This prevents the callback-overwrite problem found in many monolithic GLUT projects.

## Coordinate system

The world uses a fixed 16:9 logical coordinate system:

- X: `-1.6` to `1.6`
- Y: `-0.9` to `0.9`

The reshape handler uses letterboxing to preserve the aspect ratio. Mouse coordinates are translated through the active viewport before scene interaction.


## Original yacht renderer

`src/Yacht.cpp` intentionally uses the original project’s immediate-mode coordinate geometry rather than the simplified reconstruction yacht. It remains encapsulated behind the `Yacht::draw(const AppState&)` interface, allowing the original artwork to coexist with the updated scene and application architecture.
