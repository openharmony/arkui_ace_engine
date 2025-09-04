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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_H

#include "base/image/pixel_map.h"

namespace OHOS::Ace {
enum class DrawableType {
    BASE,
    LAYERED,
    ANIMATED,
    PIXELMAP,
};

struct MediaData {
    std::unique_ptr<uint8_t[]> data;
    size_t len = 0;
};

class ACE_FORCE_EXPORT DrawableDescriptor : public AceType {
public:
    DrawableDescriptor() = default;
    virtual ~DrawableDescriptor() = default;

    virtual RefPtr<PixelMap> GetPixelMap()
    {
        return nullptr;
    }

    virtual DrawableType GetDrawableType() const
    {
        return DrawableType::BASE;
    }

private:
    virtual void CreatePixelMap() {}
};
}; // namesapce OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_DRAWABLE_DRAWABLE_DESCRIPTOR_H
