#ifndef HEIGHTGENERATOR_H
#define HEIGHTGENERATOR_H

#include <stdlib.h>
#include <time.h>


class HeightGenerator
{
    public:
        HeightGenerator(){}

        float generateHeight(float x, float z)
        { return getNoise(x, z) * AMPLITUDE; }

    protected:
    private:
        const float AMPLITUDE = 70.0f;
        double random = rand();
        double seed;

        float getNoise(int x, int z)
        {
            srand(x * 234223 + z * 234223);
            random = rand();
            return random;
        }
};

#endif // HEIGHTGENERATOR_H
