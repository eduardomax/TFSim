#pragma once

class branch_target_buffer_vector
{
public:
    branch_target_buffer_vector(unsigned int size);
    ~branch_target_buffer_vector();
    int find_index_by_PC(unsigned int pc);
    bool exist_predicted_pc(unsigned int pc);
    void insert_pc(unsigned int pc, unsigned int predicted_pc);
    void delete_entry(unsigned int pc);
    void print_btb();

    struct btb {
            bool busy;
            unsigned int pc;
            unsigned int predicted_pc;

            btb()
            {
                busy = false;
                pc = 0;
                predicted_pc = 0;
            }
        };    
private:
    unsigned int size;
    btb **btb_vector;

};
