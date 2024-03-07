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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_on_size_change_function.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"

namespace OHOS::Ace::Framework {
void JsOnSizeChangeFunction::Execute(const NG::RectF& oldRect, const NG::RectF& rect)
{
    JSRef<JSObject> oldSize = JSRef<JSObject>::New();
    JSRef<JSObject> newSize = JSRef<JSObject>::New();
    oldSize->SetProperty<double>("width", PipelineBase::Px2VpWithCurrentDensity(oldRect.Width()));
    oldSize->SetProperty<double>("height", PipelineBase::Px2VpWithCurrentDensity(oldRect.Height()));
    newSize->SetProperty<double>("width", PipelineBase::Px2VpWithCurrentDensity(rect.Width()));
    newSize->SetProperty<double>("height", PipelineBase::Px2VpWithCurrentDensity(rect.Height()));
    JSRef<JSVal> params[2];
    params[0] = oldSize;
    params[1] = newSize;
    JsFunction::ExecuteJS(2, params);
}
} // namespace OHOS::Ace::Framework
