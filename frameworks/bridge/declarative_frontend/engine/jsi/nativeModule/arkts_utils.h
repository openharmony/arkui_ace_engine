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
#include "core/interfaces/native/node/api.h"
#include "bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "bridge/declarative_frontend/jsview/js_canvas_image_data.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

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
    static bool ParseStringArray(
        const EcmaVM* vm, const Local<JSValueRef>& arg, std::string* array, int32_t defaultLength);
    static bool ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result);
    static bool ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, uint32_t &result);
    static bool ParseJsDouble(const EcmaVM *vm, const Local<JSValueRef> &value, double &result);
    static bool ParseAllBorder(const EcmaVM *vm, const Local<JSValueRef> &args, CalcDimension &result);
    static bool ParseAllRadius(const EcmaVM *vm, const Local<JSValueRef> &args, CalcDimension &result);
    static bool ParseJsFontFamiliesToString(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string &result);
    static bool ParseJsFontFamilies(
        const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result);
    static bool ParseJsFontFamiliesFromResource(
        const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result);
    static bool ParseJsDimension(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        DimensionUnit defaultUnit, bool isSupportPercent = true, bool enableCheckInvalidvalue = true);
    static bool ParseJsDimensionFp(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        bool isSupportPercent = true, bool enableCheckInvalidvalue = true);
    static bool ParseJsDimensionVp(
        const EcmaVM *vm, const Local<JSValueRef> &value, CalcDimension &result, bool enableCheckInvalidvalue = true);
    static bool ParseJsDimensionNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        DimensionUnit defaultUnit, bool isSupportPercent = true);
    static bool ParseJsDimensionVpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        bool isSupportPercent = true);
    static bool ParseJsMedia(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string& result);
    static bool ParseJsMediaFromResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string& result);
    static bool ParseResourceToDouble(const EcmaVM* vm, const Local<JSValueRef>& jsValue, double& result);
    static bool ParseJsIntegerArray(const EcmaVM* vm, Local<JSValueRef> values, std::vector<uint32_t>& result);
    static bool ParseJsString(const EcmaVM *vm, const Local<JSValueRef> &value, std::string& result);
    static bool ParseJsStringFromResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string& result);
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
        int32_t length = static_cast<int32_t>(handle->Length(vm));
        if (length != defaultLength) {
            return false;
        }
        for (int32_t i = 0; i < length; i++) {
            auto value = handle->GetValueAt(vm, arg, i);
            *(array + i) = getValue(vm, value);
        }
        return true;
    }
    static void GetStringFromJS(const EcmaVM *vm, const Local<JSValueRef> &value, std::string& result);
    static bool ParseJsResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result);
    static void GetJsMediaBundleInfo(
        const EcmaVM* vm, const Local<JSValueRef>& jsValue, std::string& bundleName, std::string& moduleName);
    static bool ParseJsColorStrategy(
        const EcmaVM* vm, const Local<JSValueRef>& value, ForegroundColorStrategy& strategy);
    static bool GetJsPasswordIcon(const EcmaVM *vm, const Local<JSValueRef> &jsOnIconSrc,
        const Local<JSValueRef> &jsOffIconSrc, PasswordIcon& result);
    static void ParsePadding(
        const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& dimen, ArkUISizeType& result);
    static bool ParseResponseRegion(
        const EcmaVM* vm, const Local<JSValueRef>& jsValue,
        double* regionValues, int32_t* regionUnits, uint32_t length);
    template<typename T>
    static RefPtr<T> GetTheme()
    {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto themeManager = pipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(themeManager, nullptr);
        return themeManager->GetTheme<T>();
    }
    static bool IsPercentStr(std::string& percent)
    {
        if (percent.find("%") != std::string::npos) {
            size_t index = percent.find("%");
            percent = percent.substr(0, index);
            return true;
        }
        return false;
    }
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_UTILS_H
