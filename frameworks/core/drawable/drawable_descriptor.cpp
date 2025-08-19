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

#include "core/drawable/layered_drawable_descriptor.h"
#include "core/drawable/pixel_map_drawable_descriptor.h"

namespace OHOS::Ace {

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

} // namespace OHOS::Ace
