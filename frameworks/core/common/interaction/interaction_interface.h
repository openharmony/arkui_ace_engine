/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INTERACTION_INTERFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INTERACTION_INTERFACE_H

#include "base/memory/ace_type.h"
#include "core/common/interaction/interaction_data.h"

namespace OHOS::Rosen {
    class RSTransaction;
}

namespace OHOS::Ace {
class ACE_FORCE_EXPORT InteractionInterface : public AceType {
    DECLARE_ACE_TYPE(InteractionInterface, AceType);

public:
    static InteractionInterface* GetInstance();

    virtual int32_t UpdateShadowPic(const ShadowInfoCore& shadowInfo) = 0;

    virtual int32_t SetDragWindowVisible(bool visible,
        const std::shared_ptr<Rosen::RSTransaction>& rSTransaction = nullptr) = 0;

    virtual int32_t SetMouseDragMonitorState(bool state) = 0;

    virtual int32_t StartDrag(const DragDataCore& dragData,
        std::function<void(const OHOS::Ace::DragNotifyMsg&)> callback) = 0;

    virtual int32_t GetDragBundleInfo(DragBundleInfo& dragBundleInfo) = 0;

    virtual int32_t UpdateDragStyle(DragCursorStyleCore style, const int32_t eventId = -1) = 0;

    virtual int32_t UpdatePreviewStyle(const PreviewStyle& previewStyle) = 0;

    virtual int32_t UpdatePreviewStyleWithAnimation(const PreviewStyle& previewStyle,
                     const PreviewAnimation& animation) = 0;

    virtual int32_t StopDrag(DragDropRet result) = 0;

    virtual int32_t GetUdKey(std::string& udKey) = 0;

    virtual int32_t GetShadowOffset(ShadowOffsetData& shadowOffsetData) = 0;

    virtual int32_t GetDragState(DragState& dragState) const = 0;

    virtual int32_t GetDragSummary(std::map<std::string, int64_t>& summary) = 0;

    virtual int32_t GetDragExtraInfo(std::string& extraInfo) = 0;

    virtual int32_t EnterTextEditorArea(bool enable) = 0;

    virtual int32_t AddPrivilege() = 0;

    virtual int32_t RegisterCoordinationListener(std::function<void()> dragOutCallback) = 0;

    virtual int32_t UnRegisterCoordinationListener() = 0;

    virtual int32_t SetDraggableState(bool state) = 0;

    virtual int32_t GetAppDragSwitchState(bool& state) = 0;

    virtual void SetDraggableStateAsync(bool state, int64_t downTime) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INTERACTION_INTERFACE_H