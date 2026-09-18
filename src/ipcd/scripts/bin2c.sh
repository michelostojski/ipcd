#!/bin/sh
# bin2c.sh — convert a file to a C array, mimicking `xxd -i`.
#
# Usage: bin2c.sh <symbol-name> <input-file> <output-header>
#
# We can't depend on `xxd` because uClibc/BusyBox toolchains often
# omit it. Pure POSIX shell + od works everywhere.

set -e

if [ $# -ne 3 ]; then
    echo "usage: $0 <symbol> <infile> <outfile>" >&2
    exit 1
fi

SYM=$1
INF=$2
OUT=$3

if [ ! -f "$INF" ]; then
    echo "$0: missing input $INF" >&2
    exit 1
fi

LEN=$(wc -c < "$INF")
LEN=$(echo "$LEN" | tr -d ' ')

# Header + byte stream. od gives us decimal bytes, comma-separated, 16 per line.
{
    echo "/* Auto-generated from $INF — do not edit. */"
    echo "#ifndef WEB_BLOB_${SYM}_H"
    echo "#define WEB_BLOB_${SYM}_H"
    echo "unsigned char ${SYM}[] = {"
    od -v -An -tu1 -w16 "$INF" |
        sed -e 's/^[ \t]*//' \
            -e 's/[ \t]\{1,\}/, /g' \
            -e 's/^/  /' \
            -e 's/$/,/'
    echo "};"
    echo "unsigned int ${SYM}_len = ${LEN};"
    echo "#endif"
} > "$OUT"
