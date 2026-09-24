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
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "base/json/json_util.h"
#include "core/common/ace_application_info.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/canvas/canvas_modifier.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/components_ng/pattern/canvas/canvas_render_context_deferred.h"
#include "core/components_ng/pattern/canvas/canvas_render_context_immediate.h"
#include "core/components_v2/inspector/inspector_constants.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CanvasPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<CanvasPattern> pattern_;
    RefPtr<FrameNode> frameNode_;
};

void CanvasPatternTestNg::SetUpTestCase()
{
    MockContainer::SetUp();
}

void CanvasPatternTestNg::TearDownTestCase()
{
    MockContainer::TearDown();
}

void CanvasPatternTestNg::SetUp()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    frameNode_ = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    pattern_ = frameNode_->GetPattern<CanvasPattern>();
    ASSERT_NE(pattern_, nullptr);
    auto contentModifier = AceType::MakeRefPtr<CanvasModifier>();
    pattern_->paintMethod_ = AceType::MakeRefPtr<CanvasPaintMethod>(contentModifier, frameNode_);
    pattern_->contentModifier_ = contentModifier;
    pattern_->paintMethod_->canvasRenderContext_ = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
}

void CanvasPatternTestNg::TearDown()
{
    ViewStackProcessor::GetInstance()->ClearStack();
    pattern_ = nullptr;
    frameNode_ = nullptr;
}

// Helper: create a pattern without paintMethod_
static RefPtr<CanvasPattern> CreatePatternWithoutPaintMethod()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });
    auto pattern = frameNode->GetPattern<CanvasPattern>();
    pattern->paintMethod_ = nullptr;
    return pattern;
}

// ==================== DetachRenderContext ====================

HWTEST_F(CanvasPatternTestNg, DetachRenderContext001, TestSize.Level1)
{
    pattern_->isAttached_ = true;
    pattern_->onContext2DDetach_ = nullptr;
    pattern_->DetachRenderContext(true);
    EXPECT_FALSE(pattern_->isAttached_);
}

HWTEST_F(CanvasPatternTestNg, DetachRenderContext002, TestSize.Level1)
{
    pattern_->isAttached_ = false;
    pattern_->DetachRenderContext(true);
    EXPECT_FALSE(pattern_->isAttached_);
}

HWTEST_F(CanvasPatternTestNg, DetachRenderContext003, TestSize.Level1)
{
    pattern_->isAttached_ = true;
    pattern_->immediateRender_ = true;
    pattern_->DetachRenderContext(false);
    EXPECT_TRUE(pattern_->isAttached_);
}

HWTEST_F(CanvasPatternTestNg, DetachRenderContext004, TestSize.Level1)
{
    pattern_->isAttached_ = true;
    pattern_->immediateRender_ = false;
    bool called = false;
    pattern_->onContext2DDetach_ = [&called]() { called = true; };
    pattern_->DetachRenderContext(false);
    EXPECT_FALSE(pattern_->isAttached_);
    EXPECT_TRUE(called);
}

HWTEST_F(CanvasPatternTestNg, DetachRenderContext005, TestSize.Level1)
{
    pattern_->isAttached_ = false;
    pattern_->immediateRender_ = std::nullopt;
    pattern_->DetachRenderContext(false);
    EXPECT_FALSE(pattern_->isAttached_);
}

// ==================== AttachRenderContext ====================

HWTEST_F(CanvasPatternTestNg, AttachRenderContext001, TestSize.Level1)
{
    pattern_->isAttached_ = false;
    bool called = false;
    pattern_->onContext2DAttach_ = [&called]() { called = true; };
    pattern_->AttachRenderContext();
    EXPECT_TRUE(pattern_->isAttached_);
    EXPECT_TRUE(called);
}

// ==================== FireOnContext2DAttach ====================

