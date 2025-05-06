/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_SPAN_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_SPAN_NODE_H

#include <list>
#include <memory>
#include <optional>
#include <string>

#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "core/common/ai/data_detector_adapter.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/text/span/tlv_util.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/utils.h"
#include "core/components_ng/pattern/symbol/symbol_effect_options.h"
#include "core/components_ng/property/accessibility_property.h"

#define DEFINE_SPAN_FONT_STYLE_ITEM_GET(name, type)                          \
public:                                                                      \
    std::optional<type> Get##name() const                                    \
    {                                                                        \
        if (spanItem_->fontStyle) {                                          \
            return spanItem_->fontStyle->Get##name();                        \
        }                                                                    \
        return std::nullopt;                                                 \
    }                                                                        \
    bool Has##name() const                                                   \
    {                                                                        \
        if (spanItem_->fontStyle) {                                          \
            return spanItem_->fontStyle->Has##name();                        \
        }                                                                    \
        return false;                                                        \
    }                                                                        \
    type Get##name##Value(const type& defaultValue) const                    \
    {                                                                        \
        if (spanItem_->fontStyle) {                                          \
            return spanItem_->fontStyle->Get##name().value_or(defaultValue); \
        }                                                                    \
        return defaultValue;                                                 \
    }

#define DEFINE_SPAN_FONT_STYLE_ITEM(name, type, changeflag)       \
    DEFINE_SPAN_FONT_STYLE_ITEM_GET(name, type)                   \
public:                                                           \
    void Update##name(const type& value)                          \
    {                                                             \
        if (!spanItem_->fontStyle) {                              \
            spanItem_->fontStyle = std::make_unique<FontStyle>(); \
        }                                                         \
        if (spanItem_->fontStyle->Check##name(value)) {           \
            return;                                               \
        }                                                         \
        spanItem_->fontStyle->Update##name(value);                \
        if (changeflag == ChangeFlag::RE_CREATE) {                \
            spanItem_->MarkDirty();                               \
        } else {                                                  \
            spanItem_->MarkReLayoutParagraph();                   \
        }                                                         \
        RequestTextFlushDirty();                                  \
    }                                                             \
    void Reset##name()                                            \
    {                                                             \
        if (spanItem_->fontStyle) {                               \
            return spanItem_->fontStyle->Reset##name();           \
        }                                                         \
    }                                                             \
    void Update##name##WithoutFlushDirty(const type& value)       \
    {                                                             \
        if (!spanItem_->fontStyle) {                              \
            spanItem_->fontStyle = std::make_unique<FontStyle>(); \
        }                                                         \
        if (spanItem_->fontStyle->Check##name(value)) {           \
            return;                                               \
        }                                                         \
        spanItem_->fontStyle->Update##name(value);                \
    }

#define DEFINE_SPAN_FONT_STYLE_ITEM_RECREATE(name, type, changeflag) \
    DEFINE_SPAN_FONT_STYLE_ITEM_GET(name, type)                   \
public:                                                           \
    void Update##name(const type& value)                          \
    {                                                             \
        if (!spanItem_->fontStyle) {                              \
            spanItem_->fontStyle = std::make_unique<FontStyle>(); \
        }                                                         \
        if (spanItem_->fontStyle->Check##name(value)) {           \
            return;                                               \
        }                                                         \
        spanItem_->fontStyle->Update##name(value);                \
        if (changeflag == ChangeFlag::RE_CREATE) {                \
            spanItem_->MarkDirty();                               \
        } else {                                                  \
            spanItem_->MarkReLayoutParagraph();                   \
        }                                                         \
        RequestTextFlushDirty();                                  \
        spanItem_->MarkReCreateParagraph();                       \
    }                                                             \
    void Reset##name()                                            \
    {                                                             \
        if (spanItem_->fontStyle) {                               \
            spanItem_->fontStyle->Reset##name();                  \
        }                                                         \
        if (changeflag == ChangeFlag::RE_CREATE) {                \
            spanItem_->MarkDirty();                               \
        } else {                                                  \
            spanItem_->MarkReLayoutParagraph();                   \
        }                                                         \
        spanItem_->MarkReCreateParagraph();                       \
    }                                                             \
    void Update##name##WithoutFlushDirty(const type& value)       \
    {                                                             \
        if (!spanItem_->fontStyle) {                              \
            spanItem_->fontStyle = std::make_unique<FontStyle>(); \
        }                                                         \
        if (spanItem_->fontStyle->Check##name(value)) {           \
            return;                                               \
        }                                                         \
        spanItem_->fontStyle->Update##name(value);                \
        spanItem_->MarkReCreateParagraph();                       \
    }

