#include <iostream>
#include <stack>
#include <vector>
#include <math.h>
#include <queue>
#include <time.h>

using namespace std;

class Labirinto{
private:
	pair<int, int> ini;
	pair<int, int> fim;
	int linha;
	int coluna;
	float custo;
public:
	char **lab;
	char **visitados;
	char **visual;
	
	void setIni(int i, int j){
		ini.first = i;
		ini.second = j;
	}
	
	void setFim(int i, int j){
		fim.first = i;
		fim.second = j;
	}
	
	pair<int, int> getIni(){
		return ini;
	}
	
	pair<int, int> getFim(){
		return fim;
	}
	
	void imprimirIniFim(){
		cout<<ini.first<<" "<<ini.second<<endl;
		cout<<fim.first<<" "<<fim.second<<endl;
	}
	
	void setLinCol(){
		cin>>linha>>coluna;
	}
	
	pair<int, int> getLinCol(){
		pair<int, int> tamanho;
		tamanho.first = linha;
		tamanho.second = coluna;
		return tamanho;
	}
	
	void iniciaLab(){
		setLinCol();
		//cout<<linha<<" "<<coluna;
		lab = new char*[linha];
		for(int i = 0; i<linha; i++){
			lab[i] = new char[coluna];
		}
		visual = new char*[linha];
		for(int i = 0; i<linha; i++){
			visual[i] = new char[coluna];
		}
	}
	
	void deletarLab(){
		for(int i = 0; i<linha; i++){
			delete[] lab[i];
		}
		delete[] lab;
	}
	
	
	void setLab(){
		string s;
		for(int i = 0; i<linha; i++){
			cin>>s;
			for(int j = 0; j<s.size(); j++){
				if(s[j] == '#')
					setIni(i, j);
				if(s[j] == '$')
					setFim(i, j);
				lab[i][j] = s[j];
			}
		}
	}
	
	void copiarLab(){
		for(int i = 0; i<linha; i++){
			for(int j = 0; j<coluna; j++){
				if(lab[i][j] != '*' and lab[i][j] != '-')
					visual[i][j] = lab[i][j];
				else if(lab[i][j] == '*')
					visual[i][j] = '.';
				else if(lab[i][j] == '-')
					visual[i][j] = '=';
			}
		}
	}
	
	void visualizar(){
		cout<<endl;
		cout<<"      ";
		for(int i = 0; i<coluna*2+2; i++){
			cout<<"=";
		}
		cout<<endl;
		visual[ini.first][ini.second] = '#';
		visual[fim.first][fim.second] = '$';
		for(int i = 0; i<linha; i++){
			cout<<"      |";
			for(int j = 0; j<coluna; j++){
				cout<<visual[i][j]<<" ";
			}
			cout<<"|"<<endl;
		}
		cout<<"      ";
		for(int i = 0; i<coluna*2+2; i++){
			cout<<"=";
		}
		cout<<endl<<endl;
	}
	
	void deletarVisualizar(){
		for(int i = 0; i<linha; i++){
			delete[] visual[i];
		}
		delete[] visual;
	}
	
