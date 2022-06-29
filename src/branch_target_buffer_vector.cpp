#include "branch_target_buffer_vector.hpp"
#include <ostream>
#include <iostream>

using namespace std;

branch_target_buffer_vector::branch_target_buffer_vector(unsigned int size): size(size)
{
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
        cout << " ######### busy: " << btb_vector[index]->busy <<" pc: " << btb_vector[index]->pc <<" predicted_pc: " << btb_vector[index]->predicted_pc << endl << flush;
    }
    cout << " ######### BTB Summary End " << endl << flush;
}

int branch_target_buffer_vector::find_index_by_PC(unsigned int pc)
{
	for (unsigned int index = 0; index < size; index++)
    {
        if (btb_vector[index]->busy && btb_vector[index]->pc == pc) {
            return index;
        }
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
        
        for (unsigned int i = 0; i < size; i++) {
            if (!btb_vector[i]->busy) {
                btb_vector[i]->busy = true;
                btb_vector[i]->pc = pc;
                btb_vector[i]->predicted_pc = predicted_pc;

                cout << "Inserido no BTB - Pc: " << btb_vector[i]->pc << " Predicted_pc: " << btb_vector[i]->predicted_pc << endl << flush;

                break;
            }
        }

        //TODO: Oq faz se estiver cheio?
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