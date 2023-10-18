/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_SUBWINDOW_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_SUBWINDOW_OHOS_H

#include <unordered_map>

#include "event_handler.h"
#include "event_runner.h"
#include "resource_manager.h"
#include "wm/window.h"

#include "adapter/ohos/entrance/platform_event_callback.h"
#include "base/resource/asset_manager.h"
#include "base/subwindow/subwindow.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/thread/task_executor.h"
#include "core/common/ace_view.h"
#include "core/common/js_message_dispatcher.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/select_popup/select_popup_component.h"
#include "core/components/stack/stack_element.h"
#include "core/components/tween/tween_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Rosen {
class Window;
class WindowOption;
class RSUIDirector;
} // namespace OHOS::Rosen

namespace OHOS::Ace {

class SubwindowOhos : public Subwindow {
    DECLARE_ACE_TYPE(SubwindowOhos, Subwindow)

public:
    explicit SubwindowOhos(int32_t instanceId);
    ~SubwindowOhos() = default;

    void InitContainer() override;
    void ResizeWindow() override;
    NG::RectF GetRect() override;
    void ShowMenu(const RefPtr<Component>& newComponent) override;
    void ShowMenuNG(const RefPtr<NG::FrameNode> menuNode, int32_t targetId, const NG::OffsetF& offset) override;
    void HideMenuNG(const RefPtr<NG::FrameNode>& menu, int32_t targetId) override;
    void HideMenuNG(bool showPreviewAnimation, bool startDrag) override;
    void ShowPopup(const RefPtr<Component>& newComponent, bool disableTouchEvent = true) override;
    void ShowPopupNG(int32_t targetId, const NG::PopupInfo& popupInfo) override;
    void HidePopupNG(int32_t targetId) override;
    void GetPopupInfoNG(int32_t targetId, NG::PopupInfo& popupInfo) override;
    bool CancelPopup(const std::string& id) override;
    void CloseMenu() override;
    void ClearMenu() override;
    void ClearMenuNG(bool inWindow, bool showAnimation = false) override;
    RefPtr<NG::FrameNode> ShowDialogNG(const DialogProperties& dialogProps, std::function<void()>&& buildFunc) override;
    void HideSubWindowNG() override;
    bool GetShown() override
    {
        return isShowed_;
    }

    void SetHotAreas(const std::vector<Rect>& rects, int32_t overlayId) override;
    void ClearToast() override;
    void ShowToast(const std::string& message, int32_t duration, const std::string& bottom,
        const NG::ToastShowMode& showMode) override;
    void ShowDialog(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
        bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks) override;
    void ShowDialog(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks) override;
    void ShowActionMenu(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback) override;
    void CloseDialog(int32_t instanceId) override;
    const RefPtr<NG::OverlayManager> GetOverlayManager() override;

    int32_t GetChildContainerId() const override
    {
        return childContainerId_;
    }
    sptr<OHOS::Rosen::Window> GetDialogWindow() const
    {
        return dialogWindow_;
    }
    bool IsToastWindow() const
    {
        return isToastWindow_;
    }
    void SetIsToastWindow(bool isToastWindow)
    {
        isToastWindow_ = isToastWindow;
    }

    void UpdateAceView(int32_t width, int32_t height, float density, int32_t containerId);

    // Gets parent window's size and offset
    Rect GetParentWindowRect() const override;

    void RequestFocus() override;

private:
    RefPtr<StackElement> GetStack();
    void AddMenu(const RefPtr<Component>& newComponent);
    void ShowWindow(bool needFocus = true);
    void HideWindow();

    // Convert Rect to Rosen::Rect
    void RectConverter(const Rect& rect, Rosen::Rect& rosenRect);

    bool CreateEventRunner();
    void GetToastDialogWindowProperty(
        int32_t& width, int32_t& height, int32_t& posX, int32_t& posY, float& density) const;
    bool InitToastDialogWindow(int32_t width, int32_t height, int32_t posX, int32_t posY, bool isToast = false);
    bool InitToastDialogView(int32_t width, int32_t height, float density);
    void ShowToastForAbility(
        const std::string& message, int32_t duration, const std::string& bottom, const NG::ToastShowMode& showMode);
    void ShowToastForService(
        const std::string& message, int32_t duration, const std::string& bottom, const NG::ToastShowMode& showMode);
    void ShowDialogForAbility(const std::string& title, const std::string& message,
        const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks);
    void ShowDialogForService(const std::string& title, const std::string& message,
        const std::vector<ButtonInfo>& buttons, bool autoCancel, std::function<void(int32_t, int32_t)>&& callback,
        const std::set<std::string>& callbacks);
    void ShowDialogForAbility(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks);
    void ShowDialogForService(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
        std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks);
    void ShowActionMenuForAbility(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);
    void ShowActionMenuForService(const std::string& title, const std::vector<ButtonInfo>& button,
        std::function<void(int32_t, int32_t)>&& callback);

    RefPtr<PipelineBase> GetChildPipelineContext() const;

#ifdef ENABLE_DRAG_FRAMEWORK
    void HideFilter();
    void HidePixelMap(bool startDrag = false, double x = 0, double y = 0, bool showAnimation = true);
    void HideEventColumn();
#endif // ENABLE_DRAG_FRAMEWORK
    static int32_t id_;
    int32_t windowId_ = 0;
    int32_t parentContainerId_ = -1;
    int32_t childContainerId_ = -1;
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    sptr<OHOS::Rosen::Window> window_ = nullptr;
    RefPtr<SelectPopupComponent> popup_;
    std::unordered_map<int32_t, std::vector<Rosen::Rect>> hotAreasMap_;

    sptr<OHOS::Rosen::Window> dialogWindow_;
    std::shared_ptr<AppExecFwk::EventRunner> eventLoop_;
    std::shared_ptr<AppExecFwk::EventHandler> handler_;
    int32_t targetId_ = -1;
    bool isToastWindow_ = false;
    int32_t popupTargetId_ = -1;
    bool isShowed_ = false;
    sptr<OHOS::Rosen::Window> parentWindow_ = nullptr;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_SUBWINDOW_OHOS_H
