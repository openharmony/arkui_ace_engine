/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PIXEL_MAP_ACCESSOR_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PIXEL_MAP_ACCESSOR_PEER_IMPL_H

#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"

struct PixelMapPeer final {
    OHOS::Ace::RefPtr<OHOS::Ace::PixelMap> pixelMap;

    static PixelMapPeer *Create(const OHOS::Ace::RefPtr<OHOS::Ace::PixelMap>& src)
    {
        return new PixelMapPeer{src};
    }

    static void Destroy(PixelMapPeer *peer)
    {
        CHECK_NULL_VOID(peer);
        delete peer;
    }
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PIXEL_MAP_ACCESSOR_PEER_IMPL_H