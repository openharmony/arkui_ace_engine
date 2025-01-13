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

#include "arc_list_napi.h"

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
#include "bridge/declarative_frontend/jsview/js_scrollable.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

extern const char _binary_arkui_arclist_abc_start[];
extern const char _binary_arkui_arclist_abc_end[];

namespace OHOS::Ace {
namespace {
static constexpr size_t MAX_ARG_NUM = 10;
} // namespace

using namespace ArcList;

namespace ArcList {
void SetScroller(napi_env env, Framework::JSScroller* jsScroller)
{
    if (jsScroller) {
        auto scroller = Referenced::Claim(reinterpret_cast<Framework::JSScroller*>(jsScroller));
        scroller->SetInstanceId(Container::CurrentId());

        auto listController = ListModel::GetInstance()->CreateScrollController();
        scroller->SetController(listController);

        // Init scroll bar proxy.
        auto proxy = scroller->GetScrollBarProxy();
        if (!proxy) {
            proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
            scroller->SetScrollBarProxy(proxy);
        }
        ListModel::GetInstance()->SetScroller(listController, proxy);
    }
}

void SetHeader(napi_env env, napi_value jsBuilderNode)
{
    if (ExtNapiUtils::CheckTypeForNapiValue(env, jsBuilderNode, napi_object)) {
        napi_value jsNodePtr = ExtNapiUtils::GetNamedProperty(env, jsBuilderNode, "nodePtr_");
        NG::FrameNode* nodePtr = nullptr;
        if (napi_get_value_external(env, jsNodePtr, (void**)&nodePtr) == napi_ok && nodePtr != nullptr) {
            auto frameNode = AceType::Claim(nodePtr);
            ListModel::GetInstance()->SetHeader(frameNode);
        }
    }
}

napi_value JsCreate(napi_env env, napi_callback_info info)
{
    ListModel::GetInstance()->Create(true);
    auto vm = reinterpret_cast<NativeEngine*>(env)->GetEcmaVm();
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    if (argc > 0 && ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_object)) {
        napi_value jsInitialIndex = ExtNapiUtils::GetNamedProperty(env, argv[0], "initialIndex");
        if (ExtNapiUtils::CheckTypeForNapiValue(env, jsInitialIndex, napi_number)) {
            int32_t initialIndex = ExtNapiUtils::GetCInt32(env, jsInitialIndex);
            if (initialIndex >= 0) {
                ListModel::GetInstance()->SetInitialIndex(initialIndex);
            }
        }

        napi_value jsScroller = ExtNapiUtils::GetNamedProperty(env, argv[0], "scroller");
        if (ExtNapiUtils::CheckTypeForNapiValue(env, jsScroller, napi_object)) {
            panda::Local<panda::ObjectRef> scrollerObject((uintptr_t)jsScroller);
            if (scrollerObject->GetNativePointerFieldCount(vm) > 0) {
                Framework::JSScroller* scroller = (Framework::JSScroller*)scrollerObject->GetNativePointerField(vm, 0);
                SetScroller(env, scroller);
            }
        }

        napi_value jsHeader = ExtNapiUtils::GetNamedProperty(env, argv[0], "header");
        if (ExtNapiUtils::CheckTypeForNapiValue(env, jsHeader, napi_object)) {
            napi_value jsBuilderNode = ExtNapiUtils::GetNamedProperty(env, jsHeader, "builderNode_");
            SetHeader(env, jsBuilderNode);
        }
    }
    return ExtNapiUtils::CreateNull(env);
}

napi_value JsSpace(napi_env env, napi_callback_info info)
{
    HandleValue handleValue = [](napi_env env, napi_value value, napi_valuetype type) {
        CalcDimension space;
        if (type == napi_null || !ExtNapiUtils::ParseLengthMetrics(env, value, space) || space.IsNegative()) {
            space.Reset();
        }
        ListModel::GetInstance()->SetSpace(space);
    };
    HandleUndefined handleUndefined = [] { ListModel::GetInstance()->SetSpace(Dimension(0)); };
    return UnwrapOptionalValue(env, info, handleValue, handleUndefined);
}

napi_value JsDigitalCrownSensitivity(napi_env env, napi_callback_info info)
{
#ifdef SUPPORT_DIGITAL_CROWN
    HandleValue handleValue = [](napi_env env, napi_value value, napi_valuetype type) {
        int32_t sensitivity = static_cast<int32_t>(CrownSensitivity::MEDIUM);
        napi_get_value_int32(env, value, &sensitivity);
        if (sensitivity < static_cast<int32_t>(CrownSensitivity::LOW) ||
            sensitivity > static_cast<int32_t>(CrownSensitivity::HIGH)) {
            sensitivity = static_cast<int32_t>(CrownSensitivity::MEDIUM);
        }
        ListModel::GetInstance()->SetDigitalCrownSensitivity(static_cast<CrownSensitivity>(sensitivity));
    };
    HandleUndefined handleUndefined = [] {
        ListModel::GetInstance()->SetDigitalCrownSensitivity(CrownSensitivity::MEDIUM);
    };
    return UnwrapOptionalValue(env, info, handleValue, handleUndefined);
#else
    return ExtNapiUtils::CreateNull(env);
#endif
}

napi_value JsResetSpace(napi_env env, napi_callback_info info)
{
    return UnwrapModifier(env, info, [](napi_env env, NG::FrameNode* frameNode, int32_t num, napi_value* params) {
        NG::ListModelNG::SetListSpace(frameNode, Dimension(0));
    });
}

napi_value JsSetSpace(napi_env env, napi_callback_info info)
{
    return UnwrapModifier(env, info, [](napi_env env, NG::FrameNode* frameNode, int32_t num, napi_value* params) {
        CalcDimension space;
        if (num < 1) {
            space.Reset();
        } else if (!ExtNapiUtils::ParseLengthMetrics(env, params[0], space) || space.IsNegative()) {
            space.Reset();
        }

        NG::ListModelNG::SetListSpace(frameNode, space);
    });
}

napi_value JsResetDigitalCrownSensitivity(napi_env env, napi_callback_info info)
{
#ifdef SUPPORT_DIGITAL_CROWN
    return UnwrapModifier(env, info, [](napi_env env, NG::FrameNode* frameNode, int32_t num, napi_value* params) {
        NG::ListModelNG::SetDigitalCrownSensitivity(frameNode, CrownSensitivity::MEDIUM);
    });
#else
    return ExtNapiUtils::CreateNull(env);
#endif
}

napi_value JsSetDigitalCrownSensitivity(napi_env env, napi_callback_info info)
{
#ifdef SUPPORT_DIGITAL_CROWN
    return UnwrapModifier(env, info, [](napi_env env, NG::FrameNode* frameNode, int32_t num, napi_value* params) {
        int32_t sensitivity = static_cast<int32_t>(CrownSensitivity::MEDIUM);
        if (num > 0) {
            napi_get_value_int32(env, params[0], &sensitivity);
            if (sensitivity < static_cast<int32_t>(CrownSensitivity::LOW) ||
                sensitivity > static_cast<int32_t>(CrownSensitivity::HIGH)) {
                sensitivity = static_cast<int32_t>(CrownSensitivity::MEDIUM);
            }
            NG::ListModelNG::SetDigitalCrownSensitivity(frameNode, static_cast<CrownSensitivity>(sensitivity));
        }
    });
#else
    return ExtNapiUtils::CreateNull(env);
#endif
}

napi_value JsResetChildrenMainSize(napi_env env, napi_callback_info info)
{
    return UnwrapModifier(env, info, [](napi_env env, NG::FrameNode* frameNode, int32_t num, napi_value* params) {
        NG::ListModelNG::ResetListChildrenMainSize(frameNode);
    });
}

napi_value JsSetChildrenMainSize(napi_env env, napi_callback_info info)
{
    return UnwrapModifier(env, info, [](napi_env env, NG::FrameNode* frameNode, int32_t num, napi_value* params) {
        float defaultSize = 0.f;
        std::vector<float> mainSize;

        if (num > 1) {
            double tmpVar;
            napi_get_value_double(env, params[0], &tmpVar);
            defaultSize = static_cast<float>(tmpVar);

            if (ExtNapiUtils::IsArray(env, params[1])) {
                uint32_t length;
                napi_get_array_length(env, params[1], &length);
                for (uint32_t i = 0; i < length; i++) {
                    napi_value elementValue;
                    napi_get_element(env, params[1], i, &elementValue);
                    napi_get_value_double(env, elementValue, &tmpVar);
                    mainSize.emplace_back(static_cast<float>(tmpVar));
                }
            }
        }

        NG::ListModelNG::SetListChildrenMainSize(frameNode, defaultSize, mainSize);
    });
}
} // namespace ArcList

