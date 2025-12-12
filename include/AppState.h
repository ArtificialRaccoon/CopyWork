#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include "WrappedText.h"

// Represents the state of each character in the text
enum CharState
{
    STATE_DEFAULT,
    STATE_CORRECT,
    STATE_INCORRECT
};

// Manages the application state, including loading, saving, and updating text progress.
class AppStateManager
{
	public:				
		void LoadState();
		void SaveState();
		void Resize(int cols);
		void SetScrollY(int y) { scrollY = y; }
		void Backspace();
		void CheckInput(int inputChar);		
		bool Initialize(std::string filename, int cols);
		int GetScrollY() const { return scrollY; }	
		size_t GetCurrentPos() const { return currentPos; }
		size_t GetLength() const { return originalText.length(); }			
		const std::vector<CharState>& GetProgress() const { return progress; }		
		const std::string& GetText() const { return originalText; }
		const WrappedText& GetWrapped() const { return wrapped; }

	private:
		void ResetToDefault();

	private:		
		int scrollY = 0;
		size_t currentPos = 0;
		size_t highWaterMark = 0;	
		std::string originalTextFileName;
		std::string originalText;
		std::vector<CharState> progress;	
		WrappedText wrapped;
};