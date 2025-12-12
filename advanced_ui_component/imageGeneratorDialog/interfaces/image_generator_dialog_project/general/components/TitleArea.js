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

var __decorate = (this && this.__decorate) || function (o5, p5, q5, r5) {
    var s5 = arguments.length, t5 = s5 < 3 ? p5 : r5 === null ? r5 = Object.getOwnPropertyDescriptor(p5, q5) : r5, u5;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        t5 = Reflect.decorate(o5, p5, q5, r5);
    else
        for (var v5 = o5.length - 1; v5 >= 0; v5--)
            if (u5 = o5[v5])
                t5 = (s5 < 3 ? u5(t5) : s5 > 3 ? u5(p5, q5, t5) : u5(p5, q5)) || t5;
    return s5 > 3 && t5 && Object.defineProperty(p5, q5, t5), t5;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import promptAction from "@ohos.promptAction";
export class HomeTitle extends ViewV2 {
    constructor(i5, j5, k5, l5 = -1, m5, n5) {
        super(i5, l5, n5);
        this.initParam("titleName", (j5 && "titleName" in j5) ? j5.titleName : '__NA__');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(h5) {
        this.resetParam("titleName", (h5 && "titleName" in h5) ? h5.titleName : '__NA__');
    }
    initialRender() {
        this.observeComponentCreation2((f5, g5) => {
            Column.create();
            Column.height(64);
            Column.width('100%');
            Column.padding({ left: 16, right: 16, top: 8 });
        }, Column);
        this.observeComponentCreation2((d5, e5) => {
            Row.create();
            Row.height(56);
            Row.width(618);
        }, Row);
        this.observeComponentCreation2((b5, c5) => {
            Row.create();
            Row.height('100%');
            Row.width('50%');
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((z4, a5) => {
            Text.create(this.titleName);
            Text.fontFamily("HarmonyHeiTi");
            Text.fontColor("#000000");
            Text.fontSize(20);
            Text.fontWeight(700);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((x4, y4) => {
            Row.create();
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.End);
            Row.height('100%');
            Row.width('50%');
        }, Row);
        this.observeComponentCreation2((v4, w4) => {
            __Common__.create();
            __Common__.margin({ right: 8 });
        }, __Common__);
        {
            this.observeComponentCreation2((r4, s4) => {
                if (s4) {
                    let t4 = new TitleMenu(this, { name: 'menu one' }, undefined, r4, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/TitleArea.ets", line: 23, col: 11 });
                    ViewV2.create(t4);
                    let u4 = () => {
                        return {
                            name: 'menu one'
                        };
                    };
                    t4.paramsGenerator_ = u4;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(r4, {
                        name: 'menu one'
                    });
                }
            }, { name: "TitleMenu" });
        }
        __Common__.pop();
        {
            this.observeComponentCreation2((n4, o4) => {
                if (o4) {
                    let p4 = new TitleMenu(this, { name: 'x_icon' }, undefined, n4, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/TitleArea.ets", line: 25, col: 11 });
                    ViewV2.create(p4);
                    let q4 = () => {
                        return {
                            name: 'x_icon'
                        };
                    };
                    p4.paramsGenerator_ = q4;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(n4, {
                        name: 'x_icon'
                    });
                }
            }, { name: "TitleMenu" });
        }
        Row.pop();
        Row.pop();
        Column.pop();
    }
    updateStateVars(m4) {
        if (m4 === undefined) {
            return;
        }
        if ("titleName" in m4) {
            this.updateParam("titleName", m4.titleName);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], HomeTitle.prototype, "titleName", void 0);
class TitleMenu extends ViewV2 {
    constructor(g4, h4, i4, j4 = -1, k4, l4) {
        super(g4, j4, l4);
        this.initParam("name", (h4 && "name" in h4) ? h4.name : '__NA__');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(f4) {
        this.resetParam("name", (f4 && "name" in f4) ? f4.name : '__NA__');
    }
    initialRender() {
        this.observeComponentCreation2((d4, e4) => {
            Image.create('');
            Image.width(40);
            Image.height(40);
            Image.borderRadius(20);
            Image.backgroundColor('rgba(0,0,0,0.05)');
            Image.onClick(() => {
                promptAction.openToast({ message: `${this.name} clicked` })
                    .then(() => { })
                    .catch(() => { });
            });
        }, Image);
    }
    updateStateVars(c4) {
        if (c4 === undefined) {
            return;
        }
        if ("name" in c4) {
            this.updateParam("name", c4.name);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], TitleMenu.prototype, "name", void 0);
