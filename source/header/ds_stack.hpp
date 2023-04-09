#ifndef __ds_stack_hpp__
#define __ds_stack_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"

#include "ds_staticarray.hpp"
struct StructStack : StructStaticArray {
    StructStack(sf::RenderWindow* window, bool active) : StructStaticArray(window, active) {}
};

#endif