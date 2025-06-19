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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_MODEL_H

#include <functional>
#include <memory>
#include <mutex>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT ListItemModel {
public:
    static ListItemModel* GetInstance();
    virtual ~ListItemModel() = default;

    virtual void Create(bool isCreateArc = false) = 0;
    virtual void Create(
        std::function<void(int32_t)>&& deepRenderFunc, V2::ListItemStyle listItemStyle, bool isCreateArc = false) = 0;
    virtual void OnDidPop();
    virtual void SetBorderRadius(const Dimension& borderRadius) = 0;
    virtual void SetType(const std::string& type) = 0;
    virtual void SetIsLazyCreating(bool isLazy) = 0;
    virtual void SetSticky(V2::StickyMode stickyMode) = 0;
    virtual void SetEditMode(uint32_t editMode) = 0;
    virtual void SetSelectable(bool selectable) = 0;
    virtual void SetSelected(bool selected) = 0;
    virtual void SetSelectChangeEvent(std::function<void(bool)>&& changeEvent) = 0;
    // use SetDeleteArea to update builder function
    virtual void SetSwiperAction(std::function<void()>&& startAction, std::function<void()>&& endAction,
        OnOffsetChangeFunc&& onOffsetChangeFunc, V2::SwipeEdgeEffect edgeEffect,
        NG::FrameNode* node = nullptr) = 0;
    virtual void SetSelectCallback(OnSelectFunc&& selectCallback) = 0;
    virtual void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) = 0;
    virtual void SetDeleteArea(std::function<void()>&& builderAction, OnDeleteEvent&& onDelete,
        OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
        OnStateChangedEvent&& onStateChange, const Dimension& length, bool isStartArea,
        NG::FrameNode* node = nullptr) = 0;
    virtual void SetDeleteAreaWithFrameNode(const RefPtr<NG::UINode>& builderComponent, OnDeleteEvent&& onDelete,
        OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
        OnStateChangedEvent&& onStateChange, const Dimension& length, bool isStartArea,
        NG::FrameNode* node) = 0;
    virtual void SetAutoScale(bool autoScale) {}
    virtual void ParseResObjStartArea(const RefPtr<ResourceObject>& resObj) {};
    virtual void ParseResObjEndArea(const RefPtr<ResourceObject>& resObj) {};

private:
    static std::unique_ptr<ListItemModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_MODEL_H
