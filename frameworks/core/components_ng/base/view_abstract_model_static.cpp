/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/view_abstract_model_static.h"

#include "base/utils/multi_thread.h"
#include "core/common/ace_engine.h"
#include "core/common/vibrator/vibrator_utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#include "core/components_ng/syntax/static/detached_free_root_proxy_node.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#endif

namespace OHOS::Ace::NG {
namespace {
const std::string BLOOM_RADIUS_SYS_RES_NAME = "sys.float.ohos_id_point_light_bloom_radius";
const std::string BLOOM_COLOR_SYS_RES_NAME = "sys.color.ohos_id_point_light_bloom_color";
const std::string ILLUMINATED_BORDER_WIDTH_SYS_RES_NAME = "sys.float.ohos_id_point_light_illuminated_border_width";
constexpr char KEY_CONTEXT_MENU[] = "ContextMenu";
constexpr char KEY_MENU[] = "Menu";
constexpr float DEFAULT_BIAS = 0.5f;

void StartVibrator(const MenuParam& menuParam, bool isMenu, const std::string& menuHapticFeedback)
{
    if (menuParam.hapticFeedbackMode == HapticFeedbackMode::ENABLED) {
        VibratorUtils::StartViratorDirectly(menuHapticFeedback);
        return;
    }
    if (menuParam.hapticFeedbackMode == HapticFeedbackMode::AUTO) {
        if (menuParam.maskEnable.has_value()) {
            if (menuParam.maskEnable.value()) {
                VibratorUtils::StartViratorDirectly(menuHapticFeedback);
            }
            return;
        }
        if (!isMenu && menuParam.previewMode != MenuPreviewMode::NONE) {
            VibratorUtils::StartViratorDirectly(menuHapticFeedback);
        }
    }
}

void UpdateIsShowStatusForMenu(int32_t targetId, bool isShow)
{
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
        Container::CurrentId(), SubwindowType::TYPE_MENU);
    CHECK_NULL_VOID(subwindow);
    auto overlayManager = subwindow->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto menuNode = overlayManager->GetMenuNode(targetId);
    CHECK_NULL_VOID(menuNode);
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    wrapperPattern->SetIsShowFromUser(isShow);
}

NG::OffsetF UpdateMenuPostion(
    const NG::OffsetF& menuPosition, const MenuParam& menuParam, const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(targetNode, menuPosition);
    if (menuParam.anchorPosition.has_value()) {
        NG::OffsetF targetNodePosition = targetNode->GetPositionToWindowWithTransform();

        return { menuParam.anchorPosition->GetX() + menuParam.positionOffset.GetX() + targetNodePosition.GetX(),
            menuParam.anchorPosition->GetY() + menuParam.positionOffset.GetY() + targetNodePosition.GetY() };
    }
    return menuPosition;
}
} // namespace

void ViewAbstractModelStatic::BindMenuGesture(FrameNode* targetNode,
    std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(targetNode);
    GestureEventFunc showMenu;
    auto weakTarget = AceType::WeakClaim(targetNode);
    if (!params.empty()) {
        showMenu = [params, weakTarget, menuParam](GestureEvent& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            if (NG::ViewAbstractModelNG::CheckSkipMenuShow(targetNode)) {
                TAG_LOGI(AceLogTag::ACE_MENU, "skip menu show with params %{public}d", targetNode->GetId());
                return;
            }
            auto pipelineContext = targetNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
            CHECK_NULL_VOID(menuTheme);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            StartVibrator(menuParam, true, menuTheme->GetMenuHapticFeedback());
            NG::ViewAbstract::BindMenuWithItems(
                std::move(params), targetNode, UpdateMenuPostion(menuPosition, menuParam, targetNode), menuParam);
        };
    } else if (buildFunc) {
        showMenu = [builderFunc = std::move(buildFunc), weakTarget, menuParam](const GestureEvent& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            if (NG::ViewAbstractModelNG::CheckSkipMenuShow(targetNode)) {
                TAG_LOGI(AceLogTag::ACE_MENU, "skip menu show with builder %{public}d", targetNode->GetId());
                return;
            }
            auto pipelineContext = targetNode->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
            CHECK_NULL_VOID(menuTheme);
            NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
            StartVibrator(menuParam, true, menuTheme->GetMenuHapticFeedback());
            std::function<void()> previewBuildFunc;
            NG::ViewAbstract::BindMenuWithCustomNode(std::move(builderFunc), targetNode,
                UpdateMenuPostion(menuPosition, menuParam, targetNode), menuParam, std::move(previewBuildFunc));
        };
    }
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    gestureHub->BindMenu(std::move(showMenu));
    BindMenuTouch(targetNode, gestureHub);
}

void ViewAbstractModelStatic::BindMenuTouch(FrameNode* targetNode, const RefPtr<GestureEventHub>& gestrueHub)
{
    CHECK_NULL_VOID(targetNode);
    auto weakTarget = AceType::WeakClaim(targetNode);
    auto touchCallback = [weakTarget](const TouchEventInfo& info) {
        auto targetNode = weakTarget.Upgrade();
        CHECK_NULL_VOID(targetNode);
        const auto& touches = info.GetTouches();
        CHECK_EQUAL_VOID(touches.empty(), true);
        auto touchType = touches.front().GetTouchType();
        auto targetId = targetNode->GetId();
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId());
        CHECK_NULL_VOID(subwindow);
        auto childContainerId = subwindow->GetChildContainerId();
        auto childContainer = AceEngine::Get().GetContainer(childContainerId);
        CHECK_NULL_VOID(childContainer);
        auto subwindowPipline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
        CHECK_NULL_VOID(subwindowPipline);
        auto subwindowOverlay = subwindowPipline->GetOverlayManager();
        CHECK_NULL_VOID(subwindowOverlay);
        if (touchType == TouchType::DOWN) {
            auto wrapperNode = subwindowOverlay->GetMenuNode(targetId);
            CHECK_NULL_VOID(wrapperNode);
            auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_VOID(wrapperPattern);
            if (wrapperPattern->IsShow() || wrapperPattern->GetMenuStatus() == MenuStatus::ON_HIDE_ANIMATION) {
                TAG_LOGI(AceLogTag::ACE_MENU, "skip menu show, target %{public}d", targetId);
                subwindowOverlay->SkipMenuShow(targetId);
            }
        } else if ((touchType == TouchType::UP || touchType == TouchType::CANCEL) &&
                   subwindowOverlay->CheckSkipMenuShow(targetId)) {
            auto weakOverlay = AceType::WeakClaim(AceType::RawPtr(subwindowOverlay));
            auto taskExecutor = Container::CurrentTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            TAG_LOGI(AceLogTag::ACE_MENU, "post resume menu show task, target %{public}d", targetId);
            taskExecutor->PostTask(
                [weakOverlay, targetId]() mutable {
                    TAG_LOGI(AceLogTag::ACE_MENU, "execute resume menu show, target %{public}d", targetId);
                    auto subwindowOverlay = weakOverlay.Upgrade();
                    CHECK_NULL_VOID(subwindowOverlay);
                    subwindowOverlay->ResumeMenuShow(targetId);
                }, TaskExecutor::TaskType::PLATFORM, "ArkUIResumeMenuShow");
        }
    };
    gestrueHub->RegisterMenuOnTouch(touchCallback);
}

bool ViewAbstractModelStatic::CheckMenuIsShow(
    const MenuParam& menuParam, int32_t targetId, const RefPtr<FrameNode>& targetNode, bool isBuildFuncNull)
{
    RefPtr<NG::PipelineContext> pipeline = nullptr;
    if (menuParam.isShowInSubWindow) {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
            Container::CurrentId(), SubwindowType::TYPE_MENU);
        CHECK_NULL_RETURN(subwindow, false);
        auto childContainerId = subwindow->GetChildContainerId();
        auto childContainer = AceEngine::Get().GetContainer(childContainerId);
        CHECK_NULL_RETURN(childContainer, false);
        pipeline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
    } else {
        CHECK_NULL_RETURN(targetNode, false);
        pipeline = targetNode->GetContextRefPtr();
    }
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    auto menuNode = overlayManager->GetMenuNode(targetId);
    CHECK_NULL_RETURN(menuNode, false);
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(wrapperPattern, false);
    if (menuParam.hasTransitionEffect) {
        auto renderContext = menuNode->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        renderContext->UpdateChainedTransition(menuParam.transition);
    }
    if ((wrapperPattern->IsShow() && !wrapperPattern->GetIsOpenMenu()) &&
        ((menuParam.setShow && !menuParam.isShow) || isBuildFuncNull)) {
        TAG_LOGI(AceLogTag::ACE_MENU, "execute hide menu.");
        overlayManager->HideMenu(menuNode, targetId, false);
    }
    return true;
}

