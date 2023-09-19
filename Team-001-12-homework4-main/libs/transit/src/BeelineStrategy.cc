#include "BeelineStrategy.h"
using namespace std;
BeelineStrategy::BeelineStrategy(Vector3 pos, Vector3 des)
     : PathStrategy({{pos[0], pos[1], pos[2]}, {des[0], des[1], des[2]}}) {
     }

