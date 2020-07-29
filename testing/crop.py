from PIL import Image
import argparse
import random


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('name', nargs='?', default=None, help='name of image file.', type=str)
    parser.add_argument('--box', help=' 4 consecutive floats separated by \',\'.\n '
                                      'representing left, upper, right, lower.\n'
                                      ' Example: \'10, 40, 300, 200\'\n '
                                      'Make sure the cropped image is within the margins specified  ', default=None, type=str)
    parser.add_argument('--margin', help='percent of margin to leave on all sides when auto running.', default=0.1, type=float)

    args = parser.parse_args()

    filename = args.name or random.choice(list(filter(lambda x: 'dup' not in x, os.listdir())))
    img = Image.open(filename)

    margin = args.margin
    left = random.randint(a=0, b=int(img.width*margin))
    upper = random.randint(a=0, b=int(img.height*margin))
    right = random.randint(a=int(img.width*(1-margin)), b=int(img.width))
    lower = random.randint(a=int(img.height*(1-margin)), b=int(img.height))

    if args.box:
        left, upper, right, lower = map(float, args.box.split(','))
        assert left < img.width*margin and upper < img.height*margin and right < img.width*(1-margin) and lower < img.height*(1-margin), 'Not within margin borders'

    box = (left, upper, right, lower)
    img2 = img.crop(box=box)
    name = filename.split('/')
    percent_left = (img2.width * img2.height) / (img.width * img.height)
    percent_left = round(percent_left, 1)
    name[-1] = 'dup_{}_'.format(percent_left) + name[-1]
    img2.save('/'.join(name))


if __name__ == '__main__':
    main()
