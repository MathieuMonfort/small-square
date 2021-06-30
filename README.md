# Small Square Game Engine
## Building Small Square
### NixOS
#### NixOS with CLion
If you're using NixOS, you probably know how awesome it is. 
All you need to do to build the project and modify it with CLion is cd into small-square root directory and 

	nix-shell shell.nix

Then from the Nix Shell:

	clion

And you're ready to go.

#### NixOS without CLion
if you don't want nix-shell to install clion you just need to remove this line from shell.nix

	pkgs.jetbrains.clion

and either replace it with you're favorite IDE or write nothing.
It will work as long as you launch cmake and make from the nix-shell.

### Requirements
To build small-square libraries you need to download a bunch of external libraries

Fedora
    
    sudo dnf install git g++ cmake glm-devel libX11-devel libgl1-mesa-dev

Debian
    
    sudo apt-get install git g++ cmake xorg-dev libglm-dev 

NixOS

No requirements needed if you use nix-shell shell.nix cause NixOS rocks!!!

#### GLFW3
glfw3 is a common OpenGL library, you need to build it from source. 
You can clone gflw from github : https://github.com/glfw/glfw 
Build it with (when in glfw _directory)
        
    mkdir build
    cd build 
    cmake ../
    make 
    sudo make install

#### GLAD
This is a tricky one (will be built in situ in future builds)

Go to https://glad.dav1d.de/

setup this way:

    Language : c/c++
    Specification : OpenGL
    Profile : core
    API : gl : Version 3.3
    Check "Generate a Loader"

Generate & download given .zip
Copy the content of the include _directory into your 

    /usr/include 

_directory (you probably need super user privileges).

#### Assimp
Assimp is the Open Asset Import Library (Manages 3d models imports).
clone the source from https://github.com/assimp/assimp
Build with (when in assimp _directory):

    kdir build   cd build
    cmake ../ -DBUILD_SHARED_LIBS=ON -DASSIMP_BUILD_ZLIB=ON
    make 
    sudo make install

### Building
Clone the source and build with ( in small-square _directory) :

    mkdir build
    cd build 
    cmake ../
    make

Then test the sample code with ( in small-square _directory) : 

    ./samples/sample

