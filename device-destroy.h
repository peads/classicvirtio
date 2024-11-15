/* Copyright (c) 2023-2024 Elliot Nunn, Patrick Eads */
/* Licensed under the MIT license */

#ifndef CLASSICVIRTIO_DEVICE_DESTROY_H
#define CLASSICVIRTIO_DEVICE_DESTROY_H

#include <Devices.h>
#include <DriverServices.h>
#include "transport.h"
#include "virtqueue.h"
#include "printf.h"

OSStatus finalize(DriverFinalInfo *info, uint16_t maxSize) {

    SynchronizeIO();
    int nbuf = QFinal(info->refNum, maxSize);
    if (nbuf == 0) {
        printf("Virtqueue layer failure\n");
        VFail();
        return closErr;
    }
    SynchronizeIO();
    printf("Virtqueue layer finalized\n");

    SynchronizeIO();
    CloseDriver(info->refNum);
    SynchronizeIO();

    if (!VFinal(&info->deviceEntry)) {
        printf("Transport layer failure\n");
        VFail();
        return closErr;
    }
    printf("Transport layer finalized\n");

    SynchronizeIO();
    printf("Removed Successfully\n");

    return noErr;
}

#endif //CLASSICVIRTIO_DEVICE_DESTROY_H
