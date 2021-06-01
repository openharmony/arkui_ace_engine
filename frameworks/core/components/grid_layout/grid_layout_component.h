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
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace {

class ACE_EXPORT GridLayoutComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(GridLayoutComponent, ComponentGroup);

public:
    explicit GridLayoutComponent(const std::list<RefPtr<Component>>& children)
        : ComponentGroup(children) {}

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
    void SetColumnGap(double columnGap);
    void SetRowGap(double rowGap);
    void SetRightToLeft(bool rightToLeft);

    const std::string& GetColumnsArgs() const
    {
        return columnsArgs_;
    }

    const std::string& GetRowsArgs() const
    {
        return rowsArgs_;
    }

    double GetColumnGap() const
    {
        return columnGap_;
    }

    double GetRowGap() const
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

private:
    FlexDirection direction_ = FlexDirection::COLUMN;
    FlexAlign flexAlign_ = FlexAlign::CENTER;
    double width_ = -1.0;
    double height_ = -1.0;
    int32_t columnCount_ = 1;
    int32_t rowCount_ = 1;

    std::string columnsArgs_;
    std::string rowsArgs_;
    double columnGap_ = 0.0;
    double rowGap_ = 0.0;
    bool rightToLeft_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_GRID_LAYOUT_COMPONENT_H
