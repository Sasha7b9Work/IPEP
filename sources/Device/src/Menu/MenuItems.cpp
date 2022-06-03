// 2022/05/05 12:27:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/MenuItems.h"
#include "Menu/Pages/Pages.h"
#include "Display/Display.h"
#include "Utils/Text/String.h"
#include "Menu/Menu.h"


Page Page::Empty;

namespace Menu
{
    extern const Page *opened;
}


const Page *Menu::OpenedPage()
{
    return opened;
}


void Page::Open() const
{
    Menu::opened = this;

    uint8 *currentItem = ReinterpretToDPage()->currentItem;

    if (*currentItem == NumItems() - 1)
    {
        *currentItem = 0;
    }
}


void Page::Close() const
{
    if (this == PageMain::self)
    {
        Menu::opened = &Page::Empty;
    }
    else
    {
        Menu::opened = ReinterpretToDPage()->keeper;
    }
}


bool Item::Opened() const
{
    return true;
}


void Item::Draw(int x, int y) const
{
    if (Opened())
    {
        DrawOpened(x, y);
    }
    else
    {
        DrawClosed(x, y);
    }
}


void Item::DrawOpened(int x, int y) const
{
    if (IsPage())
    {
        ReinterpetToPage()->DrawOpened(x, y);
    }
    else if (IsChoice())
    {
        ReinterpretToChoice()->DrawOpened(x, y);
    }
}


void Item::DrawClosed(int x, int y) const
{
    if (IsPage())
    {
        ReinterpetToPage()->DrawClosed(x, y);
    }
    else if (IsChoice())
    {
        ReinterpretToChoice()->DrawClosed(x, y);
    }
    else if (IsButton())
    {
        ReinterpretToButton()->DrawClosed(x, y);
    }
}


void Page::DrawOpened(int x, int y) const
{
    DrawTitle(x, y);

    DrawItems(x, y + 27);
}


void Page::DrawTitle(int x, int y) const
{
    Rectangle(Item::WIDTH, 27).DrawFilled(x, y, Color::BLACK, Color::WHITE);

    String<>(Title()).Draw(x + 10, y + 10, Color::GRAY_50);
}


void Page::DrawItems(int x, int y) const
{
    for (int i = FirstItemOnScreen(); i < LastItemOnScreen(); i++)
    {
        ReinterpretToDPage()->items[i]->DrawClosed(x, y);
        y += Item::HEIGHT;
    }
}


const Item *Page::CurrentItem() const
{
    const Item *const *items = ReinterpretToDPage()->items;

    uint8 *currentItem = ReinterpretToDPage()->currentItem;

    return items[*currentItem];
}


void Page::DrawClosed(int x, int y) const
{
    Color::E fill = Color::BLACK;
    Color::E draw = Color::WHITE;

    if (ReinterpretToDPage()->keeper->CurrentItem() == this)
    {
        fill = Color::GREEN_50;
    }

    Rectangle(Item::WIDTH, Item::HEIGHT).DrawFilled(x, y, fill, draw);

    String<>(Title()).Draw(x + 10, y + 5, draw);
}


pchar Choice::CurrentName() const
{
    const DChoice *choice = ReinterpretToDChoice();

    return choice->names[*choice->cell];
}


void Choice::DrawClosed(int x, int y) const
{
    Color::E fill = Color::BLACK;
    Color::E draw = Color::WHITE;

    if (ReinterpretToDItem()->keeper->CurrentItem() == this)
    {
        fill = Color::GREEN_50;
    }

    Rectangle(Item::WIDTH, Item::HEIGHT).DrawFilled(x, y, fill, draw);

    String<>(Title()).Draw(x + 10, y + 5, draw);

    String<>(CurrentName()).Draw(x + 130, y + 5, draw);
}


void Button::DrawClosed(int x, int y) const
{
    Color::E fill = Color::BLACK;
    Color::E draw = Color::WHITE;

    if (ReinterpretToDItem()->keeper->CurrentItem() == this)
    {
        fill = Color::GREEN_50;
    }

    Rectangle(Item::WIDTH, Item::HEIGHT).DrawFilled(x, y, fill, draw);

    String<>(Title()).Draw(x + 10, y + 5, draw);
}


int Page::FirstItemOnScreen() const
{
    return (*ReinterpretToDPage()->currentItem / Page::NUM_ITEMS_ON_SCREEN) * Page::NUM_ITEMS_ON_SCREEN;
}


int Page::LastItemOnScreen() const
{
    int result = FirstItemOnScreen() + Page::NUM_ITEMS_ON_SCREEN;

    if (result > NumItems())
    {
        result = NumItems();
    }

    return result;
}


int Page::NumItems() const
{
    for (int i = 0; ; i++)
    {
        if (ReinterpretToDPage()->items[i] == nullptr)
        {
            return i;
        }
    }
}


void Page::SelectNextItem() const
{
    uint8 *currentItem = ReinterpretToDPage()->currentItem;

    *currentItem = (uint8)(*currentItem + 1);

    if (*currentItem == NumItems())
    {
        *currentItem = 0;
    }
}


void Page::ChangeCurrentItem() const
{
    const Item *item = CurrentItem();

    if (item->IsPage())
    {
        item->ReinterpetToPage()->Open();
    }
    else if (item->IsChoice())
    {
        item->ReinterpretToChoice()->Change();
    }
    else if (item->IsButton())
    {
        item->ReinterpretToButton()->FuncOnPress();
    }
}


void Choice::Change() const
{
    uint8 *cell = ReinterpretToDChoice()->cell;

    *cell = (uint8)(*cell + 1);

    if (*cell == ReinterpretToDChoice()->count)
    {
        *cell = 0;
    }
}
