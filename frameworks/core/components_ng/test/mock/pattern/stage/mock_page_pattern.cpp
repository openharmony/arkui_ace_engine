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

#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {
void PagePattern::ProcessHideState() {}
void PagePattern::ProcessShowState() {}
void PagePattern::BuildSharedTransitionMap() {}
void PagePattern::AddPageTransition(const RefPtr<PageTransitionEffect>& effect) {}
void PagePattern::ClearPageTransitionEffect() {}
void PagePattern::OnAttachToFrameNode() {}
void PagePattern::AddDelaytLayoutNode(const WeakPtr<FrameNode>& node) {}

void PagePattern::OnShow()
{
    isOnShow_ = true;
}

void PagePattern::OnHide()
{
    isOnShow_ = false;
}

bool PagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& /*wrapper*/, const DirtySwapConfig& /*config*/)
{
    return false;
} 

bool PagePattern::TriggerPageTransition(PageTransitionType type, const std::function<void()>& onFinish)
{
    return false;
}

void PagePattern::BeforeCreateLayoutWrapper() {}

RefPtr<PageTransitionEffect> PagePattern::FindPageTransitionEffect(PageTransitionType type)
{
    return nullptr;
}

RefPtr<PageTransitionEffect> PagePattern::GetTopTransition() const
{
    return nullptr;
}

void PagePattern::AddJsAnimator(const std::string& animatorId, const RefPtr<Framework::AnimatorInfo>& animatorInfo) {}

RefPtr<Framework::AnimatorInfo> PagePattern::GetJsAnimator(const std::string& animatorId)
{
    return AceType::MakeRefPtr<Framework::AnimatorInfo>();
}

bool PagePattern::AvoidKeyboard() const
{
    return false;
}

RefPtr<LayoutAlgorithm> PagePattern::CreateLayoutAlgorithm()
{
    return Pattern::CreateLayoutAlgorithm();
}
} // namespace OHOS::Ace::NG
