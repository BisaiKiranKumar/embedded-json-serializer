#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>

/* Error codes */
#define JSON_OK 0
#define JSON_ERROR_BUFFER_TOO_SMALL -1
#define JSON_ERROR_INVALID_INPUT   -2

/* Meter data point */
typedef struct {
    const char* timestamp;
    const char* meter_datetime;
    float total_m3;
    const char* status;
} MeterData;

/* Device reading */
typedef struct {
    const char* media;
    const char* meter;
    const char* deviceId;
    const char* unit;
    MeterData* data;
    int data_count;
} DeviceReading;

/* Gateway-level data */
typedef struct {
    const char* gatewayId;
    const char* date;
    const char* deviceType;
    int interval_minutes;
    int total_readings;
    int device_count;
    DeviceReading* readings;
} GatewayData;

/* Serialization API */
int serialize_to_json(const GatewayData* input,
                      char* output,
                      size_t buffer_size);



#endif /* JSON_SERIALIZER_H */

