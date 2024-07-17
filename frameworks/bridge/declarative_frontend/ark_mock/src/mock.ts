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

abstract class ViewPU {
    id__(): number { return 0; }
    aboutToUpdate?: (updateParams: Object) => void;
    updateStateVars(params: {}): void {}
    aboutToReuseInternal(param?: Object): void {}
    aboutToRecycleInternal(): void {}
    updateDirtyElements(): void {}
}
(globalThis as any).ViewPU = ViewPU;

class __JSBaseNode__ {
    constructor(options?: RenderOptions) {}
    create(builder: (...args: Object[]) => void, params: Object, update: (instanceId: number, nodePtr: NodePtr) => void,
        updateConfiguration): NodePtr {
        return null;
    }
    finishUpdateFunc(): void {}
    postTouchEvent(touchEvent: TouchEvent): boolean { return false; }
    disposeNode(): void {}
    updateStart(): void {}
    updateEnd(): void {}
}
(globalThis as any).__JSBaseNode__ = __JSBaseNode__;

class __JSScopeUtil__ {
    static syncInstanceId(instanceId: number): void {}
    static restoreInstanceId(): void {}
}
(globalThis as any).__JSScopeUtil__ = __JSScopeUtil__;

interface CustomDialogControllerConstructorArg {
    builder: () => void;
    cancel?: () => void;
}

class CustomDialogController {
    private arg_: CustomDialogControllerConstructorArg;
    private view_: ViewPU;

    constructor(arg: CustomDialogControllerConstructorArg, view: ViewPU) {}
    open() {}
    close() {}
}
(globalThis as any).CustomDialogController = CustomDialogController;

class TextModifier {
    constructor(nativePtr: KNode, classType: ModifierType) {}
    applyNormalAttribute(instance: TextAttribute) {}
}

export default { ViewPU, __JSBaseNode__, __JSScopeUtil__, CustomDialogController, TextModifier };