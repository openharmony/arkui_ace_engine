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
const PUBLIC_MORE = { 'id': -1, 'type': 40000, params: ['sys.symbol.dot_grid_2x2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 40000, params: ['sys.symbol.arrow_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
class ButtonGestureModifier {
    constructor(u11) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = u11;
    }
    applyGesture(r11) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            r11.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (r11) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            r11.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
export class SelectTitleBar extends ViewPU {
    constructor(k11, l11, m11, n11 = -1, o11 = undefined, p11) {
        super(k11, m11, n11, p11);
        if (typeof o11 === 'function') {
            this.paramsGenerator_ = o11;
        }
        this.__selected = new SynchedPropertySimpleOneWayPU(l11.selected, this, 'selected');
        this.options = [];
        this.menuItems = [];
        this.subtitle = '';
        this.badgeValue = 0;
        this.hidesBackButton = false;
        this.onSelected = () => { };
        this.messageDesc = '';
        this.__selectMaxWidth = new ObservedPropertySimplePU(0, this, 'selectMaxWidth');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(l11);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(j11) {
        if (j11.selected === undefined) {
            this.__selected.set(0);
        }
        if (j11.options !== undefined) {
            this.options = j11.options;
        }
        if (j11.menuItems !== undefined) {
            this.menuItems = j11.menuItems;
        }
        if (j11.subtitle !== undefined) {
            this.subtitle = j11.subtitle;
        }
        if (j11.badgeValue !== undefined) {
            this.badgeValue = j11.badgeValue;
        }
        if (j11.hidesBackButton !== undefined) {
            this.hidesBackButton = j11.hidesBackButton;
        }
        if (j11.onSelected !== undefined) {
            this.onSelected = j11.onSelected;
        }
        if (j11.messageDesc !== undefined) {
            this.messageDesc = j11.messageDesc;
        }
        if (j11.selectMaxWidth !== undefined) {
            this.selectMaxWidth = j11.selectMaxWidth;
        }
        if (j11.fontSize !== undefined) {
            this.fontSize = j11.fontSize;
        }
    }
    updateStateVars(i11) {
        this.__selected.reset(i11.selected);
    }
    purgeVariableDependenciesOnElmtId(h11) {
        this.__selected.purgeDependencyOnElmtId(h11);
        this.__selectMaxWidth.purgeDependencyOnElmtId(h11);
        this.__fontSize.purgeDependencyOnElmtId(h11);
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
    set selected(g11) {
        this.__selected.set(g11);
    }
    get selectMaxWidth() {
        return this.__selectMaxWidth.get();
    }
    set selectMaxWidth(f11) {
        this.__selectMaxWidth.set(f11);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(e11) {
        this.__fontSize.set(e11);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((x10, y10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(x10);
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.width('100%');
            Flex.height(SelectTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((a11, b11) => {
                let c11 = Number(b11.width);
                if (!this.hidesBackButton) {
                    c11 -= ImageMenuItem.imageHotZoneWidth;
                    c11 += SelectTitleBar.leftPadding;
                    c11 -= SelectTitleBar.leftPaddingWithBack;
                }
                if (this.menuItems.length > 0) {
                    let d11 = this.menuItems.length;
                    if (d11 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        c11 -= ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (d11 > 0) {
                        c11 -= ImageMenuItem.imageHotZoneWidth * d11;
                    }
                }
                if (this.badgeValue) {
                    this.selectMaxWidth = c11 - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding -
                    SelectTitleBar.rightPadding - SelectTitleBar.badgePadding;
                }
                else {
                    this.selectMaxWidth = c11 - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding;
                }
            });
            if (!y10) {
                Flex.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((v10, w10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v10);
            Row.create();
            Row.margin({ left: this.hidesBackButton ? { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_max_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } : { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            if (!w10) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((k10, l10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k10);
            If.create();
            if (!this.hidesBackButton) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation((p10, q10) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(p10);
                            if (q10) {
                                let r10 = new ImageMenuItem(this, { item: {
                                    value: PUBLIC_BACK,
                                    symbolValue: new SymbolGlyphModifier((PUBLIC_BACK)),
                                    isEnabled: true,
                                    action: () => this.getUIContext()?.getRouter()?.back()
                                }, index: -1 }, undefined, p10, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 109, col: 11 });
                                ViewPU.create(r10);
                                let s10 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            symbolValue: new SymbolGlyphModifier((PUBLIC_BACK)),
                                            isEnabled: true,
                                            action: () => this.getUIContext()?.getRouter()?.back()
                                        },
                                        index: -1
                                    };
                                };
                                r10.paramsGenerator_ = s10;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(p10, {});
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
            if (!l10) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((i10, j10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(i10);
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.selectMaxWidth });
            if (!j10) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((p9, q9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p9);
            If.create();
            if (this.badgeValue) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((g10, h10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(g10);
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
                        if (!h10) {
                            Badge.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((e10, f10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e10);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        Row.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_elements_margin_horizontal_l'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
                        if (!f10) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((c10, d10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c10);
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
                        if (!d10) {
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
                    this.observeComponentCreation((w9, x9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(w9);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        if (!x9) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((u9, v9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(u9);
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
                        if (!v9) {
                            Select.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Select.pop();
                    Row.pop();
                });
            }
            if (!q9) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((f9, g9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f9);
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((n9, o9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(n9);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        Row.margin({ left: SelectTitleBar.subtitleLeftPadding });
                        if (!o9) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((l9, m9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(l9);
                        Text.create(this.subtitle);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.selectMaxWidth });
                        Text.offset({ y: -4 });
                        if (!m9) {
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
            if (!g9) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Column.pop();
        Row.pop();
        this.observeComponentCreation((u8, v8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u8);
            If.create();
            if (this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation((z8, a9) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(z8);
                            if (a9) {
                                let b9 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + SelectTitleBar.instanceCount++ }, undefined, z8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 188, col: 9 });
                                ViewPU.create(b9);
                                let c9 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + SelectTitleBar.instanceCount++
                                    };
                                };
                                b9.paramsGenerator_ = c9;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(z8, {});
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
            if (!v8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Flex.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    aboutToAppear() {
        let m8 = getContext().resourceManager;
        this.messageDesc = m8?.getStringByNameSync('selecttitlebar_accessibility_message_desc');
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
    constructor(c8, d8, e8, f8 = -1, g8 = undefined, h8) {
        super(c8, e8, f8, h8);
        if (typeof g8 === 'function') {
            this.paramsGenerator_ = g8;
        }
        this.menuItems = [];
        this.item = {
            value: PUBLIC_MORE,
            symbolValue: new SymbolGlyphModifier(PUBLIC_MORE),
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(d8.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let i8 = new SelectTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    selectTitleDialog: this.item,
                    selectTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 252, col: 14 });
                i8.setController(this.dialogController);
                ViewPU.create(i8);
                let j8 = () => {
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
                i8.paramsGenerator_ = j8;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(d8);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b8) {
        if (b8.menuItems !== undefined) {
            this.menuItems = b8.menuItems;
        }
        if (b8.item !== undefined) {
            this.item = b8.item;
        }
        if (b8.index !== undefined) {
            this.index = b8.index;
        }
        if (b8.minFontSize !== undefined) {
            this.minFontSize = b8.minFontSize;
        }
        if (b8.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = b8.isFollowingSystemFontScale;
        }
        if (b8.maxFontScale !== undefined) {
            this.maxFontScale = b8.maxFontScale;
        }
        if (b8.systemFontScale !== undefined) {
            this.systemFontScale = b8.systemFontScale;
        }
        if (b8.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = b8.firstFocusableIndex;
        }
        if (b8.isPopupShown !== undefined) {
            this.isPopupShown = b8.isPopupShown;
        }
        if (b8.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = b8.isMoreIconOnFocus;
        }
        if (b8.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = b8.isMoreIconOnHover;
        }
        if (b8.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = b8.isMoreIconOnClick;
        }
        if (b8.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (b8.dialogController !== undefined) {
            this.dialogController = b8.dialogController;
        }
        if (b8.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = b8.buttonGestureModifier;
        }
    }
    updateStateVars(a8) {
        this.__fontSize.reset(a8.fontSize);
    }
    purgeVariableDependenciesOnElmtId(z7) {
        this.__isPopupShown.purgeDependencyOnElmtId(z7);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(z7);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(z7);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(z7);
        this.__fontSize.purgeDependencyOnElmtId(z7);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(z7);
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
    set isPopupShown(y7) {
        this.__isPopupShown.set(y7);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(x7) {
        this.__isMoreIconOnFocus.set(x7);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(w7) {
        this.__isMoreIconOnHover.set(w7);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(v7) {
        this.__isMoreIconOnClick.set(v7);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u7) {
        this.__fontSize.set(u7);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(t7) {
        this.__buttonGestureModifier.set(t7);
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
            let s7 = this.getUIContext();
            this.isFollowingSystemFontScale = s7.isFollowingSystemFontScale();
            this.maxFontScale = s7.getMaxFontScale();
        }
        catch (p7) {
            let q7 = p7.code;
            let r7 = p7.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${q7}, message: ${r7}`);
        }
        this.menuItems.forEach((n7, o7) => {
            if (n7.isEnabled && this.firstFocusableIndex === -1 &&
                o7 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                this.firstFocusableIndex = this.index * 1000 + o7 + 1;
            }
        });
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let l7 = this.getUIContext();
        this.systemFontScale = l7.getHostContext()?.config?.fontSizeScale ?? 1;
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
        this.observeComponentCreation((j7, k7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j7);
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
            if (!k7) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((h7, i7) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h7);
            Row.create();
            if (!i7) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((j5, k5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j5);
            If.create();
            if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((t6, u6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(t6);
                        ForEach.create();
                        const v6 = (x6, y6) => {
                            const z6 = x6;
                            {
                                this.observeComponentCreation((b7, c7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(b7);
                                    if (c7) {
                                        let d7 = new ImageMenuItem(this, { item: z6, index: this.index * 1000 + y6 + 1 }, undefined, b7, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 321, col: 13 });
                                        ViewPU.create(d7);
                                        let e7 = () => {
                                            return {
                                                item: z6,
                                                index: this.index * 1000 + y6 + 1
                                            };
                                        };
                                        d7.paramsGenerator_ = e7;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(b7, {});
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            }
                        };
                        this.forEachUpdateFunction(t6, this.menuItems, v6, undefined, true, false);
                        if (!u6) {
                            ForEach.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((d6, e6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d6);
                        ForEach.create();
                        const f6 = (h6, i6) => {
                            const j6 = h6;
                            {
                                this.observeComponentCreation((l6, m6) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(l6);
                                    if (m6) {
                                        let n6 = new ImageMenuItem(this, { item: j6, index: this.index * 1000 + i6 + 1 }, undefined, l6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 326, col: 15 });
                                        ViewPU.create(n6);
                                        let o6 = () => {
                                            return {
                                                item: j6,
                                                index: this.index * 1000 + i6 + 1
                                            };
                                        };
                                        n6.paramsGenerator_ = o6;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(l6, {});
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            }
                        };
                        this.forEachUpdateFunction(d6, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), f6, undefined, true, false);
                        if (!e6) {
                            ForEach.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    ForEach.pop();
                    this.observeComponentCreation((r5, s5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(r5);
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
                        Button.onHover((c6) => this.isMoreIconOnHover = c6);
                        Button.onKeyEvent((b6) => {
                            if (b6.keyCode !== KeyCode.KEYCODE_ENTER && b6.keyCode !== KeyCode.KEYCODE_SPACE) {
                                return;
                            }
                            if (b6.type === KeyType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (b6.type === KeyType.Up) {
                                this.isMoreIconOnClick = false;
                            }
                        });
                        Button.onTouch((a6) => {
                            if (a6.type === TouchType.Down) {
                                this.isMoreIconOnClick = true;
                            }
                            if (a6.type === TouchType.Up || a6.type === TouchType.Cancel) {
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
                            onStateChange: (z5) => {
                                this.isPopupShown = z5.isVisible;
                                if (!z5.isVisible) {
                                    this.isMoreIconOnClick = false;
                                }
                            }
                        });
                        if (!s5) {
                            Button.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((p5, q5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(p5);
                        SymbolGlyph.create(PUBLIC_MORE);
                        SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.focusable(true);
                        if (!q5) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Button.pop();
                });
            }
            if (!k5) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    popupBuilder(m4 = null) {
        this.observeComponentCreation((d5, e5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d5);
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex);
            });
            if (!e5) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((p4, q4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p4);
            ForEach.create();
            const r4 = (t4, u4) => {
                const v4 = t4;
                {
                    this.observeComponentCreation((x4, y4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(x4);
                        if (y4) {
                            let z4 = new ImageMenuItem(this, { item: v4, index: this.index * 1000 +
                            CollapsibleMenuSection.maxCountOfVisibleItems + u4, isPopup: true }, undefined, x4, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 410, col: 11 });
                            ViewPU.create(z4);
                            let a5 = () => {
                                return {
                                    item: v4,
                                    index: this.index * 1000 +
                                    CollapsibleMenuSection.maxCountOfVisibleItems + u4,
                                    isPopup: true
                                };
                            };
                            z4.paramsGenerator_ = a5;
                        }
                        else {
                            this.updateStateVarsOfChildByElmtId(x4, {});
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                }
            };
            this.forEachUpdateFunction(p4, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), r4, undefined, true, false);
            if (!q4) {
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
    constructor(c4, d4, e4, f4 = -1, g4 = undefined, h4) {
        super(c4, e4, f4, h4);
        if (typeof g4 === 'function') {
            this.paramsGenerator_ = g4;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(d4.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let i4 = new SelectTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    selectTitleDialog: this.item,
                    selectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 445, col: 14 });
                i4.setController(this.dialogController);
                ViewPU.create(i4);
                let j4 = () => {
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
                i4.paramsGenerator_ = j4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(d4);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b4) {
        if (b4.item !== undefined) {
            this.item = b4.item;
        }
        if (b4.index !== undefined) {
            this.index = b4.index;
        }
        if (b4.minFontSize !== undefined) {
            this.minFontSize = b4.minFontSize;
        }
        if (b4.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = b4.isFollowingSystemFontScale;
        }
        if (b4.maxFontScale !== undefined) {
            this.maxFontScale = b4.maxFontScale;
        }
        if (b4.systemFontScale !== undefined) {
            this.systemFontScale = b4.systemFontScale;
        }
        if (b4.isPopup !== undefined) {
            this.isPopup = b4.isPopup;
        }
        if (b4.isOnFocus !== undefined) {
            this.isOnFocus = b4.isOnFocus;
        }
        if (b4.isOnHover !== undefined) {
            this.isOnHover = b4.isOnHover;
        }
        if (b4.isOnClick !== undefined) {
            this.isOnClick = b4.isOnClick;
        }
        if (b4.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (b4.dialogController !== undefined) {
            this.dialogController = b4.dialogController;
        }
        if (b4.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = b4.buttonGestureModifier;
        }
    }
    updateStateVars(a4) {
        this.__fontSize.reset(a4.fontSize);
    }
    purgeVariableDependenciesOnElmtId(z3) {
        this.__isOnFocus.purgeDependencyOnElmtId(z3);
        this.__isOnHover.purgeDependencyOnElmtId(z3);
        this.__isOnClick.purgeDependencyOnElmtId(z3);
        this.__fontSize.purgeDependencyOnElmtId(z3);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(z3);
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
    set isOnFocus(y3) {
        this.__isOnFocus.set(y3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(x3) {
        this.__isOnHover.set(x3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(w3) {
        this.__isOnClick.set(w3);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(v3) {
        this.__fontSize.set(v3);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(u3) {
        this.__buttonGestureModifier.set(u3);
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
            let t3 = this.getUIContext();
            this.isFollowingSystemFontScale = t3.isFollowingSystemFontScale();
            this.maxFontScale = t3.getMaxFontScale();
        }
        catch (q3) {
            let r3 = q3.code;
            let s3 = q3.message;
            hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${r3}, message: ${s3}`);
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        let p3 = this.getUIContext();
        this.systemFontScale = p3.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(this.systemFontScale, this.maxFontScale);
    }
    toStringFormat(k3) {
        if (typeof k3 === 'string') {
            return k3;
        }
        else if (typeof k3 === 'undefined') {
            return '';
        }
        else {
            let l3 = '';
            try {
                l3 = getContext()?.resourceManager?.getStringSync(k3);
            }
            catch (m3) {
                let n3 = m3?.code;
                let o3 = m3?.message;
                hilog.error(0x3900, 'Ace', `Faild to SelectTitleBar toStringFormat,code: ${n3},message:${o3}`);
            }
            return l3;
        }
    }
    getAccessibilityReadText() {
        if (this.item.value === PUBLIC_BACK) {
            return this.toStringFormat({ 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        else if (this.item.value === PUBLIC_MORE) {
            return this.toStringFormat({ 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
        }
        else if (this.item.accessibilityText) {
            return this.toStringFormat(this.item.accessibilityText);
        }
        else if (this.item.label) {
            return this.toStringFormat(this.item.label);
        }
        return ' ';
    }
    onPlaceChildren(f3, g3, h3) {
        g3.forEach((j3) => {
            j3.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((u2, v2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u2);
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
            Button.onHover((e3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = e3;
            });
            Button.onKeyEvent((d3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (d3.keyCode !== KeyCode.KEYCODE_ENTER && d3.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (d3.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (d3.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((c3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (c3.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (c3.type === TouchType.Up || c3.type === TouchType.Cancel) {
                    this.isOnClick = false;
                    if (this.fontSize >= this.minFontSize && this.isPopup === false) {
                        this.dialogController?.close();
                    }
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
            Button.gestureModifier(ObservedObject.GetRawObject(this.buttonGestureModifier));
            if (!v2) {
                Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((k2, l2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k2);
            If.create();
            if (this.item.symbolValue) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((s2, t2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s2);
                        SymbolGlyph.create();
                        SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                        SymbolGlyph.attributeModifier.bind(this)(this.item.symbolValue);
                        SymbolGlyph.fontSize(ImageMenuItem.imageSize);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(this.item?.isEnabled);
                        SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                        if (!t2) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((o2, p2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o2);
                        Image.create(this.item.value);
                        Image.draggable(false);
                        Image.width(ImageMenuItem.imageSize);
                        Image.height(ImageMenuItem.imageSize);
                        Image.focusable(this.item.isEnabled);
                        Image.key(ImageMenuItem.focusablePrefix + this.index);
                        Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!p2) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            if (!l2) {
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
    constructor(a2, b2, c2, d2 = -1, e2 = undefined, f2) {
        super(a2, c2, d2, f2);
        if (typeof e2 === 'function') {
            this.paramsGenerator_ = e2;
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
        this.setInitiallyProvidedValue(b2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z1) {
        if (z1.selectTitleDialog !== undefined) {
            this.selectTitleDialog = z1.selectTitleDialog;
        }
        if (z1.callbackId !== undefined) {
            this.callbackId = z1.callbackId;
        }
        if (z1.selectTitleBarDialog !== undefined) {
            this.selectTitleBarDialog = z1.selectTitleBarDialog;
        }
        if (z1.mainWindowStage !== undefined) {
            this.mainWindowStage = z1.mainWindowStage;
        }
        if (z1.controller !== undefined) {
            this.controller = z1.controller;
        }
        if (z1.minFontSize !== undefined) {
            this.minFontSize = z1.minFontSize;
        }
        if (z1.maxFontSize !== undefined) {
            this.maxFontSize = z1.maxFontSize;
        }
        if (z1.screenWidth !== undefined) {
            this.screenWidth = z1.screenWidth;
        }
        if (z1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = z1.verticalScreenLines;
        }
        if (z1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = z1.horizontalsScreenLines;
        }
        if (z1.fontSize !== undefined) {
            this.fontSize = z1.fontSize;
        }
        if (z1.maxLines !== undefined) {
            this.maxLines = z1.maxLines;
        }
        if (z1.cancel !== undefined) {
            this.cancel = z1.cancel;
        }
        if (z1.confirm !== undefined) {
            this.confirm = z1.confirm;
        }
    }
    updateStateVars(y1) {
    }
    purgeVariableDependenciesOnElmtId(x1) {
        this.__mainWindow.purgeDependencyOnElmtId(x1);
        this.__fontSize.purgeDependencyOnElmtId(x1);
        this.__maxLines.purgeDependencyOnElmtId(x1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(x1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(w1) {
        this.controller = w1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(v1) {
        this.__mainWindow.set(v1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u1) {
        this.__fontSize.set(u1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(t1) {
        this.__maxLines.set(t1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(s1) {
        this.__windowStandardHeight.set(s1);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((e, f) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            if (this.selectTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((q1, r1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(q1);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!r1) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((f1, g1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(f1);
                        If.create();
                        if (this.selectTitleDialog.symbolValue) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((o1, p1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(o1);
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.selectTitleDialog.symbolValue);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.selectTitleDialog?.isEnabled);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    if (!p1) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else if (this.selectTitleDialog.value) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((k1, l1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(k1);
                                    Image.create(this.selectTitleDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!l1) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                        if (!g1) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((d1, e1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d1);
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        if (!e1) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((b1, c1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b1);
                        Text.create(this.selectTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!c1) {
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
                    this.observeComponentCreation((u, v) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(u);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                        if (!v) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((j, k) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(j);
                        If.create();
                        if (this.selectTitleDialog.symbolValue) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((s, t) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(s);
                                    SymbolGlyph.create();
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.attributeModifier.bind(this)(this.selectTitleDialog.symbolValue);
                                    SymbolGlyph.fontSize(IMAGE_SIZE);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.selectTitleDialog?.isEnabled);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    if (!t) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else if (this.selectTitleDialog.value) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((o, p) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(o);
                                    Image.create(this.selectTitleDialog.value);
                                    Image.width(IMAGE_SIZE);
                                    Image.height(IMAGE_SIZE);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!p) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                        if (!k) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    Column.pop();
                });
            }
            if (!f) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
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
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export default {
SelectTitleBar: SelectTitleBar,
IconResource: IconResource,
};
