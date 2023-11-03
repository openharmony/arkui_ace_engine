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

#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "core/event/ace_events.h"
#include "core/gestures/velocity.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "base/geometry/rect.h"
#include "core/common/udmf/unified_data.h"
#endif

namespace OHOS::Ace {

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

#ifdef ENABLE_DRAG_FRAMEWORK
enum class DragRet {
    DRAG_DEFAULT = -1,
    DRAG_SUCCESS = 0,
    DRAG_FAIL,
    DRAG_CANCEL,
    ENABLE_DROP,
    DISABLE_DROP,
};
enum class DragBehavior {
    COPY = 0,
    MOVE = 1,
};
#endif

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

#ifdef ENABLE_DRAG_FRAMEWORK
    void SetData(const RefPtr<UnifiedData>& unifiedData);

    RefPtr<UnifiedData>& GetData();

    void SetSummary(std::map<std::string, int64_t>& summary);

    std::map<std::string, int64_t>& GetSummary();

    void SetResult(DragRet dragRet);

    DragRet GetResult();

    void SetPreviewRect(Rect previewRect);

    Rect GetPreviewRect();

    void UseCustomAnimation(bool useCustomAnimation);

    bool IsUseCustomAnimation();

    void SetUdKey(const std::string udKey);

    std::string GetUdKey();

    void SetDragInfo(const RefPtr<UnifiedData>& dragInfo);

    RefPtr<UnifiedData>& GetDragInfo();

    void SetCopy(bool copy);

    bool IsCopy();

    void SetIsGetDataSuccess(bool isGetDataSuccess);

    bool IsGetDataSuccess();
#endif

    void SetVelocity(const Velocity& velocity)
    {
        velocity_ = velocity;
    }

    const Velocity& GetVelocity() const
    {
        return velocity_;
    }

private:
    RefPtr<PasteData> pasteData_;
    double screenX_ = 0.0;
    double screenY_ = 0.0;
    double x_ = 0.0;
    double y_ = 0.0;
    std::string description_;
    RefPtr<PixelMap> pixelMap_;
#ifdef ENABLE_DRAG_FRAMEWORK
    RefPtr<UnifiedData> unifiedData_;
    std::map<std::string, int64_t> summary_;
    std::string udKey_ = "";
    DragRet dragRet_ = DragRet::DRAG_DEFAULT;
    Rect previewRect_;
    bool useCustomAnimation_ = false;
    bool isGetDataSuccess_ = false;
    RefPtr<UnifiedData> dragInfo_;
    bool copy_ = true;
#endif
    Velocity velocity_;
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

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_CLICK_RECOGNIZER_H