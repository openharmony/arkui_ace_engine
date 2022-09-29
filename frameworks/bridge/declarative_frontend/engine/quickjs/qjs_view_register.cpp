/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_view_register.h"

#include <cstdint>

#include "base/i18n/localization.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "bridge/common/accessibility/accessibility_node_manager.h"
#include "core/components/common/layout/constants.h"
#include "frameworks/bridge/declarative_frontend/engine/js_object_template.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_declarative_engine_instance.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"

namespace OHOS::Ace::Framework {

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
static JSValue JsPreviewComponent(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("PreviewerComponent start");
    if (ctx == nullptr) {
        LOGE("ctx is nullptr. Failed!");
        return JS_UNDEFINED;
    }
    auto* instance = QJSDeclarativeEngineInstance::UnWrapEngineInstance(ctx);
    if (!instance) {
        LOGE("QJS context has no ref to engine instance. Failed!");
        return JS_UNDEFINED;
    }
    std::string requiredComponentName = instance->GetRequiredComponent();
    JSValue obj = instance->GetPreviewComponent(requiredComponentName);
    if (JS_IsUndefined(obj)) {
        LOGE("Get PreviewComponent object from map failed");
        return JS_UNDEFINED;
    }

    JSView* view = static_cast<JSView*>(UnwrapAny(obj));
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        return JS_ThrowReferenceError(ctx, "JsPreviewComponent: argument provided is not a View!");
    }

    Container::SetCurrentUsePartialUpdate(!view->isFullUpdate());
    LOGD("Loading page root component: Setting pipeline to use %{public}s.",
        view->isFullUpdate() ? "Full Update" : "Partial Update");

    auto page = QJSDeclarativeEngineInstance::GetRunningPage(ctx);
    LOGD("JsPreviewComponent setting root view");
    CreatePageRoot(page, view);
    // We are done, tell to the JSAgePage
    if (!page) {
        return JS_UNDEFINED;
    }
    page->SetPageCreated();
    page->SetDeclarativeOnPageAppearCallback([view]() { view->FireOnShow(); });
    page->SetDeclarativeOnPageDisAppearCallback([view]() { view->FireOnHide(); });
    page->SetDeclarativeOnPageRefreshCallback([view]() { view->MarkNeedUpdate(); });
    page->SetDeclarativeOnBackPressCallback([view]() { return view->FireOnBackPress(); });
    page->SetDeclarativeOnUpdateWithValueParamsCallback([view](const std::string& params) {
        if (view && !params.empty()) {
            view->ExecuteUpdateWithValueParams(params);
        }
    });

    return JS_UNDEFINED;
}

static JSValue JsGetPreviewComponentFlag(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Get PreviewComponentFlag start");
    if (ctx == nullptr) {
        LOGE("ctx is nullptr. Failed!");
        return JS_UNDEFINED;
    }
    auto* instance = QJSDeclarativeEngineInstance::UnWrapEngineInstance(ctx);
    if (!instance) {
        LOGE("QJS context has no ref to engine instance. Failed!");
        return JS_UNDEFINED;
    }
    bool isComponentPreview = instance->GetPreviewFlag();
    return JS_NewBool(ctx, isComponentPreview);
}

