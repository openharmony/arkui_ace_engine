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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_PIPELINE_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_PIPELINE_BASE_H

#include "gmock/gmock.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class MockPipelineBase : public PipelineContext {
    DECLARE_ACE_TYPE(MockPipelineBase, PipelineContext);

public:
    MockPipelineBase() = default;
    ~MockPipelineBase() override = default;

    static void SetUp();
    static void TearDown();
    static RefPtr<MockPipelineBase> GetCurrent();
    void SetRootSize(double rootWidth, double rootHeight);

    MOCK_METHOD0(SetupRootElement, void());
    MOCK_METHOD3(
        AddKeyFrame, void(float fraction, const RefPtr<Curve>& curve, const std::function<void()>& propertyCallback));
    MOCK_METHOD2(AddKeyFrame, void(float fraction, const std::function<void()>& propertyCallback));
    MOCK_METHOD1(AddScheduleTask, uint32_t(const RefPtr<ScheduleTask>& task));
    MOCK_METHOD1(RemoveScheduleTask, void(uint32_t id));
    MOCK_METHOD2(OnTouchEvent, void(const TouchEvent& point, bool isSubPipe));
    MOCK_METHOD1(OnKeyEvent, bool(const KeyEvent& event));
    MOCK_METHOD1(OnMouseEvent, void(const MouseEvent& event));
    MOCK_METHOD1(OnAxisEvent, void(const AxisEvent& event));
    MOCK_CONST_METHOD1(OnRotationEvent, bool(const RotationEvent& event));
    MOCK_METHOD3(OnDragEvent, void(int32_t x, int32_t y, DragEventAction action));
    MOCK_METHOD1(OnIdle, void(int64_t deadline));
    MOCK_METHOD1(SetBuildAfterCallback, void(const std::function<void()>& callback));
    MOCK_METHOD1(FlushAnimation, void(uint64_t nanoTimestamp));
    MOCK_METHOD1(SaveExplicitAnimationOption, void(const AnimationOption& option));
    MOCK_METHOD1(CreateExplicitAnimator, void(const std::function<void()>& onFinishEvent));
    MOCK_METHOD0(ClearExplicitAnimationOption, void());
    MOCK_CONST_METHOD0(GetExplicitAnimationOption, AnimationOption());
    MOCK_METHOD0(Destroy, void());
    MOCK_METHOD0(OnShow, void());
    MOCK_METHOD0(OnHide, void());
    MOCK_METHOD1(WindowFocus, void(bool isFocus));
    MOCK_METHOD2(ShowContainerTitle, void(bool isShow, bool hasDeco));
    MOCK_METHOD4(OnSurfaceChanged, void(int32_t width, int32_t height, WindowSizeChangeReason type,
                                       const std::shared_ptr<Rosen::RSTransaction>& rsTransaction));
    MOCK_METHOD2(OnSurfacePositionChanged, void(int32_t posX, int32_t posY));
    MOCK_METHOD1(OnSurfaceDensityChanged, void(double density));
    MOCK_METHOD2(OnSystemBarHeightChanged, void(double statusBar, double navigationBar));
    MOCK_METHOD0(OnSurfaceDestroyed, void());
    MOCK_METHOD0(NotifyOnPreDraw, void());
    MOCK_METHOD0(CallRouterBackToPopPage, bool());
    MOCK_METHOD0(OnPageShow, void());
    MOCK_CONST_METHOD1(Finish, void(bool autoFinish));
    MOCK_METHOD1(RequestFullWindow, void(int32_t duration));
    MOCK_METHOD1(RequestFocus, bool(const std::string& targetNodeId));
    MOCK_METHOD0(IsLastPage, bool());
    MOCK_CONST_METHOD0(GetIsDeclarative, bool());
    MOCK_METHOD1(SetAppBgColor, void(const Color& color));
    MOCK_METHOD1(SetAppTitle, void(const std::string& title));
    MOCK_METHOD1(SetAppIcon, void(const RefPtr<PixelMap>& icon));
    MOCK_CONST_METHOD0(RefreshRootBgColor, void());
    MOCK_METHOD0(PostponePageTransition, void());
    MOCK_METHOD0(LaunchPageTransition, void());
    MOCK_METHOD2(GetBoundingRectData, void(int32_t nodeId, Rect& rect));
    MOCK_METHOD0(FlushReload, void());
    MOCK_METHOD0(FlushBuild, void());
    MOCK_METHOD0(FlushReloadTransition, void());
    MOCK_METHOD1(NotifyMemoryLevel, void(int32_t level));
    MOCK_METHOD0(FlushMessages, void());
    MOCK_METHOD0(FlushUITasks, void());
    MOCK_CONST_METHOD1(OnDumpInfo, bool(const std::vector<std::string>& params));
    MOCK_METHOD2(FlushVsync, void(uint64_t nanoTimestamp, uint32_t frameCount));
    MOCK_METHOD3(SetRootRect, void(double width, double height, double offset));
    MOCK_METHOD0(FlushPipelineWithoutAnimation, void());
    MOCK_METHOD0(FlushPipelineImmediately, void());
    MOCK_METHOD2(OnVirtualKeyboardHeightChange,
        void(float keyboardHeight, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction));
    MOCK_METHOD1(SetContainerWindow, void(bool isShow));
    MOCK_METHOD1(SetTouchPipeline, void(const WeakPtr<PipelineBase>& context));
    MOCK_METHOD2(AddEtsCardTouchEventCallback, void(int32_t ponitId, EtsCardTouchEventCallback&& callback));
    MOCK_METHOD1(RestoreNodeInfo, void(std::unique_ptr<JsonValue> nodeInfo));
    MOCK_METHOD0(GetStoredNodeInfo, std::unique_ptr<JsonValue>());
    MOCK_METHOD1(UpdateSystemSafeArea, void(const SafeAreaInsets& systemSafeArea));
    MOCK_CONST_METHOD0(GetSystemSafeArea, SafeAreaInsets());
    MOCK_METHOD1(UpdateCutoutSafeArea, void(const SafeAreaInsets& cutoutSafeArea));
    MOCK_CONST_METHOD0(GetCutoutSafeArea, SafeAreaInsets());
    MOCK_CONST_METHOD0(GetViewSafeArea, SafeAreaInsets());
    static RefPtr<MockPipelineBase> pipeline_;

protected:
    double dipScale_ = 1.0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_PIPELINE_BASE_H
