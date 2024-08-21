#include <stdio.h>
#include <cstring>
#include <algorithm>

int  n,m,t;
int mat[10000+10];
int mat2[10000+10];
// bool tranposed = false;
signed main(void) {
    scanf("%d%d%d",&n,&m,&t);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; j++)
            scanf("%d", &mat[j + i * m]);
    while(t--) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d",&n,&m);
        }
        if(op == 2) {
            int i,j;
            scanf("%d%d",&i,&j);
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; j++)
                    mat2[i+j*n] = mat[j + i*m];
            memcpy(mat, mat2,sizeof mat);
            std::swap(n,m);
        }
        if(op == 3) {
            int i,j;
            scanf("%d%d",&i,&j);
            printf("%d\n", mat[i * m + j]);
        }
    }    
}