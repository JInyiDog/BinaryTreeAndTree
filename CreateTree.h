#pragma warning(disable:4996)
#include <iostream>

#ifndef __CREATETREE_H__
#define __CREATETREE_H__
using namespace std;

//����ɭ�֣���˫�ױ�ʾ������㷨--------------------------------------------
#define MAXLEN 100

typedef char elementType;
   //���Ľ��ṹ
typedef struct pNode
{
	elementType data;   //���������
	int parent;         //�����ָ�루�±꣩

}PTNode;

    //˫�ױ�ʾ������ɭ�֣��ṹ
typedef struct pTree
{
	PTNode node[MAXLEN];   //�������
	int n;              //�������
}pTree;

int firstChild(pTree &T,int v)    //�����±�Ϊv�Ľ��ĵ�һ�����ӽ���±�
{
	int w;
	if(v==-1)
		return -1;

	for(w=0;w<T.n;w++)
	{
		if(T.node[w].parent==v)
			return w;
	}
	return -1;
}

//�����ֵ������ʾ���塢�����㷨��ʼ---------------------------------------------------
    //����ɭ�֣��ĺ����ֵ������ʾ
typedef char elementType;

typedef struct csNode
{
	elementType data;
	struct csNode *firstChild, *nextSibling;
}csNode,*csTree;

//ɾ���ַ������ַ�������߿ո�
void strLTrim(char* str)
{
	int i,j;
	int n=0;
	n=strlen(str)+1;
	for(i=0;i<n;i++)
	{
		if(str[i]!=' ')  //�ҵ������һ���ǿո�λ��
			break;
	}
	    //�Ե�һ���ǿո��ַ�Ϊ���ַ��ƶ��ַ���
	for(j=0;j<n;j++)
	{
		str[j]=str[i];
		i++;
	}
}


//****************** �ļ�����˫�ױ�ʾ������ɭ�֣�********************//
//* �������ܣ����ı��ļ�����˫�ױ�ʾ��ͼ                            *//
//* ��ڲ���  char fileName[]�������ļ���                           *//
//* ���ڲ�����pTree &T������������                                  *//
//* �� �� ֵ��bool��true�����ɹ���false����ʧ��                     *//
//* �� �� ����CreateTreeFromFile(char fileName[], pTree &T)         *//
//* ��ע��������ʹ�õ������ļ���ʽ�Աߣ����Ӷԣ�Ϊ��������          *//
//*******************************************************************//
int CreateTreeFromFile(char fileName[], pTree &T)
{
	FILE* pFile;     //����˳�����ļ�ָ��
	char str[1000];  //��Ŷ���һ���ı����ַ���
	char strTemp[10]; //�ж��Ƿ�ע����

    int i=0,j=0;


	pFile=fopen(fileName,"r");
	if(!pFile)
	{
		printf("�����ļ�%s��ʧ�ܡ�\n",fileName);
		return false;
	}
	
	while(fgets(str,1000,pFile)!=NULL)  //�������к�ע����
	{
		//ɾ���ַ�����߿ո�
		strLTrim(str);
		if (str[0]=='\n')  //���У�������ȡ��һ��
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //����ע����
			continue;
		else  //��ע���С��ǿ��У�����ѭ��
			break;
	}

    //ѭ��������str��Ӧ���Ѿ����ļ���ʶ���ж��ļ���ʽ
	if(strstr(str,"Tree or Forest")==NULL)
	{
		printf("���󣺴򿪵��ļ���ʽ����\n");
		fclose(pFile); //�ر��ļ�
		return false;
	}


	//��ȡ������ݣ���str����������
	while(fgets(str,1000,pFile)!=NULL)
	{
		//ɾ���ַ�����߿ո�
		strLTrim(str);
		if (str[0]=='\n')  //���У�������ȡ��һ��
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //ע���У�������������ȡ��һ��
			continue;		
		else  //�ǿ��У�Ҳ��ע���У���ͼ�Ķ���Ԫ����
			break;
	}

	//������ݴ������Ľ������		
	char* token=strtok(str," ");
	int nNum=0;	
	while(token!=NULL)
	{
		T.node[nNum].data=*token;
		T.node[nNum].parent=-1;       //�����ָ���ʼ��Ϊ-1
		
		token = strtok( NULL, " ");
        
		nNum++;
	}
	
    //ѭ����ȡ�ߣ����Ӷӣ�����
	int nP;  //����������±�
	int nC;  //�ӽ�������±�

	elementType Nf,Ns; //���ӽ��Ե��������
	while(fgets(str,1000,pFile)!=NULL)
	{
		//ɾ���ַ�����߿ո�
		strLTrim(str);
		if (str[0]=='\n')  //���У�������ȡ��һ��
			continue;
		
		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //ע���У�������������ȡ��һ��
			continue;

		char* token=strtok(str," ");  //�Կո�Ϊ�ָ������ָ�һ�����ݣ�д���ڽӾ���
		
		if(token==NULL)  //�ָ�Ϊ�մ���ʧ���˳�
		{
			printf("���󣺶�ȡ���ı�����ʧ�ܣ�\n");
			fclose(pFile); //�ر��ļ�
			return false;
		}
		Nf=*token;  //��ȡ�����
		
		token = strtok( NULL, " ");  //��ȡ��һ���Ӵ������ӽ��
		if(token==NULL)  //�ָ�Ϊ�մ���ʧ���˳�
		{
			printf("���󣺶�ȡ���ı�����ʧ�ܣ�\n");
			fclose(pFile); //�ر��ļ�
			return false;
		}

		Ns=*token;  //��ȡ�ߵĵڶ�����㣨�ӽ�㣩
            //ȡ�ø�����±�		
		for(nP=0;nP<nNum;nP++)
		{
			if(T.node[nP].data==Nf)  //�Ӷ����б��ҵ���һ������ı��
				break;
		}
           //��ȡ�ӽ��������±�		
		for(nC=0;nC<nNum;nC++)
		{
			if(T.node[nC].data==Ns)  //�Ӷ����б��ҵ��ڶ�������ı��
				break;
		}

		T.node[nC].parent=nP;        //nC�ĸ������±�ΪnP
	}

    T.n=nNum;  //���Ľ�����������������ʵ�ʴ�С

	fclose(pFile); //�ر��ļ�
	return true;
}

