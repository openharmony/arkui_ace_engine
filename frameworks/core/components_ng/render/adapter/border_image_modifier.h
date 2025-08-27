/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"

namespace OHOS::Ace::NG {
class BorderImageModifier : public RSForegroundStyleModifier {
public:
    BorderImageModifier() = default;
    ~BorderImageModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        CHECK_NULL_VOID(context.canvas);
        CHECK_NULL_VOID(paintTask_);
        paintTask_(*context.canvas);
    }

    void SetPaintTask(std::function<void(RSCanvas&)>&& paintTask)
    {
        paintTask_ = paintTask;
    }

    void Modify()
    {
        if (!flag_) {
            flag_ = std::make_shared<Rosen::RSProperty<bool>>(0);
            AttachProperty(flag_);
        } else {
            flag_->Set(!flag_->Get());
        }
    }

private:
    std::shared_ptr<Rosen::RSProperty<bool>> flag_;
    std::function<void(RSCanvas&)> paintTask_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_BORDER_IMAGE_MODIFIER_H
