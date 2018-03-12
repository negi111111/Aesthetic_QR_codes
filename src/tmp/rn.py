#!/usr/bin/env python
# coding: UTF-8
import sys
import os
import re
import argparse
def main(rename_dir):
    a = 1
    data_dir_path = rename_dir
    files = sorted(os.listdir(rename_dir))
    '''
    print(files)
    for file in files:
        root, ext = os.path.splitext(file)
        abs_name = data_dir_path + '/' + file
        print(abs_name)   
    '''
    for file in files:
        root, ext = os.path.splitext(file)
        if ext == u'.png' or u'.jpeg' or u'.jpg' or u'.bmp' :
            abs_name = data_dir_path + '/' + file
            if ext == u'.png':
                png = re.compile("png")
                if png.search(abs_name):
                    os.rename(abs_name, "%d.png" %(a))
                    a += 1
            elif ext == u'.bmp':
                png = re.compile("bmp")
                if png.search(abs_name):
                    os.rename(abs_name, "%d.jpg" %(a))
                    a += 1
        else:
            pass
  
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='rename path')
    parser.add_argument('--dir', '-i', default='input',
                        help='rename dir')
    args = parser.parse_args()
    main(args.dir)