#define DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(name, type, changeflag)                 \
public:                                                                          \
    std::optional<type> Get##name() const                                        \
    {                                                                            \
        if (spanItem_->textLineStyle) {                                          \
            return spanItem_->textLineStyle->Get##name();                        \
        }                                                                        \
        return std::nullopt;                                                     \
    }                                                                            \
    bool Has##name() const                                                       \
    {                                                                            \
        if (spanItem_->textLineStyle) {                                          \
            return spanItem_->textLineStyle->Has##name();                        \
        }                                                                        \
        return false;                                                            \
    }                                                                            \
    type Get##name##Value(const type& defaultValue) const                        \
    {                                                                            \
        if (spanItem_->textLineStyle) {                                          \
            return spanItem_->textLineStyle->Get##name().value_or(defaultValue); \
        }                                                                        \
        return defaultValue;                                                     \
    }                                                                            \
    void Update##name(const type& value)                                         \
    {                                                                            \
        if (!spanItem_->textLineStyle) {                                         \
            spanItem_->textLineStyle = std::make_unique<TextLineStyle>();        \
        }                                                                        \
        if (spanItem_->textLineStyle->Check##name(value)) {                      \
            return;                                                              \
        }                                                                        \
        spanItem_->textLineStyle->Update##name(value);                           \
        if (changeflag == ChangeFlag::RE_CREATE) {                               \
            spanItem_->MarkDirty();                                              \
        } else {                                                                 \
            spanItem_->MarkReLayoutParagraph();                                  \
        }                                                                        \
        RequestTextFlushDirty();                                                 \
    }                                                                            \
    void Reset##name()                                                           \
    {                                                                            \
        if (spanItem_->textLineStyle) {                                          \
            spanItem_->textLineStyle->Reset##name();                             \
        }                                                                        \
        if (changeflag == ChangeFlag::RE_CREATE) {                               \
            spanItem_->MarkDirty();                                              \
        } else {                                                                 \
            spanItem_->MarkReLayoutParagraph();                                  \
        }                                                                        \
    }                                                                            \
    void Update##name##WithoutFlushDirty(const type& value)                      \
    {                                                                            \
        if (!spanItem_->textLineStyle) {                                         \
            spanItem_->textLineStyle = std::make_unique<TextLineStyle>();        \
        }                                                                        \
        if (spanItem_->textLineStyle->Check##name(value)) {                      \
            return;                                                              \
        }                                                                        \
        spanItem_->textLineStyle->Update##name(value);                           \
    }

namespace OHOS::Ace::NG {
using FONT_FEATURES_LIST = std::list<std::pair<std::string, int32_t>>;
class InspectorFilter;
class Paragraph;

enum class SpanItemType { NORMAL = 0, IMAGE = 1, CustomSpan = 2, SYMBOL = 3, PLACEHOLDER = 4 };

struct PlaceholderStyle {
    double width = 0.0f;
    double height = 0.0f;
    double baselineOffset = 0.0f;
    VerticalAlign verticalAlign = VerticalAlign::BOTTOM;
    TextBaseline baseline = TextBaseline::ALPHABETIC;
};

struct CustomSpanPlaceholderInfo {
    int32_t customSpanIndex = -1;
    int32_t paragraphIndex = -1;
    std::function<void(NG::DrawingContext&, CustomSpanOptions)> onDraw;

