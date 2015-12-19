/*
 * dictreeWithTest.cpp
 *
 *  Created on: 2015年12月19日
 *      Author: 星尘幻影 
 */
 

#include <stdio.h>
#include <string.h>
#include <vector>

//字典树
struct dictree {
    char c;    //节点字符
    std::vector<dictree*> child;  //子树数组 
    dictree(char ch='$'){c=ch;}    //构造函数，默认为$字符,例如根节点 
};

//构造字典树
void makeDictree(const char**,int);
//在字典树(或子树)的子树节点中寻找是否有某个字符
dictree* dicFind(dictree*, char);
//按照题目意思。判断一个字符串是否能拆分为字典中的单词。
bool fromDict(char*,int);

//某个单词是否在字典内。在本题中不用。
bool inDict(char* str);
//某个单词是否是字典中某个单词的开头。在本题中不用。例如lik是like的开头.完全匹配的也返回true. 
bool matchDict(char* str);

//打印字典树，调试用
void printDict(dictree);
void test(const char**,int,const int,const int);

dictree dic;

int main() {
    const char *dictionary[] = { "i", "like", "sam", "sung", "samsung", "mobile",
            "ice", "cream", "icecream", "hu", "go", "human" };
    //构造字典树
    makeDictree(dictionary,12);

    /* 
     //测试
    printf("%d\n",matchDict("lik"));
    printf("%d\n",matchDict("like"));

    printf("%d\n",inDict("lik"));
    printf("%d\n",inDict("like"));

    printf("%d\n",fromDict("ilik",0));
    printf("%d\n",fromDict("idlik",0));
    printf("%d\n",fromDict("ilike",0));
    */
    
     //随机测试.1000表示1000组,200表示每组数据都由200个随机单词组成. 
    test(dictionary,12,1000,200);
    
    char str[1000];
    scanf("%s",str);
    printf("%s\n",fromDict(str,0)?"yes":"no");
}

void makeDictree(const char** dictionary,int size){
    for (int i = 0; i < size; i++) {
            const char* str = dictionary[i];
            int j = 0;
            dictree* p = &dic;
            while (j < strlen(str)) {
                dictree* p1 = dicFind(p, str[j]);
                if (p1 != NULL) {
                    p = p1;
                } else {
                    dictree* d = new dictree(str[j]);
                    p->child.push_back(d);
                    p = d;
                }
                j++;
                //printDict(dic);
            }
            dictree* d = new dictree(' ');
            p->child.push_back(d);
        }
}

dictree* dicFind(dictree* d, char c) {
    for (int i = 0; i < d->child.size(); i++) {
        dictree* result = (d->child.at(i));
        if (result->c == c) {
            return result;
        }
    }
    return NULL;
}

bool fromDict(char* str,int i){
    dictree* p=&dic;
    if(dicFind(p,str[i])==NULL)return false;
    while(i<strlen(str)){
        p=dicFind(p,str[i]);
        if(p==NULL)return fromDict(str,i);
        i++;
        if(i<strlen(str)&&fromDict(str,i))return true; 
    }
    return dicFind(p,' ');
}

bool matchDict(char* str) {
    int i=0;
    dictree* p=&dic;
    while(i<strlen(str)){
        p = dicFind(p,str[i]);
        if(p==NULL)return false;
        i++;
    }
    return true;
}

bool inDict(char* str) {
    int i=0;
    dictree* p=&dic;
    while(i<strlen(str)){
        p = dicFind(p,str[i]);
        if(p==NULL)return false;
        i++;
    }
    return dicFind(p,' ');
}

void printDict(dictree d) {
    for (int i = 0; i < d.child.size(); i++) {
        printf("%c", d.c);
        printDict(*d.child.at(i));
    }
}

#include <stdlib.h>
#include <time.h>
#include <string>

void test(const char** dictionary,int size,const int n,const int m){
	std::string str[n];
	srand((unsigned int)time(0));
	for(int i=0;i<n;i++){
		str[i]="";
		for(int j=0;j<m;j++){
			str[i]+=dictionary[rand()%size];
		}
	}
	int count=0;
	unsigned int start=(unsigned int)clock();
	for(int i=0;i<n;i++){
		bool b=fromDict((char*)str[i].c_str(),0);
		if(b)count++;
		/*
		printf("%s\n",str[i].c_str());
		if(!b)printf("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
		printf("Pass: %d/%d\n",count,n);
		*/	
	}
	unsigned int end=(unsigned int)clock();
	printf("Pass: %d/%d\nTime(ms): %u\n",count,n,end-start);
	
}
