#Small Square Game Engine



##Building Small Square
###Requirements
To build small-square libraries you need to download a bunch of external libraries

fedora
    
    sudo dnf install git g++ cmake glm-devel libX11-devel

debian
    
    sudo apt-get install git g++ cmake xorg-dev libglm-dev 

####GLFW3
glfw3 is a common OpenGL library, you need to build it from source. 
You can clone gflw from github : https://github.com/glfw/glfw 
Build it with (when in glfw directory)
        
    mkdir build
    cd build 
    cmake ../
    make 
    sudo make install

####GLAD
This is a tricky one (will be built in situ in future builds)

Go to https://glad.dav1d.de/

setup this way:

    Language : c/c++
    Specification : OpenGL
    Profile : core
    API : gl : Version 3.3
    Check "Generate a Loader"

Generate & download given .zip
Copy the content of the include directory into your 

    /usr/include 

directory (you probably need super user privileges).

####Assimp
Assimp is the Open Asset Import Library (Manages 3d models imports).
clone the source from https://github.com/assimp/assimp
Build with (when in assimp directory):

    kdir build   cd build
    cmake ../ -DBUILD_SHARED_LIBS=ON -DASSIMP_BUILD_ZLIB=ON
    make 
    sudo make install

###Building
Clone the source and build with ( in small-square directory) :

    mkdir build
    cd build 
    cmake ../
    make

Then test the sample code with ( in small-square directory) : 

    ./samples/sample

