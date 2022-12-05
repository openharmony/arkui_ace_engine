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

#include "gmock/gmock-function-mocker.h"
#include "gmock/gmock.h"
#include "core/common/window.h"
#include "core/components/test/unittest/image/image_test_utils.h"

namespace OHOS::Ace::NG {
class MockWindow : public Window {
public:
    MockWindow() = default;
    MOCK_METHOD(void, RequestFrame, (), (override));
    MOCK_METHOD(void, Destroy, (), (override));
    MOCK_METHOD(void, SetRootRenderNode, (const RefPtr<RenderNode>& root), (override));
    MOCK_METHOD(void, RecordFrameTime, (uint64_t timeStamp, const std::string& name), (override));
    MOCK_METHOD(bool, FlushCustomAnimation, (uint64_t timeStamp), (override));
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_MOCK_MOCK_WINDOW_H
