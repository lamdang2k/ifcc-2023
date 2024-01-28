if [ $# -eq 0 ]; then
    python3 ./tests/ifcc-test.py ./tests/testfiles
    exit 1
fi

python3 ./tests/ifcc-test.py "$@"

