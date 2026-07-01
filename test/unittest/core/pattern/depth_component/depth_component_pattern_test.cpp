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

// TDD coverage for DepthComponentPattern + DepthComponentModel + DepthComponentLayoutProperty.
// Rosen-backend functions (guarded by ENABLE_ROSEN_BACKEND && !ACE_UNITTEST) and GLTF/3D functions
// (guarded by KIT_3D_ENABLE) are compiled out under ACE_UNITTEST and are intentionally not covered here.

#include "depth_component_test_base.h"

namespace OHOS::Ace::NG {

class DepthComponentPatternTestNg : public DepthComponentTestBase {};

// ===================== Construction & factory methods =====================

/**
 * @tc.name: Construct001
 * @tc.desc: Verify default construction and factory overrides.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Construct001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->IsAtomicNode());
    auto ctxParam = pattern->GetContextParam();
    ASSERT_TRUE(ctxParam.has_value());
    EXPECT_EQ(ctxParam->type, RenderContext::ContextType::DEPTH);
    EXPECT_EQ(ctxParam->surfaceName, std::nullopt);
    EXPECT_NE(pattern->CreateLayoutProperty(), nullptr);
    EXPECT_NE(pattern->CreateLayoutAlgorithm(), nullptr);
    EXPECT_NE(pattern->CreateEventHub(), nullptr);
    EXPECT_NE(pattern->CreateAccessibilityProperty(), nullptr);
    EXPECT_NE(pattern->CreateNodePaintMethod(), nullptr);
    EXPECT_EQ(pattern->GetDepthSpace(), OHOS::Ace::DepthSpaceType::INSTANCE);
    EXPECT_EQ(pattern->GetRender3DScale(), 1.0f);
}

/**
 * @tc.name: DepthSpace001
 * @tc.desc: SetDepthSpace/GetDepthSpace round-trip for all enum values.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, DepthSpace001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    pattern->SetDepthSpace(OHOS::Ace::DepthSpaceType::GLOBAL);
    EXPECT_EQ(pattern->GetDepthSpace(), OHOS::Ace::DepthSpaceType::GLOBAL);
    pattern->SetDepthSpace(OHOS::Ace::DepthSpaceType::INSTANCE);
    EXPECT_EQ(pattern->GetDepthSpace(), OHOS::Ace::DepthSpaceType::INSTANCE);
}

/**
 * @tc.name: Render3DScale001
 * @tc.desc: SetRender3DScale/GetRender3DScale round-trip incl. zero.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Render3DScale001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    pattern->SetRender3DScale(2.5f);
    EXPECT_EQ(pattern->GetRender3DScale(), 2.5f);
    pattern->SetRender3DScale(0.0f);
    EXPECT_EQ(pattern->GetRender3DScale(), 0.0f);
}

/**
 * @tc.name: BackgroundImageId001
 * @tc.desc: GetBackgroundImageId lazily allocates a stable id; HasBackgroundImageNode toggles.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, BackgroundImageId001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    EXPECT_FALSE(pattern->HasBackgroundImageNode());
    int32_t id1 = pattern->GetBackgroundImageId();
    EXPECT_TRUE(id1 > 0);
    EXPECT_TRUE(pattern->HasBackgroundImageNode());
    int32_t id2 = pattern->GetBackgroundImageId();
    EXPECT_EQ(id1, id2);
}

/**
 * @tc.name: DepthMap001
 * @tc.desc: SetDepthMap/GetDepthMap round-trip.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, DepthMap001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    ImageSourceInfo depthMap("file:///data/depth.png");
    pattern->SetDepthMap(depthMap);
    EXPECT_EQ(pattern->GetDepthMap().GetSrc(), depthMap.GetSrc());
}

// ===================== GetBackgroundSource / IsGltfBackground =====================

/**
 * @tc.name: GetBackgroundSource001
 * @tc.desc: GetBackgroundSource returns empty when host is null.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, GetBackgroundSource001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    auto source = pattern->GetBackgroundSource();
    EXPECT_EQ(source.type, OHOS::Ace::DepthBackgroundSource::Type::NONE);
}

/**
 * @tc.name: GetBackgroundSource002
 * @tc.desc: GetBackgroundSource returns empty when property is not DepthComponentLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, GetBackgroundSource002, TestSize.Level1)
{
    auto plainNode = CreateNodeWithTag("plain", ElementRegister::GetInstance()->MakeUniqueId());
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    pattern->frameNode_ = plainNode; // attach a host whose layoutProperty is NOT DepthComponent's
    auto source = pattern->GetBackgroundSource();
    EXPECT_EQ(source.type, OHOS::Ace::DepthBackgroundSource::Type::NONE);
}

/**
 * @tc.name: GetBackgroundSource003
 * @tc.desc: GetBackgroundSource returns the configured source.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, GetBackgroundSource003, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    auto source = pattern->GetBackgroundSource();
    EXPECT_EQ(source.type, OHOS::Ace::DepthBackgroundSource::Type::IMAGE);
    EXPECT_EQ(source.src, std::string(DEPTH_IMAGE_SRC));
}

/**
 * @tc.name: IsGltfBackground001
 * @tc.desc: IsGltfBackground distinguishes GLTF / IMAGE / NONE sources.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, IsGltfBackground001, TestSize.Level1)
{
    auto gltfHost = CreateNode(MakeGltfSource());
    EXPECT_TRUE(gltfHost->GetPattern<DepthComponentPattern>()->IsGltfBackground());

    auto imageHost = CreateNode(MakeImageSource());
    EXPECT_FALSE(imageHost->GetPattern<DepthComponentPattern>()->IsGltfBackground());

    auto noneHost = CreateNode({});
    EXPECT_FALSE(noneHost->GetPattern<DepthComponentPattern>()->IsGltfBackground());
}

// ===================== SetBackgroundSource =====================

/**
 * @tc.name: SetBackgroundSource001
 * @tc.desc: SetBackgroundSource is a no-op when host is null.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, SetBackgroundSource001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    pattern->SetBackgroundSource(MakeImageSource()); // host null -> CHECK
    EXPECT_EQ(pattern->GetBackgroundSource().type, OHOS::Ace::DepthBackgroundSource::Type::NONE);
}

/**
 * @tc.name: SetBackgroundSource002
 * @tc.desc: SetBackgroundSource is a no-op when layoutProperty is null.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, SetBackgroundSource002, TestSize.Level1)
{
    auto plainNode = CreateNodeWithTag("plain", ElementRegister::GetInstance()->MakeUniqueId());
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    pattern->frameNode_ = plainNode;
    pattern->SetBackgroundSource(MakeImageSource()); // property null -> CHECK
}

/**
 * @tc.name: SetBackgroundSource003
 * @tc.desc: SetBackgroundSource persists the source into the layout property.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, SetBackgroundSource003, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->SetBackgroundSource(MakeGltfSource());
    EXPECT_TRUE(pattern->IsGltfBackground());
}

// ===================== OnAttachToFrameNode / OnDetachFromFrameNode =====================

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: OnAttachToFrameNode with null host is a safe no-op.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    pattern->OnAttachToFrameNode(); // host null -> CHECK, no crash
}

/**
 * @tc.name: OnAttachToFrameNode002
 * @tc.desc: OnAttachToFrameNode enables content-rect-based render frame on the host.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, OnAttachToFrameNode002, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->OnAttachToFrameNode();
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr); // SetUsingContentRectForRenderFrame(true) applied
}

/**
 * @tc.name: OnDetachFromFrameNode001
 * @tc.desc: OnDetachFromFrameNode does not crash (ACE_UNITTEST path is a no-op).
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, OnDetachFromFrameNode001, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->OnDetachFromFrameNode(AceType::RawPtr(host));
    pattern->OnDetachFromFrameNode(nullptr); // null node path
}

// ===================== OnModifyDone =====================

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: GLTF background path triggers RemoveBackgroundImageNode (else branch in ACE_UNITTEST).
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    auto host = CreateNode(MakeGltfSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    MountToStageNode(host);
    pattern->OnModifyDone();
    EXPECT_FALSE(pattern->HasBackgroundImageNode()); // gltf must not keep an image child
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: IMAGE background path triggers SetupBackgroundImageNode.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, OnModifyDone002, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    MountToStageNode(host);
    pattern->OnModifyDone();
    EXPECT_TRUE(pattern->HasBackgroundImageNode());
}

// ===================== SetupBackgroundImageNode =====================

/**
 * @tc.name: SetupBackgroundImageNode001
 * @tc.desc: SVG background source is rejected (removed).
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, SetupBackgroundImageNode001, TestSize.Level1)
{
    auto host = CreateNode(MakeSvgSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    ASSERT_TRUE(pattern->GetBackgroundImageSource().IsSvg());
    pattern->SetupBackgroundImageNode();
    EXPECT_FALSE(pattern->HasBackgroundImageNode());
}

/**
 * @tc.name: SetupBackgroundImageNode002
 * @tc.desc: First call creates an IMAGE child node with HTMNONE hit-test mode.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, SetupBackgroundImageNode002, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->SetupBackgroundImageNode();
    EXPECT_TRUE(pattern->HasBackgroundImageNode());
    auto bgNode = FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, pattern->GetBackgroundImageId());
    ASSERT_NE(bgNode, nullptr);
    EXPECT_EQ(bgNode->GetHitTestMode(), HitTestMode::HTMNONE);
    auto imagePattern = bgNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr); // SetIsBackground(true) applied
}

/**
 * @tc.name: SetupBackgroundImageNode003
 * @tc.desc: Second call reuses the existing node and updates its source info / ideal size.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, SetupBackgroundImageNode003, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->SetupBackgroundImageNode();
    int32_t firstId = pattern->GetBackgroundImageId();
    int32_t childCountBefore = static_cast<int32_t>(host->GetChildren().size());

    pattern->SetupBackgroundImageNode(); // idempotent: reuse node
    EXPECT_EQ(pattern->GetBackgroundImageId(), firstId);
    EXPECT_EQ(host->GetChildren().size(), static_cast<size_t>(childCountBefore));

    auto bgNode = FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, firstId);
    ASSERT_NE(bgNode, nullptr);
    auto layoutProp = bgNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_EQ(layoutProp->GetImageSourceInfo()->GetSrc(), std::string(DEPTH_IMAGE_SRC));
}

// ===================== RemoveBackgroundImageNode =====================

/**
 * @tc.name: RemoveBackgroundImageNode001
 * @tc.desc: No-op when there is no background image id.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, RemoveBackgroundImageNode001, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    EXPECT_FALSE(pattern->HasBackgroundImageNode());
    pattern->RemoveBackgroundImageNode();
    EXPECT_FALSE(pattern->HasBackgroundImageNode());
}

/**
 * @tc.name: RemoveBackgroundImageNode002
 * @tc.desc: Early-return when the referenced FrameNode no longer exists.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, RemoveBackgroundImageNode002, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->backgroundImageId_ = 999999; // non-existent id
    pattern->pendingCleanupImage_ = true;
    pattern->RemoveBackgroundImageNode(); // GetFrameNode returns null -> return
    EXPECT_TRUE(pattern->backgroundImageId_.has_value()); // unchanged
}

/**
 * @tc.name: RemoveBackgroundImageNode003
 * @tc.desc: Removes the child, resets the id and pendingCleanupImage flag.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, RemoveBackgroundImageNode003, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->SetupBackgroundImageNode();
    ASSERT_TRUE(pattern->HasBackgroundImageNode());
    pattern->pendingCleanupImage_ = true;
    pattern->RemoveBackgroundImageNode();
    EXPECT_FALSE(pattern->HasBackgroundImageNode());
    EXPECT_FALSE(pattern->pendingCleanupImage_);
}

// ===================== ApplyBackgroundImageMatrix =====================

namespace {
RefPtr<FrameNode> SetupBackgroundChild(const RefPtr<FrameNode>& host)
{
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->SetupBackgroundImageNode();
    return FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, pattern->GetBackgroundImageId());
}
} // namespace

/**
 * @tc.name: ApplyBackgroundImageMatrix001
 * @tc.desc: Without cameraBufferCrop, image fit becomes COVER and matrix is identity.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, ApplyBackgroundImageMatrix001, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    auto bgNode = SetupBackgroundChild(host);
    ASSERT_NE(bgNode, nullptr);
    pattern->ApplyBackgroundImageMatrix(bgNode);
    auto renderProp = bgNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);
    EXPECT_EQ(renderProp->GetImageFit().value_or(ImageFit::MATRIX), ImageFit::COVER);
    auto layoutProp = bgNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_EQ(layoutProp->GetImageFitValue(ImageFit::MATRIX), ImageFit::COVER);
}

/**
 * @tc.name: ApplyBackgroundImageMatrix002
 * @tc.desc: cropScale <= 0 short-circuits before writing MATRIX fit.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, ApplyBackgroundImageMatrix002, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    auto camera = MakeCamera(1.0f, true);
    camera.cameraBufferCrop->cropScale = 0.0f;
    DepthComponentModel::SetCamera(AceType::RawPtr(host), camera);
    auto bgNode = SetupBackgroundChild(host);
    ASSERT_NE(bgNode, nullptr);
    // Pre-set a non-MATRIX fit so we can detect whether the function bailed out.
    bgNode->GetPaintProperty<ImageRenderProperty>()->UpdateImageFit(ImageFit::CONTAIN);
    pattern->ApplyBackgroundImageMatrix(bgNode);
    auto renderProp = bgNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_EQ(renderProp->GetImageFit().value_or(ImageFit::MATRIX), ImageFit::CONTAIN);
}

/**
 * @tc.name: ApplyBackgroundImageMatrix003
 * @tc.desc: With a valid crop, fit becomes MATRIX and the matrix encodes scale + offset.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, ApplyBackgroundImageMatrix003, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DepthComponentModel::SetCamera(AceType::RawPtr(host), MakeCamera(1.0f, true));
    auto bgNode = SetupBackgroundChild(host);
    ASSERT_NE(bgNode, nullptr);
    pattern->ApplyBackgroundImageMatrix(bgNode);
    auto renderProp = bgNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(renderProp, nullptr);
    EXPECT_EQ(renderProp->GetImageFit().value_or(ImageFit::COVER), ImageFit::MATRIX);
    auto matrix = renderProp->GetImageMatrix();
    ASSERT_TRUE(matrix.has_value());
    // scale = 1 / cropScale = 1 / 0.5 = 2.0
    EXPECT_NEAR(matrix.value()(0, 0), 2.0, 0.001);
    EXPECT_NEAR(matrix.value()(1, 1), 2.0, 0.001);
}

/**
 * @tc.name: ApplyBackgroundImageMatrix004
 * @tc.desc: Null background image node is handled gracefully.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, ApplyBackgroundImageMatrix004, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->ApplyBackgroundImageMatrix(nullptr); // CHECK_NULL_VOID -> no crash
}

// ===================== ApplyOnCompleteCallback / ApplyOnErrorCallback =====================

/**
 * @tc.name: ApplyOnCompleteCallback001
 * @tc.desc: SetupBackgroundImageNode registers an image->depth complete bridge; the depth
 *          event hub fires when triggered.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, ApplyOnCompleteCallback001, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    auto eventHub = host->GetEventHub<DepthComponentEventHub>();
    ASSERT_NE(eventHub, nullptr);
    double reportedWidth = 0.0;
    eventHub->SetOnComplete([&reportedWidth](const DepthComponentCompleteEvent& event) {
        reportedWidth = event.componentWidth;
    });
    pattern->SetupBackgroundImageNode();
    auto bgNode = SetupBackgroundChild(host);
    ASSERT_NE(bgNode, nullptr);
    auto imageEventHub = bgNode->GetEventHub<ImageEventHub>();
    ASSERT_NE(imageEventHub, nullptr);
    EXPECT_TRUE(imageEventHub->completeEvent_ != nullptr);
    // Fire a depth complete directly to confirm wiring is intact.
    DepthComponentCompleteEvent completeEvent;
    completeEvent.componentWidth = 320.0;
    eventHub->FireCompleteEvent(completeEvent);
    EXPECT_EQ(reportedWidth, 320.0);
}

/**
 * @tc.name: ApplyOnErrorCallback001
 * @tc.desc: SetupBackgroundImageNode registers an image->depth error bridge; firing reports
 *          the error code/message.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, ApplyOnErrorCallback001, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    auto eventHub = host->GetEventHub<DepthComponentEventHub>();
    ASSERT_NE(eventHub, nullptr);
    int32_t reportedCode = -1;
    std::string reportedMsg;
    eventHub->SetOnError([&](const DepthComponentErrorEvent& event) {
        reportedCode = event.errorCode;
        reportedMsg = event.errorMessage;
    });
    pattern->SetupBackgroundImageNode();
    auto bgNode = SetupBackgroundChild(host);
    ASSERT_NE(bgNode, nullptr);
    auto imageEventHub = bgNode->GetEventHub<ImageEventHub>();
    ASSERT_NE(imageEventHub, nullptr);
    EXPECT_TRUE(imageEventHub->errorEvent_ != nullptr);
    DepthComponentErrorEvent errorEvent;
    errorEvent.errorCode = 404;
    errorEvent.errorMessage = "not found";
    eventHub->FireErrorEvent(errorEvent);
    EXPECT_EQ(reportedCode, 404);
    EXPECT_EQ(reportedMsg, std::string("not found"));
}

// ===================== FinishBackgroundSwitch / OnPaint3D =====================

/**
 * @tc.name: FinishBackgroundSwitch001
 * @tc.desc: FinishBackgroundSwitch is a safe no-op under ACE_UNITTEST (KIT_3D compiled out).
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, FinishBackgroundSwitch001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    pattern->FinishBackgroundSwitch(); // no crash
}

/**
 * @tc.name: OnPaint3D001
 * @tc.desc: OnPaint3D is a safe no-op under ACE_UNITTEST (KIT_3D compiled out).
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, OnPaint3D001, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    pattern->OnPaint3D(); // no crash
}

// ===================== IsCameraChange =====================

/**
 * @tc.name: IsCameraChange001
 * @tc.desc: Returns false when host / property / cameraParams are absent.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, IsCameraChange001, TestSize.Level1)
{
    auto standalone = AceType::MakeRefPtr<DepthComponentPattern>();
    EXPECT_FALSE(standalone->IsCameraChange()); // host null

    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    EXPECT_FALSE(pattern->IsCameraChange()); // cameraParams not set
}

/**
 * @tc.name: IsCameraChange002
 * @tc.desc: First observation reports true and caches the params.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, IsCameraChange002, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DepthComponentModel::SetCamera(AceType::RawPtr(host), MakeCamera(1.0f, false));
    EXPECT_TRUE(pattern->IsCameraChange());
    EXPECT_TRUE(pattern->preCameraParams_.has_value());
}

/**
 * @tc.name: IsCameraChange003
 * @tc.desc: Re-observing the same params reports false.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, IsCameraChange003, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DepthComponentModel::SetCamera(AceType::RawPtr(host), MakeCamera(1.0f, false));
    pattern->IsCameraChange();
    EXPECT_FALSE(pattern->IsCameraChange());
}

/**
 * @tc.name: IsCameraChange004
 * @tc.desc: Changing the camera params reports true again.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, IsCameraChange004, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DepthComponentModel::SetCamera(AceType::RawPtr(host), MakeCamera(1.0f, false));
    pattern->IsCameraChange();
    DepthComponentModel::SetCamera(AceType::RawPtr(host), MakeCamera(2.0f, false));
    EXPECT_TRUE(pattern->IsCameraChange());
}

// ===================== GetEffectiveCameraBufferCrop =====================

/**
 * @tc.name: GetEffectiveCameraBufferCrop001
 * @tc.desc: Returns nullopt when host / property / cameraParams are absent.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, GetEffectiveCameraBufferCrop001, TestSize.Level1)
{
    auto standalone = AceType::MakeRefPtr<DepthComponentPattern>();
    EXPECT_FALSE(standalone->GetEffectiveCameraBufferCrop().has_value());

    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    EXPECT_FALSE(pattern->GetEffectiveCameraBufferCrop().has_value());
}

/**
 * @tc.name: GetEffectiveCameraBufferCrop002
 * @tc.desc: Returns the explicit cameraBufferCrop when present.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, GetEffectiveCameraBufferCrop002, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DepthComponentModel::SetCamera(AceType::RawPtr(host), MakeCamera(1.0f, true));
    auto crop = pattern->GetEffectiveCameraBufferCrop();
    ASSERT_TRUE(crop.has_value());
    EXPECT_EQ(crop->bufferWidth, 200);
    EXPECT_EQ(crop->bufferHeight, 200);
    EXPECT_NEAR(crop->cropScale, 0.5f, 0.001f);
}

/**
 * @tc.name: GetEffectiveCameraBufferCrop003
 * @tc.desc: Without explicit crop, derives buffer size from the geometry node.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, GetEffectiveCameraBufferCrop003, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DepthComponentModel::SetCamera(AceType::RawPtr(host), MakeCamera(1.0f, false));
    host->GetGeometryNode()->SetFrameSize(SizeF(300.0f, 200.0f));
    auto crop = pattern->GetEffectiveCameraBufferCrop();
    ASSERT_TRUE(crop.has_value());
    EXPECT_EQ(crop->bufferWidth, 300);
    EXPECT_EQ(crop->bufferHeight, 200);
}

/**
 * @tc.name: GetEffectiveCameraBufferCrop004
 * @tc.desc: Without explicit crop and without geometry, returns a default-constructed crop.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, GetEffectiveCameraBufferCrop004, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DepthComponentModel::SetCamera(AceType::RawPtr(host), MakeCamera(1.0f, false));
    auto crop = pattern->GetEffectiveCameraBufferCrop();
    ASSERT_TRUE(crop.has_value());
    EXPECT_EQ(crop->bufferWidth, 0);
}

// ===================== ComputeTiltShift =====================

/**
 * @tc.name: ComputeTiltShift001
 * @tc.desc: Without a usable crop, returns the passthrough fov and zero offset.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, ComputeTiltShift001, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    auto camera = MakeCamera(1.0f, false);
    DepthComponentModel::SetCamera(AceType::RawPtr(host), camera);
    auto result = pattern->ComputeTiltShift(camera, 100.0f, 100.0f);
    EXPECT_FLOAT_EQ(result.fov, camera.yFov);
    EXPECT_FLOAT_EQ(result.xOffset, 0.0f);
    EXPECT_FLOAT_EQ(result.yOffset, 0.0f);
}

/**
 * @tc.name: ComputeTiltShift002
 * @tc.desc: With a valid crop, fov is narrowed and offsets are computed from the ROI.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, ComputeTiltShift002, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    auto camera = MakeCamera(1.0f, true); // crop buffer=200x200, scale=0.5, offset=(10,20)
    DepthComponentModel::SetCamera(AceType::RawPtr(host), camera);
    auto result = pattern->ComputeTiltShift(camera, 100.0f, 100.0f);
    EXPECT_FLOAT_EQ(result.xOffset, -1.3f); // (10 - (100 - 25)) / 50
    EXPECT_FLOAT_EQ(result.yOffset, -1.1f); // (20 - (100 - 25)) / 50
    EXPECT_NE(result.fov, camera.yFov);     // narrowed by atan(0.25 * tan(half))
}

/**
 * @tc.name: ComputeTiltShift003
 * @tc.desc: Non-positive crop scale falls back to the passthrough result.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, ComputeTiltShift003, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    auto camera = MakeCamera(0.8f, true);
    camera.cameraBufferCrop->cropScale = -1.0f;
    DepthComponentModel::SetCamera(AceType::RawPtr(host), camera);
    auto result = pattern->ComputeTiltShift(camera, 100.0f, 100.0f);
    EXPECT_FLOAT_EQ(result.fov, camera.yFov);
    EXPECT_FLOAT_EQ(result.xOffset, 0.0f);
}

// ===================== OnDirtyLayoutWrapperSwap =====================

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Returns false when both skipMeasure and skipLayout are set.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    ASSERT_NE(host, nullptr);
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(wrapper, config));
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Returns false when the dirty wrapper is null.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    auto host = CreateNode({});
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DirtySwapConfig config;
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(nullptr, config));
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap003
 * @tc.desc: Normal path returns !(skipMeasure || SkipMeasureContent).
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    ASSERT_NE(host, nullptr);
    auto pattern = host->GetPattern<DepthComponentPattern>();
    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    EXPECT_TRUE(pattern->OnDirtyLayoutWrapperSwap(wrapper, config));
}

// ===================== DepthComponentModel API =====================

/**
 * @tc.name: Model_Create001
 * @tc.desc: DepthComponentModel::Create pushes a DepthComponent onto the view stack.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_Create001, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->Finish(); // clear
    DepthComponentModel::Create(MakeImageSource());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::DEPTH_COMPONENT_ETS_TAG);
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: Model_CreateFrameNode001
 * @tc.desc: CreateFrameNode builds a node tagged DepthComponent with the source applied.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_CreateFrameNode001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = DepthComponentModel::CreateFrameNode(nodeId, MakeGltfSource());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::DEPTH_COMPONENT_ETS_TAG);
    EXPECT_TRUE(frameNode->GetPattern<DepthComponentPattern>()->IsGltfBackground());
}

/**
 * @tc.name: Model_SetBackgroundSource001
 * @tc.desc: Null frameNode / null pattern guards.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_SetBackgroundSource001, TestSize.Level1)
{
    DepthComponentModel::SetBackgroundSource(nullptr, MakeImageSource()); // null frameNode
    auto plainNode = CreateNodeWithTag("plain", ElementRegister::GetInstance()->MakeUniqueId());
    DepthComponentModel::SetBackgroundSource(AceType::RawPtr(plainNode), MakeImageSource()); // null pattern
}

/**
 * @tc.name: Model_SetDepthSpace001
 * @tc.desc: Both overloads; null guards and effective update.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_SetDepthSpace001, TestSize.Level1)
{
    DepthComponentModel::SetDepthSpace(nullptr, OHOS::Ace::DepthSpaceType::GLOBAL); // null frameNode
    auto host = CreateNode({});
    DepthComponentModel::SetDepthSpace(AceType::RawPtr(host), OHOS::Ace::DepthSpaceType::GLOBAL);
    EXPECT_EQ(host->GetPattern<DepthComponentPattern>()->GetDepthSpace(), OHOS::Ace::DepthSpaceType::GLOBAL);

    ViewStackProcessor::GetInstance()->Finish();
    DepthComponentModel::SetDepthSpace(OHOS::Ace::DepthSpaceType::INSTANCE); // no main frame node -> CHECK
    DepthComponentModel::Create({});
    DepthComponentModel::SetDepthSpace(OHOS::Ace::DepthSpaceType::INSTANCE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetPattern<DepthComponentPattern>()->GetDepthSpace(), OHOS::Ace::DepthSpaceType::INSTANCE);
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: Model_SetRender3DScale001
 * @tc.desc: Both overloads; null guard and effective update.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_SetRender3DScale001, TestSize.Level1)
{
    DepthComponentModel::SetRender3DScale(nullptr, 3.0f);
    auto host = CreateNode({});
    DepthComponentModel::SetRender3DScale(AceType::RawPtr(host), 3.0f);
    EXPECT_EQ(host->GetPattern<DepthComponentPattern>()->GetRender3DScale(), 3.0f);

    ViewStackProcessor::GetInstance()->Finish();
    DepthComponentModel::SetRender3DScale(0.5f); // no main frame node -> CHECK, no crash
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: Model_SetDepthMap001
 * @tc.desc: SetDepthMap overloads (with and without callback) and null guards.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_SetDepthMap001, TestSize.Level1)
{
    ImageSourceInfo depthMap("file:///data/depth.png");
    DepthComponentModel::SetDepthMap(nullptr, depthMap); // null frameNode
    auto host = CreateNode({});
    DepthComponentModel::SetDepthMap(AceType::RawPtr(host), depthMap);
    EXPECT_EQ(host->GetPattern<DepthComponentPattern>()->GetDepthMap().GetSrc(), depthMap.GetSrc());

    bool called = false;
    DepthComponentModel::SetDepthMap(AceType::RawPtr(host), depthMap,
        [&called](int32_t code, const std::string& msg) { called = true; });
    auto eventHub = host->GetEventHub<DepthComponentEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->GetOnDepthMapError() != nullptr);
    eventHub->FireDepthMapErrorEvent(1, "err");
    EXPECT_TRUE(called);

    ViewStackProcessor::GetInstance()->Finish();
    DepthComponentModel::SetDepthMap(depthMap); // no main frame node -> CHECK
    DepthComponentModel::SetDepthMap(depthMap, [&called](int32_t, const std::string&) {});
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: Model_SetCamera001
 * @tc.desc: SetCamera writes CameraParams; null guard.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_SetCamera001, TestSize.Level1)
{
    DepthComponentModel::SetCamera(nullptr, MakeCamera(1.0f, false));
    auto host = CreateNode({});
    auto camera = MakeCamera(1.5f, true);
    DepthComponentModel::SetCamera(AceType::RawPtr(host), camera);
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    ASSERT_TRUE(prop->GetCameraParams().has_value());
    EXPECT_NEAR(prop->GetCameraParams()->yFov, 1.5f, 0.001f);
    EXPECT_TRUE(prop->GetCameraParams()->cameraBufferCrop.has_value());
}

/**
 * @tc.name: Model_SetLight001
 * @tc.desc: SetLight writes LightParams; null guard.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_SetLight001, TestSize.Level1)
{
    DepthComponentModel::SetLight(nullptr, MakeLight());
    auto host = CreateNode({});
    DepthComponentModel::SetLight(AceType::RawPtr(host), MakeLight());
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    ASSERT_TRUE(prop->GetLightParams().has_value());
    EXPECT_NEAR(prop->GetLightParams()->intensity, 1.0f, 0.001f);
}

/**
 * @tc.name: Model_SetOnComplete001
 * @tc.desc: SetOnComplete registers the callback; null guards.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_SetOnComplete001, TestSize.Level1)
{
    DepthComponentModel::SetOnComplete(nullptr, [](const DepthComponentCompleteEvent&) {});
    auto host = CreateNode({});
    bool called = false;
    DepthComponentModel::SetOnComplete(
        AceType::RawPtr(host), [&called](const DepthComponentCompleteEvent&) { called = true; });
    auto eventHub = host->GetEventHub<DepthComponentEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetOnComplete() != nullptr);
    eventHub->FireCompleteEvent(DepthComponentCompleteEvent());
    EXPECT_TRUE(called);
}

/**
 * @tc.name: Model_SetOnError001
 * @tc.desc: SetOnError registers the callback; null guards.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, Model_SetOnError001, TestSize.Level1)
{
    DepthComponentModel::SetOnError(nullptr, [](const DepthComponentErrorEvent&) {});
    auto host = CreateNode({});
    bool called = false;
    DepthComponentModel::SetOnError(AceType::RawPtr(host), [&called](const DepthComponentErrorEvent&) {
        called = true;
    });
    auto eventHub = host->GetEventHub<DepthComponentEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetOnError() != nullptr);
    eventHub->FireErrorEvent(DepthComponentErrorEvent());
    EXPECT_TRUE(called);
}

// ===================== DepthComponentLayoutProperty Clone / Reset =====================

/**
 * @tc.name: LayoutProperty_Clone001
 * @tc.desc: Clone deep-copies BackgroundSource / CameraParams / LightParams.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, LayoutProperty_Clone001, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<DepthComponentLayoutProperty>();
    prop->UpdateBackgroundSource(MakeGltfSource());
    prop->UpdateCameraParams(MakeCamera(2.0f, true));
    prop->UpdateLightParams(MakeLight());
    auto cloned = AceType::DynamicCast<DepthComponentLayoutProperty>(prop->Clone());
    ASSERT_NE(cloned, nullptr);
    ASSERT_TRUE(cloned->GetBackgroundSource().has_value());
    EXPECT_EQ(cloned->GetBackgroundSource()->resolvedPath, MakeGltfSource().resolvedPath);
    ASSERT_TRUE(cloned->GetCameraParams().has_value());
    EXPECT_NEAR(cloned->GetCameraParams()->yFov, 2.0f, 0.001f);
    EXPECT_TRUE(cloned->GetLightParams().has_value());
}

/**
 * @tc.name: LayoutProperty_Reset001
 * @tc.desc: Reset clears the depth-specific properties.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPatternTestNg, LayoutProperty_Reset001, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<DepthComponentLayoutProperty>();
    prop->UpdateBackgroundSource(MakeImageSource());
    prop->UpdateCameraParams(MakeCamera(1.0f, true));
    prop->UpdateLightParams(MakeLight());
    prop->Reset();
    EXPECT_FALSE(prop->GetBackgroundSource().has_value());
    EXPECT_FALSE(prop->GetCameraParams().has_value());
    EXPECT_FALSE(prop->GetLightParams().has_value());
}

} // namespace OHOS::Ace::NG
