#include "GridWindow.hpp"
#include "../MapSystem/Item.h"
#include "../Resources/Utils.hpp"
GridWindow::GridWindow
(sf::Texture* _gtex, sf::Vector2f _position,
 unsigned int w_tiles, unsigned int h_tiles,
 unsigned int w_tile, unsigned int h_tile, sf::Color _colline, sf::Color _colfill)
:grid(w_tiles,h_tiles,w_tile,h_tile)
,_backgrd(sf::Vector2f(w_tiles*w_tile,h_tiles*h_tile))
{
    grid.loadTex(_gtex);
    _backgrd.setFillColor(_colfill);
    _backgrd.setOutlineThickness(1);
    _backgrd.setOutlineColor(_colline);
    _backgrd.setPosition(_position);
    grid.setPosition(0,0);
    setPosition(_position);
    appendBackground();
}
void GridWindow::move(const sf::Vector2f& pos)
{
    _backgrd.setPosition(pos);
    grid.setPosition(0,0);
    setPosition(pos);
}
void GridWindow::cleanBg()
{
    grid.clean();
}
void GridWindow::resizeBg()
{
    grid.resizeBg();
}
void GridWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if(!grid.getBgVisible())
        target.draw(_backgrd);
    grid.draw(target,states);
}
void GridWindow::refresh(unsigned int t_sq)
{
    grid.cleanLastSquare(t_sq);
}
void GridWindow::appendBackground()
{
    for(size_t i=0;i<grid.getSize().x; ++i)
        for(size_t j=0;j<grid.getSize().y; ++j)
            grid.appendItem(i, j, 710, 1);
}
void GridWindow::update(const std::vector<Item>& items)
{
    unsigned int x,y;
    x=y=0;
    items_in_grid.clear();
    for(auto it : items)
    {
        grid.appendItem(x,y,it.gid, 0);
        grid.appendItem(x,y,710,1);
        items_in_grid.push_back(Item(x,y,it.gid, it.id));
        if(x < grid.getSize().x)
            ++x;
        if(x == grid.getSize().x)
        {
            x=0;
            ++y;
        }
    }
}
bool GridWindow::isVisible() const
{
    return visible;
}
void GridWindow::setVisible(bool v)
{
    visible = v;
}
bool GridWindow::buttonHold(int n_msec)
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
void GridWindow::appendItem(const int x, const int y, const int GID,const int layer)
{
    grid.appendItem(x,y,GID, layer);
}
bool GridWindow::intersects(sf::Vector2i& vct)
{
    if((vct.x >= getPosition().x && vct.x <= (getPosition().x + _backgrd.getSize().x))
    && (vct.y >= getPosition().y && vct.y <= (getPosition().y + _backgrd.getSize().y)))
    {
        hoover = true;
        return true;
    }
    hoover = false;
    return false;
}
sf::Vector2i GridWindow::underSquare(sf::Vector2i& vct)
{
    sf::Vector2i normalized = sf::Vector2i((vct.x - getPosition().x) / grid.getTileSize().x,
                                           (vct.y - getPosition().y) / grid.getTileSize().y);
    if(intersects(vct))
        return normalized;
    else return sf::Vector2i(-1,-1);
}
unsigned int GridWindow::getGID(sf::Vector2i vct)
{
    sf::Vector2i buf = underSquare(vct);
    if(buf.x != -1 && buf.y != -1)
    {
        std::vector<Item>::const_iterator it =
            std::find_if(items_in_grid.cbegin(), items_in_grid.cend(), std::bind(xyCompareUnsigned<Item>, std::placeholders::_1,buf));
        if(it != items_in_grid.end())
            return it->gid;
    }
    return 0;
}
unsigned int GridWindow::getID(sf::Vector2i vct)
{
    sf::Vector2i buf = underSquare(vct);
    if(buf.x != -1 && buf.y != -1)
    {
        std::vector<Item>::const_iterator it =
            std::find_if(items_in_grid.cbegin(), items_in_grid.cend(), std::bind(xyCompareUnsigned<Item>, std::placeholders::_1,buf));
        if(it != items_in_grid.end())
            return it->id;
    }
    return 0;
}