	void printLab(){
		for(int i = 0; i<linha; i++){
			for(int j = 0; j<coluna; j++){
				cout<<lab[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	
	void iniciarVisitados(){
		visitados = new char*[linha];
		for(int i = 0; i<linha; i++){
			visitados[i] = new char[coluna];
		}
		for(int i = 0; i<linha; i++){
			for(int j = 0; j<coluna; j++){
				visitados[i][j] = lab[i][j];
			}
		}
	}
	
	void deletarVisitados(){
		for(int i = 0; i<linha; i++){
			delete[] visitados[i];
		}
		delete[] visitados;
	}
	
	
	stack<pair<int, int> > s;
	void dfsReal(pair<int, int> atual, char **visitados, float custo){
		visitados[atual.first][atual.second] = '-';
		
		if(atual == fim){
			s.push(atual);
			vector<pair<int, int > > aux1;
			stack<pair<int, int> > aux;
			aux = s;
			cout<<"- Caminho encontrado = ";
			cout<<"[";
			while(!aux.empty()){
				aux1.push_back(aux.top());
				aux.pop();
			}
			for(int i = (int)aux1.size()-1; i >= 0; i--){
				visual[aux1[i].first][aux1[i].second] = '0';
				cout<<"("<<aux1[i].first<<", "<<aux1[i].second;
				if(i != 0)
					cout<<"), ";
				else
					cout<<")";
			}
			cout<<"]"<<endl<<endl;
			cout<<"- Custo = "<<custo<<endl;
		}
		else{
			//N
			if(atual.first - 1 >= 0 and visitados[atual.first-1][atual.second] != '-'){
				s.push(atual);
				dfsReal(make_pair(atual.first-1, atual.second), visitados, custo + 1);
				s.pop();
			}
			//NL
			if(atual.first - 1 >= 0 and atual.second + 1 < coluna and visitados[atual.first-1][atual.second + 1] != '-'){
				s.push(atual);
				dfsReal(make_pair(atual.first - 1, atual.second + 1), visitados, custo + sqrt(2));
				s.pop();
			}
			//L
			if(atual.second + 1 < coluna and visitados[atual.first][atual.second + 1] != '-'){
				s.push(atual);
				dfsReal(make_pair(atual.first, atual.second + 1), visitados, custo + 1);
				s.pop();
			}
			//SL
			if(atual.first + 1 < linha and atual.second + 1 < coluna and visitados[atual.first+1][atual.second+1] != '-'){
				s.push(atual);
				dfsReal(make_pair(atual.first+1, atual.second+1), visitados, custo + sqrt(2));
				s.pop();
			}
			//S
			if(atual.first + 1 < linha and visitados[atual.first+1][atual.second] != '-'){
				s.push(atual);
				dfsReal(make_pair(atual.first+1, atual.second), visitados, custo + 1);
				s.pop();
			}
			//SO
			if(atual.first + 1 < linha and atual.second - 1 >= 0 and visitados[atual.first+1][atual.second-1] != '-'){
				s.push(atual);
				dfsReal(make_pair(atual.first+1, atual.second-1), visitados, custo + sqrt(2));
				s.pop();
			}
			//O
			if(atual.second - 1 >= 0 and visitados[atual.first][atual.second-1] != '-'){
				s.push(atual);
				dfsReal(make_pair(atual.first, atual.second-1), visitados, custo + 1);
				s.pop();
			}
			//NO
			if(atual.first - 1 >= 0 and atual.second - 1 >= 0 and visitados[atual.first-1][atual.second-1] != '-'){
				s.push(atual);
				dfsReal(make_pair(atual.first-1, atual.second-1), visitados, custo + sqrt(2));
				s.pop();
			}
		}
	}
	
	void dfs(){
		custo = 0;
		iniciarVisitados();
		cout<<"DFS:"<<endl;
		dfsReal(ini, visitados, custo);
		deletarVisitados();
	}
	
	void bfs(){
		cout<<"BFS:"<<endl;
		iniciarVisitados();
		queue<pair<int, int> > q;
		visitados[ini.first][ini.second] = '-';
		q.push(ini);
		pair<int, int> atual;
		pair<int, int> caminho[linha][coluna];
		caminho[ini.first][ini.second] = make_pair(-1, -1);
		while(!q.empty()){
			atual = q.front();
			q.pop();
			if(atual == fim)
				break;
			//N
			if(atual.first - 1 >= 0 and visitados[atual.first-1][atual.second] != '-'){
				visitados[atual.first-1][atual.second] = '-';
				caminho[atual.first-1][atual.second] = atual;
				q.push(make_pair(atual.first-1, atual.second));
			}
			//L
			if(atual.second + 1 < coluna and visitados[atual.first][atual.second + 1] != '-'){
				visitados[atual.first][atual.second+1] = '-';
				caminho[atual.first][atual.second+1] = atual;
				q.push(make_pair(atual.first, atual.second+1));
			}
			//S
			if(atual.first + 1 < linha and visitados[atual.first+1][atual.second] != '-'){
				visitados[atual.first+1][atual.second] = '-';
				caminho[atual.first+1][atual.second] = atual;
				q.push(make_pair(atual.first+1, atual.second));
			}
			//O
			if(atual.second - 1 >= 0 and visitados[atual.first][atual.second-1] != '-'){
				visitados[atual.first][atual.second-1] = '-';
				caminho[atual.first][atual.second-1] = atual;
				q.push(make_pair(atual.first, atual.second-1));
			}
			//NL
			if(atual.first - 1 >= 0 and atual.second + 1 < coluna and visitados[atual.first-1][atual.second + 1] != '-'){
				visitados[atual.first-1][atual.second+1] = '-';
				caminho[atual.first-1][atual.second+1] = atual;
				q.push(make_pair(atual.first-1, atual.second+1));
			}
			//SL
			if(atual.first + 1 < linha and atual.second + 1 < coluna and visitados[atual.first+1][atual.second+1] != '-'){
				visitados[atual.first+1][atual.second+1] = '-';
				caminho[atual.first+1][atual.second+1] = atual;
				q.push(make_pair(atual.first+1, atual.second+1));
			}
			//SO
			if(atual.first + 1 < linha and atual.second - 1 >= 0 and visitados[atual.first+1][atual.second-1] != '-'){
				visitados[atual.first+1][atual.second-1] = '-';
				caminho[atual.first+1][atual.second-1] = atual;
				q.push(make_pair(atual.first+1, atual.second-1));
			}
			//NO
			if(atual.first - 1 >= 0 and atual.second - 1 >= 0 and visitados[atual.first-1][atual.second-1] != '-'){
				visitados[atual.first-1][atual.second-1] = '-';
				caminho[atual.first-1][atual.second-1] = atual;
				q.push(make_pair(atual.first-1, atual.second-1));
			}
		}
		stack<pair<int, int> > s;
		pair<int, int> aux;
		custo = 0;
		int dif1;
		int dif2;
		s.push(fim);
		dif1 = fim.first - caminho[fim.first][fim.second].first;
		dif2 = fim.second - caminho[fim.first][fim.second].second;
		if(dif1 == 0 || dif2 == 0)
			custo += 1;
		else
			custo += sqrt(2);
		aux = caminho[fim.first][fim.second];
		while(caminho[aux.first][aux.second].first != -1 and caminho[aux.first][aux.second].second != -1){
			s.push(aux);
			
			dif1 = aux.first - caminho[aux.first][aux.second].first;
			dif2 = aux.second - caminho[aux.first][aux.second].second;
			
			if(dif1 == 0 || dif2 == 0)
				custo += 1;
			else
				custo += sqrt(2);
			
			aux = caminho[aux.first][aux.second];
		}
		s.push(ini);
		cout<<"- Caminho encontrado = ";
		cout<<"[";
		while(!s.empty()){
			visual[s.top().first][s.top().second] = '0';
			cout<<"("<<s.top().first<<", "<<s.top().second;
			if(s.size() > 1)
				cout<<"), ";
			else
				cout<<")";
			s.pop();
		}
		cout<<"]"<<endl<<endl;
		cout<<"- Custo = "<<custo<<endl;
		deletarVisitados();
	}
	
	void bff(){
		cout<<"BFF:"<<endl;
		iniciarVisitados();
		priority_queue<pair<double, pair<int, int>> , vector<pair<double, pair<int, int>>> , greater<pair<double, pair<int, int>>>> pq;
		visitados[ini.first][ini.second] = '-';
		pq.push(make_pair(0, ini));
		pair<double, pair<int, int>> atual;
		pair<double, pair<int,int>> caminho[linha][coluna];
		caminho[ini.first][ini.second] = make_pair(0, make_pair(-1, -1));
		while(!pq.empty()){
			atual = pq.top();
			pq.pop();
			if(atual.second == fim)
				break;
			//N
			if(atual.second.first - 1 >= 0 and visitados[atual.second.first-1][atual.second.second] != '-'){
				visitados[atual.second.first-1][atual.second.second] = '-';
				atual.first = 1;
				caminho[atual.second.first-1][atual.second.second] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first-1, atual.second.second)));
			}
			//L
			if(atual.second.second + 1 < coluna and visitados[atual.second.first][atual.second.second + 1] != '-'){
				visitados[atual.second.first][atual.second.second+1] = '-';
				atual.first = 1;
				caminho[atual.second.first][atual.second.second+1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first, atual.second.second+1)));
			}
			//S
			if(atual.second.first + 1 < linha and visitados[atual.second.first+1][atual.second.second] != '-'){
				visitados[atual.second.first+1][atual.second.second] = '-';
				atual.first = 1;
				caminho[atual.second.first+1][atual.second.second] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first+1, atual.second.second)));
			}
			//O
			if(atual.second.second - 1 >= 0 and visitados[atual.second.first][atual.second.second-1] != '-'){
				visitados[atual.second.first][atual.second.second-1] = '-';
				atual.first = 1;
				caminho[atual.second.first][atual.second.second-1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first, atual.second.second-1)));
			}
			//NL
			if(atual.second.first - 1 >= 0 and atual.second.second + 1 < coluna and visitados[atual.second.first-1][atual.second.second + 1] != '-'){
				visitados[atual.second.first-1][atual.second.second+1] = '-';
				atual.first = sqrt(2);
				caminho[atual.second.first-1][atual.second.second+1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first-1, atual.second.second+1)));
			}
			//SL
			if(atual.second.first + 1 < linha and atual.second.second + 1 < coluna and visitados[atual.second.first+1][atual.second.second+1] != '-'){
				visitados[atual.second.first+1][atual.second.second+1] = '-';
				atual.first = sqrt(2);
				caminho[atual.second.first+1][atual.second.second+1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first+1, atual.second.second+1)));
			}
			//SO
			if(atual.second.first + 1 < linha and atual.second.second - 1 >= 0 and visitados[atual.second.first+1][atual.second.second-1] != '-'){
				visitados[atual.second.first+1][atual.second.second-1] = '-';
				atual.first = sqrt(2);
				caminho[atual.second.first+1][atual.second.second-1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first+1, atual.second.second-1)));
			}
			//NO
			if(atual.second.first - 1 >= 0 and atual.second.second - 1 >= 0 and visitados[atual.second.first-1][atual.second.second-1] != '-'){
				visitados[atual.second.first-1][atual.second.second-1] = '-';
				atual.first = sqrt(2);
				caminho[atual.second.first-1][atual.second.second-1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first-1, atual.second.second-1)));
			}
		}
		stack<pair<double, pair<int, int> > > s;
		pair<double, pair<int, int>> aux;
		custo = 0;
		int dif1;
		int dif2;
		dif1 = fim.first - caminho[fim.first][fim.second].second.first;
		dif2 = fim.second - caminho[fim.first][fim.second].second.second;
		if(dif1 == 0 || dif2 == 0){
			s.push(make_pair(1, fim));
			custo+=1;
		}
		else{
			s.push(make_pair(sqrt(2), fim));
			custo+=sqrt(2);
		}
		aux = caminho[fim.first][fim.second];
		while(caminho[aux.second.first][aux.second.second].second.first != -1 and caminho[aux.second.first][aux.second.second].second.second != -1){
			s.push(aux);
			aux = caminho[aux.second.first][aux.second.second];
			custo+=aux.first;
		}
		s.push(make_pair(aux.first, ini));
		cout<<"- Caminho encontrado = ";
		cout<<"[";
		while(!s.empty()){
			visual[s.top().second.first][s.top().second.second] = '0';
			cout<<"("<<s.top().second.first<<", "<<s.top().second.second;
			if(s.size() > 1)
				cout<<"), ";
			else
				cout<<")";
			s.pop();
		}
		cout<<"]"<<endl<<endl;
		cout<<"- Custo = "<<custo<<endl;
		deletarVisitados();
	}
	
	void bA(){
		
	}
	
};


