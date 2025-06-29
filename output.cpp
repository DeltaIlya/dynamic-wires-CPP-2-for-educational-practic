#include "header.h"

string num_to_str(int s)
{
	if (!(s % 1000))		return std::to_string(s / 1000);
	else if (!(s % 100))	return std::to_string(s / 1000) + "." + std::to_string(s % 1000 / 100);
	else if (!(s % 10))		return std::to_string(s / 1000) + "." + std::to_string(s % 1000 / 10);
	else					return std::to_string(s / 1000) + "." + std::to_string(s % 1000);
}

void printVector(vector<int> vector, string caption)
{
	cout << std::right;
	size_t size = caption.size();
	cout << caption << ": ";
	if (vector.empty()) cout << "[НЕТ ДАННЫХ]";
	else
	{
		int count = 0; std::map<int, int> mapWire;
		for (auto element : vector) mapWire[element]++;

		auto it = mapWire.begin();
		cout << num_to_str(it->first) << "м - " << it->second << "шт.";
		if (mapWire.size() > 1)
		{
			it++;
			for (; it != mapWire.end(); it++)
			{
				cout << endl << setw(size + 2) << "" << num_to_str(it->first) << "м - " << it->second << "шт.";
			}
		}
	}
	cout << endl;
}

void Output_solution(vector<vector<int>>& solution)
{
	if (solution.empty()) cout << "Нет решения!\n";
	else
	{
		cout << "Самое оптимальное решение:" << endl;
		for (const auto& cuts : solution)
		{
			cout << num_to_str(cuts[0]) << " -> ";
			for (size_t i = 1; i < cuts.size(); ++i)
			{
				cout << num_to_str(cuts[i]);
				if (i + 1 < cuts.size()) cout << ", ";
			}
			cout << endl;
		}
	}
}