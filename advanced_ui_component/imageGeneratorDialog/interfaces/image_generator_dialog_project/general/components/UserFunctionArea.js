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

var __decorate = (this && this.__decorate) || function (f14, g14, h14, i14) {
    var j14 = arguments.length, k14 = j14 < 3 ? g14 : i14 === null ? i14 = Object.getOwnPropertyDescriptor(g14, h14) : i14, l14;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        k14 = Reflect.decorate(f14, g14, h14, i14);
    else
        for (var m14 = f14.length - 1; m14 >= 0; m14--)
            if (l14 = f14[m14])
                k14 = (j14 < 3 ? l14(k14) : j14 > 3 ? l14(g14, h14, k14) : l14(g14, h14)) || k14;
    return j14 > 3 && k14 && Object.defineProperty(g14, h14, k14), k14;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { AIGenerateOptions } from "../utils/AIGenerateOptions";
export function UserInteractiveTabBarBuilder(x13, y13 = null) {
    const z13 = x13;
    {
        (y13 ? y13 : this).observeComponentCreation2((a14, b14, c14 = z13) => {
            if (b14) {
                let d14 = new UserInteractiveAreaTabBar(y13 ? y13 : this, {
                    name: c14
                }, undefined, a14, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 20, col: 3 });
                ViewV2.create(d14);
                let e14 = () => {
                    return {
                        name: c14
                    };
                };
                d14.paramsGenerator_ = e14;
            }
            else {
                (y13 ? y13 : this).updateStateVarsOfChildByElmtId(a14, {
                    name: c14
                });
            }
        }, { name: "UserInteractiveAreaTabBar" });
    }
}
class StyleSelectTabBarParams {
    constructor() {
        this.name = '';
        this.icon = { bundleName: "", moduleName: "", id: 0 };
        this.bgColor = 'rgba(0,0,0,0.05)';
    }
}
export function StyleSelectTabBarBuilder(p13, q13 = null) {
    const r13 = p13;
    {
        (q13 ? q13 : this).observeComponentCreation2((s13, t13, u13 = r13) => {
            if (t13) {
                let v13 = new UserFunctionAreaTabBar(q13 ? q13 : this, {
                    name: u13.name,
                    icon: u13.icon,
                    tabBarBgColor: u13.bgColor
                }, undefined, s13, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 32, col: 3 });
                ViewV2.create(v13);
                let w13 = () => {
                    return {
                        name: u13.name,
                        icon: u13.icon,
                        tabBarBgColor: u13.bgColor
                    };
                };
                v13.paramsGenerator_ = w13;
            }
            else {
                (q13 ? q13 : this).updateStateVarsOfChildByElmtId(s13, {
                    name: u13.name,
                    icon: u13.icon,
                    tabBarBgColor: u13.bgColor
                });
            }
        }, { name: "UserFunctionAreaTabBar" });
    }
}
export function StyleSelectBuilder(h13, i13 = null) {
    const j13 = h13;
    {
        (i13 ? i13 : this).observeComponentCreation2((k13, l13, m13 = j13) => {
            if (l13) {
                let n13 = new StyleSelect(i13 ? i13 : this, { stylesArray: m13 }, undefined, k13, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 40, col: 3 });
                ViewV2.create(n13);
                let o13 = () => {
                    return {
                        stylesArray: m13
                    };
                };
                n13.paramsGenerator_ = o13;
            }
            else {
                (i13 ? i13 : this).updateStateVarsOfChildByElmtId(k13, {
                    stylesArray: m13
                });
            }
        }, { name: "StyleSelect" });
    }
}
export class FunctionAreaPlaceholder extends ViewV2 {
    constructor(b13, c13, d13, e13 = -1, f13, g13) {
        super(b13, e13, g13);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(a13) {
    }
    initialRender() {
        this.observeComponentCreation2((y12, z12) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.padding({
                right: 14
            });
        }, Column);
        this.observeComponentCreation2((w12, x12) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.border({ width: 0.5 });
        }, Column);
        Column.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class UserFunctionAreaTabBar extends ViewV2 {
    constructor(q12, r12, s12, t12 = -1, u12, v12) {
        super(q12, t12, v12);
        this.initParam("name", (r12 && "name" in r12) ? r12.name : '__NA__');
        this.initParam("icon", (r12 && "icon" in r12) ? r12.icon : undefined);
        this.initParam("tabBarBgColor", (r12 && "tabBarBgColor" in r12) ? r12.tabBarBgColor : 'rgba(0,0,0,0.05)');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(p12) {
        this.resetParam("name", (p12 && "name" in p12) ? p12.name : '__NA__');
        this.resetParam("icon", (p12 && "icon" in p12) ? p12.icon : undefined);
        this.resetParam("tabBarBgColor", (p12 && "tabBarBgColor" in p12) ? p12.tabBarBgColor : 'rgba(0,0,0,0.05)');
    }
    initialRender() {
        this.observeComponentCreation2((n12, o12) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((l12, m12) => {
            Column.create();
            Column.padding(12);
            Column.width(48);
            Column.height(48);
            Column.margin({ bottom: 4 });
            Column.borderRadius(100);
            Column.backgroundColor(this.tabBarBgColor);
        }, Column);
        this.observeComponentCreation2((j12, k12) => {
            Image.create(this.icon);
            Image.width(24);
            Image.height(24);
        }, Image);
        Column.pop();
        this.observeComponentCreation2((h12, i12) => {
            Column.create();
            Column.height(10);
        }, Column);
        this.observeComponentCreation2((f12, g12) => {
            Text.create(this.name);
            Text.fontFamily("HarmonyHeiTi");
            Text.fontColor("#000000");
            Text.fontSize(10);
            Text.fontWeight(500);
        }, Text);
        Text.pop();
        Column.pop();
        Column.pop();
    }
    updateStateVars(e12) {
        if (e12 === undefined) {
            return;
        }
        if ("name" in e12) {
            this.updateParam("name", e12.name);
        }
        if ("icon" in e12) {
            this.updateParam("icon", e12.icon);
        }
        if ("tabBarBgColor" in e12) {
            this.updateParam("tabBarBgColor", e12.tabBarBgColor);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], UserFunctionAreaTabBar.prototype, "name", void 0);
__decorate([
    Param
], UserFunctionAreaTabBar.prototype, "icon", void 0);
__decorate([
    Param
], UserFunctionAreaTabBar.prototype, "tabBarBgColor", void 0);
export class StyleSelect extends ViewV2 {
    constructor(y11, z11, a12, b12 = -1, c12, d12) {
        super(y11, b12, d12);
        this.curSelectedStyle = AIGenerateOptions.getInstance().style;
        this.initParam("stylesArray", (z11 && "stylesArray" in z11) ? z11.stylesArray : [
            {
                name: '插画',
                resourceAddr: undefined
            },
            {
                name: '写实',
                resourceAddr: undefined
            },
            {
                name: '油画',
                resourceAddr: undefined
            },
            {
                name: '水彩',
                resourceAddr: undefined
            },
            {
                name: '线描',
                resourceAddr: undefined
            },
            {
                name: '动漫',
                resourceAddr: undefined
            },
        ]);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(x11) {
        this.curSelectedStyle = AIGenerateOptions.getInstance().style;
        this.resetParam("stylesArray", (x11 && "stylesArray" in x11) ? x11.stylesArray : [
            {
                name: '插画',
                resourceAddr: undefined
            },
            {
                name: '写实',
                resourceAddr: undefined
            },
            {
                name: '油画',
                resourceAddr: undefined
            },
            {
                name: '水彩',
                resourceAddr: undefined
            },
            {
                name: '线描',
                resourceAddr: undefined
            },
            {
                name: '动漫',
                resourceAddr: undefined
            },
        ]);
    }
    updateSelectIndex(w11) {
        if (this.curSelectedStyle === w11) {
            this.curSelectedStyle = undefined;
        }
        else {
            this.curSelectedStyle = w11;
        }
        AIGenerateOptions.getInstance().style = this.curSelectedStyle;
    }
    initialRender() {
        this.observeComponentCreation2((u11, v11) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((s11, t11) => {
            Scroll.create();
            Scroll.scrollBar(BarState.Off);
            Scroll.scrollable(ScrollDirection.Vertical);
            Scroll.height(260);
            Scroll.width(56);
        }, Scroll);
        this.observeComponentCreation2((q11, r11) => {
            Column.create({ space: 12 });
        }, Column);
        this.observeComponentCreation2((t10, u10) => {
            Repeat(this.stylesArray, this).each((v10) => {
                this.observeComponentCreation2((m11, n11) => {
                    Column.create();
                    Column.height(56);
                    Column.width(56);
                    Column.onClick(() => {
                        let o11 = '';
                        if (typeof (v10.item.name) === 'string') {
                            o11 = v10.item.name;
                        }
                        else {
                            let p11 = this.getUIContext().getHostContext();
                            if (p11) {
                                o11 = p11.resourceManager.getStringSync(v10.item.name.id);
                            }
                        }
                        this.updateSelectIndex(o11);
                    });
                }, Column);
                this.observeComponentCreation2((k11, l11) => {
                    Stack.create();
                    Stack.alignContent(Alignment.TopEnd);
                }, Stack);
                this.observeComponentCreation2((i11, j11) => {
                    Image.create(v10.item.resourceAddr);
                    Image.height(56);
                    Image.width(56);
                    Image.borderRadius(12);
                    Image.borderColor("#000000");
                    Image.linearGradient({
                        angle: 0,
                        colors: [["#000000", 0], ["#000000", 1]]
                    });
                }, Image);
                this.observeComponentCreation2((g11, h11) => {
                    Column.create();
                }, Column);
                this.observeComponentCreation2((c11, d11) => {
                    Checkbox.create();
                    Checkbox.select(this.curSelectedStyle === v10.item.name);
                    Checkbox.shape(CheckBoxShape.CIRCLE);
                    Checkbox.onClick(() => {
                        let e11 = '';
                        if (typeof (v10.item.name) === 'string') {
                            e11 = v10.item.name;
                        }
                        else {
                            let f11 = this.getUIContext().getHostContext();
                            if (f11) {
                                e11 = f11.resourceManager.getStringSync(v10.item.name.id);
                            }
                        }
                        this.updateSelectIndex(e11);
                    });
                    Checkbox.height(16);
                    Checkbox.width(16);
                    Checkbox.unselectedColor(Color.Transparent);
                }, Checkbox);
                Checkbox.pop();
                Column.pop();
                this.observeComponentCreation2((a11, b11) => {
                    Column.create();
                    Column.padding({ top: 36, bottom: 4 });
                    Column.width('100%');
                    Column.height('100%');
                }, Column);
                this.observeComponentCreation2((y10, z10) => {
                    Column.create();
                    Column.width(48);
                    Column.height(16);
                }, Column);
                this.observeComponentCreation2((w10, x10) => {
                    Text.create(v10.item.name);
                    Text.fontFamily("HarmonyHeiTi");
                    Text.fontColor("#FFFFFF");
                    Text.fontSize(12);
                    Text.fontWeight(500);
                    Text.lineHeight(14);
                    Text.textAlign(TextAlign.Center);
                }, Text);
                Text.pop();
                Column.pop();
                Column.pop();
                Stack.pop();
                Column.pop();
            }).render(u10);
        }, Repeat);
        Column.pop();
        Scroll.pop();
        Column.pop();
    }
    updateStateVars(s10) {
        if (s10 === undefined) {
            return;
        }
        if ("stylesArray" in s10) {
            this.updateParam("stylesArray", s10.stylesArray);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Local
], StyleSelect.prototype, "curSelectedStyle", void 0);
__decorate([
    Param
], StyleSelect.prototype, "stylesArray", void 0);
class UserInteractiveAreaTabBar extends ViewV2 {
    constructor(m10, n10, o10, p10 = -1, q10, r10) {
        super(m10, p10, r10);
        this.initParam("name", (n10 && "name" in n10) ? n10.name : '__NA__');
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(l10) {
        this.resetParam("name", (l10 && "name" in l10) ? l10.name : '__NA__');
    }
    initialRender() {
        this.observeComponentCreation2((j10, k10) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((h10, i10) => {
            Column.create();
            Column.padding(12);
            Column.width(48);
            Column.height(48);
            Column.margin({ bottom: 4 });
            Column.borderRadius(24);
            Column.backgroundColor('rgba(0,0,0,0.05)');
        }, Column);
        this.observeComponentCreation2((f10, g10) => {
            Image.create('');
            Image.width(24);
            Image.height(24);
        }, Image);
        Column.pop();
        this.observeComponentCreation2((d10, e10) => {
            Column.create();
            Column.height(10);
        }, Column);
        this.observeComponentCreation2((b10, c10) => {
            Text.create(this.name);
            Text.fontFamily("HarmonyHeiTi");
            Text.fontColor("#000000");
            Text.fontSize(10);
            Text.fontWeight(500);
        }, Text);
        Text.pop();
        Column.pop();
        Column.pop();
    }
    updateStateVars(a10) {
        if (a10 === undefined) {
            return;
        }
        if ("name" in a10) {
            this.updateParam("name", a10.name);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], UserInteractiveAreaTabBar.prototype, "name", void 0);
