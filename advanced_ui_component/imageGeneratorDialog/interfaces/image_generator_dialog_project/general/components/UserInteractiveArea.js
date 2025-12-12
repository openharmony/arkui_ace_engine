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
    constructor(q8, r8, s8, t8 = -1, u8, v8) {
        super(q8, t8, v8);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(p8) {
    }
    initialRender() {
        this.observeComponentCreation2((n8, o8) => {
            Tabs.create();
            Tabs.barHeight(284);
            Tabs.scrollable(false);
            Tabs.vertical(true);
            Tabs.barPosition(BarPosition.End);
            Tabs.width(118);
            Tabs.height(386);
        }, Tabs);
        this.observeComponentCreation2((h8, i8) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((j8, k8) => {
                        if (k8) {
                            let l8 = new FunctionAreaPlaceholder(this, {}, undefined, j8, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 8, col: 9 });
                            ViewV2.create(l8);
                            let m8 = () => {
                                return {};
                            };
                            l8.paramsGenerator_ = m8;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(j8, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '图像');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((b8, c8) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((d8, e8) => {
                        if (e8) {
                            let f8 = new FunctionAreaPlaceholder(this, {}, undefined, d8, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 13, col: 9 });
                            ViewV2.create(f8);
                            let g8 = () => {
                                return {};
                            };
                            f8.paramsGenerator_ = g8;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(d8, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '风格');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((v7, w7) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((x7, y7) => {
                        if (y7) {
                            let z7 = new FunctionAreaPlaceholder(this, {}, undefined, x7, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 18, col: 9 });
                            ViewV2.create(z7);
                            let a8 = () => {
                                return {};
                            };
                            z7.paramsGenerator_ = a8;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(x7, {});
                        }
                    }, { name: "FunctionAreaPlaceholder" });
                }
            });
            TabContent.tabBar({ builder: () => {
                    UserInteractiveTabBarBuilder.call(this, '比例');
                } });
        }, TabContent);
        TabContent.pop();
        this.observeComponentCreation2((p7, q7) => {
            TabContent.create(() => {
                {
                    this.observeComponentCreation2((r7, s7) => {
                        if (s7) {
                            let t7 = new FunctionAreaPlaceholder(this, {}, undefined, r7, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserInteractiveArea.ets", line: 23, col: 9 });
                            ViewV2.create(t7);
                            let u7 = () => {
                                return {};
                            };
                            t7.paramsGenerator_ = u7;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(r7, {});
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
