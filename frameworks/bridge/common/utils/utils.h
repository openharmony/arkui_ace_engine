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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_UTILS_H

#include <climits>
#include <cmath>
#include <map>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include "base/geometry/axis.h"
#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/resource/asset_manager.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/animation/animation_pub.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/text_style.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace::Framework {

constexpr int32_t OFFSET_VALUE_NUMBER = 2;

template<class T>
bool GetAssetContentImpl(const RefPtr<AssetManager>& assetManager, const std::string& url, T& content)
{
    if (!assetManager) {
        LOGE("AssetManager is null");
        return false;
    }
    auto jsAsset = assetManager->GetAsset(url);
    if (jsAsset == nullptr) {
        LOGE("uri:%{private}s Asset is null", url.c_str());
        return false;
    }
    auto bufLen = jsAsset->GetSize();
    auto buffer = jsAsset->GetData();
    if ((buffer == nullptr) || (bufLen <= 0)) {
        LOGE("uri:%{private}s buffer is null", url.c_str());
        return false;
    }
    content.assign(buffer, buffer + bufLen);
    return true;
}

inline std::unique_ptr<JsonValue> ParseFileData(const std::string& data)
{
    const char* endMsg = nullptr;
    auto fileData = JsonUtil::ParseJsonString(data, &endMsg);
    if (!fileData) {
        LOGE("parse i18n data failed, error: %{private}s", endMsg);
        return nullptr;
    }
    return fileData;
}

inline double StringToDouble(const std::string& value)
{
    return StringUtils::StringToDouble(value);
}

inline Dimension StringToDimension(const std::string& value)
{
    return StringUtils::StringToDimension(value);
}

inline int32_t StringToInt(const std::string& value)
{
    return StringUtils::StringToInt(value);
}

inline bool StringToBool(const std::string& value)
{
    return value == "true";
}

inline BorderStyle ConvertStrToBorderStyle(const std::string& style)
{
    static const LinearMapNode<BorderStyle> borderStyleTable[] = {
        { "dashed", BorderStyle::DASHED },
        { "dotted", BorderStyle::DOTTED },
        { "solid", BorderStyle::SOLID },
    };

    auto index = BinarySearchFindIndex(borderStyleTable, ArraySize(borderStyleTable), style.c_str());
    return index < 0 ? BorderStyle::NONE : borderStyleTable[index].value;
}

inline BadgePosition ConvertStrToBadgePosition(const std::string& badgePosition)
{
    static const LinearMapNode<BadgePosition> badgePositionTable[] = {
        { "left", BadgePosition::LEFT },
        { "right", BadgePosition::RIGHT },
        { "rightTop", BadgePosition::RIGHT_TOP },
    };
    auto index = BinarySearchFindIndex(badgePositionTable, ArraySize(badgePositionTable), badgePosition.c_str());
    return index < 0 ? BadgePosition::RIGHT_TOP : badgePositionTable[index].value;
}

inline ImageRepeat ConvertStrToImageRepeat(const std::string& repeat)
{
    static const LinearMapNode<ImageRepeat> imageRepeatTable[] = {
        { "no-repeat", ImageRepeat::NOREPEAT },
        { "repeat", ImageRepeat::REPEAT },
        { "repeat-x", ImageRepeat::REPEATX },
        { "repeat-y", ImageRepeat::REPEATY },
    };

    auto index = BinarySearchFindIndex(imageRepeatTable, ArraySize(imageRepeatTable), repeat.c_str());
    return index < 0 ? ImageRepeat::NOREPEAT : imageRepeatTable[index].value;
}

inline FontWeight ConvertStrToFontWeight(const std::string& weight)
{
    return StringUtils::StringToFontWeight(weight);
}

inline TextDecoration ConvertStrToTextDecoration(const std::string& textDecoration)
{
    // this map should be sorted bu key.
    static const LinearMapNode<TextDecoration> textDecorationTable[] = {
        { DOM_TEXT_DECORATION_INHERIT, TextDecoration::INHERIT },
        { DOM_TEXT_DECORATION_LINETHROUGH, TextDecoration::LINE_THROUGH },
        { DOM_TEXT_DECORATION_NONE, TextDecoration::NONE },
        { DOM_TEXT_DECORATION_OVERLINE, TextDecoration::OVERLINE },
        { DOM_TEXT_DECORATION_UNDERLINE, TextDecoration::UNDERLINE },
    };

    auto index = BinarySearchFindIndex(textDecorationTable, ArraySize(textDecorationTable), textDecoration.c_str());
    return index < 0 ? TextDecoration::NONE : textDecorationTable[index].value;
}

