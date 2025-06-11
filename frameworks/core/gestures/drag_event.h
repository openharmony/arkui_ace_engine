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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_DRAG_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_DRAG_EVENT_H

#include <map>
#include <string_view>

#include "base/geometry/rect.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "core/common/udmf/unified_data.h"
#include "core/event/ace_events.h"
#include "core/gestures/velocity.h"
#include "core/components_ng/manager/drag_drop/drag_drop_related_configuration.h"

namespace OHOS::Ace {
constexpr Dimension DEFAULT_DRAG_START_PAN_DISTANCE_THRESHOLD = 10.0_vp;
constexpr float DEFAULT_DRAG_START_SCALE = 0.2;
class PasteData : public AceType {
    DECLARE_ACE_TYPE(PasteData, AceType);

public:
    PasteData() = default;
    ~PasteData() override = default;

    void SetPlainText(const std::string& plainText)
    {
        plainText_ = plainText;
    }

    const std::string& GetPlainText() const
    {
        return plainText_;
    }

private:
    std::string plainText_;
};

enum class DragDropInitiatingStatus : int32_t {
    IDLE = 0,
    READY,
    PRESS,
    LIFTING,
    MOVING,
};

enum class DragSpringLoadingState {
    BEGIN = 0,
    UPDATE,
    END,
    CANCEL,
};

enum class DragRet {
    DRAG_DEFAULT = -1,
    DRAG_SUCCESS = 0,
    DRAG_FAIL,
    DRAG_CANCEL,
    ENABLE_DROP,
    DISABLE_DROP,
};

enum class PreDragStatus {
    ACTION_DETECTING_STATUS = 0,
    READY_TO_TRIGGER_DRAG_ACTION,
    PREVIEW_LIFT_STARTED,
    PREVIEW_LIFT_FINISHED,
    PREVIEW_LANDING_STARTED,
    PREVIEW_LANDING_FINISHED,
    ACTION_CANCELED_BEFORE_DRAG,
    PREPARING_FOR_DRAG_DETECTION,
};

enum class DragStartRequestStatus : int32_t {
    WAITING = 0,
    READY
};

enum class DragBehavior {
    UNKNOWN = -1,
    COPY = 0,
    MOVE = 1,
};

class ACE_FORCE_EXPORT DragEvent : public AceType {
    DECLARE_ACE_TYPE(DragEvent, AceType)

public:
    DragEvent() = default;
    ~DragEvent() override = default;

    void SetPasteData(const RefPtr<PasteData>& pasteData)
    {
        pasteData_ = pasteData;
    }

    RefPtr<PasteData> GetPasteData() const
    {
        return pasteData_;
    }

    double GetScreenX() const
    {
        return screenX_;
    }

    double GetScreenY() const
    {
        return screenY_;
    }

    void SetScreenX(double x)
    {
        screenX_ = x;
    }

    void SetScreenY(double y)
    {
        screenY_ = y;
    }

    double GetX() const
    {
        return x_;
    }

    double GetY() const
    {
        return y_;
    }

    void SetX(double x)
    {
        x_ = x;
    }

    void SetY(double y)
    {
        y_ = y;
    }

    double GetDisplayX() const
    {
        return displayX_;
    }

    double GetDisplayY() const
    {
        return displayY_;
    }

    void SetDisplayX(double x)
    {
        displayX_ = x;
    }

    void SetDisplayY(double y)
    {
        displayY_ = y;
    }

    void SetDescription(const std::string& description)
    {
        description_ = description;
    }

    const std::string& GetDescription() const
    {
        return description_;
    }

    void SetPixmap(const RefPtr<PixelMap>& pixelMap)
    {
        pixelMap_ = pixelMap;
    }

    RefPtr<PixelMap> GetPixmap() const
    {
        return pixelMap_;
    }

    void SetSummary(std::map<std::string, int64_t>& summary)
    {
        summary_ = summary;
    }

    std::map<std::string, int64_t>& GetSummary()
    {
        return summary_;
    }

