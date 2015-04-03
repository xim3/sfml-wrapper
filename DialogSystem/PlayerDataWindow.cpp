#include "PlayerDataWindow.hpp"
DataWindow::DataWindow(sf::Vector2f pos, sf::Vector2u& ppos,sf::Vector2i& _mouse, sf::Font* f, sf::Texture* tex, ItemManager& img, TileMap& m,IDataFormat& idf,  unsigned int f_size)
: mouse(_mouse)
, player_pos(ppos)
, font(f)
, font_size(f_size)
, selectedPage(0)
, eq_0(tex,f,sf::Vector2f(pos.x+font_size,pos.y+font_size*2.5),5,5,5,img, idf)
, imgr(img)
, map(m)
{
    setVisible(true);
    win.setPosition(pos);
    win.setSize(sf::Vector2f(400,300));
    win.setFillColor(sf::Color(50,50,50,200));
    win.setOutlineThickness(1);
    win.setOutlineColor(sf::Color::Black);

    setPosition(pos);
    addButton("Stats");
    addButton("Equip");
    addButton("Skills");
    addButton("Info");
}
bool DataWindow::isVisible() const
{
    return visible;
}
bool DataWindow::buttonHold(int n_msec)
{
    sf::Time time_button_hold;
    if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
    {
        time_button_hold += sf::Time(click_clock.getElapsedTime());
        if( time_button_hold > sf::milliseconds(n_msec) )
        {
            time_button_hold = sf::Time::Zero;
            click_clock.restart();
            return true;
        }
        else return false;
    }
    else
    {
        time_button_hold = sf::Time::Zero;
        click_clock.restart();
        return false;
    }
}
void DataWindow::setMemoryManager(MemoryManager* m){mmgr = m;}
int DataWindow::underButton()
{
    int i=0;
    for(auto button : pageButtons)
    {
        if((mouse.x >= button.getPosition().x && mouse.x <= button.getPosition().x + button.getSize().x)
         &&(mouse.y >= button.getPosition().y && mouse.y <= button.getPosition().y + button.getSize().y))
              break;
        if(mouse.y > button.getPosition().y + button.getSize().y) return -1;
        i++;
    }
    if(visible && intersects(mouse))
        return i;
    else return -1;
}
void DataWindow::update()
{
    int under = underButton();
    if(under != -1 && buttonHold(50)) selectedPage = under;
    unsigned int i=0;
    for(auto &button : pageButtons)
    {
        if(selectedPage == i) button.setFillColor(sf::Color(50,180,50));
        else button.setFillColor(sf::Color(50,50,50));
        i++;
    }
    drawPage();
    if(selectedPage == 0)
        smallButtonSelected();
    if(selectedPage == 1)
        eq_0.controlCloud(mouse);
}
void DataWindow::equipRefresh(){eq_0.refresh(0);}
void DataWindow::drawStats()
{
    int padding_left = 10;
    ad_data.clear();
    smallButton.clear();
    smallButtonSign.clear();
    sf::Text _buf;
    sf::String _text;
    _text = L"Siła:";
    if(mmgr != nullptr) _text += std::to_string(mmgr->getStrength());
    _buf.setFont(*font);
    _buf.setColor(sf::Color::Yellow);
    _buf.setString(_text);
    _buf.setCharacterSize(font_size);
    _buf.setPosition(win.getPosition().x+padding_left, win.getPosition().y + (font_size*2));
    ad_data.push_back(_buf);
    addSmallButton(0);
    _text = L"Zręczność:";
    if(mmgr != nullptr) _text += std::to_string(mmgr->getAgility());
    _buf.setString(_text);
    _buf.setPosition(win.getPosition().x+padding_left, win.getPosition().y + (font_size*3.5));
    ad_data.push_back(_buf);
    addSmallButton(1);
    _text = L"Witalność:";
    if(mmgr != nullptr) _text += std::to_string(mmgr->getVital());
    _buf.setString(_text);
    _buf.setPosition(win.getPosition().x+padding_left, win.getPosition().y + (font_size*5));
    ad_data.push_back(_buf);
    addSmallButton(2);
    _text = L"Energia:";
    if(mmgr != nullptr) _text += std::to_string(mmgr->getEnergy());
    _buf.setString(_text);
    _buf.setPosition(win.getPosition().x+padding_left, win.getPosition().y + (font_size*6.5));
    ad_data.push_back(_buf);
    addSmallButton(3);
    _text = L"Charyzma:";
    if(mmgr != nullptr) _text += std::to_string(mmgr->getCharisma());
    _buf.setString(_text);
    _buf.setPosition(win.getPosition().x+padding_left, win.getPosition().y + (font_size*8));
    ad_data.push_back(_buf);
    addSmallButton(4);
    _text= L"Inteligencja:";
    if(mmgr != nullptr) _text += std::to_string(mmgr->getWisdom());
    _buf.setString(_text);
    _buf.setPosition(win.getPosition().x+padding_left, win.getPosition().y + (font_size*9.5));
    ad_data.push_back(_buf);
    addSmallButton(5);
    _text= L"Punkty do rozdania:";
    if(mmgr != nullptr) _text += std::to_string(mmgr->getFreepoints());
    _buf.setString(_text);
    _buf.setPosition((win.getPosition().x + win.getSize().x) - 160, win.getPosition().y + font_size * 2);
    ad_data.push_back(_buf);
}
int DataWindow::underSmallButton()
{
    unsigned int i=0;
    for(auto button : smallButton)
    {
        if((mouse.x >= button.getPosition().x && mouse.x <= button.getPosition().x + button.getSize().x)
         &&(mouse.y >= button.getPosition().y && mouse.y <= button.getPosition().y + button.getSize().y))
              break;
        i++;
    }
    if(i == smallButton.size()) return -1;
    if(visible && intersects(mouse))
        return i;
    else return -1;
}
void DataWindow::smallButtonSelected()
{
    if(mmgr != nullptr)
    {
        if(mmgr->hasFreepoints())
        {
            int under = underSmallButton();
            if(under != -1 && buttonHold(60))
            {
                if(under == 0)
                {
                    mmgr->freepoints()--;
                    mmgr->strength()++;
                }
                if(under == 1)
                {
                    mmgr->freepoints()--;
                    mmgr->agility()++;
                }
                if(under == 2)
                {
                    mmgr->freepoints()--;
                    mmgr->vital()++;
                }
                if(under == 3)
                {
                    mmgr->freepoints()--;
                    mmgr->energy()++;
                }
                if(under == 4)
                {
                    mmgr->freepoints()--;
                    mmgr->charisma()++;
                }
                if(under == 5)
                {
                    mmgr->freepoints()--;
                    mmgr->wisdom()++;
                }
            }

        }
    }
}
void DataWindow::addSmallButton(int i)
{
    sf::RectangleShape _smallbutton(sf::Vector2f(font_size, font_size));
    _smallbutton.setOutlineColor(sf::Color::Red);
    _smallbutton.setOutlineThickness(1);
    _smallbutton.setFillColor(sf::Color(50,50,50,200));
    _smallbutton.setPosition(sf::Vector2f((ad_data[i].getPosition().x + 130), ad_data[i].getPosition().y));
    smallButton.push_back(_smallbutton);
    sf::Text sign;
    sign.setCharacterSize(13);
    sign.setString(L"+");
    sign.setFont(*font);
    sign.setColor(sf::Color::Green);
    sign.setPosition(sf::Vector2f(_smallbutton.getPosition().x+2, _smallbutton.getPosition().y-3));
    smallButtonSign.push_back(sign);
}
int  DataWindow::solveConditions(std::string cond)
{
    if(cond == "< ") return 0;
    if(cond == "> ") return 1;
    if(cond == "==") return 2;
    if(cond == "!=") return 3;
    if(cond == ">=") return 4;
    if(cond == "<=") return 5;
    return 6;
}
bool DataWindow::checkCondition(Item it)
{
    if(mmgr == nullptr) return true;
    ItemData data = imgr.getData(imgr.getGID(it.id));
    enum CTYPE {LOWER, GREATER, EQUAL, NOT_EQUAL, GREATER_EQUAL, LOWER_EQUAL, UNKNOWN} COMP_TYPE;
    enum VTYPE {NUMERIC, STRING} VALUE_TYPE;
    for(auto condition : data.conditions)
    {
        std::string argument_1 = std::get<0>(std::get<0>(condition));
        std::string argument_2;
        unsigned int argument_2_numeric;
        COMP_TYPE  = (CTYPE) solveConditions(std::get<1>(std::get<0>(condition)));
        if(isalpha(std::get<1>(condition)[0]))
        {
            VALUE_TYPE = STRING;
            argument_2 = std::get<1>(condition);
        }
        else
        {
            VALUE_TYPE = NUMERIC;
            argument_2_numeric = std::stoi(std::get<1>(condition));
        }
        if(VALUE_TYPE == STRING)
        {
            if(COMP_TYPE == LOWER){
                if(mmgr->get(argument_1) < mmgr->get(argument_2)) continue; else return false;}
            if(COMP_TYPE == GREATER){
                if(mmgr->get(argument_1) > mmgr->get(argument_2)) continue; else return false;}
            if(COMP_TYPE == EQUAL){
                if(mmgr->get(argument_1) == mmgr->get(argument_2)) continue; else return false;}
            if(COMP_TYPE == NOT_EQUAL){
                if(mmgr->get(argument_1) != mmgr->get(argument_2)) continue; else return false;}
            if(COMP_TYPE == GREATER_EQUAL){
                if(mmgr->get(argument_1) >= mmgr->get(argument_2)) continue; else return false;}
            if(COMP_TYPE == LOWER_EQUAL){
                if(mmgr->get(argument_1) >= mmgr->get(argument_2)) continue; else return false;}
        }
        if(VALUE_TYPE == NUMERIC)
        {
            if(COMP_TYPE == LOWER){
                if(mmgr->get(argument_1)  < argument_2_numeric) continue; else return false;}
            if(COMP_TYPE == GREATER){
                if(mmgr->get(argument_1) >  argument_2_numeric) continue; else return false;}
            if(COMP_TYPE == EQUAL){
                if(mmgr->get(argument_1) == argument_2_numeric) continue; else return false;}
            if(COMP_TYPE == NOT_EQUAL){
                if(mmgr->get(argument_1) != argument_2_numeric) continue; else return false;}
            if(COMP_TYPE == GREATER_EQUAL){
                if(mmgr->get(argument_1) >= argument_2_numeric) continue; else return false;}
            if(COMP_TYPE == LOWER_EQUAL){
                if(mmgr->get(argument_1) <= argument_2_numeric) continue; else return false;}
        }
    }
    return true;
}
void DataWindow::drawEquip()
{
    eq_0.updateItems();
    std::pair<int, int> selected = eq_0.selectedItem(mouse);
    std::pair<int, int> selected_right_eq = eq_0.getSelectedEq(mouse);
    enum SEL_TYPE {SET_WEAR, SET_DROP, SET_DESTROY, POPUP_HIDE, SEL_NOACTION = -1           } ACTION;
    enum SEL_PART {PART_WEAPON, PART_HELMET, PART_ARMOR, PART_PANTS, PART_BOOTS, PART_SHIELD} SELECTED_PART;
    ACTION        = (SEL_TYPE) std::get<0>(selected);
    SELECTED_PART = (SEL_PART) std::get<0>(selected_right_eq);
    int id = std::get<1>(selected);
    bool valid = 0;
    ItemData it;
    Item     it1;
    switch(ACTION)
    {
        case SET_WEAR:
        it = imgr.getData(imgr.getGID(id));
        it1 = imgr.getItem(id);
        if(it.type == SHIELD && mmgr->shieldEquiped() == false)
        {
            if(checkCondition(it1))
            {
                mmgr->wearShield(id);
                valid = eq_0.setShield(it1);
            }
        }
        if(it.type == WEAPON && mmgr->weaponEquiped() == false)
        {
            if(checkCondition(it1))
            {
                mmgr->wearWeapon(id);
                valid = eq_0.setWeapon(it1);
            }
        }
        if(it.type == BOOTS && mmgr->bootsEquiped() == false)
        {
            if(checkCondition(it1))
            {
                mmgr->wearBoots(id);
                valid = eq_0.setBoots(it1);
            }
        }
        if(it.type == PANTS && mmgr->pantsEquiped() == false)
        {
            if(checkCondition(it1))
            {
                mmgr->wearPants(id);
                valid = eq_0.setPants(it1);
            }
        }
        if(it.type == ARMOR && mmgr->armorEquiped() == false)
        {
            if(checkCondition(it1))
            {
                mmgr->wearArmor(id);
                valid = eq_0.setArmor(it1);
            }
        }
        if(it.type == HELMET && mmgr->helmetEquiped() == false)
        {
            if(checkCondition(it1))
            {
                mmgr->wearHelmet(id);
                valid = eq_0.setHelmet(it1);
            }
        }
        if(valid)
        {
            imgr.deleteItem(id);
            equipRefresh();
        }
        break;
        case SET_DROP:
        int bufid;
        if(!map.isItem(player_pos, bufid))
        {
            map.dropItem(id);
            equipRefresh();
        }
        break;
        case SET_DESTROY:
        imgr.deleteItem(id);
        equipRefresh();
        break;
        case SEL_NOACTION:

        break;
        case POPUP_HIDE:
        eq_0.hideMenu();
        break;
        default:
        break;
    }
    Item unw;
    switch(SELECTED_PART)
    {
        case PART_WEAPON:
        unw = eq_0.unwearWeapon();
        if(unw.id != -1)
        {
            imgr.addItem(unw);
            mmgr->unwearWeapon();
        }
        break;
        case PART_HELMET:
        unw = eq_0.unwearHelmet();
        if(unw.id != -1)
        {
            imgr.addItem(unw);
            mmgr->unwearHelmet();
        }
        break;
        case PART_ARMOR:
        unw = eq_0.unwearArmor();
        if(unw.id != -1)
        {
            imgr.addItem(unw);
            mmgr->unwearArmor();
        }
        break;
        case PART_PANTS:
        unw = eq_0.unwearPants();
        if(unw.id != -1)
        {
            imgr.addItem(unw);
            mmgr->unwearPants();
        }
        break;
        case PART_SHIELD:
        unw = eq_0.unwearShield();
        if(unw.id != -1)
        {
            imgr.addItem(unw);
            mmgr->unwearShield();
        }
        break;
        case PART_BOOTS:
        unw = eq_0.unwearBoots();
        if(unw.id != -1)
        {
            imgr.addItem(unw);
            mmgr->unwearBoots();
        }
        break;
        default:
        break;
    }

}
void DataWindow::drawSkills()
{
}
void DataWindow::drawInfo()
{
}
void DataWindow::drawPage()
{
    ad_data.clear();
    smallButton.clear();
    smallButtonSign.clear();
    switch(selectedPage)
    {
        case 0:
            drawStats();
        break;
        case 1:
            drawEquip();
        break;
        case 2:
            drawSkills();
        break;
        case 3:
            drawInfo();
        break;
        default:
        break;
    }
}
void DataWindow::addButton(std::string txt)
{
    int button_count = 4;
    int width = win.getSize().x / button_count;
    sf::RectangleShape new_button(sf::Vector2f(width, 0 + font_size + 5));
    new_button.setPosition(sf::Vector2f((win.getPosition().x) + width * pageButtons.size(), win.getPosition().y));
    new_button.setFillColor(sf::Color(100,100,100,200));
    new_button.setOutlineColor(sf::Color::Black);
    new_button.setOutlineThickness(1);
    sf::Text desc;
    desc.setString(txt);
    desc.setColor(sf::Color::Black);
    desc.setPosition(sf::Vector2f(win.getPosition().x + (width) * pageButtons.size(), win.getPosition().y));
    desc.setCharacterSize(font_size);
    desc.setFont(*font);
    buttonText.push_back(desc);
    pageButtons.push_back(new_button);
}
void DataWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(win);
    for(auto button : pageButtons)
    {
        target.draw(button);
        for(auto text : buttonText)
            target.draw(text);
    }
    if(selectedPage == 0)
    {
        for(auto desc : ad_data)
        {
            target.draw(desc);
            if(mmgr->hasFreepoints())
            {
                for(auto small : smallButton)
                    target.draw(small);
                    for(auto sign : smallButtonSign)
                        target.draw(sign);
            }
        }
    }
    else if(selectedPage == 1)
    {
        target.draw(eq_0);
    }

}
bool DataWindow::intersects(sf::Vector2i& vct)
{
    if(visible)
    {
       if((vct.x >= getPosition().x && vct.x <= (getPosition().x + win.getSize().x))
       && (vct.y >= getPosition().y && vct.y <= (getPosition().y + win.getSize().y)))
       {
          hoover = true;
          return true;
       }
       hoover = false;
       return false;
    }
    return false;
}
void DataWindow::setVisible(bool v)
{
    visible = v;
}
bool DataWindow::getVisible() const
{
    return visible;
}
