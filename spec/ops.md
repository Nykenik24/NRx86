# Operations

| Name | Description                               | Params            | Opcode    |
| ---- | ----------------------------------------- | ----------------- | --------- |
| HALT | Stops execution                           | _None_            | `0x1` (1) |
| LD   | Loads a value from memory into a register | `reg`, `PCoffset` | `0x2` (2) |
| ST   | Stores a register into memory             | `reg`             | `0x3` (3) |
