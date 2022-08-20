#pragma once
#include<ntddk.h>
#include<wdf.h>
#include<vhf.h>
#define DEVICE_NAME L"\\Device\\WuhuaController"
#define SYB_NAME    L"\\??\\WuhuaController"

typedef struct _DEVICE_CONTEXT
{
    VHFHANDLE VhfHandle;
    HID_XFER_PACKET VhfHidReport;

} DEVICE_CONTEXT, * PDEVICE_CONTEXT;
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)

UCHAR JoyStickRepDesc[] = {
0x05, 0x01, //UsagePage(Generic Desktop) UsagePage�������ݵ��÷�����
        0x15, 0x00,
        0x09, 0x04, //Usage(Joystick) Usage������Ŀ��collection��ʹ�õ�����
        0xA1, 0x01, //Collection(Application) �����й�ͬ��;����ִ�е�һ���ܵ���Ŀ������Ŀ����ָ����������X�����Y�����ָ�룬һ���������Ʒɻ����ƶ�
        0x05, 0x02, //UsagePage(Simulation Controls)����ģ������Ŀ�����
        0x09, 0xBB, //Usage (Throttle)�����������������ڷɻ�������
        0x15, 0x81, //Logical Minimum (-127) ������Ŀ����С��ֵ
        0x25, 0x7F, //Logical Maximum (127) ������Ŀ�������ֵ
        0x75, 0x08, //Report Size (8) ��Ŀ�ֶεĴ�С����ÿ���ش�������Ϊ8λ
        0x95, 0x01, //Report Count (1) ��Ŀ��������λ����Ŀ�����ش�һ������
        0x81, 0x02, //Input (Data, Variable, Absolute)����0x02�ĸ�λ����������

        0x05, 0x01, //UsagePage(Generic Desktop)����ͨ�������豸
        0x09, 0x01, //Usage (Pointer)����ָ�룬���Ʒɻ����������ҷ������Ҳ��һ��Pointer��
        0xA1, 0x00, //Collection (Physical) ��������������һ����һ�����ϵ���Ŀ
        0x09, 0x30, //Usage (X)����X����
        0x09, 0x31, //Usage (Y)����Y����
        0x09, 0x32, //Usage (Z)����Z����
        0x09, 0x33, //Usage (RX)����RX����
        0x09, 0x34, //Usage (RY)����RY����
        0x09, 0x35, //Usage (RZ)����RZ����
        0x95,0x06,
        0x81,0x02,
        0xc0,
        0x09,0x39,
        0x15,0x00,
        0x25,0x03,
        0x35,0x00,
        0x46,0x0e,0x01,
        0x65,20,
        0x75,0x04,
        0x95,0x01,
        0x81,0x02,
        0x05,0x09,
        0x19,0x01,
        0x29,20,
        0x15,0x00,
        0x25,0x01,
        0x75,0x01,
        0x95,0x14,
        0x55,0x00,
        0x65,0x00,
        0x81,0x02,
        0xc0
};