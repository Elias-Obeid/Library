
template <typename NUMERICAL_TYPE>
NUMERICAL_TYPE GCD(NUMERICAL_TYPE X, NUMERICAL_TYPE Y)
{
    if (X == 0)
    {
        return Y;
    }
    return GCD(Y % X, X);
}

template <typename NUMERICAL_TYPE>
NUMERICAL_TYPE LCM(NUMERICAL_TYPE X, NUMERICAL_TYPE Y)
{
    return (1LL * X * Y) / GCD(X, Y);
}