inline FontStyle ConvertStrToFontStyle(const std::string& fontStyle)
{
    return fontStyle == DOM_TEXT_FONT_STYLE_ITALIC ? FontStyle::ITALIC : FontStyle::NORMAL;
}

inline TextAlign ConvertStrToTextAlign(const std::string& align)
{
    static const LinearMapNode<TextAlign> textAlignTable[] = {
        { DOM_CENTER, TextAlign::CENTER },
        { DOM_END, TextAlign::END },
        { DOM_LEFT, TextAlign::LEFT },
        { DOM_RIGHT, TextAlign::RIGHT },
        { DOM_START, TextAlign::START },
    };

    auto index = BinarySearchFindIndex(textAlignTable, ArraySize(textAlignTable), align.c_str());
    return index < 0 ? TextAlign::CENTER : textAlignTable[index].value;
}

inline TextOverflow ConvertStrToTextOverflow(const std::string& overflow)
{
    return overflow == DOM_ELLIPSIS ? TextOverflow::ELLIPSIS : TextOverflow::CLIP;
}

inline Overflow ConvertStrToOverflow(const std::string& val)
{
    const LinearMapNode<Overflow> overflowTable[] = {
        { "hidden", Overflow::CLIP },
        { "scroll", Overflow::SCROLL },
        { "visible", Overflow::OBSERVABLE },
    };
    auto index = BinarySearchFindIndex(overflowTable, ArraySize(overflowTable), val.c_str());
    return index < 0 ? Overflow::OBSERVABLE : overflowTable[index].value;
}

inline std::vector<std::string> ConvertStrToFontFamilies(const std::string& family)
{
    std::vector<std::string> fontFamilies;
    std::stringstream stream(family);
    std::string fontFamily;
    while (getline(stream, fontFamily, ',')) {
        fontFamilies.emplace_back(fontFamily);
    }
    return fontFamilies;
}

inline FlexDirection ConvertStrToFlexDirection(const std::string& flexKey)
{
    return flexKey == DOM_FLEX_COLUMN ? FlexDirection::COLUMN : FlexDirection::ROW;
}

inline FlexAlign ConvertStrToFlexAlign(const std::string& flexKey)
{
    static const LinearMapNode<FlexAlign> flexMap[] = {
        { DOM_ALIGN_ITEMS_BASELINE, FlexAlign::BASELINE },
        { DOM_JUSTIFY_CONTENT_CENTER, FlexAlign::CENTER },
        { DOM_JUSTIFY_CONTENT_END, FlexAlign::FLEX_END },
        { DOM_JUSTIFY_CONTENT_START, FlexAlign::FLEX_START },
        { DOM_JUSTIFY_CONTENT_AROUND, FlexAlign::SPACE_AROUND },
        { DOM_JUSTIFY_CONTENT_BETWEEN, FlexAlign::SPACE_BETWEEN },
        { DOM_JUSTIFY_CONTENT_EVENLY, FlexAlign::SPACE_EVENLY },
        { DOM_ALIGN_ITEMS_STRETCH, FlexAlign::STRETCH },
    };
    auto index = BinarySearchFindIndex(flexMap, ArraySize(flexMap), flexKey.c_str());
    return index < 0 ? FlexAlign::FLEX_START : flexMap[index].value;
}

inline Offset ConvertStrToOffset(const std::string& value)
{
    Offset offset;
    std::vector<std::string> offsetValues;
    std::stringstream stream(value);
    std::string offsetValue;
    while (getline(stream, offsetValue, ' ')) {
        offsetValues.emplace_back(offsetValue);
    }
    // To avoid illegal input, such as "100px ".
    offsetValues.resize(OFFSET_VALUE_NUMBER);
    offset.SetX(StringToDouble(offsetValues[0]));
    offset.SetY(StringToDouble(offsetValues[1]));
    return offset;
}

inline QrcodeType ConvertStrToQrcodeType(const std::string& value)
{
    return value == "circle" ? QrcodeType::CIRCLE : QrcodeType::RECT;
}

inline AnimationCurve ConvertStrToAnimationCurve(const std::string& value)
{
    return value == "standard" ? AnimationCurve::STANDARD : AnimationCurve::FRICTION;
}

RefPtr<Curve> CreateBuiltinCurve(const std::string& aniTimFunc);

RefPtr<Curve> CreateCustomCurve(const std::string& aniTimFunc);

ACE_EXPORT RefPtr<Curve> CreateCurve(const std::string& aniTimFunc);

