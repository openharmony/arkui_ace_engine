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
#include "core/components/coverage/render_coverage.h"
#include "core/components/display/render_display.h"
#include "core/components/flex/flex_item_element.h"
#include "core/components/flex/render_flex_item.h"
#include "core/components/text/render_text.h"
#include "core/components/text/text_element.h"
#include "core/components/transform/transform_element.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {

namespace {

constexpr uint32_t WINDOW_BLUR_STYLE_ENUM_OFFSET = 100;

const char* VISIBLE_TYPE[] = { "Visibility.Visible", "Visibility.Hidden", "Visibility.None" };

const char* ITEM_ALIGN[] = { "ItemAlign.Auto", "ItemAlign.Start", "ItemAlign.Center", "ItemAlign.End",
    "ItemAlign.Stretch", "ItemAlign.Baseline" };

// NONE translate to Solid
const char* BORDER_STYLE[] = {
    "BorderStyle.Solid",
    "BorderStyle.Dashed",
    "BorderStyle.Dotted",
    "BorderStyle.Solid",
};

const char* WINDOW_BLUR_STYLE[] = { "BlurStyle.SmallLight", "BlurStyle.MediumLight", "BlurStyle.LargeLight",
    "BlurStyle.XlargeLight", "BlurStyle.SmallDark", "BlurStyle.MediumDark", "BlurStyle.LargeDark",
    "BlurStyle.XlargeDark" };

const char* ALIGNMENT_TYPE[3][3] = { { "Alignment.TopStart", "Alignment.Start", "Alignment.BottomStart" },
    { "Alignment.Top", "Alignment.Center", "Alignment.Bottom" },
    { "Alignment.TopEnd", "Alignment.End", "Alignment.BottomEnd" } };

const char* GRID_SIZE_TYPE[] = { "default", "sx", "sm", "md", "lg" };

constexpr const char* TEXT_DIRECTION[] = { "Direction.Ltr", "Direction.Rtl", "Direction.Inherit", "Direction.Auto" };

constexpr const char* BASIC_SHAPE_TYPE[] { "None", "Inset", "Circle", "Ellipse", "Polygon", "Path", "Rect" };

const std::unordered_map<std::string, DoubleJsonFunc> CREATE_JSON_DOUBLE_MAP {
    { "opacity", [](const InspectorComposedElement& inspector) { return inspector.GetOpacity(); } },
    { "flexGrow", [](const InspectorComposedElement& inspector) { return inspector.GetFlexGrow(); } },
    { "flexShrink", [](const InspectorComposedElement& inspector) { return inspector.GetFlexShrink(); } },
    { "gridOffset", [](const InspectorComposedElement& inspector) { return inspector.GetGridOffset(); } },
    { "blur", [](const InspectorComposedElement& inspector) { return inspector.GetBlur(); } },
    { "backdropBlur", [](const InspectorComposedElement& inspector) { return inspector.GetBackDropBlur(); } },
    { "aspectRatio", [](const InspectorComposedElement& inspector) { return inspector.GetAspectRatio(); } },
    { "brightness", [](const InspectorComposedElement& inspector) { return inspector.GetBrightness(); } },
    { "saturate", [](const InspectorComposedElement& inspector) { return inspector.GetSaturate(); } },
    { "contrast", [](const InspectorComposedElement& inspector) { return inspector.GetContrast(); } },
    { "invert", [](const InspectorComposedElement& inspector) { return inspector.GetInvert(); } },
    { "sepia", [](const InspectorComposedElement& inspector) { return inspector.GetSepia(); } },
    { "grayscale", [](const InspectorComposedElement& inspector) { return inspector.GetGrayScale(); } },
    { "hueRotate", [](const InspectorComposedElement& inspector) { return inspector.GetHueRotate(); } },
};

const std::unordered_map<std::string, StringJsonFunc> CREATE_JSON_STRING_MAP {
    { "visibility", [](const InspectorComposedElement& inspector) { return inspector.GetVisibility(); } },
    { "alignSelf", [](const InspectorComposedElement& inspector) { return inspector.GetAlignSelf(); } },
    { "constraintSize", [](const InspectorComposedElement& inspector) { return inspector.GetConstraintSize(); } },
    { "borderColor", [](const InspectorComposedElement& inspector) { return inspector.GetBorderColor(); } },
    { "borderStyle", [](const InspectorComposedElement& inspector) { return inspector.GetBorderStyle(); } },
    { "borderWidth", [](const InspectorComposedElement& inspector) { return inspector.GetBorderWidth(); } },
    { "borderRadius",
        [](const InspectorComposedElement& inspector) {
            return inspector.GetBorderRadius();
        } },
    { "backgroundImage", [](const InspectorComposedElement& inspector) { return inspector.GetBackgroundImage(); } },
    { "backgroundColor", [](const InspectorComposedElement& inspector) { return inspector.GetBackgroundColor(); } },
    { "flexBasis", [](const InspectorComposedElement& inspector) { return inspector.GetFlexBasis(); } },
    { "width", [](const InspectorComposedElement& inspector) { return inspector.GetWidth(); } },
    { "height", [](const InspectorComposedElement& inspector) { return inspector.GetHeight(); } },
    { "align", [](const InspectorComposedElement& inspector) { return inspector.GetAlign(); } },
};

const std::unordered_map<std::string, BoolJsonFunc> CREATE_JSON_BOOL_MAP {
    { "enabled", [](const InspectorComposedElement& inspector) { return inspector.GetEnabled(); } },
    { "clip", [](const InspectorComposedElement& inspector) { return inspector.GetClip(); } }
};

const std::unordered_map<std::string, IntJsonFunc> CREATE_JSON_INT_MAP {
    { "zIndex", [](const InspectorComposedElement& inspector) { return inspector.GetZIndex(); } },
    { "gridSpan", [](const InspectorComposedElement& inspector) { return inspector.GetGridSpan(); } },
    { "layoutPriority", [](const InspectorComposedElement& inspector) { return inspector.GetLayoutPriority(); } },
    { "layoutWeight", [](const InspectorComposedElement& inspector) { return inspector.GetLayoutWeight(); } },
    { "displayPriority", [](const InspectorComposedElement& inspector) { return inspector.GetDisplayPriority(); } },
};

const std::unordered_map<std::string, JsonValueJsonFunc> CREATE_JSON_JSON_VALUE_MAP {
    { "windowBlur", [](const InspectorComposedElement& inspector) { return inspector.GetWindowBlur(); } },
    { "shadow", [](const InspectorComposedElement& inspector) { return inspector.GetShadow(); } },
    { "position", [](const InspectorComposedElement& inspector) { return inspector.GetPosition(); } },
    { "offset", [](const InspectorComposedElement& inspector) { return inspector.GetOffset(); } },
    { "padding", [](const InspectorComposedElement& inspector) { return inspector.GetPadding(); } },
    { "margin", [](const InspectorComposedElement& inspector) { return inspector.GetAllMargin(); } },
    { "backgroundImageSize",
        [](const InspectorComposedElement& inspector) { return inspector.GetBackgroundImageSize(); } },
    { "backgroundImagePosition",
        [](const InspectorComposedElement& inspector) { return inspector.GetBackgroundImagePosition(); } },
    { "useSizeType", [](const InspectorComposedElement& inspector) { return inspector.GetUseSizeType(); } },
    { "rotate", [](const InspectorComposedElement& inspector) { return inspector.GetRotate(); } },
    { "scale", [](const InspectorComposedElement& inspector) { return inspector.GetScale(); } },
    { "transform", [](const InspectorComposedElement& inspector) { return inspector.GetTransform(); } },
    { "translate", [](const InspectorComposedElement& inspector) { return inspector.GetTranslate(); } },
    { "markAnchor", [](const InspectorComposedElement& inspector) { return inspector.GetMarkAnchor(); } },
    { "mask", [](const InspectorComposedElement& inspector) { return inspector.GetMask(); } },
    { "useAlign", [](const InspectorComposedElement& inspector) { return inspector.GetUseAlign(); } },
    { "overlay", [](const InspectorComposedElement& inspector) { return inspector.GetOverlay(); } },
};

}; // namespace

