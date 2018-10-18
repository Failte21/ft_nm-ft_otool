import subprocess
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
nm_path = os.path.join(dir_path, "../ft_nm/ft_nm")
test_path = os.path.join(dir_path, "custom_tests")

if __name__ == '__main__':
	out1 = subprocess.check_output([nm_path, os.path.join(test_path, "test_facile")])
	print(out1)