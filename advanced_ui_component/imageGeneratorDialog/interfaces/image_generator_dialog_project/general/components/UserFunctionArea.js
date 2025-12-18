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

var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function")
        r = Reflect.decorate(decorators, target, key, desc);
    else
        for (var i = decorators.length - 1; i >= 0; i--)
            if (d = decorators[i])
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
import { CanvasLayoutDirection } from "../types/Declaration";
import { AIGenerateOptions } from "../utils/AIGenerateOptions";
export function UserInteractiveTabBarBuilder(index, name, icon, parent = null) {
    {
        (parent ? parent : this).observeComponentCreation2((elmtId, isInitialRender) => {
            if (isInitialRender) {
                let componentCall = new UserInteractiveAreaTabBar(parent ? parent : this, {
                    index: index,
                    name: name,
                    icon: icon
                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 21, col: 3 });
                ViewV2.create(componentCall);
                let paramsLambda = () => {
                    return {
                        index: index,
                        name: name,
                        icon: icon
                    };
                };
                componentCall.paramsGenerator_ = paramsLambda;
            }
            else {
                (parent ? parent : this).updateStateVarsOfChildByElmtId(elmtId, {
                    index: index,
                    name: name,
                    icon: icon
                });
            }
        }, { name: "UserInteractiveAreaTabBar" });
    }
}
export function StyleSelectBuilder(styleItems, parent = null) {
    const __styleItems__ = styleItems;
    {
        (parent ? parent : this).observeComponentCreation2((elmtId, isInitialRender, styleItems = __styleItems__) => {
            if (isInitialRender) {
                let componentCall = new StyleSelect(parent ? parent : this, { stylesArray: styleItems }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 29, col: 3 });
                ViewV2.create(componentCall);
                let paramsLambda = () => {
                    return {
                        stylesArray: styleItems
                    };
                };
                componentCall.paramsGenerator_ = paramsLambda;
            }
            else {
                (parent ? parent : this).updateStateVarsOfChildByElmtId(elmtId, {
                    stylesArray: styleItems
                });
            }
        }, { name: "StyleSelect" });
    }
}
export class FunctionAreaPlaceholder extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width('100%');
            Column.height('100%');
            Column.padding({
                right: 14
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
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
export class StyleSelect extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.curSelectedStyle = AIGenerateOptions.getInstance().style;
        this.initParam("stylesArray", (params && "stylesArray" in params) ? params.stylesArray : [
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
    resetStateVarsOnReuse(params) {
        this.curSelectedStyle = AIGenerateOptions.getInstance().style;
        this.resetParam("stylesArray", (params && "stylesArray" in params) ? params.stylesArray : [
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
    updateSelectIndex(newSelectedStyle) {
        if (this.curSelectedStyle === newSelectedStyle) {
            this.curSelectedStyle = undefined;
        }
        else {
            this.curSelectedStyle = newSelectedStyle;
        }
        AIGenerateOptions.getInstance().style = this.curSelectedStyle;
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create();
            Scroll.scrollBar(BarState.Off);
            Scroll.scrollable(ScrollDirection.Vertical);
            Scroll.height(396);
            Scroll.width(56);
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create({ space: 12 });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Repeat(this.stylesArray, this).each((item) => {
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Column.create();
                    Column.height(56);
                    Column.width(56);
                    Column.onClick(() => {
                        let nameStr = '';
                        if (typeof (item.item.name) === 'string') {
                            nameStr = item.item.name;
                        }
                        else {
                            let hostContext = this.getUIContext().getHostContext();
                            if (hostContext) {
                                nameStr = hostContext.resourceManager.getStringSync(item.item.name.id);
                            }
                        }
                        this.updateSelectIndex(nameStr);
                    });
                }, Column);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Stack.create();
                    Stack.alignContent(Alignment.TopEnd);
                }, Stack);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Image.create(item.item.resourceAddr);
                    Image.height(56);
                    Image.width(56);
                    Image.borderRadius(12);
                    Image.borderColor("#000000");
                    Image.linearGradient({
                        angle: 0,
                        colors: [["#000000", 0], ["#000000", 1]]
                    });
                }, Image);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Column.create();
                }, Column);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Checkbox.create();
                    Checkbox.select(this.curSelectedStyle === item.item.name);
                    Checkbox.opacity(this.curSelectedStyle === item.item.name ? 1.0 : 0.0);
                    Checkbox.shape(CheckBoxShape.ROUNDED_SQUARE);
                    Checkbox.onClick(() => {
                        let nameStr = '';
                        if (typeof (item.item.name) === 'string') {
                            nameStr = item.item.name;
                        }
                        else {
                            let hostContext = this.getUIContext().getHostContext();
                            if (hostContext) {
                                nameStr = hostContext.resourceManager.getStringSync(item.item.name.id);
                            }
                        }
                        this.updateSelectIndex(nameStr);
                    });
                    Checkbox.height(16);
                    Checkbox.width(16);
                    Checkbox.unselectedColor(Color.Transparent);
                }, Checkbox);
                Checkbox.pop();
                Column.pop();
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Column.create();
                    Column.padding({ top: 36, bottom: 4 });
                    Column.width('100%');
                    Column.height('100%');
                }, Column);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Column.create();
                    Column.width(48);
                    Column.height(16);
                }, Column);
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    Text.create(item.item.name);
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
            }).render(isInitialRender);
        }, Repeat);
        Column.pop();
        Scroll.pop();
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("stylesArray" in params) {
            this.updateParam("stylesArray", params.stylesArray);
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
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("index", (params && "index" in params) ? params.index : 0);
        this.initParam("name", (params && "name" in params) ? params.name : '__NA__');
        this.initParam("icon", (params && "icon" in params) ? params.icon : undefined);
        this.selectedIndex = 0;
        this.curLayoutDirection = CanvasLayoutDirection.DEFAULT;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("index", (params && "index" in params) ? params.index : 0);
        this.resetParam("name", (params && "name" in params) ? params.name : '__NA__');
        this.resetParam("icon", (params && "icon" in params) ? params.icon : undefined);
        this.resetConsumer("selectedIndex", 0);
        this.resetConsumer("curLayoutDirection", CanvasLayoutDirection.DEFAULT);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.curLayoutDirection === CanvasLayoutDirection.HORIZONTAL) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.margin({ bottom: 4 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new UserInteractiveAreaTabBarIcon(this, {
                                    iconSize: 48,
                                    iconPadding: 12,
                                    totalBorderRadius: 24,
                                    index: this.index,
                                    icon: this.icon
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 185, col: 11 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        iconSize: 48,
                                        iconPadding: 12,
                                        totalBorderRadius: 24,
                                        index: this.index,
                                        icon: this.icon
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    iconSize: 48,
                                    iconPadding: 12,
                                    totalBorderRadius: 24,
                                    index: this.index,
                                    icon: this.icon
                                });
                            }
                        }, { name: "UserInteractiveAreaTabBarIcon" });
                    }
                    __Common__.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.height(10);
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new UserInteractiveAreaTabBarText(this, {
                                    name: this.name,
                                    fontSize: 10,
                                    fontWeight: 500,
                                    index: this.index
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 193, col: 11 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        name: this.name,
                                        fontSize: 10,
                                        fontWeight: 500,
                                        index: this.index
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    name: this.name,
                                    fontSize: 10,
                                    fontWeight: 500,
                                    index: this.index
                                });
                            }
                        }, { name: "UserInteractiveAreaTabBarText" });
                    }
                    __Common__.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.padding({ left: 10, right: 10 });
                        Row.width(64);
                        Row.height(28);
                        Row.borderRadius(8);
                        Row.backgroundColor(this.index === this.selectedIndex ? 'rgba(255, 255, 255, 0.9)' : 'rgba(0, 0, 0, 0.05)');
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.margin({ right: 4 });
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new UserInteractiveAreaTabBarIcon(this, {
                                    iconSize: 16,
                                    iconPadding: 1.33,
                                    totalBorderRadius: 0,
                                    index: this.index,
                                    icon: this.icon
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 203, col: 11 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        iconSize: 16,
                                        iconPadding: 1.33,
                                        totalBorderRadius: 0,
                                        index: this.index,
                                        icon: this.icon
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    iconSize: 16,
                                    iconPadding: 1.33,
                                    totalBorderRadius: 0,
                                    index: this.index,
                                    icon: this.icon
                                });
                            }
                        }, { name: "UserInteractiveAreaTabBarIcon" });
                    }
                    __Common__.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        __Common__.create();
                        __Common__.height(10);
                    }, __Common__);
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new UserInteractiveAreaTabBarText(this, {
                                    name: this.name,
                                    fontSize: 12,
                                    fontWeight: 400,
                                    index: this.index
                                }, undefined, elmtId, () => { }, { page: "image_generator_dialog/src/main/ets/general/components/UserFunctionArea.ets", line: 211, col: 11 });
                                ViewV2.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        name: this.name,
                                        fontSize: 12,
                                        fontWeight: 400,
                                        index: this.index
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {
                                    name: this.name,
                                    fontSize: 12,
                                    fontWeight: 400,
                                    index: this.index
                                });
                            }
                        }, { name: "UserInteractiveAreaTabBarText" });
                    }
                    __Common__.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("index" in params) {
            this.updateParam("index", params.index);
        }
        if ("name" in params) {
            this.updateParam("name", params.name);
        }
        if ("icon" in params) {
            this.updateParam("icon", params.icon);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], UserInteractiveAreaTabBar.prototype, "index", void 0);
