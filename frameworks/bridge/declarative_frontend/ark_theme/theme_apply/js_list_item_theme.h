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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_LIST_ITEM_THEME_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_LIST_ITEM_THEME_H

namespace OHOS::Ace::Framework {
class JSListItemTheme {
public:
    static void ObtainDeepRenderFuncForThemeSupport(panda::ecmascript::EcmaVM* vm, JSRef<JSFunc> &deepRenderFunc)
    {
        CHECK_NULL_VOID(vm);

        panda::Local<panda::ObjectRef> globalObj(JSNApi::GetGlobalObject(vm));
        if (!globalObj->IsObject(vm)) {
            return;
        }

        JSRef<JSVal> list = JSRef<JSObject>::Make(globalObj)->GetProperty("ListItem");
        if (!list->IsObject()) {
            return;
        }

        JSRef<JSVal> updateItemFunc = JSRef<JSObject>::Cast(list)->GetProperty("getDeepRenderFuncForThemeSupport");
        if (!updateItemFunc->IsFunction()) {
            return;
        }

        JSRef<JSVal> params[] = { JSRef<JSVal>::Cast(deepRenderFunc) };
        JSRef<JSVal> retVal = JSRef<JSFunc>::Cast(updateItemFunc)->Call(JSRef<JSObject>(), ArraySize(params), params);
        if (!retVal->IsFunction()) {
            return;
        }
        deepRenderFunc = JSRef<JSFunc>::Cast(retVal);
    }
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_THEME_JS_LIST_ITEM_THEME_H