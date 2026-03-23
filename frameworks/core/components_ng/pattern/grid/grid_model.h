/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_MODEL_H

#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/grid/grid_constants.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"
#include "core/components_ng/pattern/grid/grid_properties.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace {
class ResourceObject;
class ScrollControllerBase;
class ScrollProxy;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
struct EditModeOptions;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

class ACE_FORCE_EXPORT GridModel {
public:
    static GridModel* GetInstance();
    virtual ~GridModel() = default;

    virtual void Create(
        const RefPtr<ScrollControllerBase>& positionController, const RefPtr<ScrollProxy>& scrollBarProxy) = 0;
    virtual void Pop() = 0;
    virtual void SetLayoutOptions(GridLayoutOptions options) = 0;
    virtual void SetColumnsTemplate(const std::string& value) = 0;
    virtual void SetItemFillPolicy(PresetFillType policy) {};
    virtual void SetRowsTemplate(const std::string& value) = 0;
    virtual void SetColumnsGap(const Dimension& value) = 0;
    virtual void SetRowsGap(const Dimension& value) = 0;
    virtual void SetGridHeight(const Dimension& value) = 0;
    virtual void SetScrollBarMode(DisplayMode value) = 0;
    virtual void SetScrollBarColor(const std::string& value) = 0;
    virtual void SetScrollBarColor(const std::optional<Color>& scrollBarColor) {};
    virtual void SetScrollBarWidth(const std::string& value) = 0;
    virtual void SetCachedCount(int32_t value, bool show = false) = 0;
    virtual void SetIsRTL(TextDirection direction) = 0;
    virtual void SetLayoutDirection(FlexDirection value) = 0;
    virtual void SetMaxCount(int32_t value) = 0;
    virtual void SetMinCount(int32_t value) = 0;
    virtual void SetCellLength(int32_t value) = 0;
    virtual void SetEditable(bool value) = 0;
    virtual void SetMultiSelectable(bool value) = 0;
    virtual void SetSupportAnimation(bool value) = 0;
    virtual void SetSupportDragAnimation(bool value) = 0;
    virtual void SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge effectEdge = EffectEdge::ALL) = 0;
    virtual void SetNestedScroll(const NestedScrollOptions& nestedOpt) = 0;
    virtual void SetScrollEnabled(bool scrollEnabled) = 0;
    virtual void SetFriction(double friction) = 0;
    virtual void SetFocusWrapMode(const std::optional<FocusWrapMode>& focusWrapMode) {}
    virtual void SetAlignItems(GridItemAlignment itemAlign) = 0;
    virtual void SetOnScrollToIndex(OHOS::Ace::NG::ScrollToIndexFunc&& value) = 0;
    virtual void SetOnScrollBarUpdate(OHOS::Ace::NG::ScrollBarUpdateFunc&& value) = 0;
    virtual void SetOnItemDragStart(std::function<void(const ItemDragInfo&, int32_t)>&& value) = 0;
    virtual void SetOnItemDragEnter(OHOS::Ace::NG::ItemDragEnterFunc&& value) = 0;
    virtual void SetOnItemDragMove(OHOS::Ace::NG::ItemDragMoveFunc&& value) = 0;
    virtual void SetOnItemDragLeave(OHOS::Ace::NG::ItemDragLeaveFunc&& value) = 0;
    virtual void SetOnItemDrop(OHOS::Ace::NG::ItemDropFunc&& value) = 0;
    virtual RefPtr<ScrollControllerBase> CreatePositionController();
    virtual RefPtr<ScrollProxy> CreateScrollBarProxy();
    virtual void SetOnScroll(std::function<void(Dimension, ScrollState)>&& onScroll) = 0;
    virtual void SetOnScrollFrameBegin(
        std::function<ScrollFrameResult(Dimension, ScrollState)>&& onScrollFrameBegin) = 0;
    virtual void SetOnScrollStart(std::function<void()>&& onScrollStart) = 0;
    virtual void SetOnScrollStop(std::function<void()>&& onScrollStop) = 0;
    virtual void SetOnScrollIndex(std::function<void(int32_t, int32_t)>&& onScrollIndex) = 0;
    virtual void SetOnReachStart(std::function<void()>&& onReachStart) = 0;
    virtual void SetOnReachEnd(std::function<void()>&& onReachEnd) = 0;
    virtual void SetSyncLoad(bool syncLoad) {}
    virtual void SetEditModeOptions(NG::EditModeOptions& editModeOptions) {};
    virtual void CreateWithResourceObjFriction(const RefPtr<ResourceObject>& resObj) {};
    virtual void CreateWithResourceObjScrollBarColor(const RefPtr<ResourceObject>& resObj) {};
    virtual void ParseResObjRowsGap(const RefPtr<ResourceObject>& resObj) {};
    virtual void ParseResObjColumnsGap(const RefPtr<ResourceObject>& resObj) {};
    virtual void SetSupportLazyLoadingEmptyBranch(bool enable) {};

    virtual DisplayMode GetDisplayMode() const = 0;

private:
    static std::unique_ptr<GridModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_MODEL_H