    std::string ToString()
    {
        std::string result = "CustomPlaceholderInfo: [";
        result += "customSpanIndex: " + std::to_string(customSpanIndex);
        result += ", paragraphIndex: " + std::to_string(paragraphIndex);
        result += ", onDraw: ";
        result += !onDraw ? "nullptr" : "true";
        result += "]";
        return result;
    }
};

enum class ChangeFlag {
    RE_CREATE = 0,
    RE_LAYOUT = 1,
};

struct SpanItem : public AceType {
    DECLARE_ACE_TYPE(SpanItem, AceType);

public:
    SpanItem() = default;
    virtual ~SpanItem()
    {
        children.clear();
    }
    int32_t rangeStart = -1;
    int32_t position = -1;  // position of last char + 1
    int32_t nodeId_ = -1;
    int32_t paragraphIndex = -1;
    int32_t itemIndex_ = -1;
    uint32_t length = 0;
    std::string inspectId;
    std::string description;
    std::u16string content;
    uint32_t unicode = 0;
    SpanItemType spanItemType = SpanItemType::NORMAL;
    std::pair<int32_t, int32_t> interval;
    std::unique_ptr<FontStyle> fontStyle = std::make_unique<FontStyle>();
    std::unique_ptr<TextLineStyle> textLineStyle = std::make_unique<TextLineStyle>();
    // for text background style
    std::optional<TextBackgroundStyle> backgroundStyle;
    GestureEventFunc onClick;
    GestureEventFunc onLongPress;
    GestureEventFunc onDoubleClick;
    OnHoverFunc onHover;
    [[deprecated]] std::list<RefPtr<SpanItem>> children;
    std::map<int32_t, AISpan> aiSpanMap;
    int32_t placeholderIndex = -1;
    // when paragraph ends with a \n, it causes the paragraph height to gain an extra line
    // to have normal spacing between paragraphs, remove \n from every paragraph except the last one.
    bool needRemoveNewLine = false;
    bool useThemeFontColor = true;
    bool useThemeDecorationColor = true;
    std::optional<LeadingMargin> leadingMargin;
    int32_t selectedStart = -1;  // relative offset from span, [selectedStart, selectedEnd)
    int32_t selectedEnd = -1;
    bool needReLayoutParagraph = false;
    bool needReLayout = false;
    // used for Span uiNode
    bool needReCreateParagraph_ = true;
    RefPtr<AccessibilityProperty> accessibilityProperty = MakeRefPtr<AccessibilityProperty>();
    bool UpdateSymbolSpanFontFamily(TextStyle& symbolSpanStyle);
    void UpdateSymbolSpanParagraph(const RefPtr<FrameNode>& frameNode, const TextStyle& textStyle,
        const RefPtr<Paragraph>& builder, bool isDragging = false);
    virtual int32_t UpdateParagraph(const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& builder,
        const TextStyle& textStyle, bool isMarquee = false);
    virtual bool UpdateSpanTextStyle(const TextStyle& textStyle, const RefPtr<FrameNode>& frameNode);
    bool CheckSpanNeedReCreate(int32_t index);
    void UpdateReLayoutTextStyle(
        TextStyle& spanTextStyle, const TextStyle& textStyle, bool isSymbol);
    virtual void UpdateSymbolSpanColor(const RefPtr<FrameNode>& frameNode, TextStyle& symbolSpanStyle);
    virtual void UpdateTextStyleForAISpan(const std::u16string& content, const RefPtr<Paragraph>& builder,
        const TextStyle& textStyle, const TextStyle& aiSpanStyle);
    virtual void UpdateTextStyle(const std::u16string& content, const RefPtr<Paragraph>& builder,
        const TextStyle& textStyle, const int32_t selStart, const int32_t selEnd);
    virtual void UpdateContentTextStyle(
        const std::u16string& content, const RefPtr<Paragraph>& builder, const TextStyle& textStyle);
    virtual void GetIndex(int32_t& start, int32_t& end) const;
    virtual void FontRegisterCallback(const RefPtr<FrameNode>& frameNode, const TextStyle& textStyle);
    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const;
    std::string GetFont() const;
    virtual void StartDrag(int32_t start, int32_t end);
    virtual void EndDrag();
    virtual bool IsDragging();
    virtual ResultObject GetSpanResultObject(int32_t start, int32_t end);
    virtual RefPtr<SpanItem> GetSameStyleSpanItem(bool isEncodeTlvS = false) const;
    std::optional<std::pair<int32_t, int32_t>> GetIntersectionInterval(std::pair<int32_t, int32_t> interval) const;
    std::u16string urlAddress;
    std::function<void()> urlOnRelease;
    void SetUrlOnReleaseEvent(std::function<void()>&& onRelease)
    {
        urlOnRelease = std::move(onRelease);
    }
    bool Contains(int32_t index)
    {
        return rangeStart < index && index < position;
    }
    std::optional<TextStyle> GetTextStyle() const
    {
        return textStyle_;
    }
    void SetTextStyle(const std::optional<TextStyle>& textStyle)
    {
        textStyle_ = textStyle;
    }
    RefPtr<ResourceObject> GetResourceObject()
    {
        return resourceObject_;
    }
    void SetResourceObject(RefPtr<ResourceObject> resourceObject)
    {
        resourceObject_ = resourceObject;
    }
    void SetNeedRemoveNewLine(bool value)
    {
        needRemoveNewLine = value;
    }
    void SetOnClickEvent(GestureEventFunc&& onClick_)
    {
        onClick = std::move(onClick_);
    }
    void SetLongPressEvent(GestureEventFunc&& onLongPress_)
    {
        onLongPress = std::move(onLongPress_);
    }

