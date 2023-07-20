Getting started with Small Square
=================================

=====
Cmake
=====
Cmake is the tool the engine is built with and the intended tool for using it. All you should need to run small square inside a CMakeLists.txt file,
is an instruction to find the Small Square Package and a set of library module links.

.. code-block:: CMAKE

    cmake_minimum_required(VERSION 3.17)
    project(smallsquare)

    set(CMAKE_CXX_STANDARD 20)
    set(FIND_LIBRARY_USE_LIB64_PATHS True)

    find_package(smallsquare)

    add_executable(MyGame main.cpp)

    target_link_libraries(MyGame PRIVATE smallsquare_core smallsquare_ui)


=============
Making a game
=============
Start by overriding the Game class and running the game loop from your main function.

.. code-block:: C++

    #include "game.h"

    using namespace smallsquare;
    class MyGame : public Game{

    MyGame(int width, int height) : Game(width   ,height){
        //Put everything that should initialise your game here
    }

    void Tick() override{
        Game::Tick(); //Keep this line.
        //Put everything that should be run at every game tick here
    }

    int main([[maybe_unused]] int argc, [[maybe_unused]] char * argv[]){
        auto game = new MyGame();
        game->GameLoop();
    }


.. warning::
    The "Game::Tick();" line should be kept unless you want to drastically change your game's behaviour. The base function calls every GameObject's Tick function and draws every drawables as well as checking the game tree's integrity.

.. note::
    Small Square is made with the idea that everything should be changed if it needs to. That means it's great with you want to get technical but it also means you can break things pretty easily if you experiment outside of how things are "meant" to be used. Still, if you're feeling adventurous, don't let me stop you from finding new pathways to greatness!


===============
And after that?
===============
Small Square is supposed to be easy to learn by yourself by following the API. But everybody doesn't like to learn that way. You can either read this guide further and see me explaining what every class is supposed to do, follow some of the tutorials, or, you can browse through the samples showcasing the different modules and do a bit of reverse engineering, if you're that kind of person...



