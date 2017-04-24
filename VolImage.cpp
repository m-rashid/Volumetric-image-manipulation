#include "VolImage.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ios>
#include <sstream>
#include <cmath>

using namespace std;

namespace RSHMUS001{

  VolImage::VolImage(){
      width = 0;
      height = 0;

  }

  VolImage::~VolImage(){
      for (int i = 0; i < slices.size(); i++){
          for (int j = 0; j < height; j++){
              delete [] slices[i][j];
          }
          delete slices[i];
      }
  }

  bool VolImage::readImages(string baseName){

      //getting filepath of .dat file
      string folderName = "brain_mri_raws";
      string fileName = folderName + "/" + baseName + ".data";
      ifstream dataFile (fileName.c_str(), ios::binary);
      int noOfImages;
      if (!dataFile){
          cerr << "File open failed!" << endl;
      }

      vector<int> data_vec; //vector to hold specs: width, height, number of slices
      string imgData;

      while (!dataFile.eof()){


          for (imgData ; getline(dataFile, imgData);){
              istringstream str (imgData);
              while (str){
                  int split;
                  str >> split;
                  data_vec.push_back(split);
              }
          }

          width = data_vec[0];
          height = data_vec[1];
          noOfImages = data_vec[2];
          //cout << width << " " << height << " " << noOfImages << endl;
      }
      dataFile.close();

      //store the contents of each .raw file into 2D array
      unsigned char** slice;
      string file_raw = "";

      for(int i=0; i<noOfImages; i++){
          stringstream ss;
          ss << i;
          file_raw = "brain_mri_raws/"+baseName + ss.str() + ".raw";

          ifstream raw(file_raw.c_str(), ios::binary);

          slice = new unsigned char*[height]; //row

          for(int j=0; j<height; j++){
              slice[j] = new unsigned char[width]; //columns
              raw.read((char*)slice[j], width);

          }
          raw.close();
          slices.push_back(slice);
      }

      return true;
  }

  void VolImage::diffmap (int sliceI, int sliceJ, string output_prefix){
      string output = output_prefix + ".raw";
      ofstream of(output.c_str(), ios::binary);

      //array to hold the diff maps
      unsigned char** temp_arr = new unsigned char* [height];

      for (int r = 0; r < height; r++){
          temp_arr[r] = new unsigned char[width];
          for (int c = 0; c < width; c++){
              temp_arr[r][c] = (unsigned char)(fabs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c])/2);
          }
          of.write((char*)temp_arr[r], width);
      }

      of.close();
      generateHeader (width, height, 1, output_prefix);

  }
  void VolImage::extract (int sliceId, string output_prefix){
      string output = output_prefix + ".raw";
      ofstream of(output.c_str(), ios::binary);

      for(int r = 0; r < height; r++){
          of.write((char*)slices[sliceId][r], width);
      }

      of.close();
      generateHeader (width, height, 1, output_prefix);
  }

  void VolImage::sliceThrough (int rowId, string output_prefix){
      string output = output_prefix + ".raw";
      ofstream of(output.c_str(), ios::binary);

      for (int i = 0; i < slices.size(); i++){
          of.write((char*)slices[i][rowId], width);
      }

      of.close();
      generateHeader(width, slices.size(), 1, output_prefix);
  }

  int VolImage::volImageSize(void){

      //(no. of elements * charSize) + (rows * pointerSize) + (double pointer)
      return (width * height * slices.size() * sizeof(char)) + (height * slices.size() * sizeof(unsigned char*)) + (slices.size() * sizeof(unsigned char*));
  }

  int VolImage::volImageNum(void){
      return slices.size();
  }


  void VolImage::generateHeader(int w, int h, int n, string output_prefix) {
      string filename = output_prefix + ".data";
      ofstream of(filename.c_str(), ios::binary);
      of << w << " " << h << " " << n;
      of.close();
  }

}
