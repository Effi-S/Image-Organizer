from PIL import Image
import argparse
import random


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('name', nargs='?', default=None, help='name of image file.', type=str)
    parser.add_argument('--box', help='height of new image. must be between 0 and original height. if not chosen then a random value between'
                                      ' 10 and 90 percent of original height is chosen', default=None, type=int)
    parser.add_argument('--width',
                        help='width of new image. must be between 0 and original width. if not chosen then a random value between '
                             '10 and 90 percent of original width is chosen', default=None, type=int)

    args = parser.parse_args()

    filename = args.name or random.choice(list(filter(lambda x: 'dup' not in x, os.listdir())))
    img = Image.open(filename)

    left = random.randint(a=0, b=img.width/4)
    upper = random.randint(a=0, b=img.height/4)
    right = random.randint(a=img.width*0.75, b=img.width)
    lower = random.randint(a=img.height*0.75, b=img.height)

    box = (left, upper, right, lower)
    img2 = img.crop(box=box)
    img2.save('dup_{}_'.format(box) + img.filename)


if __name__ == '__main__':
    main()
