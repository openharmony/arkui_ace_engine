/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/bind_sheet_utils.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"
#include "core/interfaces/native/implementation/tabs_controller_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr int32_t INVALID_ID = -1;
struct ScrollInfo {
    bool isTouching = false;
    bool isScrolling = false;
    bool isAtTop = false;
    bool isAtBottom = false;
    std::optional<WeakPtr<ScrollControllerBase>> parentScroller;
};
using ScrollInfoMap = std::map<WeakPtr<ScrollControllerBase>, ScrollInfo>;
using BindInfoMap = std::map<WeakPtr<TabsControllerNG>, ScrollInfoMap>;
BindInfoMap bindInfoMap_;

constexpr int32_t SHOW_TAB_BAR_DELAY = 2000;
constexpr float SCROLL_RATIO = 2.0f;

void HandleOnTouchEvent(WeakPtr<ScrollControllerBase> scroller, const TouchEventInfo& info)
{
    auto touches = info.GetTouches();
    if (touches.empty()) {
        return;
    }
    auto touchType = touches.front().GetTouchType();
    if (touchType != TouchType::DOWN && touchType != TouchType::UP && touchType != TouchType::CANCEL) {
        return;
    }

    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(scroller);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        scrollInfo.isTouching = touchType == TouchType::DOWN;
        auto tabsController = bindInfo.first.Upgrade();
        if (!tabsController) {
            continue;
        }
        if (touchType == TouchType::DOWN) {
            if (!scrollInfo.isAtTop && !scrollInfo.isAtBottom && tabsController) {
                tabsController->CancelShowTabBar();
            }
        } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
            if (!scrollInfo.isScrolling && tabsController) {
                tabsController->StartShowTabBar(SHOW_TAB_BAR_DELAY);
            }
        }
    }
}

void HandleOnReachEvent(WeakPtr<ScrollControllerBase> scroller, bool isTopEvent)
{
    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(scroller);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        if (isTopEvent) {
            scrollInfo.isAtTop = true;
        } else {
            scrollInfo.isAtBottom = true;
        }
    }
}

void HandleOnScrollStartEvent(WeakPtr<ScrollControllerBase> scroller)
{
    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(scroller);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        scrollInfo.isScrolling = true;
        auto tabsController = bindInfo.first.Upgrade();
        if (!tabsController) {
            continue;
        }
        if (!scrollInfo.isAtTop && !scrollInfo.isAtBottom && !scrollInfo.isTouching && tabsController) {
            tabsController->CancelShowTabBar();
        }
    }
}

void HandleOnScrollStopEvent(WeakPtr<ScrollControllerBase> scroller)
{
    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(scroller);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        scrollInfo.isScrolling = false;
        auto tabsController = bindInfo.first.Upgrade();
        if (!tabsController) {
            continue;
        }
        if (!scrollInfo.parentScroller.has_value() && !scrollInfo.isTouching && tabsController) {
            // start show tab bar when parent scrollable component stop scroll.
            tabsController->StartShowTabBar(SHOW_TAB_BAR_DELAY);
        }
    }
}

void HandleOnDidScrollEvent(
    WeakPtr<ScrollControllerBase> scroller, Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom)
{
    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(scroller);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        if ((scrollInfo.isAtTop && isAtTop) || (scrollInfo.isAtBottom && isAtBottom)) {
            continue;
        }
        auto tabsController = bindInfo.first.Upgrade();
        if (!tabsController) {
            scrollInfo.isAtTop = isAtTop;
            scrollInfo.isAtBottom = isAtBottom;
            return;
        }
        auto offset = dimension.ConvertToPx() / SCROLL_RATIO;
        if (NonPositive(offset) || !(source == ScrollSource::SCROLLER || source == ScrollSource::SCROLLER_ANIMATION)) {
            tabsController->UpdateTabBarHiddenOffset(offset);
        }

        auto isChildReachTop = !scrollInfo.isAtTop && isAtTop;
        auto isChildReachBottom = !scrollInfo.isAtBottom && isAtBottom;
        auto isParentAtTop = true;
        auto isParentAtBottom = true;
        if (scrollInfo.parentScroller.has_value()) {
            auto iter = scrollInfoMap.find(scrollInfo.parentScroller.value());
            isParentAtTop = iter == scrollInfoMap.end() || iter->second.isAtTop;
            isParentAtBottom = iter == scrollInfoMap.end() || iter->second.isAtBottom;
        }
        if ((isChildReachTop && isParentAtTop) || (isChildReachBottom && isParentAtBottom)) {
            tabsController->StartShowTabBar();
        }
        scrollInfo.isAtTop = isAtTop;
        scrollInfo.isAtBottom = isAtBottom;
    }
}

