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
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/components/counter/counter_theme.h"
#include "core/components_ng/pattern/counter/counter_pattern.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_ENABLE_DEC_NAME = "enableDec";
    const auto ATTRIBUTE_ENABLE_DEC_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_ENABLE_INC_NAME = "enableInc";
    const auto ATTRIBUTE_ENABLE_INC_DEFAULT_VALUE = "true";

    struct EventsTracker {
        static inline GENERATED_ArkUICounterEventsReceiver counterEventsReceiver {};

        static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
            .getCounterEventsReceiver = [] () -> const GENERATED_ArkUICounterEventsReceiver* {
                return &counterEventsReceiver;
            }
        };
    }; // EventsTracker
} // namespace

class CounterModifierTest : public ModifierTestBase<GENERATED_ArkUICounterModifier,
    &GENERATED_ArkUINodeModifiers::getCounterModifier, GENERATED_ARKUI_COUNTER> {
public:

    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
            return counterTheme;
        });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp();
        GeneratedModifier::GetFullAPI()->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/*
 * @tc.name: setEnableDecTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setEnableDecTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_DEC_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ENABLE_DEC_DEFAULT_VALUE);
}

/*
 * @tc.name: setEnableDecTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setEnableDecTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Boolean inputValue;

    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setEnableDec(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_DEC_NAME);
    EXPECT_EQ(strResult, "false");

    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setEnableDec(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_DEC_NAME);
    EXPECT_EQ(strResult, "true");
}

/*
 * @tc.name: setEnableIncTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setEnableIncTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_INC_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ENABLE_INC_DEFAULT_VALUE);
}

/*
 * @tc.name: setEnableIncTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setEnableIncTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Boolean inputValue;

    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setEnableInc(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_INC_NAME);
    EXPECT_EQ(strResult, "false");

    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setEnableInc(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ENABLE_INC_NAME);
    EXPECT_EQ(strResult, "true");
}

/*
 * @tc.name: setOnIncTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setOnIncTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    auto addId = pattern->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    auto subGestureHub = addNode->GetOrCreateGestureEventHub();

    struct CheckEvent {
        int32_t nodeId;
        int32_t value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::counterEventsReceiver.onInc = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
            .value = 1
        };
    };

    modifier_->setOnInc(node_, func);

    EXPECT_EQ(checkEvent.has_value(), false);
    subGestureHub->ActClick();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->value, 1);
}

/*
 * @tc.name: setOnDecTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CounterModifierTest, setOnDecTest, TestSize.Level1)
{
    Ark_Function func = {};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto pattern = frameNode->GetPattern<CounterPattern>();
    auto subId = pattern->GetSubId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    auto subGestureHub = addNode->GetOrCreateGestureEventHub();

    struct CheckEvent {
        int32_t nodeId;
        int32_t value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    EventsTracker::counterEventsReceiver.onDec = [](Ark_Int32 nodeId)
    {
        checkEvent = {
            .nodeId = nodeId,
            .value = -1
        };
    };

    modifier_->setOnDec(node_, func);

    EXPECT_EQ(checkEvent.has_value(), false);
    subGestureHub->ActClick();
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->value, -1);
}
} // namespace OHOS::Ace::NG
