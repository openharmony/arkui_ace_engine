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

#include <cstdint>
#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/components/panel/render_sliding_panel.h"
#include "core/components/panel/sliding_panel_component_v2.h"
#include "core/components/test/json/json_frontend.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/mock/fake_task_executor.h"
#include "core/mock/mock_resource_register.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {

const int32_t HEIGHT_VALUE = 100;

} // namespace

class RenderSlidingPanelTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void RenderSlidingPanelTest::SetUpTestCase() {}
void RenderSlidingPanelTest::TearDownTestCase() {}
void RenderSlidingPanelTest::SetUp() {}
void RenderSlidingPanelTest::TearDown() {}

class MockRenderSlidingPanel final : public RenderSlidingPanel {
    DECLARE_ACE_TYPE(MockRenderSlidingPanel, RenderSlidingPanel);

public:
    MockRenderSlidingPanel() = default;
    ~MockRenderSlidingPanel() = default;

};

/**
 * @tc.name: RenderSlidingPanel001
 * @tc.desc: Test setting borders separately to sliding panel.
 * @tc.type: FUNC
 * @tc.require: issueI5MWS0
 */
HWTEST_F(RenderSlidingPanelTest, RenderSlidingPanel001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderSlidingPanelTest RenderSlidingPanel001 start";
    /**
     * @tc.steps: step1. Build a sliding panel component and set onHeightChange callback to it.
     */
    auto slidingPanel = AceType::MakeRefPtr<SlidingPanelComponentV2>();
    int32_t currentHeight = 0;
    auto onHeightChangeCallback = std::function<void(int32_t)>([&currentHeight](const int32_t height) {
        currentHeight = height;
    });
    slidingPanel->SetOnHeightChanged(onHeightChangeCallback);
    auto renderSlidingPanel = AceType::MakeRefPtr<MockRenderSlidingPanel>();
    renderSlidingPanel->Update(slidingPanel);
    auto callback = renderSlidingPanel->GetOnHeightChange();
    /**
     * @tc.steps: step2. Call onHeightCallback with a value and assert the value can be received correctly
     */
    callback(HEIGHT_VALUE);
    EXPECT_EQ(currentHeight, HEIGHT_VALUE);
    GTEST_LOG_(INFO) << "RenderSlidingPanelTest RenderSlidingPanel001 end";
}

} // namespace OHOS::Ace
