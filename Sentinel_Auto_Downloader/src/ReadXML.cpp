//
//  ReadXML.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/5.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include "Product.h"
#include <string>
#include <vector>
#include <iostream>

using namespace xercesc;
using namespace std;

int ReadXML(std::string InputXML, vector<Product> *ProductList)
{
    XMLPlatformUtils::Initialize();
    XercesDOMParser *XML = new XercesDOMParser();
    XML->parse(InputXML.c_str());
    DOMDocument *xmlDoc = XML->getDocument();
    DOMNodeList* entryList = xmlDoc->getElementsByTagName(XMLString::transcode("entry"));
    unsigned long ProductCount = entryList->getLength();
    //ProductList = new vector<Product>[ProductCount];
    cout << "Find " << ProductCount << " Products" <<endl;
    for (unsigned long i = 0; i < ProductCount; i++)
    {
        Product Product;
        DOMNode *entry = entryList->item(i);
        Product.read(entry);
        cout << Product.call_title() << endl;
        ProductList -> push_back(Product);
    }
    delete(XML);
    XML = NULL;
    XMLPlatformUtils::Terminate();
    return 0;
}

