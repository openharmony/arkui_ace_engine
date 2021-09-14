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

#include "core/components_v2/inspector/inspector_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/box/box_element.h"
#include "core/components/display/render_display.h"
#include "core/components/flex/flex_item_element.h"
#include "core/components/flex/render_flex_item.h"
#include "core/components/text/render_text.h"
#include "core/components/text/text_element.h"
#include "core/components/transform/transform_element.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::V2 {

namespace {

constexpr uint32_t WINDOW_BLUR_STYLE_ENUM_OFFSET = 100;

const char* VISIBLE_TYPE[] = {
    "Visibility.Visible",
    "Visibility.Hidden",
    "Visibility.None"
};

const char* ITEM_ALIGN[] = {
    "ItemAlign.Auto",
    "ItemAlign.Start",
    "ItemAlign.Center",
    "ItemAlign.End",
    "ItemAlign.Stretch",
    "ItemAlign.Baseline"
};

const char* BORDER_STYLE[] = {
    "BorderStyle.Dotted",
    "BorderStyle.Dashed",
    "BorderStyle.Solid",
    "NONE"
};

const char* WINDOW_BLUR_STYLE[] = {
    "BlurStyle.SmallLight",
    "BlurStyle.MediumLight",
    "BlurStyle.LargeLight",
    "BlurStyle.XlargeLight",
    "BlurStyle.SmallDark",
    "BlurStyle.MediumDark",
    "BlurStyle.LargeDark",
    "BlurStyle.XlargeDark"
};

const char* ALIGNMENT_TYPE[3][3] = {
    { "Alignment.TopStart", "Alignment.Top", "Alignment.TopEnd" },
    { "Alignment.Start", "Alignment.Center", "Alignment.End" },
    { "Alignment.BottomStart", "Alignment.Bottom", "Alignment.BottomEnd" }
};

const char* GRID_SIZE_TYPE[] = {
    "default",
    "sx",
    "sm",
    "md",
    "lg"
};

const std::unordered_map<std::string, DoubleJsonFunc> CREATE_JSON_DOUBLE_MAP {
    { "opacity", [](const InspectorComposedElement& inspector) { return inspector.GetOpacity(); } },
    { "flexBasis", [](const InspectorComposedElement& inspector) { return inspector.GetFlexBasis(); } },
    { "flexGrow", [](const InspectorComposedElement& inspector) { return inspector.GetFlexGrow(); } },
    { "flexShrink", [](const InspectorComposedElement& inspector) { return inspector.GetFlexShrink(); } },
    { "gridOffset", [](const InspectorComposedElement& inspector) { return inspector.GetGridOffset(); } },
    { "width", [](const InspectorComposedElement& inspector) { return inspector.GetWidth(); } },
    { "height", [](const InspectorComposedElement& inspector) { return inspector.GetHeight(); } },
    { "blur", [](const InspectorComposedElement& inspector) { return inspector.GetBlur(); } },
    { "backdropBlur", [](const InspectorComposedElement& inspector) { return inspector.GetBackDropBlur(); } }
};

const std::unordered_map<std::string, StringJsonFunc> CREATE_JSON_STRING_MAP {
    { "visibility", [](const InspectorComposedElement& inspector) { return inspector.GetVisibility(); } },
    { "alignSelf", [](const InspectorComposedElement& inspector) { return inspector.GetAlignSelf(); } },
    { "padding-top",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetPadding(AnimatableType::PROPERTY_PADDING_TOP).ToString();
        } },
    { "padding-right",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetPadding(AnimatableType::PROPERTY_PADDING_RIGHT).ToString();
        } },
    { "padding-bottom",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetPadding(AnimatableType::PROPERTY_PADDING_BOTTOM).ToString();
        } },
    { "padding-left",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetPadding(AnimatableType::PROPERTY_PADDING_LEFT).ToString();
        } },
    { "margin-top",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetMargin(AnimatableType::PROPERTY_PADDING_TOP).ToString();
        } },
    { "margin-right",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetMargin(AnimatableType::PROPERTY_PADDING_RIGHT).ToString();
        } },
    { "margin-bottom",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetMargin(AnimatableType::PROPERTY_PADDING_BOTTOM).ToString();
        } },
    { "margin-left",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetMargin(AnimatableType::PROPERTY_PADDING_LEFT).ToString();
        } },
    { "constraintSize",
        [](const InspectorComposedElement& inspector) { return inspector.GetConstraintSize(); } },
    { "borderStyle", [](const InspectorComposedElement& inspector) { return inspector.GetBorderStyle(); } },
    { "borderWidth", [](const InspectorComposedElement& inspector) { return inspector.GetBorderWidth(); } },
    { "borderRadius",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetBorder().TopLeftRadius().GetX().ToString();
        } },
    { "backgroundImage", [](const InspectorComposedElement& inspector) { return inspector.GetBackgroundImage(); } }
};

