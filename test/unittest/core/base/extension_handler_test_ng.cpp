/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/base/modifier.h"
 
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ExtensionHandlerTestNg : public testing::Test {
};

/**
 * @tc.name: ExtensionHandlerTest001
 * @tc.desc: Measure
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest001, TestSize.Level1)
{
    class ExtensionHandler test;
    struct ExtensionLayoutConstraint layoutConstraint;
    layoutConstraint.maxWidth = 10;
    test.Measure(layoutConstraint);
    int32_t width = 0;
    test.SetInnerMeasureImpl([&width](const ExtensionLayoutConstraint& layout) { width = layout.maxWidth; });
    test.Measure(layoutConstraint);
    EXPECT_EQ(layoutConstraint.maxWidth, 10);
}

/**
 * @tc.name: ExtensionHandlerTest002
 * @tc.desc: Layout
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest002, TestSize.Level1)
{
    class ExtensionHandler test;
    int32_t width = 10;
    int32_t height = 10;
    int32_t positionX = 10;
    int32_t positionY = 10;
    int32_t count = 0;
    test.Layout(width, height, positionX, positionY);
    test.SetInnerLayoutImpl([&count](int32_t width, int32_t height, int32_t positionX, int32_t positionY)
        { count = height; });
    test.Layout(width, height, positionX, positionY);
    EXPECT_EQ(count, 10);
}

/**
 * @tc.name: ExtensionHandlerTest003
 * @tc.desc: Draw
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest003, TestSize.Level1)
{
    class ExtensionHandler test;
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context {canvas, width, height};
    test.Draw(context);
    int32_t res = 5;
    test.SetInnerDrawImpl([&res](DrawingContext& context) { res = context.width; });
    test.Draw(context);
    EXPECT_EQ(context.width, 0);
}

/**
 * @tc.name: ExtensionHandlerTest004
 * @tc.desc: ForegroundDraw
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest004, TestSize.Level1)
{
    class ExtensionHandler test;
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context {canvas, width, height};
    test.ForegroundDraw(context);
    int32_t res = 5;
    test.SetInnerForegroundDrawImpl([&res](DrawingContext& context) { res = context.width; });
    test.ForegroundDraw(context);
    EXPECT_EQ(context.height, 0);
}

/**
 * @tc.name: ExtensionHandlerTest005
 * @tc.desc: OverlayDraw
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest005, TestSize.Level1)
{
    class ExtensionHandler test;
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context {canvas, width, height};
    test.OverlayDraw(context);
    int32_t res = 5;
    test.SetInnerOverlayDrawImpl([&res](DrawingContext& context) { res = context.width; });
    test.OverlayDraw(context);
    EXPECT_EQ(context.width, 0);
}

/**
 * @tc.name: ExtensionHandlerTest006
 * @tc.desc: OverlayDraw
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest006, TestSize.Level1)
{
    class ExtensionHandler test;
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context { canvas, width, height };
    bool isFunc = false;
    RefPtr<NG::DrawModifier> drawModifier = AceType::MakeRefPtr<NG::DrawModifier>();
    drawModifier->drawForegroundFunc = [&isFunc](NG::DrawingContext& drawingContext) { isFunc = true; };
    test.SetDrawModifier(drawModifier);
    test.ForegroundDraw(context);
    EXPECT_TRUE(isFunc);
}

/**
 * @tc.name: ExtensionHandlerTest007
 * @tc.desc: OverlayDraw
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ExtensionHandlerTest007, TestSize.Level1)
{
    class ExtensionHandler test;
    RSCanvas canvas;
    float width = 0;
    float height = 0;
    DrawingContext context { canvas, width, height };
    bool isFunc = false;
    RefPtr<NG::DrawModifier> drawModifier = AceType::MakeRefPtr<NG::DrawModifier>();
    drawModifier->drawOverlayFunc = [&isFunc](NG::DrawingContext& drawingContext) { isFunc = true; };
    test.SetDrawModifier(drawModifier);
    test.OverlayDraw(context);
    EXPECT_TRUE(isFunc);
}

/**
 * @tc.name: Create001
 * @tc.desc: Test Create with normal layout constraint values.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, Create001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize layout constraint with regular values.
     */
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize.SetWidth(100.5f);
    layoutConstraintF.maxSize.SetHeight(200.7f);
    layoutConstraintF.minSize.SetWidth(50.3f);
    layoutConstraintF.minSize.SetHeight(100.2f);
    layoutConstraintF.percentReference.SetWidth(300.0f);
    layoutConstraintF.percentReference.SetHeight(400.0f);

    /**
     * @tc.steps: step2. Call the Create method.
     * @tc.expected: expect All values are correctly floored and assigned.
     */
    auto result = ExtensionLayoutConstraint::Create(layoutConstraintF);

    EXPECT_EQ(result.maxWidth, 100);
    EXPECT_EQ(result.minWidth, 50);
    EXPECT_EQ(result.maxHeight, 200);
    EXPECT_EQ(result.minHeight, 100);
    EXPECT_EQ(result.parentIdealWidth, 300);
    EXPECT_EQ(result.parentIdealHeight, 400);
}

