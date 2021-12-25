# PCE_xlate_MottekeTamago

This repository holds the information used during the creation of the translation patch
for the PC Engine game MottekeTamago.

## About the Game

### History

This is a pretty fun maze/action game that was nearly released in 1993
by Naxat.  It was apparently complete, but there may have been
hesitation over releasing it as a HuCard or CDROM.  Actually, I don't
know why they didn't release it, because it's a pretty entertaining
game in the style of Bomberman and others, and there were a lot worse
games released in that era.

It was finally released in 1997 as a "free pack-in CDROM" in the
second issue of "Super PC Engine Fan Deluxe" magazine.  Hats off to
Naxat for releasing it under these circumstances, and also for
cooperating with Tokuma Shoten Intermedia (the publisher of "Super
PC Engine Fan Deluxe").

### Overview

You control a cute little duck walking around a maze, collecting eggs
and powerups.  When your eggs hatch, they head for your home, and
bring you points (sometimes bonus points too).  Of course, you can
always disrupt the efforts of the other players, and there are other
perils in the game. 


## About the Repository

This patch was made with direct/raw updates to the binary, rather than using tools to extract
and reinsert, so there aren't a large number of notes which were kept.

However, I realized that the translated manual was not made available at the time of the patch,
so I have included it here in various forms.


## About the Translation

This patch was made with direct/raw updates to the binary, rather than using tools to extract
and reinsert en masse, categorizing each piece.

### Tools Used

SNESTool for IPS
MAKEPPF3 for PPF
TMOD2 with my plug-ins for graphics
Daemon Tools
MagicEngine
Hex editor
Numerous custom utilities 

### Items I had to change

- Uncompressed font (it was ugly)
- Sprites for selection choices on main screen and "press RUN"
- Compressed font
- Compressed sprite for "choose level"
- Explanatory text and bonus scoring areas
- Some other miscellaneous text
- NO EXECUTABLE CODE WAS CHANGED

 
### Text storage

Text was not stored as regular 1-byte ASCII, 1-byte SJIS,
modified character set, or even 2-byte SJIS.  It was instead
stored as 2-byte VRAM references, such as would be copied
directly to the BAT area of VRAM.

It wasn't too terrible though, since one of the bytes was like
an ASCII value, with a modified 1-byte JIS table containing
both hiragana and katakana.  It really helped that I could
find the uncompressed character set, and work backwards from
there.

Another great hint is to use MagicEngine gamesave snapshots in
uncompressed format (not the default setting).  These, together
with a hex editor and the TMOD2 program with PC Engine plug-ins,
helped immensely.


### Compression

The compression scheme employed was a specialized 16-bit
run-length encoding.

For each 8-bytes in the output stream, there is a header byte
and up to 8 payload bytes.  The header byte is a bitmap to show
which of the payload bytes exists, and where to put them.

A '1' bit represents "use the next payload byte here", and a '0'
bit represents "repeat the same byte from 2 bytes ago (ie. 16-bit).

Examples:

input:
```
FF 00 01 02 03 04 05 06 07 - header = FF = 11111111 (use all 8 bytes)
```
output:
```
   00 01 02 03 04 05 06 07
```

input:
```
F0 00 01 02 03             - header = F0 = 11110000 (4 bytes & repeat)
```
output:
```
   00 01 02 03 02 03 02 03
```

input:
```
C4 00 FF          00       - header = C4 = 11000100 (3 bytes)
```
output:
```
   00 FF 00 FF 00 00 00 00
```


### Special things I found - future possible hacks

The level maps can be found at offset 0x36b00 in the data track.
There are 30 levels, one after another, in 16x16 array format,
uncompressed.

This offset is relative to the beginning of the data track, when
viewed as a MODE1/2048-bytes per sector data track (as PC Engine
data tracks should be).

So, anybody can make hacks to change the shape/structure of the
various levels... but I'll leave it to the reader to explore the
various meanings of the bytes in this array. 


## About the Team

The work broke down roughly as follows:

### Game

Hacking: David Shadoff

Major Text Translation: Forrest Richmond

Minor Translation/Edit: David Shadoff

PPF version of patch: NightWolve


### English version of game manual

Translator: Forrest Richmond

Layout: Adam Pavlacka 

#### We all hope that you enjoy the translation.
