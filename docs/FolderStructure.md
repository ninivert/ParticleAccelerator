# Folder structure

- `/`: `Makefile`, `Doxyfile`, `README.md`, `.gitignore`, etc.
- `/assets`: images, saves, config, etc.
- `/bin`: executables (`.bin`)
- `/build`: compiled files (`.o`)
- `/dev`: useful files for unified development (snippets, etc.)
- `/docs`: documentation for the project
- `/doxydocs`: Doxygen-generated documentation (run with `make run_docs`)
- `/common`: source code common to all binaries
	- `/includes`: class headers (`.h`)
		- `/bundle`: bundled class headers, see Conception (`.bundle.h`)
	- `/lib`: class implementations (`.cpp`)
- `/apps`: binaries source code
	- `/app`: main executable
	- `/exercices`: exercices
	- `/tests`: tests
- `/log`: logs from tests