void ViewAbstractModelStatic::BindMenu(FrameNode* frameNode,
    std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    auto targetNode = AceType::Claim(frameNode);
    CHECK_NULL_VOID(targetNode);
    FREE_NODE_CHECK(frameNode, BindMenu, frameNode, std::move(params), std::move(buildFunc), menuParam);
    auto targetId = targetNode->GetId();
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true, frameNode);
    bool isBuildFuncNull = (buildFunc == nullptr && params.empty());
    if (CheckMenuIsShow(menuParam, targetId, targetNode, isBuildFuncNull)) {
        TAG_LOGI(AceLogTag::ACE_MENU, "hide menu done %{public}d %{public}d.", menuParam.isShowInSubWindow, targetId);
    } else if (menuParam.isShow) {
        auto pipelineContext = targetNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
        CHECK_NULL_VOID(menuTheme);
        StartVibrator(menuParam, true, menuTheme->GetMenuHapticFeedback());
        NG::OffsetF menuPosition { menuParam.positionOffset.GetX(), menuParam.positionOffset.GetY() };
        if (!params.empty()) {
            NG::ViewAbstract::BindMenuWithItems(
                std::move(params), targetNode, UpdateMenuPostion(menuPosition, menuParam, targetNode), menuParam);
        } else if (buildFunc) {
            std::function<void()> previewBuildFunc;
            NG::ViewAbstract::BindMenuWithCustomNode(std::move(buildFunc), targetNode,
                UpdateMenuPostion(menuPosition, menuParam, targetNode), menuParam, std::move(previewBuildFunc));
        }
    }
    if (isBuildFuncNull) {
        auto gestureHub = targetNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->RemoveBindMenu();
        gestureHub->RegisterMenuOnTouch(nullptr);
        return;
    }
    if (!menuParam.setShow) {
        BindMenuGesture(frameNode, std::move(params), std::move(buildFunc), menuParam);
    }
    // delete menu when target node destroy
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    if (!theme->GetExpandDisplay() || !menuParam.isShowInSubWindow) {
        auto destructor = [id = targetNode->GetId(), params]() mutable {
            params.clear();
            auto pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->DeleteMenu(id);
        };
        targetNode->PushDestroyCallbackWithTag(destructor, KEY_MENU);
    } else {
        auto destructor = [id = targetNode->GetId(), containerId = Container::CurrentId(), params]() mutable {
            params.clear();
            auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(containerId, SubwindowType::TYPE_MENU);
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
        targetNode->PushDestroyCallbackWithTag(destructor, KEY_MENU);
    }
}

void ViewAbstractModelStatic::CreateCustomMenuWithPreview(FrameNode* targetNode,
    std::function<void()>&& buildFunc, const MenuParam& menuParam, std::function<void()>&& previewBuildFunc)
{
    CHECK_NULL_VOID(targetNode);
    if (menuParam.previewMode == MenuPreviewMode::IMAGE) {
        auto context = targetNode->GetRenderContext();
        CHECK_NULL_VOID(context);
        auto gestureHub = targetNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto pixelMap = context->GetThumbnailPixelMap();
        gestureHub->SetPixelMap(pixelMap);
    }
    auto refTargetNode = AceType::Claim<NG::FrameNode>(targetNode);
    auto pipelineContext = targetNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    StartVibrator(menuParam, false, menuTheme->GetMenuHapticFeedback());
    NG::OffsetF menuPosition { menuParam.positionOffset.GetX(), menuParam.positionOffset.GetY() };
    NG::ViewAbstract::BindMenuWithCustomNode(std::move(buildFunc), refTargetNode,
        UpdateMenuPostion(menuPosition, menuParam, refTargetNode), menuParam, std::move(previewBuildFunc));
}

void ViewAbstractModelStatic::BindContextMenuSingle(FrameNode* targetNode,
    std::function<void()>&& buildFunc, const MenuParam& menuParam, std::function<void()>&& previewBuildFunc)
{
    CHECK_NULL_VOID(targetNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true, targetNode);
    auto targetId = targetNode->GetId();
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "target %{public}d menu isShow %{public}d", targetId, menuParam.isShow);
    auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
        Container::CurrentId(), SubwindowType::TYPE_MENU);
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
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "menuNode already exist");
            auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_VOID(wrapperPattern);
            // If menu is shown or in show animation, set isShow to false will close menu. If menu is not shown or
            // in close animation, wrapperPattern->IsShow() is false, set isShow to false will not trigger close again.
            if (wrapperPattern->IsShow() && !menuParam.isShow) {
                TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu, tagetNode id %{public}d.", targetId);
                SubwindowManager::GetInstance()->HideMenuNG(menuNode, targetId);
                UpdateIsShowStatusForMenu(targetId, false);
            } else if (!wrapperPattern->IsShow() && menuParam.isShow &&
                       wrapperPattern->GetIsShowFromUser() != menuParam.isShow) {
                // If click outside to close menu during show animation, and isShow is always true without changing,
                // then show new menu will result in an incorrect isShow state because onDisappear not be triggered.
                // The menu only show if isShow is manually set from false to true.
                CreateCustomMenuWithPreview(targetNode, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
                UpdateIsShowStatusForMenu(targetId, true);
            }
        } else if (menuParam.isShow && buildFunc) {
            CreateCustomMenuWithPreview(targetNode, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
            UpdateIsShowStatusForMenu(targetId, true);
        }
    } else {
        // first response for build subwindow and menu
        if (menuParam.isShow && buildFunc) {
            CreateCustomMenuWithPreview(targetNode, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
            UpdateIsShowStatusForMenu(targetId, true);
        }
    }
}

void ViewAbstractModelStatic::BindContextMenuStatic(const RefPtr<FrameNode>& targetNode, ResponseType type,
    std::function<void()>&& buildFunc, NG::MenuParam& menuParam, std::function<void()>&& previewBuildFunc)
{
    CHECK_NULL_VOID(targetNode);
    FREE_NODE_CHECK(targetNode, BindContextMenuStatic, targetNode, type, std::move(buildFunc), menuParam,
        std::move(previewBuildFunc));
    auto targetId = targetNode->GetId();
    bool isBuildFuncNull = (buildFunc == nullptr);
    if (CheckMenuIsShow(menuParam, targetId, targetNode, isBuildFuncNull)) {
        TAG_LOGI(AceLogTag::ACE_MENU, "hide menu done %{public}d %{public}d.", menuParam.isShowInSubWindow, targetId);
    }
    if (isBuildFuncNull) {
        auto inputHub = targetNode->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        inputHub->BindContextMenu(nullptr);
        return;
    }
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
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "menuNode already exist");
            auto menuWrapperPattern = menuNode->GetPattern<NG::MenuWrapperPattern>();
            CHECK_NULL_VOID(menuWrapperPattern);
            menuWrapperPattern->SetMenuTransitionEffect(menuNode, menuParam);
            menuWrapperPattern->RegisterMenuStateChangeCallback(menuParam.onStateChange);
        }
    }
    if (menuParam.contextMenuRegisterType == ContextMenuRegisterType::CUSTOM_TYPE) {
        BindContextMenuSingle(AceType::RawPtr(targetNode), std::move(buildFunc), menuParam,
            std::move(previewBuildFunc));
    } else {
        auto hub = targetNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(hub);
        auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
        if (type == ResponseType::RIGHT_CLICK) {
            OnMouseEventFunc event = [builderF = buildFunc, weakTarget, menuParam,
                                         previewBuildFunc = std::move(previewBuildFunc)](MouseInfo& info) mutable {
                TAG_LOGI(AceLogTag::ACE_MENU, "Execute rightClick task for menu");
                auto containerId = Container::CurrentId();
                auto taskExecutor = Container::CurrentTaskExecutor();
                CHECK_NULL_VOID(taskExecutor);
                if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
                    info.SetStopPropagation(true);
                }
                taskExecutor->PostTask(
                    [containerId, builder = builderF, weakTarget, menuParam, info,
                        previewBuildFunc = std::move(previewBuildFunc)]() mutable {
                        auto targetNode = weakTarget.Upgrade();
                        CHECK_NULL_VOID(targetNode);
                        NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
                            info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
                        if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
                            auto pipelineContext = targetNode->GetContext();
                            CHECK_NULL_VOID(pipelineContext);
                            auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
                            CHECK_NULL_VOID(menuTheme);
                            StartVibrator(menuParam, false, menuTheme->GetMenuHapticFeedback());
                            NG::ViewAbstract::BindMenuWithCustomNode(std::move(builder), targetNode,
                                UpdateMenuPostion(menuPosition, menuParam, targetNode), menuParam,
                                std::move(previewBuildFunc));
                        }
                    },
                    TaskExecutor::TaskType::PLATFORM, "ArkUIRightClickCreateCustomMenu");
            };
            auto inputHub = targetNode->GetOrCreateInputEventHub();
            CHECK_NULL_VOID(inputHub);
            inputHub->BindContextMenu(std::move(event));
        } else if (type == ResponseType::LONG_PRESS) {
            ViewAbstractModelNG::BindContextMenuWithLongPress(targetNode, buildFunc, menuParam, previewBuildFunc, true);
        } else {
            return;
        }
        RegisterContextMenuKeyEvent(targetNode, buildFunc, menuParam);
    }

    // delete menu when target node destroy
    auto destructor = [id = targetNode->GetId(), containerId = Container::CurrentId()]() {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(containerId, SubwindowType::TYPE_MENU);
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
    targetNode->PushDestroyCallbackWithTag(destructor, KEY_CONTEXT_MENU);
}

