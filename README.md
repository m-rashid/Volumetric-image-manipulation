# Volumetric-image-manipulation
Volumetric Image Manipulation tool to load a 'stack' of 2D MRI images and manipulate them as a group.  
  
GETTING STARTED  
  
After unpacking the tarball, you will find the following files:  
  
VolImage.h     -  Header file containing the structure for VolImage class  
VolImage.cpp   -  Defintions for the methods declared in the header file  
driver.cpp     -  Driver file containing the main() method to run the program  
viewer.py      -  Command line RAW file viewer  
brain_mri_raws -  Folder containing the RAW MRI image slices  
Makefile       -  Utility for compiling, linking and creating the executable  
  
  
COMPILING  
  
Navigate to the project source folder. Run 'make' in the terminal.
An executable named 'volimage' is created  
  
  
RUNNING  
  
Execute only one of the following commands to run one of the three operations in  
the format: volimage <imageBase> [-d i j output_file_name] [-x i output_file_name]  
ImageBase (prefix for file sequences) used in this program is MRI.  
  
./volimage MRI  
Build the internal representation, display number of images and total bytes  
  
./volImage MRI -d i j output  
Compute difference map between images i and j, and write this to 'output.raw'  
  
./volImage MRI -x i output  
Extract the slice with number i, and write this to output.raw  
  
./volImage MRI -g i output  
Extract an image along row i, across all slices, and write this to 'output.raw'  
  
  
NOTES  
  
1. This Image Manipulation tool makes use of a sequence of MRI RAW images to  
   perform operations on. If you wish to use a different sequence, you either  
   need to change the folder name in the VolImage::readImages() function  
   implementation or place the RAW files into the brain_mri_raws folder.  
  
2. The python convenience utility, viewer.py, can be used to view RAW files  
   via the command line. This can be invoked in the following way:  
   python viewer.py <raw filename> <width> <height>  
   The width and height for the RAW image is displayed in the .data header file  
   placed in the MRI sequence folder, and available with every output RAW file.  
   Header file format: <width> <height> <number_of_images>  