const std::unordered_map<std::string, BoolJsonFunc> CREATE_JSON_BOOL_MAP { { "enabled",
    [](const InspectorComposedElement& inspector) { return inspector.GetEnabled(); } } };

const std::unordered_map<std::string, IntJsonFunc> CREATE_JSON_INT_MAP {
    { "zIndex", [](const InspectorComposedElement& inspector) { return inspector.GetZIndex(); } },
    { "gridSpan", [](const InspectorComposedElement& inspector) { return inspector.GetGridSpan(); } },
    { "layoutPriority", [](const InspectorComposedElement& inspector) { return inspector.GetLayoutPriority(); } },
    { "layoutWeight", [](const InspectorComposedElement& inspector) { return inspector.GetLayoutWeight(); } },
    { "borderColor", [](const InspectorComposedElement& inspector) { return inspector.GetBorderColor(); } }
};

const std::unordered_map<std::string, JsonValueJsonFunc> CREATE_JSON_JSON_VALUE_MAP {
    { "windowBlur", [](const InspectorComposedElement& inspector) { return inspector.GetWindowBlur(); } },
    { "shadow", [](const InspectorComposedElement& inspector) { return inspector.GetShadow(); } },
    { "position", [](const InspectorComposedElement& inspector) { return inspector.GetPosition(); } },
    { "offset", [](const InspectorComposedElement& inspector) { return inspector.GetOffset(); } },
    { "backgroundImageSize",
        [](const InspectorComposedElement& inspector) { return inspector.GetBackgroundImageSize(); } },
    { "backgroundImagePosition",
        [](const InspectorComposedElement& inspector) { return inspector.GetBackgroundImagePosition(); } },
    { "useSizeType",
        [](const InspectorComposedElement& inspector) { return inspector.GetUseSizeType(); } }
};

}; // namespace

std::unique_ptr<JsonValue> InspectorComposedElement::ToJsonObject() const
{
    auto resultJson = JsonUtil::Create(true);
    for (const auto& value : CREATE_JSON_DOUBLE_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this));
    }
    for (const auto& value : CREATE_JSON_STRING_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    for (const auto& value : CREATE_JSON_BOOL_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this));
    }
    for (const auto& value : CREATE_JSON_INT_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this));
    }

    for (const auto& value : CREATE_JSON_JSON_VALUE_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this));
    }
    return resultJson;
}

bool InspectorComposedElement::CanUpdate(const RefPtr<Component>& newComponent)
{
    return Element::CanUpdate(newComponent);
}

RefPtr<RenderNode> InspectorComposedElement::GetInspectorNode(IdType typeId) const
{
    LOGD("children size = %d", static_cast<int32_t>(children_.size()));
    auto child = children_.empty() ? nullptr : children_.front();
    while (child) {
        if (AceType::TypeId(child) == typeId) {
            return child->GetRenderNode();
        }
        child = child->GetChildren().empty() ? nullptr : child->GetChildren().front();
    }
    return nullptr;
}

RefPtr<RenderBox> InspectorComposedElement::GetRenderBox() const
{
    auto node = GetInspectorNode(BoxElement::TypeId());
    if (!node) {
        return nullptr;
    }
    return AceType::DynamicCast<RenderBox>(node);
}

double InspectorComposedElement::GetWidth() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetWidth();
    }
    return -1.0;
}

double InspectorComposedElement::GetHeight() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetHeight();
    }
    return -1.0;
}

