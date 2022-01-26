
template <class NUMERICAL_TYPE>
NUMERICAL_TYPE fast_exp(NUMERICAL_TYPE base, NUMERICAL_TYPE power, NUMERICAL_TYPE modulo = MOD)
{
    NUMERICAL_TYPE result = 1;
    while (power != 0)
    {
        if (power % 2 == 1)
        {
            result = (result * base) % modulo;
        }
        base = (base * base) % modulo;
        power = (power / 2);
    }
    return result;
}