static JSValue JsStorePreviewComponents(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Store PreviewerComponents start");
    if (argc < 3) {
        return JS_ThrowSyntaxError(ctx, "storePreviewComponents requires at least three arguments.");
    }
    if (!JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "parameter action must be number");
    }
    if (ctx == nullptr) {
        LOGE("ctx is nullptr. Failed!");
        return JS_UNDEFINED;
    }
    int32_t numOfComponent = 0;
    if (JS_ToInt32(ctx, &numOfComponent, argv[0]) < 0) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, must be uint32 value");
    }
    if (numOfComponent * 2 != argc - 1) {
        return JS_ThrowSyntaxError(ctx, "The number of components is wrong.");
    }
    auto* instance = QJSDeclarativeEngineInstance::UnWrapEngineInstance(ctx);
    if (!instance) {
        LOGE("QJS context has no ref to engine instance. Failed!");
        return JS_UNDEFINED;
    }
    for (int32_t index = 1; index <= numOfComponent; index++) {
        if (!JS_IsString(argv[2 * index - 1]) || JS_IsUndefined(argv[2 * index])) {
            LOGE("The %{private}d component passed by StorePreviewComponents has wrong type", index);
            return JS_UNDEFINED;
        }
        ScopedString componentName(ctx, argv[2 * index - 1]);
        std::string name = componentName.get();
        JSValue jsView = JS_DupValue(ctx, argv[2 * index]);
        instance->AddPreviewComponent(name, jsView);
    }
    return JS_UNDEFINED;
}
#endif

static JSValue JsLoadDocument(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Load Document");

    if ((argc != 1) || (!JS_IsObject(argv[0]))) {
        return JS_ThrowSyntaxError(ctx, "loadDocument expects a single object as parameter");
    }

    QJSHandleScope sc(ctx);
    QJSContext::Scope scope(ctx);

    // JS_DupValue on arg[0]. And release when done. Otherwise it will get GC-d as soon as this function exits.
    // Store jsView in page, so when page is unloaded a call to JS_FreeValue is made to release it
    JSValue jsView = JS_DupValue(ctx, argv[0]);

    JSView* view = static_cast<JSView*>(UnwrapAny(jsView));
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        return JS_ThrowReferenceError(ctx, "loadDocument: argument provided is not a View!");
    }

    Container::SetCurrentUsePartialUpdate(!view->isFullUpdate());
    LOGD("Loading page root component: Setting pipeline to use %{public}s.",
        view->isFullUpdate() ? "Full Update" : "Partial Update");

    auto page = QJSDeclarativeEngineInstance::GetRunningPage(ctx);
    LOGD("Load Document setting root view");
    CreatePageRoot(page, view);
    // We are done, tell to the JSAgePage
    if (!page) {
        return JS_UNDEFINED;
    }
    page->SetPageCreated();
    page->SetDeclarativeOnPageAppearCallback([view]() { view->FireOnShow(); });
    page->SetDeclarativeOnPageDisAppearCallback([view]() { view->FireOnHide(); });
    page->SetDeclarativeOnPageRefreshCallback([view]() { view->MarkNeedUpdate(); });
    page->SetDeclarativeOnBackPressCallback([view]() { return view->FireOnBackPress(); });
    page->SetDeclarativeOnUpdateWithValueParamsCallback([view](const std::string& params) {
        if (view && !params.empty()) {
            view->ExecuteUpdateWithValueParams(params);
        }
    });

    return JS_UNDEFINED;
}

static TouchEvent GetTouchPointFromJS(JSContext* ctx, JSValue value)
{
    TouchEvent touchPoint;

    auto type = JS_GetPropertyStr(ctx, value, "type");
    auto iType = static_cast<int32_t>(TouchType::UNKNOWN);
    JS_ToInt32(ctx, &iType, type);
    touchPoint.type = static_cast<TouchType>(iType);

    auto id = JS_GetPropertyStr(ctx, value, "id");
    JS_ToInt32(ctx, &touchPoint.id, id);

    auto x = JS_GetPropertyStr(ctx, value, "x");
    double dx;
    JS_ToFloat64(ctx, &dx, x);
    touchPoint.x = dx;

    auto y = JS_GetPropertyStr(ctx, value, "y");
    double dy;
    JS_ToFloat64(ctx, &dy, y);
    touchPoint.y = dy;

    touchPoint.time = std::chrono::high_resolution_clock::now();

    return touchPoint;
}

