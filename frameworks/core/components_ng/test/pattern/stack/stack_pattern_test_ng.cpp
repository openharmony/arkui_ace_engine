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

#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/position_param.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const Alignment alignMent = Alignment::TOP_CENTER;
} // namespace
class StackPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: StackPatternTest001
 * @tc.desc: Check the stackModelNG Create() with alignment setted
 * @tc.type: FUNC
 */
HWTEST_F(StackPatternTestNg, StackPatternTest001, TestSize.Level1)
{
    StackModelNG stackModelNG;
    stackModelNG.Create(alignMent);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(frameNode == nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_FALSE(layoutProperty == nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    EXPECT_FALSE(layoutWrapper == nullptr);
    EXPECT_EQ(alignMent, layoutProperty->GetPositionProperty()->GetAlignmentValue());
}
} // namespace OHOS::Ace::NG