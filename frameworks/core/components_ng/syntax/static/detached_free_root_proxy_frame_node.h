/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/container.h"
#include "core/common/frontend.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
class DetachedFreeRootProxyFrameNode : public FrameNode {
    DECLARE_ACE_TYPE(DetachedFreeRootProxyFrameNode, FrameNode);
    ACE_DISALLOW_COPY_AND_MOVE(DetachedFreeRootProxyFrameNode);

public:
    explicit DetachedFreeRootProxyFrameNode(int32_t instanceId)
        : FrameNode(
              "DetachedFreeRootProxy", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>())
    {
        const auto& container = Container::GetContainer(instanceId);
        CHECK_NULL_VOID(container);
        frontend_ = container->GetFrontend();
    }

    ~DetachedFreeRootProxyFrameNode() override
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
    WeakPtr<Frontend> frontend_;
};

} // namespace OHOS::Ace::NG
