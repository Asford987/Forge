# Forge

<!-- ![image](res/forge.webp) -->
Cargo like C++ project manager

<!-- Allows seamless integration with other languages (Rust, Python, Go, Zig, ...) -->

<!-- Use .toml to manage CMakeLists.txt -->

- Forge install (--global for global installation, default is project. Also capable of installing directly from github, if a url is passed)
- Forge publish
- Forge build (--arch for defining pc architecture)
- Forge run
- Forge new (--bin (default) --lib)

<!-- For writing the CMakeLists.txt: sharding mechanism inplemented (CMakeLists.txt is split in several sections, each being changed by each command, and once build/run is called, CMakeLists.txt will be composed and then ran) -->