void ViewAbstractModelStatic::BindDragWithContextMenuParamsStatic(FrameNode* targetNode, const NG::MenuParam& menuParam)
{
    CHECK_NULL_VOID(targetNode);

    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    if (gestureHub) {
        if (menuParam.contextMenuRegisterType == ContextMenuRegisterType::CUSTOM_TYPE) {
            gestureHub->SetBindMenuStatus(
                true, menuParam.isShow, menuParam.previewMode);
        } else if (menuParam.menuBindType == MenuBindingType::LONG_PRESS) {
            gestureHub->SetBindMenuStatus(false, false, menuParam.previewMode);
        }
        gestureHub->SetPreviewMode(menuParam.previewMode);
        gestureHub->SetContextMenuShowStatus(menuParam.isShow);
        gestureHub->SetMenuBindingType(menuParam.menuBindType);
        // set menu preview scale to drag.
        if (menuParam.menuBindType != MenuBindingType::RIGHT_CLICK) {
            auto menuPreviewScale = LessOrEqual(menuParam.previewAnimationOptions.scaleTo, 0.0)
                                        ? DEFALUT_DRAG_PPIXELMAP_SCALE
                                        : menuParam.previewAnimationOptions.scaleTo;
            gestureHub->SetMenuPreviewScale(menuPreviewScale);
        }
    } else {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Can not get gestureEventHub!");
    }
}

void ViewAbstractModelStatic::BindContentCover(FrameNode* frameNode, bool isShow,
    std::function<void(const std::string&)>&& callback, std::function<RefPtr<UINode>()>&& buildFunc,
    NG::ModalStyle& modalStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
    std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
    const NG::ContentCoverParam& contentCoverParam)
{
    auto targetNode = AceType::Claim(frameNode);
    CHECK_NULL_VOID(targetNode);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    // delete full screen modal when target node destroy
    auto destructor = [id = targetNode->GetId()]() {
        auto pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteModal(id);
    };
    targetNode->PushDestroyCallbackWithTag(destructor, V2::MODAL_PAGE_TAG);

    overlayManager->BindContentCover(isShow, std::move(callback), std::move(buildFunc), modalStyle,
        std::move(onAppear), std::move(onDisappear), std::move(onWillAppear), std::move(onWillDisappear),
        contentCoverParam, targetNode);
}

void ViewAbstractModelStatic::RegisterContextMenuKeyEvent(
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

RefPtr<PipelineContext> ViewAbstractModelStatic::GetSheetContext(NG::SheetStyle& sheetStyle)
{
    RefPtr<PipelineContext> context;
    if (sheetStyle.instanceId.has_value()) {
        TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet uiContext id is: %{public}d", sheetStyle.instanceId.value());
        auto container = AceEngine::Get().GetContainer(sheetStyle.instanceId.value());
        CHECK_NULL_RETURN(container, nullptr);
        auto contextBase = container->GetPipelineContext();
        CHECK_NULL_RETURN(contextBase, nullptr);
        context = AceType::DynamicCast<PipelineContext>(contextBase);
    } else {
        context = PipelineContext::GetCurrentContextSafelyWithCheck();
    }
    return context;
}

void ViewAbstractModelStatic::BindSheet(FrameNode* frameNode, bool isShow,
    std::function<void(const std::string&)>&& callback,
    std::function<void()>&& buildFunc, std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle,
    std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
    std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
    std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
    std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
    std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack)
{
    auto targetNode = AceType::Claim(frameNode);
    CHECK_NULL_VOID(targetNode);
    auto instanceId = sheetStyle.instanceId.has_value() && !sheetStyle.showInSubWindow.value_or(false) ?
        sheetStyle.instanceId.value() : Container::CurrentId();
    auto buildNodeFunc = [buildFunc](int32_t id) -> RefPtr<UINode> {
        NG::ScopedViewStackProcessor builderViewStackProcess(id);
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        return customNode;
    };
    auto buildTitleNodeFunc = [titleBuildFunc, instanceId]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(titleBuildFunc, nullptr);
        NG::ScopedViewStackProcessor builderViewStackProcess(instanceId);
        titleBuildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        return customNode;
    };
    auto context = GetSheetContext(sheetStyle);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    if (sheetStyle.showInPage.value_or(false)) {
        overlayManager = SheetManager::FindPageNodeOverlay(targetNode, isShow);
    }
    CHECK_NULL_VOID(overlayManager);

    // delete Sheet when target node destroy
    SheetManager::GetInstance().RegisterDestroyCallback(targetNode, sheetStyle, instanceId);

    if (sheetStyle.showInSubWindow.value_or(false)) {
        if (isShow) {
            SubwindowManager::GetInstance()->ShowBindSheetNG(isShow, std::move(callback), std::move(buildNodeFunc),
                std::move(buildTitleNodeFunc), sheetStyle, std::move(onAppear), std::move(onDisappear),
                std::move(shouldDismiss), std::move(onWillDismiss),
                std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
                std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
                std::move(sheetSpringBack), targetNode);
        } else {
            SheetManager::GetInstance().CloseSheetInSubWindow(SheetKey(targetNode->GetId()));
        }
        return;
    }

    overlayManager->BindSheet(isShow, std::move(callback), std::move(buildNodeFunc), std::move(buildTitleNodeFunc),
        sheetStyle, std::move(onAppear), std::move(onDisappear), std::move(shouldDismiss), std::move(onWillDismiss),
        std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
        std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
        std::move(sheetSpringBack), targetNode);
}

void ViewAbstractModelStatic::SetBackgroundEffect(FrameNode* frameNode,
    const std::optional<EffectOption>& effectOption, const std::optional<SysOptions>& sysOptions)
{
    FREE_NODE_CHECK(frameNode, SetBackgroundEffect, frameNode, effectOption, sysOptions);
    ViewAbstract::SetBackgroundEffect(frameNode, effectOption.value_or(EffectOption()),
        sysOptions.value_or(DEFAULT_SYS_OPTIONS));
}

void ViewAbstractModelStatic::SetTranslate(FrameNode* frameNode, const NG::TranslateOptions& value)
{
    FREE_NODE_CHECK(frameNode, SetTranslate, frameNode, value);
    ViewAbstract::SetTranslate(frameNode, value);
}

void ViewAbstractModelStatic::SetGeometryTransition(FrameNode* frameNode, const std::string& id,
    bool followWithoutTransition, bool doRegisterSharedTransition)
{
    FREE_NODE_CHECK(frameNode, SetGeometryTransition,
        frameNode, id, followWithoutTransition, doRegisterSharedTransition);
    ViewAbstract::SetGeometryTransition(frameNode, id, followWithoutTransition, doRegisterSharedTransition);
}

bool ViewAbstractModelStatic::CreatePropertyAnimation(FrameNode* frameNode, AnimationPropertyType property,
    const std::vector<float>& startValue, const std::vector<float>& endValue, const AnimationOption& option)
{
    CHECK_NULL_RETURN(frameNode, false);
    return ViewAbstract::CreatePropertyAnimation(frameNode, property, startValue, endValue, option);
}

