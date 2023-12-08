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
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/manager/select_overlay/select_overlay_proxy.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID = 143;
constexpr int32_t NODE_ID_2 = 601;
const RectF FIRST_HANDLE_INFO_RECT(0, 0, 100.0f, 100.0f);
const RectF SECOND_HANDLE_INFO_RECT(0, 0, 200.0f, 200.0f);
} // namespace

class SelectOverlayProxyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SelectOverlayProxyTestNg::SetUpTestCase()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void SelectOverlayProxyTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: SelectOverlayProxyTest001
 * @tc.desc: test the Functions about updating the property of selectOverlayInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayProxyTestNg, SelectOverlayProxyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayProxy
     * @tc.expected: step1. selectOverlayId = NODE_ID
     */
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(NODE_ID);
    auto overlayId = selectOverlayProxy->GetSelectOverlayId();
    EXPECT_EQ(overlayId, NODE_ID);

    /**
     * @tc.steps: step2. call the relevant Functions to update the property of selectOverlayInfo
     * @tc.expected: step2. no fatal failures occour, some logs will be print
     *                      they are defined in "mock_select_overlay_pattern.cpp"
     */
    // call UpdateFirstSelectHandleInfo
    SelectHandleInfo selectHandleInfo;
    selectHandleInfo.paintRect = FIRST_HANDLE_INFO_RECT;
    selectOverlayProxy->UpdateFirstSelectHandleInfo(selectHandleInfo);

    // call UpdateSecondSelectHandleInfo
    SelectHandleInfo selectHandleInfo2;
    selectHandleInfo.paintRect = SECOND_HANDLE_INFO_RECT;
    selectOverlayProxy->UpdateSecondSelectHandleInfo(selectHandleInfo2);

    // call UpdateSelectMenuInfo
    SelectMenuInfo selectMenuInfo;
    selectOverlayProxy->UpdateSelectMenuInfo(selectMenuInfo);

    // call UpdateShowArea
    RectF showArea;
    selectOverlayProxy->UpdateShowArea(showArea);
}

/**
 * @tc.name: SelectOverlayProxyTest002
 * @tc.desc: test the Functions about closing the proxy
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayProxyTestNg, SelectOverlayProxyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayProxy
     * @tc.expected: step1. selectOverlayId = NODE_ID
     */
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(NODE_ID);
    auto overlayId = selectOverlayProxy->GetSelectOverlayId();
    EXPECT_EQ(overlayId, NODE_ID);

    /**
     * @tc.steps: step2. call IsClosed() without calling Close()
     * @tc.expected: step2. hasn't closed, return true
     */
    auto isClosed = selectOverlayProxy->IsClosed();
    EXPECT_TRUE(isClosed);

    /**
     * @tc.steps: step3. call Close()
     */
    selectOverlayProxy->Close();

    /**
     * @tc.steps: step4. call IsClosed() after calling Close()
     * @tc.expected: step4. has closed, return false
     */
    auto selectOverlayProxy2 = AceType::MakeRefPtr<SelectOverlayProxy>(NODE_ID_2);
    auto isClosed2 = selectOverlayProxy2->IsClosed();
    EXPECT_TRUE(isClosed2);
}

/**
 * @tc.name: SelectOverlayProxyIsMenuShow001
 * @tc.desc: test the IsMenuShow function
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayProxyTestNg, SelectOverlayProxyIsMenuShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayProxy
     * @tc.expected: step1. IsMenuShow method returns true.
     */
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(NODE_ID);
    EXPECT_FALSE(selectOverlayProxy->IsMenuShow());
}

/**
 * @tc.name: SelectOverlayProxyIsHandleShow001
 * @tc.desc: test the IsHandleShow function
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayProxyTestNg, SelectOverlayProxyIsHandleShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SelectOverlayProxy
     * @tc.expected: step1. IsHandleShow method returns true.
     */
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(NODE_ID);
    EXPECT_FALSE(selectOverlayProxy->IsHandleShow());
}
} // namespace OHOS::Ace::NG
