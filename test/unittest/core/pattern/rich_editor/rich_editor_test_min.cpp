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

#include "rich_editor_test_min.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#undef private
#undef protected

using namespace testing;
using namespace OHOS::Ace;
using namespace OHOS::Ace::NG;

void RichEditorTestBase::SetUpTestCase() {}

void RichEditorTestBase::TearDownTestCase() {}

void RichEditorTestBase::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(testing::Return(textFieldTheme));
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    pattern->InitScrollablePattern();
    pattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    pattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorTestBase::TearDown()
{
    richEditorNode_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}
