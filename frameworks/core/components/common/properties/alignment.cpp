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

#include "core/components/common/properties/alignment.h"

namespace OHOS::Ace {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
}

const Alignment Alignment::TOP_LEFT = Alignment(-1.0, -1.0);
const Alignment Alignment::TOP_CENTER = Alignment(0.0, -1.0);
const Alignment Alignment::TOP_RIGHT = Alignment(1.0, -1.0);
const Alignment Alignment::CENTER_LEFT = Alignment(-1.0, 0.0);
const Alignment Alignment::CENTER = Alignment(0.0, 0.0);
const Alignment Alignment::CENTER_RIGHT = Alignment(1.0, 0.0);
const Alignment Alignment::BOTTOM_LEFT = Alignment(-1.0, 1.0);
const Alignment Alignment::BOTTOM_CENTER = Alignment(0.0, 1.0);
const Alignment Alignment::BOTTOM_RIGHT = Alignment(1.0, 1.0);

/*
 * This function is used to calculate the relative position of child rectangle in parent rectangle.
 * Note that parentSize should not be less than childSize,
 * which means neither width or height of parent rectangle should be less than child's.
 *
 * @param parentSize Size of parent in which you want to put a child.
 * @param childSize Size of child you want to put in parent.
 * @param alignment A variable by which to decide the position of a child in parent.
 * @return A relative position toward top-left point of parent.
 */
Offset Alignment::GetAlignPosition(const Size& parentSize, const Size& childSize, const Alignment& alignment)
{
    Offset offset;
    if (GreatOrEqual(parentSize.Width(), childSize.Width())) {
        offset.SetX((1.0 + alignment.GetHorizontal()) * (parentSize.Width() - childSize.Width()) / 2.0);
    }
    if (GreatOrEqual(parentSize.Height(), childSize.Height())) {
        offset.SetY((1.0 + alignment.GetVertical()) * (parentSize.Height() - childSize.Height()) / 2.0);
    }
    return offset;
}

NG::OffsetF Alignment::GetAlignPosition(
    const NG::SizeF& parentSize, const NG::SizeF& childSize, const Alignment& alignment)
{
    NG::OffsetF offset;
    if (GreatOrEqual(parentSize.Width(), childSize.Width())) {
        offset.SetX((1.0 + alignment.GetHorizontal()) * (parentSize.Width() - childSize.Width()) / 2.0);
    }
    if (GreatOrEqual(parentSize.Height(), childSize.Height())) {
        offset.SetY((1.0 + alignment.GetVertical()) * (parentSize.Height() - childSize.Height()) / 2.0);
    }
    return offset;
}

NG::OffsetF Alignment::GetAlignPositionWithDirection(const NG::SizeF& parentSize, const NG::SizeF& childSize,
    const Alignment& alignment, TextDirection direction)
{
    Alignment realAlignment = alignment;
    if (direction == TextDirection::RTL) {
        if (alignment == Alignment::TOP_LEFT) {
            realAlignment = Alignment::TOP_RIGHT;
        } else if (alignment == Alignment::TOP_CENTER) {
            realAlignment = Alignment::TOP_CENTER;
        } else if (alignment == Alignment::TOP_RIGHT) {
            realAlignment = Alignment::TOP_LEFT;
        } else if (alignment == Alignment::CENTER_LEFT) {
            realAlignment = Alignment::CENTER_RIGHT;
        } else if (alignment == Alignment::CENTER) {
            realAlignment = Alignment::CENTER;
        } else if (alignment == Alignment::CENTER_RIGHT) {
            realAlignment = Alignment::CENTER_LEFT;
        } else if (alignment == Alignment::BOTTOM_LEFT) {
            realAlignment = Alignment::BOTTOM_RIGHT;
        } else if (alignment == Alignment::BOTTOM_CENTER) {
            realAlignment = Alignment::BOTTOM_CENTER;
        } else if (alignment == Alignment::BOTTOM_RIGHT) {
            realAlignment = Alignment::BOTTOM_LEFT;
        }
    }
    return GetAlignPosition(parentSize, childSize, realAlignment);
}

