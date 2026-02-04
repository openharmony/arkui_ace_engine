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

#include "gtest/gtest.h"

#include "core/components_ng/base/extension_handler.h"
#include "core/components_ng/base/modifier.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

// Mock classes for testing
class MockContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(MockContentModifier, ContentModifier);

public:
    MockContentModifier() = default;
    ~MockContentModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        drawCalled_ = true;
    }

    bool drawCalled_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(MockContentModifier);
};

class MockOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(MockOverlayModifier, OverlayModifier);

public:
    MockOverlayModifier() = default;
    ~MockOverlayModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        drawCalled_ = true;
    }

    bool drawCalled_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(MockOverlayModifier);
};

class MockForegroundModifier : public ForegroundModifier {
    DECLARE_ACE_TYPE(MockForegroundModifier, ForegroundModifier);

public:
    MockForegroundModifier() = default;
    ~MockForegroundModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        drawCalled_ = true;
    }

    bool drawCalled_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(MockForegroundModifier);
};

class ModifierTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}

    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: ModifierConstructor001
 * @tc.desc: Test Modifier constructor generates unique id
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ModifierConstructor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create multiple Modifier instances
     */
    MockContentModifier modifier1;
    MockContentModifier modifier2;
    MockContentModifier modifier3;

    /**
     * @tc.steps: step2. Verify each has unique id
     * @tc.expected: Ids should be different and incrementing
     */
    EXPECT_NE(modifier1.GetId(), modifier2.GetId());
    EXPECT_NE(modifier2.GetId(), modifier3.GetId());
    EXPECT_NE(modifier1.GetId(), modifier3.GetId());
}

/**
 * @tc.name: ContentModifierDraw001
 * @tc.desc: Test ContentModifier Draw without extension handler
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ContentModifierDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MockContentModifier
     */
    auto modifier = AceType::MakeRefPtr<MockContentModifier>();

    /**
     * @tc.steps: step2. Create DrawingContext
     */
    RSCanvas canvas;
    DrawingContext context { canvas, 100.0f, 100.0f };

    /**
     * @tc.steps: step3. Call Draw
     * @tc.expected: onDraw should be called
     */
    modifier->Draw(context);
    EXPECT_TRUE(modifier->drawCalled_);
}

/**
 * @tc.name: ContentModifierAttachProperty001
 * @tc.desc: Test ContentModifier AttachProperty
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ContentModifierAttachProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ContentModifier and property
     */
    auto modifier = AceType::MakeRefPtr<MockContentModifier>();
    auto property = AceType::MakeRefPtr<PropertyInt>(42);

    /**
     * @tc.steps: step2. Attach property
     */
    modifier->AttachProperty(property);

    /**
     * @tc.steps: step3. Verify property is attached
     * @tc.expected: Property should be in attached properties list
     */
    const auto& properties = modifier->GetAttachedProperties();
    EXPECT_EQ(properties.size(), 2);
    EXPECT_EQ(properties[1], property);
}

/**
 * @tc.name: ContentModifierAttachProperty002
 * @tc.desc: Test ContentModifier attaches changeCount property in constructor
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ContentModifierAttachProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ContentModifier
     */
    auto modifier = AceType::MakeRefPtr<MockContentModifier>();

    /**
     * @tc.steps: step2. Check default attached properties
     * @tc.expected: Should have changeCount property attached
     */
    const auto& properties = modifier->GetAttachedProperties();
    EXPECT_GT(properties.size(), 0);
}

/**
 * @tc.name: ContentModifierSetContentChange001
 * @tc.desc: Test ContentModifier SetContentChange increments changeCount
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ContentModifierSetContentChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ContentModifier
     */
    auto modifier = AceType::MakeRefPtr<MockContentModifier>();

    /**
     * @tc.steps: step2. Call SetContentChange multiple times
     */
    modifier->SetContentChange();
    modifier->SetContentChange();
    modifier->SetContentChange();

    /**
     * @tc.steps: step3. Verify changeCount is incremented
     * @tc.expected: changeCount should be 3
     */
    const auto& properties = modifier->GetAttachedProperties();
    auto changeCountProp = AceType::DynamicCast<PropertyInt>(properties[0]);
    ASSERT_NE(changeCountProp, nullptr);
    EXPECT_EQ(changeCountProp->Get(), 3);
}

/**
 * @tc.name: ContentModifierBoundsRect001
 * @tc.desc: Test ContentModifier SetBoundsRect and GetBoundsRect
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ContentModifierBoundsRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ContentModifier
     */
    auto modifier = AceType::MakeRefPtr<MockContentModifier>();

    /**
     * @tc.steps: step2. Set bounds rect
     */
    RectF rect(10.0f, 20.0f, 100.0f, 200.0f);
    modifier->SetBoundsRect(rect);

    /**
     * @tc.steps: step3. Verify bounds rect
     * @tc.expected: GetBoundsRect should return the same rect
     */
    const auto& result = modifier->GetBoundsRect();
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->Left(), 10.0f);
    EXPECT_EQ(result->Top(), 20.0f);
    EXPECT_EQ(result->Width(), 100.0f);
    EXPECT_EQ(result->Height(), 200.0f);
}

/**
 * @tc.name: ContentModifierCustomFont001
 * @tc.desc: Test ContentModifier SetIsCustomFont and GetIsCustomFont
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ContentModifierCustomFont001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ContentModifier
     */
    auto modifier = AceType::MakeRefPtr<MockContentModifier>();

    /**
     * @tc.steps: step2. Check default value
     * @tc.expected: Should be false
     */
    EXPECT_FALSE(modifier->GetIsCustomFont());

    /**
     * @tc.steps: step3. Set custom font
     */
    modifier->SetIsCustomFont(true);

    /**
     * @tc.steps: step4. Verify value changed
     * @tc.expected: Should be true
     */
    EXPECT_TRUE(modifier->GetIsCustomFont());
}

