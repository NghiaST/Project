#include "state.hpp"

State::State(VisualizationSettings* settings)
{
    // setup text
    this->settings = settings;
    this->window = settings->getWindow();
    this->theme = settings->getTheme();
    this->font = settings->getFont();
    this->quit = false;
    InitAllButton();
}
State::~State()
{
    delete sBtnSpeed;
    delete sBtnStep;
}

void State::InitAllButton()
{
    int cntCategory = 7;
    std::vector<std::string> strCategory;
    std::vector<std::vector<std::string>> listStrManipulate;
    std::vector<std::vector<std::vector<std::string>>> listStrSubManipulate;
    std::vector<std::vector<std::string>> listStrInputBox;
    std::vector<std::string> strAnimation;
    std::vector<std::vector<std::vector<std::vector<std::string>>>> listStrStep;

    strCategory = {"Static Array", "Dynamic Array", "Simply Linked List", "Doubly Linked List", "Circular Linked List", "Stack", "Queue"};
    listStrManipulate = {
        {"Initialize", "Insert", "Remove", "Update", "Access & Search"},
        {"Initialize", "Insert", "Remove", "Update & Allocate", "Access & Search"},
        {"Initialize", "Insert", "Remove", "Update", "Search"},
        {"Initialize", "Insert", "Remove", "Update", "Search"},
        {"Initialize", "Insert", "Remove", "Update", "Search"},
        {"Initialize", "Push", "Pop", "Peek", "Clear"},
        {"Initialize", "Enqueue", "Dequeue", "Clear"}
    };
    listStrSubManipulate = {
        {
            {"Empty", "Random", "Manual", "File"},
            {"First", "Last", "Middle"},
            {"First", "Last", "Middle"},
            {"Update"},
            {"Access", "Search"}
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"First", "Last", "Middle"},
            {"First", "Last", "Middle"},
            {"Update", "Allocate"},
            {"Access", "Search"}
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"First", "Last", "Middle"},
            {"First", "Last", "Middle"},
            {"Update"},
            {"Search"}
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"First", "Last", "Middle"},
            {"First", "Last", "Middle"},
            {"Update"},
            {"Search"}
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"First", "Last", "Middle"},
            {"First", "Last", "Middle"},
            {"Update"},
            {"Search"}
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"Push"},
            {"Pop"},
            {"Peek"},
            {"Clear"}
        },
        {
            {"Empty", "Random", "Manual", "File"},
            {"Enqueue"},
            {"Dequeue"},
            {"Clear"}
        }
    };
    listStrInputBox = {
        {"Fixed size = ", "Filename = ", "Array = ", "Pos = ", "Value = "},
        {"Filename = ", "Array = ", "Pos = ", "Value = ", "Size allocate = "},
        {"Filename = ", "Array = ", "Pos = ", "Value = "},
        {"Filename = ", "Array = ", "Pos = ", "Value = "},
        {"Filename = ", "Array = ", "Pos = ", "Value = "},
        {"Filename = ", "Array = ", "Pos = ", "Value = "},
        {"Filename = ", "Array = ", "Pos = ", "Value = "}
    };
    strAnimation = {
        "<<", "<", "||", "Play", ">", ">>"
    };
    listStrStep = {
        {
            {
                {"Initialize Empty"},{"Initialize Random Value"},{"Initialize Manual Value"},{"Initialize From File"}
            },
            {
                {
                    "if (N == fixedSize) return",
                    "N++",
                    "for(int i = N - 2; i >= 0; i--)",
                    "   elements[i + 1] = elements[i]",
                    "elements[0] = value"
                },
                {
                    "if (N == fixedSize) return",
                    "N++",
                    "elements[N - 1] = value"
                },
                {
                    "if (N == fixedSize) return",
                    "N++",
                    "for(int i = pos - 1; i >= 0; i--)",
                    "   elements[i + 1] = elements[i]",
                    "elements[pos] = value"
                }
            },
            {
                {
                    "if (N == 0) return",
                    "for(int i = N - 1; i > 0; i--)",
                    "   elements[i - 1] = elements[i]",
                    "elements[N--] = 0"
                }, 
                {
                    "if (N == 0) return",
                    "elements[N--] = 0",
                }, 
                {
                    "if (N == 0) return",
                    "for(int i = N - 1; i > pos; i--)",
                    "   elements[i - 1] = elements[i]",
                    "elements[N--] = 0"
                }
            },
            {
                {
                    "elements[pos] = value"
                }
            },
            {
                {
                    "return elements[pos]"
                }, 
                {
                    "for(int i = 0; i < N; i++)",
                    "   if (elements[i] == value)",
                    "       return i",
                    "return NOT_FOUND"
                }
            }
        },
        {
            {
                {"Initialize Empty"},{"Initialize Random Value"},{"Initialize Manual Value"},{"Initialize From File"}
            },
            {
                {
                    "int *newarray = new int[++N]",
                    "for(int i = 0, j = 0; i < N - 1; i++, j++)",
                    "   if (j == 0) j++",
                    "   newarray[j] = array[i]",
                    "newarray[0] = value",
                    "delete [] array",
                    "array = newarray"
                }, 
                {
                    "int *newarray = new int[++N]",
                    "for(int i = 0, j = 0; i < N - 1; i++, j++)",
                    "   if (j == N - 2) j++",
                    "   newarray[j] = array[i]",
                    "newarray[0] = value",
                    "delete [] array",
                    "array = newarray"
                }, 
                {
                    "int *newarray = new int[++N]",
                    "for(int i = 0, j = 0; i < N - 1; i++, j++)",
                    "   if (j == pos) j++",
                    "   newarray[j] = array[i]",
                    "newarray[0] = value",
                    "delete [] array",
                    "array = newarray"
                }
            },
            {
                {
                    "if (N == 0) return",
                    "int *newarray = new int[--N]",
                    "for(int i = 0, j = 0; j < N; i++, j++)",
                    "   if (i == 0) i++",
                    "   newarray[j] = array[i]",
                    "delete [] array",
                    "array = newarray"
                },
                {
                    "if (N == 0) return",
                    "int *newarray = new int[--N]",
                    "for(int i = 0, j = 0; j < N; i++, j++)",
                    "   if (i == N - 1) i++",
                    "   newarray[j] = array[i]",
                    "delete [] array",
                    "array = newarray"
                },
                {
                    "if (N == 0) return",
                    "int *newarray = new int[--N]",
                    "for(int i = 0, j = 0; j < N; i++, j++)",
                    "   if (i == pos) i++",
                    "   newarray[j] = array[i]",
                    "delete [] array",
                    "array = newarray"
                }
            },
            
            {
                {
                    "elements[pos] = value"
                },
                {
                    "if (array != nullptr) delete [] array",
                    "array = new int[N = size_allocate]",
                    "for(int i = 0; i < N; i++)",
                    "   array[i] = value"
                }
            },
            {
                {
                    "return elements[pos]"
                }, 
                {
                    "for(int i = 0; i < N; i++)",
                    "   if (elements[i] == value)",
                    "       return i",
                    "return NOT_FOUND"
                }
            }
        },
        {
            {
                {"Initialize Empty"},{"Initialize Random Value"},{"Initialize Manual Value"},{"Initialize From File"}
            },
            {
                {
                    "Node* cur = new Node(value)", 
                    "cur->next = head", 
                    "head = cur; if (!tail) tail = head"
                }, 
                {
                    "Node* cur = new Node(value)", 
                    "tail->next = cur", 
                    "tail = cur; if (!head) head = tail"
                },
                {
                    "Node* pre = head",
                    "for (int i = 0; i < pos - 1; i++)",
                    "   pre = pre->next",
                    "Node* cur = new Node(value)",
                    "cur->next = pre->next",
                    "pre->next = cur"
                }
            },
            {
                {
                    "if (head == nullptr) return",
                    "Node* cur = head",
                    "head = cur->next",
                    "delete cur"
                }, 
                {
                    "if (head == nullptr) return",
                    "Node* pre = nullptr, *cur = head",
                    "while (cur != tail)",
                    "   pre = cur, cur = cur->next",
                    "tail = pre; if (pre) pre->next = nullptr",
                    "delete cur"
                }, 
                {
                    "Node* pre = head",
                    "for(int i = 0; i < pos - 1; i++)",
                    "   pre = pre->next",
                    "Node* tmp = pre->next",
                    "pre->next = tmp->next",
                    "delete tmp"
                }
            },
            {
                {
                    "Node* cur = head",
                    "for(int i = 0; i < pos; i++)",
                    "   cur = cur->next",
                    "cur->value = value"
                }
            },
            {
                {
                    "Node* cur = head",
                    "while (cur != nullptr && cur->value != value)",
                    "   cur = cur->next",
                    "if (tmp == nullptr) return NOT_FOUND",
                    "return cur"
                }
            }
        },
        {
            {
                {"Initialize Empty"},{"Initialize Random Value"},{"Initialize Manual Value"},{"Initialize From File"}
            },
            {
                {
                    "Node* cur = new Node(value)", 
                    "cur->next = head; if (head) head->prev = cur",
                    "head = cur; if (!tail) tail = head"
                }, 
                {
                    "Node* cur = new Node(value)", 
                    "if (tail) tail->next = cur; cur->prev = tail", 
                    "tail = cur; if (!head) head = tail"
                },
                {
                    "Node* pre = head",
                    "for (int i = 0; i < pos - 1; i++)",
                    "   pre = pre->next",
                    "Node* cur = new Node(value), nxt = pre->next",
                    "cur->next = nxt; if (nxt) nxt->prev = cur",
                    "pre->next = cur; cur->prev = pre"
                }
            },
            {
                {
                    "if (head == nullptr) return",
                    "Node* cur = head",
                    "head = cur->next",
                    "cur->next = nullptr; if (head) head->prev = nullptr"
                    "delete cur"
                }, 
                {
                    "if (head == nullptr) return",
                    "Node* cur = tail",
                    "tail = cur->prev",
                    "cur->prev = nullptr; if (tail) tail->next = nullptr",
                    "delete cur"
                }, 
                {
                    "Node* cur = head",
                    "for(int i = 0; i < pos; i++)",
                    "   cur = cur->next",
                    "Node* pre = cur->prev, nxt = cur->next",
                    "cur->prev = cur->next = nullptr",
                    "if (pre) pre->next = nxt; if (nxt) nxt->prev = pre",
                    "delete cur"
                }
            },
            {
                {
                    "Node* cur = head",
                    "for(int i = 0; i < pos; i++)",
                    "   cur = cur->next",
                    "cur->value = value"
                }
            },
            {
                {
                    "Node* cur = head",
                    "while (cur != nullptr && cur->value != value)",
                    "   cur = cur->next",
                    "if (tmp == nullptr) return NOT_FOUND",
                    "return cur"
                }
            }
        },
        {
            {
                {"Initialize Empty"},{"Initialize Random Value"},{"Initialize Manual Value"},{"Initialize From File"}
            },
            {
                {
                    "Node* cur = new Node(value)", 
                    "cur->next = head; if (tail) tail->next = cur",
                    "head = cur; if (!tail) tail = head"
                }, 
                {
                    "Node* cur = new Node(value)", 
                    "tail->next = cur; cur->next = (tail ? tail->next : cur)", 
                    "tail = cur; if (!head) head = tail"
                },
                {
                    "Node* pre = head",
                    "for (int i = 0; i < pos - 1; i++)",
                    "   pre = pre->next",
                    "Node* cur = new Node(value)",
                    "cur->next = pre->next",
                    "pre->next = cur"
                }
            },
            {
                {
                    "if (head == nullptr) return",
                    "Node* cur = head",
                    "head = cur->next",
                    "if (tail) tail->next = head",
                    "delete cur"
                }, 
                {
                    "if (head == nullptr) return",
                    "Node* pre = nullptr, *cur = head",
                    "while (cur != tail)",
                    "   pre = cur, cur = cur->next",
                    "tail = pre; if (pre) pre->next = head",
                    "delete cur"
                },
                {
                    "Node* pre = head",
                    "for(int i = 0; i < pos - 1; i++)",
                    "   pre = pre->next",
                    "Node* tmp = pre->next",
                    "pre->next = tmp->next",
                    "delete tmp"
                }
            },
            {
                {
                    "Node* cur = head",
                    "for(int i = 0; i < pos; i++)",
                    "   cur = cur->next",
                    "cur->value = value"
                }
            },
            {
                {
                    "Node* cur = head",
                    "while (cur != nullptr && cur->value != value)",
                    "   cur = cur->next",
                    "if (tmp == nullptr) return NOT_FOUND",
                    "return cur"
                }
            }
        },
        {
            {
                {"Initialize Empty"},{"Initialize Random Value"},{"Initialize Manual Value"},{"Initialize From File"}
            },
            {
                {
                    "Node* cur = new Node(value)", 
                    "cur->next = head", 
                    "head = cur"
                }, 
            },
            {
                {
		            "if (head == nullptr) return",
                    "Node* cur = head",
                    "head = cur->next",
                    "delete cur"
                }
            },
            {
                {
                    "if (head == nullptr) return NOT_FOUND",
                    "return head"
                }
            },
            {
                {
                    "while (head != nullptr)",
                    "   Node* tmp = head",
                    "   head = head->next",
                    "   delete tmp"
                }   
            }
        },
        {
            {
                {"Initialize Empty"},{"Initialize Random Value"},{"Initialize Manual Value"},{"Initialize From File"}
            },
            {
                {
                    "Node* cur = new Node(value)",
                    "tail->next = cur",
                    "tail = cur"
                }
            },
            {
                {
                    "if (head == nullptr) return",
                    "Node* tmp = head",
                    "head = head->next",
                    "delete tmp"
                }
            },
            {
                {
                    "while (head != nullptr)",
                    "   Node* tmp = head",
                    "   head = head->next",
                    "   delete tmp"
                }   
            }
        }
    };

    for(int i = 0; i < cntCategory; i++)
    {
        sCategory.push_back(StateCategory(window, theme, font, i, strCategory, listStrManipulate[i], listStrSubManipulate[i], listStrInputBox[i]));
    }

    sf::Vector2f coord, velocity, sizeRec;
    coord = sf::Vector2f(516, 650);
    velocity = sf::Vector2f(39, 0);
    sizeRec = sf::Vector2f(velocity.x - 2, 35);
    
    for(std::string strname : strAnimation) {
        btnAnimation.push_back(Button(coord, sizeRec.x, sizeRec.y, 12, 2, true, false, 0, strname, this->font, this->theme->getButtonDS()));
        coord += velocity;
    }

    this->typeCategory = 0;
    btnTheme.push_back(Button(sf::Vector2f(4, 650), 100, 35, 11, 2, true, true, 0, "Light Mode", this->font, this->theme->getButtonDS()));
    btnTheme.push_back(Button(sf::Vector2f(104, 650), 100, 35, 11, 2, true, true, 0, "Dark Mode", this->font, this->theme->getButtonDS()));
    btnTheme[0].setStatus(3);

    sBtnSpeed = new ButtonSpeed(window, theme, font, settings->getSpeed());
    sBtnStep = new ButtonStep(window, theme, font, listStrStep);
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
std::vector<std::string> State::getInputBox(int typeManipulate)
{
    return sCategory[typeCategory].getInputBox(typeManipulate);
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
    sf::Vector2i ret2 = sBtnSpeed->update(mouseType, keyboardType, mousePosView);
    if (ret2.x != -1) ret = ret2;

    if (0 <= ret.x && ret.x < 100)
    {
        this->typeCategory = ret.x;
    }
    if (100 <= ret.x && ret.x < 200)
    {
        sBtnStep->assign(typeCategory, ret.x - 100, ret.y);
    }
    for(int i = 0; i < btnAnimation.size(); i++)
    {
        if (btnAnimation[i].updateCheckClick(mousePosView, mouseType))
            ret = {300, i};
    }

    for(int i = 0; i < 2; i++)
    {
        if (btnTheme[i].updateCheckClick(mousePosView, mouseType))
        {
            ret = {200, i};
            btnTheme[i ^ 1].setStatus(0);
        }
    }
    return ret;
}

void State::updateBtnCode(int Manipulate, int subManipulate)
{
    sBtnStep->assign(typeCategory, Manipulate, subManipulate);
}

void State::updateBtnStep(int typeStep)
{
    sBtnStep->update(typeStep);
}

void State::render()
{
    if (this->getQuit()) return;
    sCategory[this->typeCategory].render();
    sBtnSpeed->render();
    sBtnStep->render();
    for(Button& btn : btnTheme)
        btn.render(window);
    for(Button& btn : btnAnimation)
        btn.render(window);
}
