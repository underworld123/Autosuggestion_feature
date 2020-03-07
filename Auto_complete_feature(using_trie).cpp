#include<bits/stdc++.h>
#include <fstream>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize ("-ffloat-store") // to restrict undesirable precision
#pragma GCC optimize ("-fno-defer-pop")// to pop argument of function as soon as it returns
#define ll long long int
#define all(a) a.begin(),a.end()
#define N 3000005
#define endl "\n"
#define words_to_display 10
string tolowercs(string a){
	string s;
	ll i,n=a.length();
	for(i=0;i<n;i++){
		if(a[i]<'a') s[i]=a[i]+32;
		else s[i]=a[i];
	}
	return s;
}
//print top k (default 10) suggestions for a given word.
struct tnode{
	bool iswordend; ll count_hits;
	struct tnode* children[26];
};
struct tnode* root;
struct tnode* newnode(){
	struct tnode* nd = new tnode;
	nd->iswordend=false; nd->count_hits=0;
	for(ll i=0;i<26;i++){
		nd->children[i]=NULL;
	}
	return nd;
}
//If key is not present, inserts key into trie.  
//If the key is prefix of trie node, just marks leaf node 
void insert(const string key){
	struct tnode* tmp=root;
	for(ll i=0;i<key.length();i++){
		ll k=key[i]-'a';
		if(tmp->children[k]==NULL){
			tmp->children[k]=newnode();
		}
		tmp=tmp->children[k];
	}
	tmp->iswordend=true;
}
//returns true if key presents in trie, else false
//update the hits count of that word
bool search_word(const string key){
	struct tnode* tmp=root;
	for(ll i=0;i<key.length();i++){
		ll k=key[i]-'a';
		if(tmp->children[k]==NULL){
			return false;
		}
		tmp=tmp->children[k];
	}
	if(tmp!=NULL&&tmp->iswordend){
		tmp->count_hits++;
		return true;
	}
	else return false;
}
vector< pair<ll,string> > found_words;
void suggest_words(struct tnode* tmp,string cur_str){
	if(tmp->iswordend){
		found_words.push_back({tmp->count_hits,cur_str});
	}
	for(ll i=0;i<26;i++){
		if(tmp->children[i]!=NULL){
			cur_str.push_back(('a'+i));
			suggest_words(tmp->children[i],cur_str);
			cur_str.pop_back();
		}
	}
}
ll autosuggestions(const string query){
	struct tnode* tmp=root;
	for(ll i=0;i<query.length();i++){
		ll k=query[i]-'a';
		// no string in the Trie has this prefix 
		if(tmp->children[k]==NULL) return 0;
		tmp=tmp->children[k];
	}

	string cur_str=query;
	suggest_words(tmp,cur_str);
	return 1;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	root=newnode();	
	ifstream inFile;
	inFile.open("words.txt");
	if (!inFile) {
	    cerr << "Unable to open file datafile.txt";
	    exit(1);   // call system to stop
	}

	string x;
	while(inFile>>x){
		insert(x);
	}
	inFile.close();

	cout<<"Enter words to search or 0 to exit"<<endl;
	while(true){
		string str;
		cin>>str;
		if(str=="0") break;
		bool an=search_word(str);
		if(an) cout<<"present"<<endl;
		else cout<<"not present"<<endl;
	}cout<<endl;

	found_words.clear();
	ll an=autosuggestions("th");
	sort(all(found_words));
	reverse(all(found_words));
	//show only top 10 words with maximum hit count.
	for(ll i=0;i<words_to_display;i++){
		cout<<found_words[i].second<<endl;
	}
	if(an==0){
		cout<<"No string found with this prefix\n";
	}
	return 0;
}