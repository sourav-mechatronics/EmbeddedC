/*!---------------------------------------------------------------------------------------
 * @brief      moving avarage Filter structure.
 * @author     Sourav Sahoo
 * @date       14 April 2020
 *//*-----------------------------------------------------------------------------------*/
typedef struct filter_avg_tag
{
    /** input */
    float32_t * rawInput_f32pc;
    /** moving avg bucket */
    float32_t adcRawValue_f32[4];
    /** bucket counter */
    uint8_t count_u8;
    /** sum of sample */
    float32_t sum_f32;
    /** averaged sample */
    float32_t avg_f32;
} filter_avg_t;

/**---------------------------------------------------------------------------------------
 * @brief         The average is calculated.
 * @author        Sourav Sahoo
 * @date          14 April 2020
 * @param[in,out] avrg_stpc  pointer to destination.
 *                \n range N/A, unit N/A res N/A scope RAM
 * @param[in]     numOfEntrys_u16c  number average entries.
 *                \n range N/A, unit N/A res N/A scope RAM
 *                4 samples moving average
 *                y[k]=(u[0]+u[1]+u[2]+u[3])/4
 *//*-----------------------------------------------------------------------------------*/
void movingAvgFilter_Calculate_vd(filter_avg_t * const avrg_stpc,const uint16_t numOfEntrys_u16c)
{
    uint8_t idx_u8 = 0u;
    avrg_stpc[idx_u8].count_u8 = (avrg_stpc[idx_u8].count_u8 + 1) & 0x3U;//0,1,2,3,0,1,2...
    do
    {
        avrg_stpc[idx_u8].adcRawValue_f32[avrg_stpc[idx_u8].count_u8] = (*avrg_stpc[idx_u8].rawInput_f32pc);
        avrg_stpc[idx_u8].sum_f32=avrg_stpc[idx_u8].adcRawValue_f32[0]+avrg_stpc[idx_u8].adcRawValue_f32[1]+
                avrg_stpc[idx_u8].adcRawValue_f32[2]+avrg_stpc[idx_u8].adcRawValue_f32[3];
        avrg_stpc[idx_u8].avg_f32 = (avrg_stpc[idx_u8].sum_f32)*0.25f;
        idx_u8++;
    }while(idx_u8 < numOfEntrys_u16c);
}
