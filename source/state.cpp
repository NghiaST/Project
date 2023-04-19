#include "state.hpp"

State::State(sf::RenderWindow* window, PublicThemes* theme)
{
    // setup text
    this->window = window;
    this->quit = false;
    this->theme = theme;
    if (!this->font.loadFromFile("dat/roboto/Roboto-Medium.ttf")) {
        std::cout << "Error Load Font\n";
    }

    int cntCategory = 5;
    std::vector<std::string> strCategory;
    std::vector<std::vector<std::string>> listStrManipulate;
    std::vector<std::vector<std::vector<std::string>>> listStrSubManipulate;
    std::vector<std::vector<std::vector<std::string>>> listStrInputBox;

    strCategory = {"StaticArray", "DynamicArray", "LinkedList", "Stack", "Queue"};
    listStrManipulate = {
        {"Initialize", "Insert", "Remove", "Update", "Search"},
        {"Initialize", "Insert", "Remove", "Update", "Search"},
        {"Initialize", "Insert", "Remove", "Update", "Search"},
        {"Initialize", "Peek", "Push", "Pop"},
        {"Initialize", "Peek", "Enqueue", "Dequeue"}
    };
    listStrSubManipulate = {
        {
            {"Empty", "Random", "Manual", "File"},
            {"First", "Last", "Manual"},
            {"First", "Last", "Manual"},
            {"Manual"},
            {"Manual"}
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"First", "Last", "Manual"},
            {"First", "Last", "Manual"},
            {"Manual"},
            {"Manual"}
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"First", "Last", "Manual"},
            {"First", "Last", "Manual"},
            {"Manual"},
            {"Manual"}
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"Peek"},
            {"Push"},
            {"Pop"},
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"Front", "Back"},
            {"Enqueue"},
            {"Dequeue"}
        }
    };
    listStrInputBox = {
        {
            {"Array=", "FileName="},
            {"Pos=", "Value="},
            {"Pos="},
            {"Pos=", "Value="},
            {"Value="}
        },
        {
            {"Array=", "FileName="},
            {"Pos=", "Value="},
            {"Pos="},
            {"Pos=", "Value="},
            {"Value="}
        },
        {
            {"Array=", "FileName="},
            {"Pos=", "Value="},
            {"Pos="},
            {"Pos=", "Value="},
            {"Value="}
        },
        {
            {"Array=", "FileName="},
            {},
            {"Value="},
            {}
        },
        {
            {"Array=", "FileName="},
            {},
            {"Value="},
            {}
        }
    };

    for(int i = 0; i < cntCategory; i++)
    {
        sCategory.push_back(StateCategory(window, theme, &font, i, strCategory, listStrManipulate[i], listStrSubManipulate[i], listStrInputBox[i]));
    }
    this->typeCategory = 0;

    btnTheme.push_back(Button(sf::Vector2f(5, 635), 80, 40, 11, 2, true, true, "Light Mode", &this->font, &this->theme->button_ds));
    btnTheme.push_back(Button(sf::Vector2f(85, 635), 80, 40, 11, 2, true, true, "Dark Mode", &this->font, &this->theme->button_ds));
    btnTheme[0].setStatus(3);
}
State::~State()
{
}

void State::checkforQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
        this->quit = true;
}

// setvalue
void State::updateInputBox(int pos, int value)
{
    sCategory[typeCategory].updateInputBox(pos, value);
}

// getvalue
const bool &State::getQuit() const
{
    return this->quit;
}
std::string State::getValueButton(int typeManipulate, int id)
{
    return sCategory[typeCategory].getValueButton(typeManipulate, id);
}

void State::updateMousePositions()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

sf::Vector2i State::update(int mouseType, int keyboardType)
{
    this->updateMousePositions();
    if (this->getQuit()) return sf::Vector2i(-1, -1);

    sf::Vector2i ret = sCategory[this->typeCategory].update(mouseType, keyboardType, mousePosView);
    if (0 <= ret.x && ret.x < 100)
    {
        this->typeCategory = ret.x;
    }

    for(int i = 0; i < 2; i++)
    {
        btnTheme[i].update(mousePosView, mouseType);
        if (mouseType == MSE_LEFTCLICK && btnTheme[i].getStatus() == 2)
        {
            ret.x = 200 + i;
            btnTheme[i ^ 1].setStatus(0);
        }
    }
    return ret;
}
void State::render()
{
    if (this->getQuit()) return;
    sCategory[this->typeCategory].render();
    for(Button& btn : btnTheme)
        btn.render(window);
}
