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

#include "grid_row_base_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
void GridRowBaseTestNG::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void GridRowBaseTestNG::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void GridRowBaseTestNG::SetUp() 
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

void GridRowBaseTestNG::TearDown() {}

RefPtr<FrameNode> GridRowBaseTestNG::CreateGridRow(const std::function<void(GridRowModelNG)>& callback)
{
    GridRowModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> GridRowBaseTestNG::CreateGridCol(const std::function<void(GridColModelNG)>& callback)
{
    GridColModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

} // namespace OHOS::Ace::NG
