#include <iostream>
#include <fstream>


bool hascurl;

void checkcurl() {
    std::string stdout;
    std::string stdoutline;
    std::system("which curl > /dev/null > .stdout");
    std::ifstream stdoutfile(".stdout");
    while (getline(stdoutfile, stdoutline)) {
        stdout += stdoutline;
    }
    if (stdout == "/usr/bin/curl") {
        hascurl = true;
    } else {
        hascurl = false;
    }
    stdoutfile.close();
    stdout.clear();
    stdoutline.clear();
}

void request(std::string domain) { //Domain should be freelinuxpcgames.com
    std::string convert = "curl " + domain + " -o data";
    const char * command = convert.c_str();
    std::system(command);
}


int main() {
    checkcurl();
    if (hascurl) {
        request("http://example.com");
    }
    return 0;
}