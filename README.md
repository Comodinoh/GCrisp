# Usage
## Linux
__Note:__ needs CMake >= 3.30.4 and Make

To use GCrisp in your project, you can import it with CMake by making a submodule:
```bash
    git submodule add https://github.com/Comodinoh/GCrisp.git lib/GCrisp
    git submodule update --remote --recursive
```

Then add that folder as a subdirectory in your `CMakeLists.txt` file and link the library with:
```CMake 
    add_subdirectory(lib/GCrisp)
    target_link_libraries(${PROJECT_NAME} PUBLIC gcrisp)
```
    
Now you can use the headers of the library :

```c++
#include <GCrisp/core.h>
// ... do stuff
```


# Building & Installing
## Linux
__Note__: needs CMake >= 3.30.4, Make and SDL3
****

### Building
```bash
    git clone --recursive https://github.com/Comodinoh/GCrisp.git
    cd GCrisp/out
    cmake ../
    make
```
The static library file `libgcrisp.a` will be inside the `GCrisp/out` folder.

****

### Installing
```bash
    git clone --recursive https://github.com/Comodinoh/GCrisp.git
    cd GCrisp/out
    cmake ../
    make install
```
This will install the static library `libgcrisp.a` inside your default lib folder (ex: `/usr/lib`)

