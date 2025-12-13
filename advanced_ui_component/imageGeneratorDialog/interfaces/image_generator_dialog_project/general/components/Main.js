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

var __decorate = (this && this.__decorate) || function (b7, c7, d7, e7) {
    var f7 = arguments.length, g7 = f7 < 3 ? c7 : e7 === null ? e7 = Object.getOwnPropertyDescriptor(c7, d7) : e7, h7;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        g7 = Reflect.decorate(b7, c7, d7, e7);
    else
        for (var i7 = b7.length - 1; i7 >= 0; i7--)
            if (h7 = b7[i7])
                g7 = (f7 < 3 ? h7(g7) : f7 > 3 ? h7(c7, d7, g7) : h7(c7, d7)) || g7;
    return f7 > 3 && g7 && Object.defineProperty(c7, d7, g7), g7;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { CanvasHome } from "./CanvasFramework";
export class ImageGeneratorDialog extends ViewV2 {
    constructor(v6, w6, x6, y6 = -1, z6, a7) {
        super(v6, y6, a7);
        this.stack = new NavPathStack();
        this.options = undefined;
        this.width_ = 650;
        this.height_ = 560;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(u6) {
        this.width_ = 650;
        this.height_ = 560;
    }
    pageMap(m6, n6 = null) {
        this.observeComponentCreation2((o6, p6) => {
            If.create();
            if (m6 === 'home') {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((q6, r6) => {
                            if (r6) {
                                let s6 = new CanvasHome(this, {}, undefined, q6, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/Main.ets", line: 29, col: 7 });
                                ViewV2.create(s6);
                                let t6 = () => {
                                    return {};
                                };
                                s6.paramsGenerator_ = t6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(q6, {});
                            }
                        }, { name: "CanvasHome" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }
    aboutToAppear() {
        this.stack.pushPath({ name: 'home' });
    }
    initialRender() {
        this.observeComponentCreation2((k6, l6) => {
            Scroll.create();
            Scroll.width('100%');
            Scroll.height('100%');
            Scroll.scrollable(ScrollDirection.FREE);
        }, Scroll);
        this.observeComponentCreation2((i6, j6) => {
            Navigation.create(this.stack, { moduleName: "__harDefaultModuleName__", pagePath: "", isUserCreateStack: true });
            Navigation.navDestination({ builder: this.pageMap.bind(this) });
            Navigation.hideNavBar(true);
            Navigation.height(this.height_);
            Navigation.width(this.width_);
            Navigation.borderRadius(32);
            Navigation.mode(NavigationMode.Stack);
            Navigation.clip(true);
            Navigation.alignSelf(ItemAlign.Center);
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
