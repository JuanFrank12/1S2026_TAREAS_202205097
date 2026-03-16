#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

enum TipoToken {
    RESERVADA,
    IDENTIFICADOR,
    NUMERO_ENTERO,
    NUMERO_REAL,
    OPERADOR,
    DELIMITADOR,
    DESCONOCIDO
};

struct Token {
    TipoToken tipo;
    string lexema;
    string patron;
};

struct ErrorLexico {
    string lexema;
    string mensaje;
    int linea;
    int columna;
};

bool esReservada(const string& palabra) {
    return palabra == "if" || palabra == "while" || palabra == "for" || palabra == "int" || 
    palabra == "float" || palabra == "return"; }


string tipoATexto(TipoToken tipo) {
    switch (tipo) {
        case RESERVADA:
            return "RESERVADA";
        case IDENTIFICADOR:
            return "IDENTIFICADOR";
        case NUMERO_ENTERO:
            return "NUMERO_ENTERO";
        case NUMERO_REAL:
            return "NUMERO_REAL";
        case OPERADOR:
            return "OPERADOR";
        case DELIMITADOR:
            return "DELIMITADOR";
        default:
            return "DESCONOCIDO";
    }
}

string leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return "";
    }
    stringstream buffer;
    buffer << archivo.rdbuf();
    archivo.close();
    return buffer.str();
}

void imprimirTablaTokens(const vector<Token>& tokens) {
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "TOKEN\t\t\tLEXEMA\t\tPATRON" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < tokens.size(); i++) {
        cout << tipoATexto(tokens[i].tipo) << "\t\t"
             << tokens[i].lexema << "\t\t"
             << tokens[i].patron << endl;
    }
}

void imprimirErrores(const vector<ErrorLexico>& errores) {
    cout << endl;
    cout << "LISTADO DE ERRORES LEXICOS" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    cout << "LEXEMA\t\tDESCRIPCION\t\t\t\tLINEA\tCOLUMNA" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    if (errores.empty()) {
        cout << "No se encontraron errores lexicos." << endl;
        return;
    }
    for (int i = 0; i < errores.size(); i++) {
        cout << errores[i].lexema << "\t\t"
             << errores[i].mensaje << "\t\t"
             << errores[i].linea << "\t"
             << errores[i].columna << endl;
    }
}

int main() {
    string codigo = leerArchivo("entry.txt");
    if (codigo.empty()) {
        cout << "El archivo esta vacio o no se pudo leer." << endl;
        return 1;
    }

    vector<Token> tokens;
    vector<ErrorLexico> errores;
    int i = 0;
    int linea = 1;
    int columna = 1;
    while (i < codigo.length()) {
        char c = codigo[i];
        if (c == ' ' || c == '\t') {
            i++;
            columna++;
            continue;
        }

        if (c == '\n') {
            i++;
            linea++;
            columna = 1;
            continue;
        }

        int lineaInicio = linea;
        int columnaInicio = columna;
        if (isalpha(c) || c == '_') {
            string lexema = "";
            while (i < codigo.length() && (isalnum(codigo[i]) || codigo[i] == '_')) {
                lexema += codigo[i];
                i++;
                columna++;
            }
            if (esReservada(lexema)) {
                tokens.push_back({RESERVADA, lexema, "if|while|for|int|float|return"});
            } else {
                tokens.push_back({IDENTIFICADOR, lexema, "[a-zA-Z_][a-zA-Z0-9_]*"});
            }
            continue;
        }

        if (isdigit(c)) {
            string lexema = "";
            bool esReal = false;
            while (i < codigo.length() && isdigit(codigo[i])) {
                lexema += codigo[i];
                i++;
                columna++;
            }
            if (i < codigo.length() && (isalpha(codigo[i]) || codigo[i] == '_')) {
                while (i < codigo.length() && (isalnum(codigo[i]) || codigo[i] == '_')) {
                    lexema += codigo[i];
                    i++;
                    columna++;
                }
                errores.push_back({
                    lexema,
                    "Identificador invalido: no puede iniciar con numero",
                    lineaInicio,
                    columnaInicio
                });
                continue;
            }

            if (i < codigo.length() && codigo[i] == '.') {
                if (i + 1 < codigo.length() && isdigit(codigo[i + 1])) {
                    esReal = true;
                    lexema += codigo[i];
                    i++;
                    columna++;

                    while (i < codigo.length() && isdigit(codigo[i])) {
                        lexema += codigo[i];
                        i++;
                        columna++;
                    }
                }
            }
            if (esReal) {
                tokens.push_back({NUMERO_REAL, lexema, "[0-9]+\\.[0-9]+"});
            } else {
                tokens.push_back({NUMERO_ENTERO, lexema, "[0-9]+"});
            }
            continue;
        }

        if (i + 1 < codigo.length()) {
            string doble = "";
            doble += codigo[i];
            doble += codigo[i + 1];
            if (doble == "==" || doble == ">=" || doble == "<=" || doble == "!=") {
                tokens.push_back({OPERADOR, doble, "==|>=|<=|!=|>|<|=|\\+|-|\\*|/"});
                i += 2;
                columna += 2;
                continue;
            }
        }

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '>' || c == '<') {
            string lexema = "";
            lexema += c;
            tokens.push_back({OPERADOR, lexema, "==|>=|<=|!=|>|<|=|\\+|-|\\*|/"});
            i++;
            columna++;
            continue;
        }

        if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';') {
            string lexema = "";
            lexema += c;
            tokens.push_back({DELIMITADOR, lexema, "[(){};]"});
            i++;
            columna++;
            continue;
        }

  
        string lexema = "";
        lexema += c;
        errores.push_back({
            lexema,
            "Caracter no valido",
            linea,
            columna
        });
        i++;
        columna++;
    }
    imprimirTablaTokens(tokens);
    imprimirErrores(errores);
    return 0;
}