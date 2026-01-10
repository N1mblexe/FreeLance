# Airline Crew Rostering

Small C++17 project containing custom data structures and a basic crew rostering engine used for teaching and prototyping.

- Build: `make`
- Run: `./roster`

Project layout:
- `include/` — public headers
- `src/` — implementation sources
- `data/` — sample data files

Notes:
- Project enforces `-Wall -Wextra -Werror` in the `Makefile`.
- The current `FileParser` is a lightweight ad-hoc parser for sample JSON. For production use, replace with a proper JSON library (e.g. `nlohmann/json`).

Quick start
```
make clean && make -j1
./roster
```

Authors: Project scaffold generated and maintained in this workspace.
