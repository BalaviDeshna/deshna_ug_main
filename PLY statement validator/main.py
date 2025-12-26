from lexer import lexer
from parser import parser

def display_menu():
    print("\n" + "=" * 60)
    print("Kotlin Validator - Choose what to validate:")
    print("=" * 60)
    print("1. Variable Declaration")
    print("2. Function Declaration")
    print("3. Selection Statement (if/when)")
    print("4. Exit")
    print("=" * 60)

def get_examples(choice):
    examples = {
        '1': [
            "val x: Int = 10",
            "var name: String = \"Deshna\"",
            "val count = 42",
            "var isValid: Boolean = true"
        ],
        '2': [
            "fun greet() { }",
            "fun add(a: Int, b: Int): Int { }",
            "fun calculate(x: Double, y: Double): Double { }",
            "fun process(name: String) { }"
        ],
        '3': [
            "if (x > 5) { }",
            "if (x > 5) { } else { }",
            "when (x) { 1 -> { } else -> { } }",
            "when (status) { true -> { } false -> { } }"
        ]
    }
    return examples.get(choice, [])

print("Kotlin Variable, Function, and Selection Statement Validator")

while True:
    display_menu()
    
    try:
        choice = input("\nEnter your choice (1-4): ").strip()
        
        if choice == '4':
            print("\nValidator terminated.")
            break
        
        if choice not in ['1', '2', '3']:
            print("Invalid choice! Please enter 1, 2, 3, or 4.")
            continue
        
        # Display examples
        examples = get_examples(choice)
        if examples:
            print("\nExamples:")
            for i, example in enumerate(examples, 1):
                print(f"  {i}. {example}")
        
        print("\nEnter your code (or 'back' to return to menu):")
        
        while True:
            data = input("\n> ").strip()
            
            if data.lower() == 'back':
                break
            
            if not data:
                print("Please enter some code.")
                continue
            
            try:
                lexer.input(data)
                parsed = parser.parse(data, debug=False)
                
                if parsed == None:
                    print("✓ Accepted - Valid syntax!")
            
            except Exception as e:
                print(f"✗ Error: {e}")
    
    except EOFError:
        print("\n\nValidator terminated.")
        break
    except KeyboardInterrupt:
        print("\n\nValidator terminated.")
        break