    void SetDoubleClickEvent(GestureEventFunc&& onDoubleClick_)
    {
        onDoubleClick = std::move(onDoubleClick_);
    }

    void SetHoverEvent(OnHoverFunc&& onHover_)
    {
        onHover = std::move(onHover_);
    }

    void SetIsParentText(bool isText)
    {
        isParentText = isText;
    }
    bool GetIsParentText()
    {
        return isParentText;
    }
    std::u16string GetSpanContent(const std::u16string& rawContent, bool isMarquee = false);
    std::u16string GetSpanContent();
    uint32_t GetSymbolUnicode();
    std::string SymbolColorToString();

    virtual bool EncodeTlv(std::vector<uint8_t>& buff);
    static RefPtr<SpanItem> DecodeTlv(std::vector<uint8_t>& buff, int32_t& cursor);

    void SetTextPattern(const RefPtr<Pattern>& pattern)
    {
        pattern_ = pattern;
    }

    bool UpdateSpanTextColor(Color color);

    bool GetSymbolEffectSwitch() const
    {
        return symbolEffectSwitch_;
    }

    void SetSymbolEffectSwitch(bool symbolEffectSwitch)
    {
        symbolEffectSwitch_ = symbolEffectSwitch;
    }

    void SetSymbolId(uint32_t symbolId)
    {
        symbolId_ = symbolId;
    }

    uint32_t GetSymbolId()
    {
        return symbolId_;
    }
    
    virtual void SpanDumpInfo();
    void SpanDumpInfoAdvance();
    void MarkDirty()
    {
        needReLayout = true;
    }

    void MarkReCreateParagraph()
    {
        needReCreateParagraph_ = true;
    }

    void ResetNeedReCreateParagraph()
    {
        needReCreateParagraph_ = false;
    }

    void MarkReLayoutParagraph()
    {
        needReLayoutParagraph = true;
    }

    void ResetReLayout()
    {
        needReLayout = false;
        needReLayoutParagraph = false;
    }

    void UpdateContent(const std::u16string& newContent)
    {
        if (content != newContent) {
            MarkReCreateParagraph();
        }
        content = newContent;
        MarkDirty();
    }

    void UpdateTextColorWithoutCheck(Color color)
    {
        fontStyle->propTextColor = color;
        MarkReLayoutParagraph();
    }

    void UpdateTextDecorationColorWithoutCheck(Color color)
    {
        fontStyle->propTextDecorationColor = color;
        MarkReLayoutParagraph();
    }

    void ResetReCreateAndReLayout()
    {
        needReCreateParagraph_ = false;
        CHECK_NULL_VOID(textStyle_.has_value());
        textStyle_.value().ResetReCreateAndReLayoutBitmap();
    }

    std::optional<TextStyle> textStyle_;

private:
    void EncodeFontStyleTlv(std::vector<uint8_t>& buff) const;
    void EncodeTextLineStyleTlv(std::vector<uint8_t>& buff) const;
    bool isParentText = false;
    RefPtr<ResourceObject> resourceObject_;
    WeakPtr<Pattern> pattern_;
    bool symbolEffectSwitch_ = true;
    uint32_t symbolId_ = 0;
};

class ACE_EXPORT BaseSpan : public virtual AceType {
    DECLARE_ACE_TYPE(BaseSpan, AceType);

public:
    explicit BaseSpan(int32_t id) : groupId_(id)
    {}
    virtual void MarkTextDirty() = 0;
    virtual void SetTextBackgroundStyle(const TextBackgroundStyle& style);
    virtual void UpdateTextBackgroundFromParent(const std::optional<TextBackgroundStyle>& style)
    {
        textBackgroundStyle_ = style;
    }

    const std::optional<TextBackgroundStyle> GetTextBackgroundStyle() const
    {
        return textBackgroundStyle_;
    }

    void SetHasTextBackgroundStyle(bool hasStyle)
    {
        hasTextBackgroundStyle_ = hasStyle;
    }

