/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

if (!('finalizeConstruction' in ViewPU.prototype)) {
  Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
if (PUV2ViewBase.contextStack === undefined) {
  Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('ohos.hilog');
const r5 = { 'id': -1, 'type': 40000, params: ['sys.symbol.dot_grid_2x2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const s5 = { 'id': -1, 'type': 40000, params: ['sys.symbol.arrow_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const t5 = '18.3fp';
const u5 = '64vp';
const v5 = '256vp';
const w5 = '216vp';
const k5 = 40000;
class Util {
    static l5(l5) {
        if (!Util.m5(l5)) {
            return false;
        }
        let resource = l5;
        return resource.type === k5;
    }
    static m5(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }
}
class ComposeTitleBar extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.item = undefined;
        this.title = '';
        this.subtitle = '';
        this.menuItems = [];
        this.q5 = new ObservedPropertySimplePU(0, this, 'titleMaxWidth');
        this.b6 = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.item !== undefined) {
            this.item = params.item;
        }
        if (params.title !== undefined) {
            this.title = params.title;
        }
        if (params.subtitle !== undefined) {
            this.subtitle = params.subtitle;
        }
        if (params.menuItems !== undefined) {
            this.menuItems = params.menuItems;
        }
        if (params.titleMaxWidth !== undefined) {
            this.titleMaxWidth = params.titleMaxWidth;
        }
        if (params.fontSize !== undefined) {
            this.fontSize = params.fontSize;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.q5.purgeDependencyOnElmtId(rmElmtId);
        this.b6.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.q5.aboutToBeDeleted();
        this.b6.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get titleMaxWidth() {
        return this.q5.get();
    }
    set titleMaxWidth(newValue) {
        this.q5.set(newValue);
    }
    get fontSize() {
        return this.b6.get();
    }
    set fontSize(newValue) {
        this.b6.set(newValue);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.width('100%');
            Flex.height(ComposeTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((c3, newValue) => {
                let d3 = Number(newValue.width);
                if (this.menuItems !== undefined) {
                    let e3 = this.menuItems.length;
                    if (e3 >= y5.maxCountOfVisibleItems) {
                        d3 = d3 - z5.imageHotZoneWidth * y5.maxCountOfVisibleItems;
                    }
                    else if (e3 > 0) {
                        d3 = d3 - z5.imageHotZoneWidth * e3;
                    }
                }
                this.titleMaxWidth = d3;
                this.titleMaxWidth -= ComposeTitleBar.leftPadding;
                this.titleMaxWidth -= z5.imageHotZoneWidth;
                if (this.item !== undefined) {
                    this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
                        ComposeTitleBar.portraitImageSize +
                        ComposeTitleBar.portraitImageRightPadding;
                }
                this.titleMaxWidth -= ComposeTitleBar.rightPadding;
            });
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.margin({ left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
        }, Row);
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new z5(this, {
                        item: {
                            value: s5,
                            isEnabled: true,
                            action: () => this.getUIContext()?.getRouter()?.back()
                        },
                        index: -1
                    }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 80, d3: 9 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            item: {
                                value: s5,
                                isEnabled: true,
                                action: () => this.getUIContext()?.getRouter()?.back()
                            },
                            index: -1
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'ImageMenuItem' });
        }
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.item.value);
                        Image.width(ComposeTitleBar.portraitImageSize);
                        Image.height(ComposeTitleBar.portraitImageSize);
                        Image.margin({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                        });
                        Image.focusable(false);
                        Image.borderRadius(z5.buttonBorderRadius);
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.title !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.title);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(this.subtitle !== undefined ? 1 : 2);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
                    }, Text);
                    Text.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.subtitle);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
                    }, Text);
                    Text.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Column.pop();
        Row.pop();
        Row.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new y5(this, { menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 134, d3: 9 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + ComposeTitleBar.instanceCount++
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {});
                            }
                        }, { name: 'CollapsibleMenuSection' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
ComposeTitleBar.totalHeight = 56;
ComposeTitleBar.leftPadding = 12;
ComposeTitleBar.rightPadding = 12;
ComposeTitleBar.portraitImageSize = 40;
ComposeTitleBar.portraitImageLeftPadding = 4;
ComposeTitleBar.portraitImageRightPadding = 16;
ComposeTitleBar.instanceCount = 0;
class y5 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.menuItems = [];
        this.item = {
            value: r5,
            label: { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        };
        this.index = 0;
        this.longPressTime = 500;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.firstFocusableIndex = -1;
        this.c6 = new ObservedPropertySimplePU(false, this, 'isPopupShown');
        this.d6 = new ObservedPropertySimplePU(false, this, 'isMoreIconOnFocus');
        this.e6 = new ObservedPropertySimplePU(false, this, 'isMoreIconOnHover');
        this.f6 = new ObservedPropertySimplePU(false, this, 'isMoreIconOnClick');
        this.b6 = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let jsDialog = new a6(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 186, d3: 14 });
                jsDialog.setController(this.dialogController);
                ViewPU.create(jsDialog);
                let paramsLambda = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        itemComposeTitleDialog: this.item,
                        composeTitleBarDialog: this.item.label ? this.item.label : '',
                        fontSize: this.fontSize
                    };
                };
                jsDialog.paramsGenerator_ = paramsLambda;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.menuItems !== undefined) {
            this.menuItems = params.menuItems;
        }
        if (params.item !== undefined) {
            this.item = params.item;
        }
        if (params.index !== undefined) {
            this.index = params.index;
        }
        if (params.longPressTime !== undefined) {
            this.longPressTime = params.longPressTime;
        }
        if (params.minFontSize !== undefined) {
            this.minFontSize = params.minFontSize;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.maxFontScale !== undefined) {
            this.maxFontScale = params.maxFontScale;
        }
        if (params.systemFontScale !== undefined) {
            this.systemFontScale = params.systemFontScale;
        }
        if (params.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = params.firstFocusableIndex;
        }
        if (params.isPopupShown !== undefined) {
            this.isPopupShown = params.isPopupShown;
        }
        if (params.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = params.isMoreIconOnFocus;
        }
        if (params.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = params.isMoreIconOnHover;
        }
        if (params.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = params.isMoreIconOnClick;
        }
        if (params.fontSize !== undefined) {
            this.fontSize = params.fontSize;
        }
        if (params.dialogController !== undefined) {
            this.dialogController = params.dialogController;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.c6.purgeDependencyOnElmtId(rmElmtId);
        this.d6.purgeDependencyOnElmtId(rmElmtId);
        this.e6.purgeDependencyOnElmtId(rmElmtId);
        this.f6.purgeDependencyOnElmtId(rmElmtId);
        this.b6.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.c6.aboutToBeDeleted();
        this.d6.aboutToBeDeleted();
        this.e6.aboutToBeDeleted();
        this.f6.aboutToBeDeleted();
        this.b6.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isPopupShown() {
        return this.c6.get();
    }
    set isPopupShown(newValue) {
        this.c6.set(newValue);
    }
    get isMoreIconOnFocus() {
        return this.d6.get();
    }
    set isMoreIconOnFocus(newValue) {
        this.d6.set(newValue);
    }
    get isMoreIconOnHover() {
        return this.e6.get();
    }
    set isMoreIconOnHover(newValue) {
        this.e6.set(newValue);
    }
    get isMoreIconOnClick() {
        return this.f6.get();
    }
    set isMoreIconOnClick(newValue) {
        this.f6.set(newValue);
    }
    get fontSize() {
        return this.b6.get();
    }
    set fontSize(newValue) {
        this.b6.set(newValue);
    }
    getMoreIconFgColor() {
        return this.isMoreIconOnClick ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    getMoreIconBgColor() {
        if (this.isMoreIconOnClick) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.isMoreIconOnHover) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return Color.Transparent;
        }
    }
    aboutToAppear() {
        try {
            let r2 = this.getUIContext();
            this.isFollowingSystemFontScale = r2.isFollowingSystemFontScale();
            this.maxFontScale = r2.getMaxFontScale();
        }
        catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
        }
        if (this.menuItems) {
            this.menuItems.forEach((item, index) => {
                if (item.isEnabled && this.firstFocusableIndex == -1 &&
                    index > y5.maxCountOfVisibleItems - 2) {
                    this.firstFocusableIndex = this.index * 1000 + index + 1;
                }
            });
        }
    }
    decideFontScale() {
        try {
            let k2 = this.getUIContext();
            this.systemFontScale = k2.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (p1) {
            let code = p1.code;
            let message = p1.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
            return 1;
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.menuItems.length <= y5.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = (_item, index) => {
                                        const item = _item;
                                        {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                if (isInitialRender) {
                                                    let componentCall = new z5(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 259, d3: 15 });
                                                    ViewPU.create(componentCall);
                                                    let paramsLambda = () => {
                                                        return {
                                                            item: item,
                                                            index: this.index * 1000 + index + 1
                                                        };
                                                    };
                                                    componentCall.paramsGenerator_ = paramsLambda;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                                                }
                                            }, { name: 'ImageMenuItem' });
                                        }
                                    };
                                    this.forEachUpdateFunction(elmtId, this.menuItems, forEachItemGenFunction, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = (_item, index) => {
                                        const item = _item;
                                        {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                if (isInitialRender) {
                                                    let componentCall = new z5(this, { item: item, index: this.index * 1000 + index + 1 }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 264, d3: 17 });
                                                    ViewPU.create(componentCall);
                                                    let paramsLambda = () => {
                                                        return {
                                                            item: item,
                                                            index: this.index * 1000 + index + 1
                                                        };
                                                    };
                                                    componentCall.paramsGenerator_ = paramsLambda;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                                                }
                                            }, { name: 'ImageMenuItem' });
                                        }
                                    };
                                    this.forEachUpdateFunction(elmtId, this.menuItems.slice(0, y5.maxCountOfVisibleItems - 1), forEachItemGenFunction, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Button.createWithChild({ type: ButtonType.Normal, stateEffect: true });
                                    Button.width(z5.imageHotZoneWidth);
                                    Button.height(z5.imageHotZoneWidth);
                                    Button.borderRadius(z5.buttonBorderRadius);
                                    Button.foregroundColor(this.getMoreIconFgColor());
                                    Button.backgroundColor(this.getMoreIconBgColor());
                                    ViewStackProcessor.visualState('focused');
                                    Button.border({
                                        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        width: z5.focusBorderWidth,
                                        color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        style: BorderStyle.Solid
                                    });
                                    ViewStackProcessor.visualState('normal');
                                    Button.border({
                                        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        width: 0
                                    });
                                    ViewStackProcessor.visualState();
                                    Button.onFocus(() => this.isMoreIconOnFocus = true);
                                    Button.onBlur(() => this.isMoreIconOnFocus = false);
                                    Button.onHover((isOn) => this.isMoreIconOnHover = isOn);
                                    Button.onKeyEvent((event) => {
                                        if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            event.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (event.type === KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (event.type === KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((event) => {
                                        if (event.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                                            this.isMoreIconOnClick = false;
                                            if (this.fontSize >= this.minFontSize) {
                                                this.dialogController?.close();
                                            }
                                        }
                                    });
                                    Button.onClick(() => this.isPopupShown = true);
                                    Gesture.create(GesturePriority.Low);
                                    LongPressGesture.create({ repeat: false, duration: this.longPressTime });
                                    LongPressGesture.onAction((event) => {
                                        this.fontSize = this.decideFontScale();
                                        if (event) {
                                            if (this.fontSize >= this.minFontSize) {
                                                this.dialogController?.open();
                                            }
                                        }
                                    });
                                    LongPressGesture.pop();
                                    Gesture.pop();
                                    Button.bindPopup(this.isPopupShown, {
                                        builder: { builder: this.popupBuilder.bind(this) },
                                        placement: Placement.Bottom,
                                        popupColor: Color.White,
                                        enableArrow: false,
                                        onStateChange: (e) => {
                                            this.isPopupShown = e.isVisible;
                                            if (!e.isVisible) {
                                                this.isMoreIconOnClick = false;
                                            }
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create(r5);
                                    SymbolGlyph.fontSize(`${z5.imageSize}vp`);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(true);
                                }, SymbolGlyph);
                                Button.pop();
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
        Column.pop();
    }
    popupBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(z5.imageHotZoneWidth +
                y5.focusPadding * y5.marginsNum);
            Column.margin({ top: y5.focusPadding, bottom: y5.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(z5.focusablePrefix +
                    this.firstFocusableIndex);
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        ForEach.create();
                        const forEachItemGenFunction = (_item, index) => {
                            const item = _item;
                            {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    if (isInitialRender) {
                                        let componentCall = new z5(this, {
                                            item: item,
                                            index: this.index * 1000 +
                                                y5.maxCountOfVisibleItems + index,
                                            isPopup: true
                                        }, undefined, elmtId, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 360, d3: 13 });
                                        ViewPU.create(componentCall);
                                        let paramsLambda = () => {
                                            return {
                                                item: item,
                                                index: this.index * 1000 +
                                                    y5.maxCountOfVisibleItems + index,
                                                isPopup: true
                                            };
                                        };
                                        componentCall.paramsGenerator_ = paramsLambda;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(elmtId, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(elmtId, this.menuItems.slice(y5.maxCountOfVisibleItems - 1, this.menuItems.length), forEachItemGenFunction, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
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
    rerender() {
        this.updateDirtyElements();
    }
}
y5.maxCountOfVisibleItems = 3;
y5.focusPadding = 4;
y5.marginsNum = 2;
class z5 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.item = {};
        this.index = 0;
        this.longPressTime = 500;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.isPopup = false;
        this.h6 = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.i6 = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.j6 = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.b6 = new SynchedPropertySimpleOneWayPU(params.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let jsDialog = new a6(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/MainPage.ets', line: 397, d3: 14 });
                jsDialog.setController(this.dialogController);
                ViewPU.create(jsDialog);
                let paramsLambda = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        itemComposeTitleDialog: this.item,
                        composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize
                    };
                };
                jsDialog.paramsGenerator_ = paramsLambda;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.item !== undefined) {
            this.item = params.item;
        }
        if (params.index !== undefined) {
            this.index = params.index;
        }
        if (params.longPressTime !== undefined) {
            this.longPressTime = params.longPressTime;
        }
        if (params.minFontSize !== undefined) {
            this.minFontSize = params.minFontSize;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.maxFontScale !== undefined) {
            this.maxFontScale = params.maxFontScale;
        }
        if (params.systemFontScale !== undefined) {
            this.systemFontScale = params.systemFontScale;
        }
        if (params.isPopup !== undefined) {
            this.isPopup = params.isPopup;
        }
        if (params.isOnFocus !== undefined) {
            this.isOnFocus = params.isOnFocus;
        }
        if (params.isOnHover !== undefined) {
            this.isOnHover = params.isOnHover;
        }
        if (params.isOnClick !== undefined) {
            this.isOnClick = params.isOnClick;
        }
        if (params.fontSize === undefined) {
            this.b6.set(1);
        }
        if (params.dialogController !== undefined) {
            this.dialogController = params.dialogController;
        }
    }
    updateStateVars(params) {
        this.b6.reset(params.fontSize);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.h6.purgeDependencyOnElmtId(rmElmtId);
        this.i6.purgeDependencyOnElmtId(rmElmtId);
        this.j6.purgeDependencyOnElmtId(rmElmtId);
        this.b6.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.h6.aboutToBeDeleted();
        this.i6.aboutToBeDeleted();
        this.j6.aboutToBeDeleted();
        this.b6.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isOnFocus() {
        return this.h6.get();
    }
    set isOnFocus(newValue) {
        this.h6.set(newValue);
    }
    get isOnHover() {
        return this.i6.get();
    }
    set isOnHover(newValue) {
        this.i6.set(newValue);
    }
    get isOnClick() {
        return this.j6.get();
    }
    set isOnClick(newValue) {
        this.j6.set(newValue);
    }
    get fontSize() {
        return this.b6.get();
    }
    set fontSize(newValue) {
        this.b6.set(newValue);
    }
    textDialog() {
        if (this.item.value === r5) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.value === s5) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return this.item.label ? this.item.label : '';
        }
    }
    getFgColor() {
        return this.isOnClick
            ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
    getBgColor() {
        if (this.isOnClick) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_click_effect'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.isOnHover) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_hover'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return Color.Transparent;
        }
    }
    aboutToAppear() {
        try {
            let k1 = this.getUIContext();
            this.isFollowingSystemFontScale = k1.isFollowingSystemFontScale();
            this.maxFontScale = k1.getMaxFontScale();
        }
        catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
        }
    }
    decideFontScale() {
        try {
            let b1 = this.getUIContext();
            this.systemFontScale = b1.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (t) {
            let code = t.code;
            let message = t.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
            return 1;
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.enabled(this.item.isEnabled ? this.item.isEnabled : false);
            Button.width(z5.imageHotZoneWidth);
            Button.height(z5.imageHotZoneWidth);
            Button.borderRadius(z5.buttonBorderRadius);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: z5.focusBorderWidth,
                color: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_focused_outline'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: 0
            });
            ViewStackProcessor.visualState();
            Button.onFocus(() => {
                if (!this.item?.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((isOn) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                this.isOnHover = isOn;
            });
            Button.onKeyEvent((event) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
                    event.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (event.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (event.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((event) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (event.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                    this.isOnClick = false;
                    if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                        this.dialogController?.close();
                    }
                }
            });
            Button.onClick(() => {
                if (this.item) {
                    return this.item.isEnabled && this.item.action?.();
                }
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: false, duration: this.longPressTime });
            LongPressGesture.onAction((event) => {
                this.fontSize = this.decideFontScale();
                if (event) {
                    if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            Gesture.pop();
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.item?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        SymbolGlyph.create();
                        SymbolGlyph.attributeModifier.bind(this)(this.item?.symbolStyle);
                        SymbolGlyph.fontSize(`${z5.imageSize}vp`);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(this.item?.isEnabled);
                        SymbolGlyph.key(z5.focusablePrefix + this.index);
                    }, SymbolGlyph);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (Util.l5(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create(this.item.value);
                                    SymbolGlyph.fontSize(`${z5.imageSize}vp`);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                    SymbolGlyph.key(z5.focusablePrefix + this.index);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    Image.create(this.item?.value);
                                    Image.matchTextDirection(this.item?.value === s5 ? true : false);
                                    Image.width(z5.imageSize);
                                    Image.draggable(false);
                                    Image.height(z5.imageSize);
                                    Image.focusable(this.item?.isEnabled);
                                    Image.key(z5.focusablePrefix + this.index);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                }, Image);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
        }, If);
        If.pop();
        Button.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
z5.imageSize = 24;
z5.imageHotZoneWidth = 48;
z5.buttonBorderRadius = 8;
z5.focusBorderWidth = 2;
z5.focusablePrefix = 'Id-ComposeTitleBar-ImageMenuItem-';
class a6 extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.itemComposeTitleDialog = {};
        this.callbackId = undefined;
        this.composeTitleBarDialog = '';
        this.mainWindowStage = undefined;
        this.controller = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.screenWidth = 640;
        this.verticalScreenLines = 6;
        this.horizontalsScreenLines = 1;
        this.k6 = this.createStorageLink('mainWindow', undefined, 'mainWindow');
        this.b6 = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.l6 = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.m6 = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.itemComposeTitleDialog !== undefined) {
            this.itemComposeTitleDialog = params.itemComposeTitleDialog;
        }
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
        }
        if (params.composeTitleBarDialog !== undefined) {
            this.composeTitleBarDialog = params.composeTitleBarDialog;
        }
        if (params.mainWindowStage !== undefined) {
            this.mainWindowStage = params.mainWindowStage;
        }
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.minFontSize !== undefined) {
            this.minFontSize = params.minFontSize;
        }
        if (params.maxFontSize !== undefined) {
            this.maxFontSize = params.maxFontSize;
        }
        if (params.screenWidth !== undefined) {
            this.screenWidth = params.screenWidth;
        }
        if (params.verticalScreenLines !== undefined) {
            this.verticalScreenLines = params.verticalScreenLines;
        }
        if (params.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = params.horizontalsScreenLines;
        }
        if (params.fontSize !== undefined) {
            this.fontSize = params.fontSize;
        }
        if (params.maxLines !== undefined) {
            this.maxLines = params.maxLines;
        }
        if (params.cancel !== undefined) {
            this.cancel = params.cancel;
        }
        if (params.confirm !== undefined) {
            this.confirm = params.confirm;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.k6.purgeDependencyOnElmtId(rmElmtId);
        this.b6.purgeDependencyOnElmtId(rmElmtId);
        this.l6.purgeDependencyOnElmtId(rmElmtId);
        this.m6.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.k6.aboutToBeDeleted();
        this.b6.aboutToBeDeleted();
        this.l6.aboutToBeDeleted();
        this.m6.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(ctr) {
        this.controller = ctr;
    }
    get mainWindow() {
        return this.k6.get();
    }
    set mainWindow(newValue) {
        this.k6.set(newValue);
    }
    get fontSize() {
        return this.b6.get();
    }
    set fontSize(newValue) {
        this.b6.set(newValue);
    }
    get maxLines() {
        return this.l6.get();
    }
    set maxLines(newValue) {
        this.l6.set(newValue);
    }
    get windowStandardHeight() {
        return this.m6.get();
    }
    set windowStandardHeight(newValue) {
        this.m6.set(newValue);
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.composeTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? v5 : w5);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? v5 : w5 });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.itemComposeTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(`${u5}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (Util.l5(this.itemComposeTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create(this.itemComposeTitleDialog.value);
                                                SymbolGlyph.fontSize(`${u5}vp`);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                Image.create(this.itemComposeTitleDialog.value);
                                                Image.width(u5);
                                                Image.height(u5);
                                                Image.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.composeTitleBarDialog);
                        Text.fontSize(t5);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? v5 : w5);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? v5 : w5 });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.itemComposeTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(`${u5}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (Util.l5(this.itemComposeTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                SymbolGlyph.create(this.itemComposeTitleDialog.value);
                                                SymbolGlyph.fontSize(`${u5}vp`);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                Image.create(this.itemComposeTitleDialog.value);
                                                Image.width(u5);
                                                Image.height(u5);
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                            }, Image);
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                    }, If);
                    If.pop();
                    Column.pop();
                });
            }
        }, If);
        If.pop();
    }
    async aboutToAppear() {
        let context = this.getUIContext().getHostContext();
        this.mainWindowStage = context.windowStage.getMainWindowSync();
        let properties = this.mainWindowStage.getWindowProperties();
        let rect = properties.windowRect;
        if (px2vp(rect.height) > this.screenWidth) {
            this.maxLines = this.verticalScreenLines;
        }
        else {
            this.maxLines = this.horizontalsScreenLines;
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default { ComposeTitleBar };