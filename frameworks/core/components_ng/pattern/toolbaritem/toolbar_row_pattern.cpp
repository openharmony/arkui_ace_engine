/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/toolbaritem/toolbar_row_pattern.h"

#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
ScopeFocusAlgorithm ToolBarRowPattern::GetScopeFocusAlgorithm()
{
    auto focusAlgorithm = ScopeFocusAlgorithm(false, true, ScopeType::FLEX);

    focusAlgorithm.getNextFocusNode = [wp = WeakClaim(this)](FocusStep step, const WeakPtr<FocusHub>& currFocusNode,
                                          WeakPtr<FocusHub>& nextFocusNode) -> bool {
        auto toolBarRow = wp.Upgrade();
        CHECK_NULL_RETURN(toolBarRow, false);
        nextFocusNode = toolBarRow->GetNextFocusNode(step, currFocusNode);
        return nextFocusNode.Upgrade() != currFocusNode.Upgrade();
    };
    return focusAlgorithm;
}

WeakPtr<FocusHub> ToolBarRowPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto curFocus = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocus, nullptr);
    auto curFrame = curFocus->GetFrameNode();
    CHECK_NULL_RETURN(curFrame, nullptr);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto root = context->GetRootElement();
    CHECK_NULL_RETURN(root, nullptr);
    auto container = AceType::DynamicCast<FrameNode>(root->GetChildren().front());
    CHECK_NULL_RETURN(container, nullptr);
    auto pattern = container->GetPattern<NG::ContainerModalPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto page = pattern->GetPageNode();
    CHECK_NULL_RETURN(page, nullptr);
    auto pageFocusHub = page->GetFocusHub();
    CHECK_NULL_RETURN(pageFocusHub, nullptr);
    auto toolBarRow = pattern->GetCustomTitleRow();
    CHECK_NULL_RETURN(toolBarRow, nullptr);
    auto leftRow = AceType::DynamicCast<FrameNode>(toolBarRow->GetChildAtIndex(1));
    auto rightRow = AceType::DynamicCast<FrameNode>(toolBarRow->GetChildAtIndex(2));
    RefPtr<FocusHub> nextFocusNode = nullptr;
    bool isHead = true;
    if (step == FocusStep::DOWN) {
        return pageFocusHub->GetHeadOrTailChild(true);
    }
    if ((step == FocusStep::TAB || step == FocusStep::RIGHT) && rightRow) {
        isHead = true;
        nextFocusNode = rightRow->GetFocusHub();
    } else if ((step == FocusStep::SHIFT_TAB || step == FocusStep::LEFT) && leftRow) {
        isHead = false;
        nextFocusNode = leftRow->GetFocusHub();
    }
    if (!nextFocusNode && (step == FocusStep::TAB || step == FocusStep::SHIFT_TAB)) {
        return pageFocusHub;
    }
    if (nextFocusNode) {
        if (!nextFocusNode->IsCurrentFocus() && nextFocusNode->GetHeadOrTailChild(isHead)) {
            return nextFocusNode;
        } else if (step == FocusStep::TAB || step == FocusStep::SHIFT_TAB) {
            return pageFocusHub;
        }
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
