#!/bin/bash

while true; do
  echo ""
  echo "===== File Management System ====="
  echo "1. Create File"
  echo "2. Delete File"
  echo "3. Rename File"
  echo "4. Copy File"
  echo "5. Move File"
  echo "6. Display File Contents"
  echo "7. Exit"
  read -p "Choose an option (1-7): " choice

  case $choice in
    1) read -p "Enter file name to create: " f
       touch "$f" && echo "File '$f' created." ;;
    2) read -p "Enter file name to delete: " f
       if [ -f "$f" ]; then rm "$f" && echo "File '$f' deleted."; else echo "File not found."; fi ;;
    3) read -p "Enter current file name: " old
       read -p "Enter new file name: " new
       if [ -f "$old" ]; then mv "$old" "$new" && echo "Renamed to '$new'."; else echo "File not found."; fi ;;
    4) read -p "Enter file to copy: " src
       read -p "Enter destination name: " dst
       if [ -f "$src" ]; then cp "$src" "$dst" && echo "Copied to '$dst'."; else echo "File not found."; fi ;;
    5) read -p "Enter file to move: " src
       read -p "Enter destination folder: " dst
       if [ -f "$src" ]; then mv "$src" "$dst" && echo "Moved to '$dst'."; else echo "File not found."; fi ;;
    6) read -p "Enter file name to display: " f
       if [ -f "$f" ]; then cat "$f"; else echo "File not found."; fi ;;
    7) echo "Exiting."; exit 0 ;;
    *) echo "Invalid option." ;;
  esac
done