    bool HasTextBackgroundStyle()
    {
        return hasTextBackgroundStyle_;
    }

private:
    std::optional<TextBackgroundStyle> textBackgroundStyle_;
    int32_t groupId_ = 0;
    bool hasTextBackgroundStyle_ = false;
};

class ACE_EXPORT SpanNode : public UINode, public BaseSpan {
    DECLARE_ACE_TYPE(SpanNode, UINode, BaseSpan);

public:
    static RefPtr<SpanNode> GetOrCreateSpanNode(int32_t nodeId);
    static RefPtr<SpanNode> GetOrCreateSpanNode(const std::string& tag, int32_t nodeId);
    static RefPtr<SpanNode> CreateSpanNode(int32_t nodeId);

    explicit SpanNode(int32_t nodeId) : UINode(V2::SPAN_ETS_TAG, nodeId), BaseSpan(nodeId)
    {
        if (spanItem_) {
            spanItem_->nodeId_ = nodeId;
        }
    }
    explicit SpanNode(const std::string& tag, int32_t nodeId) : UINode(tag, nodeId), BaseSpan(nodeId)
    {
        if (spanItem_) {
            spanItem_->nodeId_ = nodeId;
        }
    }
    ~SpanNode() override = default;

    void SetTextBackgroundStyle(const TextBackgroundStyle& style) override;
    void UpdateTextBackgroundFromParent(const std::optional<TextBackgroundStyle>& style) override;

    bool IsAtomicNode() const override
    {
        return true;
    }

    bool IsSyntaxNode() const override
    {
        return true;
    }

    const RefPtr<SpanItem>& GetSpanItem() const
    {
        return spanItem_;
    }

    void UpdateContent(const uint32_t& unicode)
    {
        spanItem_->spanItemType = SpanItemType::SYMBOL;
        if (spanItem_->unicode == unicode) {
            return;
        }
        spanItem_->unicode = unicode;
        spanItem_->MarkDirty();
        spanItem_->MarkReCreateParagraph();
        RequestTextFlushDirty(true);
    }

    void UpdateContent(const std::u16string& content)
    {
        if (spanItem_->content == content) {
            return;
        }
        spanItem_->content = content;
        spanItem_->MarkDirty();
        spanItem_->MarkReCreateParagraph();
        RequestTextFlushDirty(true);
    }

    void UpdateOnClickEvent(GestureEventFunc&& onClick)
    {
        spanItem_->onClick = std::move(onClick);
    }

    void OnInspectorIdUpdate(const std::string& inspectorId) override
    {
        spanItem_->inspectId = inspectorId;
    }

    void OnAutoEventParamUpdate(const std::string& desc) override
    {
        spanItem_->description = desc;
    }

    void UpdateColorByResourceId()
    {
        spanItem_->fontStyle->UpdateColorByResourceId();
        if (spanItem_->backgroundStyle) {
            spanItem_->backgroundStyle->UpdateColorByResourceId();
        }
    }

    void UpdateTextColorWithoutCheck(Color color)
    {
        spanItem_->UpdateTextColorWithoutCheck(color);
    }

    void UpdateTextDecorationColorWithoutCheck(Color color)
    {
        spanItem_->UpdateTextDecorationColorWithoutCheck(color);
    }

