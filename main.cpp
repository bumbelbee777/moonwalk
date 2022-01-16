#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;
string replace(std::string subject, const std::string search,
                          const std::string replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}
bool FileExists(string name) {
    ifstream f(name.c_str());
    return f.good();
}
//string addstdlib(string code) {
//    string stdlib = "";
//    if (FileExists("C:/MoonWalk/stdlib.mw")) {
//        ifstream f("C:/MoonWalk/stdlib.mw");
//        string line;
//        while (getline(f, line)) {
//            stdlib += line + "\n";
//        }
//    }
//    return stdlib + code;
//}
bool s(string in, string ot) {
    string first = in.substr(0, ot.size());
    return first == ot;
}
int main(int argc, char const *argv[]) {
    //read from argv[0] and save file contents to string
    string code = "";
    ifstream file;
    file.open(argv[1]);
    if (file.is_open()) {
        while(!file.eof()) {
            string line;
            getline(file, line);
            //remove all spaces before the first character
            for(int i = 0; i < line.size(); i++) {
                if(line[i] == ' ') {
                    line.erase(i, 1);
                    i--;
                } else {
                    break;
                }
            }
            if(line == "imp os") {
                line = "#include <iostream>\n#include <cstdio>\nusing namespace std;";
                code += line + "\n";
                continue;
            }
            //if(line == "imp stdlib") {
            //    line = "";
            //    code = addstdlib(code);
            //}
            line = replace(line, "print", "printf");
            line = replace(line, "input", "scanf");
            line = replace(line, "exec", "system");
            line = replace(line, "str", "string");
            line = replace(line, ".c_string()", ".c_str()");
            line = replace(line, "noret", "void");
            line = replace(line, "yes", "true");
            line = replace(line, "no", "false");
            
            //change "default" in switch statement to "other"
            if(s(line, "other")) {
                line = replace(line, "other", "default");
            }
            //change array initializers {} to [] ONLY if initializing array
            if(s(line, "loop(")) {
                line = replace(line, "loop(", "for(int i = 0; i < ");
                line = replace(line, ")", "; i++)");
            }
            code += line + "\n";
        }
    }
    file.close();
    //output string to file
    ofstream outcpp;
    outcpp.open("out.cpp");
    outcpp << code;
    outcpp.close();
    //compile
    string command = "g++ out.cpp -o out.exe";
    int error = system(command.c_str());
    remove("out.cpp");
    if(error == 9009) {
        if(FileExists("C:/MinGW/bin/g++.exe")) {
            command = "C:/MinGW/bin/g++.exe out.cpp -o out.exe";
            system(command.c_str());
            remove("out.cpp");
        }
        else {
            cout << "g++ not found, outputting .cpp file..." << endl;
            return 0;
        }
    }
}