/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef MOCK_FROM_RENDERER_DISPATCHER_STUB_H
#define MOCK_FROM_RENDERER_DISPATCHER_STUB_H
#include <gmock/gmock.h>
#include "form_renderer_dispatcher_stub.h"

namespace OHOS {
namespace AppExecFwk {
class MockFormRendererDispatherStub : public Ace::FormRendererDispatcherStub {
public:
    MOCK_METHOD2(DispatchPointerEvent,
        void(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, Ace::SerializedGesture& serializedGesture));
    MOCK_METHOD1(SetAllowUpdate, void(bool allowUpdate));
    MOCK_METHOD5(DispatchSurfaceChangeEvent, void(float width, float height, uint32_t reason,
        const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, float borderWidth));
    MOCK_METHOD1(SetObscured, void(bool isObscured));
    MOCK_METHOD3(OnAccessibilityChildTreeRegister, void(uint32_t windowId, int32_t treeId, int64_t accessibilityId));
    MOCK_METHOD0(OnAccessibilityChildTreeDeregister, void());
    MOCK_METHOD2(
        OnAccessibilityDumpChildInfo, void(const std::vector<std::string>& params, std::vector<std::string>& info));
    MOCK_METHOD5(OnAccessibilityTransferHoverEvent,
        void(float pointX, float pointY, int32_t sourceType, int32_t eventType, int64_t timeMs));
    int SendRequest(uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option)
    {
        SendRequest_called = true;
        return 0;
    }
    bool SendRequest_called = false;
};
}  // namespace AppExecFwk
}  // namespace OHOS
#endif // MOCK_FROM_RENDERER_DISPATCHER_STUB_H