bool ViewAbstractModelStatic::CancelPropertyAnimations(
    FrameNode* frameNode, const std::vector<AnimationPropertyType>& properties)
{
    CHECK_NULL_RETURN(frameNode, false);
    return ViewAbstract::CancelPropertyAnimations(frameNode, properties);
}

std::vector<float> ViewAbstractModelStatic::GetRenderNodePropertyValue(
    FrameNode* frameNode, AnimationPropertyType property)
{
    CHECK_NULL_RETURN(frameNode, {});
    return ViewAbstract::GetRenderNodePropertyValue(frameNode, property);
}

void ViewAbstractModelStatic::DismissSheetStatic()
{
    auto sheetId = SheetManager::GetInstance().GetDismissSheet();
    auto sheet = FrameNode::GetFrameNode(V2::SHEET_PAGE_TAG, sheetId);
    CHECK_NULL_VOID(sheet);
    auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OverlayDismissSheet();
}

void ViewAbstractModelStatic::DismissContentCoverStatic()
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->DismissContentCover();
}

void ViewAbstractModelStatic::SheetSpringBackStatic()
{
    auto sheetId = SheetManager::GetInstance().GetDismissSheet();
    auto sheet = FrameNode::GetFrameNode(V2::SHEET_PAGE_TAG, sheetId);
    CHECK_NULL_VOID(sheet);
    auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->OverlaySheetSpringBack();
}

void ViewAbstractModelStatic::SetAccessibilityTextHint(FrameNode* frameNode, const std::string& text)
{
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityTextHint(text);
}

void ViewAbstractModelStatic::SetAccessibilityVirtualNode(FrameNode* frameNode,
    std::function<RefPtr<NG::UINode>()>&& buildFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    auto SetAccessibilityVirtualNodeTask = []
        (const WeakPtr<FrameNode>& weak, const std::function<RefPtr<NG::UINode>()>& buildFunc) {
            auto node = weak.Upgrade();
            CHECK_NULL_VOID(node);
            auto accessibilityProperty = node->GetAccessibilityProperty<AccessibilityProperty>();
            CHECK_NULL_VOID(accessibilityProperty);
            if (buildFunc == nullptr) {
                node->HasAccessibilityVirtualNode(false);
                accessibilityProperty->SaveAccessibilityVirtualNode(nullptr);
                return;
            }
            auto virtualNode = buildFunc();
            if (AceType::InstanceOf<NG::DetachedFreeRootProxyNode>(virtualNode)) {
                virtualNode = virtualNode->GetFirstChild();
            }
            auto virtualFrameNode = AceType::DynamicCast<NG::FrameNode>(virtualNode);
            CHECK_NULL_VOID(virtualFrameNode);
            virtualFrameNode->SetAccessibilityNodeVirtual();
            virtualFrameNode->SetAccessibilityVirtualNodeParent(node);
            virtualFrameNode->SetFirstAccessibilityVirtualNode();
            node->HasAccessibilityVirtualNode(true);
            accessibilityProperty->SaveAccessibilityVirtualNode(virtualNode);
    };
    auto SetAccessibilityVirtualNodeMultiThread = [weakNode, SetAccessibilityVirtualNodeTask]
        (const std::function<RefPtr<NG::UINode>()>& buildFunc) {
            auto frameNodeRef = weakNode.Upgrade();
            CHECK_NULL_VOID(frameNodeRef);
            frameNodeRef->PostAfterAttachMainTreeTask([weakNode, buildFunc, SetAccessibilityVirtualNodeTask] {
                SetAccessibilityVirtualNodeTask(weakNode, buildFunc);
            });
    };
    FREE_NODE_CHECK(frameNode, SetAccessibilityVirtualNode, buildFunc);
    SetAccessibilityVirtualNodeTask(weakNode, buildFunc);
}

void ViewAbstractModelStatic::SetAccessibilityDefaultFocus(FrameNode* frameNode, bool isFocus)
{
    CHECK_NULL_VOID(frameNode);
    auto weakNode = AceType::WeakClaim(frameNode);
    auto AddToFocusList = [](const WeakPtr<FrameNode>& weak, bool focus) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        auto pipeline = node->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto accessibilityManager = pipeline->GetAccessibilityManager();
        CHECK_NULL_VOID(accessibilityManager);
        accessibilityManager->AddFrameNodeToDefaultFocusList(node, focus);
    };
    auto SetAccessibilityDefaultFocusMultiThread = [weakNode, AddToFocusList](bool isFocus) {
        auto frameNodeRef = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNodeRef);
        frameNodeRef->PostAfterAttachMainTreeTask([weakNode, isFocus, AddToFocusList] {
            AddToFocusList(weakNode, isFocus);
        });
    };
    FREE_NODE_CHECK(frameNode, SetAccessibilityDefaultFocus, isFocus);
    AddToFocusList(weakNode, isFocus);
}

void ViewAbstractModelStatic::SetAccessibilityUseSamePage(FrameNode* frameNode, const std::string& pageMode)
{
    CHECK_NULL_VOID(frameNode);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    if (pageMode == accessibilityProperty->GetAccessibilitySamePage()) {
        return;
    }
    accessibilityProperty->SetAccessibilitySamePage(pageMode);

    auto weakNode = AceType::WeakClaim(frameNode);
    auto SendPageMode = [](const WeakPtr<FrameNode>& weak, const std::string& pageMode) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
#ifdef WINDOW_SCENE_SUPPORTED
        auto pipeline = node->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto uiExtManager = pipeline->GetUIExtensionManager();
        CHECK_NULL_VOID(uiExtManager);
        uiExtManager->SendPageModeToProvider(node->GetId(), pageMode);
#endif
    };
    auto SetAccessibilityUseSamePageMultiThread = [weakNode, SendPageMode](const std::string& pageMode) {
        auto frameNodeRef = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNodeRef);
        frameNodeRef->PostAfterAttachMainTreeTask([weakNode, &pageMode, SendPageMode] {
            SendPageMode(weakNode, pageMode);
        });
    };
    FREE_NODE_CHECK(frameNode, SetAccessibilityUseSamePage, pageMode);
    SendPageMode(weakNode, pageMode);
}

void ViewAbstractModelStatic::DisableOnAccessibilityHover(FrameNode* frameNode)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnAccessibilityHover();
}

void ViewAbstractModelStatic::SetOnAccessibilityHover(FrameNode* frameNode,
    OnAccessibilityHoverFunc &&onAccessibilityHoverEventFunc)
{
    auto eventHub = frameNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAccessibilityHoverEvent(std::move(onAccessibilityHoverEventFunc));
}

void ViewAbstractModelStatic::SetVisualEffect(FrameNode* frameNode,
    const OHOS::Rosen::VisualEffect* visualEffect)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(VisualEffect, visualEffect, frameNode);
}

void ViewAbstractModelStatic::SetBackgroundFilter(FrameNode* frameNode,
    const OHOS::Rosen::Filter* backgroundFilter)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundFilter, backgroundFilter, frameNode);
}

void ViewAbstractModelStatic::SetForegroundFilter(FrameNode* frameNode,
    const OHOS::Rosen::Filter* foregroundFilter)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundFilter, foregroundFilter, frameNode);
}

void ViewAbstractModelStatic::SetCompositingFilter(FrameNode* frameNode,
    const OHOS::Rosen::Filter* compositingFilter)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(CompositingFilter, compositingFilter, frameNode);
}

void ViewAbstractModelStatic::SetBrightnessBlender(FrameNode* frameNode,
    const OHOS::Rosen::BrightnessBlender* brightnessBlender)
{
    // CHECK_NULL_VOID(frameNode);
    // ACE_UPDATE_NODE_RENDER_CONTEXT(BrightnessBlender, brightnessBlender, frameNode);
}

void ViewAbstractModelStatic::SetBloom(FrameNode *frameNode, const std::optional<float>& value,
    const RefPtr<ThemeConstants>& themeConstants)
{
    CHECK_NULL_VOID(themeConstants);
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ViewAbstract::SetBloom(frameNode, *value);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, Bloom, frameNode);
    }
    double bloomRadius = themeConstants->GetDoubleByName(BLOOM_RADIUS_SYS_RES_NAME);
    Color bloomColor = themeConstants->GetColorByName(BLOOM_COLOR_SYS_RES_NAME);
    Shadow shadow;
    shadow.SetBlurRadius(value.value_or(0.0f) * bloomRadius);
    shadow.SetColor(bloomColor);
    std::vector<Shadow> shadows { shadow };
    ViewAbstractModelStatic::SetBackShadow(frameNode, shadows);
}

