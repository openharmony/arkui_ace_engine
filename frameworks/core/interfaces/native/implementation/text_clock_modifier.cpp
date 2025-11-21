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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_static.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/interfaces/native/implementation/text_clock_controller_peer_impl.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;
const std::vector<std::string> DEFAULT_FONT_FAMILY = { "HarmonyOS Sans" };
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
constexpr Dimension DEFAULT_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
const std::string FORM_FORMAT = "hh:mm";
const std::string FORM_FORMAT_24H = "HH:mm";
const std::string DEFAULT_FORMAT = "aa hh:mm:ss";
const std::string DEFAULT_FORMAT_24H = "HH:mm:ss";
struct TextClockOptions {
    std::optional<float> timeZoneOffset = std::nullopt;
    TextClockControllerPeer* peerController = nullptr;
};
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
    template<>
    TextClockOptions Convert(const Ark_TextClockOptions& src)
    {
        TextClockOptions dst;
        auto value = OptConvert<float>(src.timeZoneOffset);
        // valid hoursWest is within [-14, 12]
        Validator::ValidateByRange(value, -14.0f, 12.0f);
        dst.timeZoneOffset = value;
        dst.peerController = OptConvert<Ark_TextClockController>(src.controller).value_or(nullptr);
        return dst;
    }
} // namespace OHOS::Ace::NG::Converter


namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextClockModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TextClockModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TextClockModifier
namespace TextClockInterfaceModifier {
void SetTextClockOptionsImpl(Ark_NativePointer node,
                             const Opt_TextClockOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textClockOptionsOpt = Converter::OptConvertPtr<TextClockOptions>(options);
    if (textClockOptionsOpt.has_value()) {
        TextClockModelStatic::SetHoursWest(frameNode, textClockOptionsOpt.value().timeZoneOffset);

        auto controller = TextClockModelNG::InitTextController(frameNode);
        CHECK_NULL_VOID(controller);
        auto peerImplPtr = textClockOptionsOpt.value().peerController;
        CHECK_NULL_VOID(peerImplPtr);
        peerImplPtr->controller = std::move(controller);
    }
}
} // TextClockInterfaceModifier
namespace TextClockAttributeModifier {
void SetFormatImpl(Ark_NativePointer node,
                   const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        bool isForm = false;
        auto context = frameNode->GetContext();
        CHECK_NULL_VOID(context);
        auto container = Container::Current();
        bool isDynamicComponent = container && container->IsDynamicRender();
        isForm = context->IsFormRender() && !isDynamicComponent;
        std::string defaultFormat;
        if (isForm) {
            defaultFormat = FORM_FORMAT;
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) &&
                SystemProperties::Is24HourClock()) {
                defaultFormat = FORM_FORMAT_24H;
            }
        } else {
            defaultFormat = DEFAULT_FORMAT;
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) &&
                SystemProperties::Is24HourClock()) {
                defaultFormat = DEFAULT_FORMAT_24H;
            }
        }
        TextClockModelStatic::SetFormat(frameNode, std::optional<std::string>(defaultFormat));
        return;
    }
    TextClockModelStatic::SetFormat(frameNode, convValue);
}
void SetOnDateChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_I64_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextClockModelNG::SetOnDateChange(frameNode, nullptr);
        return;
    }
    auto onDateChange = [arkCallback = CallbackHelper(*optValue)](const std::string& data) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Int64>(std::stoi(data)));
    };
    TextClockModelNG::SetOnDateChange(frameNode, std::move(onDateChange));
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    TextClockModelStatic::SetFontColor(frameNode, convValue);
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> convValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        convValue = Converter::OptConvertFromArkNumStrRes<Ark_Length, Ark_Number>(value->value, DimensionUnit::FP);
    }
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    TextClockModelStatic::SetFontSize(frameNode, convValue.value_or(DEFAULT_FONT_SIZE));
}
void SetFontStyleImpl(Ark_NativePointer node,
                      const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Ace::FontStyle>(value);
    TextClockModelStatic::SetFontStyle(frameNode, convValue.value_or(DEFAULT_FONT_STYLE));
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_I32_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Ace::FontWeight>(value);
    TextClockModelStatic::SetFontWeight(frameNode, convValue.value_or(DEFAULT_FONT_WEIGHT));
}
void SetFontFamilyImpl(Ark_NativePointer node,
                       const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Converter::FontFamilies>(value);
    if (!convValue) {
        TextClockModelNG::SetFontFamily(frameNode, DEFAULT_FONT_FAMILY);
        return;
    }
    StringArray families;
    if (auto fontfamiliesOpt = convValue; fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    TextClockModelNG::SetFontFamily(frameNode, families);
}
void SetTextShadowImpl(Ark_NativePointer node,
                       const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Shadow> shadowListResult;
    auto shadowList = Converter::OptConvert<std::vector<Shadow>>(*value);
    if (shadowList.has_value()) {
        shadowListResult = shadowList.value();
    }
    TextClockModelNG::SetTextShadow(frameNode, shadowListResult);
}
void SetFontFeatureImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        std::string strValue = "normal";
        TextClockModelStatic::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
        return;
    }
    TextClockModelStatic::SetFontFeature(frameNode, ParseFontFeatureSettings(*convValue));
}
void SetDateTimeOptionsImpl(Ark_NativePointer node,
                            const Opt_intl_DateTimeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto dateTimeOptions = Converter::OptConvertPtr<DateTimeType>(value);
    std::optional<ZeroPrefixType> hourType;
    if (dateTimeOptions) {
        hourType = dateTimeOptions->hourType;
    }
    TextClockModelStatic::SetDateTimeOptions(frameNode, hourType);
}
} // TextClockAttributeModifier
const GENERATED_ArkUITextClockModifier* GetTextClockModifier()
{
    static const GENERATED_ArkUITextClockModifier ArkUITextClockModifierImpl {
        TextClockModifier::ConstructImpl,
        TextClockInterfaceModifier::SetTextClockOptionsImpl,
        TextClockAttributeModifier::SetFormatImpl,
        TextClockAttributeModifier::SetOnDateChangeImpl,
        TextClockAttributeModifier::SetFontColorImpl,
        TextClockAttributeModifier::SetFontSizeImpl,
        TextClockAttributeModifier::SetFontStyleImpl,
        TextClockAttributeModifier::SetFontWeightImpl,
        TextClockAttributeModifier::SetFontFamilyImpl,
        TextClockAttributeModifier::SetTextShadowImpl,
        TextClockAttributeModifier::SetFontFeatureImpl,
        TextClockAttributeModifier::SetDateTimeOptionsImpl,
    };
    return &ArkUITextClockModifierImpl;
}

}
