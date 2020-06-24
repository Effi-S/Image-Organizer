from PIL import Image
from PIL import ImageEnhance
import argparse
import random
import os


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('name', nargs='?', default=None, help='name of image file.', type=str)
    parser.add_argument('--brightness', help='percent to enhance if not specified a random float between 0.0 and +0.5 is chosen ', default=None, type=float)
    args = parser.parse_args()

    filename = args.name or random.choice(list(filter(lambda x: 'dup' not in x, os.listdir())))
    brightness = args.brightness or random.triangular(0.5, 1.0)

    img = Image.open(filename)
    img2 = ImageEnhance.Brightness(image=img).enhance(factor=brightness)
    name = filename.split('/')
    name[-1] = 'dup' + '_{}_'.format(brightness) + name[-1]
    img2.save('/'.join(name))


if __name__ == '__main__':
    main()