    void SetResult(DragRet dragRet)
    {
        dragRet_ = dragRet;
    }

    DragRet GetResult()
    {
        return dragRet_;
    }

    Rect GetPreviewRect()
    {
        return previewRect_;
    }

    void SetPreviewRect(Rect previewRect)
    {
        previewRect_ = previewRect;
    }

    void UseCustomAnimation(bool useCustomAnimation)
    {
        useCustomAnimation_ = useCustomAnimation;
    }

    bool IsUseCustomAnimation()
    {
        return useCustomAnimation_;
    }

    void SetCopy(bool copy)
    {
        copy_ = copy;
    }

    bool IsCopy()
    {
        return copy_;
    }

    void SetDragBehavior(DragBehavior dragBehavior)
    {
        dragBehavior_ = dragBehavior;
    }

    DragBehavior GetDragBehavior() const
    {
        return dragBehavior_;
    }

    void SetUdKey(const std::string& udKey)
    {
        udKey_ = udKey;
    }

    const std::string& GetUdKey()
    {
        return udKey_;
    }

    void SetIsGetDataSuccess(bool isGetDataSuccess)
    {
        isGetDataSuccess_ = isGetDataSuccess;
    }

    bool IsGetDataSuccess()
    {
        return isGetDataSuccess_;
    }

    void SetData(const RefPtr<UnifiedData>& unifiedData);

    RefPtr<UnifiedData>& GetData();

    void SetDragInfo(const RefPtr<UnifiedData>& dragInfo);

    RefPtr<UnifiedData>& GetDragInfo();
    void SetVelocity(const Velocity& velocity)
    {
        velocity_ = velocity;
    }

    const Velocity& GetVelocity() const
    {
        return velocity_;
    }

    void SetSourceTool(SourceTool sourceTool)
    {
        sourceTool_ = sourceTool;
    }

    SourceTool GetSourceTool() const
    {
        return sourceTool_;
    }

    const std::vector<KeyCode>& GetPressedKeyCodes() const
    {
        return pressedKeyCodes_;
    }

    void SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes)
    {
        pressedKeyCodes_ = pressedKeyCodes;
    }

    void SetCapi(bool isCapi)
    {
        isCapi_ = isCapi;
    }

    bool IsCapi()
    {
        return isCapi_;
    }

    void SetDropAnimation(std::function<void()>&& executeDropAnimation)
    {
        executeDropAnimation_ = std::move(executeDropAnimation);
    }

    bool HasDropAnimation() const
    {
        return (executeDropAnimation_ != nullptr);
    }

    void ExecuteDropAnimation()
    {
        if (executeDropAnimation_) {
            auto executeDropAnimation = executeDropAnimation_;
            executeDropAnimation();
        }
    }

    void SetIsDragEndPending(bool isDragEndPending)
    {
        isDragEndPending_ = isDragEndPending;
    }

    bool IsDragEndPending() const
    {
        return isDragEndPending_;
    }

    void SetRequestIdentify(int32_t requestId)
    {
        requestId_ = requestId;
    }

    int32_t GetRequestIdentify() const
    {
        return requestId_;
    }

    void SetDragSource(const std::string& bundleName)
    {
        bundleName_ = bundleName;
    }

    std::string GetDragSource() const
    {
        return bundleName_;
    }


    void SetRemoteDev(bool isRemoteDev)
    {
        isRemoteDev_ = isRemoteDev;
    }

    bool isRemoteDev() const
    {
        return isRemoteDev_;
    }
    
    void SetDisplayId(int32_t displayId)
    {
        displayId_ = displayId;
    }

    int32_t GetDisplayId() const
    {
        return displayId_;
    }

    void SetNeedDoInternalDropAnimation(bool needDoInternalDropAnimation)
    {
        needDoInternalDropAnimation_ = needDoInternalDropAnimation;
    }

