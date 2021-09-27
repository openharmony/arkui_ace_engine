/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_data_panel.h"

#include <vector>
#include "core/components/data_panel/data_panel_component.h"
#include "core/components/theme/theme_manager.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

constexpr size_t  MAX_COUNT = 9;
void JSDataPanel::JSBind(BindingTarget globalObj)
{
    JSClass<JSDataPanel>::Declare("DataPanel");
    JSClass<JSDataPanel>::StaticMethod("create", &JSDataPanel::Create);
    JSClass<JSDataPanel>::StaticMethod("closeEffect", &JSDataPanel::CloseEffect);

    JSClass<JSDataPanel>::Inherit<JSViewAbstract>();
    JSClass<JSDataPanel>::Bind(globalObj);
}

void JSDataPanel::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("toggle create error, info is non-valid");
        return;
    }

    RefPtr<PercentageDataPanelComponent> component =
        AceType::MakeRefPtr<PercentageDataPanelComponent>(ChartType::RAINBOW);
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto max = paramObject->GetProperty("max");
    if (max->IsNumber()) {
        component->SetMaxValue(max->ToNumber<double>());
    }

    JSRef<JSArray> values = paramObject->GetProperty("values");
    for(size_t i = 0; i < values->Length() && i < MAX_COUNT; ++i) {
        if (!values->GetValueAt(i)->IsNumber()) {
            LOGE("JSDataPanel::Create value is not number");
            return;
        }
        double value = values->GetValueAt(i)->ToNumber<double>();
        Segment segment;
        segment.SetValue(value);
        segment.SetColorType(SegmentStyleType::NONE);
        component->AppendSegment(segment);
    }
    ViewStackProcessor::GetInstance()->Push(component);
    RefPtr<ThemeManager> dataPanelManager = AceType::MakeRefPtr<ThemeManager>();
    component->InitalStyle(dataPanelManager);
}

void JSDataPanel::CloseEffect(const JSCallbackInfo& info)
{
    bool isCloseEffect = false;
    if (info[0]->IsBoolean()) {
        isCloseEffect = info[0]->ToBoolean();
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component =
        AceType::DynamicCast<PercentageDataPanelComponent>(stack->GetMainComponent());
    component->SetEffects(!isCloseEffect);
}

} // namespace OHOS::Ace::Framework
