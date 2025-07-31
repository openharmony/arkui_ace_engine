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

#pragma once

#include <cstdint>

#include "ui/base/ace_type.h"
#include "ui/base/noncopyable.h"
#include "ui/base/referenced.h"
#include "ui/base/utils/utils.h"

#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/common/container.h"
#include "core/components_ng/base/ui_node.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
class DetachedFreeRootProxyNode : public UINode {
    DECLARE_ACE_TYPE(DetachedFreeRootProxyNode, UINode);
    ACE_DISALLOW_COPY_AND_MOVE(DetachedFreeRootProxyNode);

public:
    explicit DetachedFreeRootProxyNode(int32_t instanceId)
        : UINode("DetachedFreeRootProxy", ElementRegister::UndefinedElementId)
    {
        const auto& container = Container::GetContainer(instanceId);
        CHECK_NULL_VOID(container);
        frontend_ = AceType::DynamicCast<ArktsFrontend>(container->GetFrontend());
    }

    ~DetachedFreeRootProxyNode() override
    {
        const auto& builderNode = GetFirstChild();
        CHECK_NULL_VOID(builderNode);
        auto frontEnd = frontend_.Upgrade();
        CHECK_NULL_VOID(frontEnd);
        constexpr int32_t removeFlag = 1;
        frontEnd->HandleMessage(RawPtr(builderNode), removeFlag, "");
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

private:
    WeakPtr<ArktsFrontend> frontend_;
};

} // namespace OHOS::Ace::NG
