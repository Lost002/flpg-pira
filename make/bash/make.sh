if command -v g++ > /dev/null; then
    if test -s "src/"; then
        echo "Nothing to do" #> /dev/null
    elif test -s "bash/"; then
        cd ../
    elif test -f "make.sh"; then
        cd ../../
    elif test -s "main.cpp"; then
        cd ../
    else
        echo "none"
    fi
    g++ src/main.cpp -o main
    touch data
fi