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

var __decorate = (this && this.__decorate) || function (h7, i7, j7, k7) {
    var l7 = arguments.length, m7 = l7 < 3 ? i7 : k7 === null ? k7 = Object.getOwnPropertyDescriptor(i7, j7) : k7, n7;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        m7 = Reflect.decorate(h7, i7, j7, k7);
    else
        for (var o7 = h7.length - 1; o7 >= 0; o7--)
            if (n7 = h7[o7])
                m7 = (l7 < 3 ? n7(m7) : l7 > 3 ? n7(i7, j7, m7) : n7(i7, j7)) || m7;
    return l7 > 3 && m7 && Object.defineProperty(i7, j7, m7), m7;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
export function UserInteractiveTabBarBuilder(z6, a7 = null) {
    const b7 = z6;
    {
        (a7 ? a7 : this).observeComponentCreation2((c7, d7, e7 = b7) => {
            if (d7) {
                let f7 = new UserInteractiveAreaTabBar(a7 ? a7 : this, {
                    name: e7
                }, undefined, c7, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 2, col: 3 });
                ViewV2.create(f7);
                let g7 = () => {
                    return {
                        name: e7
                    };
                };
                f7.paramsGenerator_ = g7;
            }
            else {
                (a7 ? a7 : this).updateStateVarsOfChildByElmtId(c7, {
                    name: e7
                });
            }
        }, { name: "UserInteractiveAreaTabBar" });
    }
}
export class FunctionAreaPlaceholder extends ViewV2 {
    constructor(t6, u6, v6, w6 = -1, x6, y6) {
        super(t6, w6, y6);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(s6) {
    }
    initialRender() {
        this.observeComponentCreation2((q6, r6) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.padding({
                right: 14
            });
        }, Column);
        this.observeComponentCreation2((o6, p6) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.border({ width: 0.5 });
        }, Column);
        Column.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class UserInteractiveAreaTabBar extends ViewV2 {
    constructor(i6, j6, k6, l6 = -1, m6, n6) {
        super(i6, l6, n6);
        this.initParam("name", (j6 && "name" in j6) ? j6.name : '__NA__');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(h6) {
        this.resetParam("name", (h6 && "name" in h6) ? h6.name : '__NA__');
    }
    initialRender() {
        this.observeComponentCreation2((f6, g6) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((d6, e6) => {
            Column.create();
            Column.padding(12);
            Column.width(48);
            Column.height(48);
            Column.margin({ bottom: 4 });
            Column.borderRadius(24);
            Column.backgroundColor('rgba(0,0,0,0.05)');
        }, Column);
        this.observeComponentCreation2((b6, c6) => {
            Image.create('');
            Image.width(24);
            Image.height(24);
        }, Image);
        Column.pop();
        this.observeComponentCreation2((z5, a6) => {
            Column.create();
            Column.height(10);
        }, Column);
        this.observeComponentCreation2((x5, y5) => {
            Text.create(this.name);
            Text.fontFamily("HarmonyHeiTi");
            Text.fontColor("#000000");
            Text.fontSize(10);
            Text.fontWeight(500);
        }, Text);
        Text.pop();
        Column.pop();
        Column.pop();
    }
    updateStateVars(w5) {
        if (w5 === undefined) {
            return;
        }
        if ("name" in w5) {
            this.updateParam("name", w5.name);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], UserInteractiveAreaTabBar.prototype, "name", void 0);
