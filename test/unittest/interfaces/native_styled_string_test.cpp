/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include <cstring>
#include <iostream>
 
#include "gtest/gtest.h"
#define private public
#define protected public
#include "event_converter.h"
#include "native_interface.h"
#include "native_node.h"
#include "securec.h"
#include "gesture_impl.h"
#include "node_extened.h"
#include "node_model.h"
#include "span_style_native_impl.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "interfaces/native/node/event_converter.h"
#include "native_styled_string_descriptor.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "native_styled_string_descriptor.h"
 
using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
class NativeStyledStringTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};
 
/**
 * @tc.name: CreateTextStyle001
 * @tc.desc: Test the fontSize.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle001, TestSize.Level1)
{
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();
    auto errorCode = OH_ArkUI_TextStyle_SetFontSize(textStyle, 32.0f);
    EXPECT_EQ(textStyle->fontSize, 32.0f);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    float fontSize = 0;
    errorCode = OH_ArkUI_TextStyle_GetFontSize(textStyle, &fontSize);
    EXPECT_EQ(fontSize, 32.0f);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    textStyle->fontSize = 10.0f;
    errorCode = OH_ArkUI_TextStyle_GetFontSize(textStyle, &fontSize);
    EXPECT_EQ(fontSize, 10.0f);
    OH_ArkUI_TextStyle_Destroy(textStyle);
}
 
/**
 * @tc.name: CreateTextStyle002
 * @tc.desc: Test the fontColor.
 * @tc.type: FUNC
 */
HWTEST_F(NativeStyledStringTest, CreateTextStyle002, TestSize.Level1)
{
    OH_ArkUI_TextStyle *textStyle = OH_ArkUI_TextStyle_Create();
    auto errorCode = OH_ArkUI_TextStyle_SetFontColor(textStyle, 0xFFFF0000);
    EXPECT_EQ(textStyle->fontColor, 0xFFFF0000);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    uint32_t fontColor = 0;
    errorCode = OH_ArkUI_TextStyle_GetFontColor(textStyle, &fontColor);
    EXPECT_EQ(fontColor, 0xFFFF0000);
    EXPECT_EQ(errorCode, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    textStyle->fontColor = 0xFFFF0001;
    errorCode = OH_ArkUI_TextStyle_GetFontColor(textStyle, &fontColor);
    EXPECT_EQ(fontColor, 0xFFFF0001);
    OH_ArkUI_TextStyle_Destroy(textStyle);
}
} // namespace OHOS::Ace