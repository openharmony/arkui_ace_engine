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

KNativePointer impl_skoala_NodeClipboard__1nReadText(KNativePointer peerPtr, KNativePointer context) {
  auto peer = ptr<RedrawerPeerBase>(peerPtr);
  return peer->readFromClipboard ? peer->readFromClipboard(peer->engine, context) : nullptr;
}
KOALA_INTEROP_2(skoala_NodeClipboard__1nReadText, KNativePointer, KNativePointer, KNativePointer)

void impl_skoala_NodeClipboard__1nWriteText(KNativePointer peerPtr, KNativePointer context, const KStringPtr& strPtr) {
  auto peer = ptr<RedrawerPeerBase>(peerPtr);
  // TODO: use const char* here!
  if (peer->writeToClipboard) {
    peer->writeToClipboard(peer->engine, context, SkString(strPtr.c_str()));
  }
}
KOALA_INTEROP_V3(skoala_NodeClipboard__1nWriteText, KNativePointer, KNativePointer, KStringPtr)
