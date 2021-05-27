# Corewar
One of the Epitech's Mythic Projects

<img align='center' src="https://raw.githubusercontent.com/Heliferepo/Corewar/master/screen.png" width="1000">

## Results

- 97% On the assembler

- 100% On the virtual machine

The explanations of the project have been taken from [rizky/corewar](https://github.com/rizky/corewar) 
## The arena
Matches are played by a **V**irtual **M**achine featuring:
  - A circular memory buffer of **4096** bytes  
  - A CPU with: 
      - An instruction set of 16 operations
      - 16 32bit registers labelled from `r1` to `r16`
      - a **z**ero **f**lag (`zf`) whose state depends on the result of some instructions
  - A round-robin **process** scheduler

Each process has:
  - A **p**rogram **c**ounter (`pc`) that moves around in memory and point to specific memory locations
  - Its own set of register values
  - Its own `zf` value

## Match setup
Each player is assigned a unique 32bit **identifier**.  
Champions are loaded in memory at equally spaced offsets.  
Each champion is assigned a starting **process** which has:
  - Its `pc` set to the location of the champion's first byte
  - Its `zf` set to `0`
  - Its `r1` register set to its player's identifier
  - All of its other registers set to `0`

## Execution
The game is *turn*-based.  
Turns are called **cycle**s and correspond to a pass of the process scheduler.  
Every cycle, the scheduler gives a fixed amount of CPU time to each process sequentially, in the reverse order that they were spawned.

Running processes can be in either one of two states:
  - `Idle`: Waiting to decode an instruction
  - `Executing` an instruction: Waiting for a sufficient amount of CPU time to finish its execution

When an `Idle` process is given a cycle worth of CPU time, it attempts to decode the byte pointed by its `pc`:
  - If the byte is a valid instruction **opcode**, it starts `Executing` it 
  - Otherwise it stays `Idle` and the `pc` is moved to the next byte in memory

When an `Executing` process is given its last required cycle worth of CPU time, it attempts to decode the rest of the instruction pointed by its `pc`:
  - If the instruction is valid, it is **executed** and the `pc` is incremented by the decoded size
  - Otherwise it goes back to an `Idle` state and the `pc` is moved to the next byte in memory

## Win condition
The VM periodically performs a **live-check**.  
The number of cycles before a live-check is determined by a `check interval` value which is initialized to `1536`.  
During a live-check:
  - Every process that didn't execute at least one `live` instruction since the last live-check is **killed**
  - The `check interval` is decreased by `50` if either:
      - The total number of `live`s among all the processes is `≥ 21`
      - `10` consecutive live-checks had a number of `live`s `< 21`

The match ends when all processes are killed.  
The winner is the last player who has been reported alive. 

⚠ Processes can report any player to be alive, not exclusively their champion's player. See the `live` instruction for more information.

## Instruction set
The VM supports 16 instructions.  
Instructions take between **1** and **3** parameters.  
Parameters can be one of three types:
 - `Register`: one of the 16 registers available
 - `Direct`: an immediate numeric value
 - `Indirect`: a pointer offset to a location in memory. the offset is applied to the executing process' `pc` and the result is used to address a 32bit value in memory.

⚠ For most instructions that perform addressing, the *reach* is limited, in which case the `pc` offset is wrapped within a `(-512, 512)` ring using a modulo operation. The only three instructions that have unlimited reach are referred to as **long** instructions.

Every instruction has an `opcode` and executes in a certain number of cycles.  
Some instructions can take different types of parameters and therefore need an additional **p**arameter **c**ode **b**yte (`pcb`) when encoded (more details in the encoding section).  
Some instructions have 16bit `Direct` values instead of 32bit.

The table below summarizes all those characterics for every instruction:

| mnemonic | opcode | cycles ⏱ | param 1 | param 2 | param 3 |  pcb  | Direct size |
| -------- | ------ | --------- | ------- | ------- | ------- | ----- | ----------- |
| live     | 1      | 10        | D       |         |         | ❌    | 32          |
| ld       | 2      | 5         | DI      | R       |         | ✔    | 32          |
| st       | 3      | 5         | R       | RI      |         | ✔    | 32          |
| add      | 4      | 10        | R       | R       | R       | ✔    | 32          |
| sub      | 5      | 10        | R       | R       | R       | ✔    | 32          |
| and      | 6      | 6         | RDI     | RDI     | R       | ✔    | 32          |
| or       | 7      | 6         | RDI     | RDI     | R       | ✔    | 32          |
| xor      | 8      | 6         | RDI     | RDI     | R       | ✔    | 32          |
| zjmp     | 9      | 20        | D       |         |         | ❌    | 16          |
| ldi      | 10     | 25        | RDI     | RD      | R       | ✔    | 16          |
| sti      | 11     | 25        | R       | RDI     | RD      | ✔    | 16          |
| fork     | 12     | 800       | D       |         |         | ❌    | 16          |
| lld      | 13     | 10        | DI      | R       |         | ✔    | 32          |
| lldi     | 14     | 50        | RDI     | RD      | R       | ✔    | 16          |
| lfork    | 15     | 1000      | D       |         |         | ❌    | 16          |
| aff      | 16     | 2         | R       |         |         | ✔    | 32          |

📝 **R** = `Register` **D** = `Direct` **I** = `Indirect`

Some instructions can affect the zero flag `zf` by either reading or computing a value. If the value is zero, `zf` is set to `1`, otherwise it is set to `0`.

Detailed behaviors for every instruction:
<hr/>

`live` *id* | ⏱10

Reports this process **and** the player #`id` as being alive.
<hr/>

`ld` *src, dst* | ⏱5

*Load*s `src` in the register `dst`. `src`'s value affects `zf`.
<hr/>

`st` *src, dst* | ⏱5

*Store*s `src`'s register value in `dst` (either a register or a memory location).
<hr/>

`add` *lhs, rhs, dst* | ⏱10

Computes `lhs + rhs` and stores the result in the register `dst`. The result affects `zf`.
<hr/>

`sub` *lhs, rhs, dst* | ⏱10

Computes `lhs - rhs` and stores the result in the register `dst`. The result affects `zf`.
<hr/>

`and` *lhs, rhs, dst* | ⏱6

Computes `lhs & rhs` and stores the result in the register `dst`. The result affects `zf`.
<hr/>

`or` *lhs, rhs, dst* | ⏱6

Computes `lhs | rhs` and stores the result in the register `dst`. The result affects `zf`.
<hr/>

`xor` *lhs, rhs, dst* | ⏱6

Computes `lhs ^ rhs` and stores the result in the register `dst`. The result affects `zf`.
<hr/>

`zjmp` *offset* | ⏱20

Moves the process' `pc` by `offset` **only** if the process' `zf` is set to `1`.
<hr/>

`ldi` *lhs, rhs, dst* | ⏱25

Computes `lhs + rhs` and uses the result as an offset to address memory and load a 32bit value into the register `dst`.
<hr/>

`sti` *src, lhs, rhs* | ⏱25

Computes `lhs + rhs` and uses the result as an offset to address memory and store the value of the register `src` at that memory location.
<hr/>

`fork` *offset* | ⏱800

*Fork*s this process. This effectively creates a new process that inherits the current process' registers and `zf`. The spawned process has its `pc` set to his parent's `pc` offseted by `offset`.
<hr/>

`lld` *src, dst* | ⏱10


The **long** version of **ld**.
<hr/>

`lldi` *lhs, rhs, dst* | ⏱50

The **long** version of **ldi**. Neither the parameter values nor the computed address will have their reach limited. Contrary to **ldi**, the value loaded from memory affects `zf`.
<hr/>

`lfork` *offset* | ⏱1000

The **long** version of **fork**
<hr/>

`aff` *chr* | ⏱2 (not yet implemented, subject to change)

Makes this process' champion talk by displaying `chr`'s value. This instruction is useful if you want to ridicule your opponents.
<hr/>


## Writing champions
Champions consist of bytecode generated from compiling programs written in the VM's assembly language.

### The assembly language
A champion's program consist of:
 - A name
 - A description
 - A sequence of instructions

The champion's name and description are set using the `.name` and `.comment` directives respectively.  
Instructions and directives are each placed on a single line, empty lines are allowed, token spacing works with any number of whitespaces and you can start line comments by using the `#` character  
To create a champion called "John Cena", you could for instance start your program by writing:
```
.name    "John Cena"          # Champion's name
.comment "And his name is..." # Champion's description
```

Instructions are composed of a **mnemonic** followed by comma (`,`) separated parameters
 - `Register` parameters are valid register numbers prefixed by a `r` character. (e.g: `r12`)
 - `Direct` parameters are numbers (or labels, see below) prefixed by a `%` character. (e.g. `%1337`)
 - `Indirect` parameters are standalone numbers (or labels, see below). (e.g. `42`)

An instruction that *xor*s the memory value at offset 42 with the number 1337 and stored it in the 12th register could be written:
```
xor  42, %1337, r12    # r12 = mem[pc+42] ^ 1337
```

Instructions can be optionally preceded by **labels**.  
Labels are references to locations in your code. They can be used in parameters to help with offset computation and code readability.  
A label is declared as a colon (`:`) **suffixed** alphanumeric identifier, and referenced with its identifier **prefixed** by a colon.  
An infinite live loop could look like:
```
loop: live %1         # Stay alive
      and  r1, %0, r1 # Set zf = 1 to make sure the next zjmp takes effect
      zjmp %:loop     # Jump back to the start of the loop
```
When compiling this program, `%:loop` is treated as `%-13` (the `live` and the `and` instructions are respectively 5 and 8 bytes long when encoded here)
