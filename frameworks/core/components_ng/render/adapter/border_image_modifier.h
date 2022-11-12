/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_BORDER_IMAGE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_BORDER_IMAGE_MODIFIER_H

#include <functional>
#include <memory>

#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/render/adapter/rosen_foreground_modifier.h"
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"

namespace OHOS::Ace::NG {

class BorderImageModifier : public RSForegroundStyleModifier {
public:
    BorderImageModifier() = default;
    ~BorderImageModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        CHECK_NULL_VOID(property_);
        std::shared_ptr<SkCanvas> skCanvas { context.canvas, [](SkCanvas* /*unused*/) {} };
        RSCanvas rsCanvas(&skCanvas);
        CHECK_NULL_VOID(&rsCanvas);
        paintTask_(property_->Get(), rsCanvas);
    }

    void SetCustomData(const NG::Gradient& gradient)
    {
        if (property_ == nullptr) {
            property_ = std::make_shared<Rosen::RSProperty<NG::Gradient>>(gradient);
            AttachProperty(property_);
        } else {
            property_->Set(gradient);
        }
    }

    void SetPaintTask(const std::function<void(const NG::Gradient&, RSCanvas&)>& paintTask)
    {
        paintTask_ = paintTask;
    }

private:
    std::shared_ptr<Rosen::RSProperty<NG::Gradient>> property_;
    std::function<void(const NG::Gradient&, RSCanvas&)> paintTask_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_BORDER_IMAGE_MODIFIER_H
