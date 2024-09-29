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

namespace OHOS::Ace {
RefPtr<ImageObject> GetImageSvgDomObj(ImageSourceInfo source, const std::unique_ptr<SkMemoryStream >& svgStream,
    const RefPtr<PipelineBase>& context, std::optional<Color>& color)
{
    auto svgDom = SvgDom::CreateSvgDom(*svgStream, AceType::DynamicCast<PipelineContext>(context), color);
    return svgDom ? AceType::MakeRefPtr<SvgImageObject>(source, Size(), 1, svgDom) : nullptr;
}
}