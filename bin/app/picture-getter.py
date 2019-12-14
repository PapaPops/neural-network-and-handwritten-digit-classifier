from PIL import Image
import sys
import os
import random

"""
    Honestly I don't want to use c++ libraries to open files;

    This module is meant to run in the main c++ program;

    you give it a file path and it returns a file with the grayscale data of the picture;

    only 28 x 28; 
"""

filename = "PICTURE_CONVERTER_FILE.txt"
def delete(filepath):
    open(filename,"w").close()

def open_file(filepath):
    print("input file " + filepath+ " ")
    img = Image.open(filepath).convert("LA")

    width,height = img.size

    if width != height and width != 28:
        print("WRONG FILE SIZE")
        return
    
    file = open(filename,"w")
    t = 0
    for i in list(img.getdata()):

        #getting only two digits

        nr = i[0] / 255
        nr *= 2
        nr -= 1
        nr *= 100
        nr //= 1
        nr /= 100

        t+=1



        file.write(str(nr)+" ")

    file.close()

def main():


    filepath = sys.argv[-1] # I know this is ugly but it's 10 pm and I am very tired


    if len(sys.argv) > 2:
        if len(sys.argv) == 3:

            if sys.argv[-2] == "--random" or sys.argv[-2] == "-R":
                try:

                    ls = os.listdir(filepath)
                    open_file(filepath + ls[random.randint(0,len(ls)-1)])
                except:
                    print("ERROR: problem opening the directory")

                

        else:
            print("ERROR: too many arguments ")

    elif len(sys.argv) == 1:
        print("ERROR: few arguments")

    else:
        
        if filepath == "--help" or filepath == "-h":
            print("python module -- opens mnist files and creates a text file:\n\npicture-getter.py [filepath]-opens contents of file and copies them in {"+filename+"}\n--delete or -d to delete the contents of a file\n--remove or -r in order to remove the file-converter file\n--random or -R [directory_path] -picking a random file in directory\n")


        elif filepath == "--delete" or filepath == "-d":
            delete(filepath)

        elif filepath == "--remove" or filepath == "-r":
            os.remove(filename)

        


        else:
            try:
                open_file(filepath)
            except:
                print("Error: couldn't get image")
    
    

if __name__ != "__main__":
    print("file is not meant to be ran as module")
else:
    main()