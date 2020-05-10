#include"deque.h"
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    deque<string> dq;
    while(t--){
        cout<<"1.Insert Back\n2.Insert Front\n3.Pop Back\n4.Pop Front\n5.Return nth element\n6.Resize(with x)\n7.Clear\n8.Size\n"<<endl;
        int choice;
        cin>>choice;
        if(choice == 1){
            string element;
            cin>>element;
            dq.push_back(element);
        }
        else if(choice == 2){
            string element;
            cin>>element;
            dq.push_front(element);
        }
        else if(choice == 3){
            dq.pop_back();
        }
        else if(choice == 4){
            dq.pop_front();
        }
        else if(choice == 6){
            int s;
            cin>>s;
            dq.resize(s);
        }
        else if(choice == 5){
            int index;
            cin>>index;
            cout<<dq[index]<<endl;
        }
        else if(choice == 7){
            dq.clear();
        }
        else if(choice == 8){
            cout<<dq.size()<<endl;
        }
        dq.printdeque();
   }
    return 0;
}
