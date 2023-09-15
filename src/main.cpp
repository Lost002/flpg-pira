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
    std::string convert = "curl " + domain + " -s -o data.txt";
    const char * command = convert.c_str();
    std::system(command);
}

void findgames() {
    //std::regex URL("\\b((?:https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:, .;]*[-a-zA-Z0-9+&@#/%=~_|])");
    std::regex URL ("\\b((https?|ftp|file)://[-a-zA-Z0-9+&@#/%?=~_|!:, .;]*[-a-zA-Z0-9+&@#/%=~_|])");
    std::string line, word, url;
    int count;
    for (int i=1; i < 51; i++) {
        count = 0;
        if (i > 1) {
            std::string dom = "https://freelinuxpcgames.com/page/"+std::to_string(i)+"/";
            request(dom);
        } else {
            request("https://freelinuxpcgames.com");
        }
        std::ifstream file("data.txt");
        while (getline(file, line)) {
            if (line.find("nv-post-thumbnail-wrap img-wrap") != std::string::npos) {
                // get only first link in line, 2 useless links are after it (maybe get the thumbnail link to use for GUI.)
                std::stringstream ss(line);
                while (ss >> word) {
                    if (std::regex_search(word, URL)) {
                        url = word;
                        if (url.find("src") != std::string::npos) {;} else if (url.find(".jpg") != std::string::npos) {;} else {
                            if (count%2==0) {    
                                count++;
                                url.erase(0,6);
                                url.erase(url.size() - 1);
                                std::cout << url << "\n\n";
                            }
                        }
                    }
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