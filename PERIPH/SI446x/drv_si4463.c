/**
  ******************************************************************************
  * @file    drv_si446x.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-02-23
  * @brief   
  ******************************************************************************
  */

#include "drv_si4463.h"

const static uint8_t config_table[] = RADIO_CONFIGURATION_DATA_ARRAY;

/**
  * @brief :SI446x�ȴ�CTS״̬
  * @param :��
  * @note  :��
  * @retval:��
  */ 
void SI446x_Wait_Cts( void )
{
    uint8_t l_Cts;
	uint16_t l_ReadCtsTimes = 0;
	
    do
    {
        SI_SET_CSN_LOW( );		//SPIƬѡ
		
		//��CTS״̬
        drv_spi_read_write_byte( READ_CMD_BUFF );
        l_Cts = drv_spi_read_write_byte( 0xFF );		
		
        SI_SET_CSN_HIGH( );		//ȡ��SPIƬѡ
		
		if( 1000 == l_ReadCtsTimes++ )
		{
			SI446x_Init( );
			break;
		}
		
	}while( l_Cts != 0xFF );	//ֱ����CTS�ķ���ֵ����0xFF
}

/**
  * @brief :SI446xд����
  * @param :
  *			@pCmd:�����׵�ַ
  *			@CmdNumber���������
  * @note  :��
  * @retval:��
  */ 
void SI446x_Write_Cmds( uint8_t *pCmd, uint8_t CmdNumber )
{
    SI446x_Wait_Cts( );			//��ѯCTS״̬
	
    SI_SET_CSN_LOW( );			//SPIƬѡ
	
    while( CmdNumber -- )
    {
        drv_spi_read_write_byte( *pCmd );	//��������
		pCmd++;
    }
	
    SI_SET_CSN_HIGH( );			//ȡ��SPIƬѡ
}

/**
  * @brief :SI446x POWER_UP
  * @param :
  *			@Xo_Freq:����Ƶ��
  * @note  :SI446x��λ֮����Ҫ����
  * @retval:��
  */
void SI446x_Power_Up( uint32_t Xo_Freq )
{
    uint8_t l_Cmd[7] = { 0 };
	
    l_Cmd[0] = POWER_UP;		//Power_Up����
    l_Cmd[1] = 0x01;
    l_Cmd[2] = 0x00;
    l_Cmd[3] = Xo_Freq >> 24;
    l_Cmd[4] = Xo_Freq >> 16;
    l_Cmd[5] = Xo_Freq >> 8;
    l_Cmd[6] = Xo_Freq;
    SI446x_Write_Cmds( l_Cmd, 7 );	//д����
}

/**
  * @brief :SI446x��CTS������Ӧ��
  * @param :
  *			@pRead:���������׵�ַ
  *			@Length:����
  * @note  :��
  * @retval:��
  */
void SI446x_Read_Response( uint8_t *pRead, uint8_t Length )
{
    SI446x_Wait_Cts( );		//��ѯCTS״̬
    SI_SET_CSN_LOW( );		//SPIƬѡ
	
	drv_spi_read_write_byte( READ_CMD_BUFF );	//���Ͷ�����
	while( Length-- )
    {
        *pRead = drv_spi_read_write_byte( 0xFF );	//��������
		pRead++;
    }
	
    SI_SET_CSN_HIGH( );		//SPIȡ��Ƭѡ

}

/**
  * @brief :SI446x�ղ���
  * @param :��
  * @note  :��
  * @retval:��
  */
uint8_t SI446x_Nop( void )
{
    uint8_t l_Cts;
	
    SI_SET_CSN_LOW( );		//SPIƬѡ
	
    l_Cts = drv_spi_read_write_byte( NOP );	//�ղ�������
	
    SI_SET_CSN_HIGH( );		//SPIȡ��Ƭѡ
	
	return l_Cts;
}

/**
  * @brief :SI446x���豸������Ϣ
  * @param :
  *			@pRead:���������׵�ַ
  * @note  :��
  * @retval:��
  */
