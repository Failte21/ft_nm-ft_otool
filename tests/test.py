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
nm_path = os.path.join(dir_path, "../ft_nm")
test_path = os.path.join(dir_path, "custom_tests")

def handle_base(test_files, title):
	print(bcolors.HEADER + "----------{}----------".format(title))
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

def handle_corrupted(test_files, title):
	print(bcolors.HEADER + "----------{}----------".format(title))
	for f in test_files:
		print(bcolors.OKBLUE + f)
		try:
			cmnd = [nm_path, os.path.join(test_path, f)]
			out1 = subprocess.check_output(cmnd, stderr=subprocess.STDOUT)
			# output = subprocess.check_output(
			# 	cmnd, , shell=True, timeout=3,
			# 	universal_newlines=True)
		except subprocess.CalledProcessError as exc:
			if exc.output == "An error occured":
				print(bcolors.OKGREEN + "OK")
			else:
				print(bcolors.FAIL + "KO")
		else:
			print(bcolors.FAIL + "KO")


test_files = ["test_facile", "test_moins_facile"]
corrupted_files = ["test_half_obj"]
if __name__ == '__main__':
	handle_base(test_files, "BASE")
	print("\n")
	handle_corrupted(corrupted_files, "BASE CORRUPTED")