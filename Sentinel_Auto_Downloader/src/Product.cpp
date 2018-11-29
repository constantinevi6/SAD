//
//  Product.cpp
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/7/5.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "Product.h"
#include "node.hpp"
#include "sad.h"
#include <math.h>
#include <iostream>

using namespace std;

Product::Product()
{
    Title = "";
    PlatformName="";
    FileSize=0;

    Satellite = "";
    Mode = "";
    Category="";
    Type = "";
    Resolution = "";
    Level = "";
    Class = "";
    Polarisation = "";
    StartTime = "";
    StopTime = "";
    Orbit = "";
    TakeID = "";
    UniqueID = "";
    DatabaseTitle = "";
    UUID = "";
}

void Product::read(xercesc::DOMNode *ProductEntry)
{
    
    xercesc::DOMNodeList* nodeList = ProductEntry->getChildNodes();
    for (unsigned long i = 0; i < nodeList->getLength(); i++)
    {
        xercesc::DOMNode *node = nodeList->item(i);
        string nodeName = xercesc::XMLString::transcode(node->getNodeName());
        if (nodeName == "title")
        {
            Title = xercesc::XMLString::transcode(node->getTextContent());
        }
        else if (nodeName == "id")
        {
            UUID = xercesc::XMLString::transcode(node->getTextContent());
            get_url();
        }
        else if (nodeName == "str")
        {
            string Attribute = findAttributeValue("name", node);
            if (Attribute == "platformname") {
                PlatformName = xercesc::XMLString::transcode(node->getTextContent());
                set(Title);
            }
            else if (Attribute == "size") {
                string filesize = xercesc::XMLString::transcode(node->getTextContent());
                string unit;
                unit.assign(filesize,filesize.size()-2,filesize.size());
                filesize.assign(filesize,0,filesize.size()-3);
                FileSize = stod(filesize);
            }
            else if (Attribute == "instrumentshortname") {
                InstrumentShortname = xercesc::XMLString::transcode(node->getTextContent());
            }
            else if (Attribute == "sensoroperationalmode") {
                SensorOperationalMode = xercesc::XMLString::transcode(node->getTextContent());
            }
            else if (Attribute == "instrumentname") {
                InstrumentName = xercesc::XMLString::transcode(node->getTextContent());
            }
            else if (Attribute == "swathidentifier") {
                SwathIdentifier = xercesc::XMLString::transcode(node->getTextContent());
            }
            else if (Attribute == "orbitdirection") {
                OrbitDirection = xercesc::XMLString::transcode(node->getTextContent());
            }
            else if (Attribute == "polarisationmode") {
                PolarisationMode = xercesc::XMLString::transcode(node->getTextContent());
            }
            else if (Attribute == "productclass") {
                ProductClass = xercesc::XMLString::transcode(node->getTextContent());
            }
            else if (Attribute == "platformserialidentifier") {
                PlatformSerialIdentifier = xercesc::XMLString::transcode(node->getTextContent());
            }
            else if (Attribute == "processinglevel") {
                ProcessingLevel = xercesc::XMLString::transcode(node->getTextContent());
            }
            else if (Attribute == "producttype") {
                ProductType = xercesc::XMLString::transcode(node->getTextContent());
            }
        }
    }
}

void Product::set(std::string ProductTitle)
{
    Title = ProductTitle;
    if (PlatformName == "Sentinel-1") {
        Satellite.assign(Title,0,3);
        Mode.assign(Title,4,2);
        Type.assign(Title,7,3);
        Resolution.assign(Title,10,1);
        Level.assign(Title,12,1);
        Class.assign(Title,13,1);
        Polarisation.assign(Title,14,2);
        StartTime.assign(Title,17,15);
        StopTime.assign(Title,33,15);
        Orbit.assign(Title,49,6);
        TakeID.assign(Title,56,6);
        UniqueID.assign(Title,63,4);
    }
    else if (PlatformName == "Sentinel-2") {
        Satellite.assign(Title,0,3);
        Category.assign(Title,4,3);
        Level.assign(Title,7,3);
        StartTime.assign(Title,11,15);
    }
}

void Product::get_url()
{
    DownloadLink = (string)OpenDataHub + "('" + UUID + "')" + "/" + URLSlash + "$value";
}

void Product::get_uuid(std::string uuid)
{
    UUID = uuid;
}

std::string &Product::call_title()
{
    return Title;
}

std::string &Product::call_url()
{
    return DownloadLink;
}

std::string &Product::call_database_title()
{
    std::string UnderLine = "_";
    DatabaseTitle = Satellite + UnderLine + Mode + UnderLine + Type + Resolution + UnderLine + Level + Class + Polarisation + UnderLine + StartTime + UnderLine + UniqueID;
    return DatabaseTitle;
}
