# Contributing

This repository is a portfolio reconstruction of a collaborative university project. Contributions should improve code quality while preserving accurate attribution.

## Workflow

1. Create a branch from `main`.
2. Make one focused change.
3. Build locally with CMake.
4. Use clear commit messages.
5. Open a pull request explaining the change and validation.

## Code conventions

- C++17
- Four-space indentation
- `PascalCase` for classes
- `camelCase` for functions and variables
- Prefer small rendering helpers over duplicated OpenGL blocks
- Keep mutable application state inside `AppState`
- Register each GLUT callback once and route behavior internally
- Avoid platform-specific code outside dedicated modules

## Attribution

Do not remove the original-project reference or convert collaborative work into an individual claim. Update `docs/CONTRIBUTIONS.md` when responsibilities are verified.
