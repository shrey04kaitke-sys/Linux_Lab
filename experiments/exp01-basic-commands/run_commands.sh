#!/bin/bash
# Runs each command from commands.txt in a scratch folder and saves the results
cd "$(dirname "$0")" || exit 1
WORK=$(mktemp -d)
cd "$WORK" || exit 1
OUT="$OLDPWD/output.txt"
: > "$OUT"
while read -r c; do
  case "$c" in
    clear|history) echo "\$ $c  (not saved: no useful output)" >> "$OUT"; continue ;;
    "man ls") echo "\$ man ls  (first 15 lines)" >> "$OUT"
              MANPAGER=cat man ls 2>/dev/null | head -15 >> "$OUT"
              echo >> "$OUT"; continue ;;
  esac
  echo "\$ $c" >> "$OUT"
  eval "$c" < /dev/null >> "$OUT" 2>&1
  echo >> "$OUT"
done < "$OLDPWD/commands.txt"
cd / && rm -rf "$WORK"
echo "Saved to $OUT"
