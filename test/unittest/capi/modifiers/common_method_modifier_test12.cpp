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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "generated/type_helpers.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "test/unittest/capi/stubs/ace_pixelmap_stub.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_DRAG_PREVIEW_NAME = "dragPreview";
    const auto ATTRIBUTE_DRAG_PREVIEW_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_OVERLAY_NAME = "overlay";
    const auto ATTRIBUTE_OVERLAY_DEFAULT_VALUE = "{\"title\":\"\","
        "\"options\":{\"align\":\"Alignment.Center\",\"offset\":{\"x\":\"0.00px\",\"y\":\"0.00px\"}}}";
}


class CommonMethodModifierTest12 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

//////////// DragPreview
/*
 * @tc.name: setDragPreviewTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest12, setDragPreviewTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_DRAG_PREVIEW_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_DRAG_PREVIEW_DEFAULT_VALUE);
}

/*
 * @tc.name: setDragPreview_CustomBuilderTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest12, DISABLED_setDragPreview0TestCustomBuilderTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDragPreview0, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    int callsCount = 0;
    CustomNodeBuilderTestHelper<CommonMethodModifierTest12> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();

    auto unionValue = Converter::ArkUnion<Opt_Union_CustomBuilder_DragItemInfo_String,
        CustomNodeBuilder>(builder);
    modifier_->setDragPreview0(node_, &unionValue);
    const DragDropInfo resultDragPreview = frameNode->GetDragPreview();

    EXPECT_EQ(builderHelper.GetCustomNode(), Referenced::RawPtr(resultDragPreview.customNode));
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
}

/*
 * @tc.name: setDragPreview_DragItemInfoTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest12, DISABLED_setDragPreview0TestDragItemInfoTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDragPreview0, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    // CustomNodeBuilder
    int callsCount = 0;
    CustomNodeBuilderTestHelper<CommonMethodModifierTest12> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    // PixelMap
    Ace::RefPtr<Ace::PixelMap> expectedPixelMapRefPtr = AceType::MakeRefPtr<Ace::PixelMapStub>();
    image_PixelMapPeer pixelMapPeer;
    pixelMapPeer.pixelMap = expectedPixelMapRefPtr;
    Ark_image_PixelMap expectedPixelMap = &pixelMapPeer;
    // ExtraInfo
    std::string expectedExtraInfo{"extraInfo"};
    // struct DragItemInfo
    Ark_DragItemInfo dragItemInfo = {
        .builder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder),
        .extraInfo = Converter::ArkValue<Opt_String>(expectedExtraInfo),
        .pixelMap = Converter::ArkValue<Opt_image_PixelMap>(expectedPixelMap)};

    auto unionValue = Converter::ArkUnion<Opt_Union_CustomBuilder_DragItemInfo_String,
        Ark_DragItemInfo>(dragItemInfo);
    modifier_->setDragPreview0(node_, &unionValue);
    const DragDropInfo resultDragPreview = frameNode->GetDragPreview();

    EXPECT_EQ(builderHelper.GetCustomNode(), Referenced::RawPtr(resultDragPreview.customNode));
    EXPECT_EQ(resultDragPreview.extraInfo, expectedExtraInfo);
    EXPECT_EQ(resultDragPreview.pixelMap, expectedPixelMapRefPtr);
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
}

/*
 * @tc.name: setDragPreview_String
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest12, DISABLED_setDragPreview0TestString, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDragPreview0, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string expectedString{"DragPreview_String"};
    auto arkExpectedString = Converter::ArkValue<Ark_String>(expectedString);

    auto unionValue = Converter::ArkUnion<Opt_Union_CustomBuilder_DragItemInfo_String, Ark_String>(arkExpectedString);
    modifier_->setDragPreview0(node_, &unionValue);

    const DragDropInfo resultDragPreview = frameNode->GetDragPreview();

    EXPECT_EQ(resultDragPreview.inspectorId, expectedString);
}

//////// AccessibilityVirtualNode
/*
 * @tc.name: AccessibilityVirtualNode
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest12, AccessibilityVirtualNodeTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAccessibilityVirtualNode, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    int callsCount = 0;
    CustomNodeBuilderTestHelper<CommonMethodModifierTest12> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    const auto arkBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(builder);
    modifier_->setAccessibilityVirtualNode(node_, &arkBuilder);
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
}

//////// Overlay
using OverlayTestStep = std::tuple<Ark_Alignment, std::string>;
static const std::vector<OverlayTestStep> testPlan = {
    {Ark_Alignment::ARK_ALIGNMENT_TOP_START, "{\"title\":\"overlay string\","
        "\"options\":{\"align\":\"Alignment.TopStart\",\"offset\":{\"x\":\"5.00vp\",\"y\":\"6.00vp\"}}}"},
    {Ark_Alignment::ARK_ALIGNMENT_TOP, "{\"title\":\"overlay string\","
        "\"options\":{\"align\":\"Alignment.Top\",\"offset\":{\"x\":\"5.00vp\",\"y\":\"6.00vp\"}}}"},
    {Ark_Alignment::ARK_ALIGNMENT_TOP_END, "{\"title\":\"overlay string\","
        "\"options\":{\"align\":\"Alignment.TopEnd\",\"offset\":{\"x\":\"5.00vp\",\"y\":\"6.00vp\"}}}"},
    {Ark_Alignment::ARK_ALIGNMENT_START, "{\"title\":\"overlay string\","
        "\"options\":{\"align\":\"Alignment.Start\",\"offset\":{\"x\":\"5.00vp\",\"y\":\"6.00vp\"}}}"},
    {Ark_Alignment::ARK_ALIGNMENT_CENTER, "{\"title\":\"overlay string\","
        "\"options\":{\"align\":\"Alignment.Center\",\"offset\":{\"x\":\"5.00vp\",\"y\":\"6.00vp\"}}}"},
    {Ark_Alignment::ARK_ALIGNMENT_END, "{\"title\":\"overlay string\","
        "\"options\":{\"align\":\"Alignment.End\",\"offset\":{\"x\":\"5.00vp\",\"y\":\"6.00vp\"}}}"},
    {Ark_Alignment::ARK_ALIGNMENT_BOTTOM_START, "{\"title\":\"overlay string\","
        "\"options\":{\"align\":\"Alignment.BottomStart\",\"offset\":{\"x\":\"5.00vp\",\"y\":\"6.00vp\"}}}"},
    {Ark_Alignment::ARK_ALIGNMENT_BOTTOM, "{\"title\":\"overlay string\","
        "\"options\":{\"align\":\"Alignment.Bottom\",\"offset\":{\"x\":\"5.00vp\",\"y\":\"6.00vp\"}}}"},
    {Ark_Alignment::ARK_ALIGNMENT_BOTTOM_END, "{\"title\":\"overlay string\","
        "\"options\":{\"align\":\"Alignment.BottomEnd\",\"offset\":{\"x\":\"5.00vp\",\"y\":\"6.00vp\"}}}"},
};

/*
 * @tc.name: OverlayTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest12, OverlayTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_OVERLAY_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_OVERLAY_DEFAULT_VALUE);
}

/*
 * @tc.name: OverlayTest_Union_String_CustomNodeBuilder_Values
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest12, DISABLED_OverlayTest_Union_String_CustomNodeBuilder_Values, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOverlay, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string expectedStr = "overlay string";
    auto arkExpectedStr = Converter::ArkValue<Ark_String>(expectedStr);
    auto unionStringValue = Converter::ArkUnion<Opt_Union_String_CustomBuilder_ComponentContent, Ark_String>(
        arkExpectedStr);
    Ark_OverlayOffset arkOverlayOffset = {
        .x = Converter::ArkValue<Opt_Number>(5), .y = Converter::ArkValue<Opt_Number>(6)};
    Ark_OverlayOptions arkOverlayOptions;
    Opt_OverlayOptions optOverlayOptions;

    for (auto [inputValue, expectedValue]: testPlan) {
        arkOverlayOptions = {
            .align = Converter::ArkValue<Opt_Alignment>(inputValue),
            .offset = Converter::ArkValue<Opt_OverlayOffset>(arkOverlayOffset),
        };
        optOverlayOptions = Converter::ArkValue<Opt_OverlayOptions>(arkOverlayOptions);
        modifier_->setOverlay(node_, &unionStringValue, &optOverlayOptions);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_OVERLAY_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }

    // test CustomNodeBuilder
    int callsCount = 0;
    CustomNodeBuilderTestHelper<CommonMethodModifierTest12> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    auto unionCustomNodeBuilderValue = Converter::ArkUnion<Opt_Union_String_CustomBuilder_ComponentContent,
        CustomNodeBuilder>(builder);
    modifier_->setOverlay(node_, &unionCustomNodeBuilderValue, &optOverlayOptions);
    EXPECT_EQ(builderHelper.GetCallsCountAsync(), ++callsCount);
}

}
