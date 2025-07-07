/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "border_property.h"

namespace OHOS::Ace::NG {
void BorderStyleProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, std::unique_ptr<JsonValue>& borderJson,
    const InspectorFilter& filter, bool isOutline) const
{
    static const char* BORDER_STYLE[] = {
        "BorderStyle.Solid",
        "BorderStyle.Dashed",
        "BorderStyle.Dotted",
        "BorderStyle.None",
    };
    static const char* OUTLINE_STYLE[] = {
        "OutlineStyle.SOLID",
        "OutlineStyle.DASHED",
        "OutlineStyle.DOTTED",
        "OutlineStyle.NONE",
    };
    const char** style = isOutline ? OUTLINE_STYLE : BORDER_STYLE;
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (multiValued) {
        auto res = JsonUtil::Create(true);
        res->Put("left", style[static_cast<int>(styleLeft.value_or(BorderStyle::SOLID))]);
        res->Put("top", style[static_cast<int>(styleTop.value_or(BorderStyle::SOLID))]);
        res->Put("right", style[static_cast<int>(styleRight.value_or(BorderStyle::SOLID))]);
        res->Put("bottom", style[static_cast<int>(styleBottom.value_or(BorderStyle::SOLID))]);
        json->PutExtAttr(isOutline ? "outlineStyle" : "borderStyle", res, filter);
        borderJson->Put("style", res);
    } else {
        json->PutExtAttr(isOutline ? "outlineStyle" : "borderStyle",
            style[static_cast<int>(styleLeft.value_or(BorderStyle::SOLID))], filter);
        borderJson->Put("style", style[static_cast<int>(styleLeft.value_or(BorderStyle::SOLID))]);
    }
}

std::string BorderWidthPropertyT<Dimension>::ToString() const
{
    std::string str;
    str.append("[").append(leftDimen.has_value() ? leftDimen->ToString() : "NA");
    str.append(",").append(rightDimen.has_value() ? rightDimen->ToString() : "NA");
    str.append(",").append(topDimen.has_value() ? topDimen->ToString() : "NA");
    str.append(",").append(bottomDimen.has_value() ? bottomDimen->ToString() : "NA").append("]");
    return str;
}

