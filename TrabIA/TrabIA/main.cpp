//Vitor Avian 10295392
//Gabriela Chavez 10295440
#include <iostream>
#include <stack>
#include <algorithm>
#include <tuple>
#include <set>
#include <vector>
#include <math.h>
#include <queue>
#include <fstream>
#include <time.h>

using namespace std;

#define INF 0x3f3f3f3f

class Labirinto{
private:
	pair<int, int> ini;
	pair<int, int> fim;
	int linha;
	int coluna;
	float custo;
	int flag;
	int nvisitados;
	ofstream dados;
public:
	char **lab;
	char **visitados;
	char **visual;
	
	void abrirArquivo(){
		dados.open ("dados.csv", ios::app);
	}
	
	void fecharArquivo(){
		dados.close();
	}
	
	void escreverArquivo(double n){
		dados<<n<<",,";
	}
	
	void enterArquivo(){
		dados<<"\n";
	}
	
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
	
	void printVisitados(){
		for(int i = 0; i<linha; i++){
			for(int j = 0; j<coluna; j++){
				cout<<visitados[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	
	void copiarLab(){
		//printVisitados();
		for(int i = 0; i<linha; i++){
			for(int j = 0; j<coluna; j++){
				if(lab[i][j] != '*' and lab[i][j] != '-')
					visual[i][j] = lab[i][j];
				else if(lab[i][j] == '*')
					visual[i][j] = ' ';
				else if(lab[i][j] == '-')
					visual[i][j] = '=';
			}
		}
	}
	
	void visualizar(){
		cout<<endl;
		cout<<"      ";
		cout<<"\x1b[34m";
		for(int i = 0; i<coluna*2+2; i++){
			cout<<"=";
		}
		cout<<endl;
		visual[ini.first][ini.second] = '#';
		visual[fim.first][fim.second] = '$';
		for(int i = 0; i<linha; i++){
			cout<<"      |";
			for(int j = 0; j<coluna; j++){
				if(visual[i][j] == '0'){
					cout<<"\x1b[33m";
					cout<<visual[i][j]<<" ";
				}
				else if(visual[i][j] == '.'){
					cout<<"\033[0;36m";
					cout<<visual[i][j]<<" ";
				}
				else if(visual[i][j] == '#'){
					cout<<"\x1b[32m";
					cout<<visual[i][j]<<" ";
				}
				else if(visual[i][j] == '$'){
					cout<<"\x1b[31m";
					cout<<visual[i][j]<<" ";
				}
				else{
					cout<<"\x1b[0m";
					cout<<visual[i][j]<<" ";
				}
			}
			cout<<"\x1b[34m"<<"|"<<endl;
		}
		cout<<"      ";
		for(int i = 0; i<coluna*2+2; i++){
			cout<<"\x1b[34m"<<"=";
		}
		cout<<"\x1b[0m"<<endl<<endl;
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
		visual[atual.first][atual.second] = '.';
		nvisitados++;
		if(atual == fim){
			flag = 0;
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
			dados<<custo<<","<<nvisitados<<",";
			cout<<endl<<"- Casas visitadas = "<<nvisitados<<endl;
		}
		else{
			//N
			if(atual.first - 1 >= 0 and visitados[atual.first-1][atual.second] != '-' and flag){
				s.push(atual);
				dfsReal(make_pair(atual.first-1, atual.second), visitados, custo + 1);
				s.pop();
			}
			//NL
			if(atual.first - 1 >= 0 and atual.second + 1 < coluna and visitados[atual.first-1][atual.second + 1] != '-' and flag){
				s.push(atual);
				dfsReal(make_pair(atual.first - 1, atual.second + 1), visitados, custo + sqrt(2));
				s.pop();
			}
			//L
			if(atual.second + 1 < coluna and visitados[atual.first][atual.second + 1] != '-' and flag){
				s.push(atual);
				dfsReal(make_pair(atual.first, atual.second + 1), visitados, custo + 1);
				s.pop();
			}
			//SL
			if(atual.first + 1 < linha and atual.second + 1 < coluna and visitados[atual.first+1][atual.second+1] != '-' and flag){
				s.push(atual);
				dfsReal(make_pair(atual.first+1, atual.second+1), visitados, custo + sqrt(2));
				s.pop();
			}
			//S
			if(atual.first + 1 < linha and visitados[atual.first+1][atual.second] != '-' and flag){
				s.push(atual);
				dfsReal(make_pair(atual.first+1, atual.second), visitados, custo + 1);
				s.pop();
			}
			//SO
			if(atual.first + 1 < linha and atual.second - 1 >= 0 and visitados[atual.first+1][atual.second-1] != '-' and flag){
				s.push(atual);
				dfsReal(make_pair(atual.first+1, atual.second-1), visitados, custo + sqrt(2));
				s.pop();
			}
			//O
			if(atual.second - 1 >= 0 and visitados[atual.first][atual.second-1] != '-' and flag){
				s.push(atual);
				dfsReal(make_pair(atual.first, atual.second-1), visitados, custo + 1);
				s.pop();
			}
			//NO
			if(atual.first - 1 >= 0 and atual.second - 1 >= 0 and visitados[atual.first-1][atual.second-1] != '-' and flag){
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
		flag = 1;
		nvisitados = 0;
		dfsReal(ini, visitados, custo);
	}
	
	void bfs(){
		cout<<"BFS:"<<endl;
		iniciarVisitados();
		nvisitados = 0;
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
				visual[atual.first-1][atual.second] = '.';
				nvisitados++;
				caminho[atual.first-1][atual.second] = atual;
				q.push(make_pair(atual.first-1, atual.second));
			}
			//L
			if(atual.second + 1 < coluna and visitados[atual.first][atual.second + 1] != '-'){
				visitados[atual.first][atual.second+1] = '-';
				visual[atual.first][atual.second+1] = '.';
				nvisitados++;
				caminho[atual.first][atual.second+1] = atual;
				q.push(make_pair(atual.first, atual.second+1));
			}
			//S
			if(atual.first + 1 < linha and visitados[atual.first+1][atual.second] != '-'){
				visitados[atual.first+1][atual.second] = '-';
				visual[atual.first+1][atual.second] = '.';
				nvisitados++;
				caminho[atual.first+1][atual.second] = atual;
				q.push(make_pair(atual.first+1, atual.second));
			}
			//O
			if(atual.second - 1 >= 0 and visitados[atual.first][atual.second-1] != '-'){
				visitados[atual.first][atual.second-1] = '-';
				visual[atual.first][atual.second-1] = '.';
				nvisitados++;
				caminho[atual.first][atual.second-1] = atual;
				q.push(make_pair(atual.first, atual.second-1));
			}
			//NL
			if(atual.first - 1 >= 0 and atual.second + 1 < coluna and visitados[atual.first-1][atual.second + 1] != '-'){
				visitados[atual.first-1][atual.second+1] = '-';
				visual[atual.first-1][atual.second+1] = '.';
				nvisitados++;
				caminho[atual.first-1][atual.second+1] = atual;
				q.push(make_pair(atual.first-1, atual.second+1));
			}
			//SL
			if(atual.first + 1 < linha and atual.second + 1 < coluna and visitados[atual.first+1][atual.second+1] != '-'){
				visitados[atual.first+1][atual.second+1] = '-';
				visual[atual.first+1][atual.second+1] = '.';
				nvisitados++;
				caminho[atual.first+1][atual.second+1] = atual;
				q.push(make_pair(atual.first+1, atual.second+1));
			}
			//SO
			if(atual.first + 1 < linha and atual.second - 1 >= 0 and visitados[atual.first+1][atual.second-1] != '-'){
				visitados[atual.first+1][atual.second-1] = '-';
				visual[atual.first+1][atual.second-1] = '.';
				nvisitados++;
				caminho[atual.first+1][atual.second-1] = atual;
				q.push(make_pair(atual.first+1, atual.second-1));
			}
			//NO
			if(atual.first - 1 >= 0 and atual.second - 1 >= 0 and visitados[atual.first-1][atual.second-1] != '-'){
				visitados[atual.first-1][atual.second-1] = '-';
				visual[atual.first-1][atual.second-1] = '.';
				nvisitados++;
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
		cout<<endl<<"- Casas visitadas = "<<nvisitados<<endl;
		dados<<custo<<","<<nvisitados<<",";
	}
	
	void bff(){
		cout<<"BFF:"<<endl;
		iniciarVisitados();
		nvisitados = 0;
		priority_queue<pair<double, pair<int, int> > , vector<pair<double, pair<int, int> > > , greater<pair<double, pair<int, int> > > > pq;
		visitados[ini.first][ini.second] = '-';
		pq.push(make_pair(0, ini));
		pair<double, pair<int, int> > atual;
		pair<double, pair<int,int> > caminho[linha][coluna];
		caminho[ini.first][ini.second] = make_pair(0, make_pair(-1, -1));
		while(!pq.empty()){
			atual = pq.top();
			pq.pop();
			if(atual.second == fim)
				break;
			//N
			if(atual.second.first - 1 >= 0 and visitados[atual.second.first-1][atual.second.second] != '-'){
				visitados[atual.second.first-1][atual.second.second] = '-';
				visual[atual.second.first-1][atual.second.second] = '.';
				nvisitados++;
				atual.first = 1;
				caminho[atual.second.first-1][atual.second.second] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first-1, atual.second.second)));
			}
			//L
			if(atual.second.second + 1 < coluna and visitados[atual.second.first][atual.second.second + 1] != '-'){
				visitados[atual.second.first][atual.second.second+1] = '-';
				visual[atual.second.first][atual.second.second+1] = '.';
				nvisitados++;
				atual.first = 1;
				caminho[atual.second.first][atual.second.second+1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first, atual.second.second+1)));
			}
			//S
			if(atual.second.first + 1 < linha and visitados[atual.second.first+1][atual.second.second] != '-'){
				visitados[atual.second.first+1][atual.second.second] = '-';
				visual[atual.second.first+1][atual.second.second] = '.';
				nvisitados++;
				atual.first = 1;
				caminho[atual.second.first+1][atual.second.second] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first+1, atual.second.second)));
			}
			//O
			if(atual.second.second - 1 >= 0 and visitados[atual.second.first][atual.second.second-1] != '-'){
				visitados[atual.second.first][atual.second.second-1] = '-';
				visual[atual.second.first][atual.second.second-1] = '.';
				nvisitados++;
				atual.first = 1;
				caminho[atual.second.first][atual.second.second-1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first, atual.second.second-1)));
			}
			//NL
			if(atual.second.first - 1 >= 0 and atual.second.second + 1 < coluna and visitados[atual.second.first-1][atual.second.second + 1] != '-'){
				visitados[atual.second.first-1][atual.second.second+1] = '-';
				visual[atual.second.first-1][atual.second.second+1] = '.';
				nvisitados++;
				atual.first = sqrt(2);
				caminho[atual.second.first-1][atual.second.second+1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first-1, atual.second.second+1)));
			}
			//SL
			if(atual.second.first + 1 < linha and atual.second.second + 1 < coluna and visitados[atual.second.first+1][atual.second.second+1] != '-'){
				visitados[atual.second.first+1][atual.second.second+1] = '-';
				visual[atual.second.first+1][atual.second.second+1] = '.';
				nvisitados++;
				atual.first = sqrt(2);
				caminho[atual.second.first+1][atual.second.second+1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first+1, atual.second.second+1)));
			}
			//SO
			if(atual.second.first + 1 < linha and atual.second.second - 1 >= 0 and visitados[atual.second.first+1][atual.second.second-1] != '-'){
				visitados[atual.second.first+1][atual.second.second-1] = '-';
				visual[atual.second.first+1][atual.second.second-1] = '.';
				nvisitados++;
				atual.first = sqrt(2);
				caminho[atual.second.first+1][atual.second.second-1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first+1, atual.second.second-1)));
			}
			//NO
			if(atual.second.first - 1 >= 0 and atual.second.second - 1 >= 0 and visitados[atual.second.first-1][atual.second.second-1] != '-'){
				visitados[atual.second.first-1][atual.second.second-1] = '-';
				visual[atual.second.first-1][atual.second.second-1] = '.';
				nvisitados++;
				atual.first = sqrt(2);
				caminho[atual.second.first-1][atual.second.second-1] = atual;
				pq.push(make_pair(atual.first, make_pair(atual.second.first-1, atual.second.second-1)));
			}
		}
		stack<pair<double, pair<int, int> > > s;
		pair<double, pair<int, int> > aux;
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
		cout<<endl<<"- Casas visitadas = "<<nvisitados<<endl;
		dados<<custo<<","<<nvisitados<<",";
	}
	
	
   /*typedef tuple<double, double, double, pair<int, int> > Tupla;

   void imprimeT(Tupla a)
   {
	   cout << "TUPLE: " << get<0>(a) << " " << get<1>(a) << " " << get<2>(a) << " " << get<3>(a).first << " " << get<3>(a).second << endl;
   }

   void insereValorT(Tupla *t, double f, double g, double h, pair<int, int> p)
   {
	   get<0>(*t) = f;
	   get<1>(*t) = g;
	   get<2>(*t) = h;
	   get<3>(*t) = p;
   }


   void bA(){

	   vector<Tupla> aberta;//na tupla temos, f, g, h e as coordenadas do determinado elemento
	   Tupla  ** labPais; //matriz que armazenará os pesos e os pais de cada elemento
	   labPais = new Tupla *[linha];
	   for(int i = 0; i < linha; i++){
		   labPais[i] = new Tupla [coluna];
		   for(int j = 0; j < coluna; j++)
		   {
			   get<0>(labPais[i][j]) = INF;
			   get<1>(labPais[i][j]) = INF;
			   get<2>(labPais[i][j]) = INF;
			   get<3>(labPais[i][j]) = make_pair(INF, INF);
		   }
	   }
	   iniciarVisitados();

	   //colocando o nó inicial no vector aberta, com f(n) = 0
	   aberta.emplace_back(make_tuple(0.0, 0.0, 0.0, make_pair(ini.first, ini.second)));
	   
	   Tupla objetivo;//tupla auxiliar qeu ajudará a seguir
	   insereValorT(&objetivo, 0.0, 0.0, 0.0, fim);

	   while(!aberta.empty())
	   {
		   //encontrar o nó com f(n)
		   sort(aberta.begin(), aberta.end());
		   Tupla q = aberta[0];
		   aberta.erase(aberta.begin());
		   
		   //associar os filhos com os pais, sendo q o pai
		   double f = get<0>(q);
		   double g = get<1>(q);
		   double h = get<2>(q);
		   int x = get<3>(q).first;
		   int y = get<3>(q).second;
	   
		   double N_f_atual;
		   double NL_f_atual;
		   double L_f_atual;
		   double SL_f_atual;
		   double S_f_atual;
		   double SO_f_atual;
		   double O_f_atual;
		   double NO_f_atual;

		   pair<double, int> f_min = make_pair(INF, 0);

   
		   //primeiro verifica se é possível acessar tal vértice filho.
		   //em seguida, vê-se se a f(n) calculada atualmente é menor que a anterior.
		   //para tal utiliza-se a função heuristica de distância diagonal.
		   //N
   
		   if(x - 1 >= 0 and visitados[x - 1][y] == '*')
		   {
			   int heuristica = max(abs((x - 1) - fim.first), abs(y - fim.second));
			   N_f_atual = (g + 1) + heuristica;
			   if(get<0>(labPais[x - 1][y]) > N_f_atual)
			   {
				   if(f_min.first > N_f_atual)
				   {
					   f_min.first = N_f_atual;
					   f_min.second = 0;
				   }

				   get<0>(labPais[x - 1][y]) = N_f_atual;
				   get<1>(labPais[x - 1][y]) = g + 1; //peso do vértice + o valor do pai acumulado
				   get<2>(labPais[x - 1][y]) = heuristica;
				   get<3>(labPais[x - 1][y]) = make_pair(x, y); //coloca-se que q é pai deste nó
			   }
			   if(visitados[x - 1][y] == visitados[fim.first][fim.second])//checa-se se é o nó procurado ou não
			   {
				   get<0>(objetivo) =  get<0>(labPais[x - 1][y]);
				   get<1>(objetivo) =  get<1>(labPais[x - 1][y]);
				   get<2>(objetivo) =  get<2>(labPais[x - 1][y]);
				   break;
			   }
		   }

		   
		   //NL
		   if(x - 1 >= 0 and y + 1 < coluna and visitados[x - 1][y + 1] == '*')
		   {
			   int heuristica = max(abs((x - 1) - fim.first), abs((y + 1) - fim.second));
			   NL_f_atual = (g + sqrt(2)) + heuristica;
			   if(get<0>(labPais[x - 1][y + 1]) > NL_f_atual)
			   {
				   if(f_min.first > NL_f_atual)
				   {
					   f_min.first = NL_f_atual;
					   f_min.second = 1;
				   }
					 
				   get<0>(labPais[x - 1][y + 1]) = NL_f_atual;
				   get<1>(labPais[x - 1][y + 1]) = g + sqrt(2); //peso do vértice + o valor do pai acumulado
				   get<2>(labPais[x - 1][y + 1]) = heuristica;
				   get<3>(labPais[x - 1][y + 1]) = make_pair(x, y); //coloca-se que q é pai deste nó
			   }
		   
			   if(visitados[x - 1][y + 1] == visitados[fim.first][fim.second])
			   {
				   get<0>(objetivo) =  get<0>(labPais[x - 1][y + 1]);
				   get<1>(objetivo) =  get<1>(labPais[x - 1][y + 1]);
				   get<2>(objetivo) =  get<2>(labPais[x - 1][y + 1]);
				   break;
			   }
		   }

		   //L
		   if(y + 1 < coluna and visitados[x][y + 1] == '*')
		   {
			   int heuristica = max(abs(x - fim.first), abs((y + 1) - fim.second));
			   L_f_atual = (g + 1) + heuristica;
			   if(get<0>(labPais[x][y + 1]) > L_f_atual)
			   {
				   if(f_min.first > L_f_atual)
				   {
					   f_min.first = L_f_atual;
					   f_min.second = 2;
				   }
					 
				   get<0>(labPais[x][y + 1]) = L_f_atual;
				   get<1>(labPais[x][y + 1]) = g + 1; //peso do vértice + o valor do pai acumulado
				   get<2>(labPais[x][y + 1]) = heuristica;
				   get<3>(labPais[x][y + 1]) = make_pair(x, y); //coloca-se que q é pai deste nó
			   }
			   if(visitados[x][y + 1] == visitados[fim.first][fim.second])
			   {
				   get<0>(objetivo) =  get<0>(labPais[x][y + 1]);
				   get<1>(objetivo) =  get<1>(labPais[x][y + 1]);
				   get<2>(objetivo) =  get<2>(labPais[x][y + 1]);
				   break;
			   }
		   }
 

		   //SL
		   if(x + 1 < linha and y + 1 < coluna and visitados[x + 1][y + 1] == '*')
		   {
			   int heuristica = max(abs((x + 1) - fim.first), abs((y + 1) - fim.second));
			   SL_f_atual = (g + sqrt(2)) + heuristica;
			   if(get<0>(labPais[x + 1][y + 1]) > SL_f_atual)
			   {
				   if(f_min.first > SL_f_atual)
				   {
					   f_min.first = SL_f_atual;
					   f_min.second = 3;
				   }
					 
				   get<0>(labPais[x + 1][y + 1]) = SL_f_atual;
				   get<1>(labPais[x + 1][y + 1]) = g + sqrt(2); //peso do vértice + o valor do pai acumulado
				   get<2>(labPais[x + 1][y + 1]) = heuristica;
				   get<3>(labPais[x + 1][y + 1]) = make_pair(x, y); //coloca-se que q é pai deste nó
			   }
			   if(visitados[x + 1][y + 1] == visitados[fim.first][fim.second])
			   {
				   get<0>(objetivo) =  get<0>(labPais[x + 1][y + 1]);
				   get<1>(objetivo) =  get<1>(labPais[x + 1][y + 1]);
				   get<2>(objetivo) =  get<2>(labPais[x + 1][y + 1]);
				   break;
			   }
		   }


		   //S
		   if(x + 1 < linha and visitados[x + 1][y] == '*')
		   {
			   int heuristica = max(abs((x + 1) - fim.first), abs(y - fim.second));
			   S_f_atual = (g + 1) + heuristica;
			   if(get<0>(labPais[x + 1][y]) > S_f_atual)
			   {
				   if(f_min.first > S_f_atual)
				   {
					   f_min.first = S_f_atual;
					   f_min.second = 4;
				   }
					 
				   get<0>(labPais[x + 1][y]) = S_f_atual;
				   get<1>(labPais[x + 1][y]) = g + 1; //peso do vértice + o valor do pai acumulado
				   get<2>(labPais[x + 1][y]) = heuristica;
				   get<3>(labPais[x + 1][y]) = make_pair(x, y); //coloca-se que q é pai deste nó
			   }
			   if(visitados[x + 1][y] == visitados[fim.first][fim.second])
			   {
				   get<0>(objetivo) =  get<0>(labPais[x + 1][y]);
				   get<1>(objetivo) =  get<1>(labPais[x + 1][y]);
				   get<2>(objetivo) =  get<2>(labPais[x + 1][y]);
				   break;
			   }
		   }


		   //SO
		   if(x + 1 < linha and y - 1 >=0 and visitados[x + 1][y - 1] == '*')
		   {
			   int heuristica = max(abs((x + 1) - fim.first), abs((y - 1) - fim.second));
			   SO_f_atual = (g + sqrt(2)) + heuristica;
			   if(get<0>(labPais[x + 1][y - 1]) > SO_f_atual)
			   {
				   if(f_min.first > SO_f_atual)
				   {
					   f_min.first = SO_f_atual;
					   f_min.second = 5;
				   }
					 
				   get<0>(labPais[x + 1][y - 1]) = SO_f_atual;
				   get<1>(labPais[x + 1][y - 1]) = g + sqrt(2); //peso do vértice + o valor do pai acumulado
				   get<2>(labPais[x + 1][y - 1]) = heuristica;
				   get<3>(labPais[x + 1][y - 1]) = make_pair(x, y); //coloca-se que q é pai deste nó
			   }
			   if(visitados[x + 1][y - 1] == visitados[fim.first][fim.second])
			   {
				   get<0>(objetivo) =  get<0>(labPais[x + 1][y - 1]);
				   get<1>(objetivo) =  get<1>(labPais[x + 1][y - 1]);
				   get<2>(objetivo) =  get<2>(labPais[x + 1][y - 1]);
				   break;
			   }

		   }


		   //O
		   if(y - 1 >=0 and visitados[x][y - 1] == '*')
		   {
			   int heuristica = max(abs(x - fim.first), abs((y - 1) - fim.second));
			   O_f_atual = (g + 1) + heuristica;
			   if(get<0>(labPais[x][y - 1]) > O_f_atual)
			   {
				   if(f_min.first > O_f_atual)
				   {
					   f_min.first = O_f_atual;
					   f_min.second = 6;
				   }
					 
				   get<0>(labPais[x][y - 1]) = O_f_atual;
				   get<1>(labPais[x][y - 1]) = g + 1; //peso do vértice + o valor do pai acumulado
				   get<2>(labPais[x][y - 1]) = heuristica;
				   get<3>(labPais[x][y - 1]) = make_pair(x, y); //coloca-se que q é pai deste nó
			   }
			   if(visitados[x][y - 1] == visitados[fim.first][fim.second])
			   {
				   get<0>(objetivo) =  get<0>(labPais[x][y - 1]);
				   get<1>(objetivo) =  get<1>(labPais[x][y - 1]);
				   get<2>(objetivo) =  get<2>(labPais[x][y - 1]);
				   break;
			   }
		   
		   }


		   //NO
		   if(x - 1 >= 0 and y - 1 >= 0 and visitados[x - 1][y - 1] == '*')
		   {
			   int heuristica = max(abs((x - 1) - fim.first), abs((y - 1) - fim.second));
			   NO_f_atual = (g + sqrt(2)) + heuristica;
			   if(get<0>(labPais[x - 1][y - 1]) > NO_f_atual)
			   {
				   if(f_min.first > NO_f_atual)
				   {
					   f_min.first = NO_f_atual;
					   f_min.second = 7;
				   }
					 
				   get<0>(labPais[x - 1][y - 1]) = NO_f_atual;
				   get<1>(labPais[x - 1][y - 1]) = g + sqrt(2); //peso do vértice + o valor do pai acumulado
				   get<2>(labPais[x - 1][y - 1]) = heuristica;
				   get<3>(labPais[x - 1][y - 1]) = make_pair(x, y); //coloca-se que q é pai deste nó
			   }
			   if(visitados[x - 1][y - 1] == visitados[fim.first][fim.second])
			   {
				   get<0>(objetivo) =  get<0>(labPais[x - 1][y - 1]);
				   get<1>(objetivo) =  get<1>(labPais[x - 1][y - 1]);
				   get<2>(objetivo) =  get<2>(labPais[x - 1][y - 1]);
				   break;
			   }
		   }


		   visitados[x][y] = '-'; //marca-se q como visitado
		   
		   if(f_min.second == 0 && x != 0)
			   aberta.emplace_back(make_tuple(get<0>(labPais[x - 1][y]), get<1>(labPais[x - 1][y]), get<2>(labPais[x - 1][y]), get<3>(labPais[x - 1][y])));
		   else if(f_min.second == 1)
			   aberta.emplace_back(make_tuple(get<0>(labPais[x - 1][y + 1]), get<1>(labPais[x - 1][y + 1]), get<2>(labPais[x - 1][y + 1]), get<3>(labPais[x - 1][y + 1])));
		   else if(f_min.second == 2)
			   aberta.emplace_back(make_tuple(get<0>(labPais[x][y + 1]), get<1>(labPais[x][y + 1]), get<2>(labPais[x][y + 1]), get<3>(labPais[x][y + 1])));
		   else if(f_min.second == 3)
			   aberta.emplace_back(make_tuple(get<0>(labPais[x + 1][y + 1]), get<1>(labPais[x + 1][y + 1]), get<2>(labPais[x + 1][y + 1]), get<3>(labPais[x + 1][y + 1])));
		   else if(f_min.second == 4)
			   aberta.emplace_back(make_tuple(get<0>(labPais[x + 1][y]), get<1>(labPais[x + 1][y]), get<2>(labPais[x + 1][y]), get<3>(labPais[x + 1][y])));
		   else if(f_min.second == 5)
			   aberta.emplace_back(make_tuple(get<0>(labPais[x + 1][y - 1]), get<1>(labPais[x + 1][y - 1]), get<2>(labPais[x + 1][y - 1]), get<3>(labPais[x + 1][y - 1])));
		   else if(f_min.second == 6)
			   aberta.emplace_back(make_tuple(get<0>(labPais[x][y - 1]), get<1>(labPais[x][y - 1]), get<2>(labPais[x][y - 1]), get<3>(labPais[x][y - 1])));
		   else if(f_min.second == 7)
			   aberta.emplace_back(make_tuple(get<0>(labPais[x - 1][y - 1]), get<1>(labPais[x - 1][y - 1]), get<2>(labPais[x - 1][y - 1]), get<3>(labPais[x - 1][y - 1])));
		
	   }

   }*/
};


