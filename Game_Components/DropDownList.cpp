#include "DropDownList.h"

namespace SSEngine
{
DropDownList::DropDownList(GameDataRef data, const std::string &font, const float &x, const float &y,
                           std::string list[], unsigned numOfElements, unsigned default_idx) : m_Data(std::move(data)), m_ShowList(false), keyTimeMax( 1.f ), keyTime( keyTimeMax )
{
    m_Font = m_Data->assets.GetFont(font);

    // int numOfElements = sizeof( list ) / sizeof( std::string );

    for (size_t i = 0; i < numOfElements; i++)
    {
        // Create new button
        m_List.emplace_back(new Button(m_Data));
        m_List.back()->CreateButton(x, y + (i * LIST_HEIGHT), LIST_WIDTH, LIST_HEIGHT);
        std::vector<sf::Color> textColor = {sf::Color(LIST_TEXT_IDLE_FILL_COLOR),
                                            sf::Color(LIST_TEXT_HOVER_FILL_COLOR),
                                            sf::Color(LIST_TEXT_ACTIVE_FILL_COLOR)};

        m_List.back()->SetButtonProperties(font, list[i], LIST_TEXT_SIZE, textColor, 
                        {sf::Color(LIST_IDLE_FILL_COLOR), sf::Color(LIST_HOVER_FILL_COLOR), sf::Color(LIST_ACTIVE_FILL_COLOR)});
    }

    m_ActiveElement = new Button(*m_List[default_idx]);
}

DropDownList::~DropDownList()
{
    delete m_ActiveElement;
    for (auto &l : m_List)
    {
        delete l;
    }
}

const bool DropDownList::GetKeyTime()
{
    if (keyTime >= keyTimeMax)
    {
        keyTime = 0.f;
        return true;
    }
    return false;
}

void DropDownList::UpdateKeyTime(const float &dt)
{
    if (keyTime < keyTimeMax)
    {
        keyTime += 10.f * dt;
    }
}

void DropDownList::Update(const float &dt, const sf::Vector2f &mousePosition)
{
    UpdateKeyTime(dt);
    m_ActiveElement->Update(mousePosition);

    // Show and hide the list
    if (m_ActiveElement->isPressed() && GetKeyTime())
    {
        m_ShowList = !m_ShowList;
    }

    if (m_ShowList)
    {
        for (auto &i : m_List)
        {
            i->Update(mousePosition);
        }
    }
}

void DropDownList::Draw()
{
    m_ActiveElement->Draw();

    if (m_ShowList)
    {
        for (auto &i : m_List)
        {
            i->Draw();
        }
    }
}
}; // namespace SSEngine