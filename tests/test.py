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

class Base(TestCase):
	def compare(self, test_files):
		for f in test_files:
			out1 = subprocess.check_output([nm_path, os.path.join(self.test_path, f)])
			out2 = subprocess.check_output(["nm", os.path.join(self.test_path, f)])
			self.assertEqual(out1, out2)

	def compare_multiple(self, test_files, nb):
		for f in test_files:
			fs = [os.path.join(self.test_path, f) for i in range(nb)]
			out1 = subprocess.check_output([nm_path] + fs)
			out2 = subprocess.check_output(["nm"] + fs)
			self.assertEqual(out1, out2)

class Easy(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests")

	def test_easy(self):
		self.compare(["test_facile", "test_moins_facile"])
	
	def test_multiple(self):
		self.compare_multiple(["test_facile", "test_moins_facile"], 2)
		self.compare_multiple(["test_facile", "test_moins_facile"], 3)
		self.compare_multiple(["test_facile", "test_moins_facile"], 4)

class Fat(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests/fat")
	
	def test_fat(self):
		self.compare(["appsleepd", "MachO-OSX-ppc-and-i386-bash"])

if __name__ == '__main__':
	ut.main()