import os
import argparse

import numpy as np

from PIL import Image

class ArgNotAFileError(Exception):
    pass

def main():
    args = getArgs()
    image = Image.open(args.image)
    image = image.convert('RGB')
    im = np.asarray(image).astype(np.int16)
    im = 255 - im;
    differenceImage = Image.fromarray(im.astype(np.uint8))
    differenceImage.save('/'.join(args.image.split('/')[:-1]) + '/invert.png')

def getArgs():
    parser = argparse.ArgumentParser(description='Invert an image.')
    parser.add_argument('image', type=checkArgFileValue, help='image to invert.')
    args = parser.parse_args()
    return args

def checkArgFileValue(file):
    if os.path.isfile(file):
        return file
    else:
        raise ArgNotAFileError

main()
