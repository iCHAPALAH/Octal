//������ ���� ��������

//������� ����� Octal ��� ������ � ������������ ������ ������������� �������,
//��������� ��� ������������� ����� ������ �� 100 ��������� ���� unsigned char,
//������ ������� �������� �������� ������������ ������. ������� ����� �����
//������� ������ (������� � � ������� �������� �������). �������� ������
//�������� ��� �������� ������������. ����������� �������������� ��������,
//����������� ���������� ��� ����� � C++, � �������� ���������.

#pragma once
#include "Octal.h"
#include <Windows.h>
#include <functional>
#include <fstream>

//������� ��� ���������� ������ �����
//���������� 1, ���� ����� ������� ������� � ��� ������������� ����������� ��������, 0 - �����
bool get_checked_integer(int& number, std::function<bool(int)> check = [](int x) {return true; })
{
	bool result = false;
	std::cin >> number;
	if (std::cin.good() && check(number))
	{
		result = true;
		while (result && std::cin.rdbuf()->in_avail() - 1)
		{
			char c = 0;
			std::cin.get(c);
			if (c != ' ')
				result = false;
		}
	}
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return result;
}

//������� ���������� ����� ����� � �������� �� ��� �������������
//-1 � ��� ����� �������� ������������ �������
//0 � ��� ����� ���������, �� ��� �� ������� �������
//1 � ��� ����� ��������� � �� �����������
int get_filename(std::string& filename)
{
	int result = -1;
	std::getline(std::cin, filename);
	if (filename.find_first_of("<>:\"/\\|?*") == std::string::npos)
	{
		filename.append(".txt");
		std::ifstream file(filename);
		result = (file.good() ? 1 : 0);
		file.close();
	}
	return result;
}

//������� ���������� ������������� ����� � ����������
//false � ������� 0 ����
//true � ������� �� 0 ����
bool read_from_keyboard(Octal& A)
{
	bool result = false;
	result = (A.read() != 0);
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return result;
}

//������� ���������� ������������� ����� �� �����
//false � ������� 0 ����
//true � ������� �� 0 ����
bool read_from_file(Octal& A)
{
	bool result = false;
	std::string filename;
	if (get_filename(filename) == 1)
	{
		std::ifstream file(filename);
		if (A.read(file) != 0)
			result = true;
		file.close();
	}
	system("cls");
	return result;
}

//����� ���������� ���������, ���������� �� ����� ���������� � ����
void write_in_file(const Octal& A)
{
	std::cout << "\n�������� ��������� � ����?\n1. ��\n0. ���\n->";
	int subchoice = 0;
	while (!get_checked_integer(subchoice, [](int x) {return x >= 0 && x <= 1; }))
		std::cout << "������ �����!\n->";
	if (subchoice)
	{
		std::string filename;
		std::cout << "������� ��� ����� (��� ���������� .txt):\n->";
		if (get_filename(filename) == 0)
		{
			std::ofstream file(filename);
			A.display(file);
			file.close();
		}
	}
	system("cls");
}

//��������� ������� ��� �������� ������
void print(std::string text, const Octal& number)
{
	std::cout << text;
	number.display();
	std::cout << '\n';
}

//����� ���������� ���������, ���������� �� ����� ��������
//���������� ����� ��������� ��������
int menu()
{
	std::cout << "1. A + B\n2. A - B\n3. A * B\n4. A / B\n5. A % B\n";
	std::cout << "6. A += B\n7. A -= B\n8. A *= B\n9. A /= B\n10. A %= B\n";
	std::cout << "11. A < B\n12. A > B\n13. A <= B\n14. A >= B\n15. A == B\n";
	std::cout << "16. A != B\n17. A++\n18. A--\n19. ++A\n20. --A\n->";
	int choice = 0;
	while (!get_checked_integer(choice, [](int x) {return x >= 1 && x <= 20; }))
		std::cout << "������ �����!\n->";
	system("cls");
	return choice;
}

