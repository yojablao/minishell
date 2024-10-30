#!/bin/bash

for file in ./*.c; do
	c_formatter_42 < "$file" > tmp
	cat tmp > "$file"
done
