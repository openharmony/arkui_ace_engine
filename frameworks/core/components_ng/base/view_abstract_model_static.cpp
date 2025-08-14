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
#include "core/components_ng/base/view_abstract_model_ng.h"
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
#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#endif

namespace OHOS::Ace::NG {
namespace {
const std::string BLOOM_RADIUS_SYS_RES_NAME = "sys.float.ohos_id_point_light_bloom_radius";
const std::string BLOOM_COLOR_SYS_RES_NAME = "sys.color.ohos_id_point_light_bloom_color";
const std::string ILLUMINATED_BORDER_WIDTH_SYS_RES_NAME = "sys.float.ohos_id_point_light_illuminated_border_width";
// constexpr int32_t HOVER_IMAGE_INTERRUPT_DURATION = 500;
// constexpr char KEY_CONTEXT_MENU_HOVER[] = "ContextMenuHover";
// constexpr char KEY_CONTEXT_MENU[] = "ContextMenu";
// constexpr char KEY_MENU[] = "Menu";

void StartVirator(const MenuParam& menuParam, bool isMenu, const std::string& menuHapticFeedback)
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
 
// NG::OffsetF UpdateMenuPostionStatic(const NG::OffsetF& menuPosition, const MenuParam& menuParam,
//     const RefPtr<FrameNode>& targetNode)
// {
//     if (menuParam.anchorPosition.has_value()) {
//         NG::OffsetF targetNodePosition = targetNode->GetPositionToWindowWithTransform();
//         return { menuParam.anchorPosition->GetX() + menuParam.positionOffset.GetX() +
//                  targetNodePosition.GetX(),
//                  menuParam.anchorPosition->GetY() + menuParam.positionOffset.GetY() +
//                  targetNodePosition.GetY() };
//     }
//     return menuPosition;
// }
 
// static void BindGestureForMenuHoverScale(const RefPtr<FrameNode>& targetNode, const MenuParam& menuParam)
// {
//     CHECK_NULL_VOID(targetNode);
//     auto gestureHub = targetNode->GetOrCreateGestureEventHub();
//     CHECK_NULL_VOID(gestureHub);
 
//     // bind touch evnet for hoverScaleInterruption
//     auto targetId = targetNode->GetId();
//     gestureHub->RegisterMenuOnTouch([targetId](const TouchEventInfo& info) {
//         if (MenuViewStatic::GetMenuHoverScaleStatus(targetId) == MenuHoverScaleStatus::DISABLE) {
//             return;
//         }
 
//         const auto& touches = info.GetTouches();
//         CHECK_EQUAL_VOID(touches.empty(), true);
//         auto touchType = touches.front().GetTouchType();
//         if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
//             auto hoverStatus = MenuViewStatic::GetMenuHoverScaleStatus(targetId);
//             TAG_LOGI(AceLogTag::ACE_MENU, "target touch up or cancel, hoverStatus: %{public}d", hoverStatus);
//             if (hoverStatus == MenuHoverScaleStatus::HOVER) {
//                 MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::INTERRUPT);
//                 SubwindowManager::GetInstance()->HideMenuNG();
//             }
//         }
//     });
 
//     auto gesture = AceType::MakeRefPtr<NG::LongPressGesture>(1, false, HOVER_IMAGE_INTERRUPT_DURATION, false, true);
//     CHECK_NULL_VOID(gesture);
//     gesture->SetTag(KEY_CONTEXT_MENU_HOVER);
//     auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
//     gesture->SetOnActionId([targetId](GestureEvent& info) {
//         TAG_LOGI(AceLogTag::ACE_MENU, "long press 500ms for menu hoverScale");
//         MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::MENU_SHOW);
//     });
//     gestureHub->AddGesture(gesture);
// }
 
// static void BindGestureJudgeForMenuHoverScale(const RefPtr<FrameNode>& targetNode,
//     std::function<void(const NG::OffsetF&)>& contextMenuShow, std::function<void()> startVibratorCall)
// {
//     CHECK_NULL_VOID(targetNode);
//     auto gestureHub = targetNode->GetOrCreateGestureEventHub();
//     CHECK_NULL_VOID(gestureHub);
 
//     auto targetId = targetNode->GetId();
//     if (MenuViewStatic::GetMenuHoverScaleStatus(targetId) == MenuHoverScaleStatus::DISABLE) {
//         gestureHub->SetOnGestureJudgeNativeBeginForMenu(
//             [](const RefPtr<NG::GestureInfo>& gestureInfo,
//                 const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
//                 CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
//                 if (gestureInfo->GetType() == GestureTypeName::CONTEXT_MENU_HOVER) {
//                     return GestureJudgeResult::CONTINUE;
//                 } else if (gestureInfo->GetTag() == KEY_CONTEXT_MENU_HOVER) {
//                     return GestureJudgeResult::REJECT;
//                 }
//                 return GestureJudgeResult::CONTINUE;
//             });
//         return;
//     }
 
//     // bind GestureJudge for hoverScaleInterruption
//     gestureHub->SetOnGestureJudgeNativeBeginForMenu(
//         [targetId, showMenu = std::move(contextMenuShow), callVibrator = std::move(startVibratorCall)](
//             const RefPtr<NG::GestureInfo>& gestureInfo,
//             const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
//             CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
//             if (gestureInfo->GetType() == GestureTypeName::CONTEXT_MENU_HOVER) {
//                 TAG_LOGI(AceLogTag::ACE_OVERLAY, "Trigger longPress event for menu hoverScaleInterruption");
//                 MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::HOVER);
//                 NG::OffsetF position;
//                 if (info && !info->GetFingerList().empty()) {
//                     auto finger = info->GetFingerList().front();
//                     position = NG::OffsetF(finger.globalLocation_.GetX(), finger.globalLocation_.GetY());
//                 }
//                 // show menu for target hoverScale, during which the opacity of menu and preview is 0
//                 showMenu(position);
//                 return GestureJudgeResult::REJECT;
//             }
 
//             auto isDragGesture = gestureInfo->GetType() == GestureTypeName::DRAG;
//             auto isContextMenuGesture = gestureInfo->GetTag() == KEY_CONTEXT_MENU_HOVER;
//             if (isDragGesture || isContextMenuGesture) {
//                 auto hoverStatus = MenuViewStatic::GetMenuHoverScaleStatus(targetId);
//                 TAG_LOGI(AceLogTag::ACE_MENU,
//                     "isDragGesture: %{public}d isContextMenuGesture: %{public}d hoverStatus: %{public}d", isDragGesture,
//                     isContextMenuGesture, hoverStatus);
//                 if (hoverStatus == MenuHoverScaleStatus::HOVER) {
//                     callVibrator();
//                     MenuViewStatic::SetMenuHoverScaleStatus(targetId, MenuHoverScaleStatus::MENU_SHOW);
//                 }
//             }
//             return GestureJudgeResult::CONTINUE;
//         });
// }

// void UpdateIsShowStatusForMenu(int32_t targetId, bool isShow)
// {
    // auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
    //     Container::CurrentId(), SubwindowType::TYPE_MENU);
    // CHECK_NULL_VOID(subwindow);
    // auto overlayManager = subwindow->GetOverlayManager();
    // CHECK_NULL_VOID(overlayManager);
    // auto menuNode = overlayManager->GetMenuNode(targetId);
    // CHECK_NULL_VOID(menuNode);
    // auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    // CHECK_NULL_VOID(wrapperPattern);
    // wrapperPattern->SetIsShowFromUser(isShow);
// }
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
            StartVirator(menuParam, true, menuTheme->GetMenuHapticFeedback());
            NG::ViewAbstract::BindMenuWithItems(std::move(params), targetNode, menuPosition, menuParam);
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
            StartVirator(menuParam, true, menuTheme->GetMenuHapticFeedback());
            std::function<void()> previewBuildFunc;
            NG::ViewAbstract::BindMenuWithCustomNode(
                std::move(builderFunc), targetNode, menuPosition, menuParam, std::move(previewBuildFunc));
        };
    } else {
        return;
    }
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    gestureHub->BindMenu(std::move(showMenu));
    BindMenuTouch(targetNode, gestureHub);
}

