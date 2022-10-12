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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_layout_property.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_view.h"
#include "core/components_ng/test/pattern/relative_container/relative_container_common_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {

const std::string CONTAINER_ID = "__container__";

} // namespace

class RelativeContainerPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: RelativeContainerPropertyTest001
 * @tc.desc: Add first item--Bottom1 with alignrules value into RelativeContainer and get it.
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerPropertyTestNg, RelativeContainerPatternTest001, TestSize.Level1)
{
    RelativeContainerView::Create();
    auto relativeContainerFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_FALSE(relativeContainerFrameNode == nullptr);
    auto relativeContainerLayoutProperty = relativeContainerFrameNode->GetLayoutProperty();
    EXPECT_FALSE(relativeContainerLayoutProperty == nullptr);
    auto relativeContainerLayoutWrapper = relativeContainerFrameNode->CreateLayoutWrapper();
    EXPECT_FALSE(relativeContainerLayoutWrapper == nullptr);

    /**
    corresponding ets code:
       RelativeContainer() {
            Button("Button 1")
              .alignRules({
                left: { anchor: "__container__", align: HorizontalAlign.Start }
              }).id("bt1").borderWidth(1).borderColor(Color.Black)
            }.width(200).height(200).backgroundColor(Color.Orange)
    */
    auto firstItem = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 1, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::ButtonPattern>(); });
    const auto& firstItemFlexProperty = firstItem->GetLayoutProperty()->GetFlexItemProperty();
    std::map<AlignDirection, AlignRule> firstItemAlignRules;
    RelativeContainerTestUtilsNG::AddAlignRule(
        CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstItemAlignRules);
    firstItem->GetLayoutProperty()->UpdateAlignRules(firstItemAlignRules);
    relativeContainerFrameNode->AddChild(firstItem);
    EXPECT_EQ(firstItemFlexProperty->GetAlignRulesValue(), firstItemAlignRules);
}

} // namespace OHOS::Ace::NG