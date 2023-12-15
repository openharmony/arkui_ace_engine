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

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/event/mouse_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LONG_PRESS_DURATION = 800;
} // namespace

void ViewAbstractModelNG::CreateCustomMenu(const std::function<void()>& buildFunc,
    const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset, std::function<void()>& previewBuildFunc,
    MenuParam menuParam)
{
    NG::ScopedViewStackProcessor builderViewStackProcessor;
    if (!buildFunc) {
        return;
    }
    buildFunc();
    auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();

    RefPtr<UINode> previewCustomNode;
    if (previewBuildFunc && menuParam.previewMode == MenuPreviewMode::CUSTOM) {
        previewBuildFunc();
        previewCustomNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
#ifdef PREVIEW
    // unable to use the subWindow in the Previewer.
    menuParam.type = MenuType::MENU;
#endif
    NG::ViewAbstract::BindMenuWithCustomNode(customNode, targetNode, offset, menuParam, previewCustomNode);
}

void ViewAbstractModelNG::BindMenu(
    std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    auto targetId = targetNode->GetId();
#ifdef ENABLE_DRAG_FRAMEWORK
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true);
#endif // ENABLE_DRAG_FRAMEWORK
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto menuNode = overlayManager->GetMenuNode(targetId);
    if (menuNode) {
        auto pattern = menuNode->GetPattern<MenuWrapperPattern>();
        if (!pattern->GetShow() && menuParam.isShow) {
            overlayManager->ShowMenu(targetId, menuParam.positionOffset, menuNode);
        } else if (pattern->GetShow() && menuParam.setShow && !menuParam.isShow) {
            overlayManager->HideMenu(menuNode, targetId, false);
        }
    } else if (menuParam.isShow) {
        if (!params.empty()) {
            NG::ViewAbstract::BindMenuWithItems(std::move(params), targetNode, menuParam.positionOffset, menuParam);
        } else if (buildFunc) {
            std::function<void()> previewBuildFunc;
            CreateCustomMenu(buildFunc, targetNode, menuParam.positionOffset, previewBuildFunc, menuParam);
        }
    }
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
            std::function<void()> previewBuildFunc;
            CreateCustomMenu(builderFunc, targetNode, menuPosition, previewBuildFunc, menuParam);
        };
    } else {
        return;
    }
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    gestureHub->BindMenu(std::move(showMenu));

    // delete menu when target node destroy
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    if (!expandDisplay) {
        auto destructor = [id = targetNode->GetId()]() {
            auto pipeline = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->DeleteMenu(id);
        };
        targetNode->PushDestroyCallback(destructor);
    } else {
        auto destructor = [id = targetNode->GetId(), containerId = Container::CurrentId()]() {
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
}

void ViewAbstractModelNG::BindContextMenu(ResponseType type, std::function<void()>& buildFunc,
    const MenuParam& menuParam, std::function<void()>& previewBuildFunc)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);

    auto hub = targetNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
    if (type == ResponseType::RIGHT_CLICK) {
        OnMouseEventFunc event = [builderF = buildFunc, weakTarget, menuParam](MouseInfo& info) mutable {
            auto containerId = Container::CurrentId();
            auto taskExecutor = Container::CurrentTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
                info.SetStopPropagation(true);
            }
            taskExecutor->PostTask(
                [containerId, builder = builderF, weakTarget, menuParam, info]() mutable {
                    auto targetNode = weakTarget.Upgrade();
                    CHECK_NULL_VOID(targetNode);
                    NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                        info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
                    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
                    CHECK_NULL_VOID(pipelineContext);
                    auto windowRect = pipelineContext->GetDisplayWindowRectInfo();
                    menuPosition += NG::OffsetF { windowRect.Left(), windowRect.Top() };
                    if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
                        std::function<void()> previewBuildFunc;
                        NG::ViewAbstractModelNG::CreateCustomMenu(
                            builder, targetNode, menuPosition, previewBuildFunc, menuParam);
                    }
                },
                TaskExecutor::TaskType::PLATFORM);
        };
        auto inputHub = targetNode->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        inputHub->BindContextMenu(std::move(event));
    } else if (type == ResponseType::LONG_PRESS) {
#ifdef ENABLE_DRAG_FRAMEWORK
        auto gestureHub = targetNode->GetEventHub<EventHub>()->GetGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetPreviewMode(menuParam.previewMode);
#endif
        // create or show menu on long press
        auto event = [builderF = buildFunc, weakTarget, menuParam, previewBuildFunc](const GestureEvent& info) mutable {
            auto containerId = Container::CurrentId();
            auto taskExecutor = Container::CurrentTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [containerId, builder = builderF, weakTarget, menuParam, previewBuildFunc, info]() mutable {
                    auto targetNode = weakTarget.Upgrade();
                    CHECK_NULL_VOID(targetNode);
                    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
                    CHECK_NULL_VOID(pipelineContext);
                    auto dragDropManager = pipelineContext->GetDragDropManager();
                    CHECK_NULL_VOID(dragDropManager);
                    if (dragDropManager->IsAboutToPreview() || dragDropManager->IsDragging()) {
                        return;
                    }
                    if (menuParam.previewMode == MenuPreviewMode::IMAGE) {
                        auto context = targetNode->GetRenderContext();
                        CHECK_NULL_VOID(context);
                        auto gestureHub = targetNode->GetEventHub<EventHub>()->GetGestureEventHub();
                        CHECK_NULL_VOID(gestureHub);
                        auto pixelMap = context->GetThumbnailPixelMap();
                        gestureHub->SetPixelMap(pixelMap);
                    }
                    NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                        info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
                    auto windowRect = pipelineContext->GetDisplayWindowRectInfo();
                    menuPosition += NG::OffsetF { windowRect.Left(), windowRect.Top() };
                    NG::ViewAbstractModelNG::CreateCustomMenu(
                        builder, targetNode, menuPosition, previewBuildFunc, menuParam);
                },
                TaskExecutor::TaskType::PLATFORM);
        };
        auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(event));
