# Run on Linux Mint

## 1. Install dependencies

```bash
sudo apt update
sudo apt install -y build-essential cmake libglut-dev libglu1-mesa-dev
```

## 2. Enter the project folder

```bash
cd ~/Downloads/opengl-yacht-journey-original-design
```

Use quotes if you place the project inside a folder whose name contains spaces.

## 3. Build and run

```bash
chmod +x scripts/build_and_run_linux.sh
./scripts/build_and_run_linux.sh
```

Alternatively:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/yacht_journey
```

## Controls

- `W/A/S/D`: move the yacht;
- arrow up/down: move vertically;
- arrow left/right or `+/-`: change speed;
- `N`: day/night;
- `F`: flag animation;
- `Q/E` or `1-4`: change scene;
- space: pause;
- `R`: reset;
- right-click: menu;
- `Esc`: exit.
