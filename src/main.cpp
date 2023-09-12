#include <iostream>
#include <fstream>

bool hascurl;
std::string lines[0];

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
    std::string convert = "curl " + domain + " -o data > /dev/null";
    const char * command = convert.c_str();
    std::system(command);
    std::cout << "\n";
}

void findgames() {
    std::string line;
    std::ifstream file("data");
    int count = 0;
    while (getline(file, line)) {
        if (line.find("nv-post-thumbnail-wrap img-wrap") != std::string::npos) {
            lines[count] = line;
            count++;
        }
    }
}

int main() {
    checkcurl();
    if (hascurl) {
        request("https://freelinuxpcgames.com");
    }
    findgames();
    return 0;
}
