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

#include "relative_container_base_test_ng.h"

namespace OHOS::Ace::NG {
void RelativeContainerBaseTestNG::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void RelativeContainerBaseTestNG::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RelativeContainerBaseTestNG::SetUp() {}
void RelativeContainerBaseTestNG::TearDown() {}

RefPtr<FrameNode> RelativeContainerBaseTestNG::CreateRelativeContainer(
    const std::function<void(RelativeContainerModelNG)>& callback)
{
    RelativeContainerModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}
} // namespace OHOS::Ace::NG