#include "terminal.h"

#include "dungeon.h"
#include "cell.h"
#include "curses.h"
#include "player.h"
#include "item.h"
#include "game.h"
//#include <ctime>

std::shared_ptr<Terminal> Terminal::term = nullptr;

int Terminal::prevCols = 0;
int Terminal::prevLines = 0;

enum class Terminal::WinType {
    Main,
    StatusLine,
    Inventory,
    Equipment
};
//int delayMilSec = 30;

constexpr static int invSizeY = 30;
constexpr static int invSizeX = 30;
constexpr static int equipSizeY = 30;
constexpr static int equipSizeX = 30;

// WINDOW CLASS
class Terminal::Window {
public:
    Window(std::string name, int sizeY, int sizeX, int startY, int startX, WinType type);

    virtual ~Window();

    void moveCurs(int Y, int X) const;

    void print(const std::string &str) const;

    void mvPrint(int Y, int X, const std::string &str) const;

    void printBorder() const;

    void clearWindow() const;

    void clearContent() const;

    virtual void printContent() = 0;

    virtual void processInput() = 0;

    int getSizeY() const;

    int getSizeX() const;

    int getStartY() const;

    int getStartX() const;

    bool isActive() const;

    void setActive(bool bNewActive);

    WinType getType();

private:
    int sizeY;
    int sizeX;
    int startY;
    int startX;

    std::string name;

    bool bActive = false;

    const WinType type;
};

Terminal::Window::Window(std::string name, int sizeY, int sizeX, int startY, int startX, WinType type) : name(
        std::move(name)),
                                                                                                         sizeY(sizeY),
                                                                                                         sizeX(sizeX),
                                                                                                         startY(startY),
                                                                                                         startX(startX),
                                                                                                         type(type) {}

Terminal::Window::~Window() = default;

int Terminal::Window::getSizeY() const {
    return sizeY;
}

int Terminal::Window::getSizeX() const {
    return sizeX;
}

int Terminal::Window::getStartY() const {
    return startY;
}

int Terminal::Window::getStartX() const {
    return startX;
}

bool Terminal::Window::isActive() const {
    return bActive;
}

void Terminal::Window::setActive(bool bNewActive) {
    bActive = bNewActive;
}

Terminal::WinType Terminal::Window::getType() {
    return type;
}

void Terminal::Window::moveCurs(int Y, int X) const {
    move(startY + Y, startX + X);
}

void Terminal::Window::print(const std::string &str) const {
    printw("%s", str.c_str());
}

void Terminal::Window::mvPrint(int Y, int X, const std::string &str) const {
    mvprintw(startY + Y, startX + X, "%s", str.c_str());
}

void Terminal::Window::printBorder() const {
    clearWindow();
    for (int i = 0; i < sizeY; i++) {
        moveCurs(i, 0);
        for (int j = 0; j < sizeX; j++) {
            if (i == 0) {
                if (j == 0) {
                    print("\u250F");
                } else if (j == sizeX - 1) {
                    print("\u2513");
                } else {
                    print("\u2501");
                }
            } else if (i == sizeY - 1) {
                if (j == 0) {
                    print("\u2517");
                } else if (j == sizeY - 1) {
                    print("\u251B");
                } else {
                    print("\u2501");
                }
            } else if (j == 0 || j == sizeX - 1) {
                print("\u2503");
            } else {
                print(" ");
            }
        }
    }
    mvPrint(0, 1, name);
}

void Terminal::Window::clearWindow() const {
    for (int i = 0; i < sizeY; i++) {
        move(startY + i, startX);
        for (int j = 0; j < sizeX; j++) {
            printw(" ");
        }
    }
}

void Terminal::Window::clearContent() const {
    for (int i = 0; i < sizeY - 2; i++) {
        move(startY + 1 + i, startX + 1);
        for (int j = 0; j < sizeX - 2; j++) {
            printw(" ");
        }
    }

}

// INVENTORY WINDOW
class Terminal::WinInventory : public Terminal::Window {
public:
    WinInventory();

    ~WinInventory() override;

    void printContent() override;

    void processInput() override;

private:
    void moveInvCursUp();

    void moveInvCursDown();

    void moveInvPageUp();

    void moveInvPageDown();

    std::list<std::unique_ptr<Item>>::iterator getInvItemUnderCurs();

    int invCursPos = 0;
    int invCurrentPage = 0;
    int invMaxPage = 0;
    int invMaxPageSize = 0;
    std::list<std::unique_ptr<Item>>::iterator invItemUnderCurs;

    constexpr static int invTopIndent = 1;
    constexpr static int invBottomIndent = 2;
    constexpr static int invLeftIndent = 1;
    constexpr static int invRightIndent = 1;
};

