#include <set>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

class IdCreator{
    public:
        static int createId();

    private:
        static std::unordered_set<int> idUsed;
};