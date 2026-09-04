# Original Yacht Design Preservation

## Source

The yacht geometry in `src/Yacht.cpp` was extracted from the collaborative university project hosted at:

`Shihab-Abesh/Computer-graphics`

## Preserved visual elements

- original polygonal hull coordinates and dark-blue fill;
- purple first-floor superstructure;
- metallic upper-deck polygon;
- cyan front-deck polygon;
- black window strip and white dividers;
- six circular portholes with red outlines;
- center deck decoration;
- sail-deck platform;
- second-floor and third-floor structures and windows;
- rudder/control tower and blue decorations;
- fence/rail geometry;
- antenna platform and antenna;
- Bangladesh flag colors, proportions, pole, and cubic Bézier wave geometry.

## Modernized around the yacht

The following areas were modernized without redesigning the yacht:

- modular C++17 source organization;
- delta-time movement and automatic scene transitions;
- bounded controls without the old `D` key conflict;
- single mouse callback routing;
- consistent double buffering;
- responsive aspect-ratio handling;
- CMake and GitHub Actions;
- documentation and explicit team attribution.

## Accuracy note

Minor code-level corrections were made where required for a standalone module—for example, removing invalid `glEnd()` calls outside drawing blocks and using time-based values for the original flag control points. These corrections do not intentionally change the visual design.
