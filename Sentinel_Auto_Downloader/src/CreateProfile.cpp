//
//  Sentinel Auto Downloader
//
//  Created by Constantine VI on 2018/6/29.
//  Copyright © 2018年 Constantine VI. All rights reserved.
//

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int CreateProfile(std::string Profile){
    cout << "Creating input profile \"" << Profile << "\"..." << endl;
    fstream ProfileOutput;
    ProfileOutput.open(Profile, ios::out);
    ProfileOutput << "#Sentinel Auto Download Configure" << endl;
    ProfileOutput << "# Leave empty line for none setting." << endl;
    ProfileOutput << "#" << endl;
    ProfileOutput << "# Download Path" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Username for login Sentinel Data Hub" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Password" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Platform Name (Sentinel-1, Sentinel-2, Sentinel-3)" << endl;
    ProfileOutput << "Sentinel-1" << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Time Search (beginposition, endposition, ingestiondate)" << endl;
    ProfileOutput << "beginposition" << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Start Time (yyyy-MM-ddThh:mm:ss.SSSZ, NOW, NOW-<n>[MINUTE(S), HOUR(S), DAY(S), MONTH(S)])" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# End Time (yyyy-MM-ddThh:mm:ss.SSSZ, NOW, NOW-<n>[MINUTE(S), HOUR(S), DAY(S), MONTH(S)])" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Product File Name (* can be used in name)" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Area Of Interest(AOI) (Use polygon search while there are several line of coordinate.)" << endl;
    ProfileOutput << "Lon Lat" << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Product Type (SLC, GRD, OCN)" << endl;
    ProfileOutput << "SLC" << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Product Mode (IW, SM, EW, WV)" << endl;
    ProfileOutput << "IW" << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Direction of the Orbit (Ascending, Descending)" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Absolute Orbit Number Search (orbitnumber, lastorbitnumber)" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Absolute Orbit Number (<orbitnumber>, [<orbitnumber> TO <orbitnumber>])" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Relative Orbit Number Search (relativeorbitnumber, lastrelativeorbitnumber)" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Relative Orbit Number (<orbitnumber>, [<orbitnumber> TO <orbitnumber>])" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Product Polarisation (HH, VV, HV, VH, HH HV, VV VH)" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Product Swath Identifier (S1, S2, S3, S4, S5, S6, IW, IW1, IW2, IW3, EW, EW1, EW2, EW3, EW4, EW5)" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Product Cloud Cover Percentage (<cloudcoverpercentage>, [<cloudcoverpercentage> TO <cloudcoverpercentage>])" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput << "# Collection" << endl;
    ProfileOutput << endl;
    ProfileOutput << endl;
    ProfileOutput.close();
    return 0;
}