//����˫�ױ�ʾ�У��±�w����һ���ֵܽ�㣬�����ֵܽ����±�
int next(pTree T,int w)  
{
	int i;
	for(i=w+1;i<T.n;i++)
	{
		if(T.node[w].parent==T.node[i].parent)
			return i;	
	}
	return -1;
}

//�ݹ鴴��һ�ú����ֵ������ʾ����
void create(csNode *&T,pTree &T1,int v)
{
	int w;
	T=new csNode;
	T->data=T1.node[v].data;
	T->firstChild=NULL;
	T->nextSibling=NULL;
	w=firstChild(T1,v);  //����v�ĵ�һ�����ӽ��
	if(w!=-1)
	{
		create(T->firstChild,T1,w);
	}
	
	w=next(T1,v);       //����v����һ���ֵܽ��
	if(w!=-1)
	{
		create(T->nextSibling,T1,w);
	}	
}

//��˫�ױ�ʾ������ɭ�֣����������ֵ������ʾ������ɭ�֣�
void createCsTree(csNode *&T,pTree T1)
{
	int i;
	//����T1�ĵ�һ�������
	for(i=0;i<T1.n;i++)
	{
		if(T1.node[i].parent==-1)   //�ҵ���һ�������
			break;		
	}
	if(i<T1.n)
		create(T,T1,i);
}


//�����ֵ������ʾ���塢�����㷨����---------------------------------------------------

void getTreeFileName(char* filename)
{
	while (1)
	{
		cout << "             ___________________________________________________________________________ " << endl;
		cout << "            |                           ��ѡ�������ļ�                                  |" << endl;
		cout << "            |1.F14.tre                                                                  |" << endl;
		cout << "            |2.F16.tre                                                                  |" << endl;
		cout << "            |3.F18.tre                                                                  |" << endl;
		cout << "            |4.F20.tre                                                                  |" << endl;
		cout << "            |5.tree10.tre                                                               |" << endl;
		cout << "            |6.tree11.tre                                                               |" << endl;
		cout << "            |___________________________________________________________________________|" << endl;
		cout << endl;
		cout << "����ѡ��������ļ���";
		int n;
		cin >> n;
		switch (n)
		{
		case 1: { strcpy(filename, "Tdata\\F14.tre"); return; }
		case 2: { strcpy(filename, "Tdata\\F16.tre"); return; }
		case 3: { strcpy(filename, "Tdata\\F18.tre"); return; }
		case 4: { strcpy(filename, "Tdata\\F20.tre"); return; }
		case 5: { strcpy(filename, "Tdata\\tree10.tre"); return; }
		case 6: { strcpy(filename, "Tdata\\tree11.tre"); return; }
		default: { cout << "������Ч" << endl; }
		}
	}
}

int getTreeHeight(csNode* bt)
{
	int lHeight = 1, rHeight = 1;
	if (bt->firstChild != NULL)
		lHeight = getTreeHeight(bt->firstChild) + 1;
	if (bt->nextSibling != NULL)
		rHeight = getTreeHeight(bt->nextSibling);
	return (lHeight >= rHeight) ? lHeight : rHeight;
}

void printCsTree(csNode* bt)
{
	if (bt == NULL)
		return;
	cout << bt->data;
	if (bt->firstChild != NULL)
	{
		cout << "(";
		printCsTree(bt->firstChild);
		cout << ")";
	}
	if (bt->nextSibling != NULL)
	{
		cout << ",";
		printCsTree(bt->nextSibling);
	}
}

void printCsTreeToGT(csNode* bt)
{
	if (bt != NULL)
	{
		cout << bt->data;
		cout << "(";
		printCsTree(bt->firstChild);
		cout << ")";
		if (bt->nextSibling != NULL)
		{
			cout << ",  ";
			printCsTreeToGT(bt->nextSibling);
		}
	}
	else
		return;
}

void treeQuestion(int question)
{
	pTree T;
	csNode* csT;
	char filename[20] = "\0";
	getTreeFileName(filename);
	if (CreateTreeFromFile(filename, T) == true)
	{
		createCsTree(csT, T);
		if (question == 1)
			cout << "����Ϊ��" << getTreeHeight(csT) << endl;;
		if (question == 2)
		{
			cout << "������ʾ������ɭ�֣�Ϊ��";
			printCsTreeToGT(csT);
			cout << endl;	
		}
			
	}
	else
	{
		cout << "��ȡ�ļ���Ϣʱ��������" << endl;
	}
}

#endif