namespace ArcListItem {
void CreateForPartialUpdate(napi_env env, int32_t argc, napi_value* argv)
{
    const int32_t ARGS_LENGTH = 2;
    if (argc < ARGS_LENGTH) {
        ListItemModel::GetInstance()->Create(true);
        return;
    }
    napi_value arg0 = argv[0];
    if (!ExtNapiUtils::CheckTypeForNapiValue(env, arg0, napi_function)) {
        ListItemModel::GetInstance()->Create(true);
        return;
    }
    napi_value arg1 = argv[1];
    if (!ExtNapiUtils::CheckTypeForNapiValue(env, arg1, napi_boolean)) {
        return;
    }
    const bool isLazy = ExtNapiUtils::GetBool(env, arg1);

    V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE;
    if (argc > ARGS_LENGTH && ExtNapiUtils::CheckTypeForNapiValue(env, argv[ARGS_LENGTH], napi_object)) {
        napi_value styleObj = ExtNapiUtils::GetNamedProperty(env, argv[ARGS_LENGTH], "style");
        int32_t style = 0;
        if (ExtNapiUtils::CheckTypeForNapiValue(env, styleObj, napi_number) &&
            napi_get_value_int32(env, styleObj, &style) == napi_ok) {
            listItemStyle = static_cast<V2::ListItemStyle>(style);
        }
    }

    if (!isLazy) {
        ListItemModel::GetInstance()->Create(true);
    } else {
        auto jsDeepRender = std::make_shared<NapiAsyncEvent>(env, arg0);
        auto listItemDeepRenderFunc = [jsDeepRender](int32_t nodeId) {
            ACE_SCOPED_TRACE("JSArcListItem::ExecuteDeepRender");
            napi_env env = jsDeepRender->GetEnv();
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            CHECK_NULL_VOID(scope);

            napi_value jsParams[2];
            napi_create_int32(env, nodeId, &jsParams[0]);
            napi_create_int32(env, 1, &jsParams[1]);
            jsDeepRender->Call(2, jsParams);

            napi_close_handle_scope(env, scope);
        }; // listItemDeepRenderFunc lambda
        ListItemModel::GetInstance()->Create(std::move(listItemDeepRenderFunc), listItemStyle, true);
        ListItemModel::GetInstance()->SetIsLazyCreating(isLazy);
    }
}

napi_value JsCreate(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));

    if (Container::IsCurrentUsePartialUpdate()) {
        CreateForPartialUpdate(env, argc, argv);
    } else {
        std::string type;
        if (argc >= 1 && ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_string)) {
            type = ExtNapiUtils::GetStringFromValueUtf8(env, argv[0]);
        }
        ListItemModel::GetInstance()->Create(true);
        if (!type.empty()) {
            ListItemModel::GetInstance()->SetType(type);
        }
    }
    return ExtNapiUtils::CreateNull(env);
}

