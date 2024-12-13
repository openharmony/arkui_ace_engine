/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_TITLE_BAR_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_TITLE_BAR_LAYOUT_ALGORITHM_H

#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TitleBarLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(TitleBarLayoutAlgorithm, LayoutAlgorithm);

public:
    TitleBarLayoutAlgorithm() = default;
    ~TitleBarLayoutAlgorithm() override = default;
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    float GetInitialTitleOffsetY() const
    {
        return initialTitleOffsetY_;
    }

    void SetInitialTitleOffsetY(float initialTitleOffsetY)
    {
        initialTitleOffsetY_ = initialTitleOffsetY;
    }

    bool IsInitialTitle() const
    {
        return isInitialTitle_;
    }

    void MarkIsInitialTitle(bool isInitialTitle)
    {
        isInitialTitle_ = isInitialTitle;
    }

    float GetInitialSubtitleOffsetY() const
    {
        return initialSubtitleOffsetY_;
    }

    void SetInitialSubtitleOffsetY(float initialSubtitleOffsetY)
    {
        initialSubtitleOffsetY_ = initialSubtitleOffsetY;
    }

    bool IsInitialSubtitle() const
    {
        return isInitialSubtitle_;
    }

    void MarkIsInitialSubtitle(bool isInitialSubtitle)
    {
        isInitialSubtitle_ = isInitialSubtitle;
    }

    void SetMinTitleHeight(float minTitleHeight)
    {
        minTitleHeight_ = minTitleHeight;
    }

    float GetMinTitleHeight() const
    {
        return minTitleHeight_;
    }

private:
    void BackButtonLayout(LayoutWrapper* layoutWrapper);

    void UpdateIconSize(const RefPtr<FrameNode>& backButtonNode);

    void MeasureBackButton(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
        const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty);

    void MeasureSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
        const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize, float occupiedWidth);

    void MeasureTitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
        const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize, float maxWidth);

    float GetTitleWidth(const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize);

    float WidthAfterAvoidMenuBarAndContainerModal(const RefPtr<TitleBarNode>& titleBarNode, float width);

    void MeasureMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
        const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty);

    void ShowBackButtonLayout(LayoutWrapper* layoutWrapper, RefPtr<GeometryNode>& geometryNode,
        const RefPtr<LayoutWrapper>& backButtonWrapper, float titleBarHeight);

    void LayoutBackButton(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
        const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty);

    float GetFullModeTitleOffsetY(float titleHeight, float subtitleHeight, RefPtr<GeometryNode> titleBarGeometryNode);

    void LayoutTitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
        const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, float subtitleHeight);

    void LayoutSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
        const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, float titleHeight);
    void LayoutMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
        const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, float subtitleHeight);
    float ChangeOffsetByDirection(LayoutWrapper* layoutWrapper,
        const RefPtr<NG::GeometryNode>& childGeometryNode, float offsetX) const;

    // set variables from theme
    void InitializeTheme(const RefPtr<TitleBarNode>& titleBarNode, const SizeF& titleBarSize);

    Dimension maxPaddingStart_;
    Dimension maxPaddingEnd_;
    Dimension defaultPaddingStart_;
    Dimension iconSize_;
    Dimension titleFontSize_;
    Dimension iconBackgroundWidth_;
    Dimension backButtonWidth_;
    Dimension backButtonHeight_;
    Dimension backIconWidth_;
    Dimension backIconHeight_;
    Dimension menuCompPadding_;
    Dimension paddingTopTwolines_;
    Dimension titleSpaceVertical_;

    float menuHeight_ = 0.0f;
    float initialTitleOffsetY_ = 0.0f;

    bool isInitialTitle_ = true;
    float initialSubtitleOffsetY_ = 0.0f;
    bool isInitialSubtitle_ = true;
    float minTitleHeight_ = 0.0f;
    float menuWidth_ = 0.0f;
    bool showBackButton_ = false;

    float singleLineTitleHeight_ = 0.0f;
    float doubleLineTitleBarHeight_ = 0.0f;
    float navTitleSpaceVertical_ = 0.0f;
    float paddingLeft_ = 0.0f;
    float paddingLeftForBackButton_ = 0.0f;
    float paddingRight_ = 0.0f;
    float paddingRightForMenu_ = 0.0f;
    float navBackIconWidth_ = 0.0f;
    float navButtonPadding_ = 0.0f;
    float navHorizontalMargin_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(TitleBarLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_TITLE_BAR_LAYOUT_ALGORITHM_H
