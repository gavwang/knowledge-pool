#ifndef  _CHEAP_H_
#define _CHEAP_H_

namespace cth
{
	void HeapAdjust(int array[],int i,int nLength)
	{
		int nChild;
		int nTemp;
		for(;2*i+1<nLength;i=nChild)
		{
			//�ӽ���λ��=2*�������λ�ã�+1
			nChild=2*i+1;
			//�õ��ӽ���нϴ�Ľ��
			if(nChild<nLength-1&&array[nChild+1]>array[nChild])
				++nChild;
			//����ϴ���ӽ����ڸ������ô�ѽϴ���ӽ�������ƶ����滻���ĸ����
			if(array[i]<array[nChild])
			{
				nTemp=array[i];
				array[i]=array[nChild];
				array[nChild]=nTemp;
			}
			else
				//�����˳�ѭ��
				break;
		}
	}

	//�������㷨
	void HeapSort(int array[],int length)
	{
		int tmp;
		//�������е�ǰ�벿��Ԫ�أ�������֮���һ��Ԫ�������е�����Ԫ��
		//length/2-1�����һ����Ҷ�ڵ㣬�˴�"/"Ϊ����
		for(int i=length/2-1;i>=0;--i)
			HeapAdjust(array,i,length);
		//�����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
		for(int i=length-1;i>0;--i)
		{
			//�ѵ�һ��Ԫ�غ͵�ǰ�����һ��Ԫ�ؽ�����
			//��֤��ǰ�����һ��λ�õ�Ԫ�ض��������ڵ��������֮������
			///Swap(&array[0],&array[i]);
			tmp=array[i];
			array[i]=array[0];
			array[0]=tmp;
			//������С����heap�ķ�Χ��ÿһ�ε�����ϱ�֤��һ��Ԫ���ǵ�ǰ���е����ֵ
			HeapAdjust(array,0,i);
		}
	}
}

#endif