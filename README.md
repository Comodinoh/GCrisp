# How to build
## Linux
 Clone the repository in a folder with ``git clone https://github.com/Comodinoh/GCrisp.git my-folder``. Go into the folder with ``cd my-folder``.
 
 Make sure that the C3 compiler ``c3c``, ``glfw`` and ``make-essentials``(on Ubuntu/Debian) or ``base-devel``(on Archlinux) are installed.
 
 Run ``make`` in the cloned folder.
 The binary ``gcrisp`` should have been created in the folder you're in.
## Windows and OSX
To Be Done.

# TODO
- Implement custom rendering raylib wrappers
- Write shaders for heavy gpu effects
- Implement custom character rendering
- ~Implement functionality for conditional actions and branching~ <- Partially completed
- ~Add API for script and scene creation~ <- Completed
- Add built-in actions for backgrounds, character rendering, effects, etc.
- Move character, effects, background code outside of main script module
- Improve font rendering
- Add size and resolution customization
- Make script parser
- Create a good parsing language and structure for scripting
- Implement better memory management and resolve memory leaks

