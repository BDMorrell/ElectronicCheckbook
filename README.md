# Electronic Checkbook

This project is developing a checkbook program to conform to specific specifications.

The `master` branch should be the stable version, so it's not going to have anything for a while.

All experimental development should be in the `dev` branch. That said, please look at signed tags for stable builds.

## File organization
- `src` should have the base code for the model
- `test` should have test code
- `doc` will eventually have documentation
- `build` will probably be open for building the code, in which case I will `.gitignore` it

## Goals
- Make a working checkbook program.
- Make a system-independent portable application. (Including the build system.)  
  `cmake`
- Keep the code clean!!! Bad code will kill this project [again].  
  `C++`
- Make test code to ensure code quality.  
  CI?
- Design bottom-up. (I already did this twice top-down. Got too complicated.)

### Roadmap
- Make a `csv` file parser
  - Figure out what common programs use, and figure out what would be appropriate for the variable types needed
    - List out what variable types are needed
  - Make it so columns are independent of order
- Create the model
  - Needs to load, 'understand,' and save
- Compute things needed for the UI to display, to try and make the interface trivial to develop (aside from using APIs)
- Start making a UI-independent front-end, making sure to make a good code API

### What was wrong with previous attempts
1. A few attempts were not taken seriously; and quickly fizzled out.
2. Making a web app  
   Using node.js and next.js, I was able to make a user interface. I was planning for future server-client interactions, and mentally and marking which areas should and should not be served using next.js.
    - I did not have enough comments explaining my plans, and so some ideas for the future were forgotten.
    - When it came time to have the client and server communicate, I was planning on using GraphQL, but I was overwhelmed by trying to learn the API.
    - I lost motivation by becomming overwhelmed.
      - I was trying to do things I had no experience in, without an external aid.
      - The prospect of eventually making a server script was not helping.
      - Maybe this could have gone better if I did not rush wanting to see real results, and practice and learn using various tiny test programs.
3. Using Gtkmm  
   I was able to hode-code the layouts. The idea behind this, instead of Glade, was that if I used Glade, I would have a large amount of code just hooking the built UI to the code behind the view.
    - The code was getting messier and messier very quickly. Refactoring seemed like it would be overwhelming by the point I realized that the program can not continue unless it was refactored thoroughly.
      - I should refactor as I go.
    - I may reuse some of the better code from this.

## License
This project (currently) uses the MIT license.
