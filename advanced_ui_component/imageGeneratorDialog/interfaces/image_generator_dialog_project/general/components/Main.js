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

var __decorate = (this && this.__decorate) || function (h3, i3, j3, k3) {
    var l3 = arguments.length, m3 = l3 < 3 ? i3 : k3 === null ? k3 = Object.getOwnPropertyDescriptor(i3, j3) : k3, n3;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        m3 = Reflect.decorate(h3, i3, j3, k3);
    else
        for (var o3 = h3.length - 1; o3 >= 0; o3--)
            if (n3 = h3[o3])
                m3 = (l3 < 3 ? n3(m3) : l3 > 3 ? n3(i3, j3, m3) : n3(i3, j3)) || m3;
    return l3 > 3 && m3 && Object.defineProperty(i3, j3, m3), m3;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { CanvasHome } from "./CanvasFramework";
export class ImageGeneratorDialog extends ViewV2 {
    constructor(b3, c3, d3, e3 = -1, f3, g3) {
        super(b3, e3, g3);
        this.stack = new NavPathStack();
        this.options = undefined;
        this.width_ = 650;
        this.height_ = 560;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(a3) {
        this.width_ = 650;
        this.height_ = 560;
    }
    pageMap(s2, t2 = null) {
        this.observeComponentCreation2((u2, v2) => {
            If.create();
            if (s2 === 'home') {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((w2, x2) => {
                            if (x2) {
                                let y2 = new CanvasHome(this, {}, undefined, w2, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/Main.ets", line: 29, col: 7 });
                                ViewV2.create(y2);
                                let z2 = () => {
                                    return {};
                                };
                                y2.paramsGenerator_ = z2;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(w2, {});
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
        this.observeComponentCreation2((q2, r2) => {
            Scroll.create();
            Scroll.width('100%');
            Scroll.height('100%');
            Scroll.scrollable(ScrollDirection.FREE);
        }, Scroll);
        this.observeComponentCreation2((o2, p2) => {
            Navigation.create(this.stack, { moduleName: "image_generator_dialog", pagePath: "", isUserCreateStack: true });
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