InspectorComposedElement::~InspectorComposedElement()
{
    RemoveInspectorNode(id_);
}

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

void InspectorComposedElement::Update()
{
    const RefPtr<ComposedComponent> compose = AceType::DynamicCast<ComposedComponent>(component_);
    if (compose != nullptr) {
        name_ = compose->GetName();
        if (id_ != compose->GetId()) {
            auto context = context_.Upgrade();
            if (addedToMap_ && context != nullptr) {
                context->RemoveComposedElement(id_, AceType::Claim(this));
                context->AddComposedElement(compose->GetId(), AceType::Claim(this));
                UpdateComposedComponentId(id_, compose->GetId());
            }
            id_ = compose->GetId();
        }
        compose->ClearNeedUpdate();
    }
}

bool InspectorComposedElement::CanUpdate(const RefPtr<Component>& newComponent)
{
    return Element::CanUpdate(newComponent);
}

void InspectorComposedElement::UpdateComposedComponentId(const ComposeId& oldId, const ComposeId& newId)
{
    auto context = context_.Upgrade();
    if (context == nullptr) {
        LOGW("get context failed");
        return;
    }
    auto accessibilityManager = context->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGW("get AccessibilityManager failed");
        return;
    }
    RemoveInspectorNode(oldId);
    accessibilityManager->AddComposedElement(newId, AceType::Claim(this));
    LOGD("Update ComposedComponent Id %{public}s to %{public}s", oldId.c_str(), newId.c_str());
}

