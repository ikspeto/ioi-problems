#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class node
{
public:
    node *children[26];
    string suffix;
    bool is_word;
    node()
    {
        this->is_word = false;
        this->suffix = "";
        for(int i=0;i<26;i++)
            children[i] = NULL;
    }

};

vector<pair<int, string> > operations;

void add_word(node *head, string word)
{
    for(int i=0;i<word.size();i++)
    {
        if(head->children[word[i]-'a'] == NULL)
        {
            head->children[word[i]-'a'] = new node();
            head = head->children[word[i]-'a'];
            head->suffix = word.substr(i+1);
            head->is_word = true;
            break;
        } else {
            head = head->children[word[i]-'a'];
            if(head->suffix != "")
                add_word(head, head->suffix), head->suffix = "", head->is_word = false;
            if(i == word.size()-1)
                head->is_word = true;
        }
    }
}

string fopr ="", opr;

void print(node* head)
{
    if(head->suffix != "")
    {
        for(int i=0;i<head->suffix.size();i++)
            opr+=head->suffix[i];
        opr+='P';
        for(int i=0;i<head->suffix.size();i++)
            opr+='-';
        return;
    } else if(head->is_word) {
        opr+='P';
    }
    for(int i=0;i<26;i++)
    {
        if(head->children[i] != NULL)
        {
            opr+=char('a'+i);
            print(head->children[i]);
            opr+=char('-');
        }
    }
}

int main()
{
    int n, i, j;
    node *head, *root = new node();
    string word;

    cin >> n;
    for(i=0;i<n;i++)
    {
        cin >> word;
        add_word(root, word);
    }
    head = root;
    for(int i=0;i<26;i++)
    {
        if(head->children[i] != NULL)
        {
            opr = "";
            opr+=char('a'+i);
            print(head->children[i]);
            opr+=char('-');
            j = opr.size()-1;
            while(opr[j] == '-')
                j--;
            operations.push_back(make_pair(opr.size()-j, opr));
        }
    }
    sort(operations.begin(), operations.end());
    for(auto a:operations)
        fopr += a.second;
    j = fopr.size()-1;
    while(fopr[j] == '-')
        j--;
    fopr = fopr.substr(0, j+1);
    cout << fopr.size() << '\n';
    for(auto a: fopr)
        cout << a << '\n';
    return 0;
}
