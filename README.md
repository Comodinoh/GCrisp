# Usage
## Linux
__Note:__ CMake >= 3.30.4 required

To use GCrisp in your project, you can import it with CMake by making a submodule:
```bash
    git submodule add https://github.com/Comodinoh/GCrisp.git lib/GCrisp
    git submodule update --init --remote --recursive lib/GCrisp
```

Then add that folder as a subdirectory in your `CMakeLists.txt` file and link the library with:
```CMake 
    add_subdirectory(lib/GCrisp)
    target_link_libraries(${PROJECT_NAME} PUBLIC gcrisp)
```
    
Now you can use the header of the library:

```c++
#include <GCrisp/GCrisp.h>
// ... do stuff
```
