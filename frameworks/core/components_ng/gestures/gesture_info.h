/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_INFO_H

#include <functional>
#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/event/gesture_info.h"
#include "core/components_ng/property/border_property.h"
#include "core/gestures/gesture_event.h"
#include "core/gestures/gesture_info.h"
#include "core/gestures/gesture_type.h"
#include "core/gestures/velocity.h"
#include "core/gestures/velocity_tracker.h"
#include "core/components/common/properties/blur_style_option.h"
#include "core/components/common/properties/shadow.h"

namespace OHOS::Ace::NG {

class NGGestureRecognizer;

enum class DragPreviewMode : int32_t {
    AUTO = 1,
    DISABLE_SCALE = 2,
    ENABLE_DEFAULT_SHADOW = 3,
    ENABLE_DEFAULT_RADIUS = 4,
    ENABLE_DRAG_ITEM_GRAY_EFFECT = 5,
    ENABLE_MULTI_TILE_EFFECT  = 6,
    ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW = 7,
};

enum class DraggingSizeChangeEffect : int32_t {
    DEFAULT = 0,
    SIZE_TRANSITION = 1,
    SIZE_CONTENT_TRANSITION = 2,
};

struct BlurBackGroundInfo {
    EffectOption  backGroundEffect;
    void ToJsonValue(const std::unique_ptr<JsonValue>& json)
    {
        json->Put("blur_radius", backGroundEffect.radius.Value());
        json->Put("blur_staturation", backGroundEffect.saturation);
        json->Put("blur_brightness", backGroundEffect.brightness);
        int32_t blurColor = static_cast<int32_t> (backGroundEffect.color.GetValue());
        json->Put("blur_color", blurColor);
        json->Put("blur_style", static_cast<int32_t>(backGroundEffect.adaptiveColor));
        constexpr int32_t GRAYSCALE_MAX_VALUE = 2;
        if (backGroundEffect.blurOption.grayscale.size() >= GRAYSCALE_MAX_VALUE) {
            json->Put("blur_coef1", backGroundEffect.blurOption.grayscale[0]);
            json->Put("blur_coef2", backGroundEffect.blurOption.grayscale[1]);
        } else {
            json->Put("blur_coef1", 0);
            json->Put("blur_coef2", 0);
        }
    }
};

struct OptionsAfterApplied {
    double opacity { 1.0f };
    std::optional<Shadow> shadow;
    std::string shadowPath;
    bool isFilled = true;
    std::optional<BorderRadiusProperty> borderRadius;
    BlurBackGroundInfo blurbgEffect;
};

struct DragPreviewOption {
    bool isScaleEnabled = true;
    bool defaultAnimationBeforeLifting = false;
    bool isMultiSelectionEnabled = false;
    bool isNumber = false;
    bool isDefaultShadowEnabled = false;
    bool isDefaultRadiusEnabled = false;
    bool isDragPreviewEnabled = true;
    bool isDefaultDragItemGrayEffectEnabled = false;
    bool enableEdgeAutoScroll = true;
    bool enableHapticFeedback = false;
    bool isMultiTiled = false;
    bool isLiftingDisabled = false;
    bool isTouchPointCalculationBasedOnFinalPreviewEnable = false;
    NG::DraggingSizeChangeEffect sizeChangeEffect = DraggingSizeChangeEffect::DEFAULT;
    union {
        int32_t badgeNumber;
        bool isShowBadge = true;
    };
    std::optional<int32_t> GetCustomerBadgeNumber()
    {
        if (isNumber) {
            return badgeNumber > 1 ? badgeNumber : 1;
        } else if (!isShowBadge) {
            return 1;
        }
        return std::nullopt;
    }
    std::function<void(WeakPtr<NG::FrameNode>)> onApply;
    OptionsAfterApplied options; // options from modifier after applied
    void ResetDragPreviewMode()
    {
        isScaleEnabled = true;
        isDefaultShadowEnabled = false;
        isDefaultRadiusEnabled = false;
        isDefaultDragItemGrayEffectEnabled = false;
        isMultiTiled = false;
    }
};

class ACE_EXPORT Gesture : public virtual AceType {
    DECLARE_ACE_TYPE(Gesture, AceType);

public:
    Gesture() = default;
    explicit Gesture(int32_t fingers) : fingers_(fingers) {}
    explicit Gesture(
        int32_t fingers, bool isLimitFingerCount) : fingers_(fingers), isLimitFingerCount_(isLimitFingerCount) {}
    ~Gesture() override = default;

