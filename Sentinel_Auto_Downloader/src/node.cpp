//
//  node.cpp
//  Automatic SAR Processing System
//
//  Created by Constantine VI on 2018/8/7.
//  Copyright © 2018 Constantine VI. All rights reserved.
//

#include "node.hpp"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace xercesc;
using namespace std;

node::node()
{
    nodeCurrentNode = nullptr;
    elementCurrentNode = nullptr;
}

node::node(xercesc::DOMNode* Node)
{
    nodeCurrentNode = Node;
    elementCurrentNode = nullptr;
    iStatus = 1;
}

node::node(xercesc::DOMElement* Node)
{
    elementCurrentNode = Node;
    nodeCurrentNode = Node;
    iStatus = 1;
}

node node::getNodebyName(std::string NodeName)
{
    node Node;
    if (nodeCurrentNode->hasChildNodes())
    {
        DOMNodeList* ChildNodeList = nodeCurrentNode->getChildNodes();
        int i = 0;
        while (Node.getStatus() == 0 && i < (int)ChildNodeList->getLength())
        {
            node ChildNode(ChildNodeList->item(i));
            if (NodeName.compare(ChildNode.getNodeName()) == 0)
            {
                Node = ChildNode;
            }
            else
            {
                i++;
            }
        }

        if (Node.getStatus() == 0) {
            debugPrint("getNodebyName Node : " << NodeName << " not found.");
        }
    }
    return Node;
}

node node::getNodebyAttribute(std::string AttributeName, std::string AttributeValue)
{
    node Node;
    if (nodeCurrentNode->hasChildNodes())
    {
        DOMNodeList* ChildNodeList = nodeCurrentNode->getChildNodes();
        int i = 0;
        while (Node.getStatus() == 0 && i < (int)ChildNodeList->getLength())
        {
            node ChildNode(ChildNodeList->item(i));
            unsigned short nodetype = ChildNode.nodeCurrentNode->getNodeType();
            if (nodetype == 1 && ChildNode.nodeCurrentNode->hasChildNodes()) {
                string NodeAttributeValue = ChildNode.getAttributeValue(AttributeName);
                if (AttributeValue.compare(NodeAttributeValue) == 0) {
                    Node = ChildNode;
                }
            }
            i++;
        }

        if (Node.getStatus() == 0) {
            cout << "findNodebyAttribute Node not found" << endl;
        }
    }
    return Node;
}

node node::clone()
{
    return node(nodeCurrentNode->cloneNode(true));
}

std::string node::getNodeName()
{
    return XMLString::transcode(nodeCurrentNode->getNodeName());
}

std::string node::getNodeValue()
{
    return XMLString::transcode(nodeCurrentNode->getTextContent());
}

std::string node::getAttributeValue(std::string Attribute)
{
    string AttributeValue;
    if (nodeCurrentNode->hasAttributes()) {
        DOMNamedNodeMap* AttributesList = nodeCurrentNode->getAttributes();
        int i = 0;
        string AttributeName;
        while (AttributeName.compare(Attribute) != 0 && i < (int)AttributesList->getLength())
        {
            node ChildNode(AttributesList->item(i));
            AttributeName.assign(ChildNode.getNodeName());
            AttributeValue.assign(ChildNode.getNodeValue());
            i++;
        }
    }
    return AttributeValue;
}

int node::getStatus()
{
    return iStatus;
}

int node::appendChild(node ChildElement)
{
    nodeCurrentNode->appendChild(ChildElement.nodeCurrentNode);
    return 0;
}

int node::setAttribute(std::string Name, std::string Value)
{
    elementCurrentNode->setAttribute(XMLString::transcode(Name.c_str()), XMLString::transcode(Value.c_str()));
    return 0;
}

std::vector<node> node::findNodesChildNode()
{
    std::vector<node> Nodes;
    if (nodeCurrentNode->hasChildNodes())
    {
        DOMNodeList* ChildNodeList = nodeCurrentNode->getChildNodes();
        for (unsigned long i = 0; i < ChildNodeList->getLength(); i++)
        {
            node ChildNode(ChildNodeList->item(i));
            if (ChildNode.nodeCurrentNode->getNodeType() == 1)
            {
                Nodes.push_back(ChildNode);
            }
        }
        if (Nodes.size() == 0) {
            debugPrint("findNodesChild Node not found");
        }
    }
    return Nodes;
}

std::vector<node> node::findNodesbyName(std::string NodeName)
{
    std::vector<node> Nodes;
    if (nodeCurrentNode->hasChildNodes())
    {
        DOMNodeList* ChildNodeList = nodeCurrentNode->getChildNodes();
        for (unsigned long i = 0; i < ChildNodeList->getLength(); i++)
        {
            node ChildNode(ChildNodeList->item(i));
            if (NodeName.compare(ChildNode.getNodeName()) == 0)
            {
                Nodes.push_back(ChildNode);
            }
        }
        if (Nodes.size() == 0) {
            debugPrint("findNodesbyNodeName Node not found");
        }
    }
    return Nodes;
}

std::vector<node> node::findNodesbyAttribute(std::string Attribute, std::string AttributeValue)
{
    std::vector<node> Nodes;
    if (nodeCurrentNode->hasChildNodes())
    {
        DOMNodeList* ChildNodeList = nodeCurrentNode->getChildNodes();
        for (unsigned long i = 0; i < ChildNodeList->getLength(); i++)
        {
            node ChildNode(ChildNodeList->item(i));
            if (AttributeValue.compare(ChildNode.getAttributeValue(Attribute)) == 0) {
                Nodes.push_back(ChildNode);
            }
        }
        if (Nodes.size() == 0) {
            debugPrint("findNodesbyAttribute Node not found");
        }
    }
    return Nodes;
}

int node::setTextContent(std::string TextContent)
{
    nodeCurrentNode->setTextContent(XMLString::transcode(TextContent.c_str()));
    return 0;
}

void node::listChildNode()
{
    DOMNodeList* ChildNodeList = nodeCurrentNode ->getChildNodes();
    cout << "ChildNode: " << ChildNodeList->getLength() << endl;
    for (unsigned long i = 0; i < ChildNodeList->getLength(); i++)
    {
        cout << XMLString::transcode(ChildNodeList->item(i)->getNodeName()) << " : " << XMLString::transcode(ChildNodeList->item(i)->getTextContent()) << "." << endl;
    }
}
