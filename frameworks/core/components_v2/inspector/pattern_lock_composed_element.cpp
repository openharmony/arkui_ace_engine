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

#include "core/components_v2/inspector/pattern_lock_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components_v2/inspector/utils.h"
namespace OHOS::Ace::V2 {
namespace {
const std::unordered_map<std::string, std::function<std::string(const PatternLockComposedElement&)>> CREATE_JSON_MAP {
    { "sideLength", [](const PatternLockComposedElement& inspector) { return inspector.GetSideLength(); } },
    { "circleRadius", [](const PatternLockComposedElement& inspector) { return inspector.GetCircleRadius(); } },
    { "regularColor", [](const PatternLockComposedElement& inspector) { return inspector.GetRegularColor(); } },
    { "selectedColor", [](const PatternLockComposedElement& inspector) { return inspector.GetSelectedColor(); } },
    { "activeColor", [](const PatternLockComposedElement& inspector) { return inspector.GetActiveColor(); } },
    { "pathColor", [](const PatternLockComposedElement& inspector) { return inspector.GetPathColor(); } },
    { "pathStrokeWidth", [](const PatternLockComposedElement& inspector) { return inspector.GetStrokeWidth(); } },
    { "autoReset", [](const PatternLockComposedElement& inspector) { return inspector.GetAutoReset(); } }
};
}

void PatternLockComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("sideLength: ").append(GetSideLength()));
    DumpLog::GetInstance().AddDesc(
        std::string("circleRadius: ").append(GetCircleRadius()));
    DumpLog::GetInstance().AddDesc(
        std::string("regularColor: ").append(GetRegularColor()));
    DumpLog::GetInstance().AddDesc(
        std::string("selectedColor: ").append(GetSelectedColor()));
    DumpLog::GetInstance().AddDesc(
        std::string("activeColor: ").append(GetActiveColor()));
    DumpLog::GetInstance().AddDesc(
        std::string("pathColor: ").append(GetPathColor()));
    DumpLog::GetInstance().AddDesc(
        std::string("pathStrokeWidth: ").append(GetStrokeWidth()));
    DumpLog::GetInstance().AddDesc(
        std::string("autoReset: ").append(GetAutoReset()));
}

std::unique_ptr<JsonValue> PatternLockComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string PatternLockComposedElement::GetSideLength() const
{
    auto node = GetInspectorNode(PatternLockElement::TypeId());
    if (!node) {
        return "300vp";
    }
    auto renderPatternLock = AceType::DynamicCast<RenderPatternLock>(node);
    if (renderPatternLock) {
        return renderPatternLock->GetSideLength().ToString();
    }
    return "300vp";
}

std::string PatternLockComposedElement::GetCircleRadius() const
{
    auto node = GetInspectorNode(PatternLockElement::TypeId());
    if (!node) {
        return "14vp";
    }
    auto renderPatternLock = AceType::DynamicCast<RenderPatternLock>(node);
    if (renderPatternLock) {
        return renderPatternLock->GetCircleRadius().ToString();
    }
    return "14vp";
}

std::string PatternLockComposedElement::GetRegularColor() const
{
    auto node = GetInspectorNode(PatternLockElement::TypeId());
    if (!node) {
        return "Color.Black";
    }
    auto renderPatternLock = AceType::DynamicCast<RenderPatternLock>(node);
    if (renderPatternLock) {
        return renderPatternLock->GetRegularColor().ColorToString();
    }
    return "Color.Black";
}

std::string PatternLockComposedElement::GetSelectedColor() const
{
    auto node = GetInspectorNode(PatternLockElement::TypeId());
    if (!node) {
        return "Color.Black";
    }
    auto renderPatternLock = AceType::DynamicCast<RenderPatternLock>(node);
    if (renderPatternLock) {
        return renderPatternLock->GetSelectedColor().ColorToString();
    }
    return "Color.Black";
}

std::string PatternLockComposedElement::GetActiveColor() const
{
    auto node = GetInspectorNode(PatternLockElement::TypeId());
    if (!node) {
        return "Color.Black";
    }
    auto renderPatternLock = AceType::DynamicCast<RenderPatternLock>(node);
    if (renderPatternLock) {
        return renderPatternLock->GetActiveColor().ColorToString();
    }
    return "Color.Black";
}

std::string PatternLockComposedElement::GetPathColor() const
{
    auto node = GetInspectorNode(PatternLockElement::TypeId());
    if (!node) {
        return "Color.Black";
    }
    auto renderPatternLock = AceType::DynamicCast<RenderPatternLock>(node);
    if (renderPatternLock) {
        return renderPatternLock->GetPathColor().ColorToString();
    }
    return "Color.Black";
}

std::string PatternLockComposedElement::GetStrokeWidth() const
{
    auto node = GetInspectorNode(PatternLockElement::TypeId());
    if (!node) {
        return "34vp";
    }
    auto renderPatternLock = AceType::DynamicCast<RenderPatternLock>(node);
    if (renderPatternLock) {
        return renderPatternLock->GetStrokeWidth().ToString();
    }
    return "34vp";
}

std::string PatternLockComposedElement::GetAutoReset() const
{
    auto node = GetInspectorNode(PatternLockElement::TypeId());
    if (!node) {
        return "true";
    }
    auto renderPatternLock = AceType::DynamicCast<RenderPatternLock>(node);
    if (renderPatternLock) {
        return ConvertBoolToString(renderPatternLock->GetAutoReset());
    }
    return "true";
}
} // namespace OHOS::Ace::V2