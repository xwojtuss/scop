# ft_vox
A simple voxel engine built with modern C++ and Vulkan. The project is designed to be a learning experience for graphics programming and engine development, with a focus on clean code and modular design.

**WORK IN PROGRESS**

## Prerequisites

- C++17 compatible compiler
- CMake 3.25 or later
- Vulkan SDK
- GLFW (auto-fetched)
- GLM (auto-fetched)
- ImGui (auto-fetched)
- stb_image (single header, included)
- tinyobjloader (single header, included)
- nlohmann/json (single header, included)

## Getting Started
After cloning the repository you can build the project using cmake:

```bash
cmake --preset dev-clang
cmake --build --preset dev-clang
```

Then run the executable:
```bash
./build/dev-clang/scop
```

## Documentation

To generate documentation (might take a while):
```bash
cmake --build --preset dev-clang --target generate_docs
```

## Author
* **Wojtek Kornatowski** - [xwojtuss](https://github.com/xwojtuss)