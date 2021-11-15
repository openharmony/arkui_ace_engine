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

#include "core/components_v2/inspector/progress_composed_element.h"

#include <unordered_map>

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components/progress/progress_element.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const ProgressComposedElement&)>> CREATE_JSON_MAP {
    { "value", [](const ProgressComposedElement& inspector) { return inspector.GetValue(); } },
    { "total", [](const ProgressComposedElement& inspector) { return inspector.GetTotal(); } },
    { "style", [](const ProgressComposedElement& inspector) { return inspector.GetStyle(); } },
    { "color", [](const ProgressComposedElement& inspector) { return inspector.GetColor(); } },
    { "strokeWidth", [](const ProgressComposedElement& inspector) { return inspector.GetStrokeWidth(); } },
    { "scaleCount", [](const ProgressComposedElement& inspector) { return inspector.GetScaleCount(); } },
    { "scaleWidth", [](const ProgressComposedElement& inspector) { return inspector.GetScaleWidth(); } }
};

} // namespace

void ProgressComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("value: ").append(GetValue()));
    DumpLog::GetInstance().AddDesc(std::string("total: ").append(GetTotal()));
    DumpLog::GetInstance().AddDesc(std::string("style: ").append(GetStyle()));
    DumpLog::GetInstance().AddDesc(std::string("color: ").append(GetColor()));
    DumpLog::GetInstance().AddDesc(std::string("strokeWidth: ").append(GetStrokeWidth()));
    DumpLog::GetInstance().AddDesc(std::string("scaleCount: ").append(GetScaleCount()));
    DumpLog::GetInstance().AddDesc(std::string("scaleWidth: ").append(GetScaleWidth()));
}

std::unique_ptr<JsonValue> ProgressComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string ProgressComposedElement::GetValue() const
{
    auto renderProgress = GetRenderProgress();
    if (renderProgress) {
        return std::to_string(renderProgress->GetValue());
    }
    return "";
}

std::string ProgressComposedElement::GetTotal() const
{
    auto renderProgress = GetRenderProgress();
    if (renderProgress) {
        return std::to_string(renderProgress->GetMaxValue());
    }
    return "";
}

std::string ProgressComposedElement::GetStyle() const
{
    auto renderProgress = GetRenderProgress();
    if (renderProgress) {
        ProgressType type = renderProgress->GetProgressType();
        if (type == ProgressType::LINEAR) {
            return std::string("ProgressStyle.Linear");
        } else if (type == ProgressType::MOON) {
            return std::string("ProgressStyle.Eclipse");
        } else if (type == ProgressType::CIRCLE) {
            return std::string("ProgressStyle.Circular");
        } else {
            return "";
        }
    }
    return "";
}

std::string ProgressComposedElement::GetColor() const
{
    auto renderProgress = GetRenderProgress();
    if (renderProgress) {
        Color color = renderProgress->GetProgressComponent()->GetSelectColor();
        return std::to_string(color.GetValue());
    }
    return "";
}

std::string ProgressComposedElement::GetStrokeWidth() const
{
    auto renderProgress = GetRenderProgress();
    if (renderProgress) {
        Dimension strokeWidth = renderProgress->GetProgressComponent()->GetTrackThickness();
        return strokeWidth.ToString();
    }
    return "";
}

std::string ProgressComposedElement::GetScaleCount() const
{
    auto renderProgress = GetRenderProgress();
    if (renderProgress) {
        auto scaleCount = renderProgress->GetProgressComponent()->GetScaleNumber();
        return std::to_string(scaleCount);
    }
    return "";
}

std::string ProgressComposedElement::GetScaleWidth() const
{
    auto renderProgress = GetRenderProgress();
    if (renderProgress) {
        Dimension scaleWidth = renderProgress->GetProgressComponent()->GetScaleWidth();
        return scaleWidth.ToString();
    }
    return "";
}

RefPtr<RenderProgress> ProgressComposedElement::GetRenderProgress() const
{
    auto node = GetInspectorNode(ProgressElement::TypeId());
    if (node) {
        return AceType::DynamicCast<RenderProgress>(node);
    }
    return nullptr;
}

} // namespace OHOS::Ace::V2
