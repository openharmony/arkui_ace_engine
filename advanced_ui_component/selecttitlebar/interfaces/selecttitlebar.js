/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
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
    constructor(v12) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = v12;
    }
    applyGesture(s12) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            s12.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (s12) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            s12.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class SelectTitleBar extends ViewPU {
    constructor(l12, m12, n12, o12 = -1, p12 = undefined, q12) {
        super(l12, n12, o12, q12);
        if (typeof p12 === 'function') {
            this.paramsGenerator_ = p12;
        }
        this.__selected = new SynchedPropertySimpleOneWayPU(m12.selected, this, 'selected');
        this.options = [];
        this.menuItems = [];
        this.subtitle = '';
        this.badgeValue = 0;
        this.hidesBackButton = false;
        this.messageDesc = '';
        this.onSelected = () => { };
        this.__selectMaxWidth = new ObservedPropertySimplePU(0, this, 'selectMaxWidth');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(m12);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(k12) {
        if (k12.selected === undefined) {
            this.__selected.set(0);
        }
        if (k12.options !== undefined) {
            this.options = k12.options;
        }
        if (k12.menuItems !== undefined) {
            this.menuItems = k12.menuItems;
        }
        if (k12.subtitle !== undefined) {
            this.subtitle = k12.subtitle;
        }
        if (k12.badgeValue !== undefined) {
            this.badgeValue = k12.badgeValue;
        }
        if (k12.hidesBackButton !== undefined) {
            this.hidesBackButton = k12.hidesBackButton;
        }
        if (k12.messageDesc !== undefined) {
            this.messageDesc = k12.messageDesc;
        }
        if (k12.onSelected !== undefined) {
            this.onSelected = k12.onSelected;
        }
        if (k12.selectMaxWidth !== undefined) {
            this.selectMaxWidth = k12.selectMaxWidth;
        }
        if (k12.fontSize !== undefined) {
            this.fontSize = k12.fontSize;
        }
    }
    updateStateVars(j12) {
        this.__selected.reset(j12.selected);
    }
    purgeVariableDependenciesOnElmtId(i12) {
        this.__selected.purgeDependencyOnElmtId(i12);
        this.__selectMaxWidth.purgeDependencyOnElmtId(i12);
        this.__fontSize.purgeDependencyOnElmtId(i12);
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
    set selected(h12) {
        this.__selected.set(h12);
    }
    get selectMaxWidth() {
        return this.__selectMaxWidth.get();
    }
    set selectMaxWidth(g12) {
        this.__selectMaxWidth.set(g12);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(f12) {
        this.__fontSize.set(f12);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((y11, z11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y11);
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.width('100%');
            Flex.height(SelectTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((b12, c12) => {
                let d12 = Number(c12.width);
                if (!this.hidesBackButton) {
                    d12 -= ImageMenuItem.imageHotZoneWidth;
                    d12 += SelectTitleBar.leftPadding;
                    d12 -= SelectTitleBar.leftPaddingWithBack;
                }
                if (this.menuItems !== undefined) {
                    let e12 = this.menuItems.length;
                    if (e12 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        d12 -= ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (e12 > 0) {
                        d12 -= ImageMenuItem.imageHotZoneWidth * e12;
                    }
                }
                if (this.badgeValue) {
                    this.selectMaxWidth = d12 - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding -
                    SelectTitleBar.rightPadding - SelectTitleBar.badgePadding;
                }
                else {
                    this.selectMaxWidth = d12 - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding;
                }
            });
            if (!z11) {
                Flex.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((w11, x11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w11);
            Row.create();
            Row.margin({ left: this.hidesBackButton ? { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            if (!x11) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((l11, m11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(l11);
            If.create();
            if (!this.hidesBackButton) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation((q11, r11) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(q11);
                            if (r11) {
                                let s11 = new ImageMenuItem(this, { item: {
                                    value: '',
                                    symbolStyle: new SymbolGlyphModifier(PUBLIC_BACK),
                                    isEnabled: true,
                                    label: { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    action: () => this.getUIContext()?.getRouter()?.back()
                                }, index: -1 }, undefined, q11, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 105, col: 11 });
                                ViewPU.create(s11);
                                let t11 = () => {
                                    return {
                                        item: {
                                            value: '',
                                            symbolStyle: new SymbolGlyphModifier(PUBLIC_BACK),
                                            isEnabled: true,
                                            label: { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                            action: () => this.getUIContext()?.getRouter()?.back()
                                        },
                                        index: -1
                                    };
                                };
                                s11.paramsGenerator_ = t11;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(q11, {});
                            }
                            ViewStackProcessor.StopGetAccessRecording();
                        });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!m11) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((j11, k11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j11);
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.selectMaxWidth });
            if (!k11) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((q10, r10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q10);
            If.create();
            if (this.badgeValue) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((h11, i11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(h11);
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
                        if (!i11) {
                            Badge.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((f11, g11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(f11);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        Row.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
                        if (!g11) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((d11, e11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d11);
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
                        Select.accessibilityDescription(this.messageDesc.replace('%s', this.badgeValue.toString()));
                        if (!e11) {
                            Select.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Select.pop();
                    Row.pop();
                    Badge.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((x10, y10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(x10);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        if (!y10) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((v10, w10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(v10);
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
                        if (!w10) {
                            Select.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Select.pop();
                    Row.pop();
                });
            }
            if (!r10) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((g10, h10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g10);
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((o10, p10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o10);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        Row.margin({ left: SelectTitleBar.subtitleLeftPadding });
                        if (!p10) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((m10, n10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m10);
                        Text.create(this.subtitle);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.selectMaxWidth });
                        Text.offset({ y: -4 });
                        if (!n10) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!h10) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Column.pop();
        Row.pop();
        this.observeComponentCreation((v9, w9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v9);
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation((a10, b10) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(a10);
                            if (b10) {
                                let c10 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + SelectTitleBar.instanceCount++ }, undefined, a10, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 185, col: 9 });
                                ViewPU.create(c10);
                                let d10 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + SelectTitleBar.instanceCount++
                                    };
                                };
                                c10.paramsGenerator_ = d10;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(a10, {});
                            }
                            ViewStackProcessor.StopGetAccessRecording();
                        });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!w9) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Flex.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    aboutToAppear() {
        let n9 = getContext().resourceManager;
        this.messageDesc = n9?.getStringByNameSync('selecttitlebar_accessibility_message_desc');
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
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
    constructor(d9, e9, f9, g9 = -1, h9 = undefined, i9) {
        super(d9, f9, g9, i9);
        if (typeof h9 === 'function') {
            this.paramsGenerator_ = h9;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(e9.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let j9 = new SelectTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    selectTitleDialog: this.item,
                    selectTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 247, col: 14 });
                j9.setController(this.dialogController);
                ViewPU.create(j9);
                let k9 = () => {
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
                j9.paramsGenerator_ = k9;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(e9);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c9) {
        if (c9.menuItems !== undefined) {
            this.menuItems = c9.menuItems;
        }
        if (c9.item !== undefined) {
            this.item = c9.item;
        }
        if (c9.index !== undefined) {
            this.index = c9.index;
        }
        if (c9.minFontSize !== undefined) {
            this.minFontSize = c9.minFontSize;
        }
        if (c9.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = c9.isFollowingSystemFontScale;
        }
        if (c9.maxFontScale !== undefined) {
            this.maxFontScale = c9.maxFontScale;
        }
        if (c9.systemFontScale !== undefined) {
            this.systemFontScale = c9.systemFontScale;
        }
        if (c9.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = c9.firstFocusableIndex;
        }
        if (c9.isPopupShown !== undefined) {
            this.isPopupShown = c9.isPopupShown;
        }
        if (c9.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = c9.isMoreIconOnFocus;
        }
        if (c9.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = c9.isMoreIconOnHover;
        }
        if (c9.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = c9.isMoreIconOnClick;
        }
        if (c9.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (c9.dialogController !== undefined) {
            this.dialogController = c9.dialogController;
        }
        if (c9.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = c9.buttonGestureModifier;
        }
    }
    updateStateVars(b9) {
        this.__fontSize.reset(b9.fontSize);
    }
    purgeVariableDependenciesOnElmtId(a9) {
        this.__isPopupShown.purgeDependencyOnElmtId(a9);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(a9);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(a9);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(a9);
        this.__fontSize.purgeDependencyOnElmtId(a9);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(a9);
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
    set isPopupShown(z8) {
        this.__isPopupShown.set(z8);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(y8) {
        this.__isMoreIconOnFocus.set(y8);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(x8) {
        this.__isMoreIconOnHover.set(x8);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(w8) {
        this.__isMoreIconOnClick.set(w8);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(v8) {
        this.__fontSize.set(v8);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(u8) {
        this.__buttonGestureModifier.set(u8);
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
            let t8 = this.getUIContext();
            this.isFollowingSystemFontScale = t8.isFollowingSystemFontScale();
            this.maxFontScale = t8.getMaxFontScale();
        }
        catch (q8) {
            let r8 = q8.code;
            let s8 = q8.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${r8}, message: ${s8}`);
        }
        this.menuItems.forEach((o8, p8) => {
            if (o8.isEnabled && this.firstFocusableIndex === -1 &&
                p8 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                this.firstFocusableIndex = this.index * 1000 + p8 + 1;
            }
        });
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let m8 = this.getUIContext();
        this.systemFontScale = m8.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((k8, l8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k8);
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
            if (!l8) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((i8, j8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i8);
            Row.create();
            if (!j8) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((k6, l6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k6);
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((u7, v7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(u7);
                        ForEach.create();
                        const w7 = (y7, z7) => {
                            const a8 = y7;
                            {
                                this.observeComponentCreation((c8, d8) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(c8);
                                    if (d8) {
                                        let e8 = new ImageMenuItem(this, { item: a8, index: this.index * 1000 + z7 + 1 }, undefined, c8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 317, col: 13 });
                                        ViewPU.create(e8);
                                        let f8 = () => {
                                            return {
                                                item: a8,
                                                index: this.index * 1000 + z7 + 1
                                            };
                                        };
                                        e8.paramsGenerator_ = f8;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(c8, {});
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            }
                        };
                        this.forEachUpdateFunction(u7, this.menuItems, w7, undefined, true, false);
                        if (!v7) {
                            ForEach.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((e7, f7) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e7);
                        ForEach.create();
                        const g7 = (i7, j7) => {
                            const k7 = i7;
                            {
                                this.observeComponentCreation((m7, n7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(m7);
                                    if (n7) {
                                        let o7 = new ImageMenuItem(this, { item: k7, index: this.index * 1000 + j7 + 1 }, undefined, m7, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 322, col: 15 });
                                        ViewPU.create(o7);
                                        let p7 = () => {
                                            return {
                                                item: k7,
                                                index: this.index * 1000 + j7 + 1
                                            };
                                        };
                                        o7.paramsGenerator_ = p7;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(m7, {});
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            }
                        };
                        this.forEachUpdateFunction(e7, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), g7, undefined, true, false);
                        if (!f7) {
                            ForEach.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    ForEach.pop();
                    this.observeComponentCreation((s6, t6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s6);
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
                        Button.onHover((d7) => this.isMoreIconOnHover = d7);
                        Button.onKeyEvent((c7) => {
                            if (c7.keyCode !== KeyCode.KEYCODE_ENTER && c7.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (c7.type === KeyType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (c7.type === KeyType.Up) {
                                this.isMoreIconOnClick = false;
                            }
                        });
                        Button.onTouch((b7) => {
                            if (b7.type === TouchType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (b7.type === TouchType.Up || b7.type === TouchType.Cancel) {
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
                            onStateChange: (a7) => {
                                this.isPopupShown = a7.isVisible;
                                if (!a7.isVisible) {
                                    this.isMoreIconOnClick = false;
                                }
                            }
                        });
                        if (!t6) {
                            Button.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((q6, r6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(q6);
                        SymbolGlyph.create(PUBLIC_MORE);
                        SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.focusable(true);
                        if (!r6) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Button.pop();
                });
            }
            if (!l6) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    popupBuilder(n5 = null) {
        this.observeComponentCreation((e6, f6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e6);
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
            });
            if (!f6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((q5, r5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q5);
            ForEach.create();
            const s5 = (u5, v5) => {
                const w5 = u5;
                {
                    this.observeComponentCreation((y5, z5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(y5);
                        if (z5) {
                            let a6 = new ImageMenuItem(this, { item: w5, index: this.index * 1000 +
                            CollapsibleMenuSection.maxCountOfVisibleItems + v5, isPopup: true }, undefined, y5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 406, col: 11 });
                            ViewPU.create(a6);
                            let b6 = () => {
                                return {
                                    item: w5,
                                    index: this.index * 1000 +
                                    CollapsibleMenuSection.maxCountOfVisibleItems + v5,
                                    isPopup: true
                                };
                            };
                            a6.paramsGenerator_ = b6;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(y5, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                }
            };
            this.forEachUpdateFunction(q5, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), s5, undefined, true, false);
            if (!r5) {
                ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        ForEach.pop();
        Column.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
CollapsibleMenuSection.maxCountOfVisibleItems = 3;
CollapsibleMenuSection.focusPadding = 4;
CollapsibleMenuSection.marginsNum = 2;
class ImageMenuItem extends ViewPU {
    constructor(d5, e5, f5, g5 = -1, h5 = undefined, i5) {
        super(d5, f5, g5, i5);
        if (typeof h5 === 'function') {
            this.paramsGenerator_ = h5;
        }
        this.item = {};
        this.index = 0;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.isPopup = false;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(e5.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let j5 = new SelectTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    selectTitleDialog: this.item,
                    selectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 441, col: 14 });
                j5.setController(this.dialogController);
                ViewPU.create(j5);
                let k5 = () => {
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
                j5.paramsGenerator_ = k5;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(e5);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c5) {
        if (c5.item !== undefined) {
            this.item = c5.item;
        }
        if (c5.index !== undefined) {
            this.index = c5.index;
        }
        if (c5.minFontSize !== undefined) {
            this.minFontSize = c5.minFontSize;
        }
        if (c5.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = c5.isFollowingSystemFontScale;
        }
        if (c5.maxFontScale !== undefined) {
            this.maxFontScale = c5.maxFontScale;
        }
        if (c5.systemFontScale !== undefined) {
            this.systemFontScale = c5.systemFontScale;
        }
        if (c5.isPopup !== undefined) {
            this.isPopup = c5.isPopup;
        }
        if (c5.isOnFocus !== undefined) {
            this.isOnFocus = c5.isOnFocus;
        }
        if (c5.isOnHover !== undefined) {
            this.isOnHover = c5.isOnHover;
        }
        if (c5.isOnClick !== undefined) {
            this.isOnClick = c5.isOnClick;
        }
        if (c5.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (c5.dialogController !== undefined) {
            this.dialogController = c5.dialogController;
        }
        if (c5.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = c5.buttonGestureModifier;
        }
    }
    updateStateVars(b5) {
        this.__fontSize.reset(b5.fontSize);
    }
    purgeVariableDependenciesOnElmtId(a5) {
        this.__isOnFocus.purgeDependencyOnElmtId(a5);
        this.__isOnHover.purgeDependencyOnElmtId(a5);
        this.__isOnClick.purgeDependencyOnElmtId(a5);
        this.__fontSize.purgeDependencyOnElmtId(a5);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(a5);
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
    set isOnFocus(z4) {
        this.__isOnFocus.set(z4);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(y4) {
        this.__isOnHover.set(y4);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(x4) {
        this.__isOnClick.set(x4);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(w4) {
        this.__fontSize.set(w4);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(v4) {
        this.__buttonGestureModifier.set(v4);
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
            let u4 = this.getUIContext();
            this.isFollowingSystemFontScale = u4.isFollowingSystemFontScale();
            this.maxFontScale = u4.getMaxFontScale();
        }
        catch (r4) {
            let s4 = r4.code;
            let t4 = r4.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${s4}, message: ${t4}`);
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let q4 = this.getUIContext();
        this.systemFontScale = q4.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    toStringFormat(l4) {
        if (typeof l4 === 'string') {
            return l4;
        }
        else if (typeof l4 === 'undefined') {
            return '';
        }
        else {
            let m4 = '';
            try {
                m4 = getContext()?.resourceManager?.getStringSync(l4);
            }
            catch (n4) {
                let o4 = n4?.code;
                let p4 = n4?.message;
                hilog.error(0x3900, 'Ace', `Faild to SelectTitleBar toStringFormat,code: ${o4},message:${p4}`);
            }
            return m4;
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
    onPlaceChildren(g4, h4, i4) {
        h4.forEach((k4) => {
            k4.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((v3, w3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v3);
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.accessibilityText(this.getAccessibilityReadText());
            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
            Button.accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription));
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneWidth);
            Button.borderRadius(ImageMenuItem.buttonBorderRadius);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            Button.opacity(this.item.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity);
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
            Button.onHover((f4) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = f4;
            });
            Button.onKeyEvent((e4) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (e4.keyCode !== KeyCode.KEYCODE_ENTER && e4.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (e4.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (e4.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((d4) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (d4.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (d4.type === TouchType.Up || d4.type === TouchType.Cancel) {
                    this.isOnClick = false;
                    if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                        this.dialogController?.close();
                    }
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
            if (!w3) {
                Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((d3, e3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d3);
            If.create();
            if (this.item.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((t3, u3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(t3);
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.attributeModifier.bind(this)(this.item.symbolStyle);
                        SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(this.item?.isEnabled);
                        SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        if (!u3) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((h3, i3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(h3);
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((p3, q3) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(p3);
                                    SymbolGlyph.create(this.item.value);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                    SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                    if (!q3) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((l3, m3) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(l3);
                                    Image.create(this.item.value);
                                    Image.draggable(false);
                                    Image.width(ImageMenuItem.imageSize);
                                    Image.height(ImageMenuItem.imageSize);
                                    Image.focusable(this.item.isEnabled);
                                    Image.key(ImageMenuItem.focusablePrefix + this.index);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!m3) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        if (!i3) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                });
            }
            if (!e3) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Button.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}
ImageMenuItem.imageSize = '24vp';
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.disabledImageOpacity = 0.4;
ImageMenuItem.focusablePrefix = 'Id-SelectTitleBar-ImageMenuItem-';
class SelectTitleBarDialog extends ViewPU {
    constructor(t2, u2, v2, w2 = -1, x2 = undefined, y2) {
        super(t2, v2, w2, y2);
        if (typeof x2 === 'function') {
            this.paramsGenerator_ = x2;
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
        this.setInitiallyProvidedValue(u2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(s2) {
        if (s2.selectTitleDialog !== undefined) {
            this.selectTitleDialog = s2.selectTitleDialog;
        }
        if (s2.callbackId !== undefined) {
            this.callbackId = s2.callbackId;
        }
        if (s2.selectTitleBarDialog !== undefined) {
            this.selectTitleBarDialog = s2.selectTitleBarDialog;
        }
        if (s2.mainWindowStage !== undefined) {
            this.mainWindowStage = s2.mainWindowStage;
        }
        if (s2.controller !== undefined) {
            this.controller = s2.controller;
        }
        if (s2.minFontSize !== undefined) {
            this.minFontSize = s2.minFontSize;
        }
        if (s2.maxFontSize !== undefined) {
            this.maxFontSize = s2.maxFontSize;
        }
        if (s2.screenWidth !== undefined) {
            this.screenWidth = s2.screenWidth;
        }
        if (s2.verticalScreenLines !== undefined) {
            this.verticalScreenLines = s2.verticalScreenLines;
        }
        if (s2.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = s2.horizontalsScreenLines;
        }
        if (s2.fontSize !== undefined) {
            this.fontSize = s2.fontSize;
        }
        if (s2.maxLines !== undefined) {
            this.maxLines = s2.maxLines;
        }
        if (s2.cancel !== undefined) {
            this.cancel = s2.cancel;
        }
        if (s2.confirm !== undefined) {
            this.confirm = s2.confirm;
        }
    }
    updateStateVars(r2) {
    }
    purgeVariableDependenciesOnElmtId(q2) {
        this.__mainWindow.purgeDependencyOnElmtId(q2);
        this.__fontSize.purgeDependencyOnElmtId(q2);
        this.__maxLines.purgeDependencyOnElmtId(q2);
        this.__windowStandardHeight.purgeDependencyOnElmtId(q2);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(p2) {
        this.controller = p2;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(o2) {
        this.__mainWindow.set(o2);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(n2) {
        this.__fontSize.set(n2);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(m2) {
        this.__maxLines.set(m2);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(l2) {
        this.__windowStandardHeight.set(l2);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((h, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h);
            If.create();
            if (this.selectTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((j2, k2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(j2);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!k2) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((q1, r1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(q1);
                        If.create();
                        if (this.selectTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((h2, i2) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(h2);
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
                                    if (!i2) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else if (this.selectTitleDialog.value) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((v1, w1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(v1);
                                    If.create();
                                    if (Util.isSymbolResource(this.selectTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation((d2, e2) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(d2);
                                                SymbolGlyph.create(this.selectTitleDialog.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                                SymbolGlyph.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                                if (!e2) {
                                                    SymbolGlyph.pop();
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation((z1, a2) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(z1);
                                                Image.create(this.selectTitleDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
                                                Image.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                if (!a2) {
                                                    Image.pop();
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        });
                                    }
                                    if (!w1) {
                                        If.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                If.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                        if (!r1) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((o1, p1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o1);
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        if (!p1) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((m1, n1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m1);
                        Text.create(this.selectTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!n1) {
                            Text.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Text.pop();
                    Column.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((f1, g1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(f1);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                        if (!g1) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((m, n) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m);
                        If.create();
                        if (this.selectTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((d1, e1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(d1);
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
                                    if (!e1) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else if (this.selectTitleDialog.value) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((r, s) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(r);
                                    If.create();
                                    if (Util.isSymbolResource(this.selectTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation((z, a1) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(z);
                                                SymbolGlyph.create(this.selectTitleDialog.value);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.draggable(false);
                                                SymbolGlyph.focusable(this.selectTitleDialog.isEnabled);
                                                SymbolGlyph.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                                if (!a1) {
                                                    SymbolGlyph.pop();
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation((v, w) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(v);
                                                Image.create(this.selectTitleDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                if (!w) {
                                                    Image.pop();
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        });
                                    }
                                    if (!s) {
                                        If.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                If.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                        if (!n) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    Column.pop();
                });
            }
            if (!i) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
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
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
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
