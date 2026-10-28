#!/bin/bash

DB="students.txt"
touch "$DB"

while true; do
  echo ""
  echo "===== Student Information System ====="
  echo "1. Add Student"
  echo "2. Display All Records"
  echo "3. Search by Roll Number"
  echo "4. Delete Student"
  echo "5. Exit"
  read -p "Choose an option (1-5): " choice

  case $choice in
    1) read -p "Enter roll number: " roll
       if grep -q "^$roll " "$DB"; then
         echo "Roll number $roll already exists."
       else
         read -p "Enter name: " name
         read -p "Enter marks: " marks
         echo "$roll $name $marks" >> "$DB"
         echo "Student added."
       fi ;;
    2) if [ -s "$DB" ]; then
         echo "Roll Name Marks"
         cat "$DB"
       else
         echo "No records found."
       fi ;;
    3) read -p "Enter roll number to search: " roll
       result=$(grep "^$roll " "$DB")
       if [ -n "$result" ]; then echo "$result"; else echo "Student not found."; fi ;;
    4) read -p "Enter roll number to delete: " roll
       if grep -q "^$roll " "$DB"; then
         grep -v "^$roll " "$DB" > temp.txt && mv temp.txt "$DB"
         echo "Student deleted."
       else
         echo "Student not found."
       fi ;;
    5) echo "Exiting."; exit 0 ;;
    *) echo "Invalid option." ;;
  esac
done

