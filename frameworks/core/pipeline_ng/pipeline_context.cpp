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

#include "core/pipeline_ng/pipeline_context.h"

#include <memory>

#include "base/log/ace_trace.h"
#include "base/log/ace_tracker.h"
#include "base/log/event_report.h"
#include "base/log/frame_report.h"
#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "core/common/ace_application_info.h"
#include "core/common/thread_checker.h"
#include "core/common/window.h"
#include "core/components_ng/base/custom_node.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/modifier/modify_task.h"
#include "core/components_ng/modifier/render/bg_color_modifier.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

PipelineContext::PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, RefPtr<PlatformResRegister> platformResRegister,
    const RefPtr<Frontend>& frontend, int32_t instanceId)
    : V1::PipelineContext(std::move(window), std::move(taskExecutor), std::move(assetManager),
          std::move(platformResRegister), frontend, instanceId)
{}
PipelineContext::PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor>& taskExecutor,
    RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend)
    : V1::PipelineContext(std::move(window), taskExecutor, std::move(assetManager), frontend)
{}

void PipelineContext::AddDirtyComposedNode(const RefPtr<CustomNode>& dirtyElement)
{
    CHECK_RUN_ON(JS);
    if (!dirtyElement) {
        LOGW("dirtyElement is null");
        return;
    }
    dirtyComposedNodes_.emplace(dirtyElement);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::AddDirtyRenderTree(const RefPtr<FrameNode>& dirtyNode)
{
    CHECK_RUN_ON(UI);
    if (!dirtyNode) {
        LOGW("dirtyNode is null");
        return;
    }
    dirtyRenderTree_.emplace(dirtyNode);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::BuildDirtyElement()
{
    auto task = [weak = WeakClaim(this)]() {
        auto context = weak.Upgrade();
        if (!context) {
            return;
        }
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().BeginFlushBuild();
        }
        if (!context->dirtyComposedNodes_.empty()) {
            LOGI("flush build dirty node");
            decltype(dirtyComposedNodes_) dirtyElements(std::move(context->dirtyComposedNodes_));
            for (const auto& elementWeak : dirtyElements) {
                auto element = elementWeak.Upgrade();
                // maybe unavailable when update parent
                if (element) {
                    element->Rebuild();
                }
            }
            UiTaskScheduler::GetInstance()->FlushTask();
        }
        if (FrameReport::GetInstance().GetEnable()) {
            FrameReport::GetInstance().EndFlushBuild();
        }
    };
    PostAsyncEvent(std::move(task), TaskExecutor::TaskType::JS);
}

void PipelineContext::FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACK();
    static const std::string abilityName = AceApplicationInfo::GetInstance().GetProcessName().empty()
                                               ? AceApplicationInfo::GetInstance().GetPackageName()
                                               : AceApplicationInfo::GetInstance().GetProcessName();
    window_->RecordFrameTime(nanoTimestamp, abilityName);
    FlushPipelineWithoutAnimation();
}

void PipelineContext::FlushMessages()
{
    ACE_FUNCTION_TRACK();
    window_->FlushTasks();
}

void PipelineContext::FlushPipelineWithoutAnimation()
{
    BuildDirtyElement();
    ClearDeactivateElements();
    FlushMessages();
}

void PipelineContext::SetupRootElement()
{
    CHECK_RUN_ON(UI);
    // TODO: Add unique id.
    rootNode_ =
        FrameNode::CreateFrameNodeWithTree(V2::ROOT_ETS_TAG, V2::ROOT_ETS_TAG, MakeRefPtr<StagePattern>(), Claim(this));
    rootNode_->SetHostRootId(GetInstanceId());
    StateModifyTask modifyTask;
    modifyTask.GetRenderContextTask().emplace_back(BgColorModifier(Color::WHITE));
    rootNode_->FlushModifyTaskOnCreate(modifyTask);
    CalcSize idealSize { CalcLength(rootWidth_), CalcLength(rootHeight_) };
    MeasureProperty layoutConstraint;
    layoutConstraint.selfIdealSize = idealSize;
    layoutConstraint.maxSize = idealSize;
    rootNode_->UpdateLayoutConstraint(layoutConstraint);
    window_->SetRootFrameNode(rootNode_);
    stageManager_ = MakeRefPtr<StageManager>(rootNode_);
    LOGI("SetupRootElement success!");
}

RefPtr<StageManager> PipelineContext::GetStageManager()
{
    return stageManager_;
}

void PipelineContext::SetRootRect(double width, double height, double offset)
{
    CHECK_RUN_ON(UI);
    if (!rootNode_) {
        LOGE("rootNode_ is nullptr");
        return;
    }
    LOGI("SetRootRect %{public}f %{public}f", width, height);
    auto jsTask = [width, height, rootNode = rootNode_]() {
        SizeF sizeF { static_cast<float>(width), static_cast<float>(height) };
        if (rootNode->GetGeometryNode()->GetFrameSize() != sizeF) {
            CalcSize idealSize { CalcLength(width), CalcLength(height) };
            MeasureProperty layoutConstraint;
            layoutConstraint.selfIdealSize = idealSize;
            layoutConstraint.maxSize = idealSize;
            rootNode->UpdateLayoutConstraint(layoutConstraint);
            (*rootNode->CreateLayoutTask())();
        }
    };
    PostAsyncEvent(std::move(jsTask), TaskExecutor::TaskType::JS);
}

} // namespace OHOS::Ace::NG
