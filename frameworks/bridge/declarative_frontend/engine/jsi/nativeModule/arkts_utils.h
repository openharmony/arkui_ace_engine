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
#include "bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_image_data.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Rosen {
    class BrightnessBlender;
}

namespace OHOS::Ace::NG {
using ArkUIRuntimeCallInfo = panda::JsiRuntimeCallInfo;

enum class ResourceType : uint32_t {
    COLOR = 10001,
    FLOAT,
    STRING,
    PLURAL,
    BOOLEAN,
    INTARRAY,
    INTEGER,
    PATTERN,
    STRARRAY,
    MEDIA = 20000,
    RAWFILE = 30000,
    NONE = 40000
};
class ArkTSUtils {
public:
    static uint32_t ColorAlphaAdapt(uint32_t origin);
    static bool ParseJsColorContent(const EcmaVM* vm, const Local<JSValueRef>& value);
    static bool ParseJsColor(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result);
    static bool ParseJsColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result);
    static bool ParseJsColorAlpha(
        const EcmaVM* vm, const Local<JSValueRef>& value, Color& result, const Color& defaultColor);
    static bool ParseJsSymbolColorAlpha(const EcmaVM* vm, const Local<JSValueRef>& value, Color& result);
    static void CompleteResourceObject(const EcmaVM* vm, Local<panda::ObjectRef>& jsObj);
    static bool ParseJsColorFromResource(const EcmaVM* vm, const Local<JSValueRef>& jsObj, Color& result);
    static bool ParseJsDimensionFromResource(
        const EcmaVM* vm, const Local<JSValueRef>& jsObj, DimensionUnit dimensionUnit, CalcDimension& result);
    static bool ParseJsDimensionFromResourceNG(
        const EcmaVM* vm, const Local<JSValueRef>& jsObj, DimensionUnit dimensionUnit, CalcDimension& result);
    static bool ParseStringArray(
        const EcmaVM* vm, const Local<JSValueRef>& arg, std::string* array, int32_t defaultLength);
    static bool ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result);
    static bool ParseJsInteger(const EcmaVM *vm, const Local<JSValueRef> &value, uint32_t &result);
    static bool ParseJsIntegerWithResource(const EcmaVM* vm, const Local<JSValueRef>& jsValue, int32_t& result);
    static bool ParseJsDouble(const EcmaVM *vm, const Local<JSValueRef> &value, double &result);
    static bool ParseAllBorder(const EcmaVM *vm, const Local<JSValueRef> &args, CalcDimension &result);
    static bool ParseAllRadius(const EcmaVM *vm, const Local<JSValueRef> &args, CalcDimension &result);
    static bool ParseJsFontFamiliesToString(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string &result);
    static bool ParseJsFontFamilies(
        const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result);
    static bool ParseJsFontFamiliesFromResource(
        const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::vector<std::string> &result);
    static bool ParseJsLengthMetrics(
        const EcmaVM *vm, const Local<JSValueRef> &obj, CalcDimension &result);
    static bool ParseJsDimension(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        DimensionUnit defaultUnit, bool isSupportPercent = true, bool enableCheckInvalidvalue = true);
    static bool ParseJsDimensionFp(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        bool isSupportPercent = true, bool enableCheckInvalidvalue = true);
    static bool ParseJsDimensionFpNG(const EcmaVM *vm, const Local<JSValueRef> &jsValue, CalcDimension &result,
        bool isSupportPercent = true);
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
    static panda::Local<panda::ObjectRef> GetContext(EcmaVM* vm);
    static bool ParseJsStringFromResource(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::string& result);
    static uint32_t parseShadowColor(const EcmaVM* vm, const Local<JSValueRef>& jsValue);
    static uint32_t parseShadowFill(const EcmaVM* vm, const Local<JSValueRef>& jsValue);
    static uint32_t parseShadowType(const EcmaVM* vm, const Local<JSValueRef>& jsValue);
    static double parseShadowRadius(const EcmaVM* vm, const Local<JSValueRef>& jsValue);
    static double parseShadowOffset(const EcmaVM* vm, const Local<JSValueRef>& jsValue);
    static bool ParseJsSymbolId(const EcmaVM *vm, const Local<JSValueRef> &jsValue, std::uint32_t& symbolId);
    static void ParseOuterBorder(EcmaVM* vm, const Local<JSValueRef>& args,
        std::optional<CalcDimension>& optionalDimension);
    static void ParseOuterBorderForDashParams(EcmaVM* vm, const Local<JSValueRef>& args,
        std::optional<CalcDimension>& optionalDimension);
    static void PushOuterBorderDimensionVector(const std::optional<CalcDimension>& valueDim,
        std::vector<ArkUI_Float32>& values, std::vector<ArkUI_Int32>& units);
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
        if (handle.IsEmpty() || handle->IsUndefined() || handle->IsNull()) {
            return false;
        }
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
        ArkUI_Float32* regionValues, int32_t* regionUnits, uint32_t length);
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
    static BorderStyle ConvertBorderStyle(int32_t value);
    static void PushOuterBorderDimensionVector(
        const std::optional<CalcDimension>& valueDim, std::vector<ArkUI_Float32> &options);
    static void ParseOuterBorderWidth(
        ArkUIRuntimeCallInfo *runtimeCallInfo, EcmaVM *vm, std::vector<ArkUI_Float32> &values);
    static void PushOuterBorderColorVector(
        const std::optional<Color>& valueColor, std::vector<uint32_t> &options);
    static void ParseOuterBorderColor(ArkUIRuntimeCallInfo* runtimeCallInfo,
        EcmaVM* vm, std::vector<uint32_t>& values, int32_t argsIndex);
    static void ParseOuterBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo,
        EcmaVM* vm, std::vector<ArkUI_Float32>& values, int32_t argsIndex);
    static void ParseOuterBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo,
        EcmaVM* vm, std::vector<ArkUI_Float32>& values, std::vector<ArkUI_Int32>& units, int32_t argsIndex);
    static void PushOuterBorderStyleVector(
        const std::optional<BorderStyle>& value, std::vector<uint32_t> &options);
    static void ParseOuterBorderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo,
        EcmaVM* vm, std::vector<uint32_t>& values, int32_t argsIndex);
    static void SetBorderWidthArray(const EcmaVM* vm, const Local<JSValueRef>& args,
        ArkUI_Float32 values[], int units[], int index);
    static ArkUISizeType ParseJsToArkUISize(const EcmaVM *vm, const Local<JSValueRef> &arg);
    static bool IsDrawable(const EcmaVM* vm, const Local<JSValueRef>& jsValue);
    static RefPtr<PixelMap> GetDrawablePixmap(const EcmaVM* vm, Local<JSValueRef> obj);
    static Rosen::BrightnessBlender* CreateRSBrightnessBlenderFromNapiValue(const EcmaVM* vm, Local<JSValueRef> obj);
    static void* UnwrapNapiValue(const EcmaVM* vm, const Local<JSValueRef>& obj);
