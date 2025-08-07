/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

 
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

#include "test/mock/core/common/mock_frontend.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "text_base.h"

#include "ui/base/geometry/dimension.h"

namespace OHOS::Ace::NG {
 
class TextArkoalaTest : public TextBases {
public:
    static RefPtr<MockFrontend> frontend_;

    static void SetUpTestSuite()
    {
        TextBases::SetUpTestSuite();
        auto pipeline = PipelineContext::GetCurrentContext();
        ASSERT_TRUE(pipeline);
        // set up pipeline's frontendType_
        pipeline->frontendType_ = FrontendType::ARK_TS;
    }
};
 
/**
 * @tc.name: TextArkoalaTest test GetSelectedBackgroundColor001
 * @tc.desc: Test GetSelectedBackgroundColor when GetHost is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextArkoalaTest, GetSelectedBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create.
     * @tc.expected: exam ContentValue of textLayoutProperty
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);
 
    /**
     * @tc.steps: step2. set theme.
     * @tc.expected: exam SelectedBackgroundColor of textModelNG
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    EXPECT_EQ(textModelNG.GetSelectedBackgroundColor(frameNode), Color::BLACK);
 
    /**
     * @tc.steps: step3. SetFont.
     * @tc.expected: exam GetFontSize of textModelNG
     */
    Font font;
    textModelNG.SetFont(font);
    EXPECT_EQ(textModelNG.GetFontSize(frameNode), ADAPT_ZERO_FONT_SIZE_VALUE);
}
} // namespace OHOS::Ace::NG