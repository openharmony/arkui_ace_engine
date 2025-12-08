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
import { CanvasHome } from "./canvasPages/CanvasHome";
import { CanvasMode } from "../types/Declaration";
export class ImageGeneratorDialog extends ViewPU {
    constructor(r4, s4, t4, u4 = -1, v4 = undefined, w4) {
        super(r4, t4, u4, w4);
        if (typeof v4 === "function") {
            this.paramsGenerator_ = v4;
        }
        this.options = undefined;
        this.__width_ = new ObservedPropertyObjectPU(650, this, "width_");
        this.__height_ = new ObservedPropertyObjectPU(560, this, "height_");
        this.__currentCanvasMode = new ObservedPropertySimplePU(CanvasMode.COMMON_MODE, this, "currentCanvasMode");
        this.setInitiallyProvidedValue(s4);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q4) {
        if (q4.options !== undefined) {
            this.options = q4.options;
        }
        if (q4.width_ !== undefined) {
            this.width_ = q4.width_;
        }
        if (q4.height_ !== undefined) {
            this.height_ = q4.height_;
        }
        if (q4.currentCanvasMode !== undefined) {
            this.currentCanvasMode = q4.currentCanvasMode;
        }
    }
    updateStateVars(p4) {
    }
    purgeVariableDependenciesOnElmtId(o4) {
        this.__width_.purgeDependencyOnElmtId(o4);
        this.__height_.purgeDependencyOnElmtId(o4);
        this.__currentCanvasMode.purgeDependencyOnElmtId(o4);
    }
    aboutToBeDeleted() {
        this.__width_.aboutToBeDeleted();
        this.__height_.aboutToBeDeleted();
        this.__currentCanvasMode.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get width_() {
        return this.__width_.get();
    }
    set width_(n4) {
        this.__width_.set(n4);
    }
    get height_() {
        return this.__height_.get();
    }
    set height_(m4) {
        this.__height_.set(m4);
    }
    get currentCanvasMode() {
        return this.__currentCanvasMode.get();
    }
    set currentCanvasMode(l4) {
        this.__currentCanvasMode.set(l4);
    }
    initialRender() {
        this.observeComponentCreation2((j4, k4) => {
            Scroll.create();
            Scroll.width('100%');
            Scroll.height('100%');
            Scroll.scrollable(ScrollDirection.FREE);
        }, Scroll);
        this.observeComponentCreation2((h4, i4) => {
            Column.create();
            Column.height(ObservedObject.GetRawObject(this.height_));
            Column.width(ObservedObject.GetRawObject(this.width_));
            Column.borderRadius(32);
            Column.clip(true);
            Column.alignSelf(ItemAlign.Center);
        }, Column);
        this.observeComponentCreation2((b4, c4) => {
            If.create();
            if (this.currentCanvasMode === CanvasMode.COMMON_MODE) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((d4, e4) => {
                            if (e4) {
                                let f4 = new CanvasHome(this, {}, undefined, d4, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/main.ets", line: 16, col: 11 });
                                ViewPU.create(f4);
                                let g4 = () => {
                                    return {};
                                };
                                f4.paramsGenerator_ = g4;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(d4, {});
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
        Column.pop();
        Scroll.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
