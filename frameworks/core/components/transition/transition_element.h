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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSITION_TRANSITION_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSITION_TRANSITION_ELEMENT_H

#include "core/components/common/properties/page_transition_option.h"
#include "core/components/common/properties/tween_option.h"
#include "core/components/display/display_component.h"
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace {

class Animator;
class TweenElement;

enum class TransitionOptionType {
    TRANSITION_IN,
    TRANSITION_OUT,
    TRANSITION_SHARED_IN,
    TRANSITION_SHARED_OUT,
};

class TransitionElement : public ComposedElement {
    DECLARE_ACE_TYPE(TransitionElement, ComposedElement);

public:
    explicit TransitionElement(const ComposeId& id) : ComposedElement(id) {}
    ~TransitionElement() override = default;

    void Update() override;
    void SetController(const RefPtr<Animator>& controller);
    RefPtr<Animator> GetController() const;
    void SetTouchable(bool enable);
    void SetVisible(VisibleType visible);
    void SwitchTransitionOption(TransitionOptionType direction, bool needApplyOption = false);
    void SetTransition(const TweenOption& inOption, const TweenOption& outOption);
    void SetSharedTransition(const TweenOption& inOption, const TweenOption& outOption);
    RefPtr<Element> GetContentElement() const;

protected:
    RefPtr<Component> BuildChild() override;

private:
    RefPtr<TweenElement> GetChildTween() const;

    std::map<TransitionOptionType, TweenOption> optionMap_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSITION_TRANSITION_ELEMENT_H