Terminal::WinInventory::WinInventory() : Terminal::Window(
        "INVENTORY", invSizeY, invSizeY, 0, Terminal::prevCols - invSizeX, WinType::Inventory) {
    printBorder();
    invCursPos = invTopIndent;
    invCurrentPage = 0;
//    printContent();
}

Terminal::WinInventory::~WinInventory() {
    clearWindow();
}

void Terminal::WinInventory::printContent() {
    clearContent();

    auto &inv = Player::getPlayer()->getInventory();
    auto it = inv.begin();
    invMaxPage = inv.size() / (invSizeY - invTopIndent - invBottomIndent);
    invMaxPageSize = inv.size() % (invSizeY - invTopIndent - invBottomIndent);
    if (invCurrentPage > invMaxPage) {
        invCurrentPage = invMaxPage;
    }
    std::advance(it, invCurrentPage * (invSizeY - invBottomIndent - invTopIndent));
    for (int i = invTopIndent; i < invSizeY - invBottomIndent && it != inv.end(); i++, it++) {
        auto name = (*it)->getName();
        // if name is too long, cut it
        if (name.length() > invSizeX - invLeftIndent - invRightIndent)
            name = name.substr(0, invSizeX - invLeftIndent - invRightIndent - 3) + "...";
        if (i == invCursPos && isActive()) {
            invItemUnderCurs = it;
            attron(A_STANDOUT);
        }
        mvPrint(i, invLeftIndent, name);
        if (i == invCursPos && isActive()) {
            attroff(A_STANDOUT);
        }
    }

    // print currentPage / maxPage
    mvPrint(invSizeY - 2, invLeftIndent,
            std::to_string(invCurrentPage + 1) + " / " + std::to_string(invMaxPage + 1));
}

void Terminal::WinInventory::processInput() {
    auto terminal = Terminal::getTerminal();
    auto key = getch();
    switch (key) {
        case KEY_UP:
            moveInvCursUp();
            break;
        case KEY_DOWN:
            moveInvCursDown();
            break;
        case KEY_LEFT:
            moveInvPageDown();
            break;
        case KEY_RIGHT:
            moveInvPageUp();
            break;
        case 'e': {
            Player::getPlayer()->equipItem(getInvItemUnderCurs());
            printContent();
            if (terminal->winEquipment) {
                terminal->winEquipment->printContent();
            }
            break;
        }
        case '\t': {
            terminal->changeActiveWindow();
            printContent();
            break;
        }
        case 'i':
        case 27:
//            term->closeInventory();
//            term->closeEquipment();
        {
            if (term->winEquipment) {
                term->setWinActive(term->winEquipment);
            } else {
                term->setWinActive(term->winMain);
            }
            term->winInventory.reset();
            return;
        }
    }
}

void Terminal::WinInventory::moveInvCursUp() {
    invCursPos--;
    if (invCursPos < invTopIndent) {
        invCursPos = invTopIndent;
    }
    printContent();
}

void Terminal::WinInventory::moveInvCursDown() {
    invCursPos++;
    if (invCursPos >= invSizeY - invBottomIndent) {
        invCursPos = invSizeY - invBottomIndent - 1;
    }
    if (invCursPos > invMaxPageSize) {
        invCursPos = invMaxPageSize;
    }
    printContent();
}

void Terminal::WinInventory::moveInvPageUp() {
    invCurrentPage++;
    if (invCurrentPage > invMaxPage) {
        invCurrentPage = invMaxPage;
    }
    printContent();
}

void Terminal::WinInventory::moveInvPageDown() {
    invCurrentPage--;
    if (invCurrentPage < 0) {
        invCurrentPage = 0;
    }
    printContent();
}

std::list<std::unique_ptr<Item>>::iterator Terminal::WinInventory::getInvItemUnderCurs() {
    return invItemUnderCurs;
}


class Terminal::WinMain : public Terminal::Window {
public:
    WinMain();

    ~WinMain() override;

    void printContent() override;

    void processInput() override;

//    void setDungeon(std::shared_ptr<Dungeon> newDungeon);

private:
    std::weak_ptr<Dungeon> dungeon;
};

Terminal::WinMain::WinMain() : Terminal::Window("MAIN", Terminal::prevLines - 1,
                                                Terminal::prevCols, 0, 0, WinType::Main) {
    dungeon = Game::getGame()->getDungeon();
}

Terminal::WinMain::~WinMain() {
    clearWindow();
}

