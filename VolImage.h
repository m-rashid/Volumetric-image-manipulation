#ifndef VOLIMAGE_H
#define VOLIMAGE_H

#include <vector>

using namespace std;

namespace RSHMUS001 {

    class VolImage {

    private:  

        int width, height;
        vector <unsigned char**> slices;

    public:

        VolImage();
        ~VolImage();

        bool readImages(string baseName);

        void diffmap(int sliceI, int slice J, string output_prefix);

        void extract(int sliceId, string output_prefix);

        int volImageSize(void);

    };

}