static JSValue JsSendTouchEvent(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have 1 arguments");
    }

    if (!JS_IsObject(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be object");
    }

    QJSContext::Scope scp(ctx);
    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        return JS_ThrowSyntaxError(ctx, "pipeline is null");
    }
    TouchEvent touchPoint = GetTouchPointFromJS(ctx, argv[0]);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, touchPoint]() { pipelineContext->OnTouchEvent(touchPoint); }, TaskExecutor::TaskType::UI);

    return JS_NewBool(ctx, result);
}

static MouseEvent GetMouseEventFromJS(JSContext* ctx, JSValue value)
{
    MouseEvent mouseEvent;

    auto type = JS_GetPropertyStr(ctx, value, "action");
    auto iType = static_cast<int32_t>(MouseAction::NONE);
    JS_ToInt32(ctx, &iType, type);
    mouseEvent.action = static_cast<MouseAction>(iType);

    auto button = JS_GetPropertyStr(ctx, value, "button");
    auto iButton = static_cast<int32_t>(MouseButton::NONE_BUTTON);
    JS_ToInt32(ctx, &iButton, button);
    mouseEvent.button = static_cast<MouseButton>(iButton);

    auto x = JS_GetPropertyStr(ctx, value, "x");
    double dx;
    JS_ToFloat64(ctx, &dx, x);
    mouseEvent.x = dx;
    mouseEvent.deltaX = mouseEvent.x;

    auto y = JS_GetPropertyStr(ctx, value, "y");
    double dy;
    JS_ToFloat64(ctx, &dy, y);
    mouseEvent.y = dy;
    mouseEvent.deltaY = mouseEvent.y;

    mouseEvent.time = std::chrono::high_resolution_clock::now();
    mouseEvent.sourceType = SourceType::MOUSE;
    return mouseEvent;
}

static JSValue JsSendMouseEvent(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have 1 arguments");
    }

    if (!JS_IsObject(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be object");
    }

    QJSContext::Scope scp(ctx);
    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        return JS_ThrowSyntaxError(ctx, "pipeline is null");
    }
    auto mouseEvent = GetMouseEventFromJS(ctx, argv[0]);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, mouseEvent]() { pipelineContext->OnMouseEvent(mouseEvent); }, TaskExecutor::TaskType::UI);

    return JS_NewBool(ctx, result);
}

static JSValue JsDumpMemoryStats(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
#ifdef ACE_DEBUG
    QJSContext::Scope scope(ctx);

    QJSUtils::JsDumpMemoryStats(ctx);
#endif
    return JS_UNDEFINED;
}

JSValue JsGetI18nResource(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("JsGetI18nResource");
    if (argc != 2 && argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one or two arguments");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsString(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be string");
    }

    std::vector<std::string> splitStr;
    ScopedString targetString(ctx, argv[0]);
    std::string str = targetString.get();
    StringUtils::SplitStr(str, ".", splitStr);
    if (splitStr.size() != 2) {
        return JS_ThrowSyntaxError(ctx, "input string res value must can be split by dot");
    }

    auto targetStringKey = splitStr[0];
    auto targetStringKeyValue = splitStr[1];
    auto resultStrJson = QJSDeclarativeEngineInstance::GetI18nStringResource(targetStringKey, targetStringKeyValue);
    auto resultStr = resultStrJson->GetString();
    if (argc == 2) {
        if (JS_IsArray(ctx, argv[1])) {
            auto len = QJSUtils::JsGetArrayLength(ctx, argv[1]);
            std::vector<std::string> arrayResult;
            for (int32_t i = 0; i < len; i++) {
                JSValue subItemVal = JS_GetPropertyUint32(ctx, argv[1], i);
                if (!JS_IsString(subItemVal)) {
                    arrayResult.emplace_back(std::string());
                    JS_FreeValue(ctx, subItemVal);
                    continue;
                }

                ScopedString subScopedStr(ctx, subItemVal);
                arrayResult.emplace_back(subScopedStr.get());
            }

            ReplacePlaceHolderArray(resultStr, arrayResult);
        } else if (JS_IsObject(argv[1])) {
            std::unique_ptr<JsonValue> argsJson = JsonUtil::Create(true);
            JSPropertyEnum* pTab = nullptr;
            uint32_t len = 0;
            if (CheckAndGetJsProperty(ctx, argv[1], &pTab, &len)) {
                for (uint32_t i = 0; i < len; i++) {
                    auto key = JS_AtomToCString(ctx, pTab[i].atom);
                    if (key == nullptr) {
                        JS_FreeAtom(ctx, pTab[i].atom);
                        LOGW("key is null. Ignoring!");
                        continue;
                    }
                    JSValue value = JS_GetProperty(ctx, argv[1], pTab[i].atom);
                    if (JS_IsString(value)) {
                        ScopedString valStr(ctx, value);
                        argsJson->Put(key, valStr.get());
                    }
                }
                ReplacePlaceHolder(resultStr, argsJson);
            }
        } else if (JS_IsNumber(argv[1])) {
            ScopedString valueString(ctx, argv[1]);
            auto count = StringToDouble(valueString.get());
            auto pluralChoice = Localization::GetInstance()->PluralRulesFormat(count);
            if (!pluralChoice.empty()) {
                resultStr = ParserPluralResource(resultStrJson, pluralChoice, str);
            }
        }
    }

    JSValue result = JS_NewString(ctx, resultStr.c_str());
    return result;
}

