/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_group_node.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_event_hub.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_ALIGN_CONTENT_NAME = "alignContent";
    const auto ATTRIBUTE_ALIGN_CONTENT_DEFAULT_VALUE = "Alignment.Center";
    const auto ATTRIBUTE_ENABLE_ANIMATION_NAME = "enableAnimation";
    const auto ATTRIBUTE_ENABLE_ANIMATION_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_AUTO_HALF_FOLD_NAME = "autoHalfFold";
    const auto ATTRIBUTE_AUTO_HALF_FOLD_DEFAULT_VALUE = "true";

struct EventsTracker {
    static inline GENERATED_ArkUIFolderStackEventsReceiver eventsReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
        .getFolderStackEventsReceiver = [] () -> const GENERATED_ArkUIFolderStackEventsReceiver* {
            return &eventsReceiver;
        }
    };
}; // EventsTracker
} // namespace

class FolderStackModifierTest : public ModifierTestBase<
    GENERATED_ArkUIFolderStackModifier,
    &GENERATED_ArkUINodeModifiers::getFolderStackModifier,
    GENERATED_ARKUI_FOLDER_STACK> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/*
 * @tc.name: setAlignContentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackModifierTest, setAlignContentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ALIGN_CONTENT_DEFAULT_VALUE);
}

// Valid values for attribute 'alignContent' of method 'alignContent'
static std::vector<std::tuple<std::string, enum Ark_Alignment, std::string>> alignContentAlignContentValidValues = {
    {"ARK_ALIGNMENT_TOP_START", Converter::ArkValue<enum Ark_Alignment>(ARK_ALIGNMENT_TOP_START),
        "Alignment.TopStart"},
    {"ARK_ALIGNMENT_TOP", Converter::ArkValue<enum Ark_Alignment>(ARK_ALIGNMENT_TOP),
        "Alignment.Top"},
    {"ARK_ALIGNMENT_TOP_END", Converter::ArkValue<enum Ark_Alignment>(ARK_ALIGNMENT_TOP_END),
        "Alignment.TopEnd"},
    {"ARK_ALIGNMENT_START", Converter::ArkValue<enum Ark_Alignment>(ARK_ALIGNMENT_START),
        "Alignment.Start"},
    {"ARK_ALIGNMENT_CENTER", Converter::ArkValue<enum Ark_Alignment>(ARK_ALIGNMENT_CENTER),
        "Alignment.Center"},
    {"ARK_ALIGNMENT_END", Converter::ArkValue<enum Ark_Alignment>(ARK_ALIGNMENT_END),
        "Alignment.End"},
    {"ARK_ALIGNMENT_BOTTOM_START", Converter::ArkValue<enum Ark_Alignment>(ARK_ALIGNMENT_BOTTOM_START),
        "Alignment.BottomStart"},
    {"ARK_ALIGNMENT_BOTTOM", Converter::ArkValue<enum Ark_Alignment>(ARK_ALIGNMENT_BOTTOM),
        "Alignment.Bottom"},
    {"ARK_ALIGNMENT_BOTTOM_END", Converter::ArkValue<enum Ark_Alignment>(ARK_ALIGNMENT_BOTTOM_END),
        "Alignment.BottomEnd"},
};

/*
 * @tc.name: setAlignContentTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackModifierTest, setAlignContentTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Alignment inputValueAlignContent;
    Ark_Alignment initValueAlignContent;

    // Initial setup
    initValueAlignContent = std::get<1>(alignContentAlignContentValidValues[0]);

    // Verifying attribute's  values
    inputValueAlignContent = initValueAlignContent;
    for (auto&& value: alignContentAlignContentValidValues) {
        inputValueAlignContent = std::get<1>(value);
        modifier_->setAlignContent(node_, inputValueAlignContent);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_CONTENT_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

// Invalid values for attribute 'alignContent' of method 'alignContent'
static std::tuple<std::string, enum Ark_Alignment> alignContentAlignContentInvalidValue = {
    "static_cast<enum Ark_Alignment>(-1)",
    Converter::ArkValue<enum Ark_Alignment>(static_cast<enum Ark_Alignment>(-1))
};

/*
 * @tc.name: setAlignContentTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackModifierTest, setAlignContentTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Alignment inputValueAlignContent;
    Ark_Alignment initValueAlignContent;

    // Initial setup
    initValueAlignContent = std::get<1>(alignContentAlignContentValidValues[0]);

    // Verifying attribute's  values
    inputValueAlignContent = initValueAlignContent;
    modifier_->setAlignContent(node_, inputValueAlignContent);
    inputValueAlignContent = std::get<1>(alignContentAlignContentInvalidValue);
    modifier_->setAlignContent(node_, inputValueAlignContent);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ALIGN_CONTENT_NAME);
    expectedStr = ATTRIBUTE_ALIGN_CONTENT_DEFAULT_VALUE;
    EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(alignContentAlignContentInvalidValue);
}

/*
 * @tc.name: setOnFolderStateChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackModifierTest, setOnFolderStateChangeTest, TestSize.Level1)
{
    static Ark_FoldStatus foldStatus = ARK_FOLD_STATUS_FOLD_STATUS_UNKNOWN;
    EventsTracker::eventsReceiver.onFolderStateChange = [](Ark_Int32 nodeId, const Ark_OnFoldStatusChangeInfo event) {
        foldStatus = event.foldStatus;
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    OnFoldStatusChangeCallback func{};
    ASSERT_NE(frameNode, nullptr);
    auto context = reinterpret_cast<PipelineContext*>(MockPipelineContext::GetCurrent().GetRawPtr());
    frameNode->AttachToMainTree(true, context);
    modifier_->setOnFolderStateChange(node_, &func);

    auto folderStackNode = AceType::DynamicCast<FolderStackGroupNode>(frameNode);
    ASSERT_NE(folderStackNode, nullptr);
    auto eventHub = folderStackNode->GetEventHub<FolderStackEventHub>();
    ASSERT_NE(eventHub, nullptr);

    FolderEventInfo info(FoldStatus::FOLDED);
    eventHub->OnFolderStateChange(std::move(info));
    EXPECT_EQ(foldStatus, ARK_FOLD_STATUS_FOLD_STATUS_FOLDED);
}

/*
 * @tc.name: setOnHoverStatusChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackModifierTest, setOnHoverStatusChangeTest, TestSize.Level1)
{
    static Ark_FoldStatus foldStatus = ARK_FOLD_STATUS_FOLD_STATUS_UNKNOWN;
    EventsTracker::eventsReceiver.onHoverStatusChange = [](Ark_Int32 nodeId, const Ark_HoverEventParam param) {
        foldStatus = param.foldStatus;
    };
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    OnHoverStatusChangeCallback func{};
    ASSERT_NE(frameNode, nullptr);
    auto context = reinterpret_cast<PipelineContext*>(MockPipelineContext::GetCurrent().GetRawPtr());
    frameNode->AttachToMainTree(true, context);
    modifier_->setOnHoverStatusChange(node_, &func);

    auto folderStackNode = AceType::DynamicCast<FolderStackGroupNode>(frameNode);
    ASSERT_NE(folderStackNode, nullptr);
    auto eventHub = folderStackNode->GetEventHub<FolderStackEventHub>();
    ASSERT_NE(eventHub, nullptr);

    FolderEventInfo info(FoldStatus::FOLDED);
    eventHub->OnHoverStatusChange(std::move(info));
    EXPECT_EQ(foldStatus, ARK_FOLD_STATUS_FOLD_STATUS_FOLDED);
}

/*
 * @tc.name: setEnableAnimationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackModifierTest, setEnableAnimationTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANIMATION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_ENABLE_ANIMATION_DEFAULT_VALUE);
}

// Valid values for attribute 'enableAnimation' of method 'enableAnimation'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> enableAnimationEnableAnimationValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setEnableAnimationTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackModifierTest, setEnableAnimationTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueEnableAnimation;
    Ark_Boolean initValueEnableAnimation;

    // Initial setup
    initValueEnableAnimation = std::get<1>(enableAnimationEnableAnimationValidValues[0]);

    // Verifying attribute's  values
    inputValueEnableAnimation = initValueEnableAnimation;
    for (auto&& value: enableAnimationEnableAnimationValidValues) {
        inputValueEnableAnimation = std::get<1>(value);
        modifier_->setEnableAnimation(node_, inputValueEnableAnimation);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_ENABLE_ANIMATION_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}

/*
 * @tc.name: setAutoHalfFoldTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackModifierTest, setAutoHalfFoldTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_HALF_FOLD_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_AUTO_HALF_FOLD_DEFAULT_VALUE);
}

// Valid values for attribute 'autoHalfFold' of method 'autoHalfFold'
static std::vector<std::tuple<std::string, Ark_Boolean, std::string>> autoHalfFoldAutoHalfFoldValidValues = {
    {"true", Converter::ArkValue<Ark_Boolean>(true), "true"},
    {"false", Converter::ArkValue<Ark_Boolean>(false), "false"},
};

/*
 * @tc.name: setAutoHalfFoldTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackModifierTest, setAutoHalfFoldTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    std::string expectedStr;
    Ark_Boolean inputValueAutoHalfFold;
    Ark_Boolean initValueAutoHalfFold;

    // Initial setup
    initValueAutoHalfFold = std::get<1>(autoHalfFoldAutoHalfFoldValidValues[0]);

    // Verifying attribute's  values
    inputValueAutoHalfFold = initValueAutoHalfFold;
    for (auto&& value: autoHalfFoldAutoHalfFoldValidValues) {
        inputValueAutoHalfFold = std::get<1>(value);
        modifier_->setAutoHalfFold(node_, inputValueAutoHalfFold);
        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_AUTO_HALF_FOLD_NAME);
        expectedStr = std::get<2>(value);
        EXPECT_EQ(resultStr, expectedStr) << "Passed value is: " << std::get<0>(value);
    }
}
} // namespace OHOS::Ace::NG
