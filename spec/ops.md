# Operations

| Name | Description                               | Params          | Opcode    |
| ---- | ----------------------------------------- | --------------- | --------- |
| HALT | Stops execution                           | _None_          | `0x1` (1) |
| LD   | Loads a value from memory into a register | `reg`, `offset` | `0x2` (2) |
| LDI  | Loads an immediate value into a register  | `reg`, `imm`    | `0x3` (3) |
| ST   | Stores a register into memory             | `reg`           | `0x4` (4) |

## LD

LD will load a value from memory (`mem[USEMEM_START + offset]`) to a register.

## LDI

LDI will load an immediate value (second operand of the operation) to a register.
