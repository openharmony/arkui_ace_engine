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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_H

#include <functional>
#include <string>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"

namespace OHOS::Ace::NG {
// CustomNode is the frame node of @Component struct.
class ACE_EXPORT CustomNode : public FrameNode {
    DECLARE_ACE_TYPE(CustomNode, FrameNode);

public:
    static RefPtr<CustomNode> CreateCustomNode(int32_t nodeId, const std::string& viewKey);

    CustomNode(int32_t nodeId, const std::string& viewKey);
    ~CustomNode() override;

    void SetRenderFunction(const RenderFunction& renderFunction)
    {
        auto pattern = DynamicCast<CustomNodePattern>(GetPattern());
        if (pattern) {
            pattern->SetRenderFunction(renderFunction);
        }
    }

    void FireOnAppear() const
    {
        if (appearFunc_) {
            appearFunc_();
        }
    }

    void SetAppearFunction(std::function<void()>&& appearFunc)
    {
        appearFunc_ = std::move(appearFunc);
    }

    void SetUpdateFunction(std::function<void()>&& updateFunc)
    {
        updateFunc_ = std::move(updateFunc);
    }

    void SetDestroyFunction(std::function<void()>&& destroyFunc)
    {
        destroyFunc_ = std::move(destroyFunc);
    }

    // called by view in js thread
    void MarkNeedUpdate();

    // called by pipeline in js thread of update.
    void Update();

private:
    std::function<void()> updateFunc_;
    std::function<void()> appearFunc_;
    std::function<void()> destroyFunc_;
    std::string viewKey_;
    bool needRebuild_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_H
