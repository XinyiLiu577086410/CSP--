#include <cstdio>
#include <cstdlib>
#include <fstream>
#define endl '\n'
#define mod 998244353
int main(int argc, char ** argv) {
	int m, n;
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	std::ofstream of;
	of.open("treasure.in");
	of << n << ' ' << m << endl;
	for(int i=0; i<n; ++i) {
		int j = rand() % 3 + 1;
		of << j << ' ';
		switch (j)
		{
		case 1: case 2:
			for(int k=0; k<4; ++k)
				of << rand() % mod << (k == 3 ? '\n' : ' ');
			break;
		case 3:
			of << endl;
			break;
		default:
			break;
		}
	}
	for(int i=0; i<m; ++i)  {
		int j = rand() % 2 + 1;
		of << j << ' ';
		switch (j)
		{
		case 1:
			{
				int s = rand() % n + 1;
				of << s << ' ';
				int k = rand() % 3 + 1;
				of << k << ' ';
				switch (k)
				{
				case 1: case 2:
					for(int l=0; l<4; ++l)
						of << rand() % mod << (l == 3 ? '\n' : ' ');
					break;
				case 3:
					of << endl;
					break;
				default:
					break;
				}
			}
			break;
		case 2:{
				int s = rand() % n + 1;
				int len = rand() % (n - s + 1);
				of << s << ' ' << s + len << endl;
				break;
			}
		default:
			break;
		}
	}

}