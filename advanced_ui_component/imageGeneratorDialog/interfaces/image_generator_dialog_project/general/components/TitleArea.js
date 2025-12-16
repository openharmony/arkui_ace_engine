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

var __decorate = (this && this.__decorate) || function (u9, v9, w9, x9) {
    var y9 = arguments.length, z9 = y9 < 3 ? v9 : x9 === null ? x9 = Object.getOwnPropertyDescriptor(v9, w9) : x9, a10;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        z9 = Reflect.decorate(u9, v9, w9, x9);
    else
        for (var b10 = u9.length - 1; b10 >= 0; b10--)
            if (a10 = u9[b10])
                z9 = (y9 < 3 ? a10(z9) : y9 > 3 ? a10(v9, w9, z9) : a10(v9, w9)) || z9;
    return y9 > 3 && z9 && Object.defineProperty(v9, w9, z9), z9;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import promptAction from "@ohos.promptAction";
import { ImageGenerateState } from "../types/Declaration";
export class HomeTitle extends ViewV2 {
    constructor(o9, p9, q9, r9 = -1, s9, t9) {
        super(o9, r9, t9);
        this.initParam("titleName", (p9 && "titleName" in p9) ? p9.titleName : '__NA__');
        this.initParam("currentGenerateState", (p9 && "currentGenerateState" in p9) ? p9.currentGenerateState : ImageGenerateState.CONFIGURATION);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(n9) {
        this.resetParam("titleName", (n9 && "titleName" in n9) ? n9.titleName : '__NA__');
        this.resetParam("currentGenerateState", (n9 && "currentGenerateState" in n9) ? n9.currentGenerateState : ImageGenerateState.CONFIGURATION);
    }
    initialRender() {
        this.observeComponentCreation2((l9, m9) => {
            Column.create();
            Column.height(64);
            Column.width('100%');
            Column.padding({ left: 16, right: 16, top: 8 });
        }, Column);
        this.observeComponentCreation2((j9, k9) => {
            Row.create();
            Row.height(56);
            Row.width(618);
        }, Row);
        this.observeComponentCreation2((h9, i9) => {
            Row.create();
            Row.height('100%');
            Row.width('50%');
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((f9, g9) => {
            Text.create(this.titleName);
            Text.fontFamily("HarmonyHeiTi");
            Text.fontColor("#000000");
            Text.fontSize(20);
            Text.fontWeight(700);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((d9, e9) => {
            Row.create();
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.End);
            Row.height('100%');
            Row.width('50%');
        }, Row);
        this.observeComponentCreation2((v8, w8) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((b9, c9) => {
                        __Common__.create();
                        __Common__.margin({ right: 8 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((x8, y8) => {
                            if (y8) {
                                let z8 = new TitleMenu(this, { name: 'menu one' }, undefined, x8, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/TitleArea.ets", line: 41, col: 13 });
                                ViewV2.create(z8);
                                let a9 = () => {
                                    return {
                                        name: 'menu one'
                                    };
                                };
                                z8.paramsGenerator_ = a9;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(x8, {
                                    name: 'menu one'
                                });
                            }
                        }, { name: "TitleMenu" });
                    }
                    __Common__.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        {
            this.observeComponentCreation2((r8, s8) => {
                if (s8) {
                    let t8 = new TitleMenu(this, { name: 'x_icon' }, undefined, r8, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/TitleArea.ets", line: 44, col: 11 });
                    ViewV2.create(t8);
                    let u8 = () => {
                        return {
                            name: 'x_icon'
                        };
                    };
                    t8.paramsGenerator_ = u8;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(r8, {
                        name: 'x_icon'
                    });
                }
            }, { name: "TitleMenu" });
        }
        Row.pop();
        Row.pop();
        Column.pop();
    }
    updateStateVars(q8) {
        if (q8 === undefined) {
            return;
        }
        if ("titleName" in q8) {
            this.updateParam("titleName", q8.titleName);
        }
        if ("currentGenerateState" in q8) {
            this.updateParam("currentGenerateState", q8.currentGenerateState);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], HomeTitle.prototype, "titleName", void 0);
__decorate([
    Param
], HomeTitle.prototype, "currentGenerateState", void 0);
class TitleMenu extends ViewV2 {
    constructor(k8, l8, m8, n8 = -1, o8, p8) {
        super(k8, n8, p8);
        this.initParam("name", (l8 && "name" in l8) ? l8.name : '__NA__');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(j8) {
        this.resetParam("name", (j8 && "name" in j8) ? j8.name : '__NA__');
    }
    initialRender() {
        this.observeComponentCreation2((h8, i8) => {
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
    updateStateVars(g8) {
        if (g8 === undefined) {
            return;
        }
        if ("name" in g8) {
            this.updateParam("name", g8.name);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], TitleMenu.prototype, "name", void 0);
