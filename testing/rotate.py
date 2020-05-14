from PIL import Image
import argparse
import random


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('name', nargs='?', default=None, help='name of image file.', type=str)
    parser.add_argument('--angle', help='angle to rotate image if not entered a random angle is chosen between 1 and 359', default=None, type=int)
    args = parser.parse_args()

    angle = args.angle or random.randint(a=1, b=359)
    filename = args.name or random.choice(list(filter(lambda x: 'dup' not in x, os.listdir())))
    img = Image.open(filename)
    img2 = img.rotate(angle=angle, expand=True)
    img2.save('dup' + img.filename)


if __name__ == '__main__':
    main()
