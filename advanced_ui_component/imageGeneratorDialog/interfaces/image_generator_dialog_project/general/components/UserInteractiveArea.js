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
import { FunctionAreaPlaceholder, UserInteractiveTabBarBuilder } from "./UserFunctionArea";
export class LandscapeSelectFuncArea extends ViewV2 {
    constructor(w12, x12, y12, z12 = -1, a13, b13) {
        super(w12, z12, b13);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(v12) {
    }
    initialRender() {
        this.observeComponentCreation2((t12, u12) => {
            Tabs.create();
            Tabs.barHeight(284);
            Tabs.scrollable(false);
            Tabs.vertical(true);
            Tabs.barPosition(BarPosition.End);
            Tabs.width(118);
            Tabs.height(386);
        }, Tabs);
        this.observeComponentCreation2((n12, o12) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((p12, q12) => {
                        if (q12) {
                            let r12 = new FunctionAreaPlaceholder(this, {}, undefined, p12, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 23, col: 9 });
                            ViewV2.create(r12);
                            let s12 = () => {
                                return {};
                            };
                            r12.paramsGenerator_ = s12;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(p12, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '图像');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((h12, i12) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((j12, k12) => {
                        if (k12) {
                            let l12 = new FunctionAreaPlaceholder(this, {}, undefined, j12, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 28, col: 9 });
                            ViewV2.create(l12);
                            let m12 = () => {
                                return {};
                            };
                            l12.paramsGenerator_ = m12;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(j12, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '风格');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((b12, c12) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((d12, e12) => {
                        if (e12) {
                            let f12 = new FunctionAreaPlaceholder(this, {}, undefined, d12, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 33, col: 9 });
                            ViewV2.create(f12);
                            let g12 = () => {
                                return {};
                            };
                            f12.paramsGenerator_ = g12;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(d12, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '比例');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((v11, w11) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((x11, y11) => {
                        if (y11) {
                            let z11 = new FunctionAreaPlaceholder(this, {}, undefined, x11, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 38, col: 9 });
                            ViewV2.create(z11);
                            let a12 = () => {
                                return {};
                            };
                            z11.paramsGenerator_ = a12;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(x11, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '清晰度');
                } });
        }, TabContent);
        TabContent.pop();
        Tabs.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
