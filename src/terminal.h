#pragma once

#include "curses.h"

#include <memory>
#include <string>
#include <list>

class Dungeon;

class Cell;

class Item;

enum class ItemType;

class Terminal {
public:
    Terminal(Terminal &other) = delete;

    void operator=(const Terminal &other) = delete;

    ~Terminal();

    static std::shared_ptr<Terminal> getTerminal();

    void printContent();

    void processInput();

    void refreshScreen();

//    void openInventory();
//    void refreshInventory();
//    void closeInventory();
//    void moveInvCursUp();
//    void moveInvCursDown();
//    void moveInvPageUp();
//    void moveInvPageDown();
//    std::list<std::unique_ptr<Item>>::iterator getInvItemUnderCurs();

//    void openEquipment();
//    void closeEquipment();
//    void refreshEquipment();

    std::string statusLineText = "ABOBABABBABABABBABBABBYAEBALNCURSESQHWIUOEQRIUQHEWUIOEHWQIUEBLYAT";

private:
    Terminal();

    static void initialize();

    static void end();

    static std::shared_ptr<Terminal> term;

    static void init_colors();

    void updateStatusLine(std::string text);

    void updateWindowSizes();

    class Window;

    class WinInventory;

    class WinMain;

    class WinEquipment;

    class WinStatusLine;

    enum class WinType;

    std::unique_ptr<Window> createWindow(WinType type);

    std::shared_ptr<Window> winActive;
    std::shared_ptr<Window> winMain;
    std::shared_ptr<Window> winInventory;
    std::shared_ptr<Window> winEquipment;
    std::shared_ptr<Window> winStatusLine;

    void setWinActive(std::shared_ptr<Window> newWinActive);

    void changeActiveWindow();

    static int prevLines;
    static int prevCols;
};