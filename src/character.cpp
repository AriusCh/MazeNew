#include "character.h"

#include <utility>

using std::string;
using std::pair;
using std::shared_ptr;

character::character(string name, std::shared_ptr<cell> Cell) : name(std::move(name)), Cell(std::move(Cell)) {

}

char character::getCharForm() const{
    return charForm;
}

std::shared_ptr<cell> character::getCell() const {
    return Cell;
}

void character::setCell(shared_ptr<cell> Cell) {
    this->Cell = Cell;
}
