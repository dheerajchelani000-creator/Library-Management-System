#include<iostream>
#include<vector>
using namespace std;
int count=0,i=0,j,k,st;
vector<bool> book_present;
vector<string> book_name;
vector<int> book_id;
vector<int> reg_no;
bool b;

class book{public:

    
void to_add_book(){
 
cout<<"enter the book name";

cin>>book_name[i];

cout<<"book id";
cin>>book_id[j];

book_present[i]=true;
i++;

}

void to_remove_book(){
  
cout<<"enter the book name";
string bookname;
cin>>bookname;
for( k=0;k<book_name.size();k++){
    if(bookname==book_name[k]){
        b=true;
        break;
    }
}
if(b==true){
book_name.erase(book_name.begin()+k);
book_id.erase(book_id.begin()+k);

}


}



};

class admin{
public:
string book_name;

void issue(){
cout<<"enter your registration number";
cin>>reg_no[j];
cout<<"enter book name";
cin>>book_name[j];
j++;

}

void submit(){

int s;
cin>>s;
for(int l=0;l<reg_no.size();l++){
if(s==reg_no[l]){
reg_no.erase(reg_no.begin() + l);

}

}
}
};

class student{
    public:
string bookName;
void search(){
    cin>>bookName;
    for(st=0;st<book_name.size();st++){
if(bookName==book_name[st]){
    cout<<"book is present";
}
    
}
}
};

int main (){
    int choice;
switch (choice)
{
case 1:
    /* code */
    cout<<"how many book you want to add";
    break;


default:
    break;
}
student s1;
admin a1;
book b1;

}