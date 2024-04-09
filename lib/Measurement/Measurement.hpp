#ifndef __MEASUREMENT_H__
#define __MEASUREMENT_H__

typedef enum measurement_type_t
{
  TEMPERATURE,
  HUMIDITY
} measurementType;

typedef struct measurement_t
{
  measurementType type;
  union
  {
    float floatValue;
  } value;

} Measurement;

#endif