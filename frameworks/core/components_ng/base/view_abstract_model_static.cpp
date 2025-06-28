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

#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/base/view_abstract_model_static.h"
 
#include "core/common/ace_engine.h"
#include "core/common/vibrator/vibrator_utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view_static.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#endif
 
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t LONG_PRESS_DURATION = 800;
constexpr int32_t HOVER_IMAGE_LONG_PRESS_DURATION = 250;
constexpr int32_t HOVER_IMAGE_INTERRUPT_DURATION = 500;
constexpr char KEY_CONTEXT_MENU_HOVER[] = "ContextMenuHover";
constexpr char KEY_CONTEXT_MENU[] = "ContextMenu";
constexpr char KEY_MENU[] = "Menu";
} // namespace
 
void StartVibratorStatic(const MenuParam& menuParam, bool isMenu, const std::string& menuHapticFeedback)
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
 
NG::OffsetF UpdateMenuPostionStatic(const NG::OffsetF& menuPosition, const MenuParam& menuParam,
    const RefPtr<FrameNode>& targetNode)
{
    if (menuParam.isAnchorPosition) {
        NG::OffsetF targetNodePosition = targetNode->GetPositionToWindowWithTransform();
        return { menuParam.anchorPosition.GetX() + menuParam.positionOffset.GetX() +
                 targetNodePosition.GetX(),
                 menuParam.anchorPosition.GetY() + menuParam.positionOffset.GetY() +
                 targetNodePosition.GetY() };
    }
    return menuPosition;
}
 
static void BindGestureForMenuHoverScale(const RefPtr<FrameNode>& targetNode, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(targetNode);
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
 
    // bind touch evnet for hoverScaleInterruption
    auto targetId = targetNode->GetId();
    gestureHub->RegisterMenuOnTouch([targetId](const TouchEventInfo& info) {
        if (MenuViewStatic::GetMenuHoverScaleStatus(targetId) == MenuHoverScaleStatus::DISABLE) {
            return;
        }
 
        const auto& touches = info.GetTouches();
        CHECK_EQUAL_VOID(touches.empty(), true);
        auto touchType = touches.front().GetTouchType();
        if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
            auto hoverStatus = MenuViewStatic::GetMenuHoverScaleStatus(targetId);
            TAG_LOGI(AceLogTag::ACE_MENU, "target touch up or cancel, hoverStatus: %{public}d", hoverStatus);
            if (hoverStatus == MenuHoverScaleStatus::HOVER) {
                MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::INTERRUPT);
                SubwindowManager::GetInstance()->HideMenuNG();
            }
        }
    });
 
    auto gesture = AceType::MakeRefPtr<NG::LongPressGesture>(1, false, HOVER_IMAGE_INTERRUPT_DURATION, false, true);
    CHECK_NULL_VOID(gesture);
    gesture->SetTag(KEY_CONTEXT_MENU_HOVER);
    auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
    gesture->SetOnActionId([targetId](GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_MENU, "long press 500ms for menu hoverScale");
        MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::MENU_SHOW);
    });
    gestureHub->AddGesture(gesture);
}
 
