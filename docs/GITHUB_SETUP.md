# GitHub Setup

## Recommended repository name

`opengl-yacht-journey`

## Upload with Git

From the extracted project folder:

```bash
git init
git branch -M main
git add .
git commit -m "Rebuild OpenGL yacht journey as a portfolio project"
git remote add origin https://github.com/mehedihasanrafid/computerGraphicsOpenGL.git
git push -u origin main
```

Your target repository is currently empty, so the first push should initialize it.

## Preserve the original team reference

Keep the original repository URL in `README.md`, `NOTICE.md`, and `docs/CONTRIBUTIONS.md`.

## Repository settings

1. Add the repository description from `docs/CV_ENTRY.md`.
2. Add the recommended topics.
3. Enable Issues.
4. Keep GitHub Actions enabled.
5. Add screenshots after running the program.
6. Pin the repository on your GitHub profile.

## Suggested first release

Tag: `v2.0.0-portfolio`

Release title: `Portfolio Reconstruction v2.0.0`

Release notes:

```markdown
- Rebuilt the collaborative yacht-animation concept using modular C++17.
- Added four independent scenes and a hierarchical yacht renderer.
- Added Bézier flag animation, day/night interaction, HUD, menus, and responsive viewport handling.
- Corrected callback, buffering, speed, input, and portability problems.
- Added CMake, Linux/Windows build scripts, GitHub Actions, and complete documentation.
```
