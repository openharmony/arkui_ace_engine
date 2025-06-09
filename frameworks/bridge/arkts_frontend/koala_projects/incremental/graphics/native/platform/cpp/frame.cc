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

#include "skoala-interop.h"
#include "SkoalaCursor.h"
#include <stdlib.h>

KNativePointer impl_skoala_getFrame(KNativePointer peerPtr, const KStringPtr& titlePtr, int width, int height, int flags, int placement, int x, int y) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    peer->title.assign(titlePtr.c_str());
    return peer->getFrame ? peer->getFrame(peer->engine, peerPtr, width, height, flags, placement, x, y) : peer;
}
KOALA_INTEROP_8(skoala_getFrame, KNativePointer, KNativePointer, KStringPtr, KInt, KInt, KInt, KInt, KInt, KInt)

void impl_skoala_setFrameTitle(KNativePointer peerPtr, KNativePointer frame, const KStringPtr& titlePtr) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->setFrameTitle) peer->setFrameTitle(peer->engine, frame, titlePtr.c_str());
}
KOALA_INTEROP_V3(skoala_setFrameTitle, KNativePointer, KNativePointer, KStringPtr)

KInt impl_skoala_getFrameX(KNativePointer peerPtr, KNativePointer frame) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    return peer->getFrameX ? peer->getFrameX(peer->engine, frame) : 0;
}
KOALA_INTEROP_2(skoala_getFrameX, KInt, KNativePointer, KNativePointer)

KInt impl_skoala_getFrameY(KNativePointer peerPtr, KNativePointer frame) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    return peer->getFrameY ? peer->getFrameY(peer->engine, frame) : 0;
}
KOALA_INTEROP_2(skoala_getFrameY, KInt, KNativePointer, KNativePointer)

KInt impl_skoala_getFrameWidth(KNativePointer peerPtr, KNativePointer frame) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    return peer->getFrameWidth ? peer->getFrameWidth(peer->engine, frame) : 0;
}
KOALA_INTEROP_2(skoala_getFrameWidth, KInt, KNativePointer, KNativePointer)

KInt impl_skoala_getFrameHeight(KNativePointer peerPtr, KNativePointer frame) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    return peer->getFrameHeight ? peer->getFrameHeight(peer->engine, frame) : 0;
}
KOALA_INTEROP_2(skoala_getFrameHeight, KInt, KNativePointer, KNativePointer)

KFloat impl_skoala_getContentScale(KNativePointer peerPtr, KNativePointer frame) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    return peer->getContentScale ? peer->getContentScale(peer->engine, frame) : 1.0f;
}
KOALA_INTEROP_2(skoala_getContentScale, KFloat, KNativePointer, KNativePointer)

void impl_skoala_requestHaptic(KNativePointer peerPtr, KInt p1, KInt p2) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->requestHaptic) peer->requestHaptic(peer->engine, p1, p2);
}
KOALA_INTEROP_V3(skoala_requestHaptic, KNativePointer, KInt, KInt)

KInt impl_skoala_getOrientation(KNativePointer peerPtr) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    return peer->getOrientation ? peer->getOrientation(peer->engine) : -1;
}
KOALA_INTEROP_1(skoala_getOrientation, KInt, KNativePointer)

void impl_skoala_softKeyboard(KNativePointer peerPtr, KBoolean show) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->softKeyboard) peer->softKeyboard(peer->engine, show);
}
KOALA_INTEROP_V2(skoala_softKeyboard, KNativePointer, KBoolean)

void impl_skoala_commitInput(KNativePointer peerPtr) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->commitInput) peer->commitInput(peer->engine);
}
KOALA_INTEROP_V1(skoala_commitInput, KNativePointer)

void impl_skoala_askPermissions(KNativePointer peerPtr, KStringArray perms) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->askPermissions) peer->askPermissions(peer->engine, perms);
}
KOALA_INTEROP_V2(skoala_askPermissions, KNativePointer, KStringArray)

void impl_skoala_sendRequest(KNativePointer peerPtr, KNativePointer frame, KInt type, KInt data1, KInt data2) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->sendRequest) peer->sendRequest(peer->engine, frame, type, data1, data2);
}
KOALA_INTEROP_V5(skoala_sendRequest, KNativePointer, KNativePointer, KInt, KInt, KInt)

void impl_skoala_setCursor(KNativePointer peerPtr, KNativePointer frame, KInt cursor) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->setCursor) peer->setCursor(peer->engine, frame, static_cast<SkoalaCursor>(cursor));
}
KOALA_INTEROP_V3(skoala_setCursor, KNativePointer, KNativePointer, KInt)

void impl_skoala_exitApp(KNativePointer peerPtr, KInt code) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->exitApp) peer->exitApp(peer->engine, code);
}
KOALA_INTEROP_V2(skoala_exitApp, KNativePointer, KInt)

void impl_skoala_closeFrame(KNativePointer peerPtr, KNativePointer frame) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->closeFrame) peer->closeFrame(peer->engine, frame);
}
KOALA_INTEROP_V2(skoala_closeFrame, KNativePointer, KNativePointer)

void impl_skoala_getGlobalPointer(KNativePointer peerPtr, KInt* pointer) {
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);
    if (peer->getGlobalPointer) {
        peer->getGlobalPointer(peerPtr, pointer);
    }
}
KOALA_INTEROP_V2(skoala_getGlobalPointer, KNativePointer, KInt*)

void impl_skoala_exit(KInt code) {
    exit(0);
}
KOALA_INTEROP_V1(skoala_exit, KInt)
