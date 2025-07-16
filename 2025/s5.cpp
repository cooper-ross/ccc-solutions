#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); 
    cin.tie(0);
    
    int num_queries;
    cin >> num_queries;
    
    const int MAX_SIZE = 1000025;
    const int MOD = 1000003;

    vector<long long> tree_begin(4 * MAX_SIZE, INT_MAX);
    vector<long long> tree_time(4 * MAX_SIZE, INT_MIN);
    
    vector<long long> accumulated_values(MAX_SIZE, 0);

    vector<pair<long long, long long>> operation_history;
    
    long long current_answer = 0;
    
    for (int query_idx = 0; query_idx < num_queries; query_idx++) {
        char operation_type;
        cin >> operation_type;
        
        if (operation_type == 'A') {
            long long pos, duration;
            cin >> pos >> duration;
            
            pos = (pos + current_answer - 1 + MOD) % MOD;
            duration = (duration + current_answer) % MOD;
            
            accumulated_values[pos] += duration;
            operation_history.push_back({pos, duration});
            
            long long tree_node = 0;
            long long range_left = 0;
            long long range_right = MAX_SIZE;
            
            while (range_left != range_right) {
                long long range_middle = (range_left + range_right) / 2;
                
                if (pos <= range_middle) {
                    tree_node = tree_node * 2 + 1;
                    range_right = range_middle;
                } else {
                    tree_node = tree_node * 2 + 2;
                    range_left = range_middle + 1;
                }
            }
            
            if (accumulated_values[pos] == 0) {
                tree_begin[tree_node] = INT_MAX;
                tree_time[tree_node] = INT_MIN;
            } else {
                tree_begin[tree_node] = pos;
                tree_time[tree_node] = accumulated_values[pos];
            }
            
            while (tree_node > 0) {
                tree_node = (tree_node - 1) / 2;
                
                long long left_child = tree_node * 2 + 1;
                long long right_child = tree_node * 2 + 2;
                
                long long left_begin = tree_begin[left_child];
                long long left_time = tree_time[left_child];
                long long right_begin = tree_begin[right_child];
                long long right_time = tree_time[right_child];
                
                if (left_begin == INT_MAX) {
                    tree_begin[tree_node] = right_begin;
                    tree_time[tree_node] = right_time;
                } else if (right_begin == INT_MAX) {
                    tree_begin[tree_node] = left_begin;
                    tree_time[tree_node] = left_time;
                } else {
                    tree_begin[tree_node] = max(left_begin + left_time, right_begin) - left_time;
                    tree_time[tree_node] = left_time + right_time;
                }
            }
            
        } else {
            long long removal_index;
            cin >> removal_index;

            removal_index = (removal_index + current_answer - 1) % MOD;

            long long pos = operation_history[removal_index].first;
            long long duration = operation_history[removal_index].second;
            
            accumulated_values[pos] -= duration;
            
            long long tree_node = 0;
            long long range_left = 0;
            long long range_right = MAX_SIZE;
            
            while (range_left != range_right) {
                long long range_middle = (range_left + range_right) / 2;
                
                if (pos <= range_middle) {
                    tree_node = tree_node * 2 + 1;
                    range_right = range_middle;
                } else {
                    tree_node = tree_node * 2 + 2;
                    range_left = range_middle + 1;
                }
            }

            if (accumulated_values[pos] == 0) {
                tree_begin[tree_node] = INT_MAX;
                tree_time[tree_node] = INT_MIN;
            } else {
                tree_begin[tree_node] = pos;
                tree_time[tree_node] = accumulated_values[pos];
            }

            while (tree_node > 0) {
                tree_node = (tree_node - 1) / 2;
                
                long long left_child = tree_node * 2 + 1;
                long long right_child = tree_node * 2 + 2;
                
                long long left_begin = tree_begin[left_child];
                long long left_time = tree_time[left_child];
                long long right_begin = tree_begin[right_child];
                long long right_time = tree_time[right_child];
                
                if (left_begin == INT_MAX) {
                    tree_begin[tree_node] = right_begin;
                    tree_time[tree_node] = right_time;
                } else if (right_begin == INT_MAX) {
                    tree_begin[tree_node] = left_begin;
                    tree_time[tree_node] = left_time;
                } else {
                    tree_begin[tree_node] = max(left_begin + left_time, right_begin) - left_time;
                    tree_time[tree_node] = left_time + right_time;
                }
            }
        }
        
        current_answer = tree_begin[0] + tree_time[0];
        cout << current_answer << "\n";
    }
    
    return 0;
}