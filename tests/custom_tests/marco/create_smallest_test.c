#include <unistd.h>

int main() {
	int har = 0xFEEDFACE;
	char a[4];
	a[0] = har & 0xff;
	a[1] = (har>>8)  & 0xff;
	a[2] = (har>>16) & 0xff;
	a[3] = (har>>24) & 0xff;
	write(1, a, 4);
}
