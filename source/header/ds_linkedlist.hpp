#ifndef __ds_linkedlist_hpp__
#define __ds_linkedlist_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"
#include "ds_staticarray.hpp"

struct StructLinkedList : StructStaticArray {
    StructLinkedList(sf::RenderWindow* window, bool active) : StructStaticArray(window, active) {}
};
#endif