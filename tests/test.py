import subprocess
import os

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
nm_path = os.path.join(dir_path, "../ft_nm/ft_nm")
test_path = os.path.join(dir_path, "custom_tests")

test_files = ["test_facile", "test_moins_facile", "test_half_obj"]
if __name__ == '__main__':
	# print(out1)
	# print(out2)
	print(bcolors.HEADER + "----------BASE TESTS----------")
	for f in test_files:
		print(bcolors.OKBLUE + f)
		out1 = subprocess.check_output([nm_path, os.path.join(test_path, f)])
		out2 = subprocess.check_output(["nm", os.path.join(test_path, f)])
		if out1 == out2:
			print(bcolors.OKGREEN + "OK")
		else:
			print(bcolors.FAIL + "KO")
			print(bcolors.WARNING + "ft_nm:")
			print(out1)
			print("nm:")
			print(out2)