//����� ��������� ���������, ���������� �� ���������� � ����� �� ������� ����������
void print_result(int choice, Octal& A, const Octal& B)
{
	Octal C;
	std::string message;
	switch (choice)
	{
	case 1:
		C = A + B;
		message = "A + B = ";
		break;
	case 2:
		C = A - B;
		message = "A - B = ";
		break;
	case 3:
		C = A * B;
		message = "A * B = ";
		break;
	case 4:
		C = A / B;
		message = "A / B = ";
		break;
	case 5:
		C = A % B;
		message = "A % B = ";
		break;
	case 6:
		C = A += B;
		message = "A += B\nA = ";
		break;
	case 7:
		C = A -= B;
		message = "A -= B\nA = ";
		break;
	case 8:
		C = A *= B;
		message = "A *= B\nA = ";
		break;
	case 9:
		C = A /= B;
		message = "A /= B\nA = ";
		break;
	case 10:
		C = A %= B;
		message = "A %= B\nA = ";
		break;
	case 11:
		std::cout << "A < B = " << (A < B ? "true" : "false");
		break;
	case 12:
		std::cout << "A > B = " << (A > B ? "true" : "false");
		break;
	case 13:
		std::cout << "A <= B = " << (A <= B ? "true" : "false");
		break;
	case 14:
		std::cout << "A >= B = " << (A >= B ? "true" : "false");
		break;
	case 15:
		std::cout << "A == B = " << (A == B ? "true" : "false");
		break;
	case 16:
		std::cout << "A != B = " << (A != B ? "true" : "false");
		break;
	case 17:
		print("A++ = ", A++);
		C = A;
		message = "A = ";
		break;
	case 18:
		print("A-- = ", A--);
		C = A;
		message = "A = ";
		break;
	case 19:
		print("++A = ", ++A);
		C = A;
		message = "A = ";
		break;
	case 20:
		print("--A = ", --A);
		C = A;
		message = "A = ";
		break;
	}
	print(message, C);

	write_in_file(C);
}

//����� ���������� ���������, ���������� �� ������������������ �������� ��� ���������� ����� � ����������
void keyboard()
{
	Octal A, B;
	bool tmp;
	do
	{
		std::cout << "A = ";
		tmp = read_from_keyboard(A);
		if(!tmp)
			std::cout << "������ �����!\n";
	} while (!tmp);
	system("cls");
	print("A = ", A);
	int choice = menu();
	if (choice < 17)
	{
		do{
			std::cout << "B = ";
			tmp = read_from_keyboard(B);
			if (!tmp)
				std::cout << "������ �����!\n";
		} while (!tmp);
		system("cls");
	}
	print("A = ", A);
	if (choice < 17)
		print("B = ", B);
	print_result(choice, A, B);
}

//����� ���������� ���������, ���������� �� ������������������ �������� ��� ���������� ����� �� ������
void file()
{
	Octal A, B;
	std::cout << "������� ��� ����� (��� ���������� .txt):\n->";
	if (read_from_file(A))
	{
		print("A = ", A);
		int choice = menu();
		if (choice < 17)
		{
			std::cout << "������� ��� ����� (��� ���������� .txt):\n->";
			if (read_from_file(B))
			{
				print("A = ", A);
				print("B = ", B);
				print_result(choice, A, B);
			}
			else
				std::cout << "�� ������� ������� ����� �� �����!\n";
		}
		else
		{
			print("A = ", A);
			print_result(choice, A, B);
		}
	}
	else
		std::cout << "�� ������� ������� ����� �� �����!\n";
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice = -1;
	while (choice != 0)
	{
		std::cout << "1. ������ � ����������\n2. ������� �� �����\n0. �����\n->";
		while (!get_checked_integer(choice, [](int x) {return x >= 0 && x <= 2; }))
			std::cout << "������ �����!\n->";
		system("cls");
		if (choice == 1)
			keyboard();
		else if (choice == 2)
			file();
	}
	return 0;
}