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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_MEASURE_LAYOUT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_MEASURE_LAYOUT_H

#include <utility>

#include "base/memory/ace_type.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT ViewMeasureLayout : AceType {
    DECLARE_ACE_TYPE(ViewMeasureLayout, AceType);

public:
    ViewMeasureLayout() = default;
    ~ViewMeasureLayout() override
    {
        LOGD("Destroy: ViewMeasureLayout");
    }

#ifdef USE_ARK_ENGINE
    static panda::Local<panda::JSValueRef> JSMeasure(panda::JsiRuntimeCallInfo* info);
    static panda::Local<panda::JSValueRef> JSLayout(panda::JsiRuntimeCallInfo* info);
    static panda::Local<panda::JSValueRef> JSPlaceChildren(panda::JsiRuntimeCallInfo* info);

    static void SetMeasureChildren(std::list<RefPtr<NG::LayoutWrapper>> children)
    {
        measureChildren_ = std::move(children);
        iterMeasureChildren_ = measureChildren_.begin();
    }

    static void SetLayoutChildren(std::list<RefPtr<NG::LayoutWrapper>> children)
    {
        layoutChildren_ = std::move(children);
        iterLayoutChildren_ = layoutChildren_.begin();
    }

    static void SetDefaultMeasureConstraint(NG::LayoutConstraintF constraint)
    {
        measureDefaultConstraint_ = constraint;
    }

private:
    static thread_local std::list<RefPtr<NG::LayoutWrapper>> measureChildren_;
    static thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator iterMeasureChildren_;
    static thread_local std::list<RefPtr<NG::LayoutWrapper>> layoutChildren_;
    static thread_local std::list<RefPtr<NG::LayoutWrapper>>::iterator iterLayoutChildren_;
    static thread_local NG::LayoutConstraintF measureDefaultConstraint_;
#endif
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_MEASURE_LAYOUT_H