#include "touch.h"

//X- PA3
//X+ PA1
//Y- PA8
//Y+ PA2

uint16_t x_ori,y_ori;

void Touch_Config(void)
{
  //IO��ʼ��
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

  //X-���
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIOA->BSRRH = GPIO_Pin_3;
  
  //Y+����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Touch_Detect(void)
{
  if (((GPIOA->IDR)&0x04)!=0x04)
  {
    Delay(1);
    if (((GPIOA->IDR)&0x04)!=0x04)
    {
      return 1;
    }
  }
  return 0;
}

void Touch_ADCInit(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //��ADC1ʱ��
  ADC_DeInit();
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;  //����Ϊ12λ           
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;   //ɨ��ת��ģʽʧ��
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;  //����ת��ʹ��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //�����ⲿ�������������ת��
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //�����Ҷ��룬���ֽڶ���
  ADC_InitStructure.ADC_NbrOfConversion = 1;    //�涨��˳����й���ת����ADCͨ������Ŀ
  ADC_Init(ADC1, &ADC_InitStructure);      
  
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent; //����ģʽ
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8; //��ƵΪ8
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //ʧ��DMA_MODE
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;//���β������20������
  ADC_CommonInit(&ADC_CommonInitStructure);
  
//  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_480Cycles);//����ͨ�����ã�1��ʾ���������˳��
  
  ADC_Cmd(ADC1, ENABLE);       //ʹ��ADC1
//  ADC_DMACmd(ADC1, ENABLE);        //ʹ��ADC1��DMA
//  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE); //��ͨ��ģʽ���ϴ�ת����ɺ�DMA��������Ҳ���ǳ���DMA
}
  
void Touch_Measure(void)
{
  uint16_t vref;
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  Touch_ADCInit();
  ADC_RegularChannelConfig(ADC1, ADC_Channel_Vrefint, 1, ADC_SampleTime_480Cycles);
  ADC_SoftwareStartConv(ADC1);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
 vref = ADC_GetConversionValue(ADC1);
  
  //X+ģ������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  //Y+ Y-�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  //X-��������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  Touch_ADCInit();
  
  GPIOA->BSRRH = GPIO_Pin_4;
  GPIOA->BSRRL = GPIO_Pin_2;
  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_480Cycles);//����ͨ�����ã�1��ʾ���������˳��
  
  ADC_SoftwareStartConv(ADC1);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
  y_ori = ADC_GetConversionValue(ADC1);
  
    //Y+ģ������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  //X+ X-�������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  //Y-��������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  Touch_ADCInit();
  
  GPIOA->BSRRH = GPIO_Pin_3;
  GPIOA->BSRRL = GPIO_Pin_1;
  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_480Cycles);//����ͨ�����ã�1��ʾ���������˳��
  
  ADC_SoftwareStartConv(ADC1);
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
  x_ori = ADC_GetConversionValue(ADC1);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, DISABLE);
  
  ADC_DeInit();
  
  //X-���
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  //Y+����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  //X+ Y-��������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  x_ori = (x_ori*10)/(vref/30);
  y_ori = (y_ori*10)/(vref/30);
}

void Touch_Measure_Filter(void)
{
  uint32_t x1,y1;
  uint8_t i;
  
  x1=0;y1=0;
  for (i=0;i<5;i++)
  {
    Touch_Measure();
    Delay(1);
    x1+=x_ori;
    y1+=y_ori;
  }
  x_ori=x1/5;
  y_ori=y1/5;
  
}