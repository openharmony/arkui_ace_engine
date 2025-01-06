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

#include "arc_scroll_bar_napi.h"

#include "ext_napi_utils.h"
#include "core/common/container.h"
#ifdef PREVIEW
#include "native_engine/native_engine.h"
#ifdef WINDOWS_PLATFORM
#undef TRANSPARENT
#undef ERROR
#undef ALTERNATE
#endif
#endif
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"

#include "napi/native_api.h"
#include "napi/native_node_api.h"

extern const char _binary_arkui_arcscrollbar_abc_start[];
extern const char _binary_arkui_arcscrollbar_abc_end[];

namespace OHOS::Ace {
namespace {
static constexpr size_t MAX_ARG_NUM = 10;
} // namespace

using namespace ArcScrollBar;

namespace ArcScrollBar {

napi_value JsCreate(napi_env env, napi_callback_info info)
{
    auto vm = reinterpret_cast<NativeEngine*>(env)->GetEcmaVm();
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));

    bool proxyFlag = false;
    RefPtr<ScrollProxy> proxy;
    int directionNum = -1;
    int32_t stateNum = -1;
    bool infoflag = false;
    if (argc > 0 && ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_object)) {
        infoflag = true;
        napi_value jsScroller = ExtNapiUtils::GetNamedProperty(env, argv[0], "scroller");
        if (ExtNapiUtils::CheckTypeForNapiValue(env, jsScroller, napi_object)) {
            panda::Local<panda::ObjectRef> scrollerObject((uintptr_t)jsScroller);
            if (scrollerObject->GetNativePointerFieldCount(vm) > 0) {
                Framework::JSScroller* scroller = (Framework::JSScroller*)scrollerObject->GetNativePointerField(vm, 0);
                scroller->SetInstanceId(Container::CurrentId());
                auto scrollBarProxy = scroller->GetScrollBarProxy();
                proxyFlag = true;
                proxy = ScrollBarModel::GetInstance()->GetScrollBarProxy(scrollBarProxy);
                scroller->SetScrollBarProxy(proxy);
            }
        }

        napi_value jsState = ExtNapiUtils::GetNamedProperty(env, argv[0], "state");
        if (ExtNapiUtils::CheckTypeForNapiValue(env, jsState, napi_number)) {
            stateNum = ExtNapiUtils::GetCInt32(env, jsState);
        }
    }
    ScrollBarModel::GetInstance()->Create(proxy, infoflag, proxyFlag, directionNum, stateNum, true);
    return ExtNapiUtils::CreateNull(env);
}

napi_value InitArcScrollBar(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("create", ArcScrollBar::JsCreate),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));

    napi_value modifier = nullptr;
    napi_create_object(env, &modifier);
    NAPI_CALL(env, napi_set_named_property(env, exports, "modifier", modifier));

    return exports;
}

napi_value ExportArcScrollBar(napi_env env, napi_value exports)
{
    InitArcScrollBar(env, exports);
    return exports;
}
} // namespace ArcScrollBar

} // namespace OHOS::Ace

extern "C" ACE_FORCE_EXPORT void NAPI_arkui_ArcScrollBar_GetABCCode(const char** buf, int* buflen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_arcscrollbar_abc_start;
    }
    if (buflen != nullptr) {
        *buflen = _binary_arkui_arcscrollbar_abc_end - _binary_arkui_arcscrollbar_abc_start;
    }
}

static napi_module arcScrollBarModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = OHOS::Ace::ArcScrollBar::ExportArcScrollBar,
    .nm_modname = "arkui.ArcScrollBar",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterArcScrollBarModule()
{
    napi_module_register(&arcScrollBarModule);
}
