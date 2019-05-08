#include "AttributeComponent.h"


AttributeComponent::AttributeComponent()
{
    timer = MAX_GAME_TIME;
    points = 0;
}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::UpdatePoints()
{
    points++;
    timer += BONUS_TIME;
    if( timer >= MAX_GAME_TIME )
    {
        timer = MAX_GAME_TIME;
    }
}

void AttributeComponent::UpdateTime( const float& dt )
{
    timer -= dt;
}