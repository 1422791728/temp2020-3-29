#include <iostream>
using namespace std;
class Node
{
public:
	int id;
	Node* next;//ָ����
};
class Linklist
{
public:
	Node* next;
	int length;
	Linklist()
	{
		next = NULL;
		length = 0;
	}
};
void Insert(Linklist* list, int pos, int Num);
void Init(Linklist* list, int* num, int length)
{
	list->next = NULL;
	for (int i = 0; i < length; i++)
	{
		Insert(list, i + 1, num[i]);
	}
}
void Insert(Linklist* list, int pos, int Num)
{
	Node* ptr_node = new Node;
	ptr_node->id = Num;
	ptr_node->next = NULL;
	if (pos == 1)
	{
		ptr_node->next = list->next;
		list->next = ptr_node;
		list->length++;
		return;
	}

	Node* curr = list->next;
	for (int i = 1; (curr != NULL) && i < pos - 1; i++)
	{
		curr = curr->next;
	}

	if (curr != NULL)//�ж��Ƿ�Ҫ�����λ���е�ǰһ��Ԫ�ش��� ��֤�����������
	{
		ptr_node->next = curr->next;
		curr->next = ptr_node;
		list->length++;
		//Ϊ�˺������������pos == list-> �������Բ���
		//if (pos == list->length)//��β�ڵ��Nextָ��Ϊ��
		//{
		//	ptr_node = NULL;
		//}
	}
}
void Show(Linklist* list)
{
	Node* newNode = list->next;
	for (int i = 0; i < list->length; i++)
	{
		cout << newNode->id << endl;
		newNode = newNode->next;
	}
}
int Delete(Linklist* list, int pos)
{
	Node* node = list->next;
	int num;
	num = -999;
	if (pos == 1)
	{
		if (node != NULL)
		{
			num = node->id;
			list->next = node->next;
			delete node;
			list->length--;
		}
		return num;
	}
	Node* prenode = NULL;
	for (int i = 1; node && i < pos; i++)
	{
		prenode = node;
		node = node->next;
	}
	if (node != NULL)
	{
		prenode->next = node->next;
		num = node->id;
		delete node;
		list->length--;
	}
	return num;
}
void Clear(Linklist* list)
{
	Node* node = NULL;
	Node* nextnode = NULL;
	node = list->next;
	while (node != NULL)
	{
		nextnode = node->next;
		cout << node->id << endl;
		delete node;
		node = nextnode;
	}
	list->length = 0;
	list->next = NULL;
}
int Find(Linklist* list, int pos)
{//
	Node* node = list->next;
	for (int i = 1; (node != NULL) && i < pos; i++)
	{
		node = node->next;

	}
	return node->id;
}
Node  Get(Linklist* list, int pos)
{
	Node* node = list->next;
	for (int i = 1; (node != NULL) && i < pos; i++)
	{
		node = node->next;
	}
	return *node;
}
//��������
//range���� ��Χ 0 ~ range Ҳ�����Ӹ���
void BinSort(Linklist* list, int range)
{
	int length = list->length;
	Linklist* bin = new Linklist[range + 1];//����range + 1������
	for (int i = 1; i <= length; i++)
	{
		Node node = Get(list, 1);//��ȡ��һ�����
		Delete(list, 1);//ɾ����һ�����
		Insert(&bin[node.id], 1, node.id);//�ѻ�ȡ�ĵ�һ�������뵽�����е�
	}
	for (int i = range; i >= 0; i--)
	{
		while (bin[i].next != NULL)
		{			
			Node node = Get(&bin[i], 1);
			Delete(&bin[i], 1);
			Insert(list, 1, node.id);
		}
	}
	delete[]bin;
}

//��������
//range�����ӵķ�Χ 0 ~range rangeҲ�ǻ���
//maxlength ��������ֳ���Ҳ����Ҫ������ܴ���
void BaseSort_LSD(Linklist* list,int range,int maxlength)
{
	int length = list->length;
	Linklist* bin = new Linklist[range + 1];
	for (int i = maxlength - 1; i >= 0; i--)
	{
		for (int j = 1; j <= length; j++)
		{
			Node node = Get(list, 1);
			Delete(list, 1);
			int index = node.id % (range + 1);
			Insert(&bin[index], 1, node.id);
		}
		for (int k = range; k >= 0; k--)
		{
			while (bin[k].next != NULL)
			{			
				Node node = Get(&bin[k], 1);
				Delete(&bin[k], 1);
				Insert(list, 1, node.id);
			}
		}
		
	}
	delete[]bin;
}
//int main()
//{
//	Linklist list;
//	int num[] = {2,4,5,4,3,0,4,3,4,4};
//	Init(&list, num, 10);
//	//cout << list.length << endl;
//	/*int NUM = 2222;
//	Insert(&list, 3, NUM);
//	Show(&list);
//	Delete(&list, 3);
//	Show(&list);
//	Clear(&list);
//	Show(&list);*/
//	//BinSort(&list, 5);
//	BaseSort_LSD(&list,5,1);
//	Show(&list);
//}