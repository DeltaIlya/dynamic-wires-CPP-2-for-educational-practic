#include "header.h"

void printVector(vector<int> vector, string caption)
{
	int size = caption.size();
	cout << caption << ": ";
	if (vector.empty())
		cout << "[НЕТ ДАННЫХ]";
	else
	{
		std::sort(vector.begin(), vector.end());
		int count = 0; std::map<int, int> mapWire;
		for (auto element : vector) mapWire[element]++;

		auto it = mapWire.begin();
		cout << it->first << "м - " << it->second << "шт.";
		if (mapWire.size() > 1)
		{
			it++;
			for (; it != mapWire.end(); it++)
			{
				cout << ";\n" << setw(size + 2) << "" << it->first << "м - " << it->second << "шт.";
			}
		}
	}
	cout << endl;
}

static void parseNumber(const std::string& s, int& length, int& count)
{
	// Находим позицию разделителя 'x' (регистронезависимо)
	if (s.find('x') == s.find('X'))
	{
		// Если разделитель 'x' не найден, обрабатываем всю строку как длину,
		// а количество устанавливаем в 1
		std::string string = s;
		std::replace(string.begin(), string.end(), ',', '.');
		length = std::stoi(string);
		count = 1;
	}
	else
	{
		size_t pos_char_x = s.find('x') < s.find('X') ? s.find('x') : s.find('X');
		// Разделяем строку на часть до 'x' (длина) и после 'x' (количество)
		std::string string_before_x = s.substr(0, pos_char_x);
		std::string string_after_x = s.substr(pos_char_x + 1);

		// Парсим длину (заменяем запятые на точки и преобразуем в float)
		std::replace(string_before_x.begin(), string_before_x.end(), ',', '.');
		length = std::stoi(string_before_x);

		// Парсим количество (заменяем запятые на точки и преобразуем в int)
		std::replace(string_after_x.begin(), string_after_x.end(), ',', '.');
		count = std::stoi(string_after_x);
	}
}

static void Input_string_to_vector_int(vector<int>& vector)
{
	vector.clear();
    string line;
    string token;
	int length;
	int count;

    getline(cin, line, '\n');
    istringstream iss(line);
    while (iss >> token)
    {
		try
		{
			parseNumber(token, length, count);
			if (!count || !length) continue;
			for (int i = 0; i < count; i++) vector.push_back(length);
		}
		catch (...) {}
    }
	sort(vector.begin(), vector.end());
}

static void Input_string_to_int(int& number)
{
	string line;

	getline(cin, line, '\n');
	try
	{
		std::replace(line.begin(), line.end(), ',', '.');
		number = std::stoi(line);
	}
	catch (...) { number = 0; }
}

void Input_data(vector<int>& wires, vector<int>& task, int& minRemainder)
{
	string answer = "n";
	do
	{
		system("cls");
		cout << "Введите исходные длины проводов через пробел: ";
		Input_string_to_vector_int(wires);
		system("cls");

		if (wires.size() == 0) cout << "Длины проводов указаны неверно..." << endl;
		else
		{
			printVector(wires, "Исходные длины");
			cout << "Продолжить с этими данными? [Y/N]: "; getline(cin, answer);
		}
	} while (!(answer[0] == 'Y' || answer[0] == 'y' || answer[0] == 'Н' || answer[0] == 'н' || answer[0] == '\0'));
	answer = "n";

	do
	{
		system("cls");
		printVector(wires, "Исходные длины");
		cout << "Введите длины проводов, которые нужно получить, через пробел: ";
		Input_string_to_vector_int(task);
		system("cls");
		printVector(wires, "Исходные длины");

		if (wires.size() == 0) cout << "Длины проводов указаны неверно..." << endl;
		else
		{
			printVector(task, "Необходимые длины");
			cout << "Продолжить с этими данными? [Y/N]: "; getline(cin, answer);
		}
	} while (!(answer[0] == 'Y' || answer[0] == 'y' || answer[0] == 'Н' || answer[0] == 'н' || answer[0] == '\0'));
	answer = "n";
	
	do
	{
		system("cls");
		printVector(wires, "Исходные длины");
		printVector(task, "Необходимые длины");
		cout << "Введите минимально допустимый остаток: ";
		Input_string_to_int(minRemainder);
		system("cls");
		printVector(wires, "Исходные длины");
		printVector(task, "Необходимые длины");
	 
		if (minRemainder == 0) cout << "Делать расчёт без учёта остатка?" << endl;
		else cout << "Делать расчёт с учётом минимального остатка: " << minRemainder << "?";
		cout << " [Y/N]: "; getline(cin, answer);
	} while (!(answer[0] == 'Y' || answer[0] == 'y' || answer[0] == 'Н' || answer[0] == 'н' || answer[0] == '\0'));
	system("cls");
}