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
    constructor(c6, d6, e6, f6 = -1, g6, h6) {
        super(c6, f6, h6);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(b6) {
    }
    initialRender() {
        this.observeComponentCreation2((z5, a6) => {
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
