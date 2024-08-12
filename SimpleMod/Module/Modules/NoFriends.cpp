#include "NoFriends.h"

NoFriends::NoFriends() : IModule(0, Category::PLAYER, "Ignores friend list check.") {
}

NoFriends::~NoFriends() {
}

std::string NoFriends::getModuleName() {
	return ("NoFriends");
}
