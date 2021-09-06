//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/6/29.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include "xml.hpp"
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int CreateProfile(std::filesystem::path xmlConfiguration){
    cout << "Creating input configuration file: " << xmlConfiguration.string() << "..." << endl;
    xml xmlProfile(xmlConfiguration);
    xmlProfile.create("Sentinel_Auto_Download_Configuration");
    node Root = xmlProfile.getRootElement();
    node nodeDownload_Path = xmlProfile.createElement("Download_Path", "");
    node nodeUsername = xmlProfile.createElement("Username", "");
    node nodePassword = xmlProfile.createElement("Password", "");
    node nodeComPlatform_Name = xmlProfile.createComment("Platform Name (Sentinel-1, Sentinel-2, Sentinel-3)");
    node nodePlatform_Name = xmlProfile.createElement("Platform_Name", "Sentinel-1");
    
    node nodeComTime_Search = xmlProfile.createComment("Time Search (beginposition, endposition, ingestiondate)");
    node nodeTime_Search = xmlProfile.createElement("Time_Search", "beginposition");
    
    node nodeComStart_Time = xmlProfile.createComment("Start Time / End Time (yyyy-MM-ddThh:mm:ss.SSSZ, NOW, NOW-<n>[MINUTE(S), HOUR(S), DAY(S), MONTH(S)])");
    node nodeStart_Time = xmlProfile.createElement("Start_Time", "NOW-30DAYS");
    node nodeEnd_Time = xmlProfile.createElement("End_Time", "NOW");
    
    node nodeComProduct_File_Name = xmlProfile.createComment("Product File Name (* can be used in name)");
    node nodeProduct_File_Name = xmlProfile.createElement("Product_File_Name", "");
    
    node nodeComAOI = xmlProfile.createComment("Area Of Interest(AOI) (Use polygon search while there are several line of coordinate.)");
    node nodeAOI = xmlProfile.createElement("Area_Of_Interest");
    node nodeFootprint = xmlProfile.createElement("Footprint", "");
    nodeAOI.appendChild(nodeFootprint);
    
    node nodeComProduct_Type = xmlProfile.createComment("Product Type (SLC, GRD, OCN)");
    node nodeProduct_Type = xmlProfile.createElement("Product_Type", "SLC");
    
    node nodeComProduct_Mode = xmlProfile.createComment("Product Mode (IW, SM, EW, WV)");
    node nodeProduct_Mode = xmlProfile.createElement("Product_Mode", "IW");
    
    node nodeComOrbit_Direction = xmlProfile.createComment("Direction of the Orbit (Ascending, Descending)");
    node nodeOrbit_Direction = xmlProfile.createElement("Orbit_Direction", "");
    
    node nodeComAbsolute_Mode = xmlProfile.createComment("Absolute Orbit Number Search (orbitnumber, lastorbitnumber)");
    node nodeAbsolute_Mode = xmlProfile.createElement("Absolute_Orbit_Number_Search_Mode", "");
    node nodeComAbsolute_Orbit = xmlProfile.createComment("Absolute Orbit Number (<orbitnumber>, [<orbitnumber> TO <orbitnumber>])");
    node nodeAbsolute_Orbit = xmlProfile.createElement("Absolute_Orbit_Number", "");
    node nodeComRelative_Mode = xmlProfile.createComment("Relative Orbit Number Search (relativeorbitnumber, lastrelativeorbitnumber)");
    node nodeRelative_Mode = xmlProfile.createElement("Relative_Orbit_Number_Search_Mode", "");
    node nodeComRelative_Orbit = xmlProfile.createComment("Relative Orbit Number (<orbitnumber>, [<orbitnumber> TO <orbitnumber>])");
    node nodeRelative_Orbit = xmlProfile.createElement("Relative_Orbit_Number", "");
    
    node nodeComPolarisation = xmlProfile.createComment("Polarisation (HH, VV, HV, VH, HH HV, VV VH)");
    node nodePolarisation = xmlProfile.createElement("Polarisation", "");
    
    node nodeComSwath_Identifier = xmlProfile.createComment("Product Swath Identifier (S1, S2, S3, S4, S5, S6, IW, IW1, IW2, IW3, EW, EW1, EW2, EW3, EW4, EW5)");
    node nodeSwath_Identifier = xmlProfile.createElement("Swath_Identifier", "");
    
    node nodeComCloud_Cover = xmlProfile.createComment("Product Cloud Cover Percentage (<cloudcoverpercentage>, [<cloudcoverpercentage> TO <cloudcoverpercentage>])");
    node nodeCloud_Cover = xmlProfile.createElement("Cloud_Cover_Percentage", "");
    node nodeCollection = xmlProfile.createElement("Collection", "");
    Root.appendChild(nodeDownload_Path);
    Root.appendChild(nodeUsername);
    Root.appendChild(nodePassword);
    Root.appendChild(nodeComPlatform_Name);
    Root.appendChild(nodePlatform_Name);
    Root.appendChild(nodeComTime_Search);
    Root.appendChild(nodeTime_Search);
    Root.appendChild(nodeComStart_Time);
    Root.appendChild(nodeStart_Time);
    Root.appendChild(nodeEnd_Time);
    Root.appendChild(nodeComProduct_File_Name);
    Root.appendChild(nodeProduct_File_Name);
    Root.appendChild(nodeComAOI);
    Root.appendChild(nodeAOI);
    Root.appendChild(nodeComProduct_Type);
    Root.appendChild(nodeProduct_Type);
    Root.appendChild(nodeComProduct_Mode);
    Root.appendChild(nodeProduct_Mode);
    Root.appendChild(nodeComOrbit_Direction);
    Root.appendChild(nodeOrbit_Direction);
    Root.appendChild(nodeComAbsolute_Mode);
    Root.appendChild(nodeAbsolute_Mode);
    Root.appendChild(nodeComAbsolute_Orbit);
    Root.appendChild(nodeAbsolute_Orbit);
    Root.appendChild(nodeComRelative_Mode);
    Root.appendChild(nodeRelative_Mode);
    Root.appendChild(nodeComRelative_Orbit);
    Root.appendChild(nodeRelative_Orbit);
    Root.appendChild(nodeComPolarisation);
    Root.appendChild(nodePolarisation);
    Root.appendChild(nodeComSwath_Identifier);
    Root.appendChild(nodeSwath_Identifier);
    Root.appendChild(nodeComCloud_Cover);
    Root.appendChild(nodeCloud_Cover);
    Root.appendChild(nodeCollection);
    xmlProfile.save();
    return 0;
}
