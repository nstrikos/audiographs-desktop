#ifndef GENSUM_H
#define GENSUM_H

#include <generator/genparameters.h>

class GenSum
{
public:
    GenSum(GenParameters *params);
    void sum();
private:
    GenParameters *m_params;
};

#endif // GENSUM_H
