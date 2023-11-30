/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_UTILS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_UTILS_H

#include "bridge/declarative_frontend/declarative_frontend.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/js_object_template.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "bridge/declarative_frontend/jsview/js_canvas_image_data.h"
#include "core/components/common/properties/text_style.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"

namespace OHOS::Ace::NG {
class ArkTSUtils {
public:
    static uint32_t ColorAlphaAdapt(uint32_t origin);
    static bool ParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result);
    static bool ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result);
    static bool ParseJsColorFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj, Color& result);
    static bool ParseJsDimensionFromResource(
        const EcmaVM* vm, const Local<JSValueRef>& jsObj, DimensionUnit dimensionUnit, CalcDimension& result);
    static bool ParseJsDimensionFromResourceNG(
        const EcmaVM* vm, const Local<JSValueRef>& jsObj, DimensionUnit dimensionUnit, CalcDimension& result);
    static bool ParseStringArray(const EcmaVM *vm, const Local<JSValueRef> &arg, char **array, int32_t defaultLength);
    static bool ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result);
    static bool ParseJsDouble(const EcmaVM *vm, const Local<JSValueRef> &value, double &result);
    static void ParseAllBorder(const EcmaVM *vm, const Local<JSValueRef> &args, CalcDimension &result);
    static bool ParseJsFontFamilies(
        const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result);
    static bool ParseJsDimension(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        DimensionUnit defaultUnit);
    static bool ParseJsDimensionFp(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result);
    static bool ParseJsDimensionVp(const EcmaVM *vm, const Local<JSValueRef> &value, CalcDimension &result);
    static bool ParseJsDimensionNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        DimensionUnit defaultUnit, bool isSupportPercent = true);
    static bool ParseJsDimensionVpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        bool isSupportPercent = true);
    static bool ParseResourceToDouble(const EcmaVM* vm, const Local<JSValueRef>& jsValue, double& result);
    template <class T>
    static bool ParseArray(const EcmaVM *vm, const Local<JSValueRef> &arg, T *array, int32_t defaultLength,
        std::function<T(const EcmaVM *, const Local<JSValueRef> &)> getValue)
    {
        CHECK_NULL_RETURN(vm, false);
        CHECK_NULL_RETURN(array, false);
        if (defaultLength <= 0) {
            return false;
        }
        auto handle = panda::CopyableGlobal<panda::ArrayRef>(vm, arg);
        int32_t length = handle->Length(vm);
        if (length != defaultLength) {
            return false;
        }
        for (int32_t i = 0; i < length; i++) {
            auto value = handle->GetValueAt(vm, arg, i);
            *(array + i) = getValue(vm, value);
        }
        return true;
    }
    static std::string GetStringFromJS(const EcmaVM *vm, const Local<JSValueRef> &value);
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_UTILS_H