void ViewAbstractModelStatic::BindMenuTouch(FrameNode* targetNode, const RefPtr<GestureEventHub>& gestrueHub)
{
    // CHECK_NULL_VOID(targetNode);
    // auto weakTarget = AceType::WeakClaim(targetNode);
    // auto touchCallback = [weakTarget](const TouchEventInfo& info) {
    //     auto targetNode = weakTarget.Upgrade();
    //     CHECK_NULL_VOID(targetNode);
    //     const auto& touches = info.GetTouches();
    //     CHECK_EQUAL_VOID(touches.empty(), true);
    //     auto touchType = touches.front().GetTouchType();
    //     auto targetId = targetNode->GetId();
    //     auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId());
    //     CHECK_NULL_VOID(subwindow);
    //     auto childContainerId = subwindow->GetChildContainerId();
    //     auto childContainer = AceEngine::Get().GetContainer(childContainerId);
    //     CHECK_NULL_VOID(childContainer);
    //     auto subwindowPipline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
    //     CHECK_NULL_VOID(subwindowPipline);
    //     auto subwindowOverlay = subwindowPipline->GetOverlayManager();
    //     CHECK_NULL_VOID(subwindowOverlay);
    //     if (touchType == TouchType::DOWN) {
    //         auto wrapperNode = subwindowOverlay->GetMenuNode(targetId);
    //         CHECK_NULL_VOID(wrapperNode);
    //         auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    //         CHECK_NULL_VOID(wrapperPattern);
    //         if (wrapperPattern->IsShow() || wrapperPattern->GetMenuStatus() == MenuStatus::ON_HIDE_ANIMATION) {
    //             TAG_LOGI(AceLogTag::ACE_MENU, "skip menu show, target %{public}d", targetId);
    //             subwindowOverlay->SkipMenuShow(targetId);
    //         }
    //     } else if ((touchType == TouchType::UP || touchType == TouchType::CANCEL) &&
    //                subwindowOverlay->CheckSkipMenuShow(targetId)) {
    //         auto weakOverlay = AceType::WeakClaim(AceType::RawPtr(subwindowOverlay));
    //         auto taskExecutor = Container::CurrentTaskExecutor();
    //         CHECK_NULL_VOID(taskExecutor);
    //         TAG_LOGI(AceLogTag::ACE_MENU, "post resume menu show task, target %{public}d", targetId);
    //         taskExecutor->PostTask(
    //             [weakOverlay, targetId]() mutable {
    //                 TAG_LOGI(AceLogTag::ACE_MENU, "execute resume menu show, target %{public}d", targetId);
    //                 auto subwindowOverlay = weakOverlay.Upgrade();
    //                 CHECK_NULL_VOID(subwindowOverlay);
    //                 subwindowOverlay->ResumeMenuShow(targetId);
    //             }, TaskExecutor::TaskType::PLATFORM, "ArkUIResumeMenuShow");
    //     }
    // };
    // gestrueHub->RegisterMenuOnTouch(touchCallback);
}

