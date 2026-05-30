# Custom GPS NEO-6M Chip for Wokwi (VS Code)

This repository contains a custom GPS NEO-6M chip for Wokwi. The chip is implemented in C, compiled to WebAssembly, and wired into a Wokwi diagram so you can run the simulation directly from VS Code.

## Features

- Custom GPS NEO-6M chip for Wokwi
- Chip logic written in C and compiled to WebAssembly
- Example configuration included in `diagram.json`

## Usage
To use this chip in your project, include it as a dependency in your diagram.json file:

```json
{
  "dependencies": {
    "chip-gps-neo6m": "github:erickweil/gps-neo-6m-wokwi-for-vscode@1.0.0"
  }
}
```
Then, add the chip to your circuit by adding a chip-gps-neo6m item to the parts section of diagram.
```json
{
  "parts": [
    ...,
    { "type": "chip-gps-neo6m", "id": "gps" }
  ]
}
```

## Project Structure

- `chips/` — chip sources and generated `*.wasm`
- `src/` — PlatformIO application code
- `diagram.json` — Wokwi diagram
- `wokwi.toml` — Wokwi configuration

## Prerequisites

- VS Code
- Wokwi VS Code Extension
- Wokwi CLI (for chip compilation)
- PlatformIO (for build/flash)

## Build the Chip

Run the following command from the project root:

```bash
wokwi-cli chip compile chips/gps-neo6m.chip.c -o chips/gps-neo6m.chip.wasm
```

## Run the Simulation

1. Open `diagram.json` in VS Code.
2. Click Run in Wokwi.
3. Ensure `wokwi.toml` points to `diagram.json` and `chips/*.wasm` is compiled.

## Use in Your Diagram

An example is already included in `diagram.json`. To reuse the chip in another project:

1. Copy `chips/gps-neo6m.chip.json` and `chips/gps-neo6m.chip.wasm`.
2. Add the chip to your `diagram.json`.

## License

Choose a license for your project (for example, MIT).
