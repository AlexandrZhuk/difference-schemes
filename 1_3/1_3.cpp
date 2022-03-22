
#include<iostream>
#include<vector>
#include<cmath>
#include<cstdlib>


#define TYPE double
#define l 1.
#define eps 0.1
//#define T 0.5//
//#define N 100//x//
//#define M 20//t//


			// u'_t = u''_xx, 0<=x<=l, T>=t>=0
		 	//t=0 -> u=f(x); 0<=x<=l,
			//x=0 -> u=0; T>=t>=0
			//x=l -> u=0; T>=t>=0


TYPE f(TYPE x){
	return -x*x+x;//+ eps*x;
}
//-x^2+x /1


//TYPE u[N][M];
//TYPE **u;

int function1(TYPE sigma, TYPE dx ,TYPE dt, TYPE **u, int N, int M, TYPE T){
	for(int i = 0; i < N; ++i){
		for (int j = 0; j < M; ++j)
		{
			u[i][j]=0;
		}
	}
	TYPE x=0;
	for (int i = 0; i < N; i++)
	{
		u[i][0]=f(x);
		x+=dx;
	}
//	printf("%f\n",u[N-1][M-1] );
//	int s;
//	scanf("%d", &s);
	TYPE r=0;
	TYPE rm=0;
	TYPE rmax;
	//TYPE eps = 0.001;
	//TYPE sigma=1./2 - dx*dx / (12*dt);//1./2;
	for (int n = 0; n < 10000; ++n)
	{
		/* code */
	
	for(int i = 1; i < N-1; i++){
		for (int j = 0; j < M-1; ++j)
		{
			//r = u[i][j+1];
			u[i][j+1] =  (u[i][j]/dt + sigma*(u[i+1][j+1] + u[i-1][j+1])/(dx*dx) + (1-sigma)*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(dx*dx))/(1./dt + 2*sigma/(dx*dx));
			//printf("%f\n", (u[i][j]/dt + sigma*(u[i+1][j+1] + u[i-1][j+1])/(dx*dx) + (1-sigma)*(u[i+1][j]-2*u[i][j]+u[i-1][j])/(dx*dx)) );
			//printf("%f\n", u[i][j+1]);
			//scanf("");
			//r = fabs(r - u[i][j+1]); 
			//if (r > rm) rm = r;
			//printf("%f \n", rm);
		}
		rmax = rm;
	}
	}
	return 0;
}



int createPlot(FILE *file, int pause, char *name, int N, int M, TYPE T, int flagN);
int saveData(FILE *file, char *name, TYPE **u, int N, int M, TYPE T, int flagN);
int drawData(FILE *file, char *name, int iter);
int animationData(TYPE **u, TYPE T, int ITER, TYPE sigma);

int main(){
	int N = 100;
	int M = 20;
	TYPE T = 0.5;
	static TYPE **u;
	TYPE dx = l/(N-1);
	TYPE dt = T/(M-1);
	TYPE sigma = 1./2 - dx*dx / (12.*dt);
	
	animationData(u, T, 10, sigma);


	u = (TYPE **)malloc((N)*sizeof(TYPE*));
		for(int i = 0; i< N;++i){
			u[i] = (TYPE*)malloc((M)*sizeof(TYPE));
		}
	
	function1(sigma, dx, dt, u, N, M, T);//sigma = 1./2 - dx*dx / (12.*dt)
	FILE *fp;
	saveData(fp, "1.txt", u, N, M, T, 1);
	FILE *fp2;
	createPlot(fp2,10000,"1.txt", N, M, T, 1);



	for(int i = 0; i< N;++i){
		free(u[i]);// = (TYPE*)malloc(M*sizeof(TYPE));
	}
	free(u);
	return 0;
}











