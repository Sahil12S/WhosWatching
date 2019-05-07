#include "DropDownList.h"

namespace gui
{
    DropDownList::DropDownList(GameDataRef data, const std::string &font, const float &x, const float &y,
                            std::string list[], unsigned numOfElements, unsigned default_idx) : m_Data(std::move(data)), m_ShowList(false), keyTimeMax( 1.f ), keyTime( keyTimeMax )
    {
        m_Font = m_Data->assets.GetFont(font);

        std::vector<sf::Color> textColor = {sf::Color(LIST_TEXT_IDLE_FILL_COLOR),
                                            sf::Color(LIST_TEXT_HOVER_FILL_COLOR),
                                            sf::Color(LIST_TEXT_ACTIVE_FILL_COLOR)};
        std::vector<sf::Color> listBgColor = {sf::Color(LIST_IDLE_FILL_COLOR), 
                                            sf::Color(LIST_HOVER_FILL_COLOR),
                                            sf::Color(LIST_ACTIVE_FILL_COLOR)};
        std::vector<sf::Color> outlineColor = { sf::Color( OUTLINE_COLOR_IDLE ), 
                                            sf::Color( OUTLINE_COLOR_HOVER ),
                                            sf::Color( OUTLINE_COLOR_ACTIVE ) };

        // int numOfElements = sizeof( list ) / sizeof( std::string );
        m_ActiveElement = new Button(m_Data);
        m_ActiveElement->CreateButton(x, y, LIST_WIDTH, LIST_HEIGHT );
        m_ActiveElement->SetButtonProperties( m_Data->assets.GetFont( font ), list[default_idx], LIST_TEXT_SIZE, textColor, listBgColor, outlineColor );

        outlineColor = { sf::Color( 255, 255, 255, 0 ),
                    sf::Color( 255, 255, 255, 0 ),
                    sf::Color( 20, 20, 20, 0 ) };

        for (size_t i = 0; i < numOfElements; i++)
        {
            // Create new button
            m_List.emplace_back( new Button( m_Data ) );
            m_List.back()->CreateButton( x, y + ( ( i + 1 ) * LIST_HEIGHT), LIST_WIDTH, LIST_HEIGHT );
            m_List.back()->SetButtonProperties( m_Data->assets.GetFont( font ), list[i], LIST_TEXT_SIZE, textColor, listBgColor, outlineColor, i );
        }

    }

    DropDownList::~DropDownList()
    {
        delete m_ActiveElement;
        for (auto &l : m_List)
        {
            delete l;
        }
    }

    const short unsigned& DropDownList::getActiveElementId()
    {
        return m_ActiveElement->getId();
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

        // Set current resolution on click
        if (m_ShowList)
        {
            for (auto &i : m_List)
            {
                i->Update(mousePosition);

                if ( i->isPressed() && GetKeyTime() )
                {
                    m_ShowList = false;
                    m_ActiveElement->setText( i->getText() );
                    m_ActiveElement->setId( i->getId() );
                }
            }
        }
    }

    void DropDownList::Draw( sf::RenderTarget& target )
    {
        m_ActiveElement->Draw( target );

        if (m_ShowList)
        {
            for (auto &i : m_List)
            {
                i->Draw( target );
            }
        }
    }
}