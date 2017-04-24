#ifndef VOLIMAGE_H
#define VOLIMAGE_H

#include <vector>

using namespace std;

namespace RSHMUS001 {

    class VolImage {

    private:  // private memebers

        int width, height;  //width and height of image stack
        vector <unsigned char**> slices;  // data for each slice, in order

    public: //public members

        VolImage(); // default constructor - define in .cpp
        ~VolImage();  // destructor - define in .cpp file

        // populate the object with images in stack and
        //set member variables define in .cpp
        bool readImages(string baseName);

        // compute difference map and write out; define in .cpp
        void diffmap(int sliceI, int slice J, string output_prefix);

        // extract slice sliceId and write to output - define in .cpp
        void extract(int sliceId, string output_prefix);

        // extract image along rowId of the volume, across all rows.
      	//write output to file output_prefix.raw. Define in .cpp
      	void sliceThrough(int rowId, string output_prefix);

        // number of bytes uses to store image data bytes
        //and pointers (ignore vector<> container, dims etc)
        int volImageSize(void); // define in .cpp

        //number of images
        //define in .cpp
        int volImageNum(void);

        //generate header file for each opearation
        void generateHeader(int w, int h, int n, string output_prefix);

    };

}
