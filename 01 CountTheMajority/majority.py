from random import randint as rand

# This is used for randomly generate the data array and it is not used in the actual algorithm
numOfDistinctElements = 5000
numOfElements = 200

# The algorithm does not rely on the fact that this array's element are organised like this.
# It is used just for ease of generating a randomised array
selectedMajority = rand(1, numOfDistinctElements)
print(f"Selected Majority: {selectedMajority}")

data = [selectedMajority if rand(0, 2) else rand(1, numOfDistinctElements)
        for _ in range(numOfElements)]

# Case that guaranteed to has no majority
# selectedMajority = None
# data = [i for i in range(numOfElements)]

# Completely randomised case
# data = [rand(1, numOfDistinctElements) for _ in range(numOfElements)]

# Print the actual array
print(data)


# The real algorithm is inside this function
def findMajority(dataArr: list):

    # There are two cases for picking a pivot
    # 1. It is the majority
    # 2. It is NOT the majority

    # Imagine the voting scenario where each person got 1 score
    # Instead of counting how many votes our pivot got, we count how much our pivot got more than all others combined
    # If the number is <= 0, then the chosen pivot is not our majority
    # The nice thing about this approach is that if we iterate through the array, at any given point we will be able to
    # tell if the pivot is or is not our majority by just checking the number.

    # Choose the first element as our pivot
    pivot = dataArr[0]                          # Assignment: O(1)

    # Currently it is as popular as others
    score = 0                                   # Assignment: O(1)

    n = len(dataArr)                            # len(): O(1) ; Assignment: O(1)
    # Loop through each element in the array
    for i in range(n):                          # Loop for n elements
        d = dataArr[i]                          # Assignment: O(1)
        # If the vote goes to our pivot
        if d == pivot:                          # Condition: O(1)
            # Our pivot gets more popular, and it might be the majority, increase the score
            score += 1                          # Addition: O(1)
        # If the vote goes to someone else
        else:
            # Our pivot has more competitor, decrease the score
            score -= 1                          # Subtraction: O(1)

        # If score is 0, that's a tie.
        # Choose the next one to be a new pivot because last one is not as popular as it should be.
        if score == 0 and i != n - 1:           # Condition: O(1)
            pivot = dataArr[i + 1]              # Assignment: O(1)

        # So each loop takes O(1)
    # Looping for n elements will take O(n)

    if score == 0:                              # Condition: O(1)
        return None                             # Return: O(1)

    return pivot                                # Return: O(1)

    # Time complexity: O(n) + O(1) => O(n)


majority = findMajority(data)
print(f"Majority: {majority}")
print(f"Correct answer? {majority == selectedMajority}")  # Only for
