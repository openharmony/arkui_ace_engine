/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include <string>

#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/utils.h"
#include "core/gestures/gesture_info.h"

#define DEFINE_SPAN_FONT_STYLE_ITEM(name, type)                              \
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
    }                                                                        \
    void Update##name(const type& value)                                     \
    {                                                                        \
        if (!spanItem_->fontStyle) {                                         \
            spanItem_->fontStyle = std::make_unique<FontStyle>();            \
        }                                                                    \
        if (spanItem_->fontStyle->Check##name(value)) {                      \
            LOGD("the %{public}s is same, just ignore", #name);              \
            return;                                                          \
        }                                                                    \
        spanItem_->fontStyle->Update##name(value);                           \
        RequestTextFlushDirty();                                             \
    }                                                                        \
    void Reset##name()                                                       \
    {                                                                        \
        if (spanItem_->fontStyle) {                                          \
            return spanItem_->fontStyle->Reset##name();                      \
        }                                                                    \
    }                                                                        \
    void Update##name##WithoutFlushDirty(const type& value)                  \
    {                                                                        \
        if (!spanItem_->fontStyle) {                                         \
            spanItem_->fontStyle = std::make_unique<FontStyle>();            \
        }                                                                    \
        if (spanItem_->fontStyle->Check##name(value)) {                      \
            LOGD("the %{public}s is same, just ignore", #name);              \
            return;                                                          \
        }                                                                    \
        spanItem_->fontStyle->Update##name(value);                           \
    }                                                                        \


#define DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(name, type)                             \
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
            LOGD("the %{public}s is same, just ignore", #name);                  \
            return;                                                              \
        }                                                                        \
        spanItem_->textLineStyle->Update##name(value);                           \
        RequestTextFlushDirty();                                                 \
    }                                                                            \
    void Reset##name()                                                           \
    {                                                                            \
        if (spanItem_->textLineStyle) {                                          \
            return spanItem_->textLineStyle->Reset##name();                      \
        }                                                                        \
    }                                                                            \
    void Update##name##WithoutFlushDirty(const type& value)                      \
    {                                                                            \
        if (!spanItem_->textLineStyle) {                                         \
            spanItem_->textLineStyle = std::make_unique<TextLineStyle>();        \
        }                                                                        \
        if (spanItem_->textLineStyle->Check##name(value)) {                      \
            LOGD("the %{public}s is same, just ignore", #name);                  \
            return;                                                              \
        }                                                                        \
        spanItem_->textLineStyle->Update##name(value);                           \
    }

namespace OHOS::Ace::NG {

class Paragraph;

struct SpanItem : public AceType {
    DECLARE_ACE_TYPE(SpanItem, AceType);

public:
    SpanItem() = default;
    virtual ~SpanItem()
    {
        children.clear();
    }
    int32_t position = -1;
    std::string content;
    std::unique_ptr<FontStyle> fontStyle;
    std::unique_ptr<TextLineStyle> textLineStyle;
    GestureEventFunc onClick;
    std::list<RefPtr<SpanItem>> children;
    int32_t placeHolderIndex = -1;
#ifdef ENABLE_DRAG_FRAMEWORK
    int32_t selectedStart = -1;
    int32_t selectedEnd = -1;
#endif // ENABLE_DRAG_FRAMEWORK
    virtual int32_t UpdateParagraph(const RefPtr<Paragraph>& builder, double width = 0.0f, double height = 0.0f,
        VerticalAlign verticalAlign = VerticalAlign::BASELINE);
    virtual void UpdateTextStyle(const RefPtr<Paragraph>& builder, const std::optional<TextStyle>& textStyle);

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json) const;
    std::string GetFont() const;
#ifdef ENABLE_DRAG_FRAMEWORK
    virtual void StartDrag(int32_t start, int32_t end);
    virtual void EndDrag();
    virtual bool IsDragging();
#endif // ENABLE_DRAG_FRAMEWORK
};

struct ImageSpanItem : public SpanItem {
    DECLARE_ACE_TYPE(ImageSpanItem, SpanItem);

public:
    ImageSpanItem() = default;
    ~ImageSpanItem() override = default;
    int32_t UpdateParagraph(
        const RefPtr<Paragraph>& builder, double width, double height, VerticalAlign verticalAlign) override;
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override {};

    TextStyle textStyle;

    ACE_DISALLOW_COPY_AND_MOVE(ImageSpanItem);
};

enum class PropertyInfo {
    FONTSIZE = 0,
    FONTCOLOR,
    FONTSTYLE,
    FONTWEIGHT,
    FONTFAMILY,
    TEXTDECORATION,
    TEXTCASE,
    LETTERSPACE,
    LINEHEIGHT,
    NONE,
};

class ACE_EXPORT SpanNode : public UINode {
    DECLARE_ACE_TYPE(SpanNode, UINode);

public:
    static RefPtr<SpanNode> GetOrCreateSpanNode(int32_t nodeId);

    explicit SpanNode(int32_t nodeId) : UINode(V2::SPAN_ETS_TAG, nodeId) {}
    ~SpanNode() override = default;

    bool IsAtomicNode() const override
    {
        return true;
    }

    const RefPtr<SpanItem>& GetSpanItem() const
    {
        return spanItem_;
    }

    void UpdateContent(const std::string& content)
    {
        if (spanItem_->content == content) {
            LOGD("the content is same, just ignore");
            return;
        }
        spanItem_->content = content;
        RequestTextFlushDirty();
    }

    void UpdateOnClickEvent(GestureEventFunc&& onClick)
    {
        spanItem_->onClick = std::move(onClick);
    }

    DEFINE_SPAN_FONT_STYLE_ITEM(FontSize, Dimension);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextColor, Color);
    DEFINE_SPAN_FONT_STYLE_ITEM(ItalicFontStyle, Ace::FontStyle);
    DEFINE_SPAN_FONT_STYLE_ITEM(FontWeight, FontWeight);
    DEFINE_SPAN_FONT_STYLE_ITEM(FontFamily, std::vector<std::string>);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextDecoration, TextDecoration);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextDecorationColor, Color);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextCase, TextCase);
    DEFINE_SPAN_FONT_STYLE_ITEM(LetterSpacing, Dimension);
    DEFINE_SPAN_TEXT_LINE_STYLE_ITEM(LineHeight, Dimension);

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

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        spanItem_->ToJsonValue(json);
    }

    void RequestTextFlushDirty();
    // The function is only used for fast preview.
    void FastPreviewUpdateChildDone() override
    {
        RequestTextFlushDirty();
    }

    void AddPropertyInfo(PropertyInfo value)
    {
        propertyInfo_.insert(value);
    }

    void CleanPropertyInfo()
    {
        propertyInfo_.clear();
    }

    std::set<PropertyInfo> CaculateInheritPropertyInfo()
    {
        std::set<PropertyInfo> inheritPropertyInfo;
        const std::set<PropertyInfo> propertyInfoContainer = { PropertyInfo::FONTSIZE,
                                                               PropertyInfo::FONTCOLOR,
                                                               PropertyInfo::FONTSTYLE,
                                                               PropertyInfo::FONTWEIGHT,
                                                               PropertyInfo::FONTFAMILY,
                                                               PropertyInfo::TEXTDECORATION,
                                                               PropertyInfo::TEXTCASE,
                                                               PropertyInfo::LETTERSPACE,
                                                               PropertyInfo::LINEHEIGHT };
        set_difference(propertyInfoContainer.begin(), propertyInfoContainer.end(),
                       propertyInfo_.begin(), propertyInfo_.end(),
                       inserter(inheritPropertyInfo, inheritPropertyInfo.begin()));
        return inheritPropertyInfo;
    }

private:
    std::list<RefPtr<SpanNode>> spanChildren_;
    std::set<PropertyInfo> propertyInfo_;

    RefPtr<SpanItem> spanItem_ = MakeRefPtr<SpanItem>();

    ACE_DISALLOW_COPY_AND_MOVE(SpanNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_NODE_H
