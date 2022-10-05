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

#include "bridge/declarative_frontend/jsview/js_data_panel.h"

#include <vector>

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/data_panel/data_panel_component.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/data_panel/data_panel_view.h"

namespace OHOS::Ace::Framework {

constexpr size_t MAX_COUNT = 9;
void JSDataPanel::JSBind(BindingTarget globalObj)
{
    JSClass<JSDataPanel>::Declare("DataPanel");
    JSClass<JSDataPanel>::StaticMethod("create", &JSDataPanel::Create);
    JSClass<JSDataPanel>::StaticMethod("closeEffect", &JSDataPanel::CloseEffect);
    JSClass<JSDataPanel>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSDataPanel>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSDataPanel>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSDataPanel>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSDataPanel>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSDataPanel>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSDataPanel>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSDataPanel>::Inherit<JSViewAbstract>();
    JSClass<JSDataPanel>::Bind(globalObj);
}

void JSDataPanel::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("toggle create error, info is non-valid");
        return;
    }
    auto param = JsonUtil::ParseJsonString(info[0]->ToString());
    if (!param || param->IsNull()) {
        LOGE("JSDataPanel::Create param is null");
        return;
    }
    // max
    auto max = param->GetDouble("max", 100.0);
    // values
    auto values = param->GetValue("values");
    if (!values || !values->IsArray()) {
        LOGE("JSDataPanel::Create values is not array");
        return;
    }
    auto type = param->GetValue("type");
    size_t length = static_cast<size_t>(values->GetArraySize());
    std::vector<double> dateValues;
    double dataSum = 0.0;
    for (size_t i = 0; i < length && i < MAX_COUNT; i++) {
        auto item = values->GetArrayItem(i);
        if (!item || !item->IsNumber()) {
            LOGE("JSDataPanel::Create value is not number");
            return;
        }
        auto value = item->GetDouble();
        if (LessOrEqual(value, 0.0)) {
            value = 0.0;
        }
        dataSum += value;
        if (GreatOrEqual(dataSum, max) && max > 0) {
            value = max - (dataSum - value);
            if (NearEqual(value, 0.0)) {
                break;
            }
        }
        dateValues.push_back(value);
    }
    if (LessOrEqual(max, 0.0)) {
        max = dataSum;
    }
    size_t dataPanelType = 0;
    if (type->IsNumber()) {
        if (type->GetInt() == static_cast<int32_t>(ChartType::LINE)) {
            dataPanelType = 1;
        } else if (type->GetInt() == static_cast<int32_t>(ChartType::RAINBOW)) {
            dataPanelType = 0;
        }
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::DataPanelView::Create(dateValues, max, dataPanelType);
        return;
    }
    RefPtr<PercentageDataPanelComponent> component =
        AceType::MakeRefPtr<PercentageDataPanelComponent>(ChartType::RAINBOW);
    double valueSum = 0.0;
    for (size_t i = 0; i < length && i < MAX_COUNT; i++) {
        auto item = values->GetArrayItem(i);
        if (!item || !item->IsNumber()) {
            LOGE("JSDataPanel::Create value is not number");
            return;
        }
        auto value = item->GetDouble();
        if (LessOrEqual(value, 0.0)) {
            value = 0.0;
        }
        valueSum += value;
        if (GreatOrEqual(valueSum, max) && max > 0) {
            value = max - (valueSum - value);
            if (NearEqual(value, 0.0)) {
                break;
            }
            Segment segment;
            segment.SetValue(value);
            segment.SetColorType(SegmentStyleType::NONE);
            component->AppendSegment(segment);
            break;
        }
        Segment segment;
        segment.SetValue(value);
        segment.SetColorType(SegmentStyleType::NONE);
        component->AppendSegment(segment);
    }
    if (LessOrEqual(max, 0.0)) {
        max = valueSum;
    }
    component->SetMaxValue(max);
    if (type->IsNumber()) {
        if (type->GetInt() == static_cast<int32_t>(ChartType::LINE)) {
            component->SetPanelType(ChartType::LINE);
        } else if (type->GetInt() == static_cast<int32_t>(ChartType::RAINBOW)) {
            component->SetPanelType(ChartType::RAINBOW);
        }
    }
    RefPtr<ThemeManager> dataPanelManager = AceType::MakeRefPtr<ThemeManager>();
    component->InitalStyle(dataPanelManager);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
}

void JSDataPanel::CloseEffect(const JSCallbackInfo& info)
{
    bool isCloseEffect = false;
    bool ngCloseEffect = true;
    if (info[0]->IsBoolean()) {
        isCloseEffect = info[0]->ToBoolean();
        ngCloseEffect = info[0]->ToBoolean();
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::DataPanelView::SetEffect(!ngCloseEffect);
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PercentageDataPanelComponent>(stack->GetMainComponent());
    component->SetEffects(!isCloseEffect);
}

} // namespace OHOS::Ace::Framework