static void BindGestureJudgeForMenuHoverScale(const RefPtr<FrameNode>& targetNode,
    std::function<void(const NG::OffsetF&)>& contextMenuShow, std::function<void()> startVibratorCall)
{
    CHECK_NULL_VOID(targetNode);
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
 
    auto targetId = targetNode->GetId();
    if (MenuViewStatic::GetMenuHoverScaleStatus(targetId) == MenuHoverScaleStatus::DISABLE) {
        gestureHub->SetOnGestureJudgeNativeBeginForMenu(
            [](const RefPtr<NG::GestureInfo>& gestureInfo,
                const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
                CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
                if (gestureInfo->GetType() == GestureTypeName::CONTEXT_MENU_HOVER) {
                    return GestureJudgeResult::CONTINUE;
                } else if (gestureInfo->GetTag() == KEY_CONTEXT_MENU_HOVER) {
                    return GestureJudgeResult::REJECT;
                }
                return GestureJudgeResult::CONTINUE;
            });
        return;
    }
 
    // bind GestureJudge for hoverScaleInterruption
    gestureHub->SetOnGestureJudgeNativeBeginForMenu(
        [targetId, showMenu = std::move(contextMenuShow), callVibrator = std::move(startVibratorCall)](
            const RefPtr<NG::GestureInfo>& gestureInfo,
            const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
            CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
            if (gestureInfo->GetType() == GestureTypeName::CONTEXT_MENU_HOVER) {
                TAG_LOGI(AceLogTag::ACE_OVERLAY, "Trigger longPress event for menu hoverScaleInterruption");
                MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::HOVER);
                NG::OffsetF position;
                if (info && !info->GetFingerList().empty()) {
                    auto finger = info->GetFingerList().front();
                    position = NG::OffsetF(finger.globalLocation_.GetX(), finger.globalLocation_.GetY());
                }
                // show menu for target hoverScale, during which the opacity of menu and preview is 0
                showMenu(position);
                return GestureJudgeResult::REJECT;
            }
 
            auto isDragGesture = gestureInfo->GetType() == GestureTypeName::DRAG;
            auto isContextMenuGesture = gestureInfo->GetTag() == KEY_CONTEXT_MENU_HOVER;
            if (isDragGesture || isContextMenuGesture) {
                auto hoverStatus = MenuViewStatic::GetMenuHoverScaleStatus(targetId);
                TAG_LOGI(AceLogTag::ACE_MENU,
                    "isDragGesture: %{public}d isContextMenuGesture: %{public}d hoverStatus: %{public}d", isDragGesture,
                    isContextMenuGesture, hoverStatus);
                if (hoverStatus == MenuHoverScaleStatus::HOVER) {
                    callVibrator();
                    MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::MENU_SHOW);
                }
            }
            return GestureJudgeResult::CONTINUE;
        });
}
 
static void BindGestureForContextMenu(const RefPtr<FrameNode>& targetNode, const MenuParam& menuParam,
    std::function<void(const NG::OffsetF&)> contextMenuShow)
{
    CHECK_NULL_VOID(targetNode);
    auto targetId = targetNode->GetId();
    auto isHoverInterrupt = menuParam.isShowHoverImage && menuParam.hoverScaleInterruption;
    if (!isHoverInterrupt) {
        MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::DISABLE);
    } else {
        MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::READY);
        BindGestureForMenuHoverScale(targetNode, menuParam);
    }
 
    auto startVibratorCall = [menuParam, weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode))]() {
        auto targetNode = weakTarget.Upgrade();
        CHECK_NULL_VOID(targetNode);
        auto pipelineContext = targetNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
        CHECK_NULL_VOID(menuTheme);
        StartVibratorStatic(menuParam, false, menuTheme->GetMenuHapticFeedback());
    };
 
    BindGestureJudgeForMenuHoverScale(targetNode, contextMenuShow, startVibratorCall);
}
 
