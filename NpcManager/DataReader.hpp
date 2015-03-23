#pragma once
#include "../Resources/tinyxml/tinyxml.h"
#include "../Resources/Utils.hpp"
#include <string>
#include <vector>
class DataRead : public IDataRead
{
public:
    DataRead(){};
    ~DataRead(){};
    virtual void read(TiXmlElement*) override;
    Action  get()                    override;
private:
    void parseParams(const std::string, std::vector<int>&, char);
    Action  current_processed;
};
