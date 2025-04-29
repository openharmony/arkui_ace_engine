/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/pattern.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_layout_algorithm.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_model_ng.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_modifier.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_paint_method.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "testtag";
} // namespace

class CustomNodeExtTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateNode();
};

void CustomNodeExtTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void CustomNodeExtTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> CustomNodeExtTestNg::CreateNode()
{
    auto frameNode = CustomNodeExtModelNG::GetOrCreateFrameNode(TEST_TAG);
    return frameNode;
}

/**
 * @tc.name: CustomNodeExtCreator001
 * @tc.desc: Test the create of CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    RefPtr<FrameNode> customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
}

/**
 * @tc.name: CustomNodeExtSetMeasureCallback001
 * @tc.desc: Test the set of MeasureCallback in CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtSetMeasureCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step2. CustomNodeExtPattern set measurecallback.
     * @tc.expected: measureCallback_ has value.
     */
    auto onMeasureFunction = [](LayoutConstraintF layoutConstraint){};
    CustomNodeExtModelNG::SetMeasureCallback(AceType::RawPtr(customExtFrameNode),
        std::move(onMeasureFunction));
    ASSERT_NE(pattern->measureCallback_, nullptr);
}

/**
 * @tc.name: CustomNodeExtSetLayoutCallback001
 * @tc.desc: Test the set of SetLayoutCallback in CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtSetLayoutCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step2. CustomNodeExtPattern set layoutcallback.
     * @tc.expected: layoutCallback_ has value.
     */
    auto onLayoutFunction = [](RectF rect){};
    CustomNodeExtModelNG::SetLayoutCallback(AceType::RawPtr(customExtFrameNode),
        std::move(onLayoutFunction));
    ASSERT_NE(pattern->layoutCallback_, nullptr);
}


/**
 * @tc.name: CustomNodeExtSetContentDrawCallback001
 * @tc.desc: Test the set of ContentDrawCallback in CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtSetContentDrawCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step2. CustomNodeExtPattern set ContentDrawCallback.
     * @tc.expected: contentModifier_ has value.
     */
    auto drawFunction = [](DrawingContext context){};
    CustomNodeExtModelNG::SetContentDrawCallback(AceType::RawPtr(customExtFrameNode),
        std::move(drawFunction));
    ASSERT_NE(pattern->contentModifier_, nullptr);
}

/**
 * @tc.name: CustomNodeExtSetForegroundDrawCallback001
 * @tc.desc: Test the set of ForegroundDrawCallback in CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtSetForegroundDrawCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step2. CustomNodeExtPattern set ForegroundDrawCallback.
     * @tc.expected: foregroundModifier_ has value.
     */
    auto drawFunction = [](DrawingContext context){};
    CustomNodeExtModelNG::SetForegroundDrawCallback(AceType::RawPtr(customExtFrameNode),
        std::move(drawFunction));
    ASSERT_NE(pattern->foregroundModifier_, nullptr);
}

/**
 * @tc.name: CustomNodeExtSetOverlayDrawCallback001
 * @tc.desc: Test the set of OverlayDrawCallback in CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtSetOverlayDrawCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step2. CustomNodeExtPattern set OverlayDrawCallback.
     * @tc.expected: overlayModifier_ has value.
     */
    auto drawFunction = [](DrawingContext context){};
    CustomNodeExtModelNG::SetOverlayDrawCallback(AceType::RawPtr(customExtFrameNode),
        std::move(drawFunction));
    ASSERT_NE(pattern->overlayModifier_, nullptr);
}

/**
 * @tc.name: CustomNodeExtSetOnConfigUpdateCallback001
 * @tc.desc: Test the set of ConfigUpdateCallback in CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtSetOnConfigUpdateCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step2. CustomNodeExtPattern set OnConfigUpdateCallback.
     * @tc.expected: onConfigUpdate_ has value.
     */
    auto onConfigUpdateFunction = [](ConfigurationType configType){};
    CustomNodeExtModelNG::SetOnConfigUpdateCallback(AceType::RawPtr(customExtFrameNode),
        std::move(onConfigUpdateFunction));
    ASSERT_NE(pattern->onConfigUpdate_, nullptr);
}

/**
 * @tc.name: CustomNodeExtSetOnModifyDoneCallback001
 * @tc.desc: Test the set of OnModifyDoneCallback in CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtSetOnModifyDoneCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step2. CustomNodeExtPattern set OnModifyDoneCallback.
     * @tc.expected: onModifyDoneCallback_ has value.
     */
    auto onModifyDonFunction = [](){};
    CustomNodeExtModelNG::SetOnModifyDoneCallback(AceType::RawPtr(customExtFrameNode),
        std::move(onModifyDonFunction));
    ASSERT_NE(pattern->onModifyDoneCallback_, nullptr);
}