int createPlot(FILE *file, int pause, char *name, int N, int M, TYPE T, int flagN){
	file = fopen("gnu1.gpi", "w");
	int n;
	char c[80];
	if (flagN){
		n = sprintf(c, "./data/%s.%d.%d.%f.txt",name,N,M,T);}
	else {
		n = sprintf(c, "./data/%s.txt",name);
	}
	//char* s = (char*)malloc(n* sizeof(char));
	//sprintf(s,c,n);
	//file = fopen(s, "w");
	//free(s)
	fprintf(file, "set xlabel \"X\" \n");
	fprintf(file, "set ylabel \"Y\" \n");
	fprintf(file, "set zlabel \"Z\" \n");
	fprintf(file, "set grid \n");
	fprintf(file, "splot '%s' matrix using ($1/((40))):($2/((100))):3 with lines\n", c);
	fprintf(file, "pause %d", pause);
	//free(s);
	//fprintf(fp2, "splot '1.txt' u 1:2:3 w ");
	fclose(file);
	system("gnuplot gnu1.gpi");
	return 0;
}
int saveData(FILE *file, char *name, TYPE **u, int N, int M, TYPE T, int flagN){
	//system("mkdir(\"data\")");
	system("mkdir data");
	int n;
	char c[80];
	if (flagN){
	
	n = sprintf(c, "./data/%s.%d.%d.%f.txt",name, N, M, T);
	//char* s = (char*)malloc(n* sizeof(char));
	//sprintf(s,c,n);
	
	}
	else {
		n = sprintf(c, "./data/%s",name);
	}
	file = fopen(c, "w");
	//free(s);
	for(int i = 0; i < N; ++i){
		for (int j = 0; j < M; ++j)
		{
			fprintf(file, "%f ", u[i][j]);
		}
		fprintf(file, "\n");
		
	}
	fclose(file);

	return 0;
}
int drawData(FILE *file, char *name, int iter){
	//system("mkdir(\"data\")");
	system("mkdir data");

	int n;
	char c[80];
	n = sprintf(c, "./data/%s0.txt", name);
	//char* s = (char*)malloc(n* sizeof(char));($1/$x):($2/$x):3
	//sprintf(s,c,n);
	file = fopen("gnu2.gpi", "w");
	//free(s);
	fprintf(file, "set term gif animate 1 loop 0\n");
	fprintf(file, "set output \"graph.gif\"\n");
	//fprintf(file, "load 'plot_profile.gnu'\n");


	fprintf(file, "set xlabel \"t\" \n");
	fprintf(file, "set ylabel \"x\" \n");
	fprintf(file, "set zlabel \"u\" \n");
	fprintf(file, "set grid \n");
	fprintf(file, "splot '%s' matrix with lines\n", c);
	//fprintf(file, "pause %d", pause);
	fprintf(file, "do for [i=0:%d]{ \n", iter);
	//fprintf(file, "sprintf(\%d )");
	fprintf(file, "splot sprintf('./data/%s%%d.txt', i) matrix using ($1/(2*(i+1))):2:($3/(10*(i+1))) with lines\n", name);
	fprintf(file, "pause %d \n", 1);
	//fprintf(file, "replot \n");
	fprintf(file, "}\n");
	fprintf(file, "pause %d \n", 1);
	
	fprintf(file, "unset output\n");
	//fprintf(file, "set term win\n");
	//fprintf(file, "do for [i=0:%d]{ \n", iter);
	//fprintf(file, "do for [i=0:%d]{ \n", iter);
	fclose(file);
	system("gnuplot gnu2.gpi");

	return 0;
}
int animationData(TYPE **u, TYPE T, int ITER, TYPE sigma){
	
	int N=10;
	int M=2;
	TYPE dx = l/(N-1);
	TYPE dt = T/(M-1);
	FILE *fp;
	FILE *fp2;
	char nameTemp[30];
	for(int n=0; n<ITER; n++){
		u = (TYPE **)malloc((N)*sizeof(TYPE*));
		for(int i = 0; i< N;++i){
			u[i] = (TYPE*)malloc((M)*sizeof(TYPE));
		}
		function1(sigma, dx, dt, u, N, M, T);
		sprintf(nameTemp,"%d.txt", n);
		saveData(fp, nameTemp, u, N, M, T, 0);
		
		for(int i = 0; i< N;++i){
			free(u[i]);
		}
		free(u);
		N+=10;
		M+=3;
		dt = T/(M-1);
		dx = l/(N-1);
	}
	drawData(fp2,"",ITER-1);
	return 0;
}