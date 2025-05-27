/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENT_FORM_FORM_RENDER_WINDOW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENT_FORM_FORM_RENDER_WINDOW_H

#include <memory>

#ifdef ENABLE_ROSEN_BACKEND
#include <mutex>
#include "render_service_client/core/feature/hyper_graphic_manager/rs_frame_rate_linker.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include "vsync_receiver.h"
#endif

#include "base/thread/task_executor.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/common/window.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
class ACE_EXPORT FormRenderWindow : public Window {
public:
    using OnVsyncCallback = std::function<void(int64_t, int64_t, void*)>;
    explicit FormRenderWindow(RefPtr<TaskExecutor> taskExecutor, int32_t id);
    FormRenderWindow() = default;
    ~FormRenderWindow() = default;

    void RequestFrame() override;
    void Destroy() override;
    void SetRootRenderNode(const RefPtr<RenderNode>& root) override {}
    void SetRootFrameNode(const RefPtr<NG::FrameNode>& root) override;
    void FlushFrameRate(int32_t rate, int32_t animatorExpectedFrameRate, int32_t rateType) override;

#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<OHOS::Rosen::RSUIDirector> GetRsUIDirector() const
    {
        return rsUIDirector_;
    }

    std::shared_ptr<Rosen::RSSurfaceNode> GetRSSurfaceNode() const
    {
        return rsSurfaceNode_;
    }

    bool FlushAnimation(uint64_t timeStamp) override
    {
        CHECK_NULL_RETURN(rsUIDirector_, false);
        return rsUIDirector_->FlushAnimation(timeStamp);
    }

    bool HasFirstFrameAnimation() override
    {
        CHECK_NULL_RETURN(rsUIDirector_, false);
        return rsUIDirector_->HasFirstFrameAnimation();
    }

    void FlushAnimationStartTime(uint64_t timeStamp) override
    {
        CHECK_NULL_VOID(rsUIDirector_);
        rsUIDirector_->FlushAnimationStartTime(timeStamp);
    }

    void FlushModifier() override
    {
        CHECK_NULL_VOID(rsUIDirector_);
        rsUIDirector_->FlushModifier();
    }

    bool HasUIRunningAnimation() override
    {
        CHECK_NULL_RETURN(rsUIDirector_, false);
        return rsUIDirector_->HasUIRunningAnimation();
    }

    int32_t GetCurrentRefreshRateMode() const override
    {
        CHECK_NULL_RETURN(rsUIDirector_, -1);
        return rsUIDirector_->GetCurrentRefreshRateMode();
    }

    int32_t GetAnimateExpectedRate() const override
    {
        CHECK_NULL_RETURN(rsUIDirector_, 0);
        return rsUIDirector_->GetAnimateExpectedRate();
    }
#endif

    void OnShow() override;
    void OnHide() override;
    void FlushTasks(std::function<void()> callback = nullptr) override;

    void Lock() override;
    void Unlock() override;
    int64_t GetVSyncPeriod() const override;

private:
    WeakPtr<TaskExecutor> taskExecutor_ = nullptr;
    int32_t id_ = 0;
#ifdef ENABLE_ROSEN_BACKEND
    void InitOnVsyncCallback();
    static std::recursive_mutex globalMutex_;
    std::shared_ptr<Rosen::VSyncReceiver> receiver_ = nullptr;
    Rosen::VSyncReceiver::FrameCallback frameCallback_;
    OnVsyncCallback onVsyncCallback_;
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUIDirector_;
    std::shared_ptr<Rosen::RSSurfaceNode> rsSurfaceNode_;
    std::shared_ptr<Rosen::RSFrameRateLinker> frameRateLinker_ = nullptr;
    std::tuple<int32_t, int32_t, int32_t> frameRateData_{0, 0, 0};
#endif
    ACE_DISALLOW_COPY_AND_MOVE(FormRenderWindow);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENT_FORM_FORM_RENDER_WINDOW_H
