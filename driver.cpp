#include "VolImage.h"

using namespace std;

int main (int arc, char* argv[]){

    if (argc < 2){
        cerr << "Incorrect number of arguments\n" << endl;
        return 1;
    }

    else {

        VolImage vol;

        bool success = vol.readImages(argv[1]); //argv[1] is the image base

        if (success == "false") {
            cerr << "An error occured. Please check that your <imageBase> is correct" << endl;
            return 1;
        }

        cout << "Number of images: " << vol.slices.size() << endl;
        cout << "Number of bytes required" << vol.volImageSize() << endl;

        for (int i = 2; i < argc; i++){

            if (argv[i] == "-d"){

                if ((i==2 && argc<6) || (i==6 && argc<9)) {
                    cerr << "Incorrect number of arguments" << endl;
                    return 1;
                }

                int image1, image2;
                istringstream(argv[i+1]) >> image1;
                istringstream(argv[i+2]) >> image2;
                vol.diffmap(image1, image2, argv[i+3]);
                cout << "Computed a difference map between images " << image1 << "and" << image2 << "
                        and wrote this out to file" << argv[i+3] << ".raw" << endl;
            }

            if (argv[i] == "-x"){

                if ((i==2 && argc<6) || (i==6 && argc<9)) {
                    cerr << "Incorrect number of arguments" << endl;
                    return 1;
                }

                int sliceId;
                istringstream(argv[i+1] >> sliceId);
                vol.extract (sliceId, argv[i+2]);
                cout << "Extracted the slice with number " << sliceId << "and wrote this to file "
                        << argv[i+2] << endl;

            }

        }

    }

    return 1;
}
