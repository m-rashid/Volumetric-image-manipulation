#include "VolImage.h"

using namespace std;
using namespace RSHMUS001;

VolImage::VolImage(){
    width = 0;
    height = 0;
}

VolImage::~VolImage(){

}

bool VolImage::readImages(string baseName){
    string folderName = "brain_mri_raws.tar";
    string fileName = folderName + "/" + baseName + ".dat";
    ifstream dataFile (fileName.c_str());
    int noOfImages;
    if (!dataFile){
        cerr << "File open failed!" << endl;
    }

    vector<int> data_vec;
    string imgData;

    while (dataFile.eof()){

        for (imgData ; getline(dataFile, imgData);){
            istringstream str (imgData);
            while (str){
                string split;
                str >> split;
                data_vec.push_back(split);
                split = "";
            }
        }

        width = data_vec[0];
        height = data_vec[1];
        noOfImages = data_vec[2];

    }
}