void ViewAbstractModelStatic::SetIlluminatedBorderWidth(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetIlluminatedBorderWidth(frameNode, value);
}

void ViewAbstractModelStatic::SetLightIlluminated(FrameNode *frameNode, const std::optional<uint32_t>& value,
    const RefPtr<ThemeConstants>& themeConstants)
{
    CHECK_NULL_VOID(themeConstants);
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ViewAbstract::SetLightIlluminated(frameNode, *value);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, LightIlluminated, frameNode);
    }
    auto illuminatedBorderWidth = themeConstants->GetDimensionByName(ILLUMINATED_BORDER_WIDTH_SYS_RES_NAME);
    ViewAbstractModelStatic::SetIlluminatedBorderWidth(frameNode, illuminatedBorderWidth);
}


void ViewAbstractModelStatic::SetBackShadow(FrameNode *frameNode, const std::vector<Shadow>& shadows)
{
    if (!shadows.empty()) {
        ViewAbstract::SetBackShadow(frameNode, shadows[0]);
    }
}

void ViewAbstractModelStatic::SetLightPosition(FrameNode* frameNode, const std::optional<CalcDimension>& positionX,
    const std::optional<CalcDimension>& positionY, const std::optional<CalcDimension>& positionZ)
{
    CHECK_NULL_VOID(frameNode);
    if (positionX && positionY && positionZ) {
        ViewAbstract::SetLightPosition(frameNode, *positionX, *positionY, *positionZ);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, LightPosition, frameNode);
    }
}

void ViewAbstractModelStatic::SetLightIntensity(FrameNode* frameNode, const std::optional<float>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ViewAbstract::SetLightIntensity(frameNode, *value);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, LightIntensity, frameNode);
    }
}

void ViewAbstractModelStatic::SetLightColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ViewAbstract::SetLightColor(frameNode, *value);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, LightColor, frameNode);
    }
}

void ViewAbstractModelStatic::BindBackground(FrameNode* frameNode,
    std::function<RefPtr<UINode>()>&& buildFunc, const std::optional<Alignment>& align)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetBackgroundFunction(std::move(buildFunc));
    if (align.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundAlign, align.value(), frameNode);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, BackgroundAlign, frameNode);
    }
}

void ViewAbstractModelStatic::ResetBackground(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(IsTransitionBackground, true, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BuilderBackgroundFlag, false, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundAlign, Alignment::CENTER, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        LayoutProperty, BackgroundIgnoresLayoutSafeAreaEdges, LAYOUT_SAFE_AREA_EDGE_ALL, frameNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("customBackgroundColor");
    ACE_UPDATE_NODE_RENDER_CONTEXT(CustomBackgroundColor, Color::TRANSPARENT, frameNode);
}

void ViewAbstractModelStatic::SetFlexGrow(FrameNode* frameNode, float value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFlexGrow(frameNode, value);
}

void ViewAbstractModelStatic::SetFlexShrink(FrameNode* frameNode, float value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFlexShrink(frameNode, value);
}

void ViewAbstractModelStatic::ResetFlexShrink(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetFlexShrink(frameNode);
}

void ViewAbstractModelStatic::SetFlexBasis(FrameNode* frameNode, const std::optional<Dimension>& optValue)
{
    CHECK_NULL_VOID(frameNode);
    if (optValue.has_value()) {
        Dimension value = optValue.value();
        // flexbasis don't support percent case.
        if (value.Unit() == DimensionUnit::PERCENT) {
            value.SetUnit(DimensionUnit::AUTO);
        }
        ViewAbstract::SetFlexBasis(frameNode, value);
    } else {
        ViewAbstract::SetFlexBasis(frameNode, Dimension(0));
    }
}

void ViewAbstractModelStatic::SetPadding(FrameNode* frameNode, const std::optional<PaddingProperty>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ViewAbstract::SetPadding(frameNode, ConstraintPaddingPropertyNonNegative(value.value()));
    } else {
        PaddingProperty padding;
        padding.SetEdges(CalcLength(0.0));
        ViewAbstract::SetPadding(frameNode, padding);
    }
}

void ViewAbstractModelStatic::SetMargin(FrameNode* frameNode, const std::optional<PaddingProperty>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ViewAbstract::SetMargin(frameNode, value.value());
    } else {
        PaddingProperty padding;
        padding.SetEdges(CalcLength(0.0));
        ViewAbstract::SetMargin(frameNode, padding);
    }
}

void ViewAbstractModelStatic::SetAspectRatio(FrameNode* frameNode, float ratio)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetAspectRatio(frameNode, ratio);
}

void ViewAbstractModelStatic::ResetAspectRatio(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetAspectRatio(frameNode);
}

void ViewAbstractModelStatic::SetLayoutWeight(FrameNode* frameNode, float value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutWeight(frameNode, value);
}

void ViewAbstractModelStatic::SetAlignSelf(FrameNode* frameNode, FlexAlign value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetAlignSelf(frameNode, value);
}

void ViewAbstractModelStatic::SetLayoutGravity(FrameNode* frameNode, Alignment value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutGravity(frameNode, value);
}

void ViewAbstractModelStatic::SetLayoutDirection(FrameNode* frameNode, TextDirection value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLayoutDirection(frameNode, value);
}

void ViewAbstractModelStatic::SetBorderStyle(FrameNode *frameNode, const BorderStyleProperty& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBorderStyle(frameNode, value);
}

void ViewAbstractModelStatic::SetBorderWidth(FrameNode *frameNode, const BorderWidthProperty& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBorderWidth(frameNode, value);
}

void ViewAbstractModelStatic::SetBorderColor(FrameNode *frameNode, const BorderColorProperty& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBorderColor(frameNode, value);
}

void ViewAbstractModelStatic::SetBorderRadius(FrameNode *frameNode, const BorderRadiusProperty& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBorderRadius(frameNode, value);
}

void ViewAbstractModelStatic::SetRenderStrategy(FrameNode* frameNode, const RenderStrategy& type)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRenderStrategy(frameNode, type);
}

void ViewAbstractModelStatic::SetBorderImage(
    FrameNode* frameNode, const RefPtr<BorderImage>& borderImage, uint8_t bitset)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(borderImage);
    if (bitset & BorderImage::SOURCE_BIT) {
        ViewAbstractModelStatic::SetBorderImageSource(
            frameNode, borderImage->GetSrc(), borderImage->GetBundleName(), borderImage->GetModuleName());
    }
    if (bitset & BorderImage::OUTSET_BIT) {
        ViewAbstract::SetHasBorderImageOutset(frameNode, true);
    }
    if (bitset & BorderImage::SLICE_BIT) {
        ViewAbstract::SetHasBorderImageSlice(frameNode, true);
    }
    if (bitset & BorderImage::REPEAT_BIT) {
        ViewAbstract::SetHasBorderImageRepeat(frameNode, true);
    }
    if (bitset & BorderImage::WIDTH_BIT) {
        ViewAbstract::SetHasBorderImageWidth(frameNode, true);
    }
    ViewAbstract::SetBorderImage(frameNode, borderImage);
}

void ViewAbstractModelStatic::SetBorderImageSource(
    FrameNode* frameNode, const std::string& imageSrc, const std::string& bundleName, const std::string& moduleName)
{
    ImageSourceInfo imageSourceInfo(imageSrc, bundleName, moduleName);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderImageSource, imageSourceInfo, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BorderSourceFromImage, true, frameNode);
}

void ViewAbstractModelStatic::SetDashGap(FrameNode *frameNode, const BorderWidthProperty& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDashGap(frameNode, value);
}

void ViewAbstractModelStatic::SetDashWidth(FrameNode *frameNode, const BorderWidthProperty& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetDashWidth(frameNode, value);
}

void ViewAbstractModelStatic::SetAlign(FrameNode* frameNode, Alignment alignment)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetAlign(frameNode, alignment);
}

void ViewAbstractModelStatic::SetAlign(FrameNode* frameNode, std::string localizedAlignment)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetAlign(frameNode, localizedAlignment);
    ViewAbstract::SetIsMirrorable(frameNode, true);
}

void ViewAbstractModelStatic::SetPosition(FrameNode* frameNode, const OffsetT<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetPosition(frameNode, value);
}

void ViewAbstractModelStatic::SetPositionEdges(FrameNode* frameNode, const EdgesParam& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetPositionEdges(frameNode, value);
}

void ViewAbstractModelStatic::SetPositionLocalizedEdges(FrameNode* frameNode, bool needLocalized)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateNeedPositionLocalizedEdges(needLocalized);
}

