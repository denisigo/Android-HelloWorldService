/*
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

//#define LOG_NDEBUG 0
#define LOG_TAG "IHelloWorldListener"
#include <utils/Log.h>
#include <stdint.h>
#include <sys/types.h>
#include <IHelloWorldListener.h>

namespace android {

enum {
    ON_STATUS_CHANGED = IBinder::FIRST_CALL_TRANSACTION
};

class BpHelloWorldListener: public BpInterface<IHelloWorldListener>
{
public:
    BpHelloWorldListener(const sp<IBinder>& impl)
        : BpInterface<IHelloWorldListener>(impl)
    {
    }

    // generic callback from camera service to app
    void onStatusChanged(int32_t status)
    {
        ALOGV("notifyCallback");
        Parcel data, reply;
        data.writeInterfaceToken(IHelloWorldListener::getInterfaceDescriptor());
        data.writeInt32(status);
        remote()->transact(ON_STATUS_CHANGED, data, &reply, IBinder::FLAG_ONEWAY);
    }
};

IMPLEMENT_META_INTERFACE(HelloWorldListener, "org.credil.helloworldservice.IHelloWorldListener");

// ----------------------------------------------------------------------

status_t BnHelloWorldListener::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch(code) {
        case ON_STATUS_CHANGED: {
            ALOGV("ON_STATUS_CHANGED");
            CHECK_INTERFACE(IHelloWorldListener, data, reply);
            int32_t status = data.readInt32();
            onStatusChanged(status);
            return NO_ERROR;
        } break;
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

// ----------------------------------------------------------------------------

}; // namespace android