std::string Alignment::GetAlignmentStr(TextDirection direction) const
{
    std::string result;
    Alignment alignment = Alignment(horizontal_, vertical_);
    if (alignment == TOP_LEFT) {
        result = direction == TextDirection::RTL ? "Alignment.TopEnd" : "Alignment.TopStart";
    } else if (alignment == TOP_CENTER) {
        result = "Alignment.Top";
    } else if (alignment == TOP_RIGHT) {
        result = direction == TextDirection::RTL ? "Alignment.TopStart" : "Alignment.TopEnd";
    } else if (alignment == CENTER_LEFT) {
        result = direction == TextDirection::RTL ? "Alignment.End" : "Alignment.Start";
    } else if (alignment == CENTER) {
        result = "Alignment.Center";
    } else if (alignment == CENTER_RIGHT) {
        result = direction == TextDirection::RTL ? "Alignment.Start" : "Alignment.End";
    } else if (alignment == BOTTOM_LEFT) {
        result = direction == TextDirection::RTL ? "Alignment.BottomEnd" : "Alignment.BottomStart";
    } else if (alignment == BOTTOM_CENTER) {
        result = "Alignment.Bottom";
    } else if (alignment == BOTTOM_RIGHT) {
        result = direction == TextDirection::RTL ? "Alignment.BottomStart" : "Alignment.BottomEnd";
    } else {
        result = "Alignment.Center";
    }
    return result;
}

Alignment Alignment::GetAlignment(TextDirection direction, const std::string& str)
{
    static const std::unordered_map<std::string, std::function<Alignment(TextDirection)>> uMap {
        { "Alignment.Top", [](TextDirection direction) { return TOP_CENTER; } },
        { "Alignment.TopStart",
            [](TextDirection direction) { return direction == TextDirection::LTR ? TOP_LEFT : TOP_RIGHT; } },
        { "Alignment.TopEnd",
            [](TextDirection direction) { return direction == TextDirection::LTR ? TOP_RIGHT : TOP_LEFT; } },
        { "Alignment.Center", [](TextDirection direction) { return CENTER; } },
        { "Alignment.Start",
            [](TextDirection direction) { return direction == TextDirection::LTR ? CENTER_LEFT : CENTER_RIGHT; } },
        { "Alignment.End",
            [](TextDirection direction) { return direction == TextDirection::LTR ? CENTER_RIGHT : CENTER_LEFT; } },
        { "Alignment.Bottom", [](TextDirection direction) { return BOTTOM_CENTER; } },
        { "Alignment.BottomStart",
            [](TextDirection direction) { return direction == TextDirection::LTR ? BOTTOM_LEFT : BOTTOM_RIGHT; } },
        { "Alignment.BottomEnd",
            [](TextDirection direction) { return direction == TextDirection::LTR ? BOTTOM_RIGHT : BOTTOM_LEFT; } },
    };

    return uMap.count(str) ? uMap.at(str)(direction) : CENTER;
}

std::optional<Alignment> Alignment::ParseAlignment(int32_t alignment)
{
    switch (alignment) {
        case NUM_0:
            return Alignment::TOP_LEFT;
        case NUM_1:
            return Alignment::TOP_CENTER;
        case NUM_2:
            return Alignment::TOP_RIGHT;
        case NUM_3:
            return Alignment::CENTER_LEFT;
        case NUM_4:
            return Alignment::CENTER;
        case NUM_5:
            return Alignment::CENTER_RIGHT;
        case NUM_6:
            return Alignment::BOTTOM_LEFT;
        case NUM_7:
            return Alignment::BOTTOM_CENTER;
        case NUM_8:
            return Alignment::BOTTOM_RIGHT;
        default:
            break;
    }
    return std::nullopt;
}
} // namespace OHOS::Ace