Dimension InspectorComposedElement::GetPadding(OHOS::Ace::AnimatableType type) const
{
    auto render = GetRenderBox();
    if (render) {
        if (type == AnimatableType::PROPERTY_PADDING_LEFT) {
            return render->GetPadding(DimensionHelper(&Edge::SetLeft, &Edge::Left));
        } else if (type == AnimatableType::PROPERTY_PADDING_TOP) {
            return render->GetPadding(DimensionHelper(&Edge::SetTop, &Edge::Top));
        } else if (type == AnimatableType::PROPERTY_PADDING_RIGHT) {
            return render->GetPadding(DimensionHelper(&Edge::SetRight, &Edge::Right));
        } else if (type == AnimatableType::PROPERTY_PADDING_BOTTOM) {
            return render->GetPadding(DimensionHelper(&Edge::SetBottom, &Edge::Bottom));
        } else {
            render->GetPadding(DimensionHelper(&Edge::SetLeft, &Edge::Left)).ToString();
        }
    }
    return Dimension();
}

Dimension InspectorComposedElement::GetMargin(OHOS::Ace::AnimatableType type) const
{
    auto render = GetRenderBox();
    if (render) {
        if (type == AnimatableType::PROPERTY_MARGIN_LEFT) {
            return render->GetMargin(DimensionHelper(&Edge::SetLeft, &Edge::Left));
        } else if (type == AnimatableType::PROPERTY_MARGIN_TOP) {
            return render->GetMargin(DimensionHelper(&Edge::SetTop, &Edge::Top));
        } else if (type == AnimatableType::PROPERTY_MARGIN_RIGHT) {
            return render->GetMargin(DimensionHelper(&Edge::SetRight, &Edge::Right));
        } else if (type == AnimatableType::PROPERTY_MARGIN_BOTTOM) {
            return render->GetMargin(DimensionHelper(&Edge::SetBottom, &Edge::Bottom));
        }
    }
    return Dimension();
}

std::string InspectorComposedElement::GetConstraintSize() const
{
    LayoutParam layoutParam = LayoutParam(Size(), Size());
    auto render = GetRenderBox();
    if (render) {
        layoutParam = render->GetConstraints();
    }
    auto jsonStr = JsonUtil::Create(true);
    jsonStr->Put("minWidth", layoutParam.GetMinSize().Width());
    jsonStr->Put("minHeight", layoutParam.GetMinSize().Height());
    jsonStr->Put("maxWidth", layoutParam.GetMaxSize().Width());
    jsonStr->Put("maxHeight", layoutParam.GetMaxSize().Height());
    return jsonStr->ToString();
}

int32_t InspectorComposedElement::GetLayoutPriority() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetDisplayIndex();
    }
    return 0;
}

int32_t InspectorComposedElement::GetLayoutWeight() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetFlexWeight();
    }
    return 0.0;
}

std::string InspectorComposedElement::GetAlign() const
{
    auto render = GetRenderBox();
    if (render) {
        auto align = render->GetAlign();
        int32_t h = align.GetHorizontal() + 1;
        int32_t v = align.GetVertical() + 1;
        return ALIGNMENT_TYPE[h][v];
    }
    return ALIGNMENT_TYPE[1][1];
}

TextDirection InspectorComposedElement::GetDirection() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetTextDirection();
    }
    return TextDirection::AUTO;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetPosition() const
{
    auto jsonValue = JsonUtil::Create(true);
    auto node = GetInspectorNode(FlexItemElement::TypeId());
    if (!node) {
        jsonValue->Put("x", "0.0px");
        jsonValue->Put("y", "0.0px");
        return jsonValue;
    }
    auto render = AceType::DynamicCast<RenderFlexItem>(node);
    if (render) {
        PositionType type = render->GetPositionType();
        if (type == PositionType::ABSOLUTE) {
            jsonValue->Put("x", render->GetLeft().ToString().c_str());
            jsonValue->Put("y", render->GetTop().ToString().c_str());
            return jsonValue;
        }
    }
    jsonValue->Put("x", "0.0px");
    jsonValue->Put("y", "0.0px");
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetOffset() const
{
    auto jsonValue = JsonUtil::Create(true);
    auto node = GetInspectorNode(FlexItemElement::TypeId());
    if (!node) {
        jsonValue->Put("x", "0.0px");
        jsonValue->Put("y", "0.0px");
        return jsonValue;
    }
    auto render = AceType::DynamicCast<RenderFlexItem>(node);
    if (render) {
        PositionType type = render->GetPositionType();
        if (type == PositionType::OFFSET) {
            jsonValue->Put("x", render->GetLeft().ToString().c_str());
            jsonValue->Put("y", render->GetTop().ToString().c_str());
            return jsonValue;
        }
    }
    jsonValue->Put("x", "0.0px");
    jsonValue->Put("y", "0.0px");
    return jsonValue;
}

std::string InspectorComposedElement::GetRect() const
{
    std::string strRec;
    Rect rect = GetRenderRect();
    Rect parentRect = GetParentRect();
    rect = rect.Constrain(parentRect);
    strRec = std::to_string(rect.Left()).append(",").
            append(std::to_string(rect.Top())).
            append(",").append(std::to_string(rect.Width())).
            append(",").append(std::to_string(rect.Height()));
    return strRec;
}

Rect InspectorComposedElement::GetParentRect() const
{
    auto parent = GetElementParent().Upgrade();
    if (!parent) {
        return Rect();
    }
    Rect parentRect = parent->GetRenderRect();
    return parentRect;
}

double InspectorComposedElement::GetAspectRatio() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetAspectRatio();
    }
    return 0.0;
}

