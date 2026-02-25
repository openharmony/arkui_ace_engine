/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/sub_tab_bar_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SubTabBarStyleAccessor {
ImageType ConvertToImageType(DrawableType type)
{
    switch (type) {
        case DrawableType::BASE:
            return ImageType::DRAWABLE;
        case DrawableType::LAYERED:
            return ImageType::LAYERED_DRAWABLE;
        case DrawableType::ANIMATED:
            return ImageType::ANIMATED_DRAWABLE;
        case DrawableType::PIXELMAP:
            return ImageType::PIXELMAP_DRAWABLE;
        default:
            return ImageType::BASE;
    }
}
bool ParseImageInfoConfig(const Ark_DrawableTabBarIndicator& src, ImageInfoConfig& config)
{
    if (src.drawable.tag == INTEROP_TAG_UNDEFINED) {
        return false;
    }
    auto desc = Converter::Convert<DrawableDescriptor*>(src.drawable.value);
    auto drawableType = desc->GetDrawableType();
    config.type = ConvertToImageType(drawableType);
    if (config.type == ImageType::ANIMATED_DRAWABLE) {
        config.drawable = Referenced::Claim<DrawableDescriptor>(desc);
        return true;
    } else if (config.type == ImageType::PIXELMAP_DRAWABLE || config.type == ImageType::DRAWABLE ||
               config.type == ImageType::LAYERED_DRAWABLE) {
        config.pixelMap = desc->GetPixelMap();
        return true;
    }
    return false;
}
void ParseIndicatorStyle(const Ark_DrawableTabBarIndicator& src, IndicatorStyle& indicatorStyle)
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    if (tabTheme) {
        indicatorStyle.color = tabTheme->GetActiveIndicatorColor();
        indicatorStyle.height = tabTheme->GetActiveIndicatorWidth();
        indicatorStyle.marginTop = tabTheme->GetSubTabIndicatorGap();
    }
    std::optional<Dimension> height = Converter::OptConvert<Dimension>(src.height);
    Validator::ValidateNonNegative(height);
    Validator::ValidateNonPercent(height);
    if (height) {
        indicatorStyle.height = height.value();
    }
    std::optional<Dimension> width = Converter::OptConvert<Dimension>(src.width);
    Validator::ValidateNonNegative(width);
    Validator::ValidateNonPercent(width);
    if (width) {
        indicatorStyle.width = width.value();
    }
    std::optional<Dimension> borderRadius = Converter::OptConvert<Dimension>(src.borderRadius);
    Validator::ValidateNonNegative(borderRadius);
    Validator::ValidateNonPercent(borderRadius);
    if (borderRadius) {
        indicatorStyle.borderRadius = borderRadius.value();
    }
    std::optional<Dimension> marginTop = Converter::OptConvert<Dimension>(src.marginTop);
    Validator::ValidateNonNegative(marginTop);
    Validator::ValidateNonPercent(marginTop);
    if (marginTop) {
        indicatorStyle.marginTop = marginTop.value();
    }
}
void DestroyPeerImpl(Ark_SubTabBarStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_SubTabBarStyle ConstructImpl(const Ark_Union_ResourceStr_ComponentContentBase* content)
{
    auto peer = PeerUtils::CreatePeer<SubTabBarStylePeer>();
    std::optional<std::string> cntnt = std::nullopt;
    Converter::VisitUnionPtr(content,
        [&cntnt](const Ark_ResourceStr& arkContent) {
            cntnt = Converter::OptConvert<std::string>(arkContent);
        },
        [](const Ark_ComponentContentBase& arkContent) {
            LOGE("SubTabBarStyleAccessor.ConstructImpl content (type Ark_ComponentContent) is not supported yet.");
        },
        []() {}
    );
    peer->content = cntnt;
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_SubTabBarStyle OfImpl(const Ark_Union_ResourceStr_ComponentContentBase* content)
{
    return ConstructImpl(content);
}
Ark_SubTabBarStyle Indicator0Impl(Ark_SubTabBarStyle peer,
                                  const Ark_SubTabBarIndicatorStyle* style)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->indicator = Converter::OptConvertPtr<IndicatorStyle>(style);
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle Indicator1Impl(Ark_SubTabBarStyle peer,
                                  const Ark_Union_SubTabBarIndicatorStyle_DrawableTabBarIndicator* value)
{
    CHECK_NULL_RETURN(peer, peer);
    Converter::VisitUnionPtr(value,
        [&peer](const Ark_SubTabBarIndicatorStyle& arkStyle) {
            peer->indicator = Converter::OptConvert<IndicatorStyle>(arkStyle);
        },
        [&peer](const Ark_DrawableTabBarIndicator& arkIndicator) {
            ImageInfoConfig config;
            IndicatorStyle indicatorStyle;
            bool isDrawableIndicator = ParseImageInfoConfig(arkIndicator, config);
            ParseIndicatorStyle(arkIndicator, indicatorStyle);
            if (isDrawableIndicator) {
                peer->imageInfoConfig = config;
            }
            peer->indicatorColorByUser = false;
            peer->indicator = indicatorStyle;
        },
        []() {}
    );

    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle SelectedModeImpl(Ark_SubTabBarStyle peer,
                                    Ark_SelectedMode value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->selectedMode = Converter::OptConvert<SelectedMode>(value);
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle BoardImpl(Ark_SubTabBarStyle peer,
                             const Ark_BoardStyle* value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->board = Converter::OptConvertPtr<BoardStyle>(value);
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle LabelStyleImpl(Ark_SubTabBarStyle peer,
                                  const Ark_TabBarLabelStyle* style)
{
    CHECK_NULL_RETURN(peer, peer);
    auto optLabelStyle = Converter::OptConvertPtr<LabelStyle>(style);
    if (optLabelStyle) {
        auto labelFont = Converter::OptConvertFromFont(style->font, true);
        optLabelStyle->fontSize = labelFont.fontSize;
        optLabelStyle->fontStyle = labelFont.fontStyle;
        optLabelStyle->fontWeight = labelFont.fontWeight;
        if (labelFont.fontFamilies.size() > 0) {
            optLabelStyle->fontFamily = labelFont.fontFamilies;
        }
    }
    peer->labelStyle = optLabelStyle;
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle Padding0Impl(Ark_SubTabBarStyle peer,
                                const Ark_Union_Padding_Dimension* value)
{
    CHECK_NULL_RETURN(peer, peer);
    std::optional<PaddingProperty> optPadding;
    bool useLocalizedPadding = false;
    Converter::VisitUnionPtr(value,
        [&optPadding](const Ark_Padding& arkPadding) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkPadding);
        },
        [&optPadding](const Ark_Dimension& arkLength) {
            optPadding = Converter::OptConvert<PaddingProperty>(arkLength);
        },
        []() {}
    );
    Validator::ValidatePaddingProperty(optPadding);
    peer->padding = optPadding;
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle Padding1Impl(Ark_SubTabBarStyle peer,
                                const Ark_LocalizedPadding* padding)
{
    CHECK_NULL_RETURN(peer, peer);
    std::optional<PaddingProperty> optPadding = Converter::OptConvertPtr<PaddingProperty>(padding);
    bool useLocalizedPadding = true;
    Validator::ValidatePaddingProperty(optPadding);
    peer->padding = optPadding;
    peer->useLocalizedPadding = useLocalizedPadding;
    peer->IncRefCount();
    return peer;
}
Ark_SubTabBarStyle IdImpl(Ark_SubTabBarStyle peer,
                          const Ark_String* value)
{
    CHECK_NULL_RETURN(peer, peer);
    peer->id = Converter::OptConvertPtr<std::string>(value);
    peer->IncRefCount();
    return peer;
}
} // SubTabBarStyleAccessor
const GENERATED_ArkUISubTabBarStyleAccessor* GetSubTabBarStyleAccessor()
{
    static const GENERATED_ArkUISubTabBarStyleAccessor SubTabBarStyleAccessorImpl {
        SubTabBarStyleAccessor::DestroyPeerImpl,
        SubTabBarStyleAccessor::ConstructImpl,
        SubTabBarStyleAccessor::GetFinalizerImpl,
        SubTabBarStyleAccessor::OfImpl,
        SubTabBarStyleAccessor::Indicator0Impl,
        SubTabBarStyleAccessor::Indicator1Impl,
        SubTabBarStyleAccessor::SelectedModeImpl,
        SubTabBarStyleAccessor::BoardImpl,
        SubTabBarStyleAccessor::LabelStyleImpl,
        SubTabBarStyleAccessor::Padding0Impl,
        SubTabBarStyleAccessor::Padding1Impl,
        SubTabBarStyleAccessor::IdImpl,
    };
    return &SubTabBarStyleAccessorImpl;
}

}