static void BindContextMenuWithLongPress(const RefPtr<FrameNode>& targetNode, std::function<void()>& buildFunc,
    const MenuParam& menuParam, std::function<void()>& previewBuildFunc)
{
    CHECK_NULL_VOID(targetNode);
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetPreviewMode(menuParam.previewMode);
 
    auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
    auto contextMenuShow = [builder = buildFunc, weakTarget, menuParam, previewBuildFunc](NG::OffsetF globalPosition) {
        auto taskExecutor = Container::CurrentTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [builder, weakTarget, menuParam, previewBuildFunc, globalPosition]() mutable {
                TAG_LOGI(AceLogTag::ACE_MENU, "Execute longPress task for menu");
                auto targetNode = weakTarget.Upgrade();
                CHECK_NULL_VOID(targetNode);
                auto pipelineContext = targetNode->GetContext();
                CHECK_NULL_VOID(pipelineContext);
                auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
                CHECK_NULL_VOID(menuTheme);
                if (pipelineContext->IsDragging()) {
                    TAG_LOGI(AceLogTag::ACE_MENU, "TargetNode is dragging, menu is no longer show");
                    return;
                }
                if (menuParam.previewMode == MenuPreviewMode::IMAGE || menuParam.isShowHoverImage) {
                    auto context = targetNode->GetRenderContext();
                    CHECK_NULL_VOID(context);
                    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
                    CHECK_NULL_VOID(gestureHub);
                    auto pixelMap = context->GetThumbnailPixelMap();
                    gestureHub->SetPixelMap(pixelMap);
                }
                NG::OffsetF menuPosition { globalPosition.GetX() + menuParam.positionOffset.GetX(),
                    globalPosition.GetY() + menuParam.positionOffset.GetY() };
                if (!(menuParam.isShowHoverImage && menuParam.hoverScaleInterruption)) {
                    StartVibratorStatic(menuParam, false, menuTheme->GetMenuHapticFeedback());
                }
                NG::ViewAbstract::BindMenuWithCustomNode(std::move(builder), targetNode,
                    UpdateMenuPostionStatic(menuPosition, menuParam, targetNode), menuParam,
                    std::move(previewBuildFunc));
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUILongPressCreateCustomMenu");
    };
 
    // create or show menu on long press
    auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>([contextMenuShow](const GestureEvent& info) mutable {
        TAG_LOGI(AceLogTag::ACE_MENU, "Trigger longPress event for menu");
        contextMenuShow(NG::OffsetF(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY()));
    });
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true);
    auto longPressDuration = menuParam.isShowHoverImage ? HOVER_IMAGE_LONG_PRESS_DURATION : LONG_PRESS_DURATION;
    gestureHub->SetLongPressEvent(longPress, false, true, longPressDuration);
    gestureHub->SetLongPressEventType(GestureTypeName::CONTEXT_MENU_HOVER);
 
    BindGestureForContextMenu(targetNode, menuParam, contextMenuShow);
}
 
void UpdateIsShowStatusForMenuStatic(int32_t targetId, bool isShow)
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
 
void ViewAbstractModelStatic::BindContextMenu(const RefPtr<FrameNode>& targetNode, ResponseType type,
    std::function<void()>& buildFunc, const NG::MenuParam& menuParam, std::function<void()>& previewBuildFunc)
{
    ViewAbstractModelStatic::BindContextMenuStatic(
        targetNode, type, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
}
 
void ViewAbstractModelStatic::BindContextMenuStatic(const RefPtr<FrameNode>& targetNode, ResponseType type,
    std::function<void()>&& buildFunc, const NG::MenuParam& menuParam, std::function<void()>&& previewBuildFunc)
{
    CHECK_NULL_VOID(targetNode);
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
            OnMouseEventFunc event = [builderF = buildFunc, weakTarget, menuParam](MouseInfo& info) mutable {
                TAG_LOGI(AceLogTag::ACE_MENU, "Execute rightClick task for menu");
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
                        if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
                            std::function<void()> previewBuildFunc;
                            TAG_LOGI(AceLogTag::ACE_MENU, "Execute rightClick task for menu");
                            auto pipelineContext = targetNode->GetContext();
                            CHECK_NULL_VOID(pipelineContext);
                            auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
                            CHECK_NULL_VOID(menuTheme);
                            StartVibratorStatic(menuParam, false, menuTheme->GetMenuHapticFeedback());
                            NG::ViewAbstract::BindMenuWithCustomNode(std::move(builder), targetNode,
                                UpdateMenuPostionStatic(menuPosition, menuParam, targetNode), menuParam,
                                    std::move(previewBuildFunc));
                        }
                    }, TaskExecutor::TaskType::PLATFORM, "ArkUIRightClickCreateCustomMenu");
            };
            auto inputHub = targetNode->GetOrCreateInputEventHub();
            CHECK_NULL_VOID(inputHub);
            inputHub->BindContextMenu(std::move(event));
        } else if (type == ResponseType::LONG_PRESS) {
            BindContextMenuWithLongPress(targetNode, buildFunc, menuParam, previewBuildFunc);
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
        MenuViewStatic::RemoveMenuHoverScaleStatus(id);
    };
    targetNode->PushDestroyCallbackWithTag(destructor, KEY_CONTEXT_MENU);
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
 
