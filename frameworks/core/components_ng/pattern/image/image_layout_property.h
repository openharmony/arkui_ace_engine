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

#include "core/common/ace_application_info.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ImagePattern;
struct ImageSizeStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AutoResize, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SourceSize, SizeF);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FitOriginalSize, bool);
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const
    {
        json->Put("sourceSize", propSourceSize.value_or(SizeF()).ToString().c_str());
        json->Put("fitOriginalSize", propFitOriginalSize.value_or(false) ? "true" : "false");
        json->Put("autoResize", propAutoResize.value_or(true) ? "true" : "false");
    }
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
        value->propImageSizeStyle_ = CloneImageSizeStyle();
        value->propVerticalAlign_ = CloneVerticalAlign();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetImageSourceInfo();
        ResetAlt();
        ResetImageFit();
        ResetImageSizeStyle();
        ResetVerticalAlign();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);
        static const char* OBJECTFITVALUE[] = { "ImageFit.Fill", "ImageFit.Contain", "ImageFit.Cover",
            "ImageFit.Auto", "ImageFit.FitHeight", "ImageFit.None", "ImageFit.ScaleDown" };
        static const char* VERTICALALIGNVALUE[] = { "VerticalAlign.NONE", "VerticalAlign.TOP", "VerticalAlign.CENTER",
            "VerticalAlign.BOTTOM", "CopyOptions.BASELINE", "VerticalAlign.NONE" };
        json->Put("alt", propAlt_.value_or(ImageSourceInfo("")).GetSrc().c_str());
        json->Put("objectFit", OBJECTFITVALUE[static_cast<int32_t>(propImageFit_.value_or(ImageFit::COVER))]);
        json->Put("verticalAlign",
            VERTICALALIGNVALUE[static_cast<int32_t>(propVerticalAlign_.value_or(VerticalAlign::BOTTOM))]);
        std::string src;
        if (propImageSourceInfo_.has_value()) {
            src = propImageSourceInfo_->GetSrc();
            if (src.find("resources") != std::string::npos) {
                auto num = src.find("resources");
                src = src.substr(num);
            }
            for (auto& character : src) {
                character = tolower(character);
            }
        }
        json->Put("src", src.c_str());
        json->Put("rawSrc", propImageSourceInfo_->GetSrc().c_str());
        json->Put("moduleName", propImageSourceInfo_->GetModuleName().c_str());
        ACE_PROPERTY_TO_JSON_VALUE(propImageSizeStyle_, ImageSizeStyle);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        static const std::unordered_map<std::string, ImageFit> uMap {
            { "ImageFit.Fill", ImageFit::FILL },
            { "ImageFit.Contain", ImageFit::CONTAIN },
            { "ImageFit.Cover", ImageFit::COVER },
            { "ImageFit.FitWidth", ImageFit::FITWIDTH },
            { "ImageFit.FitHeight", ImageFit::FITHEIGHT },
            { "ImageFit.None", ImageFit::NONE },
            { "ImageFit.ScaleDown", ImageFit::SCALE_DOWN },
        };

        std::string src = json->GetString("rawSrc");
        std::string bundleName = AceApplicationInfo::GetInstance().GetPackageName();
        std::string moduleName = json->GetString("moduleName");
        UpdateImageSourceInfo(ImageSourceInfo(src, bundleName, moduleName));
        auto objectFit = json->GetString("objectFit");
        UpdateImageFit(uMap.count(objectFit) ? uMap.at(objectFit) : ImageFit::COVER);
        UpdateAutoResize(json->GetString("autoResize") == "true" ? true : false);
        /* register image frame node to pipeline context to receive memory level notification and window state change
         * notification */
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        pipeline->AddNodesToNotifyMemoryLevel(frameNode->GetId());
        pipeline->AddWindowStateChangedCallback(frameNode->GetId());
        LayoutProperty::FromJson(json);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageFit, ImageFit, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Alt, ImageSourceInfo, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_GROUP(ImageSizeStyle, ImageSizeStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImageSizeStyle, AutoResize, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImageSizeStyle, SourceSize, SizeF, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImageSizeStyle, FitOriginalSize, bool, PROPERTY_UPDATE_BY_CHILD_REQUEST);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(VerticalAlign, VerticalAlign, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(ImageLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_LAYOUT_PROPERTY_H
