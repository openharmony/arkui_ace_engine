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
export class DoodleBoardArea extends ViewV2 {
    constructor(i2, j2, k2, l2 = -1, m2, n2) {
        super(i2, l2, n2);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(h2) {
    }
    initialRender() {
        this.observeComponentCreation2((f2, g2) => {
            Column.create();
            Column.width(386);
            Column.height(386);
            Column.borderRadius(24);
            Column.borderWidth(2);
            Column.borderColor('#ffffff');
            Column.shadow({
                radius: 10,
            });
        }, Column);
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
