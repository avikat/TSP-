#include <stdio.h>
#include <time.h>
#include <bits/stdc++.h>

using namespace std; 

float matrix[10000][10000],cost=0;
int completed[10000];
int n;
int least(int c);
vector<int> path;


void print_vector(vector<int> v){
   for (int i = 0; i < v.size(); ++i)
   {
      cout<<v[i]<<" ";
   }
   cout<<endl;
}

float costp2(vector<int> v){
   float tcost = 0;
   for (int i = 0; i < v.size()-1; ++i)
   {
      tcost = tcost + matrix[v[i]][v[i+1]];
   }
   tcost = tcost+matrix[v[v.size()-1]][v[0]];
   return tcost;
}


vector<int> swap2opt(vector<int> route,int i,int k){

   vector<int> new_route;
   if(i>=0 && i<route.size()-1 && k > i && k < route.size()){
      for (int c = 0; c < i; ++c)
      {
         new_route.push_back(route[c]);
      }
      int dec = 0;
      for (int c = i; c < k+1 ; ++c)
      {
         new_route.push_back(route[k-dec]);
         dec++;
      }
      for (int c = k+1; c < route.size(); ++c)
      {
         new_route.push_back(route[c]);
      }

      return new_route;
   }
   
}

vector<int> two_opt(vector<int> route){
   vector<int> best;
   best = route;
   bool improved = true;

   int count_improve = 0;

   //print_vector(route);
   time_t start, stop;
   start = time(NULL);
   stop = start + 290;

   while(improved && count_improve<20 && stop>start){
      improved = false;
      for (int i = 0; i < route.size()-1; ++i)
      {
         for(int j=i+1;j<route.size();j++){
            vector<int> new_route = swap2opt(route,i,j);
            if(costp2(new_route)<costp2(best)){
               best = new_route;
               print_vector(best);
               improved = true;
               count_improve = 0;
               break;
            }
         }
         if(improved)
            break;
      }
      start = time(NULL);
      route = best;
      count_improve++;
   }
   return best;
}


void mincost(int city)
{
   //printf("%d\n",);
    int i,ncity;
 
    completed[city]=1;

    //cout<<city<<" ";
    path.push_back(city);

    ncity=least(city);
 
    if(ncity==999999)
    {
        ncity=0;
        //printf("%d ",ncity+1);
        cost+=matrix[city][ncity];
 
        return;
    }
 
    mincost(ncity);
}
 
int least(int c)
{
    int i,nc=999999;
    float min=999999,kmin;
   

    for(i=0;i < n;i++)
    {
      //printf("here\n");
        if((matrix[c][i]!=0)&&(completed[i]==0)){
         if(matrix[c][i]+matrix[i][c] < min)
            {
                min=matrix[i][0]+matrix[c][i];
                kmin=matrix[c][i];
                nc=i;
                //printf("here\n");
            }
        }
            
    }
 
    if(min!=999999){
      cost+=kmin;
    }
    return nc;
}

int main(void) {
   string s;
   cin>>s;
   cin>>n;
   float x[n],y[n];

   for (int i = 0; i < n; ++i)
   {
      cin>>x[i]>>y[i];
   }

   for (int i = 0; i < n; ++i)
   {
      for (int j = 0; j < n; ++j)
      {
         cin>>matrix[i][j];
      }
   }

   float min_cost_cal = 999999.0;

   for(int z=0;z<n;z++){
      for(int i=0;i<n;i++)
         completed[i] = 0;

      cost = 0;
      path.clear();
      mincost(z);
      if(cost<min_cost_cal)
         min_cost_cal = cost;
   }

   vector<int> final = two_opt(path);
   print_vector(final);
   return 0;
}
