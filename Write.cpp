#include<bits/stdc++.h>
#include<fstream>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
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

    opcode["div"]=0; 
    opcode["sll"]=0; 
    opcode["srl"]=0; 
    opcode["sra"]=0;
    opcode["addu"]=0; 

    //FOR DIVISION SPECIAL TYPES  //CALL IT DIV INSTRUCTION
    opcode["mfhi"]=0;
    opcode["mflo"]=0;
    functionValues["mfhi"]=16;
    functionValues["mflo"]=18; 
    shamtValues["mfhi"]=0;
    shamtValues["mflo"]=0;


    functionValues["add"]=32;
    functionValues["sub"]=34;
    functionValues["mul"]=24; 
    functionValues["and"]=36;
    functionValues["or"]=37;

    functionValues["div"]=26;
    functionValues["sll"]=0;
    functionValues["srl"]=2;
    functionValues["sra"]=3;
    functionValues["addu"]=33; 



    shamtValues["add"]=0;
    shamtValues["sub"]=0;
    shamtValues["mul"]=0;
    shamtValues["and"]=0;
    shamtValues["or"]=0;

    shamtValues["div"]=0;
    shamtValues["sll"]=0;       //I WILL OVERRIDE THIS IN INPUT
    shamtValues["srl"]=0;       //I WILL OVERRIDE THIS IN INPUT
    shamtValues["sra"]=0;       //I WILL OVERRIDE THIS IN INPUT
    shamtValues["addu"]=0; 


    //I-FORMAT
    opcode["lw"]=35;
    opcode["sw"]=43;
    opcode["beq"]=4; 
    opcode["bne"]=5;
    opcode["addi"]=8;
    opcode["lb"]=32;
    opcode["sb"]=40;
    


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
            
            if(instructions[i][0]=="sll" || instructions[i][0]=="srl" || instructions[i][0]=="sra")
            {
                bitset<6>opcodeReader(opcode[instructions[i][0]]);
                bitset<5>rs(0);
                bitset<5>rt(regValues[instructions[i][2]]);
                bitset<5>rd(regValues[instructions[i][1]]);
                bitset<5>shamt(stoi(instructions[i][3]));
                bitset<6>func(functionValues[instructions[i][0]]);

                bit32B += opcodeReader.to_string();
                bit32B +=rs.to_string();
                bit32B +=rt.to_string();
                bit32B +=rd.to_string();
                bit32B +=shamt.to_string();
                bit32B +=func.to_string();
            }
            else if(instructions[i][0]=="mfhi"|| instructions[i][0]=="mflo")
            {
                bitset<6>opcodeReader(opcode[instructions[i][0]]);
                bitset<5>rs(0);
                bitset<5>rt(regValues[instructions[i][1]]);
                bitset<5>rd(0);
                bitset<5>shamt(shamtValues[instructions[i][0]]);
                bitset<6>func(functionValues[instructions[i][0]]);

                bit32B += opcodeReader.to_string();
                bit32B +=rs.to_string();
                bit32B +=rt.to_string();
                bit32B +=rd.to_string();
                bit32B +=shamt.to_string();
                bit32B +=func.to_string();

            }
            else
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
   
            }
            
            
            //cout<<bit32B<<endl;
            binary.pb(bit32B);

        }
        else if(instructions[i][instructions[i].size()-1]=="2")   //LW AND SW LB SB
        {
            bitset<6>opcodeReader(opcode[instructions[i][0]]);
            bitset<5>rs(regValues[instructions[i][2]]);
            bitset<5>rt(regValues[instructions[i][1]]);
            string hexStr = instructions[i][3]; 
            unsigned int x; 
            stringstream ss; 
            ss << std::hex << hexStr; 
            ss >> x; 
            //cout<<"The hex value is "<<x<<endl;
            bitset<16>immediate(x);
            
            //bitset<16>immediate(stoi(instructions[i][3]));

            bit32B+=opcodeReader.to_string();
            bit32B+=rs.to_string();
            bit32B+=rt.to_string();
            bit32B+=immediate.to_string();
            binary.pb(bit32B);
           
        }
        else if(instructions[i][instructions[i].size()-1]=="3")   //BEQ AND BNE AND ADDI
        {
            bitset<6>opcodeReader(opcode[instructions[i][0]]);
            bitset<5>rs(regValues[instructions[i][1]]);
            bitset<5>rt(regValues[instructions[i][2]]);
            string hexStr = instructions[i][3]; 
            unsigned int x; 
            stringstream ss; 
            ss << std::hex << hexStr; 
            ss >> x; 
            //cout<<"The decimal value is "<<x<<endl;
            bitset<16>immediate(x);
            
           

            bit32B+=opcodeReader.to_string();
            bit32B+=rs.to_string();
            bit32B+=rt.to_string();
            bit32B+=immediate.to_string();
           
            binary.pb(bit32B);
            
        }
        else if(instructions[i][instructions[i].size()-1]=="4")  //J
        {
            bitset<6>opcodeReader(opcode[instructions[i][0]]);
            //bitset<26>immediate(stoi(instructions[i][1]));
            string hexStr = instructions[i][1]; 
            unsigned int x; 
            stringstream ss; 
            ss << std::hex << hexStr; 
            ss >> x; 
            //cout<<"The decimal value is "<<x<<endl;
            bitset<16>immediate(x);
          


            bit32B+=opcodeReader.to_string();
            bit32B+=immediate.to_string();
            
            //cout<<bit32B<<endl;
            binary.pb(bit32B);
        }
        else if(instructions[i][instructions[i].size()-1]=="10") //DIV FORMAT
        {
            bitset<6>opcodeReader(opcode[instructions[i][0]]);
            bitset<5>rs(regValues[instructions[i][1]]);
            bitset<5>rt(regValues[instructions[i][2]]);
            bitset<5>rd(0);
            bitset<5>shamt(shamtValues[instructions[i][0]]);
            bitset<6>func(functionValues[instructions[i][0]]);

            bit32B += opcodeReader.to_string();
            bit32B +=rs.to_string();
            bit32B +=rt.to_string();
            bit32B +=rd.to_string();
            bit32B +=shamt.to_string();
            bit32B +=func.to_string();
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
//DATA FORWARDING IS ALLOWED  SO WILL DETECT ONLY DATA HAZARD CAUSED BY LOAD INSTRUCTION
void detectDataHazard(vector<vector<string>>instructions)
{
    int flag=0;
    for(int i=0;i<instructions.size();i++)
    {
        if(instructions[i][0]=="lw")  //THIS IS A LOAD WORD INSTRUCTION
        {
            if(i+1 <instructions.size())
            {
                if(instructions[i+1][instructions[i+1].size()-1]=="1")
                {
                    if(instructions[i+1][0] !="mfhi" && instructions[i+1][0]!="mflo")
                    {
                        if(instructions[i][1]==instructions[i+1][2] || instructions[i][1]==instructions[i+1][3])
                        {
                            cout<<"DATA DEPENDENCY FOUND ---R-FORMAT VIOLATION"<<endl;
                            flag=1;
                        }
                    }
                }
                else if(instructions[i+1][instructions[i+1].size()-1]=="2")  //FOR LW SW LB SB
                {
                    if(instructions[i][1]==instructions[i+1][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION"<<endl;
                        flag=1;
                    }
                }
                else if(instructions[i+1][instructions[i+1].size()-1]=="3")   //BEQ BNE
                {
                    if(instructions[i][1]==instructions[i+1][1] || instructions[i][1]==instructions[i+1][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND --I FORMAT VIOLATION"<<endl;
                        flag=1;
                    }
                }
                
            }
        }
    }
    if(flag==0)
    {
        cout<<"No Data Hazard Detected"<<endl;
    }
}
void detectDataHazard_noForwarding(vector<vector<string>>instructions){
    int flag=0;
    for(int i=0;i<instructions.size();i++)
    {
        if(instructions[i][instructions[i].size()-1]=="1")  //THIS IS A R TYPE INSTRUCTION
        {
            if(i+1 <instructions.size())
            {
                if(instructions[i+1][instructions[i+1].size()-1]=="1") // FOR R FORMAT
                {
                    if(instructions[i+1][0] !="mfhi" && instructions[i+1][0]!="mflo")
                    {
                        if(instructions[i][1]==instructions[i+1][2] || instructions[i][1]==instructions[i+1][3])
                        {
                            cout<<"DATA DEPENDENCY FOUND ---R-FORMAT VIOLATION WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                            flag=1;
                        }
                    }
                }
                if(instructions[i+1][instructions[i+1].size()-1]=="2") // FOR LW,SW,ADDI
                {
                    if(instructions[i][1]==instructions[i+1][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                        flag=1;
                    }
                }
                if(instructions[i+1][instructions[i+1].size()-1]=="3") //FOR BEQ,BNE
                {
                    if(instructions[i][1]==instructions[i+1][1] || instructions[i][1]==instructions[i+1][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION FOR BEQ OR BNE WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                        flag=1;
                    }
                }
            }
            if(i+2 <instructions.size())
            {
                if(instructions[i+2][instructions[i+2].size()-1]=="1") // FOR R FORMAT
                {
                    if(instructions[i+2][0] !="mfhi" && instructions[i+2][0]!="mflo")
                    {
                        if(instructions[i][1]==instructions[i+2][2] || instructions[i][1]==instructions[i+2][3])
                        {
                            cout<<"DATA DEPENDENCY FOUND ---R-FORMAT VIOLATION WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                            flag=1;
                        }
                    }
                }
                if(instructions[i+2][instructions[i+2].size()-1]=="2") // FOR LW,SW,ADDI
                {
                    if(instructions[i][1]==instructions[i+2][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                        flag=1;
                    }
                }
                if(instructions[i+2][instructions[i+2].size()-1]=="3") //FOR BEQ,BNE
                {
                    if(instructions[i][1]==instructions[i+2][1] || instructions[i][1]==instructions[i+2][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION FOR BEQ OR BNE WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                        flag=1;
                    }
                }
            }
            
        }
    }
    if(flag==0)
    {
        cout<<"No Data Hazard Detected Even When Fowarding Is Not Considered"<<endl;
    }   
}

int32_t main()   
{
    initialize(); //INITIALIZE ALL MAPS

    vector<vector<string>>instructions;
    while(1)
    {
        //R=1          LW,SW=2             BEQ,BNE=3      J=4   //PASSED AT LAST TO IDENTIFY FORMAT OF INS. TO MAKE IMPLEMENTATION EASY
        vector<string>temp;
        string x;
        cin>>x;
        if(x=="##")
        {
            break;
        }
        else if(x=="add" || x=="sub" || x=="mul" || x=="and" || x=="or" ||  x=="sll" || x=="srl" || x=="sra" || x=="addu") //R-FORMAT
        {
            string reg1,reg2,reg3;
            cin>>reg1>>reg2>>reg3;
            
            temp.pb(x);
            temp.pb(reg1);
            temp.pb(reg2);
            temp.pb(reg3);
            temp.pb(to_string(1));
        }
        else if(x=="lw" || x=="sw" || x=="lb" || x=="sb") //I-FORMAT TYPE1
        {
            string reg1,reg2;
            string offset;
            cin>>reg1>>offset>>reg2;
            
            temp.pb(x);
            temp.pb(reg1);
            temp.pb(reg2);
            temp.pb(offset);
            temp.pb(to_string(2));
        }
        else if(x=="beq" || x=="bne" || x=="addi") //I-FORMAT TYPE2
        {
            string reg1,reg2;
            string offset;
            cin>>reg1>>reg2>>offset;
            
            temp.pb(x);
            temp.pb(reg1);
            temp.pb(reg2);
            temp.pb(offset);
            temp.pb(to_string(3));
        }
        else if(x=="div")
        {
            string reg1,reg2;
            cin>>reg1>>reg2;
            temp.pb(x);
            temp.pb(reg1);
            temp.pb(reg2);
            temp.pb(to_string(10));
        }
        else if(x=="j")  //JUMP-FORMAT
        {
            string address;
            cin>>address;
           
            temp.pb(x);
            temp.pb(address);
            temp.pb(to_string(4));
        }
        else if(x=="mfhi" || x=="mflo") //R FORMAT SPECIAL TYPE
        {
            string reg;
            cin>>reg;
            temp.pb(x);
            temp.pb(reg);
            temp.pb(to_string(1));
        }
        instructions.pb(temp);
    }
    detectDataHazard(instructions);
    detectDataHazard_noForwarding(instructions);
    processInstructions(instructions);
}
//SUPPORTS 20 INSTRUCTIONS 
