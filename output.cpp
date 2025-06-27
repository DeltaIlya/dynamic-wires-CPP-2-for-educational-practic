#include "header.h"


void Output_solution(vector<vector<int>>& solution)
{
    if (solution.empty())
        cout << "Нет решения!\n";
    else {
        cout << "Самое оптимальное решение:\n";
        for (const auto& cuts : solution)
        {
            cout << cuts[0] << " -> ";
            for (size_t i = 1; i < cuts.size(); ++i)
            {
                cout << cuts[i];
                if (i + 1 < cuts.size()) cout << ", ";
            }
            cout << std::endl;
        }
    }
}