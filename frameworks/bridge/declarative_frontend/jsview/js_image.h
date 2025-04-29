/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_H

#include "base/image/image_defines.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/image/image_event.h"

namespace OHOS::Ace::Framework {

JSRef<JSVal> LoadImageSuccEventToJSValue(const LoadImageSuccessEvent& eventInfo);
JSRef<JSVal> LoadImageFailEventToJSValue(const LoadImageFailEvent& eventInfo);

class JSImage : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void CreateImage(const JSCallbackInfo& info, bool isImageSpan = false);
    static void CreateImageAnimation(std::vector<RefPtr<PixelMap>>& pixelMaps, int32_t duration, int32_t iterations);
    static void CheckIsCard(std::string& src, const JSRef<JSVal>& jsValue);
    static bool CheckResetImage(const bool& srcValid, const JSCallbackInfo& info);
    static void HandleLoadImageSuccess(const BaseEventInfo& param);
    static void HandleLoadImageFail(const BaseEventInfo& param);
    static void SetAlt(const JSCallbackInfo& args);
    static void SetMatchTextDirection(bool value);
    static void SetFitOriginalSize(bool value);
    static void SetSourceSize(const JSCallbackInfo& info);
    static void SetObjectFit(const JSCallbackInfo& args);
    static void SetImageMatrix(const JSCallbackInfo& args);
    static void SetDefaultImageMatrix();
    static void SetImageFill(const JSCallbackInfo& info);
    static bool ParseColorContent(const JSRef<JSVal>& jsValue);
    static void SetImageInterpolation(int32_t imageInterpolation);
    static void SetImageRenderMode(const JSCallbackInfo& info);
    static void SetImageRepeat(int32_t imageRepeat);
    static void JSBind(BindingTarget globalObj);
    static void OnComplete(const JSCallbackInfo& args);
    static void OnError(const JSCallbackInfo& args);
    static void OnFinish(const JSCallbackInfo& info);
    static void SetSyncLoad(const JSCallbackInfo& info);
    static void SetColorFilter(const JSCallbackInfo& info);
    static void SetSmoothEdge(const JSCallbackInfo& info);
    static void SetDynamicRangeMode(const JSCallbackInfo& info);
    static void SetHdrBrightness(const JSCallbackInfo& info);
    static void SetEnhancedImageQuality(const JSCallbackInfo& info);
    static void SetOrientation(const JSCallbackInfo& info);

    static void JsBorder(const JSCallbackInfo& info);
    static void JsBorderRadius(const JSCallbackInfo& info);
    static void SetLeftBorderWidth(const CalcDimension& value);
    static void SetTopBorderWidth(const CalcDimension& value);
    static void SetRightBorderWidth(const CalcDimension& value);
    static void SetBottomBorderWidth(const CalcDimension& value);
    static void SetBorderRadius(const CalcDimension& value);
    static void ParseBorderRadius(const JSRef<JSVal>& args);
    static void JsOpacity(const JSCallbackInfo& info);
    static void JsBlur(const JSCallbackInfo& info);
    static void JsTransition(const JSCallbackInfo& info);
    static void JsSetDraggable(const JSCallbackInfo& info);
    static void JsOnDragStart(const JSCallbackInfo& info);
    static void SetCopyOption(const JSCallbackInfo& info);

    static void EnableAnalyzer(bool isEnableAnalyzer);
    static void AnalyzerConfig(const JSCallbackInfo& info);
    static void ParseResizableSlice(const JSRef<JSObject>& info);
    static void ParseResizableLattice(const JSRef<JSObject>& info);
    static void JsImageResizable(const JSCallbackInfo& info);
    static bool IsDrawable(const JSRef<JSVal>& jsValue);
    static ImageType ParseImageType(const JSRef<JSVal>& jsValue);

protected:
    static void SetBorder(const Border& border);
    static void SetAutoResize(bool autoResize);
    static void UpdateSliceResult(const JSRef<JSObject>& sliceObj, ImageResizableSlice& sliceResult);
    static void ParseImageAIOptions(const JSCallbackInfo& info);
};

class JSColorFilter : public AceType {
    DECLARE_ACE_TYPE(JSColorFilter, AceType);

public:
    JSColorFilter() = default;
    ~JSColorFilter() override = default;
    static void ConstructorCallback(const JSCallbackInfo& info);
    static void DestructorCallback(JSColorFilter* obj);

    void SetColorFilterMatrix(const std::vector<float>&& matrix)
    {
        colorfiltermatrix_ = std::move(matrix);
    }

    const std::vector<float>& GetColorFilterMatrix() const
    {
        return colorfiltermatrix_;
    }

private:
    std::vector<float> colorfiltermatrix_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IMAGE_H
