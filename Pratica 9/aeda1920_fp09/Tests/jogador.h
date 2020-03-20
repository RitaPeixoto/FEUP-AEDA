#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "aposta.h"
#include <string>

using namespace std;

struct apostaHash
{
	int operator() (const Aposta & ap) const
	{
		return 3;
	}
	
	bool operator() (const Aposta & ap1, const Aposta & ap2) const
	{
	    return ap1==ap2;
	}
};



typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;

class Jogador
{
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm="anonimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/