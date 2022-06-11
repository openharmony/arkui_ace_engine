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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_CONTEXT_H

#include <utility>

#include "core/components_ng/base/custom_node.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace V1 = ::OHOS::Ace;

class ACE_EXPORT PipelineContext final : public V1::PipelineContext {
    DECLARE_ACE_TYPE(NG::PipelineContext, PipelineContext);

public:
    PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
        RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
        const RefPtr<Frontend>& frontend, int32_t instanceId);
    PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor>& taskExecutor,
        RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend);

    ~PipelineContext() override = default;

    void AddDirtyComposedNode(const RefPtr<CustomNode>& dirtyElement);

    void SetupRootElement() override;

    void SetRootRect(double width, double height, double offset) override;

    RefPtr<StageManager> GetStageManager();

    void OnTouchEvent(const TouchEvent& point, bool isSubPipe = false) override;

protected:
    void FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount) override;
    void FlushPipelineWithoutAnimation() override;
    void FlushMessages() override;

private:
    void FlushTouchEvents();

    void BuildDirtyElement();

    template<typename T>
    struct NodeCompare {
        bool operator()(const T& nodeLeft, const T& nodeRight)
        {
            if (nodeLeft->GetDepth() < nodeRight->GetDepth()) {
                return true;
            }
            if (nodeLeft->GetDepth() == nodeRight->GetDepth()) {
                return nodeLeft < nodeRight;
            }
            return false;
        }
    };

    template<typename T>
    struct NodeCompareWeak {
        bool operator()(const T& nodeLeftWeak, const T& nodeRightWeak)
        {
            auto nodeLeft = nodeLeftWeak.Upgrade();
            auto nodeRight = nodeRightWeak.Upgrade();
            if (!nodeLeft || !nodeRight) {
                return false;
            }
            auto compare = NodeCompare<decltype(nodeLeft)>();
            return compare(nodeLeft, nodeRight);
        }
    };

    std::set<WeakPtr<CustomNode>, NodeCompareWeak<WeakPtr<CustomNode>>> dirtyComposedNodes_;
    std::list<TouchEvent> touchEvents_;

    RefPtr<FrameNode> rootNode_ = nullptr;
    RefPtr<StageManager> stageManager_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(PipelineContext);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_CONTEXT_H
