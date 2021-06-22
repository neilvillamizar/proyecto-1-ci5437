#include "search_algorithms.hpp"
#include "utils.hpp"

vector<int> NODES_PER_HEIGHT;

clock_t START, END;
double MAX_TIME_WITHOUT_PRUN = 1 * 60;
double MAX_TIME_WITH_PRUN = 12 * 60;

/*
    bfs:

    param:
        root = pointer to a node

    return:
        pointer to the goal state or null if the goal wasnt reached

    breadth first search implementation without pruning, limit time
    of 1 minute because it generates a lot of nodes
*/
node* bfs(node *root) {
    NODES_PER_HEIGHT.clear();
    START = clock();

    queue<node*> ord;
    ord.push(root);

    while (!ord.empty()) {
        node *curr = ord.front(); ord.pop();

        if (curr->h >= NODES_PER_HEIGHT.size())
            NODES_PER_HEIGHT.push_back(1);
        else
            ++NODES_PER_HEIGHT[curr->h];

        if (is_goal(curr->state)) {
            END = clock();
            return curr;
        }

        ruleid_iterator_t my_it;
        init_fwd_iter(&my_it, curr->state);
        int rule_id;
        while ((rule_id = next_ruleid(&my_it)) >= 0)
            ord.push(curr->create_succ(rule_id));

        END = clock();
        double current_time = (double)(END - START) / CLOCKS_PER_SEC;
        if (current_time >= MAX_TIME_WITHOUT_PRUN)
            break;
    }
    END = clock();
    return nullptr;
}

/*
    bfs_with_pruning:

    param:
        root = pointer to a node

    return:
        pointer to the goal state or null if the goal wasnt reached

    breadth first search implementation with pruning, limit time
    of 12 minutes
*/
node* bfs_with_pruning(node *root) {
    NODES_PER_HEIGHT.clear();
    START = clock();

    queue<node*> ord;
    ord.push(root);

    state_set visited;
    visited.insert(root);

    while (!ord.empty()) {
        node *curr = ord.front(); ord.pop();

        if (curr->h >= NODES_PER_HEIGHT.size())
            NODES_PER_HEIGHT.push_back(1);
        else
            ++NODES_PER_HEIGHT[curr->h];

        if (is_goal(curr->state)) {
            END = clock();
            return curr;
        }

        ruleid_iterator_t my_it;
        init_fwd_iter(&my_it, curr->state);
        int rule_id;
        while ((rule_id = next_ruleid(&my_it)) >= 0) {
            node *succ = curr->create_succ(rule_id);

            if (!visited.find(succ)) {
                ord.push(succ);
                visited.insert(succ);
            }
            else
                delete succ;
        }

        END = clock();
        double current_time = (double)(END - START) / CLOCKS_PER_SEC;
        if (current_time >= MAX_TIME_WITH_PRUN)
            break;
    }
    END = clock();
    return nullptr;
}

/*
    a_star:

    param:
        root : pointer to a node
        h : heuristic to use in a_star

    return:
        pointer to the goal state or null if the goal wasnt reached


*/
node* a_star(node *root, int (*h)(node*)) {
    NODES_PER_HEIGHT.clear();
    START = clock();

    state_map min_cost;
    priority_queue<pair<int, node*>> pq;

    pq.push({ -h(root), root});

    while (!pq.empty()) {
        node *u = pq.top().second; pq.pop();

        if (u->g < min_cost.get_cost(u)) {
            min_cost.insert(u, u->g);

            if (u->h >= NODES_PER_HEIGHT.size())
                NODES_PER_HEIGHT.push_back(1);
            else
                ++NODES_PER_HEIGHT[u->h];

            if (is_goal(u->state)) {
                END = clock();
                return u;
            }

            ruleid_iterator_t my_it;
            init_fwd_iter(&my_it, u->state);
            int rule_id;
            while ((rule_id = next_ruleid(&my_it)) >= 0) {
                node *succ = u->create_succ(rule_id);

                if (h(succ) < INF())
                    pq.push({ -(succ->g + h(succ)), succ});
            }
        }
    }

    END = clock();
    return nullptr;
}


// global variables for ida*
vector<int> ida_path;
state_set ida_visited;

/*
    ida_star_expansion:

    param:
        bound : int representing the max node cost to expand
        g : current node cost
        h : heuristic
        u : pointer to the current node

    return:
        bool representing if a goal was found and an int representing
        the next bound to iterate on

    efficient implementation of ida_star in memory, only using one node
    and storing the ids of the rules on ida_path
*/
pair<bool, int> ida_star_expansion(int bound, int g, int (*h)(node*), node *u) {
    int hval = h(u);
    int f = g + hval;
    if (f > bound)
        return {false, f};
    if (ida_visited.find(u))
        return {false, INF()};

    if (ida_path.size() >= NODES_PER_HEIGHT.size())
        NODES_PER_HEIGHT.push_back(1);
    else
        ++NODES_PER_HEIGHT[ida_path.size()];

    if (hval == 0)
        return {true, g};

    node *v = new node;
    copy_state(v->state, u->state);
    ida_visited.insert(v);

    int t = INF();
    ruleid_iterator_t my_it;
    init_fwd_iter(&my_it, u->state);
    int rule_id;
    while ((rule_id = next_ruleid(&my_it)) >= 0) {
        int cost = g + get_fwd_rule_cost(rule_id);
        u->apply_fwd(rule_id);

        if (h(u) < INF()) {
            ida_path.push_back(rule_id);
            auto p = ida_star_expansion(bound, cost, h, u);

            if (p.first) {
                ida_visited.erase(v);
                delete v;
                return p;
            }

            t = min(t, p.second);
            ida_path.pop_back();
        }

        u->apply_bwd(rule_id);
    }

    ida_visited.erase(v);
    delete v;
    return {false, t};
}

/*
    ida_star:

    param:
        root : pointer to a node
        h : heuristic

    return:
        pointer to a goal and the vector of rule ids used
*/
pair<node*, vector<int>> ida_star(node *root, int (*h)(node*)) {
    NODES_PER_HEIGHT.clear();
    START = clock();
    node *u = new node;
    int bound = h(root);
    while (bound < INF()) {
        copy_state(u->state, root->state);
        auto p = ida_star_expansion(bound, 0, h, u);
        if (p.first) {
            END = clock();
            return {u, ida_path};
        }
        bound = p.second;
    }
    END = clock();
    return {nullptr, ida_path};
}





/*
    print_nodes_per_height:

    prints the nodes for each height of the last runned algorithm
*/
void print_nodes_per_height() {
    printf("NODOS POR ALTURA:\n");
    for (int i = 0; i < NODES_PER_HEIGHT.size(); ++i)
        printf("%d : %d\n", i, NODES_PER_HEIGHT[i]);
}

/*
    print_time:

    prints the time taken by the last runned algorithm
*/
void print_time() {
    double current_time = (double)(END - START) / CLOCKS_PER_SEC;
    printf("TIEPO TOMADO : %.4lF seg\n", current_time);
}