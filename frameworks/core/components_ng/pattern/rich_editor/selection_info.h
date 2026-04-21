/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/event/ace_events.h"
#include "core/event/axis_event.h"
namespace OHOS::Ace::NG {
struct SpanItem;
}

namespace OHOS::Ace {
class ResourceObject;
class PixelMap;
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
    SymbolSpanStyle(const TextStyle& style);
    bool operator==(const SymbolSpanStyle& rhs) const;
    bool operator!=(const SymbolSpanStyle& rhs) const;
};

struct TextStyleResult {
    std::string fontColor;
    double fontSize = 0.0;
    double lineHeight = 0.0;
    bool halfLeading = false;
    double letterSpacing = 0.0;
    double lineSpacing = 0.0;
    bool optimizeTrailingSpace = false;
    std::optional<Dimension> paragraphSpacing;
    std::optional<int32_t> textVerticalAlign;
    std::optional<int32_t> textDirection;
    int32_t fontStyle = 0;
    int32_t fontWeight = 0;
    FONT_FEATURES_LIST fontFeature;
    std::string fontFamily;
    int32_t decorationType = 0;
    std::vector<TextDecoration> decorationTypes;
    std::string decorationColor;
    int32_t decorationStyle = 0;
    int32_t wordBreak = static_cast<int32_t>(WordBreak::BREAK_WORD);
    int32_t lineBreakStrategy = static_cast<int32_t>(LineBreakStrategy::GREEDY);
    int32_t textAlign = 0;
    std::string leadingMarginSize[2] = { "0.00px", "0.00px" };
    std::vector<Shadow> textShadows;
    std::optional<TextBackgroundStyle> textBackgroundStyle;
    float lineThicknessScale = 1.0f;
    bool orphanCharOptimization = false;
    bool compressLeadingPunctuation = false;
    double strokeWidth = 0.0;
    std::string strokeColor;
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
    std::u16string urlAddress;
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

class ACE_FORCE_EXPORT SelectionInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(SelectionInfo, BaseEventInfo);

public:
    SelectionInfo() : BaseEventInfo("SelectionInfo") {}

    ~SelectionInfo() = default;
    ACE_FORCE_EXPORT Selection GetSelection() const;
    Selection& GetSelectionRef();
    ACE_FORCE_EXPORT void SetSelectionStart(int32_t start);
    ACE_FORCE_EXPORT void SetSelectionEnd(int32_t end);
    ACE_FORCE_EXPORT void SetResultObjectList(const std::list<ResultObject>& resultObjectList);

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
    void reset();
    bool operator==(const SelectionRangeInfo& rhs) const;
};

struct ParagraphInfo {
    // style
    RefPtr<PixelMap> leadingMarginPixmap;
    std::string leadingMarginSize[2] = { "0.00px", "0.00px" };
    int32_t textAlign = 0;
    int32_t wordBreak = static_cast<int32_t>(WordBreak::BREAK_WORD);
    int32_t lineBreakStrategy = static_cast<int32_t>(LineBreakStrategy::GREEDY);
    // unit of paragraphSpacing is fp
    std::optional<double> paragraphSpacing;
    std::optional<int32_t> textVerticalAlign;
    std::optional<int32_t> textDirection;
    std::pair<int32_t, int32_t> range;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_SELECTION_H
