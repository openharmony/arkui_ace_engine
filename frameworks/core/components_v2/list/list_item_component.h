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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_COMPONENT_H

#include <string>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_v2/common/common_def.h"
#include "core/components_v2/list/list_properties.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace::V2 {


using DeepRenderFunc = std::function<RefPtr<Component>()>;

class ACE_EXPORT ListItemComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(V2::ListItemComponent, SoleChildComponent);

public:
    ListItemComponent() = default;
    ~ListItemComponent() override = default;

    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    ACE_DEFINE_COMPONENT_PROP(Type, std::string);
    ACE_DEFINE_COMPONENT_PROP(Sticky, StickyMode, StickyMode::NONE);
    ACE_DEFINE_COMPONENT_PROP(EditMode, uint32_t, EditMode::NONE);
    ACE_DEFINE_COMPONENT_PROP(BorderRadius, Dimension, 0.0_vp);
    ACE_DEFINE_COMPONENT_PROP(EdgeEffect, SwipeEdgeEffect, SwipeEdgeEffect::Spring);
    ACE_DEFINE_COMPONENT_PROP(StartDeleteAreaDistance, Dimension, 0.0_vp);
    ACE_DEFINE_COMPONENT_PROP(UseStartDefaultDeleteAnimation, bool, true);
    ACE_DEFINE_COMPONENT_PROP(UseEndDefaultDeleteAnimation, bool, true);
    ACE_DEFINE_COMPONENT_EVENT(OnStartDelete, void());
    ACE_DEFINE_COMPONENT_EVENT(OnEnterStartDeleteArea, void());
    ACE_DEFINE_COMPONENT_EVENT(OnExitStartDeleteArea, void());
    ACE_DEFINE_COMPONENT_PROP(EndDeleteAreaDistance, Dimension, 0.0_vp);
    ACE_DEFINE_COMPONENT_EVENT(OnEndDelete, void());
    ACE_DEFINE_COMPONENT_EVENT(OnEnterEndDeleteArea, void());
    ACE_DEFINE_COMPONENT_EVENT(OnExitEndDeleteArea, void());

    uint32_t Compare(const RefPtr<Component>& component) const override;

    bool GetSelectable() const
    {
        return selectable_;
    }

    void SetSelectable(bool selectable)
    {
        selectable_ = selectable;
    }

    void SetSwiperStartComponent(RefPtr<Component> component)
    {
        swiperStartComponent_ = component;
    }

    RefPtr<Component> GetSwiperStartComponent()
    {
        return swiperStartComponent_;
    }

    void SetSwiperEndComponent(RefPtr<Component> component)
    {
        swiperEndComponent_ = component;
    }

    RefPtr<Component> GetSwiperEndComponent()
    {
        return swiperEndComponent_;
    }

    OnSelectFunc GetOnSelectId() const
    {
        return onSelectId_;
    }

    void SetOnSelectId(const OnSelectFunc& onSelectId)
    {
        onSelectId_ = onSelectId;
    }

    // transfer ownershop of deepRenderFunc_ to provided ListItemComponent
    void MoveDeepRenderFunc(RefPtr<ListItemComponent>& component)
    {
        component->deepRenderFunc_ = std::move(deepRenderFunc_);
        ACE_DCHECK(deepRenderFunc_ == nullptr);
    }

    void SetDeepRenderFunc(const DeepRenderFunc& deepRenderFunc)
    {
        deepRenderFunc_ = deepRenderFunc;
    }

    RefPtr<Component> ExecDeepRender() const
    {
        return (deepRenderFunc_) ? deepRenderFunc_() : nullptr;
    }

    void SetIsLazyCreating(const bool isLazy)
    {
        isLazyCreating_ = isLazy;
    }

    bool GetIsLazyCreating() const
    {
        return isLazyCreating_;
    }

    bool IsDragStart() const
    {
        return isDragStart_;
    }

    void MarkIsDragStart(bool isDragStart)
    {
        isDragStart_ = isDragStart;
    }

private:
    OnSelectFunc onSelectId_;
    DeepRenderFunc deepRenderFunc_ = nullptr;
    bool isLazyCreating_ = false;
    bool selectable_ = true;
    bool isDragStart_ = false;
    RefPtr<Component> swiperStartComponent_;
    RefPtr<Component> swiperEndComponent_;
    ACE_DISALLOW_COPY_AND_MOVE(ListItemComponent);
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_COMPONENT_H
