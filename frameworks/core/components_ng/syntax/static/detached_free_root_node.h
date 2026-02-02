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
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {
class DetachedFreeRootNode : public UINode {
    DECLARE_ACE_TYPE(DetachedFreeRootNode, UINode);
    ACE_DISALLOW_COPY_AND_MOVE(DetachedFreeRootNode);

public:
    explicit DetachedFreeRootNode(int32_t nodeId) : UINode("DetachedFreeRoot", nodeId) {}

    bool IsAtomicNode() const override
    {
        return false;
    }
};

} // namespace OHOS::Ace::NG
