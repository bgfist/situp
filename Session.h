#ifndef SESSION_H
#define SESSION_H

#include "User.h"

/**
  Session contains the User object,
  used to maintain the Login info.

*/
class Session
{
public:
    Session();
    static User user;
};

#endif // SESSION_H
