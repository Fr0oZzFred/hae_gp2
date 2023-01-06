#pragma once
#include <vector>
#include <SFML/System.hpp>

struct Node {
	int x, y;
	int cost, heuristic;

	int compareNodeHeuristic(Node n1, Node n2) {
		return n1.heuristic - n2.heuristic;
	};

	int operator < (Node n) {
		compareNodeHeuristic(*this, n);
	};
	int operator > (Node n) {
		compareNodeHeuristic(*this, n);
	};
};

class A_etoile {
public:
	std::vector<Node> area;

    std::vector<Node*> way;

    void reset() {
        way.clear();
        for (auto& n : area) {
            n.cost = 0;
            n.heuristic = 0;
        }
    }

    void nearestWay(sf::Vector2i _start, sf::Vector2i _end) {
        //Init
        std::vector<Node*> closedList;
        reset();
        Node* start = findNode(_start.x, _start.y);
        if(start == nullptr) throw "Start not found";
        way.push_back(start);
        Node* end = findNode(_end.x, _end.y);
        if (end == nullptr) throw "End not found";


        int idx = 0;
        while (!way.empty()) {
            Node* u = way[idx];
            if (u->x == end->x && u->y == end->y) {
                //faire chemin
                return;
            }


            std::vector<Node*> neighbours;
            addNeighbours(u, neighbours);
            for (auto& n : neighbours) {
                if(!findNode(n,closedList) ||
                   !(findNode(n, way) && n.cost < u.cost)) {
                    n.cost = u.cost + 1;
                    n.heuristic = n.cost +
                        n.x * end.x + n.y * end.y;
                    //Il faut passer node en pointer pour qu'il soit commun
                }

                //si non(v existe dans closedLists
                //ou v existe dans openList avec un coût inférieur)
                //v.cout = u.cout + 1
                  //  v.heuristique = v.cout + distance([v.x, v.y], [objectif.x, objectif.y])
            }
        }


    };
    Node* findNode(int x, int y) {
        for (auto& n : area)
            if ((n.x == x) && (n.y == y)) return &n;

        return nullptr;
    };
    Node* findNode(int x, int y, std::vector<Node>& list) {
        for (auto& n : list)
            if ((n.x == x) && (n.y == y)) {
                return &n;
            }

        return false;
    };

    void addNeighbours(Node cur, std::vector<Node>& neighbours) {
        Node u, ur, r, dr, d, dl, l, ul;
        if(findNode(u   , cur.x     , cur.y + -1  )) neighbours.push_back(u );
        if(findNode(ur  , cur.x + 1 , cur.y + -1  )) neighbours.push_back(ur);
        if(findNode(r   , cur.x + 1 , cur.y       )) neighbours.push_back(r );
        if(findNode(dr  , cur.x + 1 , cur.y + 1   )) neighbours.push_back(dr);
        if(findNode(d   , cur.x     , cur.y + 1   )) neighbours.push_back(d );
        if(findNode(dl  , cur.x + -1, cur.y + 1   )) neighbours.push_back(dl);
        if(findNode(l   , cur.x + -1, cur.y       )) neighbours.push_back(l );
        if(findNode(ul  , cur.x + -1, cur.y+ -1   )) neighbours.push_back(ul);
    };


    /*
    Fonction cheminPlusCourt(g:Graphe, objectif : Nœud, depart : Nœud)
        closedLists = File()
        openList = FilePrioritaire(comparateur = compareParHeuristique)
        openList.ajouter(depart)
        tant que openList n'est pas vide
        u = openList.defiler()
        si u.x == objectif.x et u.y == objectif.y
        reconstituerChemin(u)
        terminer le programme
        pour chaque voisin v de u dans g
        si non(v existe dans closedLists
            ou v existe dans openList avec un coût inférieur)
        v.cout = u.cout + 1
        v.heuristique = v.cout + distance([v.x, v.y], [objectif.x, objectif.y])
        openLists.ajouter(v)
        closedLists.ajouter(u)
        terminer le programme(avec erreur)
        */
};