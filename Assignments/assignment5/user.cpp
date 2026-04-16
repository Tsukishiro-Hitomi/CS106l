#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/** 
  * Destructor 
 */
User::~User() {
  delete[] _friends;
}

/**
 * Copy Constructor
 */
User::User(const User& other) : _name(other._name), _capacity(other._capacity), _size(other._size) {
  _friends = new std::string[_capacity];
  std::copy(other._friends, other._friends + _size, _friends);
}

/**
 * Copy Assignable
 */
User& 
User::operator =(const User& user) {
  if (this != &user) {
    delete[] _friends;
    _name = user._name;
    _capacity = user._capacity;
    _size = user._size;

    _friends = new std::string[_capacity];
    std::copy(user._friends, user._friends + _size, _friends);
  }
  return *this;
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */
std::ostream& 
operator<<(std::ostream& os, const User& u) {
  os << "User(name=" << u._name << ", friends=[";
  for (size_t i = 0; i < u._size; i++) {
    std::string f = u._friends[i];
    os << f;
    if (i != u._size - 1) {
      os << ", ";
    }
  } 
  os << "])";
  return os;
} 

User&
User::operator+=(User& rhs) {
  this->add_friend(rhs.get_name());
  rhs.add_friend(_name);
  return *this;
}

bool 
User::operator<(const User& rhs) const{
  return this->_name < rhs.get_name();
}