JSValue JsGetMediaResource(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("JsGetMediaResource");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one argument");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsString(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be string");
    }

    ScopedString targetMediaFileJsName(ctx, argv[0]);
    std::string targetMediaFileName = targetMediaFileJsName.get();
    std::string filePath = QJSDeclarativeEngineInstance::GetMediaResource(targetMediaFileName);
    JSValue result = JS_NewString(ctx, filePath.c_str());
    return result;
}

JSValue Vp2Px(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Vp2Px");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one argument");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be number");
    }

    ScopedString valueString(ctx, argv[0]);
    auto vpValue = StringToDouble(valueString.get());
    double density = SystemProperties::GetResolution();
    double pxValue = vpValue * density;

    int32_t result = GreatOrEqual(pxValue, 0) ? (pxValue + 0.5) : (pxValue - 0.5);
    JSValue pxQJSValue = JS_NewInt32(ctx, result);
    return pxQJSValue;
}

JSValue Px2Vp(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Px2Vp");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one argument");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be number");
    }

    ScopedString valueString(ctx, argv[0]);
    auto pxValue = StringToDouble(valueString.get());
    double density = SystemProperties::GetResolution();
    double vpValue = pxValue / density;

    JSValue vpQJSValue = JS_NewFloat64(ctx, vpValue);
    return vpQJSValue;
}

JSValue Fp2Px(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Fp2Px");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one argument");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be number");
    }
    ScopedString valueString(ctx, argv[0]);
    auto fpValue = StringToDouble(valueString.get());
    double density = SystemProperties::GetResolution();

    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double pxValue = fpValue * density * fontScale;

    int32_t result = GreatOrEqual(pxValue, 0) ? (pxValue + 0.5) : (pxValue - 0.5);
    JSValue pxQJSValue = JS_NewInt32(ctx, result);
    return pxQJSValue;
}

JSValue Px2Fp(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Px2Fp");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one argument");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be number");
    }
    ScopedString valueString(ctx, argv[0]);
    auto pxValue = StringToDouble(valueString.get());
    double density = SystemProperties::GetResolution();

    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double ratio = density * fontScale;
    double fpValue = pxValue / ratio;

    JSValue pxQJSValue = JS_NewInt32(ctx, fpValue);
    return pxQJSValue;
}

JSValue Lpx2Px(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Lpx2Px");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one argument");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be number");
    }
    ScopedString valueString(ctx, argv[0]);
    auto lpxValue = StringToDouble(valueString.get());

    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto frontend = container->GetFrontend();
    auto& windowConfig = frontend->GetWindowConfig();
    double pxValue = lpxValue * windowConfig.designWidthScale;

    int32_t result = GreatOrEqual(pxValue, 0) ? (pxValue + 0.5) : (pxValue - 0.5);
    JSValue lpxQJSValue = JS_NewInt32(ctx, result);
    return lpxQJSValue;
}

