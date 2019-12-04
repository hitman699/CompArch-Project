#include<bits/stdc++.h>
#include<fstream>
#define pb push_back
#define mp make_pair
#define fi first
#define se secind
using namespace std;

//TO DO LIST
//FILL THE MAPS FOR INSTRUCTIONS GIVEN // AND IN INT_32T MAIN() ADD INSTRUCTION TYPE IN IF ELSE CONDITION'S GIVEN


map<string,int>opcode;
map<string,int>regValues;
map<string,int>functionValues;
map<string,int>shamtValues;


void initialize()
{
    //REGISTERS STORED HERE
    regValues["$zero"]=0;
    regValues["$s0"]=16;
    regValues["$s1"]=17;
    regValues["$s2"]=18;
    regValues["$s3"]=19;
    regValues["$s4"]=20;
    regValues["$s5"]=21;
    regValues["$s6"]=22;
    regValues["$s7"]=23;

    regValues["$t0"]=8;
    regValues["$t1"]=9;
    regValues["$t2"]=10;
    regValues["$t3"]=11;
    regValues["$t4"]=12;
    regValues["$t5"]=13;
    regValues["$t6"]=14;
    regValues["$t7"]=15;


    //R-FORMAT
    opcode["add"]=0; 
    opcode["sub"]=0;
    opcode["mul"]=0;
    opcode["and"]=0;
    opcode["or"]=0; 

    functionValues["add"]=32;
    functionValues["sub"]=34;
    functionValues["mul"]=24; 
    functionValues["and"]=36;
    functionValues["or"]=37;

    shamtValues["add"]=0;
    shamtValues["sub"]=0;
    shamtValues["mul"]=0;
    shamtValues["and"]=0;
    shamtValues["or"]=0;



    //I-FORMAT
    opcode["lw"]=35;
    opcode["sw"]=43;
    opcode["beq"]=4; 
    opcode["bne"]=5;


    //JUMP FORMAT
    opcode["j"]=2;
}
void processInstructions(vector<vector<string>>&instructions)
{
  
    vector<string>binary;
    for(int i=0;i<instructions.size();i++)
    {
        string bit32B="";
        if(instructions[i][instructions[i].size()-1]=="1")   //R FORMAT
        {
            
            bitset<6>opcodeReader(opcode[instructions[i][0]]);
            bitset<5>rs(regValues[instructions[i][2]]);
            bitset<5>rt(regValues[instructions[i][3]]);
            bitset<5>rd(regValues[instructions[i][1]]);
            bitset<5>shamt(shamtValues[instructions[i][0]]);
            bitset<6>func(functionValues[instructions[i][0]]);

            
            bit32B += opcodeReader.to_string();
            bit32B +=rs.to_string();
            bit32B +=rt.to_string();
            bit32B +=rd.to_string();
            bit32B +=shamt.to_string();
            bit32B +=func.to_string();
            //cout<<bit32B<<endl;
            binary.pb(bit32B);

        }
        else if(instructions[i][instructions[i].size()-1]=="2")   //LW AND SW
        {
            bitset<6>opcodeReader(opcode[instructions[i][0]]);
            bitset<5>rs(regValues[instructions[i][2]]);
            bitset<5>rt(regValues[instructions[i][1]]);
            bitset<16>immediate(stoi(instructions[i][3]));

            bit32B+=opcodeReader.to_string();
            bit32B+=rs.to_string();
            bit32B+=rt.to_string();
            bit32B+=immediate.to_string();

    
            //cout<<bit32B<<endl;
            binary.pb(bit32B);
        }
        else if(instructions[i][instructions[i].size()-1]=="3")   //BEQ AND BNE
        {
            bitset<6>opcodeReader(opcode[instructions[i][0]]);
            bitset<5>rs(regValues[instructions[i][1]]);
            bitset<5>rt(regValues[instructions[i][2]]);
            bitset<16>immediate(stoi(instructions[i][3]));

            bit32B+=opcodeReader.to_string();
            bit32B+=rs.to_string();
            bit32B+=rt.to_string();
            bit32B+=immediate.to_string();

            //cout<<bit32B<<endl;
            binary.pb(bit32B);
            
        }
        else if(instructions[i][instructions[i].size()-1]=="4")  //J
        {
            bitset<6>opcodeReader(opcode[instructions[i][0]]);
            bitset<26>immediate(stoi(instructions[i][1]));

            bit32B+=opcodeReader.to_string();
            bit32B+=immediate.to_string();
            
            //cout<<bit32B<<endl;
            binary.pb(bit32B);
        }
    }
    ofstream myfile("xyz.txt");
    for(int i=0;i<binary.size();i++)
    {
        //cout<<binary[i]<<endl;
        myfile<<binary[i]<<endl;
    }
    myfile.close();
}
int32_t main()   
{
    initialize(); //INITIALIZE ALL MAPS

    //string x;
    //vector<string>aaa;
    //ifstream obj("read.txt");
    //while(obj)
    //{
    //    getline(obj,x);
    //    if(x=="##")
    //    {
    //        break;
    //    }
    //    aaa.push_back(x);
    //} 

    string x;
    vector<vector<string>>instructions;
    ifstream obj("inputs.txt");
    while(obj)
    {
        getline(obj,x);
    }
    //vector<vector<string>>instructions;
    //while(1)
    //{
    //   
    //    //R=1          LW,SW=2             BEQ,BNE=3      J=4   //PASSED AT LAST TO IDENTIFY FORMAT OF INS. TO MAKE IMPLEMENTATION EASY
    //    vector<string>temp;
    //    string x;
    //    cin>>x;
    //    if(x=="##")
    //    {
    //        break;
    //    }
    //    else if(x=="add" || x=="sub" || x=="mul" || x=="and" || x=="or") //R-FORMAT
    //    {
    //        string reg1,reg2,reg3;
    //        cin>>reg1>>reg2>>reg3;
    //        
    //        temp.pb(x);
    //        temp.pb(reg1);
    //        temp.pb(reg2);
    //        temp.pb(reg3);
    //        temp.pb(to_string(1));
    //    }
    //    else if(x=="lw" || x=="sw") //I-FORMAT
    //    {
    //        string reg1,reg2;
    //        string offset;
    //        cin>>reg1>>offset>>reg2;
    //        
    //        temp.pb(x);
    //        temp.pb(reg1);
    //        temp.pb(reg2);
    //        temp.pb(offset);
    //        temp.pb(to_string(2));
    //    }
    //    else if(x=="beq" || x=="bne") //I-FORMAT
    //    {
    //        string reg1,reg2;
    //        string offset;
    //        cin>>reg1>>reg2>>offset;
    //        
    //        temp.pb(x);
    //        temp.pb(reg1);
    //        temp.pb(reg2);
    //        temp.pb(offset);
    //        temp.pb(to_string(3));
    //    }
    //    else if(x=="j")  //JUMP-FORMAT
    //    {
    //        string address;
    //        cin>>address;
    //       
    //        temp.pb(x);
    //        temp.pb(address);
    //        temp.pb(to_string(4));
    //    }
    //    instructions.pb(temp);
    //}
    //processInstructions(instructions);
}