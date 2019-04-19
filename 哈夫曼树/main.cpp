#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#define N 10000

using namespace std;

struct node//������������Ľڵ�
{
    int weight;
    int parent;
    int lchild;
    int rchild;
    char c;
};

struct HuffmanCode//�������ڴ洢����������Ľṹ��
{
    char ch;
    string bits;
};

void compress(string passage,string &passage1)//����passage����ַ����ֵ�������
{
    passage1=passage;
    int len=passage1.length(),minx;
    for (int i=0;i<len;i++)
    {
        minx=i;
        for (int j=i+1;j<len;j++)   //ð������
        {
            if (passage1[minx]>passage1[j]) minx=j;
        }
        swap(passage1[i],passage1[minx]);
    }
}

int WeightingSort(node HuffmanT[N],string PassageSort)//��PassageSort�ַ������뵽HuffManT,������weightȨ�أ����ֳɵ����ڵ㣬����ÿ���ڵ��Ȩ��
{
    int len=PassageSort.length();
    int cnt=0;
    HuffmanT[cnt].c=PassageSort[0];
    HuffmanT[cnt].weight++;
    for (int i=1;i<len;i++)
    {
        if (PassageSort[i]==PassageSort[i-1])
            HuffmanT[cnt].weight++;
        else
        {
            cnt++;
            HuffmanT[cnt].c=PassageSort[i];
            HuffmanT[cnt].weight++;
        }
    }
    return cnt+1;//return HuffmanT�ĸ���
}

void initial(node HuffmanT[N])//��ʼ��
{
    for (int i=0;i<N;i++)
    {
        HuffmanT[i].weight=0;
        HuffmanT[i].lchild=-1;
        HuffmanT[i].rchild=-1;
        HuffmanT[i].parent=-1;
    }
}

void selectMin(node HuffmanT[N],int n,int &p1,int &p2)//ѡ��Ȩ����С���������ڵ�ı����Ϊp1,p2
{
    int cnt;
    p1=-1;
    p2=-1;
    for (int i=0;i<n;i++)
    {
        cnt=i;
        if (HuffmanT[i].parent==-1)
        {
            p1=cnt;
            break;
        }
    }
    for (int i=cnt+1;i<n;i++)
    {
        if (HuffmanT[i].parent==-1&&HuffmanT[i].weight<HuffmanT[p1].weight)
        {
            p1=i;
        }
    }
    HuffmanT[p1].parent=-2;
    for (int i=0;i<n;i++)
    {
        cnt=i;
        if (HuffmanT[i].parent==-1)
        {
            p2=cnt;
            break;
        }
    }
    for (int i=cnt+1;i<n;i++)
    {
        if (HuffmanT[i].parent==-1&&HuffmanT[i].weight<HuffmanT[p2].weight)
        {
            p2=i;
        }
    }
}

void creatHT(node HuffmanT[N],int n)//������������
{
    for (int i=n;i<2*n-1;i++)//��Ҫn-1�κϲ�
    {
        int p1,p2;
        selectMin(HuffmanT,i,p1,p2);
        HuffmanT[p1].parent=i;
        HuffmanT[p2].parent=i;
        HuffmanT[i].lchild=p1;
        HuffmanT[i].rchild=p2;
        HuffmanT[i].weight=HuffmanT[p1].weight+HuffmanT[p2].weight;
        HuffmanT[i].parent=-1;
    }
}

void Encode(node HuffmanT[N],int n,HuffmanCode Hcode[N])//��Ҷ�ڵ㿪ʼ�Թ����������б���
{
    for (int i=0;i<n;i++)
    {
        Hcode[i].ch=HuffmanT[i].c;//�����������ڵ���������ڵ����Ը��ƴ������ṹ����
        int m=i;
        while (HuffmanT[m].parent!=-1)//��Ҷ�ڵ����ϱ������������ڵ������ӡ�0����������ҽڵ������ӡ�1��
        {
            int p=HuffmanT[m].parent;
            if (HuffmanT[p].lchild==m) Hcode[i].bits+='0';
            else Hcode[i].bits+='1';
            m=p;
        }
        reverse(Hcode[i].bits.begin(),Hcode[i].bits.end());//���õ��ı����ַ���ת��
    }
}