napi_value JsAutoScale(napi_env env, napi_callback_info info)
{
    HandleValue handleValue = [](napi_env env, napi_value value, napi_valuetype type) {
        bool autoScale = true;
        napi_get_value_bool(env, value, &autoScale);
        ListItemModel::GetInstance()->SetAutoScale(autoScale);
    };
    HandleUndefined handleUndefined = [] { ListItemModel::GetInstance()->SetAutoScale(true); };
    return UnwrapOptionalValue(env, info, handleValue, handleUndefined);
}

napi_value JsResetAutoScale(napi_env env, napi_callback_info info)
{
    return UnwrapModifier(env, info, [](napi_env env, NG::FrameNode* frameNode, int32_t num, napi_value* params) {
        NG::ListItemModelNG::SetAutoScale(frameNode, true);
    });
}

napi_value JsSetAutoScale(napi_env env, napi_callback_info info)
{
    return UnwrapModifier(env, info, [](napi_env env, NG::FrameNode* frameNode, int32_t num, napi_value* params) {
        if (num >= 1) {
            bool autoScale = true;
            napi_get_value_bool(env, params[0], &autoScale);
            NG::ListItemModelNG::SetAutoScale(frameNode, autoScale);
        }
    });
}
} // namespace ArcListItem

namespace ArcList {
napi_value UnwrapOptionalValue(
    napi_env env, napi_callback_info info, const HandleValue& handleValue, const HandleUndefined& handleUndefined)
{
    napi_value retValue = ExtNapiUtils::CreateNull(env);
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    if (argc < 1) {
        return retValue;
    }
    napi_valuetype valueType = ExtNapiUtils::GetValueType(env, argv[0]);
    if (valueType == napi_undefined) {
        handleUndefined();
    } else {
        handleValue(env, argv[0], valueType);
    }
    return retValue;
}

napi_value UnwrapModifier(napi_env env, napi_callback_info info, const HandleModifier& handleModifier)
{
    napi_value retValue = ExtNapiUtils::CreateNull(env);
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    if (argc < 1) {
        return retValue;
    }
    NG::FrameNode* nodePtr = nullptr;
    if (napi_get_value_external(env, argv[0], (void**)&nodePtr) != napi_ok || nodePtr == nullptr) {
        return retValue;
    }
    handleModifier(env, nodePtr, argc - 1, &argv[1]);
    return retValue;
}

napi_value InitArcList(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("create", ArcList::JsCreate),
        DECLARE_NAPI_FUNCTION("space", ArcList::JsSpace),
        DECLARE_NAPI_FUNCTION("digitalCrownSensitivity", ArcList::JsDigitalCrownSensitivity),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));

    napi_value modifier = nullptr;
    napi_create_object(env, &modifier);
    napi_property_descriptor modifierDesc[] = {
        DECLARE_NAPI_FUNCTION("resetSpace", ArcList::JsResetSpace),
        DECLARE_NAPI_FUNCTION("setSpace", ArcList::JsSetSpace),
        DECLARE_NAPI_FUNCTION("resetDigitalCrownSensitivity", ArcList::JsResetDigitalCrownSensitivity),
        DECLARE_NAPI_FUNCTION("setDigitalCrownSensitivity", ArcList::JsSetDigitalCrownSensitivity),
        DECLARE_NAPI_FUNCTION("resetChildrenMainSize", ArcList::JsResetChildrenMainSize),
        DECLARE_NAPI_FUNCTION("setChildrenMainSize", ArcList::JsSetChildrenMainSize),
    };
    NAPI_CALL(env, napi_define_properties(env, modifier, sizeof(modifierDesc) / sizeof(modifierDesc[0]), modifierDesc));
    NAPI_CALL(env, napi_set_named_property(env, exports, "modifier", modifier));

    return exports;
}