JSValue Px2Lpx(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    LOGD("Px2Lpx");
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one argument");
    }

    QJSContext::Scope scp(ctx);
    if (!JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be number");
    }
    ScopedString valueString(ctx, argv[0]);
    auto pxValue = StringToDouble(valueString.get());

    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto frontend = container->GetFrontend();
    auto& windowConfig = frontend->GetWindowConfig();
    double lpxValue = pxValue / windowConfig.designWidthScale;

    JSValue lpxQJSValue = JS_NewInt32(ctx, lpxValue);
    return lpxQJSValue;
}

JSValue SetAppBackgroundColor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return JS_ThrowSyntaxError(ctx, "input value must be number");
    }
    QJSContext::Scope scp(ctx);
    if (!JS_IsString(argv[0])) {
        LOGE("The arg is wrong, value must be string");
        return JS_ThrowSyntaxError(ctx, "input value must be string");
    }
    ScopedString valueString(ctx, argv[0]);
    std::string backgroundColorStr = valueString.get();
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext) {
        pipelineContext->SetAppBgColor(Color::FromString(backgroundColorStr));
    }
    return JS_UNDEFINED;
}

JSValue JsGetInspectorNodes(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    QJSContext::Scope scp(ctx);
    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto front = container->GetFrontend();
    if (!front) {
        return JS_ThrowSyntaxError(ctx, "front is null");
    }
    auto accessibilityManager = AceType::DynamicCast<AccessibilityNodeManager>(front->GetAccessibilityManager());
    if (!accessibilityManager) {
        return JS_ThrowSyntaxError(ctx, "AccessibilityManager is null");
    }
    auto nodeInfos = accessibilityManager->DumpComposedElementsToJson();
    auto infoStr = nodeInfos->ToString();
    return JS_ParseJSON(ctx, infoStr.c_str(), infoStr.length(), nullptr);
}

JSValue JsGetInspectorNodeById(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    QJSContext::Scope scp(ctx);
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have one argument");
    }
    if (!JS_IsNumber(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be number");
    }
    auto container = Container::Current();
    if (!container) {
        return JS_ThrowSyntaxError(ctx, "container is null");
    }
    auto front = container->GetFrontend();
    if (!front) {
        return JS_ThrowSyntaxError(ctx, "front is null");
    }
    auto accessibilityManager = AceType::DynamicCast<AccessibilityNodeManager>(front->GetAccessibilityManager());
    if (!accessibilityManager) {
        return JS_ThrowSyntaxError(ctx, "AccessibilityManager is null");
    }
    int32_t nodeId = 0;
    if (JS_ToInt32(ctx, &nodeId, argv[0]) < 0) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, must be int32 value");
    }
    auto nodeInfo = accessibilityManager->DumpComposedElementToJson(nodeId);
    auto infoStr = nodeInfo->ToString();
    return JS_ParseJSON(ctx, infoStr.c_str(), infoStr.length(), nullptr);
}

static JSValue RequestFocus(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    if (argc != 1) {
        return JS_ThrowSyntaxError(ctx, "The arg is wrong, it is supposed to have 1 arguments");
    }

    if (!JS_IsString(argv[0])) {
        return JS_ThrowSyntaxError(ctx, "input value must be string");
    }
    ScopedString targetString(ctx, argv[0]);
    std::string inspectorKey = targetString.get();

    QJSContext::Scope scp(ctx);
    bool result = false;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, JS_NewBool(ctx, result));
    if (!pipelineContext->GetTaskExecutor()) {
        LOGE("pipelineContext's task executor is null");
        return JS_NewBool(ctx, result);
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, inspectorKey, &result]() { result = pipelineContext->RequestFocus(inspectorKey); },
        TaskExecutor::TaskType::UI);

    return JS_NewBool(ctx, result);
}

