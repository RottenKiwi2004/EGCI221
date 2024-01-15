from random import randint as rand

# This is used for randomly generate the data array. It is not used in the actual algorithm
numOfDistinctElements = 5000
numOfElements = 200

# The algorithm does not rely on the fact that this array's element are organised like this.
# It is used just for ease of generating a randomised array
selectedMajority = rand(1, numOfDistinctElements)
print(f"Selected Majority: {selectedMajority}")

data = [selectedMajority if rand(0, 2) else rand(1, numOfDistinctElements)
        for _ in range(numOfElements)]

# data = [1, 1, 2, 3, 2]

# Case that guaranteed to have no majority
# selectedMajority = None
# data = [i for i in range(numOfElements)]

# Completely randomised case
# data = [rand(1, numOfDistinctElements) for _ in range(numOfElements)]

# Print the actual array
print(data)


# The real algorithm is inside this function
def findMajority(dataArr: list):

    # There are two cases for picking a subject
    # 1. It is the majority
    # 2. It is NOT the majority

    # Imagine the voting scenario where each person got 1 score
    # Instead of counting how many votes our subject got,
    # we deduct a point from our subject when we find votes that go to others
    # If the number is <= 0, then the chosen subject has not enough potential to be the majority

    # Choose the first element as our subject
    subject = dataArr[0]                        # Assignment: O(1)

    # Currently it is as popular as others
    score = 0                                   # Assignment: O(1)

    n = len(dataArr)                            # len(): O(1) ; Assignment: O(1)
    # Loop through each element in the array
    for i in range(n):                          # Loop for n elements
        # If the vote goes to our subject
        if dataArr[i] == subject:               # Condition: O(1)
            # Our subject gets more popular, and it might be the majority, increase the score
            score += 1                          # Addition: O(1)
        # If the vote goes to someone else
        else:
            # Our subject has more competitor, decrease the score
            score -= 1                          # Subtraction: O(1)

        # If score is 0, that's a tie.
        # Choose the next one to be a new subject because previous one is not as popular as it should be.
        if score == 0 and i != n - 1:           # Condition: O(1)
            subject = dataArr[i + 1]            # Assignment: O(1)

        # So each loop takes O(1)
    # Looping for n elements will take O(n)

    # If the score cancels out, then it is clear that there is no potential subject. Thus, no majority, return None
    if score == 0:                              # Condition: O(1)
        return None                             # Return: O(1)

    # Here we have our potential subject that might be the majority
    # But there are cases that our subject might not be the majority
    # For example: [1, 1, 2, 3, 2] --> Our subject is 2, but it is not the majority

    # So we have to loop over the array to check if the subject is actually the majority

    subjectCount = 0                            # Assignment: O(1)

    for element in dataArr:                     # Loop for n elements

        if subject == element:                  # Condition: O(1)
            subjectCount += 1                   # Assignment: O(1)

        # Each loop takes O(1)

    # Looping for n elements will take O(n)

    # If our potential subject occurs more than half of the size of the array, then it is the majority.
    if subjectCount > n // 2:                   # Condition: O(1)
        return subject                          # Return: O(1)

    # Otherwise, there is no majority in this array
    return None                                 # Return: O(1)

    # Time complexity:  O(n) + O(n) + ( O(1) + O(1) + ... + O(1) ) => O(n)
    #                        ^                      ^
    #                        |                      |
    #                        |    Any other operation outside 2 main loops are lots of O(1) combined which is still O(1)
    #                        |
    #                   2( O(n) ) here from 2 loops


majority = findMajority(data)
print(f"Majority: {majority}")
