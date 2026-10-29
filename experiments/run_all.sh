#!/bin/bash
# Compiles each .cpp, runs each program, saves results to output.txt in each folder
cd ~/linux-lab/experiments || exit 1
rm -f exp03-shell-scripting/students.txt
for dir in exp*/; do
  cd "$dir" || continue
  for src in *.cpp; do
    [ -f "$src" ] && g++ -std=c++17 -Wall -pthread "$src" -o "${src%.cpp}"
  done
  : > output.txt
  for prog in *; do
    [ -f "$prog" ] && [ -x "$prog" ] || continue
    if [[ "$prog" == *.sh ]]; then
      input="${prog%.sh}.input"; [ -f "$input" ] || input=/dev/null
      echo "===== $prog =====" >> output.txt
      ./"$prog" < "$input" >> output.txt 2>&1
    elif [[ "$prog" != *.* ]]; then
      echo "===== $prog =====" >> output.txt
      ./"$prog" < /dev/null >> output.txt 2>&1
    else
      continue
    fi
    echo >> output.txt
  done
  cd ..
done
echo "Done. Each experiment folder now has output.txt"