bool ViewAbstractModelStatic::CheckMenuIsShow(
    const MenuParam& menuParam, int32_t targetId, const RefPtr<FrameNode>& targetNode)
{
    // RefPtr<NG::PipelineContext> pipeline = nullptr;
    // if (menuParam.isShowInSubWindow) {
    //     auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
    //         Container::CurrentId(), SubwindowType::TYPE_MENU);
    //     CHECK_NULL_RETURN(subwindow, false);
    //     auto childContainerId = subwindow->GetChildContainerId();
    //     auto childContainer = AceEngine::Get().GetContainer(childContainerId);
    //     CHECK_NULL_RETURN(childContainer, false);
    //     pipeline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
    // } else {
    //     CHECK_NULL_RETURN(targetNode, false);
    //     pipeline = targetNode->GetContextRefPtr();
    // }
    // CHECK_NULL_RETURN(pipeline, false);
    // auto overlayManager = pipeline->GetOverlayManager();
    // CHECK_NULL_RETURN(overlayManager, false);
    // auto menuNode = overlayManager->GetMenuNode(targetId);
    // CHECK_NULL_RETURN(menuNode, false);
    // auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    // CHECK_NULL_RETURN(wrapperPattern, false);
    // if (menuParam.hasTransitionEffect) {
    //     auto renderContext = menuNode->GetRenderContext();
    //     CHECK_NULL_RETURN(renderContext, false);
    //     renderContext->UpdateChainedTransition(menuParam.transition);
    // }
    // if (wrapperPattern->IsShow() && menuParam.setShow && !menuParam.isShow && !wrapperPattern->GetIsOpenMenu()) {
    //     TAG_LOGI(AceLogTag::ACE_MENU, "execute hide menu.");
    //     overlayManager->HideMenu(menuNode, targetId, false);
    // }
    return true;
}

