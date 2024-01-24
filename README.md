# SUMMARY
Haven't implimented a hash table in a while and I don't know if I ever did one in C and I thought maybe it could come in handy
later. I also have a parser implimented and the main will basically parse a file moby dick in the this case and we'll
count all the instances of the words. There's also a vector implimentation for Strings in here so I can get all the words
in the book without having to know the exact size. Will have that up tomorow.

# NOTES
The dynamic vector isn't needed to actually put things into the dictionary you can modify this so that the dictionary can just take a string directly from the file the array is just a nice way of checking that we have the same number of words and that everything is accurate. This process of adding the array should actually slow down the process pretty severley.
And in order to change this you would have to have another add function that takes the location of the start of the original
word from the file and it's size create a new instance of that string using malloc and then memcpy
it the way i did it in the vec add but also you would have to free the word if it already existed.
May due this later but it's not like this is a very serious project don't see a lot of people using this.
Despite all of this parsing Moby Dick and then putting it all into a hashmap/dictionary and counting all the occurances is
relativley fast
