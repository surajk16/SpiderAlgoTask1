#include<fstream>
#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
#include<sstream>

using namespace std;

ofstream out;


void computeLPSArray(std::string pat, int M, int *lps)
{
    // length of the previous longest prefix suffix
    int len = 0;
 
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar 
            // to search step.
            if (len != 0)
            {
                len = lps[len-1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}


void KMPSearch(std::string pat, std::string txt,int page, int line, int &count, int *lps)
{
    int M = pat.length();
    int N = txt.length();
   
    int i = 0;  // index for txt[]
    int j  = 0;  // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
 
        if (j == M)
        {
        	if (i==j && !isalpha(txt[i-j+M]))
        	{
        		out.open("output.txt",std::ios::app);
				std::cout<<"Page "<<page<<", line "<<line<<"\n";
				out<<"Page "<<page<<", line "<<line<<"\n";
				out.close();
				count++;
			}
			
        	else if (!isalpha(txt[i-j-1]) && !isalpha(txt[i-j+M]))
            {
				out.open("output.txt",std::ios::app);
				std::cout<<"Page "<<page<<", line "<<line<<"\n";
				out<<"Page "<<page<<", line "<<line<<"\n";
				out.close();
				count++;
			}
            j = lps[j-1];
            
            
        }
 
        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
}





int main ()
{
	
	ifstream q,t;
	string query;
	
	q.open("queries.txt");
	out.open("output.txt",std::ios::trunc);
	out.close();

	
	
	while (std::getline(q, query))
	{
		out.open("output.txt",std::ios::app);
		cout<<"Word: "<<query<<"\nOccurences:\n";
		out<<"Word: "<<query<<"\nOccurences:\n";
		out.close();
				
		int page=1,count=0,M=query.length();
		int lps[M];
		computeLPSArray(query, M, lps);
		
		for (;page<=4;page++)
			{
				int line=1;
				string Result;
				stringstream convert; 
				convert << page;
				convert >> Result;
				
				string p = "page_"+Result+".txt";
				char *s = (char*) p.c_str();
				t.open(s);
				
				string txt;
				
				while (std::getline(t, txt))
				{
					KMPSearch(query, txt, page, line, count, lps);
					line++;	
				}
				
				page++;
				
				t.close();
				
			}
			
				
				
		out.open("output.txt",std::ios::app);

		if (count==0) { cout<<"None\n\n\n"; out<<"None\n\n\n"; }
		else { cout<<"\n\n"; out<<"\n\n"; }
		
		out.close();		
		
		
	}
	
	
	

	
	return 0;
}