int main(int argc, const char * argv[]) {
	
	clock_t antes;
	clock_t depois;
	double segundos;
	Labirinto l;
	l.abrirArquivo();
	
	l.iniciaLab();
	l.setLab();
	
	//DFS
	cout<<"---------------------------------------------------------------------------------------------------"<<endl;
	l.copiarLab();
	antes = clock();
	l.dfs();
	depois = clock();
	segundos = (double)(depois - antes)/CLOCKS_PER_SEC;
	cout<<endl<<"- Tempo = "<<segundos<<" segundos"<<endl;
	l.escreverArquivo(segundos);
	cout<<endl<<"- Visulização do caminho:"<<endl;
	l.visualizar();
	l.deletarVisitados();
	
	//BFS
	cout<<"---------------------------------------------------------------------------------------------------"<<endl;
	l.copiarLab();
	antes = clock();
	l.bfs();
	depois = clock();
	segundos = (double)(depois - antes)/CLOCKS_PER_SEC;
	cout<<endl<<"- Tempo = "<<segundos<<" segundos"<<endl;
	l.escreverArquivo(segundos);
	cout<<endl<<"- Visulização do caminho:"<<endl;
	l.visualizar();
	l.deletarVisitados();
	
	//BFF
	cout<<"---------------------------------------------------------------------------------------------------"<<endl;
	l.copiarLab();
	antes = clock();
	l.bff();
	depois = clock();
	segundos = (double)(depois - antes)/CLOCKS_PER_SEC;
	cout<<endl<<"- Tempo = "<<segundos<<" segundos"<<endl;
	l.escreverArquivo(segundos);
	l.enterArquivo();
	cout<<endl<<"- Visulização do caminho:"<<endl;
	l.visualizar();
	l.deletarVisitados();
	//l.bA();
	
	l.fecharArquivo();
	l.deletarLab();
	return 0;
}
