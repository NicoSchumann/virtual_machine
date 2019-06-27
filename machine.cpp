#include "machine.hpp"

#include <iostream>

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
           r[ip] = mem[r[ip]];
           break;
            
       case JZ:
           if( r[flags] & f::zero ) r[ip] = mem[r[ip]];
           break;
           
       case JNZ:
           if( !(r[flags] & f::zero) ) r[ip] = mem[r[ip]];
           break;
           
       case JE:  // jump if equal
           if( r[flags] & f::equal  ) r[ip] = mem[r[ip]];
           break;
       
       case JNE:  // jump if not equal
           if( !(r[flags] & f::equal) ) r[ip] = mem[r[ip]];
           break;
       
       case JG:   // jump if greater
           if( r[flags] & f::greater ) r[ip] = mem[r[ip]];
           break;
       
       case JLE:   // jump if not greater (lower or equal)
           if( !(r[flags] & f::greater) ) r[ip] = mem[r[ip]];
           break;
       
       case JL:   // jump if lower
           if( r[flags] & f::lower ) r[ip] = mem[r[ip]];
           break;
       
       case JGE:   // jump if not lower (greater or equal)
          if( !(r[flags] & f::lower) ) r[ip] = mem[r[ip]];
          break;
       
        
          // comparing operations
             
       case CMP:   // CMP rs, rt of equal-, greater-, and lower than
           rs = mem[ip];
           ++ r[ip];
           rt = mem[ip];
           if( r[rt] == r[rs] ) r[flags] |= f::equal;  // setting equql flag
           else r[flags] &= -1 & ~f::equal;           // clearing equal flag
           if( r[rt] < r[rs] ) r[flags] |= f::lower;    // setting lower flag
           else r[flags] &= -1 & ~f::lower;            // clearing lower flag
           if( r[rt] > r[rs] )  r[flags] |= f::greater; // setting flag
           else r[flags] &= -1 & ~f::greater;           // clearing flag
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
           std::cout << ip_v << ": Operation not implemented.\n";
           break;
    }
}

/*         
int main()
{
}
*/