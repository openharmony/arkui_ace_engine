/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <unistd.h>
#include <stdio.h>

#include "common-interop.h"
#include "convertors-jsc.h"

#include <JavaScriptCore/JavaScriptCore.h>

int skoala_startJS(void* view, const char* contentJSFile) {
    printf("skoala_startJS: %p\n", view);
    JSContextGroupRef contextGroup = JSContextGroupCreate();
    JSGlobalContextRef globalContext = JSGlobalContextCreateInGroup(contextGroup, nullptr);
    JSObjectRef globalObject = JSContextGetGlobalObject(globalContext);
    InitExports(globalContext);

    // Create object with view data.
    JSObjectSetProperty(globalContext, globalObject,
        JSStringCreateWithUTF8CString("__koala_view"),
        JSObjectMake(globalContext, nullptr, view),
        kJSPropertyAttributeNone, nullptr);

    // Note, that console.log is visible from Develop menu item in Safari.
    JSStringRef appJs = JSStringCreateWithUTF8CString(contentJSFile);
    JSEvaluateScript(globalContext, appJs, nullptr, nullptr, 1,nullptr);

    return 0;
}
