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
    static isSymbolResource(t8) {
        if (!Util.isResourceType(t8)) {
            return false;
        }
        let u8 = t8;
        return u8.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(s8) {
        if (!s8) {
            return false;
        }
        if (typeof s8 === 'string' || typeof s8 === 'undefined') {
            return false;
        }
        return true;
    }
}
class ButtonGestureModifier {
    constructor(r8) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = r8;
    }
    applyGesture(q8) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            q8.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                if (q8) {
                    this.controller?.open();
                }
            })
                .onActionEnd(() => {
                this.controller?.close();
            }));
        }
        else {
            q8.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
class ComposeTitleBar extends ViewPU {
    constructor(k8, l8, m8, n8 = -1, o8 = undefined, p8) {
        super(k8, m8, n8, p8);
        if (typeof o8 === 'function') {
            this.paramsGenerator_ = o8;
        }
        this.item = undefined;
        this.title = '';
        this.subtitle = '';
        this.menuItems = [];
        this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, 'titleMaxWidth');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__uniqueId = new ObservedPropertySimplePU(-1, this, 'uniqueId');
        this.addProvidedVar('uniqueId', this.__uniqueId, false);
        this.setInitiallyProvidedValue(l8);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(j8) {
        if (j8.item !== undefined) {
            this.item = j8.item;
        }
        if (j8.title !== undefined) {
            this.title = j8.title;
        }
        if (j8.subtitle !== undefined) {
            this.subtitle = j8.subtitle;
        }
        if (j8.menuItems !== undefined) {
            this.menuItems = j8.menuItems;
        }
        if (j8.titleMaxWidth !== undefined) {
            this.titleMaxWidth = j8.titleMaxWidth;
        }
        if (j8.fontSize !== undefined) {
            this.fontSize = j8.fontSize;
        }
        if (j8.uniqueId !== undefined) {
            this.uniqueId = j8.uniqueId;
        }
    }
    updateStateVars(i8) {
    }
    purgeVariableDependenciesOnElmtId(h8) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(h8);
        this.__fontSize.purgeDependencyOnElmtId(h8);
        this.__uniqueId.purgeDependencyOnElmtId(h8);
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
    set titleMaxWidth(g8) {
        this.__titleMaxWidth.set(g8);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(f8) {
        this.__fontSize.set(f8);
    }
    get uniqueId() {
        return this.__uniqueId.get();
    }
    set uniqueId(e8) {
        this.__uniqueId.set(e8);
    }
    initialRender() {
        this.observeComponentCreation2((y7, z7) => {
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
            Flex.onAreaChange((a8, b8) => {
                let c8 = Number(b8.width);
                if (this.menuItems !== undefined) {
                    let d8 = this.menuItems.length;
                    if (d8 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        c8 = c8 - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (d8 > 0) {
                        c8 = c8 - ImageMenuItem.imageHotZoneWidth * d8;
                    }
                }
                this.titleMaxWidth = c8;
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
        this.observeComponentCreation2((w7, x7) => {
            Row.create();
            Row.margin({ left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
        }, Row);
        {
            this.observeComponentCreation2((s7, t7) => {
                if (t7) {
                    let u7 = new ImageMenuItem(this, {
                        item: {
                            value: PUBLIC_BACK,
                            isEnabled: true,
                            action: () => this.getUIContext()?.getRouter()?.back()
                        },
                        index: -1,
                        itemIndex: -1
                    }, undefined, s7, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 113, col: 9 });
                    ViewPU.create(u7);
                    let v7 = () => {
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
                    u7.paramsGenerator_ = v7;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(s7, {});
                }
            }, { name: 'ImageMenuItem' });
        }
        this.observeComponentCreation2((q7, r7) => {
            Row.create();
            Row.accessibilityGroup(true);
        }, Row);
        this.observeComponentCreation2((m7, n7) => {
            If.create();
            if (this.item !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o7, p7) => {
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
        this.observeComponentCreation2((k7, l7) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
        }, Column);
        this.observeComponentCreation2((e7, f7) => {
            If.create();
            if (this.title !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i7, j7) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((g7, h7) => {
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
        this.observeComponentCreation2((y6, z6) => {
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c7, d7) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((a7, b7) => {
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
        this.observeComponentCreation2((s6, t6) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((u6, v6) => {
                            if (v6) {
                                let w6 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ }, undefined, u6, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 170, col: 9 });
                                ViewPU.create(w6);
                                let x6 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + ComposeTitleBar.instanceCount++
                                    };
                                };
                                w6.paramsGenerator_ = x6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(u6, {});
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
    constructor(k6, l6, m6, n6 = -1, o6 = undefined, p6) {
        super(k6, m6, n6, p6);
        if (typeof o6 === 'function') {
            this.paramsGenerator_ = o6;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(l6.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let q6 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 221, col: 14 });
                q6.setController(this.dialogController);
                ViewPU.create(q6);
                let r6 = () => {
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
                q6.paramsGenerator_ = r6;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(l6);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(j6) {
        if (j6.menuItems !== undefined) {
            this.menuItems = j6.menuItems;
        }
        if (j6.item !== undefined) {
            this.item = j6.item;
        }
        if (j6.index !== undefined) {
            this.index = j6.index;
        }
        if (j6.minFontSize !== undefined) {
            this.minFontSize = j6.minFontSize;
        }
        if (j6.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = j6.isFollowingSystemFontScale;
        }
        if (j6.maxFontScale !== undefined) {
            this.maxFontScale = j6.maxFontScale;
        }
        if (j6.systemFontScale !== undefined) {
            this.systemFontScale = j6.systemFontScale;
        }
        if (j6.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = j6.firstFocusableIndex;
        }
        if (j6.isPopupShown !== undefined) {
            this.isPopupShown = j6.isPopupShown;
        }
        if (j6.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = j6.isMoreIconOnFocus;
        }
        if (j6.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = j6.isMoreIconOnHover;
        }
        if (j6.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = j6.isMoreIconOnClick;
        }
        if (j6.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (j6.dialogController !== undefined) {
            this.dialogController = j6.dialogController;
        }
        if (j6.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = j6.buttonGestureModifier;
        }
    }
    updateStateVars(i6) {
        this.__fontSize.reset(i6.fontSize);
    }
    purgeVariableDependenciesOnElmtId(h6) {
        this.__isPopupShown.purgeDependencyOnElmtId(h6);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(h6);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(h6);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(h6);
        this.__fontSize.purgeDependencyOnElmtId(h6);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(h6);
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
    set isPopupShown(g6) {
        this.__isPopupShown.set(g6);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(f6) {
        this.__isMoreIconOnFocus.set(f6);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(e6) {
        this.__isMoreIconOnHover.set(e6);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(d6) {
        this.__isMoreIconOnClick.set(d6);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(c6) {
        this.__fontSize.set(c6);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(b6) {
        this.__buttonGestureModifier.set(b6);
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
            let a6 = this.getUIContext();
            this.isFollowingSystemFontScale = a6.isFollowingSystemFontScale();
            this.maxFontScale = a6.getMaxFontScale();
        }
        catch (x5) {
            let y5 = x5.code;
            let z5 = x5.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${y5}, message: ${z5}`);
        }
        if (this.menuItems) {
            this.menuItems.forEach((v5, w5) => {
                if (v5.isEnabled && this.firstFocusableIndex == -1 &&
                    w5 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                    this.firstFocusableIndex = this.index * 1000 + w5 + 1;
                }
            });
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        try {
            let u5 = this.getUIContext();
            this.systemFontScale = u5.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (r5) {
            let s5 = r5.code;
            let t5 = r5.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${s5}, message: ${t5}`);
            return 1;
        }
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        this.observeComponentCreation2((p5, q5) => {
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((n5, o5) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((h4, i4) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j4, k4) => {
                        If.create();
                        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((d5, e5) => {
                                    ForEach.create();
                                    const f5 = (g5, h5) => {
                                        const i5 = g5;
                                        {
                                            this.observeComponentCreation2((j5, k5) => {
                                                if (k5) {
                                                    let l5 = new ImageMenuItem(this, { item: i5, index: this.index * 1000 + h5 + 1, itemIndex: h5 }, undefined, j5, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 301, col: 15 });
                                                    ViewPU.create(l5);
                                                    let m5 = () => {
                                                        return {
                                                            item: i5,
                                                            index: this.index * 1000 + h5 + 1,
                                                            itemIndex: h5
                                                        };
                                                    };
                                                    l5.paramsGenerator_ = m5;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(j5, {});
                                                }
                                            }, { name: 'ImageMenuItem' });
                                        }
                                    };
                                    this.forEachUpdateFunction(d5, this.menuItems, f5, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((t4, u4) => {
                                    ForEach.create();
                                    const v4 = (w4, x4) => {
                                        const y4 = w4;
                                        {
                                            this.observeComponentCreation2((z4, a5) => {
                                                if (a5) {
                                                    let b5 = new ImageMenuItem(this, { item: y4, index: this.index * 1000 + x4 + 1, itemIndex: x4 }, undefined, z4, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 306, col: 17 });
                                                    ViewPU.create(b5);
                                                    let c5 = () => {
                                                        return {
                                                            item: y4,
                                                            index: this.index * 1000 + x4 + 1,
                                                            itemIndex: x4
                                                        };
                                                    };
                                                    b5.paramsGenerator_ = c5;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(z4, {});
                                                }
                                            }, { name: 'ImageMenuItem' });
                                        }
                                    };
                                    this.forEachUpdateFunction(t4, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), v4, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                                this.observeComponentCreation2((n4, o4) => {
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
                                    Button.onHover((s4) => this.isMoreIconOnHover = s4);
                                    Button.onKeyEvent((r4) => {
                                        if (r4.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            r4.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (r4.type === KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (r4.type === KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((q4) => {
                                        if (q4.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (q4.type === TouchType.Up || q4.type === TouchType.Cancel) {
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
                                        onStateChange: (p4) => {
                                            this.isPopupShown = p4.isVisible;
                                            if (!p4.isVisible) {
                                                this.isMoreIconOnClick = false;
                                            }
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((l4, m4) => {
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
    popupBuilder(s3 = null) {
        this.observeComponentCreation2((f4, g4) => {
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth +
                CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix +
                    this.firstFocusableIndex);
            });
        }, Column);
        this.observeComponentCreation2((t3, u3) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((v3, w3) => {
                        ForEach.create();
                        const x3 = (y3, z3) => {
                            const a4 = y3;
                            {
                                this.observeComponentCreation2((b4, c4) => {
                                    if (c4) {
                                        let d4 = new ImageMenuItem(this, {
                                            item: a4, index: this.index * 1000 +
                                                CollapsibleMenuSection.maxCountOfVisibleItems + z3,
                                            isPopup: true
                                        }, undefined, b4, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 394, col: 13 });
                                        ViewPU.create(d4);
                                        let e4 = () => {
                                            return {
                                                item: a4,
                                                index: this.index * 1000 +
                                                    CollapsibleMenuSection.maxCountOfVisibleItems + z3,
                                                isPopup: true
                                            };
                                        };
                                        d4.paramsGenerator_ = e4;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(b4, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(v3, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), x3, undefined, true, false);
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
    constructor(k3, l3, m3, n3 = -1, o3 = undefined, p3) {
        super(k3, m3, n3, p3);
        if (typeof o3 === 'function') {
            this.paramsGenerator_ = o3;
        }
        this.item = {};
        this.index = 0;
        this.itemIndex = 0;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.isPopup = false;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(l3.fontSize, this, 'fontSize');
        this.__parentParentUniqueId = this.initializeConsume('uniqueId', 'parentParentUniqueId');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let q3 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 432, col: 14 });
                q3.setController(this.dialogController);
                ViewPU.create(q3);
                let r3 = () => {
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
                q3.paramsGenerator_ = r3;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(l3);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(j3) {
        if (j3.item !== undefined) {
            this.item = j3.item;
        }
        if (j3.index !== undefined) {
            this.index = j3.index;
        }
        if (j3.itemIndex !== undefined) {
            this.itemIndex = j3.itemIndex;
        }
        if (j3.minFontSize !== undefined) {
            this.minFontSize = j3.minFontSize;
        }
        if (j3.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = j3.isFollowingSystemFontScale;
        }
        if (j3.maxFontScale !== undefined) {
            this.maxFontScale = j3.maxFontScale;
        }
        if (j3.systemFontScale !== undefined) {
            this.systemFontScale = j3.systemFontScale;
        }
        if (j3.isPopup !== undefined) {
            this.isPopup = j3.isPopup;
        }
        if (j3.isOnFocus !== undefined) {
            this.isOnFocus = j3.isOnFocus;
        }
        if (j3.isOnHover !== undefined) {
            this.isOnHover = j3.isOnHover;
        }
        if (j3.isOnClick !== undefined) {
            this.isOnClick = j3.isOnClick;
        }
        if (j3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (j3.dialogController !== undefined) {
            this.dialogController = j3.dialogController;
        }
        if (j3.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = j3.buttonGestureModifier;
        }
    }
    updateStateVars(i3) {
        this.__fontSize.reset(i3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(h3) {
        this.__isOnFocus.purgeDependencyOnElmtId(h3);
        this.__isOnHover.purgeDependencyOnElmtId(h3);
        this.__isOnClick.purgeDependencyOnElmtId(h3);
        this.__fontSize.purgeDependencyOnElmtId(h3);
        this.__parentParentUniqueId.purgeDependencyOnElmtId(h3);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(h3);
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
    set isOnFocus(g3) {
        this.__isOnFocus.set(g3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(f3) {
        this.__isOnHover.set(f3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(e3) {
        this.__isOnClick.set(e3);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(d3) {
        this.__fontSize.set(d3);
    }
    get parentParentUniqueId() {
        return this.__parentParentUniqueId.get();
    }
    set parentParentUniqueId(c3) {
        this.__parentParentUniqueId.set(c3);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(b3) {
        this.__buttonGestureModifier.set(b3);
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
    toStringFormat(w2) {
        if (typeof w2 === 'string') {
            return w2;
        }
        else if (typeof w2 === 'undefined') {
            return '';
        }
        else {
            let x2 = '';
            try {
                x2 = getContext()?.resourceManager?.getStringSync(w2);
            }
            catch (y2) {
                let z2 = y2?.code;
                let a3 = y2?.message;
                hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBar toStringFormat,code: ${z2},message:${a3}`);
            }
            return x2;
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
    onPlaceChildren(s2, t2, u2) {
        t2.forEach((v2) => {
            v2.layout({ x: 0, y: 0 });
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
            let r2 = this.getUIContext();
            this.isFollowingSystemFontScale = r2.isFollowingSystemFontScale();
            this.maxFontScale = r2.getMaxFontScale();
        }
        catch (o2) {
            let p2 = o2.code;
            let q2 = o2.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${p2}, message: ${q2}`);
        }
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    decideFontScale() {
        try {
            let n2 = this.getUIContext();
            this.systemFontScale = n2.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (k2) {
            let l2 = k2.code;
            let m2 = k2.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${l2}, message: ${m2}`);
            return 1;
        }
    }
    initialRender() {
        this.observeComponentCreation2((f2, g2) => {
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
            Button.onHover((j2) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                this.isOnHover = j2;
            });
            Button.onKeyEvent((i2) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (i2.keyCode !== KeyCode.KEYCODE_ENTER &&
                    i2.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (i2.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (i2.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((h2) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (h2.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (h2.type === TouchType.Up || h2.type === TouchType.Cancel) {
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
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
        }, Button);
        this.observeComponentCreation2((v1, w1) => {
            If.create();
            if (this.item?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((d2, e2) => {
                        SymbolGlyph.create();
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
                    this.observeComponentCreation2((x1, y1) => {
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((b2, c2) => {
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
                                this.observeComponentCreation2((z1, a2) => {
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
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(`${IMAGE_SIZE}vp`);
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
                                                SymbolGlyph.fontSize(`${IMAGE_SIZE}vp`);
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
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(`${IMAGE_SIZE}vp`);
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
                                                SymbolGlyph.fontSize(`${IMAGE_SIZE}vp`);
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