void ViewAbstractModelStatic::BindMenu(FrameNode* frameNode,
    std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam)
{
    // auto targetNode = AceType::Claim(frameNode);
    // CHECK_NULL_VOID(targetNode);
    // auto targetId = targetNode->GetId();
    // ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true, frameNode);
    // if (CheckMenuIsShow(menuParam, targetId, targetNode)) {
    //     TAG_LOGI(AceLogTag::ACE_MENU, "hide menu done %{public}d %{public}d.", menuParam.isShowInSubWindow, targetId);
    // } else if (menuParam.isShow) {
    //     auto pipelineContext = targetNode->GetContext();
    //     CHECK_NULL_VOID(pipelineContext);
    //     auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    //     CHECK_NULL_VOID(menuTheme);
    //     StartVirator(menuParam, true, menuTheme->GetMenuHapticFeedback());
    //     if (!params.empty()) {
    //         NG::ViewAbstract::BindMenuWithItems(std::move(params), targetNode, menuParam.positionOffset, menuParam);
    //     } else if (buildFunc) {
    //         std::function<void()> previewBuildFunc;
    //         NG::ViewAbstract::BindMenuWithCustomNode(
    //             std::move(buildFunc), targetNode, menuParam.positionOffset, menuParam, std::move(previewBuildFunc));
    //     }
    // }
    // if (!menuParam.setShow) {
    //     BindMenuGesture(frameNode, std::move(params), std::move(buildFunc), menuParam);
    // }
    // // delete menu when target node destroy
    // auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    // CHECK_NULL_VOID(pipeline);
    // auto theme = pipeline->GetTheme<SelectTheme>();
    // CHECK_NULL_VOID(theme);
    // if (!theme->GetExpandDisplay() || !menuParam.isShowInSubWindow) {
    //     auto destructor = [id = targetNode->GetId(), params]() mutable {
    //         params.clear();
    //         auto pipeline = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    //         CHECK_NULL_VOID(pipeline);
    //         auto overlayManager = pipeline->GetOverlayManager();
    //         CHECK_NULL_VOID(overlayManager);
    //         overlayManager->DeleteMenu(id);
    //     };
    //     targetNode->PushDestroyCallbackWithTag(destructor, KEY_MENU);
    // } else {
    //     auto destructor = [id = targetNode->GetId(), containerId = Container::CurrentId(), params]() mutable {
    //         params.clear();
    //         auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(containerId, SubwindowType::TYPE_MENU);
    //         CHECK_NULL_VOID(subwindow);
    //         auto childContainerId = subwindow->GetChildContainerId();
    //         auto childContainer = AceEngine::Get().GetContainer(childContainerId);
    //         CHECK_NULL_VOID(childContainer);
    //         auto pipeline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
    //         CHECK_NULL_VOID(pipeline);
    //         auto overlayManager = pipeline->GetOverlayManager();
    //         CHECK_NULL_VOID(overlayManager);
    //         overlayManager->DeleteMenu(id);
    //     };
    //     targetNode->PushDestroyCallbackWithTag(destructor, KEY_MENU);
    // }
}

void ViewAbstractModelStatic::CreateCustomMenuWithPreview(FrameNode* targetNode,
    std::function<void()>&& buildFunc, const MenuParam& menuParam, std::function<void()>&& previewBuildFunc)
{
    // CHECK_NULL_VOID(targetNode);
    // if (menuParam.previewMode.value_or(MenuPreviewMode::NONE) == MenuPreviewMode::IMAGE) {
    //     auto context = targetNode->GetRenderContext();
    //     CHECK_NULL_VOID(context);
    //     auto gestureHub = targetNode->GetEventHub<EventHub>()->GetOrCreateGestureEventHub();
    //     CHECK_NULL_VOID(gestureHub);
    //     auto pixelMap = context->GetThumbnailPixelMap();
    //     gestureHub->SetPixelMap(pixelMap);
    // }
    // auto refTargetNode = AceType::Claim<NG::FrameNode>(targetNode);
    // auto pipelineContext = targetNode->GetContext();
    // CHECK_NULL_VOID(pipelineContext);
    // auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    // CHECK_NULL_VOID(menuTheme);
    // StartVirator(menuParam, false, menuTheme->GetMenuHapticFeedback());
    // NG::ViewAbstract::BindMenuWithCustomNode(
    //     std::move(buildFunc), refTargetNode, menuParam.positionOffset, menuParam, std::move(previewBuildFunc));
}

