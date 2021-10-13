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

#include "core/components_v2/inspector/shape_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/shape/shape_element.h"
#include "core/components_v2/inspector/shape_container_composed_element.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const ShapeComposedElement&)>> CREATE_JSON_MAP {
    { "shapeType", [](const ShapeComposedElement& inspector) { return inspector.GetShapeType(); } },
    { "fill", [](const ShapeComposedElement& inspector) { return inspector.GetFill(); } },
    { "fillOpacity", [](const ShapeComposedElement& inspector) { return inspector.GetFillOpacity(); } },
    { "stroke", [](const ShapeComposedElement& inspector) { return inspector.GetStroke(); } },
    { "strokeDashOffset", [](const ShapeComposedElement& inspector) { return inspector.GetStrokeDashOffset(); } },
    { "strokeLineCap", [](const ShapeComposedElement& inspector) { return inspector.GetStrokeLineCap(); } },
    { "strokeLineJoin", [](const ShapeComposedElement& inspector) { return inspector.GetStrokeLineJoin(); } },
    { "strokeMiterLimit", [](const ShapeComposedElement& inspector) { return inspector.GetStrokeMiterLimit(); } },
    { "strokeOpacity", [](const ShapeComposedElement& inspector) { return inspector.GetStrokeOpacity(); } },
    { "strokeWidth", [](const ShapeComposedElement& inspector) { return inspector.GetStrokeWidth(); } },
    { "antiAlias", [](const ShapeComposedElement& inspector) { return inspector.GetAntiAlias(); } },
    { "commands", [](const ShapeComposedElement& inspector) { return inspector.GetCommands(); } },
    { "topLeftRadius", [](const ShapeComposedElement& inspector) { return inspector.GetTopLeftRadius(); } },
    { "topRightRadius", [](const ShapeComposedElement& inspector) { return inspector.GetTopRightRadius(); } },
    { "bottomLeftRadius", [](const ShapeComposedElement& inspector) { return inspector.GetBottomLeftRadius(); } },
    { "bottomRightRadius", [](const ShapeComposedElement& inspector) { return inspector.GetBottomRightRadius(); } },
};

using JsonFuncType = std::function<std::unique_ptr<JsonValue>(const ShapeComposedElement&)>;
const std::unordered_map<std::string, JsonFuncType> CREATE_JSON_JSON_VALUE_MAP {
    { "strokeDashArray", [](const ShapeComposedElement& inspector) { return inspector.GetStrokeDashArray(); } },
};

} // namespace

void ShapeComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    for (const auto& value: CREATE_JSON_MAP) {
        DumpLog::GetInstance().AddDesc(std::string(value.first + ":").append(value.second(*this)));
    }
}

std::string ShapeComposedElement::GetWidth() const
{
    auto renderShape = AceType::DynamicCast<RenderShape>(GetInspectorNode(ShapeElement::TypeId()));
    if (renderShape) {
        return renderShape->GetWidthDimension().ToString();
    }
    return InspectorComposedElement::GetWidth();
}

std::string ShapeComposedElement::GetHeight() const
{
    auto renderShape = AceType::DynamicCast<RenderShape>(GetInspectorNode(ShapeElement::TypeId()));
    if (renderShape) {
        return renderShape->GetHeightDimension().ToString();
    }
    return InspectorComposedElement::GetHeight();
}

std::unique_ptr<JsonValue> ShapeComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    for (const auto& value : CREATE_JSON_JSON_VALUE_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this));
    }

    return resultJson;
}

std::string ShapeComposedElement::GetShapeType() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return std::to_string(static_cast<int32_t>(render->GetShapeType()));
    }
    return "";
}

std::string ShapeComposedElement::GetCommands() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return render->GetPathCmd();
    }
    return "";
}

std::string ShapeComposedElement::GetAntiAlias() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return ConvertBoolToString(render->GetAntiAlias());
    }
    return "";
}

std::string ShapeComposedElement::GetTopLeftRadius() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return render->GetTopLeftRadius().ToString();
    }
    return "";
}

std::string ShapeComposedElement::GetTopRightRadius() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return render->GetTopRightRadius().ToString();
    }
    return "";
}

std::string ShapeComposedElement::GetBottomRightRadius() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return render->GetBottomRightRadius().ToString();
    }
    return "";
}

std::string ShapeComposedElement::GetBottomLeftRadius() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return render->GetBottomLeftRadius().ToString();
    }
    return "";
}

std::string ShapeComposedElement::GetFill() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return render->GetFillState().GetColor().ColorToString();
    }
    return "";
}

std::string ShapeComposedElement::GetFillOpacity() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return std::to_string(render->GetFillState().GetOpacity().GetValue());
    }
    return "";
}

std::string ShapeComposedElement::GetStroke() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return render->GetStrokeState().GetColor().ColorToString();
    }
    return "";
}

std::string ShapeComposedElement::GetStrokeDashOffset() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return render->GetStrokeState().GetStrokeDashOffset().ToString();
    }
    return "";
}

std::unique_ptr<JsonValue> ShapeComposedElement::GetStrokeDashArray() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    auto jsonDashArray = JsonUtil::CreateArray(true);
    if (render) {
        std::vector<Dimension> array = render->GetStrokeState().GetStrokeDashArray();
        for (size_t i = 0; i < array.size(); i++) {
            auto index = std::to_string(i);
            auto value = array[i].ToString();
            jsonDashArray->Put(index.c_str(), value.c_str());
        }
    }
    return jsonDashArray;
}

std::string ShapeComposedElement::GetStrokeLineCap() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        auto style = render->GetStrokeState().GetLineCap();
        return ShapeContainerComposedElement::LineCapStyleToString(style);
    }
    return "";
}

std::string ShapeComposedElement::GetStrokeLineJoin() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        auto style = render->GetStrokeState().GetLineJoin();
        return ShapeContainerComposedElement::LineJoinStyleToString(style);
    }
    return "";
}

std::string ShapeComposedElement::GetStrokeMiterLimit() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return std::to_string(render->GetStrokeState().GetMiterLimit());
    }
    return "";
}

std::string ShapeComposedElement::GetStrokeOpacity() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return std::to_string(render->GetStrokeState().GetOpacity().GetValue());
    }
    return "";
}

std::string ShapeComposedElement::GetStrokeWidth() const
{
    auto render = GetContentRender<RenderShape>(ShapeElement::TypeId());
    if (render) {
        return render->GetStrokeState().GetLineWidth().ToString();
    }
    return "";
}

} // namespace OHOS::Ace::V2