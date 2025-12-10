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

void* CreateDrawableDescriptorByType(uint32_t type)
{
    if (type > static_cast<uint32_t>(DrawableType::PIXELMAP)) {
        return nullptr;
    }
    auto enumType = static_cast<DrawableType>(type);
    if (enumType == DrawableType::BASE) {
        return new DrawableDescriptor();
    } else if (enumType == DrawableType::LAYERED) {
        return new LayeredDrawableDescriptor();
    } else if (enumType == DrawableType::ANIMATED) {
        return new AnimatedDrawableDescriptor();
    } else if (enumType == DrawableType::PIXELMAP) {
        return new PixelMapDrawableDescriptor();
    }
    return nullptr;
}

void SetPixelMapList(void* object, void* pixelMapVec)
{
    if (object == nullptr || pixelMapVec == nullptr) {
        return;
    }

    auto* drawable = static_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    auto* pixelMaps = static_cast<std::vector<std::shared_ptr<OHOS::Media::PixelMap>>*>(pixelMapVec);

    std::vector<RefPtr<PixelMap>> pixelMapList;
    for (size_t i = 0; i < pixelMaps->size(); i++) {
        auto pixelMap = PixelMap::Create((*pixelMaps)[i]);
        pixelMapList.push_back(pixelMap);
    }
    drawable->SetPixelMapList(pixelMapList);
}

void SetAnimatedTotalDuration(void* object, int32_t duration)
{
    if (object == nullptr) {
        return;
    }
    auto* drawable = static_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    drawable->SetTotalDuration(duration);
}

void SetAnimatedIterations(void* object, int32_t iterations)
{
    if (object == nullptr) {
        return;
    }
    auto* drawable = static_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    drawable->SetIterations(iterations);
}

void SetAnimatedPath(void* object, const char* path)
{
    if (object == nullptr || path == nullptr) {
        return;
    }
    auto* drawable = static_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    auto info = AceType::MakeRefPtr<DrawableDescriptorInfo>(std::string(path));
    drawable->SetDrawableDescriptorInfo(info);
}

void SetAnimatedResource(void* object, void* resourceObject)
{
    if (object == nullptr || resourceObject == nullptr) {
        return;
    }
    auto* drawable = static_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    auto* resourcePtr = static_cast<OHOS::Ace::ResourceObject*>(resourceObject);
    auto resourceRef = Referenced::Claim(resourcePtr);
    resourceRef->DecRefCount();
    auto info = AceType::MakeRefPtr<DrawableDescriptorInfo>(resourceRef);
    drawable->SetDrawableDescriptorInfo(info);
}

void SetAnimatedAutoPlay(void* object, bool autoPlay)
{
    if (object == nullptr) {
        return;
    }
    auto* drawable = static_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    drawable->SetAutoPlay(autoPlay);
}

void SetAnimatedDurations(void* object, const void* durationsVec)
{
    if (object == nullptr || durationsVec == nullptr) {
        return;
    }
    auto* drawable = static_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    auto* durations = static_cast<const std::vector<int32_t>*>(durationsVec);
    drawable->SetDurations(*durations);
}

void LoadSyncAnimated(void* object, int32_t* width, int32_t* height, int32_t* errorCode)
{
    if (object == nullptr || width == nullptr || height == nullptr || errorCode == nullptr) {
        return;
    }
    auto* drawable = static_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    auto result = drawable->LoadSync();
    *width = result.imageWidth_;
    *height = result.imageHeight_;
    *errorCode = result.errorCode;
}

void* GetAnimatedController(void* object, const char* id)
{
    if (object == nullptr || id == nullptr) {
        return nullptr;
    }
    auto* drawable = static_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    auto controller = drawable->GetControlledAnimator(std::string(id));
    return AceType::RawPtr(controller);
}

void StartAnimated(void* object)
{
    if (object == nullptr) {
        return;
    }
    auto* controller = static_cast<OHOS::Ace::ControlledAnimator*>(object);
    controller->Finish();
    controller->Forward();
}

void StopAnimated(void* object)
{
    if (object == nullptr) {
        return;
    }
    auto* controller = static_cast<OHOS::Ace::ControlledAnimator*>(object);
    controller->Finish();
}

void PauseAnimated(void* object)
{
    if (object == nullptr) {
        return;
    }
    auto* controller = static_cast<OHOS::Ace::ControlledAnimator*>(object);
    controller->Pause();
}

void ResumeAnimated(void* object)
{
    if (object == nullptr) {
        return;
    }
    auto* controller = static_cast<OHOS::Ace::ControlledAnimator*>(object);
    controller->Forward();
}

int32_t GetAnimatedStatus(void* object)
{
    int32_t status = -1;
    if (object == nullptr) {
        return status;
    }
    auto* controller = static_cast<OHOS::Ace::ControlledAnimator*>(object);
    status = static_cast<int32_t>(controller->GetControlStatus());
    return status;
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
        .createDrawableDescriptorByType = OHOS::Ace::CreateDrawableDescriptorByType,
        .setPixelMapList = OHOS::Ace::SetPixelMapList,
        .setAnimatedTotalDuration = OHOS::Ace::SetAnimatedTotalDuration,
        .setAnimatedIterations = OHOS::Ace::SetAnimatedIterations,
        .setAnimatedPath = OHOS::Ace::SetAnimatedPath,
        .setAnimatedResource = OHOS::Ace::SetAnimatedResource,
        .setAnimatedAutoPlay = OHOS::Ace::SetAnimatedAutoPlay,
        .setAnimatedDurations = OHOS::Ace::SetAnimatedDurations,
        .loadSyncAnimated = OHOS::Ace::LoadSyncAnimated,
        .getAnimatedController = OHOS::Ace::GetAnimatedController,
        .startAnimated = OHOS::Ace::StartAnimated,
        .stopAnimated = OHOS::Ace::StopAnimated,
        .pauseAnimated = OHOS::Ace::PauseAnimated,
        .resumeAnimated = OHOS::Ace::ResumeAnimated,
        .getAnimatedStatus = OHOS::Ace::GetAnimatedStatus
    };
    return &impl;
}
}