void ViewAbstractModelStatic::BindContextMenuSingle(FrameNode* targetNode,
    std::function<void()>&& buildFunc, const MenuParam& menuParam, std::function<void()>&& previewBuildFunc)
{
    // CHECK_NULL_VOID(targetNode);
    // ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true, targetNode);
    // auto targetId = targetNode->GetId();
    // TAG_LOGD(AceLogTag::ACE_OVERLAY, "target %{public}d menu isShow %{public}d", targetId, menuParam.isShow);
    // auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
    //     Container::CurrentId(), SubwindowType::TYPE_MENU);
    // if (subwindow) {
    //     auto childContainerId = subwindow->GetChildContainerId();
    //     auto childContainer = AceEngine::Get().GetContainer(childContainerId);
    //     CHECK_NULL_VOID(childContainer);
    //     auto pipeline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
    //     CHECK_NULL_VOID(pipeline);
    //     auto overlayManager = pipeline->GetOverlayManager();
    //     CHECK_NULL_VOID(overlayManager);
    //     auto menuNode = overlayManager->GetMenuNode(targetId);
    //     if (menuNode) {
    //         TAG_LOGI(AceLogTag::ACE_OVERLAY, "menuNode already exist");
    //         auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    //         CHECK_NULL_VOID(wrapperPattern);
    //         // If menu is shown or in show animation, set isShow to false will close menu. If menu is not shown or
    //         // in close animation, wrapperPattern->IsShow() is false, set isShow to false will not trigger close again.
    //         if (wrapperPattern->IsShow() && !menuParam.isShow) {
    //             TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu, tagetNode id %{public}d.", targetId);
    //             SubwindowManager::GetInstance()->HideMenuNG(menuNode, targetId);
    //             UpdateIsShowStatusForMenu(targetId, false);
    //         } else if (!wrapperPattern->IsShow() && menuParam.isShow &&
    //                    wrapperPattern->GetIsShowFromUser() != menuParam.isShow) {
    //             // If click outside to close menu during show animation, and isShow is always true without changing,
    //             // then show new menu will result in an incorrect isShow state because onDisappear not be triggered.
    //             // The menu only show if isShow is manually set from false to true.
    //             CreateCustomMenuWithPreview(targetNode, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
    //             UpdateIsShowStatusForMenu(targetId, true);
    //         }
    //     } else if (menuParam.isShow && buildFunc) {
    //         CreateCustomMenuWithPreview(targetNode, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
    //         UpdateIsShowStatusForMenu(targetId, true);
    //     }
    // } else {
    //     // first response for build subwindow and menu
    //     if (menuParam.isShow && buildFunc) {
    //         CreateCustomMenuWithPreview(targetNode, std::move(buildFunc), menuParam, std::move(previewBuildFunc));
    //         UpdateIsShowStatusForMenu(targetId, true);
    //     }
    // }
}

