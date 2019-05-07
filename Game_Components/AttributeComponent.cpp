#include "AttributeComponent.h"


AttributeComponent::AttributeComponent()
{
    timer = 30.f;
}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::UpdatePoints()
{

    timer += 5.f;
}

void AttributeComponent::UpdateTime( const float& dt )
{
    timer -= dt;
}