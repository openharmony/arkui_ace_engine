/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tab_content_node.h"

#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int DEFAULT_MAXLINES = 1;
} // namespace

void TabContentNode::OnAttachToMainTree(bool recursive)
{
    if (!UseOffscreenProcess()) {
        ProcessTabBarItem();
    }
    FrameNode::OnOffscreenProcess(recursive);
}

void TabContentNode::OnDetachFromMainTree(bool recursive)
{
    auto tabs = TabContentModelNG::FindTabsNode(Referenced::Claim(this));
    CHECK_NULL_VOID(tabs);

    // Change focus to the other tab if current is being deleted
    auto swiper = AceType::DynamicCast<FrameNode>(tabs->GetTabs());
    CHECK_NULL_VOID(swiper);

    auto swiperPattern = AceType::DynamicCast<SwiperPattern>(swiper->GetPattern());
    CHECK_NULL_VOID(swiperPattern);

    auto deletedIdx = swiper->GetChildFlatIndex(GetId()).second;
    auto currentIdx = swiperPattern->GetCurrentShownIndex();
    LOGD("Deleting tab: %{public}d, currentTab: %{public}d", deletedIdx, swiperPattern->GetCurrentShownIndex());

    // Removing currently shown tab, focus on first after that
    if (currentIdx == deletedIdx) {
        swiperPattern->GetSwiperController()->SwipeToWithoutAnimation(0);
    }
    TabContentModelNG::RemoveTabBarItem(Referenced::Claim(this));

    // Removing tab before current, re-focus on the same tab with new index
    if (currentIdx > deletedIdx) {
        LOGD("RE-activate TAB with new IDX %{public}d from idx %{public}d", currentIdx - 1, deletedIdx);
        swiperPattern->GetSwiperController()->SwipeToWithoutAnimation(currentIdx - 1);
    }
}

void TabContentNode::OnOffscreenProcess(bool recursive)
{
    ProcessTabBarItem();
    FrameNode::OnOffscreenProcess(recursive);
}

void TabContentNode::ProcessTabBarItem()
{
    auto tabs = TabContentModelNG::FindTabsNode(Referenced::Claim(this));
    CHECK_NULL_VOID(tabs);
    auto swiper = tabs->GetTabs();
    CHECK_NULL_VOID(swiper);
    auto myIndex = swiper->GetChildFlatIndex(GetId()).second;
    bool update = false;
#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        if (distributedUI->IsSinkMode()) {
            update = true;
        }
    } while (false);
#endif
    TabContentModelNG::AddTabBarItem(Referenced::Claim(this), myIndex, update);
}

RefPtr<TabContentNode> TabContentNode::GetOrCreateTabContentNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto node = GetFrameNode(tag, nodeId);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(node);

    if (tabContentNode) {
        LOGD("found existing");
        return tabContentNode;
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    tabContentNode = AceType::MakeRefPtr<TabContentNode>(tag, nodeId, pattern, false);
    tabContentNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(tabContentNode);
    return tabContentNode;
}

void TabContentNode::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    FrameNode::ToJsonValue(json);
    auto tabBar = JsonUtil::Create(true);

    auto tabContentPattern = GetPattern<TabContentPattern>();
    CHECK_NULL_VOID(tabContentPattern);

    auto indicator = JsonUtil::Create(true);
    auto indicatorStyle = tabContentPattern->GetIndicatorStyle();
    indicator->Put("color", indicatorStyle.color.ColorToString().c_str());
    indicator->Put("height", indicatorStyle.height.ToString().c_str());
    indicator->Put("width", indicatorStyle.width.ToString().c_str());
    indicator->Put("borderRadius", indicatorStyle.borderRadius.ToString().c_str());
    indicator->Put("marginTop", indicatorStyle.marginTop.ToString().c_str());
    tabBar->Put("indicator", indicator);

    auto board = JsonUtil::Create(true);
    auto boardStyle = tabContentPattern->GetBoardStyle();
    board->Put("borderRadius", boardStyle.borderRadius.ToString().c_str());
    tabBar->Put("board", board);

    tabBar->Put("selectedMode", tabContentPattern->GetSelectedMode() == SelectedMode::INDICATOR ?
		"SelectedMode.INDICATOR" : "SelectedMode.BOARD");

    auto font = JsonUtil::Create(true);
    auto labelStyle = tabContentPattern->GetLabelStyle();
    font->Put("size", labelStyle.fontSize.value_or(Dimension(0)).ToString().c_str());
    font->Put("weight",
        V2::ConvertWrapFontWeightToStirng(labelStyle.fontWeight.value_or(FontWeight::NORMAL)).c_str());
    std::vector<std::string> emptyFontFamily = { "" };
    auto fontFamilyVector = labelStyle.fontFamily.value_or(emptyFontFamily);
    std::string fontFamily = fontFamilyVector.at(0);
    for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
        fontFamily += ',' + fontFamilyVector.at(i);
    }
    font->Put("family", fontFamily.c_str());
    font->Put("style", labelStyle.fontStyle.value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL
                                ? "FontStyle.Normal"
                                : "FontStyle.Italic");

    auto label = JsonUtil::Create(true);
    label->Put("overflow",
        V2::ConvertWrapTextOverflowToString(labelStyle.textOverflow.value_or(TextOverflow::ELLIPSIS)).c_str());
    label->Put("maxLines", std::to_string(labelStyle.maxLines.value_or(DEFAULT_MAXLINES)).c_str());
    label->Put("minFontSize", labelStyle.minFontSize.value_or(Dimension(0)).ToString().c_str());
    label->Put("maxFontSize", labelStyle.maxFontSize.value_or(Dimension(0)).ToString().c_str());
    label->Put("heightAdaptivePolicy", V2::ConvertWrapTextHeightAdaptivePolicyToString(
        labelStyle.heightAdaptivePolicy.value_or(TextHeightAdaptivePolicy::MAX_LINES_FIRST)).c_str());
    label->Put("font", font);
    tabBar->Put("labelStyle", label);
    
    json->Put("tabBar", tabBar);
}
} // namespace OHOS::Ace::NG