void ViewAbstractModelStatic::BindContextMenuStatic(const RefPtr<FrameNode>& targetNode, ResponseType type,
    std::function<void()>&& buildFunc, const NG::MenuParam& menuParam, std::function<void()>&& previewBuildFunc)
{
    // CHECK_NULL_VOID(targetNode);
    // auto targetId = targetNode->GetId();
    // auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId());
    // if (subwindow) {
    //     auto childContainerId = subwindow->GetChildContainerId();
    //     auto childContainer = AceEngine::Get().GetContainer(childContainerId);
    //     CHECK_NULL_VOID(childContainer);
    //     auto pipeline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
    //     CHECK_NULL_VOID(pipeline);
    //     auto overlayManager = pipeline->GetOverlayManager();
    //     CHECK_NULL_VOID(overlayManager);
    //     auto menuNode = overlayManager->GetMenuNode(targetId);
    //     if (menuNode) {
    //         TAG_LOGI(AceLogTag::ACE_OVERLAY, "menuNode already exist");
    //         auto menuWrapperPattern = menuNode->GetPattern<NG::MenuWrapperPattern>();
    //         CHECK_NULL_VOID(menuWrapperPattern);
    //         menuWrapperPattern->SetMenuTransitionEffect(menuNode, menuParam);
    //         menuWrapperPattern->RegisterMenuStateChangeCallback(menuParam.onStateChange);
    //     }
    // }
    // if (menuParam.contextMenuRegisterType == ContextMenuRegisterType::CUSTOM_TYPE) {
    //     BindContextMenuSingle(AceType::RawPtr(targetNode), std::move(buildFunc), menuParam,
    //         std::move(previewBuildFunc));
    // } else {
    //     auto hub = targetNode->GetOrCreateGestureEventHub();
    //     CHECK_NULL_VOID(hub);
    //     auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
    //     if (type == ResponseType::RIGHT_CLICK) {
    //         OnMouseEventFunc event = [builderF = buildFunc, weakTarget, menuParam](MouseInfo& info) mutable {
    //             TAG_LOGI(AceLogTag::ACE_MENU, "Execute rightClick task for menu");
    //             auto containerId = Container::CurrentId();
    //             auto taskExecutor = Container::CurrentTaskExecutor();
    //             CHECK_NULL_VOID(taskExecutor);
    //             if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
    //                 info.SetStopPropagation(true);
    //             }
    //             taskExecutor->PostTask(
    //                 [containerId, builder = builderF, weakTarget, menuParam, info]() mutable {
    //                     auto targetNode = weakTarget.Upgrade();
    //                     CHECK_NULL_VOID(targetNode);
    //                     NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
    //                         info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
    //                     if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
    //                         std::function<void()> previewBuildFunc;
    //                         NG::ViewAbstract::BindMenuWithCustomNode(
    //                             std::move(builder), targetNode, menuPosition, menuParam, std::move(previewBuildFunc));
    //                     }
    //                 },
    //                 TaskExecutor::TaskType::PLATFORM, "ArkUIRightClickCreateCustomMenu");
    //         };
    //         auto inputHub = targetNode->GetOrCreateInputEventHub();
    //         CHECK_NULL_VOID(inputHub);
    //         inputHub->BindContextMenu(std::move(event));
    //     } else if (type == ResponseType::LONG_PRESS) {
    //         auto gestureHub = targetNode->GetEventHub<EventHub>()->GetGestureEventHub();
    //         CHECK_NULL_VOID(gestureHub);
    //         gestureHub->SetPreviewMode(menuParam.previewMode.value_or(MenuPreviewMode::NONE));
    //         // create or show menu on long press
    //         auto event =
    //             [builderF = buildFunc, weakTarget, menuParam, previewBuildFunc](const GestureEvent& info) mutable {
    //             TAG_LOGI(AceLogTag::ACE_MENU, "Trigger longPress event for menu");
    //             auto containerId = Container::CurrentId();
    //             auto taskExecutor = Container::CurrentTaskExecutor();
    //             CHECK_NULL_VOID(taskExecutor);
    //             taskExecutor->PostTask(
    //                 [containerId, builder = builderF, weakTarget, menuParam, previewBuildFunc, info]() mutable {
    //                     TAG_LOGI(AceLogTag::ACE_MENU, "Execute longPress task for menu");
    //                     auto targetNode = weakTarget.Upgrade();
    //                     CHECK_NULL_VOID(targetNode);
    //                     auto pipelineContext = NG::PipelineContext::GetCurrentContextSafelyWithCheck();
    //                     CHECK_NULL_VOID(pipelineContext);
    //                     if (menuParam.previewMode == MenuPreviewMode::IMAGE || menuParam.isShowHoverImage) {
    //                         auto context = targetNode->GetRenderContext();
    //                         CHECK_NULL_VOID(context);
    //                         auto gestureHub = targetNode->GetEventHub<EventHub>()->GetGestureEventHub();
    //                         CHECK_NULL_VOID(gestureHub);
    //                         auto pixelMap = context->GetThumbnailPixelMap();
    //                         gestureHub->SetPixelMap(pixelMap);
    //                     }
    //                     NG::OffsetF menuPosition { info.GetGlobalLocation().GetX() + menuParam.positionOffset.GetX(),
    //                         info.GetGlobalLocation().GetY() + menuParam.positionOffset.GetY() };
    //                     NG::ViewAbstract::BindMenuWithCustomNode(
    //                         std::move(builder), targetNode, menuPosition, menuParam, std::move(previewBuildFunc));
    //                 },
    //                 TaskExecutor::TaskType::PLATFORM, "ArkUILongPressCreateCustomMenu");
    //         };
    //         auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(event));
    //         ACE_UPDATE_NODE_LAYOUT_PROPERTY(LayoutProperty, IsBindOverlay, true, targetNode);
    //         auto longPressDuration = menuParam.isShowHoverImage ? HOVER_IMAGE_LONG_PRESS_DURATION : LONG_PRESS_DURATION;
    //         hub->SetLongPressEvent(longPress, false, true, longPressDuration);
    //     } else {
    //         return;
    //     }
    //     RegisterContextMenuKeyEvent(targetNode, buildFunc, menuParam);
    // }

    // // delete menu when target node destroy
    // auto destructor = [id = targetNode->GetId(), containerId = Container::CurrentId()]() {
    //     auto subwindow = SubwindowManager::GetInstance()->GetSubwindow(containerId);
    //     CHECK_NULL_VOID(subwindow);
    //     auto childContainerId = subwindow->GetChildContainerId();
    //     auto childContainer = AceEngine::Get().GetContainer(childContainerId);
    //     CHECK_NULL_VOID(childContainer);
    //     auto pipeline = AceType::DynamicCast<NG::PipelineContext>(childContainer->GetPipelineContext());
    //     CHECK_NULL_VOID(pipeline);
    //     auto overlayManager = pipeline->GetOverlayManager();
    //     CHECK_NULL_VOID(overlayManager);
    //     overlayManager->DeleteMenu(id);
    // };
    // targetNode->PushDestroyCallbackWithTag(destructor, KEY_CONTEXT_MENU);
}

