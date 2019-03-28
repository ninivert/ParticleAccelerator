# Folder structure

- `/`: `Makefile`, `README.md`, `.gitignore`
- `/assets`: images, saves, config, etc.
- `/bin`: executables (`.bin`)
- `/build`: compiled files (`.o`)
- `/dev`: useful files for unified development (snippets, etc.)
- `/docs`: documentation for the project
- `/doxydocs`: Doxygen-generated documentation (run with `make run_docs`)
- `/lib`: third party libraries (openGL, Qt, etc.)
- `/src`: source code
	- `/includes`: class headers (`.h`)
		- `/bundle`: bundled class headers, see Conception (`.bundle.h`)
	- `/lib`: class implementations (`.cpp`)
- `/test`: test scripts
	- `/bin`: executable test cases
	- `/build`: compiled test cases
	- `/lib`: test utility classes
	- `/src`: test cases source code
