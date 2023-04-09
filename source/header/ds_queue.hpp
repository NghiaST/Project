#ifndef __ds_queue_hpp__
#define __ds_queue_hpp__
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <vector>

#include "node.hpp"
#include "support_function.hpp"
#include "struct_ds.hpp"
#include "ds_queue.hpp"

struct StructQueue : StructStaticArray {
    StructQueue(sf::RenderWindow* window, bool active) : StructStaticArray(window, active) {}
};
#endif