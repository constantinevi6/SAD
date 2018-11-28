//
//  node.hpp
//  SNAP_SBAS
//
//  Created by Constantine VI on 2018/8/7.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <xercesc/dom/DOM.hpp>
#include <string>
#include <vector>

xercesc::DOMNode *findNodebyNodeName(std::string NodeName, xercesc::DOMNode *InputNode);
xercesc::DOMNode *findNodebyAttribute(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode);
xercesc::DOMElement *findElementbyNodeName(std::string NodeName, xercesc::DOMNode *InputNode);
std::string findAttributeValue(std::string Attribute, xercesc::DOMNode *InputNode);
std::string findNodeValuebyAttribute(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode);
std::vector<xercesc::DOMNode*> findNodesbyNodeName(std::string NodeName, xercesc::DOMNode *Data_Access);
std::vector<xercesc::DOMNode*> findNodesbyAttribute(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode);
std::vector<xercesc::DOMNode*> findNodesincludeAttribute(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode);
xercesc::DOMNode *getNodebyName(std::string NodeName, std::string NodeValue, std::vector<xercesc::DOMNode*> InputNodes);
xercesc::DOMNode *getNodeincludeAttribute(std::string AttributeName, std::string AttributeValue, std::vector<xercesc::DOMNode*> InputNodes);
void replaceTextContentbyNodeName(std::string NodeName, std::string TextContent,xercesc::DOMNode *InputNode);
void replaceTextContentbyAttribute(std::string AttributeName, std::string AttributeValue, std::string TextContent,xercesc::DOMNode *InputNode);
void replaceAttributeValue(std::string AttributeName, std::string AttributeValue, xercesc::DOMNode *InputNode);
void listChildNode(xercesc::DOMNode *InputNode);

#endif /* node_hpp */
