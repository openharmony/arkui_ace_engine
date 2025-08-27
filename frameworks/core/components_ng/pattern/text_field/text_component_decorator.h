/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_COMPONENT_DECORATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_COMPONENT_DECORATOR_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TextComponentDecorator : public AceType {
    DECLARE_ACE_TYPE(TextComponentDecorator, AceType);
public:
    TextComponentDecorator(const RefPtr<FrameNode>& decoratedNode);
    ~TextComponentDecorator();
    void BuildDecorator();
    void CleanDecorator();
    virtual void UpdateTextFieldMargin() = 0;
    virtual float MeasureDecorator(float contentWidth, const std::u16string& textContent, bool showPlaceHolder) = 0;
    virtual void LayoutDecorator() = 0;
    virtual float GetBoundHeight() const = 0;
    virtual float GetDecoratorHeight() const;
    virtual float GetContentWidth() const;

protected:
    WeakPtr<FrameNode> decoratedNode_;
    WeakPtr<FrameNode> textNode_;
};

class ACE_EXPORT CounterDecorator : public TextComponentDecorator {
    DECLARE_ACE_TYPE(CounterDecorator, TextComponentDecorator);
public:
    explicit CounterDecorator(const RefPtr<FrameNode>& decoratedNode): TextComponentDecorator(decoratedNode) {}
    ~CounterDecorator() override = default;
    void UpdateTextFieldMargin() override;
    float MeasureDecorator(float contentWidth, const std::u16string& textContent, bool showPlaceHolder) override;
    void LayoutDecorator() override;
    float GetBoundHeight() const override;
    bool HasContent() const;
private:
    void UpdateCounterContentAndStyle(uint32_t textLength, uint32_t maxLength, bool isVisible = true);
    float MeasureTextNodeHeight();
    void UpdateTextNodeAndMeasure(uint32_t textLength, uint32_t maxLength, const LayoutConstraintF& contentConstraint);
    TextAlign GetCounterNodeAlignment();
    void HandleNonTextArea();
    void HandleTextArea();
    std::string GetAccessibilityText(uint32_t textLength, uint32_t maxLength);
};

class ACE_EXPORT ErrorDecorator : public TextComponentDecorator {
    DECLARE_ACE_TYPE(ErrorDecorator, TextComponentDecorator);
public:
    explicit ErrorDecorator(const RefPtr<FrameNode>& decoratedNode): TextComponentDecorator(decoratedNode) {}
    ~ErrorDecorator() override = default;
    void UpdateTextFieldMargin() override;
    float MeasureDecorator(float contentWidth, const std::u16string& textContent, bool showPlaceHolder) override;
    void LayoutDecorator() override;
    float GetBoundHeight() const override;
private:
    void BeforeLayout();
    void UpdateLayoutProperty();
    void UpdateErrorStyle();

};

}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_COMPONENT_DECORATOR_H