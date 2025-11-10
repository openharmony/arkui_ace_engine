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

#include "interfaces/native/node/resource.h"
#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "base/error/error_code.h"
#include "core/common/resource/resource_object.h"
#include "core/drawable/drawable_descriptor.h"
#include "core/drawable/animated_drawable_descriptor.h"
#include "core/drawable/drawable_descriptor_info.h"
#include "core/drawable/layered_drawable_descriptor.h"
#include "core/drawable/pixel_map_drawable_descriptor.h"

namespace OHOS::Ace {
constexpr int32_t STRING = 10003;
constexpr int32_t MEDIA = 20000;
constexpr int32_t RAWFILE = 30000;
RefPtr<ResourceWrapper> CreateResourceWrapperDrawableDescriptor()
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter(Container::CurrentIdSafely());
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, nullptr);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto themeManager = pipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(themeManager, nullptr);
        themeConstants = themeManager->GetThemeConstants("", "");
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}
} // namespace

namespace OHOS::Ace {
extern "C" ACE_FORCE_EXPORT size_t OHOS_ACE_DrawableDescriptor_GetDrawableType(void* object)
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

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_PixelMapDrawableDescriptor_GetPixelMap(void* object, void* pixelMap)
{
    if (object == nullptr || pixelMap == nullptr) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::PixelMapDrawableDescriptor*>(object);
    if (drawable && drawable->GetPixelMap()) {
        auto* pixelMapPtr = reinterpret_cast<std::shared_ptr<OHOS::Media::PixelMap>*>(pixelMap);
        *pixelMapPtr = drawable->GetPixelMap()->GetPixelMapSharedPtr();
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

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_LayeredDrawableDescriptor_GetForeground(void* object, void* pixelMap)
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

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_LayeredDrawableDescriptor_GetBackground(void* object, void* pixelMap)
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

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_LayeredDrawableDescriptor_GetMask(void* object, void* pixelMap)
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

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_GetPixelMapVec(void* object, void* pixelMapVec)
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

extern "C" ACE_FORCE_EXPORT int32_t OHOS_ACE_AnimatedDrawableDescriptor_GetDuration(void* object)
{
    int32_t duration = 0;
    if (object == nullptr) {
        return duration;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    duration = drawable->GetTotalDuration();
    return duration;
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_SetPixelMapList(
    void* object, std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps)
{
    if (pixelMaps.size() == 0) {
        return;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        std::vector<RefPtr<PixelMap>> pixelMapList;
        for (size_t i = 0; i < pixelMaps.size(); i++) {
            auto pixelMap = PixelMap::Create(pixelMaps[i]);
            pixelMapList.push_back(pixelMap);
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

extern "C" ACE_FORCE_EXPORT uint32_t OHOS_ACE_AnimatedDrawableDescriptor_GetFrameCount(void* object)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        return drawable->GetFrameCount();
    } else {
        return 0;
    }
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_AnimatedDrawableDescriptor_SetDurations(
    void* object, const std::vector<int32_t>& durations)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetDurations(durations);
    }
}

extern "C" ACE_FORCE_EXPORT int32_t OHOS_ACE_AnimatedDrawableDescriptor_GetDurations(
    void* object, uint32_t* durations, size_t* size)
{
    std::vector<int32_t> frameVec;
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        frameVec = drawable->GetDurations();
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (frameVec.size() != (*size)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    for (size_t i = 0; i < frameVec.size(); i++) {
        if (frameVec[i] < 0) {
            return ERROR_CODE_PARAM_INVALID;
        }
        durations[i] = static_cast<uint32_t>(frameVec[i]);
    }
    return ERROR_CODE_NO_ERROR;
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

extern "C" ACE_FORCE_EXPORT int32_t OHOS_ACE_AnimatedDrawableDescriptor_GetAutoPlay(void* object, uint32_t* autoPlay)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        *autoPlay = drawable->GetAutoPlay();
    } else {
        return ERROR_CODE_PARAM_INVALID;
    }
    return ERROR_CODE_NO_ERROR;
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

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_AnimatedDrawableDescriptor_GetAnimationControllerById(
    void* object, const int32_t id)
{
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    if (drawable) {
        auto controller = drawable->GetControlledAnimator(id);
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

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_ParseStaticMedia(
    int32_t type, int32_t resId, const char* paramC, void* resource)
{
    ArkUI_Resource* res = reinterpret_cast<ArkUI_Resource*>(resource);
    if (!res || !paramC) {
        return;
    }
    std::string param(paramC);
    auto resourceWrapper = CreateResourceWrapperDrawableDescriptor();
    CHECK_NULL_VOID(resourceWrapper);
    if (type == static_cast<int32_t>(RAWFILE)) {
        res->src = resourceWrapper->GetRawfile(param);
        return;
    }
    if (resId == -1) {
        if (type == static_cast<int32_t>(MEDIA)) {
            res->src = resourceWrapper->GetMediaPathByName(param);
            return;
        }
        if (type == static_cast<int32_t>(STRING)) {
            res->src = resourceWrapper->GetStringByName(param);
            return;
        }
    } else if (type == static_cast<int32_t>(MEDIA)) {
        res->src = resourceWrapper->GetMediaPath(resId);
    } else if (type == static_cast<int32_t>(STRING)) {
        res->src = resourceWrapper->GetString(resId);
    }
}
} // namespace OHOS::Ace