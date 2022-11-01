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
#include <string>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const bool BUBBLE_PROPERTY_SHOW = true;
const std::string BUBBLE_MESSAGE = "HelloWorld";
} // namespace
class BubblePropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: BubblePropertyTest001
 * @tc.desc: Set show value into BubblePropertyTest001 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest001, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto isShow = popupParam->IsShow();
    EXPECT_EQ(isShow, BUBBLE_PROPERTY_SHOW);
}

/**
 * @tc.name: BubblePropertyTest002
 * @tc.desc: set panelType value into BubblePropertyTest002 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest002, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto message = popupParam->GetMessage();
    EXPECT_EQ(message, BUBBLE_MESSAGE);
}

} // namespace OHOS::Ace::NG
