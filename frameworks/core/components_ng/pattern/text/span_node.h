/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
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
        MarkNeedFlushDirty(PROPERTY_UPDATE_BY_CHILD_REQUEST);                \
    }

namespace OHOS::Ace::NG {

struct SpanItem : public Referenced {
    std::string content;
    std::unique_ptr<FontStyle> fontStyle;
    GestureEventFunc onClick;
    std::list<RefPtr<SpanItem>> children;

    void UpdateParagraph(RSParagraphBuilder* builder);
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
            LOGD("the =content is same, just ignore");
            return;
        }
        spanItem_->content = content;
        MarkNeedFlushDirty(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    }

    void UpdateOnClickEvent(GestureEventFunc&& onClick)
    {
        spanItem_->onClick = std::move(onClick);
    }

    DEFINE_SPAN_FONT_STYLE_ITEM(FontSize, Dimension);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextColor, Color);
    DEFINE_SPAN_FONT_STYLE_ITEM(ItalicFontStyle, ItalicFontStyle);
    DEFINE_SPAN_FONT_STYLE_ITEM(FontWeight, FontWeight);
    DEFINE_SPAN_FONT_STYLE_ITEM(FontFamily, std::vector<std::string>);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextDecoration, TextDecoration);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextDecorationColor, Color);
    DEFINE_SPAN_FONT_STYLE_ITEM(TextCase, TextCase);

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

private:
    std::list<RefPtr<SpanNode>> spanChildren_;

    RefPtr<SpanItem> spanItem_ = MakeRefPtr<SpanItem>();

    ACE_DISALLOW_COPY_AND_MOVE(SpanNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_NODE_H
