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

#include "core/components_v2/inspector/shape_container_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/shape/render_shape_container.h"
#include "core/components/shape/shape_container_element.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const ShapeContainerComposedElement&)>>
    CREATE_JSON_MAP {
        { "fill", [](const ShapeContainerComposedElement& inspector) { return inspector.GetFill(); } },
        { "fillOpacity", [](const ShapeContainerComposedElement& inspector) { return inspector.GetFillOpacity(); } },
        { "stroke", [](const ShapeContainerComposedElement& inspector) { return inspector.GetStroke(); } },
        { "strokeDashOffset",
            [](const ShapeContainerComposedElement& inspector) { return inspector.GetStrokeDashOffset(); } },
        { "strokeDashArray",
            [](const ShapeContainerComposedElement& inspector) { return inspector.GetStrokeDashArray(); } },
        { "strokeLineCap",
            [](const ShapeContainerComposedElement& inspector) { return inspector.GetStrokeLineCap(); } },
        { "strokeLineJoin",
            [](const ShapeContainerComposedElement& inspector) { return inspector.GetStrokeLineJoin(); } },
        { "strokeMiterLimit",
            [](const ShapeContainerComposedElement& inspector) { return inspector.GetStrokeMiterLimit(); } },
        { "strokeOpacity",
            [](const ShapeContainerComposedElement& inspector) { return inspector.GetStrokeOpacity(); } },
        { "strokeWidth", [](const ShapeContainerComposedElement& inspector) { return inspector.GetStrokeWidth(); } },
        { "antiAlias", [](const ShapeContainerComposedElement& inspector) { return inspector.GetAntiAlias(); } },
        { "viewPort", [](const ShapeContainerComposedElement& inspector) { return inspector.GetViewBox(); } },
    };

}

void ShapeContainerComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    for (const auto& value : CREATE_JSON_MAP) {
        DumpLog::GetInstance().AddDesc(std::string(value.first + ": ").append(value.second(*this)));
    }
}

std::unique_ptr<JsonValue> ShapeContainerComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string ShapeContainerComposedElement::GetAntiAlias() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return ConvertBoolToString(render->GetAntiAlias());
    }
    return "";
}

std::string ShapeContainerComposedElement::GetFill() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return std::to_string(render->GetFillState().GetColor().GetValue());
    }
    return "";
}

std::string ShapeContainerComposedElement::GetFillOpacity() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return std::to_string(render->GetFillState().GetOpacity().GetValue());
    }
    return "";
}

std::string ShapeContainerComposedElement::GetStroke() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return std::to_string(render->GetStrokeState().GetColor().GetValue());
    }
    return "";
}

std::string ShapeContainerComposedElement::GetStrokeDashOffset() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return render->GetStrokeState().GetStrokeDashOffset().ToString();
    }
    return "";
}

std::string ShapeContainerComposedElement::GetStrokeDashArray() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        std::string strDashArray;
        for (const auto& dash : render->GetStrokeState().GetStrokeDashArray()) {
            strDashArray.append(dash.ToString() + ",");
        }
        return strDashArray;
    }
    return "";
}

std::string ShapeContainerComposedElement::GetStrokeLineCap() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return std::to_string(static_cast<int32_t>(render->GetStrokeState().GetLineCap()));
    }
    return "";
}

std::string ShapeContainerComposedElement::GetStrokeLineJoin() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return std::to_string(static_cast<int32_t>(render->GetStrokeState().GetLineJoin()));
    }
    return "";
}

std::string ShapeContainerComposedElement::GetStrokeMiterLimit() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return std::to_string(render->GetStrokeState().GetMiterLimit());
    }
    return "";
}

std::string ShapeContainerComposedElement::GetStrokeOpacity() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return std::to_string(render->GetStrokeState().GetOpacity().GetValue());
    }
    return "";
}

std::string ShapeContainerComposedElement::GetStrokeWidth() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        return render->GetStrokeState().GetLineWidth().ToString();
    }
    return "";
}

std::string ShapeContainerComposedElement::GetViewBox() const
{
    auto render = GetContentRender<RenderShapeContainer>(ShapeContainerElement::TypeId());
    if (render) {
        std::string strViewPort;
        auto viewBox = render->GetShapeViewBox();
        strViewPort.append("x = ")
            .append(viewBox.Left().ToString())
            .append(" y = ")
            .append(viewBox.Top().ToString())
            .append(" width = ")
            .append(viewBox.Width().ToString())
            .append(" height = ")
            .append(viewBox.Height().ToString());
        return strViewPort;
    }
    return "";
}

} // namespace OHOS::Ace::V2