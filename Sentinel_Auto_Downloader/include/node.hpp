//
//  node.hpp
//  Automatic SAR Processing System
//
//  Created by Constantine VI on 2018/8/7.
//  Copyright © 2018 Constantine VI. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <xercesc/dom/DOM.hpp>
#include <string>
#include <vector>

#if defined(_DEBUG) || defined(DEBUG)
#define debugPrint(x) std::cerr << x << std::endl;
#else
#define debugPrint(x)
#endif

class node
{
private:
    int iStatus = 0;
    xercesc::DOMNode* nodeCurrentNode;
    xercesc::DOMElement* elementCurrentNode;
public:
    node();
    node(xercesc::DOMNode* Node);
    node(xercesc::DOMElement* Node);
    node getNodebyName(std::string NodeName);
    node getNodebyAttribute(std::string AttributeName, std::string AttributeValue);
    node clone();
    std::string getNodeName();
    std::string getNodeValue();
    std::string getAttributeValue(std::string Attribute);
    int getStatus();
    int appendChild(node ChildElement);
    int setAttribute(std::string Name, std::string Value);
    int setTextContent(std::string TextContent);
    std::vector<node> findNodesChildNode();
    std::vector<node> findNodesbyName(std::string NodeName);
    std::vector<node> findNodesbyAttribute(std::string AttributeName, std::string AttributeValue);
    void listChildNode();
};

#endif /* node_hpp */
