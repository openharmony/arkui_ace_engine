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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_PATTERN_H

#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_event_hub.h"
#include "core/components_ng/pattern/tabs/tab_content_layout_property.h"
#include "core/components_ng/syntax/shallow_builder.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TabContentPattern : public Pattern {
    DECLARE_ACE_TYPE(TabContentPattern, Pattern);

public:
    explicit TabContentPattern(const RefPtr<ShallowBuilder>& shallowBuilder)
        : shallowBuilder_(shallowBuilder), tabBarParam_(std::string(""), std::string(""), nullptr)
    {}
    ~TabContentPattern() override = default;

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override
    {
        if (shallowBuilder_ && !shallowBuilder_->IsExecuteDeepRenderDone()) {
            auto host = GetHost();
            CHECK_NULL_RETURN(host, false);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            return true;
        }
        return false;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsMeasureBoundary() const override
    {
        return false;
    }

    bool UsResRegion() override
    {
        return false;
    }

    void OnAttachToFrameNode() override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->GetRenderContext()->UpdateClipEdge(true);
        FireWillShowEvent();
        auto parentNode = host->GetAncestorNodeOfFrame();
        CHECK_NULL_VOID(parentNode);
        auto grandParentNode = parentNode->GetAncestorNodeOfFrame();
        CHECK_NULL_VOID(grandParentNode);
        if (grandParentNode->GetTag() == V2::TABS_ETS_TAG) {
            auto tabLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(
                grandParentNode->GetLayoutProperty());
            CHECK_NULL_VOID(tabLayoutProperty);
            if (tabLayoutProperty->GetSafeAreaPaddingProperty()) {
                host->GetLayoutProperty()->UpdateSafeAreaExpandOpts({
                    .type = SAFE_AREA_TYPE_SYSTEM,
                    .edges = SAFE_AREA_EDGE_TOP + SAFE_AREA_EDGE_BOTTOM });
            }
        }
        
    }

    void CheckTabAnimateMode()
    {
        if (!shallowBuilder_ || !firstTimeLayout_) {
            return;
        }

        // Check whether current tabcontent belongs to tab component.
        auto tabContentNode = GetHost();
        CHECK_NULL_VOID(tabContentNode);
        auto parentNode = tabContentNode->GetAncestorNodeOfFrame();
        CHECK_NULL_VOID(parentNode);
        if (parentNode->GetTag() != V2::SWIPER_ETS_TAG) {
            return;
        }
        auto grandParentNode = parentNode->GetAncestorNodeOfFrame();
        CHECK_NULL_VOID(grandParentNode);
        if (grandParentNode->GetTag() != V2::TABS_ETS_TAG) {
            return;
        }

        auto tabsPattern = grandParentNode->GetPattern<TabsPattern>();
        CHECK_NULL_VOID(tabsPattern);
        auto tabsLayoutProperty = grandParentNode->GetLayoutProperty<TabsLayoutProperty>();
        CHECK_NULL_VOID(tabsLayoutProperty);
        TabAnimateMode mode = tabsPattern->GetAnimateMode();
        if (mode == TabAnimateMode::ACTION_FIRST
            && !tabsLayoutProperty->GetHeightAutoValue(false)
            && !tabsLayoutProperty->GetWidthAutoValue(false)) {
            ACE_SCOPED_TRACE("TabContentMarkRenderDone");
            /*
             * Set render done only when tab's height&weight is not set to 'auto' and its animateMode
             * is set to AnimateMode::ACTION_FIRST.
             * Set render done before first layout, so to measure tabcontent and its children
             * in two seperate frame.
             */
            shallowBuilder_->MarkIsExecuteDeepRenderDone(true);
        }
    }

    void CleanChildren()
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (host->GetChildren().empty()) {
            return;
        }
        host->Clean();
        firstTimeLayout_ = true;
        CHECK_NULL_VOID(shallowBuilder_);
        shallowBuilder_->MarkIsExecuteDeepRenderDone(false);
    }

    void BeforeCreateLayoutWrapper() override
    {
        if (firstTimeLayout_) {
            CheckTabAnimateMode();
        }

        if (shallowBuilder_ && !shallowBuilder_->IsExecuteDeepRenderDone()) {
            shallowBuilder_->ExecuteDeepRender();
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        } else if (firstTimeLayout_ && shallowBuilder_ && shallowBuilder_->IsExecuteDeepRenderDone()) {
            auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
            if (!pipeline) {
                shallowBuilder_->MarkIsExecuteDeepRenderDone(false);
                return;
            }

            pipeline->AddAfterRenderTask([weak = WeakClaim(this), shallowBuilder = shallowBuilder_]() {
                CHECK_NULL_VOID(shallowBuilder);
                shallowBuilder->MarkIsExecuteDeepRenderDone(false);
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto host = pattern->GetHost();
                CHECK_NULL_VOID(host);
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
            });
        }
        firstTimeLayout_ = false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TabContentLayoutProperty>();
    }

    void SetTabBar(const std::string& text, const std::string& icon,
                   const std::optional<TabBarSymbol>& tabBarSymbol, TabBarBuilderFunc&& builder)
    {
        tabBarParam_.SetText(text);
        tabBarParam_.SetIcon(icon);
        tabBarParam_.SetSymbol(tabBarSymbol);
        if (tabBarSymbol.has_value()) {
            symbol_ = tabBarSymbol.value();
        }
        tabBarParam_.SetBuilder(move(builder));
    }

    void SetTabBarWithContent(const RefPtr<NG::UINode>& content)
    {
        tabBarParam_.SetContent(content);
    }

    const TabBarSymbol& GetSymbol()
    {
        return symbol_;
    }

    const TabBarParam& GetTabBarParam() const
    {
        return tabBarParam_;
    }

    void SetCustomTabBar(FrameNode* node)
    {
        tabBarParam_.SetCustomNode(node);
    }

    void SetTabBarStyle(TabBarStyle tabBarStyle)
    {
        tabBarParam_.SetTabBarStyle(tabBarStyle);
    }

    TabBarStyle GetTabBarStyle() const
    {
        return tabBarParam_.GetTabBarStyle();
    }

    void SetIndicatorStyle(const IndicatorStyle& indicatorStyle)
    {
        indicatorStyle_ = indicatorStyle;
    }

    const IndicatorStyle& GetIndicatorStyle() const
    {
        return indicatorStyle_;
    }

    void SetSelectedMode(SelectedMode selectedMode)
    {
        selectedMode_ = selectedMode;
    }

    SelectedMode GetSelectedMode() const
    {
        return selectedMode_;
    }

    void SetBoardStyle(const BoardStyle& boardStyle)
    {
        boardStyle_ = boardStyle;
    }

    const BoardStyle& GetBoardStyle() const
    {
        return boardStyle_;
    }

    void SetLabelStyle(const LabelStyle& labelStyle)
    {
        labelStyle_ = labelStyle;
    }

    const LabelStyle& GetLabelStyle() const
    {
        return labelStyle_;
    }

    void SetIconStyle(const IconStyle& iconStyle)
    {
        iconStyle_ = iconStyle;
    }

    const IconStyle& GetIconStyle() const
    {
        return iconStyle_;
    }

    void SetPadding(const PaddingProperty& padding)
    {
        padding_ = padding;
    }

    const PaddingProperty& GetPadding() const
    {
        return padding_;
    }

    void SetUseLocalizedPadding(bool useLocalizedPadding)
    {
        useLocalizedPadding_ = useLocalizedPadding;
    }

    bool GetUseLocalizedPadding()
    {
        return useLocalizedPadding_;
    }

    void SetSymmetricExtensible(bool isExtensible)
    {
        bottomTabBarStyle_.symmetricExtensible = isExtensible;
    }

    void SetLayoutMode(LayoutMode layoutMode)
    {
        bottomTabBarStyle_.layoutMode = layoutMode;
    }

    void SetVerticalAlign(FlexAlign verticalAlign)
    {
        bottomTabBarStyle_.verticalAlign = verticalAlign;
    }

    void SetId(const std::string& id)
    {
        tabBarInspectorId_ = id;
    }

    const std::string& GetId() const
    {
        return tabBarInspectorId_;
    }

    const BottomTabBarStyle& GetBottomTabBarStyle() const
    {
        return bottomTabBarStyle_;
    }

    void DumpAdvanceInfo() override
    {
        switch (selectedMode_) {
            case SelectedMode::INDICATOR: {
                DumpLog::GetInstance().AddDesc("SelectedMode:INDICATOR");
                break;
            }
            case SelectedMode::BOARD: {
                DumpLog::GetInstance().AddDesc("SelectedMode:BOARD");
                break;
            }
            default: {
                break;
            }
        }
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<TabContentEventHub>();
    }

    void FireWillShowEvent()
    {
        auto tabContentEventHub = GetEventHub<TabContentEventHub>();
        CHECK_NULL_VOID(tabContentEventHub);
        tabContentEventHub->FireWillShowEvent();
    }

    void FireWillHideEvent()
    {
        auto tabContentEventHub = GetEventHub<TabContentEventHub>();
        CHECK_NULL_VOID(tabContentEventHub);
        tabContentEventHub->FireWillHideEvent();
    }

    bool HasSubTabBarStyleNode() const
    {
        return customStyleNode_ != nullptr;
    }

    void SetCustomStyleNode(const RefPtr<FrameNode>& customStyleNode)
    {
        customStyleNode_ = customStyleNode;
    }

    const RefPtr<FrameNode>& FireCustomStyleNode() const
    {
        return customStyleNode_;
    }

    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override
    {
        switch (selectedMode_) {
            case SelectedMode::INDICATOR: {
                json->Put("SelectedMode", "INDICATOR");
                break;
            }
            case SelectedMode::BOARD: {
                json->Put("SelectedMode", "BOARD");
                break;
            }
            default: {
                break;
            }
        }
    }

private:
    RefPtr<ShallowBuilder> shallowBuilder_;
    TabBarParam tabBarParam_;
    IndicatorStyle indicatorStyle_;
    SelectedMode selectedMode_ = SelectedMode::INDICATOR;
    BoardStyle boardStyle_;
    LabelStyle labelStyle_;
    IconStyle iconStyle_;
    PaddingProperty padding_;
    std::string tabBarInspectorId_;
    BottomTabBarStyle bottomTabBarStyle_;
    RefPtr<FrameNode> customStyleNode_ = nullptr;
    TabBarSymbol symbol_;

    bool firstTimeLayout_ = true;
    bool useLocalizedPadding_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(TabContentPattern);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TAB_CONTENT_PATTERN_H
