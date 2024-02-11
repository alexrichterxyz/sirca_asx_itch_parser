# High-performance parser for ASX ITCH feed data provided by SIRCA

This is a highly optimized library for parsing ASX ITCH messages provided by SIRCA. The ASX ITCH feed provides traders with a view of the entire market including full order book activity and trades of thousands of assets. The library is written in C++ (17 or higher).

**Some features include**:

- full parsing support for all 14 message types outlined in the [message format specification](asx_itch_message_specification_2015.pdf)
- efficient parsing of timestamps with nanosecond precision
- conversion of hex-string order numbers to 64-bit and 96-bit numeric representations

## Efficiency

The code parses each message (line) sequentially. Bellow is an example of 5 messages. Each message consists comma-separated components.

```
2024-01-04 09:57:24.293086295,D,6c5ae041:00064240,70759,S,IGO,230016
2024-01-04 09:57:24.293992811,Z,70860,4662,7597,52100,56000,49500,5,500,NUF,230017
2024-01-04 09:57:24.293992811,D,6c5ae041:00060344,70860,S,NUF,230018
2024-01-04 09:57:24.295321875,D,6c5ae041:00064300,70915,B,RIO,230019
2024-01-04 09:57:24.295506674,A,6c5ae041:0006430b,70915,B,56,25,1342400,0,2,RIO,230020
```

I make use of numerous optimizations including:

- **pre-parsing functions**: shared message components (e.g. the message type, timestamp, and symbol) can be parsed directly from the message string without having to instantiate a message object.
- **reduced memory allocation**: support for ```std::string_view``` as opposed to ```std::string``` as the data type for messages avoids memory allocation when splitting the comma-separated message components. Preliminary tests have shown this can more than double performance.
- **memory preallocation**: the maximum number of message components is known and can be used to pre-allocate sufficient memory for storing the components of any message type.
- **lazy processing**: message components are only fully parsed once they are needed.



## Example

This example shows how to parse messages from ```sample.csv``` and output the symbol, nanosecond timestamp, price, and quantity of all insertion orders (without participants). 

```cpp
#include <fstream>
#include <iostream>
#include "include/asxitch.hpp"

int main() {
    std::ifstream file("sample.csv");

    if (!file.is_open()) {
        std::cerr << "Could not open the file." << std::endl;
        return 1;
    }

    // string to hold message contents
    std::string message_str;
    
    // loop through each line
    while(std::getline(file, message_str)) { 

        // extract message type before instantiating message object
        const asxitch::message_type_t type = asxitch::get_message_type(message_str);

        // ignore all messages that are not "add orders"
        if(type != asxitch::message_type_t::ADD_ORDER_NO_PARTICIPANT) {
            continue;
        }

        // convert message string to string_view to improve performance 
        const std::string_view message_view(message_str); 

        // create message from string view
        const asxitch::message_add_order_no_participant message(message_view);
        
        // output parsed message payload
        std::cout
        << "Add order for symbol " << message.symbol()
        << " at time " << message.timestamp().count()
        << " at price " << message.price()
        << " with quantity " << message.quantity() << '\n';
        
    }

    file.close();

    return 0;
}
```

## Todos

- add doxygen-style documentation comments
- add tests for all message types
- support for decimal output of the custom ```asxitch::int96_t``` type