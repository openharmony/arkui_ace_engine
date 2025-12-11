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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
export class TextInputArea extends ViewV2 {
    constructor(w3, x3, y3, z3 = -1, a4, b4) {
        super(w3, z3, b4);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(v3) {
    }
    initialRender() {
        this.observeComponentCreation2((t3, u3) => {
            Row.create();
            Row.width('100%');
            Row.height(45);
        }, Row);
        this.observeComponentCreation2((r3, s3) => {
            Column.create();
            Column.height(40);
            Column.width(510);
            Column.margin({ top: 3, bottom: 2, left: 16, right: 12 });
            Column.borderRadius(31.11);
            Column.borderWidth(0.5);
        }, Column);
        Column.pop();
        this.observeComponentCreation2((p3, q3) => {
            Column.create();
            Column.borderRadius(31.11);
            Column.borderWidth(0.5);
            Column.height(40);
            Column.width(96);
            Column.margin({ top: 3, bottom: 2, right: 16 });
        }, Column);
        Column.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
