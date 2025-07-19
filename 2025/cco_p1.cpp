#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long M;
    cin >> N >> M;
    
    vector<pair<long long, long long>> chunks(N);
    for (int i = 0; i < N; ++i)
        cin >> chunks[i].first >> chunks[i].second;

    // Small M and N
    if (N <= 1000 && M <= 10000) {
        vector<long long> dp(M + 1, 0);
        for (auto [value, mass] : chunks) {
            for (long long w = M; w >= mass; --w) {
                dp[w] = max(dp[w], dp[w - mass] + value);
            }
        }
        cout << dp[M] << '\n';
        return 0;
    }

    // At most 2 distinct masses
    set<long long> unique_masses;
    for (auto& [value, mass] : chunks)
        unique_masses.insert(mass);

    if (unique_masses.size() <= 2) {
        long long m1 = *unique_masses.begin();
        long long m2 = (unique_masses.size() == 2) ? *next(unique_masses.begin()) : m1;
        if (m1 > m2) swap(m1, m2);

        vector<pair<long long, long long>> group1, group2;
        for (auto& chunk : chunks) {
            (chunk.second == m1 ? group1 : group2).push_back(chunk);
        }

        sort(group1.rbegin(), group1.rend());
        sort(group2.rbegin(), group2.rend());

        vector<long long> prefix1(group1.size() + 1), prefix2(group2.size() + 1);
        for (size_t i = 0; i < group1.size(); ++i)
            prefix1[i + 1] = prefix1[i] + group1[i].first;
        for (size_t i = 0; i < group2.size(); ++i)
            prefix2[i + 1] = prefix2[i] + group2[i].first;

        long long best = 0;
        for (size_t cnt2 = 0; cnt2 <= group2.size(); ++cnt2) {
            long long used_mass = cnt2 * m2;
            if (used_mass > M) break;
            long long cnt1 = min((long long)group1.size(), (M - used_mass) / m1);
            best = max(best, prefix2[cnt2] + prefix1[cnt1]);
        }

        cout << best << '\n';
        return 0;
    }

    // General case
    long long total_value = 0;

    while (M > 0 && !chunks.empty()) {
        long long min_mass = LLONG_MAX;
        for (const auto& [_, mass] : chunks)
            min_mass = min(min_mass, mass);
        
        if (min_mass > M) break;

        if (min_mass > 1) {
            M /= min_mass;
            for (auto& chunk : chunks)
                chunk.second /= min_mass;
        } else {
            long long second_min = LLONG_MAX;
            for (const auto& [_, mass] : chunks) {
                if (mass > 1)
                    second_min = min(second_min, mass);
            }

            if (second_min == LLONG_MAX) {
                sort(chunks.rbegin(), chunks.rend());
                long long take = min(M, (long long)chunks.size());
                for (int i = 0; i < take; ++i)
                    total_value += chunks[i].first;
                break;
            }

            long long x = second_min;
            vector<long long> ones;
            vector<pair<long long, long long>> others;

            for (const auto& chunk : chunks) {
                if (chunk.second == 1)
                    ones.push_back(chunk.first);
                else
                    others.push_back(chunk);
            }

            sort(ones.rbegin(), ones.rend());

            long long take_ones = min(M % x, (long long)ones.size());
            for (long long i = 0; i < take_ones; ++i) {
                total_value += ones[i];
                --M;
            }

            vector<pair<long long, long long>> reduced_chunks;
            for (long long i = take_ones; i + x <= (long long)ones.size(); i += x) {
                long long sum = 0;
                for (long long j = 0; j < x; ++j)
                    sum += ones[i + j];
                reduced_chunks.emplace_back(sum, x);
            }

            reduced_chunks.insert(reduced_chunks.end(), others.begin(), others.end());

            M /= x;
            for (auto& chunk : reduced_chunks)
                chunk.second /= x;

            chunks = move(reduced_chunks);
        }
    }

    cout << total_value << '\n';
    return 0;
}