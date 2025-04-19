/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_DRAWABLE_DESCRIPTOR_H

#include <cstdint>
#include <functional>

#include "base/memory/ace_type.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_forward.h"


namespace OHOS {
namespace Ace {
class DrawableDescriptor : public AceType {
    DECLARE_ACE_TYPE(DrawableDescriptor, AceType);

public:
    using RedrawCallback = std::function<void()>;

    static RefPtr<DrawableDescriptor> CreateDrawable(void* sptrAddr);

    virtual void RegisterRedrawCallback(RedrawCallback&& callback) = 0;

    virtual void Draw(RSCanvas& canvas, const NG::ImagePaintConfig& config) = 0;

    // Used to shield existing services temporarily.
    virtual int32_t GetDrawableSrcType() = 0;
};
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_DRAWABLE_DESCRIPTOR_H
