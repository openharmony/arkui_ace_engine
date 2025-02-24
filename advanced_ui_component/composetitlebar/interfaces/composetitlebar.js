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
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('ohos.hilog');
const PUBLIC_MORE = { 'id': -1, 'type': 40000, params: ['sys.symbol.dot_grid_2x2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 40000, params: ['sys.symbol.arrow_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const RESOURCE_TYPE_SYMBOL = 40000;
class Util {
    static isSymbolResource(o9) {
        if (!Util.isResourceType(o9)) {
            return false;
        }
        let p9 = o9;
        return p9.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(n9) {
        if (!n9) {
            return false;
        }
        if (typeof n9 === 'string' || typeof n9 === 'undefined') {
            return false;
        }
        return true;
    }
}
class ButtonGestureModifier {
    constructor(m9) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = m9;
    }
    applyGesture(l9) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            l9.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (l9) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            l9.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
class ComposeTitleBar extends ViewPU {
    constructor(f9, g9, h9, i9 = -1, j9 = undefined, k9) {
        super(f9, h9, i9, k9);
        if (typeof j9 === 'function') {
            this.paramsGenerator_ = j9;
        }
        this.item = undefined;
        this.title = '';
        this.subtitle = '';
        this.menuItems = [];
        this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, 'titleMaxWidth');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__uniqueId = new ObservedPropertySimplePU(-1, this, 'uniqueId');
        this.addProvidedVar('uniqueId', this.__uniqueId, false);
        this.setInitiallyProvidedValue(g9);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(e9) {
        if (e9.item !== undefined) {
            this.item = e9.item;
        }
        if (e9.title !== undefined) {
            this.title = e9.title;
        }
        if (e9.subtitle !== undefined) {
            this.subtitle = e9.subtitle;
        }
        if (e9.menuItems !== undefined) {
            this.menuItems = e9.menuItems;
        }
        if (e9.titleMaxWidth !== undefined) {
            this.titleMaxWidth = e9.titleMaxWidth;
        }
        if (e9.fontSize !== undefined) {
            this.fontSize = e9.fontSize;
        }
        if (e9.uniqueId !== undefined) {
            this.uniqueId = e9.uniqueId;
        }
    }
    updateStateVars(d9) {
    }
    purgeVariableDependenciesOnElmtId(c9) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(c9);
        this.__fontSize.purgeDependencyOnElmtId(c9);
        this.__uniqueId.purgeDependencyOnElmtId(c9);
    }
    aboutToBeDeleted() {
        this.__titleMaxWidth.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__uniqueId.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get titleMaxWidth() {
        return this.__titleMaxWidth.get();
    }
    set titleMaxWidth(b9) {
        this.__titleMaxWidth.set(b9);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(a9) {
        this.__fontSize.set(a9);
    }
    get uniqueId() {
        return this.__uniqueId.get();
    }
    set uniqueId(z8) {
        this.__uniqueId.set(z8);
    }
    initialRender() {
        this.observeComponentCreation2((t8, u8) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.onAppear(() => {
                this.uniqueId = this.getUIContext().getFrameNodeByUniqueId(this.getUniqueId())?.getFirstChild()?.getUniqueId();
            });
            Flex.width('100%');
            Flex.height(ComposeTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((v8, w8) => {
                let x8 = Number(w8.width);
                if (this.menuItems !== undefined) {
                    let y8 = this.menuItems.length;
                    if (y8 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        x8 = x8 - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (y8 > 0) {
                        x8 = x8 - ImageMenuItem.imageHotZoneWidth * y8;
                    }
                }
                this.titleMaxWidth = x8;
                this.titleMaxWidth -= ComposeTitleBar.leftPadding;
                this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth;
                if (this.item !== undefined) {
                    this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
                    ComposeTitleBar.portraitImageSize +
                    ComposeTitleBar.portraitImageRightPadding;
                }
                this.titleMaxWidth -= ComposeTitleBar.rightPadding;
            });
        }, Flex);
        this.observeComponentCreation2((r8, s8) => {
            Row.create();
            Row.margin({ left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
        }, Row);
        {
            this.observeComponentCreation2((n8, o8) => {
                if (o8) {
                    let p8 = new ImageMenuItem(this, {
                        item: {
                            value: PUBLIC_BACK,
                            isEnabled: true,
                            action: () => this.getUIContext()?.getRouter()?.back()
                        },
                        index: -1,
                        itemIndex: -1
                    }, undefined, n8, () => { }, { page: 'library/src/main/ets/components/composetitlebar.ets', line: 113, col: 9 });
                    ViewPU.create(p8);
                    let q8 = () => {
                        return {
                            item: {
                                value: PUBLIC_BACK,
                                isEnabled: true,
                                action: () => this.getUIContext()?.getRouter()?.back()
                            },
                            index: -1,
                            itemIndex: -1
                        };
                    };
                    p8.paramsGenerator_ = q8;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(n8, {});
                }
            }, { name: 'ImageMenuItem' });
        }
        this.observeComponentCreation2((l8, m8) => {
            Row.create();
            Row.accessibilityGroup(true);
        }, Row);
        this.observeComponentCreation2((h8, i8) => {
            If.create();
            if (this.item !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j8, k8) => {
                        Image.create(this.item.value);
                        Image.width(ComposeTitleBar.portraitImageSize);
                        Image.height(ComposeTitleBar.portraitImageSize);
                        Image.margin({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                        });
                        Image.focusable(false);
                        Image.borderRadius(ImageMenuItem.buttonBorderRadius);
                    }, Image);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((f8, g8) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
        }, Column);
        this.observeComponentCreation2((z7, a8) => {
            If.create();
            if (this.title !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d8, e8) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((b8, c8) => {
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
        this.observeComponentCreation2((t7, u7) => {
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x7, y7) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((v7, w7) => {
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
        this.observeComponentCreation2((n7, o7) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((p7, q7) => {
                            if (q7) {
                                let r7 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ }, undefined, p7, () => { }, { page: 'library/src/main/ets/components/composetitlebar.ets', line: 170, col: 9 });
                                ViewPU.create(r7);
                                let s7 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + ComposeTitleBar.instanceCount++
                                    };
                                };
                                r7.paramsGenerator_ = s7;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(p7, {});
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
class CollapsibleMenuSection extends ViewPU {
    constructor(f7, g7, h7, i7 = -1, j7 = undefined, k7) {
        super(f7, h7, i7, k7);
        if (typeof j7 === 'function') {
            this.paramsGenerator_ = j7;
        }
        this.menuItems = [];
        this.item = {
            value: PUBLIC_MORE,
            label: { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        };
        this.index = 0;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.firstFocusableIndex = -1;
        this.__isPopupShown = new ObservedPropertySimplePU(false, this, 'isPopupShown');
        this.__isMoreIconOnFocus = new ObservedPropertySimplePU(false, this, 'isMoreIconOnFocus');
        this.__isMoreIconOnHover = new ObservedPropertySimplePU(false, this, 'isMoreIconOnHover');
        this.__isMoreIconOnClick = new ObservedPropertySimplePU(false, this, 'isMoreIconOnClick');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(g7.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let l7 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/composetitlebar.ets', line: 224, col: 14 });
                l7.setController(this.dialogController);
                ViewPU.create(l7);
                let m7 = () => {
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
                l7.paramsGenerator_ = m7;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(g7);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(e7) {
        if (e7.menuItems !== undefined) {
            this.menuItems = e7.menuItems;
        }
        if (e7.item !== undefined) {
            this.item = e7.item;
        }
        if (e7.index !== undefined) {
            this.index = e7.index;
        }
        if (e7.minFontSize !== undefined) {
            this.minFontSize = e7.minFontSize;
        }
        if (e7.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = e7.isFollowingSystemFontScale;
        }
        if (e7.maxFontScale !== undefined) {
            this.maxFontScale = e7.maxFontScale;
        }
        if (e7.systemFontScale !== undefined) {
            this.systemFontScale = e7.systemFontScale;
        }
        if (e7.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = e7.firstFocusableIndex;
        }
        if (e7.isPopupShown !== undefined) {
            this.isPopupShown = e7.isPopupShown;
        }
        if (e7.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = e7.isMoreIconOnFocus;
        }
        if (e7.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = e7.isMoreIconOnHover;
        }
        if (e7.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = e7.isMoreIconOnClick;
        }
        if (e7.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (e7.dialogController !== undefined) {
            this.dialogController = e7.dialogController;
        }
        if (e7.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = e7.buttonGestureModifier;
        }
    }
    updateStateVars(d7) {
        this.__fontSize.reset(d7.fontSize);
    }
    purgeVariableDependenciesOnElmtId(c7) {
        this.__isPopupShown.purgeDependencyOnElmtId(c7);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(c7);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(c7);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(c7);
        this.__fontSize.purgeDependencyOnElmtId(c7);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(c7);
    }
    aboutToBeDeleted() {
        this.__isPopupShown.aboutToBeDeleted();
        this.__isMoreIconOnFocus.aboutToBeDeleted();
        this.__isMoreIconOnHover.aboutToBeDeleted();
        this.__isMoreIconOnClick.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__buttonGestureModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isPopupShown() {
        return this.__isPopupShown.get();
    }
    set isPopupShown(b7) {
        this.__isPopupShown.set(b7);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(a7) {
        this.__isMoreIconOnFocus.set(a7);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(z6) {
        this.__isMoreIconOnHover.set(z6);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(y6) {
        this.__isMoreIconOnClick.set(y6);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(x6) {
        this.__fontSize.set(x6);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(w6) {
        this.__buttonGestureModifier.set(w6);
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
            let v6 = this.getUIContext();
            this.isFollowingSystemFontScale = v6.isFollowingSystemFontScale();
            this.maxFontScale = v6.getMaxFontScale();
        }
        catch (s6) {
            let t6 = s6.code;
            let u6 = s6.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${t6}, message: ${u6}`);
        }
        if (this.menuItems) {
            this.menuItems.forEach((q6, r6) => {
                if (q6.isEnabled && this.firstFocusableIndex === -1 &&
                    r6 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                    this.firstFocusableIndex = this.index * 1000 + r6 + 1;
                }
            });
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        try {
            let p6 = this.getUIContext();
            this.systemFontScale = p6.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (m6) {
            let n6 = m6.code;
            let o6 = m6.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${n6}, message: ${o6}`);
            return 1;
        }
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        this.observeComponentCreation2((k6, l6) => {
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((i6, j6) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((c5, d5) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e5, f5) => {
                        If.create();
                        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((y5, z5) => {
                                    ForEach.create();
                                    const a6 = (b6, c6) => {
                                        const d6 = b6;
                                        {
                                            this.observeComponentCreation2((e6, f6) => {
                                                if (f6) {
                                                    let g6 = new ImageMenuItem(this, { item: d6, index: this.index * 1000 + c6 + 1, itemIndex: c6 }, undefined, e6, () => { }, { page: 'library/src/main/ets/components/composetitlebar.ets', line: 304, col: 15 });
                                                    ViewPU.create(g6);
                                                    let h6 = () => {
                                                        return {
                                                            item: d6,
                                                            index: this.index * 1000 + c6 + 1,
                                                            itemIndex: c6
                                                        };
                                                    };
                                                    g6.paramsGenerator_ = h6;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(e6, {});
                                                }
                                            }, { name: 'ImageMenuItem' });
                                        }
                                    };
                                    this.forEachUpdateFunction(y5, this.menuItems, a6, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((o5, p5) => {
                                    ForEach.create();
                                    const q5 = (r5, s5) => {
                                        const t5 = r5;
                                        {
                                            this.observeComponentCreation2((u5, v5) => {
                                                if (v5) {
                                                    let w5 = new ImageMenuItem(this, { item: t5, index: this.index * 1000 + s5 + 1, itemIndex: s5 }, undefined, u5, () => { }, { page: 'library/src/main/ets/components/composetitlebar.ets', line: 309, col: 17 });
                                                    ViewPU.create(w5);
                                                    let x5 = () => {
                                                        return {
                                                            item: t5,
                                                            index: this.index * 1000 + s5 + 1,
                                                            itemIndex: s5
                                                        };
                                                    };
                                                    w5.paramsGenerator_ = x5;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(u5, {});
                                                }
                                            }, { name: 'ImageMenuItem' });
                                        }
                                    };
                                    this.forEachUpdateFunction(o5, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), q5, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                                this.observeComponentCreation2((i5, j5) => {
                                    Button.createWithChild({ type: ButtonType.Normal, stateEffect: true });
                                    Button.accessibilityText({ 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    Button.width(ImageMenuItem.imageHotZoneWidth);
                                    Button.height(ImageMenuItem.imageHotZoneWidth);
                                    Button.borderRadius(ImageMenuItem.buttonBorderRadius);
                                    Button.foregroundColor(this.getMoreIconFgColor());
                                    Button.backgroundColor(this.getMoreIconBgColor());
                                    ViewStackProcessor.visualState('focused');
                                    Button.border({
                                        radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        width: ImageMenuItem.focusBorderWidth,
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
                                    Button.onHover((n5) => this.isMoreIconOnHover = n5);
                                    Button.onKeyEvent((m5) => {
                                        if (m5.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            m5.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (m5.type === KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (m5.type === KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((l5) => {
                                        if (l5.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (l5.type === TouchType.Up || l5.type === TouchType.Cancel) {
                                            this.isMoreIconOnClick = false;
                                            if (this.fontSize >= this.minFontSize) {
                                                this.dialogController?.close();
                                            }
                                        }
                                    });
                                    Button.onClick(() => this.isPopupShown = true);
                                    Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
                                    Button.bindPopup(this.isPopupShown, {
                                        builder: { builder: this.popupBuilder.bind(this) },
                                        placement: Placement.Bottom,
                                        popupColor: Color.White,
                                        enableArrow: false,
                                        onStateChange: (k5) => {
                                            this.isPopupShown = k5.isVisible;
                                            if (!k5.isVisible) {
                                                this.isMoreIconOnClick = false;
                                            }
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((g5, h5) => {
                                    SymbolGlyph.create(PUBLIC_MORE);
                                    SymbolGlyph.fontSize(`${ImageMenuItem.imageSize}vp`);
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
    onPlaceChildren(y4, z4, a5) {
        z4.forEach((b5) => {
            b5.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    popupBuilder(j4 = null) {
        this.observeComponentCreation2((w4, x4) => {
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth +
                CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix +
                this.firstFocusableIndex);
            });
        }, Column);
        this.observeComponentCreation2((k4, l4) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m4, n4) => {
                        ForEach.create();
                        const o4 = (p4, q4) => {
                            const r4 = p4;
                            {
                                this.observeComponentCreation2((s4, t4) => {
                                    if (t4) {
                                        let u4 = new ImageMenuItem(this, {
                                            item: r4, index: this.index * 1000 +
                                            CollapsibleMenuSection.maxCountOfVisibleItems + q4,
                                            isPopup: false
                                        }, undefined, s4, () => { }, { page: 'library/src/main/ets/components/composetitlebar.ets', line: 404, col: 13 });
                                        ViewPU.create(u4);
                                        let v4 = () => {
                                            return {
                                                item: r4,
                                                index: this.index * 1000 +
                                                CollapsibleMenuSection.maxCountOfVisibleItems + q4,
                                                isPopup: false
                                            };
                                        };
                                        u4.paramsGenerator_ = v4;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(s4, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(m4, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), o4, undefined, true, false);
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
CollapsibleMenuSection.maxCountOfVisibleItems = 3;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
class ImageMenuItem extends ViewPU {
    constructor(b4, c4, d4, e4 = -1, f4 = undefined, g4) {
        super(b4, d4, e4, g4);
        if (typeof f4 === 'function') {
            this.paramsGenerator_ = f4;
        }
        this.item = {};
        this.index = 0;
        this.itemIndex = 0;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.isPopup = true;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(c4.fontSize, this, 'fontSize');
        this.__parentParentUniqueId = this.initializeConsume('uniqueId', 'parentParentUniqueId');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let h4 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/composetitlebar.ets', line: 442, col: 14 });
                h4.setController(this.dialogController);
                ViewPU.create(h4);
                let i4 = () => {
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
                h4.paramsGenerator_ = i4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(c4);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a4) {
        if (a4.item !== undefined) {
            this.item = a4.item;
        }
        if (a4.index !== undefined) {
            this.index = a4.index;
        }
        if (a4.itemIndex !== undefined) {
            this.itemIndex = a4.itemIndex;
        }
        if (a4.minFontSize !== undefined) {
            this.minFontSize = a4.minFontSize;
        }
        if (a4.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = a4.isFollowingSystemFontScale;
        }
        if (a4.maxFontScale !== undefined) {
            this.maxFontScale = a4.maxFontScale;
        }
        if (a4.systemFontScale !== undefined) {
            this.systemFontScale = a4.systemFontScale;
        }
        if (a4.isPopup !== undefined) {
            this.isPopup = a4.isPopup;
        }
        if (a4.isOnFocus !== undefined) {
            this.isOnFocus = a4.isOnFocus;
        }
        if (a4.isOnHover !== undefined) {
            this.isOnHover = a4.isOnHover;
        }
        if (a4.isOnClick !== undefined) {
            this.isOnClick = a4.isOnClick;
        }
        if (a4.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (a4.dialogController !== undefined) {
            this.dialogController = a4.dialogController;
        }
        if (a4.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = a4.buttonGestureModifier;
        }
    }
    updateStateVars(z3) {
        this.__fontSize.reset(z3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(y3) {
        this.__isOnFocus.purgeDependencyOnElmtId(y3);
        this.__isOnHover.purgeDependencyOnElmtId(y3);
        this.__isOnClick.purgeDependencyOnElmtId(y3);
        this.__fontSize.purgeDependencyOnElmtId(y3);
        this.__parentParentUniqueId.purgeDependencyOnElmtId(y3);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(y3);
    }
    aboutToBeDeleted() {
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__parentParentUniqueId.aboutToBeDeleted();
        this.__buttonGestureModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(x3) {
        this.__isOnFocus.set(x3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(w3) {
        this.__isOnHover.set(w3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(v3) {
        this.__isOnClick.set(v3);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u3) {
        this.__fontSize.set(u3);
    }
    get parentParentUniqueId() {
        return this.__parentParentUniqueId.get();
    }
    set parentParentUniqueId(t3) {
        this.__parentParentUniqueId.set(t3);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(s3) {
        this.__buttonGestureModifier.set(s3);
    }
    textDialog() {
        if (this.item.value === PUBLIC_MORE) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.value === PUBLIC_BACK) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return this.item.label ? this.item.label : '';
        }
    }
    toStringFormat(n3) {
        if (typeof n3 === 'string') {
            return n3;
        }
        else if (typeof n3 === 'undefined') {
            return '';
        }
        else {
            let o3 = '';
            try {
                o3 = getContext()?.resourceManager?.getStringSync(n3);
            }
            catch (p3) {
                let q3 = p3?.code;
                let r3 = p3?.message;
                hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBar toStringFormat,code: ${q3},message:${r3}`);
            }
            return o3;
        }
    }
    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_BACK) {
            return getContext()?.resourceManager?.getStringByNameSync('icon_back');
        }
        else if (this.item.value === PUBLIC_MORE) {
            return getContext()?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
        }
        else if (this.item.accessibilityText) {
            return this.toStringFormat(this.item.accessibilityText);
        }
        else if (this.item.label) {
            return this.toStringFormat(this.item.label);
        }
        return ' ';
    }
    onPlaceChildren(j3, k3, l3) {
        k3.forEach((m3) => {
            m3.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
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
            let i3 = this.getUIContext();
            this.isFollowingSystemFontScale = i3.isFollowingSystemFontScale();
            this.maxFontScale = i3.getMaxFontScale();
        }
        catch (f3) {
            let g3 = f3.code;
            let h3 = f3.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${g3}, message: ${h3}`);
        }
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    decideFontScale() {
        try {
            let e3 = this.getUIContext();
            this.systemFontScale = e3.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (b3) {
            let c3 = b3.code;
            let d3 = b3.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${c3}, message: ${d3}`);
            return 1;
        }
    }
    initialRender() {
        this.observeComponentCreation2((v1, w1) => {
            If.create();
            if (this.isPopup) {
                this.ifElseBranchUpdateFunction(0, () => {
                    if (!If.canRetake(`ComposeTitleBar_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`)) {
                        this.observeComponentCreation2((w2, x2) => {
                            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
                            Button.id(`ComposeTitleBar_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`);
                            Button.accessibilityText(this.getAccessibilityReadText());
                            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
                            Button.accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription));
                            Button.enabled(this.item.isEnabled ? this.item.isEnabled : false);
                            Button.width(ImageMenuItem.imageHotZoneWidth);
                            Button.height(ImageMenuItem.imageHotZoneWidth);
                            Button.borderRadius(ImageMenuItem.buttonBorderRadius);
                            Button.foregroundColor(this.getFgColor());
                            Button.backgroundColor(this.getBgColor());
                            ViewStackProcessor.visualState('focused');
                            Button.border({
                                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                width: ImageMenuItem.focusBorderWidth,
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
                            Button.onHover((a3) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnHover = a3;
                            });
                            Button.onKeyEvent((z2) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (z2.keyCode !== KeyCode.KEYCODE_ENTER &&
                                    z2.keyCode !== KeyCode.KEYCODE_SPACE) {
                                    return;
                                }
                                if (z2.type === KeyType.Down) {
                                    this.isOnClick = true;
                                }
                                if (z2.type === KeyType.Up) {
                                    this.isOnClick = false;
                                }
                            });
                            Button.onTouch((y2) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (y2.type === TouchType.Down) {
                                    this.isOnClick = true;
                                }
                                if (y2.type === TouchType.Up || y2.type === TouchType.Cancel) {
                                    this.isOnClick = false;
                                    if (this.fontSize >= this.minFontSize) {
                                        this.dialogController?.close();
                                    }
                                }
                            });
                            Button.onClick(() => {
                                if (this.item) {
                                    return this.item.isEnabled && this.item.action?.();
                                }
                            });
                            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
                        }, Button);
                        this.observeComponentCreation2((m2, n2) => {
                            If.create();
                            if (this.item?.symbolStyle) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((u2, v2) => {
                                        SymbolGlyph.create();
                                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                        SymbolGlyph.attributeModifier.bind(this)(this.item?.symbolStyle);
                                        SymbolGlyph.fontSize(`${ImageMenuItem.imageSize}vp`);
                                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                        SymbolGlyph.draggable(false);
                                        SymbolGlyph.focusable(this.item?.isEnabled);
                                        SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                    }, SymbolGlyph);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.observeComponentCreation2((o2, p2) => {
                                        If.create();
                                        if (Util.isSymbolResource(this.item.value)) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((s2, t2) => {
                                                    SymbolGlyph.create(this.item.value);
                                                    SymbolGlyph.fontSize(`${ImageMenuItem.imageSize}vp`);
                                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                    SymbolGlyph.draggable(false);
                                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                                    SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                                }, SymbolGlyph);
                                            });
                                        }
                                        else {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((q2, r2) => {
                                                    Image.create(this.item?.value);
                                                    Image.matchTextDirection(this.item?.value === PUBLIC_BACK ? true : false);
                                                    Image.width(ImageMenuItem.imageSize);
                                                    Image.draggable(false);
                                                    Image.height(ImageMenuItem.imageSize);
                                                    Image.focusable(this.item?.isEnabled);
                                                    Image.key(ImageMenuItem.focusablePrefix + this.index);
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
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    if (!If.canRetake(`ComposeTitleBar_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`)) {
                        this.observeComponentCreation2((h2, i2) => {
                            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
                            Button.id(`ComposeTitleBar_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`);
                            Button.accessibilityText(this.getAccessibilityReadText());
                            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
                            Button.accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription));
                            Button.enabled(this.item.isEnabled ? this.item.isEnabled : false);
                            Button.width(ImageMenuItem.imageHotZoneWidth);
                            Button.height(ImageMenuItem.imageHotZoneWidth);
                            Button.borderRadius(ImageMenuItem.buttonBorderRadius);
                            Button.foregroundColor(this.getFgColor());
                            Button.backgroundColor(this.getBgColor());
                            ViewStackProcessor.visualState('focused');
                            Button.border({
                                radius: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_corner_radius_clicked'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                width: ImageMenuItem.focusBorderWidth,
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
                            Button.onHover((l2) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnHover = l2;
                            });
                            Button.onKeyEvent((k2) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (k2.keyCode !== KeyCode.KEYCODE_ENTER &&
                                    k2.keyCode !== KeyCode.KEYCODE_SPACE) {
                                    return;
                                }
                                if (k2.type === KeyType.Down) {
                                    this.isOnClick = true;
                                }
                                if (k2.type === KeyType.Up) {
                                    this.isOnClick = false;
                                }
                            });
                            Button.onTouch((j2) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (j2.type === TouchType.Down) {
                                    this.isOnClick = true;
                                }
                                if (j2.type === TouchType.Up || j2.type === TouchType.Cancel) {
                                    this.isOnClick = false;
                                    if (this.fontSize >= this.minFontSize) {
                                        this.dialogController?.close();
                                    }
                                }
                            });
                            Button.onClick(() => {
                                if (this.item) {
                                    return this.item.isEnabled && this.item.action?.();
                                }
                            });
                        }, Button);
                        this.observeComponentCreation2((x1, y1) => {
                            If.create();
                            if (this.item?.symbolStyle) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((f2, g2) => {
                                        SymbolGlyph.create();
                                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                        SymbolGlyph.attributeModifier.bind(this)(this.item?.symbolStyle);
                                        SymbolGlyph.fontSize(`${ImageMenuItem.imageSize}vp`);
                                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                        SymbolGlyph.draggable(false);
                                        SymbolGlyph.focusable(this.item?.isEnabled);
                                        SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                    }, SymbolGlyph);
                                });
                            }
                            else {
                                this.ifElseBranchUpdateFunction(1, () => {
                                    this.observeComponentCreation2((z1, a2) => {
                                        If.create();
                                        if (Util.isSymbolResource(this.item.value)) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((d2, e2) => {
                                                    SymbolGlyph.create(this.item.value);
                                                    SymbolGlyph.fontSize(`${ImageMenuItem.imageSize}vp`);
                                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                    SymbolGlyph.draggable(false);
                                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                                    SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                                }, SymbolGlyph);
                                            });
                                        }
                                        else {
                                            this.ifElseBranchUpdateFunction(1, () => {
                                                this.observeComponentCreation2((b2, c2) => {
                                                    Image.create(this.item?.value);
                                                    Image.matchTextDirection(this.item?.value === PUBLIC_BACK ? true : false);
                                                    Image.width(ImageMenuItem.imageSize);
                                                    Image.draggable(false);
                                                    Image.height(ImageMenuItem.imageSize);
                                                    Image.focusable(this.item?.isEnabled);
                                                    Image.key(ImageMenuItem.focusablePrefix + this.index);
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
                });
            }
        }, If);
        If.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
ImageMenuItem.imageSize = 24;
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.focusablePrefix = 'Id-ComposeTitleBar-ImageMenuItem-';
class ComposeTitleBarDialog extends ViewPU {
    constructor(p1, q1, r1, s1 = -1, t1 = undefined, u1) {
        super(p1, r1, s1, u1);
        if (typeof t1 === 'function') {
            this.paramsGenerator_ = t1;
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
        this.__mainWindow = this.createStorageLink('mainWindow', undefined, 'mainWindow');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.setInitiallyProvidedValue(q1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(o1) {
        if (o1.itemComposeTitleDialog !== undefined) {
            this.itemComposeTitleDialog = o1.itemComposeTitleDialog;
        }
        if (o1.callbackId !== undefined) {
            this.callbackId = o1.callbackId;
        }
        if (o1.composeTitleBarDialog !== undefined) {
            this.composeTitleBarDialog = o1.composeTitleBarDialog;
        }
        if (o1.mainWindowStage !== undefined) {
            this.mainWindowStage = o1.mainWindowStage;
        }
        if (o1.controller !== undefined) {
            this.controller = o1.controller;
        }
        if (o1.minFontSize !== undefined) {
            this.minFontSize = o1.minFontSize;
        }
        if (o1.maxFontSize !== undefined) {
            this.maxFontSize = o1.maxFontSize;
        }
        if (o1.screenWidth !== undefined) {
            this.screenWidth = o1.screenWidth;
        }
        if (o1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = o1.verticalScreenLines;
        }
        if (o1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = o1.horizontalsScreenLines;
        }
        if (o1.fontSize !== undefined) {
            this.fontSize = o1.fontSize;
        }
        if (o1.maxLines !== undefined) {
            this.maxLines = o1.maxLines;
        }
        if (o1.cancel !== undefined) {
            this.cancel = o1.cancel;
        }
        if (o1.confirm !== undefined) {
            this.confirm = o1.confirm;
        }
    }
    updateStateVars(n1) {
    }
    purgeVariableDependenciesOnElmtId(m1) {
        this.__mainWindow.purgeDependencyOnElmtId(m1);
        this.__fontSize.purgeDependencyOnElmtId(m1);
        this.__maxLines.purgeDependencyOnElmtId(m1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(m1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(l1) {
        this.controller = l1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(k1) {
        this.__mainWindow.set(k1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(j1) {
        this.__fontSize.set(j1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(i1) {
        this.__maxLines.set(i1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(h1) {
        this.__windowStandardHeight.set(h1);
    }
    initialRender() {
        this.observeComponentCreation2((d, e) => {
            If.create();
            if (this.composeTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f1, g1) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Column);
                    this.observeComponentCreation2((v, w) => {
                        If.create();
                        if (this.itemComposeTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((d1, e1) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
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
                                this.observeComponentCreation2((x, y) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((b1, c1) => {
                                                SymbolGlyph.create(this.itemComposeTitleDialog.value);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
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
                                            this.observeComponentCreation2((z, a1) => {
                                                Image.create(this.itemComposeTitleDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
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
                    this.observeComponentCreation2((t, u) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((r, s) => {
                        Text.create(this.composeTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
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
                    this.observeComponentCreation2((p, q) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((f, g) => {
                        If.create();
                        if (this.itemComposeTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((n, o) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((h, i) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((l, m) => {
                                                SymbolGlyph.create(this.itemComposeTitleDialog.value);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((j, k) => {
                                                Image.create(this.itemComposeTitleDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
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
        let a = this.getUIContext().getHostContext();
        this.mainWindowStage = a.windowStage.getMainWindowSync();
        let b = this.mainWindowStage.getWindowProperties();
        let c = b.windowRect;
        if (px2vp(c.height) > this.screenWidth) {
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