/**
 * @tc.name: OverlayModifierDraw001
 * @tc.desc: Test OverlayModifier Draw without extension handler
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, OverlayModifierDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MockOverlayModifier
     */
    auto modifier = AceType::MakeRefPtr<MockOverlayModifier>();

    /**
     * @tc.steps: step2. Create DrawingContext
     */
    RSCanvas canvas;
    DrawingContext context { canvas, 100.0f, 100.0f };

    /**
     * @tc.steps: step3. Call Draw
     * @tc.expected: onDraw should be called
     */
    modifier->Draw(context);
    EXPECT_TRUE(modifier->drawCalled_);
}

/**
 * @tc.name: OverlayModifierSetOverlayChange001
 * @tc.desc: Test OverlayModifier SetOverlayChange increments changeCount
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, OverlayModifierSetOverlayChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create OverlayModifier
     */
    auto modifier = AceType::MakeRefPtr<MockOverlayModifier>();

    /**
     * @tc.steps: step2. Call SetOverlayChange multiple times
     */
    modifier->SetOverlayChange();
    modifier->SetOverlayChange();

    /**
     * @tc.steps: step3. Verify changeCount is incremented
     * @tc.expected: changeCount should be 2
     */
    const auto& properties = modifier->GetAttachedProperties();
    auto changeCountProp = AceType::DynamicCast<PropertyInt>(properties[0]);
    ASSERT_NE(changeCountProp, nullptr);
    EXPECT_EQ(changeCountProp->Get(), 2);
}

/**
 * @tc.name: OverlayModifierBoundsRect001
 * @tc.desc: Test OverlayModifier SetBoundsRect and GetBoundsRect
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, OverlayModifierBoundsRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create OverlayModifier
     */
    auto modifier = AceType::MakeRefPtr<MockOverlayModifier>();

    /**
     * @tc.steps: step2. Set bounds rect
     */
    RectF rect(5.0f, 10.0f, 50.0f, 100.0f);
    modifier->SetBoundsRect(rect);

    /**
     * @tc.steps: step3. Verify bounds rect
     * @tc.expected: GetBoundsRect should return the same rect
     */
    const auto& result = modifier->GetBoundsRect();
    EXPECT_EQ(result.Left(), 5.0f);
    EXPECT_EQ(result.Top(), 10.0f);
    EXPECT_EQ(result.Width(), 50.0f);
    EXPECT_EQ(result.Height(), 100.0f);
}

/**
 * @tc.name: ForegroundModifierDraw001
 * @tc.desc: Test ForegroundModifier Draw without extension handler
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ForegroundModifierDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MockForegroundModifier
     */
    auto modifier = AceType::MakeRefPtr<MockForegroundModifier>();

    /**
     * @tc.steps: step2. Create DrawingContext
     */
    RSCanvas canvas;
    DrawingContext context { canvas, 100.0f, 100.0f };

    /**
     * @tc.steps: step3. Call Draw
     * @tc.expected: onDraw should be called
     */
    modifier->Draw(context);
    EXPECT_TRUE(modifier->drawCalled_);
}

/**
 * @tc.name: ForegroundModifierSetForegroundChange001
 * @tc.desc: Test ForegroundModifier SetForegroundChange increments changeCount
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ForegroundModifierSetForegroundChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ForegroundModifier
     */
    auto modifier = AceType::MakeRefPtr<MockForegroundModifier>();

    /**
     * @tc.steps: step2. Call SetForegroundChange multiple times
     */
    modifier->SetForegroundChange();
    modifier->SetForegroundChange();
    modifier->SetForegroundChange();

    /**
     * @tc.steps: step3. Verify changeCount is incremented
     * @tc.expected: changeCount should be 3
     */
    const auto& properties = modifier->GetAttachedProperties();
    auto changeCountProp = AceType::DynamicCast<PropertyInt>(properties[0]);
    ASSERT_NE(changeCountProp, nullptr);
    EXPECT_EQ(changeCountProp->Get(), 3);
}

/**
 * @tc.name: ForegroundModifierBoundsRect001
 * @tc.desc: Test ForegroundModifier SetBoundsRect and GetBoundsRect
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ForegroundModifierBoundsRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ForegroundModifier
     */
    auto modifier = AceType::MakeRefPtr<MockForegroundModifier>();

    /**
     * @tc.steps: step2. Set bounds rect
     */
    RectF rect(0.0f, 0.0f, 200.0f, 300.0f);
    modifier->SetBoundsRect(rect);

    /**
     * @tc.steps: step3. Verify bounds rect
     * @tc.expected: GetBoundsRect should return the same rect
     */
    const auto& result = modifier->GetBoundsRect();
    EXPECT_EQ(result.Left(), 0.0f);
    EXPECT_EQ(result.Top(), 0.0f);
    EXPECT_EQ(result.Width(), 200.0f);
    EXPECT_EQ(result.Height(), 300.0f);
}

/**
 * @tc.name: ContentModifierGetContentTransitionParam001
 * @tc.desc: Test ContentModifier GetContentTransitionParam returns default IDENTITY
 * @tc.type: FUNC
 */
HWTEST_F(ModifierTestNg, ContentModifierGetContentTransitionParam001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ContentModifier
     */
    auto modifier = AceType::MakeRefPtr<MockContentModifier>();

    /**
     * @tc.steps: step2. Call GetContentTransitionParam
     * @tc.expected: Should return IDENTITY by default
     */
    EXPECT_EQ(modifier->GetContentTransitionParam(), ContentTransitionType::IDENTITY);
}

} // namespace OHOS::Ace::NG