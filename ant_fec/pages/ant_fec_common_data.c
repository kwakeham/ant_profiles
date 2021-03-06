/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_FEC)

#include "ant_fec_common_data.h"
#include "ant_fec_utils.h"

#define NRF_LOG_MODULE_NAME ant_fec_common_data
#if ANT_FEC_COMMON_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_FEC_COMMON_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_FEC_COMMON_INFO_COLOR
#else // ANT_FEC_COMMON_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_FEC_COMMON_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief FEC common page data layout structure. */
typedef struct
{
    uint8_t reserved0[2];
    uint8_t instantaneous_cadence;
    uint8_t reserved1[4];
}ant_fec_cadence_data_layout_t;

/**@brief Function for tracing common data.
 *
 * @param[in]  p_common_data      Pointer to the common data.
 */
static void cadence_data_log(ant_fec_common_data_t const * p_common_data)
{
    if (p_common_data->instantaneous_cadence == 0xFF)
    {
        NRF_LOG_INFO("instantaneous cadence:               -- rpm\r\n\n");
    }
    else
    {
        NRF_LOG_INFO("instantaneous cadence:               %u rpm\r\n\n",
                    p_common_data->instantaneous_cadence);
    }
}

void ant_fec_cadence_encode(uint8_t                     * p_page_buffer,
                            ant_fec_common_data_t const * p_common_data)
{
    ant_fec_cadence_data_layout_t * p_outcoming_data = (ant_fec_cadence_data_layout_t *)p_page_buffer;
    p_outcoming_data->instantaneous_cadence           = p_common_data->instantaneous_cadence;

    cadence_data_log(p_common_data);
}

void ant_fec_cadence_decode(uint8_t const         * p_page_buffer,
                            ant_fec_common_data_t * p_common_data)
{
    ant_fec_cadence_data_layout_t const * p_incoming_data = (ant_fec_cadence_data_layout_t *)p_page_buffer;
    p_common_data->instantaneous_cadence                   = p_incoming_data->instantaneous_cadence;

    cadence_data_log(p_common_data);
}

#endif // NRF_MODULE_ENABLED(ANT_FEC)
