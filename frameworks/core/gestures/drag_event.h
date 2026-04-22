/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/common/udmf/data_load_params.h"
#include "core/common/udmf/unified_data.h"
#include "core/event/ace_events.h"
#include "core/gestures/drag_constants.h"
#include "core/gestures/gesture_info.h"
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

    void SetPlainText(const std::string& plainText);
    const std::string& GetPlainText() const;

private:
    std::string plainText_;
};

class ACE_FORCE_EXPORT DragEvent : public AceType {
    DECLARE_ACE_TYPE(DragEvent, AceType);

public:
    DragEvent() = default;
    ~DragEvent() override = default;

    void SetPasteData(const RefPtr<PasteData>& pasteData);
    RefPtr<PasteData> GetPasteData() const;

    double GetScreenX() const;
    double GetScreenY() const;
    void SetScreenX(double x);
    void SetScreenY(double y);

    double GetX() const;
    double GetY() const;
    void SetX(double x);
    void SetY(double y);

    double GetDisplayX() const;
    double GetDisplayY() const;
    void SetDisplayX(double x);
    void SetDisplayY(double y);

    double GetGlobalDisplayX() const;
    double GetGlobalDisplayY() const;
    void SetGlobalDisplayX(double x);
    void SetGlobalDisplayY(double y);

    void SetDescription(const std::string& description);
    const std::string& GetDescription() const;

    void SetPixmap(const RefPtr<PixelMap>& pixelMap);
    RefPtr<PixelMap> GetPixmap() const;

    void SetSummary(std::map<std::string, int64_t>& summary);
    std::map<std::string, int64_t>& GetSummary();

    void SetResult(DragRet dragRet);
    DragRet GetResult();

    Rect GetPreviewRect();
    void SetPreviewRect(Rect previewRect);

    void UseCustomAnimation(bool useCustomAnimation);
    bool IsUseCustomAnimation();

    void SetCopy(bool copy);
    bool IsCopy();

    void SetDragBehavior(DragBehavior dragBehavior);
    DragBehavior GetDragBehavior() const;

    void SetAutoHideComponentUniqueIds(const std::vector<int32_t>& autoHideComponentUniqueIds);
    const std::vector<int32_t>& GetAutoHideComponentUniqueIds() const;

    void SetUdKey(const std::string& udKey);
    const std::string& GetUdKey();

    void SetIsGetDataSuccess(bool isGetDataSuccess);
    bool IsGetDataSuccess();

    void SetData(const RefPtr<UnifiedData>& unifiedData);
    RefPtr<UnifiedData>& GetData();

    void SetDragInfo(const RefPtr<UnifiedData>& dragInfo);
    RefPtr<UnifiedData>& GetDragInfo();

    void SetVelocity(const Velocity& velocity);
    const Velocity& GetVelocity() const;

    void SetSourceTool(SourceTool sourceTool);
    SourceTool GetSourceTool() const;

    const std::vector<KeyCode>& GetPressedKeyCodes() const;
    void SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes);

    void SetCapi(bool isCapi);
    bool IsCapi();

    void SetDropAnimation(std::function<void()>&& executeDropAnimation);
    bool HasDropAnimation() const;
    void ExecuteDropAnimation();

    void SetIsDragEndPending(bool isDragEndPending);
    bool IsDragEndPending() const;

    void SetRequestIdentify(int32_t requestId);
    int32_t GetRequestIdentify() const;

    void SetDisplayId(int32_t displayId);
    int32_t GetDisplayId() const;

    void SetDragSource(const std::string& bundleName);
    const std::string& GetDragSource() const;

    void SetRemoteDev(bool isRemoteDev);
    bool isRemoteDev() const;

    void SetNeedDoInternalDropAnimation(bool needDoInternalDropAnimation);
    bool GetNeedDoInternalDropAnimation() const;

    void SetDataLoadParams(const RefPtr<DataLoadParams>& dataLoadParams);
    RefPtr<DataLoadParams> GetDataLoadParams() const;

    void SetUseDataLoadParams(bool useDataLoadParams);
    bool IsUseDataLoadParams() const;

    // only use for ArkTs1.2 begin
    RefPtr<PixelMap> GetDragDropInfoPixelMap() const;
    void* GetDragDropInfoCustomNode() const;
    std::string GetDragDropInfoExtraInfo() const;
    void SetDragDropInfoPixelMap(RefPtr<PixelMap> pixelMap);
    void SetDragDropInfoCustomNode(void* customNode);
    void SetDragDropInfoExtraInfo(std::string& extraInfo);
    // only use for ArkTs1.2 end

private:
    RefPtr<PasteData> pasteData_;
    double screenX_ = 0.0;
    double screenY_ = 0.0;
    double x_ = 0.0;
    double y_ = 0.0;
    double displayX_ = 0.0;
    double displayY_ = 0.0;
    double globalDisplayX_ = 0.0;
    double globalDisplayY_ = 0.0;
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
    std::vector<int32_t> autoHideComponentUniqueIds_;
    RefPtr<UnifiedData> unifiedData_;
    RefPtr<UnifiedData> dragInfo_;
    Velocity velocity_;
    std::vector<KeyCode> pressedKeyCodes_;
    bool isCapi_ = false;
    std::function<void()> executeDropAnimation_;
    int32_t requestId_ = -1;
    bool isDragEndPending_ = false;
    int32_t displayId_ = -1;
    std::string bundleName_;
    bool isRemoteDev_ { false };
    bool needDoInternalDropAnimation_ = false;
    RefPtr<DataLoadParams> dataLoadParams_ = nullptr;
    bool useDataLoadParams_ { false };
    RefPtr<PixelMap> dragDropInfoPixelMap_;
    void* dragDropInfoCustomNode_;
    std::string dragDropInfoExtraInfo_;
};

class NotifyDragEvent : public DragEvent {
    DECLARE_ACE_TYPE(NotifyDragEvent, DragEvent);

public:
    NotifyDragEvent() = default;
    ~NotifyDragEvent() override = default;
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

    void SetFrameNode(const WeakPtr<NG::FrameNode>& frameNode)
    {
        frameNode_ = frameNode;
    }

    WeakPtr<NG::FrameNode> GetFrameNode() const
    {
        return frameNode_;
    }

private:
    double x_ = 0.0;
    double y_ = 0.0;
    WeakPtr<NG::FrameNode> frameNode_;
};

class DragSpringLoadingContext : public AceType {
    DECLARE_ACE_TYPE(DragSpringLoadingContext, AceType);
public:
    explicit DragSpringLoadingContext() = default;
    ~DragSpringLoadingContext() override = default;

    void SetState(DragSpringLoadingState state);
    DragSpringLoadingState GetState() const;

    void SetCurrentNotifySequence(int32_t currentNotifySequence);
    int32_t GetCurrentNotifySequence() const;

    void SetExtraInfos(std::string_view extraInfos);
    const std::string& GetExtraInfos() const;

    void SetSummary(const std::map<std::string, int64_t>& summary);
    const std::map<std::string, int64_t>& GetSummary() const;

    void SetSpringLoadingAborted();
    bool IsSpringLoadingAborted() const;

    const RefPtr<NG::DragSpringLoadingConfiguration>& GetDragSpringLoadingConfiguration() const;
    void SetDragSpringLoadingConfiguration(
        const RefPtr<NG::DragSpringLoadingConfiguration>& dragSpringLoadingConfiguration);

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
