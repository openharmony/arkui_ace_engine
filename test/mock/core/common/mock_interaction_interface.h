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

#ifndef FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_INTERACTION_H
#define FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_INTERACTION_H

#include "gmock/gmock-function-mocker.h"
#include "gmock/gmock.h"

#include "base/memory/ace_type.h"
#include "core/common/interaction/interaction_interface.h"

namespace OHOS::Ace {
class MockInteractionInterface : public InteractionInterface {
    DECLARE_ACE_TYPE(MockInteractionInterface, InteractionInterface);

public:
    MOCK_METHOD(int32_t, UpdateShadowPic, (const ShadowInfoCore& shadowInfo), (override));

    MOCK_METHOD(int32_t, SetDragWindowVisible,
        (bool visible, const std::shared_ptr<Rosen::RSTransaction>& rSTransaction), (override));

    MOCK_METHOD(int32_t, SetMouseDragMonitorState, (bool state), (override));

    MOCK_METHOD(int32_t, UpdateDragStyle, (DragCursorStyleCore style, const int32_t eventId), (override));
    
    MOCK_METHOD(int32_t, UpdatePreviewStyle, (const PreviewStyle& previewStyle), (override));

    MOCK_METHOD(int32_t, UpdatePreviewStyleWithAnimation, (const PreviewStyle& previewStyle,
        const PreviewAnimation& animation), (override));

    MOCK_METHOD(int32_t, StopDrag, (DragDropRet result), (override));

    MOCK_METHOD(int32_t, GetUdKey, (std::string& udKey), (override));

    MOCK_METHOD(int32_t, GetShadowOffset, (ShadowOffsetData& shadowOffsetData), (override));

    MOCK_METHOD(int32_t, GetDragState, (DragState& dragState), (const, override));

    MOCK_METHOD(int32_t, GetDragSummary, ((std::map<std::string, int64_t>& summary)), (override));

    MOCK_METHOD(int32_t, GetDragExtraInfo, (std::string& extraInfo), (override));

    MOCK_METHOD(int32_t, EnterTextEditorArea, (bool enable), (override));

    MOCK_METHOD(int32_t, AddPrivilege, (), (override));

    int32_t RegisterCoordinationListener(std::function<void()> dragOutCallback) override
    {
        gDragOutCallback = dragOutCallback;
        return 1;
    }

    int32_t StartDrag(const DragDataCore& dragData, std::function<void(const OHOS::Ace::DragNotifyMsg&)> callback)
    {
        gDragData_ = dragData;
        return gStartDrag;
    }

    MOCK_METHOD(int32_t, UnRegisterCoordinationListener, (), (override));

    MOCK_METHOD(int32_t, SetDraggableState, (bool state), (override));

    MOCK_METHOD(int32_t, GetAppDragSwitchState, (bool& state), (override));

    MOCK_METHOD(void, SetDraggableStateAsync, (bool state, int64_t downTime), (override));

private:
    std::function<void()> gDragOutCallback = nullptr;
    int gStartDrag = 0;
    DragDataCore gDragData_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_INTERACTION_H