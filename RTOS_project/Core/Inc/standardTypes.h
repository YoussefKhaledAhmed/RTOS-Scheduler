/*
 * Name: Youssef Khaled Ahmed
 * Date: 15/8/2023
 */

#ifndef STANDARDTYPES_H_
#define STANDARDTYPES_H_

#define uint8_t         char
#define uint16_t        short
#define uint32_t        int
#define uin64_t         long long
#define float32_t       float
#define bool            char
#define STATUS          char
#define TRUE            (1U)
#define FALSE           (0U)
#define LOGIC_HIGH      (1U)
#define LOGIC_LOW       (0U)
#define E_OK            (1U)
#define E_NOK           (0U)
#define PIN_HIGH        (1U)
#define PIN_LOW         (0U)
#define STD_ON          (1U)
#define STD_OFF         (0U)
#define NULL            (0U)

#define Std_ReturnType  uint8_t
typedef enum{
	RTE_E_OK,
	RTE_E_NOK
} RT_STATUs;



#endif /* STANDARDTYPES_H_ */
