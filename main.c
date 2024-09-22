#include <iostream>
#include <fstream>
#include <regex>
#include <windows.h>

using namespace std;
 
BOOL isFileExists(const string &path) {
    DWORD dwAttr = GetFileAttributes((LPCSTR) path.c_str());
    if (dwAttr == 0xFFFFFFFF) return false;
    return true;
}
 
int main() {
    cout << "===GFE Pass by ez4y2f===" << endl;
 
    string appjs = R"(C:\Program Files\NVIDIA Corporation\NVIDIA GeForce Experience\www\app.js)";
 
    cout << "Trying to find app.js in " << appjs << endl;
 
    while(!isFileExists(appjs)) {
        cout << "Cannot find app.js." << endl << "Please drag app.js in (install dir)\\www>_";
        getline(cin, appjs);
    }
 
    ifstream inFile;
    inFile.open(appjs);
 
    istreambuf_iterator<char> fileBegin(inFile);
    istreambuf_iterator<char> fileEnd;
 
    smatch res;
 
    string rawjs(fileBegin, fileEnd);
 
    inFile.close();
    regex regMatch(R"("choose"===\w\.nvActiveAuthView[\D]*\)\})");
 
    if(!regex_search(rawjs, res, regMatch)) {
        cout << "Failed" << endl;
        system("pause > nul");
        return 0;
    }
 
    rawjs = regex_replace(rawjs, regMatch, R"("choose"===this.nvActiveAuthView)};this.handleLoggedIn({sessionToken:"",userToken:"",user: {core:{displayName:"GFE",primaryEmailVerified: true}}});)");
 
    ofstream outFile;
    outFile.open(appjs, ios::out);
    if(!outFile) {
        cout << "Failed when write file, maybe no permission." << endl;
        system("pause > nul");
        return 0;
    }
    outFile << rawjs;
    outFile.close();
    cout << "Succeed" << endl;
 
    system("pause > nul");
 
    return 0;
}
