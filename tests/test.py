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
		self.files = os.listdir(self.test_path)
	
	def test_fat(self):
		self.compare(["appsleepd", "MachO-OSX-ppc-and-i386-bash", 
			"MachO-iOS-armv7-armv7s-arm64-Helloworld", "fat_hard"])
		# self.compare(self.files)

class LibStat(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests/lib_stat")
		self.files = os.listdir(self.test_path)
	
	def test_lib_stat(self):
		# self.compare(["libft32.a", "lib_long_name.a", "libft_static.a", 
		# "libftprintf.a", "libftprintf32.a", "libmalloc_test.a", "libmlx.a"])
		self.compare(self.files)

class FatLib(Base):
	def setUp(self):
		self.test_path = os.path.join(dir_path, "custom_tests/fat_lib")
		self.files = os.listdir(self.test_path)

	def test_fat_lib(self):
		# self.compare(["PN548_API.dylib", "PN548_HAL_OSX.dylib", "PN548_OSX.dylib",
		# "libAccountPolicyTranslation.dylib", "libFosl_dynamic.dylib", "libarchive.dylib",
		# "libate.dylib", "libblas.dylib", "libc++.1.dylib"])
		self.compare(self.files)

if __name__ == '__main__':
	ut.main()