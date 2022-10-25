FILENAME = 'items.txt'

def readFile(FILENAME):
    '''
    Gets the list of lines read in from the file in raw form.
    @param - the filename to read in (must be in same directory as the Source.cpp!)
    @return - the list of lines
    '''
    
    lines = None

    with open(FILENAME) as file:
        lines = file.readlines()
        
       

    return lines


def getInventory():
    '''
    Get the inventory read in from the file.
    '''
    
    # Dictionary of {item : frequency} 
    inventory = {}
    
    items = readFile(FILENAME)

    # Loop through the list of items
    for item in items:
        # Remove the newline character at end of line. 
        item = item.strip() 

        # Update existing frequency; otherwise add item to dictionary
        
        if item in inventory:
             inventory[item] += 1 # accumulate to the dictionary
        else:
             inventory[item] = 1
            
    return inventory
        
   
def determineInventory():
    # Get the inventory
    inventory = getInventory()
    # loop through the dictionary's keys and values
    for key, value in inventory.items():
        
    # print the output
        print (key,':',value)



def determineFrequency(item):
    frequency = 0
    # Get the inventory
    inventory = getInventory()

# Access the item from the inventory
    for key, value in inventory.items():
        if item == key:
            frequency = value

    return  frequency

def output(): 
    # Get the inventory
    inventory = getInventory()

    # loop through the dictionary's keys and values
    file = open("frequency.dat", "w")
    for key, value in inventory.items():
        #write to the frequency.dat file
        output = (key, ': ' ,str(value),'\n')
        file.writelines(output)
    file.close()