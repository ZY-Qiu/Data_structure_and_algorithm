#include <iostream>
#include <string>
#include <math.h>
#include "array.hpp"
using namespace std;

#define N_OPTR 9

const char pri[N_OPTR][N_OPTR] =
{
	//        |--------------当前运算符---------------|
	//        +    -    *    /    ^    !    (    )    $
	/*-- +*/ '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/* | -*/ '>', '>', '<', '<', '<', '<', '<', '>', '>',
	/*栈 **/ '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/*底 /*/ '>', '>', '>', '>', '<', '<', '<', '>', '>',
	/*运 ^*/ '>', '>', '>', '>', '>', '<', '<', '>', '>',
	/*算 !*/ '>', '>', '>', '>', '>', '>', ' ', '>', '>',
	/*符 (*/ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
	/* | )*/ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	/*-- $*/ '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};

const char op[9] = { '+', '-', '*', '/', '^', '!', '(', ')', '$' };

int find_op(char c)
{
	for (int i = 0; i < 9; i++)
	{
		if (c == op[i]) return i;
	}
}

void readNumber(char c, Array<float>& opnd, bool flag)
{
	if (flag)
	{
		opnd.push_back(10 * opnd.pop_back() + float(c - '0'));
	}
	else
	{
		opnd.push_back(float(c - '0'));
	}
}

char orderBetween(char fst, char snd)
{
	return pri[find_op(fst)][find_op(snd)];
}

float calcu(char op, float opnd)
{
	if (opnd == 0) return 1;
	else
	{
		float f = 1;
		for (int i = 1; i <= opnd; i++)
		{
			f *= i;
		}
		return f;
	}
}

float calcu(float opnd1, char op, float opnd2)
{
	switch (op)
	{
	case '+':
		return opnd1 + opnd2;
		break;
	case '-':
		return opnd1 - opnd2;
		break;
	case '*':
		return opnd1 * opnd2;
		break;
	case '/':
		return opnd1 / opnd2;
		break;
	case '^':
		return pow(opnd1, opnd2);
		break;
	}
}

float evalute(char* S, string& RPN)
{
	Array<float> opnd;
	Array<char> optr;
	bool flag = 0;

	optr.push_back('$');
	
	while (!optr.is_empty())
	{
		//cout << "cnt" << endl;
		//cout << *S << endl;
		if (isdigit(*S))
		{
			readNumber(*S, opnd, flag);
			RPN.append(1, *S);
			S++;
			flag = 1;
		}
		else
		{
			flag = 0;
			//cout << orderBetween(optr.top(), *S) << endl;
			switch (orderBetween(optr.top(), *S))
			{
			case '<':
				optr.push_back(*S);
				S++;
				break;
			case '=':
				optr.pop_back();
				S++;
				break;
			case '>':
				char op = optr.pop_back();
				RPN.append(1, op);
				if (op == '!')
				{
					opnd.push_back(calcu(op, opnd.pop_back()));
				}
				else
				{
					float pOpnd2 = opnd.pop_back(), pOpnd1 = opnd.pop_back();
					opnd.push_back(calcu(pOpnd1, op, pOpnd2));
				}
				break;
			}
		}
		
	}
	return opnd.pop_back();
}

int main()
{
	char* str = new char[100];
	string RPN;

	cout << "请输入算式，并以$结尾" << endl;
	cin >> str;

	float f = evalute(str, RPN);

	cout << "结果为" << f << endl;
	cout << "RPN = " << RPN << endl;

	system("pause");
	return 0;
}