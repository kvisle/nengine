#include "drawable.h"
#include "input.h"

void
input::subscribe(drawable *s)
{
    subscribers.push_back(s);
}

void
input::unsubscribe(drawable *s)
{
    std::vector<drawable*>::iterator it;

    for ( it=subscribers.begin() ; it < subscribers.end(); it++ )
    {
        if ( *it == s ) {
            it = subscribers.erase(it);
        }
    }

}

void
input::read_input(union ninput in)
{
    for (unsigned int i=0; i < subscribers.size(); i++)
    {
        subscribers[i]->input(in);
    }
}

