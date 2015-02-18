Builder - High Level Design
===========================

Builder is an attempt to make a new C/C++ Build Tool that can be used for a variety of projects on a variety of platforms. This is no easy task. As such, the goal is to have a tool that doesn't do very much itself, but instead delegates all of the work to a series of plugins that can be made available. The idea is that Everything is a Plugin. This means that if a developer wants to use the tool on a platform that is not currently supported - e.g. using a new compiler - then they can simply write a plugin that does the appropriate work.

The Plugins will all be written as scripts in the Lua programming language. The main program will expose hooks as appropriate to the plugins that are being loaded. 

Plugin Types
------------

Different parts of the build process need to do different things. Some of these things will be core to the system - e.g. finding source files or tidying up build directories - and some of these things will be controlled by Plugins. 

In some cases, there may be multiple Plugins that can implement the same behaviour. To support this, Plugins will be written to have a priority, and all usable ones will be executed in priority order until one is successful. One example of this is the plugins to load Dependency information, if you have a plugin to use pkg-config but want to have a more specific plugin for a dependency that does something slightly different.

### Compiler Plugin
The Compiler Plugins are responsible for taking an Input source file and producing an Output object file.

### Linker Plugin
The Linker Plugins are responsible for taking a collection of Input object files and producing an Output artifact - which may be an Executable, a Shared Library, a Static Library or something altogether different.

### Dependency Plugin
The Dependency Plugins are responsible for taking a dependency name and determining the Compiler and Linker options to use for that dependency.

### Test Plugin
The Test Plugins are responsible for taking a collection of Input source files - the unit tests - and executing them.

### Custom Plugin
Some extra functionality can only be performed by having a custom plugin that performs some action at some point in the build process.
