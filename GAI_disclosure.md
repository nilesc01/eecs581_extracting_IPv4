Generative AI Disclosure
GAI Tool Used: CHAT GPT-5.6 Luna 
Date consulted: September 25-27, 2026
How GAI Was Used: I first provided ChatGPT with the assignment objectives, requirements, restrictions, sample input/output, and required function prototype. I asked for a simple C++ implementation of the `extractIPv4` function.

Prompts:
The initial prompt was `Give me a simple C++ implementation of extractIPv4` followed by a copy of the assignment's problemn description, function prototype, library requirements, other/program requirements listed in the assignment. ChatGPT generated an initial character-by-character implementation of `extractIPv4`. The implementation manually accumulated digits and checked IPv4 octets, port numbers, leading zeros, ranges, and invalid punctuation without using prohibited conversion or regular-expression functions. The program was then compiled using MinGW/g++, specifically using `g++ -Wall -Wextra -std=c++17 ip_extractor.cpp -o ip_extractor.exe` in the command line. The first compilation issue was caused by the function being used before it had been declared. I added the required function prototype before `main()`.

The program was tested using the sample cases provided in the assignment. The program produced the expected results, correctly handling:
* Valid IPv4 addresses.
* IPv4 addresses with ports.
* Invalid leading zeros.
* Ports outside the valid range.
* Incomplete addresses.
* Addresses followed by an invalid period.
* Garbage surrounding a valid address.
* The special case `192a168.1.1.1`, where the valid address `168.1.1.1` is extracted.

Student Modifications
The initial AI-generated `main()` printed only "Valid address found" which did not meet the assignment's required output format. I asked ChatGPT to modify the program to printed the extracted IPv4 address, decimal value, and port.
The final `main()` converts the returned 32-bit address back into its four octets using bit shifting and prints the required format.

Critical Review and Testing
I compared its behavior against the assignment's sample run and checked the output for the required edge cases.

The tested cases included:
* connecting to 192.168.1.1 now
* server=10.0.0.255:8080end
* 192a168.1.1.1
* 192.168.1.1.
* Connection from 192.168.1.1 refused
* 192.168.01.1
* 1.2.3.4:99999
* 12.34.56
* no number here

The results matched the expected behavior specified by the assignment. The program also appropriately terminated when `END` was entered. Additional edge cases were also identified and tested, including maximum valid octets and ports, invalid ports, leading-zero ports, multiple colons, and additional periods.

Verification Statement
I understand the code in the submitted program and reviewed every line of code and I did not use AI output without reviewing it. I compiled and tested the program and confirmed that it produces the required results for the assignment's sample inputs.
At the time of submission, I have not identified any unresolved bugs in the tested sample cases. Additional edge-case testing was performed/identified to further verify the parser's behavior.
