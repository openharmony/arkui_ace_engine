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
 
    void GetGlyphPositionAtCoordinate(const JSCallbackInfo& args);
 
    void DidExceedMaxLines(const JSCallbackInfo& args);
 
    void GetLineMetrics(const JSCallbackInfo& info);
 
    JSRef<JSObject> CreateJSTextStyleResult(const TextStyle& textStyle);
 
    JSRef<JSObject> CreateJSFontMetrics(const FontMetrics& fontMetrics);
 
    JSRef<JSObject> CreateJSRunMetrics(const RunMetrics& runMetrics);
 
    void CreateJSLineMetrics(JSRef<JSObject>& lineMetricsObj, const TextLineMetrics& lineMetrics);
 
private:
    WeakPtr<OHOS::Ace::NG::LayoutInfoInterface> layoutInfoInterface_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAYOUTMANAGER_H