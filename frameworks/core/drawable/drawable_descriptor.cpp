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

#include "core/drawable/drawable_descriptor.h"

#include "interfaces/native/node/resource.h"

#include "core/common/container.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/drawable/animated_drawable_descriptor.h"
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

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_DrawableDescriptor_GetPixelMap(void* object, void* pixelMap)
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

extern "C" ACE_FORCE_EXPORT int32_t OHOS_ACE_AnimatedDrawableDescriptor_GetIterations(void* object)
{
    int32_t iterations = 0;
    if (object == nullptr) {
        return iterations;
    }
    auto* drawable = reinterpret_cast<OHOS::Ace::AnimatedDrawableDescriptor*>(object);
    iterations = drawable->GetIterations();
    return iterations;
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
