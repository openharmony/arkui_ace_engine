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

var __decorate = (this && this.__decorate) || function (q16, r16, s16, t16) {
    var u16 = arguments.length, v16 = u16 < 3 ? r16 : t16 === null ? t16 = Object.getOwnPropertyDescriptor(r16, s16) : t16, w16;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        v16 = Reflect.decorate(q16, r16, s16, t16);
    else
        for (var x16 = q16.length - 1; x16 >= 0; x16--)
            if (w16 = q16[x16])
                v16 = (u16 < 3 ? w16(v16) : u16 > 3 ? w16(r16, s16, v16) : w16(r16, s16)) || v16;
    return u16 > 3 && v16 && Object.defineProperty(r16, s16, v16), v16;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { Constants } from '../common/CommonConstants';
import { CanvasHome } from "./CanvasFramework";
import { TextTouchUpComponent } from "./TextTouchUp";
export class ImageGeneratorDialog extends ViewV2 {
    constructor(k16, l16, m16, n16 = -1, o16, p16) {
        super(k16, n16, p16);
        this.stack = new NavPathStack();
        this.options = undefined;
        this.width_ = 650;
        this.height_ = 560;
        this.MAX_IMAGE_COUNT = 4;
        this.imageInfoArr = [];
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(j16) {
        this.width_ = 650;
        this.height_ = 560;
        this.imageInfoArr = [];
    }
    pageMap(x15, y15 = null) {
        this.observeComponentCreation2((z15, a16) => {
            If.create();
            if (x15 === 'home') {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((f16, g16) => {
                            if (g16) {
                                let h16 = new CanvasHome(this, { imageInfoArr: this.imageInfoArr }, undefined, f16, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/Main.ets", line: 33, col: 7 });
                                ViewV2.create(h16);
                                let i16 = () => {
                                    return {
                                        imageInfoArr: this.imageInfoArr
                                    };
                                };
                                h16.paramsGenerator_ = i16;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(f16, {
                                    imageInfoArr: this.imageInfoArr
                                });
                            }
                        }, { name: "CanvasHome" });
                    }
                });
            }
            else if (x15 === 'textTouchUp') {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((b16, c16) => {
                            if (c16) {
                                let d16 = new TextTouchUpComponent(this, {}, undefined, b16, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/Main.ets", line: 35, col: 7 });
                                ViewV2.create(d16);
                                let e16 = () => {
                                    return {};
                                };
                                d16.paramsGenerator_ = e16;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(b16, {});
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
    initImageInfoArr() {
        if (this.options && this.options.images) {
            let t15 = 1;
            for (let w15 = 0; w15 < this.options.images.length && w15 < this.MAX_IMAGE_COUNT; w15++) {
                if (this.options.images[w15].zIndex === undefined) {
                    this.options.images[w15].zIndex = t15;
                    t15++;
                }
                this.imageInfoArr.push(this.options.images[w15]);
            }
            this.imageInfoArr.sort((u15, v15) => {
                return (u15.zIndex ?? 0) - (v15.zIndex ?? 0);
            });
        }
        while (this.imageInfoArr.length < this.MAX_IMAGE_COUNT) {
            this.imageInfoArr.push({ image: undefined, url: Constants.NOT_SELECTED_NAME });
        }
    }
    aboutToAppear() {
        this.initImageInfoArr();
        this.stack.pushPath({ name: 'home' });
    }
    initialRender() {
        this.observeComponentCreation2((r15, s15) => {
            Scroll.create();
            Scroll.width('100%');
            Scroll.height('100%');
            Scroll.scrollable(ScrollDirection.FREE);
        }, Scroll);
        this.observeComponentCreation2((p15, q15) => {
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
__decorate([
    Local
], ImageGeneratorDialog.prototype, "imageInfoArr", void 0);