void ViewAbstractModelStatic::SetTransform3DMatrix(FrameNode* frameNode, const Matrix4& matrix)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetTransform3DMatrix(frameNode, matrix);
}

void ViewAbstractModelStatic::SetMarkAnchorStart(FrameNode* frameNode, const std::optional<Dimension>& markAnchorStart)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (markAnchorStart.has_value()) {
        layoutProperty->UpdateMarkAnchorStart(markAnchorStart.value());
    } else {
        layoutProperty->ResetMarkAnchorStart();
    }
}

void ViewAbstractModelStatic::MarkAnchor(FrameNode* frameNode, const std::optional<OffsetT<Dimension>>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(Anchor, *value, frameNode);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, Anchor, frameNode);
    }
}

void ViewAbstractModelStatic::ResetMarkAnchorStart(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->ResetMarkAnchorStart();
}

void ViewAbstractModelStatic::SetOffset(FrameNode* frameNode, const OffsetT<Dimension>& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOffset(frameNode, value);
}

void ViewAbstractModelStatic::SetOffsetEdges(FrameNode* frameNode, const EdgesParam& value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOffsetEdges(frameNode, value);
}

void ViewAbstractModelStatic::SetOffsetLocalizedEdges(FrameNode* frameNode, bool needLocalized)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateNeedOffsetLocalizedEdges(needLocalized);
}

void ViewAbstractModelStatic::UpdateSafeAreaExpandOpts(FrameNode* frameNode, const SafeAreaExpandOpts& opts)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::UpdateSafeAreaExpandOpts(frameNode, opts);
}

void ViewAbstractModelStatic::UpdateIgnoreLayoutSafeAreaOpts(FrameNode* frameNode, const IgnoreLayoutSafeAreaOpts& opts)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::UpdateIgnoreLayoutSafeAreaOpts(frameNode, opts);
}

void ViewAbstractModelStatic::SetAlignRules(FrameNode* frameNode,
    const std::optional<std::map<AlignDirection, AlignRule>>& alignRules)
{
    CHECK_NULL_VOID(frameNode);
    if (alignRules.has_value()) {
        ViewAbstract::SetAlignRules(frameNode, alignRules.value());
    } else {
        ViewAbstract::ResetAlignRules(frameNode);
    }
}

void ViewAbstractModelStatic::SetBias(FrameNode* frameNode, const std::optional<BiasPair>& biasPair)
{
    CHECK_NULL_VOID(frameNode);
    if (biasPair.has_value()) {
        ViewAbstract::SetBias(frameNode, biasPair.value());
    } else {
        ViewAbstract::ResetBias(frameNode);
    }
}

void ViewAbstractModelStatic::SetBias(FrameNode* frameNode, const std::optional<float>& horisontal,
    const std::optional<float>& vertical)
{
    auto biasPair = BiasPair(DEFAULT_BIAS, DEFAULT_BIAS);
    if (horisontal.has_value()) {
        biasPair.first = horisontal.value();
    }
    if (vertical.has_value()) {
        biasPair.second = vertical.value();
    }
    ViewAbstract::SetBias(frameNode, biasPair);
}

void ViewAbstractModelStatic::SetKeyboardShortcut(FrameNode* frameNode, const std::string& value,
    const std::vector<ModifierKey>& keys, std::function<void()>&& onKeyboardShortcutAction)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto frameNodeRef = AceType::Claim<FrameNode>(frameNode);
    if (value.empty()) {
        eventHub->ClearSingleKeyboardShortcut();
        return;
    }
    auto key = eventManager->GetKeyboardShortcutKeys(keys);
    if ((key == 0 && value.length() == 1) || (key == 0 && !keys.empty() && value.length() > 1)) {
        return;
    }
    if (eventManager->IsSameKeyboardShortcutNode(value, key)) {
        return;
    }
    eventHub->SetKeyboardShortcut(value, key, onKeyboardShortcutAction);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeRef));
}

void ViewAbstractModelStatic::SetPixelRound(FrameNode* frameNode, uint16_t value)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetPixelRound(frameNode, value);
}

void ViewAbstractModelStatic::SetMaxWidth(FrameNode* frameNode, const CalcDimension& minWidth)
{
    if (minWidth.Unit() == DimensionUnit::CALC) {
        ViewAbstract::SetMaxWidth(frameNode, NG::CalcLength(minWidth.CalcValue()));
    } else {
        ViewAbstract::SetMaxWidth(frameNode, NG::CalcLength(minWidth));
    }
}

void ViewAbstractModelStatic::SetMaxHeight(FrameNode* frameNode, const CalcDimension& minHeight)
{
    if (minHeight.Unit() == DimensionUnit::CALC) {
        ViewAbstract::SetMaxHeight(frameNode, NG::CalcLength(minHeight.CalcValue()));
    } else {
        ViewAbstract::SetMaxHeight(frameNode, NG::CalcLength(minHeight));
    }
}

void ViewAbstractModelStatic::SetDisplayIndex(FrameNode* frameNode, int32_t value)
{
    ViewAbstract::SetDisplayIndex(frameNode, value);
}

void ViewAbstractModelStatic::SetBackgroundColor(FrameNode *frameNode, const std::optional<Color>& color)
{
    if (color) {
        ViewAbstract::SetBackgroundColor(frameNode, color.value());
    } else {
        ViewAbstract::SetBackgroundColor(frameNode, Color::TRANSPARENT);
    }
}

void ViewAbstractModelStatic::SetPivot(FrameNode* frameNode, const std::optional<DimensionOffset>& optValue)
{
    if (optValue.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(TransformCenter, optValue.value(), frameNode);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, TransformCenter, frameNode);
    }
}

void  ViewAbstractModelStatic::SetRotate(FrameNode* frameNode, const std::vector<std::optional<float>>& value)
{
    constexpr size_t requiredSize = 5;
    if (value.size() != requiredSize) {
        return;
    }
    NG::Vector5F rotateVec = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    const NG::Vector5F DEFAULT_ROTATE_VEC = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    constexpr int32_t indX = 0;
    constexpr int32_t indY = 1;
    constexpr int32_t indZ = 2;
    constexpr int32_t indA = 3;
    constexpr int32_t indP = 4;
    if (!value[indX] && !value[indY] && !value[indZ]) {
        rotateVec.z = 1.0f;
    } else {
        rotateVec.x = value[indX].has_value() ? value[indX].value() : DEFAULT_ROTATE_VEC.x;
        rotateVec.y = value[indY].has_value() ? value[indY].value() : DEFAULT_ROTATE_VEC.y;
        rotateVec.z = value[indZ].has_value() ? value[indZ].value() : DEFAULT_ROTATE_VEC.z;
    }
    rotateVec.w = value[indA].has_value() ? value[indA].value() : DEFAULT_ROTATE_VEC.w;
    rotateVec.v = value[indP].has_value() ? value[indP].value() : DEFAULT_ROTATE_VEC.v;
    ACE_UPDATE_NODE_RENDER_CONTEXT(TransformRotate, rotateVec, frameNode);
}

void  ViewAbstractModelStatic::SetRotateAngle(FrameNode* frameNode, const std::vector<std::optional<float>>& value)
{
    constexpr size_t requiredSize = 4;
    if (value.size() != requiredSize) {
        return;
    }
    NG::Vector4F rotateVec = { 0.0f, 0.0f, 0.0f, 0.0f };
    const NG::Vector4F DEFAULT_ROTATE_VEC = { 0.0f, 0.0f, 0.0f, 0.0f };
    constexpr int32_t indX = 0;
    constexpr int32_t indY = 1;
    constexpr int32_t indZ = 2;
    constexpr int32_t indP = 3;
    if (!value[indX] && !value[indY] && !value[indZ]) {
        rotateVec.z = 1.0f;
    } else {
        rotateVec.x = value[indX].has_value() ? value[indX].value() : DEFAULT_ROTATE_VEC.x;
        rotateVec.y = value[indY].has_value() ? value[indY].value() : DEFAULT_ROTATE_VEC.y;
        rotateVec.z = value[indZ].has_value() ? value[indZ].value() : DEFAULT_ROTATE_VEC.z;
    }
    rotateVec.w = value[indP].has_value() ? value[indP].value() : DEFAULT_ROTATE_VEC.w;
    ACE_UPDATE_NODE_RENDER_CONTEXT(TransformRotateAngle, rotateVec, frameNode);
}

