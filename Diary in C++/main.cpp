#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <filesystem>
#include <variant>
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;

vector<string> optionsPrimary = {
  "1. Adicionar uma nova anotação",
  "2. Listar todas as anotações",
  "3. Sair"
};

vector <string> optionsListNotes = {
  "1. Listar todas as anotações de um arquivo específico",
  "2. Listar todas as anotações de todos os arquivos"
};

vector<string> optionsAddNotes = {
  "1. Adicionar uma nova anotação em um arquivo existente",
  "2. Escrever em um novo arquivo"
};

const string path = "./annots";
const size_t maxSize = 1024 * 1024;

using vecType = variant<std::function<void()>, std::function<bool()>>;

template <typename T>
void printVector(vector<T> vec) {
  for (T item : vec) {
    cout << item << endl;
  }
}

void exitProgram() {
  cout << "Finalizando..." << endl;
  exit(0);
}

string getOption() {
  string answer;
  cout << "Escolha uma opção: ";
  cin >> answer;
  return answer;
}

template <typename T>
void visitFunc(T& func) {
  string answer = getOption();
  int index = stol(answer) - 1;

  if (index < 0 || index >= func.size()) {
    cout << "Opção inválida" << '\n';
    return;
  }
  
  cout << "\033[2J\033[H";
  std::visit([](auto&& f) { f(); }, func[index]);
}


bool findAnots() {
  bool pathExists = fs::exists(path);

  if (!pathExists) {return false;}

  return true;
}

bool checkSize(string filename) {
  if (fs::file_size(path + "/" + filename + ".txt") > maxSize) {
    cout << "Arquivo muito grande" << '\n';
    return false;
  }
  return true;
}

bool checkFileExist(string fileName) {
  if (!fs::exists(path + "/" + fileName + ".txt")) {
    cout << "Arquivo não encontrado" << '\n';
    return false;
  }
  return true;
}

void getAnot(ofstream& MyFile) {
  if (MyFile.is_open()) {
    string anot;
    cout << "Digite a anotação: ";
    getline(cin, anot);
    MyFile << anot;
    MyFile.close();
    cout << "Anotação adicionada com sucesso!" << '\n' << endl;
    return;
  }
  cout << "Não foi possível abrir o arquivo" << '\n' << endl;
}

void addExistentNote() {
  cout << "Digite o nome do arquivo: ";
  string fileName;
  cin >> fileName;
  cin.ignore(1, '\n');

  bool checkExist = checkFileExist(fileName);
  if (!checkExist) {return;}
  bool size = checkSize(fileName);
  if (!size) {return;}

  ofstream MyFile(path + "/" + fileName + ".txt", ios::app);
  getAnot(MyFile);
}

void addNewNote() {
  cout << "Digite o nome do novo arquivo: ";
  string fileName;
  cin >> fileName;
  cin.ignore(1, '\n');

  ofstream MyFile(path + "/" + fileName + ".txt");
  getAnot(MyFile);
}

using vecType3 = variant<std::function<void()>>;
vector<vecType3> optionsAddNotesFunctions = {
  addExistentNote,
  addNewNote
};

void addNote() {
  bool find = findAnots();
  if (find) {
    printVector(optionsAddNotes);
    visitFunc(optionsAddNotesFunctions);
    return;
  }
  cout << "Pasta de anotações não encontrada" << '\n';
}

bool checkFiles() {
  if (fs::is_empty(path)) {
    cout << "Pasta de anotações vazia" << '\n';
    return false;
  }
  return true;
}


void fileIterator(string fileName) {
  ifstream MyFile(path + "/" + fileName + ".txt");
  if (MyFile.is_open()) {
    string line;
    while (getline(MyFile, line)) {
      cout << line << "\n";
    }
    MyFile.close();
    cout << "==========================" << endl;
  } else {
    cout << "Não foi possível abrir o arquivo";
  }
  cout << '\n';
}

void listNotesAll() {
  bool fileExists = checkFiles();
  if (!fileExists) {return;}

  for (const auto& entry : fs::directory_iterator(path)) {
    string nameFile = entry.path().stem().string();
    cout << nameFile << + ".txt" << endl;
    bool size = checkSize(nameFile);
    if (!size) {break; return;}
    fileIterator(nameFile);
  }
}

void listNotesSpec() {
  bool fileExists = checkFiles();
  if (!fileExists) {return;}
  
  cout << "Digite o nome do arquivo: ";
  string fileName;
  cin >> fileName;
  
bool fileExist = checkFileExist(fileName);
  if (!fileExist) {return;}

  bool size = checkSize(fileName);
  if (!size) {return;}
  
  fileIterator(fileName);
}

using vecType2 = variant<std::function<void()>>;

vector<vecType2> optionsListNotesFunctions = {
  listNotesSpec,
  listNotesAll
};

void listNotes() {
  bool find = findAnots();
  if (find) {
    printVector(optionsListNotes);
    visitFunc(optionsListNotesFunctions);
    

    return;
  }

  cout << "Pasta de anotações não encontrada" << '\n';
}

vector<vecType> optionsPrimaryFunctions = {
  addNote,
  listNotes,
  exitProgram
};


void mainMenu() {
  printVector(optionsPrimary);
  visitFunc(optionsPrimaryFunctions);
  return;
}

int main() {
  while (true) {
  mainMenu();
  }
  return 0;
}
