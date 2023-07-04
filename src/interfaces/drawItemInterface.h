#pragma once

namespace screen
{
class DrawItemInterface
{
public:
    virtual void draw() = 0;
};

} // namespace screen




// void ScreenBuffer::drawToBuffer(const wchar_t* object, int objectHeight, int objectWidth, int xOffset, int yOffset)
// {
//     for (int x = 0; x < objectWidth; x++)
//     {
// 		for (int y = 0; y < objectHeight; y++)
//         {
//                 mBuffer[(y + yOffset) * mScreenWidth + (x + xOffset)] = object[y * objectWidth + x];
//         }
//     }
// }



// class Display
// {
// public:
//     bool registerDrawItem(DrawItem& drawItem)
//     {
//         drawItems[mNumDrawItems] = drawItem;
//     }

//     void drawItemsToScreen()
//     {
//         for (int i = 0; i < 100; i++)
//         {
//             drawItems[i]->draw();
//         }
//     }

// private:
//     int mMaxDrawItems = 100;
//     int mNumDrawItems = 0;
//     DrawItem* drawItems[];

// };


// class Score : public DrawItem
// {
// public:
//     Score()
//     {
//         mDisplay.registerDrawItem(*this);
//     }

//     void draw(wchar_t* thing, int x , int y , int h , int w ) {}

// private:
//     Display& mDisplay;
// };

// } namespace screen


