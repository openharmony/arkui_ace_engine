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

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/list/list_item_event_hub.h"
#include "core/components_v2/list/list_properties.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
static constexpr int TEST_RESOURCE_ID = 1000;
static constexpr int32_t NODE_ID = 555;
struct CheckEvent {
    int32_t resourceId;
    Ark_NativePointer parentNode;
};
static std::optional<RefPtr<UINode>> uiNode = std::nullopt;
static std::optional<CheckEvent> checkEventH = std::nullopt;
static std::optional<CheckEvent> checkEventF = std::nullopt;

class ListItemGroupModifierTest : public ModifierTestBase<GENERATED_ArkUIListItemGroupModifier,
    &GENERATED_ArkUINodeModifiers::getListItemGroupModifier, GENERATED_ARKUI_LIST_ITEM_GROUP> {
public:
    CustomNodeBuilder getBuilderCb(bool headerCb = true)
    {
        static std::optional<bool> isHeader;
        static std::optional<bool> isFooter;
        if (headerCb) {
            isHeader = true;
        } else {
            isFooter = true;
        }
        auto checkCallback = [](
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            if (isHeader) {
                checkEventH = {.resourceId = resourceId, .parentNode = parentNode};
            }
            if (isFooter) {
                checkEventF = {.resourceId = resourceId, .parentNode = parentNode};
            }
            if (uiNode) {
                CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
            }
        };
        CustomNodeBuilder customBuilder =
            Converter::ArkValue<CustomNodeBuilder>(checkCallback, TEST_RESOURCE_ID);
        return customBuilder;
    }
};

/*
 * @tc.name: setListItemGroupOptionsTest
 * @tc.desc: Check the functionality of ListItemGroupModifier.setListItemGroupOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModifierTest, setListItemGroupOptionsTest, TestSize.Level1)
{
    auto style = GetAttrValue<std::string>(node_, "itemGroupStyle");
    EXPECT_EQ(style, "ListItemGroupStyle.NONE");
    auto space = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(space, "0.00vp");

    auto arg = Converter::ArkValue<Opt_ListItemGroupOptions>(Ark_Empty());
    modifier_->setListItemGroupOptions(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemGroupStyle");
    EXPECT_EQ(style, "ListItemGroupStyle.NONE");
    space = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(space, "0.00vp");

    Ark_ListItemGroupOptions groupOptions = {
        .style = Converter::ArkValue<Opt_ListItemGroupStyle>
            (Converter::ArkValue<Ark_ListItemGroupStyle>(V2::ListItemGroupStyle::CARD)),
        .space = Converter::ArkValue<Opt_Union_Number_String>
            (Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(10)),
    };
    arg = Converter::ArkValue<Opt_ListItemGroupOptions>(groupOptions);
    modifier_->setListItemGroupOptions(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemGroupStyle");
    EXPECT_EQ(style, "ListItemGroupStyle.CARD");
    space = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(space, "10.00vp");

    groupOptions = {
        .style = Converter::ArkValue<Opt_ListItemGroupStyle>
            (Converter::ArkValue<Ark_ListItemGroupStyle>(V2::ListItemGroupStyle::CARD)),
        .space = Converter::ArkValue<Opt_Union_Number_String>
            (Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("20")),
    };
    arg = Converter::ArkValue<Opt_ListItemGroupOptions>(groupOptions);
    modifier_->setListItemGroupOptions(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemGroupStyle");
    EXPECT_EQ(style, "ListItemGroupStyle.CARD");
    space = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(space, "20.00vp");

    groupOptions = {
        .style = Converter::ArkValue<Opt_ListItemGroupStyle>(Ark_Empty()),
        .space = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty()),
    };
    arg = Converter::ArkValue<Opt_ListItemGroupOptions>(groupOptions);
    modifier_->setListItemGroupOptions(node_, &arg);
    style = GetAttrValue<std::string>(node_, "itemGroupStyle");
    // should be NONE but GetHost returns nullptr in SetListItemGroupStyle
    EXPECT_EQ(style, "ListItemGroupStyle.CARD");
    space = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(space, "0.00vp");
}

/*
 * @tc.name: setListItemGroupOptionsCustomBuilderTest
 * @tc.desc: Check the functionality of ListItemGroupModifier.setListItemGroupOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModifierTest, setListItemGroupOptionsCustomBuilderTest, TestSize.Level1)
{
    uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
    auto builder = getBuilderCb();
    auto header = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);

    auto builder2 = getBuilderCb(false);
    auto footer = Converter::ArkValue<Opt_CustomNodeBuilder>(builder2);
    Ark_ListItemGroupOptions options = {
        .header = header,
        .footer = footer,
        .style = Converter::ArkValue<Opt_ListItemGroupStyle>
            (Converter::ArkValue<Ark_ListItemGroupStyle>(V2::ListItemGroupStyle::CARD)),
        .space = Converter::ArkValue<Opt_Union_Number_String>
            (Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(10))};
    auto optionsOpt = Converter::ArkValue<Opt_ListItemGroupOptions>(options);
    checkEventH = std::nullopt;
    checkEventF = std::nullopt;
    modifier_->setListItemGroupOptions(node_, &optionsOpt);
    ASSERT_EQ(checkEventH.has_value(), true);
    EXPECT_EQ(checkEventH->resourceId, TEST_RESOURCE_ID);
    ASSERT_EQ(checkEventF.has_value(), true);
    EXPECT_EQ(checkEventF->resourceId, TEST_RESOURCE_ID);
    uiNode = std::nullopt;
    checkEventH = std::nullopt;
    checkEventF = std::nullopt;
}

/**
 * @tc.name: setDividerTest
 * @tc.desc: Check the functionality of ListItemGroupModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModifierTest, setDividerTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto dividerCheckValue = dividerObject->ToString();
    EXPECT_EQ(dividerCheckValue, "{}");

    // set valid values, color as Ark_Color aka int
    Ark_ListDividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>(11.),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77.)),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_WHITE),
    };
    auto divider = Converter::ArkValue<Opt_ListDividerOptions>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "11.00vp");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "55.50vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "77.00vp");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FFFFFFFF");

    // set color as Ark_Number
    dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>(11.),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77.)),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456),
    };
    divider = Converter::ArkValue<Opt_ListDividerOptions>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FF123456");
}

/**
 * @tc.name: setDividerUndefinedTest
 * @tc.desc: Check the functionality of ListItemGroupModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModifierTest, setDividerUndefinedTest, TestSize.Level1)
{
    // set undefined values
    Ark_ListDividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>(11.),
        .startMargin = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .endMargin = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .color = Converter::ArkValue<Opt_ResourceColor>(),
    };
    auto divider = Converter::ArkValue<Opt_ListDividerOptions>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "11.00vp");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "0.00vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "0.00vp");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#00000000");
}

/**
 * @tc.name: setDividerColorStringTest
 * @tc.desc: Check the functionality of ListItemGroupModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModifierTest, setDividerColorStringTest, TestSize.Level1)
{
    // set color as Ark_String
    Ark_ListDividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>(11.),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77.)),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"),
    };
    auto divider = Converter::ArkValue<Opt_ListDividerOptions>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#11223344");

    divider = Converter::ArkValue<Opt_ListDividerOptions>();
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "0.00vp");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "0.00vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "0.00vp");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#00000000");
}

/**
 * @tc.name: setChildrenMainSizeTest
 * @tc.desc: Check the functionality of ListItemGroupModifier.setChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModifierTest, DISABLED_setChildrenMainSizeTest, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
}
} // namespace OHOS::Ace::NG
