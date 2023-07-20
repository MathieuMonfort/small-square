Building Small Square
=====================

===================
Building on Windows
===================
..
    TODO Build guide for windows.

There's no guide to build on Windows yet.


=================
Building on Linux
=================

Requirements
~~~~~~~~~~~~
* git
* g++
* libX11
* cmake
* glfw3
* glm
* assimp

~~~~~~~~~~~~~~~
Debian/Ubuntu
~~~~~~~~~~~~~~~
..
    TODO Find Dependency libraries for Debian.

.. code-block:: console

    sudo apt install git g++ cmake xorg-dev libglm-dev

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Fedora/Redhat/CentOS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.. code-block:: console

    sudo dnf isntall git gcc cmake libX11-devel glfw-devel glm-devel assimp-devel

~~~~~~~~~~~~~~~
Arch
~~~~~~~~~~~~~~~
..
    TODO Find Dependency libraries for Arch.


Cmake Configuration
~~~~~~~~~~~~~~~~~~~
Clone and prep the small-square repository

.. code-block:: console

    git clone git@github.com:MathieuMonfort/small-square.git
    cd small-square
    mkdir build && cd build

Run Cmake. If you just want to build the core, run:

.. code-block:: console

    cmake ../

If you want to build all available modules for your version,
run with

.. code-block:: console

    cmake ../ -DSQ_MODULES="all"

you can chose to build only the modules you need.
Only the physics module for instance

.. code-block:: console

    cmake ../ -DSQ_MODULES="physics"

The physics module and the UI module

.. code-block:: console

    cmake ../ -DSQ_MODULES="physics UI"

To see all modules available in your version of Small Square, refer to this page.

You can also choose to build samples. Add the following option.

.. code-block:: console

    -DBUILD_SAMPLES=ON

To see all the Cmake options relevant to the engine, refer to this page.

Build & Install
~~~~~~~~~~~~~~~
Once you're cmake configuration is done run Make:

.. code-block:: console

    make && sudo make install

If you don't have any errors, you're good to go.