    bool GetNeedDoInternalDropAnimation() const
    {
        return needDoInternalDropAnimation_;
    }

private:
    RefPtr<PasteData> pasteData_;
    double screenX_ = 0.0;
    double screenY_ = 0.0;
    double x_ = 0.0;
    double y_ = 0.0;
    double displayX_ = 0.0;
    double displayY_ = 0.0;
    std::string description_;
    RefPtr<PixelMap> pixelMap_;
    std::map<std::string, int64_t> summary_;
    std::string udKey_ = "";
    DragRet dragRet_ = DragRet::DRAG_DEFAULT;
    SourceTool sourceTool_ = { SourceTool::UNKNOWN };
    Rect previewRect_;
    bool useCustomAnimation_ = false;
    bool isGetDataSuccess_ = false;
    bool copy_ = true;
    DragBehavior dragBehavior_ = DragBehavior::UNKNOWN;
    RefPtr<UnifiedData> unifiedData_;
    RefPtr<UnifiedData> dragInfo_;
    Velocity velocity_;
    std::vector<KeyCode> pressedKeyCodes_;
    bool isCapi_ = false;
    std::function<void()> executeDropAnimation_;
    int32_t requestId_ = -1;
    bool isDragEndPending_ = false;
    std::string bundleName_;
    bool isRemoteDev_ { false };
    int32_t displayId_ = -1;
    bool needDoInternalDropAnimation_ = false;
};

class NotifyDragEvent : public DragEvent {
    DECLARE_ACE_TYPE(NotifyDragEvent, DragEvent)

public:
    NotifyDragEvent() = default;
    ~NotifyDragEvent() = default;
};

class ItemDragInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(ItemDragInfo, BaseEventInfo);

public:
    ItemDragInfo() : BaseEventInfo("itemDrag") {}
    ~ItemDragInfo() override = default;

    double GetX() const
    {
        return x_;
    }

    double GetY() const
    {
        return y_;
    }

    void SetX(double x)
    {
        x_ = x;
    }

    void SetY(double y)
    {
        y_ = y;
    }

private:
    double x_ = 0.0;
    double y_ = 0.0;
};

class DragSpringLoadingContext : public AceType {
    DECLARE_ACE_TYPE(DragSpringLoadingContext, AceType)
public:
    explicit DragSpringLoadingContext() = default;
    ~DragSpringLoadingContext() override = default;

    void SetState(DragSpringLoadingState state)
    {
        state_ = state;
    }

    DragSpringLoadingState GetState() const
    {
        return state_;
    }

    void SetCurrentNotifySequence(int32_t currentNotifySequence)
    {
        currentNotifySequence_ = currentNotifySequence;
    }

    int32_t GetCurrentNotifySequence() const
    {
        return currentNotifySequence_;
    }

    void SetExtraInfos(std::string_view extraInfos)
    {
        extraInfos_ = extraInfos.data();
    }

    const std::string& GetExtraInfos() const
    {
        return extraInfos_;
    }

    void SetSummary(const std::map<std::string, int64_t>& summary)
    {
        summary_ = summary;
    }

    const std::map<std::string, int64_t>& GetSummary() const
    {
        return summary_;
    }

    void SetSpringLoadingAborted()
    {
        isSpringLoadingAborted_ = true;
    }

    bool IsSpringLoadingAborted() const
    {
        return isSpringLoadingAborted_;
    }

    const RefPtr<NG::DragSpringLoadingConfiguration>& GetDragSpringLoadingConfiguration() const
    {
        return DragSpringLoadingConfiguration_;
    }

    void SetDragSpringLoadingConfiguration(
        const RefPtr<NG::DragSpringLoadingConfiguration>& dragSpringLoadingConfiguration)
    {
        DragSpringLoadingConfiguration_ = dragSpringLoadingConfiguration;
    }

private:
    DragSpringLoadingState state_;
    int32_t currentNotifySequence_ = 0;
    std::string extraInfos_;
    std::map<std::string, int64_t> summary_;
    bool isSpringLoadingAborted_ = false;
    RefPtr<NG::DragSpringLoadingConfiguration> DragSpringLoadingConfiguration_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_RECOGNIZER_H