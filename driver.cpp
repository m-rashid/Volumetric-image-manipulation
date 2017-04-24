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

        if (!success) {
            cerr << "An error occured.\n Please check that your <imageBase> is correct\nPlease check that the folder name is correct" << endl;
            return 1;
        }

        cout << "Number of images: " << vol.volImageNum() << endl;
        cout << "Number of bytes required: " << vol.volImageSize() << endl;

        if (argc == 2){
            return 1;
        }

        string operation = string(argv[2]);

        if (operation == "-d") {

            if (argc!=6) {
                cerr << "Incorrect number of arguments" << endl;
                return 1;
            }


            int image1, image2;
            istringstream(argv[3]) >> image1;
            istringstream(argv[4]) >> image2;
            vol.diffmap(image1, image2, string(argv[5]));
            cout << "Computed a difference map between images " << image1 << "and " << image2 << ", and wrote this out to file " << argv[5] << ".raw" << endl;
            cout << "Generated header file, " << string(argv[5]) << " .data" << endl;

        }

        if (operation == "-x"){

            if (argc!=5) {
                cerr << "Incorrect number of arguments" << endl;
                return 1;
            }

            int sliceId;
            istringstream(argv[3]) >> sliceId;
            //cout << sliceId;
            vol.extract (sliceId, string(argv[4]));
            cout << "Extracted the slice with number " << sliceId << " and wrote this to file "<< argv[4] << ".raw" << endl;
            cout << "Generated header file, " << string(argv[4]) << " .data" << endl;

        }

        if (operation == "-g"){

            if (argc!=5) {
                cerr << "Incorrect number of arguments" << endl;
                return 1;
            }

            int rowId;
            istringstream(argv[3]) >> rowId;
            vol.sliceThrough(rowId, string(argv[4]));
            cout << "Extracted an image along row " << rowId << " of the volume, across all slices. Output written to file " << argv[4] << ".raw" << endl;
            cout << "Generated header file, " << string(argv[4]) << " .data" << endl;

        }
    }

return 1;

}
