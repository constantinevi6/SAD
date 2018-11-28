//
//  node.cpp
//  SNAP_SBAS
//
//  Created by Constantine VI on 2018/8/7.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "node.hpp"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace xercesc;
using namespace std;

xercesc::DOMNode *findNodebyNodeName(std::string NodeName, xercesc::DOMNode *InputNode)
{
    xercesc::DOMNode *Node=nullptr;
    DOMNodeList *ChildNodeList = InputNode->getChildNodes();
    int i=0;
    do {
        DOMNode *ChildNode = ChildNodeList->item(i);
        if (NodeName.compare(XMLString::transcode(ChildNode->getNodeName())) == 0)
        {
            Node = ChildNode;
        }
        i++;
    } while (Node==nullptr && i < ChildNodeList->getLength());
    i=0;
    do {
        DOMNode *ChildNode = ChildNodeList->item(i);
        unsigned short nodetype = ChildNode->getNodeType();
        if (nodetype == 1 && ChildNode->hasChildNodes()) {
            Node=findNodebyNodeName(NodeName, ChildNode);
        }
        i++;
    } while (Node==nullptr && i < ChildNodeList->getLength());
    if (Node == nullptr) {
        cout << "findNodebyNodeName Node not found" << endl;
    }
    return Node;
}

xercesc::DOMNode *findNodebyAttribute(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode)
{
    xercesc::DOMNode *Node=nullptr;
    DOMNodeList *ChildNodeList = InputNode->getChildNodes();
    int i=0;
    do {
        DOMNode *ChildNode = ChildNodeList->item(i);
        unsigned short nodetype = ChildNode->getNodeType();
        if (nodetype == 1 && ChildNode->hasChildNodes()) {
            string NodeAttributeValue=findAttributeValue(AttributeName, ChildNode);
            if (AttributeValue.compare(NodeAttributeValue) == 0) {
                Node = ChildNode;
            }
        }
        i++;
    } while (Node==nullptr && i < ChildNodeList->getLength());
    i=0;
    do {
        DOMNode *ChildNode = ChildNodeList->item(i);
        unsigned short nodetype = ChildNode->getNodeType();
        if (nodetype == 1 && ChildNode->hasChildNodes()) {
            Node=findNodebyAttribute(AttributeName, AttributeValue, ChildNode);
        }
        i++;
    } while (Node==nullptr && i < ChildNodeList->getLength());
    if (Node == nullptr) {
        cout << "findNodebyAttribute Node not found" << endl;
    }
    return Node;
}

std::string findAttributeValue(std::string Attribute, xercesc::DOMNode *InputNode)
{
    string AttributeValue;
    if (InputNode->hasAttributes()) {
        DOMNamedNodeMap *AttributesList = InputNode->getAttributes();
        for (unsigned long i=0; i<AttributesList->getLength(); i++)
        {
            DOMNode *ChildNode = AttributesList->item(i);
            string AttributeName = XMLString::transcode(ChildNode->getNodeName());
            if (AttributeName.compare(Attribute) == 0) {
                AttributeValue.assign(XMLString::transcode(ChildNode->getFirstChild()->getNodeValue()));
                break;
            }
        }
    }
    return AttributeValue;
}

std::string findNodeValuebyAttribute(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode)
{
    string NodeValue;
    DOMNodeList *ChildNodeList = InputNode->getChildNodes();
    for (unsigned long i=0; i<ChildNodeList->getLength(); i++)
    {
        DOMNode *ChildNode = ChildNodeList->item(i);
        string NodeAttributeValue=findAttributeValue(AttributeName, ChildNode);
        if (AttributeValue.compare(NodeAttributeValue) == 0) {
            NodeValue.assign(XMLString::transcode(ChildNode->getFirstChild()->getNodeValue()));
            break;
        }
    }
    return NodeValue;
}

std::vector<xercesc::DOMNode*> findNodesbyNodeName(std::string NodeName, xercesc::DOMNode *InputNode)
{
    std::vector<xercesc::DOMNode*> Nodes;
    DOMNodeList *ChildNodeList = InputNode->getChildNodes();
    for (unsigned long i=0; i<ChildNodeList->getLength(); i++)
    {
        DOMNode *ChildNode = ChildNodeList->item(i);
        string ChildNodeName = XMLString::transcode(ChildNode->getNodeName());
        if (NodeName.compare(ChildNodeName) == 0)
        {
            Nodes.push_back(ChildNode->cloneNode(true));
        }
    }
    if (Nodes.size() == 0) {
        cout << "findNodesbyNodeName Node not found" << endl;
    }
    return Nodes;
}

