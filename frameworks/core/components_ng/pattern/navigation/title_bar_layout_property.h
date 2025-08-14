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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_TITLE_BAR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_TITLE_BAR_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TitleBarLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(TitleBarLayoutProperty, LayoutProperty);

public:
    TitleBarLayoutProperty() = default;

    ~TitleBarLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto copy = MakeRefPtr<TitleBarLayoutProperty>();
        copy->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        copy->propTitleMode_ = CloneTitleMode();
        copy->propHideBackButton_ = CloneHideBackButton();
        copy->propTitleBarParentType_ = CloneTitleBarParentType();
        copy->propTitleHeight_ = CloneTitleHeight();
        copy->propNoPixMap_ = CloneNoPixMap();
        copy->propImageSource_ = CloneImageSource();
        copy->propPixelMap_ = ClonePixelMap();
        copy->propIsValidImage_ = CloneIsValidImage();
        copy->propIsCustomTitleBarSize_ = CloneIsCustomTitleBarSize();
        copy->backIconSymbol_ = backIconSymbol_;
        return copy;
    }

    void ResetSymbol()
    {
        backIconSymbol_ = nullptr;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetTitleMode();
        ResetHideBackButton();
        ResetTitleBarParentType();
        ResetTitleHeight();
        ResetNoPixMap();
        ResetImageSource();
        ResetPixelMap();
        ResetSymbol();
        ResetIsValidImage();
        ResetIsCustomTitleBarSize();
    }

    const std::function<void(WeakPtr<NG::FrameNode>)>& GetBackIconSymbol() const
    {
        return backIconSymbol_;
    }

    void SetBackIconSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& backIconSymbol)
    {
        backIconSymbol_ = backIconSymbol;
    }

private:
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TitleMode, NavigationTitleMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HideBackButton, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TitleBarParentType, TitleBarParentType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TitleHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    // back button icon
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NoPixMap, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageSource, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PixelMap, RefPtr<PixelMap>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsValidImage, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsCustomTitleBarSize, bool, PROPERTY_UPDATE_MEASURE);
    std::function<void(WeakPtr<NG::FrameNode>)> backIconSymbol_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_TITLE_BAR_LAYOUT_PROPERTY_H
