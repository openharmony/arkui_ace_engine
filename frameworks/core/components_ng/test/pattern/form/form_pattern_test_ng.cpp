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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_event_hub.h"
#include "core/components_ng/pattern/form/form_layout_property.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/components_ng/pattern/form/form_view.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
FormView formView;
RequestFormInfo formInfo;
DirtySwapConfig config;
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
    formView.Create(formInfo);
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
} // namespace OHOS::Ace::NG
