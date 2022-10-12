#pragma once

#include "cell.h"

class wall : public cell {
public:
    wall();
    ~wall() override;
};
