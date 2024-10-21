
def add(a, b):   # Function definition without braces
    return a + b  # No semicolon is needed

result = add(3, 5)  # Function call


def multiply(a, b) {
    return a * b;  // Semicolon used, as it's within braces
}

result = multiply(10, 4);  // Function call with arguments


def greet():
    print("Hello, PyC!")  # Single-line body

greet()  # Function call with no arguments


def factorial(n):
    if n == 1:
        return 1
    else:
        return n * factorial(n - 1)  # Recursive function call

result = factorial(5)


def calculate(a, b):
    sum = a + b
    difference = a - b
    return sum * difference  # Using indentation for multi-line function body

result = calculate(6, 2)



def add(int a, int b) {
    return a + b;   // Function with C-style parameter types
}

result = add(3, 5);  // Function call

def add_fractions(fraction a, fraction b) {
    return (a.num * b.den + b.num * a.den) : (a.den * b.den);  // Return fraction in C-style
}

# frac is a keyword, it means the type fraction
frac  result = add_fractions(1:2, 2:3);  // Call with fraction literals

def increment(pointer int a) {
    *a = *a + 1;  // Use of pointer dereferencing
}

int x = 10;
increment(&x);  // Pass the address of x to increment function

def pointer int get_pointer_to_value(int a) {
    return &a;  // Return the address of a
}

pointer int ptr = get_pointer_to_value(10);  // Call function, return pointer

def fraction add_fractions(fraction a, fraction b) {
    return (a.num * b.den + b.num * a.den) : (a.den * b.den);  // Return type is fraction
}

frac result = add_fractions(1:2, 2:3);  // Call to add_fractions

def void print_message() {
    print("Hello, PyC!")   // No return value
}

print_message();  // Call to void function

def int add(int a, int b) {
    return a + b;   // Function returns an integer
}

int result = add(3, 5);  // Call to add function




