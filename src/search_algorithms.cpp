#include "search_algorithms.hpp"

vector<int> NODES_PER_HEIGHT;

const int SEARCH_ALG_INF = 1e9;
clock_t START, END;
double MAX_TIME_WITHOUT_PRUN = 1 * 60;
double MAX_TIME_WITH_PRUN = 15 * 60;

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

        if (is_goal(curr->state))
            return curr;

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
    of 15 minutes
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

        if (is_goal(curr->state))
            return curr;

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
node* a_star(node *root, int (*h)(state_t*)) {
    NODES_PER_HEIGHT.clear();
    START = clock();

    state_map min_cost;
    priority_queue<pair<int, node*>> pq;

    pq.push({ -h(root->state), root});

    while (!pq.empty()) {
        node *u = pq.top().second; pq.pop();

        if (u->g < min_cost.get_cost(u)) {
            min_cost.insert(u, u->g);

            if (u->h >= NODES_PER_HEIGHT.size())
                NODES_PER_HEIGHT.push_back(1);
            else
                ++NODES_PER_HEIGHT[u->h];

            if (is_goal(u->state))
                return u;

            ruleid_iterator_t my_it;
            init_fwd_iter(&my_it, u->state);
            int rule_id;
            while ((rule_id = next_ruleid(&my_it)) >= 0) {
                node *succ = u->create_succ(rule_id);

                if (h(succ->state) < SEARCH_ALG_INF)
                    pq.push({ -(succ->g + h(succ->state)), succ});
            }
        }
    }

    END = clock();
    return nullptr;
}


// global variables needed for efficient ida_star
state_t *state, *state_cpy;
vector<int> rules;


char PRINT[256];
/*
    ida_star_expansion:

    param:
        bound : maximun value to reach in expansion
        g : cost of the current state
        h : heuristic to use

    return:
        bool representing if a goal was found and an int representing
        the bound of the next iteration

    here we use the efficient implementation of ida_star, using only
    one state and a vector of actions
*/
pair<bool, int> ida_star_expansion(int bound, int g, int (*h)(state_t*)) {
    int hval = h(state);
    int f = g + hval;
    if (f > bound)
        return {false, f};
    if (hval == 0)
        return {true, g};

    if (rules.size() >= NODES_PER_HEIGHT.size())
        NODES_PER_HEIGHT.push_back(1);
    else
        ++NODES_PER_HEIGHT[rules.size()];

    int t = SEARCH_ALG_INF;
    ruleid_iterator_t my_it;
    init_fwd_iter(&my_it, state);
    int rule_id;
    while ((rule_id = next_ruleid(&my_it)) >= 0) {
        copy_state(state_cpy, state);

        int cost = g + get_fwd_rule_cost(rule_id);
        apply_fwd_rule(rule_id, state_cpy, state);

        if (h(state) < SEARCH_ALG_INF) {
            rules.push_back(rule_id);
            auto p = ida_star_expansion(bound, cost, h);
            if (p.first)
                return p;

            t = min(t, p.second);
            rules.pop_back();
        }

        // devolver el cambio hecho por la regla, hay que copiar el estado
        // porque si aplicas una regla a un mismo estado
        copy_state(state_cpy, state);
        apply_bwd_rule(rule_id, state_cpy, state);
    }
    return {false, t};
}

/*
    ida_star:

    param:
        root : pointer to a node
        h : heuristic to use

    return:
        pointer to the goal found and vector of actions taken
*/
pair<state_t*, vector<int>> ida_star(state_t *root, int (*h)(state_t*)) {
    NODES_PER_HEIGHT.clear();

    state_cpy = new state_t;
    state = new state_t;

    int bound = h(state);
    while (bound < SEARCH_ALG_INF) {
        copy_state(state, root);

        auto p = ida_star_expansion(bound, 0, h);
        if (p.first)
            return {state, rules};
        bound = p.second;
        cout << bound << endl;
    }
    return {nullptr, rules};
}

/*
    print_nodes_per_height:

    prints the nodes for each height of the last runned algorithm
*/
void print_nodes_per_height() {
    for (int i = 0; i < NODES_PER_HEIGHT.size(); ++i)
        printf("%d : %d\n", i, NODES_PER_HEIGHT[i]);
}
