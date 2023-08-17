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
#include "gtest/gtest.h"

#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
namespace OHOS::Ace::NG {
void SelectOverlayPattern::UpdateFirstSelectHandleInfo(const SelectHandleInfo& info)
{
    GTEST_LOG_(INFO) << "UpdateFirstSelectHandleInfo has called";
}

void SelectOverlayPattern::UpdateSecondSelectHandleInfo(const SelectHandleInfo& info)
{
    GTEST_LOG_(INFO) << "UpdateSecondSelectHandleInfo has called";
}

void SelectOverlayPattern::UpdateSelectMenuInfo(const SelectMenuInfo& info)
{
    GTEST_LOG_(INFO) << "UpdateSelectMenuInfo has called";
}

void SelectOverlayPattern::UpdateShowArea(const RectF& area)
{
    GTEST_LOG_(INFO) << "UpdateShowArea has called";
}

void SelectOverlayPattern::ShowOrHiddenMenu(bool isHidden)
{
    GTEST_LOG_(INFO) << "ShowOrHiddenMenu has called";
}

bool SelectOverlayPattern::IsMenuShow()
{
    return true;
}

bool SelectOverlayPattern::IsHandleShow()
{
    return true;
}

void SelectOverlayPattern::OnAttachToFrameNode() {}

void SelectOverlayPattern::OnDetachFromFrameNode(FrameNode* frameNode) {}

void SelectOverlayLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper) {}

bool SelectOverlayPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return firstHandleDrag_ && secondHandleDrag_ && false;
}

void SelectOverlayPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper) {}

void SelectOverlayPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper) {}
} // namespace OHOS::Ace::NG
