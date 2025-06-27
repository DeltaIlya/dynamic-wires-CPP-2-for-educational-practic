#include "header.h"


bool find_best_set
(
    int capacity,
    const vector<int>& targets,
    const vector<bool>& used,
    vector<int>& best_idxs,
    int& best_sum, int idx = 0,
    int sum = 0, vector<int> current = {}
)
{
    if (sum > capacity) return false;
    if (sum > best_sum)
    {
        best_idxs = current;
        best_sum = sum;
    }
    bool found = false;
    for (int i = idx; i < targets.size(); ++i)
    {
        if (used[i]) continue;
        current.push_back(i);
        if (find_best_set(capacity, targets, used, best_idxs, best_sum, i + 1, sum + targets[i], current))
            found = true;
        current.pop_back();
    }
    return found;
}

bool solve
(
    const vector<int>& sources,
    const vector<int>& targets,
    int srcIdx,
    vector<bool>& used,
    SolutionVector& answer)
{
    if (std::all_of(used.begin(), used.end(), [](bool x) {return x; })) return true;
    if (srcIdx >= sources.size()) return false;

    int best_sum = 0;
    vector<int> best_idxs;
    find_best_set(sources[srcIdx], targets, used, best_idxs, best_sum);

    if (best_sum == 0)
    {
        // Не используется этот исходник (мб вообще не нужен)
        if (solve(sources, targets, srcIdx + 1, used, answer))
            return true;
        return false;
    }

    // использовать максимальное наполнение для этого исходника
    for (int idx : best_idxs) used[idx] = true;

    if (solve(sources, targets, srcIdx + 1, used, answer))
    {
        vector<int> cut = { sources[srcIdx] };
        for (int idx : best_idxs) cut.push_back(targets[idx]);
        answer.insert(answer.begin(), cut);
        return true;
    }

    // Откат
    for (int idx : best_idxs) used[idx] = false;
    // Вариант: не используем этот исходник вообще
    if (solve(sources, targets, srcIdx + 1, used, answer))
        return true;

    return false;
}

SolutionVector WireCutter(vector<int> source_wires, vector<int> target_wires, int min_remainder)
{
    SolutionVector solution;
    std::sort(source_wires.begin(), source_wires.end(), std::less<int>());
    std::sort(target_wires.begin(), target_wires.end(), std::greater<int>());

    vector<bool> used(target_wires.size(), false);
    SolutionVector answer;
    solve(source_wires, target_wires, 0, used, answer);
    if (answer.empty()) return SolutionVector();

    for (auto cuts : answer) if (cuts[0] == std::accumulate(++cuts.begin(), cuts.end(), 0)) solution.push_back(cuts);
    if (answer == solution) return solution;

    vector<int> new_source_wires = source_wires, new_target_wires = target_wires;
    for (auto& cuts : solution)
    {
        auto it = cuts.begin();
        auto it_erase = std::find(new_source_wires.begin(), new_source_wires.end(), *it);
        if (it_erase != new_source_wires.end()) new_source_wires.erase(it_erase);

        for (; it != cuts.end(); ++it)
        {
            auto it_erase = std::find(new_target_wires.begin(), new_target_wires.end(), *it);
            if (it_erase != new_target_wires.end()) new_target_wires.erase(it_erase);
        }
    }
    for (auto& e : new_source_wires) e -= min_remainder;


    vector<bool> new_used(new_target_wires.size(), false);
    SolutionVector new_answer;
    solve(new_source_wires, new_target_wires, 0, new_used, new_answer);
    if (new_answer.empty()) return SolutionVector();
    for (auto& cuts : new_answer)
    {
        cuts[0] += min_remainder;
        solution.push_back(cuts);
    }
    return solution;
}

int main()
{
	// Для ввода/вывода кириллицы
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    vector<int> source_wires, target_wires; int min_remainder; string answer;
    do
    {
        Input_data(source_wires, target_wires, min_remainder);
        printVector(source_wires, "Исходные длины");
        printVector(target_wires, "Необходимые длины");

        if (min_remainder) std::cout << "Минимально допустимый остаток: " << min_remainder << std::endl;
        SolutionVector solution = WireCutter(source_wires, target_wires, min_remainder);
        Output_solution(solution);

        std::cout << "\n\nХотите продолжить? [Y/N]:";
        getline(std::cin, answer, '\n');
    } while (answer[0] == 'Y' || answer[0] == 'y' || answer[0] == 'Н' || answer[0] == 'н' || answer[0] == '\0');
    std::cout << "До свидания! :D\n\n";
    
	system("pause");
	return 0;
}