void ViewAbstractModelStatic::BindContextMenuSingle(FrameNode* targetNode,
    std::function<void()>&& buildFunc, const MenuParam& menuParam, std::function<void()>&& previewBuildFunc)
{
    CHECK_NULL_VOID(targetNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true, targetNode);
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
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "menuNode already exist");
            auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
            CHECK_NULL_VOID(wrapperPattern);
            // If menu is shown or in show animation, set isShow to false will close menu. If menu is not shown or
            // in close animation, wrapperPattern->IsShow() is false, set isShow to false will not trigger close again.
            if (wrapperPattern->IsShow() && !menuParam.isShow) {
                TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu, tagetNode id %{public}d.", targetId);
                SubwindowManager::GetInstance()->HideMenuNG(menuNode, targetId);
                UpdateIsShowStatusForMenuStatic(targetId, false);
            } else if (!wrapperPattern->IsShow() && menuParam.isShow &&
                       wrapperPattern->GetIsShowFromUser() != menuParam.isShow) {
                // If click outside to close menu during show animation, and isShow is always true without changing,
                // then show new menu will result in an incorrect isShow state because onDisappear not be triggered.
                // The menu only show if isShow is manually set from false to true.
                CreateCustomMenuWithPreview(targetNode, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
                UpdateIsShowStatusForMenuStatic(targetId, true);
            }
        } else if (menuParam.isShow && buildFunc) {
            CreateCustomMenuWithPreview(targetNode, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
            UpdateIsShowStatusForMenuStatic(targetId, true);
        }
    } else {
        // first response for build subwindow and menu
        if (menuParam.isShow && buildFunc) {
            CreateCustomMenuWithPreview(targetNode, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
            UpdateIsShowStatusForMenuStatic(targetId, true);
        }
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
    StartVibratorStatic(menuParam, false, menuTheme->GetMenuHapticFeedback());
    NG::OffsetF menuPosition { menuParam.positionOffset.GetX(), menuParam.positionOffset.GetY() };
    NG::ViewAbstract::BindMenuWithCustomNode(std::move(buildFunc), refTargetNode,
        UpdateMenuPostionStatic(menuPosition, menuParam, refTargetNode), menuParam, std::move(previewBuildFunc));
}
 
void ViewAbstractModelStatic::BindDragWithContextMenuParams(FrameNode* targetNode, const NG::MenuParam& menuParam)
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
 
void ViewAbstractModelStatic::SetAccessibilityVirtualNode(FrameNode* frameNode,
    std::function<RefPtr<NG::UINode>()>&& buildFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto virtualNode = buildFunc();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto virtualFrameNode = AceType::DynamicCast<NG::FrameNode>(virtualNode);
    CHECK_NULL_VOID(virtualFrameNode);
    virtualFrameNode->SetAccessibilityNodeVirtual();
    virtualFrameNode->SetAccessibilityVirtualNodeParent(AceType::Claim(AceType::DynamicCast<NG::UINode>(frameNode)));
    virtualFrameNode->SetFirstAccessibilityVirtualNode();
    frameNode->HasAccessibilityVirtualNode(true);
    accessibilityProperty->SaveAccessibilityVirtualNode(virtualNode);
}
 
bool ViewAbstractModelStatic::CheckMenuIsShow(
    const MenuParam& menuParam, int32_t targetId, const RefPtr<FrameNode>& targetNode)
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
    if (wrapperPattern->IsShow() && menuParam.setShow && !menuParam.isShow && !wrapperPattern->GetIsOpenMenu()) {
        TAG_LOGI(AceLogTag::ACE_MENU, "execute hide menu.");
        overlayManager->HideMenu(menuNode, targetId, false, HideMenuType::IS_SHOW);
    }
    return true;
}
 
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
 
void ViewAbstractModelStatic::BindMenu(FrameNode* frameNode,
    std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    auto targetNode = AceType::Claim(frameNode);
    CHECK_NULL_VOID(targetNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true, frameNode);
    if (CheckMenuIsShow(menuParam, targetNode->GetId(), targetNode)) {
        TAG_LOGI(AceLogTag::ACE_MENU, "hide menu done %{public}d %{public}d.",
            menuParam.isShowInSubWindow, targetNode->GetId());
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
        targetNode->PushDestroyCallbackWithTag(destructor, KEY_MENU);
    }
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
 
} // namespace OHOS::Ace::NG