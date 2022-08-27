/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"

#include "base/log/ace_trace.h"
#include "core/components/wrap/wrap_component.h"
#include "core/components_ng/pattern/linear_layout/column_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
std::string JSColumn::inspectorTag_ = "";

void JSColumn::Create(const JSCallbackInfo& info)
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
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ColumnView::Create(space);
        return;
    }
    std::list<RefPtr<Component>> children;
    RefPtr<ColumnComponent> columnComponent =
        AceType::MakeRefPtr<OHOS::Ace::ColumnComponent>(FlexAlign::FLEX_START, FlexAlign::CENTER, children);
    ViewStackProcessor::GetInstance()->ClaimElementId(columnComponent);
    columnComponent->SetMainAxisSize(MainAxisSize::MIN);
    columnComponent->SetCrossAxisSize(CrossAxisSize::MIN);
    if (space.has_value()) {
        columnComponent->SetSpace(space.value());
    }

    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> useAlign = obj->GetProperty("useAlign");
        if (useAlign->IsObject()) {
            HorizontalAlignDeclaration* declaration =
                JSRef<JSObject>::Cast(useAlign)->Unwrap<HorizontalAlignDeclaration>();
            if (declaration != nullptr) {
                columnComponent->SetAlignDeclarationPtr(declaration);
            }
        }
    }
    columnComponent->SetInspectorTag(inspectorTag_);
    ViewStackProcessor::GetInstance()->Push(columnComponent, false);
    JSInteractableView::SetFocusNode(true);
}

void JSColumn::CreateWithWrap(const JSCallbackInfo& info)
{
    std::list<RefPtr<Component>> children;
    RefPtr<OHOS::Ace::WrapComponent> component = AceType::MakeRefPtr<WrapComponent>(0.0, 0.0, children);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);

    component->SetDirection(WrapDirection::VERTICAL);
    component->SetMainAlignment(WrapAlignment::START);
    component->SetCrossAlignment(WrapAlignment::START);
    component->SetAlignment(WrapAlignment::START);
    component->SetDialogStretch(false);

    ViewStackProcessor::GetInstance()->Push(component);
}

void JSColumn::SetInspectorTag(const std::string& inspectorTag)
{
    inspectorTag_ = inspectorTag;
}

void JSColumn::ClearInspectorTag()
{
    inspectorTag_.clear();
}

void JSColumn::SetAlignItems(int32_t value)
{
    if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
        (value == static_cast<int32_t>(FlexAlign::FLEX_END)) || (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
        (value == static_cast<int32_t>(FlexAlign::STRETCH))) {
        if (Container::IsCurrentUseNewPipeline()) {
            NG::ColumnView::AlignItems(static_cast<FlexAlign>(value));
            return;
        }
        JSFlex::SetAlignItems(value);
    } else {
        // FIXME: we have a design issue here, setters return void, can not signal error to JS
        LOGE("invalid value for justifyContent");
    }
}

void JSColumn::SetJustifyContent(int32_t value)
{
    if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
        (value == static_cast<int32_t>(FlexAlign::FLEX_END)) ||
        (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_BETWEEN)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_AROUND)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_EVENLY))) {
        if (Container::IsCurrentUseNewPipeline()) {
            NG::ColumnView::JustifyContent(static_cast<FlexAlign>(value));
            return;
        }
        JSFlex::SetJustifyContent(value);
    } else {
        LOGE("invalid value for justifyContent");
    }
}

void HorizontalAlignDeclaration::ConstructorCallback(const JSCallbackInfo& args)
{
    auto align = HorizontalAlign::CENTER;
    if (args.Length() > 0 && args[0]->IsNumber()) {
        auto value = args[0]->ToNumber<int32_t>();
        if (value >= static_cast<int32_t>(HorizontalAlign::START) &&
            value <= static_cast<int32_t>(HorizontalAlign::END)) {
            align = static_cast<HorizontalAlign>(value);
        }
    }
    auto obj = new HorizontalAlignDeclaration(align);
    args.SetReturnValue(obj);
}

void HorizontalAlignDeclaration::DestructorCallback(HorizontalAlignDeclaration* obj)
{
    delete obj;
}

} // namespace OHOS::Ace::Framework
