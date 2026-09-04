# Changelog

## 2.1.0 — Original Yacht Design Edition

- replaced the reconstruction yacht with the original team-designed yacht geometry;
- preserved the original hull, decks, windows, portholes, rudder structure, railings, antenna, colors, and Bangladesh flag;
- connected the original Bézier flag geometry to the updated time-based animation state;
- retained the improved four scenes, controls, resizing, build system, and CI;
- added `docs/ORIGINAL_YACHT_DESIGN.md`.

## 2.0.0 — Portfolio reconstruction

### Added

- Modular C++17 application architecture
- Four independent scene classes
- Reusable graphics primitives
- Hierarchical yacht renderer
- Cubic Bézier Bangladesh flag animation
- Centralized delta-time update loop
- Keyboard, special-key, mouse, and menu controls
- Responsive 16:9 viewport and coordinate conversion
- CMake build configuration
- Linux and Windows build scripts
- GitHub Actions build workflow
- Architecture, project report, contribution, CV, GitHub setup, and validation documentation
- SVG project preview

### Fixed by design

- Conflicting keyboard responsibilities
- Multiple mouse callbacks replacing one another
- Mixed single- and double-buffer behavior
- Unbounded animation speed
- Platform-specific audio spread across rendering code
- Monolithic scene and object implementation
- Missing resize handling
- Missing attribution and portfolio documentation
