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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        r = Reflect.decorate(decorators, target, key, desc);
    else
        for (var i = decorators.length - 1; i >= 0; i--)
            if (d = decorators[i])
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import promptAction from "@ohos.promptAction";
import { ImageGenerateState } from "../types/Declaration";
export class HomeTitle extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("titleName", (params && "titleName" in params) ? params.titleName : '__NA__');
        this.initParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : ImageGenerateState.CONFIGURATION);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("titleName", (params && "titleName" in params) ? params.titleName : '__NA__');
        this.resetParam("currentGenerateState", (params && "currentGenerateState" in params) ? params.currentGenerateState : ImageGenerateState.CONFIGURATION);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.height(64);
            Column.width('100%');
            Column.padding({ left: 16, right: 16, top: 8 });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height(56);
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height('100%');
            Row.width('50%');
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.titleName);
            Text.fontFamily("HarmonyHeiTi");
            Text.fontColor("#000000");
            Text.fontSize(20);
            Text.fontWeight(700);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.alignItems(VerticalAlign.Center);
            Row.justifyContent(FlexAlign.End);
            Row.height('100%');
            Row.width('50%');
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.margin({ right: 8 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new TitleMenu(this, { name: 'menu one' }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/TitleArea.ets", line: 41, col: 13 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        name: 'menu one'
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
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
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new TitleMenu(this, { name: 'x_icon' }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/TitleArea.ets", line: 44, col: 11 });
                    ViewV2.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            name: 'x_icon'
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {
                        name: 'x_icon'
                    });
                }
            }, { name: "TitleMenu" });
        }
        Row.pop();
        Row.pop();
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("titleName" in params) {
            this.updateParam("titleName", params.titleName);
        }
        if ("currentGenerateState" in params) {
            this.updateParam("currentGenerateState", params.currentGenerateState);
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
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("name", (params && "name" in params) ? params.name : '__NA__');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("name", (params && "name" in params) ? params.name : '__NA__');
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("name" in params) {
            this.updateParam("name", params.name);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], TitleMenu.prototype, "name", void 0);