    void SetOnActionId(const GestureEventFunc& onActionId)
    {
        onActionId_ = std::make_shared<GestureEventFunc>(onActionId);
    }
    std::shared_ptr<GestureEventFunc> GetOnActionId()
    {
        return onActionId_;
    }
    void SetOnActionStartId(const GestureEventFunc& onActionStartId)
    {
        onActionStartId_ = std::make_unique<GestureEventFunc>(onActionStartId);
    }
    void SetOnActionUpdateId(const GestureEventFunc& onActionUpdateId)
    {
        onActionUpdateId_ = std::make_unique<GestureEventFunc>(onActionUpdateId);
    }
    void SetOnActionEndId(const GestureEventFunc& onActionEndId)
    {
        onActionEndId_ = std::make_unique<GestureEventFunc>(onActionEndId);
    }
    void SetOnActionCancelId(const GestureEventFunc& onActionCancelId)
    {
        onActionCancelId_ = std::make_unique<GestureEventFunc>(onActionCancelId);
    }
    void SetPriority(GesturePriority priority)
    {
        priority_ = priority;
    }
    void SetGestureMask(GestureMask gestureMask)
    {
        gestureMask_ = gestureMask;
    }

    GesturePriority GetPriority() const
    {
        return priority_;
    }

    GestureMask GetGestureMask() const
    {
        return gestureMask_;
    }

    int32_t GetFingers() const
    {
        return fingers_;
    }

    void SetLimitFingerCount(bool limitFingerCount)
    {
        isLimitFingerCount_ = limitFingerCount;
    }

    bool GetLimitFingerCount() const
    {
        return isLimitFingerCount_;
    }

    void SetTag(std::string tag)
    {
        if (gestureInfo_) {
            gestureInfo_->SetTag(std::move(tag));
        } else {
            gestureInfo_ = MakeRefPtr<GestureInfo>(tag);
        }
    }

    void SetAllowedTypes(std::set<SourceTool> allowedTypes)
    {
        if (gestureInfo_) {
            gestureInfo_->SetAllowedTypes(std::move(allowedTypes));
        } else {
            gestureInfo_ = MakeRefPtr<GestureInfo>(allowedTypes);
        }
    }

    std::optional<std::string> GetTag()
    {
        if (gestureInfo_) {
            return gestureInfo_->GetTag();
        }
        return std::nullopt;
    }

    std::set<SourceTool> GetAllowedTypes()
    {
        if (gestureInfo_) {
            return gestureInfo_->GetAllowedTypes();
        }
        return {};
    }

    virtual int32_t SizeofMe()
    {
        return 0;
    }

    virtual int32_t Serialize(char* p)
    {
        return 0;
    }

    virtual int32_t Deserialize(const char* p)
    {
        return 0;
    }

    char* SetHeader(char* buff, GestureType type, int32_t len)
    {
        if (buff == nullptr) {
            return nullptr;
        }
        *reinterpret_cast<GestureType*>(buff) = type;
        buff += sizeof(GestureType);
        *reinterpret_cast<int32_t*>(buff) = len;
        buff += sizeof(int32_t);
        return buff;
    }
    
    void SetUserData(void* userData)
    {
        userData_ = userData;
    }

    virtual RefPtr<NGGestureRecognizer> CreateRecognizer() = 0;

    void SetDisposeTag(bool tag)
    {
        if (gestureInfo_) {
            gestureInfo_->SetDisposeTag(tag);
        }
    }

#ifdef ARKUI_CAPI_UNITTEST
    std::optional<GestureTypeName> GetType()
    {
        if (gestureInfo_) {
            return gestureInfo_->GetType();
        }
        return std::nullopt;
    }
#endif // ARKUI_CAPI_UNITTEST
protected:
    int32_t fingers_ = 1;
    bool isLimitFingerCount_ = false;
    GesturePriority priority_ = GesturePriority::Low;
    GestureMask gestureMask_ = GestureMask::Normal;
    std::shared_ptr<GestureEventFunc> onActionId_;
    std::unique_ptr<GestureEventFunc> onActionStartId_;
    std::unique_ptr<GestureEventFunc> onActionUpdateId_;
    std::unique_ptr<GestureEventFunc> onActionEndId_;
    std::unique_ptr<GestureEventFunc> onActionCancelId_;
    RefPtr<GestureInfo> gestureInfo_;
    void* userData_ = nullptr;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_INFO_H
