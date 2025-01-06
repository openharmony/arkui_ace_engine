/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_SELECTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_SELECTION_H

#include <list>

#include "base/geometry/offset.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/event/ace_events.h"
#include "core/event/axis_event.h"

namespace OHOS::Ace::NG {
struct SpanItem;
}
namespace OHOS::Ace {
namespace {
Color DEFAULT_SYMBOL_COLOR = Color::BLACK;
}
using FONT_FEATURES_LIST = std::list<std::pair<std::string, int32_t>>;
enum GetSpansMethod : int32_t {
    GETSPANS,
    ONSELECT,
};

enum RichEditorImageSize : int32_t {
    SIZEWIDTH,
    SIZEHEIGHT,
};

enum RichEditorSpanRange : int32_t {
    RANGESTART,
    RANGEEND,
};

enum SelectSpanType : int32_t {
    TYPESPAN,
    TYPEIMAGE,
    TYPESYMBOLSPAN,
    TYPEBUILDERSPAN,
};

enum RichEditorLeadingRange : int32_t {
    LEADING_START,
    LEADING_END,
};

struct SpanPosition {
    int32_t spanIndex = 0;
    int32_t spanRange[2] = { 0, 0 };
};

struct SymbolSpanStyle {
    double fontSize = 0.0;
    double lineHeight = 0.0;
    bool halfLeading = false;
    double letterSpacing = 0.0;
    double lineSpacing = 0.0;
    std::string symbolColor;
    FONT_FEATURES_LIST fontFeature;
    int32_t fontWeight = 0;
    int32_t renderingStrategy = 0;
    int32_t effectStrategy = 0;

    SymbolSpanStyle() {}
    SymbolSpanStyle(const TextStyle& style)
    {
        fontSize = style.GetFontSize().ConvertToVp();
        lineHeight = style.GetLineHeight().ConvertToPx();
        letterSpacing = style.GetLetterSpacing().ConvertToPx();
        lineSpacing = style.GetLineSpacing().ConvertToPx();

        for (const auto& color : style.GetSymbolColorList()) {
            symbolColor += color.ColorToString() + ",";
        }
        if (symbolColor.size() > 0) {
            symbolColor = symbolColor.substr(0, symbolColor.size() - 1);
        }
        symbolColor = symbolColor.empty() ? DEFAULT_SYMBOL_COLOR.ColorToString() : symbolColor;

        fontFeature = style.GetFontFeatures();
        fontWeight = static_cast<int32_t>(style.GetFontWeight());
        renderingStrategy = style.GetRenderStrategy();
        effectStrategy = style.GetEffectStrategy();
    }

    bool operator==(const SymbolSpanStyle& rhs) const
    {
        return fontSize == rhs.fontSize
            && lineHeight == rhs.lineHeight
            && letterSpacing == rhs.letterSpacing
            && lineSpacing == rhs.lineSpacing
            && symbolColor == rhs.symbolColor
            && fontFeature == rhs.fontFeature
            && fontFeature == rhs.fontFeature
            && fontWeight == rhs.fontWeight
            && renderingStrategy == rhs.renderingStrategy
            && effectStrategy == rhs.effectStrategy;
    }

    bool operator!=(const SymbolSpanStyle& rhs) const
    {
        return !operator==(rhs);
    }
};

struct TextStyleResult {
    std::string fontColor;
    double fontSize = 0.0;
    double lineHeight = 0.0;
    bool halfLeading = false;
    double letterSpacing = 0.0;
    double lineSpacing = 0.0;
    int32_t fontStyle = 0;
    int32_t fontWeight = 0;
    FONT_FEATURES_LIST fontFeature;
    std::string fontFamily;
    int32_t decorationType = 0;
    std::string decorationColor;
    int32_t decorationStyle = 0;
    int32_t textAlign = 0;
    int32_t wordBreak = static_cast<int32_t>(WordBreak::BREAK_WORD);
    int32_t lineBreakStrategy = static_cast<int32_t>(LineBreakStrategy::GREEDY);
    std::string leadingMarginSize[2] = { "0.00px", "0.00px" };
    std::vector<Shadow> textShadows;
    std::optional<TextBackgroundStyle> textBackgroundStyle;
};

struct ImageStyleResult {
    double size[2] = { 0.0, 0.0 };
    int32_t verticalAlign = 0;
    int32_t objectFit = 0;
    std::string borderRadius;
    std::string margin;
};

struct ResultObject {
    SpanPosition spanPosition;
    SelectSpanType type = SelectSpanType::TYPESPAN;
    int32_t offsetInSpan[2] = { 0, 0 };
    std::u16string valueString;
    std::u16string previewText;
    RefPtr<PixelMap> valuePixelMap;
    TextStyleResult textStyle;
    ImageStyleResult imageStyle;
    SymbolSpanStyle symbolSpanStyle;
    RefPtr<ResourceObject> valueResource;
    WeakPtr<NG::SpanItem> span;
    bool isDraggable = true;
    bool isInit = false;
};

struct Selection {
    int32_t selection[2] = { 0, 0 };
    std::list<ResultObject> resultObjects;
};

class SelectionInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(SelectionInfo, BaseEventInfo);

public:
    SelectionInfo() : BaseEventInfo("SelectionInfo") {}

    ~SelectionInfo() = default;

    Selection GetSelection() const
    {
        return selection_;
    }

    Selection& GetSelectionRef()
    {
        return selection_;
    }

    void SetSelectionStart(int32_t start)
    {
        selection_.selection[RichEditorSpanRange::RANGESTART] = start;
    }

    void SetSelectionEnd(int32_t end)
    {
        selection_.selection[RichEditorSpanRange::RANGEEND] = end;
    }

    void SetResultObjectList(const std::list<ResultObject>& resultObjectList)
    {
        for (auto& resultObject : resultObjectList) {
            selection_.resultObjects.emplace_back(resultObject);
        }
    }

private:
    Selection selection_;
};

class SelectionRangeInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(SelectionRangeInfo, BaseEventInfo);

public:
    SelectionRangeInfo(int32_t start, int32_t end) : BaseEventInfo("SelectionRangeInfo"), start_(start), end_(end) {};

    ~SelectionRangeInfo() = default;

    int32_t start_;

    int32_t end_;

    void reset()
    {
        start_ = -1;
        end_ = -1;
    }

    bool operator==(const SelectionRangeInfo& rhs) const
    {
        return start_ == rhs.start_ && end_ == rhs.end_;
    }
};

struct ParagraphInfo {
    // style
    RefPtr<PixelMap> leadingMarginPixmap;
    std::string leadingMarginSize[2] = { "0.00px", "0.00px" };
    int32_t textAlign = 0;
    int32_t wordBreak = static_cast<int32_t>(WordBreak::BREAK_WORD);
    int32_t lineBreakStrategy = static_cast<int32_t>(LineBreakStrategy::GREEDY);

    std::pair<int32_t, int32_t> range;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_SELECTION_H
