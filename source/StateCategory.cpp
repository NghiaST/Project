#include "StateCategory.hpp"

StateCategory::StateCategory(sf::RenderWindow* window, PublicThemes* theme, sf::Font* font, int typeCategory, std::vector<std::string> strCategory, std::vector<std::string> strManipulate, std::vector<std::vector<std::string>> strsubManipulate, std::vector<std::vector<std::string>> strInputBox)
{
    this->window = window;
    this->font = font;
    this->theme = theme;
    this->typeCategory = typeCategory;
    this->cntCategory = strCategory.size();
    this->cntManipulate = strManipulate.size();

    sf::Vector2f coord, velocity, sizeRec;
    // category
    coord = sf::Vector2f(5, 450);
    velocity = sf::Vector2f(0, 35);
    sizeRec = sf::Vector2f(100, velocity.y - 5);

    for(std::string strname : strCategory) {
        buttonCategory.push_back(Button(coord, sizeRec.x, sizeRec.y, 13, 2, true, true, strname, this->font, &this->theme->button_ds));
        coord += velocity;
    }

    // 3 other
    buttonCategory[this->typeCategory].setStatus(2);
    buttonsubManipulate.resize(cntManipulate);
    boxarr.resize(cntManipulate);

    coord = sf::Vector2f(115, 450);
    velocity = sf::Vector2f(0, 35);
    sizeRec = sf::Vector2f(80, velocity.y - 5);
    for(std::string strname : strManipulate) 
    {
        buttonManipulate.push_back(Button(coord, sizeRec.x, sizeRec.y, 13, 2, true, false, strname, this->font, &this->theme->button_manipulate));
        coord += velocity;
    }

    // update submanipulate: create_empty, create_random, etc
    coord = sf::Vector2f(200, 452);
    velocity = sf::Vector2f(70, 35);
    sizeRec = sf::Vector2f(velocity.x - 5, 26);
    for(int i = 0; i < this->cntManipulate; i++)
    {
        sf::Vector2f coord2 = coord;
        for(std::string strname : strsubManipulate[i]) {
            buttonsubManipulate[i].push_back(Button(coord2, sizeRec.x, sizeRec.y, 11, 2, false, false, strname, this->font, &this->theme->button_submanipulate));
            coord2.x += velocity.x;
        }
        coord.y += velocity.y;
    }
    
    // update inputBox
    coord = sf::Vector2f(500, 452);
    velocity = sf::Vector2f(180, 35);
    sizeRec = sf::Vector2f(velocity.x - 5, 26);
    for(int i = 0; i < this->cntManipulate; i++)
    {
        sf::Vector2f coord2 = coord;
        for(std::string strname : strInputBox[i]) {
            boxarr[i].push_back(InputBox(coord2, sizeRec.x, sizeRec.y, 11, 2, false, false, strname, this->font, &this->theme->button_inputbox));
            coord2.x += velocity.x;
        }
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
        btn.setView(false);
    for(std::vector<InputBox>& vecipb : boxarr)
    for(InputBox& ipb : vecipb)
    {
        ipb.setView(false);
        ipb.setWordInput("");
    }
}

sf::Vector2i StateCategory::update(int mouseType, int keyboardType, sf::Vector2f mousePosView)
{
    sf::Vector2i ret = sf::Vector2i(-1, -1);
    int cnt = 0;
    for(Button& btn : this->buttonCategory) {
        btn.update(mousePosView, mouseType);
        if (btn.isPressed()) {
            ret.x = cnt;
            ret.y = -1;
        }
        cnt++;
    }
    
    cnt = 200;
    for(Button& btn : this->buttonManipulate) {
        btn.update(mousePosView, mouseType);
        if (btn.isPressed()) {
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
            btn.update(mousePosView, mouseType);
            if (btn.isPressed()) {
                ret.x = i + cnt;
                ret.y = cnt2;
            }
            cnt2++;
        }
        for(InputBox& box : boxarr[i])
            box.update(mousePosView, mouseType, keyboardType);
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
        for(Button& btn : buttonsubManipulate[ret.x - 200])
            btn.swapView();
        for(InputBox& box : boxarr[ret.x - 200])
            box.swapView();
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
        case 0 : case 1 : case 2 :
            boxarr[1][0].setWordInput(strpos);
            boxarr[2][0].setWordInput(strpos);
            boxarr[3][0].setWordInput(strpos);
            boxarr[4][0].setWordInput(strvalue);
            break;
        case 3 :
            break;
        case 4 :
            break;
    }
}

std::string StateCategory::getValueButton(int typeManipulate, int id)
{
    if (this->boxarr[typeManipulate].size() <= id) 
        return "";
    return this->boxarr[typeManipulate][id].getWordInput();
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
        for(InputBox& box : boxarr[i])
            box.render(window);
    }
}
