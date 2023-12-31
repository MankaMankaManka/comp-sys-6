#include <string>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){
    if (segment == "constant") {
        return "@" + to_string(offset) + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
    if (segment == "static"){
        return "@" + to_string(16 + offset) + "\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
    else if (segment == "temp") {
        return "@R5\nD=A\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
        else if (segment == "pointer") {
        if (offset == 0) {
            return "@THIS\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";

        } else if (offset == 1) {
            return "@THAT\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";

        }
        }
        string segmentBase = "";
        if (segment == "local") {
            segmentBase = "LCL";
        }

        else if (segment == "this") {
            segmentBase = "THIS";
        }
        else if (segment == "that") {
            segmentBase = "THAT";
        }

        else if (segment == "argument") {
            segmentBase = "ARG";
        }
        return "@" + segmentBase + "\nD=M\n@" + to_string(offset) + "\nA=D+A\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){
    if (segment == "static") {
        return "@SP\nM=M-1\nA=M\nD=M\n@" + to_string(16 + offset) + "\nM=D\n";
    }
    if (segment == "temp") {
        return "@R5\nD=A\n@" + to_string(offset) + "\nD=D+A\n@13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@13\nA=M\nM=D\n";
    }
        if (segment == "pointer") {
        if (offset == 0) {
            return "@THIS\n@SP\nM=M-1\nA=M\nD=M\n@THIS\nM=D\n";
        } else if (offset == 1) {
            return "@THAT\n@SP\nM=M-1\nA=M\nD=M\n@THAT\nM=D\n";
        }
    }
     else if (segment == "local" || segment == "this" || segment == "that" || segment == "argument") {
        string segmentBase = "";
        if (segment == "local") {
            segmentBase = "LCL";
        }
        else if (segment == "this") {
            segmentBase = "THIS";
        }
        else if (segment == "that") {
            segmentBase = "THAT";
        }
        else if (segment == "argument") {
            segmentBase = "ARG";
        }
        return "@" + segmentBase + "\nD=M\n@" + to_string(offset) + "\nD=D+A\n@13\nM=D\n@SP\nM=M-1\nA=M\nD=M\n@13\nA=M\nM=D\n";
    }
}
/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return "";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M-D\n";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    return "";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    return "";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M&D\n";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "@SP\nM=M-1\nA=M\nD=M\nA=A-1\nM=M|D\n";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "("+label+")\n";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "@"+label+"\n0;JMP\n";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "@SP\nM=M-1\nA=M\nD=M\n@"+label+"\nD;JNE\n";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}