void BorderWidthPropertyT<Dimension>::ToJsonValue(std::unique_ptr<JsonValue>& json,
    std::unique_ptr<JsonValue>& borderJson, const InspectorFilter& filter, bool isOutline) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (multiValued) {
        auto res = JsonUtil::Create(true);
        res->Put("left", leftDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("top", topDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("start", startDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("end", endDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("right", rightDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("bottom", bottomDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());

        borderJson->Put("width", res);
        json->PutExtAttr(isOutline ? "outlineWidth" : "borderWidth", res, filter);
    } else {
        auto left = leftDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString();
        borderJson->Put("width", left.c_str());
        json->PutExtAttr(isOutline ? "outlineWidth" : "borderWidth", left.c_str(), filter);
    }
}

void BorderWidthPropertyT<Dimension>::ToDashJsonValue(std::unique_ptr<JsonValue>& json,
    std::unique_ptr<JsonValue>& borderJson, const InspectorFilter& filter, const std::string& keyValue) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (multiValued) {
        auto res = JsonUtil::Create(true);
        res->Put("left", leftDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("top", topDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("start", startDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("end", endDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("right", rightDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("bottom", bottomDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());

        borderJson->Put(keyValue.c_str(), res);
    } else {
        auto left = leftDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString();
        borderJson->Put(keyValue.c_str(), left.c_str());
    }
}

bool BorderWidthPropertyT<Dimension>::UpdateWithCheck(const BorderWidthPropertyT& value)
{
    bool isModified = false;
    if (value.leftDimen.has_value() && (leftDimen != value.leftDimen)) {
        leftDimen = value.leftDimen;
        isModified = true;
    }
    if (value.rightDimen.has_value() && (rightDimen != value.rightDimen)) {
        rightDimen = value.rightDimen;
        isModified = true;
    }
    if (value.topDimen.has_value() && (topDimen != value.topDimen)) {
        topDimen = value.topDimen;
        isModified = true;
    }
    if (value.bottomDimen.has_value() && (bottomDimen != value.bottomDimen)) {
        bottomDimen = value.bottomDimen;
        isModified = true;
    }
    return isModified;
}

void BorderColorProperty::ToJsonValue(std::unique_ptr<JsonValue>& json,
    std::unique_ptr<JsonValue>& borderJson, const InspectorFilter& filter, bool isOutline) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (multiValued) {
        auto res = JsonUtil::Create(true);
        res->Put("left", leftColor.value_or(Color()).ColorToString().c_str());
        res->Put("right", rightColor.value_or(Color()).ColorToString().c_str());
        res->Put("top", topColor.value_or(Color()).ColorToString().c_str());
        res->Put("bottom", bottomColor.value_or(Color()).ColorToString().c_str());

        borderJson->Put("color", res);
        json->PutExtAttr(isOutline ? "outlineColor" : "borderColor", res, filter);
    } else {
        auto left = leftColor.value_or(Color()).ColorToString();
        borderJson->Put("color", left.c_str());
        json->PutExtAttr(isOutline ? "outlineColor" : "borderColor", left.c_str(), filter);
    }
}

std::string BorderColorProperty::ToString() const
{
    std::string str;
    str.append("leftColor: [").append(leftColor.has_value() ? leftColor->ColorToString() : "NA").append("]");
    str.append("rightColor: [").append(rightColor.has_value() ? rightColor->ColorToString() : "NA").append("]");
    str.append("topColor: [").append(topColor.has_value() ? topColor->ColorToString() : "NA").append("]");
    str.append("bottomColor: [").append(bottomColor.has_value() ? bottomColor->ColorToString() : "NA").append("]");
    return str;
}

void BorderRadiusPropertyT<Dimension>::ToJsonValue(std::unique_ptr<JsonValue>& json,
    std::unique_ptr<JsonValue>& borderJson, const InspectorFilter& filter, bool isOutline) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (multiValued) {
        auto res = JsonUtil::Create(true);
        res->Put("topLeft", radiusTopLeft.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("topRight", radiusTopRight.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("bottomLeft", radiusBottomLeft.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("bottomRight", radiusBottomRight.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());

        json->PutExtAttr(isOutline ? "outlineRadius" : "borderRadius", res, filter);
        borderJson->Put("radius", res);
    } else {
        auto left = radiusTopLeft.value_or(Dimension(0.0, DimensionUnit::VP)).ToString();
        json->PutExtAttr(isOutline ? "outlineRadius" : "borderRadius", left.c_str(), filter);
        borderJson->Put("radius", left.c_str());
    }
}

bool BorderRadiusPropertyT<Dimension>::UpdateWithCheck(const BorderRadiusPropertyT<Dimension>& value)
{
    bool isModified = false;
    if (value.radiusTopLeft.has_value() && (radiusTopLeft != value.radiusTopLeft)) {
        radiusTopLeft = value.radiusTopLeft;
        isModified = true;
    }
    if (value.radiusTopRight.has_value() && (radiusTopRight != value.radiusTopRight)) {
        radiusTopRight = value.radiusTopRight;
        isModified = true;
    }
    if (value.radiusBottomLeft.has_value() && (radiusBottomLeft != value.radiusBottomLeft)) {
        radiusBottomLeft = value.radiusBottomLeft;
        isModified = true;
    }
    if (value.radiusBottomRight.has_value() && (radiusBottomRight != value.radiusBottomRight)) {
        radiusBottomRight = value.radiusBottomRight;
        isModified = true;
    }
    if (value.radiusTopStart.has_value() && (radiusTopStart != value.radiusTopStart)) {
        radiusTopStart = value.radiusTopStart;
        isModified = true;
    }
    if (value.radiusTopEnd.has_value() && (radiusTopEnd != value.radiusTopEnd)) {
        radiusTopEnd = value.radiusTopEnd;
        isModified = true;
    }
    if (value.radiusBottomEnd.has_value() && (radiusBottomEnd != value.radiusBottomEnd)) {
        radiusBottomEnd = value.radiusBottomEnd;
        isModified = true;
    }
    if (value.radiusBottomStart.has_value() && (radiusBottomStart != value.radiusBottomStart)) {
        radiusBottomStart = value.radiusBottomStart;
        isModified = true;
    }
    return isModified;
}

void BorderStyleProperty::SetBorderStyle(const BorderStyle& borderStyle)
{
    styleLeft = borderStyle;
    styleRight = borderStyle;
    styleTop = borderStyle;
    styleBottom = borderStyle;
}

bool BorderStyleProperty::operator==(const BorderStyleProperty& value) const
{
    return (styleLeft == value.styleLeft) && (styleRight == value.styleRight) && (styleTop == value.styleTop) &&
           (styleBottom == value.styleBottom);
}

void BorderWidthPropertyT<Dimension>::SetBorderWidth(const Dimension& borderWidth)
{
    leftDimen = borderWidth;
    rightDimen = borderWidth;
    topDimen = borderWidth;
    bottomDimen = borderWidth;
}

bool BorderWidthPropertyT<Dimension>::operator==(const BorderWidthPropertyT& value) const
{
    return (leftDimen == value.leftDimen) && (rightDimen == value.rightDimen) && (topDimen == value.topDimen) &&
           (bottomDimen == value.bottomDimen);
}

void BorderRadiusPropertyT<Dimension>::SetRadius(const Dimension& borderRadius)
{
    radiusTopLeft = borderRadius;
    radiusTopRight = borderRadius;
    radiusBottomLeft = borderRadius;
    radiusBottomRight = borderRadius;
}

bool BorderRadiusPropertyT<Dimension>::operator==(const BorderRadiusPropertyT<Dimension>& value) const
{
    return (radiusTopLeft == value.radiusTopLeft) && (radiusTopRight == value.radiusTopRight) &&
           (radiusBottomLeft == value.radiusBottomLeft) && (radiusBottomRight == value.radiusBottomRight);
}
bool BorderRadiusPropertyT<Dimension>::operator!=(const BorderRadiusPropertyT<Dimension>& value) const
{
    return !(*this == value);
}
} // namespace OHOS::Ace::NG
