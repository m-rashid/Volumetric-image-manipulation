#include "VolImage.h"
#include <string>
#include <iostream>
#include <ios>
#include <sstream>

using namespace std;

int main (int argc, char* argv[]){

    if (argc < 2){
        cerr << "Incorrect number of arguments\n" << endl;
        return 1;
    }

    else {

        RSHMUS001::VolImage vol;

        bool success = vol.readImages(string(argv[1])); //argv[1] is the image base
        //vol.extract(5, "output");

        if (!success) {
            cerr << "An error occured. Please check that your <imageBase> is correct" << endl;
            return 1;
        }

        cout << "Number of images: " << vol.volImageNum() << endl;
        cout << "Number of bytes required: " << vol.volImageSize() << endl;

        for (int i = 2; i < argc; i++){

            if (string(argv[i]) == "-d"){

                if ((i==2 && argc<6) || (i==6 && argc<9)) {
                    cerr << "Incorrect number of arguments" << endl;
                    return 1;
                }

                int image1, image2;
                istringstream(argv[i+1]) >> image1;
                istringstream(argv[i+2]) >> image2;
                vol.diffmap(image1, image2, argv[i+3]);
                cout << "Computed a difference map between images " << image1 << "and" << image2 << "and wrote this out to file " << argv[i+3] << ".raw" << endl;
            }

            if (string(argv[i]) == "-x"){

                if ((i==2 && argc<5) || (i==6 && argc<8)) {
                    cerr << "Incorrect number of arguments" << endl;
                    return 1;
                }

                int sliceId;
                istringstream(argv[i+1]) >> sliceId;
                cout << sliceId;
                vol.extract (sliceId, argv[i+2]);
                cout << "Extracted the slice with number " << sliceId << " and wrote this to file "<< argv[i+2] << ".raw" << endl;

            }

        }

    }

    return 1;
}
