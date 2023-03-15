
//  newboid.hpp

#ifndef newboid_hpp
#define newboid_hpp

#include <stdio.h>
#include "boid.h"

//Define a new class called "newboid", which is based on the Boid class
class newboid : public Boid {
public:
    newboid();
    void draw();
};

#endif