void ViewAbstractModelStatic::SetBackdropBlur(FrameNode *frameNode, const std::optional<Dimension>& radius,
    const std::optional<BlurOption>& blurOption, const SysOptions& sysOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetBackgroundEffect().has_value()) {
            target->UpdateBackgroundEffect(std::nullopt);
        }
        target->UpdateBackBlur(radius.value_or(Dimension()), blurOption.value_or(BlurOption()), sysOptions);
        if (target->GetBackBlurStyle().has_value()) {
            target->UpdateBackBlurStyle(std::nullopt);
        }
    }
}

void ViewAbstractModelStatic::SetClipEdge(FrameNode* frameNode, std::optional<bool> isClip)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetClipShape().has_value()) {
            target->ResetClipShape();
            target->OnClipShapeUpdate(nullptr);
        }
        target->UpdateClipEdge(isClip.value_or(false));
    }
}

void ViewAbstractModelStatic::SetTransformMatrix(FrameNode* frameNode, const std::optional<Matrix4>& matrix)
{
    if (matrix.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(TransformMatrix, matrix.value(), frameNode);
    } else {
        const auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, TransformMatrix, frameNode);
    }
}

void ViewAbstractModelStatic::SetLinearGradientBlur(FrameNode *frameNode,
    const std::optional<NG::LinearGradientBlurPara>& blurPara)
{
    if (blurPara.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(LinearGradientBlur, blurPara.value(), frameNode);
    } else {
        const auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, LinearGradientBlur, frameNode);
    }
}

void ViewAbstractModelStatic::SetRenderFit(FrameNode* frameNode, const std::optional<RenderFit>& renderFit)
{
    if (renderFit.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(RenderFit, renderFit.value(), frameNode);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, RenderFit, frameNode);
    }
}
void ViewAbstractModelStatic::SetForegroundColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (color) {
        if (renderContext->GetForegroundColorStrategy().has_value()) {
            renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::NONE);
            renderContext->ResetForegroundColorStrategy();
        }
        renderContext->UpdateForegroundColor(color.value());
        renderContext->UpdateForegroundColorFlag(true);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, false, frameNode);
    }
}

void ViewAbstractModelStatic::SetForegroundColorStrategy(FrameNode* frameNode,
    const std::optional<ForegroundColorStrategy>& strategy)
{
    if (strategy) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorStrategy, strategy.value(), frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, false, frameNode);
    }
}

void ViewAbstractModelStatic::SetForegroundEffect(FrameNode* frameNode, const std::optional<float>& radius)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (radius) {
            target->UpdateForegroundEffect(*radius);
        } else {
            target->ResetForegroundEffect();
        }
    }
}

void ViewAbstractModelStatic::SetBlendMode(FrameNode* frameNode, const std::optional<BlendMode>& blendMode)
{
    ViewAbstract::SetBlendMode(frameNode, blendMode.value_or(BlendMode::NONE));
}

void ViewAbstractModelStatic::SetFocusBoxStyle(FrameNode* frameNode, const std::optional<NG::FocusBoxStyle>& style)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (!style.has_value()) {
        FocusBoxStyle paintStyle;
        focusHub->GetFocusBox().SetStyle(paintStyle);
        return;
    }
    auto paintStyle = style.value();
    if (paintStyle.strokeWidth.has_value() && paintStyle.strokeWidth.value().Unit() == DimensionUnit::PERCENT) {
        paintStyle.strokeWidth.value().SetUnit(DimensionUnit::FP);
    }
    if (paintStyle.margin.has_value() && paintStyle.margin.value().Unit() == DimensionUnit::PERCENT) {
        paintStyle.margin.value().SetUnit(DimensionUnit::FP);
    }
    focusHub->GetFocusBox().SetStyle(paintStyle);
}

void ViewAbstractModelStatic::SetFocusScopeId(FrameNode* frameNode, const std::optional<std::string>& focusScopeId,
    const std::optional<bool>& isGroup, const std::optional<bool>& arrowKeyStepOut)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    bool isGroupValue = isGroup.value_or(DEFAULT_FOCUS_IS_GROUP);
    bool arrowKeyStepOutValue = arrowKeyStepOut.value_or(DEFAULT_FOCUS_ARROW_KEY_STEP_OUT);
    focusHub->SetFocusScopeId(focusScopeId.value_or(""), isGroupValue, arrowKeyStepOutValue);
}

void ViewAbstractModelStatic::SetFocusScopePriority(
    FrameNode* frameNode, const std::optional<std::string>& focusScopeId, const std::optional<uint32_t>& focusPriority)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto proirity = focusPriority.value_or(static_cast<uint32_t>(FocusPriority::AUTO));
    focusHub->SetFocusScopePriority(focusScopeId.value_or(""), proirity);
}

void ViewAbstractModelStatic::SetGrayScale(FrameNode* frameNode, const std::optional<Dimension>& grayScale)
{
    if (grayScale.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(FrontGrayScale, grayScale.value(), frameNode);
    } else {
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, FrontGrayScale, frameNode);
    }
}

void ViewAbstractModelStatic::SetColorBlend(FrameNode* frameNode, const std::optional<Color>& colorBlend)
{
    if (colorBlend.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(FrontColorBlend, colorBlend.value(), frameNode);
    } else {
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, FrontColorBlend, frameNode);
    }
}

void ViewAbstractModelStatic::SetUseShadowBatching(FrameNode* frameNode, std::optional<bool> useShadowBatching)
{
    if (useShadowBatching.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(UseShadowBatching, useShadowBatching.value(), frameNode);
    } else {
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, UseShadowBatching, frameNode);
    }
}

void ViewAbstractModelStatic::SetUseEffect(
    FrameNode* frameNode, const std::optional<bool>& useEffectOpt, const std::optional<EffectType>& effectTypeOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto target = frameNode->GetRenderContext();
    CHECK_NULL_VOID(target);
    if (useEffectOpt) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(UseEffect, *useEffectOpt, frameNode);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(target, UseEffect, frameNode);
    }
    if (effectTypeOpt) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(UseEffectType, *effectTypeOpt, frameNode);
    } else {
        ACE_RESET_NODE_RENDER_CONTEXT(target, UseEffectType, frameNode);
    }
}

void ViewAbstractModelStatic::SetInvert(FrameNode* frameNode, const std::optional<InvertVariant>& invertOpt)
{
    if (invertOpt) {
        ViewAbstract::SetInvert(frameNode, invertOpt.value());
        return;
    }
    InvertVariant invert = 0.0f;
    ViewAbstract::SetInvert(frameNode, invert);
}

void ViewAbstractModelStatic::SetDrawModifier(FrameNode* frameNode, const RefPtr<NG::DrawModifier>& drawModifier)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDrawModifier(drawModifier);
}

void ViewAbstractModelStatic::SetFreeze(FrameNode* frameNode, std::optional<bool> freeze)
{
    ViewAbstract::SetFreeze(frameNode, freeze.value_or(false));
}

void ViewAbstractModelStatic::SetClickEffectLevel(FrameNode* frameNode,
    const std::optional<ClickEffectLevel>& level, std::optional<float> scaleValue)
{
    if (level.has_value() || scaleValue.has_value()) {
        ClickEffectInfo clickEffectInfo;
        if (level.has_value()) {
            clickEffectInfo.level = level.value();
        }
        if (scaleValue.has_value()) {
            clickEffectInfo.scaleNumber = scaleValue.value();
        }
        ACE_UPDATE_NODE_RENDER_CONTEXT(ClickEffectLevel, clickEffectInfo, frameNode);
    } else {
        ClickEffectInfo clickEffectInfo;
        clickEffectInfo.level = ClickEffectLevel::UNDEFINED;
        ACE_UPDATE_NODE_RENDER_CONTEXT(ClickEffectLevel, clickEffectInfo, frameNode);
    }
}

void ViewAbstractModelStatic::SetBrightness(FrameNode* frameNode,
    const std::optional<Dimension>& brightness)
{
    if (brightness.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(FrontBrightness, brightness.value(), frameNode);
    } else {
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, FrontBrightness, frameNode);
    }
}

void ViewAbstractModelStatic::SetContrast(FrameNode* frameNode,
    const std::optional<Dimension>& contrast)
{
    if (contrast.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(FrontContrast, contrast.value(), frameNode);
    } else {
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, FrontContrast, frameNode);
    }
}

void ViewAbstractModelStatic::SetSphericalEffect(FrameNode* frameNode, std::optional<double> radio)
{
    if (radio.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(SphericalEffect, radio.value(), frameNode);
    } else {
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, SphericalEffect, frameNode);
    }
}

