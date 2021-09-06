//
//  xml.cpp
//  Automatic SAR Processing System
//
//  Created by Constantine VI on 2020/6/4.
//  Copyright © 2020 Constantine VI. All rights reserved.
//

#include "xml.hpp"
#include <iostream>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

using namespace xercesc;
using namespace std;

xml::xml() {

}

xml::xml(std::string XMLPath) {
    PATH_XML = filesystem::path(XMLPath);
}

xml::xml(std::filesystem::path XMLPath) {
    PATH_XML = XMLPath;
}

node xml::getRootElement()
{
    return node(XMLDoc->getDocumentElement());
}

node xml::getNodebyName(std::string NodeName)
{
    node Node;
    if (XMLDoc->hasChildNodes())
    {
        DOMNodeList* ChildNodeList = XMLDoc->getChildNodes();
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
            std::cout << "getNodebyName Node : " << NodeName << " not found." << std::endl;
        }
    }
    return Node;
}

int xml::save()
{
    XMLCh tempStr[100];
    XMLString::transcode("LS", tempStr, 99);
    DOMImplementation* pImplement = DOMImplementationRegistry::getDOMImplementation(tempStr);
    DOMLSSerializer* pSerializer = ((DOMImplementationLS*)pImplement)->createLSSerializer();
    XMLFormatTarget* pTarget = new LocalFileFormatTarget(PATH_XML.string().c_str());
    DOMConfiguration* pDomConfiguration = pSerializer->getDomConfig();
    DOMLSOutput* pDomLsOutput = ((DOMImplementationLS*)pImplement)->createLSOutput();
    pDomConfiguration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
    pDomConfiguration->setParameter(XMLUni::fgDOMWRTXercesPrettyPrint, false);
    pDomLsOutput->setByteStream(pTarget);
    try {
        pSerializer->write(XMLDoc, pDomLsOutput);
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        return 1;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        cout << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        return 1;
    }
    catch (...) {
        cout << "Unexpected Exception \n";
        return 1;
    }

    pSerializer->release();
    pDomLsOutput->release();
    delete pTarget;
    return 0;
}

int xml::save(std::string XMLPath)
{
    XMLCh tempStr[100];
    XMLString::transcode("LS", tempStr, 99);
    DOMImplementation* pImplement = DOMImplementationRegistry::getDOMImplementation(tempStr);
    DOMLSSerializer* pSerializer = ((DOMImplementationLS*)pImplement)->createLSSerializer();
    XMLFormatTarget* pTarget = new LocalFileFormatTarget(XMLPath.c_str());
    DOMConfiguration* pDomConfiguration = pSerializer->getDomConfig();
    DOMLSOutput* pDomLsOutput = ((DOMImplementationLS*)pImplement)->createLSOutput();
    pDomConfiguration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
    pDomLsOutput->setByteStream(pTarget);
    try {
        pSerializer->write(XMLDoc, pDomLsOutput);
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        return 1;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        cout << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        return 1;
    }
    catch (...) {
        cout << "Unexpected Exception \n";
        return 1;
    }

    pSerializer->release();
    pDomLsOutput->release();
    delete pTarget;
    return 0;
}

int xml::create(std::string RootName)
{
    XMLPlatformUtils::Initialize();
    DOMImplementation* p_DOMImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));
    XMLDoc = p_DOMImplementation->createDocument(0, XMLString::transcode(RootName.c_str()), 0);
    return 0;
}

int xml::read()
{
    if (!exists(PATH_XML))
    {
        cout << "XML file " << PATH_XML.string() << " not found." << endl;
        exit(1);
    }
    XMLPlatformUtils::Initialize();
    XML = new xercesc::XercesDOMParser();
    XML->parse(PATH_XML.string().c_str());
    XMLDoc = XML->getDocument();
    return 0;
}

void xml::close()
{
    delete(XML);
    XMLPlatformUtils::Terminate();
}

node xml::createComment(std::string NodeComment)
{
    DOMComment* Comment = XMLDoc->createComment(XMLString::transcode(NodeComment.c_str()));
    return node(Comment);
}

node xml::createElement(std::string NodeName)
{
    node newElement(XMLDoc->createElement(XMLString::transcode(NodeName.c_str())));
    return newElement;
}

node xml::createElement(std::string NodeName,std::string NodeValue)
{
    node newElement(XMLDoc->createElement(XMLString::transcode(NodeName.c_str())));
    newElement.setTextContent(NodeValue);
    return newElement;
}

node xml::createTextNode(std::string NodeText)
{
    DOMText* TextNode = XMLDoc->createTextNode(XMLString::transcode(NodeText.c_str()));
    return node(TextNode);
}
