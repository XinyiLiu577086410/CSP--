#include <stdio.h>
int n,m,p,q;
int mat[100000];
signed main(void) {
    scanf("%d%d%d%d",&n,&m,&p,&q);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; j++)
            scanf("%d", &mat[j + i * m]);
    for(int i = 0; i < p; ++i){
        for(int j = 0; j < q; j++){
            printf("%d", mat[j + i * q]);
            if(j + 1 != q) printf(" ");
        }
        printf("\n");
    }
}
