/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_KEYBOARD_SHEET_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_KEYBOARD_SHEET_VIEW_H

#include <functional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"

namespace OHOS::Ace::NG {
class KeyboardPattern;
class ACE_EXPORT KeyboardView {
public:
    static RefPtr<FrameNode> CreateKeyboard(int32_t targetId, std::function<void()> builder)
    {
        CHECK_NULL_RETURN(builder, nullptr);

        // create wrapper node
        auto wrapperNode = FrameNode::CreateFrameNode(V2::KEYBOARD_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<KeyboardPattern>(targetId));
        auto wrapperLayoutProperty = wrapperNode->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(wrapperLayoutProperty, nullptr);

        // build keyboard node
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        builder();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        auto keyboardNode = AceType::DynamicCast<FrameNode>(customNode);
        CHECK_NULL_RETURN(keyboardNode, nullptr);

        // set custom keyboard view width match parent
        auto layoutProperty = keyboardNode->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProperty, nullptr);
        std::optional<CalcLength> height = std::nullopt;
        auto&& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
        if (layoutConstraint && layoutConstraint->selfIdealSize) {
            height = layoutConstraint->selfIdealSize->Height();
        }
        auto dimension = Dimension(1.0f, DimensionUnit::PERCENT);
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(dimension), height));

        // put builder node to the bottom, and set the wrapper size match parent page
        wrapperLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
        wrapperLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

        wrapperNode->AddChild(keyboardNode);
        wrapperNode->MarkModifyDone();

        // disable focus
        auto focusHub = wrapperNode->GetOrCreateFocusHub();
        focusHub->SetFocusable(false);

        // transparent touch event
        auto gestureHub = wrapperNode->GetOrCreateGestureEventHub();
        gestureHub->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
        return wrapperNode;
    };
};

class ACE_EXPORT KeyboardPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(KeyboardPattern, LinearLayoutPattern);

public:
    KeyboardPattern(int32_t targetId) : LinearLayoutPattern(true)
    {
        targetId_ = targetId;
    }

    int32_t GetTargetId()
    {
        return targetId_;
    }

    ~KeyboardPattern() override = default;

private:
    int32_t targetId_ = -1;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_KEYBOARD_SHEET_VIEW_H
