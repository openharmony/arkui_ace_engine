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
#ifndef MOCK_WINDOW_EXTENSION_CONNECTION_ADAPTER_NG_H
#define MOCK_WINDOW_EXTENSION_CONNECTION_ADAPTER_NG_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "core/common/window_ng/window_extension_connection_adapter_ng.h"

namespace OHOS::Ace {
class MockWindowExtensionConnectionAdapterNG : public WindowExtensionConnectionAdapterNG {
public:
    MockWindowExtensionConnectionAdapterNG() = default;
    MOCK_METHOD0(Show, void());
    MOCK_METHOD0(Hide, void());
    MOCK_METHOD0(RequestFocus, void());
    MOCK_METHOD2(ConnectExtension, void(const RefPtr<NG::FrameNode>& node, int32_t windowId));
    MOCK_METHOD1(UpdateRect, void(const Rect& rect));
    MOCK_METHOD0(RemoveExtension, void());
};
} // namespace OHOS::Ace
#endif /* MOCK_WINDOW_EXTENSION_CONNECTION_ADAPTER_NG_H */