/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_TEXT_LAYOUT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_TEXT_LAYOUT_H

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/style_string/js_span_object.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Framework {

class JSTextLayout : public Referenced {
public:
    JSTextLayout() = default;
    ~JSTextLayout() override = default;

    static void JSBind(BindingTarget globalObj);
 
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsTextlayout = Referenced::MakeRefPtr<JSTextLayout>();
        jsTextlayout->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsTextlayout));
    }
 
    static void Destructor(JSTextLayout* jsTextlayout)
    {
        if (jsTextlayout) {
            jsTextlayout->DecRefCount();
        }
    }

    static CalcDimension ParseLengthMetrics(const JSRef<JSObject>& obj);
    static void GetParagraphs(const JSCallbackInfo& info);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_STYLE_STRING_JS_TEXT_LAYOUT_H