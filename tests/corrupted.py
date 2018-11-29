#! /usr/bin/env python3

import subprocess
from subprocess import Popen, PIPE
import os
from unittest import TestCase
import unittest as ut

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

dir_path = os.path.dirname(os.path.realpath(__file__))
nm_path = os.path.join(dir_path, "../ft_nm")

def test_corrupted(test_path, test_files):
    for f in test_files:
        print(bcolors.OKBLUE + f)
        try:
            cmnd = [nm_path, os.path.join(test_path, f)]
            out = subprocess.check_output(cmnd, stderr=subprocess.STDOUT, universal_newlines=True)
        except subprocess.CalledProcessError as exc:
            if exc.output == "An error occured\n":
                print(bcolors.OKGREEN + "OK")
            else:
                print(bcolors.FAIL + "KO")
        else:
            print(bcolors.FAIL + "KO")

if __name__ == '__main__':
	test_corrupted(os.path.join(dir_path, "custom_tests"), ['test_half_obj'])
	harder = ['32_exe_hard_corupted', 'curl_truncated_load']
	test_corrupted(os.path.join(dir_path, "custom_tests/corrupt"), harder)