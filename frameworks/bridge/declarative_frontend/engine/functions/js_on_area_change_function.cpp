/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_on_area_change_function.h"

#include "frameworks/bridge/declarative_frontend/engine/js_types.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"

namespace OHOS::Ace::Framework {
namespace {

template<typename Rect, typename Offset>
JSRef<JSObject> CreateAreaObject(const Rect& rect, const Offset& origin)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> area = objectTemplate->NewInstance();
    JSRef<JSObject> offset = objectTemplate->NewInstance();
    JSRef<JSObject> globalOffset = objectTemplate->NewInstance();
    auto localOffset = rect.GetOffset();
    offset->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    offset->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    globalOffset->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX() + origin.GetX()));
    globalOffset->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY() + origin.GetY()));
    // keep compatible, need remove after
    area->SetPropertyObject("pos", offset);
    area->SetPropertyObject("position", offset);
    // keep compatible, need remove after
    area->SetPropertyObject("globalPos", globalOffset);
    area->SetPropertyObject("globalPosition", globalOffset);
    area->SetProperty<double>("width", PipelineBase::Px2VpWithCurrentDensity(rect.Width()));
    area->SetProperty<double>("height", PipelineBase::Px2VpWithCurrentDensity(rect.Height()));
    return area;
}

} // namespace

void JsOnAreaChangeFunction::Execute(
    const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin)
{
    panda::JsiFastNativeScope fastNativeScope(jsFunction_->GetEcmaVM());
    auto oldArea = CreateAreaObject<Rect, Offset>(oldRect, oldOrigin);
    auto area = CreateAreaObject<Rect, Offset>(rect, origin);
    JSRef<JSVal> params[2];
    params[0] = oldArea;
    params[1] = area;
    JsFunction::ExecuteJS(2, params);
}

void JsOnAreaChangeFunction::Execute(
    const NG::RectF& oldRect, const NG::OffsetF& oldOrigin, const NG::RectF& rect, const NG::OffsetF& origin)
{
    panda::JsiFastNativeScope fastNativeScope(jsFunction_->GetEcmaVM());
    auto oldArea = CreateAreaObject<NG::RectF, NG::OffsetF>(oldRect, oldOrigin);
    auto area = CreateAreaObject<NG::RectF, NG::OffsetF>(rect, origin);
    JSRef<JSVal> params[2];
    params[0] = oldArea;
    params[1] = area;
    JsFunction::ExecuteJS(2, params);
}

} // namespace OHOS::Ace::Framework
