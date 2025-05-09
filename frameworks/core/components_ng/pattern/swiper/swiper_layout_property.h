/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "base/utils/string_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SwiperLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SwiperLayoutProperty, LayoutProperty);

public:
    SwiperLayoutProperty() = default;

    ~SwiperLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<SwiperLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propDirection_ = CloneDirection();
        value->propIndex_ = CloneIndex();
        value->propItemSpace_ = CloneItemSpace();
        value->propCachedCount_ = CloneCachedCount();
        value->propCachedIsShown_ = CloneCachedIsShown();
        value->propDisplayMode_ = CloneDisplayMode();
        value->propDisplayCount_ = CloneDisplayCount();
        value->propMinSize_ = CloneMinSize();
        value->propShowIndicator_ = CloneShowIndicator();
        value->propIndicatorType_ = CloneIndicatorType();
        value->propLeft_ = CloneLeft();
        value->propTop_ = CloneTop();
        value->propRight_ = CloneRight();
        value->propBottom_ = CloneBottom();
        value->propPrevMargin_ = ClonePrevMargin();
        value->propPrevMarginIgnoreBlank_ = ClonePrevMarginIgnoreBlank();
        value->propNextMargin_ = CloneNextMargin();
        value->propNextMarginIgnoreBlank_ = CloneNextMarginIgnoreBlank();
        value->propDisplayArrow_ = CloneDisplayArrow();
        value->propHoverShow_ = CloneHoverShow();
        value->propIsShowBackground_ = CloneIsShowBackground();
        value->propIsSidebarMiddle_ = CloneIsSidebarMiddle();
        value->propBackgroundSize_ = CloneBackgroundSize();
        value->propBackgroundColor_ = CloneBackgroundColor();
        value->propArrowSize_ = CloneArrowSize();
        value->propArrowColor_ = CloneArrowColor();
        value->propLoop_ = CloneLoop();
        value->propIndicatorInteractive_ = CloneIndicatorInteractive();
        value->propDisableSwipe_ = CloneDisableSwipe();
        value->ignoreItemSpace_ = ignoreItemSpace_;
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetDirection();
        ResetIndex();
        ResetItemSpace();
        ResetCachedCount();
        ResetCachedIsShown();
        ResetDisplayMode();
        ResetDisplayCount();
        ResetMinSize();
        ResetShowIndicator();
        ResetIndicatorType();
        ResetLeft();
        ResetTop();
        ResetRight();
        ResetBottom();
        ResetPrevMargin();
        ResetPrevMarginIgnoreBlank();
        ResetNextMargin();
        ResetNextMarginIgnoreBlank();
        ResetDisplayArrow();
        ResetHoverShow();
        ResetIsShowBackground();
        ResetIsSidebarMiddle();
        ResetBackgroundSize();
        ResetBackgroundColor();
        ResetArrowSize();
        ResetArrowColor();
        ResetLoop();
        ResetIndicatorInteractive();
        ResetDisableSwipe();
        ignoreItemSpace_ = false;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        CHECK_NULL_VOID(json);
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("index", std::to_string(propIndex_.value_or(0)).c_str(), filter);
        json->PutExtAttr("vertical",
            propDirection_.value_or(Axis::HORIZONTAL) == Axis::VERTICAL ? "true" : "false", filter);
        json->PutExtAttr("indicator", propShowIndicator_.value_or(true) ? "true" : "false", filter);
        json->PutExtAttr("itemSpace",
            propItemSpace_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("cachedCount", propCachedCount_.value_or(1), filter);
        json->PutExtAttr("displayMode",
            propDisplayMode_.value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::AUTO_LINEAR ?
            "SwiperDisplayMode.AutoLinear" : "SwiperDisplayMode.Stretch", filter);
        json->PutExtAttr("displayCount", propDisplayCount_.value_or(1), filter);
        json->PutExtAttr("minSize",
            propMinSize_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("prevMargin",
            ignorePrevMarginAndNextMargin_
                ? Dimension(0.0_px).ToString().c_str()
                : propPrevMargin_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("prevMarginIgnoreBlank",
            propPrevMarginIgnoreBlank_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("nextMargin",
            ignorePrevMarginAndNextMargin_
                ? Dimension(0.0_px).ToString().c_str()
                : propNextMargin_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("nextMarginIgnoreBlank",
            propNextMarginIgnoreBlank_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("displayArrow", propDisplayArrow_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("hoverShow", propHoverShow_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("showBackground", propIsShowBackground_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("isSidebarMiddle", propIsSidebarMiddle_.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("arrowBackgroundSize",
            propBackgroundSize_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("arrowSize",
            propArrowSize_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("arrowBackgroundColor",
            propBackgroundColor_.value_or(Color::TRANSPARENT).ColorToString().c_str(), filter);
        json->PutExtAttr("arrowColor",
            propArrowColor_.value_or(Color::TRANSPARENT).ColorToString().c_str(), filter);
        json->PutExtAttr("loop", propLoop_.value_or(true) ? "true" : "false", filter);
        json->PutExtAttr("indicatorInteractive", propIndicatorInteractive_.value_or(true) ? "true" : "false", filter);
        json->PutExtAttr("disableSwipe", GetDisableSwipe().value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("swipeByGroup", propSwipeByGroup_.value_or(false) ? "true" : "false", filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        CHECK_NULL_VOID(json);
        static const std::unordered_map<std::string, SwiperDisplayMode> uMap {
            { "SwiperDisplayMode.AutoLinear", SwiperDisplayMode::AUTO_LINEAR },
            { "SwiperDisplayMode.Stretch", SwiperDisplayMode::STRETCH },
        };

        UpdateLoop(json->GetBool("loop"));
        UpdateIndex(StringUtils::StringToInt(json->GetString("index")));
        UpdateDirection(json->GetString("vertical") == "true" ? Axis::VERTICAL : Axis::HORIZONTAL);
        UpdateShowIndicator(json->GetString("indicator") == "true" ? true : false);
        UpdateItemSpace(Dimension::FromString(json->GetString("itemSpace")));
        UpdateCachedCount(json->GetInt("cachedCount"));
        auto displayMode = json->GetString("displayMode");
        SwiperDisplayMode swiperDisplayMode = SwiperDisplayMode::STRETCH;
        auto iter = uMap.find(displayMode);
        if (iter != uMap.end()) {
            swiperDisplayMode = iter->second;
        }
        UpdateDisplayMode(swiperDisplayMode);
        UpdateDisplayCount(json->GetInt("displayCount"));
        UpdateDisableSwipe(json->GetBool("disableSwipe"));
        LayoutProperty::FromJson(json);
    }

    void UpdateIndexWithoutMeasure(int32_t index)
    {
        if (propIndex_ != index) {
            propIndex_ = index;
        }
    }

    void ResetIgnorePrevMarginAndNextMargin()
    {
        ignorePrevMarginAndNextMargin_ = false;
    }

    void MarkIgnorePrevMarginAndNextMargin()
    {
        ignorePrevMarginAndNextMargin_ = true;
    }

    float GetCalculatedPrevMargin() const
    {
        if (!IsStretch() || ignorePrevMarginAndNextMargin_) {
            return 0.0f;
        }
        return GetPrevMarginValue(0.0_vp).ConvertToPx();
    }

    float GetCalculatedNextMargin() const
    {
        if (!IsStretch() || ignorePrevMarginAndNextMargin_) {
            return 0.0f;
        }
        return GetNextMarginValue(0.0_vp).ConvertToPx();
    }

    bool IsStretch() const
    {
        // If display count is setted, use stretch mode.
        if (HasDisplayCount() && !HasMinSize()) {
            return true;
        }

        return GetDisplayMode().value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::STRETCH;
    }

    void ResetIgnoreItemSpace()
    {
        ignoreItemSpace_ = false;
    }

    void MarkIgnoreItemSpace()
    {
        ignoreItemSpace_ = true;
    }

    bool IgnoreItemSpace() const
    {
        return ignoreItemSpace_;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Direction, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Index, int32_t, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemSpace, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedCount, int32_t, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayMode, SwiperDisplayMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MinSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowIndicator, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorType, SwiperIndicatorType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Left, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Top, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Right, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Bottom, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PrevMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PrevMarginIgnoreBlank, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NextMargin, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NextMarginIgnoreBlank, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayArrow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HoverShow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowBackground, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsSidebarMiddle, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowColor, Color, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Loop, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorInteractive, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsCustomAnimation, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisableSwipe, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SwipeByGroup, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedIsShown, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MaintainVisibleContentPosition, bool, PROPERTY_UPDATE_NORMAL);

private:
    bool ignoreItemSpace_ = false; // displayCount and prevMargin/nextMargin have higher priorities, so itemSpace might
                                   // be ignored in some situations.
    bool ignorePrevMarginAndNextMargin_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_PROPERTY_H
