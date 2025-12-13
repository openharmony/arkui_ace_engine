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

var __decorate = (this && this.__decorate) || function (d7, e7, f7, g7) {
    var h7 = arguments.length, i7 = h7 < 3 ? e7 : g7 === null ? g7 = Object.getOwnPropertyDescriptor(e7, f7) : g7, j7;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        i7 = Reflect.decorate(d7, e7, f7, g7);
    else
        for (var k7 = d7.length - 1; k7 >= 0; k7--)
            if (j7 = d7[k7])
                i7 = (h7 < 3 ? j7(i7) : h7 > 3 ? j7(e7, f7, i7) : j7(e7, f7)) || i7;
    return h7 > 3 && i7 && Object.defineProperty(e7, f7, i7), i7;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { CanvasHome } from "./CanvasFramework";
import { TextTouchUpComponent } from "./TextTouchUp";
export class ImageGeneratorDialog extends ViewV2 {
    constructor(x6, y6, z6, a7 = -1, b7, c7) {
        super(x6, a7, c7);
        this.stack = new NavPathStack();
        this.options = undefined;
        this.width_ = 650;
        this.height_ = 560;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(w6) {
        this.width_ = 650;
        this.height_ = 560;
    }
    pageMap(k6, l6 = null) {
        this.observeComponentCreation2((m6, n6) => {
            If.create();
            if (k6 === 'home') {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((s6, t6) => {
                            if (t6) {
                                let u6 = new CanvasHome(this, {}, undefined, s6, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/Main.ets", line: 30, col: 7 });
                                ViewV2.create(u6);
                                let v6 = () => {
                                    return {};
                                };
                                u6.paramsGenerator_ = v6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(s6, {});
                            }
                        }, { name: "CanvasHome" });
                    }
                });
            }
            else if (k6 === 'textTouchUp') {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((o6, p6) => {
                            if (p6) {
                                let q6 = new TextTouchUpComponent(this, {}, undefined, o6, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/Main.ets", line: 32, col: 7 });
                                ViewV2.create(q6);
                                let r6 = () => {
                                    return {};
                                };
                                q6.paramsGenerator_ = r6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o6, {});
                            }
                        }, { name: "TextTouchUpComponent" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(2, () => {
                });
            }
        }, If);
        If.pop();
    }
    aboutToAppear() {
        this.stack.pushPath({ name: 'home' });
    }
    initialRender() {
        this.observeComponentCreation2((i6, j6) => {
            Scroll.create();
            Scroll.width('100%');
            Scroll.height('100%');
            Scroll.scrollable(ScrollDirection.FREE);
        }, Scroll);
        this.observeComponentCreation2((g6, h6) => {
            Navigation.create(this.stack, { moduleName: "__harDefaultModuleName__", pagePath: "", isUserCreateStack: true });
            Navigation.navDestination({ builder: this.pageMap.bind(this) });
            Navigation.hideNavBar(true);
            Navigation.height(this.height_);
            Navigation.width(this.width_);
            Navigation.borderRadius(32);
            Navigation.mode(NavigationMode.Stack);
            Navigation.clip(true);
            Navigation.alignSelf(ItemAlign.Center);
            Navigation.expandSafeArea([SafeAreaType.SYSTEM, SafeAreaType.CUTOUT]);
        }, Navigation);
        Navigation.pop();
        Scroll.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Local
], ImageGeneratorDialog.prototype, "width_", void 0);
__decorate([
    Local
], ImageGeneratorDialog.prototype, "height_", void 0);