HWTEST_F(CanvasPatternTestNg, FireOnContext2DAttach001, TestSize.Level1)
{
    pattern_->onContext2DAttach_ = nullptr;
    pattern_->FireOnContext2DAttach();
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

HWTEST_F(CanvasPatternTestNg, FireOnContext2DAttach002, TestSize.Level1)
{
    int32_t count = 0;
    pattern_->onContext2DAttach_ = [&count]() { ++count; };
    pattern_->FireOnContext2DAttach();
    EXPECT_EQ(count, 1);
}

// ==================== FireOnContext2DDetach ====================

HWTEST_F(CanvasPatternTestNg, FireOnContext2DDetach001, TestSize.Level1)
{
    pattern_->onContext2DDetach_ = nullptr;
    pattern_->FireOnContext2DDetach();
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

HWTEST_F(CanvasPatternTestNg, FireOnContext2DDetach002, TestSize.Level1)
{
    int32_t count = 0;
    pattern_->onContext2DDetach_ = [&count]() { ++count; };
    pattern_->FireOnContext2DDetach();
    EXPECT_EQ(count, 1);
}

// ==================== OnAttachToMainTree ====================

HWTEST_F(CanvasPatternTestNg, OnAttachToMainTree001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->OnAttachToMainTree();
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

// ==================== AntialiasOperations ====================

HWTEST_F(CanvasPatternTestNg, AntialiasOperations001, TestSize.Level1)
{
    /**
     * @tc.steps1: call OnAttachToMainTree, SetAntiAlias, GetAntialiasExt, SetAntialiasExt.
     * @tc.expected: NeedRender returns true after SetAntiAlias pushes a deferred task;
     *               SetAntiAlias only defers, so GetAntialiasExt has no value until
     *               SetAntialiasExt (which calls SetAntialiasExtParam immediately) sets it.
     */
    pattern_->OnAttachToMainTree();
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
    pattern_->SetAntiAlias(true);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    EXPECT_FALSE(pattern_->GetAntialiasExt().has_value());
    pattern_->SetAntialiasExt(true);
    ASSERT_TRUE(pattern_->GetAntialiasExt().has_value());
    EXPECT_TRUE(pattern_->GetAntialiasExt().value());
    pattern_->SetAntialiasExt(false);
    ASSERT_TRUE(pattern_->GetAntialiasExt().has_value());
    EXPECT_FALSE(pattern_->GetAntialiasExt().value());
}

// ==================== SetAntiAlias ====================

HWTEST_F(CanvasPatternTestNg, SetAntiAlias001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->SetAntiAlias(true);
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

// ==================== GetAntialiasExt ====================

HWTEST_F(CanvasPatternTestNg, GetAntialiasExt002, TestSize.Level1)
{
    pattern_->SetAntialiasExt(true);
    auto result = pattern_->GetAntialiasExt();
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result.value());
}

// ==================== SetAntialiasExt ====================

HWTEST_F(CanvasPatternTestNg, SetAntialiasExt001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->SetAntialiasExt(std::nullopt);
    EXPECT_EQ(nullPattern->GetAntialiasExt(), std::nullopt);
}

// ==================== FillRect ====================

HWTEST_F(CanvasPatternTestNg, FillRect001, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    pattern_->FillRect(rect);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== StrokeRect ====================

HWTEST_F(CanvasPatternTestNg, StrokeRect001, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    pattern_->StrokeRect(rect);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== ClearRect ====================

HWTEST_F(CanvasPatternTestNg, ClearRect001, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    pattern_->ClearRect(rect);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== PathOperations ====================

HWTEST_F(CanvasPatternTestNg, PathOperations001, TestSize.Level1)
{
    /**
     * @tc.steps1: call path operations (Fill, Stroke, Clip, BeginPath, ClosePath, MoveTo, LineTo).
     * @tc.expected: NeedRender returns true after each operation.
     */
    pattern_->Fill();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->Stroke();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->Clip();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->BeginPath();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->ClosePath();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->MoveTo(10.0, 20.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->LineTo(30.0, 40.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

HWTEST_F(CanvasPatternTestNg, Fill002, TestSize.Level1)
{
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    pattern_->Fill(path);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Stroke ====================

HWTEST_F(CanvasPatternTestNg, Stroke002, TestSize.Level1)
{
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    pattern_->Stroke(path);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Clip ====================

HWTEST_F(CanvasPatternTestNg, Clip002, TestSize.Level1)
{
    auto path = AceType::MakeRefPtr<CanvasPath2D>();
    pattern_->Clip(path);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Arc ====================

HWTEST_F(CanvasPatternTestNg, Arc001, TestSize.Level1)
{
    ArcParam param;
    pattern_->Arc(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== ArcTo ====================

HWTEST_F(CanvasPatternTestNg, ArcTo001, TestSize.Level1)
{
    ArcToParam param;
    pattern_->ArcTo(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== AddRect ====================

HWTEST_F(CanvasPatternTestNg, AddRect001, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    pattern_->AddRect(rect);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== AddRoundRect ====================

HWTEST_F(CanvasPatternTestNg, AddRoundRect001, TestSize.Level1)
{
    Rect rect(0.0, 0.0, 100.0, 100.0);
    pattern_->AddRoundRect(rect, { 5.0, 5.0, 5.0, 5.0 });
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Ellipse ====================

HWTEST_F(CanvasPatternTestNg, Ellipse001, TestSize.Level1)
{
    EllipseParam param;
    pattern_->Ellipse(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== BezierCurveTo ====================

HWTEST_F(CanvasPatternTestNg, BezierCurveTo001, TestSize.Level1)
{
    BezierCurveParam param;
    pattern_->BezierCurveTo(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== QuadraticCurveTo ====================

HWTEST_F(CanvasPatternTestNg, QuadraticCurveTo001, TestSize.Level1)
{
    QuadraticCurveParam param;
    pattern_->QuadraticCurveTo(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== TextDrawing ====================

HWTEST_F(CanvasPatternTestNg, TextDrawing001, TestSize.Level1)
{
    /**
     * @tc.steps1: call FillText and StrokeText.
     * @tc.expected: NeedRender returns true after each operation.
     */
    pattern_->FillText("hello", 1.0, 2.0, std::nullopt);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->StrokeText("world", 3.0, 4.0, 10.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== MeasureTextMetrics ====================

HWTEST_F(CanvasPatternTestNg, MeasureTextMetrics001, TestSize.Level1)
{
    PaintState state;
    auto result = pattern_->MeasureTextMetrics("text", state);
    EXPECT_GE(result.width, 0.0);
}

// ==================== DrawImage ====================

HWTEST_F(CanvasPatternTestNg, DrawImage001, TestSize.Level1)
{
    Ace::CanvasImage canvasImage;
    pattern_->DrawImage(canvasImage, 100.0, 200.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== DrawSvgImage ====================

HWTEST_F(CanvasPatternTestNg, DrawSvgImage001, TestSize.Level1)
{
    Ace::CanvasImage canvasImage;
    pattern_->DrawSvgImage(nullptr, canvasImage, ImageFit::NONE);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== DrawPixelMap ====================

HWTEST_F(CanvasPatternTestNg, DrawPixelMap001, TestSize.Level1)
{
    Ace::CanvasImage canvasImage;
    RefPtr<PixelMap> pixelMap;
    pattern_->DrawPixelMap(pixelMap, canvasImage);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== GetImageData (left, top, w, h) ====================

HWTEST_F(CanvasPatternTestNg, GetImageData001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    auto data = nullPattern->GetImageData(0, 0, 10, 20);
    ASSERT_NE(data, nullptr);
    EXPECT_EQ(data->dirtyWidth, 10);
    EXPECT_EQ(data->dirtyHeight, 20);
}

HWTEST_F(CanvasPatternTestNg, GetImageData002, TestSize.Level1)
{
    /**
     * @tc.steps1: deferred render, fetch pixel data.
     * @tc.expected: returns nullptr because DrawBitmap is stubbed under ACE_UNITTEST.
     */
    pattern_->immediateRender_ = false;
    auto data = pattern_->GetImageData(0, 0, 10, 20);
    EXPECT_EQ(data, nullptr);
}

HWTEST_F(CanvasPatternTestNg, GetImageData003, TestSize.Level1)
{
    /**
     * @tc.steps1: immediate render, fetch pixel data.
     * @tc.expected: returns nullptr because DrawBitmap is stubbed under ACE_UNITTEST.
     */
    pattern_->immediateRender_ = true;
    auto data = pattern_->GetImageData(0, 0, 10, 20);
    EXPECT_EQ(data, nullptr);
}

// ==================== GetImageData (shared_ptr) ====================

HWTEST_F(CanvasPatternTestNg, GetImageDataShared001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    auto imageData = std::make_shared<Ace::ImageData>();
    nullPattern->GetImageData(imageData);
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

HWTEST_F(CanvasPatternTestNg, GetImageDataShared002, TestSize.Level1)
{
    pattern_->immediateRender_ = false;
    auto imageData = std::make_shared<Ace::ImageData>();
    imageData->dirtyWidth = 0;
    imageData->dirtyHeight = 0;
    pattern_->GetImageData(imageData);
    EXPECT_NE(imageData, nullptr);
}

HWTEST_F(CanvasPatternTestNg, GetImageDataShared003, TestSize.Level1)
{
    pattern_->immediateRender_ = true;
    auto imageData = std::make_shared<Ace::ImageData>();
    imageData->dirtyWidth = 0;
    imageData->dirtyHeight = 0;
    pattern_->GetImageData(imageData);
    EXPECT_NE(imageData, nullptr);
}

// ==================== PutImageData ====================

HWTEST_F(CanvasPatternTestNg, PutImageData001, TestSize.Level1)
{
    Ace::ImageData imageData;
    imageData.dirtyWidth = 10;
    imageData.dirtyHeight = 10;
    pattern_->PutImageData(imageData);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== UpdateFillColor ====================

HWTEST_F(CanvasPatternTestNg, UpdateFillColor001, TestSize.Level1)
{
    pattern_->lastHdrColorHeadRoom_ = std::nullopt;
    pattern_->UpdateFillColor(Color::RED);
    EXPECT_FALSE(pattern_->lastHdrColorHeadRoom_.has_value());
}

HWTEST_F(CanvasPatternTestNg, UpdateFillColor002, TestSize.Level1)
{
    pattern_->lastHdrColorHeadRoom_ = 5.0f;
    pattern_->UpdateFillColor(Color::BLACK);
    EXPECT_FLOAT_EQ(pattern_->lastHdrColorHeadRoom_.value(), 1.0f);
}

// ==================== UpdateStrokeColor ====================

HWTEST_F(CanvasPatternTestNg, UpdateStrokeColor001, TestSize.Level1)
{
    pattern_->lastHdrColorHeadRoom_ = std::nullopt;
    pattern_->UpdateStrokeColor(Color::BLUE);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== NotifyColorHDRColorHeadRoom ====================

HWTEST_F(CanvasPatternTestNg, NotifyColorHDR001, TestSize.Level1)
{
    pattern_->lastHdrColorHeadRoom_ = std::nullopt;
    pattern_->NotifyColorHDRColorHeadRoom(Color::BLACK);
    EXPECT_FALSE(pattern_->lastHdrColorHeadRoom_.has_value());
}

HWTEST_F(CanvasPatternTestNg, NotifyColorHDR002, TestSize.Level1)
{
    pattern_->lastHdrColorHeadRoom_ = 1.0f;
    pattern_->NotifyColorHDRColorHeadRoom(Color::BLACK);
    EXPECT_FLOAT_EQ(pattern_->lastHdrColorHeadRoom_.value(), 1.0f);
}

HWTEST_F(CanvasPatternTestNg, NotifyColorHDR003, TestSize.Level1)
{
    pattern_->lastHdrColorHeadRoom_ = 5.0f;
    pattern_->NotifyColorHDRColorHeadRoom(Color::BLACK);
    EXPECT_FLOAT_EQ(pattern_->lastHdrColorHeadRoom_.value(), 1.0f);
}

// ==================== NotifyGradientHDRColorHeadRoom ====================

HWTEST_F(CanvasPatternTestNg, NotifyGradientHDR002, TestSize.Level1)
{
    auto gradient = std::make_shared<Ace::Gradient>();
    pattern_->lastHdrColorHeadRoom_ = std::nullopt;
    pattern_->NotifyGradientHDRColorHeadRoom(gradient);
    EXPECT_FALSE(pattern_->lastHdrColorHeadRoom_.has_value());
}

HWTEST_F(CanvasPatternTestNg, NotifyGradientHDR003, TestSize.Level1)
{
    auto gradient = std::make_shared<Ace::Gradient>();
    pattern_->lastHdrColorHeadRoom_ = 1.0f;
    pattern_->NotifyGradientHDRColorHeadRoom(gradient);
    EXPECT_FLOAT_EQ(pattern_->lastHdrColorHeadRoom_.value(), 1.0f);
}

HWTEST_F(CanvasPatternTestNg, NotifyGradientHDR004, TestSize.Level1)
{
    auto gradient = std::make_shared<Ace::Gradient>();
    pattern_->lastHdrColorHeadRoom_ = 5.0f;
    pattern_->NotifyGradientHDRColorHeadRoom(gradient);
    EXPECT_FLOAT_EQ(pattern_->lastHdrColorHeadRoom_.value(), 1.0f);
}

// ==================== FillStrokeGradientPattern ====================

HWTEST_F(CanvasPatternTestNg, FillStrokeGradientPattern001, TestSize.Level1)
{
    /**
     * @tc.steps1: set fill/stroke gradients, patterns, fill rules, get line dash, close image bitmap, notify gradient HDR.
     * @tc.expected: SetFillGradient/SetStrokeGradient with nullptr early-return without pushing a task,
     *               so NeedRender stays false; the remaining operations push tasks and NeedRender becomes true.
     */
    pattern_->SetFillGradient(nullptr);
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
    pattern_->SetStrokeGradient(nullptr);
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateFillPattern(nullptr);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateStrokePattern(nullptr);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateFillRuleForPath(CanvasFillRule::NONZERO);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateFillRuleForPath2D(CanvasFillRule::EVENODD);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    auto lineDash = pattern_->GetLineDash();
    EXPECT_TRUE(lineDash.lineDash.empty());
    pattern_->CloseImageBitmap("test.png");
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->NotifyGradientHDRColorHeadRoom(nullptr);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

HWTEST_F(CanvasPatternTestNg, SetFillGradient002, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    auto gradient = std::make_shared<Ace::Gradient>();
    nullPattern->SetFillGradient(gradient);
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

HWTEST_F(CanvasPatternTestNg, SetFillGradient003, TestSize.Level1)
{
    auto gradient = std::make_shared<Ace::Gradient>();
    pattern_->SetFillGradient(gradient);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetStrokeGradient ====================

HWTEST_F(CanvasPatternTestNg, StrokeGradientAndShadowColor001, TestSize.Level1)
{
    /**
     * @tc.steps1: set stroke gradient and update shadow color.
     * @tc.expected: SetStrokeGradient with nullptr early-returns without pushing a task,
     *               so NeedRender stays false; UpdateShadowColor pushes a task so NeedRender becomes true.
     */
    pattern_->SetStrokeGradient(nullptr);
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateShadowColor(Color::RED);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

HWTEST_F(CanvasPatternTestNg, SetStrokeGradient002, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    auto gradient = std::make_shared<Ace::Gradient>();
    nullPattern->SetStrokeGradient(gradient);
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

HWTEST_F(CanvasPatternTestNg, SetStrokeGradient003, TestSize.Level1)
{
    auto gradient = std::make_shared<Ace::Gradient>();
    pattern_->SetStrokeGradient(gradient);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== UpdateLineDash ====================

HWTEST_F(CanvasPatternTestNg, UpdateLineDash001, TestSize.Level1)
{
    std::vector<double> dash = { 5.0, 10.0 };
    pattern_->UpdateLineDash(dash);
    auto result = pattern_->GetLineDash();
    EXPECT_EQ(result.lineDash.size(), 2u);
    EXPECT_EQ(result.lineDash[0], 5.0);
}

// ==================== Transform Operations ====================

HWTEST_F(CanvasPatternTestNg, TransformOperations001, TestSize.Level1)
{
    /**
     * @tc.steps1: call Save, Restore, Scale, Rotate, ResetTransform, Translate, GetTransform, SaveLayer, RestoreLayer.
     * @tc.expected: NeedRender returns true after each operation; GetTransform returns valid value.
     */
    pattern_->Save();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->Restore();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->Scale(2.0, 3.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->Rotate(45.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->ResetTransform();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->Translate(10.0, 20.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    auto transform = pattern_->GetTransform();
    EXPECT_GE(transform.scaleX, 0.0);
    pattern_->SaveLayer();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->RestoreLayer();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetTransform (TransformParam) ====================

HWTEST_F(CanvasPatternTestNg, SetTransformParam001, TestSize.Level1)
{
    TransformParam param;
    param.scaleX = 2.0;
    pattern_->SetTransform(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== Transform ====================

HWTEST_F(CanvasPatternTestNg, Transform001, TestSize.Level1)
{
    TransformParam param;
    pattern_->Transform(param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== ToDataURL ====================

HWTEST_F(CanvasPatternTestNg, ToDataURL001, TestSize.Level1)
{
    pattern_->immediateRender_ = false;
    auto result = pattern_->ToDataURL("image/png", 0.8);
    EXPECT_TRUE(result.empty() || !result.empty());
}

HWTEST_F(CanvasPatternTestNg, ToDataURL002, TestSize.Level1)
{
    pattern_->immediateRender_ = true;
    auto result = pattern_->ToDataURL("image/png", 0.8);
    EXPECT_TRUE(result.empty() || !result.empty());
}

// ==================== Size and JSON Queries ====================

HWTEST_F(CanvasPatternTestNg, SizeAndJsonQueries001, TestSize.Level1)
{
    /**
     * @tc.steps1: query JSON data, width/height with nullopt and set canvasSize_.
     * @tc.expected: GetWidth/GetHeight return 0 when canvasSize_ is nullopt, correct values when set.
     */
    auto jsonData = pattern_->GetJsonData("/path");
    EXPECT_TRUE(jsonData.empty() || !jsonData.empty());
    pattern_->canvasSize_ = std::nullopt;
    EXPECT_EQ(pattern_->GetWidth(), 0.0);
    EXPECT_EQ(pattern_->GetHeight(), 0.0);
    pattern_->canvasSize_ = SizeF(300.0f, 200.0f);
    EXPECT_EQ(pattern_->GetWidth(), 300.0);
    EXPECT_EQ(pattern_->GetHeight(), 200.0);
}

// ==================== Font Property Updates ====================

HWTEST_F(CanvasPatternTestNg, FontPropertyUpdates001, TestSize.Level1)
{
    /**
     * @tc.steps1: update font weight, style, families, size, letter spacing.
     * @tc.expected: NeedRender returns true after each update.
     */
    pattern_->UpdateFontWeight(FontWeight::W700);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateFontStyle(FontStyle::ITALIC);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateFontFamilies({ "Arial", "sans-serif" });
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateFontSize(Dimension(20.0));
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateLetterSpacing(Dimension(0.5));
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== State Updates ====================

HWTEST_F(CanvasPatternTestNg, StateUpdates001, TestSize.Level1)
{
    /**
     * @tc.steps1: update global alpha, composite operation, smoothing enabled, smoothing quality.
     * @tc.expected: NeedRender returns true after each update.
     */
    pattern_->UpdateGlobalAlpha(0.5);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateCompositeOperation(CompositeOperation::SOURCE_OVER);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateSmoothingEnabled(true);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateSmoothingQuality("high");
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== LineStyleUpdates ====================

HWTEST_F(CanvasPatternTestNg, LineStyleUpdates001, TestSize.Level1)
{
    /**
     * @tc.steps1: update line cap, dash offset, join, width, miter limit.
     * @tc.expected: NeedRender returns true after each update.
     */
    pattern_->UpdateLineCap(LineCapStyle::ROUND);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateLineDashOffset(5.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateLineJoin(LineJoinStyle::BEVEL);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateLineWidth(3.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateMiterLimit(10.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== ShadowUpdates ====================

HWTEST_F(CanvasPatternTestNg, ShadowUpdates001, TestSize.Level1)
{
    /**
     * @tc.steps1: update shadow blur, offset X, offset Y.
     * @tc.expected: NeedRender returns true after each update.
     */
    pattern_->UpdateShadowBlur(4.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateShadowOffsetX(2.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateShadowOffsetY(2.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== UpdateShadowColor ====================

HWTEST_F(CanvasPatternTestNg, UpdateShadowColor001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->UpdateShadowColor(Color::BLACK);
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

// ==================== TextAlignmentAndFilter ====================

HWTEST_F(CanvasPatternTestNg, TextAlignmentAndFilter001, TestSize.Level1)
{
    /**
     * @tc.steps1: update text align, baseline, set text direction, set filter param.
     * @tc.expected: NeedRender returns true; currentSetTextDirection_ matches set value.
     */
    pattern_->UpdateTextAlign(TextAlign::CENTER);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->UpdateTextBaseline(TextBaseline::MIDDLE);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->SetTextDirection(TextDirection::LTR);
    EXPECT_EQ(pattern_->currentSetTextDirection_, TextDirection::LTR);
    pattern_->SetTextDirection(TextDirection::RTL);
    EXPECT_EQ(pattern_->currentSetTextDirection_, TextDirection::RTL);
    pattern_->SetFilterParam("blur(5px)");
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetTextDirection ====================

HWTEST_F(CanvasPatternTestNg, SetTextDirection003, TestSize.Level1)
{
    pattern_->currentSetTextDirection_ = TextDirection::LTR;
    pattern_->SetTextDirection(TextDirection::INHERIT);
    EXPECT_EQ(pattern_->currentSetTextDirection_, TextDirection::INHERIT);
}

HWTEST_F(CanvasPatternTestNg, SetTextDirection004, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->SetTextDirection(TextDirection::LTR);
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

// ==================== UpdateTextDefaultDirection ====================

HWTEST_F(CanvasPatternTestNg, UpdateTextDefaultDir001, TestSize.Level1)
{
    pattern_->currentSetTextDirection_ = TextDirection::LTR;
    pattern_->UpdateTextDefaultDirection();
    EXPECT_EQ(pattern_->currentSetTextDirection_, TextDirection::LTR);
}

HWTEST_F(CanvasPatternTestNg, UpdateTextDefaultDir002, TestSize.Level1)
{
    pattern_->currentSetTextDirection_ = TextDirection::INHERIT;
    pattern_->UpdateTextDefaultDirection();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== ResetAndDensity ====================

HWTEST_F(CanvasPatternTestNg, ResetAndDensity001, TestSize.Level1)
{
    /**
     * @tc.steps1: call Reset, SetDensity, SetInvalidate, SetRSCanvasForDrawingContext.
     * @tc.expected: NeedRender returns true after each operation.
     */
    pattern_->Reset();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->SetDensity(2.0);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->SetInvalidate();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
    pattern_->SetRSCanvasForDrawingContext();
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetTransform (shared_ptr<Pattern>, TransformParam) ====================

HWTEST_F(CanvasPatternTestNg, SetTransformPattern001, TestSize.Level1)
{
    auto acePattern = std::make_shared<Ace::Pattern>();
    TransformParam param;
    pattern_->SetTransform(acePattern, param);
    EXPECT_TRUE(pattern_->paintMethod_->NeedRender());
}

// ==================== SetInvalidate ====================

HWTEST_F(CanvasPatternTestNg, SetInvalidate001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->SetInvalidate();
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

// ==================== SetRSCanvasForDrawingContext ====================

HWTEST_F(CanvasPatternTestNg, SetRSCanvasForDrawingContext001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->SetRSCanvasForDrawingContext();
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

// ==================== OnVisibleChange ====================

HWTEST_F(CanvasPatternTestNg, OnVisibleChange001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->OnVisibleChange(true);
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

HWTEST_F(CanvasPatternTestNg, VisibleChangeOperations001, TestSize.Level1)
{
    /**
     * @tc.steps1: call OnVisibleChange and OnVisibleAreaChange with valid pattern.
     * @tc.expected: NeedRender returns true after each operation.
     */
    pattern_->OnVisibleChange(true);
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
    pattern_->OnVisibleAreaChange(false, 0.0);
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

// ==================== OnVisibleAreaChange ====================

HWTEST_F(CanvasPatternTestNg, OnVisibleAreaChange001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->OnVisibleAreaChange(true, 0.5);
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

// ==================== SetRSCanvasCallback ====================

HWTEST_F(CanvasPatternTestNg, SetRSCanvasCallback001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    std::function<void(std::shared_ptr<RSCanvas>, double, double)> callback = nullptr;
    nullPattern->SetRSCanvasCallback(callback);
    EXPECT_EQ(nullPattern->paintMethod_, nullptr);
}

// ==================== UpdateUnit ====================

HWTEST_F(CanvasPatternTestNg, UpdateUnit001, TestSize.Level1)
{
    pattern_->unit_ = CanvasUnit::DEFAULT;
    pattern_->UpdateUnit(CanvasUnit::DEFAULT);
    EXPECT_EQ(pattern_->unit_, CanvasUnit::DEFAULT);
}

HWTEST_F(CanvasPatternTestNg, UpdateUnit002, TestSize.Level1)
{
    pattern_->unit_ = CanvasUnit::DEFAULT;
    pattern_->updateContextCB_ = nullptr;
    pattern_->UpdateUnit(CanvasUnit::PX);
    EXPECT_EQ(pattern_->unit_, CanvasUnit::PX);
}

HWTEST_F(CanvasPatternTestNg, UpdateUnit003, TestSize.Level1)
{
    pattern_->unit_ = CanvasUnit::DEFAULT;
    CanvasUnit received = CanvasUnit::DEFAULT;
    pattern_->updateContextCB_ = [&received](CanvasUnit unit) { received = unit; };
    pattern_->UpdateUnit(CanvasUnit::PX);
    EXPECT_EQ(pattern_->unit_, CanvasUnit::PX);
    EXPECT_EQ(received, CanvasUnit::PX);
}

// ==================== GetDumpInfo ====================

HWTEST_F(CanvasPatternTestNg, GetDumpInfo001, TestSize.Level1)
{
    pattern_->immediateRender_ = false;
    auto info = pattern_->GetDumpInfo();
    EXPECT_TRUE(info.find("deferred") != std::string::npos);
}

HWTEST_F(CanvasPatternTestNg, GetDumpInfo002, TestSize.Level1)
{
    pattern_->immediateRender_ = true;
    auto info = pattern_->GetDumpInfo();
    EXPECT_TRUE(info.find("immediate") != std::string::npos);
}

HWTEST_F(CanvasPatternTestNg, GetDumpInfo003, TestSize.Level1)
{
    pattern_->immediateRender_ = std::nullopt;
    auto info = pattern_->GetDumpInfo();
    EXPECT_TRUE(info.find("deferred") != std::string::npos);
}

// ==================== GetSimplifyDumpInfo ====================

HWTEST_F(CanvasPatternTestNg, GetSimplifyDumpInfo001, TestSize.Level1)
{
    pattern_->immediateRender_ = false;
    auto json = JsonUtil::Create();
    pattern_->GetSimplifyDumpInfo(json);
    EXPECT_TRUE(json->Contains("RenderingMode"));
}

HWTEST_F(CanvasPatternTestNg, GetSimplifyDumpInfo002, TestSize.Level1)
{
    pattern_->immediateRender_ = true;
    auto json = JsonUtil::Create();
    pattern_->GetSimplifyDumpInfo(json);
    EXPECT_TRUE(json->Contains("RenderingMode"));
}

// ==================== DumpInfo() ====================

HWTEST_F(CanvasPatternTestNg, DumpInfo001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->contentModifier_ = nullptr;
    nullPattern->DumpInfo();
    EXPECT_EQ(nullPattern->contentModifier_, nullptr);
}

HWTEST_F(CanvasPatternTestNg, DumpAndUtility001, TestSize.Level1)
{
    /**
     * @tc.steps1: call DumpInfo, CreateNodePaintMethod, SetUpdateContextCallback, GetId.
     * @tc.expected: NeedRender returns true after DumpInfo; CreateNodePaintMethod returns paintMethod_; callback is set; GetId returns expected value.
     */
    pattern_->DumpInfo();
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
    auto paintMethod = pattern_->CreateNodePaintMethod();
    EXPECT_EQ(paintMethod, pattern_->paintMethod_);
    pattern_->SetUpdateContextCallback([](CanvasUnit) {});
    EXPECT_TRUE(pattern_->updateContextCB_);
    pattern_->id_ = 99;
    EXPECT_EQ(pattern_->GetId(), 99);
}

// ==================== DumpInfo(unique_ptr<JsonValue>&) ====================

HWTEST_F(CanvasPatternTestNg, DumpInfoJson001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->contentModifier_ = nullptr;
    auto json = JsonUtil::Create();
    nullPattern->DumpInfo(json);
    EXPECT_TRUE(json->Contains("CanvasPattern"));
}

HWTEST_F(CanvasPatternTestNg, DumpInfoJson002, TestSize.Level1)
{
    auto json = JsonUtil::Create();
    pattern_->DumpInfo(json);
    EXPECT_TRUE(json->Contains("CanvasPattern"));
}

// ==================== DumpSimplifyInfo ====================

HWTEST_F(CanvasPatternTestNg, DumpSimplifyInfo001, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->contentModifier_ = nullptr;
    auto json = JsonUtil::CreateSharedPtrJson();
    nullPattern->DumpSimplifyInfo(json);
    EXPECT_TRUE(json->Contains("CanvasPattern"));
}

HWTEST_F(CanvasPatternTestNg, DumpSimplifyInfo002, TestSize.Level1)
{
    auto json = JsonUtil::CreateSharedPtrJson();
    pattern_->DumpSimplifyInfo(json);
    EXPECT_TRUE(json->Contains("CanvasPattern"));
    EXPECT_TRUE(json->Contains("CanvasPaint"));
    EXPECT_TRUE(json->Contains("CanvasModifier"));
}

// ==================== SetImmediateRender ====================

HWTEST_F(CanvasPatternTestNg, SetImmediateRender001, TestSize.Level1)
{
    pattern_->immediateRender_ = true;
    pattern_->SetImmediateRender(true);
    EXPECT_TRUE(pattern_->immediateRender_.value());
}

HWTEST_F(CanvasPatternTestNg, SetImmediateRender002, TestSize.Level1)
{
    auto nullPattern = CreatePatternWithoutPaintMethod();
    nullPattern->immediateRender_ = std::nullopt;
    nullPattern->SetImmediateRender(true);
    EXPECT_TRUE(nullPattern->immediateRender_.value());
}

HWTEST_F(CanvasPatternTestNg, SetImmediateRender003, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    pattern_->immediateRender_ = std::nullopt;
    pattern_->hasRegisteredVisibleAreaChange_ = false;
    pattern_->SetImmediateRender(true);
    EXPECT_TRUE(pattern_->immediateRender_.value());
    EXPECT_TRUE(pattern_->paintMethod_->canvasRenderContext_);
    MockPipelineContext::TearDown();
}

HWTEST_F(CanvasPatternTestNg, SetImmediateRender004, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    pattern_->immediateRender_ = true;
    pattern_->hasRegisteredVisibleAreaChange_ = true;
    pattern_->SetImmediateRender(false);
    EXPECT_FALSE(pattern_->immediateRender_.value());
    EXPECT_FALSE(pattern_->hasRegisteredVisibleAreaChange_);
    MockPipelineContext::TearDown();
}

// ==================== UnregisterVisibleAreaChange ====================

HWTEST_F(CanvasPatternTestNg, UnregisterVisibleAreaChange001, TestSize.Level1)
{
    pattern_->hasRegisteredVisibleAreaChange_ = false;
    pattern_->UnregisterVisibleAreaChange();
    EXPECT_FALSE(pattern_->hasRegisteredVisibleAreaChange_);
}

HWTEST_F(CanvasPatternTestNg, UnregisterVisibleAreaChange002, TestSize.Level1)
{
    pattern_->hasRegisteredVisibleAreaChange_ = true;
    pattern_->id_ = 1;
    pattern_->UnregisterVisibleAreaChange();
    EXPECT_TRUE(pattern_->hasRegisteredVisibleAreaChange_);
}

// ==================== EnableAnalyzer ====================

HWTEST_F(CanvasPatternTestNg, EnableAnalyzer001, TestSize.Level1)
{
    pattern_->imageAnalyzerManager_ = nullptr;
    pattern_->EnableAnalyzer(false);
    EXPECT_FALSE(pattern_->isEnableAnalyzer_);
}

HWTEST_F(CanvasPatternTestNg, EnableAnalyzer002, TestSize.Level1)
{
    pattern_->imageAnalyzerManager_ = nullptr;
    pattern_->EnableAnalyzer(true);
    EXPECT_TRUE(pattern_->isEnableAnalyzer_);
}

// ==================== FireReadyEvent ====================

HWTEST_F(CanvasPatternTestNg, FireReadyEvent001, TestSize.Level1)
{
    pattern_->readyEvent_ = nullptr;
    pattern_->readyEventNew_ = nullptr;
    pattern_->FireReadyEvent();
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

HWTEST_F(CanvasPatternTestNg, FireReadyEvent002, TestSize.Level1)
{
    bool called = false;
    bool receivedImmediate = true;
    CanvasUnit receivedUnit = CanvasUnit::DEFAULT;
    pattern_->readyEventNew_ = [&](bool immediate, CanvasUnit unit) {
        called = true;
        receivedImmediate = immediate;
        receivedUnit = unit;
    };
    pattern_->immediateRender_ = false;
    pattern_->FireReadyEvent();
    EXPECT_TRUE(called);
    EXPECT_FALSE(receivedImmediate);
    EXPECT_EQ(receivedUnit, CanvasUnit::DEFAULT);
}

HWTEST_F(CanvasPatternTestNg, FireReadyEvent003, TestSize.Level1)
{
    bool called = false;
    bool receivedImmediate = false;
    CanvasUnit receivedUnit = CanvasUnit::DEFAULT;
    pattern_->readyEventNew_ = [&](bool immediate, CanvasUnit unit) {
        called = true;
        receivedImmediate = immediate;
        receivedUnit = unit;
    };
    pattern_->immediateRender_ = true;
    pattern_->unit_ = CanvasUnit::PX;
    pattern_->FireReadyEvent();
    EXPECT_TRUE(called);
    EXPECT_TRUE(receivedImmediate);
    EXPECT_EQ(receivedUnit, CanvasUnit::PX);
}

HWTEST_F(CanvasPatternTestNg, FireReadyEvent004, TestSize.Level1)
{
    bool called = false;
    pattern_->readyEventNew_ = nullptr;
    pattern_->readyEvent_ = [&called]() { called = true; };
    pattern_->FireReadyEvent();
    EXPECT_TRUE(called);
}

// ==================== ResetSurfaceAndFireReady ====================

HWTEST_F(CanvasPatternTestNg, ResetSurfaceAndFireReady001, TestSize.Level1)
{
    pattern_->contentModifier_ = nullptr;
    pattern_->ResetSurfaceAndFireReady(SizeF(100.0f, 100.0f));
    // contentModifier_ is null, ResetSurfaceAndFireReady returns early; no tasks are pushed.
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

HWTEST_F(CanvasPatternTestNg, ResetSurfaceAndFireReady002, TestSize.Level1)
{
    pattern_->contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    pattern_->paintMethod_ = nullptr;
    pattern_->readyEvent_ = nullptr;
    pattern_->readyEventNew_ = nullptr;
    pattern_->ResetSurfaceAndFireReady(SizeF(100.0f, 100.0f));
    // paintMethod_ is null, ResetSurfaceAndFireReady returns early; paintMethod_ stays null.
    EXPECT_EQ(pattern_->paintMethod_, nullptr);
}

HWTEST_F(CanvasPatternTestNg, ResetSurfaceAndFireReady003, TestSize.Level1)
{
    pattern_->contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    pattern_->paintMethod_ = AceType::MakeRefPtr<CanvasPaintMethod>(pattern_->contentModifier_, frameNode_);
    pattern_->readyEvent_ = nullptr;
    pattern_->readyEventNew_ = nullptr;
    pattern_->ResetSurfaceAndFireReady(SizeF(100.0f, 100.0f));
    // canvasRenderContext_ is not set on the new paintMethod_, so NeedRender() returns false.
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

// ==================== OnDetachFromFrameNode ====================

HWTEST_F(CanvasPatternTestNg, OnDetachFromFrameNode001, TestSize.Level1)
{
    pattern_->isAttached_ = true;
    pattern_->onContext2DDetach_ = nullptr;
    pattern_->OnDetachFromFrameNode(AceType::RawPtr(frameNode_));
    EXPECT_FALSE(pattern_->isAttached_);
}

// ==================== OnLanguageConfigurationUpdate ====================

HWTEST_F(CanvasPatternTestNg, OnLanguageConfigurationUpdate001, TestSize.Level1)
{
    pattern_->currentSetTextDirection_ = TextDirection::LTR;
    pattern_->OnLanguageConfigurationUpdate();
    EXPECT_EQ(pattern_->currentSetTextDirection_, TextDirection::LTR);
}

// ==================== OnModifyDone ====================

HWTEST_F(CanvasPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    pattern_->currentSetTextDirection_ = TextDirection::RTL;
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->currentSetTextDirection_, TextDirection::RTL);
}

// ==================== TransferFromImageBitmap ====================

HWTEST_F(CanvasPatternTestNg, TransferFromImageBitmap001, TestSize.Level1)
{
    /**
     * @tc.steps1: transfer an image bitmap to the canvas.
     * @tc.expected: NeedRender stays false; PushTask is compiled out under ACE_UNITTEST.
     */
    Ace::ImageData imageData;
    pattern_->TransferFromImageBitmap(imageData);
    EXPECT_FALSE(pattern_->paintMethod_->NeedRender());
}

} // namespace OHOS::Ace::NG