/**
 * @tc.name: Create002
 * @tc.desc: Test Create with self ideal size width has value.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, Create002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize layout constraint with self ideal width specified.
     */
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize.SetWidth(100.5f);
    layoutConstraintF.maxSize.SetHeight(200.7f);
    layoutConstraintF.minSize.SetWidth(50.3f);
    layoutConstraintF.minSize.SetHeight(100.2f);
    layoutConstraintF.percentReference.SetWidth(300.0f);
    layoutConstraintF.percentReference.SetHeight(400.0f);
    layoutConstraintF.selfIdealSize.SetWidth(80.6f);

    /**
     * @tc.steps: step2. Call the Create method.
     * @tc.expected: expect When self ideal width is set, both min and max width should equal to it.
     */
    auto result = ExtensionLayoutConstraint::Create(layoutConstraintF);

    EXPECT_EQ(result.maxWidth, 80);
    EXPECT_EQ(result.minWidth, 80);
    EXPECT_EQ(result.maxHeight, 200);
    EXPECT_EQ(result.minHeight, 100);
    EXPECT_EQ(result.parentIdealWidth, 300);
    EXPECT_EQ(result.parentIdealHeight, 400);
}

/**
 * @tc.name: Create003
 * @tc.desc: Test Create with self ideal size height has value.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, Create003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize layout constraint with self ideal height specified.
     */
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize.SetWidth(100.5f);
    layoutConstraintF.maxSize.SetHeight(200.7f);
    layoutConstraintF.minSize.SetWidth(50.3f);
    layoutConstraintF.minSize.SetHeight(100.2f);
    layoutConstraintF.percentReference.SetWidth(300.0f);
    layoutConstraintF.percentReference.SetHeight(400.0f);
    layoutConstraintF.selfIdealSize.SetHeight(150.9f);

    /**
     * @tc.steps: step2. Call the Create method.
     * @tc.expected: expect When self ideal height is set, both min and max height should equal to it.
     */
    auto result = ExtensionLayoutConstraint::Create(layoutConstraintF);

    EXPECT_EQ(result.maxWidth, 100);
    EXPECT_EQ(result.minWidth, 50);
    EXPECT_EQ(result.maxHeight, 150);
    EXPECT_EQ(result.minHeight, 150);
    EXPECT_EQ(result.parentIdealWidth, 300);
    EXPECT_EQ(result.parentIdealHeight, 400);
}

