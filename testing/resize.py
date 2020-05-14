from PIL import Image
import argparse
import random


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('name', nargs='?', default=None, help='name of image file.', type=str)
    parser.add_argument('--height', help='height of new image. must be between 0 and original height. if not chosen then a random value between '
                                         '10 and 90 percent of original height is chosen', default=None, type=int)
    parser.add_argument('--width',
                        help='width of new image. must be between 0 and original width. if not chosen then a random value between '
                             '10 and 90 percent of original width is chosen', default=None, type=int)

    args = parser.parse_args()

    filename = args.name or random.choice(list(filter(lambda x: 'dup' not in x, os.listdir())))
    img = Image.open(filename)
    height = args.height or 0
    width = args.width or 0

    while height <= 0 or width <= 0 or height > img.height or width > img.width:
        height = args.height or random.randint(a=img.height*0.1, b=img.height*0.9)
        width = args.height or random.randint(a=img.width*0.1, b=img.width*0.9)

    img2 = img.resize(size=(width, height))
    img2.save('dup' + img.filename)


if __name__ == '__main__':
    main()
