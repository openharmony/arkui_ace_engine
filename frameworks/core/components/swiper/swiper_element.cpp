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

#include "core/components/swiper/swiper_element.h"

#include "core/components/swiper/render_swiper.h"
#include "core/components/swiper/swiper_component.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t ELEMENT_CHANGE_END_LISTENER_KEY = 1002;
constexpr int32_t INDICATOR_FOCUS_INDEX = 1;

} // namespace

void SwiperDataChangeListener::OnDataReloaded()
{
    auto swiper = element_.Upgrade();
    if (swiper) {
        swiper->OnReload();
    }
}

void SwiperDataChangeListener::OnDataAdded(size_t index)
{
    auto swiper = element_.Upgrade();
    if (swiper) {
        swiper->OnItemAdded(static_cast<int32_t>(index));
    }
}

void SwiperDataChangeListener::OnDataDeleted(size_t index)
{
    auto swiper = element_.Upgrade();
    if (swiper) {
        swiper->OnItemDeleted(static_cast<int32_t>(index));
    }
}

void SwiperDataChangeListener::OnDataChanged(size_t index)
{
    auto swiper = element_.Upgrade();
    if (swiper) {
        swiper->OnItemChanged(static_cast<int32_t>(index));
    }
}

void SwiperDataChangeListener::OnDataMoved(size_t from, size_t to)
{
    auto swiper = element_.Upgrade();
    if (swiper) {
        swiper->OnItemMoved(static_cast<int32_t>(from), static_cast<int32_t>(to));
    }
}

void SwiperElement::Update()
{
    lazyChildItems_.clear();
    lazyForEachComponent_ = nullptr;

    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(component_);
    if (!swiperComponent) {
        return;
    }
    auto lazyForEach = swiperComponent->GetLazyForEachComponent();
    if (!lazyForEach) {
        RenderElement::Update();
        return;
    }
    if (!listener_) {
        listener_ = AceType::MakeRefPtr<SwiperDataChangeListener>(AceType::WeakClaim(this));
    }
    lazyForEach->RegiterDataChangeListener(listener_);
    lazyForEachComponent_ = lazyForEach;

    auto swiper = AceType::DynamicCast<RenderSwiper>(renderNode_);
    if (!swiper) {
        return;
    }
    swiper->SetBuildChildByIndex([weak = WeakClaim(this)](int32_t index) {
        auto element = weak.Upgrade();
        if (!element) {
            return false;
        }
        return element->BuildChildByIndex(index);
    });

    swiper->SetDeleteChildByIndex([weak = WeakClaim(this)](int32_t index) {
        auto element = weak.Upgrade();
        if (!element) {
            return;
        }
        element->DeleteChildByIndex(index);
    });
    RenderElement::Update();
}

bool SwiperElement::BuildChildByIndex(int32_t index)
{
    if (index < 0) {
        return false;
    }

    if (static_cast<size_t>(index) >= lazyForEachComponent_->TotalCount()) {
        return false;
    }
    auto child = lazyForEachComponent_->GetChildByIndex(static_cast<size_t>(index));
    auto item = lazyChildItems_.find(index);
    if (item == lazyChildItems_.end()) {
        auto element = UpdateChild(nullptr, child);
        RefPtr<RenderSwiper> swiper = AceType::DynamicCast<RenderSwiper>(renderNode_);
        if (!swiper) {
            return false;
        }
        swiper->AddChildByIndex(index, element->GetRenderNode());
        lazyChildItems_[index] = element;
    } else {
        UpdateChild(item->second, child);
    }
    return true;
}

void SwiperElement::DeleteChildByIndex(int32_t index)
{
    auto item = lazyChildItems_.find(index);
    if (item == lazyChildItems_.end()) {
        return;
    }
    Element::RemoveChild(item->second);
    lazyChildItems_.erase(item);
    RefPtr<RenderSwiper> swiper = AceType::DynamicCast<RenderSwiper>(renderNode_);
    if (!swiper) {
        return;
    }
    swiper->RemoveChildByIndex(index);
}

void SwiperElement::PerformBuild()
{
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(component_);
    if (!swiperComponent) {
        LOGE("get swiper component failed!");
        return;
    }
    axis_ = swiperComponent->GetAxis();
    auto indicator = swiperComponent->GetIndicator();
    if (!indicator) {
        showIndicator_ = false;
    }

    if (showIndicator_ && !indicatorFocusNode_) {
        indicatorFocusNode_ = AceType::MakeRefPtr<FocusNode>();
        FocusGroup::AddChild(indicatorFocusNode_);
        registerCallBack();
    }
    ComponentGroupElement::PerformBuild();
}

