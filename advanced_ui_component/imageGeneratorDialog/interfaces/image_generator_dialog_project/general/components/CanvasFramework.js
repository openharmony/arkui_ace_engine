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

var __decorate = (this && this.__decorate) || function (x1, y1, z1, a2) {
    var b2 = arguments.length, c2 = b2 < 3 ? y1 : a2 === null ? a2 = Object.getOwnPropertyDescriptor(y1, z1) : a2, d2;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        c2 = Reflect.decorate(x1, y1, z1, a2);
    else
        for (var e2 = x1.length - 1; e2 >= 0; e2--)
            if (d2 = x1[e2])
                c2 = (b2 < 3 ? d2(c2) : b2 > 3 ? d2(y1, z1, c2) : d2(y1, z1)) || c2;
    return b2 > 3 && c2 && Object.defineProperty(y1, z1, c2), c2;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { CanvasMode } from "../types/Declaration";
import { DoodleBoardArea } from "./DoodleBoardArea";
import { TextInputArea } from "./TextInputArea";
import { HomeTitle } from "./TitleArea";
import { LandscapeSelectFuncArea } from "./UserInteractiveArea";
export class CanvasHome extends ViewV2 {
    constructor(r1, s1, t1, u1 = -1, v1, w1) {
        super(r1, u1, w1);
        this.titleName = '灵感画布';
        this.currentCanvasMode = CanvasMode.GENERAL_MODE;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(q1) {
        this.titleName = '灵感画布';
        this.currentCanvasMode = CanvasMode.GENERAL_MODE;
    }
    homeTitleBuilder(l1 = null) {
        {
            this.observeComponentCreation2((m1, n1) => {
                if (n1) {
                    let o1 = new HomeTitle(this, { titleName: this.titleName }, undefined, m1, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 29, col: 5 });
                    ViewV2.create(o1);
                    let p1 = () => {
                        return {
                            titleName: this.titleName
                        };
                    };
                    o1.paramsGenerator_ = p1;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(m1, {
                        titleName: this.titleName
                    });
                }
            }, { name: "HomeTitle" });
        }
    }
    initialRender() {
        this.observeComponentCreation2((d1, e1) => {
            NavDestination.create(() => {
                this.observeComponentCreation2((f1, g1) => {
                    If.create();
                    if (this.currentCanvasMode === CanvasMode.GENERAL_MODE) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            {
                                this.observeComponentCreation2((h1, i1) => {
                                    if (i1) {
                                        let j1 = new LandscapeLayout(this, {}, undefined, h1, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 35, col: 9 });
                                        ViewV2.create(j1);
                                        let k1 = () => {
                                            return {};
                                        };
                                        j1.paramsGenerator_ = k1;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(h1, {});
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
class LandscapeLayout extends ViewV2 {
    constructor(x, y, z, a1 = -1, b1, c1) {
        super(x, a1, c1);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(w) {
    }
    initialRender() {
        this.observeComponentCreation2((u, v) => {
            Column.create();
            Column.height('100%');
            Column.width('100%');
        }, Column);
        this.observeComponentCreation2((s, t) => {
            Row.create();
            Row.margin({ top: 21, bottom: 28 });
        }, Row);
        this.observeComponentCreation2((q, r) => {
            __Common__.create();
            __Common__.margin({ left: 69, right: 54 });
        }, __Common__);
        {
            this.observeComponentCreation2((m, n) => {
                if (n) {
                    let o = new DoodleBoardArea(this, {}, undefined, m, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 51, col: 9 });
                    ViewV2.create(o);
                    let p = () => {
                        return {};
                    };
                    o.paramsGenerator_ = p;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(m, {});
                }
            }, { name: "DoodleBoardArea" });
        }
        __Common__.pop();
        this.observeComponentCreation2((k, l) => {
            __Common__.create();
            __Common__.margin({ right: 16 });
        }, __Common__);
        {
            this.observeComponentCreation2((g, h) => {
                if (h) {
                    let i = new LandscapeSelectFuncArea(this, {}, undefined, g, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 53, col: 9 });
                    ViewV2.create(i);
                    let j = () => {
                        return {};
                    };
                    i.paramsGenerator_ = j;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(g, {});
                }
            }, { name: "LandscapeSelectFuncArea" });
        }
        __Common__.pop();
        Row.pop();
        this.observeComponentCreation2((e, f) => {
            __Common__.create();
            __Common__.margin({ bottom: 14 });
        }, __Common__);
        {
            this.observeComponentCreation2((a, b) => {
                if (b) {
                    let c = new TextInputArea(this, {}, undefined, a, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/CanvasFramework.ets", line: 58, col: 7 });
                    ViewV2.create(c);
                    let d = () => {
                        return {};
                    };
                    c.paramsGenerator_ = d;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(a, {});
                }
            }, { name: "TextInputArea" });
        }
        __Common__.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