void Terminal::WinMain::printContent() {
    clearWindow();

    if (dungeon.expired())
        return;
    auto dung = dungeon.lock();
    const auto &level = dung->getLevel();
    int terminalHeight = getSizeY();
    int terminalWidth = getSizeX();
    int dungeonHeight = dung->getHeight();
    int dungeonWidth = dung->getWidth();

    int startY = 0, startX = 0;
    int endY = dungeonHeight, endX = dungeonWidth;
    int moveY = 0, moveX = 0;

    auto playerCoords = Player::getPlayer()->getCell()->getCoords();
    if (terminalHeight > dungeonHeight) {
        moveY = (terminalHeight - dungeonHeight) / 2;
    } else {
        startY = std::max(0, playerCoords.y - terminalHeight / 2);
        endY = std::min(dungeonHeight, playerCoords.y + terminalHeight / 2);
        if (startY == 0) {
            endY = terminalHeight;
        }
        if (endY == dungeonHeight) {
            startY = dungeonHeight - terminalHeight;
        }
    }
    if (terminalWidth > dungeonWidth) {
        moveX = (terminalWidth - dungeonWidth) / 2;
    } else {
        startX = std::max(0, playerCoords.x - terminalWidth / 2);
        endX = std::min(dungeonWidth, playerCoords.x + terminalWidth / 2);
        if (startX == 0) {
            endX = terminalWidth;
        }
        if (endX == dungeonWidth) {
            startX = dungeonWidth - terminalWidth;
        }
    }

    for (int i = startY; i < endY; i++) {
        moveCurs(moveY + i - startY, moveX);
        for (int j = startX; j < endX; j++) {
            print(level[i][j]->getStringForm());
        }
    }

}

void Terminal::WinMain::processInput() {
    Terminal::getTerminal()->updateStatusLine("NUMPAD TO MOVE, ");
    auto key = getch();
    switch (key) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '6':
        case '7':
        case '8':
        case '9':
            Game::getGame()->movePlayer(key);
            break;
        case 'a': {
            int direction = getch();
            Game::getGame()->attackMelee(direction);
            break;
        }
        case 'i': {
            auto terminal = Terminal::getTerminal();
            terminal->winInventory = terminal->createWindow(WinType::Inventory);
            terminal->winInventory->printContent();
            terminal->winEquipment = terminal->createWindow(WinType::Equipment);
            terminal->winEquipment->printContent();
            term->setWinActive(terminal->winInventory);
            break;
        }
        case 'q':
            Game::getGame()->setEndSession(true);
            break;
    }
}

//void Terminal::WinMain::setDungeon(std::shared_ptr<Dungeon> newDungeon) {
//    dungeon = newDungeon;
//}

class Terminal::WinEquipment : public Terminal::Window {
public:
    WinEquipment();

    ~WinEquipment() override;

    void printContent() override;

    void processInput() override;

private:
    void moveEquipCursDown();

    void moveEquipCursUp();

    ItemType equipCursPos;
    constexpr static int equipTopIndent = 1;
    constexpr static int equipBottomIndent = 1;
    constexpr static int equipLeftIndent = 1;
    constexpr static int equipRightIndent = 1;
};

Terminal::WinEquipment::WinEquipment() : Window("EQUIPMENT", equipSizeY, equipSizeX, 0,
                                                Terminal::prevCols - invSizeX - equipSizeX, WinType::Equipment) {
    printBorder();
    equipCursPos = ItemType::Weapon;
}

Terminal::WinEquipment::~WinEquipment() {
    clearWindow();
}

void Terminal::WinEquipment::printContent() {
    clearContent();

    auto &equipment = Player::getPlayer()->getEquipment();
    // print weapon
    if (equipCursPos == ItemType::Weapon && isActive()) {
        attron(A_STANDOUT);
    }
    mvPrint(equipTopIndent, equipLeftIndent, "WEAPON:");
    if (equipment.weapon) {
        mvPrint(equipTopIndent, equipLeftIndent + 10, equipment.weapon->getName());
    }
    if (equipCursPos == ItemType::Weapon && isActive()) {
        attroff(A_STANDOUT);
    }
}

void Terminal::WinEquipment::processInput() {
    auto terminal = Terminal::getTerminal();
    auto key = getch();
    switch (key) {
        case 'e': {
            Player::getPlayer()->unEquipItem(equipCursPos);
            printContent();
            if (terminal->winInventory) {
                terminal->winInventory->printContent();
            }
            break;
        }
        case '\t': {
            terminal->changeActiveWindow();
            printContent();
            break;
        }
        case 'i':
        case 27: {
            if (terminal->winInventory) {
                terminal->setWinActive(terminal->winInventory);
            } else {
                terminal->setWinActive(terminal->winMain);
            }
            terminal->winEquipment.reset();
            return;
        }
    }
}

