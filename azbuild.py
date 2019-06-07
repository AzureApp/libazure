#!/usr/bin/env python3

import configparser
import os

__author__ = "Satori (Razzile) <https://github.com/Razzile>"

config = configparser.ConfigParser()


def main():
    try:
        with open("config.ini") as f:
            config.read_file(f)
    except Exception as e:
        print(
            "No config file found. please make sure there is a valid config.ini at %s\nError: %s"
            % (os.getcwd(), str(e)))
        return 1
    for a, b in config.items():
        for i in b:
            print("{}.{}={}".format(a, i, config[a][i]))


if __name__ == '__main__':
    main()