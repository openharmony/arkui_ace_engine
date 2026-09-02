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

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/frameworks/core/common/mock_container.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/components_ng/pattern/canvas/canvas_render_context_deferred.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CanvasRenderingContext2DModelNGTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<CanvasRenderingContext2DModelNG> model_;
    RefPtr<CanvasPattern> pattern_;
    RefPtr<FrameNode> frameNode_;
};

void CanvasRenderingContext2DModelNGTest::SetUpTestCase()
{
    MockContainer::SetUp();
}

void CanvasRenderingContext2DModelNGTest::TearDownTestCase()
{
    MockContainer::TearDown();
}

void CanvasRenderingContext2DModelNGTest::SetUp()
{
    model_ = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    frameNode_ = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    pattern_ = frameNode_->GetPattern<CanvasPattern>();
    ASSERT_NE(pattern_, nullptr);
    pattern_->paintMethod_ = AceType::MakeRefPtr<CanvasPaintMethod>();
    // Wire up a CanvasRenderContextDeferred so PushTask actually queues tasks
    // and NeedRender() can be used to verify delegation actually happened.
    pattern_->paintMethod_->canvasRenderContext_ = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    model_->weakPattern_ = pattern_;
}

void CanvasRenderingContext2DModelNGTest::TearDown()
{
    model_->Release();
    ViewStackProcessor::GetInstance()->ClearStack();
    model_ = nullptr;
    pattern_ = nullptr;
    frameNode_ = nullptr;
}

// ==================== SetOnAttach ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetOnAttach001, TestSize.Level1)
{
    bool called = false;
    model_->SetOnAttach([&called]() { called = true; });
    model_->isAttached_ = false;
    model_->SetPattern(pattern_);
    EXPECT_TRUE(called);
}

// ==================== SetOnDetach ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetOnDetach001, TestSize.Level1)
{
    bool called = false;
    model_->SetOnDetach([&called]() { called = true; });
    model_->isAttached_ = false;
    model_->SetPattern(pattern_);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode2 = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    ASSERT_NE(frameNode2, nullptr);
    auto pattern2 = frameNode2->GetPattern<CanvasPattern>();
    ASSERT_NE(pattern2, nullptr);
    pattern2->paintMethod_ = AceType::MakeRefPtr<CanvasPaintMethod>();
    pattern2->paintMethod_->canvasRenderContext_ = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    model_->SetPattern(pattern2);
    EXPECT_TRUE(called);
}

// ==================== GetId ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetId001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    EXPECT_EQ(nullModel->GetId(), -1);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetId002, TestSize.Level1)
{
    pattern_->id_ = 42;
    EXPECT_EQ(model_->GetId(), 42);
}

// ==================== SetPattern ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetPattern001, TestSize.Level1)
{
    auto nonPattern = AceType::MakeRefPtr<AceType>();
    model_->SetPattern(nonPattern);
    EXPECT_EQ(model_->weakPattern_.Upgrade(), AceType::DynamicCast<CanvasPattern>(pattern_));
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetPattern002, TestSize.Level1)
{
    model_->isAttached_ = false;
    model_->SetPattern(pattern_);
    EXPECT_TRUE(model_->isAttached_);
    model_->SetPattern(pattern_);
    EXPECT_TRUE(model_->isAttached_);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetPattern003, TestSize.Level1)
{
    model_->isAttached_ = false;
    model_->SetPattern(pattern_);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode2 = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    ASSERT_NE(frameNode2, nullptr);
    auto pattern2 = frameNode2->GetPattern<CanvasPattern>();
    ASSERT_NE(pattern2, nullptr);
    pattern2->paintMethod_ = AceType::MakeRefPtr<CanvasPaintMethod>();
    pattern2->paintMethod_->canvasRenderContext_ = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    model_->SetPattern(pattern2);
    EXPECT_TRUE(model_->isAttached_);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetPattern004, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->isAttached_ = false;
    nullModel->SetPattern(pattern_);
    EXPECT_TRUE(nullModel->isAttached_);
}

// ==================== Release ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, Release001, TestSize.Level1)
{
    EXPECT_NE(model_->weakPattern_.Upgrade(), nullptr);
    model_->Release();
    EXPECT_EQ(model_->weakPattern_.Upgrade(), nullptr);
}

