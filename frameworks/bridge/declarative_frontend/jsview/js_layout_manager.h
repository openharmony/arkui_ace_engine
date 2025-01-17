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
 
#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAYOUTMANAGER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAYOUTMANAGER_H
 
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/core/components/common/properties/text_layout_info.h"
#include "frameworks/core/components_ng/pattern/text/layout_info_interface.h"
 
namespace OHOS::Ace::Framework {

constexpr int32_t DEFAULT_HEIGHT_STYLE = 5;
struct NapiMap {
    napi_value instance;
    napi_value setFunction;
};

class JSLayoutManager : public Referenced {
public:
    JSLayoutManager() = default;
    ~JSLayoutManager() override = default;
 
    static void JSBind(BindingTarget globalObj);
 
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsLayoutManager = Referenced::MakeRefPtr<JSLayoutManager>();
        jsLayoutManager->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsLayoutManager));
    }
 
    static void Destructor(JSLayoutManager* jsLayoutManager)
    {
        if (jsLayoutManager) {
            jsLayoutManager->DecRefCount();
        }
    }
 
    void SetLayoutInfoInterface(const WeakPtr<OHOS::Ace::NG::LayoutInfoInterface>& layoutInfoInterface)
    {
        layoutInfoInterface_ = layoutInfoInterface;
    }
 
    void GetLineCount(const JSCallbackInfo& args);
 
    void GetRectsForRange(const JSCallbackInfo& args);

    RectWidthStyle ParseRectWidthStyle(const JsiValue& widthStyleVal)
    {
        if (widthStyleVal->IsNumber()) {
            int widthStyleInt = widthStyleVal->ToNumber<int>();
            if (widthStyleInt == 0 || widthStyleInt == 1) {
                return static_cast<RectWidthStyle>(widthStyleInt);
            }
        }
        return RectWidthStyle::TIGHT;
    }

    RectHeightStyle ParseRectHeightStyle(const JsiValue& heightStyleVal)
    {
        if (heightStyleVal->IsNumber()) {
            int heightStyleInt = heightStyleVal->ToNumber<int>();
            if (heightStyleInt >= 0 && heightStyleInt <= DEFAULT_HEIGHT_STYLE) {
                return static_cast<RectHeightStyle>(heightStyleInt);
            }
        }
        return RectHeightStyle::TIGHT;
    }

    void GetGlyphPositionAtCoordinate(const JSCallbackInfo& args);
 
    void DidExceedMaxLines(const JSCallbackInfo& args);
 
    void GetLineMetrics(const JSCallbackInfo& info);
 
    Local<panda::ObjectRef> CreateJSRunMetrics(const std::map<size_t, RunMetrics>& mapRunMetrics,
        const JSCallbackInfo& args);

    Local<panda::ObjectRef> CreateJSFontMetrics(const FontMetrics& fontMetrics, const JSCallbackInfo& args);
    
    Local<panda::ObjectRef> CreateJSTextStyleResult(const TextStyle& textStyle, const JSCallbackInfo& args);
 
private:
    WeakPtr<OHOS::Ace::NG::LayoutInfoInterface> layoutInfoInterface_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAYOUTMANAGER_H