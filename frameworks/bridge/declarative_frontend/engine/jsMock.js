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

class ViewPU {
    id__() { return 0; }
    updateStateVars(params) {}
    aboutToReuseInternal(param) {}
    aboutToRecycleInternal() {}
    updateDirtyElements() {}
}
globalThis.ViewPU = ViewPU;

class __JSBaseNode__ {
    constructor(options) {}
    create(builder, params, update, updateConfiguration) {
        return null;
    }
    finishUpdateFunc() {}
    postTouchEvent(touchEvent) { return false; }
    disposeNode() {}
    updateStart() {}
    updateEnd() {}
}
globalThis.__JSBaseNode__ = __JSBaseNode__;

class __JSScopeUtil__ {
    static syncInstanceId(instanceId) {}
    static restoreInstanceId() {}
}
globalThis.__JSScopeUtil__ = __JSScopeUtil__;

class CustomDialogController {
    constructor(arg, view) {}
    open() {}
    close() {}
}
globalThis.CustomDialogController = CustomDialogController;

class TextModifier {
    constructor(nativePtr, classType) {}
    applyNormalAttribute(instance) {}
}

export default { ViewPU, __JSBaseNode__, __JSScopeUtil__, CustomDialogController, TextModifier };