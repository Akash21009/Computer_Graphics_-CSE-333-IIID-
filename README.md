# Assignment and Lab Instructions

To run any assignment or lab, follow these steps in your terminal:

1. **run this command to view output**
   ```bash
   ./<laborassignmentname>
   
example : ./Assignment01

To run in case you made some changes in code, follow these steps in your terminal:

1. **Delete the following files if they exist:**
   ```bash
   rm -f Makefile CMake_install.cmake CMakeCache.txt <laborassignmentname>.exe
2. **Build again:**
   ```bash
   cmake CMakeLists.txt
   make
3. **run output file**
   ```bash
   ./<assignmentorlabname>
