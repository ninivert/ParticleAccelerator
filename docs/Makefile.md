# Available make commands

- `make` : make all changed targets
	- Compilation
	- Link Editor

## Compilation

- `make Vector3D.o` : compile Vector3D.o
- `make testVector3D.o` : compile testVector3D.o
- `make Test.o` : compile Test.o

## Link editor

- `make testVector3D.bin` : link testVector3D.bin


## Run

- `make run_testVector3D` : run tests for `Vector3D`

## Clean

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


# make options

- `-B` : Unconditionally make all targets
- `-n -B` : Print the commands that would be executed, but do not execute them