void ViewAbstractModelStatic::BindDragWithContextMenuParamsStatic(FrameNode* targetNode, const NG::MenuParam& menuParam)
{
    // CHECK_NULL_VOID(targetNode);

    // auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    // if (gestureHub) {
    //     if (menuParam.contextMenuRegisterType == ContextMenuRegisterType::CUSTOM_TYPE) {
    //         gestureHub->SetBindMenuStatus(
    //             true, menuParam.isShow, menuParam.previewMode.value_or(MenuPreviewMode::NONE));
    //     } else if (menuParam.menuBindType == MenuBindingType::LONG_PRESS) {
    //         gestureHub->SetBindMenuStatus(false, false, menuParam.previewMode.value_or(MenuPreviewMode::NONE));
    //     }
    //     gestureHub->SetPreviewMode(menuParam.previewMode.value_or(MenuPreviewMode::NONE));
    //     gestureHub->SetContextMenuShowStatus(menuParam.isShow);
    //     gestureHub->SetMenuBindingType(menuParam.menuBindType);
    //     // set menu preview scale to drag.
    //     if (menuParam.menuBindType != MenuBindingType::RIGHT_CLICK) {
    //         auto menuPreviewScale = LessOrEqual(menuParam.previewAnimationOptions.scaleTo, 0.0)
    //                                     ? DEFALUT_DRAG_PPIXELMAP_SCALE
    //                                     : menuParam.previewAnimationOptions.scaleTo;
    //         gestureHub->SetMenuPreviewScale(menuPreviewScale);
    //     }
    // } else {
    //     TAG_LOGW(AceLogTag::ACE_DRAG, "Can not get gestureEventHub!");
    // }
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
    auto buildNodeFunc = [buildFunc, instanceId]() -> RefPtr<UINode> {
        NG::ScopedViewStackProcessor builderViewStackProcess(instanceId);
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
            // SubwindowManager::GetInstance()->ShowBindSheetNG(isShow, std::move(callback), std::move(buildNodeFunc),
            //     std::move(buildTitleNodeFunc), sheetStyle, std::move(onAppear), std::move(onDisappear),
            //     std::move(shouldDismiss), std::move(onWillDismiss),
            //     std::move(onWillAppear), std::move(onWillDisappear), std::move(onHeightDidChange),
            //     std::move(onDetentsDidChange), std::move(onWidthDidChange), std::move(onTypeDidChange),
            //     std::move(sheetSpringBack), targetNode);
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
        // ACE_RESET_NODE_LAYOUT_PROPERTY(LayoutProperty, FlexBasis, frameNode);
    }
}

void ViewAbstractModelStatic::SetPadding(FrameNode* frameNode, const std::optional<PaddingProperty>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ViewAbstract::SetPadding(frameNode, value.value());
    } else {
        // ACE_RESET_NODE_LAYOUT_PROPERTY(LayoutProperty, Padding, frameNode);
    }
}