    // ChangeFlag only for rich editor
    DEFINE_SPAN_FONT_STYLE_ITEM(FontSize, Dimension, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextColor, Color, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(ItalicFontStyle, Ace::FontStyle, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(FontWeight, FontWeight, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(FontFamily, std::vector<std::string>, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextDecoration, TextDecoration, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextDecorationStyle, TextDecorationStyle, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextDecorationColor, Color, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(FontFeature, FONT_FEATURES_LIST, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM_RECREATE(TextCase, TextCase, ChangeFlag::RE_CREATE);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextShadow, std::vector<Shadow>, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(LetterSpacing, Dimension, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(SymbolColorList, std::vector<Color>, ChangeFlag::RE_CREATE);
    DEFINE_SPAN_FONT_STYLE_ITEM(SymbolRenderingStrategy, uint32_t, ChangeFlag::RE_CREATE);
    DEFINE_SPAN_FONT_STYLE_ITEM(SymbolEffectStrategy, uint32_t, ChangeFlag::RE_CREATE);
    DEFINE_SPAN_FONT_STYLE_ITEM(SymbolEffectOptions, SymbolEffectOptions, ChangeFlag::RE_CREATE);
    DEFINE_SPAN_FONT_STYLE_ITEM(MinFontScale, float, ChangeFlag::RE_CREATE);
    DEFINE_SPAN_FONT_STYLE_ITEM(MaxFontScale, float, ChangeFlag::RE_CREATE);
    DEFINE_SPAN_FONT_STYLE_ITEM(VariableFontWeight, int32_t, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM(EnableVariableFontWeight, bool, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_FONT_STYLE_ITEM_RECREATE(SymbolType, SymbolType, ChangeFlag::RE_CREATE);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(LineHeight, Dimension, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(BaselineOffset, Dimension, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(TextAlign, TextAlign, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(WordBreak, WordBreak, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(LeadingMargin, LeadingMargin, ChangeFlag::RE_CREATE);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(LineBreakStrategy, LineBreakStrategy, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(LineSpacing, Dimension, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(HalfLeading, bool, ChangeFlag::RE_LAYOUT);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(ParagraphSpacing, Dimension, ChangeFlag::RE_CREATE);

    // Mount to the previous Span node or Text node.
    void MountToParagraph();

    void AddChildSpanItem(const RefPtr<SpanNode>& child)
    {
        spanItem_->children.emplace_back(child->GetSpanItem());
    }

    void CleanSpanItemChildren()
    {
        spanItem_->children.clear();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        spanItem_->ToJsonValue(json, filter);
    }

    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override
    {
        spanItem_->ToTreeJson(json, config);
    }

    void RequestTextFlushDirty(bool markModifyDone = false);
    static void RequestTextFlushDirty(const RefPtr<UINode>& node, bool markModifyDone = true);
    // The function is only used for fast preview.
    void FastPreviewUpdateChildDone() override
    {
        RequestTextFlushDirty(true);
    }

    void SetPropertyInfoContainer();

    void MarkTextDirty() override
    {
        RequestTextFlushDirty();
    }

    void UpdateSpanTextColor(Color color)
    {
        if (!spanItem_->fontStyle) {
            spanItem_->fontStyle = std::make_unique<FontStyle>();
        }
        if (spanItem_->fontStyle->CheckTextColor(color)) {
            return;
        }
        spanItem_->fontStyle->UpdateTextColor(color);
        auto parent = GetParent();
        CHECK_NULL_VOID(parent);
        if (!spanItem_->UpdateSpanTextColor(color)) {
            RequestTextFlushDirty();
        }
    }

protected:
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}

private:
    std::list<RefPtr<SpanNode>> spanChildren_;
    RefPtr<SpanItem> spanItem_ = MakeRefPtr<SpanItem>();

    ACE_DISALLOW_COPY_AND_MOVE(SpanNode);
};

struct PlaceholderSpanItem : public SpanItem {
    DECLARE_ACE_TYPE(PlaceholderSpanItem, SpanItem);

public:
    int32_t placeholderSpanNodeId = -1;
    PlaceholderRun run_;
    std::optional<Color> dragBackgroundColor_;
    bool isDragShadowNeeded_ = true;
    PlaceholderSpanItem()
    {
        this->spanItemType = SpanItemType::PLACEHOLDER;
    }
    ~PlaceholderSpanItem() override = default;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override{};
    int32_t UpdateParagraph(const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& builder,
        const TextStyle& textStyle, bool isMarquee = false) override;
    bool UpdateSpanTextStyle(const TextStyle& textStyle, const RefPtr<FrameNode>& frameNode) override;
    virtual bool UpdatePlaceholderRun(PlaceholderStyle placeholderStyle);

    void DumpInfo() const;
    ACE_DISALLOW_COPY_AND_MOVE(PlaceholderSpanItem);

    void SetCustomNode(const RefPtr<UINode>& customNode)
    {
        customNode_ = customNode;
    }

    const RefPtr<UINode> GetCustomNode() const
    {
        return customNode_;
    }

    void UpdateColorByResourceId()
    {
        CHECK_NULL_VOID(dragBackgroundColor_.has_value());
        dragBackgroundColor_.value().UpdateColorByResourceId();
    }

private:
    RefPtr<UINode> customNode_;
};

class PlaceholderSpanPattern : public Pattern {
    DECLARE_ACE_TYPE(PlaceholderSpanPattern, Pattern);

public:
    PlaceholderSpanPattern() = default;
    ~PlaceholderSpanPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }
};

class ACE_EXPORT PlaceholderSpanNode : public FrameNode {
    DECLARE_ACE_TYPE(PlaceholderSpanNode, FrameNode);

public:
    static RefPtr<PlaceholderSpanNode> GetOrCreateSpanNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
    {
        auto frameNode = GetFrameNode(tag, nodeId);
        CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<PlaceholderSpanNode>(frameNode));
        auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
        auto placeholderSpanNode = AceType::MakeRefPtr<PlaceholderSpanNode>(tag, nodeId, pattern);
        placeholderSpanNode->InitializePatternAndContext();
        ElementRegister::GetInstance()->AddUINode(placeholderSpanNode);
        return placeholderSpanNode;
    }

    PlaceholderSpanNode(const std::string& tag, int32_t nodeId) : FrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>())
    {
        if (placeholderSpanItem_) {
            placeholderSpanItem_->nodeId_ = nodeId;
        }
    }
    PlaceholderSpanNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : FrameNode(tag, nodeId, pattern)
    {
        if (placeholderSpanItem_) {
            placeholderSpanItem_->nodeId_ = nodeId;
        }
    }
    ~PlaceholderSpanNode() override = default;

    const RefPtr<PlaceholderSpanItem>& GetSpanItem() const
    {
        return placeholderSpanItem_;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void MarkModifyDone() override
    {
        FrameNode::MarkModifyDone();
        placeholderSpanItem_->MarkDirty();
    }

    void MarkDirtyNode(PropertyChangeFlag extraFlag = PROPERTY_UPDATE_NORMAL) override
    {
        FrameNode::MarkDirtyNode(extraFlag);
        placeholderSpanItem_->MarkDirty();
    }

    void DumpInfo() override
    {
        FrameNode::DumpInfo();
        CHECK_NULL_VOID(placeholderSpanItem_);
        placeholderSpanItem_->DumpInfo();
    }

private:
    RefPtr<PlaceholderSpanItem> placeholderSpanItem_ = MakeRefPtr<PlaceholderSpanItem>();

    ACE_DISALLOW_COPY_AND_MOVE(PlaceholderSpanNode);
};

struct CustomSpanItem : public PlaceholderSpanItem {
    DECLARE_ACE_TYPE(CustomSpanItem, PlaceholderSpanItem);

public:
    CustomSpanItem() : PlaceholderSpanItem()
    {
        this->spanItemType = SpanItemType::CustomSpan;
    }
    ~CustomSpanItem() override = default;
    RefPtr<SpanItem> GetSameStyleSpanItem(bool isEncodeTlvS = false) const override;
    ResultObject GetSpanResultObject(int32_t start, int32_t end) override;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override{};
    ACE_DISALLOW_COPY_AND_MOVE(CustomSpanItem);
    std::optional<std::function<CustomSpanMetrics(CustomSpanMeasureInfo)>> onMeasure;
    std::optional<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> onDraw;
    void SpanDumpInfo() override
    {
        PlaceholderSpanItem::DumpInfo();
    }
    bool isFrameNode = false;
};

class ACE_EXPORT CustomSpanNode : public FrameNode {
    DECLARE_ACE_TYPE(CustomSpanNode, FrameNode);

public:
    static RefPtr<CustomSpanNode> CreateFrameNode(int32_t nodeId)
    {
        auto customSpanNode = AceType::MakeRefPtr<CustomSpanNode>(V2::CUSTOM_SPAN_NODE_ETS_TAG, nodeId);
        customSpanNode->InitializePatternAndContext();
        ElementRegister::GetInstance()->AddUINode(customSpanNode);
        customSpanNode->customSpanItem_->isFrameNode = true;
        return customSpanNode;
    }

    static RefPtr<CustomSpanNode> GetOrCreateSpanNode(const std::string& tag, int32_t nodeId)
    {
        auto frameNode = GetFrameNode(tag, nodeId);
        CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<CustomSpanNode>(frameNode));
        auto customSpanNode = AceType::MakeRefPtr<CustomSpanNode>(tag, nodeId);
        customSpanNode->InitializePatternAndContext();
        ElementRegister::GetInstance()->AddUINode(customSpanNode);
        customSpanNode->customSpanItem_->isFrameNode = true;
        return customSpanNode;
    }

    CustomSpanNode(const std::string& tag, int32_t nodeId) : FrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>())
    {
        if (customSpanItem_) {
            customSpanItem_->nodeId_ = nodeId;
        }
    }
    ~CustomSpanNode() override = default;

    const RefPtr<CustomSpanItem>& GetSpanItem() const
    {
        return customSpanItem_;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    void DumpInfo() override
    {
        FrameNode::DumpInfo();
        CHECK_NULL_VOID(customSpanItem_);
        customSpanItem_->DumpInfo();
    }

private:
    RefPtr<CustomSpanItem> customSpanItem_ = MakeRefPtr<CustomSpanItem>();

    ACE_DISALLOW_COPY_AND_MOVE(CustomSpanNode);
};

struct ImageSpanItem : public PlaceholderSpanItem {
    DECLARE_ACE_TYPE(ImageSpanItem, PlaceholderSpanItem);

public:
    ImageSpanItem() : PlaceholderSpanItem()
    {
        this->spanItemType = SpanItemType::IMAGE;
    }
    ~ImageSpanItem() override = default;
    bool UpdatePlaceholderRun(PlaceholderStyle placeholderStyle) override;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override{};
    void UpdatePlaceholderBackgroundStyle(const RefPtr<FrameNode>& imageNode);
    void SetImageSpanOptions(const ImageSpanOptions& options);
    void ResetImageSpanOptions();
    ResultObject GetSpanResultObject(int32_t start, int32_t end) override;
    RefPtr<SpanItem> GetSameStyleSpanItem(bool isEncodeTlvS = false) const override;
    ACE_DISALLOW_COPY_AND_MOVE(ImageSpanItem);

    bool EncodeTlv(std::vector<uint8_t>& buff) override;
    static RefPtr<ImageSpanItem> DecodeTlv(std::vector<uint8_t>& buff, int32_t& cursor);

    ImageSpanOptions options;
    OnHoverFunc onHover_;
private:
    ImageSpanOptions GetImageSpanOptionsFromImageNode() const;
    ImageSpanAttribute CreateImageSpanAttribute(const RefPtr<ImageLayoutProperty>& layoutProperty) const;
};

class ACE_EXPORT ImageSpanNode : public FrameNode {
    DECLARE_ACE_TYPE(ImageSpanNode, FrameNode);

public:
    static RefPtr<ImageSpanNode> GetOrCreateSpanNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
    {
        auto frameNode = GetFrameNode(tag, nodeId);
        CHECK_NULL_RETURN(!frameNode, AceType::DynamicCast<ImageSpanNode>(frameNode));
        auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
        auto imageSpanNode = AceType::MakeRefPtr<ImageSpanNode>(tag, nodeId, pattern);
        imageSpanNode->InitializePatternAndContext();
        ElementRegister::GetInstance()->AddUINode(imageSpanNode);
        return imageSpanNode;
    }

    ImageSpanNode(const std::string& tag, int32_t nodeId) : FrameNode(tag, nodeId, AceType::MakeRefPtr<ImagePattern>())
    {
        if (imageSpanItem_) {
            imageSpanItem_->nodeId_ = nodeId;
        }
    }
    ImageSpanNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : FrameNode(tag, nodeId, pattern)
    {
        if (imageSpanItem_) {
            imageSpanItem_->nodeId_ = nodeId;
        }
    }
    ~ImageSpanNode() override = default;

    const RefPtr<ImageSpanItem>& GetSpanItem() const
    {
        return imageSpanItem_;
    }

    void DumpInfo() override
    {
        FrameNode::DumpInfo();
        CHECK_NULL_VOID(imageSpanItem_);
        imageSpanItem_->DumpInfo();
    }

    void SetImageItem(const RefPtr<ImageSpanItem>& imageSpan)
    {
        imageSpanItem_ = imageSpan;
    }

private:
    RefPtr<ImageSpanItem> imageSpanItem_ = MakeRefPtr<ImageSpanItem>();

    ACE_DISALLOW_COPY_AND_MOVE(ImageSpanNode);
};

class ACE_EXPORT ContainerSpanNode : public UINode, public BaseSpan {
    DECLARE_ACE_TYPE(ContainerSpanNode, UINode, BaseSpan);

public:
    static RefPtr<ContainerSpanNode> GetOrCreateSpanNode(int32_t nodeId)
    {
        auto spanNode = ElementRegister::GetInstance()->GetSpecificItemById<ContainerSpanNode>(nodeId);
        if (spanNode) {
            spanNode->SetHasTextBackgroundStyle(false);
            return spanNode;
        }
        spanNode = MakeRefPtr<ContainerSpanNode>(nodeId);
        ElementRegister::GetInstance()->AddUINode(spanNode);
        return spanNode;
    }

    explicit ContainerSpanNode(int32_t nodeId) : UINode(V2::CONTAINER_SPAN_ETS_TAG, nodeId), BaseSpan(nodeId) {}
    ~ContainerSpanNode() override = default;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    bool IsAtomicNode() const override
    {
        return false;
    }

    void MarkTextDirty() override
    {
        SpanNode::RequestTextFlushDirty(Claim(this));
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(ContainerSpanNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_NODE_H
