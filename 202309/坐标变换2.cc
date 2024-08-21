#include<cstdio>
#include<cmath>
double r[100000+10]={1,}, theta[100000+10]={0,};
double x, y, arg; int i, j, id;
int num_ops, num_qrys;
int main(void) {
	scanf("%d%d", &num_ops, &num_qrys);
	for (int i=1; i<=num_ops; ++i) {
		scanf("%d%lf", &id, &arg);
		if(id == 1) {
			r[i] = r[i-1]*arg;
			theta[i] = theta[i-1];  
		}
		else if(id == 2) {
			r[i] = r[i-1];
			theta[i] = theta[i-1]+arg;  
		}else;
	}
	for (int c=0; c<num_qrys; ++c) {
		scanf("%d%d%lf%lf",&i,&j,&x,&y);
		double s = r[j]/r[i-1];
		double t=theta[j]-theta[i-1];
		double nx = s*(x*cos(t)-y*sin(t));
		double ny = s*(x*sin(t)+y*cos(t));
		printf("%lf %lf\n", nx, ny);
	}
	return 0;
}