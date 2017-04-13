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

    //getting filepath of .dat file
    string folderName = "brain_mri_raws.tar";
    string fileName = folderName + "/" + baseName + ".dat";
    ifstream dataFile (fileName.c_str());
    int noOfImages;
    if (!dataFile){
        cerr << "File open failed!" << endl;
    }

    vector<int> data_vec; //vector to hold specs: width, height, number of slices
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
    dataFile.close();

    //store the contents of each .raw file into 2D array
    unsigned char** slice;
    string file_raw = "";

    for(int i=0; i<noOfImages; i++){
        stringstream ss;
        ss << i;
        file_raw = baseName + ss,str() + ".raw";

        ifstream raw(file_raw.c_str(), ios::binary);

        slice = new unsigned char*[height]; //row

        for(int j=0; j<height; j++){
            slice[j] = new unsigned char[width]; //columns
            raw.read((char*)slice[j], width);
            
        }
        raw.close();
    }

    slices.push_back(slice);

    return true;
}
