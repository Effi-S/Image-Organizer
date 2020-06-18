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

    width, height = map(int, (width, height))   # make sure integers

    if height <= 0 or width <= 0 or height > img.height or width > img.width:
        height = random.randint(a=int(img.height*0.1), b=int(img.height*0.9))
        width = random.randint(a=int(img.width*0.1),  b=int(img.width*0.9))

    img2 = img.resize(size=(width, height))
    name = filename.split('/')
    name[-1] = 'dup_{}_{}_'.format(width, height) + name[-1]
    img2.save('/'.join(name))
    

if __name__ == '__main__':
    main()
