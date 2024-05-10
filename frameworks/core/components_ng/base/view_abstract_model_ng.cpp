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
#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LONG_PRESS_DURATION = 800;

RefPtr<OverlayManager> GetOverlayFromPage(int32_t pageLevelId, bool isNav)
{
    if (pageLevelId <= 0) {
        return nullptr;
    }
    std::string tag = isNav ? V2::NAVDESTINATION_VIEW_ETS_TAG : V2::PAGE_ETS_TAG;
    auto frameNode = FrameNode::GetFrameNode(tag, pageLevelId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (tag == V2::PAGE_ETS_TAG) {
        auto node = AceType::DynamicCast<FrameNode>(frameNode);
        CHECK_NULL_RETURN(node, nullptr);
        auto pattern = node->GetPattern<PagePattern>();
        return pattern->GetOverlayManager();
    }
    return nullptr;
}

RefPtr<OverlayManager> FindPageNodeOverlay(const RefPtr<FrameNode>& targetNode, bool isShow)
{
    if (targetNode->GetPageLevelNodeId() > 0) {
        return GetOverlayFromPage(targetNode->GetPageLevelNodeId(), targetNode->PageLevelIsNavDestination());
    }
    auto parent = targetNode->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::PAGE_ETS_TAG) {
            auto node = AceType::DynamicCast<FrameNode>(parent);
            CHECK_NULL_RETURN(node, nullptr);
            auto pattern = node->GetPattern<PagePattern>();
            CHECK_NULL_RETURN(pattern, nullptr);
            pattern->CreateOverlayManager(isShow);
            auto overlay = pattern->GetOverlayManager();
            CHECK_NULL_RETURN(overlay, nullptr);
            targetNode->SetPageLevelNodeId(node->GetId());
            return overlay;
        }
        parent = parent->GetParent();
    }
    return nullptr;
}
} // namespace

void ViewAbstractModelNG::BindMenuGesture(
    std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    GestureEventFunc showMenu;
    auto weakTarget = AceType::WeakClaim(targetNode);
    if (!params.empty()) {
        showMenu = [params, weakTarget, menuParam](GestureEvent& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            NG::ViewAbstract::BindMenuWithItems(std::move(params), targetNode, menuPosition, menuParam);
        };
    } else if (buildFunc) {
        showMenu = [builderFunc = std::move(buildFunc), weakTarget, menuParam](const GestureEvent& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            std::function<void()> previewBuildFunc;
            NG::ViewAbstract::BindMenuWithCustomNode(
                std::move(builderFunc), targetNode, menuPosition, menuParam, std::move(previewBuildFunc));
        };
    } else {
        return;
    }
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    gestureHub->BindMenu(std::move(showMenu));
}

