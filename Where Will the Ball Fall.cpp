/*when the v shaped is formed?
1. current board =1 and the board on its right=-1 //stuck in the box
2. current board=-1 and the board on its left=1 // stuck in the box
3. ball's current col is 0, and grid[row][0]=-1 //left wall
4. ball's current col is grid[row].size()-1, and grid[row][0]=1 //right wall
*/
 vector<int> findBall(vector<vector<int>>& grid) {
    vector<int>ans(grid[0].size(),0);
    int n=0,col=0;
    while(col<grid[0].size()) //solve one col each time
    {
        int temp=col, n=col;
        for(int i =0; i<grid.size();i++)
        {//cout<<"ball is at  ("<<i<<","<<n<<")"<<endl;
		//Please see the explanation above for this if-statements .
            if((grid[i][n]==1&&(n+1<grid[0].size()&&grid[i][n+1]==-1))||(grid[i][n]==-1&&(n-1)>=0&&grid[i][n-1]==1)||(n==0&&grid[i][n]==-1)||(n==grid[0].size()-1&&grid[i][n]==1))
            {//cout<<"V shaped"<<endl;
                temp=-1;break;
            }else
            {
                temp+=grid[i][n];
                if(grid[i][n]==1)//determines ball's next move
                {
                    n=n+1;
                }else{n=n-1;}
            }
        }
        ans[col]=temp;
        col++; //advance to the next col
    }
      return ans;  
}