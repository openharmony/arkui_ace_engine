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
#include "test/unittest/core/layout/pixel_round_test_ng.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: PixelRoundTest001
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest001, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("200px")
            .pixelRound({start:PixelRoundCalcPolicy.FORCE_CEIL, top:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START) |
                                           static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest002
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest002, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("200px")
            .pixelRound({bottom:PixelRoundCalcPolicy.FORCE_CEIL, end:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END) |
                                           static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest003
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest003, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(99.4));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("99.4px")
            .height("200px")
            .pixelRound({end:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 99.4, height is 200 and offset is [0.0, 0.0] before piexel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(99.4f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest004
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest004, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(199.4));
            ViewAbstractModelNG model1;
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("199.4px")
            .pixelRound({bottom:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 199.4 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 199.4f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest005
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest005, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("200px")
            .pixelRound({start:PixelRoundCalcPolicy.FORCE_FLOOR, top:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START) |
                                           static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest006
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest006, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("200px")
            .pixelRound({bottom:PixelRoundCalcPolicy.FORCE_FLOOR, end:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END) |
                                           static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest007
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest007, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(99.5));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("99.5px")
            .height("200px")
            .pixelRound({end:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 99.5, height is 200 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(99.5f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 99, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 99.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest008
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest008, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(199.5));
            ViewAbstractModelNG model1;
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("199.5px")
            .pixelRound({bottom:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 199.5f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 199 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 199.0f));
}

/**
 * @tc.name: PixelRoundTest009
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest009, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("200px")
            .pixelRound({start:PixelRoundCalcPolicy.NO_FORCE_ROUND, top:PixelRoundCalcPolicy.NO_FORCE_ROUND})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_START) |
                                           static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_TOP));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest010
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest010, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("200px")
            .pixelRound({bottom:PixelRoundCalcPolicy.NO_FORCE_ROUND, end:PixelRoundCalcPolicy.NO_FORCE_ROUND})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_END) |
                                           static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest011
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest011, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(99.5));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("99.5px")
            .height("200px")
            .pixelRound({end:PixelRoundCalcPolicy.NO_FORCE_ROUND})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 99.5, height is 200 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(99.5f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 99.5, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_END));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 99.5f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest012
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest012, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(199.5));
            ViewAbstractModelNG model1;
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("199.5px")
            .pixelRound({bottom:PixelRoundCalcPolicy.NO_FORCE_ROUND})
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 199.5 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 199.5f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 199.5 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 199.5f));
}

/**
 * @tc.name: PixelRoundTest013
 * @tc.desc: Test PixelRoundTest
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest013, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0000001));
            ViewAbstract::SetHeight(CalcLength(200.0000001));
            ViewAbstractModelNG model1;
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100.0000001px")
            .height("200.0000001px")
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 199.5 and offset is [0.0, 0.0] before pixel rounding.
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0000001f, 200.0000001f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 200 and offset is [0.0, 0.0] after pixel rounding.
    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, 0);
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest014
 * @tc.desc: Test FORCE_CEIL_START with fractional width (99.4px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest014, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(99.4));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("99.4px")
            .height("200px")
            .pixelRound({start:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(99.4f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 99.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest015
 * @tc.desc: Test FORCE_CEIL_START with fractional width (100.6px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest015, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.6));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100.6px")
            .height("200px")
            .pixelRound({start:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(100.6f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 101.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest016
 * @tc.desc: Test FORCE_CEIL_TOP with fractional height (199.4px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest016, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(199.4));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("199.4px")
            .pixelRound({top:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(100.0f, 199.4f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 199.0f));
}

/**
 * @tc.name: PixelRoundTest017
 * @tc.desc: Test FORCE_CEIL_TOP with fractional height (200.6px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest017, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(200.6));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("200.6px")
            .pixelRound({top:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(100.0f, 200.6f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 201.0f));
}

/**
 * @tc.name: PixelRoundTest018
 * @tc.desc: Test FORCE_FLOOR_START with fractional width (99.5px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest018, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(99.5));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("99.5px")
            .height("200px")
            .pixelRound({start:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(99.5f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest019
 * @tc.desc: Test FORCE_FLOOR_START with fractional width (100.6px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest019, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.6));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100.6px")
            .height("200px")
            .pixelRound({start:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(100.6f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 101.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest020
 * @tc.desc: Test FORCE_FLOOR_TOP with fractional height (199.5px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest020, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(199.5));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("199.5px")
            .pixelRound({top:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(100.0f, 199.5f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest021
 * @tc.desc: Test FORCE_FLOOR_TOP with fractional height (200.6px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest021, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(200.6));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("200.6px")
            .pixelRound({top:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(100.0f, 200.6f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 201.0f));
}

/**
 * @tc.name: PixelRoundTest022
 * @tc.desc: Test NO_FORCE_ROUND_START with fractional width (99.5px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest022, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(99.5));
            ViewAbstract::SetHeight(CalcLength(200));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("99.5px")
            .height("200px")
            .pixelRound({start:PixelRoundCalcPolicy.NO_FORCE_ROUND})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(99.5f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_START));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest023
 * @tc.desc: Test NO_FORCE_ROUND_TOP with fractional height (199.5px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest023, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100));
            ViewAbstract::SetHeight(CalcLength(199.5));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("100px")
            .height("199.5px")
            .pixelRound({top:PixelRoundCalcPolicy.NO_FORCE_ROUND})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(100.0f, 199.5f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_TOP));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 100.0f, 200.0f));
}

/**
 * @tc.name: PixelRoundTest024
 * @tc.desc: Test FORCE_CEIL with very small fractional value (0.1px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest024, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(0.1));
            ViewAbstract::SetHeight(CalcLength(0.1));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("0.1px")
            .height("0.1px")
            .pixelRound({end:PixelRoundCalcPolicy.FORCE_CEIL, bottom:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(0.1f, 0.1f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END) |
                                       static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 1.0f, 1.0f));
}

/**
 * @tc.name: PixelRoundTest025
 * @tc.desc: Test FORCE_CEIL with large fractional value (999.9px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest025, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(999.9));
            ViewAbstract::SetHeight(CalcLength(999.9));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("999.9px")
            .height("999.9px")
            .pixelRound({end:PixelRoundCalcPolicy.FORCE_CEIL, bottom:PixelRoundCalcPolicy.FORCE_CEIL})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 999.9f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END) |
                                       static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 500.0f, 1000.0f));
}

/**
 * @tc.name: PixelRoundTest026
 * @tc.desc: Test FORCE_FLOOR with very small fractional value (0.9px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest026, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(0.9));
            ViewAbstract::SetHeight(CalcLength(0.9));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("0.9px")
            .height("0.9px")
            .pixelRound({end:PixelRoundCalcPolicy.FORCE_FLOOR, bottom:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(0.9f, 0.9f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END) |
                                       static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 1.0f, 1.0f));
}

/**
 * @tc.name: PixelRoundTest027
 * @tc.desc: Test FORCE_FLOOR with large fractional value (1000.9px)
 * @tc.type: FUNC
 */
HWTEST_F(PixelRoundTestNg, PixelRoundTest027, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlex([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlex([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(1000.9));
            ViewAbstract::SetHeight(CalcLength(1000.9));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("1000.9px")
            .height("1000.9px")
            .pixelRound({end:PixelRoundCalcPolicy.FORCE_FLOOR, bottom:PixelRoundCalcPolicy.FORCE_FLOOR})
        }
        .width("500px")
        .height("300px")
    */

    auto geometryNode = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 1000.9f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    auto renderContext = flexInner->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->SavePaintRect(true, static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END) |
                                       static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM));
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    EXPECT_EQ(paintRect, RectF(0.0f, 0.0f, 500.0f, 1001.0f));
}
} // namespace OHOS::Ace::NG