void ViewAbstractModelNG::BindMenu(
    std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    auto targetNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(targetNode);
    auto targetId = targetNode->GetId();
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true);
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto overlayManager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto menuNode = overlayManager->GetMenuNode(targetId);
    if (menuNode) {
        auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
        wrapperPattern->SetHasTransitionEffect(menuParam.hasTransitionEffect);
        if (menuParam.hasTransitionEffect) {
            auto renderContext = menuNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateChainedTransition(menuParam.transition);
        }
        if (wrapperPattern->IsShow() && menuParam.setShow && !menuParam.isShow) {
            overlayManager->HideMenu(menuNode, targetId, false);
        }
    } else if (menuParam.isShow) {
        if (!params.empty()) {
            NG::ViewAbstract::BindMenuWithItems(std::move(params), targetNode, menuParam.positionOffset, menuParam);
        } else if (buildFunc) {
            std::function<void()> previewBuildFunc;
            NG::ViewAbstract::BindMenuWithCustomNode(
                std::move(buildFunc), targetNode, menuParam.positionOffset, menuParam, std::move(previewBuildFunc));
        }
    }
    if (!menuParam.setShow) {
        BindMenuGesture(std::move(params), std::move(buildFunc), menuParam);
    }
    // delete menu when target node destroy
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    if (!menuParam.isShowInSubWindow && expandDisplay) {
        expandDisplay = false;
    }
    if (!expandDisplay) {
        auto destructor = [id = targetNode->GetId(), params]() mutable {
            params.clear();
            auto pipeline = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->DeleteMenu(id);
        };
        targetNode->PushDestroyCallback(destructor);
    } else {
        auto destructor = [id = targetNode->GetId(), containerId = Container::CurrentId(), params]() mutable {
            params.clear();
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

void CreateCustomMenuWithPreview(
    std::function<void()>& buildFunc, const MenuParam& menuParam, std::function<void()>& previewBuildFunc)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    if (menuParam.previewMode == MenuPreviewMode::IMAGE) {
        auto context = targetNode->GetRenderContext();
        CHECK_NULL_VOID(context);
        auto gestureHub = targetNode->GetEventHub<EventHub>()->GetGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto pixelMap = context->GetThumbnailPixelMap();
        gestureHub->SetPixelMap(pixelMap);
    }
    auto refTargetNode = AceType::Claim<NG::FrameNode>(targetNode);
    NG::ViewAbstract::BindMenuWithCustomNode(
        std::move(buildFunc), refTargetNode, menuParam.positionOffset, menuParam, std::move(previewBuildFunc));
}

void BindContextMenuSingle(
    std::function<void()>& buildFunc, const MenuParam& menuParam, std::function<void()>& previewBuildFunc)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true);
    auto targetId = targetNode->GetId();
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId());
    if (subwindow) {
        auto childContainerId = subwindow->GetChildContainerId();
        auto childContainer = AceEngine::Get().GetContainer(childContainerId);
        CHECK_NULL_VOID(childContainer);
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto menuNode = overlayManager->GetMenuNode(targetId);
        if (menuNode) {
            auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_VOID(wrapperPattern);
            if (wrapperPattern->IsShow() && !menuParam.isShow) {
                SubwindowManager::GetInstance()->HideMenuNG(menuNode, targetId);
            } else if (!wrapperPattern->IsShow() && menuParam.isShow) {
                CreateCustomMenuWithPreview(buildFunc, menuParam, previewBuildFunc);
            }
        } else if (menuParam.isShow && buildFunc) {
            CreateCustomMenuWithPreview(buildFunc, menuParam, previewBuildFunc);
        }
    } else {
        // first response for build subwindow and menu
        if (menuParam.isShow && buildFunc) {
            CreateCustomMenuWithPreview(buildFunc, menuParam, previewBuildFunc);
        }
    }
}

void ViewAbstractModelNG::BindContextMenu(ResponseType type, std::function<void()>& buildFunc,
    const MenuParam& menuParam, std::function<void()>& previewBuildFunc)
{
    auto targetNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(targetNode);

    if (menuParam.contextMenuRegisterType == ContextMenuRegisterType::CUSTOM_TYPE) {
        BindContextMenuSingle(buildFunc, menuParam, previewBuildFunc);
    } else {
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
                            NG::ViewAbstract::BindMenuWithCustomNode(
                                std::move(builder), targetNode, menuPosition, menuParam, std::move(previewBuildFunc));
                        }
                    },
                    TaskExecutor::TaskType::PLATFORM, "ArkUIRightClickCreateCustomMenu");
            };
            auto inputHub = targetNode->GetOrCreateInputEventHub();
            CHECK_NULL_VOID(inputHub);
            inputHub->BindContextMenu(std::move(event));
        } else if (type == ResponseType::LONG_PRESS) {
            auto gestureHub = targetNode->GetEventHub<EventHub>()->GetGestureEventHub();
            CHECK_NULL_VOID(gestureHub);
            gestureHub->SetPreviewMode(menuParam.previewMode);
            // create or show menu on long press
            auto event =
                [builderF = buildFunc, weakTarget, menuParam, previewBuildFunc](const GestureEvent& info) mutable {
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
                        NG::ViewAbstract::BindMenuWithCustomNode(
                            std::move(builder), targetNode, menuPosition, menuParam, std::move(previewBuildFunc));
                    },
                    TaskExecutor::TaskType::PLATFORM, "ArkUILongPressCreateCustomMenu");
            };
            auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(event));
            ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true);
            hub->SetLongPressEvent(longPress, false, true, LONG_PRESS_DURATION);
        } else {
            return;
        }
        RegisterContextMenuKeyEvent(targetNode, buildFunc, menuParam);
    }

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
    std::function<void()>&& onDisappear, std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
    const NG::ContentCoverParam& contentCoverParam)
{
    auto targetNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
        std::move(onAppear), std::move(onDisappear), std::move(onWillAppear), std::move(onWillDisappear),
        contentCoverParam, targetNode);
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
            NG::ViewAbstract::BindMenuWithCustomNode(
                std::move(builder), targetNode, OffsetF(), param, std::move(previewBuildFunc));
            return true;
        }
        return false;
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent), OnKeyEventType::CONTEXT_MENU);
}

