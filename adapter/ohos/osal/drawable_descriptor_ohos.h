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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_DRAWABLE_DESCRIPTOR_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_DRAWABLE_DESCRIPTOR_OHOS_H

#include <memory>

#include "base/paint.h"
#include "core/drawable_descriptor_base.h"

#include "base/image/drawable_descriptor.h"

namespace OHOS::Ace {

class DrawableDescriptorOhos : public DrawableDescriptor {
    DECLARE_ACE_TYPE(DrawableDescriptorOhos, DrawableDescriptor);

public:
    explicit DrawableDescriptorOhos(Drawable::DrawableDescriptor* drawable);
    ~DrawableDescriptorOhos();

    void RegisterRedrawCallback(RedrawCallback&& callback) override;

    void Draw(RSCanvas& canvas, const NG::ImagePaintConfig& config) override;

    int32_t GetDrawableSrcType() override;

private:
    Drawable::PaintConfig ConverConfig(const NG::ImagePaintConfig& config);
    
    // do not take the object out
    Drawable::DrawableDescriptor* drawable_;
    std::shared_ptr<std::mutex> mutex_ = std::make_shared<std::mutex>();
    std::shared_ptr<bool> isValid_ = std::make_shared<bool>(true);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_DRAWABLE_DESCRIPTOR_OHOS_H