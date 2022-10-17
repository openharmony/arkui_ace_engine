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

#include "bridge/declarative_frontend/jsview/js_view_measure_layout.h"

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/base/frame_node.h"

namespace OHOS::Ace::Framework {

#ifdef USE_ARK_ENGINE

thread_local std::list<RefPtr<NG::LayoutWrapper>> ViewMeasureLayout::measureChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator ViewMeasureLayout::iterMeasureChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>> ViewMeasureLayout::layoutChildren_;
thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator ViewMeasureLayout::iterLayoutChildren_;
thread_local NG::LayoutConstraintF ViewMeasureLayout::measureDefaultConstraint_;

void ViewMeasureLayout::JSMeasure(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSMeasure");

    if (info.Length() != 1 || !info[0]->IsObject()) {
        LOGE("JSMeasure arg is wrong");
        (*iterMeasureChildren_)->Measure(measureDefaultConstraint_);
        iterMeasureChildren_++;
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> minWidthValue = sizeObj->GetProperty("minWidth");
    Dimension minWidth;
    JSRef<JSVal> maxWidthValue = sizeObj->GetProperty("maxWidth");
    Dimension maxWidth;
    JSRef<JSVal> minHeightValue = sizeObj->GetProperty("minHeight");
    Dimension minHeight;
    JSRef<JSVal> maxHeightValue = sizeObj->GetProperty("maxHeight");
    Dimension maxHeight;

    if (JSViewAbstract::ParseJsDimensionVp(minWidthValue, minWidth)) {
        (*iterMeasureChildren_)
            ->GetLayoutProperty()
            ->UpdateCalcMinSize(NG::CalcSize(NG::CalcLength(minWidth), std::nullopt));
    }
    if (JSViewAbstract::ParseJsDimensionVp(maxWidthValue, maxWidth)) {
        (*iterMeasureChildren_)
            ->GetLayoutProperty()
            ->UpdateCalcMinSize(NG::CalcSize(NG::CalcLength(maxWidth), std::nullopt));
    }
    if (JSViewAbstract::ParseJsDimensionVp(minHeightValue, minHeight)) {
        (*iterMeasureChildren_)
            ->GetLayoutProperty()
            ->UpdateCalcMaxSize(NG::CalcSize(NG::CalcLength(minHeight), std::nullopt));
    }
    if (JSViewAbstract::ParseJsDimensionVp(maxHeightValue, maxHeight)) {
        (*iterMeasureChildren_)
            ->GetLayoutProperty()
            ->UpdateCalcMaxSize(NG::CalcSize(NG::CalcLength(maxHeight), std::nullopt));
    }
    (*iterMeasureChildren_)->Measure(measureDefaultConstraint_);
    iterMeasureChildren_++;
}

void ViewMeasureLayout::JSLayout(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("ViewMeasureLayout::JSLayout");

    if (info.Length() != 1 || !info[0]->IsObject()) {
        LOGE("JSLayout arg is wrong");
        (*iterMeasureChildren_)->Layout();
        iterMeasureChildren_++;
        return;
    }

    auto layoutInfo = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSObject> sizeObj = layoutInfo->GetProperty("position");
    JSRef<JSVal> xVal = sizeObj->GetProperty("x");
    JSRef<JSVal> yVal = sizeObj->GetProperty("y");
    Dimension dimenX;
    if (!JSViewAbstract::ParseJsDimensionVp(xVal, dimenX)) {
        LOGE("the x prop is illegal");
    }
    Dimension dimenY;
    if (!JSViewAbstract::ParseJsDimensionVp(yVal, dimenY)) {
        LOGE("the y prop is illegal");
    }
    (*iterMeasureChildren_)->GetHostNode()->GetRenderContext()->UpdatePosition({ dimenX, dimenY });
    iterMeasureChildren_++;
}

#endif

} // namespace OHOS::Ace::Framework