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

    //TO BE ADDED   //done
    opcode["xor"]=0;
    functionValues["xor"]=38;
    shamtValues["xor"]=0;
    opcode["slt"]=0;
    functionValues["slt"]=42;
    shamtValues["slt"]=0;

    //FOR DIVISION SPECIAL TYPES  //CALL IT DIV INSTRUCTION
    opcode["mfhi"]=0;
    opcode["mflo"]=0;
    functionValues["mfhi"]=16;
    functionValues["mflo"]=18; 
    shamtValues["mfhi"]=0;
    shamtValues["mflo"]=0;

    //To be added  //done
    opcode["jr"]=0;
    functionValues["jr"]=8;
    shamtValues["jr"]=0;
    opcode["mthi"]=0;
    functionValues["mthi"]=17;
    shamtValues["mthi"]=0;
    opcode["mtlo"]=0;
    functionValues["mtlo"]=19;
    shamtValues["mtlo"]=0;
    //opcode["divu"]=0;
    //functionValues["divu"]=27;
    //shamtValues["divu"]





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

    //TO BE ADDED //DONE
    opcode["divu"]=0;
    functionValues["divu"]=27;
    shamtValues["divu"]=0;
    opcode["mult"]=0;
    functionValues["mult"]=24;
    shamtValues["mult"]=0;
    opcode["multu"]=0;
    functionValues["multu"]=25;
    shamtValues["multu"]=0;
    
    //to be added 3 reg format DONE
    opcode["srlv"]=0;
    functionValues["srlv"]=6;
    shamtValues["srlv"]=0;
    opcode["srav"]=0;
    functionValues["srav"]=7;
    shamtValues["srav"]=0;
    opcode["sllv"]=0;
    functionValues["sllv"]=4;
    shamtValues["sllv"]=0;


    //I-FORMAT
    opcode["lw"]=35;
    opcode["sw"]=43;
    opcode["beq"]=4; 
    opcode["bne"]=5;
    opcode["addi"]=8;
    opcode["lb"]=32;
    opcode["sb"]=40;

    //LW SW FORMAT //DONE
    opcode["lbu"]=36;
    opcode["lh"]=33;
    //TO BE ADDED LW //DONE
    opcode["ll"]=48;
    opcode["sc"]=56;
    opcode["lwr"]=38;
    opcode["lwl"]=34;
    opcode["swr"]=46;
    opcode["swl"]=42;

    //BEQ IF COND //DONE
    opcode["andi"]=12;
    opcode["ori"]=13;
    opcode["slti"]=10;
    opcode["sltiu"]=11;
    
    


    //JUMP FORMAT
    opcode["j"]=2;
    opcode["b"]=2;
    //To be added
    
    
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
                bitset<5>rd(regValues[instructions[i][1]]);
                bitset<5>rt(0);
                bitset<5>shamt(shamtValues[instructions[i][0]]);
                bitset<6>func(functionValues[instructions[i][0]]);

                bit32B += opcodeReader.to_string();
                bit32B +=rs.to_string();
                bit32B +=rt.to_string();
                bit32B +=rd.to_string();
                bit32B +=shamt.to_string();
                bit32B +=func.to_string();

            }
            else if(instructions[i][0]=="mthi" || instructions[i][0]=="mtlo" || instructions[i][0]=="jr")
            {
                bitset<6>opcodeReader(opcode[instructions[i][0]]);
                bitset<5>rd(0);
                bitset<5>rs(regValues[instructions[i][1]]);
                bitset<5>rt(0);
                bitset<5>shamt(shamtValues[instructions[i][0]]);
                bitset<6>func(functionValues[instructions[i][0]]);

                bit32B += opcodeReader.to_string();
                bit32B +=rs.to_string();
                bit32B +=rt.to_string();
                bit32B +=rd.to_string();
                bit32B +=shamt.to_string();
                bit32B +=func.to_string();
            }
            else if(instructions[i][0]=="srlv" || instructions[i][0]=="srav" || instructions[i][0]=="sllv")
            {
                cout<<"Here "<<endl;
                bitset<6>opcodeReader(opcode[instructions[i][0]]);
                bitset<5>rs(regValues[instructions[i][3]]);
                bitset<5>rt(regValues[instructions[i][2]]);
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
            if(instructions[i][0]=="slti" || instructions[i][0]=="sltiu" ||instructions[i][0]=="addi" || instructions[i][0]=="ori")
            {
                bitset<6>opcodeReader(opcode[instructions[i][0]]);
                bitset<5>rs(regValues[instructions[i][2]]);
                bitset<5>rt(regValues[instructions[i][1]]);
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
            else
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
            bitset<26>immediate(x);
          


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
                            cout<<i+1<<" and "<<i+1+1<<" lines violate"<<endl;
                            flag=1;
                        }
                    }
                }
                else if(instructions[i+1][instructions[i+1].size()-1]=="2")  //FOR LW SW LB SB
                {
                    if(instructions[i][1]==instructions[i+1][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION"<<endl;
                        cout<<i+1<<" and "<<i+1+1<<" lines violate"<<endl;
                        flag=1;
                    }
                }
                else if(instructions[i+1][instructions[i+1].size()-1]=="3")   //BEQ BNE
                {
                    if(instructions[i][1]==instructions[i+1][1] || instructions[i][1]==instructions[i+1][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND --I FORMAT VIOLATION"<<endl;
                        cout<<i+1<<" and "<<i+1+1<<" lines violate"<<endl;
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
                            cout<<i+1<<" and "<<i+1+1<<" lines violate"<<endl;
                            flag=1;
                        }
                    }
                }
                if(instructions[i+1][instructions[i+1].size()-1]=="2") // FOR LW,SW,ADDI
                {
                    if(instructions[i][1]==instructions[i+1][2])
                    {
                        
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                        cout<<i+1<<" and "<<i+1+1<<" lines violate"<<endl;
                        flag=1;
                    }
                }
                if(instructions[i+1][instructions[i+1].size()-1]=="3") //FOR BEQ,BNE
                {
                    if(instructions[i][1]==instructions[i+1][1] || instructions[i][1]==instructions[i+1][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION FOR BEQ OR BNE WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                        cout<<i+1<<" and "<<i+1+1<<" lines violate"<<endl;
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
                            cout<<i+1<<" and "<<i+1+1+1<<" lines violate"<<endl;
                            flag=1;
                        }
                    }
                }
                if(instructions[i+2][instructions[i+2].size()-1]=="2") // FOR LW,SW,ADDI
                {
                    if(instructions[i][1]==instructions[i+2][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                        cout<<i+1<<" and "<<i+1+1+1<<" lines violate"<<endl;
                        flag=1;
                    }
                }
                if(instructions[i+2][instructions[i+2].size()-1]=="3") //FOR BEQ,BNE
                {
                    if(instructions[i][1]==instructions[i+2][1] || instructions[i][1]==instructions[i+2][2])
                    {
                        cout<<"DATA DEPENDENCY FOUND ---I-FORMAT VIOLATION FOR BEQ OR BNE WHEN FOWARDING IS NOT CONSIDERED"<<endl;
                        cout<<i+1<<" and "<<i+1+1+1<<" lines violate"<<endl;
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
    try
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
        else if(x=="srlv" || x=="srav" || x=="sllv" ||x=="xor" || x=="slt" || x=="add" || x=="sub" || x=="mul" || x=="and" || x=="or" ||  x=="sll" || x=="srl" || x=="sra" || x=="addu") //R-FORMAT
        {
            string reg1,reg2,reg3;
            cin>>reg1>>reg2>>reg3;
            //if(x!="sll" || x!="srl" || x!="sra" ||reg3[0]!='$' || reg1[0]!='$' || reg2[0]!='$')
            //{
            //    cout<<"Invalid R-Instruction Format"<<endl;
            //    return 0;
            //}
            temp.pb(x);
            temp.pb(reg1);
            temp.pb(reg2);
            temp.pb(reg3);

            temp.pb(to_string(1));
        }
        else if(x=="lwl" || x=="swr" || x=="swl" ||x=="lw" || x=="sw" || x=="lb" || x=="sb" || x=="lbu" || x=="lh" || x=="ll" || x=="sc" || x=="lwr") //I-FORMAT TYPE1
        {
            string reg1,reg2;
            string offset;
            cin>>reg1>>offset>>reg2;
            if(reg1[0]!='$' || reg2[0]!='$' || offset[0]=='$')
            {
                cout<<"Invalid I-Instruction Format"<<endl;
                return 0;
            }
            temp.pb(x);
            temp.pb(reg1);
            temp.pb(reg2);
            temp.pb(offset);
            temp.pb(to_string(2));
        }
        else if(x=="beq" || x=="bne" || x=="addi" ||x=="ori"|| x=="slti" || x=="sltiu" ) //I-FORMAT TYPE2
        {
            string reg1,reg2;
            string offset;
            cin>>reg1>>reg2>>offset;
            if(reg1[0]!='$' || reg2[0]!='$' || offset[0]=='$')
            {
                cout<<"Invalid I-Instruction Format"<<endl;
                return 0;
            }
            temp.pb(x);
            temp.pb(reg1);
            temp.pb(reg2);
            temp.pb(offset);
            temp.pb(to_string(3));
        }
        else if(x=="div" || x=="divu" || x=="mult" || x=="multu")
        {
            string reg1,reg2;
            cin>>reg1>>reg2;
            if(reg1[0]!='$' || reg2[0]!='$')
            {
                cout<<"Invalid R-Instruction Format"<<endl;
                return 0;
            }
            temp.pb(x);
            temp.pb(reg1);
            temp.pb(reg2);
            temp.pb(to_string(10));
        }
        else if(x=="j" || x=="b" )  //JUMP-FORMAT
        {
            string address;
            cin>>address;

            temp.pb(x);
            temp.pb(address);
            temp.pb(to_string(4));
        }
        else if(x=="mfhi" || x=="mflo" || x=="jr" || x=="mthi" || x=="mtlo") //R FORMAT SPECIAL TYPE
        {
            string reg;
            cin>>reg;
            if(reg[0]!='$')
            {
                cout<<"Invalid R-Instruction Format(mfhi format)"<<endl;
                return 0;
            }
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
    catch(...)
    {
        cout<<"There seems to be some problem in one of the opcodes of the instruction while executing"<<endl;
    }
}
//SUPPORTS 43 INSTRUCTIONS 