// ==================== SetFillText ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillText001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    PaintState state;
    FillTextInfo info { "text", 1.0, 2.0, std::nullopt };
    nullModel->SetFillText(state, info);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillText002, TestSize.Level1)
{
    PaintState state;
    FillTextInfo info { "text", 1.0, 2.0, std::nullopt };
    model_->SetFillText(state, info);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetStrokeText ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeText001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    PaintState state;
    FillTextInfo info { "text", 1.0, 2.0, std::nullopt };
    nullModel->SetStrokeText(state, info);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeText002, TestSize.Level1)
{
    PaintState state;
    FillTextInfo info { "text", 1.0, 2.0, std::nullopt };
    model_->SetStrokeText(state, info);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetAntiAlias ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetAntiAlias001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetAntiAlias(true);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetAntiAlias002, TestSize.Level1)
{
    model_->SetAntiAlias(true);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== GetAntialiasExt ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetAntialiasExt001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    EXPECT_EQ(nullModel->GetAntialiasExt(), std::nullopt);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetAntialiasExt002, TestSize.Level1)
{
    pattern_->SetAntialiasExt(true);
    auto result = model_->GetAntialiasExt();
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result.value());
}

// ==================== SetAntialiasExt ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetAntialiasExt001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetAntialiasExt(std::nullopt);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetAntialiasExt002, TestSize.Level1)
{
    model_->SetAntialiasExt(true);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetFontWeight ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFontWeight001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFontWeight(FontWeight::W400);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFontWeight002, TestSize.Level1)
{
    model_->SetFontWeight(FontWeight::W700);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetFontStyle ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFontStyle001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFontStyle(FontStyle::NORMAL);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFontStyle002, TestSize.Level1)
{
    model_->SetFontStyle(FontStyle::ITALIC);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetFontFamilies ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFontFamilies001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFontFamilies({ "sans-serif" });
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFontFamilies002, TestSize.Level1)
{
    model_->SetFontFamilies({ "Arial", "sans-serif" });
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetFontSize ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFontSize001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFontSize(Dimension(16.0));
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFontSize002, TestSize.Level1)
{
    model_->SetFontSize(Dimension(20.0));
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetLetterSpacing ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLetterSpacing001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetLetterSpacing(Dimension(1.0));
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLetterSpacing002, TestSize.Level1)
{
    model_->SetLetterSpacing(Dimension(0.5));
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== GetLineDash ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetLineDash001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    auto result = nullModel->GetLineDash();
    EXPECT_TRUE(result.empty());
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetLineDash002, TestSize.Level1)
{
    std::vector<double> dash = { 5.0, 10.0 };
    pattern_->UpdateLineDash(dash);
    auto result = model_->GetLineDash();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], 5.0);
    EXPECT_EQ(result[1], 10.0);
}

// ==================== SetFillGradient ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillGradient001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFillGradient(nullptr);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillGradient002, TestSize.Level1)
{
    auto gradient = std::make_shared<Ace::Gradient>();
    model_->SetFillGradient(gradient);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetFillPattern ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillPattern001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFillPattern(nullptr);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillPattern002, TestSize.Level1)
{
    auto acePattern = std::make_shared<Ace::Pattern>();
    model_->SetFillPattern(acePattern);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetFillColor ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillColor001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFillColor(Color::BLACK, false);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillColor002, TestSize.Level1)
{
    model_->SetFillColor(Color::RED, true);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetStrokeGradient ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeGradient001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetStrokeGradient(nullptr);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeGradient002, TestSize.Level1)
{
    auto gradient = std::make_shared<Ace::Gradient>();
    model_->SetStrokeGradient(gradient);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetStrokePattern ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokePattern001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetStrokePattern(nullptr);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokePattern002, TestSize.Level1)
{
    auto acePattern = std::make_shared<Ace::Pattern>();
    model_->SetStrokePattern(acePattern);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetStrokeColor ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeColor001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetStrokeColor(Color::BLACK, false);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeColor002, TestSize.Level1)
{
    model_->SetStrokeColor(Color::BLUE, true);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== DrawImage ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, DrawImage001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    ImageInfo info {};
    nullModel->DrawImage(info);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, DrawImage002, TestSize.Level1)
{
    ImageInfo info {};
    info.imgWidth = 100.0;
    info.imgHeight = 100.0;
    model_->DrawImage(info);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== DrawSvgImage ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, DrawSvgImage001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    ImageInfo info {};
    nullModel->DrawSvgImage(info);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, DrawSvgImage002, TestSize.Level1)
{
    ImageInfo info {};
    model_->DrawSvgImage(info);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== PutImageData ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, PutImageData001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    Ace::ImageData data;
    nullModel->PutImageData(data);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, PutImageData002, TestSize.Level1)
{
    Ace::ImageData data;
    data.dirtyWidth = 10;
    data.dirtyHeight = 10;
    model_->PutImageData(data);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== CloseImageBitmap ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, CloseImageBitmap001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->CloseImageBitmap("src");
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, CloseImageBitmap002, TestSize.Level1)
{
    model_->CloseImageBitmap("test.png");
    // CloseImageBitmap body is compiled out under ACE_UNITTEST, so no task is queued.
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

// ==================== GetImageData ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetImageData001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    ImageSize size { 0, 0, 10, 10 };
    auto result = nullModel->GetImageData(size);
    EXPECT_EQ(result, nullptr);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetImageData002, TestSize.Level1)
{
    ImageSize size { 0, 0, 0, 0 };
    auto result = model_->GetImageData(size);
    EXPECT_EQ(result, nullptr);
}

