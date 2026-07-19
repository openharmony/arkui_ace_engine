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

#include "jsnapi_expo.h"

#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/js_ui_index.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"

namespace OHOS::Ace::Framework {
namespace {

template<typename Rect, typename Offset>
JSRef<JSObject> CreateAreaObject(const EcmaVM* vm, const Rect& rect, const Offset& origin)
{
    auto localOffset = rect.GetOffset();
    auto d = PipelineBase::GetCurrentDensity();

    // offset: { x, y }
    Local<JSValueRef> offsetKeys[] = {
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::X)),
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::Y)),
    };
    panda::PropertyAttribute offsetAttrs[] = {
        panda::PropertyAttribute(panda::NumberRef::New(vm,
            localOffset.GetX() / d), true, true, true),
        panda::PropertyAttribute(panda::NumberRef::New(vm,
            localOffset.GetY() / d), true, true, true),
    };
    auto offsetObj = panda::ObjectRef::NewWithProperties(vm, ArraySize(offsetKeys), offsetKeys, offsetAttrs);

    // globalOffset: { x, y }
    Local<JSValueRef> globalKeys[] = {
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::X)),
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::Y)),
    };
    panda::PropertyAttribute globalAttrs[] = {
        panda::PropertyAttribute(panda::NumberRef::New(vm,
            (localOffset.GetX() + origin.GetX()) / d), true, true, true),
        panda::PropertyAttribute(panda::NumberRef::New(vm,
            (localOffset.GetY() + origin.GetY()) / d), true, true, true),
    };
    auto globalOffsetObj = panda::ObjectRef::NewWithProperties(vm, ArraySize(globalKeys), globalKeys, globalAttrs);

    // area: { pos, position, globalPos, globalPosition, width, height }
    Local<JSValueRef> areaKeys[] = {
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::POS)),
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::POSITION)),
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::GLOBAL_POS)),
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::GLOBAL_POSITION)),
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::WIDTH)),
        panda::ExternalStringCache::GetCachedString(vm, static_cast<int32_t>(ArkUIIndex::HEIGHT)),
    };
    panda::PropertyAttribute areaAttrs[] = {
        panda::PropertyAttribute(offsetObj, true, true, true),
        panda::PropertyAttribute(offsetObj, true, true, true),
        panda::PropertyAttribute(globalOffsetObj, true, true, true),
        panda::PropertyAttribute(globalOffsetObj, true, true, true),
        panda::PropertyAttribute(panda::NumberRef::New(vm,
            rect.Width() / d), true, true, true),
        panda::PropertyAttribute(panda::NumberRef::New(vm,
            rect.Height() / d), true, true, true),
    };
    auto areaObj = panda::ObjectRef::NewWithProperties(vm, ArraySize(areaKeys), areaKeys, areaAttrs);

    return JSRef<JSObject>::FastMake(vm, areaObj);
}

} // namespace

void JsOnAreaChangeFunction::Execute(
    const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin)
{
    auto vm = jsFunction_->GetEcmaVM();
    panda::JsiFastNativeScope fastNativeScope(vm);
    auto oldArea = CreateAreaObject<Rect, Offset>(vm, oldRect, oldOrigin);
    auto area = CreateAreaObject<Rect, Offset>(vm, rect, origin);
    JSRef<JSVal> params[2];
    params[0] = oldArea;
    params[1] = area;
    JsFunction::ExecuteJS(2, params);
}

void JsOnAreaChangeFunction::Execute(
    const NG::RectF& oldRect, const NG::OffsetF& oldOrigin, const NG::RectF& rect, const NG::OffsetF& origin)
{
    auto vm = jsFunction_->GetEcmaVM();
    panda::JsiFastNativeScope fastNativeScope(vm);
    auto oldArea = CreateAreaObject<NG::RectF, NG::OffsetF>(vm, oldRect, oldOrigin);
    auto area = CreateAreaObject<NG::RectF, NG::OffsetF>(vm, rect, origin);
    JSRef<JSVal> params[2];
    params[0] = oldArea;
    params[1] = area;
    JsFunction::ExecuteJS(2, params);
}

} // namespace OHOS::Ace::Framework