class Terminal::WinStatusLine : public Terminal::Window {
public:
    explicit WinStatusLine(std::string &refStatusText);

    ~WinStatusLine() override;

    void printContent() override;

    void processInput() override;

private:
    std::string &statusLineText;
};

Terminal::WinStatusLine::WinStatusLine(std::string &refStatusText) : Window("STATUS LINE", 1,
                                                                            Terminal::prevCols,
                                                                            Terminal::prevLines - 1, 0,
                                                                            WinType::StatusLine),
                                                                     statusLineText(refStatusText) {}

Terminal::WinStatusLine::~WinStatusLine() {
    clearWindow();
}

void Terminal::WinStatusLine::printContent() {
    clearWindow();
    mvPrint(0, 0, statusLineText);
}

void Terminal::WinStatusLine::processInput() {

}

void Terminal::initialize() {
    setlocale(LC_ALL, "");
    initscr(); // Initialize ncurses
    raw(); // Disable control characters (CTRL-C, CTRL-Z, etc.)
    noecho(); // Disable echo (thx cap)
    keypad(stdscr, TRUE); // Enable F-* keys and arrow keys
    curs_set(0); // Make cursor invisible

    // Init colors
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_colors();
}

void Terminal::end() {
    endwin(); // Restore normal terminal
}

Terminal::Terminal() {
    initialize();
    prevLines = LINES;
    prevCols = COLS;
    winMain = createWindow(WinType::Main);
    setWinActive(winMain);
    winStatusLine = createWindow(WinType::StatusLine);
}

Terminal::~Terminal() {
    end();
}

void Terminal::init_colors() {
    init_pair(1, COLOR_RED, COLOR_BLACK);
}

std::shared_ptr<Terminal> Terminal::getTerminal() {
    if (!term) {
        struct terminalMakeSharedEnabler : public Terminal {
        };
        term = std::make_shared<terminalMakeSharedEnabler>();
    }
    return term;
}

void Terminal::printContent() {
    updateWindowSizes();
    winActive->printContent();
    winStatusLine->printContent();
    refresh();
}

void Terminal::processInput() {
    winActive->processInput();
}

void Terminal::updateStatusLine(std::string newText) {
    if (!winStatusLine) {
        winStatusLine = createWindow(WinType::StatusLine);
    }
    statusLineText = std::move(newText);
//    winStatusLine->clearWindow();
//    winStatusLine->mvPrint(0, 0, statusLineText);
//    winStatusLine->printContent();
}

void Terminal::refreshScreen() {
    updateWindowSizes();
    refresh();
}

void Terminal::updateWindowSizes() {
    resize_term(0, 0);
    if (prevLines == LINES && prevCols == COLS)
        return;

    prevLines = LINES;
    prevCols = COLS;

    if (winMain) {
        bool bActive = winMain->isActive();
        winMain = createWindow(WinType::Main);
        if (bActive)
            setWinActive(winMain);
    }
    if (winInventory) {
        bool bActive = winInventory->isActive();
        winInventory = createWindow(WinType::Inventory);
        if (bActive)
            setWinActive(winInventory);
    }
    if (winEquipment) {
        bool bActive = winEquipment->isActive();
        winEquipment = createWindow(WinType::Equipment);
        if (bActive)
            setWinActive(winInventory);
    }
    if (winStatusLine) {
        winStatusLine = createWindow(WinType::StatusLine);
    }
}

std::unique_ptr<Terminal::Window> Terminal::createWindow(Terminal::WinType type) {
    std::unique_ptr<Terminal::Window> output;
    switch (type) {
        case WinType::Main:
            output = std::make_unique<Terminal::WinMain>();
            break;
        case WinType::Inventory:
            output = std::make_unique<Terminal::WinInventory>();
            break;
        case WinType::Equipment:
            output = std::make_unique<Terminal::WinEquipment>();
            break;
        case WinType::StatusLine:
            output = std::make_unique<Terminal::WinStatusLine>(statusLineText);
            break;
    }
    return output;
}

void Terminal::setWinActive(std::shared_ptr<Window> newWinActive) {
    if (winActive) {
        winActive->setActive(false);
    }
    winActive = std::move(newWinActive);
    winActive->setActive(true);
}

void Terminal::changeActiveWindow() {
    auto activeType = winActive->getType();
    if (activeType == WinType::Inventory) {
        if (winEquipment) {
            setWinActive(winEquipment);
            return;
        }
    } else if (activeType == WinType::Equipment) {
        if (winInventory) {
            setWinActive(winInventory);
            return;
        }
    }
}

//void terminal::delay(int milSec) {
//    milSec *= 1000;
//    auto startTime = clock();
//    while (clock() < startTime + milSec);
//}
//