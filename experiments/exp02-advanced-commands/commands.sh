#!/bin/bash
echo "\$ find . -name '*.txt'"; find . -name "*.txt"
echo "\$ grep -rn 'Linux' ."; grep -rn "Linux" .
echo "\$ sed 's/Linux/Ubuntu/' file.txt"; sed 's/Linux/Ubuntu/' file.txt
echo "\$ awk '{print \$1, \$3}' student.txt"; awk '{print $1, $3}' student.txt
echo "\$ cut -d ',' -f1 student.csv"; cut -d "," -f1 student.csv
echo "\$ paste -d ',' file1.txt file2.txt"; paste -d "," file1.txt file2.txt
echo "\$ sort -k2 student.txt"; sort -k2 student.txt
echo "\$ uniq -c fruits.txt"; uniq -c fruits.txt
echo "\$ echo 'linux' | tr 'a-z' 'A-Z'"; echo "linux" | tr 'a-z' 'A-Z'
echo "\$ echo 'Linux123' | tr -d '0-9'"; echo "Linux123" | tr -d '0-9'
echo "\$ ls -l perm_test.txt"; ls -l perm_test.txt
echo "\$ tar -tzf backup.tar.gz"; tar -tzf backup.tar.gz
echo "\$ ss -tuln"; ss -tuln
echo "\$ journalctl -n 5"; journalctl -n 5 2>&1
echo "\$ dmesg | head -5"; dmesg 2>&1 | head -5
