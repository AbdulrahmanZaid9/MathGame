#include<iostream>
#include <cstdlib>    
#include <ctime> 
using namespace std;
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperatorType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };
struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	short PlayerAnswer;
	short CorrecAnswer;
	enQuestionLevel QuestionLevel;
	enOperatorType Optype;
	bool answerResult = false;
};
struct stQuizz
{
	stQuestion QuestionsList[100];
	short NumberOfQuestions;
	enQuestionLevel Level;
	enOperatorType Optype;
	short NumberOfCorrectAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool ispass = false;

};
string GetQuestionLevelText(enQuestionLevel Level)
{
	string Levels[4] = { "Easy" , "Med" , "Hard" , "Mix" };
	return Levels[Level - 1];
}
int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}
enQuestionLevel ReadQuestionsLevel()
{
	short PLayerChoice;
	do
	{
		cout << "Enter Questinos level [1] Easy,[2] Med,[3] Hard,[4] Mix ? " << endl;
		cin >> PLayerChoice;
	} while (PLayerChoice < 1 || PLayerChoice > 4);

	return (enQuestionLevel)PLayerChoice;
}
enOperatorType ReadOperatorType()
{
	short PLayerChoice;
	do
	{
		cout << "Enter Questinos Type [1] Add,[2] Sub,[3] Mul,[4] Div,[5] Mix ? " << endl;
		cin >> PLayerChoice;
	} while (PLayerChoice < 1 || PLayerChoice > 5);

	return (enOperatorType)PLayerChoice;
}
int SimpleCulclater(int Number1, int Number2, enOperatorType OpType)
{
	switch (OpType)
	{
	case enOperatorType::Add:
		return Number1 + Number2;
	case enOperatorType::Sub:
		return Number1 - Number2;
	case enOperatorType::Mul:
		return Number1 * Number2;
	case enOperatorType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}
enOperatorType GetRandomOperator()
{
	return (enOperatorType)RandomNumber(1, 4);
}
string GetOpTypeSymbol(enOperatorType OpType)
{
	switch (OpType)
	{
	case enOperatorType::Add:
		return "+";
	case enOperatorType::Sub:
		return "-";
	case enOperatorType::Mul:
		return "*";
	case enOperatorType::Div:
		return "/";
	default:
		return "Mix";
	}
}
void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionsList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionsList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionsList[QuestionNumber].Optype);
	cout << "\n_____________\n";
}
int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}
void SetScreenColor(bool Answer)
{
	if (Answer)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
		cout << "\a" << endl;
	}
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionsList[QuestionNumber].PlayerAnswer != Quizz.QuestionsList[QuestionNumber].CorrecAnswer)
	{
		Quizz.QuestionsList[QuestionNumber].answerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << endl;
		cout << "Wrong Asnwer):" << endl;
		cout << "The Right Answer Is: ";
		cout << Quizz.QuestionsList[QuestionNumber].CorrecAnswer;
	}
	else
	{
		cout << endl;
		Quizz.QuestionsList[QuestionNumber].answerResult = true;
		Quizz.NumberOfCorrectAnswers++;
		cout << "Right Answer (: \n";
	}
	cout << endl;

	SetScreenColor(Quizz.QuestionsList[QuestionNumber].answerResult);
}
void AskandCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionsList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

	}
	Quizz.ispass = (Quizz.NumberOfCorrectAnswers >= Quizz.NumberOfWrongAnswers);
}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperatorType OpType)
{
	stQuestion Question;
	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperatorType::MixOp)
	{
		OpType = GetRandomOperator();
	}

	Question.Optype = OpType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrecAnswer = SimpleCulclater(Question.Number1, Question.Number2, Question.Optype);
		Question.QuestionLevel = QuestionLevel;

		return Question;
	case enQuestionLevel::Med:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrecAnswer = SimpleCulclater(Question.Number1, Question.Number2, Question.Optype);
		Question.QuestionLevel = QuestionLevel;

		return Question;
	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrecAnswer = SimpleCulclater(Question.Number1, Question.Number2, Question.Optype);
		Question.QuestionLevel = QuestionLevel;

		return Question;
	}
}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (int Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionsList[Question] = GenerateQuestion(Quizz.Level, Quizz.Optype);
	}
}
short HowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How Many Questions You Want To Answer ?\n";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 100);

	return NumberOfQuestions;
}
string GetFinalResultText(bool pass)
{
	if (pass)
	{
		return "Pass";
	}
	else
	{
		return "Fail";
	}
}
void PrintQuizzResult(stQuizz Quizz)
{
	cout << "\n";
	cout << "-------------------------\n\n";
	cout << "Final Result Is " << GetFinalResultText(Quizz.ispass);
	cout << "\n\n-------------------------\n\n";

	cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << "Level               : " << GetQuestionLevelText(Quizz.Level) << endl;
	cout << "Operation Type      : " << GetOpTypeSymbol(Quizz.Optype) << endl;
	cout << "Right Answers       : " << Quizz.NumberOfCorrectAnswers << endl;
	cout << "Wrong Answers       : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "\n";

}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = HowManyQuestions();
	Quizz.Level = ReadQuestionsLevel();
	Quizz.Optype = ReadOperatorType();

	GenerateQuizzQuestions(Quizz);
	AskandCorrectQuestionListAnswers(Quizz);
	PrintQuizzResult(Quizz);

}
void StartGame()
{
	char PlayAgain;
	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "Do You Want to Play Again ? Y/N" << endl;
		cin >> PlayAgain;


	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}