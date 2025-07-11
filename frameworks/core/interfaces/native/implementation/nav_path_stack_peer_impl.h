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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_NAV_PATH_STACK_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_NAV_PATH_STACK_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "navigation_context.h"

using OHOS::Ace::AceType;
using OHOS::Ace::RefPtr;
using OHOS::Ace::WeakPtr;
namespace Nav = OHOS::Ace::NG::GeneratedModifier::NavigationContext;

struct NavPathStackPeer {
public:
    NavPathStackPeer(): navStack_(nullptr)
    {
        auto* stack = new Nav::NavigationStack();
        navStack_ = AceType::Claim(stack);
    }

    void SetNavigationStack(const RefPtr<AceType>& stack)
    {
        navStack_ = nullptr;
        CHECK_NULL_VOID(stack);
        auto navStack = AceType::DynamicCast<Nav::NavigationStack>(stack);
        CHECK_NULL_VOID(navStack);
        navStack_ = navStack;
    }

    void SetInstanceId(int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    RefPtr<Nav::NavigationStack> GetNavPathStack() const
    {
        return navStack_;
    }

protected:
    RefPtr<Nav::NavigationStack> navStack_;
    int32_t instanceId_ = OHOS::Ace::INSTANCE_ID_UNDEFINED;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_NAV_PATH_STACK_PEER_IMPL_H
