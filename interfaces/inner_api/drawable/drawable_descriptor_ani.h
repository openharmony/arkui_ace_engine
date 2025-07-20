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

#ifndef FOUNDATION_ACE_INTERFACE_ETS_ANI_DRAWABLE_DESCRIPTOR_INNER_DRAWABLE_DESCRIPTOR_ANI_H
#define FOUNDATION_ACE_INTERFACE_ETS_ANI_DRAWABLE_DESCRIPTOR_INNER_DRAWABLE_DESCRIPTOR_ANI_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "ani.h"

namespace OHOS::Global::Resource {
class ResourceManager;
} // namespace OHOS::Global::Resource

namespace OHOS::Ace::Ani {

struct MediaData {
    std::unique_ptr<uint8_t[]> data;
    size_t len = 0;
};

struct DrawableInfo {
    uint32_t density = 0;      // density for gloabl resource
    std::string type = "none"; // resource type
    MediaData firstBuffer;     // json buffer / foreground buffer / dynamic buffer
    MediaData secondBuffer;    // only for background buffer
    std::shared_ptr<Global::Resource::ResourceManager> manager;
};

class __attribute__((visibility("default"))) DrawableDescriptorAni final {
public:
    /**
     * 1. when type is none, create DrawableDescriptor by first buffer
     * 2. when type is resource type, type is possible json or sut, png,
     *    jpg... type, create DrawableDescriptor by first buffer
     * 3. when type is layered, create DrawableDescriptor by first buffer and secondBuffer
     * @param env ANI environment params
     * @param DrawableInfo construct drawable descriptor object params
     * @return ani_object ArkTS object -> DrawableDescriptor
     */
    static ani_object CreateDrawableDescriptor(ani_env* env, DrawableInfo& info);
};

} // namespace OHOS::Ace::Ani

#endif // FOUNDATION_ACE_INTERFACE_ETS_ANI_DRAWABLE_DESCRIPTOR_INNER_DRAWABLE_DESCRIPTOR_ANI_H
