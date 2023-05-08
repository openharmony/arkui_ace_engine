/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define private public
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_event_hub.h"
#include "core/components_ng/pattern/form/form_layout_property.h"
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
RequestFormInfo formInfo;
DirtySwapConfig config;
FormModelNG formModelNG;
} // namespace

struct TestProperty {};

class FormPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateFromParagraph();
};

void FormPatternTestNg::SetUp()
{
    MockPipelineBase::SetUp();
    formInfo.id = 1;
    formInfo.cardName = "defalut";
    formInfo.bundleName = "bundle";
    formInfo.abilityName = "ability";
    formInfo.moduleName = "module";
}
void FormPatternTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> FormPatternTestNg::CreateFromParagraph()
{
    formModelNG.Create(formInfo);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

/**
 * @tc.name: FormNodeTest001
 * @tc.desc: create form node
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, FormNodeTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FormPatternTestNg001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, OnDirtyLayoutWrapperSwap, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateFromParagraph();
    auto pattern = frameNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    geometryNode->SetContentOffset(OffsetF(0, 0));
    RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, nullptr);
    EXPECT_NE(layoutWrapper, nullptr);
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    bool skipMeasures[2] = { false, true };
    for (int32_t i = 0; i < 2; ++i) {
        for (int32_t j = 0; j < 2; ++j) {
            config.skipMeasure = skipMeasures[i];
            auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, skipMeasures[i]);
            layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
            layoutWrapper->skipMeasureContent_ = skipMeasures[j];
            auto isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
            EXPECT_EQ(isSwap, false);
        }
    }
}

/**
 * @tc.name: FormModelNGTest001
 * @tc.desc: create form node
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, FormModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FormModelNG object
     */
    FormModelNG formNG;
    formNG.Create(formInfo);

    /**
     * @tc.steps: step2. Set call methods
     * @tc.expected: step2. Check the FormModelNG pattern value
     */
    formNG.SetDimension(1);
    formNG.AllowUpdate(false);
    formNG.SetVisibility(VisibleType(1));
    formNG.SetModuleName("test form");

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<FormLayoutProperty>();
    EXPECT_NE(property, nullptr);
    auto formInfo = property->GetRequestFormInfoValue();
    EXPECT_EQ(formInfo.dimension, 1);
    EXPECT_FALSE(formInfo.allowUpdate);
    EXPECT_EQ(formInfo.moduleName, "test form");
}

/**
 * @tc.name: FormModelNGTest002
 * @tc.desc: create form node
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, FormModelNGTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FormModelNG object
     */
    FormModelNG formNG;
    formNG.Create(formInfo);

    /**
     * @tc.steps: step2. Set call methods
     * @tc.expected: step2. Check the FormModelNG pattern value
     */
    std::string onAcquiredValue;
    auto onAcquired = [&onAcquiredValue](const std::string& param) { onAcquiredValue = param; };
    formNG.SetOnAcquired(std::move(onAcquired));
    auto frameNodeonAcquired = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonAcquired, nullptr);

    std::string onErrorValue;
    auto onError = [&onErrorValue](const std::string& param) { onErrorValue = param; };
    formNG.SetOnError(std::move(onError));
    auto frameNodeonError = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonError, nullptr);

    std::string onUninstallValue;
    auto onUninstall = [&onUninstallValue](const std::string& param) { onUninstallValue = param; };
    formNG.SetOnUninstall(std::move(onUninstall));
    auto frameNodeonUninstall = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonUninstall, nullptr);

    std::string onRouterValue;
    auto onRouter = [&onRouterValue](const std::string& param) { onRouterValue = param; };
    formNG.SetOnRouter(std::move(onRouter));
    auto frameNodeonRouter = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonRouter, nullptr);

    std::string onLoadValue;
    auto onLoad = [&onLoadValue](const std::string& param) { onLoadValue = param; };
    formNG.SetOnLoad(std::move(onLoad));
    auto frameNodeonLoad = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNodeonLoad, nullptr);
}
} // namespace OHOS::Ace::NG
