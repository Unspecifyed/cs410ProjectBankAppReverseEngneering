import os
import subprocess
import re

# Define the directory containing the .o files
directory = "."

# Output file to store the results
output_file = "local_functions_disassembly_and_strings.txt"

# Function to run objdump and disassemble the given object file
def disassemble_function_objdump(obj_file):
    # Run objdump to disassemble the entire object file
    command = ["objdump", "-d", obj_file]
    
    # Run objdump with the commands
    result = subprocess.run(command, capture_output=True, text=True)

    return result.stdout

# Function to extract strings from the object file
def extract_strings(obj_file):
    # Run strings command to extract strings from the object file
    command = ["strings", "-t", "d", obj_file]  # "-t d" option prints offset
    result = subprocess.run(command, capture_output=True, text=True)

    # Parse and return the strings with their offsets
    strings = result.stdout.splitlines()
    return [line.split(maxsplit=1) for line in strings if len(line.split()) > 1]

# Function to find which function a string belongs to based on address
def find_function_for_string(string_offset, disassembly):
    # Find all functions and their start addresses in the disassembly
    functions = re.findall(r'([0-9a-f]+)\s+<(.+)>:', disassembly)
    
    # Convert string offset to hex for comparison with disassembly addresses
    string_offset_hex = hex(int(string_offset))
    
    # Iterate through the functions and check where the string's address fits
    for i, (address, func_name) in enumerate(functions):
        if i < len(functions) - 1:
            # Compare with the next function's start address
            next_address = functions[i + 1][0]
            if address <= string_offset_hex < next_address:
                return func_name
        else:
            # If it's the last function, it belongs here
            if address <= string_offset_hex:
                return func_name
    return None

# Open the output file for writing
with open(output_file, "w") as outfile:
    outfile.write("Local Functions, Their Full Disassembly, and Strings from Object Files:\n\n")

    # Iterate through all files in the directory
    for filename in os.listdir(directory):
        # Process only .o files
        if filename.endswith(".o"):
            # Run the nm command to list symbols in the object file
            command = ["nm", "--defined-only", filename]
            result = subprocess.run(command, capture_output=True, text=True)

            # Split the output into lines
            lines = result.stdout.splitlines()

            # Filter local/static functions (symbol type 't')
            local_functions = [line for line in lines if " t " in line]

            # If there are local functions, process them with objdump
            if local_functions:
                outfile.write(f"File: {filename}\n")
                
                # Disassemble the entire object file using objdump
                disassembly = disassemble_function_objdump(filename)

                # Write the full disassembly to the output file
                outfile.write(f"{disassembly}\n")
                
                # Extract strings from the object file
                strings = extract_strings(filename)

                # Match each string to a function based on its offset
                outfile.write("Strings and the Functions they belong to:\n")
                for string_offset, string_value in strings:
                    func_name = find_function_for_string(string_offset, disassembly)
                    if func_name:
                        outfile.write(f"String '{string_value}' (offset {string_offset}) belongs to function {func_name}\n")
                    else:
                        outfile.write(f"String '{string_value}' (offset {string_offset}) could not be matched to a function\n")
                outfile.write("\n")

print(f"Disassembled functions and strings have been written to {output_file}")