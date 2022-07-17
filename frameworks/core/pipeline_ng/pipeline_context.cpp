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
    : PipelineBase(std::move(window), std::move(taskExecutor), std::move(assetManager), frontend, instanceId)
{}

PipelineContext::PipelineContext(std::unique_ptr<Window> window, RefPtr<TaskExecutor> taskExecutor,
    RefPtr<AssetManager> assetManager, const RefPtr<Frontend>& frontend, int32_t instanceId)
    : PipelineBase(std::move(window), std::move(taskExecutor), std::move(assetManager), frontend, instanceId)
{}

void PipelineContext::AddDirtyComposedNode(const RefPtr<CustomNode>& dirtyElement)
{
    CHECK_RUN_ON(UI);
    if (!dirtyElement) {
        LOGW("dirtyElement is null");
        return;
    }
    dirtyComposedNodes_.emplace(dirtyElement);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::FlushVsync(uint64_t nanoTimestamp, uint32_t frameCount)
{
    CHECK_RUN_ON(UI);
    ACE_FUNCTION_TRACE();
    static const std::string abilityName = AceApplicationInfo::GetInstance().GetProcessName().empty()
                                               ? AceApplicationInfo::GetInstance().GetPackageName()
                                               : AceApplicationInfo::GetInstance().GetProcessName();
    window_->RecordFrameTime(nanoTimestamp, abilityName);
    FlushAnimation(GetTimeFromExternalTimer());
    FlushPipelineWithoutAnimation();
}

void PipelineContext::FlushMessages()
{
    ACE_FUNCTION_TRACE();
    window_->FlushTasks();
}

void PipelineContext::FlushPipelineWithoutAnimation()
{
    FlushTouchEvents();
    UITaskScheduler::GetInstance()->FlushTask();
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
    rootNode_->FlushStateModifyTaskOnCreate(modifyTask);
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
    UpdateRootSizeAndSacle(width, height);
    if (!rootNode_) {
        LOGE("rootNode_ is nullptr");
        return;
    }
    LOGI("SetRootRect %{public}f %{public}f", width, height);
    SizeF sizeF { static_cast<float>(width), static_cast<float>(height) };
    if (rootNode_->GetGeometryNode()->GetFrameSize() != sizeF) {
        CalcSize idealSize { CalcLength(width), CalcLength(height) };
        MeasureProperty layoutConstraint;
        layoutConstraint.selfIdealSize = idealSize;
        layoutConstraint.maxSize = idealSize;
        rootNode_->UpdateLayoutConstraint(layoutConstraint);
        rootNode_->MarkDirtyNode();
        UITaskScheduler::GetInstance()->FlushLayoutTask(false, true);
    }
}

void PipelineContext::OnTouchEvent(const TouchEvent& point, bool isSubPipe)
{
    CHECK_RUN_ON(UI);
    touchEvents_.emplace_back(point);
    hasIdleTasks_ = true;
    window_->RequestFrame();
}

void PipelineContext::OnSurfaceDensityChanged(double density)
{
    CHECK_RUN_ON(UI);
    LOGI("OnSurfaceDensityChanged density_(%{public}lf)", density_);
    LOGI("OnSurfaceDensityChanged dipScale_(%{public}lf)", dipScale_);
    density_ = density;
    if (!NearZero(viewScale_)) {
        LOGI("OnSurfaceDensityChanged viewScale_(%{public}lf)", viewScale_);
        dipScale_ = density_ / viewScale_;
    }
}

void PipelineContext::FlushTouchEvents()
{
    CHECK_RUN_ON(UI);
    if (!rootNode_) {
        LOGE("root node is nullptr");
        return;
    }
    {
        ACE_SCOPED_TRACE("PipelineContext::DispatchTouchEvent");
        decltype(touchEvents_) touchEvents(std::move(touchEvents_));
        for (const auto& touchEvent : touchEvents) {
            auto scalePoint = touchEvent.CreateScalePoint(GetViewScale());
            LOGD("AceTouchEvent: x = %{public}f, y = %{public}f, type = %{public}zu", scalePoint.x, scalePoint.y,
                scalePoint.type);
            if (scalePoint.type == TouchType::DOWN) {
                LOGD("receive touch down event, first use touch test to collect touch event target");
                TouchRestrict touchRestrict { TouchRestrict::NONE };
                touchRestrict.sourceType = touchEvent.sourceType;
                eventManager_->TouchTest(scalePoint, rootNode_, touchRestrict, false);
            }
            eventManager_->DispatchTouchEvent(scalePoint);
        }
    }
}

} // namespace OHOS::Ace::NG
