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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_FUNCTIONS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_FUNCTIONS_H

#include <string>

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline/base/composed_component.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_measure_layout.h"

namespace OHOS::Ace {
class ComposedElement;
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
enum class PrebuildPhase : int32_t {
    NONE = 0,
    BUILD_PREBUILD_CMD = 1,
    EXECUTE_PREBUILD_CMD = 2,
    PREBUILD_DONE = 3,
};

class JSView;

class ViewFunctions : public AceType {
    DECLARE_ACE_TYPE(ViewFunctions, AceType);

public:
    ViewFunctions(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsRenderFunction);
    explicit ViewFunctions(const JSRef<JSObject>& jsObject);
    ~ViewFunctions() override {}

    void Destroy();
    void Destroy(JSView* parentCustomView);

    void ExecuteRender();
    void ExecuteRerender();
    void ExecuteReload(bool deep);
    void ExecuteForceNodeRerender(int32_t elemId);
    bool ExecuteHasNodeUpdateFunc(int32_t elmtId);
    void ExecuteAppear();
    void ExecuteDisappear();
    void ExecuteDidBuild();
    void ExecuteMeasure(NG::LayoutWrapper* layoutWrapper);
    void ExecuteMeasureSize(NG::LayoutWrapper* layoutWrapper);
    void ExecuteLayout(NG::LayoutWrapper* layoutWrapper);
    void ExecutePlaceChildren(NG::LayoutWrapper* layoutWrapper);
    void InitJsParam(NG::LayoutWrapper* layoutWrapper);
    void ExecuteAboutToBeDeleted();
    void ExecuteAboutToRender();
    void ExecuteOnRenderDone();
    void ExecuteTransition();
    bool ExecuteOnBackPress();
    void ExecuteShow();
    void ExecuteHide();
    void ExecuteInitiallyProvidedValue(const std::string& jsonData);
    void ExecuteUpdateWithValueParams(const std::string& jsonData);
    void ExecuteRecycle(const std::string& viewName);
    void ExecuteAboutToRecycle();
    void ExecuteAboutToReuse(void* params);
    void ExecuteSetActive(bool active, bool isReuse = false);
    void ExecuteOnDumpInfo(const std::vector<std::string>& params);
    std::string ExecuteOnDumpInfo();
    void ExecuteClearAllRecycle();
    std::string ExecuteOnFormRecycle();
    void ExecuteOnFormRecover(const std::string &statusData);
    void ExecutePrebuildComponent();
    bool ExecuteSetPrebuildPhase(PrebuildPhase prebuildPhase);
    bool ExecuteIsEnablePrebuildInMultiFrame();
    void ExecuteOnNewParam(const std::string &newParam);

    bool HasPageTransition() const;
    bool HasMeasure() const;
    bool HasMeasureSize() const;
    bool HasLayout() const;
    bool HasPlaceChildren() const;

    void ExecuteFunction(JSWeak<JSFunc>& func, const char* debugInfo);
    void ExecuteFunctionWithParams(JSWeak<JSFunc>& func, const char* debugInfo, const std::string& jsonData);
    JSRef<JSVal> ExecuteFunctionWithReturn(JSWeak<JSFunc>& func, const char* debugInfo);

    void SetContext(const JSExecutionContext& context)
    {
        context_ = context;
    }

protected:
    void InitViewFunctions(const JSRef<JSObject>& jsObject, const JSRef<JSFunc>& jsRenderFunction, bool partialUpdate);

private:
    JSWeak<JSObject> jsObject_;
    JSWeak<JSFunc> jsAppearFunc_;
    JSWeak<JSFunc> jsDisappearFunc_;
    JSWeak<JSFunc> jsDidBuildFunc_;
    JSWeak<JSFunc> jsMeasureFunc_;
    JSWeak<JSFunc> jsMeasureSizeFunc_;
    JSWeak<JSFunc> jsLayoutFunc_;
    JSWeak<JSFunc> jsPlaceChildrenFunc_;
    JSWeak<JSFunc> jsAboutToRenderFunc_;
    JSWeak<JSFunc> jsAboutToBeDeletedFunc_;
    JSWeak<JSFunc> jsRenderDoneFunc_;
    JSWeak<JSFunc> jsAboutToBuildFunc_;
    JSWeak<JSFunc> jsBuildDoneFunc_;
    JSWeak<JSFunc> jsRenderFunc_;
    JSWeak<JSFunc> jsRerenderFunc_;
    JSWeak<JSFunc> jsReloadFunc_;
    JSWeak<JSFunc> jsForceRerenderNodeFunc_;
    JSWeak<JSFunc> jsHasNodeUpdateFunc_;
    JSWeak<JSFunc> jsTransitionFunc_;
    JSWeak<JSVal> jsRenderResult_;

    JSWeak<JSFunc> jsOnHideFunc_;
    JSWeak<JSFunc> jsOnShowFunc_;
    JSWeak<JSFunc> jsBackPressFunc_;
    JSWeak<JSFunc> jsUpdateWithValueParamsFunc_;
    JSWeak<JSFunc> jsSetInitiallyProvidedValueFunc_;
    JSWeak<JSFunc> jsRecycleFunc_;
    JSWeak<JSFunc> jsAboutToRecycleFunc_;
    JSWeak<JSFunc> jsAboutToReuseFunc_;
    JSWeak<JSFunc> jsSetActive_;
    JSWeak<JSFunc> jsOnDumpInfo_;
    JSWeak<JSFunc> jsOnDumpInspector_;
    JSWeak<JSFunc> jsClearAllRecycle_;
    JSWeak<JSFunc> jsPrebuildComponent_;
    JSWeak<JSFunc> jsSetPrebuildPhase_;
    JSWeak<JSFunc> jsIsEnablePrebuildInMultiFrame_;
    JSWeak<JSFunc> jsOnFormRecycleFunc_;
    JSWeak<JSFunc> jsOnFormRecoverFunc_;
    JSWeak<JSFunc> jsOnNewParam_;

    JSExecutionContext context_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_FUNCTIONS_H
