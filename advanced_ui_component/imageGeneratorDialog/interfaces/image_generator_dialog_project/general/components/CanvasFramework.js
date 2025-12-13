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
var __decorate = (this && this.__decorate) || function (p2, q2, r2, s2) {
    var t2 = arguments.length, u2 = t2 < 3 ? q2 : s2 === null ? s2 = Object.getOwnPropertyDescriptor(q2, r2) : s2, v2;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        u2 = Reflect.decorate(p2, q2, r2, s2);
    else
        for (var w2 = p2.length - 1; w2 >= 0; w2--)
            if (v2 = p2[w2])
                u2 = (t2 < 3 ? v2(u2) : t2 > 3 ? v2(q2, r2, u2) : v2(q2, r2)) || u2;
    return t2 > 3 && u2 && Object.defineProperty(q2, r2, u2), u2;
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
export class styleItem {
    constructor() {
        this.name = 'NA';
    }
}
export class CanvasHome extends ViewV2 {
    constructor(j2, k2, l2, m2 = -1, n2, o2) {
        super(j2, m2, o2);
        this.titleName = '灵感画布';
        this.currentCanvasMode = CanvasMode.GENERAL_MODE;
        this.currentGenerateState = ImageGenerateState.CONFIGURATION;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(i2) {
        this.titleName = '灵感画布';
        this.currentCanvasMode = CanvasMode.GENERAL_MODE;
        this.currentGenerateState = ImageGenerateState.CONFIGURATION;
    }
    homeTitleBuilder(d2 = null) {
        {
            this.observeComponentCreation2((e2, f2) => {
                if (f2) {
                    let g2 = new HomeTitle(this, {
                        titleName: this.titleName,
                        currentGenerateState: this.currentGenerateState
                    }, undefined, e2, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 37, col: 5 });
                    ViewV2.create(g2);
                    let h2 = () => {
                        return {
                            titleName: this.titleName,
                            currentGenerateState: this.currentGenerateState
                        };
                    };
                    g2.paramsGenerator_ = h2;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(e2, {
                        titleName: this.titleName,
                        currentGenerateState: this.currentGenerateState
                    });
                }
            }, { name: "HomeTitle" });
        }
    }
    initialRender() {
        this.observeComponentCreation2((u1, v1) => {
            NavDestination.create(() => {
                this.observeComponentCreation2((w1, x1) => {
                    If.create();
                    if (this.currentCanvasMode === CanvasMode.GENERAL_MODE) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            {
                                this.observeComponentCreation2((y1, z1) => {
                                    if (z1) {
                                        let a2 = new LandscapeLayout(this, {
                                            currentGenerateState: this.currentGenerateState,
                                            $currentGenerateState: c2 => { this.currentGenerateState = c2; }
                                        }, undefined, y1, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 46, col: 9 });
                                        ViewV2.create(a2);
                                        let b2 = () => {
                                            return {
                                                currentGenerateState: this.currentGenerateState
                                            };
                                        };
                                        a2.paramsGenerator_ = b2;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(y1, {
                                            currentGenerateState: this.currentGenerateState
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
            }, { moduleName: "__harDefaultModuleName__", pagePath: "" });
            NavDestination.hideBackButton(true);
            NavDestination.title({ builder: this.homeTitleBuilder.bind(this) });
        }, NavDestination);
        NavDestination.pop();
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
class LandscapeLayout extends ViewV2 {
    constructor(n1, o1, p1, q1 = -1, r1, s1) {
        super(n1, q1, s1);
        this.initParam("currentGenerateState", (o1 && "currentGenerateState" in o1) ? o1.currentGenerateState : ImageGenerateState.CONFIGURATION);
        this.$currentGenerateState = "$currentGenerateState" in o1 ? o1.$currentGenerateState : (t1) => { };
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(l1) {
        this.resetParam("currentGenerateState", (l1 && "currentGenerateState" in l1) ? l1.currentGenerateState : ImageGenerateState.CONFIGURATION);
        this.$currentGenerateState = "$currentGenerateState" in l1 ? l1.$currentGenerateState : (m1) => { };
    }
    initialRender() {
        this.observeComponentCreation2((j1, k1) => {
            Column.create();
            Column.height('100%');
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((h1, i1) => {
            Row.create();
            Row.margin({ top: 21, bottom: 28 });
        }, Row);
        this.observeComponentCreation2((f1, g1) => {
            __Common__.create();
            __Common__.margin({ left: 69, right: 54 });
        }, __Common__);
        {
            this.observeComponentCreation2((b1, c1) => {
                if (c1) {
                    let d1 = new DoodleBoardArea(this, {}, undefined, b1, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 66, col: 9 });
                    ViewV2.create(d1);
                    let e1 = () => {
                        return {};
                    };
                    d1.paramsGenerator_ = e1;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(b1, {});
                }
            }, { name: "DoodleBoardArea" });
        }
        __Common__.pop();
        this.observeComponentCreation2((t, u) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z, a1) => {
                        __Common__.create();
                        __Common__.margin({ right: 16 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((v, w) => {
                            if (w) {
                                let x = new LandscapeSelectFuncArea(this, {}, undefined, v, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 69, col: 11 });
                                ViewV2.create(x);
                                let y = () => {
                                    return {};
                                };
                                x.paramsGenerator_ = y;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(v, {});
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
        this.observeComponentCreation2((j, k) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r, s) => {
                        __Common__.create();
                        __Common__.margin({ bottom: 14 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((l, m) => {
                            if (m) {
                                let n = new TextInputArea(this, {
                                    changeGenerateState: (q) => {
                                        this.$currentGenerateState(q);
                                    }
                                }, undefined, l, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 77, col: 9 });
                                ViewV2.create(n);
                                let o = () => {
                                    return {
                                        changeGenerateState: (p) => {
                                            this.$currentGenerateState(p);
                                        }
                                    };
                                };
                                n.paramsGenerator_ = o;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l, {});
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
        this.observeComponentCreation2((b, c) => {
            If.create();
            if (this.currentGenerateState === ImageGenerateState.GENERATING ||
                this.currentGenerateState === ImageGenerateState.BEFORE_GENERATED) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((d, e) => {
                            if (e) {
                                let f = new GeneratingArea(this, {
                                    currentGenerateState: this.currentGenerateState,
                                    changeGenerateState: (i) => {
                                        this.$currentGenerateState(i);
                                    }
                                }, undefined, d, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 86, col: 9 });
                                ViewV2.create(f);
                                let g = () => {
                                    return {
                                        currentGenerateState: this.currentGenerateState,
                                        changeGenerateState: (h) => {
                                            this.$currentGenerateState(h);
                                        }
                                    };
                                };
                                f.paramsGenerator_ = g;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(d, {
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
