#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "../Game.h"
#include "../DEFINITIONS.h"

#include <SFML/Graphics.hpp>

namespace SSEngine
{
    struct GameData;
    typedef std::shared_ptr<GameData> GameDataRef;

    class AnimationComponent
    {
    private:
        class Animation
        {
        public:
            sf::Sprite& sprite;
            sf::Texture& m_TextureSheet;
            sf::Clock clock;
            float animationTimer;
            float timer;
            bool m_Done;
            int width;
            int height;
            sf::IntRect m_StartRect;
            sf::IntRect m_CurrentRect;
            sf::IntRect m_EndRect;

            /*
             * @sprite: Sprite on which animation is to be done
             * @texture_sheet: Use which texture for the animation
             * @animation_timer: Speed of animation
             * @start_frame_x: index of starting frame in X axis
             * @start_frame_y: index of starting frame in Y axis
             * @frames_x: number of frames after start frame
             * @frame_y: number of frames after start frame
             * @width: width of tile in texture sheet
             * @height: height of tile in texture sheet
            */
            Animation( sf::Sprite& sprite, sf::Texture& texture_sheet,
                    float animation_timer,
                    int start_frame_x, int start_frame_y, int frames_x, int frames_y,
                    int width, int height) :
                    sprite( sprite ), m_TextureSheet( texture_sheet ),
                    animationTimer( animation_timer ), timer( 0.f ), m_Done( false ),
                    width( width ), height( height )
            {
                m_StartRect = sf::IntRect( start_frame_x * width,
                        start_frame_y * height, width, height );

                m_CurrentRect = m_StartRect;
                m_EndRect = sf::IntRect( (start_frame_x + frames_x - 1) * width,
                        (start_frame_y + frames_y - 1) * height, width,  height );

                sprite.setTexture( m_TextureSheet, true );
                sprite.setTextureRect( m_StartRect );

            }

            // Accessor
            const bool& isDone() const
            {
                return m_Done;
            }

            // Functions
            const bool& play( const float& dt )
            {
                // Update timer
                m_Done = false;
                timer += 100.f * dt;

                if ( timer >= animationTimer )
                {
                    // reset timer
                    timer = 0.f;
                    clock.restart();

                    if (m_CurrentRect != m_EndRect)
                    {
                        m_CurrentRect.left += width;
                    }
                    else //Reset
                    {
                        m_CurrentRect.left = m_StartRect.left;
                        m_Done = true;
                    }

                    sprite.setTextureRect( m_CurrentRect );
                }
                return m_Done;
            }

            const bool& play(const float& dt, float mod_percent)
            {
                //Update timer
                if (mod_percent < 0.5f)
                    mod_percent = 0.5f;

                m_Done = false;
                timer += mod_percent * 100.f * dt;
                if ( timer >= animationTimer)
                {
                    //reset timer
                    timer = 0.f;
                    clock.restart();

                    //Animate
                    if (m_CurrentRect != m_EndRect)
                    {
                        m_CurrentRect.left += width;
                    }
                    else //Reset
                    {
                        m_CurrentRect.left = m_StartRect.left;
                        m_Done = true;
                    }

                    sprite.setTextureRect(m_CurrentRect);
                }

                return m_Done;
            }

            void reset()
            {
                timer = animationTimer;
                m_CurrentRect = m_StartRect;
            }
        };

        GameDataRef m_Data;

        sf::Sprite& m_Sprite;
        sf::Texture& m_TextureSheet;

        std::map<std::string, Animation*> m_Animations;
        Animation* m_LastAnimation;
        Animation* m_PriorityAnimation;

    public:
        AnimationComponent(GameDataRef data, sf::Sprite& sprite, const std::string& texture);
        virtual ~AnimationComponent();

        /* Accessor */
        /*
         * isDone: checks if an animation is complete or not
         * @param key: name of action of which we want to run animation,
         * */
        const bool& isDone( const std::string& key );

        /* Functions */

        /*
         * AddAnimation: Add animation for our sprite ( starting and ending point )
         * @param key: name of action of which we want to run animation,
         * @param animation_timer: duration for which animation is to be run
         * @param start_frame_x: starting frame in x-axis for animation
         * @param start_frame_y: starting frame in y-axis for animation
         * @param frames_x: number of frames in x-axis starting start_frame_x
         * @param frames_y: number of frames in y-axis starting start_frame_y
         * @param width: width of tile
         * @param height: height of tile
         * */
        void AddAnimation( const std::string& key,
                float animation_timer,
                int start_frame_x, int start_frame_y,
                int frames_x, int frame_y, int width, int height );

        /*
         * Play: Play animation
         * @param key:
         * @param dt:
         * @param priority:
         * @param new_timer:
         * */
        const bool& Play(const std::string &key, const float &dt, const bool &priority = false, float new_timer = 0 );
        const bool& Play(const std::string& key, const float& dt,
                const float& modifier, const float& modifier_max, const bool priority = false);

    };
}

#endif // ANIMATIONCOMPONENT_H
