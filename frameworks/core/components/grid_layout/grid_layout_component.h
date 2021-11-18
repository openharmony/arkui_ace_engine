/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_GRID_LAYOUT_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_GRID_LAYOUT_COMPONENT_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/scroll_bar/scroll_bar_proxy.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"
#include "core/components_v2/grid/grid_position_controller.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace {

class ACE_EXPORT GridLayoutComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(GridLayoutComponent, ComponentGroup);

public:
    explicit GridLayoutComponent(const std::list<RefPtr<Component>>& children) : ComponentGroup(children) {}

    ~GridLayoutComponent() override = default;

    RefPtr<Element> CreateElement() override;

    RefPtr<RenderNode> CreateRenderNode() override;

    void SetDirection(FlexDirection direction);
    void SetFlexAlign(FlexAlign flexAlign);
    void SetColumnCount(int32_t count);
    void SetRowCount(int32_t count);
    void SetWidth(double width);
    void SetHeight(double height);
    void SetColumnsArgs(const std::string& columnsArgs);
    void SetRowsArgs(const std::string& rowsArgs);
    void SetColumnGap(const Dimension& columnGap);
    void SetRowGap(const Dimension& rowGap);
    void SetRightToLeft(bool rightToLeft);

    // set scroll bar color
    void SetScrollBarColor(const std::string& color);

    // set scroll bar width
    void SetScrollBarWidth(const std::string& width);

    void SetScrollBar(DisplayMode displayMode);

    const std::string& GetColumnsArgs() const
    {
        return columnsArgs_;
    }

    const std::string& GetRowsArgs() const
    {
        return rowsArgs_;
    }

    const Dimension& GetColumnGap() const
    {
        return columnGap_;
    }

    const Dimension& GetRowGap() const
    {
        return rowGap_;
    }

    FlexDirection GetDirection() const
    {
        return direction_;
    }

    FlexAlign GetFlexAlign() const
    {
        return flexAlign_;
    }

    int32_t GetColumnCount() const
    {
        return columnCount_;
    }

    int32_t GetRowCount() const
    {
        return rowCount_;
    }

    double GetWidth() const
    {
        return width_;
    }

    double GetHeight() const
    {
        return height_;
    }

    bool GetRightToLeft() const
    {
        return rightToLeft_;
    }

    void SetUseScroll(bool flag)
    {
        useScroll_ = flag;
    }

    const std::string& GetScrollBarColor() const
    {
        return scrollBarColor_;
    }

    const std::string& GetScrollBarWidth() const
    {
        return scrollBarWidth_;
    }

    DisplayMode GetScrollBar()
    {
        return displayMode_;
    }

    void SetDeclarative()
    {
        isDeclarative_ = true;
    }

    const RefPtr<V2::GridPositionController>& GetController() const
    {
        return controller_;
    }

    void SetController(const RefPtr<V2::GridPositionController>& controller)
    {
        controller_ = controller;
    }

    void SetScrolledEvent(const EventMarker& event)
    {
        scrolledEvent_ = event;
    }

    const EventMarker& GetScrolledEvent() const
    {
        return scrolledEvent_;
    }

    void SetCachedCount(int32_t cacheCount)
    {
        cacheCount_ = cacheCount;
    }

    int32_t GetCacheCount() const
    {
        return cacheCount_;
    }

    void SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy)
    {
        scrollBarProxy_ = scrollBarProxy;
    }

    const RefPtr<ScrollBarProxy>& GetScrollBarProxy() const
    {
        return scrollBarProxy_;
    }

private:
    FlexDirection direction_ = FlexDirection::COLUMN;
    FlexAlign flexAlign_ = FlexAlign::CENTER;
    double width_ = -1.0;
    double height_ = -1.0;
    int32_t columnCount_ = 1;
    int32_t rowCount_ = 1;
    bool isDeclarative_ = false;
    int32_t cacheCount_ = 1;

    std::string columnsArgs_;
    std::string rowsArgs_;
    Dimension columnGap_ = 0.0_px;
    Dimension rowGap_ = 0.0_px;
    bool rightToLeft_ = false;
    bool useScroll_ = true;

    // scroll bar attribute
    std::string scrollBarColor_;
    std::string scrollBarWidth_;
    DisplayMode displayMode_ = DisplayMode::OFF;
    RefPtr<V2::GridPositionController> controller_;
    EventMarker scrolledEvent_;
    RefPtr<ScrollBarProxy> scrollBarProxy_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_GRID_LAYOUT_COMPONENT_H
