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
0x05, 0x01, //UsagePage(Generic Desktop) UsagePage定义数据的用法或功能
        0x15, 0x00,
        0x09, 0x04, //Usage(Joystick) Usage描述项目或collection的使用的索引
        0xA1, 0x01, //Collection(Application) 包含有共同用途或者执行单一功能的项目。该项目可能指代节流阀、X方向和Y方向的指针，一起用来控制飞机的移动
        0x05, 0x02, //UsagePage(Simulation Controls)　　模拟输出的控制器
        0x09, 0xBB, //Usage (Throttle)　　节流阀，类似于飞机的油门
        0x15, 0x81, //Logical Minimum (-127) 报表项目的最小数值
        0x25, 0x7F, //Logical Maximum (127) 报表项目的最大数值
        0x75, 0x08, //Report Size (8) 项目字段的大小　　每个回传的数据为8位
        0x95, 0x01, //Report Count (1) 项目的数据域位的数目　　回传一个数据
        0x81, 0x02, //Input (Data, Variable, Absolute)　　0x02的各位含义详见卷标

        0x05, 0x01, //UsagePage(Generic Desktop)　　通用桌面设备
        0x09, 0x01, //Usage (Pointer)　　指针，控制飞机的上下左右方向（鼠标也是一种Pointer）
        0xA1, 0x00, //Collection (Physical) 包含代表数据在一个单一几何上的项目
        0x09, 0x30, //Usage (X)　　X方向
        0x09, 0x31, //Usage (Y)　　Y方向
        0x09, 0x32, //Usage (Z)　　Z方向
        0x09, 0x33, //Usage (RX)　　RX方向
        0x09, 0x34, //Usage (RY)　　RY方向
        0x09, 0x35, //Usage (RZ)　　RZ方向
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