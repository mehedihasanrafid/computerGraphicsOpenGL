# Validation

## Completed checks

- All C++ translation units passed a C++17 syntax-only compilation.
- Warning flags used during validation:
  - `-Wall`
  - `-Wextra`
  - `-Wpedantic`
  - `-Wconversion`
  - `-Wshadow`
- No warnings remained after cleanup.
- Header dependencies were verified through a minimal GLUT/OpenGL interface stub because the generation environment did not include the FreeGLUT development package.
- Repository paths, CMake source lists, include paths, build scripts, documentation links, and workflow paths were checked.

## Not executed in the generation environment

The graphical executable was not linked or launched because OpenGL/FreeGLUT development libraries and a display server were unavailable. Build it on Linux Mint, Ubuntu, or Windows using the instructions in `README.md`.

## Manual acceptance test

After building, verify:

1. The application opens at 1280×720.
2. Scene 1 renders and the yacht moves left to right.
3. The next scene loads automatically after the yacht exits.
4. Keys `1`–`4` select the correct scenes.
5. `W`, `A`, `S`, `D` move the yacht without changing day/night mode.
6. `N` changes day/night mode.
7. Clicking the sun or moon changes day/night mode.
8. `Space` pauses and resumes the yacht.
9. `F` stops and starts the flag wave.
10. Arrow Left/Right and `+`/`-` change speed within safe limits.
11. Right-click opens the menu and every command works.
12. Resizing the window preserves the 16:9 scene without stretching.
13. The HUD remains readable.
14. The application exits using `Esc` and the menu.
