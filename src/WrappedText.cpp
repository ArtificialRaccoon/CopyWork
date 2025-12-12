#include "WrappedText.h"

void WrappedText::AppendChar(char c, size_t originalIndex, size_t& col)
{
    size_t wpos = text.size();
    text += c;
    originalIndices.push_back(originalIndex);

    if (originalIndex != std::string::npos && originalIndex < reverseMap.size() && reverseMap[originalIndex] == std::string::npos)
        reverseMap[originalIndex] = wpos;

    if (c == CHAR_NEWLINE)
        col = 0;
    else
        col++;
}

WrappedText WrappedText::Wrap(const std::string& originalText, int width)
{
    WrappedText out;
    out.reverseMap.assign(originalText.size(), std::string::npos);

    size_t col = 0;
    size_t lastSpace = std::string::npos;

    for (size_t i = 0; i < originalText.size(); i++)
    {
        char c = originalText[i];
        switch (static_cast<unsigned char>(c))
        {
            case CHAR_INT_TAB:
                for (size_t t = 0; t < TAB_SIZE; t++)
                    out.AppendChar(CHAR_SPACE, i, col);
                continue;
            case CHAR_INT_NEWLINE:
                out.AppendChar(CHAR_NEWLINE, i, col);
                lastSpace = std::string::npos;
                continue;
        }

        if (col >= (size_t)width - 1)
        {
            if (lastSpace != std::string::npos)
            {
                out.text[lastSpace] = CHAR_NEWLINE;
                out.originalIndices[lastSpace] = std::string::npos;
                col = out.text.size() - lastSpace - 1;
                lastSpace = std::string::npos;
            }
            else
                out.AppendChar(CHAR_NEWLINE, std::string::npos, col);
        }

        if (c == CHAR_SPACE)
            lastSpace = out.text.size();

        out.AppendChar(c, i, col);
    }

    out.lineBreaks.push_back(0);
    for (size_t i = 0; i < out.text.size(); i++)
    {
        if (out.text[i] == CHAR_NEWLINE)
            out.lineBreaks.push_back(i + 1);
    }

    return out;
}

std::pair<int, int> WrappedText::GetCursorScreenCoords(size_t originalPos, int scrollY) const
{
    size_t wrappedPos = std::string::npos;
    if (originalPos < reverseMap.size())
        wrappedPos = reverseMap[originalPos];

    if (wrappedPos == std::string::npos && originalPos >= reverseMap.size())
        wrappedPos = text.length();

    if (wrappedPos != std::string::npos)
    {
        auto it = std::upper_bound(lineBreaks.begin(), lineBreaks.end(), wrappedPos);
        int y = 0;
        if (it != lineBreaks.begin())
        {
            it--;
            y = static_cast<int>(it - lineBreaks.begin());
        }

        int x = static_cast<int>(wrappedPos - *it);
        return {y - scrollY, x};
    }
    return {-1, -1};

}
