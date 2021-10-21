import re
import string

def AllItems(): #function to count the number of times each item appears in an imported list
    produceSet = set() # empty set to eliminate duplicates
    print("\nAll items purchased:\n") #outputs "All items purchased"
    produceList = open('CS210_Project_Three_Input_File.txt') #opens file with list of produce items
    frequency = open('frequency.dat.txt', 'w') #opens files to write data results into
    contents = produceList.read() # get's the contents of the imported list in string format 
    produceItems = contents.split() # seperates words 

    for word in produceItems: # loop to count each item
        count = produceItems.count(word) #counts the number of times each item appears in the list
        itemFrequency = (word + ":" + str(count)) #outputs item and count
        produceSet.add(itemFrequency) # add produce items to set
    for word in produceSet: # iterates through each item in the set
        print(word) #output each item
        frequency.write(word) #writes data to file
        frequency.write("\n") #newline
    produceList.close() # closes file
    frequency.close() # closes file
    print ("\n") # new line before menu displays again

def UserItem(userItem): #function to allow user to choose an item 
    produceList = open('CS210_Project_Three_Input_File.txt') #opens file with list of produce items
    contents = produceList.read() # get's the contents of the imported list in string format 
    count = contents.count(userItem) #counts the number of times the users item choice is in the dictionary
    produceList.close() # closes file
    return count; #returns number of times item was purchased

def Histogram(): #function to produce histogram of the number of times each item appears in an imported list
    
    i = 0 #variable for iterating through while loop
    histogramChar = '*' #variable for histogram character

    print("\nHistogram of items purchased:\n") #outputs "Histogram of items purchased"
    frequencyList = open('frequency.dat.txt') #opens file with list of produce items
    contents = frequencyList.read() # get's the contents of the imported list in string format 
    produceItems = contents.split() # seperates words 

    for word in produceItems: # loop to count each item
        splitItem = word.split(':') # splits items apart from frequency
        item = splitItem[0] # gets the item name only
        frequency = int(splitItem[1]) #gets the number of times the item was purchased
        print(item.rjust(12), (histogramChar * frequency).ljust(15)) #prints histogram 
        
    frequencyList.close() # closes file
