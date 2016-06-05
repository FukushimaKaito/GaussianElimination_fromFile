/*-----------------------------------------------
課題7　ファイルから読み込んでガウスの消去法で解を求める．

4I31 福嶋開人
2014/11/27
-----------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define M 3
//#define N 4

//文字サイズ
#define KB 1024

/*グローバル変数*/
double **a, *ap;
int M, N;//行数，列数

/*	関数プロトタイプ宣言	*/
void zensin(void);//前進消去
double pibot(int);//ピボット選択
void koutai(void);//後退代入

/*	main関数	*/
int main(void)
{
	//変数を宣言
	char buf[KB];
	FILE *fp;

	//ファイルをおっぷん
	if ((fopen_s(&fp, "C:\\Users\\kaito\\Desktop\\matdata1000w.txt", "r")) != 0){//絶対パスは任意の場所に変更
		printf("ファイルのオープンに失敗しました．\n");
		return 1;//異常終了
	}
	
	//行数を読み込み
	fgets(buf, KB, fp);
	M = atoi(buf);
	//fscanf_s(fp, "%d",M);

	//列数を読み込み
	fgets(buf, KB, fp);
	N = atoi(buf);

	//配列を動的確保
	if ((a = (double **)malloc(sizeof(double *)*M)) == NULL){
		printf("メモリの確保に失敗しました.\n");
		return 1;//異常終了
	}
	if ((ap = (double *)malloc(sizeof(double)*M*N)) == NULL){
		printf("メモリの確保に失敗しました.\n");
		return 1;//異常終了
	}

	//ポインタのポインタに関連付け
	for (int i = 0; i < M; i++)
	{
		a[i] = ap + N*i;
	}
	//配列に値を格納
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fgets(buf, KB, fp);
			a[i][j] = atof(buf);
			//fscanf_s(fp, "%lf", &a[i][j]);
		}
	}

	//ファイルのクローズ
	fclose(fp);

	printf("課題7　ガウスの消去法\n");

	/*printf("元の拡張係数行列です．\n");

	//行列表示
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M + 1; j++)
		{
			printf("%2.3lf	", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");*/

	zensin();//前進消去
	koutai();//後退代入

	printf("ガウスの消去法を適用した答えです．\n");
	for (int i = 0; i < M; i++)
	{
		printf("x[%d] = %lf\n", i, a[i][M]);
	}

	//動的確保の解放
	free(ap);
	free(a);

	return 0;
}

/*		前進消去	*/
void zensin(void)
{
	for (int k = 0; k <= M - 1; k++)
	{
		double p = pibot(k);
		for (int j = k + 1; j <= N - 1; j++){
			a[k][j] = a[k][j] / p;
		}
		for (int i = k + 1; i <= M - 1; i++){
			for (int j = k + 1; j <= N - 1; j++){
				a[i][j] = a[i][j] - a[i][k] * a[k][j];
			}
		}
	}
}

/*		ピボット選択	*/
double pibot(int k)
{
	int l = k;
	double p = a[k][k];
	for (int j = k + 1; j <= M - 1; j++){
		if (fabs(p) < fabs(a[j][k])){
			l = j;
			p = a[j][k];
		}
	}
	if (l != k){
		for (int j = k; j <= N - 1; j++){
			double w = a[k][j];
			a[k][j] = a[l][j];
			a[l][j] = w;
		}
	}
	return(p);
}

/*	後退代入		*/
void koutai(void)
{
	for (int k = M - 2; k >= 0; k--){
		for (int i = k + 1; i <= M - 1; i++){
			a[k][M] = a[k][M] - a[k][i] * a[i][M];
		}
	}
}