#include <memory>

class IScales
{
public:
    virtual double getWeight() = 0;
    virtual ~IScales()         = default;
};

class RussianScales : public IScales
{
    double _currentWeight;

public:
    RussianScales(const double weight) : _currentWeight(weight) {}

    double getWeight() override
    {
        return _currentWeight;
    }
};

class BritishScales
{
    double _currentWeight;

public:
    BritishScales(const double weight) : _currentWeight(weight) {}

    double getWeight()
    {
        return _currentWeight;
    }
};

class AdapterForBritishScales : public IScales
{
    std::unique_ptr<BritishScales> _bs;
    double                         _currentWeight;

public:
    AdapterForBritishScales(std::unique_ptr<BritishScales> bs)
        : _bs(std::move(bs)), _currentWeight(0)
    {
    }

    double getWeight() override
    {
        _currentWeight = _bs->getWeight();
        return _currentWeight *= 0.5;
    }
};
