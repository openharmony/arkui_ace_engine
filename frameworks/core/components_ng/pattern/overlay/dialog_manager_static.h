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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_DIALOG_MANAGER_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_DIALOG_MANAGER_STATIC_H

#include "base/utils/singleton.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT DialogManagerStatic : public Singleton<DialogManagerStatic> {
    DECLARE_SINGLETON(DialogManagerStatic);
public:
    static void ShowInEmbeddedOverlay(std::function<void(RefPtr<NG::OverlayManager>)>&& task,
        const std::string& name, int32_t uniqueId);
    static RefPtr<OverlayManager> GetEmbeddedOverlay(int32_t uniqueId, const RefPtr<PipelineContext>& context);

    static RefPtr<OverlayManager> FindPageNodeOverlay(const RefPtr<FrameNode>& currentNode);

    static RefPtr<OverlayManager> GetEmbeddedOverlayWithNode(const RefPtr<UINode>& dialogNode);

    static RefPtr<UINode> GetDialogNodeByContentNode(const RefPtr<UINode>& currentNode);

    static void MainWindowOverlayStatic(std::function<void(RefPtr<NG::OverlayManager>)>&& task, const std::string& name,
        const RefPtr<NG::OverlayManager>& overlay, const int32_t containerId);
    static void ShowToastStatic(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback,
        const int32_t containerId);
    static void CloseToastStatic(const int32_t toastId, std::function<void(int32_t)>&& callback,
        const int32_t containerId);
    static void ShowDialogStatic(DialogProperties& dialogProps, std::function<void(int32_t, int32_t)>&& callback,
        const int32_t containerId);
    static void ShowActionMenuStatic(DialogProperties& dialogProps, std::function<void(int32_t, int32_t)>&& callback,
        const int32_t containerId);
    static void OpenCustomDialogStatic(DialogProperties& dialogProps, std::function<void(int32_t)>&& callback,
        const int32_t containerId);
    static void UpdateCustomDialogStatic(const WeakPtr<NG::UINode>& node, DialogProperties& dialogProps,
        std::function<void(int32_t)>&& callback);
    static void CloseCustomDialogStatic(const int32_t dialogId, const int32_t containerId);
    static void CloseCustomDialogStatic(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)> &&callback);
    static void RemoveCustomDialog(int32_t instanceId);

    void SetDismissDialogInfo(int32_t id, const std::string& name)
    {
        dismissDialogId_ = id;
        dialogTag_ = name;
    }

    int32_t GetDismissDialogId() const
    {
        return dismissDialogId_;
    }

    std::string& GetDialogTag()
    {
        return dialogTag_;
    }

private:
    int32_t dismissDialogId_ = 0;
    std::string dialogTag_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_DIALOG_MANAGER_STATIC_H