/**
 * @tc.name: CustomNodeExtSetOnDirtyLayoutWrapperSwap001
 * @tc.desc: Test the set of OnDirtyLayoutWrapperSwap in CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtSetOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step2. CustomNodeExtPattern set OnDirtyLayoutWrapperSwap.
     * @tc.expected: onDirtySwap_ has value.
     */
    auto onDirtyLayoutWrapperSwapfunction = [](const DirtySwapConfig& config){};
    CustomNodeExtModelNG::SetOnDirtyLayoutWrapperSwap(AceType::RawPtr(customExtFrameNode),
        std::move(onDirtyLayoutWrapperSwapfunction));
    ASSERT_NE(pattern->onDirtySwap_, nullptr);
}

/**
 * @tc.name: CustomNodeExtSetIsAtomic001
 * @tc.desc: Test the set of Atomic in CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtSetIsAtomic001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step2. CustomNodeExtPattern set Atomic.
     * @tc.expected: isAtomic_ is true.
     */
    CustomNodeExtModelNG::SetIsAtomic(AceType::RawPtr(customExtFrameNode), true);
    ASSERT_EQ(pattern->isAtomic_, true);
}

/**
 * @tc.name: CustomNodeExtGetModifier001
 * @tc.desc: Test get GetModifier of CustomNodeExt.
 * @tc.type: FUNC
 */
HWTEST_F(CustomNodeExtTestNg, CustomNodeExtGetModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Invoke CustomNodeExt Create function.
     * @tc.expected: Create CustomNodeExt.
     */
    auto customExtFrameNode = CreateNode();
    ASSERT_NE(customExtFrameNode, nullptr);
    auto pattern = customExtFrameNode->GetPattern<CustomNodeExtPattern>();

    /**
     * @tc.steps: step1. Create LayoutAlgorithm with measureCallback_ and layoutCallback_.
     * @tc.expected: Create CustomNodeExt.
     */
    pattern->measureCallback_ = [](LayoutConstraintF){};
    pattern->layoutCallback_ = [](RectF){};
    auto customNodeExtLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(customNodeExtLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. CustomNodeExtPattern set ContentDrawCallback.
     * @tc.expected: contentModifier_ has value.
     */
    auto drawFunction = [](DrawingContext context){};
    CustomNodeExtModelNG::SetContentDrawCallback(AceType::RawPtr(customExtFrameNode),
        std::move(drawFunction));
    ASSERT_NE(pattern->contentModifier_, nullptr);

    /**
     * @tc.steps: step3. CustomNodeExtPattern set ContentDrawCallback.
     * @tc.expected: foregroundModifier_ has value.
     */
    CustomNodeExtModelNG::SetForegroundDrawCallback(AceType::RawPtr(customExtFrameNode),
        std::move(drawFunction));
    ASSERT_NE(pattern->foregroundModifier_, nullptr);

    /**
     * @tc.steps: step4. CustomNodeExtPattern set OverlayDrawCallback.
     * @tc.expected: overlayModifier_ has value.
     */
    CustomNodeExtModelNG::SetOverlayDrawCallback(AceType::RawPtr(customExtFrameNode),
        std::move(drawFunction));
    ASSERT_NE(pattern->overlayModifier_, nullptr);

    /**
     * @tc.steps: step5. CustomNodeExtPattern create NodePaintMethod.
     * @tc.expected: paintMethod has value.
     */
    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps: step6. Get renderContext.
     * @tc.expected: RenderContext has value.
     */
    auto renderContext = customExtFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step7. Get geometryNode.
     * @tc.expected: GeometryNode has value.
     */
    auto geometryNode = customExtFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);

    /**
     * @tc.steps: step8. Get paintProperty.
     * @tc.expected: PaintProperty has value.
     */
    auto paintProperty = pattern->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step9. Create paintWrapper with renderContext, geometryNode, paintProperty.
     * @tc.expected: PaintWrapper has value.
     */
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: step10. Get contentModifier.
     * @tc.expected: ContentModifier has value.
     */
    auto contentModifier = paintMethod->GetContentModifier(paintWrapper);
    ASSERT_NE(contentModifier, nullptr);

    /**
     * @tc.steps: step11. Get foregroundModifier.
     * @tc.expected: ForegroundModifier has value.
     */
    auto foregroundModifier = paintMethod->GetForegroundModifier(paintWrapper);
    ASSERT_NE(foregroundModifier, nullptr);

    /**
     * @tc.steps: step12. Get overlayModifier.
     * @tc.expected: OverlayModifier has value.
     */
    auto overlayModifier = paintMethod->GetOverlayModifier(paintWrapper);
    ASSERT_NE(overlayModifier, nullptr);
}

} // namespace OHOS::Ace::NG
