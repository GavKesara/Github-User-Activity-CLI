Simple C Command line tool to retrive user activity of a User.

**How to Run code **

    - requires libcurl, cJSON, gcc

    - clone repository

    - compile with `gcc main.c -o main -lcurl -lcjson`

    - run program with `./main <username>`
    

Resources needed - [API 4 beginners](https://www.youtube.com/watch?v=WXsD0ZgxjRw)

structure of program 


**1. Input Processing & Lifecycle Setup**

When your application launches:

    Argument Validation: It inspects the arguments passed to it in the terminal to verify a username was provided. If missing, it prints a usage guide and stops.
    
    Networking Initialization: Before making any network calls, the underlying socket/HTTP library (libcurl) must initialize its global state and SSL mechanisms.

**2. Dynamic Memory Buffer Allocation**

Unlike higher-level languages (like Python or JavaScript), C does not automatically expand strings to fit incoming network responses.

    Stream Callbacks: When an HTTP request is made, network data arrives in small chunks/packets.

    Dynamic Expansion: You register a specific function that triggers every time a chunk arrives. This function calculates the size of the incoming chunk, expands a memory buffer dynamically using memory reallocation (realloc), and appends the new bytes to the end of the buffer until the stream finishes.

**3. Constructing & Executing the HTTP Request**

To communicate with GitHub’s servers:

    URL Formatting: The user-supplied username is formatted into the target API endpoint: [https://api.github.com/users/](https://api.github.com/users/)<username>/events.

    Setting Headers: GitHub strictly enforces a User-Agent requirement. You must configure the network handle to send a custom header identifying your program (e.g., User-Agent: My-CLI-App); otherwise, the server rejects the request with a 403 Forbidden error.

    Execution: The library performs the HTTP GET request over an encrypted HTTPS connection and fills the dynamic memory buffer with the raw JSON response text.

**4. Parsing the Structured JSON Payload**

Once the network request finishes, the raw memory buffer contains a serialized JSON string.

    Tree Building: A JSON library (cJSON) reads through the text string, validates its syntax, and constructs an in-memory tree structure (nodes, objects, arrays, and primitive values).

    Array Traversal: GitHub's /events endpoint returns an array of event objects. The program checks that the root element is indeed an array and iterates over each event item up to a desired display limit.

    Key-Value Extraction: For each item, the program inspects specific key names (like "type" and "repo").

**5. Event Classification & Formatting
**
Different user actions return different JSON shapes inside the payload sub-object:

    Push Events: Contain a nested commits array. The program counts the items in that array to output how many commits were pushed.

    Issue / Watch Events: Carry specific action attributes (e.g., "opened" or "starred").

    Output Stream: The parsed information is formatted into human-readable text strings and printed line-by-line to standard output (stdout).

**6. Cleanup & Memory Management**

In C, every resource manually created must be explicitly destroyed:

    JSON Tree Deallocation: The memory allocated for the JSON tree structure is freed.

    HTTP & Network Cleanup: The HTTP handle and header structures are closed, and global networking resources are released.

    Buffer Cleanup: The raw text buffer holding the server response is freed from heap memory to ensure zero memory leaks.