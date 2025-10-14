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

#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"

namespace OHOS::Ace::NG {
void MenuWrapperPattern::OnAttachToFrameNodeMultiThread()
{
    // nothing, thread unsafe
}

void MenuWrapperPattern::OnAttachToMainTreeMultiThread()
{
    RegisterOnTouch();
    RegisterDetachCallback();
}

void MenuWrapperPattern::OnDetachFromMainTreeMultiThread()
{
    OnDetachFromMainTreeImpl();
}

void MenuWrapperPattern::SetMenuTransitionEffectMultiThread(
    const RefPtr<FrameNode>& frameNode, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = WeakClaim(RawPtr(frameNode)), menuParam]() {
        auto menuWrapperNode = weak.Upgrade();
        CHECK_NULL_VOID(menuWrapperNode);
        auto pattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetMenuTransitionEffectImpl(menuWrapperNode, menuParam);
    });
}
} // namespace OHOS::Ace::NG
