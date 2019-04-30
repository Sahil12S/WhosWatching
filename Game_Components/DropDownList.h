#ifndef DROPDOWN_LIST_H
#define DROPDOWN_LIST_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Game.h"
#include "Button.h"

namespace gui
{
    class DropDownList
    {
        private:
            GameDataRef m_Data;

            sf::Font m_Font;
            Button* m_ActiveElement;

            float keyTime;
            float keyTimeMax;

            std::vector< Button* > m_List;
            bool m_ShowList;

        public:
        DropDownList( GameDataRef data, const std::string& font, const float& x, const float& y,
                std::string list[], unsigned numOfElements, unsigned default_idx = 0 );
        virtual ~DropDownList();

        // Accessors
        const short unsigned& getActiveElementId();

        // Functions
        /*
        * Key time will prevent spamming of one button
        */
        const bool GetKeyTime();
        void UpdateKeyTime(  const float& dt );

        void Update(  const float& dt, const sf::Vector2f& mousePosition );
        void Draw();
    };
}

#endif // DROPDOWN_LIST_H