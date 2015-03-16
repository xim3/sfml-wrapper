#pragma once
#include "ItemManager.hpp"
class MyItemManager : public ItemManager
{
    public:
        MyItemManager() : ItemManager(){};
        ~MyItemManager(){};
        virtual bool loadItems(const std::string);
        virtual const Data* getData(size_t) const;
    private:
        ItemData undef;

};
