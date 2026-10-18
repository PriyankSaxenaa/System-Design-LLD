#include<bits/stdc++.h>
using namespace std;
class TrieNode{
    public:
    char data;
    TrieNode* childrens[26];
    bool isterminal;

    TrieNode(char c){
        data=c;
        for(int i=0;i<26;i++){
            childrens[i]=nullptr;
        }
        isterminal=false;
    }
};
class Trie{
    public:
    TrieNode* root;
    Trie(){
        root=new TrieNode('\0');
    }
    void insertutil(string word,TrieNode* root){
        if(word.size()==0){
            root->isterminal=true;
            cout<<"WORD INSERTED SUCCESSFULLY\n";
            return;
        }
        //assume word is in caps
        int idx=word[0]-'A';
        //present
        TrieNode* child;
        if(root->childrens[idx]!=nullptr){
            child=root->childrens[idx];
        }
        //absent
        else{
            child=new TrieNode(word[0]);
            root->childrens[idx]=child;
        }

        insertutil(word.substr(1),child);
    }   
    void insert(string word){
        insertutil(word,root);
    }
    bool searchutil(string word,TrieNode* root){
        if(word.size()==0)
        return root->isterminal;
        
        int idx=word[0]-'A';
        if(root->childrens[idx]!=nullptr){
            TrieNode* child=root->childrens[idx];
            return searchutil(word.substr(1),child);
        }
        else
        return false;
    }
    void serach(string word){
        bool ans=searchutil(word,root);

        if(ans)
        cout<<"true\n";
        else
        cout<<"NO\n";
    }
};
int main(){
    Trie* t=new Trie();
    t->insert("ABCD");
    t->serach("ABC");
    t->serach("ABCD");
    
    t->serach("ABCDE");
}   