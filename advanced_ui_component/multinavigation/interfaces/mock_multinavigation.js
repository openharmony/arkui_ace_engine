/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to  in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

export class MultiNavigation extends ViewPU {
    constructor(q8, r8, s8, t8 = -1, u8 = undefined, v8) {
        super();
    }
    setInitiallyProvidedValue(p8) {
    }
    updateStateVars(o8) {
    }
    purgeVariableDependenciesOnElmtId(n8) {
    }
    aboutToBeDeleted() {
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.backgroundColor('#ccc');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create('Preview not available for this component');
            Text.fontSize(18);
        }, Text);
        Text.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

let MultiNavPathStack = class MultiNavPathStack extends NavPathStack {}

export var SplitPolicy;
(function (z8) {
    z8[z8["HOME_PAGE"] = 0] = "HOME_PAGE";
    z8[z8["DETAIL_PAGE"] = 1] = "DETAIL_PAGE";
    z8[z8["FULL_PAGE"] = 2] = "FULL_PAGE";
    z8[z8["PlACE_HOLDER_PAGE"] = 3] = "PlACE_HOLDER_PAGE";
})(SplitPolicy || (SplitPolicy = {}));

export default { MultiNavigation, MultiNavPathStack, SplitPolicy }