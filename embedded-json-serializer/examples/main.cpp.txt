#include <stdio.h>
#include "json_serializer.h"

int main(void)
{
    /* Sample meter data */
    MeterData meter_data[] = {
        {
            "1970-01-01 00:00",
            "1970-01-01 00:00",
            107.752f,
            "OK"
        }
    };

    /* Sample device reading */
    DeviceReading device_readings[] = {
        {
            "water",
            "waterstarm",
            "stromleser_50898527",
            "m3",
            meter_data,
            1
        }
    };

    /* Gateway data */
    GatewayData gateway = {
        "gateway_1234",
        "1970-01-01",
        "stromleser",
        15,
        1,
        1,
        device_readings
    };

    char json_output[1024];

    int result = serialize_to_json(&gateway,
                                   json_output,
                                   sizeof(json_output));

    if (result == JSON_OK) {
        printf("Generated JSON:\n%s\n", json_output);
    } else {
        printf("Serialization failed (error %d)\n", result);
    }

    return 0;
}
