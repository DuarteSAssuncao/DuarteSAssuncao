#include "../lib/Auxil.hpp"

void computeBitSubsets(
        const std::vector<Vertex *> set,
        std::vector<std::string> &subsets
) {
    unsigned long long limit = 1 << set.size();
    for (unsigned long long i = 0; i < limit; i++) {
        subsets.push_back("");
        for (unsigned long long j = 0; j < set.size(); j++) {
            if (i & (1 << j))
                subsets[i] += std::to_string(set[j]->getId()) + '-';
        }
    }
}

void computeStringSubsets(
        std::vector<Vertex *> &set,
        std::vector<std::string> &subsets,
        std::string subset,
        unsigned int n) {
    if (n == set.size()) {
        subsets.push_back(subset);
    } else {
        std::string copy1 = subset, copy2 = subset;
        copy1 += '-' + std::to_string(set[n]->getId());
        computeStringSubsets(set, subsets, copy1, n + 1);
        computeStringSubsets(set, subsets, copy2, n + 1);
    }
}

void computeSubsets(
        std::vector<Vertex *> &set,
        std::vector<std::vector<Vertex *>> &subsets,
        std::vector<Vertex *> subset,
        unsigned int n) {
    if (n == set.size())
        subsets.push_back(subset);
    else {
        std::vector<Vertex *> copy1, copy2;
        for (Vertex *v: subset) {
            copy1.push_back(v);
            copy2.push_back(v);
        }
        subset.clear();
        copy1.push_back(set[n]);
        computeSubsets(set, subsets, copy1, n + 1);
        computeSubsets(set, subsets, copy2, n + 1);
    }
}

void triangleInequalityDFS(Vertex *v, std::vector<Vertex *> &path) {
    path.push_back(v);
    for (Edge *e: v->getAdj()) {
        if (e->getDest()->getPath() == e) {
            triangleInequalityDFS(e->getDest(), path);
        }
    }
}

void backtrackDFS(
        Vertex *v,
        size_t i,
        double &min,
        double length,
        Vertex *src,
        std::vector<Vertex *> path,
        std::vector<Vertex *> &minPath) {
    for (Edge *e: v->getAdj()) {
        Vertex *a = e->getDest();
        if (a == src && i == 1 && length + e->getLength() < min) {
            min = length + e->getLength();
            path.push_back(a);
            minPath = path;
        } else if (!a->isVisited() && length + e->getLength() < min) {
            a->setVisited(true);
            path.push_back(a);
            backtrackDFS(a, i - 1, min, length + e->getLength(), src, path, minPath);
            path.pop_back();
            a->setVisited(false);
        }
    }
}