void SwiperElement::registerCallBack()
{
    if (!indicatorFocusNode_) {
        return;
    }
    indicatorFocusNode_->SetOnFocusCallback([weak = WeakClaim(this)](void) {
        auto client = weak.Upgrade();
        auto weakContext = client->GetContext();
        auto context = weakContext.Upgrade();
        if (client && context) {
            client->HandleIndicatorFocus(true && context->IsKeyEvent());
        }
    });

    indicatorFocusNode_->SetOnBlurCallback([weak = WeakClaim(this)](void) {
        auto client = weak.Upgrade();
        if (client) {
            client->HandleIndicatorFocus(false);
        }
    });
}

bool SwiperElement::IsFocusable() const
{
    auto swiper = DynamicCast<RenderSwiper>(renderNode_);
    if (!swiper) {
        LOGE("get render node failed");
        return false;
    }

    if (showIndicator_) {
        return true;
    } else {
        int32_t currentIndex = swiper->GetCurrentIndex();
        auto currentFocusNode = focusNodes_.begin();
        std::advance(currentFocusNode, currentIndex);
        if (currentFocusNode == focusNodes_.end()) {
            LOGE("target focus node is null");
            return false;
        }
        return (*currentFocusNode)->IsFocusable();
    }
}

void SwiperElement::OnFocus()
{
    auto swiper = DynamicCast<RenderSwiper>(renderNode_);
    if (!swiper) {
        LOGE("get render node failed");
        itLastFocusNode_ = focusNodes_.end();
        return;
    }
    swiper->OnStatusChanged(RenderStatus::FOCUS);

    if (showIndicator_) {
        auto currentFocusNode = focusNodes_.begin();
        if ((*currentFocusNode)->RequestFocusImmediately()) {
            itLastFocusNode_ = currentFocusNode;
            indicatorFocusNode_ = *itLastFocusNode_;
        }
    } else {
        int32_t currentIndex = swiper->GetCurrentIndex();
        auto currentFocusNode = focusNodes_.begin();
        std::advance(currentFocusNode, currentIndex);
        if (currentFocusNode != focusNodes_.end()) {
            if ((*currentFocusNode)->RequestFocusImmediately()) {
                itLastFocusNode_ = currentFocusNode;
                swiper->OnFocus();
            } else {
                // Not found any focusable node, clear focus.
                itLastFocusNode_ = focusNodes_.end();
            }
        }
    }
    swiper->RegisterChangeEndListener(ELEMENT_CHANGE_END_LISTENER_KEY, [weak = WeakClaim(this)](int32_t index) {
        auto client = weak.Upgrade();
        if (client) {
            client->RequestChildFocus(index);
        }
    });
}

void SwiperElement::RequestChildFocus(int32_t index)
{
    auto currentFocusNode = focusNodes_.begin();
    if (showIndicator_) {
        std::advance(currentFocusNode, index + INDICATOR_FOCUS_INDEX);
    } else {
        std::advance(currentFocusNode, index);
    }
    if (currentFocusNode != focusNodes_.end()) {
        if ((*currentFocusNode)->RequestFocusImmediately()) {
            itLastFocusNode_ = currentFocusNode;
        }
    }
}

void SwiperElement::OnBlur()
{
    FocusGroup::OnBlur();
    auto swiper = DynamicCast<RenderSwiper>(renderNode_);
    if (swiper) {
        swiper->OnBlur();
        swiper->UnRegisterChangeEndListener(ELEMENT_CHANGE_END_LISTENER_KEY);
        swiper->OnStatusChanged(RenderStatus::BLUR);
    }
}

void SwiperElement::HandleIndicatorFocus(bool isFocus)
{
    auto swiper = DynamicCast<RenderSwiper>(renderNode_);
    if (!swiper) {
        LOGE("get swiper render node failed");
        return;
    }
    swiper->IndicatorShowFocus(isFocus);
}

bool SwiperElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    auto swiper = DynamicCast<RenderSwiper>(renderNode_);
    if (!swiper) {
        return false;
    }
    if (showIndicator_ && (*itLastFocusNode_ == indicatorFocusNode_)) {
        if ((axis_ == Axis::HORIZONTAL && vertical) || (axis_ != Axis::HORIZONTAL && !vertical)) {
            if (reverse) {
                return RequestCurrentItemFocus();
            }
        } else {
            swiper->UpdateIndicatorFocus(true, reverse);
            return true;
        }
    } else {
        if (showIndicator_) {
            if ((axis_ == Axis::HORIZONTAL && vertical) || (axis_ != Axis::HORIZONTAL && !vertical)) {
                if (!reverse) {
                    return RequestIndicatorFocus();
                }
            }
        } else {
            return false;
        }
    }
    return false;
}

bool SwiperElement::RequestIndicatorFocus()
{
    auto swiper = DynamicCast<RenderSwiper>(renderNode_);
    if (!swiper) {
        return false;
    }
    auto currentFocusNode = focusNodes_.begin();
    if ((*currentFocusNode)->RequestFocusImmediately()) {
        itLastFocusNode_ = currentFocusNode;
        indicatorFocusNode_ = *itLastFocusNode_;
        swiper->IndicatorShowFocus(true);
        return true;
    }
    return false;
}

