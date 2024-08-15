/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/focus_box.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const std::string RESULT_SUCCESS_ONE = "sucess1";
const std::string RESULT_SUCCESS_TWO = "sucess2";
} // namespace

class FocusBoxTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};
} // namespace OHOS::Ace::NG

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void FocusBoxTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void FocusBoxTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void FocusBoxTestNg::SetUp() {}

void FocusBoxTestNg::TearDown() {}

/**
 * @tc.name: FocusBoxTest001
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest001, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    NG::FocusBoxStyle style;
    style.margin = 1.0f;
    style.strokeWidth = 1.0f;

    focusBox->SetStyle(style);

    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}

/**
 * @tc.name: FocusBoxTest002
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest002, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    NG::FocusBoxStyle style;
    style.margin = 1.0f;
    style.strokeWidth = -1.0f;

    focusBox->SetStyle(style);

    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}

/**
 * @tc.name: FocusBoxTest003
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest003, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    NG::FocusBoxStyle style;

    focusBox->SetStyle(style);

    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}

/**
 * @tc.name: FocusBoxTest004
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest004, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    NG::FocusBoxStyle style;
    style.margin = 1.0f;

    focusBox->SetStyle(style);

    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}

/**
 * @tc.name: FocusBoxTest005
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest005, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    NG::FocusBoxStyle style;
    style.strokeColor = Color::WHITE;
    focusBox->SetStyle(style);

    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}

/**
 * @tc.name: FocusBoxTest006
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest006, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    NG::FocusBoxStyle style;
    style.strokeWidth = 0.0f;
    focusBox->SetStyle(style);
    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}

/**
 * @tc.name: FocusBoxTest007
 * @tc.desc: Create ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest007, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    NG::FocusBoxStyle style;
    style.strokeColor = Color::WHITE;
    style.margin = 1.0f;
    style.strokeWidth = 1.0f;
    focusBox->SetStyle(style);
    focusBox->ToJsonValue(*focusBox);
    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}

/**
 * @tc.name: FocusBoxTest008
 * @tc.desc: Create ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest008, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    NG::FocusBoxStyle style;
    style.strokeColor = Color::WHITE;
    focusBox->SetStyle(style);
    focusBox->ToJsonValue(*focusBox);
    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}

/**
 * @tc.name: FocusBoxTest009
 * @tc.desc: Create ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest009, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    NG::FocusBoxStyle style;
    style.strokeWidth = 1.0f;
    focusBox->SetStyle(style);
    focusBox->ToJsonValue(*focusBox);
    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}

/**
 * @tc.name: FocusBoxTest010
 * @tc.desc: Create ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(FocusBoxTestNg, FocusBoxTest010, TestSize.Level1)
{
    auto focusBox = AceType::MakeRefPtr<FocusBox>();
    focusBox->ToJsonValue(*focusBox);
    EXPECT_EQ(RESULT_SUCCESS_ONE, "sucess1");
}
} // namespace OHOS::Ace::NG
