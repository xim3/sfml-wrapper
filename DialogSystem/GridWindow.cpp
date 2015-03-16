#include "GridWindow.hpp"
#include "../MapSystem/Item.h"
#include "../Resources/Utils.hpp"
GridWindow::GridWindow
(sf::Texture* _gtex, sf::Vector2f _position,
 unsigned int w_tiles, unsigned int h_tiles,
 unsigned int w_tile, unsigned int h_tile, sf::Color _colline, sf::Color _colfill)
    :grid(w_tiles,h_tiles,w_tile,h_tile)
    ,in_area(0)
    ,_backgrd(sf::Vector2f(w_tiles*w_tile,h_tiles*h_tile))
{
    grid.loadTex(_gtex);
    _backgrd.setFillColor(_colfill);
    _backgrd.setOutlineThickness(1);
    _backgrd.setOutlineColor(_colline);
    _backgrd.setPosition(_position);
    grid.setPosition(0,0);
    setPosition(_position);
}
void GridWindow::move(const sf::Vector2f& pos)
{
    _backgrd.setPosition(pos);
    grid.setPosition(0,0);
    setPosition(pos);
}
void GridWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_backgrd);
    grid.draw(target,states);
}
void GridWindow::refresh(unsigned int t_sq)
{
    grid.cleanLastSquare(t_sq);
}
void GridWindow::update(const std::vector<Item>& items)
{
    unsigned int x,y;
    x=y=0;
    items_in_grid.clear();
for(auto it : items)
    {
        grid.appendItem(x,y,it.gid);
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
bool GridWindow::intersects(const sf::Vector2i& vct)
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
    else
        return sf::Vector2i(-1,-1);
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
