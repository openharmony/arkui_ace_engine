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

#include "core/common/resource/resource_object.h"
#include "core/drawable/animated_drawable_descriptor.h"
#include "core/drawable/drawable_descriptor_info.h"
#include "core/drawable/layered_drawable_descriptor.h"
#include "core/drawable/pixel_map_drawable_descriptor.h"

namespace OHOS::Ace {
extern "C" ACE_FORCE_EXPORT void OHOS_ACE_DrawableDescriptor_GetPixelMap(
    void* object, std::shared_ptr<Media::PixelMap>& pixelmap)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::DrawableDescriptor*>(object);
    if (drawable) {
        auto pixelmapRef = drawable->GetPixelMap();
        if (pixelmapRef) {
            pixelmap = pixelmapRef->GetPixelMapSharedPtr();
        }
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_PixelMapDrawableDescriptor_SetRawData(void* object, uint8_t* data, size_t len)
{
    if (len == 0 || data == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::PixelMapDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetRawData(data, len);
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_LayeredDrawableDescriptor_SetForegroundData(
    void* object, uint8_t* data, size_t len)
{
    if (len == 0 || data == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetForegroundData(data, len);
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_LayeredDrawableDescriptor_SetBackgroundData(
    void* object, uint8_t* data, size_t len)
{
    if (len == 0 || data == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetBackgroundData(data, len);
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_LayeredDrawableDescriptor_SetMaskData(void* object, uint8_t* data, size_t len)
{
    if (len == 0 || data == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetMaskData(data, len);
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_LayeredDrawableDescriptor_SetMaskPath(void* object, const char* path)
{
    if (path == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::LayeredDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetMaskPath(std::string(path));
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_SetPixelMapList(
    void* object, std::vector<void*> pixelMaps)
{
    if (pixelMaps.size() == 0) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        std::vector<RefPtr<PixelMap>> pixelMapList;
        for (size_t i = 0; i < pixelMaps.size(); i++) {
            pixelMapList.push_back(PixelMap::CreatePixelMap(pixelMaps[i]));
        }
        drawable->SetPixelMapList(pixelMapList);
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_SetPath(void* object, const char* path)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        auto info = AceType::MakeRefPtr<DrawableDescriptorInfo>(std::string(path));
        drawable->SetDrawableDescriptorInfo(info);
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_SetResource(void* object, void* resource)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        auto* resourcePtr = reinterpret_cast<OHOS::Ace::ResourceObject*>(resource);
        auto resourceRef = Referenced::Claim(resourcePtr);
        resourceRef->DecRefCount();
        auto info = AceType::MakeRefPtr<DrawableDescriptorInfo>(resourceRef);
        drawable->SetDrawableDescriptorInfo(info);
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_SetTotalDuration(void* object, int32_t duration)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetTotalDuration(duration);
    }
}

extern "C" ACE_FORCE_EXPORT int32_t OHOS_ACE_AnimatedDrawableDescriptor_GetTotalDuration(void* object)
{
    int32_t duration = -1;
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        duration = drawable->GetTotalDuration();
    }
    return duration;
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_SetDurations(
    void* object, const std::vector<int32_t>& durations)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetDurations(durations);
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_SetIterations(void* object, int32_t iterations)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetIterations(iterations);
    }
}

extern "C" ACE_FORCE_EXPORT int32_t OHOS_ACE_AnimatedDrawableDescriptor_GetIterations(void* object)
{
    int32_t iterations = 1;
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        iterations = drawable->GetIterations();
    }
    return iterations;
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_SetAutoPlay(void* object, bool autoPlay)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetAutoPlay(autoPlay);
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptorLoadSync(
    void* object, int32_t& width, int32_t& height, int32_t& errorCode)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        auto result = drawable->LoadSync();
        width = result.imageWidth_;
        height = result.imageHeight_;
        errorCode = result.errorCode;
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimationController_Start(void* object)
{
    auto* controller = reinterpret_cast<OHOS::Ace::ControlledAnimator*>(object);
    if (controller) {
        controller->Finish();
        controller->Forward();
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimationController_Pause(void* object)
{
    auto* controller = reinterpret_cast<OHOS::Ace::ControlledAnimator*>(object);
    if (controller) {
        controller->Pause();
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimationController_Stop(void* object)
{
    auto* controller = reinterpret_cast<OHOS::Ace::ControlledAnimator*>(object);
    if (controller) {
        controller->Finish();
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimationController_Resume(void* object)
{
    auto* controller = reinterpret_cast<OHOS::Ace::ControlledAnimator*>(object);
    if (controller) {
        controller->Forward();
    }
}

extern "C" ACE_FORCE_EXPORT int32_t OHOS_ACE_AnimationController_GetStatus(void* object)
{
    auto* controller = reinterpret_cast<OHOS::Ace::ControlledAnimator*>(object);
    if (controller) {
        auto status = controller->GetControlStatus();
        return static_cast<int32_t>(status);
    }
    return -1;
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_AnimatedDrawableDescriptor_GetAnimationController(
    void* object, const char* id)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        auto controller = drawable->GetControlledAnimator(std::string(id));
        return AceType::RawPtr(controller);
    }
    return nullptr;
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateDrawableDescriptorByType(uint32_t type)
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

extern "C" ACE_FORCE_EXPORT uint32_t OHOS_ACE_GetDrawableDescriptorType(void* object)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::DrawableDescriptor*>(object);
    if (drawable) {
        return static_cast<uint32_t>(drawable->GetDrawableType());
    }
    return 0;
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_IncreaseRefDrawableDescriptor(void* object)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::DrawableDescriptor*>(object);
    if (drawable) {
        drawable->IncRefCount();
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_DecreaseRefDrawableDescriptor(void* object)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::DrawableDescriptor*>(object);
    if (drawable) {
        drawable->DecRefCount();
    }
}
} // namespace OHOS::Ace