/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "focus_box.h"

namespace OHOS::Ace::NG {
void FocusBox::SetStyle(const FocusBoxStyle& style)
{
    paintStyle_ = style;

    if (paintStyle_->strokeWidth.has_value() && paintStyle_->strokeWidth->IsNegative()) {
        paintStyle_->strokeWidth.reset();
    }
    if (!paintStyle_->strokeColor && !paintStyle_->strokeWidth && !paintStyle_->margin) {
        paintStyle_.reset();
        return;
    }
}

bool FocusBox::HasCustomStyle() const
{
    return paintStyle_.has_value();
}

std::unique_ptr<JsonValue> FocusBox::ToJsonValue(const FocusBox& box)
{
    if (!box.HasCustomStyle()) {
        return nullptr;
    }
    auto json = JsonUtil::Create(false);
    if (json) {
        if (box.paintStyle_->strokeColor) {
            json->Put("strokeColor", box.paintStyle_->strokeColor.value().ToString().c_str());
        }
        if (box.paintStyle_->strokeWidth) {
            json->Put("strokeWidth", box.paintStyle_->strokeWidth.value().ToString().c_str());
        }
        if (box.paintStyle_->margin) {
            json->Put("margin", box.paintStyle_->margin.value().ToString().c_str());
        }
    }
    return json;
}
} // namespace OHOS::Ace::NG