void ViewAbstractModelStatic::SetMargin(FrameNode* frameNode, const std::optional<PaddingProperty>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ViewAbstract::SetMargin(frameNode, value.value());
    } else {
        // ACE_RESET_NODE_LAYOUT_PROPERTY(LayoutProperty, Margin, frameNode);
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
    // auto biasPair = BiasPair(DEFAULT_BIAS, DEFAULT_BIAS);
    // if (horisontal.has_value()) {
    //     biasPair.first = horisontal.value();
    // }
    // if (vertical.has_value()) {
    //     biasPair.second = vertical.value();
    // }
    // ViewAbstract::SetBias(frameNode, biasPair);
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
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, BackgroundColor, frameNode);
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
    // CHECK_NULL_VOID(frameNode);
    // NG::Vector5F rotateVec = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    // int32_t indX = 0;
    // int32_t indY = 1;
    // int32_t indZ = 2;
    // int32_t indA = 3;
    // int32_t indP = 4;
    // rotateVec.x = (value.size() > static_cast<uint32_t>(indX) && value[indX].has_value()) ? value[indX].value()
    //                                                                                       : DEFAULT_ROTATE_VEC.x;
    // rotateVec.y = (value.size() > static_cast<uint32_t>(indY) && value[indY].has_value()) ? value[indY].value()
    //                                                                                       : DEFAULT_ROTATE_VEC.y;
    // rotateVec.z = (value.size() > static_cast<uint32_t>(indZ) && value[indZ].has_value()) ? value[indZ].value()
    //                                                                                       : DEFAULT_ROTATE_VEC.z;
    // rotateVec.w = (value.size() > static_cast<uint32_t>(indA) && value[indA].has_value()) ? value[indA].value()
    //                                                                                       : DEFAULT_ROTATE_VEC.w;
    // rotateVec.v = (value.size() > static_cast<uint32_t>(indP) && value[indP].has_value()) ? value[indP].value()
    //                                                                                       : DEFAULT_ROTATE_VEC.v;
    // ACE_UPDATE_NODE_RENDER_CONTEXT(TransformRotate, rotateVec, frameNode);
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
    if (blendMode.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackBlendMode, blendMode.value(), frameNode);
    } else {
        const auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, BackBlendMode, frameNode);
    }
}

void ViewAbstractModelStatic::SetFocusBoxStyle(FrameNode* frameNode, const std::optional<NG::FocusBoxStyle>& style)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (!style.has_value()) {
        return;
    }
    focusHub->GetFocusBox().SetStyle(style.value());
}

void ViewAbstractModelStatic::SetFocusScopeId(FrameNode* frameNode, const std::string& focusScopeId,
    const std::optional<bool>& isGroup, const std::optional<bool>& arrowKeyStepOut)
{
    // CHECK_NULL_VOID(frameNode);
    // auto focusHub = frameNode->GetOrCreateFocusHub();
    // CHECK_NULL_VOID(focusHub);
    // bool isGroupValue = isGroup.value_or(DEFAULT_FOCUS_IS_GROUP);
    // bool arrowKeyStepOutValue = arrowKeyStepOut.value_or(DEFAULT_FOCUS_ARROW_KEY_STEP_OUT);
    // focusHub->SetFocusScopeId(focusScopeId, isGroupValue, arrowKeyStepOutValue);
}

void ViewAbstractModelStatic::SetFocusScopePriority(
    FrameNode* frameNode, const std::string& focusScopeId, const std::optional<uint32_t>& focusPriority)
{
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto proirity = focusPriority.value_or(static_cast<uint32_t>(FocusPriority::AUTO));
    focusHub->SetFocusScopePriority(focusScopeId, proirity);
}

void ViewAbstractModelStatic::SetBlendApplyType(
    FrameNode* frameNode, const std::optional<BlendApplyType>& blendApplyType)
{
    if (blendApplyType) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackBlendApplyType, blendApplyType.value(), frameNode);
    } else {
        const auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, BackBlendApplyType, frameNode);
    }
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

void ViewAbstractModelStatic::SetLightUpEffect(FrameNode* frameNode, std::optional<double> radio)
{
    if (radio.has_value()) {
        ACE_UPDATE_NODE_RENDER_CONTEXT(LightUpEffect, radio.value(), frameNode);
    } else {
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, LightUpEffect, frameNode);
    }
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
        auto target = frameNode->GetRenderContext();
        ACE_RESET_NODE_RENDER_CONTEXT(target, ClickEffectLevel, frameNode);
    }
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
} // namespace OHOS::Ace::NG
