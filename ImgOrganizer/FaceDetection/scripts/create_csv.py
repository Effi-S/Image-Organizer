#!/usr/bin/env python
# Use this script from ImageOrganizer as such:
#       python FaceDetection/create_csv.py FaceDetection/faces > FaceDetection/training_data.csv
#
import sys
import os.path
import ctypes
from pathlib import Path


def c_str(s):
    return ctypes.c_wchar_p(s.encode('utf-8')).replace('c_wchar_p(', '').replace(')', '')


if __name__ == "__main__":

    if len(sys.argv) != 3:
        print("usage: <directory-to-search> <output-csv-file> "
              "\n Example: python FaceDetection/create_csv.py FaceDetection/faces FaceDetection/training_data.csv")
        sys.exit(1)

    BASE_PATH = sys.argv[1]
    CSV_PATH = sys.argv[2]
    SEPARATOR = ";"
    csv_file = open(CSV_PATH, 'wb+')
    for _, dirs, __ in os.walk(BASE_PATH):
        for dir in dirs:
            for filename in os.listdir(BASE_PATH + '/' + dir):
                path = str(Path(BASE_PATH, dir, filename).as_posix())
                line = '{}{}{}\n'.format(path, SEPARATOR, dir)
                csv_file.write(line.encode())

        break
