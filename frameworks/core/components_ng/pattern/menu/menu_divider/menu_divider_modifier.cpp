/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/menu_divider/menu_divider_modifier.h"

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
MenuDividerModifier::MenuDividerModifier(float strokeWidth, const Color& dividerColor)
{
    strokeWidth_ = AceType::MakeRefPtr<PropertyFloat>(strokeWidth);
    dividerColor_ = AceType::MakeRefPtr<PropertyColor>(dividerColor);
    leftMargin_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    rightMargin_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    needDivider_ = AceType::MakeRefPtr<PropertyBool>(false);
    press_ = AceType::MakeRefPtr<PropertyBool>(false);
    hover_ = AceType::MakeRefPtr<PropertyBool>(false);
    selected_ = AceType::MakeRefPtr<PropertyBool>(false);
    defaultShow_ = AceType::MakeRefPtr<PropertyBool>(false);

    AttachProperty(strokeWidth_);
    AttachProperty(dividerColor_);
    AttachProperty(leftMargin_);
    AttachProperty(rightMargin_);
    AttachProperty(needDivider_);
    AttachProperty(press_);
    AttachProperty(hover_);
    AttachProperty(selected_);
    AttachProperty(defaultShow_);
}

void MenuDividerModifier::onDraw(DrawingContext& context)
{
    if (!defaultShow_->Get() && (press_->Get() || hover_->Get() || selected_->Get())) {
        return;
    }
    RSCanvas& canvas = context.canvas;
    float centerY = context.height / 2;
    RSPen paint;
    paint.SetColor(dividerColor_->Get().GetValue());
    paint.SetWidth(context.height);
    paint.SetAntiAlias(true);
    canvas.AttachPen(paint);

    RSPoint start(leftMargin_->Get(), centerY);
    RSPoint end(context.width - rightMargin_->Get(), centerY);
    canvas.DrawLine(start, end);
    canvas.DetachPen();
}
} // namespace OHOS::Ace::NG
