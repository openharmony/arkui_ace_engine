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

var __decorate = (this && this.__decorate) || function (n11, o11, p11, q11) {
    var r11 = arguments.length, s11 = r11 < 3 ? o11 : q11 === null ? q11 = Object.getOwnPropertyDescriptor(o11, p11) : q11, t11;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        s11 = Reflect.decorate(n11, o11, p11, q11);
    else
        for (var u11 = n11.length - 1; u11 >= 0; u11--)
            if (t11 = n11[u11])
                s11 = (r11 < 3 ? t11(s11) : r11 > 3 ? t11(o11, p11, s11) : t11(o11, p11)) || s11;
    return r11 > 3 && s11 && Object.defineProperty(o11, p11, s11), s11;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
export function UserInteractiveTabBarBuilder(f11, g11 = null) {
    const h11 = f11;
    {
        (g11 ? g11 : this).observeComponentCreation2((i11, j11, k11 = h11) => {
            if (j11) {
                let l11 = new UserInteractiveAreaTabBar(g11 ? g11 : this, {
                    name: k11
                }, undefined, i11, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 17, col: 3 });
                ViewV2.create(l11);
                let m11 = () => {
                    return {
                        name: k11
                    };
                };
                l11.paramsGenerator_ = m11;
            }
            else {
                (g11 ? g11 : this).updateStateVarsOfChildByElmtId(i11, {
                    name: k11
                });
            }
        }, { name: "UserInteractiveAreaTabBar" });
    }
}
export class FunctionAreaPlaceholder extends ViewV2 {
    constructor(z10, a11, b11, c11 = -1, d11, e11) {
        super(z10, c11, e11);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(y10) {
    }
    initialRender() {
        this.observeComponentCreation2((w10, x10) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.padding({
                right: 14
            });
        }, Column);
        this.observeComponentCreation2((u10, v10) => {
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
    constructor(o10, p10, q10, r10 = -1, s10, t10) {
        super(o10, r10, t10);
        this.initParam("name", (p10 && "name" in p10) ? p10.name : '__NA__');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(n10) {
        this.resetParam("name", (n10 && "name" in n10) ? n10.name : '__NA__');
    }
    initialRender() {
        this.observeComponentCreation2((l10, m10) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((j10, k10) => {
            Column.create();
            Column.padding(12);
            Column.width(48);
            Column.height(48);
            Column.margin({ bottom: 4 });
            Column.borderRadius(24);
            Column.backgroundColor('rgba(0,0,0,0.05)');
        }, Column);
        this.observeComponentCreation2((h10, i10) => {
            Image.create('');
            Image.width(24);
            Image.height(24);
        }, Image);
        Column.pop();
        this.observeComponentCreation2((f10, g10) => {
            Column.create();
            Column.height(10);
        }, Column);
        this.observeComponentCreation2((d10, e10) => {
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
    updateStateVars(c10) {
        if (c10 === undefined) {
            return;
        }
        if ("name" in c10) {
            this.updateParam("name", c10.name);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], UserInteractiveAreaTabBar.prototype, "name", void 0);
