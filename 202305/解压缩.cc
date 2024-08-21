#include <cstdio>
#include <cstring>
#include <algorithm>
unsigned char is[(size_t)2e6+10];
unsigned char os[(size_t)2*1024*1024+10];
int s;
char c;
int oringlen = 0; // origin data

unsigned char eval(char c) {
	if(c >= '0' && c <= '9') {
		return c - '0';
	}
	else if(c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	}
	else
		throw 1;
}

signed main (void) {
	scanf ("%d", &s);
	for(int i=0; i<s; ++i) {
		if(i % 8 == 0) 
			getchar();
		is[i] = eval(getchar()) * 16;
		is[i] += eval(getchar());
	}


	#ifdef DBG
	for(int i=0; i<s; ++i) {
		if(i % 8 == 0)
			printf("\n");
		printf("%02x", is[i]);
		
	}
	#endif

	int oscur = 0;
	int iscur = 0;
	int mul = 1;
	do {
		oringlen += (0b01111111 & is[iscur]) * mul;
		mul *= 128;
	} while (is[iscur++] >= 128);

	while (iscur < s)
	{
		if(is[iscur] & 0b00000011){
			unsigned short o = 0;
			unsigned char l = 0;
			if(is[iscur] & 0b00000001) {
			/**
			 *
			 * 当元素首字节的最低两位是 01 时，表示这是一个回溯引<o, l>，且 l in [4, 11], o in (0, 2047]。
			 * 此时，o 占 11 位，其低 8 位存储于随后的字节中，高 3 位存储于首字节的高 3 位中。 
			 * (l-4) 占 3 位，存储于首字节的 2 至 4 位中。如下图所示：
			 * 
			 *  7 6 5 4 3 2 1 0   7 6 5 4 3 2 1 0
			 * +-----+-----+-+-+ +----------------+
			 * |o(h3)| l-4 |0|1| |o (lower 8 bits)|
			 * +-----+-----+-+-+ +----------------+
			 * 
			*/
				o |= ((unsigned short) (is[iscur] >> 5)) << 8;
				l = ((is[iscur] & 0b00011100) >> 2) + 4; 
				o |= (unsigned short) (is[iscur+1]);	
				iscur += 2;
			}
			else if(is[iscur] & 0b00000010) {
			/**
			 * 
			 * 当元素首字节的最低两位是 10 时，表示这是一个回溯引用<o, l>，且l in [1, 64], o in (0, 65535]。
			 * 此时，o 占 16 位，以小端序存储于随后的两个字节中。
			 * (l-1) 占 6 位，存储于首字节的高 6 位中。
			 * 
			*/
				o = (unsigned short) is[iscur + 1] \
									| ((unsigned short) is[iscur + 2]) << 8;
				l = (is[iscur] >> 2) + 1;
				iscur += 3;
			}
			unsigned char * where = &os[oscur - o];

			if ((o >= l)) {
				memcpy(&os[oscur], where, l);	
			}
			else {
				for ( int i = 0; i < (l+o-1)/o; ++i ) {
					memcpy(&os[oscur+i*o], where, o);
				}
			}
			oscur += l;			
		}
		else {
			unsigned l = 0;
			if((is[iscur] >> 2) < 60) {
				l = (is[iscur] >> 2) + 1U;
			}
			else {
				unsigned int cnt = (is[iscur] >> 2) - 59;
				int k = 0;
				while (cnt--){
					l |= ( (unsigned int) is[++iscur] ) << ( k * 8 );
					++k;
				}
				l += 1;
			}
			++iscur;
			memcpy(&os[oscur], &is[iscur], l);
			oscur += l;
			iscur += l;
		}
	}

	for(int i=0; i<oscur; ++i) {
		if(i % 8 == 0 && i) // WA, 0
			printf("\n");
		printf("%02x", os[i]);
	}

}

/**
 * AC, Fri Feb 16, 14:06
*/