# This is a blank test. Does nothing.
# For seeing how many false positives.
import argparse
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='This is a blank test. Used for false positives.')
    parser.add_argument('name', nargs='?', default=None, help='name of image file'
                                                              '(all tests must have this).', type=str)
    args = parser.parse_args()
