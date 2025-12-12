#pragma once

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include "Constants.h"

class WrappedText
{
    public:
        WrappedText() = default;
        static WrappedText Wrap(const std::string& originalText, int width);
        std::pair<int, int> GetCursorScreenCoords(size_t originalPos, int scrollY) const;

    private:
        void AppendChar(char c, size_t originalIndex, size_t& col);

    public:
        std::string text;
        std::vector<size_t> originalIndices;
        std::vector<size_t> reverseMap;
        std::vector<size_t> lineBreaks;
};
