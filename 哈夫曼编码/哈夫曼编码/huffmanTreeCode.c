#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double DataType; //���Ȩֵ����������

typedef struct HTNode //����������Ϣ
{
	DataType weight; //Ȩֵ
	int parent; //���ڵ�
	int lc, rc; //���Һ���
}*HuffmanTree;

typedef char** HuffmanCode; //�ַ�ָ�������д洢��Ԫ������

//���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩֵ��С������ֵ���±꣬����s1��ȨֵС��s2��Ȩֵ
void Select(HuffmanTree HT, int n, int* s1, int* s2)
{
	int min=0;
	int arr[2] = { '\0' };
	//�ҵ�һ����Сֵ
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight)
			min = i;
	}
	*s1 = min; //��һ����Сֵ��s1
	arr[0] = s1;
	//�ҵڶ�����Сֵ
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && i != s1)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < HT[min].weight && i != s1)
			min = i;
	}
	*s2 = min; //�ڶ�����Сֵ��s2
	arr[1] = s2;
}

//������������
void CreateHuff(HuffmanTree HT, DataType* w, int n)
{
	int m = 2 * n - 1; //���������ܽ����
	HT = (HuffmanTree*)malloc(m + 1*sizeof(HuffmanTree)); //��m+1��HTNode����Ϊ�±�Ϊ0��HTNode���洢����
	int* p =NULL;
	p = (int*)malloc(2 * sizeof(int));
	w = NULL;
	w=(DataType*)malloc(n * sizeof(DataType*));
	for (int i = 1; i <= n; i++)
	{
		HT[i].weight = w[i - 1]; //��Ȩֵ��n��Ҷ�ӽ��
	}
	for (int i = n + 1; i <= m; i++) //������������
	{
		//ѡ��Ȩֵ��С��s1��s2���������ǵĸ����
		int s1 = NULL;
		int s2 = NULL;
		Select(HT, i - 1, &s1, &s2); //���±�Ϊ1��i-1�ķ�Χ�ҵ�Ȩֵ��С������ֵ���±꣬����s1��ȨֵС��s2��Ȩֵ
		HT[i].weight = HT[s1].weight + HT[s2].weight; //i��Ȩ����s1��s2��Ȩ��֮��
		HT[s1].parent = i; //s1�ĸ�����i
		HT[s2].parent = i; //s2�ĸ�����i
		HT[i].lc = s1; //������s1
		HT[i].rc = s2; //�Һ�����s2
	}
	//��ӡ���������и����֮��Ĺ�ϵ
	printf("��������Ϊ:>\n");
	printf("�±�   Ȩֵ     �����   ����   �Һ���\n");
	printf("0                                  \n");
	for (int i = 1; i <= m; i++)
	{
		printf("%-4d   %-6.2lf   %-6d   %-6d   %-6d\n", i, HT[i].weight, HT[i].parent, HT[i].lc, HT[i].rc);
	}
	printf("\n");
}

//���ɹ���������
void HuffCoding(HuffmanTree HT, HuffmanCode HC, int n)
{
	HC = (HuffmanCode)malloc(sizeof(char*) * (n + 1)); //��n+1���ռ䣬��Ϊ�±�Ϊ0�Ŀռ䲻��
	char* code = (char*)malloc(sizeof(char) * n); //�����ռ䣬�����Ϊn(�ʱ��ǰn-1�����ڴ洢���ݣ����1�����ڴ��'\0')
	HT = (HuffmanTree*)malloc(5 * sizeof(HuffmanTree));
	code[n - 1] = '\0'; //�����ռ����һ��λ��Ϊ'\0'
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1; //ÿ���������ݵĹ���������֮ǰ���Ƚ�startָ��ָ��'\0'
		int c = i; //���ڽ��еĵ�i�����ݵı���
		int p = 0; 
		p = HT[c].parent; //�ҵ������ݵĸ����
		while (p) //ֱ�������Ϊ0���������Ϊ�����ʱ��ֹͣ
		{
			if (HT[p].lc == c) //����ý�����丸�������ӣ������Ϊ0������Ϊ1
				code[--start] = '0';
			else
				code[--start] = '1';
			c = p; //�������Ͻ��б���
			p = HT[c].parent; //c�ĸ����
		}
		HC[i] = (char*)malloc(sizeof(char) * (n - start)); //�������ڴ洢������ڴ�ռ�
		strcpy(HC[i], &code[start]); //�����뿽�����ַ�ָ�������е���Ӧλ��
	}
	free(code); //�ͷŸ����ռ�
}

//������
int main()
{
	int n = 0;
	printf("���������ݸ���:>");
	scanf("%d", &n);
	DataType* w = w = (DataType*)malloc(sizeof(DataType));
	if (w == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	printf("����������:>");
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &w[i]);
	}
	HuffmanTree HT=NULL;
	CreateHuff(HT, &w, n); //������������

	HuffmanCode HC=NULL;
	HuffCoding(HT, HC, n); //��������������

	for (int i = 1; i <= n; i++) //��ӡ����������
	{
		printf("����%.2lf�ı���Ϊ:%s\n", HT[i].weight, HC[i]);
	}
	free(w);
	return 0;
}