// ==================== DrawPixelMap ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, DrawPixelMap001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    ImageInfo info {};
    nullModel->DrawPixelMap(info);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, DrawPixelMap002, TestSize.Level1)
{
    ImageInfo info {};
    model_->DrawPixelMap(info);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetFilterParam ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFilterParam001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFilterParam("filter");
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFilterParam002, TestSize.Level1)
{
    model_->SetFilterParam("blur(5px)");
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetTextDirection ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTextDirection001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetTextDirection(TextDirection::LTR);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTextDirection002, TestSize.Level1)
{
    model_->SetTextDirection(TextDirection::RTL);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== GetJsonData ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetJsonData001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    EXPECT_EQ(nullModel->GetJsonData("/path"), "");
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetJsonData002, TestSize.Level1)
{
    auto result = model_->GetJsonData("/path");
    // Under ACE_UNITTEST, CanvasPaintMethod::GetJsonData returns an empty string.
    EXPECT_TRUE(result.empty());
}

// ==================== ToDataURL ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, ToDataURL001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    EXPECT_EQ(nullModel->ToDataURL("image/png", 0.8), "");
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, ToDataURL002, TestSize.Level1)
{
    auto result = model_->ToDataURL("image/png", 0.8);
    // Under ACE_UNITTEST, CanvasPaintMethod::ToDataURL returns the UNSUPPORTED stub.
    EXPECT_EQ(result, UNSUPPORTED);
}

