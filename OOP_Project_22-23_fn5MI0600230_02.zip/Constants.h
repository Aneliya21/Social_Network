#pragma once
#include "String.h"

static const unsigned SIZE_OF_INT = sizeof(int);
static const unsigned SIZE_OF_UNS = sizeof(unsigned);

//NETWORK USER
static const char ENTER_FIRST_NAME[] = ">> Enter first name: ";
static const char ENTER_LAST_NAME[] = ">> Enter last name: ";
static const char ENTER_PASS[] = ">> Enter password: ";

static const char FIRST_NAME[] = "-->> First name: ";
static const char LAST_NAME[] = "-->>>> Last name: ";
static const char POINTS[] = "-->> Points: ";

//TOPIC
static const char ENTER_TOPIC_NAME[] = ">> Enter topic name: ";
static const char ENTER_TOPIC_CONTENT[] = ">> Enter topic content: ";
			 
static const char TOPIC_NAME[] = ">> Topic name: ";
static const char TOPIC_CREATOR[] = ">> Topic creator: ";
static const char TOPIC_CONTENT[] = ">> Topic content: ";
static const char TOPIC_POSTS[] = ">> Topic posts: ";

static const char TOPIC_ID[] = "{id:";

//POST
static const char ENTER_POST_TITLE[] = ">> Enter title: ";
static const char ENTER_POST_CONTENT[] = ">> Enter content: ";
			 
static const char POST_TITLE[] = ">> Post title: ";
static const char POST_ID[] = /*>> Post id:*/" {id:";
static const char CLOSE_BRACK[] = "}";
static const char SUCCESS[] = "Success! ";
			 
static const char POST_ERROR[] = "Post error! ";

//COMMAND SIGNUP
static const String SIGNUP = "signup";

//COMMAND LOGIN
static const char ALREADY_LOGGED[] = "User has already logged in! ";
static const char NOT_EXISTING_ACCOUNT[] = "No such user found in the system! ";
static const String LOGIN = "login";

//COMMAND LOGOUT
static const String LOGOUT = "logout";

//COMMAND SEARCH
static const String SEARCH = "search";
static const char SEARCH_ERROR[] = "Search error! ";

//COMMAND OPEN
static const String OPEN = "open";
static const char OPENED_TOPIC[] = ">> Welcome to: ";
static const char OPEN_ERROR[] = "Open error! ";

//COMMAND LIST
static const char LIST_ERROR[] = "List error! ";

//COMMAND P_OPEN
static const String pOPEN = "p_open";
static const char P_OPEN[] = "Q: ";

//COMMAND LIST
static const String LIST = "list";

//COMMAND POST
static const String POST = "post";

//COMMAND CREATE
static const String CREATE = "create";
static const char CREATION_ERROR[] = "Creation error! ";

//COMMAND COMMENT
static const String COMMENT_ = "comment";
static const char COMMENT[] = ">> Say something: ";
static const char COMMENT_ERROR[] = "Comment error! ";

//COMMAND COMMENTS
static const String COMMENTS = "comments";

//COMMAND REPLY
static const String REPLY = "reply";
static const char POSTED[] = ">> Posted! ";
static const char REPLY_ERROR[] = "Reply_error! ";

//COMMAND UP_VOTE
static const String UP_VOTE = "upvote";

//COMMAND DOWN_VOTE
static const String DOWN_VOTE = "downvote";

//COMMAND QUIT
static const String QUIT = "quit";
static const char QUIT_ERROR[] = "Quit error! ";

//COMMAND P_CLOSE
static const String P_CLOSE = "p_close";
static const char P_CLOSE_ERROR[] = "p_close error! ";

//COMMAND WHOAMI
static const String WHOAMI = "whoami";
static const char WHOAMI_ERROR[] = "WhoAmI error! ";

//COMMAND ABOUT
static const String ABOUT = "about";
static const char ABOUT_ERROR[] = "About error! ";

//COMMAND EXIT
static const String EXIT = "exit";