RefPtr<PipelineContext> ViewAbstractModelNG::GetSheetContext(NG::SheetStyle& sheetStyle)
{
    RefPtr<PipelineContext> context;
    if (sheetStyle.instanceId.has_value()) {
        auto container = AceEngine::Get().GetContainer(sheetStyle.instanceId.value());
        CHECK_NULL_RETURN(container, nullptr);
        auto contextBase = container->GetPipelineContext();
        CHECK_NULL_RETURN(contextBase, nullptr);
        context = AceType::DynamicCast<PipelineContext>(contextBase);
    } else {
        context = PipelineContext::GetCurrentContext();
    }
    return context;
}

void ViewAbstractModelNG::BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<void()>&& buildFunc, std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle,
    std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
    std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
    std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
    std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack)
{
    auto targetNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    auto context = GetSheetContext(sheetStyle);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    if (sheetStyle.showInPage.value_or(false)) {
        overlayManager = FindPageNodeOverlay(targetNode, isShow);
    }
    CHECK_NULL_VOID(overlayManager);

    // delete Sheet when target node destroy
    auto destructor =
        [id = targetNode->GetId(), pageLevelId = targetNode->GetPageLevelNodeId(),
            isNav = targetNode->PageLevelIsNavDestination(), showInPage = sheetStyle.showInPage.value_or(false),
            instanceId = sheetStyle.instanceId.has_value() ? sheetStyle.instanceId.value() : Container::CurrentId()]() {
            ContainerScope scope(instanceId);
            auto pipeline = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetOverlayManager();
            if (showInPage) {
                TAG_LOGD(AceLogTag::ACE_SHEET, "To showInPage, get overlayManager from GetOverlayFromPage");
                overlayManager = GetOverlayFromPage(pageLevelId, isNav);
            }
            CHECK_NULL_VOID(overlayManager);
            overlayManager->DeleteModal(id);
        };
    targetNode->PushDestroyCallback(destructor);

    overlayManager->BindSheet(isShow, std::move(callback), std::move(buildNodeFunc), std::move(buildTitleNodeFunc),
        sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
        std::move(sheetSpringBack), targetNode);
}

void ViewAbstractModelNG::DismissSheet()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->DismissSheet();
}

void ViewAbstractModelNG::DismissContentCover()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->DismissContentCover();
}

void ViewAbstractModelNG::SheetSpringBack()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->SheetSpringBack();
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

void ViewAbstractModelNG::SetAccessibilityTextHint(const std::string& text)
{
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityTextHint(text);
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

void ViewAbstractModelNG::SetAccessibilityVirtualNode(std::function<void()>&& buildFunc)
{
    auto buildNodeFunc = [buildFunc = std::move(buildFunc)]() -> RefPtr<UINode> {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        return customNode;
    };
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto virtualNode = buildNodeFunc();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    auto virtualFrameNode = AceType::DynamicCast<NG::FrameNode>(virtualNode);
    CHECK_NULL_VOID(virtualFrameNode);
    FrameNode::ProcessOffscreenNode(virtualFrameNode);
    accessibilityProperty->SaveAccessibilityVirtualNode(virtualNode);
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

bool ViewAbstractModelNG::GetAccessibilityGroup(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    return accessibilityProperty->IsAccessibilityGroup();
}

std::string ViewAbstractModelNG::GetAccessibilityText(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    return accessibilityProperty->GetAccessibilityText();
}

std::string ViewAbstractModelNG::GetAccessibilityDescription(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    return accessibilityProperty->GetAccessibilityDescription();
}

std::string ViewAbstractModelNG::GetAccessibilityImportance(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    return accessibilityProperty->GetAccessibilityLevel();
}

} // namespace OHOS::Ace::NG