int main(int argc, const char * argv[]) {
	
	clock_t antes;
	clock_t depois;
	double segundos;
	Labirinto l;
	
	l.iniciaLab();
	l.setLab();
	
	cout<<"---------------------------------------------------------------------------------------------------"<<endl;
	l.copiarLab();
	//l.printLab();
	antes = clock();
	l.dfs();
	depois = clock();
	segundos = (double)(depois - antes)/CLOCKS_PER_SEC;
	cout<<endl<<"- Tempo = "<<segundos<<" segundos"<<endl;
	cout<<endl<<"- Visulização do caminho:"<<endl;
	l.visualizar();
	cout<<"---------------------------------------------------------------------------------------------------"<<endl;
	l.copiarLab();
	antes = clock();
	l.bfs();
	depois = clock();
	segundos = (double)(depois - antes)/CLOCKS_PER_SEC;
	cout<<endl<<"- Tempo = "<<segundos<<" segundos"<<endl;
	cout<<endl<<"- Visulização do caminho:"<<endl;
	l.visualizar();
	cout<<"---------------------------------------------------------------------------------------------------"<<endl;
	l.copiarLab();
	antes = clock();
	l.bff();
	depois = clock();
	segundos = (double)(depois - antes)/CLOCKS_PER_SEC;
	cout<<endl<<"- Tempo = "<<segundos<<" segundos"<<endl;
	cout<<endl<<"- Visulização do caminho:"<<endl;
	l.visualizar();
//	l.bA();
	
	
	l.deletarLab();
	return 0;
}