void SI446x_Get_Part_Informatoin( uint8_t *pRead )
{
    uint8_t l_Cmd = PART_INFO;

    SI446x_Write_Cmds( &l_Cmd, 1 );		//����
    SI446x_Read_Response( pRead, 8 );	//���豸������Ϣ

}

/**
  * @brief :SI446x���豸���ܰ汾��Ϣ
  * @param :
  *			@pRead:���������׵�ַ
  * @note  :��
  * @retval:��
  */
void SI446x_Get_Fun_Informatoin( uint8_t *pRead )
{
    uint8_t l_Cmd = FUNC_INFO;

    SI446x_Write_Cmds( &l_Cmd, 1 );		//����
    SI446x_Read_Response( pRead, 7 );	//���豸���ܰ汾��Ϣ
}

/**
  * @brief :SI446x���ж�״̬
  * @param :
  *			@pRead:���������׵�ַ
  * @note  :��
  * @retval:��
  */
void SI446x_Interrupt_Status( uint8_t *pRead )
{
    uint8_t l_Cmd[ 4 ] = { 0 };
	
    l_Cmd[0] = GET_INT_STATUS;		
    l_Cmd[1] = 0;
    l_Cmd[2] = 0;
    l_Cmd[3] = 0;

    SI446x_Write_Cmds( l_Cmd, 4 );		//�����ж϶�ȡ����
    SI446x_Read_Response( pRead, 9 );	//��ȡ״̬
}

/**
  * @brief :SI446x��ȡ����ֵ
  * @param :
  *			@Group_Num:������(�ο�SI446X_PROPERTY)
  *			@Num_Props:��ȡ�����Ը���
  *			@pRead:���������׵�ַ
  * @note  :��
  * @retval:��
  */
void SI446x_Get_Property( SI446X_PROPERTY Group_Num, uint8_t Num_Props, uint8_t *pRead  )
{
    uint8_t l_Cmd[ 4 ] = { 0 };

    l_Cmd[ 0 ] = GET_PROPERTY;
    l_Cmd[ 1 ] = Group_Num >> 8;
    l_Cmd[ 2 ] = Num_Props;
    l_Cmd[ 3 ] = Group_Num;

    SI446x_Write_Cmds( l_Cmd, 4 );		//���Ͷ�ȡ��������
    SI446x_Read_Response( pRead, Num_Props + 1 );	//������
}

/**
  * @brief :SI446x��������
  * @param :
  *			@Group_Num:������(�ο�SI446X_PROPERTY)
  *			@Num_Props:���õ����Ը���
  *			@pWrite:д��ַ�豸
  * @note  :��
  * @retval:��
  */
void SI446x_Set_Property( SI446X_PROPERTY Group_Num, uint8_t Num_Props, uint8_t *pWrite )
{
    uint8_t l_Cmd[ 20 ] = { 0 }, i = 0;
	
    if( Num_Props >= 16 )   
	{ 
		return; 	//����������16
	}
	
    l_Cmd[ i++ ] = SET_PROPERTY;		//������������
    l_Cmd[ i++ ] = Group_Num >> 8;
    l_Cmd[ i++ ] = Num_Props;
    l_Cmd[ i++ ] = Group_Num;
	
    while( Num_Props-- )
    {
        l_Cmd[ i++ ] = *pWrite;
		pWrite++;
    }
    SI446x_Write_Cmds( l_Cmd, i );		//�����������
}

/**
  * @brief :SI446x����������1����
  * @param :
  *			@Group_Num:������
  *			@Start_Prop:��ʼ���õ����Ժ�(�ο�SI446X_PROPERTY)
  * @note  :��
  * @retval:��
  */
void SI446x_Set_Property_1( SI446X_PROPERTY Group_Num, uint8_t Start_Prop )
{
    uint8_t l_Cmd[ 5 ] = { 0 };

    l_Cmd[ 0 ] = SET_PROPERTY;		//����
    l_Cmd[ 1 ] = Group_Num >> 8;
    l_Cmd[ 2 ] = 1;
    l_Cmd[ 3 ] = Group_Num;
    l_Cmd[ 4 ] = Start_Prop;
	
    SI446x_Write_Cmds( l_Cmd, 5 );	//����������������
}

