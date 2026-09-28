#include <iostream>
#include <string>
#include <cctype>

using namespace std; // Use the standard namespace to avoid prefixing standard library names with "std::"

bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort)
{
    outAddress = 0; // Initialize the output address to 0
    outPort = -1; // Initialize the output port to -1 (indicating no port found)

    for (size_t i = 0; i < str.length(); i++) // Loop through each character in the input string
    { 
        if (!isdigit(str[i])) // If the character is not a digit, skip to the next character
            continue; // Start of a potential IPv4 address

        size_t start = i; // Remember the starting index of the potential IPv4 address
        int octets[4]; // Array to hold the four octets of the IPv4 address
        bool valid = true; // Flag to indicate if the current candidate is a valid IPv4 address

        for (int octet = 0; octet < 4; octet++) // Loop through each of the four octets
        {
            if (i >= str.length() || !isdigit(str[i])) // If the character is not a digit, the candidate is invalid
            {
                valid = false; 
                break; 
            }

            if (str[i] == '0' && i + 1 < str.length() && isdigit(str[i + 1])) // If the octet starts with a leading 0 and is followed by another digit, it's invalid
            {
                valid = false; 
                break; 
            }

            int value = 0; // Variable to hold the numeric value of the current octet
            int digits = 0; // Variable to count the number of digits in the current octet

            while (i < str.length() && isdigit(str[i])) // While the character is a digit, build the numeric value of the octet
            {
                value = value * 10 + (str[i] - '0'); // Convert the character to its numeric value and add it to the current value
                digits++; // Increment the digit count
                i++; // Move to the next character

                if (digits > 3) // If there are more than 3 digits in the octet, it's invalid
                {
                    valid = false; 
                    break; 
                }
            }

            if (!valid || value > 255) // If the octet is invalid or its value is greater than 255, the candidate is invalid
            {
                valid = false;
                break;
            }

            octets[octet] = value; // Store the valid octet value in the array
 
            if (octet < 3) // If this is not the last octet, expect a dot separator
            {
                if (i >= str.length() || str[i] != '.') // If the next character is not a dot, the candidate is invalid
                {
                    valid = false;
                    break;
                }

                i++;
            }
        }

        if (!valid) // If the candidate is invalid, reset the index to the start of the candidate and continue searching
        {
            i = start;
            continue;
        }

        if (i < str.length() && str[i] == '.') // If there is an extra dot after the last octet, the candidate is invalid
        {
            i = start;
            continue;
        }

        int port = -1; // Initialize the port to -1 (indicating no port found)

        if (i < str.length() && str[i] == ':')  // If there is a colon, attempt to parse the port number
        {
            i++; // Move past the colon

            if (i >= str.length() || !isdigit(str[i])) // If there is no digit after the colon, the candidate is invalid
            {
                i = start; // Reset the index to the start of the candidate and continue searching
                continue;
            }

            if (str[i] == '0' && i + 1 < str.length() && isdigit(str[i + 1])) // If the port starts with a leading 0 and is followed by another digit, it's invalid
            {
                i = start; // Reset the index to the start of the candidate and continue searching
                continue;
            }

            port = 0; // Initialize the port value to 0
            int digits = 0; // Variable to count the number of digits in the port number

            while (i < str.length() && isdigit(str[i])) // While the character is a digit, build the numeric value of the port
            {
                port = port * 10 + (str[i] - '0'); // Convert the character to its numeric value and add it to the current port value
                digits++; // Increment the digit count
                i++; // Move to the next character

                if (digits > 5) // If there are more than 5 digits in the port number, it's invalid
                    break;
            }

            if (digits > 5 || port > 65535) // If the port number has more than 5 digits or is greater than 65535, the candidate is invalid
            {
                i = start; // Reset the index to the start of the candidate and
                continue;
            }

            if (i < str.length() && str[i] == ':') // If there is an extra colon after the port number, the candidate is invalid
            {
                i = start;
                continue;
            }
        }

        if (i < str.length() && (str[i] == '.' || str[i] == ':')) // If there is an extra dot or colon after the last octet or port number, the candidate is invalid
        {
            i = start;
            continue;
        }

        // Build the 32-bit decimal IPv4 value.
        outAddress = 
            ((unsigned long)octets[0] << 24) | 
            ((unsigned long)octets[1] << 16) |
            ((unsigned long)octets[2] << 8) |
            (unsigned long)octets[3];

        outPort = port; // Set the output port value
        return true;
    }

    return false;
}

int main()
{
    string input; // Variable to hold the user input

    while (true)
    {
        cout << "Enter a string (or 'END' to quit): "; 
        getline(cin, input); // Read a line of input from the user

        if (input == "END")  // If the user enters "END", terminate the program
        {
            cout << "Program terminated." << endl;
            break;
        }

        unsigned long address;
        int port;

        if (extractIPv4(input, address, port)) // If a valid IPv4 address is found
        {   // Extract the individual octets from the 32-bit decimal value
            unsigned long a = (address >> 24) & 255;
            unsigned long b = (address >> 16) & 255; 
            unsigned long c = (address >> 8) & 255;
            unsigned long d = address & 255;

            cout << "Extracted IPv4 address: " // Display the extracted IPv4 address
                 << a << "." << b << "." << c << "." << d
                 << " (decimal value: " << address
                 << ", port: ";

            if (port == -1) // If no port was found, display "none"
                cout << "none";
            else
                cout << port;

            cout << ")" << endl; 
        }
        else
        {
            cout << "Invalid input: no valid IPv4 address found" << endl;
        }
    }

    return 0;
}
