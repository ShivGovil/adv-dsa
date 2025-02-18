#!/bin/bash

# Loop through all directories in the current directory
for dir in */; do
    # Remove trailing slash from directory name
    dir_name=${dir%/}
    
    # Skip if not a directory
    if [ ! -d "$dir_name" ]; then
        continue
    fi
    
    # Create .hpp file path
    hpp_file="$dir_name/$dir_name.hpp"
    # Create main.cpp file path
    cpp_file="$dir_name/main.cpp"
    
    # Check if .hpp file doesn't exist, then create it
    if [ ! -f "$hpp_file" ]; then
        cat > "$hpp_file" << EOL
#ifndef ${dir_name}_HPP
#define ${dir_name}_HPP

class ${dir_name} {
    public:
        ${dir_name}();
        ~${dir_name}();
    
    private:
        // Add private members here
};

#endif // ${dir_name}_HPP
EOL
        echo "Created $hpp_file"
    else
        echo "$hpp_file already exists, skipping..."
    fi
    
    # Check if main.cpp doesn't exist, then create it
    if [ ! -f "$cpp_file" ]; then
        cat > "$cpp_file" << EOL
#include "${dir_name}.hpp"
#include <iostream>

int main() {
    // Add your code here
    return 0;
}
EOL
        echo "Created $cpp_file"
    else
        echo "$cpp_file already exists, skipping..."
    fi
done
