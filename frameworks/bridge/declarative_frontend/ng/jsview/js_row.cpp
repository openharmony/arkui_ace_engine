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

#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"

#include "base/log/ace_trace.h"
#include "core/components_ng/pattern/linear_layout/row_view.h"

namespace OHOS::Ace::Framework {

void JSRow::Create(const JSCallbackInfo& info)
{
    std::optional<Dimension> space;
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> spaceVal = obj->GetProperty("space");
        Dimension value;
        if (ParseJsDimensionVp(spaceVal, value)) {
            space = value;
        }
    }
    NG::RowView::Create(space);
}

void JSRow::CreateWithWrap(const JSCallbackInfo& info) {}

void JSRow::SetAlignItems(int32_t value)
{
    if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
        (value == static_cast<int32_t>(FlexAlign::FLEX_END)) || (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
        (value == static_cast<int32_t>(FlexAlign::STRETCH))) {
        NG::RowView::AlignItems(static_cast<FlexAlign>(value));
    } else {
        // FIXME: we have a design issue here, setters return void, can not signal error to JS
        LOGE("invalid value for justifyContent");
    }
}

void JSRow::SetJustifyContent(int32_t value)
{
    if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
        (value == static_cast<int32_t>(FlexAlign::FLEX_END)) || (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_BETWEEN)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_AROUND)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_EVENLY))) {
        NG::RowView::JustifyContent(static_cast<FlexAlign>(value));
    } else {
        LOGE("invalid value for justifyContent");
    }
}

// TODO: VerticalAlignDeclaration is not used, remove later
void VerticalAlignDeclaration::ConstructorCallback(const JSCallbackInfo& args) {}

void VerticalAlignDeclaration::DestructorCallback(VerticalAlignDeclaration* obj) {}

} // namespace OHOS::Ace::Framework