void ViewAbstractModelStatic::SetLightUpEffect(FrameNode* frameNode, std::optional<double> radio)
{
    if (radio.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(LightUpEffect, radio.value(), frameNode);
    } else {
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, LightUpEffect, frameNode);
    }
}

void ViewAbstractModelStatic::SetPixelStretchEffect(FrameNode* frameNode,
    const std::optional<PixStretchEffectOption>& option)
{
    if (option.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(PixelStretchEffect, option.value(), frameNode);
    } else {
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, PixelStretchEffect, frameNode);
    }
}

void ViewAbstractModelStatic::SetBlendApplyType(
    FrameNode* frameNode, const std::optional<BlendApplyType>& blendApplyType)
{
    ViewAbstract::SetBlendApplyType(frameNode, blendApplyType.value_or(BlendApplyType::FAST));
}

void ViewAbstractModelStatic::SetPrivacySensitive(FrameNode* frameNode, const std::optional<bool>& flag)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(flag.value_or(false));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ViewAbstractModelStatic::SetOnTouchTestFunc(FrameNode* frameNode, NG::OnChildTouchTestFunc&& onChildTouchTest)
{
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnTouchTestFunc(std::move(onChildTouchTest));
}

void ViewAbstractModelStatic::SetOnGestureRecognizerJudgeBegin(
    FrameNode* frameNode, GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc,
    bool exposeInnerGestureFlag)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetExposeInnerGestureFlag(exposeInnerGestureFlag);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetOnGestureRecognizerJudgeBegin(std::move(gestureRecognizerJudgeFunc));
}

void ViewAbstractModelStatic::SetOuterBorderWidth(FrameNode* frameNode, const BorderWidthProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderWidth, value, frameNode);
}

void ViewAbstractModelStatic::SetOuterBorderRadius(FrameNode* frameNode, const BorderRadiusProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderRadius, value, frameNode);
}

void ViewAbstractModelStatic::SetOuterBorderColor(FrameNode* frameNode, const BorderColorProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderColor, value, frameNode);
}

void ViewAbstractModelStatic::SetOuterBorderStyle(FrameNode* frameNode, const BorderStyleProperty& value)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(OuterBorderStyle, value, frameNode);
}

void ViewAbstractModelStatic::SetAllowDrop(FrameNode* frameNode,
    const std::optional<std::set<std::string>>& allowDrop)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDisallowDropForcedly(!allowDrop.has_value());
    frameNode->SetAllowDrop(allowDrop.value_or(std::set<std::string>{}));
}

void ViewAbstractModelStatic::SetDragPreview(FrameNode* frameNode,
    const std::optional<DragDropInfo>& DragDropInfo)
{
    CHECK_NULL_VOID(frameNode);
    if (DragDropInfo.has_value()) {
        frameNode->SetDragPreview(DragDropInfo.value());
    } else {
        //Reset
        NG::DragDropInfo dragPreviewInfo;
        frameNode->SetDragPreview(dragPreviewInfo);
    }
}

void ViewAbstractModelStatic::SetBackgroundImage(FrameNode* frameNode,
    const std::optional<ImageSourceInfo>& src)
{
    if (src) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundImage, src.value(), frameNode);
    } else {
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->ResetBackgroundImage();
        ImageSourceInfo info;
        renderContext->OnBackgroundImageUpdate(info);
    }
}

void ViewAbstractModelStatic::SetBackgroundImageRepeat(FrameNode* frameNode,
    const std::optional<ImageRepeat>& imageRepeat)
{
    if (imageRepeat) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundImageRepeat, imageRepeat.value(), frameNode);
    } else {
        CHECK_NULL_VOID(frameNode);
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->ResetBackgroundImageRepeat();
        ImageRepeat repeat = ImageRepeat::NO_REPEAT;
        renderContext->OnBackgroundImageRepeatUpdate(repeat);
    }
}

void ViewAbstractModelStatic::SetBackgroundImageSyncMode(FrameNode* frameNode, bool syncMode)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundImageSyncMode, syncMode, frameNode);
}

void ViewAbstractModelStatic::SetSystemBarEffect(FrameNode* frameNode, bool systemBarEffect)
{
    ACE_UPDATE_NODE_RENDER_CONTEXT(SystemBarEffect, systemBarEffect, frameNode);
}

int32_t ViewAbstractModelStatic::GetMenuParam(NG::MenuParam& menuParam, const RefPtr<NG::UINode>& node)
{
    if (!node) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "Content of menu is null.");
        return ERROR_CODE_DIALOG_CONTENT_ERROR;
    }
    auto context = node->GetContextWithCheck();
    CHECK_NULL_RETURN(context, ERROR_CODE_INTERNAL_ERROR);
    auto overlayManager = context->GetOverlayManager();
    if (!overlayManager) {
        return ERROR_CODE_INTERNAL_ERROR;
    }
    auto menuNode = overlayManager->GetMenuNodeWithExistContent(node);
    if (!menuNode) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "GetMenuParam failed because cannot find menuNode.");
        return ERROR_CODE_DIALOG_CONTENT_NOT_FOUND;
    }
    auto wrapperPattern = AceType::DynamicCast<NG::MenuWrapperPattern>(menuNode->GetPattern());
    CHECK_NULL_RETURN(wrapperPattern, ERROR_CODE_INTERNAL_ERROR);
    auto menuProperties = wrapperPattern->GetMenuParam();
    menuParam = menuProperties;
    return ERROR_CODE_NO_ERROR;
}

void ViewAbstractModelStatic::SetClipShape(FrameNode* frameNode, const RefPtr<BasicShape>& basicShape)
{
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [basicShape, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            RefPtr<BasicShape>& basicShapeValue = const_cast<RefPtr<BasicShape>&>(basicShape);
            CHECK_NULL_VOID(basicShapeValue);
            basicShapeValue->ReloadResources();
            CHECK_NULL_VOID(frameNode);
            auto target = frameNode->GetRenderContext();
            CHECK_NULL_VOID(target);
            if (target->GetClipEdge().has_value()) {
                target->UpdateClipEdge(false);
            }
            target->UpdateClipShape(basicShapeValue);
            target->OnClipShapeUpdate(basicShapeValue);
            frameNode->MarkModifyDone();
            frameNode->MarkDirtyNode();
        };
        pattern->AddResObj("clipShape", resObj, std::move(updateFunc));
    }
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->GetClipEdge().has_value()) {
            target->UpdateClipEdge(false);
        }
        if (basicShape) {
            target->UpdateClipShape(basicShape);
        } else {
            target->ResetClipShape();
        }
    }
}

void ViewAbstractModelStatic::SetMask(FrameNode* frameNode, const RefPtr<BasicShape>& basicShape)
{
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [basicShape, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            RefPtr<BasicShape>& basicShapeValue = const_cast<RefPtr<BasicShape>&>(basicShape);
            CHECK_NULL_VOID(basicShapeValue);
            basicShapeValue->ReloadResources();
            auto target = frameNode->GetRenderContext();
            CHECK_NULL_VOID(target);
            if (target->HasProgressMask()) {
                target->ResetProgressMask();
                target->OnProgressMaskUpdate(nullptr);
            }
            target->UpdateClipMask(basicShapeValue);
            target->OnClipMaskUpdate(basicShapeValue);
        };
        pattern->AddResObj("maskShape", resObj, std::move(updateFunc));
    }
    auto target = frameNode->GetRenderContext();
    if (target) {
        if (target->HasProgressMask()) {
            target->ResetProgressMask();
            target->OnProgressMaskUpdate(nullptr);
        }
        if (basicShape) {
            target->UpdateClipMask(basicShape);
        } else {
            target->ResetClipMask();
        }
    }
}

void ViewAbstractModelStatic::SetBackgroundImagePosition(
    FrameNode* frameNode, BackgroundImagePosition& bgImgPosition, bool isReset)
{
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBackgroundImagePosition(frameNode, bgImgPosition, isReset);
    if (isReset) {
        auto renderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->ResetBackgroundImagePosition();
        renderContext->OnBackgroundImagePositionUpdate(bgImgPosition);
    }
}

void ViewAbstractModelStatic::ResetOverlay(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    OverlayOptions overlay;
    ViewAbstract::SetOverlay(frameNode, overlay);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, OverlayText, frameNode);
    frameNode->SetOverlayNode(nullptr);
    frameNode->MarkDirtyNode();
}
} // namespace OHOS::Ace::NG
