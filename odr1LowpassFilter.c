/*!---------------------------------------------------------------------------------------
 * @brief      Simple First Order Filter structure.
 * @author     Sourav Sahoo
 * @date       17 April 2020
 *//*-----------------------------------------------------------------------------------*/
typedef struct filter_order1_tag
{
    /** input */
    float32_t * rawInput_f32pc;
    /** previous averaged data */
    float32_t avgOld_f32;
    /** averaged data */
    float32_t avg_f32;
    /** filter factor */
    float32_t factor_f32;
} filter_order1_t;
/**---------------------------------------------------------------------------------------
 * @brief         The average is calculated.
 * @author        Sourav Sahoo
 * @date          14 April 2020
 * @param[in,out] avrg_stpc  pointer to destination.
 *                \n range N/A, unit N/A res N/A scope RAM
 * @param[in]     numOfEntrys_u16c  number average entries.
 *                \n range N/A, unit N/A res N/A scope RAM
 *
 *                y[k]=αu[k]+(1−α)y[k−1]   where   α=1−e−ωc⋅Ts
 *//*-----------------------------------------------------------------------------------*/
#pragma CODE_SECTION(order1Filter_Calculate_vd, "ramfuncs")
void order1Filter_Calculate_vd(filter_order1_t * const avrg_stpc,const uint16_t numOfEntrys_u16c)
{
    uint8_t idx_u8 = 0u;
    do
    {
        avrg_stpc[idx_u8].avg_f32 = (avrg_stpc[idx_u8].factor_f32) * (*avrg_stpc[idx_u8].rawInput_f32pc)+
                ((1-avrg_stpc[idx_u8].factor_f32)*avrg_stpc[idx_u8].avgOld_f32);
        avrg_stpc[idx_u8].avgOld_f32=avrg_stpc[idx_u8].avg_f32;
        idx_u8++;
    }while(idx_u8 < numOfEntrys_u16c);
}