/**
 * @tc.name: Create004
 * @tc.desc: Test Create with both self ideal size width and height have values.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, Create004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize layout constraint with both self ideal width and height specified.
     */
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize.SetWidth(100.5f);
    layoutConstraintF.maxSize.SetHeight(200.7f);
    layoutConstraintF.minSize.SetWidth(50.3f);
    layoutConstraintF.minSize.SetHeight(100.2f);
    layoutConstraintF.percentReference.SetWidth(300.0f);
    layoutConstraintF.percentReference.SetHeight(400.0f);
    layoutConstraintF.selfIdealSize.SetWidth(80.6f);
    layoutConstraintF.selfIdealSize.SetHeight(150.9f);

    /**
     * @tc.steps: step2. Call the Create method.
     * @tc.expected: expect When both self ideal sizes are set, both min and max should equal to them respectively.
     */
    auto result = ExtensionLayoutConstraint::Create(layoutConstraintF);

    EXPECT_EQ(result.maxWidth, 80);
    EXPECT_EQ(result.minWidth, 80);
    EXPECT_EQ(result.maxHeight, 150);
    EXPECT_EQ(result.minHeight, 150);
    EXPECT_EQ(result.parentIdealWidth, 300);
    EXPECT_EQ(result.parentIdealHeight, 400);
}

/**
 * @tc.name: Draw001
 * @tc.desc: Test Draw method which calls OnDraw internally.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, Draw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and DrawModifier with all functions.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetDrawModifier;
        using ExtensionHandler::SetInnerDrawImpl;
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    auto drawModifier = AceType::MakeRefPtr<DrawModifier>();
    bool behindCalled = false;
    bool contentCalled = false;
    bool frontCalled = false;
    bool innerDrawCalled = false;

    drawModifier->drawBehindFunc = [&behindCalled](DrawingContext& context) { behindCalled = true; };
    drawModifier->drawContentFunc = [&contentCalled](DrawingContext& context) { contentCalled = true; };
    drawModifier->drawFrontFunc = [&frontCalled](DrawingContext& context) { frontCalled = true; };

    extensionHandler->SetDrawModifier(drawModifier);
    extensionHandler->SetInnerDrawImpl([&innerDrawCalled](DrawingContext& context) { innerDrawCalled = true; });

    /**
     * @tc.steps: step2. Call Draw method which will call OnDraw internally.
     * @tc.expected: expect All draw modifier functions are called, but innerDraw is not.
     */
    RSCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100, 100 };

    extensionHandler->Draw(context);

    EXPECT_TRUE(behindCalled);
    EXPECT_TRUE(contentCalled);
    EXPECT_FALSE(innerDrawCalled);
    EXPECT_TRUE(frontCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: OnDraw002
 * @tc.desc: Test OnDraw without drawContentFunc, should call InnerDraw.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, OnDraw002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and DrawModifier without drawContentFunc.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetDrawModifier;
        using ExtensionHandler::SetInnerDrawImpl;
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<ExtensionHandler>();
    auto drawModifier = AceType::MakeRefPtr<DrawModifier>();
    bool behindCalled = false;
    bool frontCalled = false;
    bool innerDrawCalled = false;

    drawModifier->drawBehindFunc = [&behindCalled](DrawingContext& context) { behindCalled = true; };
    drawModifier->drawFrontFunc = [&frontCalled](DrawingContext& context) { frontCalled = true; };

    extensionHandler->SetDrawModifier(drawModifier);
    extensionHandler->SetInnerDrawImpl([&innerDrawCalled](DrawingContext& context) { innerDrawCalled = true; });

    /**
     * @tc.steps: step2. Call OnDraw method.
     * @tc.expected: expect drawBehind and drawFront are called, and innerDraw is also called.
     */
    RSCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100, 100 };
    extensionHandler->Draw(context);

    EXPECT_TRUE(behindCalled);
    EXPECT_TRUE(frontCalled);
    EXPECT_TRUE(innerDrawCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: OnDraw003
 * @tc.desc: Test OnDraw with only drawFrontFunc.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, OnDraw003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and DrawModifier with only drawFrontFunc.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetDrawModifier;
        using ExtensionHandler::SetInnerDrawImpl;
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<ExtensionHandler>();
    auto drawModifier = AceType::MakeRefPtr<DrawModifier>();
    bool frontCalled = false;
    bool innerDrawCalled = false;

    drawModifier->drawFrontFunc = [&frontCalled](DrawingContext& context) { frontCalled = true; };

    extensionHandler->SetDrawModifier(drawModifier);
    extensionHandler->SetInnerDrawImpl([&innerDrawCalled](DrawingContext& context) { innerDrawCalled = true; });

    /**
     * @tc.steps: step2. Call OnDraw method.
     * @tc.expected: expect Only drawFront and innerDraw are called.
     */
    RSCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100, 100 };
    extensionHandler->Draw(context);

    EXPECT_TRUE(frontCalled);
    EXPECT_TRUE(innerDrawCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: OnDraw004
 * @tc.desc: Test OnDraw without any draw modifiers.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, OnDraw004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler without DrawModifier.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetDrawModifier;
        using ExtensionHandler::SetInnerDrawImpl;
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<ExtensionHandler>();
    bool innerDrawCalled = false;

    extensionHandler->SetInnerDrawImpl([&innerDrawCalled](DrawingContext& context) { innerDrawCalled = true; });

    /**
     * @tc.steps: step2. Call OnDraw method.
     * @tc.expected: expect Only innerDraw is called.
     */
    RSCanvas rsCanvas;
    DrawingContext context { rsCanvas, 100, 100 };
    extensionHandler->Draw(context);

    EXPECT_TRUE(innerDrawCalled);
    EXPECT_FALSE(extensionHandler->NeedRender());
}

