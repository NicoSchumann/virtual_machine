#include <iostream>
#include <cstdint>

using Int_t = std::int16_t;

enum reg { a, b, c, d, ip, sp, flags };
namespace f { enum reg_flags { zf = 1, cf = 2, cmp = 4}; }

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
  , JZ   // JZ  mem: Loads ip with value of memory address if zero flag == 0
  , JNZ  // JNZ mem: Loads ip with value of memory address if zero flag == 1
  , CMP  // CMP rx, ry: If rx == ry, the cmp-flag == 1.
  , GT   // GT rx, ry: If rx is greater than ry, cmp-flag == 1.
  , LT   // LT rx, ry: If rx is greater than ry, cmp-flag == 1.
  
  , POP   // POP  rs:  // Remove stack value and store into register.
  , PUSH  // PUSH rt:  // Add register value to stack.
  , PEEK  // PEEK rt:  // Load stack value into register.
};

void perform_instruction()
{
    static Int_t rs, rt, val, maddr;  // register source, register target
 
    Int_t ip_v = r[ip]; // Save the value of ip.
    ++ r[ip];
    
    
    switch( ip_v )
    {
        case NOP:            // NOP
            break;
            
            
        // storing operations
            
        case MOV:            // MOV rs -> rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] = r[rs];
            break;
            
        case LD:           // LD val -> rt;
            val = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] = val;
            break;
            
        case LDR:           // <memory> -> rt
            val = mem[mem[ip]];
            ++ r[ip];
            rt = mem[ip];
            r[rt] = val;
            break;
            
        case LDM:          // LD rs -> <memory>
            rs = mem[ip];
            ++ r[ip];
            maddr = mem[ip];
            mem[maddr] = r[rs]; 
            break;
        
        
          // math operations:
        
        case ADD:       // ADD rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] += r[rs];
            break; 
            
        case SUB:        // SUB rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] -= r[rs];
            break;
        
        case MUL:   // MUL rs, rt
            rs = mem[ip];
            ++r[ip];
            rt = mem[ip]; 
            r[rt] *= r[rs];       
            break;
            
        case DIV:     // DIV rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] /= r[rs];
            break;
            
        case MOD:  // MOD rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] %= r[rs];
            break;
     
       case INC:
           rt = mem[ip];
           ++ r[rt];
           break;
           
       case DEC:
           rt = mem[ip];
           -- r[rt];
           break;
     
          // logical operations
          
        case AND:     // AND rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] &= r[rs];
            break;
            
        case OR:     // OR rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] |= r[rs];
            break;
        
        case XOR:     // XOR rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] ^= r[rs];
            break;
            
        case NOT:   // ~rt
            rt = mem[ip];
            r[rt] = ~r[rt];
            break;
            
            
         // bit shifting operations
         
        case SR:  // SR rs, rt
            rs = mem[ip];
            ++r[ip];
            rt = mem[ip];
            r[rt] >>= r[rs];
            break;
            
        case SL:  // SL rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            r[rt] <<= r[rs];
            break;
            
        case ROR:  // ROR rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            for( ; rs > 0; --rs ) {
                char bitmask = r[rt] & 1;
                bitmask << sizeof(r[rt]) * 8 - 1;
                r[rt] >>= 1;
                r[rt] |= bitmask;
            }
            break;
            
        case ROL:    // ROL rs, rt
            rs = mem[ip];
            ++ r[ip];
            rt = mem[ip];
            for( ; rs > 0; --rs) {
                char bitmask = r[rt] >> sizeof(r[rt]) * 8 - 1;
                r[rt] <<= 1;
                r[rt] |= bitmask;
            }
            break; 
            
            
         // jumping operations
         
       case JMP:   // JMP
           r[ip] = mem[ip];
           break;
            
       case JZ:
           if( !(r[flags] & f::zf) ) r[ip] = mem[ip];
           break;
           
       case JNZ:
           if( r[flags] & f::zf ) r[ip] = mem[ip]; 
           break;
           
       case CMP:   // CMP rx, ry
           rs = mem[ip];
           ++ r[ip];
           rt = mem[ip];
           if( r[rt] == r[rs] ) r[flags] |= f::cmp;
           else r[flags] &= -1 & ~f::cmp;
           break;
           
       case GT:  // GT rx, ry
           rs = mem[ip];
           ++ r[ip];
           rt = mem[ip];
           if( r[rt] > r[rs] ) r[flags] |= f::cmp;
           else r[flags] &= -1 & ~f::cmp;
           break;
           
       case LT: // LT rx, ry
           rs = mem[ip];
           ++ r[ip];
           rt = mem[ip];
           if( r[rt] < r[rs] ) r[flags] |= f::cmp;
           else r[flags] &= -1 & ~f::cmp;
           break;
           
           
         // stack operations
         
       case PUSH: // PUSH rs
           rs = mem[ip];
           r[sp] = r[rs];
           -- r[sp];
           break;
       
       case POP: // POP rt
           rt = mem[ip];
           r[sp] = r[rt];
           ++ r[sp];
           break;
           
       case PEEK:
           rt = mem[ip];
           r[rt] = r[sp];
           break;
           
       default:
           std::cout << ip_v << ": operation not implemented.\n";
           break;
    }
}

/*         
int main()
{
}
*/