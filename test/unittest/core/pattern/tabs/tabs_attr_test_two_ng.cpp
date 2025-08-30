/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "tabs_test_ng.h"
#include "test/mock/base/mock_system_properties.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
class TabsAttrTestNg : public TabsTestNg {
public:
    std::function<void()> GetDefaultBuilder()
    {
        return []() {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            ViewAbstract::SetWidth(CalcLength(Dimension(1.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetHeight(CalcLength(Dimension(50.f)));
        };
    }

    RefPtr<FrameNode> CreateCustomNode(const std::string& tag)
    {
        auto frameNode = AceType::MakeRefPtr<FrameNode>(
            tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
        auto layoutProperty = frameNode->GetLayoutProperty();
        layoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), CalcLength(Dimension(50.f))));
        return frameNode;
    }
};

/**
 * @tc.name: TabContentCreateWithResourceObj002
 * @tc.desc: test CreateWithResourceObj of TabContentModelNG
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentCreateWithResourceObj002, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    LabelStyle labelStyle;
    std::vector<std::string> fontFamily = { "unknown" };
    Dimension minFontSize = Dimension(8.0, DimensionUnit::VP);
    Dimension maxFontSize = Dimension(24.0, DimensionUnit::VP);
    labelStyle.fontFamily = fontFamily;
    labelStyle.minFontSize = minFontSize;
    labelStyle.maxFontSize = maxFontSize;
    tabContentPattern->SetLabelStyle(labelStyle);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily, fontFamily);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize, minFontSize);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize, maxFontSize);
    ResourceObjectParams paramFontFamily;
    paramFontFamily.type = ResourceObjectParamType::STRING;
    paramFontFamily.value = { "middle" };
    std::vector<ResourceObjectParams> paramsFontFamily;
    paramsFontFamily.push_back(paramFontFamily);
    auto resObjWithFontFamilyStringSize = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), paramsFontFamily, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateWithResourceObj(TabContentJsType::FONT_FAMILY, resObjWithFontFamilyStringSize);
    tabContentPattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily->size(), 1);
    ResourceObjectParams paramMinFontSize;
    paramMinFontSize.type = ResourceObjectParamType::STRING;
    paramMinFontSize.value = "20";
    std::vector<ResourceObjectParams> paramsMinFontSize;
    paramsMinFontSize.push_back(paramMinFontSize);
    auto resObjWithMinFontStringSize = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), paramsMinFontSize, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateWithResourceObj(TabContentJsType::MIN_FONT_SIZE, resObjWithMinFontStringSize);
    tabContentPattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize->Value(), 0.0);
    ResourceObjectParams paramMaxFontSize;
    paramMaxFontSize.type = ResourceObjectParamType::STRING;
    paramMaxFontSize.value = "20";
    std::vector<ResourceObjectParams> paramsMaxFontSize;
    paramsMaxFontSize.push_back(paramMaxFontSize);
    auto resObjWithMaxFontStringSize = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), paramsMinFontSize, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateWithResourceObj(TabContentJsType::MIN_FONT_SIZE, resObjWithMaxFontStringSize);
    tabContentPattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize->Value(), 24);
    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(TabContentJsType::INDICATOR_COLOR, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.IndicatorStyle.color");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj002, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(TabContentJsType::INDICATOR_HEIGHT, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.IndicatorStyle.height");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj003, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(TabContentJsType::INDICATOR_WIDTH, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.IndicatorStyle.width");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj004, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(TabContentJsType::INDICATOR_RADIUS, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.IndicatorStyle.borderRadius");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj005, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(TabContentJsType::INDICATOR_MARGIN_TOP, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.IndicatorStyle.marginTop");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj006, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(TabContentJsType::BORDER_RADIUS, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.IndicatorStyle.borderRadius");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj007, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(TabContentJsType::PADDING, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.tabBarPadding");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj008, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(TabContentJsType::TEXT_CONTENT, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.tabBarParamText");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj009, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(TabContentJsType::TAB_BAR_OPTIONS_ICON, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.tabBarOptions");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}

HWTEST_F(TabsAttrTestNg, TabContentCreateMoreWithResourceObj010, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "#FFE4B5";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithStringColor = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    tabContentModel.CreateMoreWithResourceObj(
        TabContentJsType::BOTTOM_TAB_BAR_STYLE_ICON, frameNode, resObjWithStringColor);
    auto string = tabContentPattern->resourceMgr_->GetResCacheMapByKey("tabContent.bottomTabBarStyle");
    EXPECT_EQ(string, "");

    tabContentModel.Pop();
    g_isConfigChangePerform = false;
}
} // namespace OHOS::Ace::NG