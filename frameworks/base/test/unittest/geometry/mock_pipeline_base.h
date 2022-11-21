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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_UNITTEST_GEOMETRY_MOCK_PIPELINE_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_UNITTEST_GEOMETRY_MOCK_PIPELINE_BASE_H

#include "gmock/gmock.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
class FontManager : public AceType {
    DECLARE_ACE_TYPE(FontManager, AceType);
};

class ManagerInterface : public AceType {
    DECLARE_ACE_TYPE(ManagerInterface, AceType);
};

class MockPipelineBase final : public PipelineBase {
    DECLARE_ACE_TYPE(MockPipelineBase, PipelineBase);
public:
    MockPipelineBase() = default;
    ~MockPipelineBase() = default ;
    MOCK_METHOD(void, SetupRootElement, (), (override));
    MOCK_METHOD(void, AddKeyFrame, (float fraction, const RefPtr<Curve>& curve,
        const std::function<void()>& propertyCallback), (override));
    MOCK_METHOD(void, AddKeyFrame, (float fraction, const std::function<void()>& propertyCallback), (override));
    MOCK_METHOD(uint32_t, AddScheduleTask, (const RefPtr<ScheduleTask>& task), (override));
    MOCK_METHOD(void, RemoveScheduleTask, (uint32_t id), (override));
    MOCK_METHOD(void, OnTouchEvent, (const TouchEvent& point, bool isSubPipe), (override));
    MOCK_METHOD(bool, OnKeyEvent, (const KeyEvent& event), (override));
    MOCK_METHOD(void, OnMouseEvent, (const MouseEvent& event), (override));
    MOCK_METHOD(void, OnAxisEvent, (const AxisEvent& event), (override));
    MOCK_METHOD(bool, OnRotationEvent, (const RotationEvent& event), (const, override));
    MOCK_METHOD(void, OnDragEvent, (int32_t x, int32_t y, DragEventAction action), (override));
    MOCK_METHOD(void, OnIdle, (int64_t deadline), (override));
    MOCK_METHOD(void, SetBuildAfterCallback, (const std::function<void()>& callback), (override));
    MOCK_METHOD(void, FlushAnimation, (uint64_t nanoTimestamp), (override));
    MOCK_METHOD(void, SaveExplicitAnimationOption, (const AnimationOption& option), (override));
    MOCK_METHOD(void, CreateExplicitAnimator, (const std::function<void()>& onFinishEvent), (override));
    MOCK_METHOD(void, ClearExplicitAnimationOption, (), (override));
    MOCK_METHOD(AnimationOption, GetExplicitAnimationOption, (), (const, override));
    MOCK_METHOD(void, Destroy, (), (override));
    MOCK_METHOD(void, OnShow, (), (override));
    MOCK_METHOD(void, OnHide, (), (override));
    MOCK_METHOD(void, WindowFocus, (bool isFocus), (override));
    MOCK_METHOD(void, OnSurfaceChanged, (
        int32_t width, int32_t height, WindowSizeChangeReason type), (override));
    MOCK_METHOD(void, OnSurfacePositionChanged, (int32_t posX, int32_t posY), (override));
    MOCK_METHOD(void, OnSurfaceDensityChanged, (double density), (override));
    MOCK_METHOD(void, OnSystemBarHeightChanged, (double statusBar, double navigationBar), (override));
    MOCK_METHOD(void, OnSurfaceDestroyed, (), (override));
    MOCK_METHOD(void, NotifyOnPreDraw, (), (override));
    MOCK_METHOD(bool, CallRouterBackToPopPage, (), (override));
    MOCK_METHOD(void, FlushMessages, (), (override));
    MOCK_METHOD(void, FlushUITasks, (), (override));
    MOCK_METHOD(void, ShowContainerTitle, (bool isShow), (override));
    MOCK_METHOD(void, SetAppTitle, (const std::string& title), (override));
    MOCK_METHOD(void, SetAppIcon, (const RefPtr<PixelMap>& icon), (override));
    MOCK_METHOD(void, SetContainerWindow, (bool isShow), (override));

private:
    MOCK_METHOD(void, FlushVsync, (uint64_t nanoTimestamp, uint32_t frameCount), (override));
    MOCK_METHOD(void, SetRootRect, (double width, double height, double offset), (override));
    MOCK_METHOD(void, FlushPipelineWithoutAnimation, (), (override));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_UNITTEST_GEOMETRY_MOCK_PIPELINE_BASE_H
