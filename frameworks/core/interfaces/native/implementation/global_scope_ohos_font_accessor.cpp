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
#include "arkoala_api_generated.h"
#include "core/pipeline/pipeline_base.h"

struct GlobalScope_ohos_fontPeer {
    virtual ~GlobalScope_ohos_fontPeer() = default;
};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScope_ohos_fontAccessor {
void RegisterFontImpl(const Ark_FontOptions* options)
{
    CHECK_NULL_VOID(options);
    std::string familyName;
    if (auto familyNameOpt = Converter::OptConvert<Converter::FontFamilies>(options->familyName); familyNameOpt) {
        familyName = !familyNameOpt->families.empty() ? familyNameOpt->families.front() : "";
    }
    std::string familySrc;
    if (auto familySrcOpt = Converter::OptConvert<Converter::FontFamilies>(options->familySrc); familySrcOpt) {
        familySrc = !familySrcOpt->families.empty() ? familySrcOpt->families.front() : "";
    }
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        pipeline->RegisterFont(familyName, familySrc);
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
} // GlobalScope_ohos_fontAccessor
const GENERATED_ArkUIGlobalScope_ohos_fontAccessor* GetGlobalScope_ohos_fontAccessor()
{
    static const GENERATED_ArkUIGlobalScope_ohos_fontAccessor GlobalScope_ohos_fontAccessorImpl {
        GlobalScope_ohos_fontAccessor::RegisterFontImpl,
        GlobalScope_ohos_fontAccessor::GetSystemFontListImpl,
    };
    return &GlobalScope_ohos_fontAccessorImpl;
}

}
