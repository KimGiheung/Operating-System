#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void produce_fstream(ofstream*ofs, ifstream*ifs);

int main()
{
   //produce file stream
   ofstream ofs;
   ifstream ifs;
   produce_fstream(&ofs,&ifs);
   
   //Variable declaration
   char line[256];
   int sentence       = 0;
   int idle          = 0;
   int processing_time = 0;
   ifs.getline(line,256);
   sentence = stoi(string(line));
   vector <vector <int>> v;
   string word;
   

   //2D Vector sortedmulti
   for(int i=0;i<sentence;i++)
   {
    	vector <int> segment;
    	ifs.getline(line,256);
    	stringstream ss;
    	ss.str(string(line));
    	while(ss >> word) segment.push_back(stoi(word));
    	for(int j = 0; j<segment.size();j++)
		{
//        cout << segment[j] << ' ';
      	}
      	cout << endl;
      	v.push_back(segment);
   }
   
   
   
   //process 상태 정의
   int wait = 0;
   int cpu  = 1;
   int io    = 2;
   int end    = 3;
   int work = 4;
   
   vector <vector <int>> process(sentence, vector<int>());
   //Schaduling for multi-programming
   for(int i =0; i<sentence;i++)
   {
		for(int j = 0;j<v[i].size();j++)
    	{
   			if(j%2==0)
        	{
            	for(int k=0;k<v[i][j];k++)
            	{
            		process[i].push_back(cpu);
            	} 
            
         	}   
         	else
         	{
            	for(int k=0;k<v[i][j];k++)
            	{	
               		process[i].push_back(io);
            	}
         	}
      	}
      	process[i].push_back(end);
      	cout << endl;
   }
   
   
   

   
   
   //Multi-programming
   int row[sentence];
   int process_state[sentence];   //run or end
   int job = 0;
   int idle_check = 0;


//   //process 상태 정의
//   int wait = 0;
//   int cpu  = 1;
//   int io    = 2;
//   int end    = 3;
//   int work = 4;

end

   //가장 먼저 들어온걸 기준으로 함
int end_process = 0;  
   while(true)
   {
  		bool cpu_job = false;

      	for(int j = 0;j<sentence;j++)
      	{
//         	cout << "j : " << j << " pt: " << processing_time << endl;
        	if(process_state[j] == ) 
			{
				if(end_process == sentence -1)
				{
					int idle_discount = 0;
					for(int k = 0;k<sentence;k++) 
					{ 
						if(idle_discount < process[k].size()) idle_discount = k;
					}
	
					if(process[idle_discount][processing_time] == end)
					{
						int dis_value = 0;
						for(int k = process[idle_discount].size() - 2;k>0;k--)
						{
							if(process[idle_discount][k] == cpu)break; 
							else dis_value++;
						}	
						idle -= dis_value + 1;
						break;
					}
				
				}
				else continue;
				
			}
			
			
			
        	else if(process[j][processing_time] == wait)
        	{
            	process_state[j] = wait;
        	}
        	else if(process[j][processing_time] == cpu)
        	{
            	cpu_job = true;
            	while(process[j][processing_time] == cpu)
            	{	
               		for(int k = 0;k<sentence;k++)
               		{
                		if(k == j) continue;
                		else if(process_state[k] == end) continue;
                		else if(process[k][processing_time] == cpu) 
               			{
//                     cout << "k : " << k << endl;
                    		process[k].insert(process[k].begin()+processing_time, wait);
                  		}
                  //end, wait이 나모녀 precess_state에 저장 
               		}
         
               		for(int k = 0;k<sentence;k++)
               		{
                		if(process_state[k] == end) continue;
                  		process_state[k] = process[k][processing_time];
                  		if(process[k][processing_time] == end) end_process++; 
               		}
               	processing_time++;
            	}
        		break;
        	}
        	else if(process[j][processing_time] == io)
        	{
            	process_state[j] = io;
        	}
        	else if(process[j][processing_time] == end)
        	{
            	process_state[j] = end;
        	}
        	else 
        	{
            	process_state[j] = end;
        	}

    	}
    
      //cpu 작업을 했다면 idel count할 필요 없음 
      

//      //processing_time 설정
//      cout << "processing_time" << processing_time << endl;
//      //cpu검사가 끝났으면 ++, 안함
//      //cpu검사
//      cout << "processing_time" << processing_time << endl;
      
      	for(int k = 0; k<sentence;k++)
      	{
        	if( process_state[k] != cpu) idle_check++;
      	}
      	if(idle_check == sentence) 
		{
			//idle 제거 			
			idle++;    
		}  
      	idle_check = 0;
      	for(int k = 0;k<sentence;k++)
      	{
        	if(process_state[k] == end) continue;
        	process_state[k] = process[k][processing_time];
        	if(process[k][processing_time] == end) end_process++;
        	
     	}
            
      

      //작업 끝났는지 확인
    	for(int k = 0;k<sentence;k++)
      	{
        	if(process_state[k] != end)break;
        	else job++;
      	}
      
    	if(job == sentence)   
      	{
        	processing_time--;
        	break;
      	}   
      	else job = 0;
      
      
      
//      cout << "processing_time" << processing_time << endl;
      //cpu검사가 끝났으면 ++, 안함
      //cpu검사
    	if(cpu_job == true)   continue;
    	else processing_time++;
//      cout << "processing_time" << processing_time << endl;
   }

	ofs << idle  << ' ' << processing_time + 1;
	
	ofs.close();
	ifs.close();
}



void produce_fstream(ofstream*ofs, ifstream*ifs)
{
   ofs->open("multi.out", ios::out | ios::app);
   if (ofs->fail())
   {
      cerr << "Error!" << endl;
   }
   
   ifs->open("multi.inp",  ios::in);
   if (!ifs)
   {
      cerr << "Error!" << endl;
   }
}