__decorate([
    Param
], UserInteractiveAreaTabBar.prototype, "name", void 0);
__decorate([
    Param
], UserInteractiveAreaTabBar.prototype, "icon", void 0);
__decorate([
    Consumer('functionAreaSelectedIndex')
], UserInteractiveAreaTabBar.prototype, "selectedIndex", void 0);
__decorate([
    Consumer('globalLayoutDirection')
], UserInteractiveAreaTabBar.prototype, "curLayoutDirection", void 0);
class UserInteractiveAreaTabBarIcon extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("index", (params && "index" in params) ? params.index : 0);
        this.initParam("iconSize", (params && "iconSize" in params) ? params.iconSize : 0);
        this.initParam("icon", (params && "icon" in params) ? params.icon : undefined);
        this.initParam("iconPadding", (params && "iconPadding" in params) ? params.iconPadding : 0);
        this.initParam("totalBorderRadius", (params && "totalBorderRadius" in params) ? params.totalBorderRadius : 0);
        this.selectedIndex = 0;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("index", (params && "index" in params) ? params.index : 0);
        this.resetParam("iconSize", (params && "iconSize" in params) ? params.iconSize : 0);
        this.resetParam("icon", (params && "icon" in params) ? params.icon : undefined);
        this.resetParam("iconPadding", (params && "iconPadding" in params) ? params.iconPadding : 0);
        this.resetParam("totalBorderRadius", (params && "totalBorderRadius" in params) ? params.totalBorderRadius : 0);
        this.resetConsumer("selectedIndex", 0);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.padding(this.iconPadding);
            Column.width(this.iconSize);
            Column.height(this.iconSize);
            Column.borderRadius(this.totalBorderRadius);
            Column.backgroundColor(this.index === this.selectedIndex ? 'rgba(255, 255, 255, 0.9)' : 'rgba(0, 0, 0, 0.05)');
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.icon);
            Image.width('100%');
            Image.height('100%');
            Image.opacity(this.index === this.selectedIndex ? 0.9 : 0.6);
        }, Image);
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("index" in params) {
            this.updateParam("index", params.index);
        }
        if ("iconSize" in params) {
            this.updateParam("iconSize", params.iconSize);
        }
        if ("icon" in params) {
            this.updateParam("icon", params.icon);
        }
        if ("iconPadding" in params) {
            this.updateParam("iconPadding", params.iconPadding);
        }
        if ("totalBorderRadius" in params) {
            this.updateParam("totalBorderRadius", params.totalBorderRadius);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], UserInteractiveAreaTabBarIcon.prototype, "index", void 0);
