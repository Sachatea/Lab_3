#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool is_word (const char c) 
{
    char sum[60] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_'};

    for (char a : sum) 
    {
        if (c == a) 
        {
            return false;
        }
    }
    return true;
}

bool roth (char x)                       // розділові знаки 
{
    vector<char> roth = { ',','(',')','[',']',':','{','}',' '};
    for (char a : roth)
    {
        if (x == a)
        {
            return true;
        }
    }
    return false;
}

void indecator(string slovo)
{
    char sum[60] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_' };

    int i = 0;
    for (char c : slovo) 
    {
        for (char x : sum)
        {
            if (c == x)
            {
                i = 1;
            }
        }
        if (i == 0)
        {
            cout << "<" << slovo << " | ?>,";
            return;
        }
        i = 0;
    }
    cout << "<" << slovo << " | I>,";
}

void ind (string slovo)
{
    slovo += " ";

    string word;
    for (char c : slovo)
    {
        if (c == '.' or c == ' ')
        {
            indecator(word);
            if (c == '.')
            {
                cout << "<" << c << "|PM>,";
            }
        }
        else
        {
            word += c;
        }
    }



}

bool is_num (const string slovo)
{
    bool first = isdigit(slovo[0]);
    int dot = 0;

    for (char c : slovo) 
    {
        if (c == '.')
        {
            dot += 1;
        }
        if (!isdigit(c) && c != '.') 
        {
            return false;
        }
    }
    if (dot <= 1 and first)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_SIX(const char c)
{
    vector<char> A = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','x','X'};
    for (char a : A)
    {
        if (c == a)
        {
            return true;
        }
    }
    return false;
}

bool is_six(const string slovo)
{
    int x = 0;
    if (slovo.length() < 2 or not(slovo[0] == '0' and (slovo[1] == 'x' or slovo[1] == 'X')))
    {
        return false;
    }
    for (char c : slovo)
    {
        if (c == 'x' or c == 'X')
        {
            x += 1;
        }
        if (!is_SIX(c))
        {
            return false;
        }
    }
    if (x > 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool is_operator (const string slovo)          // оператори
{
    vector<string> python_operators = {
        "+", "-", "*", "/", "%", "**", "//",
        "==", "!=", "<", ">", "<=", ">=",
        "and", "or", "not",
        "=", "+=", "-=", "*=", "/=", "%=",
        "==", "!=", "<", ">", "<=", ">=",
        "in", "is",
        "&", "|", "^", "~", "<<", ">>"
    };
    for (string a : python_operators)
    {
        if (slovo == a)
        {
            return true;
        }
    }
    return false;
}

bool is_reth (const string slovo)               //зарезервовані слова
{         
    vector<string> reserved_words = {
        "False", "None", "True", "as", "assert", "async", "await", "break",
        "class", "continue", "def", "del", "elif", "else", "except", "finally",
        "for", "from", "global", "if", "import", "lambda", "nonlocal",
        "pass", "raise", "return", "try", "while", "with", "yield"
    };
    for (string a : reserved_words)
    {
        if (slovo == a)
        {
            return true;
        }
    }
    return false;
}     

void recognizer (string slovo)                       // без пробілів 
{
    string word;

    slovo += " ";
    for (char c : slovo)
    {
        if (roth(c))
        {
            if (word != "")
            {
                if (is_reth(word))                      //резервовані слова
                {
                    cout << "<" << word << " | RW>,";
                }
                else if (is_operator(word))             //оператори
                {
                    cout << "<" << word << " | OP>,";
                }
                else if (is_num(word) or is_six(word))  //числа
                {
                    cout << "<" << word << " | N>,";
                }
                else                                    //індентифікатори + все що залишиться
                {
                    ind(word);
                }
            }
            word = "";
        }
        else
        {
            word += c;
        }
    }
}

void analys(string file_name)
{
    string str, word;
    ifstream file;

    file.open(file_name);
    if (!file.is_open())                           // повідомляє чи відкрився файл
    {                       
        cout << "error, no file" << endl;
    }

    int lapku1 = 0, lapku2 = 0;
    int com1 = 0, com2 = 0, com3 = 0;
    while (getline(file, str))                     // розділяє рядок пробілами і розділовими + коментарі
    {
        str += " ";
        for (char c : str) 
        {
            if (com1 == 1 or com2 % 2 == 1 or com3 % 2 == 1)
            {
                cout << c;
            }
            if (c == '#')
            {
                com1 = 1;
                cout << "<" << c;
            }
            if (com1 == 0)               // не малий коментар
            {
                if (roth(c))
                {
                    if (word == "'''")
                    {
                        if (com2 % 2 == 0)
                        {
                            cout << "<'''";
                        }
                        if (com2 % 2 == 1)
                        {
                            cout << "| big comment>,";
                        }
                        com2 += 1;
                    }
                    else if (word == "\"\"\"")
                    {
                        if (com3 % 2 == 0)
                        {
                            cout << "<\"\"\"";
                        }
                        if (com3 % 2 == 1)
                        {
                            cout << "| big comment>,";
                        }
                        com3 += 1;
                    }
                    else if (word != "" and com2 % 2 == 0 and com3 % 2 == 0)
                    {
                        if ((word[0] == '"' and word[word.length() - 1] == '"') or (word[0] == '\'' and word[word.length() - 1] == '\''))
                        {
                            lapku1 = 0;
                            lapku2 = 0;
                            cout << "<" << word << " | C>,";
                        }
                        else if (word[0] == '"' )
                        {
                            word += c;
                            lapku2 = 1;
                        }
                        else if (word[0] == '\'')
                        {
                            word += c;
                            lapku1 = 1;
                        }
                        else
                        {
                            recognizer(word);
                        }
                    }
                    if (c != ' ' and com2 % 2 == 0 and com3 % 2 == 0)
                    {
                        cout << "<" << c << "|PM>,";
                    }
                    else if (com2 % 2 == 0 and com3 % 2 == 0)
                    {
                        cout << " ";
                    }
                    if (lapku1 != 1 and lapku2 != 1)
                    {
                        word = "";
                    }
                }
                else
                {
                    word += c;
                }
            }
        }
        if (com1 == 1)
        {
            com1 = 0;
            cout << "| comment>,";
        }
        cout << endl;
    }
    if (com2 % 2 == 1 or com3 % 2 == 1)
    {
        cout << "| !!comment not finished>";
    }
}

int main()
{
    analys("Test1.txt");
    return 0;
}

