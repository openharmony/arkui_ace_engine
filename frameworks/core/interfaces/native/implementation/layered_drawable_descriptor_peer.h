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

#pragma once

#include "arkoala_api_generated.h"
#include "drawable_descriptor_peer.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct LayeredDrawableDescriptorPeer : public DrawableDescriptorPeer {
public:
    DrawableDescriptorPeer* GetForeground();
    DrawableDescriptorPeer* GetBackground();
    DrawableDescriptorPeer* GetMask();

protected:
    LayeredDrawableDescriptorPeer() = default;
    LayeredDrawableDescriptorPeer(PixelMapPtr foregroundValue, PixelMapPtr backgroundValue, PixelMapPtr maskValue)
        : foreground(foregroundValue), background(backgroundValue), mask(maskValue)
    {}
    friend OHOS::Ace::NG::PeerUtils;
    ~LayeredDrawableDescriptorPeer() override = default;

private:
    PixelMapPtr foreground;
    PixelMapPtr background;
    PixelMapPtr mask;
};
