#include <iostream>
#include <fstream>
#include <regex>
#include <bits/stdc++.h>

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
    std::string convert = "curl " + domain + " -o data.txt";
    const char * command = convert.c_str();
    std::system(command);
}

void findgames() {
    std::regex URL("\\b((?:https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:, .;]*[-a-zA-Z0-9+&@#/%=~_|])");
    std::string line, word, url;
    for (int i=1; i < 51; i++) {
        if (i > 1) {
            std::string dom = "https://freelinuxpcgames.com/page/"+std::to_string(i)+"/";
            request(dom);
        } else {
            request("https://freelinuxpcgames.com");
        }
        std::ifstream file("data.txt");
        while (getline(file, line)) {
            //Do somthing like line.find(somthing in like (nv post thumbnail)) so it doesnt get every image link and it should also go through faster but REGEX for link IS working.
            std::stringstream ss(line);
            while (ss >> word) {
                if (std::regex_match(word, URL)) {
                    url = word;
                    std::cout << url << "\n";
                }
            }
        }
    }
}
int main() {
    checkcurl();
    if (hascurl) {
        request("https://freelinuxpcgames.com");
    } else {
        std::cout << "You system does not have curl installed.";
        return 3;
    }
    findgames();
    return 0;
}