int32_t InspectorComposedElement::GetDisplayPriority() const
{
    auto node = GetInspectorNode(FlexItemElement::TypeId());
    if (!node) {
        return 1;
    }
    auto render = AceType::DynamicCast<RenderFlexItem>(node);
    if (render) {
        return render->GetDisplayIndex();
    }
    return 1;
}

double InspectorComposedElement::GetFlexBasis() const
{
    auto render = AceType::DynamicCast<RenderFlexItem>(GetInspectorNode(FlexItemElement::TypeId()));
    if (render) {
        return render->GetFlexBasis();
    }
    return 0.0;
}

double InspectorComposedElement::GetFlexGrow() const
{
    auto render = AceType::DynamicCast<RenderFlexItem>(GetInspectorNode(FlexItemElement::TypeId()));
    if (render) {
        return render->GetFlexGrow();
    }
    return 0.0;
}

double InspectorComposedElement::GetFlexShrink() const
{
    auto render = AceType::DynamicCast<RenderFlexItem>(GetInspectorNode(FlexItemElement::TypeId()));
    if (render) {
        return render->GetFlexShrink();
    }
    return 0.0;
}

std::string InspectorComposedElement::GetAlignSelf() const
{
    auto render = AceType::DynamicCast<RenderFlexItem>(GetInspectorNode(FlexItemElement::TypeId()));
    if (render) {
        return ITEM_ALIGN[static_cast<int32_t>(render->GetAlignSelf())];
    }
    return ITEM_ALIGN[0];
}

Border InspectorComposedElement::GetBorder() const
{
    auto render = GetRenderBox();
    if (!render) {
        return Border();
    }
    auto decoration = render->GetBackDecoration();
    if (decoration) {
        return decoration->GetBorder();
    }
    return Border();
}

std::string InspectorComposedElement::GetBorderStyle() const
{
    auto border = GetBorder();
    int32_t style = static_cast<int32_t>(border.Left().GetBorderStyle());
    return BORDER_STYLE[style];
}

std::string InspectorComposedElement::GetBorderWidth() const
{
    auto border = GetBorder();
    return border.Left().GetWidth().ToString();
}

uint32_t InspectorComposedElement::GetBorderColor() const
{
    auto border = GetBorder();
    return border.Left().GetColor().GetValue();
}

RefPtr<Decoration> InspectorComposedElement::GetBackDecoration() const
{
    auto render = GetRenderBox();
    if (!render) {
        return nullptr;
    }
    return render->GetBackDecoration();
}

