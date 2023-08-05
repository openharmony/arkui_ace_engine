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
void BorderStyleProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, std::unique_ptr<JsonValue>& borderJson) const
{
    static const char* BORDER_STYLE[] = {
        "BorderStyle.Solid",
        "BorderStyle.Dashed",
        "BorderStyle.Dotted",
        "BorderStyle.None",
    };
    if (multiValued) {
        auto res = JsonUtil::Create(true);
        res->Put("left", BORDER_STYLE[static_cast<int>(styleLeft.value_or(BorderStyle::SOLID))]);
        res->Put("top", BORDER_STYLE[static_cast<int>(styleTop.value_or(BorderStyle::SOLID))]);
        res->Put("right", BORDER_STYLE[static_cast<int>(styleRight.value_or(BorderStyle::SOLID))]);
        res->Put("bottom", BORDER_STYLE[static_cast<int>(styleBottom.value_or(BorderStyle::SOLID))]);

        json->Put("borderStyle", res);
        borderJson->Put("style", res);
    } else {
        json->Put("borderStyle", BORDER_STYLE[static_cast<int>(styleLeft.value_or(BorderStyle::SOLID))]);
        borderJson->Put("style", BORDER_STYLE[static_cast<int>(styleLeft.value_or(BorderStyle::SOLID))]);
    }
}

std::string BorderWidthPropertyT<Dimension>::ToString() const
{
    std::string str;
    str.append("leftDimen: [").append(leftDimen.has_value() ? leftDimen->ToString() : "NA").append("]");
    str.append("rightDimen: [").append(rightDimen.has_value() ? rightDimen->ToString() : "NA").append("]");
    str.append("topDimen: [").append(topDimen.has_value() ? topDimen->ToString() : "NA").append("]");
    str.append("bottomDimen: [").append(bottomDimen.has_value() ? bottomDimen->ToString() : "NA").append("]");
    return str;
}

void BorderWidthPropertyT<Dimension>::ToJsonValue(
    std::unique_ptr<JsonValue>& json, std::unique_ptr<JsonValue>& borderJson) const
{
    if (multiValued) {
        auto res = JsonUtil::Create(true);
        res->Put("left", leftDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("top", topDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("right", rightDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("bottom", bottomDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());

        borderJson->Put("width", res);
        json->Put("borderWidth", res);
    } else {
        auto left = leftDimen.value_or(Dimension(0.0, DimensionUnit::VP)).ToString();
        borderJson->Put("width", left.c_str());
        json->Put("borderWidth", left.c_str());
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

void BorderColorProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, std::unique_ptr<JsonValue>& borderJson) const
{
    if (multiValued) {
        auto res = JsonUtil::Create(true);
        res->Put("left", leftColor.value_or(Color()).ColorToString().c_str());
        res->Put("right", rightColor.value_or(Color()).ColorToString().c_str());
        res->Put("top", topColor.value_or(Color()).ColorToString().c_str());
        res->Put("bottom", bottomColor.value_or(Color()).ColorToString().c_str());

        borderJson->Put("color", res);
        json->Put("borderColor", res);
    } else {
        auto left = leftColor.value_or(Color()).ColorToString();
        borderJson->Put("color", left.c_str());
        json->Put("borderColor", left.c_str());
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

void BorderRadiusPropertyT<Dimension>::ToJsonValue(
    std::unique_ptr<JsonValue>& json, std::unique_ptr<JsonValue>& borderJson) const
{
    if (multiValued) {
        auto res = JsonUtil::Create(true);
        res->Put("topLeft", radiusTopLeft.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("topRight", radiusTopRight.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("bottomLeft", radiusBottomLeft.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
        res->Put("bottomRight", radiusBottomRight.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());

        json->Put("borderRadius", res);
        borderJson->Put("radius", res);
    } else {
        auto left = radiusTopLeft.value_or(Dimension(0.0, DimensionUnit::VP)).ToString();
        json->Put("borderRadius", left.c_str());
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
} // namespace OHOS::Ace::NG
