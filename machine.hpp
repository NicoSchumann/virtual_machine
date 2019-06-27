#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <cstdint>

using Int_t = std::int16_t;

enum reg { a, b, c, d, ip, sp, flags };

namespace f { enum reg_flags { 
    zero = 1, carry = 2, equal = 4, lower = 8, greater = 16
}; }

Int_t r [7] = {0}; // Registers a, b, c, d, ip, sp, flags;
Int_t mem [4096];  // the memory pool


enum OP {    // defined operations

    NOP  // No operation
    
  , MOV  // MOV rs,  rt: Move source register to target register.
  , LD   // LD  val, rt: Load value to target register
  , LDR  // LDR mem, rt: Load value of memory address to target register.
  , LDM  // LDM rs, mem: Save target register to memory address.
  
  , ADD  // ADD rs, rt: Add source register to target register.
  , SUB  // SUB rs, rt: Subtract source register from target register.
  , MUL  // MUL rs, rt: Multiply source register to target register.
  , DIV  // DIV rs, rt: Divide target register by source register. 
  , MOD  // MOD rs, rt: Divide target register modulo by source register.
  , INC  // INC rt
  , DEC  // DEC rt
  
  , AND  // AND rs, rt:  rt &= rs
  , OR   // OR  rs, rt:  rt |= rs
  , XOR  // XOR rs, rt:  rt ^= rs
  , NOT  // NOT rt:      rt ~= rt
  
  , ROR  // ROR rs, rt: Right rotation of rt by value of rs.
  , ROL  // ROL rs, rt: Left rotation of rt by value of rs.
  , SR   // SR  rs, rt: Right shift of rt by value of rs.
  , SL   // SL  rs, rt, Left shift of rt by value of rs
  
  , JMP  // JMP mem: Loads ip with value of memory address.
  , JZ   // JZ  mem: Loads ip with value of memory address if zero flag = 1
  , JNZ  // JNZ mem: Loads ip with value of memory address if zero flag = 0
  , JE   // JE  mem: Loads ip with value of memory address if equal flag = 1
  , JNE  // JNE mem: Loads ip with value of memory address if equal flag = 0
  , JG   // JG  mem: Loads ip with value of memory address if greater flag = 1
  , JLE  // JLE mem: Loads ip with value of memory address if greater flag = 0
  , JL   // JL  mem: Loads ip with value of memory address if lower flag = 1
  , JGE  // JGE mem: Loads ip with value of memory address if lower flag = 0

  , CMP  // CMP rs, rt: Sets equal-, greater-, and lower flags
  
  , POP   // POP  rs:  // Remove stack value and store into register.
  , PUSH  // PUSH rt:  // Add register value to stack.
  , PEEK  // PEEK rt:  // Load stack value into register.
};

#endif // MACHINE_HPP