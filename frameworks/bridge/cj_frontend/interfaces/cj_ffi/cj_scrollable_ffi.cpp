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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scroll_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_scrollable_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_shape_ffi.h"

#include "cj_lambda.h"
#include "bridge/common/utils/utils.h"
#include "bridge/cj_frontend/cppview/shape_abstract.h"
#include "core/components/scroll/scroll_component.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::NG;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkScrollableBaseFlingSpeed(double speedLimit)
{
    ScrollableModelNG::SetMaxFlingSpeed(speedLimit);
}

void FfiOHOSAceFrameworkScrollableBaseFadingEdge(bool enabled)
{
    CalcDimension fadingEdgeLength = Dimension(32.0, DimensionUnit::VP);
    ScrollableModelNG::SetFadingEdge(enabled, fadingEdgeLength);
}

void FfiOHOSAceFrameworkScrollableBaseFadingEdgeOptions(bool enabled, double fadingEdge, int32_t fadingEdgeUnit)
{
    Dimension dimWidth(fadingEdge, static_cast<DimensionUnit>(fadingEdgeUnit));
    CalcDimension fadingEdgeLength = CalcDimension(dimWidth);
    ScrollableModelNG::SetFadingEdge(enabled, fadingEdgeLength);
}

void FfiOHOSAceFrameworkScrollableBaseClipMode(int32_t clip)
{
    ScrollableModelNG::SetContentClip(static_cast<NG::ContentClipMode>(clip), nullptr);
}

void FfiOHOSAceFrameworkScrollableBaseClipShape(int64_t shapeId)
{
    auto context = FFIData::GetData<NativeShapeAbstract>(shapeId);
    ScrollableModelNG::SetContentClip(NG::ContentClipMode::CUSTOM,
        AceType::DynamicCast<ShapeRect>(context->GetBasicShape()));
}

void FfiOHOSAceFrameworkScrollableBaseOnWillScroll(
    double (*callback)(double scrollOffset, int32_t state, int32_t source))
{
    auto lambda = [callback = CJLambda::Create(callback)]
        (const Dimension& offset, const ScrollState& state, ScrollSource scrollSource) {
        ScrollFrameResult scrollRes { .offset = offset };
        auto res =
            callback(offset.Value(), static_cast<int32_t>(state), static_cast<int32_t>(scrollSource));
        scrollRes.offset =  Dimension { res, DimensionUnit::VP };
        return scrollRes;
    };
    ScrollableModelNG::SetOnWillScroll(std::move(lambda));
}

void FfiOHOSAceFrameworkScrollableBaseOnDidScroll(void (*callback)(double scrollOffset, int32_t state))
{
    auto onScroll = [callback = CJLambda::Create(callback)](
                    const Dimension& scrollOffset, const ScrollState& scrollState) {
        callback(scrollOffset.Value(), static_cast<int32_t>(scrollState));
    };
    ScrollableModelNG::SetOnDidScroll(std::move(onScroll));
}
}
