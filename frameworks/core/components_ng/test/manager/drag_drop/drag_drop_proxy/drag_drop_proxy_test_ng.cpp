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
#include <optional>

#include "gtest/gtest.h"

#define private public

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "frameworks/core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int64_t PROXY_ID = 1;
constexpr int64_t PROXY_ID_NOT_FIT = 101;
const std::string GET_EXTRA("GetExtraInfoFromClipboard");
const std::string NODE_TAG("custom_node");
const std::string EXTRA_INFO_DRAG_START("drag_start_info");
} // namespace

class DragDropProxyTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

protected:
};

/**
 * @tc.name: DragDropProxyTest001
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call onDragStart
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnDragStart() & AddDataToClipboard() will not be called
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    GestureEvent info;
    proxyUnFitted->OnDragStart(info, EXTRA_INFO_DRAG_START, frameNode);

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call onDragStart
     * @tc.expected: step4. DragDropManager->OnDragStart() & AddDataToClipboard() will be called
     *                      some logs will be print
     *                      they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->OnDragStart(info, EXTRA_INFO_DRAG_START, frameNode);
}

/**
 * @tc.name: DragDropProxyTest002
 * @tc.desc: Test OnDragMove
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call OnDragMove
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnDragMove() & GetExtraInfoFromClipboard() will not be called
     */
    GestureEvent info;
    proxyUnFitted->OnDragMove(info);

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call OnDragMove
     * @tc.expected: step4. DragDropManager->OnDragMove() & GetExtraInfoFromClipboard() will be called
     *                      some logs will be print
     *                      they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->OnDragMove(info);
}

/**
 * @tc.name: DragDropProxyTest003
 * @tc.desc: Test OnDragEnd
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call OnDragEnd
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->OnDragEnd() & GetExtraInfoFromClipboard() &
     *                      RestoreClipboardData() will not be called
     */
    GestureEvent info;
    proxyUnFitted->OnDragEnd(info);

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call OnDragEnd
     * @tc.expected: step4. DragDropManager->OnDragEnd() & GetExtraInfoFromClipboard() &
     *                      RestoreClipboardData() will be called
     *                      some logs will be print they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->OnDragEnd(info);
}

/**
 * @tc.name: DragDropProxyTest004
 * @tc.desc: Test onDragCancel
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragDropProxyTestNg, DragDropProxyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a DragDropProxy with unfitted proxyId
     * @tc.expected: step1. id_ = PROXY_ID_NOT_FIT
     */
    auto proxyUnFitted = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID_NOT_FIT);
    EXPECT_EQ(proxyUnFitted->id_, PROXY_ID_NOT_FIT);

    /**
     * @tc.steps: step2. call onDragCancel
     * @tc.expected: step2. no fatal errors happended
     *                      DragDropManager->onDragCancel() will not be called
     */
    proxyUnFitted->onDragCancel();

    /**
     * @tc.steps: step3. construct a DragDropProxy with fitted proxyId
     * @tc.expected: step3. id_ = PROXY_ID
     */
    auto proxy = AceType::MakeRefPtr<DragDropProxy>(PROXY_ID);
    EXPECT_EQ(proxy->id_, PROXY_ID);

    /**
     * @tc.steps: step4. call onDragCancel
     * @tc.expected: step4. DragDropManager->onDragCancel() will be called
     *                      some logs will be print they are defined in "mock_drag_drop_manager.cpp"
     */
    proxy->onDragCancel();
}
} // namespace OHOS::Ace::NG