inline FillMode StringToFillMode(const std::string& fillMode)
{
    if (fillMode == DOM_ANIMATION_FILL_MODE_FORWARDS) {
        return FillMode::FORWARDS;
    } else if (fillMode == DOM_ANIMATION_FILL_MODE_BACKWARDS) {
        return FillMode::BACKWARDS;
    } else if (fillMode == DOM_ANIMATION_FILL_MODE_BOTH) {
        return FillMode::BOTH;
    } else {
        return FillMode::NONE;
    }
}

inline AnimationDirection StringToAnimationDirection(const std::string& direction)
{
    if (direction == DOM_ANIMATION_DIRECTION_ALTERNATE) {
        return AnimationDirection::ALTERNATE;
    } else if (direction == DOM_ANIMATION_DIRECTION_REVERSE) {
        return AnimationDirection::REVERSE;
    } else if (direction == DOM_ANIMATION_DIRECTION_ALTERNATE_REVERSE) {
        return AnimationDirection::ALTERNATE_REVERSE;
    } else {
        return AnimationDirection::NORMAL;
    }
}

inline void RemoveHeadTailSpace(std::string& value)
{
    if (!value.empty()) {
        auto start = value.find_first_not_of(' ');
        if (start == std::string::npos) {
            value.clear();
        } else {
            value = value.substr(start, value.find_last_not_of(' ') - start + 1);
        }
    }
}

inline GradientDirection StrToGradientDirection(const std::string& direction)
{
    static const LinearMapNode<GradientDirection> gradientDirectionTable[] = {
        { DOM_GRADIENT_DIRECTION_LEFT, GradientDirection::LEFT },
        { DOM_GRADIENT_DIRECTION_RIGHT, GradientDirection::RIGHT },
        { DOM_GRADIENT_DIRECTION_TOP, GradientDirection::TOP },
    };

    auto index = BinarySearchFindIndex(gradientDirectionTable, ArraySize(gradientDirectionTable), direction.c_str());
    return index < 0 ? GradientDirection::BOTTOM : gradientDirectionTable[index].value;
}

GradientDirection StrToGradientDirectionCorner(const std::string& horizontal, const std::string& vertical);

bool ParseBackgroundImagePosition(const std::string& value, BackgroundImagePosition& backgroundImagePosition);

inline bool StartWith(const std::string& dst, const std::string& prefix)
{
    return dst.compare(0, prefix.size(), prefix) == 0;
}

inline bool EndWith(const std::string& dst, const std::string& suffix)
{
    return dst.size() >= suffix.size() && dst.compare(dst.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline double ConvertTimeStr(const std::string& str)
{
    std::string time(str);
    StringUtils::TrimStr(time);
    double result = 0.0;
    if (EndWith(time, "ms")) {
        result = StringToDouble(std::string(time.begin(), time.end() - 2.0));
    } else if (EndWith(time, "s")) {
        result = StringToDouble(std::string(time.begin(), time.end() - 1.0)) * 1000.0;
    } else if (EndWith(time, "m")) {
        result = StringToDouble(std::string(time.begin(), time.end() - 1.0)) * 60.0 * 1000.0;
    } else {
        result = StringToDouble(str);
    }
    return result;
}

inline WordBreak ConvertStrToWordBreak(const std::string& wordBreak)
{
    return StringUtils::StringToWordBreak(wordBreak);
}

inline bool CheckTransformEnum(const std::string& str)
{
    const static std::unordered_set<std::string> offsetKeywords = { "left", "right", "center", "top", "bottom" };

    return offsetKeywords.find(str) != offsetKeywords.end();
}

inline std::pair<bool, Dimension> ConvertStrToTransformOrigin(const std::string& str, Axis axis)
{
    const static std::unordered_map<std::string, Dimension> xOffsetKeywords = {
        { "left", 0.0_pct },
        { "right", 1.0_pct },
        { "center", 0.5_pct },
    };
    const static std::unordered_map<std::string, Dimension> yOffsetKeywords = {
        { "top", 0.0_pct },
        { "bottom", 1.0_pct },
        { "center", 0.5_pct },
    };

    if (axis == Axis::HORIZONTAL) {
        auto pos = xOffsetKeywords.find(str);
        if (pos != xOffsetKeywords.end()) {
            return std::make_pair(true, pos->second);
        }
    } else if (axis == Axis::VERTICAL) {
        auto pos = yOffsetKeywords.find(str);
        if (pos != yOffsetKeywords.end()) {
            return std::make_pair(true, pos->second);
        }
    }

    return std::make_pair(false, Dimension {});
}

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_UTILS_UTILS_H
