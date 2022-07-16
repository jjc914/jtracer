import os
import argparse

import numpy as np

from PIL import Image

class ArgNotAFileError(Exception):
    pass

def main():
    args = getArgs()
    imageOne = Image.open(args.firstImage)
    imageTwo = Image.open(args.secondImage)
    imageOne = imageOne.convert('RGB')
    imageTwo = imageTwo.convert('RGB')
    imOne = np.asarray(imageOne).astype(np.int16)
    imTwo = np.asarray(imageTwo).astype(np.int16)
    difference = np.absolute(imTwo - imOne)
    difference = difference * 5
    differenceImage = Image.fromarray(difference.astype(np.uint8))
    differenceImage.save('/'.join(args.firstImage.split('/')[:-1]) + '/difference.png')

def getArgs():
    parser = argparse.ArgumentParser(description='Compare two images.')
    parser.add_argument('firstImage', type=checkArgFileValue, help='first image to compare.')
    parser.add_argument('secondImage', type=checkArgFileValue, help='second image to compare.')
    args = parser.parse_args()
    return args

def checkArgFileValue(file):
    if os.path.isfile(file):
        return file
    else:
        raise ArgNotAFileError

main()