bool SwiperElement::RequestCurrentItemFocus()
{
    auto swiper = DynamicCast<RenderSwiper>(renderNode_);
    if (!swiper) {
        LOGE("get swiper render node failed");
        return false;
    }
    int32_t currentIndex = swiper->GetCurrentIndex();
    auto currentFocusNode = focusNodes_.begin();
    if (showIndicator_) {
        std::advance(currentFocusNode, currentIndex + INDICATOR_FOCUS_INDEX);
    } else {
        std::advance(currentFocusNode, currentIndex);
    }
    if (currentFocusNode != focusNodes_.end()) {
        if ((*currentFocusNode)->RequestFocusImmediately()) {
            itLastFocusNode_ = currentFocusNode;
            swiper->IndicatorShowFocus(false);
            return true;
        }
    }
    return false;
}

bool SwiperElement::OnKeyEvent(const KeyEvent& keyEvent)
{
    if (!IsCurrentFocus()) {
        return false;
    }

    if (itLastFocusNode_ != focusNodes_.end() && (*itLastFocusNode_)->HandleKeyEvent(keyEvent)) {
        return true;
    }

    if (FocusNode::OnKeyEvent(keyEvent)) {
        return true;
    }

    if (keyEvent.action != KeyAction::UP) {
        return false;
    }

    switch (keyEvent.code) {
        case KeyCode::TV_CONTROL_UP:
            return RequestNextFocus(true, true, GetRect());
        case KeyCode::TV_CONTROL_DOWN:
            return RequestNextFocus(true, false, GetRect());
        case KeyCode::TV_CONTROL_LEFT:
            return RequestNextFocus(false, true, GetRect());
        case KeyCode::TV_CONTROL_RIGHT:
            return RequestNextFocus(false, false, GetRect());
        case KeyCode::KEYBOARD_TAB:
            return RequestNextFocus(false, false, GetRect()) || RequestNextFocus(true, false, GetRect());
        default:
            return false;
    }
}

void SwiperElement::OnReload()
{
    LOGD("SwiperElement::OnReload");
    RefPtr<RenderSwiper> render = AceType::DynamicCast<RenderSwiper>(renderNode_);
    if (!render) {
        return;
    }

    children_.clear();
    lazyChildItems_.clear();
    render->OnReload();
}

void SwiperElement::OnItemAdded(int32_t index)
{
    LOGD("SwiperElement::OnItemAdded");
    auto item = lazyChildItems_.find(index);
    if (item == lazyChildItems_.end()) {
        return;
    }
    decltype(lazyChildItems_) items(std::move(lazyChildItems_));
    for (const auto& item : items) {
        if (item.first >= index) {
            lazyChildItems_.emplace(std::make_pair(item.first + 1, item.second));
        } else {
            lazyChildItems_.emplace(std::make_pair(item.first, item.second));
        }
    }
    RefPtr<RenderSwiper> render = AceType::DynamicCast<RenderSwiper>(renderNode_);
    if (!render) {
        return;
    }
    render->OnItemAdded(index);
}

void SwiperElement::OnItemDeleted(int32_t index)
{
    LOGD("SwiperElement::OnItemDeleted");
    auto item = lazyChildItems_.find(index);
    if (item == lazyChildItems_.end()) {
        return;
    }
    decltype(lazyChildItems_) items(std::move(lazyChildItems_));
    for (const auto& item : items) {
        if (item.first == index) {
            UpdateChild(item.second, nullptr);
        } else if (item.first > index) {
            lazyChildItems_.emplace(std::make_pair(item.first - 1, item.second));
        } else {
            lazyChildItems_.emplace(std::make_pair(item.first, item.second));
        }
    }
    RefPtr<RenderSwiper> render = AceType::DynamicCast<RenderSwiper>(renderNode_);
    if (!render) {
        return;
    }
    render->OnItemDeleted(index);
}

void SwiperElement::OnItemChanged(int32_t index)
{
    LOGD("SwiperElement::OnItemChanged");
    if (static_cast<size_t>(index) >= lazyForEachComponent_->TotalCount()) {
        return;
    }
    RefPtr<RenderSwiper> render = AceType::DynamicCast<RenderSwiper>(renderNode_);
    if (!render) {
        return;
    }
    auto item = lazyChildItems_.find(index);
    if (item == lazyChildItems_.end()) {
        return;
    }
    auto element = UpdateChild(item->second, lazyForEachComponent_->GetChildByIndex(static_cast<size_t>(index)));
    render->AddChildByIndex(index, element->GetRenderNode());
    render->OnItemChanged(index);
}

void SwiperElement::OnItemMoved(int32_t from, int32_t to)
{
    LOGD("SwiperElement::OnItemMoved");
    RefPtr<RenderSwiper> render = AceType::DynamicCast<RenderSwiper>(renderNode_);
    if (!render) {
        return;
    }
    render->OnItemMoved(from, to);
}

} // namespace OHOS::Ace
