
/* Feature: Integer, Fraction, and String Data Types */
int x = -1;  // C-style integer declaration
y = 23;  # Python-style integer declaration

/* Feature: Fractions */
fraction f1 = -1:9;  # Python-like fraction declaration
fraction f2 = 2:4;  /* C-style fraction declaration */

/* Feature: Arrays */
int arr[5] = {1, 2, 3, 4, 5};  // C-style integer array
string strArr[3] = {"one", "two", "three"};  # Python-like string array

/* Feature: Indexing */
int third_element = arr[2];  // Accessing array element
char first_char = strArr[0][0];  // Accessing string character

/* Feature: While Loop - Unified Grammar */
while (x < 5)  # Both C/Python styles supported
{
    x = x + 1;  // Increment
}

/* Feature: For Loop */
for (i = 0; i < 5; i++)  // C-style
    print(arr[i]);

for element in arr:  # Python-style
    print(element)

/* Feature: Do-While Loop */
do {
    x = x - 1;
} while (x > 0);

/* Feature: Selection Statements (if, if-else) */
if (x == 0) {  // C-style if statement
    print("x is zero");
} else {  // C-style else
    print("x is not zero");
}

# Python-style if-else
if x == 0:
    print("x is zero")
else:
    print("x is not zero")

/* Feature: Functions and Recursion */
int factorial(int n) {  // Function declaration with recursion
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

# Python-like comment
factorial(5);  // Function call

/* Feature: Pointers */
int *p;
p = &x;  // Pointer assignment (C-style)
print(*p);  // Dereferencing a pointer


