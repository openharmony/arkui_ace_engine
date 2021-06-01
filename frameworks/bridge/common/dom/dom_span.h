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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_SPAN_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_SPAN_H

#include "core/components/text_span/text_span_component.h"
#include "frameworks/bridge/common/dom/dom_node.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace::Framework {

class DOMSpan final : public DOMNode {
    DECLARE_ACE_TYPE(DOMSpan, DOMNode);

public:
    DOMSpan(NodeId nodeId, const std::string& nodeName);
    ~DOMSpan() override = default;

    bool HasSetFontStyle() const
    {
        return isSetFontStyle_;
    }

    bool HasSetFontColor() const
    {
        return isSetFontColor_;
    }

    bool HasSetFontWeight() const
    {
        return isSetFontWeight_;
    }

    bool HasSetFontSize() const
    {
        return isSetFontSize_;
    }

    bool HasSetFontFamily() const
    {
        return isSetFontFamily_;
    }

    bool HasSetTextDecoration() const
    {
        return isSetTextDecoration_;
    }

    RefPtr<Component> GetSpecializedComponent() override
    {
        return textSpanChild_;
    }

    bool HasSetAllowScale() const
    {
        return isSetAllowScale_;
    }

    void SetTextStyle(const TextStyle& spanStyle)
    {
        spanStyle_ = spanStyle;
    }

protected:
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool SetSpecializedStyle(const std::pair<std::string, std::string>& style) override;
    void PrepareSpecializedComponent() override;

    void OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot) override;
    void OnChildNodeRemoved(const RefPtr<DOMNode>& child) override;

private:
    void CheckAndSetCurrentSpanStyle(const RefPtr<DOMSpan>& domSpan, TextStyle& currentStyle,
        const TextStyle& parentStyle);

    TextStyle spanStyle_;
    bool isSetFontStyle_ = false;
    bool isSetFontColor_ = false;
    bool isSetFontWeight_ = false;
    bool isSetFontSize_ = false;
    bool isSetFontFamily_ = false;
    bool isSetTextDecoration_ = false;
    bool isSetAllowScale_ = false;
    std::list<RefPtr<DOMNode>> children_;
    RefPtr<TextSpanComponent> textSpanChild_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_SPAN_H