__decorate([
    Param
], UserInteractiveAreaTabBarIcon.prototype, "iconSize", void 0);
__decorate([
    Param
], UserInteractiveAreaTabBarIcon.prototype, "icon", void 0);
__decorate([
    Param
], UserInteractiveAreaTabBarIcon.prototype, "iconPadding", void 0);
__decorate([
    Param
], UserInteractiveAreaTabBarIcon.prototype, "totalBorderRadius", void 0);
__decorate([
    Consumer('functionAreaSelectedIndex')
], UserInteractiveAreaTabBarIcon.prototype, "selectedIndex", void 0);
class UserInteractiveAreaTabBarText extends ViewV2 {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda, extraInfo) {
        super(parent, elmtId, extraInfo);
        this.initParam("index", (params && "index" in params) ? params.index : 0);
        this.initParam("name", (params && "name" in params) ? params.name : '__NA__');
        this.initParam("fontSize", (params && "fontSize" in params) ? params.fontSize : 0);
        this.initParam("fontWeight", (params && "fontWeight" in params) ? params.fontWeight : 0);
        this.selectedIndex = 0;
        this.finalizeConstruction();
    }
    resetStateVarsOnReuse(params) {
        this.resetParam("index", (params && "index" in params) ? params.index : 0);
        this.resetParam("name", (params && "name" in params) ? params.name : '__NA__');
        this.resetParam("fontSize", (params && "fontSize" in params) ? params.fontSize : 0);
        this.resetParam("fontWeight", (params && "fontWeight" in params) ? params.fontWeight : 0);
        this.resetConsumer("selectedIndex", 0);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.name);
            Text.fontFamily('HarmonyHeiTi');
            Text.fontColor(this.index === this.selectedIndex ? 'rgba(0, 0, 0, 0.9)' : 'rgba(0, 0, 0, 0.6)');
            Text.fontSize(10);
            Text.fontWeight(500);
        }, Text);
        Text.pop();
        Column.pop();
    }
    updateStateVars(params) {
        if (params === undefined) {
            return;
        }
        if ("index" in params) {
            this.updateParam("index", params.index);
        }
        if ("name" in params) {
            this.updateParam("name", params.name);
        }
        if ("fontSize" in params) {
            this.updateParam("fontSize", params.fontSize);
        }
        if ("fontWeight" in params) {
            this.updateParam("fontWeight", params.fontWeight);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
__decorate([
    Param
], UserInteractiveAreaTabBarText.prototype, "index", void 0);
__decorate([
    Param
], UserInteractiveAreaTabBarText.prototype, "name", void 0);
__decorate([
    Param
], UserInteractiveAreaTabBarText.prototype, "fontSize", void 0);
__decorate([
    Param
], UserInteractiveAreaTabBarText.prototype, "fontWeight", void 0);
__decorate([
    Consumer('functionAreaSelectedIndex')
], UserInteractiveAreaTabBarText.prototype, "selectedIndex", void 0);
