#include <unordered_map>
#include <cstdio>
#include <string>
struct data
{
	char s[65];
	void read (void) {
		for( int i=0; i<8; i++)
		{
			scanf("%s", &s[i*8]);
		}
	}
};


signed n;
signed main (void) {
	std::unordered_map<std::string, int> map;
	scanf ("%d", &n);
	for( int i=0; i<n; ++i ) {
		data tmp;
		tmp.read();
		auto s = std::string(tmp.s);
		if ( map.find(s) != map.end() ) {
			map[s]++;
		}
		else {
			map[s] = 1;
		}
		printf("%d\n", map[s]);
	} 
}