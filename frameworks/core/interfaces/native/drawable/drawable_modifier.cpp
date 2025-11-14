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

#include "interfaces/native/node/resource.h"

#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/drawable/animated_drawable_descriptor.h"
#include "core/drawable/drawable_descriptor.h"
#include "core/drawable/layered_drawable_descriptor.h"
#include "core/drawable/pixel_map_drawable_descriptor.h"
#include "core/interfaces/drawable/drawable_api.h"

namespace OHOS::Ace {

size_t GetDrawableType(void* object)
{
    size_t type = 0;
    if (object == nullptr) {
        return type;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::DrawableDescriptor*>(object);
    if (drawable) {
        type = static_cast<size_t>(drawable->GetDrawableType());
    }
    return type;
}

void GetPixelMap(void* object, void* pixelMap)
{
    if (object == nullptr || pixelMap == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::DrawableDescriptor*>(object);
    if (drawable && drawable->GetPixelMap()) {
        auto* pixelMapPtr = reinterpret_cast<std::shared_ptr<OHOS::Media::PixelMap>*>(pixelMap);
        *pixelMapPtr = drawable->GetPixelMap()->GetPixelMapSharedPtr();
    }
}

void SetPixelRawData(void* object, uint8_t* data, size_t len)
{
    if (len == 0 || data == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::PixelMapDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetRawData(data, len);
    }
}

void SetForegroundData(void* object, uint8_t* data, size_t len)
{
    if (len == 0 || data == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetForegroundData(data, len);
    }
}

void SetBackgroundData(void* object, uint8_t* data, size_t len)
{
    if (len == 0 || data == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetBackgroundData(data, len);
    }
}

void SetMaskData(void* object, uint8_t* data, size_t len)
{
    if (len == 0 || data == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetMaskData(data, len);
    }
}

void SetMaskPath(void* object, const char* path)
{
    if (path == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetMaskPath(std::string(path));
    }
}

void GetForegroundPixelMap(void* object, void* pixelMap)
{
    if (object == nullptr || pixelMap == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable && drawable->GetForeground()) {
        auto* pixelMapPtr = reinterpret_cast<std::shared_ptr<OHOS::Media::PixelMap>*>(pixelMap);
        *pixelMapPtr = drawable->GetForeground()->GetPixelMapSharedPtr();
    }
}

void GetBackgroundPixelMap(void* object, void* pixelMap)
{
    if (object == nullptr || pixelMap == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable && drawable->GetBackground()) {
        auto* pixelMapPtr = reinterpret_cast<std::shared_ptr<OHOS::Media::PixelMap>*>(pixelMap);
        *pixelMapPtr = drawable->GetBackground()->GetPixelMapSharedPtr();
    }
}

void GetMaskPixelMap(void* object, void* pixelMap)
{
    if (object == nullptr || pixelMap == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable && drawable->GetMask()) {
        auto* pixelMapPtr = reinterpret_cast<std::shared_ptr<OHOS::Media::PixelMap>*>(pixelMap);
        *pixelMapPtr = drawable->GetMask()->GetPixelMapSharedPtr();
    }
}

void GetAnimatedPixelMaps(void* object, void* pixelMapVec)
{
    if (object == nullptr || pixelMapVec == nullptr) {
        return;
    }
    auto* pixelMapVecPtr = reinterpret_cast<std::vector<std::shared_ptr<OHOS::Media::PixelMap>>*>(pixelMapVec);
    (*pixelMapVecPtr).clear();
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    auto pixelMapList = drawable->GetPixelMapList();
    for (const auto& refPtrPixelMap : pixelMapList) {
        if (refPtrPixelMap) {
            (*pixelMapVecPtr).push_back(refPtrPixelMap->GetPixelMapSharedPtr());
        }
    }
}

int32_t GetAnimatedDuration(void* object)
{
    int32_t duration = 0;
    if (object == nullptr) {
        return duration;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    duration = drawable->GetTotalDuration();
    return duration;
}

int32_t GetAnimatedIterations(void* object)
{
    int32_t iterations = 0;
    if (object == nullptr) {
        return iterations;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    iterations = drawable->GetIterations();
    return iterations;
}

void IncreaseRef(void* object)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::DrawableDescriptor*>(object);
    if (drawable) {
        drawable->IncRefCount();
    }
}

void DecreaseRef(void* object)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::DrawableDescriptor*>(object);
    if (drawable) {
        drawable->DecRefCount();
    }
}

} // namespace OHOS::Ace

extern "C" {
const ArkUIDrawableDescriptor* GetArkUIDrawableDescriptor()
{
    static const ArkUIDrawableDescriptor impl {
        .getDrawableType = OHOS::Ace::GetDrawableType,
        .getPixelMap = OHOS::Ace::GetPixelMap,
        .setPixelRawData = OHOS::Ace::SetPixelRawData,
        .setForegroundData = OHOS::Ace::SetForegroundData,
        .setBackgroundData = OHOS::Ace::SetBackgroundData,
        .setMaskData = OHOS::Ace::SetMaskData,
        .setMaskPath = OHOS::Ace::SetMaskPath,
        .getForegroundPixelMap = OHOS::Ace::GetForegroundPixelMap,
        .getBackgroundPixelMap = OHOS::Ace::GetBackgroundPixelMap,
        .getMaskPixelMap = OHOS::Ace::GetMaskPixelMap,
        .getAnimatedPixelMaps = OHOS::Ace::GetAnimatedPixelMaps,
        .getAnimatedDuration = OHOS::Ace::GetAnimatedDuration,
        .getAnimatedIterations = OHOS::Ace::GetAnimatedIterations,
        .increaseRef = OHOS::Ace::IncreaseRef,
        .decreaseRef = OHOS::Ace::DecreaseRef,
    };
    return &impl;
}
}
