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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_TABS_TAB_BAR_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_TABS_TAB_BAR_PAINT_METHOD_H

#include "core/components_ng/pattern/tabs/tab_bar_modifier.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class TabBarPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(TabBarPaintMethod, NodePaintMethod);

public:
    TabBarPaintMethod(const RefPtr<TabBarModifier>& tabBarModifier, const RectF& frameRect,
        const std::vector<bool>& gradientRegions, const Color& backgroundColor,
        const IndicatorStyle& indicatorStyle, const OffsetF& indicatorOffset, bool hasIndicator)
        : tabBarModifier_(tabBarModifier), frameRect_(frameRect), gradientRegions_(gradientRegions),
        backgroundColor_(backgroundColor), indicatorStyle_(indicatorStyle),
        indicatorOffset_(indicatorOffset), hasIndicator_(hasIndicator) {}
    ~TabBarPaintMethod() override = default;

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;
    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override;
    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

private:
    static void PaintGradient(RSCanvas& canvas, const RectF& barRect, const Color& backgroundColor,
        const std::vector<bool>& gradientRegions, const MarginPropertyF& padding);
    static void PaintLeftGradient(RSCanvas& context, const RectF& barRect, const Color& backgroundColor,
        float shadowMargin, float gradientWidth, float padding);
    static void PaintRightGradient(RSCanvas& context, const RectF& barRect, const Color& backgroundColor,
        float shadowMargin, float gradientWidth, float padding);
    static void PaintTopGradient(RSCanvas& context, const RectF& barRect, const Color& backgroundColor,
        float shadowMargin, float gradientWidth);
    static void PaintBottomGradient(RSCanvas& context, const RectF& barRect, const Color& backgroundColor,
        float shadowMargin, float gradientWidth);
    static void PaintGradientRect(RSCanvas& context, const RSRect& gradientRect, const Color& backgroundColor,
        const RSPoint& startPoint, const RSPoint& endPoint, float shadowMargin, float gradientWidth);

    RefPtr<TabBarModifier> tabBarModifier_;
    RectF frameRect_;
    std::vector<bool> gradientRegions_;
    Color backgroundColor_;
    IndicatorStyle indicatorStyle_;
    OffsetF indicatorOffset_;
    bool hasIndicator_ = true;
    ACE_DISALLOW_COPY_AND_MOVE(TabBarPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_TABS_TAB_BAR_PAINT_METHOD_H