ScrollerObserver CreateObserver(WeakPtr<ScrollControllerBase> scroller)
{
    ScrollerObserver observer;

    auto touchEvent = [scroller](const TouchEventInfo& info) { HandleOnTouchEvent(scroller, info); };
    observer.onTouchEvent = AceType::MakeRefPtr<NG::TouchEventImpl>(std::move(touchEvent));

    auto reachStartEvent = [scroller]() { HandleOnReachEvent(scroller, true); };
    observer.onReachStartEvent = std::move(reachStartEvent);

    auto reachEndEvent = [scroller]() { HandleOnReachEvent(scroller, false); };
    observer.onReachEndEvent = std::move(reachEndEvent);

    auto scrollStartEvent = [scroller]() { HandleOnScrollStartEvent(scroller); };
    observer.onScrollStartEvent = std::move(scrollStartEvent);

    auto scrollStopEvent = [scroller]() { HandleOnScrollStopEvent(scroller); };
    observer.onScrollStopEvent = std::move(scrollStopEvent);

    auto didScrollEvent = [scroller](Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom) {
        HandleOnDidScrollEvent(scroller, dimension, source, isAtTop, isAtBottom);
    };
    observer.onDidScrollEvent = std::move(didScrollEvent);

    return observer;
}

void HandleOnChangeEvent(WeakPtr<TabsControllerNG> tabsControllerWeak, int32_t index)
{
    auto bindInfoIter = bindInfoMap_.find(tabsControllerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    for (const auto& scrollInfo : bindInfoIter->second) {
        auto scroller = scrollInfo.first.Upgrade();
        if (scroller) {
            scroller->StopAnimate();
        }
    }
    auto tabsController = tabsControllerWeak.Upgrade();
    CHECK_NULL_VOID(tabsController);
    tabsController->StartShowTabBar();
}

void HandleBindTabsToScrollable(Ark_TabsController arkTabsController, Ark_Scroller arkScroller,
    const std::optional<Ark_Scroller>& parentScrollerVal)
{
    auto* tabsControllerPeer = reinterpret_cast<TabsControllerPeer*>(arkTabsController);
    CHECK_NULL_VOID(tabsControllerPeer);

    TabsControllerPeerImpl* tabsControllerPeerImpl = static_cast<TabsControllerPeerImpl*>(tabsControllerPeer);
    CHECK_NULL_VOID(tabsControllerPeerImpl);

    auto tabsControllerWeak = tabsControllerPeerImpl->GetControllerWeakPtr();

    auto* scrollerPeer = reinterpret_cast<ScrollerPeer*>(arkScroller);
    CHECK_NULL_VOID(scrollerPeer);
    auto* scrollerImpl = static_cast<ScrollerPeerImpl*>(scrollerPeer);
    auto scrollerWeak = scrollerImpl->GetController();
    auto scroller = scrollerWeak.Upgrade();
    CHECK_NULL_VOID(scroller);

    ScrollInfoMap scrollInfoMap;
    auto bindInfoIter = bindInfoMap_.find(tabsControllerWeak);
    if (bindInfoIter != bindInfoMap_.end()) {
        scrollInfoMap = bindInfoIter->second;
        if (scrollInfoMap.find(scrollerWeak) != scrollInfoMap.end()) {
            return;
        }
    }
    tabsControllerPeerImpl->SetOnChangeImpl(
        [tabsControllerWeak](int32_t index) { HandleOnChangeEvent(tabsControllerWeak, index); });
    auto observer = CreateObserver(scrollerWeak);
    scrollerImpl->SetObserver(observer);
    ScrollInfo scrollInfo;
    if (parentScrollerVal.has_value()) {
        auto* parentScrollerPeer = reinterpret_cast<ScrollerPeer*>(parentScrollerVal.value());
        CHECK_NULL_VOID(scrollerPeer);
        auto* parentScrollerImpl = static_cast<ScrollerPeerImpl*>(parentScrollerPeer);
        auto parentScrollerWeak = parentScrollerImpl->GetController();
        auto parentScroller = parentScrollerWeak.Upgrade();
        if (parentScroller) {
            scrollInfo.parentScroller = parentScroller;
        }
    }
    scrollInfoMap[scrollerWeak] = scrollInfo;
    bindInfoMap_[tabsControllerWeak] = scrollInfoMap;
}

void HandleUnbindTabsFromScrollable(Ark_TabsController arkTabsController, Ark_Scroller arkScroller,
    const std::optional<Ark_Scroller>& parentScrollerVal)
{
    auto* tabsControllerPeer = reinterpret_cast<TabsControllerPeer*>(arkTabsController);
    CHECK_NULL_VOID(tabsControllerPeer);
    TabsControllerPeerImpl* tabsControllerPeerImpl = static_cast<TabsControllerPeerImpl*>(tabsControllerPeer);
    CHECK_NULL_VOID(tabsControllerPeerImpl);
    auto tabsControllerWeak = tabsControllerPeerImpl->GetControllerWeakPtr();
    auto controller = tabsControllerWeak.Upgrade();
    auto* scrollerPeer = reinterpret_cast<ScrollerPeer*>(arkScroller);
    CHECK_NULL_VOID(scrollerPeer);
    auto* scrollerImpl = static_cast<ScrollerPeerImpl*>(scrollerPeer);
    auto scrollerWeak = scrollerImpl->GetController();
    auto bindInfoIter = bindInfoMap_.find(tabsControllerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    auto& scrollInfoMap = bindInfoIter->second;
    if (scrollInfoMap.find(scrollerWeak) != scrollInfoMap.end()) {
        scrollInfoMap.erase(scrollerWeak);
        if (scrollInfoMap.empty()) {
            bindInfoMap_.erase(tabsControllerWeak);
        }
        if (controller) {
            controller->StartShowTabBar();
        }
    }
    if (!parentScrollerVal.has_value()) {
        return;
    }
    auto* parentScrollerPeer = reinterpret_cast<ScrollerPeer*>(parentScrollerVal.value());
    CHECK_NULL_VOID(parentScrollerPeer);
    auto* parentScrollerImpl = static_cast<ScrollerPeerImpl*>(parentScrollerPeer);
    auto parentScrollerWeak = parentScrollerImpl->GetController();
    bool needRemoveParent = true;
    for (const auto& scrollInfo : scrollInfoMap) {
        if (scrollInfo.second.parentScroller.has_value() &&
            scrollInfo.second.parentScroller.value() == parentScrollerWeak.Upgrade()) {
            needRemoveParent = false;
        }
    }
    if (needRemoveParent) {
        return;
    }
    scrollInfoMap.erase(parentScrollerWeak);
    if (scrollInfoMap.empty()) {
        bindInfoMap_.erase(tabsControllerWeak);
    }
    if (controller) {
        controller->StartShowTabBar();
    }
}

std::optional<std::string> ConvertString(const Ark_Union_Number_String& src)
{
    std::optional<std::string> value;
    auto selector = src.selector;
    if (selector == 1) {
        value = OHOS::Ace::NG::Converter::OptConvert<std::string>(src.value1);
    }
    return value;
}
std::optional<int32_t> ConvertNumber(const Ark_Union_Number_String& src)
{
    std::optional<int32_t> value;
    auto selector = src.selector;
    if (selector == 0) {
        value = OHOS::Ace::NG::Converter::OptConvert<int32_t>(src.value0);
    }
    return value;
}
} // namespace
namespace IUIContextAccessor {
void FreezeUINode0Impl(const Ark_String* id, Ark_Boolean isFrozen)
{
    CHECK_NULL_VOID(id);
    ViewAbstract::FreezeUINodeById(Converter::Convert<std::string>(*id), Converter::Convert<bool>(isFrozen));
}
void FreezeUINode1Impl(Ark_Int32 id, Ark_Boolean isFrozen)
{
    ViewAbstract::FreezeUINodeByUniqueId(static_cast<int32_t>(id), Converter::Convert<bool>(isFrozen));
}
Ark_Boolean DispatchKeyEventImpl(const Ark_Union_Number_String* node, Ark_KeyEvent event)
{
    auto result = false;
    RefPtr<NG::FrameNode> frameNode = nullptr;
    auto convId = ConvertString(*node);
    if (convId) {
        frameNode = NG::Inspector::GetFrameNodeByKey(*convId);
    } else {
        auto numberId = ConvertNumber(*node);
        if (numberId) {
            auto node = ElementRegister::GetInstance()->GetNodeById(*numberId);
            frameNode = AceType::DynamicCast<NG::FrameNode>(node);
        }
    }
    CHECK_NULL_RETURN(frameNode, Converter::ArkValue<Ark_Boolean>(result));
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, Converter::ArkValue<Ark_Boolean>(result));

    CHECK_NULL_RETURN(event, Converter::ArkValue<Ark_Boolean>(result));
    const auto info = event->GetEventInfo();
    CHECK_NULL_RETURN(info, Converter::ArkValue<Ark_Boolean>(result));
    KeyEvent keyEvent;
    info->ParseKeyEvent(keyEvent);
    result = focusHub->HandleEvent(keyEvent);
    return Converter::ArkValue<Ark_Boolean>(result);
}
void OpenBindSheetImpl(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker, Ark_NativePointer bindSheetContent,
    const Opt_SheetOptions* sheetOptions, const Opt_Int32* targetId,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    FrameNodePeer* sheetContentNode = bindSheetContent ? reinterpret_cast<FrameNodePeer*>(bindSheetContent) : nullptr;
    RefPtr<NG::FrameNode> sheetContentRefptr = FrameNodePeer::GetFrameNodeByPeer(sheetContentNode);
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showInPage = false;
    BindSheetUtil::SheetCallbacks cbs;
    auto options = Converter::OptConvertPtr<Ark_SheetOptions>(sheetOptions);
    if (options) {
        BindSheetUtil::ParseLifecycleCallbacks(cbs, options.value());
        BindSheetUtil::ParseFunctionalCallbacks(cbs, options.value());
        Converter::VisitUnion(
            options->title,
            [&sheetStyle](const Ark_SheetTitleOptions& value) {
                sheetStyle.isTitleBuilder = false;
                sheetStyle.sheetTitle = Converter::OptConvert<std::string>(value.title);
                sheetStyle.sheetSubtitle = Converter::OptConvert<std::string>(value.subtitle);
            },
            [&sheetStyle, bindSheetContent, &cbs](const CustomNodeBuilder& value) {
                sheetStyle.isTitleBuilder = true;
                cbs.titleBuilder = [callback = CallbackHelper(value), bindSheetContent]() {
                    auto uiNode = callback.BuildSync(bindSheetContent);
                    ViewStackProcessor::GetInstance()->Push(uiNode);
                };
            },
            []() {});
        BindSheetUtil::ParseSheetParams(sheetStyle, options.value());
    }

    int32_t id = Converter::OptConvert<int32_t>(targetId->value).value_or(INVALID_ID);

    ViewContextModel::GetInstance()->OpenBindSheet(sheetContentRefptr, std::move(cbs.titleBuilder), sheetStyle,
        std::move(cbs.onAppear), std::move(cbs.onDisappear), std::move(cbs.shouldDismiss), std::move(cbs.onWillDismiss),
        std::move(cbs.onWillAppear), std::move(cbs.onWillDisappear), std::move(cbs.onHeightDidChange),
        std::move(cbs.onDetentsDidChange), std::move(cbs.onWidthDidChange), std::move(cbs.onTypeDidChange),
        std::move(cbs.sheetSpringBack), Container::CurrentId(), id);
}
void UpdateBindSheetImpl(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker, Ark_NativePointer bindSheetContent,
    const Ark_SheetOptions* sheetOptions, const Opt_Boolean* partialUpdate,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    FrameNodePeer* sheetContentNode = bindSheetContent ? reinterpret_cast<FrameNodePeer*>(bindSheetContent) : nullptr;
    RefPtr<NG::FrameNode> sheetContentRefptr = FrameNodePeer::GetFrameNodeByPeer(sheetContentNode);

    auto partialUpdateVal = Converter::OptConvertPtr<bool>(partialUpdate).value_or(false);

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showInPage = false;
    auto options = Converter::OptConvertPtr<Ark_SheetOptions>(sheetOptions);
    BindSheetUtil::SheetCallbacks cbs;
    if (options) {
        BindSheetUtil::ParseLifecycleCallbacks(cbs, options.value());
        BindSheetUtil::ParseFunctionalCallbacks(cbs, options.value());
        Converter::VisitUnion(
            options->title,
            [&sheetStyle](const Ark_SheetTitleOptions& value) {
                sheetStyle.isTitleBuilder = false;
                sheetStyle.sheetTitle = Converter::OptConvert<std::string>(value.title);
                sheetStyle.sheetSubtitle = Converter::OptConvert<std::string>(value.subtitle);
            },
            [&sheetStyle, bindSheetContent, &cbs](const CustomNodeBuilder& value) {
                sheetStyle.isTitleBuilder = true;
                cbs.titleBuilder = [callback = CallbackHelper(value), bindSheetContent]() {
                    auto uiNode = callback.BuildSync(bindSheetContent);
                    ViewStackProcessor::GetInstance()->Push(uiNode);
                };
            },
            []() {});
        BindSheetUtil::ParseSheetParams(sheetStyle, options.value());
        BindSheetUtil::ModifySheetStyle(sheetContentRefptr, sheetStyle, partialUpdateVal);
    }

    auto ret = ViewContextModel::GetInstance()->UpdateBindSheet(
        sheetContentRefptr, sheetStyle, partialUpdateVal, Container::CurrentId());
}
void CloseBindSheetImpl(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker, Ark_NativePointer bindSheetContent,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    FrameNodePeer* sheetContentNode = bindSheetContent ? reinterpret_cast<FrameNodePeer*>(bindSheetContent) : nullptr;
    RefPtr<NG::FrameNode> sheetContentRefptr = FrameNodePeer::GetFrameNodeByPeer(sheetContentNode);
    auto ret = ViewContextModel::GetInstance()->CloseBindSheet(sheetContentRefptr, Container::CurrentId());
}
void BindTabsToScrollableImpl(Ark_TabsController tabsController, Ark_Scroller scroller)
{
    HandleBindTabsToScrollable(tabsController, scroller, std::nullopt);
}
void UnbindTabsFromScrollableImpl(Ark_TabsController tabsController, Ark_Scroller scroller)
{
    HandleUnbindTabsFromScrollable(tabsController, scroller, std::nullopt);
}
void BindTabsToNestedScrollableImpl(
    Ark_TabsController tabsController, Ark_Scroller parentScroller, Ark_Scroller scrollerchildScroller)
{
    HandleBindTabsToScrollable(tabsController, parentScroller, std::nullopt);
    HandleBindTabsToScrollable(tabsController, scrollerchildScroller, parentScroller);
}
void UnbindTabsFromNestedScrollableImpl(
    Ark_TabsController tabsController, Ark_Scroller parentScroller, Ark_Scroller childScroller)
{
    HandleUnbindTabsFromScrollable(tabsController, childScroller, parentScroller);
}
} // namespace IUIContextAccessor
const GENERATED_ArkUIIUIContextAccessor* GetIUIContextAccessor()
{
    static const GENERATED_ArkUIIUIContextAccessor IUIContextAccessorImpl {
        IUIContextAccessor::FreezeUINode0Impl,
        IUIContextAccessor::FreezeUINode1Impl,
        IUIContextAccessor::DispatchKeyEventImpl,
        IUIContextAccessor::OpenBindSheetImpl,
        IUIContextAccessor::UpdateBindSheetImpl,
        IUIContextAccessor::CloseBindSheetImpl,
        IUIContextAccessor::BindTabsToScrollableImpl,
        IUIContextAccessor::UnbindTabsFromScrollableImpl,
        IUIContextAccessor::BindTabsToNestedScrollableImpl,
        IUIContextAccessor::UnbindTabsFromNestedScrollableImpl,
    };
    return &IUIContextAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
