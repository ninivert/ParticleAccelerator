# Particle Accelerator

## OwO what's this ?

This project simulates the behavior of a very simplified particle accelerator.\
In the current configuration, it is a simple circular accelerator composed of straight elements, focalizer elements, and dipoles.\
It is planned to add a way to edit the accelerator, but you can of course simply add it manually by modifying the code and recompiling.

## Controls

| Key | Description |
| --- | --- |
| W | Camera forward |
| S | Camera backward |
| A | Camera left |
| D | Camera right |
| Q | Camera down |
| E | Camera up |
| Space | Pause physical simulation |
| Up | Increase simulation speed |
| Down | Decrease simulation speed |

## Compilation

Requirements: `qt5-default`

```sh
qmake && make && bin/app.bin
```

See `docs/Conception.md` for more information.

## Further development

- Integrate our project with Qt completely
- Rewrite a few classes for neater code
- Add a good accelerator editor
- Add auto calibrator (adjust magnetic fields and speeds)
- Add floor/sky box
- Add emittance graph
- Fix lighting issues
