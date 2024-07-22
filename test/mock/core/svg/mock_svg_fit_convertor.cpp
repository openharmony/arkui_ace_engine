/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/svg/svg_fit_convertor.h"

namespace OHOS::Ace::NG {
const std::vector<void (*)(RSCanvas& canvas,
    const Size& layoutSize, const Size& svgSize)> SvgFitConvertor::FIT_OPERATIONS = {
    ApplyFill,
};
void SvgFitConvertor::ApplyFit(ImageFit imageFit, RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{
    FIT_OPERATIONS[0](canvas, layoutSize, svgSize);
}

void SvgFitConvertor::ApplyFill(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyContain(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyCover(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyWidth(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyHeight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyNone(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyScaleDown(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyAlignmentTopLeft(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyAlignmentTop(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyAlignmentTopRight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyAlignmentCenterLeft(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyAlignmentCenter(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyAlignmentCenterRight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyAlignmentBottomLeft(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyAlignmentBottom(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::ApplyAlignmentBottomRight(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize)
{}

void SvgFitConvertor::AdjustContentFit(RSCanvas& canvas, const Size& layoutSize, const Size& svgSize,
    float svgScale, Alignment alignMent)
{}

void SvgFitConvertor::DrawNothing(RSCanvas& canvas)
{}
}