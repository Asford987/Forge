# Forge

Cargo like C++ project manager

Allows seamless integration with other languages (Rust, Python, Go, Zig, ...)

Use .toml to manage CMakeLists.txt

- Forge install (--global for global installation, default is project. Also capable of installing directly from github, if a url is passed)
- Forge publish
- Forge build (--arch for defining pc architecture (if --bin), --lang for language integration (if --lib))
- Forge run
- Forge new (--bin (default) --lib)
