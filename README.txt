Montrer /mɔ̃tʀe/
===============

Montrer — from the French verb “montrer”, meaning “to show” or “to uncover”

Montrer parses documents written in a defined, lightweight markup format which
renders into a sequence of static HTML documents, interconnected via hyperlinks.

This results in a fast, dependency-free presentation system that enables addition
of adding basic slideshow functionality without the issues of traditional
slideshow software. It aims to introduce clarity, portability and efficiency.

Anyone can use Montrer as long as you can write a text file.

NOTICE
======

Until further releases, please add an extra newline at the end of the file to
ensure the last line is read completely. This is caused by the two-pointer
logic I used to parse the file.

Usage
=====

Compile the source using GNU Make
make

Test out the program by either using `presentation.txt` or write your own
presentation in the correct format. Pass the file name into the program:
`montrer presentation.txt`

Open the generated Slide_1.html in a browser of your preference.

Please note that the parser will parse any file. I generally use a .txt extension
until further plans are made.

The format
==========

Hereby, I provide the general guidelines for the markdown definition that
we use:

- Each slide and its heading is followed by a line containing ONLY '=' signs.
- Each sub-heading is followed by a line containing ONLY '-' signs.
- Each newline is assumed to be a list item (bound to change in future revisions)

Setext much?
------------

This resembles closely to the setext markup but it doesn't adhere to all its
guidelines (the project is new), which made me not mention it as a setext parser.
And it doesn't aim to parse setext. It just happens to have a similar format.
Later revisions might see a deviation either far or closer from/to the setext
markup format.

Project Milestones
==================

This is the general outline for the project -- unless I get bored with it. Then,
I might do it later. You can also edit the code to your liking as long as you
adhere to the terms in the LICENSE

[x] Simple parsing into HTML
[ ] Custom template engine to parse directly into a premade template file
[ ] Custom parser to parse into an abstract tree to then generate the
    required files.
[ ] List and Text differentiation
[ ] Videos and Image support
