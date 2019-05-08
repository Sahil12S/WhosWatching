#include "AttributeComponent.h"


AttributeComponent::AttributeComponent()
{
    timer = 20.f;
    points = 0;
}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::UpdatePoints()
{
    points++;
    timer += 5.f;
    if( timer >= 20.f )
    {
        timer = 20.f;
    }
}

void AttributeComponent::UpdateTime( const float& dt )
{
    timer -= dt;
}