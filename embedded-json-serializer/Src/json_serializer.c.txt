#include "json_serializer.h"
#include <stdio.h>

/* Helper macro to safely append formatted text */
#define APPEND(fmt, ...)                                   \
    do {                                                    \
        int written = snprintf(output + used,              \
                               buffer_size - used,         \
                               fmt, __VA_ARGS__);           \
        if (written < 0)                                   \
            return JSON_ERROR_INVALID_INPUT;                \
        used += (size_t)written;                            \
        if (used >= buffer_size)                            \
            return JSON_ERROR_BUFFER_TOO_SMALL;             \
    } while (0)

int serialize_to_json(const GatewayData* input,
                      char* output,
                      size_t buffer_size)
{
    if (!input || !output || buffer_size == 0)
        return JSON_ERROR_INVALID_INPUT;

    size_t used = 0;

    /* Outer JSON array */
    APPEND("[{");

    /* Gateway metadata */
    APPEND("\"gatewayId\":\"%s\",", input->gatewayId);
    APPEND("\"date\":\"%s\",", input->date);
    APPEND("\"deviceType\":\"%s\",", input->deviceType);
    APPEND("\"interval_minutes\":%d,", input->interval_minutes);
    APPEND("\"total_readings\":%d,", input->total_readings);

    /* Values object */
    APPEND("\"values\":{");
    APPEND("\"device_count\":%d,", input->device_count);
    APPEND("\"readings\":[");

    for (int i = 0; i < input->device_count; i++) {
        DeviceReading* dev = &input->readings[i];

        APPEND("{");
        APPEND("\"media\":\"%s\",", dev->media);
        APPEND("\"meter\":\"%s\",", dev->meter);
        APPEND("\"deviceId\":\"%s\",", dev->deviceId);
        APPEND("\"unit\":\"%s\",", dev->unit);
        APPEND("\"data\":[");

        for (int j = 0; j < dev->data_count; j++) {
            MeterData* md = &dev->data[j];

            APPEND("{");
            APPEND("\"timestamp\":\"%s\",", md->timestamp);
            APPEND("\"meter_datetime\":\"%s\",", md->meter_datetime);
            APPEND("\"total_m3\":%.3f,", md->total_m3);
            APPEND("\"status\":\"%s\"", md->status);
            APPEND("}");

            if (j < dev->data_count - 1)
                APPEND(",");
        }

        APPEND("]}");

        if (i < input->device_count - 1)
            APPEND(",");
    }

    APPEND("]}");
    APPEND("}]");

    return JSON_OK;
}
