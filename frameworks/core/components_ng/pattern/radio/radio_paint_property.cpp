/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/radio/radio_paint_property.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

RefPtr<PaintProperty> RadioPaintProperty::Clone() const
{
    auto paintProperty = MakeRefPtr<RadioPaintProperty>();
    paintProperty->UpdatePaintProperty(this);
    paintProperty->propRadioCheck_ = CloneRadioCheck();
    paintProperty->propRadioCheckedBackgroundColor_ = CloneRadioCheckedBackgroundColor();
    paintProperty->propRadioUncheckedBorderColor_ = CloneRadioUncheckedBorderColor();
    paintProperty->propRadioIndicatorColor_ = CloneRadioIndicatorColor();
    paintProperty->propRadioIndicator_ = CloneRadioIndicator();
    return paintProperty;
}

void RadioPaintProperty::Reset()
{
    PaintProperty::Reset();
    ResetRadioCheck();
    ResetRadioCheckedBackgroundColor();
    ResetRadioUncheckedBorderColor();
    ResetRadioIndicatorColor();
    ResetRadioIndicator();
}

void RadioPaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    PaintProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto radioTheme = pipeline->GetTheme<RadioTheme>();
    json->PutExtAttr("checked", GetRadioCheck().value_or(false) ? "true" : "false", filter);
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("checkedBackgroundColor",
        GetRadioCheckedBackgroundColor().value_or(radioTheme->GetActiveColor()).ColorToString().c_str());
    jsonValue->Put("uncheckedBorderColor",
        GetRadioUncheckedBorderColor().value_or(radioTheme->GetInactiveColor()).ColorToString().c_str());
    jsonValue->Put(
        "indicatorColor", GetRadioIndicatorColor().value_or(radioTheme->GetPointColor()).ColorToString().c_str());
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        static const char* INDICATRO_TYPE[] = { "TICK", "DOT", "CUSTOM" };
        json->PutExtAttr(
            "indicatorType", INDICATRO_TYPE[static_cast<int32_t>(GetRadioIndicator().value_or(0))], filter);
    }
    json->PutExtAttr("radioStyle", jsonValue->ToString().c_str(), filter);
}

void RadioPaintProperty::ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const
{
    PaintProperty::ToTreeJson(json, config);
    json->Put(TreeKey::CHECKED, GetRadioCheck().value_or(false) ? "true" : "false");
}
} // namespace OHOS::Ace::NG
