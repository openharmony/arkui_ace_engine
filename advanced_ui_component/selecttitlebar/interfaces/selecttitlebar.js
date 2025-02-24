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
    constructor(n36) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = n36;
    }
    applyGesture(m36) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            m36.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (m36) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            m36.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class SelectTitleBar extends ViewPU {
    constructor(g36, h36, i36, j36 = -1, k36 = undefined, l36) {
        super(g36, i36, j36, l36);
        if (typeof k36 === 'function') {
            this.paramsGenerator_ = k36;
        }
        this.__selected = new SynchedPropertySimpleOneWayPU(h36.selected, this, 'selected');
        this.options = [];
        this.menuItems = [];
        this.subtitle = '';
        this.badgeValue = 0;
        this.hidesBackButton = false;
        this.messageDesc = '';
        this.onSelected = () => { };
        this.__selectMaxWidth = new ObservedPropertySimplePU(0, this, 'selectMaxWidth');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(h36);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(f36) {
        if (f36.selected === undefined) {
            this.__selected.set(0);
        }
        if (f36.options !== undefined) {
            this.options = f36.options;
        }
        if (f36.menuItems !== undefined) {
            this.menuItems = f36.menuItems;
        }
        if (f36.subtitle !== undefined) {
            this.subtitle = f36.subtitle;
        }
        if (f36.badgeValue !== undefined) {
            this.badgeValue = f36.badgeValue;
        }
        if (f36.hidesBackButton !== undefined) {
            this.hidesBackButton = f36.hidesBackButton;
        }
        if (f36.messageDesc !== undefined) {
            this.messageDesc = f36.messageDesc;
        }
        if (f36.onSelected !== undefined) {
            this.onSelected = f36.onSelected;
        }
        if (f36.selectMaxWidth !== undefined) {
            this.selectMaxWidth = f36.selectMaxWidth;
        }
        if (f36.fontSize !== undefined) {
            this.fontSize = f36.fontSize;
        }
    }
    updateStateVars(e36) {
        this.__selected.reset(e36.selected);
    }
    purgeVariableDependenciesOnElmtId(d36) {
        this.__selected.purgeDependencyOnElmtId(d36);
        this.__selectMaxWidth.purgeDependencyOnElmtId(d36);
        this.__fontSize.purgeDependencyOnElmtId(d36);
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
    set selected(c36) {
        this.__selected.set(c36);
    }
    get selectMaxWidth() {
        return this.__selectMaxWidth.get();
    }
    set selectMaxWidth(b36) {
        this.__selectMaxWidth.set(b36);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(a36) {
        this.__fontSize.set(a36);
    }
    initialRender() {
        this.observeComponentCreation2((u35, v35) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.width('100%');
            Flex.height(SelectTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((w35, x35) => {
                let y35 = Number(x35.width);
                if (!this.hidesBackButton) {
                    y35 -= ImageMenuItem.imageHotZoneWidth;
                    y35 += SelectTitleBar.leftPadding;
                    y35 -= SelectTitleBar.leftPaddingWithBack;
                }
                if (this.menuItems !== undefined) {
                    let z35 = this.menuItems.length;
                    if (z35 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        y35 -= ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (z35 > 0) {
                        y35 -= ImageMenuItem.imageHotZoneWidth * z35;
                    }
                }
                if (this.badgeValue) {
                    this.selectMaxWidth = y35 - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding -
                    SelectTitleBar.rightPadding - SelectTitleBar.badgePadding;
                }
                else {
                    this.selectMaxWidth = y35 - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding;
                }
            });
        }, Flex);
        this.observeComponentCreation2((s35, t35) => {
            Row.create();
            Row.margin({ left: this.hidesBackButton ? { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
        }, Row);
        this.observeComponentCreation2((m35, n35) => {
            If.create();
            if (!this.hidesBackButton) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((o35, p35) => {
                            if (p35) {
                                let q35 = new ImageMenuItem(this, { item: {
                                    value: '',
                                    symbolStyle: new SymbolGlyphModifier(PUBLIC_BACK),
                                    isEnabled: true,
                                    label: getContext()?.resourceManager?.getStringByNameSync('icon_back'),
                                    action: () => this.getUIContext()?.getRouter()?.back()
                                }, index: -1 }, undefined, o35, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 105, col: 11 });
                                ViewPU.create(q35);
                                let r35 = () => {
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
                                q35.paramsGenerator_ = r35;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o35, {});
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
        this.observeComponentCreation2((k35, l35) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.selectMaxWidth });
        }, Column);
        this.observeComponentCreation2((y34, z34) => {
            If.create();
            if (this.badgeValue) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i35, j35) => {
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
                    this.observeComponentCreation2((g35, h35) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        Row.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
                    }, Row);
                    this.observeComponentCreation2((e35, f35) => {
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
                    this.observeComponentCreation2((c35, d35) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((a35, b35) => {
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
        this.observeComponentCreation2((s34, t34) => {
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w34, x34) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        Row.margin({ left: SelectTitleBar.subtitleLeftPadding });
                    }, Row);
                    this.observeComponentCreation2((u34, v34) => {
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
        this.observeComponentCreation2((m34, n34) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((o34, p34) => {
                            if (p34) {
                                let q34 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + SelectTitleBar.instanceCount++ }, undefined, o34, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 185, col: 9 });
                                ViewPU.create(q34);
                                let r34 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + SelectTitleBar.instanceCount++
                                    };
                                };
                                q34.paramsGenerator_ = r34;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o34, {});
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
            let l34 = getContext().resourceManager;
            this.messageDesc =
                l34?.getPluralStringByNameSync('selecttitlebar_accessibility_message_desc_new', this.badgeValue);
        }
        catch (i34) {
            let j34 = i34.code;
            let k34 = i34.message;
            hilog.error(0x3900, 'Ace', `Faild to getPluralStringByNameSync,cause, code: ${j34}, message: ${k34}`);
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
    constructor(a34, b34, c34, d34 = -1, e34 = undefined, f34) {
        super(a34, c34, d34, f34);
        if (typeof e34 === 'function') {
            this.paramsGenerator_ = e34;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(b34.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let g34 = new SelectTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    selectTitleDialog: this.item,
                    selectTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 254, col: 14 });
                g34.setController(this.dialogController);
                ViewPU.create(g34);
                let h34 = () => {
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
                g34.paramsGenerator_ = h34;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(b34);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z33) {
        if (z33.menuItems !== undefined) {
            this.menuItems = z33.menuItems;
        }
        if (z33.item !== undefined) {
            this.item = z33.item;
        }
        if (z33.index !== undefined) {
            this.index = z33.index;
        }
        if (z33.minFontSize !== undefined) {
            this.minFontSize = z33.minFontSize;
        }
        if (z33.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = z33.isFollowingSystemFontScale;
        }
        if (z33.maxFontScale !== undefined) {
            this.maxFontScale = z33.maxFontScale;
        }
        if (z33.systemFontScale !== undefined) {
            this.systemFontScale = z33.systemFontScale;
        }
        if (z33.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = z33.firstFocusableIndex;
        }
        if (z33.isPopupShown !== undefined) {
            this.isPopupShown = z33.isPopupShown;
        }
        if (z33.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = z33.isMoreIconOnFocus;
        }
        if (z33.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = z33.isMoreIconOnHover;
        }
        if (z33.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = z33.isMoreIconOnClick;
        }
        if (z33.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (z33.dialogController !== undefined) {
            this.dialogController = z33.dialogController;
        }
        if (z33.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = z33.buttonGestureModifier;
        }
    }
    updateStateVars(y33) {
        this.__fontSize.reset(y33.fontSize);
    }
    purgeVariableDependenciesOnElmtId(x33) {
        this.__isPopupShown.purgeDependencyOnElmtId(x33);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(x33);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(x33);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(x33);
        this.__fontSize.purgeDependencyOnElmtId(x33);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(x33);
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
    set isPopupShown(w33) {
        this.__isPopupShown.set(w33);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(v33) {
        this.__isMoreIconOnFocus.set(v33);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(u33) {
        this.__isMoreIconOnHover.set(u33);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(t33) {
        this.__isMoreIconOnClick.set(t33);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(s33) {
        this.__fontSize.set(s33);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(r33) {
        this.__buttonGestureModifier.set(r33);
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
            let q33 = this.getUIContext();
            this.isFollowingSystemFontScale = q33.isFollowingSystemFontScale();
            this.maxFontScale = q33.getMaxFontScale();
        }
        catch (n33) {
            let o33 = n33.code;
            let p33 = n33.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${o33}, message: ${p33}`);
        }
        this.menuItems.forEach((l33, m33) => {
            if (l33.isEnabled && this.firstFocusableIndex === -1 &&
                m33 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                this.firstFocusableIndex = this.index * 1000 + m33 + 1;
            }
        });
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let k33 = this.getUIContext();
        this.systemFontScale = k33.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        this.observeComponentCreation2((i33, j33) => {
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((g33, h33) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((c32, d32) => {
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w32, x32) => {
                        ForEach.create();
                        const y32 = (z32, a33) => {
                            const b33 = z32;
                            {
                                this.observeComponentCreation2((c33, d33) => {
                                    if (d33) {
                                        let e33 = new ImageMenuItem(this, { item: b33, index: this.index * 1000 + a33 + 1 }, undefined, c33, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 324, col: 13 });
                                        ViewPU.create(e33);
                                        let f33 = () => {
                                            return {
                                                item: b33,
                                                index: this.index * 1000 + a33 + 1
                                            };
                                        };
                                        e33.paramsGenerator_ = f33;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(c33, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(w32, this.menuItems, y32, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((m32, n32) => {
                        ForEach.create();
                        const o32 = (p32, q32) => {
                            const r32 = p32;
                            {
                                this.observeComponentCreation2((s32, t32) => {
                                    if (t32) {
                                        let u32 = new ImageMenuItem(this, { item: r32, index: this.index * 1000 + q32 + 1 }, undefined, s32, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 329, col: 15 });
                                        ViewPU.create(u32);
                                        let v32 = () => {
                                            return {
                                                item: r32,
                                                index: this.index * 1000 + q32 + 1
                                            };
                                        };
                                        u32.paramsGenerator_ = v32;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(s32, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(m32, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), o32, undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                    this.observeComponentCreation2((g32, h32) => {
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
                        Button.onHover((l32) => this.isMoreIconOnHover = l32);
                        Button.onKeyEvent((k32) => {
                            if (k32.keyCode !== KeyCode.KEYCODE_ENTER && k32.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (k32.type === KeyType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (k32.type === KeyType.Up) {
                                this.isMoreIconOnClick = false;
                            }
                        });
                        Button.onTouch((j32) => {
                            if (j32.type === TouchType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (j32.type === TouchType.Up || j32.type === TouchType.Cancel) {
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
                            onStateChange: (i32) => {
                                this.isPopupShown = i32.isVisible;
                                if (!i32.isVisible) {
                                    this.isMoreIconOnClick = false;
                                }
                            }
                        });
                    }, Button);
                    this.observeComponentCreation2((e32, f32) => {
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
    onPlaceChildren(y31, z31, a32) {
        z31.forEach((b32) => {
            b32.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    popupBuilder(l31 = null) {
        this.observeComponentCreation2((w31, x31) => {
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
            });
        }, Column);
        this.observeComponentCreation2((m31, n31) => {
            ForEach.create();
            const o31 = (p31, q31) => {
                const r31 = p31;
                {
                    this.observeComponentCreation2((s31, t31) => {
                        if (t31) {
                            let u31 = new ImageMenuItem(this, { item: r31, index: this.index * 1000 +
                            CollapsibleMenuSection.maxCountOfVisibleItems + q31, isPopup: false }, undefined, s31, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 420, col: 11 });
                            ViewPU.create(u31);
                            let v31 = () => {
                                return {
                                    item: r31,
                                    index: this.index * 1000 +
                                    CollapsibleMenuSection.maxCountOfVisibleItems + q31,
                                    isPopup: false
                                };
                            };
                            u31.paramsGenerator_ = v31;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(s31, {});
                        }
                    }, { name: 'ImageMenuItem' });
                }
            };
            this.forEachUpdateFunction(m31, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), o31, undefined, true, false);
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
    constructor(d31, e31, f31, g31 = -1, h31 = undefined, i31) {
        super(d31, f31, g31, i31);
        if (typeof h31 === 'function') {
            this.paramsGenerator_ = h31;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(e31.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let j31 = new SelectTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    selectTitleDialog: this.item,
                    selectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/selecttitlebar.ets', line: 454, col: 14 });
                j31.setController(this.dialogController);
                ViewPU.create(j31);
                let k31 = () => {
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
                j31.paramsGenerator_ = k31;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(e31);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c31) {
        if (c31.item !== undefined) {
            this.item = c31.item;
        }
        if (c31.index !== undefined) {
            this.index = c31.index;
        }
        if (c31.minFontSize !== undefined) {
            this.minFontSize = c31.minFontSize;
        }
        if (c31.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = c31.isFollowingSystemFontScale;
        }
        if (c31.maxFontScale !== undefined) {
            this.maxFontScale = c31.maxFontScale;
        }
        if (c31.systemFontScale !== undefined) {
            this.systemFontScale = c31.systemFontScale;
        }
        if (c31.isPopup !== undefined) {
            this.isPopup = c31.isPopup;
        }
        if (c31.isOnFocus !== undefined) {
            this.isOnFocus = c31.isOnFocus;
        }
        if (c31.isOnHover !== undefined) {
            this.isOnHover = c31.isOnHover;
        }
        if (c31.isOnClick !== undefined) {
            this.isOnClick = c31.isOnClick;
        }
        if (c31.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (c31.dialogController !== undefined) {
            this.dialogController = c31.dialogController;
        }
        if (c31.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = c31.buttonGestureModifier;
        }
    }
    updateStateVars(b31) {
        this.__fontSize.reset(b31.fontSize);
    }
    purgeVariableDependenciesOnElmtId(a31) {
        this.__isOnFocus.purgeDependencyOnElmtId(a31);
        this.__isOnHover.purgeDependencyOnElmtId(a31);
        this.__isOnClick.purgeDependencyOnElmtId(a31);
        this.__fontSize.purgeDependencyOnElmtId(a31);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(a31);
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
    set isOnFocus(z30) {
        this.__isOnFocus.set(z30);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(y30) {
        this.__isOnHover.set(y30);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(x30) {
        this.__isOnClick.set(x30);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(w30) {
        this.__fontSize.set(w30);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(v30) {
        this.__buttonGestureModifier.set(v30);
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
            let u30 = this.getUIContext();
            this.isFollowingSystemFontScale = u30.isFollowingSystemFontScale();
            this.maxFontScale = u30.getMaxFontScale();
        }
        catch (r30) {
            let s30 = r30.code;
            let t30 = r30.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${s30}, message: ${t30}`);
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let q30 = this.getUIContext();
        this.systemFontScale = q30.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    toStringFormat(l30) {
        if (typeof l30 === 'string') {
            return l30;
        }
        else if (typeof l30 === 'undefined') {
            return '';
        }
        else {
            let m30 = '';
            try {
                m30 = getContext()?.resourceManager?.getStringSync(l30);
            }
            catch (n30) {
                let o30 = n30?.code;
                let p30 = n30?.message;
                hilog.error(0x3900, 'Ace', `Faild to SelectTitleBar toStringFormat,code: ${o30},message:${p30}`);
            }
            return m30;
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
    onPlaceChildren(h30, i30, j30) {
        i30.forEach((k30) => {
            k30.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        this.observeComponentCreation2((b29, c29) => {
            If.create();
            if (this.isPopup) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c30, d30) => {
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
                        Button.onHover((g30) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            this.isOnHover = g30;
                        });
                        Button.onKeyEvent((f30) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            if (f30.keyCode !== KeyCode.KEYCODE_ENTER && f30.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (f30.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (f30.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Button.onTouch((e30) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            if (e30.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (e30.type === TouchType.Up || e30.type === TouchType.Cancel) {
                                this.isOnClick = false;
                                if (this.fontSize >= this.minFontSize) {
                                    this.dialogController?.close();
                                }
                            }
                        });
                        Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
                        Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
                    }, Button);
                    this.observeComponentCreation2((s29, t29) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((a30, b30) => {
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
                                this.observeComponentCreation2((u29, v29) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((y29, z29) => {
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
                                            this.observeComponentCreation2((w29, x29) => {
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
                    this.observeComponentCreation2((n29, o29) => {
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
                        Button.onHover((r29) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            this.isOnHover = r29;
                        });
                        Button.onKeyEvent((q29) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            if (q29.keyCode !== KeyCode.KEYCODE_ENTER && q29.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (q29.type === KeyType.Down) {
                                this.isOnClick = true;
                            }
                            if (q29.type === KeyType.Up) {
                                this.isOnClick = false;
                            }
                        });
                        Button.onTouch((p29) => {
                            if (!this.item.isEnabled) {
                                return;
                            }
                            if (p29.type === TouchType.Down) {
                                this.isOnClick = true;
                            }
                            if (p29.type === TouchType.Up || p29.type === TouchType.Cancel) {
                                this.isOnClick = false;
                                if (this.fontSize >= this.minFontSize) {
                                    this.dialogController?.close();
                                }
                            }
                        });
                        Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
                    }, Button);
                    this.observeComponentCreation2((d29, e29) => {
                        If.create();
                        if (this.item.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((l29, m29) => {
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
                                this.observeComponentCreation2((f29, g29) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.item.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((j29, k29) => {
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
                                            this.observeComponentCreation2((h29, i29) => {
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
    constructor(v28, w28, x28, y28 = -1, z28 = undefined, a29) {
        super(v28, x28, y28, a29);
        if (typeof z28 === 'function') {
            this.paramsGenerator_ = z28;
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
        this.setInitiallyProvidedValue(w28);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u28) {
        if (u28.selectTitleDialog !== undefined) {
            this.selectTitleDialog = u28.selectTitleDialog;
        }
        if (u28.callbackId !== undefined) {
            this.callbackId = u28.callbackId;
        }
        if (u28.selectTitleBarDialog !== undefined) {
            this.selectTitleBarDialog = u28.selectTitleBarDialog;
        }
        if (u28.mainWindowStage !== undefined) {
            this.mainWindowStage = u28.mainWindowStage;
        }
        if (u28.controller !== undefined) {
            this.controller = u28.controller;
        }
        if (u28.minFontSize !== undefined) {
            this.minFontSize = u28.minFontSize;
        }
        if (u28.maxFontSize !== undefined) {
            this.maxFontSize = u28.maxFontSize;
        }
        if (u28.screenWidth !== undefined) {
            this.screenWidth = u28.screenWidth;
        }
        if (u28.verticalScreenLines !== undefined) {
            this.verticalScreenLines = u28.verticalScreenLines;
        }
        if (u28.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = u28.horizontalsScreenLines;
        }
        if (u28.fontSize !== undefined) {
            this.fontSize = u28.fontSize;
        }
        if (u28.maxLines !== undefined) {
            this.maxLines = u28.maxLines;
        }
        if (u28.cancel !== undefined) {
            this.cancel = u28.cancel;
        }
        if (u28.confirm !== undefined) {
            this.confirm = u28.confirm;
        }
    }
    updateStateVars(t28) {
    }
    purgeVariableDependenciesOnElmtId(s28) {
        this.__mainWindow.purgeDependencyOnElmtId(s28);
        this.__fontSize.purgeDependencyOnElmtId(s28);
        this.__maxLines.purgeDependencyOnElmtId(s28);
        this.__windowStandardHeight.purgeDependencyOnElmtId(s28);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(r28) {
        this.controller = r28;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(q28) {
        this.__mainWindow.set(q28);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(p28) {
        this.__fontSize.set(p28);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(o28) {
        this.__maxLines.set(o28);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(n28) {
        this.__windowStandardHeight.set(n28);
    }
    initialRender() {
        this.observeComponentCreation2((j27, k27) => {
            If.create();
            if (this.selectTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l28, m28) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Column);
                    this.observeComponentCreation2((b28, c28) => {
                        If.create();
                        if (this.selectTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((j28, k28) => {
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
                                this.observeComponentCreation2((d28, e28) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.selectTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((h28, i28) => {
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
                                            this.observeComponentCreation2((f28, g28) => {
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
                    this.observeComponentCreation2((z27, a28) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((x27, y27) => {
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
                    this.observeComponentCreation2((v27, w27) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((l27, m27) => {
                        If.create();
                        if (this.selectTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((t27, u27) => {
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
                                this.observeComponentCreation2((n27, o27) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.selectTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((r27, s27) => {
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
                                            this.observeComponentCreation2((p27, q27) => {
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
        let g27 = this.getUIContext().getHostContext();
        this.mainWindowStage = g27.windowStage.getMainWindowSync();
        let h27 = this.mainWindowStage.getWindowProperties();
        let i27 = h27.windowRect;
        if (px2vp(i27.height) > this.screenWidth) {
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
    static isSymbolResource(e27) {
        if (!Util.isResourceType(e27)) {
            return false;
        }
        let f27 = e27;
        return f27.type == RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(d27) {
        if (!d27) {
            return false;
        }
        if (typeof d27 === 'string' || typeof d27 === 'undefined') {
            return false;
        }
        return true;
    }
}

export default {
    SelectTitleBar: SelectTitleBar,
};
