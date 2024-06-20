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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_KEYBOARD_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_KEYBOARD_VIEW_H

#include <functional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/overlay/keyboard_base_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT KeyboardView {
public:
    static RefPtr<FrameNode> CreateKeyboard(int32_t targetId, std::function<void()> builder)
    {
        CHECK_NULL_RETURN(builder, nullptr);
        // build keyboard node
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        builder();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        auto keyboardNode = AceType::DynamicCast<UINode>(customNode);

        return CreateKeyboardWithNode(targetId, keyboardNode);
    };

    static RefPtr<FrameNode> CreateKeyboardWithNode(int32_t targetId, const RefPtr<UINode>& keyboardNode)
    {
        CHECK_NULL_RETURN(keyboardNode, nullptr);
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::KEYBOARD_ETS_TAG, targetId);
        // create wrapper node
        auto wrapperNode = FrameNode::CreateFrameNode(V2::KEYBOARD_ETS_TAG,
            nodeId, AceType::MakeRefPtr<KeyboardPattern>(targetId));
        auto wrapperLayoutProperty = wrapperNode->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(wrapperLayoutProperty, nullptr);
        wrapperLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);

        wrapperNode->AddChild(keyboardNode);
        wrapperNode->MarkModifyDone();

        // disable focus
        auto focusHub = wrapperNode->GetOrCreateFocusHub();
        focusHub->SetFocusable(false);

        // transparent touch event
        auto gestureHub = wrapperNode->GetOrCreateGestureEventHub();
        gestureHub->SetHitTestMode(HitTestMode::HTMTRANSPARENT_SELF);
        return wrapperNode;
    };
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_KEYBOARD_VIEW_H
