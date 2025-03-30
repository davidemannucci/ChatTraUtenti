#include <set>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

class IdCreator{
    public:
        static int createId();
        static void reset();

    private:
        static std::unordered_set<int> idUsed;
};