/**
  * @brief :SI446x��ȡ������1����
  * @param :
  *			@Group_Num:��ʼ�����Ժ�(�ο�SI446X_PROPERTY)
  * @note  :��
  * @retval:��
  */
uint8_t SI446x_Get_Property_1( SI446X_PROPERTY Group_Num )
{
    uint8_t l_Cmd[ 4 ] = { 0 };

    l_Cmd[ 0 ] = GET_PROPERTY;
    l_Cmd[ 1 ] = Group_Num >> 8;
    l_Cmd[ 2 ] = 1;
    l_Cmd[ 3 ] = Group_Num;
    SI446x_Write_Cmds( l_Cmd, 4 );		//��������
	
    SI446x_Read_Response( l_Cmd, 2 );	//��ȡ����
	
    return l_Cmd[ 1 ];
}

/**
  * @brief :SI446x��λ
  * @param :��
  * @note  :��
  * @retval:��
  */
void SI446x_Reset( void )
{
    SI_SET_SDN_HIGH( );		//���豸
	  delay_us( 20 );		//��ʱ �ȴ��豸��ȫ�ϵ�
    SI_SET_SDN_LOW( );		//���豸
    SI_SET_CSN_HIGH( );		//ȡ��SPIƬѡ
//	drv_delay_us( 35 );
}

/**
  * @brief :SI446x����GPIO
  * @param :��
  * @note  :��
  * @retval:��
  */
void SI446x_Config_Gpio( uint8_t Gpio_0, uint8_t Gpio_1, uint8_t Gpio_2, uint8_t Gpio_3, uint8_t Irq, uint8_t Sdo, uint8_t Gen_Config )
{
    uint8_t l_Cmd[ 10] = { 0 };
	
    l_Cmd[ 0 ] = GPIO_PIN_CFG;
    l_Cmd[ 1 ] = Gpio_0;
    l_Cmd[ 2 ] = Gpio_1;
    l_Cmd[ 3 ] = Gpio_2;
    l_Cmd[ 4 ] = Gpio_3;
    l_Cmd[ 5 ] = Irq;
    l_Cmd[ 6 ] = Sdo;
    l_Cmd[ 7 ] = Gen_Config;
	
    SI446x_Write_Cmds( l_Cmd, 8 );		//д����
    SI446x_Read_Response( l_Cmd, 8 );	//������
}

/**
  * @brief :SI446xģ������
  * @param :��
  * @note  :��
  * @retval:��
  */
void SI446x_Config_Init( void )
{
    uint8_t i;
    uint16_t j = 0;

    while( ( i = config_table[j] ) != 0 )
    {
        j += 1;
        SI446x_Write_Cmds( (uint8_t *)config_table + j, i );
        j += i;
    }
#if PACKET_LENGTH > 0           //�̶����ݳ���
	
    SI446x_Set_Property_1( PKT_FIELD_1_LENGTH_7_0, PACKET_LENGTH );
	
#else                           //��̬���ݳ���
	
    SI446x_Set_Property_1( PKT_CONFIG1, 0x00 );
    SI446x_Set_Property_1( PKT_CRC_CONFIG, 0x00 );
    SI446x_Set_Property_1( PKT_LEN_FIELD_SOURCE, 0x01 );
    SI446x_Set_Property_1( PKT_LEN, 0x2A );
    SI446x_Set_Property_1( PKT_LEN_ADJUST, 0x00 );
    SI446x_Set_Property_1( PKT_FIELD_1_LENGTH_12_8, 0x00 );
    SI446x_Set_Property_1( PKT_FIELD_1_LENGTH_7_0, 0x01 );
    SI446x_Set_Property_1( PKT_FIELD_1_CONFIG, 0x00 );
    SI446x_Set_Property_1( PKT_FIELD_1_CRC_CONFIG, 0x00 );
    SI446x_Set_Property_1( PKT_FIELD_2_LENGTH_12_8, 0x00 );
    SI446x_Set_Property_1( PKT_FIELD_2_LENGTH_7_0, 0x20 );
    SI446x_Set_Property_1( PKT_FIELD_2_CONFIG, 0x00 );
    SI446x_Set_Property_1( PKT_FIELD_2_CRC_CONFIG, 0x00 );
	
#endif 
	
	//4463 ��GDO2 GDO3������Ƶ���� 33 32
	// ���䣺GDO2 = 0, GDO3 = 1
	// ���գ�GDO2 = 1, GDO3 = 0
    SI446x_Config_Gpio( 0, 0, 33|0x40, 32|0x40, 0, 0, 0 );    //4463����Ҫ����
}

