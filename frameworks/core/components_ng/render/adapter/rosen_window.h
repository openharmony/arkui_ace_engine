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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_WINDOW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_WINDOW_H

#include "render_service_client/core/ui/rs_ui_director.h"

#ifdef OHOS_PLATFORM
#include "vsync_receiver.h"
#include "wm/window.h"
#elif VIRTUAL_RS_WINDOW
// use real rs window later
#ifdef IOS_PLATFORM
#include "adapter/ios/entrance/virtual_rs_window.h"
#else
#include "adapter/android/entrance/java/jni/virtual_rs_window.h"
#endif
#else
#include "previewer/include/window.h"
#endif

#include "base/thread/task_executor.h"
#include "base/utils/noncopyable.h"
#include "core/common/window.h"

namespace OHOS::Ace::NG {

class RosenWindow : public Window {
public:
    RosenWindow(const OHOS::sptr<OHOS::Rosen::Window>& window, RefPtr<TaskExecutor> taskExecutor, int32_t id);
    ~RosenWindow() override = default;

    void RequestFrame() override;

    void Init() override;

    void InitArkUI_X() override;

    void Destroy() override;

    void SetRootRenderNode(const RefPtr<RenderNode>& root) override {}

    void SetRootFrameNode(const RefPtr<NG::FrameNode>& root) override;

    void FlushFrameRate(int32_t rate, int32_t animatorExpectedFrameRate, int32_t rateType) override;

    std::shared_ptr<Rosen::RSUIDirector> GetRSUIDirector() const override
    {
        return rsUIDirector_;
    }

    sptr<Rosen::Window> GetRSWindow() const
    {
        return rsWindow_;
    }

    void RecordFrameTime(uint64_t timeStamp, const std::string& name) override;

    void FlushTasks(std::function<void()> callback = nullptr) override;

    void SetTaskRunner(RefPtr<TaskExecutor> taskExecutor, int32_t id);

    void FlushLayoutSize(int32_t width, int32_t height) override;

    bool FlushAnimation(uint64_t timeStamp) override
    {
        CHECK_NULL_RETURN(rsUIDirector_, false);
        int64_t vsyncPeriod = GetVSyncPeriod();
        return rsUIDirector_->FlushAnimation(timeStamp, vsyncPeriod);
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

    void OnShow() override;
    void OnHide() override;

    void SetDrawTextAsBitmap(bool useBitmap) override;

    float GetRefreshRate() const override;

    void SetKeepScreenOn(bool keepScreenOn) override;
    void SetViewKeepScreenOn(bool keepScreenOn) override;

    int64_t GetVSyncPeriod() const override;

    std::string GetWindowName() const override;

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

    void FlushImplicitTransaction(const std::shared_ptr<Rosen::RSUIDirector>& rsUIDirector);

    void OnVsync(uint64_t nanoTimestamp, uint32_t frameCount) override;
    
    void SetUiDvsyncSwitch(bool vsyncSwitch) override;

    uint32_t GetStatusBarHeight() const override;

    bool GetIsRequestVsync() override;

    void NotifyExtensionTimeout(int32_t errorCode) override;

    bool GetIsRequestFrame() override;

    void NotifySnapshotUpdate() override;

    void SetDVSyncUpdate(uint64_t dvsyncTime) override;
private:
    OHOS::sptr<OHOS::Rosen::Window> rsWindow_;
    WeakPtr<TaskExecutor> taskExecutor_;
    int32_t id_ = 0;
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUIDirector_;
    std::shared_ptr<OHOS::Rosen::VsyncCallback> vsyncCallback_;
    bool isFirstRequestVsync_ = true;
    bool directorFromWindow_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(RosenWindow);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_WINDOW_H
