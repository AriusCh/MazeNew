#pragma once

#include <string>
#include <memory>

class object;

enum class cellType{
    Empty,
    Wall,
    Ground
};

class cell {
public:
    virtual ~cell();

    std::string getStringForm();

protected:
    cellType type;
    std::string stringForm;
    std::shared_ptr<object> Object;
};