#ifdef ENABLE_DRAG_FRAMEWORK
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true);
#endif // ENABLE_DRAG_FRAMEWORK

        hub->SetLongPressEvent(longPress, false, true, LONG_PRESS_DURATION);
    } else {
        return;
    }
    RegisterContextMenuKeyEvent(targetNode, buildFunc, menuParam);

    // delete menu when target node destroy
    auto destructor = [id = targetNode->GetId(), containerId = Container::CurrentId()]() {
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

void ViewAbstractModelNG::BindBackground(std::function<void()>&& buildFunc, const Alignment& align)
{
    auto buildNodeFunc = [buildFunc = std::move(buildFunc)]() -> RefPtr<UINode> {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        return customNode;
    };
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    targetNode->SetBackgroundFunction(std::move(buildNodeFunc));
    NG::ViewAbstract::SetBackgroundAlign(align);
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

    // delete full screen modal when target node destroy
    auto destructor = [id = targetNode->GetId()]() {
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteModal(id);
    };
    targetNode->PushDestroyCallback(destructor);

    overlayManager->BindContentCover(isShow, std::move(callback), std::move(buildNodeFunc), modalStyle,
        std::move(onAppear), std::move(onDisappear), targetNode);
}

void ViewAbstractModelNG::RegisterContextMenuKeyEvent(
    const RefPtr<FrameNode>& targetNode, std::function<void()>& buildFunc, const MenuParam& menuParam)
{
    auto focusHub = targetNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto onKeyEvent = [wp = AceType::WeakClaim(AceType::RawPtr(targetNode)), builder = buildFunc, param = menuParam](
                          const KeyEvent& event) mutable -> bool {
        if (event.action != KeyAction::DOWN) {
            return false;
        }
        if (event.code == KeyCode::KEY_MENU || event.keyIntention == KeyIntention::INTENTION_MENU) {
            auto targetNode = wp.Upgrade();
            CHECK_NULL_RETURN(targetNode, false);
            if (!param.placement.has_value()) {
                param.placement = Placement::BOTTOM_LEFT;
            }
            std::function<void()> previewBuildFunc = nullptr;
            CreateCustomMenu(builder, targetNode, OffsetF(), previewBuildFunc, param);
            return true;
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent), OnKeyEventType::CONTEXT_MENU);
}

void ViewAbstractModelNG::BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<void()>&& buildFunc, std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle,
    std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    auto buildNodeFunc = [buildFunc]() -> RefPtr<UINode> {
        NG::ScopedViewStackProcessor builderViewStackProcess;
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        return customNode;
    };
    auto buildTitleNodeFunc = [titleBuildFunc]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(titleBuildFunc, nullptr);
        NG::ScopedViewStackProcessor builderViewStackProcess;
        titleBuildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        return customNode;
    };
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    // delete Sheet when target node destroy
    auto destructor = [id = targetNode->GetId()]() {
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteModal(id);
    };
    targetNode->PushDestroyCallback(destructor);

    overlayManager->BindSheet(isShow, std::move(callback), std::move(buildNodeFunc), std::move(buildTitleNodeFunc),
        sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), targetNode);
}

void ViewAbstractModelNG::DismissSheet()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->DismissSheet();
}

void ViewAbstractModelNG::SetAccessibilityGroup(bool accessible)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityGroup(accessible);
}

void ViewAbstractModelNG::SetAccessibilityText(const std::string& text)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityText(text);
}

void ViewAbstractModelNG::SetAccessibilityDescription(const std::string& description)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityDescription(description);
}

void ViewAbstractModelNG::SetAccessibilityImportance(const std::string& importance)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityLevel(importance);
}

void ViewAbstractModelNG::SetAccessibilityText(FrameNode* frameNode, const std::string& text)
{
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityText(text);
}

void ViewAbstractModelNG::SetAccessibilityImportance(FrameNode* frameNode, const std::string& importance)
{
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityLevel(importance);
}

void ViewAbstractModelNG::SetAccessibilityDescription(FrameNode* frameNode, const std::string& description)
{
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityDescription(description);
}

void ViewAbstractModelNG::SetAccessibilityGroup(FrameNode* frameNode, bool accessible)
{
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityGroup(accessible);
}
} // namespace OHOS::Ace::NG
