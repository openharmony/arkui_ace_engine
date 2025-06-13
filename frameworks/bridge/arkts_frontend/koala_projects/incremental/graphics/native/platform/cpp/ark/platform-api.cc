/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "platform-api.h"

#include "common-interop.h"
#include "common-redrawer.h"

#include "ark-interop.h"
#include "oh_sk_log.h"

static PeerFactoryFunc gPeerFactory = nullptr;
static void* gEngine = nullptr;

PeerFactoryFunc GetPeerFactory() {
    return gPeerFactory;
}

void *GetEngine() {
    return gEngine;
}

void impl_skoala_providePeerFactory(KNativePointer peerFactory, KNativePointer engine) {
    gPeerFactory = reinterpret_cast<PeerFactoryFunc>(peerFactory);
    gEngine = engine;
}
KOALA_INTEROP_V2(skoala_providePeerFactory, KNativePointer, KNativePointer);

KNativePointer impl_skoala_initRedrawer(KFloat scale, KNativePointer peerPtr, KNativePointer framePtr) {
    auto peer = ptr<RedrawerPeerBase>(peerPtr);
    auto data = sk_sp<RedrawerData>(new RedrawerData(scale, peer, framePtr));
    return data.release();
}
KOALA_INTEROP_3(skoala_initRedrawer, KNativePointer, KFloat, KNativePointer, KNativePointer)

void impl_skoala_abandonRedrawer(KNativePointer dataPtr) {
    auto data = ptr<RedrawerData>(dataPtr);
    if (data) data->abandon();
}
KOALA_INTEROP_V1(skoala_abandonRedrawer, KNativePointer)

KNativePointer impl_skoala_getDirectContext(KNativePointer dataPtr) {
    auto data = ptr<RedrawerData>(dataPtr);
    return data ? data->hwContext.get() : nullptr;
}
KOALA_INTEROP_1(skoala_getDirectContext, KNativePointer, KNativePointer)

KNativePointer impl_skoala_getNativeWindow(KNativePointer dataPtr) {
    return ptr<RedrawerData>(dataPtr)->frame;
}
KOALA_INTEROP_1(skoala_getNativeWindow, KNativePointer, KNativePointer)
