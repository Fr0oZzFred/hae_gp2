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
            Node* u = way[idx++];
            if (u->x == end->x && u->y == end->y) {
                //faire chemin
                return;
            }


            std::vector<Node*> neighbours;
            addNeighbours(u, neighbours);
            for (auto& n : neighbours) {
                if (n == nullptr) continue;
                if((findNode(n,closedList) == nullptr) ||
                   ((findNode(n, way) == nullptr) && (n->cost < u->cost))) {
                    n->cost = u->cost + 1;
                    n->heuristic = n->cost +
                        n->x * end->x + n->y * end->y;
                    way.push_back(n);
                }
            }
            closedList.push_back(u);
        }
        throw "A* -> Not Found";
    };
    Node* findNode(int x, int y) {
        for (auto& n : area)
            if ((n.x == x) && (n.y == y)) return &n;

        return nullptr;
    };
    Node* findNode(int x, int y, std::vector<Node*>& list) {
        for (auto& n : list)
            if ((n->x == x) && (n->y == y))
                return n;

        return nullptr;
    }; 
    Node* findNode(Node* cur, std::vector<Node*>& list) {
        for (auto& n : list)
            if (n == cur)
                return n;

        return nullptr;
    };

    void addNeighbours(Node* cur, std::vector<Node*>& neighbours) {
        neighbours.push_back(findNode(cur->x     , cur->y + -1  ));
        neighbours.push_back(findNode(cur->x + 1 , cur->y + -1  ));
        neighbours.push_back(findNode(cur->x + 1 , cur->y       ));
        neighbours.push_back(findNode(cur->x + 1 , cur->y + 1   ));
        neighbours.push_back(findNode(cur->x     , cur->y + 1   ));
        neighbours.push_back(findNode(cur->x + -1, cur->y + 1   ));
        neighbours.push_back(findNode(cur->x + -1, cur->y       ));
        neighbours.push_back(findNode(cur->x + -1, cur->y+ -1   ));
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