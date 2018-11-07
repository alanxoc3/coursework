# netty-rps
A C networked Rock-Paper-Scissors game.

Featuring ASCII ART!!! (thanks to [wynand1004](https://gist.github.com/wynand1004/b5c521ea8392e9c6bfe101b025c39abe)).

## The Protocol
The client sends a single byte (char in c) to the server. This has one of the following codes:
- `0x00` = rock
- `0x01` = paper
- `0x02` = scissors

The server then sends a single byte to the client, but has it packed with some more information:
- `0b00000011` = player 1's rps code (`0b00` = rock, `0b01` = paper, `0b10` = scissors)
- `0b00001100` = player 2's rps code (`0b00` = rock, `0b01` = paper, `0b10` = scissors)
- `0b00110000` = win code (0b00 = lose, 0b01 = win, 0b10 = tie)

## The Demo
[![asciicast](https://asciinema.org/a/Kog4KXJkrj8uTsxNED9hW06MS.png)](https://asciinema.org/a/Kog4KXJkrj8uTsxNED9hW06MS)
