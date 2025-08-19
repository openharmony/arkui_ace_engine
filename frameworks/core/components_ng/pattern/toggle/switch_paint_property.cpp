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

#include "core/components_ng/pattern/toggle/switch_paint_property.h"

#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void SwitchPaintParagraph::ToJsonValue(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter, const RefPtr<FrameNode>& host) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    int32_t themeScopeId = 0;
    if (host) {
        themeScopeId = host->GetThemeScopeId();
    }
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>(themeScopeId);
    CHECK_NULL_VOID(switchTheme);
    auto selectedColor = switchTheme->GetActiveColor();
    auto switchPointColor = switchTheme->GetPointColor();
    json->PutExtAttr("selectedColor", propSelectedColor.value_or(selectedColor).ColorToString().c_str(), filter);
    json->PutExtAttr(
        "switchPointColor", propSwitchPointColor.value_or(switchPointColor).ColorToString().c_str(), filter);
    auto defaultHeight = (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2);
    auto defaultPointRadius = defaultHeight / 2 - 2.0_vp; // Get the default radius of the point.
    if (propPointRadius.has_value()) {
        json->PutExtAttr("pointRadius", propPointRadius.value().ToString().c_str(), filter);
    } else {
        json->PutExtAttr("pointRadius", defaultPointRadius.ToString().c_str(), filter);
    }
    json->PutExtAttr("unselectedColor", propUnselectedColor.value_or(Color()).ColorToString().c_str(), filter);
    auto defaultTrackBorderRadius = defaultHeight / 2; // Get the default border radius of the track.
    if (propTrackBorderRadius.has_value()) {
        json->PutExtAttr("trackBorderRadius", propTrackBorderRadius.value().ToString().c_str(), filter);
    } else {
        json->PutExtAttr("trackBorderRadius", defaultTrackBorderRadius.ToString().c_str(), filter);
    }
}

RefPtr<PaintProperty> SwitchPaintProperty::Clone() const
{
    auto value = MakeRefPtr<SwitchPaintProperty>();
    value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
    value->propSwitchPaintParagraph_ = CloneSwitchPaintParagraph();
    value->propIsOn_ = CloneIsOn();
    value->propSwitchAnimationStyle_ = CloneSwitchAnimationStyle();
    return value;
}

void SwitchPaintProperty::Reset()
{
    PaintProperty::Reset();
    ResetSwitchPaintParagraph();
    ResetIsOn();
    ResetSwitchAnimationStyle();
}

void SwitchPaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    if (propSwitchPaintParagraph_) {
        propSwitchPaintParagraph_->ToJsonValue(json, filter, GetHost());
    } else {
        SwitchPaintParagraph switchPaintParagraph;
        switchPaintParagraph.ToJsonValue(json, filter, GetHost());
    }
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("type", "ToggleType.Switch", filter);
    json->PutExtAttr("isOn", propIsOn_.value_or(false) ? "true" : "false", filter);
}
} // namespace OHOS::Ace::NG
