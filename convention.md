**This is a convention that all developers of this project must respect. It will make working together easier, more efficient and more consistent.**

- The entire project is in English. Whether it's the git, comments in the code, doxygen or even variable names. The only thing that needs to be in French at the moment is the string.

- Variable name

- Variables names are in camelCase

  - Begin with a lowercase letter

    - Words are in sequence

  - The next words begin with a capital letter

    - Prefix

      - Some variable types must have a prefix. If your variable follows more than one of these instructions, do them all in order.

        - Member variables must begin with the prefix m_

        - function parameters -> in

        - value returned by a function -> out

        - strings, QStrings (and other derivatives) -> s

        - int -> n

        - bool -> b

        - Pointer -> p

        - Vector -> vec

        - Object name (without the q for qt objects)

- The first letter of the first word of a function is capitalized

- For header files, their extensions must be .hpp and not .h

- A .cpp file must not include any file except its own .hpp file. Inclusions are therefore to be made in the .hpp

- A comment at the beginning of each file must be present, containing several versions such as the file creation date, its relative path (to the source repo), its author, its copyright and a summary, 
