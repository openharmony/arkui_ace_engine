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

#include "gtest/gtest.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/components/text/rosen_render_text.h"
#include "core/pipeline/base/rosen_render_context.h"
#include "core/components/text/text_component.h"
#include "core/components/text_overlay/text_overlay_component.h"
#include "base/i18n/localization.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {

constexpr double RECT_WIDTH = 1080.0;
constexpr double RECT_HEIGHT = 2244.0;

} // namespace

class RenderTextTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
    void TestRTL(TextDirection direction, const std::string& data, TextAlign textAlign, bool isRosen);
};

void RenderTextTest::SetUpTestCase() {}
void RenderTextTest::TearDownTestCase() {}
void RenderTextTest::SetUp() {}
void RenderTextTest::TearDown() {}

void RenderTextTest::TestRTL(TextDirection direction, const std::string& data,
    TextAlign textAlign, bool isRosen)
{
    /**
     * @tc.steps: step1. construct TextComponent.
     */
    RefPtr<TextComponent> textComponent = AceType::MakeRefPtr<TextComponent>(data);
    textComponent->SetTextDirection(direction);

    /**
     * @tc.steps: step2. SetLocale.
    */
    Localization::GetInstance()->SetLocale("en", "US", "", "", "en-US");

    if (isRosen) {
        /**
         * @tc.steps: step3. construct RenderText and set property.
         */
        auto mockContext = MockRenderCommon::GetMockContext();
        RefPtr<RosenRenderText> renderText = AceType::MakeRefPtr<RosenRenderText>();
        renderText->Attach(mockContext);
        renderText->Update(textComponent);
        TextStyle textStyle;
        textStyle.SetTextAlign(TextAlign::START);
        renderText->SetTextStyle(textStyle);

        /**
         * @tc.steps: step4. PerformLayout.
         */
        LayoutParam layoutParam;
        layoutParam.SetMinSize(Size(0.0, 0.0));
        layoutParam.SetMaxSize(Size(RECT_WIDTH, RECT_HEIGHT));
        renderText->SetLayoutParam(layoutParam);
        renderText->PerformLayout();

        /**
         * @tc.steps: step5. Paint.
         */
        RefPtr<RosenRenderContext> rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
        auto renderNode = AceType::DynamicCast<RenderNode>(renderText);
        rosenRenderContext->Repaint(renderNode);
    }

    /**
     * @tc.expected: step6. The text direction is correct.
     */
    EXPECT_TRUE(textComponent->GetTextDirection() == direction);
}

class MockRenderText : public RenderText {
    DECLARE_ACE_TYPE(MockRenderText, RenderText);

public:
    MockRenderText() = default;
    ~MockRenderText() override = default;

    uint32_t GetTextLines() override
    {
        return 0;
    }

    double GetTextWidth() override
    {
        return 0;
    }

    Size Measure() override
    {
        return Size(1080.1, 0.0);
    }

    int32_t GetTouchPosition(const Offset& offset) override
    {
        return 0;
    }

    void ShowTextOverlay(const Offset& showOffset) override
    {
        return;
    }

    void RegisterCallbacksToOverlay() override
    {
        return;
    }

    Offset GetHandleOffset(int32_t extend) override
    {
        return Offset();
    }

    TextDirection GetDefaultTextDirection() const
    {
        return defaultTextDirection_;
    }
};

class MockRenderRoot final : public RenderRoot {
    DECLARE_ACE_TYPE(MockRenderRoot, RenderRoot);

public:
    MockRenderRoot() = default;
    ~MockRenderRoot() override = default;
};

/**
 * @tc.name: RenderTextTestRTL002
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for LTR
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl002 start";

    TestRTL(TextDirection::LTR, "text", TextAlign::START, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl002 stop";
}

/**
 * @tc.name: RenderTextTestRTL004
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for LTR
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl004 start";

    TestRTL(TextDirection::LTR, "text", TextAlign::END, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl004 stop";
}

/**
 * @@tc.name: RenderTextTestRTL006
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for LTR
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL006, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl006 start";

    TestRTL(TextDirection::LTR, "text", TextAlign::LEFT, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl006 stop";
}

/**
 * @@tc.name: RenderTextTestRTL008
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for LTR
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL008, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl008 start";

    TestRTL(TextDirection::LTR, "text", TextAlign::RIGHT, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl008 stop";
}

/**
 * @@tc.name: RenderTextTestRTL010
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL010, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl010 start";

    TestRTL(TextDirection::RTL, "", TextAlign::START, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl010 stop";
}

/**
 * @@tc.name: RenderTextTestRTL012
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL012, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl012 start";

    TestRTL(TextDirection::RTL, "1234567890", TextAlign::START, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl012 stop";
}

/**
 * @@tc.name: RenderTextTestRTL014
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL014, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl014 start";

    TestRTL(TextDirection::RTL, "اللغة العربية", TextAlign::START, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl014 stop";
}

/**
 * @@tc.name: RenderTextTestRTL016
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL016, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl016 start";

    TestRTL(TextDirection::RTL, "اللغة العربية", TextAlign::END, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl016 stop";
}

/**
 * @@tc.name: RenderTextTestRTL018
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL018, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl018 start";

    TestRTL(TextDirection::RTL, "اللغة العربية", TextAlign::LEFT, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl018 stop";
}

/**
 * @@tc.name: RenderTextTestRTL020
 * @tc.desc: Test UpdateParagraph and Paint of RosenRenderText for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderTextTest, RenderTextTestRTL020, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderTextTest rtl020 start";

    TestRTL(TextDirection::RTL, "اللغة العربية", TextAlign::RIGHT, true);

    GTEST_LOG_(INFO) << "RenderTextTest rtl020 stop";
}

} // namespace OHOS::Ace
