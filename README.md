# NetworkExtended
Is graphical and command line tool for Complex Networks written in C and using the [NetworkX](http://networkx.lanl.gov) python module, the [NetEvo](http://netevo.org) C computing framework and the [openFrameworks](http://www.openframeworks.cc) C++ toolkit.

This package uses the [semver](http://semver.org/) approach for versions. The very first version will be called 0.1.0-alpha but it's not ready for that yet. For more see Development section.

## Involved packages
Here is the description of each package involved in this project.

### NetworkX
NetworkX is a Python language software package for the creation, manipulation, and study of the structure, dynamics, and functions of complex networkx.

### NetEvo
NetEvo is a computing framework and collection of end-user tools designed to allow researchers to investigate evolutionary aspects of dynamical complex networks.

### openFrameworks
openFrameworks is an open source C++ toolkit designed to assist the creative process by providing a simple and intuitive framework for experimentation.

## Development
For develop NetworkExtended you must have the development libraries of Python, openFrameworks (with all it's dependencies) and a working installation of NetworkX and NetEvo for Python. Also, you must have a compatible C++ compiler, for instance `GCC`. The `make` utility is highly recommended.

For CLI branch you must have a working [`bison`](http://www.gnu.org/software/bison/) and [`flex`](http://flex.sourceforge.net/) installation or their compatible [`yacc`](http://dinosaur.compilertools.net/yacc/) and [`lex`](http://dinosaur.compilertools.net/lex/) to compile the code. On this branch a Python-like language for Complex Networks will be developed.

The GUI branch has the openFrameworks connection and the current development is centered on this.

Both branches will be merged to the master branch on 1.0.0 version. By now each one have its own milestones written in TODO file.
