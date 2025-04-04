# Spirit 


### Description:
This is a simple text editor made by Katherine and Jayden in C! It won't have many features, but serves as an opportunity to learn about memory management, terminal I/O, among other things.
READ FORMATTING.md BEFORE CONTRIBUTING.

### TBI features: 
- Basic file I/O
- Word search
- Syntax highlighting
- Maybe more? :)

### TD LIST:
- Data structure that holds the strings for the text file we are editing.
- Infrastructure to edit, append to, and read and write to files. 
- Syntax highlighting.
- Hijacking the terminal window using ANSI escape codes. 

### NEXT STEPS:
- Found out the escape codes necessary. Need to move the cursor around. 
- Need to create a buffer that we can store changes to. Could do this by saving the line of the changes, and then writing all at once.
    - Could also only write the changes to the lines we change. Could also also only update the lines we change.
- Find out window size so we know where to set the border to. (TICGWINSZ or whatever)
