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

#include "flex_base_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
void FlexBaseTestNG::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
}

void FlexBaseTestNG::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void FlexBaseTestNG::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

void FlexBaseTestNG::TearDown() {}

RefPtr<FrameNode> FlexBaseTestNG::CreateFlexRow(const std::function<void(FlexModelNG)>& callback)
{
    FlexModelNG model;
    model.CreateFlexRow();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> FlexBaseTestNG::CreateFlexWrapRow(const std::function<void(FlexModelNG)>& callback)
{
    FlexModelNG model;
    model.CreateWrap();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}
} // namespace OHOS::Ace::NG
