#include"driver.h"

EVT_WDF_DRIVER_DEVICE_ADD	EvtDevAdd;
EVT_WDF_DRIVER_UNLOAD		EvtDrvUnload;
VOID WriteDispatch(WDFQUEUE queque, WDFREQUEST request, size_t length);
NTSTATUS DriverEntry(PDRIVER_OBJECT DrvObj, PUNICODE_STRING RegPath)
{
	//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:INITIALIZING\n"));
	NTSTATUS status;
	WDF_DRIVER_CONFIG config;
	WDF_DRIVER_CONFIG_INIT(&config, EvtDevAdd);
	config.EvtDriverUnload = EvtDrvUnload;
	status = WdfDriverCreate(DrvObj, RegPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);
	return status;
}

NTSTATUS EvtDevAdd(WDFDRIVER dricer, PWDFDEVICE_INIT devInit)
{
	//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:EVT_DEV_ADD INITIALIZING\n"));
	NTSTATUS status;
	WDFDEVICE dev = NULL;
	UNICODE_STRING devName = { 0 };
	UNICODE_STRING sybName = { 0 };
	RtlInitUnicodeString(&devName, DEVICE_NAME);
	RtlInitUnicodeString(&sybName, SYB_NAME);
	status = WdfDeviceInitAssignName(devInit, &devName);
	if (!NT_SUCCESS(status))
	{
		//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:WdfDeviceInitAssignName ERROR\n"));
		return status;
	}
	//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:WdfDeviceInitAssignName SUCCESS\n"));
	WDF_OBJECT_ATTRIBUTES devAttr;
	WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&devAttr, DEVICE_CONTEXT);
	WDF_IO_QUEUE_CONFIG queConfig;
	WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&queConfig, WdfIoQueueDispatchSequential);
	queConfig.EvtIoWrite = WriteDispatch;
	status = WdfDeviceCreate(&devInit, &devAttr, &dev);
	if (!NT_SUCCESS(status))
	{
		//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:WdfDeviceCreate ERROR\n"));
		return status;
	}
	//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:WdfDeviceCreate SUCCESS\n"));
	status = WdfIoQueueCreate(dev, &queConfig, WDF_NO_OBJECT_ATTRIBUTES, NULL);
	if (!NT_SUCCESS(status))
	{
		//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:WdfIoQueueCreate ERROR\n"));
		return status;
	}
	//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:WdfIoQueueCreate SUCCESS\n"));
	WdfDeviceCreateSymbolicLink(dev, &sybName);
	VHF_CONFIG vhfConfig;
	VHF_CONFIG_INIT(&vhfConfig,
		WdfDeviceWdmGetDeviceObject(dev),
		sizeof(JoyStickRepDesc),
		JoyStickRepDesc);
	PDEVICE_CONTEXT deviceContext = DeviceGetContext(dev);
	status = VhfCreate(&vhfConfig, &(deviceContext->VhfHandle));
	if (!NT_SUCCESS(status))
	{
		//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:VhfCreate ERROR\n"));
		return status;
	}
	//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:VhfCreate SUCCESS\n"));
	status = VhfStart(deviceContext->VhfHandle);
	if (!NT_SUCCESS(status))
	{
		//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:VhfStart ERROR\n"));
		return status;
	}
	//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:VhfStart SUCCESS\n"));
	return status;
}
PVOID ControlBuffer;
VOID WriteDispatch(WDFQUEUE queque, WDFREQUEST request, size_t length)
{
	NTSTATUS status = STATUS_SUCCESS;
	WDFDEVICE dev = WdfIoQueueGetDevice(queque);
	PDEVICE_CONTEXT devcontext = DeviceGetContext(dev);
	status = WdfRequestRetrieveInputBuffer(request, 10, &ControlBuffer, NULL);
	if (!NT_SUCCESS(status))
	{
		WdfRequestComplete(request, status);
		return ;
	}
	devcontext->VhfHidReport.reportBuffer = ControlBuffer;
	devcontext->VhfHidReport.reportId = 0;
	devcontext->VhfHidReport.reportBufferLen = 10;
	status = VhfReadReportSubmit(devcontext->VhfHandle, &devcontext->VhfHidReport);
	//if (!(NT_SUCCESS(status)))
		//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:VhfReadReportSubmit ERROR\n"));
	//else
		//KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WV:VhfReadReportSubmit SUCCESS\n"));
	WdfRequestComplete(request, status);
}
VOID EvtDrvUnload(WDFDRIVER Driver)
{}