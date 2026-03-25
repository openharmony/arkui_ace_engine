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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_MOCK_MOCK_WINDOW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_MOCK_MOCK_WINDOW_H

#include "gmock/gmock.h"

#include "core/common/window.h"

namespace OHOS::Ace {
class ACE_EXPORT MockWindow : public Window {
public:
    MockWindow() = default;
    ~MockWindow() override = default;

    MOCK_METHOD0(RequestFrame, void());
    MOCK_METHOD0(Destroy, void());
    MOCK_METHOD0(Init, void());
    MOCK_METHOD0(OnShow, void());
    MOCK_METHOD0(OnHide, void());
    MOCK_METHOD1(FlushTasks, void(std::function<void()> callback));
    MOCK_METHOD0(FlushModifier, void());
    MOCK_CONST_METHOD0(GetRefreshRate, float());
    MOCK_CONST_METHOD0(GetCurrentWindowRect, Rect());
    MOCK_CONST_METHOD0(GetRSUIDirector, std::shared_ptr<Rosen::RSUIDirector>());
    MOCK_CONST_METHOD0(GetStatusBarHeight, uint32_t());
    MOCK_METHOD1(SetDrawTextAsBitmap, void(bool useBitmap));
    MOCK_METHOD1(SetRootFrameNode, void(const RefPtr<NG::FrameNode>& root));
    MOCK_METHOD1(SetInstanceId, void(int32_t instanceId));
    MOCK_METHOD1(SetTaskExecutor, void(const RefPtr<TaskExecutor>& taskExecutor));
    MOCK_METHOD1(SetVsyncCallback, void(AceVsyncCallback&& callback));
    MOCK_METHOD1(SetRootRenderNode, void(const RefPtr<RenderNode>& root));
    MOCK_METHOD1(FlushAnimation, bool(uint64_t timeStamp));
    MOCK_METHOD2(RecordFrameTime, void(uint64_t timeStamp, const std::string& name));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_MOCK_MOCK_WINDOW_H
