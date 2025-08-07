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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MOUSE_SELECT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MOUSE_SELECT_MODIFIER_H

#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"

namespace OHOS::Ace::NG {

class MouseSelectModifier : public RSForegroundStyleModifier {
public:
    MouseSelectModifier() = default;
    ~MouseSelectModifier() override = default;

    void Draw(RSDrawingContext& context) const override
    {
        CHECK_NULL_VOID(rectProperty_);

#ifndef USE_ROSEN_DRAWING
        std::shared_ptr<SkCanvas> skCanvas { context.canvas, [](SkCanvas* /*unused*/) {} };
        RSCanvas rsCanvas(&skCanvas);
        CHECK_NULL_VOID(&rsCanvas);
        paintTask_(rectProperty_->Get(), rsCanvas);
#else
        CHECK_NULL_VOID(context.canvas);
        CHECK_NULL_VOID(paintTask_);
        paintTask_(rectProperty_->Get(), *context.canvas);
#endif
    }

    void SetSelectRect(const RectF& rect)
    {
        if (rectProperty_ == nullptr) {
            rectProperty_ = std::make_shared<Rosen::RSProperty<RectF>>(rect);
            AttachProperty(rectProperty_);
        } else {
            rectProperty_->Set(rect);
        }
    }

    void SetPaintTask(const std::function<void(const RectF&, RSCanvas&)>& paintTask)
    {
        paintTask_ = paintTask;
    }

private:
    std::shared_ptr<Rosen::RSProperty<RectF>> rectProperty_;
    std::function<void(const RectF&, RSCanvas&)> paintTask_;

    ACE_DISALLOW_COPY_AND_MOVE(MouseSelectModifier);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MOUSE_SELECT_MODIFIER_H
