# `Makefile`

## Available make commands

- `make` : make all changed targets
	- Compilation
	- Link Editor
	- Docs

### Compilation

- `make <Name>.o` : compile `<Name>.o`

Names :

- Vector3D
- Particle
- Element
- MagnetElement
- ElectrElement
- Accelerator

- Test
- testVector3D
- testParticle
- testAccelerator
- testConverter

### Link editor

- `make <Name>.bin` : link `<Name>.bin`

Names :

- testVector3D
- testParticle
- testAccelerator
- testConverter

### Run

- `make run_<Name>` : run tests for `<Name>`

Names :

- testVector3D
- testParticle
- testAccelerator
- testConverter

### Clean

- `make cleanbin` : remove all bin files from
	- `/bin`
	- `/test/bin`

- `make cleanbuild` : remove all build files from
	- `/build`
	- `/test/build`

- `make clean` : remove all binary and build files from
	- `/bin`
	- `/build`
	- `/test/bin`
	- `/test/build`

### Dir

- `make dir` : Create necessary directories for the makefile to word

### Docs

- `make docs` : generate documentation `index.html`
- `make run_docs` : open `index.html`

## make options

- `-B` : Unconditionally make all targets
- `-n -B` : Print the commands that would be executed, but do not execute them
