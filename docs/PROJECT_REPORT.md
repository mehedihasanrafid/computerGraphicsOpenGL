# Yacht Journey — Project Report

## Abstract

Yacht Journey is an interactive two-dimensional computer graphics application developed with C++17, OpenGL, and GLUT/FreeGLUT. The application follows an animated yacht through four environments: a beach, a mountain passage, a coastal city, and a cargo harbor. It demonstrates geometric modeling, affine transformations, hierarchical composition, cubic Bézier curves, state-driven scene management, timer-based animation, interactive input, and viewport-preserving rendering.

## Objectives

- Model complex visual objects from fundamental OpenGL primitives.
- Animate a yacht and environmental objects using elapsed time.
- Demonstrate translation, scaling, and hierarchical composition.
- Provide keyboard, mouse, and right-click menu interaction.
- Support automatic and manual scene transitions.
- Present a maintainable alternative to a monolithic graphics program.

## Functional requirements

1. Render four visually distinct marine scenes.
2. Move the yacht automatically from left to right.
3. Advance to the next scene when the yacht exits the viewport.
4. Permit manual movement and speed control.
5. Toggle day and night modes.
6. Pause and resume yacht motion.
7. Start and stop flag animation independently.
8. Preserve the visual aspect ratio when the window is resized.
9. Provide contextual controls through a right-click menu.
10. Build on Windows and Linux using CMake and FreeGLUT-compatible dependencies.

## Graphics techniques

### Primitive construction

The project uses points generated for quads, polygons, triangles, lines, circles, ellipses, stars, and clouds. Reusable primitive functions reduce duplication across scenes.

### Transformations

The yacht is modeled in local coordinates and then translated to its world position. Scaling is applied to the assembled yacht while child components remain hierarchically aligned.

### Bézier animation

The Bangladesh flag is formed between two cubic Bézier curves. Time-dependent control points produce a smooth wave while preserving the flag's overall shape.

### Gradient backgrounds

Each scene uses vertex color interpolation to create a vertical sky or water gradient. Day/night state selects different color palettes.

### Timer-based motion

A recurring timer calculates delta time and updates the yacht. Clouds, planes, boats, wake elements, and flag movement are derived from total elapsed time, avoiding separate conflicting timers.

## Scene descriptions

### Scene 1 — Beach Escape

A warm coastal environment containing a gradient sky, sun or moon, clouds, mountains, sea, beach, palms, umbrella, waves, and the moving yacht.

### Scene 2 — Mountain Passage

A cooler landscape with layered mountains, snow caps, forested shoreline, moving clouds, aircraft, and open water.

### Scene 3 — Coastal City

An urban waterfront with multiple buildings, procedural window layouts, trees, changing window illumination, clouds, and water reflections.

### Scene 4 — Cargo Harbor

An industrial dock containing stacked containers, cranes, cargo ship, moving service boats, dock surfaces, and harbor water.

## Controls

| Input | Action |
|---|---|
| `W` / `S` | Move yacht vertically |
| `A` / `D` | Move yacht horizontally |
| Arrow Up / Down | Move yacht vertically |
| Arrow Left / Right | Decrease/increase speed |
| `+` / `-` | Increase/decrease speed |
| `N` | Toggle day/night |
| `F` | Toggle flag animation |
| `Space` | Pause/resume yacht |
| `Q` / `E` | Previous/next scene |
| `1`–`4` | Select scene directly |
| `R` | Reset yacht position and speed |
| `H` | Show/hide help |
| `M` | Enable/disable Windows scene sound |
| Left-click sun/moon | Toggle day/night |
| Right-click | Open application menu |
| `Esc` | Exit |

## Improvements over the original repository structure

- Splits rendering and behavior into focused source files.
- Eliminates conflicting use of the `D` key.
- Registers each GLUT callback once.
- Uses double buffering consistently.
- Clamps movement speed.
- Preserves aspect ratio during resize.
- Converts mouse coordinates through the letterboxed viewport.
- Removes dependence on an external WAV file.
- Adds CMake, scripts, CI, documentation, and portfolio attribution.

## Limitations

- Uses legacy immediate-mode OpenGL for educational compatibility.
- Visual behavior is deterministic rather than physics-based.
- Automated visual regression tests are not included.
- Scene notification sound is implemented only on Windows.

## Future work

- Port rendering to modern OpenGL with shaders and vertex buffers.
- Add texture loading and sprite-based effects.
- Add a scene editor and configuration files.
- Add frame capture and automated screenshot tests.
- Package native releases for Windows and Linux.
