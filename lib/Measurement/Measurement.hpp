#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__

typedef enum measurement_type_t
{
  TEMPERATURE,
  HUMIDITY,
  CO2
} measurementType;

typedef struct measurement_t
{
  measurementType type;
  union
  {
    float floatValue;
    int intValue;
  } value;

} Measurement;

#endif