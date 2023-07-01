/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_MODEL_NG_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridModelNG : public OHOS::Ace::GridModel {
public:
    void Create(
        const RefPtr<ScrollControllerBase>& positionController, const RefPtr<ScrollProxy>& scrollProxy) override;
    void Pop() override;
    void SetColumnsTemplate(const std::string& value) override;
    void SetRowsTemplate(const std::string& value) override;
    void SetColumnsGap(const Dimension& value) override;
    void SetRowsGap(const Dimension& value) override;
    void SetGridHeight(const Dimension& value) override;
    void SetScrollBarMode(int32_t value) override;
    void SetScrollBarColor(const std::string& value) override;
    void SetScrollBarWidth(const std::string& value) override;
    void SetCachedCount(int32_t value) override;
    void SetIsRTL(bool rightToLeft) override;
    void SetLayoutDirection(FlexDirection value) override;
    void SetMaxCount(int32_t value) override;
    void SetMinCount(int32_t value) override;
    void SetCellLength(int32_t value) override;
    void SetEditable(bool value) override;
    void SetMultiSelectable(bool value) override;
    void SetSupportAnimation(bool value) override;
    void SetSupportDragAnimation(bool value) override;
    void SetEdgeEffect(EdgeEffect edgeEffect) override;
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override;
    void SetScrollEnabled(bool scrollEnabled) override;
    void SetFriction(double friction) override;
    void SetOnScrollToIndex(ScrollToIndexFunc&& value) override;
    void SetOnScrollBarUpdate(ScrollBarUpdateFunc&& value) override;
    void SetOnItemDragStart(std::function<void(const ItemDragInfo&, int32_t)>&& value) override;
    void SetOnItemDragEnter(ItemDragEnterFunc&& value) override;
    void SetOnItemDragMove(ItemDragMoveFunc&& value) override;
    void SetOnItemDragLeave(ItemDragLeaveFunc&& value) override;
    void SetOnItemDrop(ItemDropFunc&& value) override;
    RefPtr<ScrollControllerBase> CreatePositionController() override;
    RefPtr<ScrollProxy> CreateScrollBarProxy() override;

private:
    void AddDragFrameNodeToManager() const;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_MODEL_NG_H
