/* ---------------------------------------------------------------------------
** checkBoard.cpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#include <checkerBoard.hpp>

CheckerBoard::CheckerBoard(const float squareSize, Color color1, Color color2) : Material(color1, BLACK, 0.0f, BLACK, BLACK),
    mSquareSize(squareSize), mColor1(color1), mColor2(color2){}

CheckerBoard::CheckerBoard(const float squareSize, Color color1, Color color2, Color specular) :
        Material(color1, specular, 0.0f, BLACK, BLACK), mSquareSize(squareSize), mColor1(color1), mColor2(color2){}

Color CheckerBoard::GetDiffuse(const Point &point) const {
    return Material::GetDiffuse(point);
}