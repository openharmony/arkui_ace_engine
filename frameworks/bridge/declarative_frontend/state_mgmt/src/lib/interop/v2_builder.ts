/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

class BuilderViewV2 extends ViewV2 {
    aboutToBeDeleted(): void {
    }
    protected purgeVariableDependenciesOnElmtId(removedElmtId: number): void {
    }
    public updateRecycleElmtId(oldElmtId: number, newElmtId: number): void {
    }
    public updateStateVars(params: Object): void  {
    }
    constructor(parent, extraInfo, elmtId = -1) {
        super(parent, elmtId, extraInfo);
        this.finalizeConstruction();
    }

    initialRender(): void {

    }
    rerender(): void {
        this.updateDirtyElements();
    }
    static getEntryName(): string {
        return 'BuilderViewV2';
    }
}

function createCompatibleNodeWithFuncVoid(fn: (() => void) | Object, elmtId: number): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)();
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)();
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

// ArkTS1.1
function createCompatibleNodeWithFunc<T1>(fn: ((arg1: T1) => void) | Object, elmtId: number, arg1: T1): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(this.arg1);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(this.arg1);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    if (typeof arg1 === 'object') {
        builderViewV2['arg1'] = UIUtilsImpl.instance().makeObserved(arg1);
    } else {
        builderViewV2['arg1'] = arg1;
    }
    builderViewV2[ObserveV2.V2_DECO_META] ??= {};
    return builderViewV2;
}

// ArkTS1.1
function createCompatibleNodeWithFunc2<T1, T2>(fn: ((arg1: T1, arg2: T2) => void) | Object,
    elmtId: number, arg1: T1, arg2: T2): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(arg1, arg2);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(arg1, arg2);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

function createCompatibleNodeWithFunc3<T1, T2, T3>(fn: ((arg1: T1, arg2: T2, arg3: T3) => void) | Object,
    elmtId: number, arg1: T1, arg2: T2, arg3: T3): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(arg1, arg2, arg3);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(arg1, arg2, arg3);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

function createCompatibleNodeWithFunc4<T1, T2, T3, T4>(fn: ((arg1: T1, arg2: T2, arg3: T3, arg4: T4) => void) | Object,
    elmtId: number, arg1: T1, arg2: T2, arg3: T3, arg4: T4): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(arg1, arg2, arg3, arg4);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(arg1, arg2, arg3, arg4);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

function createCompatibleNodeWithFunc5<T1, T2, T3, T4, T5>(fn: ((arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5) => void) | Object,
    elmtId: number, arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(arg1, arg2, arg3, arg4, arg5);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(arg1, arg2, arg3, arg4, arg5);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

function createCompatibleNodeWithFunc6<T1, T2, T3, T4, T5, T6>(fn: ((arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6) => void) | Object,
    elmtId: number, arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

function createCompatibleNodeWithFunc7<T1, T2, T3, T4, T5, T6, T7>(fn: ((arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6,
    arg7: T7) => void) | Object, elmtId: number, arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6, arg7: T7): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

function createCompatibleNodeWithFunc8<T1, T2, T3, T4, T5, T6, T7, T8>(fn: ((arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6,
    arg7: T7, arg8: T8) => void) | Object, elmtId: number, arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6, arg7: T7, arg8: T8): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

function createCompatibleNodeWithFunc9<T1, T2, T3, T4, T5, T6, T7, T8, T9>(fn: ((arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6,
    arg7: T7, arg8: T8, arg9: T9) => void) | Object, elmtId: number, arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6, arg7: T7,
    arg8: T8, arg9: T9): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

function createCompatibleNodeWithFunc10<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(fn: ((arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6,
    arg7: T7, arg8: T8, arg9: T9, arg10: T10) => void) | Object, elmtId: number, arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5, arg6: T6, arg7: T7,
    arg8: T8, arg9: T9, arg10: T10): ViewV2 {
    let builderViewV2 = new BuilderViewV2(undefined, undefined, elmtId);
    let buildFunc = function (): void {
        if (fn && typeof fn === 'function') {
            fn.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
        } else if (fn && typeof fn === 'object' && 'builder' in fn && typeof fn.builder === 'function') {
            fn.builder.bind(this)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
        }
    }
    builderViewV2.initialRender = buildFunc.bind(builderViewV2);
    builderViewV2.rerender = (): void => { builderViewV2.updateDirtyElements(); };
    return builderViewV2;
}

function runPendingJobs(): void {
    console.log('runPendingJobs enter');
}