#if !defined(PREVIEW)
    static RefPtr<PixelMap> CreatePixelMapFromNapiValue(const EcmaVM* vm, Local<JSValueRef> obj);
#endif
    static bool ParseSelectionMenuOptions(ArkUIRuntimeCallInfo* info, const EcmaVM* vm,
        NG::OnCreateMenuCallback& onCreateMenuCallback, NG::OnMenuItemClickCallback& onMenuItemClickCallback);
    static void ParseOnCreateMenu(const EcmaVM* vm, FrameNode* frameNode,
        const Local<JSValueRef>& jsValueOnCreateMenu, NG::OnCreateMenuCallback& onCreateMenuCallback);
    static Local<panda::ArrayRef> CreateJsSystemMenuItems(
        const EcmaVM* vm, const std::vector<NG::MenuItemParam>& systemMenuItems);
    static Local<panda::ObjectRef> CreateJsTextMenuItem(const EcmaVM* vm, const NG::MenuItemParam& menuItemParam);
    static Local<panda::ObjectRef> CreateJsTextMenuId(const EcmaVM* vm, const std::string& id);
    static void WrapMenuParams(
        const EcmaVM* vm, std::vector<NG::MenuOptionsParam>& menuParams, const Local<JSValueRef>& menuItems);
    static void ParseOnMenuItemClick(const EcmaVM* vm, FrameNode* frameNode,
        const Local<JSValueRef>& jsValueOnMenuItemClick, NG::OnMenuItemClickCallback& onMenuItemClickCallback);
    static Local<panda::ArrayRef> CreateJsOnMenuItemClick(const EcmaVM* vm, const NG::MenuItemParam& menuItemParam);
    static Local<panda::ObjectRef> CreateJsTextRange(const EcmaVM* vm, const NG::MenuItemParam& menuItemParam);
    static void ThrowError(const EcmaVM* vm, const std::string& msg, int32_t code);
    static bool CheckKeysPressed(
        const EcmaVM* vm, const std::vector<KeyCode>& pressedKeyCodes, std::vector<std::string>& checkKeyCodes);
    static Local<JSValueRef> GetModifierKeyState(
        ArkUIRuntimeCallInfo* info, const std::vector<KeyCode>& pressedKeyCodes);
    static Local<JSValueRef> JsGetModifierKeyState(ArkUIRuntimeCallInfo* info);
    static Local<JSValueRef> JsGetHorizontalAxisValue(ArkUIRuntimeCallInfo* info);
    static Local<JSValueRef> JsGetVerticalAxisValue(ArkUIRuntimeCallInfo* info);
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_UTILS_H