void InspectorComposedElement::RemoveInspectorNode(const ComposeId& id)
{
    auto context = context_.Upgrade();
    if (context == nullptr) {
        LOGW("get context failed");
        return;
    }
    auto accessibilityManager = context->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGW("get AccessibilityManager failed");
        return;
    }
    accessibilityManager->RemoveComposedElementById(id);
    accessibilityManager->RemoveAccessibilityNodeById(StringUtils::StringToInt(id));
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

std::string InspectorComposedElement::GetWidth() const
{
    auto render = GetRenderBox();
    if (render) {
        Dimension value = render->GetWidthDimension();
        if (value.Value() == -1) {
            return "-";
        }
        return render->GetWidthDimension().ToString();
    }
    return "-";
}

std::string InspectorComposedElement::GetHeight() const
{
    auto render = GetRenderBox();
    if (render) {
        Dimension value = render->GetHeightDimension();
        if (value.Value() == -1) {
            return "-";
        }
        return render->GetHeightDimension().ToString();
    }
    return "-";
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetPadding() const
{
    auto render = GetRenderBox();
    auto jsonValue = JsonUtil::Create(false);
    if (render) {
        auto top = render->GetPadding(DimensionHelper(&Edge::SetTop, &Edge::Top));
        auto right = render->GetPadding(DimensionHelper(&Edge::SetRight, &Edge::Right));
        auto bottom = render->GetPadding(DimensionHelper(&Edge::SetBottom, &Edge::Bottom));
        auto left = render->GetPadding(DimensionHelper(&Edge::SetLeft, &Edge::Left));
        if (top == right && right == bottom && bottom == left) {
            auto temp = JsonUtil::Create(false);
            temp->Put("padding", top.ToString().c_str());
            jsonValue = temp->GetValue("padding");
        } else {
            jsonValue->Put("top", top.ToString().c_str());
            jsonValue->Put("right", right.ToString().c_str());
            jsonValue->Put("bottom", bottom.ToString().c_str());
            jsonValue->Put("left", left.ToString().c_str());
        }
        return jsonValue;
    }
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetAllMargin() const
{
    auto render = GetRenderBox();
    auto jsonValue = JsonUtil::Create(false);
    if (render) {
        auto top = render->GetMargin(DimensionHelper(&Edge::SetTop, &Edge::Top));
        auto right = render->GetMargin(DimensionHelper(&Edge::SetRight, &Edge::Right));
        auto bottom = render->GetMargin(DimensionHelper(&Edge::SetBottom, &Edge::Bottom));
        auto left = render->GetMargin(DimensionHelper(&Edge::SetLeft, &Edge::Left));
        if (top == right && right == bottom && bottom == left) {
            auto temp = JsonUtil::Create(false);
            temp->Put("margin", top.ToString().c_str());
            jsonValue = temp->GetValue("margin");
        } else {
            jsonValue->Put("top", top.ToString().c_str());
            jsonValue->Put("right", right.ToString().c_str());
            jsonValue->Put("bottom", bottom.ToString().c_str());
            jsonValue->Put("left", left.ToString().c_str());
        }
        return jsonValue;
    }
    return jsonValue;
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
    auto jsonStr = JsonUtil::Create(false);
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
    auto node = GetInspectorNode(FlexItemElement::TypeId());
    if (!node) {
        return 0;
    }
    auto render = AceType::DynamicCast<RenderFlexItem>(node);
    if (render) {
        return render->GetFlexWeight();
    }
    return 0;
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

std::string InspectorComposedElement::GetDirectionStr() const
{
    auto render = GetRenderBox();
    if (!render) {
        return TEXT_DIRECTION[3];
    }
    auto value = static_cast<int32_t>(render->GetInspectorDirection());
    auto length = static_cast<int32_t>(sizeof(TEXT_DIRECTION) / sizeof(TEXT_DIRECTION[0]));
    if (value < length) {
        return TEXT_DIRECTION[value];
    }
    return TEXT_DIRECTION[3];
}

TextDirection InspectorComposedElement::GetDirection() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetTextDirection();
    }
    return TextDirection::AUTO;
}

std::string InspectorComposedElement::GetBorderRadius() const
{
    auto value = GetBorder().TopLeftRadius().GetX().Value();
    if (value == 0.0) {
        return "0.0vp";
    }
    return  GetBorder().TopLeftRadius().GetX().ToString();
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetPosition() const
{
    auto jsonValue = JsonUtil::Create(false);
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

std::unique_ptr<JsonValue> InspectorComposedElement::GetMarkAnchor() const
{
    auto jsonValue = JsonUtil::Create(false);
    auto node = GetInspectorNode(FlexItemElement::TypeId());
    if (!node) {
        jsonValue->Put("x", "0.0px");
        jsonValue->Put("y", "0.0px");
        return jsonValue;
    }
    auto render = AceType::DynamicCast<RenderFlexItem>(node);
    if (render) {
        jsonValue->Put("x", render->GetAnchorX().ToString().c_str());
        jsonValue->Put("y", render->GetAnchorY().ToString().c_str());
        return jsonValue;
    }
    jsonValue->Put("x", "0.0px");
    jsonValue->Put("y", "0.0px");
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetOffset() const
{
    auto jsonValue = JsonUtil::Create(false);
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
    strRec = std::to_string(rect.Left())
                 .append(",")
                 .append(std::to_string(rect.Top()))
                 .append(",")
                 .append(std::to_string(rect.Width()))
                 .append(",")
                 .append(std::to_string(rect.Height()));
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

std::string InspectorComposedElement::GetFlexBasis() const
{
    auto render = AceType::DynamicCast<RenderFlexItem>(GetInspectorNode(FlexItemElement::TypeId()));
    if (render) {
        auto flexBasis = render->GetFlexBasis();
        return flexBasis.IsValid() ? render->GetFlexBasis().ToString() : "auto";
    }
    return "auto";
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

std::string InspectorComposedElement::GetBorderColor() const
{
    auto border = GetBorder();
    return border.Left().GetColor().ColorToString();
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

std::string InspectorComposedElement::GetBackgroundColor() const
{
    auto backDecoration = GetBackDecoration();
    if (!backDecoration) {
        return "NONE";
    }
    auto color = backDecoration->GetBackgroundColor();
    LOGE("backgroundColor:%{public}s", color.ColorToString().c_str());
    return color.ColorToString();
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetBackgroundImageSize() const
{
    auto jsonValue = JsonUtil::Create(false);
    auto backDecoration = GetBackDecoration();
    if (!backDecoration) {
        jsonValue->Put("width", "ImageSize.Auto");
        return jsonValue->GetValue("width");
    }
    auto image = backDecoration->GetImage();
    if (!image) {
        jsonValue->Put("width", "ImageSize.Auto");
        return jsonValue->GetValue("width");
    }
    auto widthType = image->GetImageSize().GetSizeTypeX();
    if (widthType == BackgroundImageSizeType::CONTAIN) {
        jsonValue->Put("width", "ImageSize.Contain");
        return jsonValue->GetValue("width");
    } else if (widthType == BackgroundImageSizeType::COVER) {
        jsonValue->Put("width", "ImageSize.Cover");
        return jsonValue->GetValue("width");
    } else if (widthType == BackgroundImageSizeType::AUTO) {
        jsonValue->Put("width", "ImageSize.Auto");
        return jsonValue->GetValue("width");
    }

    auto width = image->GetImageSize().GetSizeValueX();
    auto height = image->GetImageSize().GetSizeValueY();
    jsonValue->Put("width", width);
    jsonValue->Put("height", height);
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetBackgroundImagePosition() const
{
    auto jsonValue = JsonUtil::Create(false);
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
    if (image->GetImagePosition().GetSizeTypeX() == BackgroundImagePositionType::PX) {
        auto width = image->GetImagePosition().GetSizeValueX();
        auto height = image->GetImagePosition().GetSizeValueY();
        jsonValue->Put("x", width);
        jsonValue->Put("y", height);
        return jsonValue;
    } else {
        auto width = image->GetImagePosition().GetSizeValueX();
        auto height = image->GetImagePosition().GetSizeValueY();
        return GetAlignmentType(width, height);
    }
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetAlignmentType(double width, double height) const
{
    auto jsonValue = JsonUtil::Create(false);
    if (width == 0) {
        if (height == 0) {
            jsonValue->Put("x", "Alignment.TopStart");
            return jsonValue->GetValue("x");
        } else if (height == 50) {
            jsonValue->Put("x", "Alignment.Start");
            return jsonValue->GetValue("x");
        } else {
            jsonValue->Put("x", "Alignment.BottomStart");
            return jsonValue->GetValue("x");
        }
    } else if (width == 50) {
        if (height == 0) {
            jsonValue->Put("x", "Alignment.Top");
            return jsonValue->GetValue("x");
        } else if (height == 50) {
            jsonValue->Put("x", "Alignment.Center");
            return jsonValue->GetValue("x");
        } else {
            jsonValue->Put("x", "Alignment.Bottom");
            return jsonValue->GetValue("x");
        }
    } else {
        if (height == 0) {
            jsonValue->Put("x", "Alignment.TopEnd");
            return jsonValue->GetValue("x");
        } else if (height == 50) {
            jsonValue->Put("x", "Alignment.End");
            return jsonValue->GetValue("x");
        } else {
            jsonValue->Put("x", "Alignment.BottomEnd");
            return jsonValue->GetValue("x");
        }
    }
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

bool InspectorComposedElement::GetClip() const
{
    auto render = GetRenderBox();
    if (!render) {
        return false;
    }
    auto clipPath = render->GetClipPath();
    if (clipPath && clipPath->GetBasicShape()) {
        int32_t shapeType = static_cast<int32_t>(clipPath->GetBasicShape()->GetBasicShapeType());
        int32_t size = static_cast<int32_t>(sizeof(BASIC_SHAPE_TYPE) / sizeof(BASIC_SHAPE_TYPE[0]));
        if (shapeType < size) {
            return BASIC_SHAPE_TYPE[shapeType];
        }
    } else {
        return render->GetBoxClipFlag();
    }
    return false;
}

bool InspectorComposedElement::GetEnabled() const
{
    auto node = GetInspectorNode(GetTargetTypeId());
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

std::unique_ptr<JsonValue> InspectorComposedElement::GetRotate() const
{
    auto render = AceType::DynamicCast<RenderTransform>(GetInspectorNode(TransformElement::TypeId()));
    auto jsonValue = JsonUtil::Create(false);
    if (!render) {
        return jsonValue;
    }
    for (const auto& operation : render->GetTransformEffects().GetOperations()) {
        if (operation.type_ == TransformOperationType::ROTATE) {
            const auto& rotate = operation.rotateOperation_;
            jsonValue->Put("x", std::to_string(rotate.dx).c_str());
            jsonValue->Put("y", std::to_string(rotate.dy).c_str());
            jsonValue->Put("z", std::to_string(rotate.dz).c_str());
            jsonValue->Put("angle", std::to_string(rotate.angle).c_str());
            jsonValue->Put("centerX", render->GetOriginX().ToString().c_str());
            jsonValue->Put("centerY", render->GetOriginY().ToString().c_str());
            break;
        }
    }
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetScale() const
{
    auto render = AceType::DynamicCast<RenderTransform>(GetInspectorNode(TransformElement::TypeId()));
    auto jsonValue = JsonUtil::Create(false);
    if (!render) {
        return jsonValue;
    }
    for (const auto& operation : render->GetTransformEffects().GetOperations()) {
        if (operation.type_ == TransformOperationType::SCALE) {
            const auto& scale = operation.scaleOperation_;
            jsonValue->Put("x", std::to_string(scale.scaleX).c_str());
            jsonValue->Put("y", std::to_string(scale.scaleY).c_str());
            jsonValue->Put("z", std::to_string(scale.scaleZ).c_str());
            jsonValue->Put("centerX", render->GetOriginX().ToString().c_str());
            jsonValue->Put("centerY", render->GetOriginY().ToString().c_str());
            break;
        }
    }
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetTransform() const
{
    auto render = AceType::DynamicCast<RenderTransform>(GetInspectorNode(TransformElement::TypeId()));
    auto jsonValue = JsonUtil::Create(false);
    if (!render) {
        return jsonValue;
    }
    for (const auto& operation : render->GetTransformEffects().GetOperations()) {
        if (operation.type_ == TransformOperationType::MATRIX) {
            const auto& matrix = operation.matrix4_;
            jsonValue->Put("type", "matrix");
            jsonValue->Put("matrix", matrix.ToString().c_str());
            break;
        }
    }
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetTranslate() const
{
    auto render = AceType::DynamicCast<RenderTransform>(GetInspectorNode(TransformElement::TypeId()));
    auto jsonValue = JsonUtil::Create(false);
    if (!render) {
        return jsonValue;
    }
    for (const auto& operation : render->GetTransformEffects().GetOperations()) {
        if (operation.type_ == TransformOperationType::TRANSLATE) {
            const auto& translate = operation.translateOperation_;
            jsonValue->Put("x", translate.dx.ToString().c_str());
            jsonValue->Put("y", translate.dy.ToString().c_str());
            jsonValue->Put("z", translate.dz.ToString().c_str());
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

double InspectorComposedElement::GetBrightness() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetBrightness();
    }
    return 1.0;
}

double InspectorComposedElement::GetSaturate() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetSaturate();
    }
    return 1.0;
}

double InspectorComposedElement::GetContrast() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetContrast();
    }
    return 1.0;
}

double InspectorComposedElement::GetInvert() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetInvert();
    }
    return 0.0;
}

double InspectorComposedElement::GetSepia() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetSepia();
    }
    return 0.0;
}

double InspectorComposedElement::GetGrayScale() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetGrayScale();
    }
    return 0.0;
}

double InspectorComposedElement::GetHueRotate() const
{
    auto render = GetRenderBox();
    if (render) {
        return render->GetHueRotate();
    }
    return 0.0;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetWindowBlur() const
{
    auto render = AceType::DynamicCast<RenderBox>(GetInspectorNode(BoxElement::TypeId()));
    auto jsonValue = JsonUtil::Create(false);
    if (!render) {
        return jsonValue;
    }
    jsonValue->Put("percent", std::to_string(render->GetWindowBlurProgress()).c_str());
    jsonValue->Put(
        "style", WINDOW_BLUR_STYLE[static_cast<int32_t>(render->GetWindowBlurStyle()) - WINDOW_BLUR_STYLE_ENUM_OFFSET]);
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetShadow() const
{
    auto render = AceType::DynamicCast<RenderBox>(GetInspectorNode(BoxElement::TypeId()));
    auto jsonValue = JsonUtil::Create(false);
    if (!render) {
        return jsonValue;
    }
    Shadow shadow = render->GetShadow();
    jsonValue->Put("radius", std::to_string(shadow.GetBlurRadius()).c_str());
    jsonValue->Put("color", std::to_string(shadow.GetColor().GetValue()).c_str());
    jsonValue->Put("offsetX", std::to_string(shadow.GetOffset().GetX()).c_str());
    jsonValue->Put("offsetY", std::to_string(shadow.GetOffset().GetY()).c_str());
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetOverlay() const
{
    auto jsonValue = JsonUtil::Create(false);
    auto coverage =  GetContentRender<RenderCoverage>(ComponentGroupElement::TypeId());
    if (!coverage) {
        jsonValue->Put("options", "align: Alignment.Center,offset: {0, 0}");
        return jsonValue;
    }
    auto title = coverage->GetTextVal();
    auto alignment = coverage->GetAlignment();
    auto jsonAlign = JsonUtil::Create(false);
    if (alignment == Alignment::TOP_LEFT) {
            jsonAlign->Put("align", "Alignment.TopStart");
        } else if (alignment == Alignment::TOP_CENTER) {
            jsonAlign->Put("align", "Alignment.Top");
        } else if (alignment == Alignment::TOP_RIGHT) {
            jsonAlign->Put("align", "Alignment.TopEnd");
        } else if (alignment == Alignment::CENTER_LEFT) {
            jsonAlign->Put("align", "Alignment.Start");
        } else if (alignment == Alignment::CENTER_RIGHT) {
            jsonAlign->Put("align", "Alignment.End");
        } else if (alignment == Alignment::BOTTOM_LEFT) {
            jsonAlign->Put("align", "Alignment.BottomStart");
        } else if (alignment == Alignment::BOTTOM_CENTER) {
            jsonAlign->Put("align", "Alignment.Bottom");
        } else if (alignment == Alignment::BOTTOM_RIGHT) {
            jsonAlign->Put("align", "Alignment.BottomEnd");
        } else {
            jsonAlign->Put("align", "Alignment.Center");
        }
    auto offsetJson = JsonUtil::Create(false);
    offsetJson->Put("x", coverage->GetX().ToString().c_str());
    offsetJson->Put("y", coverage->GetY().ToString().c_str());
    jsonAlign->Put("offset", offsetJson);
    jsonValue->Put("title", title.c_str());
    jsonValue->Put("options", jsonAlign);
    return jsonValue;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetMask() const
{
    auto render = GetRenderBox();
    auto jsonValue = JsonUtil::Create(false);
    if (!render) {
        return jsonValue;
    }
    auto mask = render->GetMask();
    if (mask && mask->GetMaskPath() && mask->GetMaskPath()->GetBasicShape()) {
        auto shape = mask->GetMaskPath()->GetBasicShape();
        int32_t shapeType = static_cast<int32_t>(shape->GetBasicShapeType());
        int32_t size = static_cast<int32_t>(sizeof(BASIC_SHAPE_TYPE) / sizeof(BASIC_SHAPE_TYPE[0]));
        if (shapeType < size) {
            jsonValue->Put("shape", BASIC_SHAPE_TYPE[shapeType]);
        }
    }
    return jsonValue;
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
    return 1;
}

int32_t InspectorComposedElement::GetGridOffset() const
{
    auto columnInfo = GetGridColumnInfo();
    if (columnInfo) {
        if (columnInfo->GetOffset(GridSizeType::UNDEFINED) == -1) {
            return 0;
        }
        return columnInfo->GetOffset(GridSizeType::UNDEFINED);
    }
    return 0;
}

std::unique_ptr<JsonValue> InspectorComposedElement::GetUseSizeType() const
{
    auto columnInfo = GetGridColumnInfo();
    auto jsonRoot = JsonUtil::Create(false);
    if (!columnInfo) {
        return jsonRoot;
    }
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

std::unique_ptr<JsonValue> InspectorComposedElement::GetUseAlign() const
{
    auto render = GetRenderBox();
    auto jsonValue = JsonUtil::Create(false);
    if (!render) {
        return jsonValue;
    }
    jsonValue->Put("edge", ConvertSideToString(render->GetUseAlignSide()).c_str());
    jsonValue->Put("offset", render->GetUseAlignOffset().ToString().c_str());
    return jsonValue;
}
} // namespace OHOS::Ace::V2