/**
  * @brief :SI446xдTX FIFO
  * @param :
  *			@pWriteData��д�����׵�ַ
  *			@Length�����ݳ���
  * @note  :��
  * @retval:��
  */
void SI446x_Write_TxFifo( uint8_t *pWriteData, uint8_t Length )
{
    SI_SET_CSN_LOW( );
    drv_spi_read_write_byte( WRITE_TX_FIFO );		//д����
    while( Length-- )    
	{ 
		drv_spi_read_write_byte( *pWriteData++ ); 	//д����
	}
    SI_SET_CSN_HIGH( );
}

/**
  * @brief :SI446x ��λRX FIFO
  * @param :��
  * @note  :��
  * @retval:��
  */
void SI446x_Reset_RxFifo( void )
{
    uint8_t l_Cmd[ 2 ] = { 0 };

    l_Cmd[ 0 ] = FIFO_INFO;
    l_Cmd[ 1 ] = 0x02;
    SI446x_Write_Cmds( l_Cmd, 2 );
}

/**
  * @brief :SI446x ��λTX FIFO
  * @param :��
  * @note  :��
  * @retval:��
  */
void SI446x_Reset_TxFifo( void )
{
    uint8_t l_Cmd[ 2 ] = { 0 };

    l_Cmd[0] = FIFO_INFO;
    l_Cmd[1] = 0x02;
    SI446x_Write_Cmds( l_Cmd, 2 );
}

/**
  * @brief :SI446x�������ݰ�
  * @param :
  *			@pTxData�����������׵�ַ
  *			@Length�����ݳ���
  *			@Channel��ͨ��
  *			@Condition������״��ѡ��
  * @note  :��
  * @retval:��
  */
void SI446x_Send_Packet( uint8_t *pTxData, uint8_t Length, uint8_t Channel, uint8_t Condition )
{
    uint8_t l_Cmd[ 5 ] = { 0 };
    uint8_t tx_len = Length;

    SI446x_Reset_TxFifo( );		//���TX FIFO

    SI_SET_CSN_LOW( );		
	
    drv_spi_read_write_byte( WRITE_TX_FIFO );	//дTX FIFO����
	
#if PACKET_LENGTH == 0			//��̬���ݳ���
	
    tx_len ++;
    drv_spi_read_write_byte( Length );
	
#endif
	
    while( Length-- )    
	{
		drv_spi_read_write_byte( *pTxData++ ); 	//д���ݵ�TX FIFO
	}
	
    SI_SET_CSN_HIGH( );
	
    l_Cmd[ 0 ] = START_TX;
    l_Cmd[ 1 ] = Channel;
    l_Cmd[ 2 ] = Condition;
    l_Cmd[ 3 ] = 0;
    l_Cmd[ 4 ] = tx_len;
	
    SI446x_Write_Cmds( l_Cmd, 5 );		//�������ݰ�
}

/**
  * @brief :SI446x��������
  * @param :
  *			@Length�����ݳ���
  *			@Channel��ͨ��
  *			@Condition������״��ѡ��
  * @note  :��
  * @retval:��
  */
void SI446x_Start_Tx( uint8_t Channel, uint8_t Condition, uint16_t Length )
{
    uint8_t l_Cmd[5] = { 0 };

    l_Cmd[ 0 ] = START_TX;		
    l_Cmd[ 1 ] = Channel;
    l_Cmd[ 2 ] = Condition;
    l_Cmd[ 3 ] = Length >> 8;
    l_Cmd[ 4 ] = Length;
	
    SI446x_Write_Cmds( l_Cmd, 5 );
}

/**
  * @brief :SI446x��RX FIFO����
  * @param :
  *			@pRxData�������׵�ַ
  * @note  :��
  * @retval:���ݸ���
  */