std::vector<xercesc::DOMNode*> findNodesbyAttribute(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode)
{
    std::vector<xercesc::DOMNode*> Nodes;
    DOMNodeList *ChildNodeList = InputNode->getChildNodes();
    for (unsigned long i=0; i<ChildNodeList->getLength(); i++)
    {
        DOMNode *ChildNode = ChildNodeList->item(i);
        string NodeAttributeValue=findAttributeValue(AttributeName, ChildNode);
        if (AttributeValue.compare(NodeAttributeValue) == 0) {
            Nodes.push_back(ChildNode->cloneNode(true));
        }
    }
    if (Nodes.size() == 0) {
        cout << "findNodesbyAttribute Node not found" << endl;
    }
    return Nodes;
}

std::vector<xercesc::DOMNode*> findNodesincludeAttribute(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode)
{
    std::vector<xercesc::DOMNode*> Nodes;
    DOMNodeList *ChildNodeList = InputNode->getChildNodes();
    for (unsigned long i=0; i<ChildNodeList->getLength(); i++)
    {
        DOMNode *ChildNode = ChildNodeList->item(i);
        string findNodeValue=findAttributeValue(AttributeName, ChildNode);
        if (findNodeValue.find(AttributeValue) != findNodeValue.npos) {
            Nodes.push_back(ChildNode->cloneNode(true));
        }
    }
    if (Nodes.size() == 0) {
        cout << "findNodesincludeAttribute Node not found" << endl;
    }
    return Nodes;
}

xercesc::DOMNode *getNodebyName(std::string NodeName, std::string NodeValue, std::vector<xercesc::DOMNode*> InputNodes)
{
    DOMNode *getNode = nullptr;
    vector<DOMNode*>::iterator Nodeiterator;
    for (Nodeiterator = InputNodes.begin(); Nodeiterator != InputNodes.end();)
    {
        DOMNode *Node= *Nodeiterator;
        DOMNode *findNode=findNodebyNodeName(NodeName, Node);
        string findNodeValue = XMLString::transcode(findNode->getFirstChild()->getNodeValue());
        if (findNodeValue.compare(NodeValue) == 0) {
            getNode = Node->cloneNode(true);
            Nodeiterator = InputNodes.erase(Nodeiterator);
            break;
        }
        else
        {
            ++Nodeiterator;
        }
    }
    if (getNode == nullptr) {
        cout << "getNodebyName Node not found" << endl;
    }
    return getNode;
}

xercesc::DOMNode *getNodeincludeAttribute(std::string AttributeName, std::string AttributeValue, std::vector<xercesc::DOMNode*> InputNodes)
{
    DOMNode *getNode = nullptr;
    vector<DOMNode*>::iterator Nodeiterator;
    for (Nodeiterator = InputNodes.begin(); Nodeiterator != InputNodes.end();)
    {
        DOMNode *Node= *Nodeiterator;
        string findNodeValue = findAttributeValue(AttributeName, Node);
        if (findNodeValue.find(AttributeValue) != findNodeValue.npos) {
            getNode = Node->cloneNode(true);
            Nodeiterator = InputNodes.erase(Nodeiterator);
            break;
        }
        else
        {
            ++Nodeiterator;
        }
    }
    if (getNode == nullptr) {
        cout << "getNodeincludeAttribute Node not found" << endl;
    }
    return getNode;
}

void replaceTextContentbyNodeName(std::string NodeName, std::string TextContent,xercesc::DOMNode *InputNode)
{
    DOMNode *Node = findNodebyNodeName(NodeName, InputNode);
    Node->setTextContent(XMLString::transcode(TextContent.c_str()));
}

void replaceTextContentbyAttribute(std::string AttributeName, std::string AttributeValue, std::string TextContent,xercesc::DOMNode *InputNode)
{
    DOMNode *Node = findNodebyAttribute(AttributeName, AttributeValue, InputNode);
    Node->setTextContent(XMLString::transcode(TextContent.c_str()));
}

void replaceAttributeValue(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode)
{
    if (InputNode->hasAttributes()) {
        DOMNamedNodeMap *AttributesList = InputNode->getAttributes();
        for (unsigned long i=0; i<AttributesList->getLength(); i++)
        {
            DOMNode *ChildNode = AttributesList->item(i);
            if (AttributeName.compare(XMLString::transcode(ChildNode->getNodeName())) == 0) {
                ChildNode->getFirstChild()->setNodeValue(XMLString::transcode(AttributeValue.c_str()));
                break;
            }
        }
    }
}

void listChildNode(xercesc::DOMNode *InputNode)
{
    DOMNodeList *ChildNodeList = InputNode->getChildNodes();
    for (unsigned long i=0; i<ChildNodeList->getLength(); i++)
    {
        cout << XMLString::transcode(ChildNodeList->item(i)->getNodeName()) << endl;
    }
}