string Decode(node HuffmanT[N],string secret,int n)//���뺯�������ؽ�����ַ���
{
    int pos=n*2-2;//���ڵ�
    int len=secret.length();
    string DecodePassage;
    for (int i=0;i<len;i++)
    {
        if (secret[i]=='0')//���Ϊ0,������
            pos=HuffmanT[pos].lchild;
        else//���Ϊ1,������
            pos=HuffmanT[pos].rchild;
        if (HuffmanT[pos].lchild==-1)//��Ҷ�ڵ�Ļ�
        {
            DecodePassage+=HuffmanT[pos].c;
            pos=2*n-2;
        }
    }
    return DecodePassage;
}

void menu()//�˵�����
{
   cout<<"1.�ֶ�����Ӣ������"<<endl;
   cout<<"2.���ļ���Ӣ������"<<endl;
   cout<<"3.��������������"<<endl;
   cout<<"4.��Ӣ�����½��б���"<<endl;
   cout<<"5.�Ա����������"<<endl;
  // cout<<"6.����������ļ�"<<endl;
  // cout<<"7.���ļ����������"<<endl;
   cout<<"0.�˳�"<<endl;
}

int main()
{
    node HuffmanT[N];
    HuffmanCode Hcode[N];
    string passage,PassageSort,secret,DecodePassage,passage1;
    char c;
    int n,len;
    int choice;
    while (1)
    {
        menu();
        cin>>choice;
        if (choice==0) break;
        switch (choice)
        {
            case 1:
                cout<<"������Ӣ������,��^�Ž���"<<endl;
                do
                {
                    c=cin.get();
                    if (c=='^')
                        break;
                    passage+=c;
                }while(1);
                break;
            case 2:
                {ifstream file;
                file.open("passage.txt");
                while (!file.eof())
                {
                    c=file.get();
                    passage+=c;
                }
                file.close();
                cout<<"�ļ���ȡ���³ɹ�"<<endl;
                break;}
            case 3:
                cout<<passage<<endl;
                break;
            case 4:
                compress(passage,passage1);//����ĸ�����ֵ���������
                initial(HuffmanT);
                n=WeightingSort(HuffmanT,passage1);//��ÿ���ڵ����ĸ����Ȩ��
                creatHT(HuffmanT,n);//������������
                Encode(HuffmanT,n,Hcode);//����
                for(int i=0;i<n;i++)
                {
                    cout<<Hcode[i].ch<<endl;
                    cout<<Hcode[i].bits<<endl;
                }
                len=passage.length();
                for (int i=0;i<len;i++)
                {
                    for (int j=0;j<n;j++)
                    {
                        if (passage[i]==Hcode[j].ch)
                        {
                            secret+=Hcode[j].bits;
                            break;
                        }
                    }
                }
                cout<<"�����±�������"<<endl;
                cout<<secret<<endl;
                cout<<secret.length()<<endl;
                break;
            case 5:
                cout<<"�Ա����������"<<endl;
                DecodePassage=Decode(HuffmanT,secret,n);
                cout<<DecodePassage<<endl;
                break;
            case 6:
                {
                ofstream fp;
                fp.open("decode.txt");
                /*for(int i=0;i<n;i++){
                fp<<HuffmanT[i].c;
                fp<<HuffmanT[i].lchild;
                fp<<HuffmanT[i].parent;
                fp<<HuffmanT[i].rchild;
                fp<<HuffmanT[i].weight;}*/
                fp<<n;
                fp<<secret;
                fp.close();
                cout<<"����д��ɹ�"<<endl;
                break;
                }
            case 7:
                {
                    //node temp;
                    ifstream file;
                    file.open("decode.txt");
                    file>>n;
                    /*for (int i=0;i<n;i++)
                    {file>>temp.c;
                    file>>temp.lchild;
                    file>>temp.parent;
                    file>>temp.rchild;
                    file>>temp.weight;
                    HuffmanT[i]=temp;
                    }*/
                    file>>secret;
                    file.close();
                    cout<<"�������ɹ�"<<endl;
                    break;
                }

        }
    }
    return 0;
}