napi_value InitArcListItem(napi_env env, napi_value exports)
{
    napi_value item = nullptr;
    napi_create_object(env, &item);
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("createInternal", ArcListItem::JsCreate),
        DECLARE_NAPI_FUNCTION("autoScale", ArcListItem::JsAutoScale),
    };
    NAPI_CALL(env, napi_define_properties(env, item, sizeof(desc) / sizeof(desc[0]), desc));

    napi_value modifier = nullptr;
    napi_create_object(env, &modifier);
    napi_property_descriptor modifierDesc[] = {
        DECLARE_NAPI_FUNCTION("resetAutoScale", ArcListItem::JsResetAutoScale),
        DECLARE_NAPI_FUNCTION("setAutoScale", ArcListItem::JsSetAutoScale),
    };
    NAPI_CALL(env, napi_define_properties(env, modifier, sizeof(modifierDesc) / sizeof(modifierDesc[0]), modifierDesc));
    NAPI_CALL(env, napi_set_named_property(env, item, "modifier", modifier));

    NAPI_CALL(env, napi_set_named_property(env, exports, "item", item));
    return exports;
}

napi_value ExportArcList(napi_env env, napi_value exports)
{
    InitArcList(env, exports);
    InitArcListItem(env, exports);
    return exports;
}
} // namespace ArcList

} // namespace OHOS::Ace

extern "C" ACE_FORCE_EXPORT void NAPI_arkui_ArcList_GetABCCode(const char** buf, int* buflen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_arclist_abc_start;
    }
    if (buflen != nullptr) {
        *buflen = _binary_arkui_arclist_abc_end - _binary_arkui_arclist_abc_start;
    }
}

static napi_module arcListModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = OHOS::Ace::ArcList::ExportArcList,
    .nm_modname = "arkui.ArcList",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterArcListModule()
{
    napi_module_register(&arcListModule);
}
