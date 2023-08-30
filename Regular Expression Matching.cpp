class Solution {
public:
    bool isMatch(string s, string p) {
       regex str_expr (p);
        if (regex_match (s,str_expr))
        {
            return true;
        }
      return false; 
    }
};