void JsRegisterViews(BindingTarget globalObj)
{
    JSContext* ctx = QJSContext::Current();

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    QJSUtils::DefineGlobalFunction(ctx, JsPreviewComponent, "previewComponent", 0);
    QJSUtils::DefineGlobalFunction(ctx, JsGetPreviewComponentFlag, "getPreviewComponentFlag", 0);
    QJSUtils::DefineGlobalFunction(ctx, JsStorePreviewComponents, "storePreviewComponents", 3);
#endif
    QJSUtils::DefineGlobalFunction(ctx, JsLoadDocument, "loadDocument", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsGetInspectorTree, "getInspectorTree", 0);
    QJSUtils::DefineGlobalFunction(ctx, JsGetInspectorByKey, "getInspectorByKey", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsSendEventByKey, "sendEventByKey", 3);
    QJSUtils::DefineGlobalFunction(ctx, JsSendTouchEvent, "sendTouchEvent", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsSendKeyEvent, "sendKeyEvent", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsSendMouseEvent, "sendMouseEvent", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsDumpMemoryStats, "dumpMemoryStats", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsGetI18nResource, "$s", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsGetMediaResource, "$m", 1);
    QJSUtils::DefineGlobalFunction(ctx, Vp2Px, "vp2px", 1);
    QJSUtils::DefineGlobalFunction(ctx, Px2Vp, "px2vp", 1);
    QJSUtils::DefineGlobalFunction(ctx, Fp2Px, "fp2px", 1);
    QJSUtils::DefineGlobalFunction(ctx, Px2Fp, "px2fp", 1);
    QJSUtils::DefineGlobalFunction(ctx, Lpx2Px, "lpx2px", 1);
    QJSUtils::DefineGlobalFunction(ctx, Px2Lpx, "px2lpx", 1);
    QJSUtils::DefineGlobalFunction(ctx, SetAppBackgroundColor, "setAppBgColor", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsGetInspectorNodes, "getInspectorNodes", 1);
    QJSUtils::DefineGlobalFunction(ctx, JsGetInspectorNodeById, "getInspectorNodeById", 1);
    QJSUtils::DefineGlobalModuleFunction(ctx, RequestFocus, "focusControl", "requestFocus", 1);

    JsBindViews(globalObj);

    JSObjectTemplate toggleType;
    toggleType.Constant("Checkbox", 0);
    toggleType.Constant("Switch", 1);
    toggleType.Constant("Button", 2);

    JSObjectTemplate refreshStatus;
    refreshStatus.Constant("Inactive", 0);
    refreshStatus.Constant("Drag", 1);
    refreshStatus.Constant("OverDrag", 2);
    refreshStatus.Constant("Refresh", 3);
    refreshStatus.Constant("Done", 4);

    JSObjectTemplate mainAxisAlign;
    mainAxisAlign.Constant("Start", 1);
    mainAxisAlign.Constant("Center", 2);
    mainAxisAlign.Constant("End", 3);
    mainAxisAlign.Constant("SpaceBetween", 6);
    mainAxisAlign.Constant("SpaceAround", 7);

    JSObjectTemplate crossAxisAlign;
    crossAxisAlign.Constant("Start", 1);

    crossAxisAlign.Constant("Center", 2);
    crossAxisAlign.Constant("End", 3);
    crossAxisAlign.Constant("Stretch", 4);

    JSObjectTemplate direction;
    direction.Constant("Horizontal", 0);
    direction.Constant("Vertical", 1);

    JSObjectTemplate loadingProgressStyle;
    loadingProgressStyle.Constant("Default", 1);
    loadingProgressStyle.Constant("Circular", 2);
    loadingProgressStyle.Constant("Orbital", 3);

    JSObjectTemplate progressStyle;
    progressStyle.Constant("Linear", 0);
    progressStyle.Constant("Ring", 1);
    progressStyle.Constant("Eclipse", 2);
    progressStyle.Constant("ScaleRing", 3);
    progressStyle.Constant("Capsule", 4);

    JSObjectTemplate stackFit;
    stackFit.Constant("Keep", 0);
    stackFit.Constant("Stretch", 1);
    stackFit.Constant("Inherit", 2);
    stackFit.Constant("FirstChild", 3);

    JSObjectTemplate overflow;
    overflow.Constant("Clip", 0);
    overflow.Constant("Observable", 1);

    JSObjectTemplate alignment;
    alignment.Constant("TopLeft", 0);
    alignment.Constant("TopCenter", 1);
    alignment.Constant("TopRight", 2);
    alignment.Constant("CenterLeft", 3);
    alignment.Constant("Center", 4);
    alignment.Constant("CenterRight", 5);
    alignment.Constant("BottomLeft", 6);
    alignment.Constant("BottomCenter", 7);
    alignment.Constant("BottomRight", 8);

    JSObjectTemplate buttonType;
    buttonType.Constant("Normal", (int)ButtonType::NORMAL);
    buttonType.Constant("Capsule", (int)ButtonType::CAPSULE);
    buttonType.Constant("Circle", (int)ButtonType::CIRCLE);
    buttonType.Constant("Arc", (int)ButtonType::ARC);

    JSObjectTemplate sliderStyle;
    sliderStyle.Constant("OutSet", 0);
    sliderStyle.Constant("InSet", 1);

    JSObjectTemplate sliderChangeMode;
    sliderChangeMode.Constant("Begin", 0);
    sliderChangeMode.Constant("Moving", 1);
    sliderChangeMode.Constant("End", 2);

    JSObjectTemplate iconPosition;
    iconPosition.Constant("Start", 0);
    iconPosition.Constant("End", 1);

    JSObjectTemplate pickerStyle;
    pickerStyle.Constant("Inline", 0);
    pickerStyle.Constant("Block", 1);
    pickerStyle.Constant("Fade", 2);

    JSObjectTemplate badgePosition;
    badgePosition.Constant("RightTop", 0);
    badgePosition.Constant("Right", 1);
    badgePosition.Constant("Left", 2);

    JS_SetPropertyStr(ctx, globalObj, "MainAxisAlign", *mainAxisAlign);
    JS_SetPropertyStr(ctx, globalObj, "CrossAxisAlign", *crossAxisAlign);
    JS_SetPropertyStr(ctx, globalObj, "Direction", *direction);
    JS_SetPropertyStr(ctx, globalObj, "StackFit", *stackFit);
    JS_SetPropertyStr(ctx, globalObj, "Align", *alignment);
    JS_SetPropertyStr(ctx, globalObj, "Overflow", *overflow);
    JS_SetPropertyStr(ctx, globalObj, "ButtonType", *buttonType);
    JS_SetPropertyStr(ctx, globalObj, "ToggleType", *toggleType);
    JS_SetPropertyStr(ctx, globalObj, "RefreshStatus", *refreshStatus);
    JS_SetPropertyStr(ctx, globalObj, "SliderStyle", *sliderStyle);
    JS_SetPropertyStr(ctx, globalObj, "SliderChangeMode", *sliderChangeMode);
    JS_SetPropertyStr(ctx, globalObj, "ProgressStyle", *progressStyle);
    JS_SetPropertyStr(ctx, globalObj, "LoadingProgressStyle", *loadingProgressStyle);
    JS_SetPropertyStr(ctx, globalObj, "IconPosition", *iconPosition);
    JS_SetPropertyStr(ctx, globalObj, "PickerStyle", *pickerStyle);
    JS_SetPropertyStr(ctx, globalObj, "BadgePosition", *badgePosition);

    LOGD("View classes and jsCreateDocument, registerObservableObject functions registered.");
}

} // namespace OHOS::Ace::Framework
