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

#include "adapter/ohos/osal/drawable_descriptor_ohos.h"

#include "base/log/log.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {
RefPtr<DrawableDescriptor> DrawableDescriptor::CreateDrawable(void* sptrAddr)
{
    auto* drawable = reinterpret_cast<Drawable::DrawableDescriptor*>(sptrAddr);
    if (drawable == nullptr) {
        TAG_LOGW(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "drawable is nullptr when create drawable");
        return nullptr;
    }
    return AceType::MakeRefPtr<DrawableDescriptorOhos>(drawable);
}

DrawableDescriptorOhos::DrawableDescriptorOhos(Drawable::DrawableDescriptor* drawable) : drawable_(drawable)
{
    drawable_->AddDestructCallback(this, [mutex = mutex_, isValid = isValid_] {
        std::lock_guard lg(*mutex);
        *isValid = false;
    });
}

DrawableDescriptorOhos::~DrawableDescriptorOhos()
{
    std::lock_guard lg(*mutex_);
    if (*isValid_) {
        drawable_->RemoveDestructCallback(this);
    }
}

int32_t DrawableDescriptorOhos::GetDrawableSrcType()
{
    if (!(*isValid_)) {
        TAG_LOGE(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "drawable is suspended when get src type");
        return -1;
    }
    return static_cast<int32_t>(drawable_->GetSrcType());
}

void DrawableDescriptorOhos::RegisterRedrawCallback(RedrawCallback&& callback)
{
    if (!(*isValid_)) {
        TAG_LOGE(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "drawable is suspended when component register redraw callback");
        return;
    }
    drawable_->RegisterRedrawCallback(std::move(callback));
}

Drawable::PaintConfig DrawableDescriptorOhos::ConverConfig(const NG::ImagePaintConfig& config)
{
    Drawable::PaintConfig drawableConfig;
    drawableConfig.imageFit = static_cast<Drawable::ImageFit>(config.imageFit_);
    return drawableConfig;
}

void DrawableDescriptorOhos::Draw(RSCanvas& canvas, const NG::ImagePaintConfig& config)
{
    if (!(*isValid_)) {
        TAG_LOGE(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "drawable is suspended when drawable draw to canvas");
        return;
    }
    drawable_->Draw(canvas, ConverConfig(config));
}
} // namespace OHOS::Ace
