#include <set>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

class IdCreator{
    public:
        static std::unordered_set<int> idUsed;
        static int createId();
};