uint8_t SI446x_Read_Packet( uint8_t *pRxData )
{
    uint8_t length = 0, i = 0;
	
    SI446x_Wait_Cts( );
    SI_SET_CSN_LOW( );

    drv_spi_read_write_byte( READ_RX_FIFO );	//��FIFO����
	
#if PACKET_LENGTH == 0
	
    length = drv_spi_read_write_byte( 0xFF );	//�����ݳ���
	
#else
	
    length = PACKET_LENGTH;
	
#endif
    i = length;

    while( length -- )
    {
        *pRxData++ = drv_spi_read_write_byte( 0xFF );	//������
    }
	
    SI_SET_CSN_HIGH( );		//�������ݸ���
	
    return i;
}

/**
  * @brief :SI446x��������
  * @param :
  *			@Channel��ͨ��
  *			@Condition����ʼ����״̬
  *			@Length�����ճ���
  *			@Next_State1����һ��״̬1
  *			@Next_State2����һ��״̬2
  *			@Next_State3����һ��״̬3
  * @note  :��
  * @retval:��
  */
void SI446x_Start_Rx( uint8_t Channel, uint8_t Condition, uint16_t Length, uint8_t Next_State1, uint8_t Next_State2, uint8_t Next_State3 )
{
    uint8_t l_Cmd[ 8 ] = { 0 };
	
    SI446x_Reset_RxFifo( );
    SI446x_Reset_TxFifo( );
	
    l_Cmd[ 0 ] = START_RX;
    l_Cmd[ 1 ] = Channel;
    l_Cmd[ 2 ] = Condition;
    l_Cmd[ 3 ] = Length >> 8;
    l_Cmd[ 4 ] = Length;
    l_Cmd[ 5 ] = Next_State1;
    l_Cmd[ 6 ] = Next_State2;
    l_Cmd[ 7 ] = Next_State3;
	
    SI446x_Write_Cmds( l_Cmd, 8 );
}

/**
  * @brief :SI446x��ȡ��ǰ���ݰ���Ϣ
  * @param :
  *			@pReadData�����ݴ�ŵ�ַ
  *			@FieldNumMask��������
  *			@Length������
  *			@DiffLen����ͬ����
  * @note  :��
  * @retval:��
  */
void SI446x_Get_Packet_Information( uint8_t *pReadData, uint8_t FieldNumMask, uint16_t Length, uint16_t DiffLen )
{
    uint8_t l_Cmd[ 6 ] = { 0 };
	
    l_Cmd[ 0 ] = PACKET_INFO;
    l_Cmd[ 1 ] = FieldNumMask;
    l_Cmd[ 2 ] = Length >> 8;
    l_Cmd[ 3 ] = Length;
    l_Cmd[ 4 ] = DiffLen >> 8;
    l_Cmd[ 5 ] = DiffLen;

    SI446x_Write_Cmds( l_Cmd, 6 );
    SI446x_Read_Response( pReadData, 3 );
}

/**
  * @brief :SI446x��ȡFIFO״̬
  * @param :
  *			@pReadData�����ݴ�ŵ�ַ
  * @note  :��
  * @retval:��
  */
void SI446x_Get_Fifo_Information( uint8_t *pReadData )
{
    uint8_t l_Cmd[ 2 ] = { 0 };
	
    l_Cmd[ 0 ] = FIFO_INFO;
    l_Cmd[ 1 ] = 0x03;

    SI446x_Write_Cmds( l_Cmd, 2 );
    SI446x_Read_Response( pReadData, 3 );
}

/**
  * @brief :SI446x״̬�л�
  * @param :
  *			@NextStatus����һ��״̬
  * @note  :��
  * @retval:��
  */
void SI446x_Change_Status( uint8_t NextStatus )
{
    uint8_t l_Cmd[ 2 ] = { 0 };
	
    l_Cmd[ 0 ] = CHANGE_STATE;
    l_Cmd[ 1 ] = NextStatus;
	
    SI446x_Write_Cmds( l_Cmd, 2 );
}

/**
  * @brief :SI446x��ȡ�豸��ǰ״̬
  * @param :
  * @note  :��
  * @retval:�豸��ǰ״̬
  */
