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

#include "core/components_ng/base/view_abstract_model_ng.h"

#include <utility>

#include "base/memory/ace_type.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LONG_PRESS_DURATION = 280;

void CreateCustomMenu(std::function<void()>& buildFunc, const RefPtr<NG::FrameNode>& targetNode, bool isContextMenu,
    const NG::OffsetF& offset, const MenuParam& menuParam = MenuParam())
{
    NG::ScopedViewStackProcessor builderViewStackProcessor;
    buildFunc();
    auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    NG::ViewAbstract::BindMenuWithCustomNode(customNode, targetNode, isContextMenu, offset, menuParam);
}
} // namespace

void ViewAbstractModelNG::BindMenu(
    std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
#ifdef ENABLE_DRAG_FRAMEWORK
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true);
#endif // ENABLE_DRAG_FRAMEWORK
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    RegisterMenuAppearCallback(params, std::move(buildFunc), menuParam);

    GestureEventFunc showMenu;
    auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
    if (!params.empty()) {
        showMenu = [params, weakTarget, menuParam](GestureEvent& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            // menu already created
            if (params.empty()) {
                NG::ViewAbstract::ShowMenu(targetNode->GetId(), menuPosition);
                return;
            }
            NG::ViewAbstract::BindMenuWithItems(std::move(params), targetNode, menuPosition, menuParam);
            params.clear();
        };
    } else if (buildFunc) {
        showMenu = [builderFunc = std::move(buildFunc), weakTarget, menuParam](const GestureEvent& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            CreateCustomMenu(builderFunc, targetNode, false, menuPosition, menuParam);
        };
    } else {
        LOGE("empty param or null builder");
        return;
    }
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    gestureHub->BindMenu(std::move(showMenu));

    RegisterMenuDisappearCallback(std::move(buildFunc), menuParam);

    // delete menu when target node destroy
    auto destructor = [id = targetNode->GetId()]() {
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteMenu(id);
    };
    targetNode->PushDestroyCallback(destructor);
}

void ViewAbstractModelNG::BindContextMenu(
    ResponseType type, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);

    RegisterContextMenuAppearCallback(type, menuParam);

    auto hub = targetNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
    if (type == ResponseType::RIGHT_CLICK) {
        OnMouseEventFunc event = [builder = std::move(buildFunc), weakTarget, menuParam](MouseInfo& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            auto pipelineContext = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto windowRect = pipelineContext->GetDisplayWindowRectInfo();
            menuPosition += NG::OffsetF { windowRect.Left(), windowRect.Top() };
            if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
                CreateCustomMenu(builder, targetNode, true, menuPosition, menuParam);
                info.SetStopPropagation(true);
            }
        };
        auto inputHub = targetNode->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        inputHub->BindContextMenu(std::move(event));
    } else if (type == ResponseType::LONG_PRESS) {
        // create or show menu on long press
        auto event = [builder = std::move(buildFunc), weakTarget, menuParam](const GestureEvent& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            auto pipelineContext = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto windowRect = pipelineContext->GetDisplayWindowRectInfo();
            menuPosition += NG::OffsetF { windowRect.Left(), windowRect.Top() };
            CreateCustomMenu(builder, targetNode, true, menuPosition, menuParam);
        };
        auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(event));
#ifdef ENABLE_DRAG_FRAMEWORK
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true);
#endif // ENABLE_DRAG_FRAMEWORK

        hub->SetLongPressEvent(longPress, false, true, LONG_PRESS_DURATION);
    } else {
        LOGE("The arg responseType is invalid.");
        return;
    }

    RegisterContextMenuDisappearCallback(menuParam);

    // delete menu when target node destroy
    auto destructor = [id = targetNode->GetId(), containerId = Container::CurrentId()]() {
        LOGI("BindContextMenu delete menu node from map");
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(containerId);
        CHECK_NULL_VOID(subwindow);
        auto childContainerId = subwindow->GetChildContainerId();
        auto childContainer = AceEngine::Get().GetContainer(childContainerId);
        CHECK_NULL_VOID(childContainer);
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteMenu(id);
    };
    targetNode->PushDestroyCallback(destructor);
}

void ViewAbstractModelNG::SetPivot(const Dimension& x, const Dimension& y, const Dimension& z)
{
    DimensionOffset center(x, y);
    if (!NearZero(z.Value())) {
        center.SetZ(z);
    }
    ViewAbstract::SetPivot(center);
}

void ViewAbstractModelNG::SetScale(float x, float y, float z)
{
    if (x < 0) {
        x = 1;
    }
    if (y < 0) {
        y = 1;
    }
    VectorF scale(x, y);
    ViewAbstract::SetScale(scale);
}

void ViewAbstractModelNG::BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<void()>&& buildFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    auto buildNodeFunc = [buildFunc]() -> RefPtr<UINode> {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        return customNode;
    };
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    overlayManager->BindContentCover(isShow, std::move(callback), std::move(buildNodeFunc), modalStyle,
        std::move(onAppear), std::move(onDisappear), targetNode->GetId());
}

void ViewAbstractModelNG::RegisterMenuAppearCallback(
    std::vector<NG::OptionParam>& params, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    if (!params.empty() || buildFunc) {
        overlayManager->RegisterOnShowMenu([menuParam]() {
            if (menuParam.onAppear) {
                menuParam.onAppear();
            }
        });
    }
}

void ViewAbstractModelNG::RegisterMenuDisappearCallback(std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->RegisterOnHideMenu([menuParam]() {
        if (menuParam.onDisappear) {
            menuParam.onDisappear();
        }
    });
}

void ViewAbstractModelNG::RegisterContextMenuAppearCallback(ResponseType type, const MenuParam& menuParam)
{
    if (type == ResponseType::RIGHT_CLICK || type == ResponseType::LONG_PRESS) {
        SubwindowManager::GetInstance()->RegisterOnShowMenu([menuParam]() {
            if (menuParam.onAppear) {
                menuParam.onAppear();
            }
        });
    }
}

void ViewAbstractModelNG::RegisterContextMenuDisappearCallback(const MenuParam& menuParam)
{
    SubwindowManager::GetInstance()->RegisterOnHideMenu([menuParam]() {
        if (menuParam.onDisappear) {
            menuParam.onDisappear();
        }
    });
}

void ViewAbstractModelNG::BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<void()>&& buildFunc, NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    auto buildNodeFunc = [buildFunc]() -> RefPtr<UINode> {
        NG::ScopedViewStackProcessor builderViewStackProcess;
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        return customNode;
    };
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    overlayManager->BindSheet(isShow, std::move(callback), std::move(buildNodeFunc), sheetStyle,
        std::move(onAppear), std::move(onDisappear), targetNode->GetId());
}
} // namespace OHOS::Ace::NG
