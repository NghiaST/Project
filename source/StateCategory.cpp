#include "StateCategory.hpp"

StateCategory::StateCategory(sf::RenderWindow* window, Themes* theme, sf::Font* font, int typeCategory, std::vector<std::string> strCategory, std::vector<std::string> strManipulate, std::vector<std::vector<std::string>> strsubManipulate, std::vector<std::string> strInputBox, std::vector<std::vector<int>> listShow)
{
    this->window = window;
    this->font = font;
    this->theme = theme;
    this->typeCategory = typeCategory;
    this->cntCategory = strCategory.size();
    this->cntManipulate = strManipulate.size();
    this->listShow = listShow;

    sf::Vector2f coord, velocity, sizeRec;
    // category
    coord = sf::Vector2f(5, 450);
    velocity = sf::Vector2f(0, 25);
    sizeRec = sf::Vector2f(150, velocity.y - 5);

    for(std::string strname : strCategory) {
        buttonCategory.push_back(Button(coord, sizeRec.x, sizeRec.y, 13, 2, true, true, 0, strname, this->font, this->theme->getButtonDS()));
        coord += velocity;
    }

    // 3 other
    buttonCategory[this->typeCategory].setStatus(2);
    buttonsubManipulate.resize(cntManipulate);

    coord = sf::Vector2f(160, 450);
    velocity = sf::Vector2f(0, 35);
    sizeRec = sf::Vector2f(110, velocity.y - 5);
    for(std::string strname : strManipulate) 
    {
        buttonManipulate.push_back(Button(coord, sizeRec.x, sizeRec.y, 12, 2, true, false, 0, strname, this->font, this->theme->getButtonManipulate()));
        coord += velocity;
    }

    // update submanipulate: create_empty, create_random, etc
    coord = sf::Vector2f(280, 452);
    velocity = sf::Vector2f(70, 35);
    sizeRec = sf::Vector2f(velocity.x - 5, 26);
    for(int i = 0; i < this->cntManipulate; i++)
    {
        sf::Vector2f coord2 = coord;
        for(std::string strname : strsubManipulate[i]) {
            buttonsubManipulate[i].push_back(Button(coord2, sizeRec.x, sizeRec.y, 11, 2, true, false, 0, strname, this->font, this->theme->getButtonSubmanipulate()));
            coord2.x += velocity.x;
        }
        coord.y += velocity.y;
    }
    
    // update inputBox
    velocity = sf::Vector2f(240, 30);
    sizeRec = sf::Vector2f(200, velocity.y - 7);
    coord = sf::Vector2f(600, 540 - velocity.y * strInputBox.size() / 2);
    for(std::string strname : strInputBox) {
        listBox.push_back(InputBox(coord, sizeRec.x, sizeRec.y, 11, 2, true, false, 1, strname, this->font, this->theme->getButtonInputbox()));
        coord.y += velocity.y;
    }
}

StateCategory::~StateCategory()
{
}

void StateCategory::Clean()
{
    for(Button& btn : buttonCategory)
        btn.setStatus(0);
    buttonCategory[typeCategory].setStatus(2);
    for(Button& btn : buttonManipulate)
        btn.setView(true);
    for(std::vector<Button>& vecbtn : buttonsubManipulate)
    for(Button& btn : vecbtn)
        btn.setView(true);
    for(InputBox& box : listBox)
    {
        box.setWordInput("");
    }
}

sf::Vector2i StateCategory::update(MOUSE mouseType, KEYBOARD keyboardType, sf::Vector2f mousePosView)
{
    sf::Vector2i ret = sf::Vector2i(-1, -1);
    for(InputBox& box : listBox)
        box.update(mousePosView, mouseType, keyboardType);
    int cnt = 0;
    for(Button& btn : this->buttonCategory) {
        if (btn.updateCheckClick(mousePosView, mouseType)) {
            ret.x = cnt;
            ret.y = -1;
        }
        cnt++;
    }
    
    cnt = 200;
    for(Button& btn : this->buttonManipulate) {
        if (btn.updateCheckClick(mousePosView, mouseType)) {
            ret.x = cnt;
            ret.y = -1;
        }
        cnt++;
    }

    cnt = 100;
    for(int i = 0; i < this->cntManipulate; i++)
    {
        int cnt2 = 0;
        for(Button& btn : buttonsubManipulate[i]) {
            if (btn.updateCheckClick(mousePosView, mouseType)) {
                ret.x = i + cnt;
                ret.y = cnt2;
            }
            else if (btn.getStatus() == 1) {
                for(int z = 0; z < listBox.size(); z++)
                    listBox[z].setStatus(((listShow[i][cnt2] >> z) & 1) * 4);
            }
            cnt2++;
        }
    }
    
    // update state of button
    if (mouseType != MSE_LEFTCLICK) ret = sf::Vector2i(-1, -1);

    if (0 <= ret.x && ret.x < 100) {
        if (ret.x != this->typeCategory) {
            Clean();
            return ret;
        }
        else {
            ret = sf::Vector2i(-1, -1);
        }
    }
    else if (100 <= ret.x && ret.x < 200) {
        this->typeManipulate = ret.x - 100;
        this->typesubManipulate = ret.y;
    }
    else if (200 <= ret.x && ret.x < 300) {
        ret = sf::Vector2i(-1, -1);
    }
    return ret;
}

void StateCategory::updateInputBox(int pos, int value)
{
    std::string strpos = std::to_string(pos);
    std::string strvalue = std::to_string(value);
    switch (this->typeCategory)
    {
        case 0 :
            listBox[3].setWordInput(strpos);
            listBox[4].setWordInput(strvalue);
        case 1 : case 2 : case 3 : case 4 :
            listBox[2].setWordInput(strpos);
            listBox[3].setWordInput(strvalue);
            break;
        default :
            break;
    }
}

std::vector<std::string> StateCategory::getInputBox(int typeManipulate)
{
    std::vector<std::string> ret;
    for(InputBox& box : listBox)
        ret.push_back(box.getWordInput());
    return ret;
}

void StateCategory::render()
{
    for(Button& butt : buttonCategory)
        butt.render(window);
    for(Button& butt : buttonManipulate)
        butt.render(window);
    for(int i = 0; i < cntManipulate; i++) {
        for(Button& butt : buttonsubManipulate[i])
            butt.render(window);
    }
    for(InputBox& box : listBox)
        box.render(window);
}