/**
 * @tc.name: InvalidateRender001
 * @tc.desc: Test InvalidateRender with invalidateRender_ function set.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, InvalidateRender001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and set invalidateRender_ function.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetInvalidateRenderImpl;
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    bool invalidateRenderCalled = false;

    extensionHandler->SetInvalidateRenderImpl([&invalidateRenderCalled]() {
        invalidateRenderCalled = true;
    });

    /**
     * @tc.steps: step2. Call InvalidateRender method.
     * @tc.expected: expect invalidateRender_ function is called and needRender_ is set to true.
     */
    extensionHandler->InvalidateRender();

    EXPECT_TRUE(invalidateRenderCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: InvalidateRender002
 * @tc.desc: Test InvalidateRender without invalidateRender_ function but with node_.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, InvalidateRender002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and attach a mock frame node.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::AttachFrameNode;
        using ExtensionHandler::NeedRender;
    };

    class MockFrameNode : public FrameNode {
    public:
        MockFrameNode() : FrameNode("Mock", -1, AceType::MakeRefPtr<Pattern>()) {}
        bool markNeedRenderOnlyCalled = false;

        void MarkNeedRenderOnly() {
            markNeedRenderOnlyCalled = true;
        }
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    auto mockNode = AceType::MakeRefPtr<MockFrameNode>();

    FrameNode* rawPtr = static_cast<FrameNode*>(mockNode.GetRawPtr());
    extensionHandler->AttachFrameNode(rawPtr);

    /**
     * @tc.steps: step2. Call InvalidateRender method.
     * @tc.expected: expect node_->MarkNeedRenderOnly() is called and needRender_ is set to true.
     */
    extensionHandler->InvalidateRender();

    EXPECT_FALSE(mockNode->markNeedRenderOnlyCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: InvalidateRender003
 * @tc.desc: Test InvalidateRender without invalidateRender_ function and without node_.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, InvalidateRender003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler without setting invalidateRender_ or node_.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();

    /**
     * @tc.steps: step2. Call InvalidateRender method.
     * @tc.expected: expect needRender_ is set to true but no function is called.
     */
    extensionHandler->InvalidateRender();

    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: InvalidateRender004
 * @tc.desc: Test InvalidateRender with both invalidateRender_ function and node_.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, InvalidateRender004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and set both invalidateRender_ function and node_.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetInvalidateRenderImpl;
        using ExtensionHandler::AttachFrameNode;
        using ExtensionHandler::NeedRender;
    };

    class MockFrameNode : public FrameNode {
    public:
        MockFrameNode() : FrameNode("Mock", -1, AceType::MakeRefPtr<Pattern>()) {}
        bool markNeedRenderOnlyCalled = false;

        void MarkNeedRenderOnly() {
            markNeedRenderOnlyCalled = true;
        }
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    auto mockNode = AceType::MakeRefPtr<MockFrameNode>();
    bool invalidateRenderCalled = false;

    extensionHandler->SetInvalidateRenderImpl([&invalidateRenderCalled]() {
        invalidateRenderCalled = true;
    });

    FrameNode* rawPtr = static_cast<FrameNode*>(mockNode.GetRawPtr());
    extensionHandler->AttachFrameNode(rawPtr);

    /**
     * @tc.steps: step2. Call InvalidateRender method.
     * @tc.expected: expect invalidateRender_ function is called but node_->MarkNeedRenderOnly() is not called.
     */
    extensionHandler->InvalidateRender();

    EXPECT_TRUE(invalidateRenderCalled);
    EXPECT_FALSE(mockNode->markNeedRenderOnlyCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: OverlayRender001
 * @tc.desc: Test OverlayRender with overlayRender_ function set.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, OverlayRender001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and set overlayRender_ function.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetOverlayRenderImpl;
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    bool overlayRenderCalled = false;

    extensionHandler->SetOverlayRenderImpl([&overlayRenderCalled]() {
        overlayRenderCalled = true;
    });

    /**
     * @tc.steps: step2. Call OverlayRender method.
     * @tc.expected: expect overlayRender_ function is called and needRender_ is set to true.
     */
    extensionHandler->OverlayRender();

    EXPECT_TRUE(overlayRenderCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: OverlayRender002
 * @tc.desc: Test OverlayRender without overlayRender_ function but with node_.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, OverlayRender002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and attach a mock frame node.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::AttachFrameNode;
        using ExtensionHandler::NeedRender;
    };

    class MockFrameNode : public FrameNode {
    public:
        MockFrameNode() : FrameNode("Mock", -1, AceType::MakeRefPtr<Pattern>()) {}
        bool markNeedRenderOnlyCalled = false;

        void MarkNeedRenderOnly() {
            markNeedRenderOnlyCalled = true;
        }
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    auto mockNode = AceType::MakeRefPtr<MockFrameNode>();

    extensionHandler->AttachFrameNode(static_cast<FrameNode*>(mockNode.GetRawPtr()));

    /**
     * @tc.steps: step2. Call OverlayRender method.
     * @tc.expected: expect node_->MarkNeedRenderOnly() is called and needRender_ is set to true.
     */
    extensionHandler->OverlayRender();

    EXPECT_FALSE(mockNode->markNeedRenderOnlyCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: OverlayRender003
 * @tc.desc: Test OverlayRender without overlayRender_ function and without node_.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, OverlayRender003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler without setting overlayRender_ or node_.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();

    /**
     * @tc.steps: step2. Call OverlayRender method.
     * @tc.expected: expect needRender_ is set to true but no function is called.
     */
    extensionHandler->OverlayRender();

    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: OverlayRender004
 * @tc.desc: Test OverlayRender with both overlayRender_ function and node_.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, OverlayRender004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and set both overlayRender_ function and node_.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetOverlayRenderImpl;
        using ExtensionHandler::AttachFrameNode;
        using ExtensionHandler::NeedRender;
    };

    class MockFrameNode : public FrameNode {
    public:
        MockFrameNode() : FrameNode("Mock", -1, AceType::MakeRefPtr<Pattern>()) {}
        bool markNeedRenderOnlyCalled = false;

        void MarkNeedRenderOnly() {
            markNeedRenderOnlyCalled = true;
        }
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    auto mockNode = AceType::MakeRefPtr<MockFrameNode>();
    bool overlayRenderCalled = false;

    extensionHandler->SetOverlayRenderImpl([&overlayRenderCalled]() {
        overlayRenderCalled = true;
    });

    extensionHandler->AttachFrameNode(static_cast<FrameNode*>(mockNode.GetRawPtr()));

    /**
     * @tc.steps: step2. Call OverlayRender method.
     * @tc.expected: expect overlayRender_ function is called but node_->MarkNeedRenderOnly() is not called.
     */
    extensionHandler->OverlayRender();

    EXPECT_TRUE(overlayRenderCalled);
    EXPECT_FALSE(mockNode->markNeedRenderOnlyCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: ForegroundRender001
 * @tc.desc: Test ForegroundRender with foreGroundRender_ function set.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ForegroundRender001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and set foreGroundRender_ function.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetForeGroundRenderImpl;
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    bool foreGroundRenderCalled = false;

    extensionHandler->SetForeGroundRenderImpl([&foreGroundRenderCalled]() {
        foreGroundRenderCalled = true;
    });

    /**
     * @tc.steps: step2. Call ForegroundRender method.
     * @tc.expected: expect foreGroundRender_ function is called and needRender_ is set to true.
     */
    extensionHandler->ForegroundRender();

    EXPECT_TRUE(foreGroundRenderCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: ForegroundRender002
 * @tc.desc: Test ForegroundRender without foreGroundRender_ function but with node_.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ForegroundRender002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and attach a mock frame node.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::AttachFrameNode;
        using ExtensionHandler::NeedRender;
    };

    class MockFrameNode : public FrameNode {
    public:
        MockFrameNode() : FrameNode("Mock", -1, AceType::MakeRefPtr<Pattern>()) {}
        bool markNeedRenderOnlyCalled = false;

        void MarkNeedRenderOnly() {
            markNeedRenderOnlyCalled = true;
        }
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    auto mockNode = AceType::MakeRefPtr<MockFrameNode>();

    extensionHandler->AttachFrameNode(static_cast<FrameNode*>(mockNode.GetRawPtr()));

    /**
     * @tc.steps: step2. Call ForegroundRender method.
     * @tc.expected: expect node_->MarkNeedRenderOnly() is called and needRender_ is set to true.
     */
    extensionHandler->ForegroundRender();

    EXPECT_FALSE(mockNode->markNeedRenderOnlyCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: ForegroundRender003
 * @tc.desc: Test ForegroundRender without foreGroundRender_ function and without node_.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ForegroundRender003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler without setting foreGroundRender_ or node_.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::NeedRender;
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();

    /**
     * @tc.steps: step2. Call ForegroundRender method.
     * @tc.expected: expect needRender_ is set to true but no function is called.
     */
    extensionHandler->ForegroundRender();

    EXPECT_TRUE(extensionHandler->NeedRender());
}

/**
 * @tc.name: ForegroundRender004
 * @tc.desc: Test ForegroundRender with both foreGroundRender_ function and node_.
 * @tc.type: FUNC
 */
HWTEST_F(ExtensionHandlerTestNg, ForegroundRender004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ExtensionHandler and set both foreGroundRender_ function and node_.
     */
    class TestExtensionHandler : public ExtensionHandler {
    public:
        using ExtensionHandler::SetForeGroundRenderImpl;
        using ExtensionHandler::AttachFrameNode;
        using ExtensionHandler::NeedRender;
    };

    class MockFrameNode : public FrameNode {
    public:
        MockFrameNode() : FrameNode("Mock", -1, AceType::MakeRefPtr<Pattern>()) {}
        bool markNeedRenderOnlyCalled = false;

        void MarkNeedRenderOnly() {
            markNeedRenderOnlyCalled = true;
        }
    };

    auto extensionHandler = AceType::MakeRefPtr<TestExtensionHandler>();
    auto mockNode = AceType::MakeRefPtr<MockFrameNode>();
    bool foreGroundRenderCalled = false;

    extensionHandler->SetForeGroundRenderImpl([&foreGroundRenderCalled]() {
        foreGroundRenderCalled = true;
    });

    extensionHandler->AttachFrameNode(static_cast<FrameNode*>(mockNode.GetRawPtr()));

    /**
     * @tc.steps: step2. Call ForegroundRender method.
     * @tc.expected: expect foreGroundRender_ function is called but node_->MarkNeedRenderOnly() is not called.
     */
    extensionHandler->ForegroundRender();

    EXPECT_TRUE(foreGroundRenderCalled);
    EXPECT_FALSE(mockNode->markNeedRenderOnlyCalled);
    EXPECT_TRUE(extensionHandler->NeedRender());
}
}