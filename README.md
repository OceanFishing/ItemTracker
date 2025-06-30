# ItemTracker

## Project Goals
This application serves as a grocery item tracker that takes in an input file text file with individual named items on each line; from this file, the program generates a backup log and allows the user to interact with a basic menu in order to view the item frequency data. The menu options allow for the user to search and view a specific item's amount, the amount's of all item entries, or the full list but with the frequency represented as a histogram. The program also includes basic user validation.

## Project Positives
My functions were effectively made to be small and modular. I am happy with how I could easily reuse my code in multiple scenarios. 

## Areas for Improvement
I believe believe that I could have accounted for different iterations of similar strings inputted by users. I accounted for different user inputted case types for the first letter alone; however, beyond this, items with varying casing on the characters are treated like different entities.

## Project Challenges
Finding ways to correctly encapsulate the information that I wanted for easy implementation was the most difficult aspect. Originally, I designed the program to have an 'Item' class where I would then assign individual item objects to a map held within main where I could access. This became problematic in implementation, and I had to take the time to refactor my class to be a more general 'ItemList' class.

## Skills Learned
I became much more comfortable with OOP design and working with maps in C++. Prior to this, I mainly worked with Python and Java, and this was a great oppurtunity to test similar skills in a different language. 

## Project Design
My code was made with a modular and incremental approach. I wanted all my functions to be insertable and transferrable all throughout my code from my print functions to my class fuctions. For this reason, multiple helper functions were made to specifically work with data formatting.