uint8_t SI446x_Get_Device_Status( void )
{
   uint8_t l_Cmd[ 3 ] = { 0 };
   
   l_Cmd [ 0 ] = REQUEST_DEVICE_STATE;
   
   SI446x_Write_Cmds( l_Cmd, 1 );
   SI446x_Read_Response( l_Cmd, 3 );
   
   return l_Cmd[ 1 ] & 0x0F;
}

/**
  * @brief :SI446x��������
  * @param :
  *			@PowerLevel�����ݴ�ŵ�ַ
  * @note  :��
  * @retval:�豸��ǰ״̬
  */
void SI446x_Set_Power( uint8_t PowerLevel )
{
    SI446x_Set_Property_1( PA_PWR_LVL, PowerLevel );
}

/**
  * @brief :SI446x���ų�ʼ��
  * @param :��
  * @note  :��
  * @retval:��
  */
void SI446x_Gpio_Init( void )
{
	GPIO_InitTypeDef GpioInitStructer;
	
	//�����Ŷ˿�ʱ��
	RCC_AHB1PeriphClockCmd( SI4463_SDN_CLK | SI4463_IRQ_CLK | SI4463_GPIO0_CLK | SI4463_GPIO1_CLK | SI4463_GPIO2_CLK | SI4463_GPIO3_CLK, ENABLE );
	
	//SDN ��������Ϊ�������
	GpioInitStructer.GPIO_Mode  = GPIO_Mode_OUT;
	GpioInitStructer.GPIO_Speed = GPIO_Speed_50MHz;
	GpioInitStructer.GPIO_OType = GPIO_OType_PP;
	GpioInitStructer.GPIO_PuPd  = GPIO_PuPd_UP;
	GpioInitStructer.GPIO_Pin   = SI4463_SDN_PIN;
	GPIO_Init( SI4463_SDN_PORT, &GpioInitStructer );	
	
	//IRQ GPIO0~GPIO3���� �����ⲿ�ź��ж����� Demo������ò�ѯ��ʽ δ���ó��ж�
	GpioInitStructer.GPIO_Mode  = GPIO_Mode_IN;
	GpioInitStructer.GPIO_PuPd  = GPIO_PuPd_UP;
	
	GpioInitStructer.GPIO_Pin = SI4463_IRQ_PIN;
	GPIO_Init( SI4463_IRQ_PORT, &GpioInitStructer );	//IRQ
	
	GpioInitStructer.GPIO_Pin = SI4463_GPIO0_PIN;
	GPIO_Init( SI4463_GPIO0_PORT, &GpioInitStructer );	//GPIO0
	
	GpioInitStructer.GPIO_Pin = SI4463_GPIO1_PIN;
	GPIO_Init( SI4463_GPIO1_PORT, &GpioInitStructer );	//GPIO1
	
	GpioInitStructer.GPIO_Pin = SI4463_GPIO2_PIN;
	GPIO_Init( SI4463_GPIO2_PORT, &GpioInitStructer );	//GPIO2
	
	GpioInitStructer.GPIO_Pin = SI4463_GPIO3_PIN;
	GPIO_Init( SI4463_GPIO3_PORT, &GpioInitStructer );	//GPIO3
	
	GPIO_ResetBits( SI4463_SDN_PORT, SI4463_SDN_PIN );	//SDN �õ� ʹ���豸
}

/**
  * @brief :SI446x��ʼ��
  * @param :��
  * @note  :��
  * @retval:��
  */
void SI446x_Init( void )
{
	SI446x_Gpio_Init( );		//SI4463���ų�ʼ��
	SI446x_Reset( );			//SI4463��λ
	SI446x_Power_Up( 30000000 );//reset ����ҪPower up�豸 ����30MHz
	SI446x_Config_Init( );		//SI4463ģ���ʼ��
	SI446x_Set_Power( 0x7F );	//��������
	SI446x_Change_Status( 6 );	//�л���RX״̬
	while( 6 != SI446x_Get_Device_Status( ));
	SI446x_Start_Rx( 0, 0, PACKET_LENGTH,0,0,3 );

}
