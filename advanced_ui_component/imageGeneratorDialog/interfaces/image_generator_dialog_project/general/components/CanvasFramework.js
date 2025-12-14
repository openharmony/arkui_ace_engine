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

var __decorate = (this && this.__decorate) || function (s2, t2, u2, v2) {
    var w2 = arguments.length, x2 = w2 < 3 ? t2 : v2 === null ? v2 = Object.getOwnPropertyDescriptor(t2, u2) : v2, y2;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        x2 = Reflect.decorate(s2, t2, u2, v2);
    else
        for (var z2 = s2.length - 1; z2 >= 0; z2--)
            if (y2 = s2[z2])
                x2 = (w2 < 3 ? y2(x2) : w2 > 3 ? y2(t2, u2, x2) : y2(t2, u2)) || x2;
    return w2 > 3 && x2 && Object.defineProperty(t2, u2, x2), x2;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { CanvasMode, ImageGenerateState } from "../types/Declaration";
import { DoodleBoardArea } from "./DoodleBoardArea";
import { TextInputArea } from "./TextInputArea";
import { HomeTitle } from "./TitleArea";
import { LandscapeSelectFuncArea } from "./UserInteractiveArea";
import { GeneratingArea } from './CanvasGenerate';
import { calcAABB } from './ImageOperate';
export class styleItem {
    constructor() {
        this.name = 'NA';
    }
}
export class CanvasHome extends ViewV2 {
    constructor(m2, n2, o2, p2 = -1, q2, r2) {
        super(m2, p2, r2);
        this.titleName = '灵感画布';
        this.currentCanvasMode = CanvasMode.GENERAL_MODE;
        this.currentGenerateState = ImageGenerateState.CONFIGURATION;
        this.initParam("imageInfoArr", (n2 && "imageInfoArr" in n2) ? n2.imageInfoArr : undefined);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(l2) {
        this.titleName = '灵感画布';
        this.currentCanvasMode = CanvasMode.GENERAL_MODE;
        this.currentGenerateState = ImageGenerateState.CONFIGURATION;
        this.resetParam("imageInfoArr", (l2 && "imageInfoArr" in l2) ? l2.imageInfoArr : undefined);
    }
    homeTitleBuilder(g2 = null) {
        {
            this.observeComponentCreation2((h2, i2) => {
                if (i2) {
                    let j2 = new HomeTitle(this, {
                        titleName: this.titleName,
                        currentGenerateState: this.currentGenerateState
                    }, undefined, h2, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 39, col: 5 });
                    ViewV2.create(j2);
                    let k2 = () => {
                        return {
                            titleName: this.titleName,
                            currentGenerateState: this.currentGenerateState
                        };
                    };
                    j2.paramsGenerator_ = k2;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(h2, {
                        titleName: this.titleName,
                        currentGenerateState: this.currentGenerateState
                    });
                }
            }, { name: "HomeTitle" });
        }
    }
    initialRender() {
        this.observeComponentCreation2((x1, y1) => {
            NavDestination.create(() => {
                this.observeComponentCreation2((z1, a2) => {
                    If.create();
                    if (this.currentCanvasMode === CanvasMode.GENERAL_MODE) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            {
                                this.observeComponentCreation2((b2, c2) => {
                                    if (c2) {
                                        let d2 = new LandscapeLayout(this, {
                                            currentGenerateState: this.currentGenerateState,
                                            imageInfoArr: this.imageInfoArr,
                                            $currentGenerateState: f2 => { this.currentGenerateState = f2; }
                                        }, undefined, b2, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 48, col: 9 });
                                        ViewV2.create(d2);
                                        let e2 = () => {
                                            return {
                                                currentGenerateState: this.currentGenerateState,
                                                imageInfoArr: this.imageInfoArr
                                            };
                                        };
                                        d2.paramsGenerator_ = e2;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(b2, {
                                            currentGenerateState: this.currentGenerateState,
                                            imageInfoArr: this.imageInfoArr
                                        });
                                    }
                                }, { name: "LandscapeLayout" });
                            }
                        });
                    }
                    else if (this.currentCanvasMode === CanvasMode.DOODLE_MODE) {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(2, () => {
                        });
                    }
                }, If);
                If.pop();
            }, { moduleName: "image_generator_dialog", pagePath: "" });
            NavDestination.hideBackButton(true);
            NavDestination.title({ builder: this.homeTitleBuilder.bind(this) });
        }, NavDestination);
        NavDestination.pop();
    }
    updateStateVars(w1) {
        if (w1 === undefined) {
            return;
        }
        if ("imageInfoArr" in w1) {
            this.updateParam("imageInfoArr", w1.imageInfoArr);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Local
], CanvasHome.prototype, "titleName", void 0);
__decorate([
    Local
], CanvasHome.prototype, "currentCanvasMode", void 0);
__decorate([
    Local
], CanvasHome.prototype, "currentGenerateState", void 0);
__decorate([
    Param
], CanvasHome.prototype, "imageInfoArr", void 0);
class LandscapeLayout extends ViewV2 {
    constructor(p1, q1, r1, s1 = -1, t1, u1) {
        super(p1, s1, u1);
        this.initParam("currentGenerateState", (q1 && "currentGenerateState" in q1) ? q1.currentGenerateState : ImageGenerateState.CONFIGURATION);
        this.$currentGenerateState = "$currentGenerateState" in q1 ? q1.$currentGenerateState : (v1) => {
        };
        this.initParam("imageInfoArr", (q1 && "imageInfoArr" in q1) ? q1.imageInfoArr : undefined);
        this.imageMatrixArr = [[
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ]];
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(n1) {
        this.resetParam("currentGenerateState", (n1 && "currentGenerateState" in n1) ? n1.currentGenerateState : ImageGenerateState.CONFIGURATION);
        this.$currentGenerateState = "$currentGenerateState" in n1 ? n1.$currentGenerateState : (o1) => {
        };
        this.resetParam("imageInfoArr", (n1 && "imageInfoArr" in n1) ? n1.imageInfoArr : undefined);
        this.imageMatrixArr = [[
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ], [
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            ]];
    }
    initImageMatrix() {
        let j1 = [];
        for (let m1 = 0; m1 < this.imageInfoArr.length; m1++) {
            if (this.imageInfoArr[m1].rect) {
                j1.push(this.imageInfoArr[m1]);
            }
        }
        let k1 = calcAABB(j1, this.getUIContext().vp2px(386), this.getUIContext().vp2px(386));
        for (let l1 = 0; l1 < k1.length; l1++) {
            this.imageMatrixArr[l1] = k1[l1];
        }
    }
    aboutToAppear() {
        this.initImageMatrix();
    }
    initialRender() {
        this.observeComponentCreation2((h1, i1) => {
            Column.create();
            Column.height('100%');
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((f1, g1) => {
            Row.create();
            Row.margin({ top: 21, bottom: 28 });
        }, Row);
        this.observeComponentCreation2((d1, e1) => {
            __Common__.create();
            __Common__.margin({ left: 69, right: 54 });
        }, __Common__);
        {
            this.observeComponentCreation2((z, a1) => {
                if (a1) {
                    let b1 = new DoodleBoardArea(this, {
                        imageInfoArr: this.imageInfoArr,
                        imageMatrixArr: this.imageMatrixArr
                    }, undefined, z, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 113, col: 9 });
                    ViewV2.create(b1);
                    let c1 = () => {
                        return {
                            imageInfoArr: this.imageInfoArr,
                            imageMatrixArr: this.imageMatrixArr
                        };
                    };
                    b1.paramsGenerator_ = c1;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(z, {
                        imageInfoArr: this.imageInfoArr,
                        imageMatrixArr: this.imageMatrixArr
                    });
                }
            }, { name: "DoodleBoardArea" });
        }
        __Common__.pop();
        this.observeComponentCreation2((x, y) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u3, v3) => {
                        __Common__.create();
                        __Common__.margin({ right: 16 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((q3, r3) => {
                            if (r3) {
                                let s3 = new LandscapeSelectFuncArea(this, { imageInfoArr: this.imageInfoArr, imageMatrixArr: this.imageMatrixArr }, undefined, q3, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 119, col: 11 });
                                ViewV2.create(s3);
                                let t3 = () => {
                                    return {
                                        imageInfoArr: this.imageInfoArr,
                                        imageMatrixArr: this.imageMatrixArr
                                    };
                                };
                                s3.paramsGenerator_ = t3;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(q3, {
                                    imageInfoArr: this.imageInfoArr, imageMatrixArr: this.imageMatrixArr
                                });
                            }
                        }, { name: "LandscapeSelectFuncArea" });
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
        Row.pop();
        this.observeComponentCreation2((g3, h3) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o3, p3) => {
                        __Common__.create();
                        __Common__.margin({ bottom: 14 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((i3, j3) => {
                            if (j3) {
                                let k3 = new TextInputArea(this, {
                                    changeGenerateState: (n3) => {
                                        this.$currentGenerateState(n3);
                                    }
                                }, undefined, i3, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 127, col: 9 });
                                ViewV2.create(k3);
                                let l3 = () => {
                                    return {
                                        changeGenerateState: (m3) => {
                                            this.$currentGenerateState(m3);
                                        }
                                    };
                                };
                                k3.paramsGenerator_ = l3;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(i3, {});
                            }
                        }, { name: "TextInputArea" });
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
        this.observeComponentCreation2((j, k) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.GENERATING ||
                this.currentGenerateState === ImageGenerateState.BEFORE_GENERATED) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((a3, b3) => {
                            if (b3) {
                                let c3 = new GeneratingArea(this, {
                                    currentGenerateState: this.currentGenerateState,
                                    changeGenerateState: (f3) => {
                                        this.$currentGenerateState(f3);
                                    }
                                }, undefined, a3, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 136, col: 9 });
                                ViewV2.create(c3);
                                let d3 = () => {
                                    return {
                                        currentGenerateState: this.currentGenerateState,
                                        changeGenerateState: (e3) => {
                                            this.$currentGenerateState(e3);
                                        }
                                    };
                                };
                                c3.paramsGenerator_ = d3;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(a3, {
                                    currentGenerateState: this.currentGenerateState
                                });
                            }
                        }, { name: "GeneratingArea" });
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
    }
    updateStateVars(a) {
        if (a === undefined) {
            return;
        }
        if ("currentGenerateState" in a) {
            this.updateParam("currentGenerateState", a.currentGenerateState);
        }
        if ("imageInfoArr" in a) {
            this.updateParam("imageInfoArr", a.imageInfoArr);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], LandscapeLayout.prototype, "currentGenerateState", void 0);
__decorate([
    Event
], LandscapeLayout.prototype, "$currentGenerateState", void 0);
__decorate([
    Param
], LandscapeLayout.prototype, "imageInfoArr", void 0);
__decorate([
    Local
], LandscapeLayout.prototype, "imageMatrixArr", void 0);
