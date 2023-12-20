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

#include "rich_editor_drag_test_ng.h"

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
namespace {
using namespace testing;
using namespace testing::ext;
constexpr float ROOT_WIDTH = 400.f;
constexpr float ROOT_HEIGHT = 800.f;
const std::string IMAGE_VALUE = "image1";
const std::string BUNDLE_NAME = "bundleName";
const std::string MODULE_NAME = "moduleName";
} // namespace

void RichEditorDragTestNG::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void RichEditorDragTestNG::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void RichEditorDragTestNG::SetUp() {}

void RichEditorDragTestNG::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    dragNode_ = nullptr;
    dragPattern_ = nullptr;
}

void RichEditorDragTestNG::CreateRichEditor(Callback&& callback, uint32_t childSpanNum)
{
    ViewAbstract::SetWidth(CalcLength(ROOT_WIDTH));
    ViewAbstract::SetHeight(CalcLength(ROOT_HEIGHT));
    RichEditorModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    CreateDragNodeWithImageSpan(childSpanNum);
    FlushLayoutTask(frameNode_);
}

void RichEditorDragTestNG::CreateDragNodeWithImageSpan(uint32_t childSpanNum)
{
    frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    pattern_ = frameNode_->GetPattern<RichEditorPattern>();
    for (uint32_t index = 0; index < childSpanNum; ++index) {
        AddImageSpan();
    }

    auto children = frameNode_->GetChildren();
    std::list<RefPtr<FrameNode>> imageChildren;
    for (const auto& child : children) {
        auto node = AceType::DynamicCast<FrameNode>(child);
        if (!node) {
            continue;
        }
        auto image = node->GetPattern<ImagePattern>();
        if (image) {
            imageChildren.emplace_back(node);
        }
    }
    pattern_->dragNode_ = RichEditorDragPattern::CreateDragNode(frameNode_, imageChildren);
    dragNode_ = pattern_->dragNode_;
}

void RichEditorDragTestNG::AddImageSpan()
{
    ASSERT_NE(pattern_, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    ImageSourceInfo imageInfo(IMAGE_VALUE, BUNDLE_NAME, MODULE_NAME);
    imageLayoutProperty->UpdateImageSourceInfo(imageInfo);
    imageNode->MountToParent(frameNode_, frameNode_->children_.size());
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->content = " ";
    spanItem->placeholderIndex = 0;
    pattern_->spans_.emplace_back(spanItem);
    int32_t spanTextLength = 0;
    for (auto& span : pattern_->spans_) {
        spanTextLength += StringUtils::ToWstring(span->content).length();
        span->position = spanTextLength;
    }
}

void RichEditorDragTestNG::ClearSpan()
{
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    frameNode_->children_.clear();
    pattern_->spans_.clear();
    pattern_->caretPosition_ = 0;
}

/**
 * @tc.name: RichEditorDragTestNG001
 * @tc.desc: Test FolderStackTestNG properties & ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragTestNG, RichEditorDragTestNG001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FolderStack node with Aniamtion/AutoHalfFold props false, itemId not null.
     */
    CreateRichEditor([](RichEditorModelNG model) {
        model.SetTextDetectEnable(true);
    });
    EXPECT_TRUE(true);
}
} // namespace OHOS::Ace::NG