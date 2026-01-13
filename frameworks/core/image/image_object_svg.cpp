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

#include "core/image/image_object.h"

#include "compatible/components/svg/svg_compatible_modifier.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace {
RefPtr<ImageObject> GetImageSvgDomObj(ImageSourceInfo source, const std::unique_ptr<SkMemoryStream>& svgStream,
    const RefPtr<PipelineBase>& context, std::optional<Color>& color)
{
    auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("svg");
    CHECK_NULL_RETURN(loader, nullptr);
    auto* modifier = reinterpret_cast<const ArkUISvgCompatibleModifier*>(loader->GetCustomModifier());
    CHECK_NULL_RETURN(modifier, nullptr);
    const Color* themeColor = color.has_value() ? &color.value() : nullptr;
    auto svgDom = modifier->createSvgDom(
        svgStream.get(), reinterpret_cast<PipelineContext*>(AceType::RawPtr(context)), themeColor);
    CHECK_NULL_RETURN(svgDom, nullptr);
    return svgDom ? AceType::MakeRefPtr<SvgImageObject>(source, Size(), 1, svgDom) : nullptr;
}
} // namespace OHOS::Ace