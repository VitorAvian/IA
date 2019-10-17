#include <iostream>
#include <stack>
#include <vector>
#include <math.h>
#include <queue>

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
		lab = new char*[linha];
		for(int i = 0; i<linha; i++){
			lab[i] = new char[coluna];
		}
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
			cout<<"Caminho encontrado = ";
			cout<<"[";
			while(!aux.empty()){
				aux1.push_back(aux.top());
				aux.pop();
			}
			for(int i = (int)aux1.size()-1; i >= 0; i--){
				cout<<"("<<aux1[i].first<<", "<<aux1[i].second;
				if(i != 0)
					cout<<"), ";
				else
					cout<<")";
			}
			cout<<"]"<<endl;
			cout<<"Custo = "<<custo<<endl;
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
		/*for(int i = 0; i<linha; i++){
			for(int j= 0; j<coluna;j++){
				cout<<caminho[i][j].first<<" "<<caminho[i][j].second<<"|";
			}
			cout<<endl;
		}*/
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
		cout<<"Caminho encontrado = ";
		cout<<"[";
		while(!s.empty()){
			cout<<"("<<s.top().first<<", "<<s.top().second;
			if(s.size() > 1)
				cout<<"), ";
			else
				cout<<")";
			s.pop();
		}
		cout<<"]"<<endl;
		cout<<"Custo = "<<custo<<endl;
		deletarVisitados();
	}
	
	void bff(){
		
	}
	
	void bA(){
		
	}
	
};


int main(int argc, const char * argv[]) {
	
	Labirinto l;
	
	l.iniciaLab();
	l.setLab();
	//l.printLab();
	
	cout<<"------------------------------------------------------------------------------------------"<<endl;
	l.dfs();
	cout<<"------------------------------------------------------------------------------------------"<<endl;
	l.bfs();
	cout<<"------------------------------------------------------------------------------------------"<<endl;
//	l.bff();
//	l.bA();
	
	return 0;
}
