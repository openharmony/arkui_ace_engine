/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_DRAWABALE_DESCRITOR_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_DRAWABALE_DESCRITOR_PEER_H

#include "arkoala_api_generated.h"

#include "base/image/pixel_map.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"

using PixelMapPtr = OHOS::Ace::RefPtr<OHOS::Ace::PixelMap>;

struct DrawableDescriptorPeer {
public:
    virtual PixelMapPtr GetPixelMap();

    void SetPixelMap(PixelMapPtr value)
    {
        pixelMap = value;
    }
    bool HasPixelMap();
    void ResetPixelMap();

protected:
    DrawableDescriptorPeer() = default;
    explicit DrawableDescriptorPeer(PixelMapPtr value) : pixelMap(value) {};
    virtual ~DrawableDescriptorPeer() = default;
    friend OHOS::Ace::NG::PeerUtils;

private:
    PixelMapPtr pixelMap;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_DRAWABALE_DESCRITOR_PEER_H