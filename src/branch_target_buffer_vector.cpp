#include "branch_target_buffer_vector.hpp"
#include <ostream>
#include <iostream>
#include<cmath>
#include <bitset>

using namespace std;

branch_target_buffer_vector::branch_target_buffer_vector(unsigned int size_bits): size_bits(size_bits)
{
    size = std::pow(2, size_bits);
    btb_vector = new btb*[size];
    for (unsigned int i = 0; i < size; i++) {
        btb_vector[i] = new btb();
    }
}

branch_target_buffer_vector::~branch_target_buffer_vector()
{
    for (unsigned int i = 0; i < size; i++)
        delete btb_vector[i];
    
    delete btb_vector;
}

void branch_target_buffer_vector::print_btb()
{
    cout << " ######### BTB Summary " << endl << flush;
    for (unsigned int index = 0; index < size; index++)
    {
        std::bitset<8> x(index);
        cout << " ######### [" << x << "] busy: " << btb_vector[index]->busy <<" pc: " << btb_vector[index]->pc <<" predicted_pc: " << btb_vector[index]->predicted_pc << endl << flush;
    }
    cout << " ######### BTB Summary End " << endl << flush;
}


int branch_target_buffer_vector::find_index_by_PC(unsigned int pc)
{
    unsigned int index = pc & ((1 << size_bits) - 1);
    if (btb_vector[index]->busy && btb_vector[index]->pc == pc) {
        return index;
    }
    return -1; //Not found
}

bool branch_target_buffer_vector::exist_predicted_pc(unsigned int pc)
{
    int index = find_index_by_PC(pc);
    return index != -1;
}

void branch_target_buffer_vector::insert_pc(unsigned int pc, unsigned int predicted_pc)
{
    int index = find_index_by_PC(pc);
    if (index == -1) {
        unsigned int index = pc & ((1<<size_bits)-1);

        btb_vector[index]->busy = true;
        btb_vector[index]->pc = pc;
        btb_vector[index]->predicted_pc = predicted_pc;

        cout << "Inserido no BTB - Pc: " << btb_vector[index]->pc << " Predicted_pc: " << btb_vector[index]->predicted_pc << endl << flush;
    }
}

void branch_target_buffer_vector::delete_entry(unsigned int pc)
{
    int index = find_index_by_PC(pc);
    if (index != -1) {
        btb_vector[index]->busy = false;
        btb_vector[index]->pc = 0;
        btb_vector[index]->predicted_pc = 0;

        cout << "Removendo do BTB - Pc: " << pc << endl << flush;
    }
}