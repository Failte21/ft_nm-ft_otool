#! /usr/bin/env python3

import subprocess
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
test_path = os.path.join(dir_path, "custom_tests")

class Base(TestCase):
	def setUp(self):
		self.title = "BASE"
	
	def compare(self, test_files):
		for f in test_files:
			out1 = subprocess.check_output([nm_path, os.path.join(test_path, f)])
			out2 = subprocess.check_output(["nm", os.path.join(test_path, f)])
			self.assertEqual(out1, out2)

	def test_base(self):
		self.compare(["test_facile", "test_moins_facile"])
	
	def test_corrupted(self):
		self.compare(["test_half_obj"])



if __name__ == '__main__':
	ut.main()