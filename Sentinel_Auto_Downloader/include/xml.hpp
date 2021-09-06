//
//  xml.hpp
//  Automatic SAR Processing System
//
//  Created by Constantine VI on 2020/6/4.
//  Copyright © 2020 Constantine VI. All rights reserved.
//

#ifndef xml_hpp
#define xml_hpp

#include "node.hpp"
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <string>
#include <vector>
#include <filesystem>

class xml
{
private:
    std::filesystem::path PATH_XML;
    xercesc::DOMDocument* XMLDoc = NULL;
    xercesc::XercesDOMParser* XML = NULL;
public:
    xml();
    xml(std::string XMLPath);
    xml(std::filesystem::path XMLPath);
    node getNodebyName(std::string NodeName);
    node getNodebyAttribute(std::string AttributeName, std::string AttributeValue);
    node getRootElement();
    node createElement(std::string NodeName);
    node createElement(std::string NodeName, std::string NodeValue);
    node createTextNode(std::string NodeText);
    node createComment(std::string NodeComment);
    int save();
    int save(std::string XMLPath);
    int create(std::string RootName);
    int read();
    void close();
};

#endif
