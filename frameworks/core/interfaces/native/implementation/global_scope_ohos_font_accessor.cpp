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

#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<Ark_Resource_Simple>& dst, const Ark_Resource& src)
{
    ResourceConverter converter(src);
    auto resourceString = converter.ToString();
    if (resourceString) {
        Ark_Resource_Simple temp;
        temp.content = resourceString.value();
        temp.bundleName = converter.BundleName();
        temp.moduleName = converter.ModuleName();
        dst = temp;
    } else {
        LOGE("Not a string resource: %{public}s:%{public}s\n", converter.BundleName().c_str(),
            converter.ModuleName().c_str());
    }
}
template<>
void AssignCast(std::optional<Ark_Resource_Simple>& dst, const Ark_String& src)
{
    std::string str = Converter::Convert<std::string>(src);
    if (!str.empty()) {
        Ark_Resource_Simple temp;
        temp.content = str;
        dst = temp;
    }
}
template<>
FontInfo Convert(const Ark_font_FontInfo& src)
{
    return {
        .path = Convert<std::string>(src.path),
        .postScriptName = Convert<std::string>(src.postScriptName),
        .fullName = Convert<std::string>(src.fullName),
        .family = Convert<std::string>(src.family),
        .subfamily = Convert<std::string>(src.subfamily),
        .weight = Convert<uint32_t>(src.weight),
        .width = Convert<uint32_t>(src.width),
        .italic = Convert<bool>(src.italic),
        .monoSpace = Convert<bool>(src.monoSpace),
        .symbolic = Convert<bool>(src.symbolic),
    };
}
void AssignArkValue(Ark_font_FontInfo& dst, const FontInfo& src, ConvContext *ctx)
{
    dst.path = ArkValue<Ark_String>(src.path, ctx);
    dst.postScriptName = ArkValue<Ark_String>(src.postScriptName, ctx);
    dst.fullName = ArkValue<Ark_String>(src.fullName, ctx);
    dst.family = ArkValue<Ark_String>(src.family, ctx);
    dst.subfamily = ArkValue<Ark_String>(src.subfamily, ctx);
    dst.weight = ArkValue<Ark_Int32>(src.weight);
    dst.width = ArkValue<Ark_Int32>(src.width);
    dst.italic = ArkValue<Ark_Boolean>(src.italic);
    dst.monoSpace = ArkValue<Ark_Boolean>(src.monoSpace);
    dst.symbolic = ArkValue<Ark_Boolean>(src.symbolic);
}
void AssignArkValue(Ark_font_UIFontFallbackInfo& dst, const FallbackInfo& src, ConvContext* ctx)
{
    dst.family = Converter::ArkValue<Ark_String>(src.familyName, ctx);
    dst.language = Converter::ArkValue<Ark_String>(src.font, ctx);
}
void AssignArkValue(Ark_font_UIFontFallbackGroupInfo& dst, const FallbackGroup& src, ConvContext* ctx)
{
    dst.fontSetName = Converter::ArkValue<Ark_String>(src.groupName, ctx);
    dst.fallback = Converter::ArkValue<Array_font_UIFontFallbackInfo>(src.fallbackInfoSet, ctx);
}
void AssignArkValue(Ark_font_UIFontAdjustInfo& dst, const AdjustInfo& src, ConvContext* ctx)
{
    dst.weight = Converter::ArkValue<Ark_Float64>(src.origValue);
    dst.to = Converter::ArkValue<Ark_Int32>(src.newValue);
}
void AssignArkValue(Ark_font_UIFontAliasInfo& dst, const AliasInfo& src, ConvContext* ctx)
{
    dst.name = Converter::ArkValue<Ark_String>(src.familyName, ctx);
    dst.weight = Converter::ArkValue<Ark_Float64>(src.weight);
}
void AssignArkValue(Ark_font_UIFontGenericInfo& dst, const FontGenericInfo& src, ConvContext* ctx)
{
    dst.family = Converter::ArkValue<Ark_String>(src.familyName, ctx);
    dst.alias = Converter::ArkValue<Array_font_UIFontAliasInfo>(src.aliasSet, ctx);
    dst.adjust = Converter::ArkValue<Array_font_UIFontAdjustInfo>(src.adjustSet, ctx);
}
void AssignArkValue(Ark_font_UIFontConfig& dst, const FontConfigJsonInfo& src, ConvContext* ctx)
{
    dst.fontDir = Converter::ArkValue<Array_String>(src.fontDirSet, ctx);
    dst.generic = Converter::ArkValue<Array_font_UIFontGenericInfo>(src.genericSet, ctx);
    dst.fallbackGroups = Converter::ArkValue<Array_font_UIFontFallbackGroupInfo>(src.fallbackGroupSet, ctx);
}
} /* namespace OHOS::Ace::NG::Converter */

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScope_ohos_fontAccessor {
void RegisterFontImpl(const Ark_font_FontOptions* options)
{
    CHECK_NULL_VOID(options);
    std::string familyName;
    std::string familySrc;
    std::string bundleName;
    std::string moduleName;
    if (auto familyNameOpt = Converter::OptConvert<Converter::FontFamilies>(options->familyName); familyNameOpt) {
        familyName = !familyNameOpt->families.empty() ? familyNameOpt->families.front() : "";
    }
    if (auto familySrcOpt = Converter::OptConvert<Converter::Ark_Resource_Simple>(options->familySrc);
        familySrcOpt) {
        familySrc = familySrcOpt->content;
        bundleName = familySrcOpt->bundleName;
        moduleName = familySrcOpt->moduleName;
    }
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        pipeline->RegisterFont(familyName, familySrc, bundleName, moduleName);
    }
}
Array_String GetSystemFontListImpl()
{
    StringArray fontList;
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        pipeline->GetSystemFontList(fontList);
    }
    return Converter::ArkValue<Array_String>(fontList, Converter::FC);
}
Ark_font_FontInfo GetFontByNameImpl(const Ark_String* fontName)
{
    FontInfo fontInfo;
    auto fontNameCasted = Converter::Convert<std::string>(*fontName);
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        pipeline->GetSystemFont(fontNameCasted, fontInfo);
    }
    return Converter::ArkValue<Ark_font_FontInfo>(fontInfo, Converter::FC);
}
Ark_font_UIFontConfig GetUIFontConfigImpl()
{
    FontConfigJsonInfo fontConfigJsonInfo;
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        pipeline->GetUIFontConfig(fontConfigJsonInfo);
    }
    return Converter::ArkValue<Ark_font_UIFontConfig>(fontConfigJsonInfo, Converter::FC);
}
} // GlobalScope_ohos_fontAccessor
const GENERATED_ArkUIGlobalScope_ohos_fontAccessor* GetGlobalScope_ohos_fontAccessor()
{
    static const GENERATED_ArkUIGlobalScope_ohos_fontAccessor GlobalScope_ohos_fontAccessorImpl {
        GlobalScope_ohos_fontAccessor::RegisterFontImpl,
        GlobalScope_ohos_fontAccessor::GetSystemFontListImpl,
        GlobalScope_ohos_fontAccessor::GetFontByNameImpl,
        GlobalScope_ohos_fontAccessor::GetUIFontConfigImpl,
    };
    return &GlobalScope_ohos_fontAccessorImpl;
}
}
