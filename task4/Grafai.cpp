//Anton Zagzin, 4 grupe, 2 pogrupis, 4 uzdavinis, 7 variantas

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <queue>
#include <map>
#include <list>
#include <sstream>


using namespace std;
const int maxName = 100;
int iterationIndex = 0;


// Graph class represents a directed graph
// using adjacency list representation
class Graph {
public:
    map<int, bool> visited;
    map<int, list<int> > adj;

    // function to add an edge to graph
    void addEdge(int v, int w);

    // DFS traversal of the vertices
    // reachable from v
    bool DFS(int v, int d, ofstream& out, int path[], int& index, string names[], int iteration);
};

void readFromFile(string filename, ofstream& out, string& sender, string& recipient, 
    string names[], stringstream& grapth, Graph& g, int& realNameIndex, int& senderIndex, int& recipientIndex)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "Failo " << filename << " neimanoma atidaryti" << endl;
        out << endl << "TRECIA DALIS. Rezultatai" << endl;
        out << "  1. Programa sekmingai nebaige darbo" << endl;
        cout << "Uzdaroma programa..." << endl;
        exit(0);
    }

    string tmp;
    file >> sender;
    cout << endl << "Siuntejas: " << sender << endl;
    out << "  3. Siuntejas: " << sender << endl;
    getline(file, tmp);

    file >> recipient;
    cout << "Gavejas: " << recipient << endl;
    out << "  4. Gavejas: " << recipient << endl;
    getline(file, tmp);
    getline(file, tmp);
    getline(file, tmp);

    string tempNames[maxName];
    int namesIndex = 0;
    int index = -1;
    char symbols[maxName];
    do
    {
        do
        {
            ++index;
            file >> symbols[index];
        }while (symbols[index] != '-');
        symbols[index] = '\0';
        tempNames[namesIndex] = symbols;
        ++namesIndex;
        file.get(symbols[index]);
        for (int i = 0; i < index; ++i)
        {
            symbols[i] = 0;
        }
        index = -1;

        do
        {
            ++index;
            file.get(symbols[index]);
        } while (symbols[index] != '\n');
        symbols[index] = '\0';
        tempNames[namesIndex] = symbols;
        ++namesIndex;

        for (int i = 0; i < index; ++i)
        {
            symbols[i] = 0;
        }
        index = -1;

        ++index;
        file.get(symbols[index]);
    }while (symbols[index] != '\n');

    realNameIndex = 0;
    bool nameInAList = false;
    int previousNumber = 0;
    for (int i = 0; i < namesIndex; ++i)
    {
        int j = 0;
        for (; j < realNameIndex; ++j)
        {
            if (tempNames[i] == names[j])
            {
                nameInAList = true;
                break;
            }
        }
        if (i % 2 == 0)
        {
            previousNumber = j;
        }
        if (!nameInAList)
        {
            names[realNameIndex] = tempNames[i];
            if (names[realNameIndex] == sender)
            {
                senderIndex = realNameIndex;
            }
            if (names[realNameIndex] == recipient)
            {
                recipientIndex = realNameIndex;
            }
            ++realNameIndex;
        }
        if (i % 2 == 1)
        {
            g.addEdge(previousNumber, j);
        }
        nameInAList = false;
    }
    getline(file, tmp);
    stringstream buffer;
    buffer << file.rdbuf();
    cout << endl << buffer.str() << endl;
    out << endl << buffer.str() << endl;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
    adj[w].push_back(v);
}

bool Graph::DFS(int v, int d, ofstream& out, int path[], int& index, string names[], int iteration)
{
    // Mark the current node as visited and
    // print it
    out << setw(3) << ++iterationIndex << ". ";
    for (int i = 0; i < iteration; ++i)
    {
        out << "-";
    }
    out << names[v] << ". ";
    visited[v] = true;
    path[index] = v;
    ++index;
   // ++depthIndex;
    if (v == d)
    {
        out << "Gavejas " << endl;
        return 1;
    }
    out << "Ne gavejas. ";
    // Recur for all the vertices adjacent
    // to this vertex
    bool visit = false;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
        {
            visit = true;
            out << "Gilyn " << endl;
            
            if (DFS(*i, d, out, path, index, names, iteration+1))
            {
                return 1;
            }
            else
            {
                visit = false;
                
                out << setw(3) << ++iterationIndex << ". ";
                for (int i = 0; i < iteration; ++i)
                {
                    out << "-";
                }
                out << names[v] << ". ";
                //--depthIndex;
            }
        }
    }
    if (!visit)
    {
        --index;
        path[index] = NULL;
        out << "Griztame " << endl;
        visit = false;
    }
    return 0;
}

// Driver code
int main()
{
    Graph g;
    int realNameIndex;
    string sender;
    int senderIndex;
    string recipient;
    int recipientIndex;
    string names[maxName];
    string namesInt[maxName];
    stringstream grapth;
    int path[maxName]{ 0 };
    int index = 0;
    int iteration = 0;
    ofstream file("protokolas.txt");

    system("cls");
    cout << "Anton Zagzin, 4 grupe, 2 pogrupis, 4 uzdavinis, 7 variantas" << endl;
    cout << "Programos tikslas patikrinti ar siuntejas gali gavejui issiusti laiska per pazistamus" << endl;
    cout << "(Grafo realizacija paremta kaimynystes sarasais; naudoti paieskos i gyli metoda)" << endl << endl;

    string data;
    cout << "Iveskite duomenu failo pavadinima: ";
    cin >> data;

    cout << "Pradiniai duomenys:" << endl;

    file << "PIRMA DALIS. Duomenys" << endl << endl;
    file << "  1. Anton Zagzin, 4 grupe, 2 pogrupis, 4 uzdavinis, 7 variantas" << endl;
    file << "  2. Programos tikslas patikrinti ar siuntejas gali gavejui issiusti laiska per pazistamus" << endl;
    file << "     (Grafo realizacija paremta kaimynystes sarasais; naudoti paieskos i gyli metoda)" << endl;


    
    

    readFromFile(data, file, sender, recipient, names, grapth, g, realNameIndex, senderIndex, recipientIndex);

    file << endl << "ANTRA DALIS. Vykdymas" << endl << endl;

    // Create a graph given in the above diagram

    if (g.DFS(senderIndex, recipientIndex, file, path, index, names, iteration))
    {
        file << endl << "TRECIA DALIS. Rezultatai" << endl << endl;
        file << "  1. " << sender << " issiunte laiska gavejui (" << recipient << ") " << endl;
        file << "  2. ";
        cout << endl << sender << " issiunte laiska gavejui (" << recipient << ") " << endl;
        for (int i = 0; i < index; ++i)
        {
            if (path[i] == recipientIndex)
            {
                file << names[path[i]] << endl;
                cout << names[path[i]] << endl;
                break;
            }
            file << names[path[i]] << " -> ";
            cout << names[path[i]] << " -> ";
        }
    }
    else
    {
        file << endl << "TRECIA DALIS. Rezultatai" << endl;
        file << "  1. " << recipient << " negavo laisko" << endl;
        cout << recipient << " negavo laisko" << endl;
    }
    return 0;
}