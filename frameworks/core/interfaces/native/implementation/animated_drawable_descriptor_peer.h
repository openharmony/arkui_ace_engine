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

struct AnimatedDrawableDescriptorPeer : public DrawableDescriptorPeer {
public:
    PixelMapPtr GetPixelMap() override;
    std::vector<PixelMapPtr> GetPixelMapList();
    int32_t GetDuration();
    int32_t GetIterations();
    void SetDuration(int32_t value);
    void SetIterations(int32_t value);

protected:
    AnimatedDrawableDescriptorPeer(std::vector<PixelMapPtr> pixelMapsValue, std::optional<int32_t> durationValue,
        std::optional<int32_t> iterationsValue)
        : pixelMapList(std::move(pixelMapsValue))
    {
        if (durationValue) {
            duration = *durationValue;
        }
        if (iterationsValue) {
            iterations = *iterationsValue;
        }
    }
    ~AnimatedDrawableDescriptorPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;

private:
    const int defaultDuration = 1000;
    std::vector<PixelMapPtr> pixelMapList;
    int32_t duration = -1;
    int32_t iterations = 1;
};
