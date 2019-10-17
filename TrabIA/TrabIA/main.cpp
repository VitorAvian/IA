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
	stack<pair<int, int> > s;
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
		#pragma omp parallel for
		for(int i = 0; i<linha; i++){
		#pragma omp parallel for
			for(int j = 0; j<coluna; j++){
				visitados[i][j] = lab[i][j];
			}
		}
	}
	
	void dfsReal(pair<int, int> atual, char **visitados, float custo){
		visitados[atual.first][atual.second] = '-';
		
		if(atual == fim){
			s.push(atual);
			vector<pair<int, int > > aux1;
			stack<pair<int, int> > aux;
			aux = s;
			cout<<"[";
			while(!aux.empty()){
				//cout<<"("<<aux.top().first<<", "<<aux.top().second<<"), ";
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
			cout<<"]"<<custo<<endl;
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
		iniciarVisitados();
		custo = 0;
		dfsReal(ini, visitados, custo);
		
	}
	
	void bfs(){
		iniciarVisitados();
		queue<pair<int, int> > q;
		visitados[ini.first][ini.second] = '-';
		q.push(ini);
		pair<int, int> atual;
		cout<<"[";
		while(!q.empty()){
			atual = q.front();
			cout<<"("<<atual.first<<", "<<atual.second<<")";
			q.pop();
			
			if(atual.first - 1 >= 0 and visitados[atual.first-1][atual.second] != '-'){
				visitados[atual.first-1][atual.second] = '-';
				q.push(make_pair(atual.first-1, atual.second));
			}
			//NL
			if(atual.first - 1 >= 0 and atual.second + 1 < coluna and visitados[atual.first-1][atual.second + 1] != '-'){
				visitados[atual.first-1][atual.second+1] = '-';
				q.push(make_pair(atual.first-1, atual.second+1));
			}
			//L
			if(atual.second + 1 < coluna and visitados[atual.first][atual.second + 1] != '-'){
				visitados[atual.first][atual.second+1] = '-';
				q.push(make_pair(atual.first, atual.second+1));
			}
			//SL
			if(atual.first + 1 < linha and atual.second + 1 < coluna and visitados[atual.first+1][atual.second+1] != '-'){
				visitados[atual.first+1][atual.second+1] = '-';
				q.push(make_pair(atual.first+1, atual.second+1));
			}
			//S
			if(atual.first + 1 < linha and visitados[atual.first+1][atual.second] != '-'){
				visitados[atual.first+1][atual.second] = '-';
				q.push(make_pair(atual.first+1, atual.second));
			}
			//SO
			if(atual.first + 1 < linha and atual.second - 1 >= 0 and visitados[atual.first+1][atual.second-1] != '-'){
				visitados[atual.first+1][atual.second-1] = '-';
				q.push(make_pair(atual.first+1, atual.second-1));
			}
			//O
			if(atual.second - 1 >= 0 and visitados[atual.first][atual.second-1] != '-'){
				visitados[atual.first][atual.second-1] = '-';
				q.push(make_pair(atual.first, atual.second-1));
			}
			//NO
			if(atual.first - 1 >= 0 and atual.second - 1 >= 0 and visitados[atual.first-1][atual.second-1] != '-'){
				visitados[atual.first-1][atual.second-1] = '-';
				q.push(make_pair(atual.first-1, atual.second-1));
			}
		}
		cout<<"]"<<endl;
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
	
	//l.dfs();
	
	l.bfs();
//	l.bff();
//	l.bA();
	
	return 0;
}