// ==================== SetLineCap ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineCap001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetLineCap(LineCapStyle::ROUND);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineCap002, TestSize.Level1)
{
    model_->SetLineCap(LineCapStyle::BUTT);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetLineJoin ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineJoin001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetLineJoin(LineJoinStyle::ROUND);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineJoin002, TestSize.Level1)
{
    model_->SetLineJoin(LineJoinStyle::MITER);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetMiterLimit ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetMiterLimit001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetMiterLimit(10.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetMiterLimit002, TestSize.Level1)
{
    model_->SetMiterLimit(5.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetLineWidth ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineWidth001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetLineWidth(2.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineWidth002, TestSize.Level1)
{
    model_->SetLineWidth(3.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetGlobalAlpha ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetGlobalAlpha001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetGlobalAlpha(0.5);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetGlobalAlpha002, TestSize.Level1)
{
    model_->SetGlobalAlpha(0.8);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetCompositeType ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetCompositeType001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetCompositeType(CompositeOperation::SOURCE_OVER);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetCompositeType002, TestSize.Level1)
{
    model_->SetCompositeType(CompositeOperation::COPY);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetLineDashOffset ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineDashOffset001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetLineDashOffset(5.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineDashOffset002, TestSize.Level1)
{
    model_->SetLineDashOffset(2.5);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetShadowBlur ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetShadowBlur001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetShadowBlur(3.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetShadowBlur002, TestSize.Level1)
{
    model_->SetShadowBlur(4.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetShadowColor ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetShadowColor001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetShadowColor(Color::BLACK);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetShadowColor002, TestSize.Level1)
{
    model_->SetShadowColor(Color::GREEN);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetShadowOffsetX ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetShadowOffsetX001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetShadowOffsetX(1.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetShadowOffsetX002, TestSize.Level1)
{
    model_->SetShadowOffsetX(3.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetShadowOffsetY ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetShadowOffsetY001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetShadowOffsetY(1.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetShadowOffsetY002, TestSize.Level1)
{
    model_->SetShadowOffsetY(3.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetSmoothingEnabled ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetSmoothingEnabled001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetSmoothingEnabled(true);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetSmoothingEnabled002, TestSize.Level1)
{
    model_->SetSmoothingEnabled(false);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetSmoothingQuality ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetSmoothingQuality001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetSmoothingQuality("low");
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetSmoothingQuality002, TestSize.Level1)
{
    model_->SetSmoothingQuality("high");
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== MoveTo ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, MoveTo001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->MoveTo(1.0, 2.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, MoveTo002, TestSize.Level1)
{
    model_->MoveTo(0.0, 0.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== LineTo ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, LineTo001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->LineTo(3.0, 4.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, LineTo002, TestSize.Level1)
{
    model_->LineTo(10.0, 10.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== BezierCurveTo ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, BezierCurveTo001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    BezierCurveParam param;
    nullModel->BezierCurveTo(param);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, BezierCurveTo002, TestSize.Level1)
{
    BezierCurveParam param;
    model_->BezierCurveTo(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== QuadraticCurveTo ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, QuadraticCurveTo001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    QuadraticCurveParam param;
    nullModel->QuadraticCurveTo(param);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, QuadraticCurveTo002, TestSize.Level1)
{
    QuadraticCurveParam param;
    model_->QuadraticCurveTo(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== ArcTo ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, ArcTo001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    ArcToParam param;
    nullModel->ArcTo(param);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, ArcTo002, TestSize.Level1)
{
    ArcToParam param;
    model_->ArcTo(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Arc ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, Arc001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    ArcParam param;
    nullModel->Arc(param);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, Arc002, TestSize.Level1)
{
    ArcParam param;
    model_->Arc(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Ellipse ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, Ellipse001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    EllipseParam param;
    nullModel->Ellipse(param);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, Ellipse002, TestSize.Level1)
{
    EllipseParam param;
    model_->Ellipse(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetFillRuleForPath ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillRuleForPath001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFillRuleForPath(CanvasFillRule::NONZERO);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillRuleForPath002, TestSize.Level1)
{
    model_->SetFillRuleForPath(CanvasFillRule::EVENODD);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetFillRuleForPath2D ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillRuleForPath2D001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetFillRuleForPath2D(CanvasFillRule::NONZERO, nullptr);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetFillRuleForPath2D002, TestSize.Level1)
{
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    model_->SetFillRuleForPath2D(CanvasFillRule::NONZERO, path);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetStrokeRuleForPath2D ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeRuleForPath2D001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetStrokeRuleForPath2D(CanvasFillRule::NONZERO, nullptr);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeRuleForPath2D002, TestSize.Level1)
{
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    model_->SetStrokeRuleForPath2D(CanvasFillRule::NONZERO, path);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetStrokeRuleForPath ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeRuleForPath001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetStrokeRuleForPath(CanvasFillRule::NONZERO);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetStrokeRuleForPath002, TestSize.Level1)
{
    model_->SetStrokeRuleForPath(CanvasFillRule::EVENODD);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetClipRuleForPath ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetClipRuleForPath001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetClipRuleForPath(CanvasFillRule::NONZERO);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetClipRuleForPath002, TestSize.Level1)
{
    model_->SetClipRuleForPath(CanvasFillRule::EVENODD);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetClipRuleForPath2D ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetClipRuleForPath2D001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetClipRuleForPath2D(CanvasFillRule::NONZERO, nullptr);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetClipRuleForPath2D002, TestSize.Level1)
{
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    model_->SetClipRuleForPath2D(CanvasFillRule::NONZERO, path);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== AddRect ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, AddRect001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    Rect rect(0.0, 0.0, 100.0, 100.0);
    nullModel->AddRect(rect);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, AddRect002, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    model_->AddRect(rect);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== AddRoundRect ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, AddRoundRect001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    Rect rect(0.0, 0.0, 100.0, 100.0);
    nullModel->AddRoundRect(rect, { 5.0, 5.0 });
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, AddRoundRect002, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    model_->AddRoundRect(rect, { 5.0, 5.0, 5.0, 5.0 });
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== BeginPath ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, BeginPath001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->BeginPath();
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, BeginPath002, TestSize.Level1)
{
    model_->BeginPath();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== ClosePath ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, ClosePath001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->ClosePath();
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, ClosePath002, TestSize.Level1)
{
    model_->ClosePath();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Restore ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, Restore001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->Restore();
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, Restore002, TestSize.Level1)
{
    model_->Restore();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== CanvasRendererSave ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, CanvasRendererSave001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->CanvasRendererSave();
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, CanvasRendererSave002, TestSize.Level1)
{
    model_->CanvasRendererSave();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== CanvasRendererRotate ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, CanvasRendererRotate001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->CanvasRendererRotate(45.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, CanvasRendererRotate002, TestSize.Level1)
{
    model_->CanvasRendererRotate(90.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== CanvasRendererScale ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, CanvasRendererScale001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->CanvasRendererScale(2.0, 2.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, CanvasRendererScale002, TestSize.Level1)
{
    model_->CanvasRendererScale(1.5, 1.5);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetTransform (TransformParam&, bool) ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTransformParam001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    TransformParam param;
    nullModel->SetTransform(param, true);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTransformParam002, TestSize.Level1)
{
    TransformParam param;
    param.scaleX = 2.0;
    model_->SetTransform(param, true);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== ResetTransform ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, ResetTransform001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->ResetTransform();
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, ResetTransform002, TestSize.Level1)
{
    model_->ResetTransform();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Transform ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, Transform001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    TransformParam param;
    nullModel->Transform(param);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, Transform002, TestSize.Level1)
{
    TransformParam param;
    model_->Transform(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Translate ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, Translate001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->Translate(10.0, 20.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, Translate002, TestSize.Level1)
{
    model_->Translate(10.0, 20.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetLineDash ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineDash001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetLineDash({ 1.0, 2.0 });
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetLineDash002, TestSize.Level1)
{
    model_->SetLineDash({ 5.0, 10.0 });
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetTextAlign ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTextAlign001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetTextAlign(TextAlign::LEFT);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTextAlign002, TestSize.Level1)
{
    model_->SetTextAlign(TextAlign::CENTER);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetTextBaseline ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTextBaseline001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetTextBaseline(TextBaseline::TOP);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTextBaseline002, TestSize.Level1)
{
    model_->SetTextBaseline(TextBaseline::MIDDLE);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== FillRect ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, FillRect001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    Rect rect(0.0, 0.0, 100.0, 100.0);
    nullModel->FillRect(rect);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, FillRect002, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    model_->FillRect(rect);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== StrokeRect ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, StrokeRect001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    Rect rect(0.0, 0.0, 100.0, 100.0);
    nullModel->StrokeRect(rect);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, StrokeRect002, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    model_->StrokeRect(rect);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== ClearRect ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, ClearRect001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    Rect rect(0.0, 0.0, 100.0, 100.0);
    nullModel->ClearRect(rect);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, ClearRect002, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    model_->ClearRect(rect);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== GetTransform ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetTransform001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    auto result = nullModel->GetTransform();
    EXPECT_EQ(result.scaleX, 0.0);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetTransform002, TestSize.Level1)
{
    auto result = model_->GetTransform();
    EXPECT_EQ(result.scaleX, 1.0);
}

// ==================== GetPixelMap ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetPixelMap001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    ImageSize size { 0, 0, 10, 10 };
    auto result = nullModel->GetPixelMap(size);
    EXPECT_EQ(result, nullptr);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetPixelMap002, TestSize.Level1)
{
    ImageSize size { 0, 0, 10, 10 };
    auto result = model_->GetPixelMap(size);
    EXPECT_EQ(result, nullptr);
}

// ==================== GetImageDataModel ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetImageDataModel001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    ImageSize size { 0, 0, 10, 10 };
    uint8_t buffer[16] = { 0 };
    nullModel->GetImageDataModel(size, buffer);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetImageDataModel002, TestSize.Level1)
{
    ImageSize size { 0, 0, 0, 0 };
    uint8_t buffer[16] = { 0 };
    model_->GetImageDataModel(size, buffer);
    // GetImageData returns nullptr (no frameNode in test), so no data is written and no task is queued.
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

// ==================== GetMeasureTextMetrics ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetMeasureTextMetrics001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    PaintState state;
    auto result = nullModel->GetMeasureTextMetrics(state, "text");
    EXPECT_EQ(result.width, 0.0);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetMeasureTextMetrics002, TestSize.Level1)
{
    PaintState state;
    auto result = model_->GetMeasureTextMetrics(state, "text");
    EXPECT_EQ(result.width, 0.0);
}

// ==================== SaveLayer ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SaveLayer001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SaveLayer();
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SaveLayer002, TestSize.Level1)
{
    model_->SaveLayer();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== RestoreLayer ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, RestoreLayer001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->RestoreLayer();
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, RestoreLayer002, TestSize.Level1)
{
    model_->RestoreLayer();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Reset ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, Reset001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->Reset();
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, Reset002, TestSize.Level1)
{
    model_->Reset();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetTransform (shared_ptr<Pattern>, TransformParam) ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTransformPattern001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    TransformParam param;
    nullModel->SetTransform(nullptr, param);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetTransformPattern002, TestSize.Level1)
{
    auto acePattern = std::make_shared<Ace::Pattern>();
    TransformParam param;
    model_->SetTransform(acePattern, param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== GetWidth ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetWidth001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    double width = 0.0;
    nullModel->GetWidth(width);
    EXPECT_EQ(width, 0.0);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetWidth002, TestSize.Level1)
{
    pattern_->canvasSize_ = SizeF(200.0f, 150.0f);
    double width = 0.0;
    model_->GetWidth(width);
    EXPECT_EQ(width, 200.0);
}

// ==================== GetHeight ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetHeight001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    double height = 0.0;
    nullModel->GetHeight(height);
    EXPECT_EQ(height, 0.0);
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, GetHeight002, TestSize.Level1)
{
    pattern_->canvasSize_ = SizeF(200.0f, 150.0f);
    double height = 0.0;
    model_->GetHeight(height);
    EXPECT_EQ(height, 150.0);
}

// ==================== SetDensity ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetDensity001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->SetDensity(1.0);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, SetDensity002, TestSize.Level1)
{
    model_->SetDensity(2.0);
    // SetDensity assigns density_ directly without queuing a render task.
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

// ==================== TransferFromImageBitmap ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, TransferFromImageBitmap001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    auto imageData = std::make_shared<Ace::ImageData>();
    nullModel->TransferFromImageBitmap(imageData);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, TransferFromImageBitmap002, TestSize.Level1)
{
    model_->TransferFromImageBitmap(nullptr);
    // Null input hits the CHECK_NULL_VOID guard and queues no render task.
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, TransferFromImageBitmap003, TestSize.Level1)
{
    auto imageData = std::make_shared<Ace::ImageData>();
    model_->TransferFromImageBitmap(imageData);
    // Task queueing is compiled out under ACE_UNITTEST, so no render task is queued.
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

// ==================== StartImageAnalyzer ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, StartImageAnalyzer001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    OnAnalyzedCallback onAnalyzed;
    nullModel->StartImageAnalyzer(nullptr, onAnalyzed);
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, StartImageAnalyzer002, TestSize.Level1)
{
    OnAnalyzedCallback onAnalyzed;
    model_->StartImageAnalyzer(nullptr, onAnalyzed);
    // Analyzer is disabled by default, so the callback returns early without queuing a task.
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

// ==================== StopImageAnalyzer ====================

HWTEST_F(CanvasRenderingContext2DModelNGTest, StopImageAnalyzer001, TestSize.Level1)
{
    auto nullModel = AceType::MakeRefPtr<CanvasRenderingContext2DModelNG>();
    nullModel->StopImageAnalyzer();
    // Null-pattern guard: no pattern attached; verifies CHECK_NULL_VOID returns early without crashing.
    SUCCEED();
}

HWTEST_F(CanvasRenderingContext2DModelNGTest, StopImageAnalyzer002, TestSize.Level1)
{
    model_->StopImageAnalyzer();
    // DestroyAnalyzerOverlay is a no-op without an analyzer manager, so no task is queued.
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}
} // namespace OHOS::Ace::NG
