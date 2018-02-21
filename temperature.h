#ifndef TEMPERATURE_H
#define TEMPERATURE_H


class Temperature : public Measurement
{
public:
    Temperature(float temp);
private:
    float measurement;
};

#endif // TEMPERATURE_H
