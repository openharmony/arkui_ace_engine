/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TAG_VALUE = "ContainerModal";
} // namespace

class ContainerModalTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: ContainerModalTest001
 * @tc.desc: Check number of children in container_modal
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalTestNg, ContainerModalTest001, TestSize.Level1)
{
    RefPtr<FrameNode> content;
    auto container = ContainerModalView::Create(content);
    EXPECT_FALSE(container == nullptr);
    EXPECT_EQ(container->GetChildren().size(), 1);
    EXPECT_EQ(container->GetTag(), TAG_VALUE);
}
} // namespace OHOS::Ace::NG