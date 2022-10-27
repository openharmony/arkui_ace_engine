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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
class ImagePattern;
struct ImageSizeStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AutoResize, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SourceSize, SizeF);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FitOriginalSize, bool);
};

class ACE_EXPORT ImageLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ImageLayoutProperty, LayoutProperty);

public:
    ImageLayoutProperty() = default;

    ~ImageLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ImageLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propImageSourceInfo_ = CloneImageSourceInfo();
        value->propAlt_ = CloneAlt();
        value->propImageFit_ = CloneImageFit();
        value->propSyncMode_ = CloneSyncMode();
        value->propCopyOptions_ = CloneCopyOptions();
        value->propImageSizeStyle_ = CloneImageSizeStyle();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetImageSourceInfo();
        ResetAlt();
        ResetImageFit();
        ResetSyncMode();
        ResetCopyOptions();
        ResetImageSizeStyle();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);
        static const char* OBJECTFITVALUE[] = { "ImageFit.Fill", "ImageFit.Contain", "ImageFit.Cover",
            "ImageFit.FitWidth", "ImageFit.FitHeight", "ImageFit.None", "ImageFit.ScaleDown" };
        static const char* COPYOPTIONSVALUE[] = { "CopyOptions.None", "CopyOptions.InApp", "CopyOptions.Local",
            "CopyOptions.Distributed" };
        json->Put("alt", propAlt_.value_or(ImageSourceInfo("")).GetSrc().c_str());
        json->Put("objectFit", OBJECTFITVALUE[static_cast<int32_t>(propImageFit_.value_or(ImageFit::COVER))]);
        json->Put("sourceSize", propImageSizeStyle_->propSourceSize.value_or(SizeF()).ToString().c_str());
        json->Put("fitOriginalSize", propImageSizeStyle_->propFitOriginalSize.value_or(true) ? "true" : "false");
        json->Put("autoResize", propImageSizeStyle_->propAutoResize.value_or(true) ? "true" : "false");
        json->Put("syncLoad", propSyncMode_.value_or(false) ? "true" : "false");
        json->Put("copyOption", COPYOPTIONSVALUE[static_cast<int32_t>(propCopyOptions_.value_or(CopyOptions::None))]);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageFit, ImageFit, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Alt, ImageSourceInfo, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SyncMode, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CopyOptions, CopyOptions, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_GROUP(ImageSizeStyle, ImageSizeStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImageSizeStyle, AutoResize, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImageSizeStyle, SourceSize, SizeF, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImageSizeStyle, FitOriginalSize, bool, PROPERTY_UPDATE_LAYOUT);

private:
    ACE_DISALLOW_COPY_AND_MOVE(ImageLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_LAYOUT_PROPERTY_H
