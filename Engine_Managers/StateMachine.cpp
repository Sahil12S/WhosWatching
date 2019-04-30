#include "StateMachine.h"

StateMachine::StateMachine() = default;

StateMachine::~StateMachine()
{
    while ( !m_States.empty() )
    {
        m_States.pop();
    }
    Debug( "All states destroyed" )
}

void StateMachine::AddState(StateRef newState, bool isReplacing)
{
    m_IsAdding = true;
    m_IsReplacing = isReplacing;

    m_NewState = std::move( newState );
}

void StateMachine::ProcessStateChange()
{
    if ( m_IsRemoving && !m_States.empty() )
    {
        m_States.pop();

        if ( !m_States.empty() )
        {
            Debug( "Resumed top state" )
            m_States.top()->Resume();
        }
        m_IsRemoving = false;
    }

    if ( m_IsAdding )
    {
        if ( !m_States.empty() )
        {
            if (m_IsReplacing)
            {
                m_States.pop();
            } else
            {
                Debug( "Paused top state" )
                m_States.top()->Pause();
            }
        }

        m_States.push( std::move( m_NewState ) );
        m_States.top()->Init();
        m_IsAdding = false;
    }
}

void StateMachine::RemoveState()
{
    m_IsRemoving = true;
}

StateRef& StateMachine::GetActiveState()
{
    return m_States.top();
}

int StateMachine::GetStatesCount()
{
    return m_States.size();
}

void StateMachine::ClearStates()
{
    // Store top state
    StateRef state = std::move ( m_States.top() );

    // Clear the stack
    while ( !m_States.empty() )
    {
        m_States.pop();
    }

    // Put top state back
    m_States.push( std::move( state ) );
}