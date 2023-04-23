#include "state.hpp"

State::State(VisualizationSettings* settings)
{
    // setup text
    this->window = settings->getWindow();
    this->theme = settings->getTheme();
    this->font = settings->getFont();
    this->quit = false;
    InitAllButton();
}
State::~State()
{
}

void State::InitAllButton()
{
    int cntCategory = 5;
    std::vector<std::string> strCategory;
    std::vector<std::vector<std::string>> listStrManipulate;
    std::vector<std::vector<std::vector<std::string>>> listStrSubManipulate;
    std::vector<std::vector<std::vector<std::string>>> listStrInputBox;
    std::vector<std::string> strAnimation;

    strCategory = {"Static Array", "Dynamic Array", "Linked List", "Stack", "Queue"};
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
    strAnimation = {
        "<<", "<", "||", "Play", ">", ">>"
    };

    sf::Vector2f coord, velocity, sizeRec;
    coord = sf::Vector2f(300, 650);
    velocity = sf::Vector2f(45, 0);
    sizeRec = sf::Vector2f(velocity.x - 5, 35);
    
    for(int i = 0; i < cntCategory; i++)
    {
        sCategory.push_back(StateCategory(window, theme, font, i, strCategory, listStrManipulate[i], listStrSubManipulate[i], listStrInputBox[i]));
    }
    for(std::string strname : strAnimation) {
        btnAnimation.push_back(Button(coord, sizeRec.x, sizeRec.y, 12, 2, true, false, strname, this->font, this->theme->getButtonDS()));
        coord += velocity;
    }

    this->typeCategory = 0;

    btnTheme.push_back(Button(sf::Vector2f(5, 635), 80, 40, 11, 2, true, true, "Light Mode", this->font, this->theme->getButtonDS()));
    btnTheme.push_back(Button(sf::Vector2f(85, 635), 80, 40, 11, 2, true, true, "Dark Mode", this->font, this->theme->getButtonDS()));
    btnTheme[0].setStatus(3);
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

sf::Vector2i State::update(MOUSE mouseType, KEYBOARD keyboardType)
{
    this->updateMousePositions();
    if (this->getQuit()) return sf::Vector2i(-1, -1);

    sf::Vector2i ret = sCategory[this->typeCategory].update(mouseType, keyboardType, mousePosView);
    if (0 <= ret.x && ret.x < 100)
    {
        this->typeCategory = ret.x;
    }
    for(int i = 0; i < btnAnimation.size(); i++)
    {
        if (btnAnimation[i].updateCheckClick(mousePosView, mouseType))
            ret.x = 300 + i;
    }

    for(int i = 0; i < 2; i++)
    {
        if (btnTheme[i].updateCheckClick(mousePosView, mouseType))
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
    for(Button& btn : btnAnimation)
        btn.render(window);
}
