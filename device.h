/* Copyright (c) 2023 Elliot Nunn */
/* Licensed under the MIT license */

// Implemented by device-[gpu|9p|etc].c

#pragma once

#include <Devices.h>
#include <DriverServices.h>
#include <Events.h>
#include <MixedMode.h>
#include <Types.h>

#include "allocator.h"
#include "callout68k.h"
#include "printf.h"
#include "panic.h"
#include "transport.h"
#include "scrollwheel.h"
#include "virtqueue.h"

// Device has finished with a buffer
void DNotified(__attribute__((unused)) uint16_t q, const volatile uint32_t *retlen);

// Device-specific configuration struct has changed
void DConfigChange(void);

OSStatus initialize(DriverInitInfo *info);
OSStatus finalize(DriverFinalInfo *info);
OSStatus DoDriverIO(AddressSpaceID spaceID, IOCommandID cmdID,
                    IOCommandContents pb, IOCommandCode code, IOCommandKind kind);

OSStatus DoDriverIO_(AddressSpaceID spaceID, IOCommandID cmdID,
                    IOCommandContents pb, IOCommandCode code, IOCommandKind kind) {
    
    switch (code) {
        case kInitializeCommand:
        case kReplaceCommand:
            return initialize(pb.initialInfo);
        case kFinalizeCommand:
        case kSupersededCommand:
            return finalize(pb.finalInfo);
        case kStatusCommand:
            return statusErr;
        case kOpenCommand:
        case kCloseCommand:
            return noErr;
        case kReadCommand:
            return readErr;
        case kWriteCommand:
            return writErr;
        default:
            return paramErr;
    }
}

OSStatus finalize_(DriverFinalInfo *info, size_t size) {

    SynchronizeIO();
    int nbuf = QFinal(info->refNum, size);
    if (nbuf == 0) {
        printf("Virtqueue layer failure\n");
        VFail();
        return closErr;
    }
    SynchronizeIO();
    printf("Virtqueue layer finalized\n");

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
