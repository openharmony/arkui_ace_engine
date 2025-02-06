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
const hilog = requireNapi('hilog');
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;
const PUBLIC_BACK = { 'id': -1, 'type': 40000, params: ['sys.symbol.arrow_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_MORE = { 'id': -1, 'type': 40000, params: ['sys.symbol.dot_grid_2x2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const RESOURCE_TYPE_SYMBOL = 40000;
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
class ButtonGestureModifier {
    constructor(h9) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = h9;
    }
    applyGesture(g9) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            g9.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (g9) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            g9.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class SelectTitleBar extends ViewPU {
    constructor(a9, b9, c9, d9 = -1, e9 = undefined, f9) {
        super(a9, c9, d9, f9);
        if (typeof e9 === 'function') {
            this.paramsGenerator_ = e9;
        }
        this.__selected = new SynchedPropertySimpleOneWayPU(b9.selected, this, 'selected');
        this.options = [];
        this.menuItems = [];
        this.subtitle = '';
        this.badgeValue = 0;
        this.hidesBackButton = false;
        this.messageDesc = '';
        this.onSelected = () => { };
        this.__selectMaxWidth = new ObservedPropertySimplePU(0, this, 'selectMaxWidth');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(b9);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z8) {
        if (z8.selected === undefined) {
            this.__selected.set(0);
        }
        if (z8.options !== undefined) {
            this.options = z8.options;
        }
        if (z8.menuItems !== undefined) {
            this.menuItems = z8.menuItems;
        }
        if (z8.subtitle !== undefined) {
            this.subtitle = z8.subtitle;
        }
        if (z8.badgeValue !== undefined) {
            this.badgeValue = z8.badgeValue;
        }
        if (z8.hidesBackButton !== undefined) {
            this.hidesBackButton = z8.hidesBackButton;
        }
        if (z8.messageDesc !== undefined) {
            this.messageDesc = z8.messageDesc;
        }
        if (z8.onSelected !== undefined) {
            this.onSelected = z8.onSelected;
        }
        if (z8.selectMaxWidth !== undefined) {
            this.selectMaxWidth = z8.selectMaxWidth;
        }
        if (z8.fontSize !== undefined) {
            this.fontSize = z8.fontSize;
        }
    }
    updateStateVars(y8) {
        this.__selected.reset(y8.selected);
    }
    purgeVariableDependenciesOnElmtId(x8) {
        this.__selected.purgeDependencyOnElmtId(x8);
        this.__selectMaxWidth.purgeDependencyOnElmtId(x8);
        this.__fontSize.purgeDependencyOnElmtId(x8);
    }
    aboutToBeDeleted() {
        this.__selected.aboutToBeDeleted();
        this.__selectMaxWidth.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get selected() {
        return this.__selected.get();
    }
    set selected(w8) {
        this.__selected.set(w8);
    }
    get selectMaxWidth() {
        return this.__selectMaxWidth.get();
    }
    set selectMaxWidth(v8) {
        this.__selectMaxWidth.set(v8);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u8) {
        this.__fontSize.set(u8);
    }
    initialRender() {
        this.observeComponentCreation2((o8, p8) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.width('100%');
            Flex.height(SelectTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((q8, r8) => {
                let s8 = Number(r8.width);
                if (!this.hidesBackButton) {
                    s8 -= ImageMenuItem.imageHotZoneWidth;
                    s8 += SelectTitleBar.leftPadding;
                    s8 -= SelectTitleBar.leftPaddingWithBack;
                }
                if (this.menuItems !== undefined) {
                    let t8 = this.menuItems.length;
                    if (t8 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        s8 -= ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (t8 > 0) {
                        s8 -= ImageMenuItem.imageHotZoneWidth * t8;
                    }
                }
                if (this.badgeValue) {
                    this.selectMaxWidth = s8 - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding -
                    SelectTitleBar.rightPadding - SelectTitleBar.badgePadding;
                }
                else {
                    this.selectMaxWidth = s8 - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding;
                }
            });
        }, Flex);
        this.observeComponentCreation2((m8, n8) => {
            Row.create();
            Row.margin({ left: this.hidesBackButton ? { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
        }, Row);
        this.observeComponentCreation2((g8, h8) => {
            If.create();
            if (!this.hidesBackButton) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((i8, j8) => {
                            if (j8) {
                                let k8 = new ImageMenuItem(this, { item: {
                                    value: '',
                                    symbolStyle: new SymbolGlyphModifier(PUBLIC_BACK),
                                    isEnabled: true,
                                    label: getContext()?.resourceManager?.getStringByNameSync('icon_back'),
                                    action: () => this.getUIContext()?.getRouter()?.back()
                                }, index: -1 }, undefined, i8, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 105, col: 11 });
                                ViewPU.create(k8);
                                let l7 = () => {
                                    return {
                                        item: {
                                            value: '',
                                            symbolStyle: new SymbolGlyphModifier(PUBLIC_BACK),
                                            isEnabled: true,
                                            label: getContext()?.resourceManager?.getStringByNameSync('icon_back'),
                                            action: () => this.getUIContext()?.getRouter()?.back()
                                        },
                                        index: -1
                                    };
                                };
                                k8.paramsGenerator_ = l7;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(i8, {});
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((e8, f8) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.selectMaxWidth });
        }, Column);
        this.observeComponentCreation2((s7, t7) => {
            If.create();
            if (this.badgeValue) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c8, d8) => {
                        Badge.create({
                            count: this.badgeValue,
                            position: BadgePosition.Right,
                            style: {
                                badgeColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                borderColor: { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_emphasize'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                borderWidth: 0
                            }
                        });
                        Badge.accessibilityGroup(true);
                        Badge.accessibilityLevel('no');
                    }, Badge);
                    this.observeComponentCreation2((a8, b8) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        Row.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
                    }, Row);
                    this.observeComponentCreation2((y7, z7) => {
                        Select.create(this.options);
                        Select.selected(this.selected);
                        Select.value(this.selected >= 0 && this.selected < this.options.length ?
                        this.options[this.selected].value : '');
                        Select.font({ size: this.hidesBackButton && !this.subtitle
                            ? { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline7'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
                        Select.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Select.backgroundColor(Color.Transparent);
                        Select.onSelect(this.onSelected);
                        Select.constraintSize({ maxWidth: this.selectMaxWidth });
                        Select.offset({ x: -4 });
                        Select.accessibilityLevel('yes');
                        Select.accessibilityDescription(this.messageDesc.replace('%d', this.badgeValue.toString()));
                    }, Select);
                    Select.pop();
                    Row.pop();
                    Badge.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((w7, x7) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((u7, v7) => {
                        Select.create(this.options);
                        Select.selected(this.selected);
                        Select.value(this.selected >= 0 && this.selected < this.options.length ?
                        this.options[this.selected].value : '');
                        Select.font({ size: this.hidesBackButton && !this.subtitle
                            ? { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline7'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
                        Select.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Select.backgroundColor(Color.Transparent);
                        Select.onSelect(this.onSelected);
                        Select.constraintSize({ maxWidth: this.selectMaxWidth });
                        Select.offset({ x: -4 });
                    }, Select);
                    Select.pop();
                    Row.pop();
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((m7, n7) => {
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((q7, r7) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        Row.margin({ left: SelectTitleBar.subtitleLeftPadding });
                    }, Row);
                    this.observeComponentCreation2((o7, p7) => {
                        Text.create(this.subtitle);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.selectMaxWidth });
                        Text.offset({ y: -4 });
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
        this.observeComponentCreation2((g7, h7) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((i7, j7) => {
                            if (j7) {
                                let k7 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + SelectTitleBar.instanceCount++ }, undefined, i7, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 185, col: 9 });
                                ViewPU.create(k7);
                                let f7 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + SelectTitleBar.instanceCount++
                                    };
                                };
                                k7.paramsGenerator_ = f7;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(i7, {});
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
    aboutToAppear() {
        try {
            let o10 = getContext().resourceManager;
            this.messageDesc =
                o10?.getPluralStringByNameSync('selecttitlebar_accessibility_message_desc_new', this.badgeValue);
        }
        catch (l10) {
            let m10 = l10.code;
            let n10 = l10.message;
            hilog.error(0x3900, 'Ace', `Faild to getPluralStringByNameSync,cause, code: ${m10}, message: ${n10}`);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
SelectTitleBar.badgeSize = 16;
SelectTitleBar.totalHeight = 56;
SelectTitleBar.leftPadding = 24;
SelectTitleBar.leftPaddingWithBack = 12;
SelectTitleBar.rightPadding = 24;
SelectTitleBar.badgePadding = 16;
SelectTitleBar.subtitleLeftPadding = 4;
SelectTitleBar.instanceCount = 0;
class CollapsibleMenuSection extends ViewPU {
    constructor(x6, y6, z6, a7 = -1, b7 = undefined, c7) {
        super(x6, z6, a7, c7);
        if (typeof b7 === 'function') {
            this.paramsGenerator_ = b7;
        }
        this.menuItems = [];
        this.item = {
            symbolStyle: new SymbolGlyphModifier(PUBLIC_MORE),
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(y6.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let d7 = new SelectTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    selectTitleDialog: this.item,
                    selectTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 254, col: 14 });
                d7.setController(this.dialogController);
                ViewPU.create(d7);
                let e7 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        selectTitleDialog: this.item,
                        selectTitleBarDialog: this.item.label ? this.item.label : '',
                        fontSize: this.fontSize
                    };
                };
                d7.paramsGenerator_ = e7;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(y6);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(w6) {
        if (w6.menuItems !== undefined) {
            this.menuItems = w6.menuItems;
        }
        if (w6.item !== undefined) {
            this.item = w6.item;
        }
        if (w6.index !== undefined) {
            this.index = w6.index;
        }
        if (w6.minFontSize !== undefined) {
            this.minFontSize = w6.minFontSize;
        }
        if (w6.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = w6.isFollowingSystemFontScale;
        }
        if (w6.maxFontScale !== undefined) {
            this.maxFontScale = w6.maxFontScale;
        }
        if (w6.systemFontScale !== undefined) {
            this.systemFontScale = w6.systemFontScale;
        }
        if (w6.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = w6.firstFocusableIndex;
        }
        if (w6.isPopupShown !== undefined) {
            this.isPopupShown = w6.isPopupShown;
        }
        if (w6.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = w6.isMoreIconOnFocus;
        }
        if (w6.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = w6.isMoreIconOnHover;
        }
        if (w6.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = w6.isMoreIconOnClick;
        }
        if (w6.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (w6.dialogController !== undefined) {
            this.dialogController = w6.dialogController;
        }
        if (w6.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = w6.buttonGestureModifier;
        }
    }
    updateStateVars(v6) {
        this.__fontSize.reset(v6.fontSize);
    }
    purgeVariableDependenciesOnElmtId(u6) {
        this.__isPopupShown.purgeDependencyOnElmtId(u6);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(u6);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(u6);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(u6);
        this.__fontSize.purgeDependencyOnElmtId(u6);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(u6);
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
    set isPopupShown(t6) {
        this.__isPopupShown.set(t6);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(s6) {
        this.__isMoreIconOnFocus.set(s6);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(r6) {
        this.__isMoreIconOnHover.set(r6);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(q6) {
        this.__isMoreIconOnClick.set(q6);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(p6) {
        this.__fontSize.set(p6);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(o6) {
        this.__buttonGestureModifier.set(o6);
    }
    getMoreIconFgColor() {
        return this.isMoreIconOnClick
            ? { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon_pressed'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_icon'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
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
            let n6 = this.getUIContext();
            this.isFollowingSystemFontScale = n6.isFollowingSystemFontScale();
            this.maxFontScale = n6.getMaxFontScale();
        }
        catch (k6) {
            let l6 = k6.code;
            let m6 = k6.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${l6}, message: ${m6}`);
        }
        this.menuItems.forEach((i6, j6) => {
            if (i6.isEnabled && this.firstFocusableIndex === -1 &&
                j6 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                this.firstFocusableIndex = this.index * 1000 + j6 + 1;
            }
        });
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let h6 = this.getUIContext();
        this.systemFontScale = h6.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        this.observeComponentCreation2((f6, g6) => {
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((d6, e6) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((z4, a5) => {
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t5, u5) => {
                        ForEach.create();
                        const v5 = (w5, x5) => {
                            const y5 = w5;
                            {
                                this.observeComponentCreation2((z5, a6) => {
                                    if (a6) {
                                        let b6 = new ImageMenuItem(this, { item: y5, index: this.index * 1000 + x5 + 1 }, undefined, z5, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 324, col: 13 });
                                        ViewPU.create(b6);
                                        let c6 = () => {
                                            return {
                                                item: y5,
                                                index: this.index * 1000 + x5 + 1
                                            };
                                        };
                                        b6.paramsGenerator_ = c6;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(z5, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(t5, this.menuItems, v5, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((j5, k5) => {
                        ForEach.create();
                        const l5 = (m5, n5) => {
                            const o5 = m5;
                            {
                                this.observeComponentCreation2((p5, q5) => {
                                    if (q5) {
                                        let r5 = new ImageMenuItem(this, { item: o5, index: this.index * 1000 + n5 + 1 }, undefined, p5, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 329, col: 15 });
                                        ViewPU.create(r5);
                                        let s5 = () => {
                                            return {
                                                item: o5,
                                                index: this.index * 1000 + n5 + 1
                                            };
                                        };
                                        r5.paramsGenerator_ = s5;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(p5, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(j5, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), l5, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                    this.observeComponentCreation2((d5, e5) => {
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
                        Button.onHover((i5) => this.isMoreIconOnHover = i5);
                        Button.onKeyEvent((h5) => {
                            if (h5.keyCode !== KeyCode.KEYCODE_ENTER && h5.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (h5.type === KeyType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (h5.type === KeyType.Up) {
                                this.isMoreIconOnClick = false;
                            }
                        });
                        Button.onTouch((g5) => {
                            if (g5.type === TouchType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (g5.type === TouchType.Up || g5.type === TouchType.Cancel) {
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
                            onStateChange: (f5) => {
                                this.isPopupShown = f5.isVisible;
                                if (!f5.isVisible) {
                                    this.isMoreIconOnClick = false;
                                }
                            }
                        });
                    }, Button);
                    this.observeComponentCreation2((b5, c5) => {
                        SymbolGlyph.create(PUBLIC_MORE);
                        SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.focusable(true);
                    }, SymbolGlyph);
                    Button.pop();
                });
            }
        }, If);
        If.pop();
        Row.pop();
        Column.pop();
    }
    onPlaceChildren(v4, w4, x4) {
        w4.forEach((y4) => {
            y4.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    popupBuilder(i4 = null) {
        this.observeComponentCreation2((t4, u4) => {
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
            });
        }, Column);
        this.observeComponentCreation2((j4, k4) => {
            ForEach.create();
            const l4 = (m4, n4) => {
                const o4 = m4;
                {
                    this.observeComponentCreation2((p4, q4) => {
                        if (q4) {
                            let r4 = new ImageMenuItem(this, { item: o4, index: this.index * 1000 +
                            CollapsibleMenuSection.maxCountOfVisibleItems + n4, isPopup: false }, undefined, p4, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 420, col: 11 });
                            ViewPU.create(r4);
                            let s4 = () => {
                                return {
                                    item: o4,
                                    index: this.index * 1000 +
                                    CollapsibleMenuSection.maxCountOfVisibleItems + n4,
                                    isPopup: false
                                };
                            };
                            r4.paramsGenerator_ = s4;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(p4, {});
                        }
                    }, { name: 'ImageMenuItem' });
                }
            };
            this.forEachUpdateFunction(j4, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), l4, undefined, true, false);
        }, ForEach);
        ForEach.pop();
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
    constructor(a4, b4, c4, d4 = -1, e4 = undefined, f4) {
        super(a4, c4, d4, f4);
        if (typeof e4 === 'function') {
            this.paramsGenerator_ = e4;
        }
        this.item = {};
        this.index = 0;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.isPopup = true;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(b4.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let g4 = new SelectTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    selectTitleDialog: this.item,
                    selectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 454, col: 14 });
                g4.setController(this.dialogController);
                ViewPU.create(g4);
                let h4 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        selectTitleDialog: this.item,
                        selectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize
                    };
                };
                g4.paramsGenerator_ = h4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(b4);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z3) {
        if (z3.item !== undefined) {
            this.item = z3.item;
        }
        if (z3.index !== undefined) {
            this.index = z3.index;
        }
        if (z3.minFontSize !== undefined) {
            this.minFontSize = z3.minFontSize;
        }
        if (z3.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = z3.isFollowingSystemFontScale;
        }
        if (z3.maxFontScale !== undefined) {
            this.maxFontScale = z3.maxFontScale;
        }
        if (z3.systemFontScale !== undefined) {
            this.systemFontScale = z3.systemFontScale;
        }
        if (z3.isPopup !== undefined) {
            this.isPopup = z3.isPopup;
        }
        if (z3.isOnFocus !== undefined) {
            this.isOnFocus = z3.isOnFocus;
        }
        if (z3.isOnHover !== undefined) {
            this.isOnHover = z3.isOnHover;
        }
        if (z3.isOnClick !== undefined) {
            this.isOnClick = z3.isOnClick;
        }
        if (z3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (z3.dialogController !== undefined) {
            this.dialogController = z3.dialogController;
        }
        if (z3.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = z3.buttonGestureModifier;
        }
    }
    updateStateVars(y3) {
        this.__fontSize.reset(y3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(x3) {
        this.__isOnFocus.purgeDependencyOnElmtId(x3);
        this.__isOnHover.purgeDependencyOnElmtId(x3);
        this.__isOnClick.purgeDependencyOnElmtId(x3);
        this.__fontSize.purgeDependencyOnElmtId(x3);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(x3);
    }
    aboutToBeDeleted() {
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__buttonGestureModifier.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(w3) {
        this.__isOnFocus.set(w3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(v3) {
        this.__isOnHover.set(v3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(u3) {
        this.__isOnClick.set(u3);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(t3) {
        this.__fontSize.set(t3);
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
            let r3 = this.getUIContext();
            this.isFollowingSystemFontScale = r3.isFollowingSystemFontScale();
            this.maxFontScale = r3.getMaxFontScale();
        }
        catch (o3) {
            let p3 = o3.code;
            let q3 = o3.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${p3}, message: ${q3}`);
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let n3 = this.getUIContext();
        this.systemFontScale = n3.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    toStringFormat(i3) {
        if (typeof i3 === 'string') {
            return i3;
        }
        else if (typeof i3 === 'undefined') {
            return '';
        }
        else {
            let j3 = '';
            try {
                j3 = getContext()?.resourceManager?.getStringSync(i3);
            }
            catch (k3) {
                let l3 = k3?.code;
                let m3 = k3?.message;
                hilog.error(0x3900, 'Ace', `Faild to SelectTitleBar toStringFormat,code: ${l3},message:${m3}`);
            }
            return j3;
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
    onPlaceChildren(e3, f3, g3) {
        f3.forEach((h3) => {
            h3.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        this.observeComponentCreation2((y1, z1) => {
            If.create();
            if (this.isPopup) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z2, a3) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
                        Button.accessibilityText(this.getAccessibilityReadText());
                        Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
                        Button.accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription));
                        Button.width(ImageMenuItem.imageHotZoneWidth);
                        Button.height(ImageMenuItem.imageHotZoneWidth);
                        Button.borderRadius(ImageMenuItem.buttonBorderRadius);
                        Button.foregroundColor(this.getFgColor());
                        Button.backgroundColor(this.getBgColor());
                        Button.enabled(this.item.isEnabled ? this.item.isEnabled : false);
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
                            if (!this.item.isEnabled) {
                                return;
                            }
                            this.isOnFocus = true;
                        });
                        Button.onBlur(() => this.isOnFocus = false);
                        Button.onHover((d3) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            this.isOnHover = d3;
                        });
                        Button.onKeyEvent((c3) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            if (c3.keyCode !== KeyCode.KEYCODE_ENTER && c3.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (c3.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (c3.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Button.onTouch((b3) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            if (b3.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (b3.type === TouchType.Up || b3.type === TouchType.Cancel) {
                                this.isOnClick = false;
                                if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                                    this.dialogController?.close();
                                }
                            }
                        });
                        Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
                        Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
                    }, Button);
                    this.observeComponentCreation2((p2, q2) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((x2, y2) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                                    SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                    SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((r2, s2) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((v2, w2) => {
                                                SymbolGlyph.create(this.item.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.focusable(this.item?.isEnabled);
                                                SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((t2, u2) => {
                                                Image.create(this.item.value);
                                                Image.draggable(false);
                                                Image.width(ImageMenuItem.imageSize);
                                                Image.height(ImageMenuItem.imageSize);
                                                Image.focusable(this.item.isEnabled);
                                                Image.key(ImageMenuItem.focusablePrefix + this.index);
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
                    Button.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((k2, l2) => {
                        Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
                        Button.accessibilityText(this.getAccessibilityReadText());
                        Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
                        Button.accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription));
                        Button.width(ImageMenuItem.imageHotZoneWidth);
                        Button.height(ImageMenuItem.imageHotZoneWidth);
                        Button.borderRadius(ImageMenuItem.buttonBorderRadius);
                        Button.foregroundColor(this.getFgColor());
                        Button.backgroundColor(this.getBgColor());
                        Button.enabled(this.item.isEnabled ? this.item.isEnabled : false);
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
                            if (!this.item.isEnabled) {
                                return;
                            }
                            this.isOnFocus = true;
                        });
                        Button.onBlur(() => this.isOnFocus = false);
                        Button.onHover((o2) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            this.isOnHover = o2;
                        });
                        Button.onKeyEvent((n2) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            if (n2.keyCode !== KeyCode.KEYCODE_ENTER && n2.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (n2.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (n2.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Button.onTouch((m2) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            if (m2.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (m2.type === TouchType.Up || m2.type === TouchType.Cancel) {
                                this.isOnClick = false;
                                if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                                    this.dialogController?.close();
                                }
                            }
                        });
                        Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
                    }, Button);
                    this.observeComponentCreation2((a2, b2) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((i2, j2) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                                    SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                    SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((c2, d2) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((g2, h2) => {
                                                SymbolGlyph.create(this.item.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.focusable(this.item?.isEnabled);
                                                SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((e2, f2) => {
                                                Image.create(this.item.value);
                                                Image.draggable(false);
                                                Image.width(ImageMenuItem.imageSize);
                                                Image.height(ImageMenuItem.imageSize);
                                                Image.focusable(this.item.isEnabled);
                                                Image.key(ImageMenuItem.focusablePrefix + this.index);
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
                    Button.pop();
                });
            }
        }, If);
        If.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
ImageMenuItem.imageSize = '24vp';
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.focusablePrefix = 'Id-SelectTitleBar-ImageMenuItem-';
class SelectTitleBarDialog extends ViewPU {
    constructor(s1, t1, u1, v1 = -1, w1 = undefined, x1) {
        super(s1, u1, v1, x1);
        if (typeof w1 === 'function') {
            this.paramsGenerator_ = w1;
        }
        this.selectTitleDialog = {};
        this.callbackId = undefined;
        this.selectTitleBarDialog = '';
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
        this.setInitiallyProvidedValue(t1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r1) {
        if (r1.selectTitleDialog !== undefined) {
            this.selectTitleDialog = r1.selectTitleDialog;
        }
        if (r1.callbackId !== undefined) {
            this.callbackId = r1.callbackId;
        }
        if (r1.selectTitleBarDialog !== undefined) {
            this.selectTitleBarDialog = r1.selectTitleBarDialog;
        }
        if (r1.mainWindowStage !== undefined) {
            this.mainWindowStage = r1.mainWindowStage;
        }
        if (r1.controller !== undefined) {
            this.controller = r1.controller;
        }
        if (r1.minFontSize !== undefined) {
            this.minFontSize = r1.minFontSize;
        }
        if (r1.maxFontSize !== undefined) {
            this.maxFontSize = r1.maxFontSize;
        }
        if (r1.screenWidth !== undefined) {
            this.screenWidth = r1.screenWidth;
        }
        if (r1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = r1.verticalScreenLines;
        }
        if (r1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = r1.horizontalsScreenLines;
        }
        if (r1.fontSize !== undefined) {
            this.fontSize = r1.fontSize;
        }
        if (r1.maxLines !== undefined) {
            this.maxLines = r1.maxLines;
        }
        if (r1.cancel !== undefined) {
            this.cancel = r1.cancel;
        }
        if (r1.confirm !== undefined) {
            this.confirm = r1.confirm;
        }
    }
    updateStateVars(q1) {
    }
    purgeVariableDependenciesOnElmtId(p1) {
        this.__mainWindow.purgeDependencyOnElmtId(p1);
        this.__fontSize.purgeDependencyOnElmtId(p1);
        this.__maxLines.purgeDependencyOnElmtId(p1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(p1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(o1) {
        this.controller = o1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(n1) {
        this.__mainWindow.set(n1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(m1) {
        this.__fontSize.set(m1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(l1) {
        this.__maxLines.set(l1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(k1) {
        this.__windowStandardHeight.set(k1);
    }
    initialRender() {
        this.observeComponentCreation2((g, h) => {
            If.create();
            if (this.selectTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i1, j1) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Column);
                    this.observeComponentCreation2((y, z) => {
                        If.create();
                        if (this.selectTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((g1, h1) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.selectTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else if (this.selectTitleDialog.value) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((a1, b1) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.selectTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((e1, f1) => {
                                                SymbolGlyph.create(this.selectTitleDialog.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                                SymbolGlyph.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((c1, d1) => {
                                                Image.create(this.selectTitleDialog.value);
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
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((w, x) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((u, v) => {
                        Text.create(this.selectTitleBarDialog);
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
                    this.observeComponentCreation2((s, t) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((i, j) => {
                        If.create();
                        if (this.selectTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((q, r) => {
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.selectTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                }, SymbolGlyph);
                            });
                        }
                        else if (this.selectTitleDialog.value) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((k, l) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.selectTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((o, p) => {
                                                SymbolGlyph.create(this.selectTitleDialog.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((m, n) => {
                                                Image.create(this.selectTitleDialog.value);
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
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
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
        let d = this.getUIContext().getHostContext();
        this.mainWindowStage = d.windowStage.getMainWindowSync();
        let e = this.mainWindowStage.getWindowProperties();
        let f = e.windowRect;
        if (px2vp(f.height) > this.screenWidth) {
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
class Util {
    static isSymbolResource(b) {
        if (!Util.isResourceType(b)) {
            return false;
        }
        let c = b;
        return c.type == RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(a) {
        if (!a) {
            return false;
        }
        if (typeof a === 'string' || typeof a === 'undefined') {
            return false;
        }
        return true;
    }
}

export default {
    SelectTitleBar: SelectTitleBar,
};