std::string InspectorComposedElement::GetBackgroundImage() const
{
    auto backDecoration = GetBackDecoration();
    if (!backDecoration) {
        return "NONE";
    }
    auto image = backDecoration->GetImage();
    if (!image) {
        return "NONE";
    }
    return image->GetSrc();
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetBackgroundImageSize() const
{
    auto jsonValue = JsonUtil::Create(true);
    auto backDecoration = GetBackDecoration();
    if (!backDecoration) {
        jsonValue->Put("width", 0.0);
        jsonValue->Put("height", 0.0);
        return jsonValue;
    }
    auto image = backDecoration->GetImage();
    if (!image) {
        jsonValue->Put("width", 0.0);
        jsonValue->Put("height", 0.0);
        return jsonValue;
    }
    auto width = image->GetImageSize().GetSizeValueX();
    auto height = image->GetImageSize().GetSizeValueY();
    jsonValue->Put("width", width);
    jsonValue->Put("height", height);
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetBackgroundImagePosition() const
{
    auto jsonValue = JsonUtil::Create(true);
    auto backDecoration = GetBackDecoration();
    if (!backDecoration) {
        jsonValue->Put("x", 0.0);
        jsonValue->Put("y", 0.0);
        return jsonValue;
    }
    auto image = backDecoration->GetImage();
    if (!image) {
        jsonValue->Put("x", 0.0);
        jsonValue->Put("y", 0.0);
        return jsonValue;
    }
    auto width = image->GetImagePosition().GetSizeValueX();
    auto height = image->GetImagePosition().GetSizeValueY();
    jsonValue->Put("x", width);
    jsonValue->Put("y", height);
    return jsonValue;
}

RefPtr<Decoration> InspectorComposedElement::GetFrontDecoration() const
{
    auto render = GetRenderBox();
    if (!render) {
        return nullptr;
    }
    return render->GetFrontDecoration();
}

double InspectorComposedElement::GetOpacity() const
{
    auto node = GetInspectorNode(DisplayElement::TypeId());
    if (!node) {
        return 1.0;
    }
    auto render = AceType::DynamicCast<RenderDisplay>(node);
    if (!render) {
        return 1.0;
    }
    return render->GetTransitionOpacity();
}

std::string InspectorComposedElement::GetVisibility() const
{
    auto node = GetInspectorNode(DisplayElement::TypeId());
    if (!node) {
        return VISIBLE_TYPE[static_cast<int32_t>(VisibleType::VISIBLE)];
    }
    auto render = AceType::DynamicCast<RenderDisplay>(node);
    if (!render) {
        return VISIBLE_TYPE[static_cast<int32_t>(VisibleType::VISIBLE)];
    }
    return VISIBLE_TYPE[static_cast<int32_t>(render->GetVisibleType())];
}

bool InspectorComposedElement::GetEnabled() const
{
    auto node = GetInspectorNode(ComposedElement::TypeId());
    if (!node) {
        return true;
    }
    return !node->IsDisabled();
}

int32_t InspectorComposedElement::GetZIndex() const
{
    auto node = GetInspectorNode(GetTargetTypeId());
    if (!node) {
        return 0;
    }
    return node->GetZIndex();
}

DimensionOffset InspectorComposedElement::GetOriginPoint() const
{
    auto node = GetInspectorNode(TransformElement::TypeId());
    if (!node) {
        return DimensionOffset(OHOS::Ace::HALF_PERCENT, OHOS::Ace::HALF_PERCENT);
    }
    auto render = AceType::DynamicCast<RenderTransform>(node);
    if (!render) {
        return DimensionOffset(OHOS::Ace::HALF_PERCENT, OHOS::Ace::HALF_PERCENT);
    }
    return render->GetTransformOrigin();
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetTransformEffect() const
{
    auto render = AceType::DynamicCast<RenderTransform>(GetInspectorNode(BoxElement::TypeId()));
    if (!render) {
        return nullptr;
    }
    auto jsonValue = JsonUtil::CreateArray(true);

    for (const auto& operation : render->GetTransformEffects().GetOperations()) {
        switch (operation.type_) {
            case TransformOperationType::TRANSLATE: {
                auto itemValue = JsonUtil::Create(true);
                const auto& translate = operation.translateOperation_;
                itemValue->Put("type", "translate");
                itemValue->Put("x", translate.dx.ToString().c_str());
                itemValue->Put("y", translate.dy.ToString().c_str());
                itemValue->Put("z", translate.dz.ToString().c_str());
                jsonValue->Put(itemValue);
                break;
            }
            case TransformOperationType::SCALE: {
                auto itemValue = JsonUtil::Create(true);
                const auto& scale = operation.scaleOperation_;
                itemValue->Put("type", "scale");
                itemValue->Put("x", std::to_string(scale.scaleX).c_str());
                itemValue->Put("y", std::to_string(scale.scaleY).c_str());
                itemValue->Put("z", std::to_string(scale.scaleZ).c_str());
                jsonValue->Put(itemValue);
                break;
            }
            case TransformOperationType::ROTATE: {
                auto itemValue = JsonUtil::Create(true);
                const auto& rotate = operation.rotateOperation_;
                itemValue->Put("type", "rotate");
                itemValue->Put("x", std::to_string(rotate.dx).c_str());
                itemValue->Put("y", std::to_string(rotate.dy).c_str());
                itemValue->Put("z", std::to_string(rotate.dz).c_str());
                itemValue->Put("angle", std::to_string(rotate.angle).c_str());
                jsonValue->Put(itemValue);
                break;
            }
            case TransformOperationType::MATRIX: {
                auto itemValue = JsonUtil::Create(true);
                const auto& matrix = operation.matrix4_;
                itemValue->Put("type", "matrix");
                itemValue->Put("matrix", matrix.ToString().c_str());
                jsonValue->Put(itemValue);
                break;
            }
            default:
                break;
        }
    }

    return jsonValue;
}

double InspectorComposedElement::GetBlur() const
{
    auto render = AceType::DynamicCast<RenderBox>(GetInspectorNode(BoxElement::TypeId()));
    if (!render) {
        return 0.0;
    }
    return render->GetBlurRadius().Value();
}

double InspectorComposedElement::GetBackDropBlur() const
{
    auto render = AceType::DynamicCast<RenderBox>(GetInspectorNode(BoxElement::TypeId()));
    if (!render) {
        return 0.0;
    }
    return render->GetBackdropRadius().Value();
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetWindowBlur() const
{
    auto render = AceType::DynamicCast<RenderBox>(GetInspectorNode(BoxElement::TypeId()));
    if (!render) {
        return nullptr;
    }
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("percent", std::to_string(render->GetWindowBlurProgress()).c_str());
    jsonValue->Put(
        "style", WINDOW_BLUR_STYLE[static_cast<int32_t>(render->GetWindowBlurStyle()) - WINDOW_BLUR_STYLE_ENUM_OFFSET]);
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetShadow() const
{
    auto render = AceType::DynamicCast<RenderBox>(GetInspectorNode(BoxElement::TypeId()));
    if (!render) {
        return nullptr;
    }
    auto jsonValue = JsonUtil::Create(true);
    Shadow shadow = render->GetShadow();
    jsonValue->Put("radius", std::to_string(shadow.GetBlurRadius()).c_str());
    jsonValue->Put("color", std::to_string(shadow.GetColor().GetValue()).c_str());
    jsonValue->Put("offsetX", std::to_string(shadow.GetOffset().GetX()).c_str());
    jsonValue->Put("offsetY", std::to_string(shadow.GetOffset().GetY()).c_str());
    return jsonValue;
}

RefPtr<ClipPath> InspectorComposedElement::GetClip() const
{
    auto render = GetRenderBox();
    if (!render) {
        return nullptr;
    }
    return render->GetClipPath();
}

bool InspectorComposedElement::GetBoxClipFlag() const
{
    auto render = GetRenderBox();
    if (!render) {
        return false;
    }
    return render->GetBoxClipFlag();
}

RefPtr<Mask> InspectorComposedElement::GetMask() const
{
    auto render = GetRenderBox();
    if (!render) {
        return nullptr;
    }
    return render->GetMask();
}

RefPtr<GridColumnInfo> InspectorComposedElement::GetGridColumnInfo() const
{
    auto render = GetRenderBox();
    if (!render) {
        return nullptr;
    }
    auto columnInfo = render->GetGridColumnInfo();
    if (!columnInfo) {
        return nullptr;
    }
    return columnInfo;
}

int32_t InspectorComposedElement::GetGridSpan() const
{
    auto columnInfo = GetGridColumnInfo();
    if (columnInfo) {
        return columnInfo->GetColumns();
    }
    return OHOS::Ace::DEFAULT_GRID_COLUMN_SPAN;
}

int32_t InspectorComposedElement::GetGridOffset() const
{
    auto columnInfo = GetGridColumnInfo();
    if (columnInfo) {
        return columnInfo->GetOffset(GridSizeType::UNDEFINED);
    }
    return 0;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetUseSizeType() const
{
    auto columnInfo = GetGridColumnInfo();
    if (!columnInfo) {
        return nullptr;
    }
    auto jsonRoot = JsonUtil::Create(true);
    int32_t index = static_cast<int32_t>(GridSizeType::XS);
    for (; index < static_cast<int32_t>(GridSizeType::XL); index++) {
        auto jsonValue = JsonUtil::Create(false);
        GridSizeType type = static_cast<GridSizeType>(index);
        jsonValue->Put("span", static_cast<int32_t>(columnInfo->GetColumns(type)));
        jsonValue->Put("offset", columnInfo->GetOffset(type));
        jsonRoot->Put(GRID_SIZE_TYPE[index], jsonValue);
    }
    return jsonRoot;
}

} // namespace OHOS::Ace::V2
