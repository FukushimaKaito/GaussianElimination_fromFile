/*-----------------------------------------------
�ۑ�7�@�t�@�C������ǂݍ���ŃK�E�X�̏����@�ŉ������߂�D

4I31 �����J�l
2014/11/27
-----------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define M 3
//#define N 4

//�����T�C�Y
#define KB 1024

/*�O���[�o���ϐ�*/
double **a, *ap;
int M, N;//�s���C��

/*	�֐��v���g�^�C�v�錾	*/
void zensin(void);//�O�i����
double pibot(int);//�s�{�b�g�I��
void koutai(void);//��ޑ��

/*	main�֐�	*/
int main(void)
{
	//�ϐ���錾
	char buf[KB];
	FILE *fp;

	//�t�@�C���������Ղ�
	if ((fopen_s(&fp, "C:\\Users\\kaito\\Desktop\\matdata1000w.txt", "r")) != 0){//��΃p�X�͔C�ӂ̏ꏊ�ɕύX
		printf("�t�@�C���̃I�[�v���Ɏ��s���܂����D\n");
		return 1;//�ُ�I��
	}
	
	//�s����ǂݍ���
	fgets(buf, KB, fp);
	M = atoi(buf);
	//fscanf_s(fp, "%d",M);

	//�񐔂�ǂݍ���
	fgets(buf, KB, fp);
	N = atoi(buf);

	//�z��𓮓I�m��
	if ((a = (double **)malloc(sizeof(double *)*M)) == NULL){
		printf("�������̊m�ۂɎ��s���܂���.\n");
		return 1;//�ُ�I��
	}
	if ((ap = (double *)malloc(sizeof(double)*M*N)) == NULL){
		printf("�������̊m�ۂɎ��s���܂���.\n");
		return 1;//�ُ�I��
	}

	//�|�C���^�̃|�C���^�Ɋ֘A�t��
	for (int i = 0; i < M; i++)
	{
		a[i] = ap + N*i;
	}
	//�z��ɒl���i�[
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fgets(buf, KB, fp);
			a[i][j] = atof(buf);
			//fscanf_s(fp, "%lf", &a[i][j]);
		}
	}

	//�t�@�C���̃N���[�Y
	fclose(fp);

	printf("�ۑ�7�@�K�E�X�̏����@\n");

	/*printf("���̊g���W���s��ł��D\n");

	//�s��\��
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M + 1; j++)
		{
			printf("%2.3lf	", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");*/

	zensin();//�O�i����
	koutai();//��ޑ��

	printf("�K�E�X�̏����@��K�p���������ł��D\n");
	for (int i = 0; i < M; i++)
	{
		printf("x[%d] = %lf\n", i, a[i][M]);
	}

	//���I�m�ۂ̉��
	free(ap);
	free(a);

	return 0;
}

/*		�O�i����	*/
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

/*		�s�{�b�g�I��	*/
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

/*	��ޑ��		*/
void koutai(void)
{
	for (int k = M - 2; k >= 0; k--){
		for (int i = k + 1; i <= M - 1; i++){
			a[k][M] = a[k][M] - a[k][i] * a[i][M];
		}
	}
}