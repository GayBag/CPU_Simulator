#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map<std::string, int> mp;
struct Opcods {
   std::string my_mov = "mov";
   std::string my_add = "add";
   std::string my_sub = "sub";
   std::string my_mul = "mul";
   std::string my_div = "div";
   std::string my_and = "and";
   std::string my_or  = "or";
}ops;
struct Register {
   std::string r1 = "r1";
   std::string r2 = "r2";
   std::string r3 = "r3";
}reg;
int string_to_int(std::string str)
{

   int sum=0, j = 0;
   bool flag =false;
   if(str[j]=='-'){
   j++;
   flag = true;
   }
    while(j!= str.size())
    {
      sum = sum*10 + (str[j]-'0');
      j++;
    }
 return !flag ? sum : (-1*sum);

}
int string_to_int2(std::string str,int i)
{
   std::string token;
   bool flag =false;
   int sum=0, j = 0;
   if(str[i] == 'r')
      {
         while(i < str.size())
         {
            token += str[i];
            i++;
         }
         return mp[token];
      }
   if(str[i]=='-'){
   i++;
   flag = true;
   }
   while(i!=str.size())
   {
     token+=str[i];
     i++;
   }
   
    while(j!= token.size())
    {
      sum = sum*10 + (token[j]-'0');
      j++;
    }
 return !flag ? sum : (-1*sum);

}
void mull(std::string str, int i)
{
   std::string op1,op2;
  while(str[i] != ','){
    op1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    op2+=str[i];
    i++;
  }

   if(op2[0]=='r')
    {
      mp[op1] *= mp[op2];
    }
    else
    {
      mp[op1] *= string_to_int(op2);
    }
    
}
void andd(std::string str, int i)
{
   std::string op1,op2;
  while(str[i] != ','){
    op1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    op2+=str[i];
    i++;
  }

   if(op2[0]=='r')
    {
      mp[op1] &= mp[op2];
    }
    else
    {
      mp[op1] &= string_to_int(op2);
    }
    
}
void orr(std::string str, int i)
{
   std::string op1,op2;
  while(str[i] != ','){
    op1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    op2+=str[i];
    i++;
  }

   if(op2[0]=='r')
    {
      mp[op1] |= mp[op2];
    }
    else
    {
      mp[op1] |= string_to_int(op2);
    }
    
}
void divv(std::string str, int i)
{
   std::string op1,op2;
  while(str[i] != ','){
    op1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    op2+=str[i];
    i++;
  }

   if(op2[0]=='r')
    {
      if(mp[op2] == 0)
      std::cout << "Error " << std::endl;
      else
      mp[op1] /= mp[op2];
    }
    else
    {
       if(string_to_int(op2))
      mp[op1] /= string_to_int(op2);
      else
      std::cout << "Error " << std::endl;
    }
    
}
void subb (std::string str,int i)
{

std::string op1,op2;
  while(str[i] != ','){
    op1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    op2+=str[i];
    i++;
  }

   if(op2[0]=='r')
    {
mp[op1] -= mp[op2];
    }
    else
    {
      mp[op1] -= string_to_int(op2);
    }
    
}
void addi(std::string str, int i)
{
   std::string op1,op2;
  while(str[i] != ','){
    op1+=str[i];
    ++i;
}
i = i+1;
  while(i != str.size()){
    op2+=str[i];
    i++;
  }

   if(op2[0]=='r')
    {
      mp[op1] += mp[op2];
    }
    else
    {
      mp[op1] += string_to_int(op2);
    }
    
}
void check_reg(std::string str,int i)
{
   std::string token;
   while(str[i]!=',')
   {
     token+=str[i];
     i++;
   }
    if (token == reg.r1) {
        mp[token] = string_to_int2(str, i+1);
         return;
      }
      if (token == reg.r2) {
        mp[token] = string_to_int2(str, i+1);
         return;
      }
      if (token == reg.r3) {
         
          mp[token] = string_to_int2(str, i+1);
         return;
         
      }


}
void check_opcodes(std::string str)
{
   std::string str1;
   for(int i = 0; i < str.size();i++)
   {
      while(str[i] != ' '){
        str1 += str[i];
        i++;
      }
      if (str1 == ops.my_mov) {
            check_reg(str, i+1);
         return;
      }
      if (str1 == ops.my_add) {
          addi(str, i+1);
         return;  
      }
      if (str1 == ops.my_sub) {
          subb(str, i+1);
         return;  
      }
      if (str1 == ops.my_mul) {
          mull(str, i+1);
         return;  
      }
      if (str1 == ops.my_div) {
          divv(str, i+1);
         return;  
      }
      if (str1 == ops.my_and) {
          andd(str, i+1);
         return;  
      }
      if (str1 == ops.my_or) {
          orr(str, i+1);
         return;  
      }
     
   }
}


int main()
{
  std::ifstream text("cpu.txt");
  std::string str;
 
  
  if(!text.is_open())
  {
    std::cout << "File open error " << std::endl;
  }
 else
 {
   while(!text.eof())
   {
      getline(text,str);
      check_opcodes(str);
   }
 }
  text.close();
 return 0;
}
