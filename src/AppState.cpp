#include "AppState.h"

void AppStateManager::LoadState()
{
	std::string stateFilename = originalTextFileName + ".sav";
	std::ifstream inFile(stateFilename);

	if (!inFile.is_open())
	{
		ResetToDefault();
		return;
	}
	
	std::string line;
	std::string key;
	
	if (!std::getline(inFile, line) || line != "version: v1")
	{
		ResetToDefault();
		return;
	}

	size_t loadedPos = 0;
	if (!std::getline(inFile, line) || line.rfind("currentPos: ", 0) != 0)
	{
		ResetToDefault();
		return;
	}
	loadedPos = std::stoull(line.substr(12));

	size_t loadedHwm = 0;
	if (!std::getline(inFile, line) || line.rfind("highWaterMark: ", 0) != 0)
	{
		ResetToDefault();
		return;
	}
	loadedHwm = std::stoull(line.substr(15));
	

	if (loadedHwm > originalText.length() || loadedPos > loadedHwm)
	{
		ResetToDefault();
		return;
	}
	
	currentPos = loadedPos;
	highWaterMark = loadedHwm;

	if (!std::getline(inFile, line) || line.rfind("progress: ", 0) != 0)
	{
		ResetToDefault();
		return;
	}

	std::string progressStr = line.substr(10);
	if (progressStr.length() != highWaterMark)
	{
		ResetToDefault();
		return;
	}
	
	progress.assign(originalText.length(), STATE_DEFAULT);
	for (size_t i = 0; i < highWaterMark; ++i)
	{
		int stateInt = progressStr[i] - '0';
		if (stateInt >= STATE_DEFAULT && stateInt <= STATE_INCORRECT)
			progress[i] = static_cast<CharState>(stateInt);
		else
		{
			ResetToDefault();
			return;
		}
	}
}

void AppStateManager::ResetToDefault()
{
	currentPos = 0;
	highWaterMark = 0;
	progress.assign(originalText.length(), STATE_DEFAULT);
}

void AppStateManager::SaveState()
{
	std::string stateFilename = originalTextFileName + ".sav";
	std::ofstream outFile(stateFilename);

	if (outFile.is_open())
	{
		outFile << "version: v1\n";
		outFile << "currentPos: " << currentPos << "\n";
		outFile << "highWaterMark: " << highWaterMark << "\n";	
		outFile << "progress: ";
		for (size_t i = 0; i < highWaterMark; ++i) { outFile << static_cast<int>(progress[i]); }
		outFile << "\n";
	}
}

bool AppStateManager::Initialize(std::string filename, int cols)
{
	originalTextFileName = filename;

	std::ifstream file(originalTextFileName);
	if (!file)
	{
		std::cerr << "Error: Could not open file " << originalTextFileName << std::endl;
		return false;
	}

	originalText = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	progress.assign(originalText.length(), STATE_DEFAULT);
	LoadState();

	for (size_t i = 0; i < currentPos; ++i)
	{
		if (progress[i] == STATE_DEFAULT)
			progress[i] = STATE_CORRECT;
	}
	wrapped = WrappedText::Wrap(originalText, cols);
	return true;
}

void AppStateManager::Resize(int cols)
{
	wrapped = WrappedText::Wrap(originalText, cols);
	scrollY = 0;
}

void AppStateManager::Backspace()
{
	if (currentPos > 0)
	{
		currentPos--;
		progress[currentPos] = STATE_DEFAULT;
	}
}

void AppStateManager::CheckInput(int inputChar)
{
	if (currentPos >= originalText.length())
		return;

	if (inputChar <= 0 || inputChar >= 256)
		return;
		
	if (inputChar == originalText[currentPos])
		progress[currentPos] = STATE_CORRECT;
	else
		progress[currentPos] = STATE_INCORRECT;

	currentPos++;
	if (currentPos > highWaterMark)
		highWaterMark = currentPos;
}
