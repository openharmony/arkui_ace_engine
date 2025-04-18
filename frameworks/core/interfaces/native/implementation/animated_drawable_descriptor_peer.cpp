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

#include "animated_drawable_descriptor_peer.h"

PixelMapPtr AnimatedDrawableDescriptorPeer::GetPixelMap() const
{
    if (pixelMapList.empty()) {
        return nullptr;
    }
    return pixelMapList[0];
}

std::vector<PixelMapPtr> AnimatedDrawableDescriptorPeer::GetPixelMapList() const
{
    return pixelMapList;
}

int32_t AnimatedDrawableDescriptorPeer::GetDuration()
{
    if (duration <= 0) {
        duration = defaultDuration * static_cast<int32_t>(pixelMapList.size());
    }
    return duration;
}

int32_t AnimatedDrawableDescriptorPeer::GetIterations()
{
    if (iterations < -1) {
        iterations = 1;
    }
    return iterations;
}

void AnimatedDrawableDescriptorPeer::SetDuration(int32_t value)
{
    if (value <= 0) {
        duration = defaultDuration * static_cast<int32_t>(pixelMapList.size());
    } else {
        duration = value;
    }
}

void AnimatedDrawableDescriptorPeer::SetIterations(int32_t value)
{
    if (value < -1) {
        iterations = 1;
    } else {
        iterations = value;
    }
}
