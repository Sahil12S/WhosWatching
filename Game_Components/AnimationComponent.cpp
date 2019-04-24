#include "AnimationComponent.h"

namespace SSEngine
{
    AnimationComponent::AnimationComponent(GameDataRef data, sf::Sprite& sprite, const std::string& texture ) :
        m_Data( std::move( data ) ),  m_Sprite( sprite ), m_TextureSheet( m_Data->assets.GetTexture( texture ) )
    {
        m_LastAnimation = nullptr;
        m_PriorityAnimation = nullptr;
    }

    AnimationComponent::~AnimationComponent()
    {
        for( auto& i: m_Animations )
        {
            delete i.second;
        }
    }

    const bool& AnimationComponent::isDone(const std::string& key)
    {
        return m_Animations[key]->isDone();
    }

    void
    AnimationComponent::AddAnimation(const std::string& key, float animation_timer, int start_frame_x, int start_frame_y,
                                     int frames_x, int frames_y, int width, int height)
    {
        m_Animations[key] = new Animation( m_Sprite, m_TextureSheet, animation_timer,
                start_frame_x, start_frame_y, frames_x, frames_y, width, height );
        Debug( "Animation component created" )
    }

    const bool &AnimationComponent::Play(const std::string &key, const float &dt, const bool &priority, float new_timer )
    {
        // If we want to run animation based on time.
        // NOTE: Not yet implemented
        if ( new_timer > 0.f )
            m_Animations[key]->animationTimer = new_timer;

        if (m_PriorityAnimation) //If there is a priority animation
        {
            if (m_PriorityAnimation == m_Animations[key])
            {
                if (m_LastAnimation != m_Animations[key])
                {
                    if (m_LastAnimation == nullptr)
                    {
                        m_LastAnimation = m_Animations[key];
                    }
                    else
                    {
                        m_LastAnimation->reset();
                        m_LastAnimation = m_Animations[key];
                    }
                }

                //If the priority animation is done, remove it
                if (m_Animations[key]->play(dt))
                {
                    m_PriorityAnimation = nullptr;
                }
            }
        }
        else //Play animation if no other priority animation is set
        {
            //If this is a priority animation, set it.
            if (priority)
            {
                m_PriorityAnimation = m_Animations[key];
            }

            if (m_LastAnimation != m_Animations[key])
            {
                if (m_LastAnimation == nullptr)
                    m_LastAnimation = m_Animations[key];
                else
                {
                    m_LastAnimation->reset();
                    m_LastAnimation = m_Animations[key];
                }
            }

            m_Animations[key]->play(dt);
        }

        return m_Animations[key]->isDone();
    }

    const bool& AnimationComponent::Play(const std::string& key, const float &dt,
            const float &modifier, const float &modifier_max, const bool priority)
    {
        if (m_PriorityAnimation) //If there is a priority animation
        {
            if (m_PriorityAnimation == m_Animations[key])
            {
                if (m_LastAnimation != m_Animations[key])
                {
                    if (m_LastAnimation == nullptr)
                        m_LastAnimation = m_Animations[key];
                    else
                    {
                        m_LastAnimation->reset();
                        m_LastAnimation = m_Animations[key];
                    }
                }

                //If the priority animation is done, remove it
                if (m_Animations[key]->play( dt, abs( modifier / modifier_max ) ) )
                {
                    m_PriorityAnimation = nullptr;
                }
            }
        }
        else //Play animation of no other priority animation is set
        {
            //If this is a priority animation, set it.
            if (priority)
            {
                m_PriorityAnimation = m_Animations[key];
            }

            if (m_LastAnimation != m_Animations[key])
            {
                if (m_LastAnimation == nullptr)
                    m_LastAnimation = m_Animations[key];
                else
                {
                    m_LastAnimation->reset();
                    m_LastAnimation = m_Animations[key];
                }
            }

            m_Animations[key]->play(dt, abs(modifier / modifier_max));
        }

        return m_Animations[key]->isDone();
    }
}