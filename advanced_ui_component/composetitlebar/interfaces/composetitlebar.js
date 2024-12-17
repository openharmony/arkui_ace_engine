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
const PUBLIC_MORE = { 'id': -1, 'type': 40000, params: ['sys.symbol.dot_grid_2x2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 40000, params: ['sys.symbol.arrow_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const RESOURCE_TYPE_SYMBOL = 40000;
class Util {
    static isSymbolResource(c13) {
        if (!Util.isResourceType(c13)) {
            return false;
        }
        let d13 = c13;
        return d13.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(b13) {
        if (!b13) {
            return false;
        }
        if (typeof b13 === 'string' || typeof b13 === 'undefined') {
            return false;
        }
        return true;
    }
}
class ButtonGestureModifier {
    constructor(a13) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = a13;
    }
    applyGesture(x12) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            x12.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (x12) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            x12.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
class ComposeTitleBar extends ViewPU {
    constructor(r12, s12, t12, u12 = -1, v12 = undefined, w12) {
        super(r12, t12, u12, w12);
        if (typeof v12 === 'function') {
            this.paramsGenerator_ = v12;
        }
        this.item = undefined;
        this.title = '';
        this.subtitle = '';
        this.menuItems = [];
        this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, 'titleMaxWidth');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(s12);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q12) {
        if (q12.item !== undefined) {
            this.item = q12.item;
        }
        if (q12.title !== undefined) {
            this.title = q12.title;
        }
        if (q12.subtitle !== undefined) {
            this.subtitle = q12.subtitle;
        }
        if (q12.menuItems !== undefined) {
            this.menuItems = q12.menuItems;
        }
        if (q12.titleMaxWidth !== undefined) {
            this.titleMaxWidth = q12.titleMaxWidth;
        }
        if (q12.fontSize !== undefined) {
            this.fontSize = q12.fontSize;
        }
    }
    updateStateVars(p12) {
    }
    purgeVariableDependenciesOnElmtId(o12) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(o12);
        this.__fontSize.purgeDependencyOnElmtId(o12);
    }
    aboutToBeDeleted() {
        this.__titleMaxWidth.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get titleMaxWidth() {
        return this.__titleMaxWidth.get();
    }
    set titleMaxWidth(n12) {
        this.__titleMaxWidth.set(n12);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(m12) {
        this.__fontSize.set(m12);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((f12, g12) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f12);
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.width('100%');
            Flex.height(ComposeTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((i12, j12) => {
                let k12 = Number(j12.width);
                if (this.menuItems !== undefined) {
                    let l12 = this.menuItems.length;
                    if (l12 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        k12 = k12 - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (l12 > 0) {
                        k12 = k12 - ImageMenuItem.imageHotZoneWidth * l12;
                    }
                }
                this.titleMaxWidth = k12;
                this.titleMaxWidth -= ComposeTitleBar.leftPadding;
                this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth;
                if (this.item !== undefined) {
                    this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
                    ComposeTitleBar.portraitImageSize +
                    ComposeTitleBar.portraitImageRightPadding;
                }
                this.titleMaxWidth -= ComposeTitleBar.rightPadding;
            });
            if (!g12) {
                Flex.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((d12, e12) => {
            ViewStackProcessor.StartGetAccessRecordingFor(d12);
            Row.create();
            Row.margin({ left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            if (!e12) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        {
            this.observeComponentCreation((x11, y11) => {
                ViewStackProcessor.StartGetAccessRecordingFor(x11);
                if (y11) {
                    let z11 = new ImageMenuItem(this, {
                        item: {
                            value: PUBLIC_BACK,
                            isEnabled: true,
                            action: () => this.getUIContext()?.getRouter()?.back()
                        }, index: -1
                    }, undefined, x11, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 112, col: 9 });
                    ViewPU.create(z11);
                    let a12 = () => {
                        return {
                            item: {
                                value: PUBLIC_BACK,
                                isEnabled: true,
                                action: () => this.getUIContext()?.getRouter()?.back()
                            },
                            index: -1
                        };
                    };
                    z11.paramsGenerator_ = a12;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(x11, {});
                }
                ViewStackProcessor.StopGetAccessRecording();
            });
        }
        this.observeComponentCreation((u11, v11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u11);
            Row.create();
            Row.accessibilityGroup(true);
            if (!v11) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((n11, o11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n11);
            If.create();
            if (this.item !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((s11, t11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s11);
                        Image.create(this.item.value);
                        Image.width(ComposeTitleBar.portraitImageSize);
                        Image.height(ComposeTitleBar.portraitImageSize);
                        Image.margin({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                        });
                        Image.focusable(false);
                        Image.borderRadius(ImageMenuItem.buttonBorderRadius);
                        if (!t11) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!o11) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((l11, m11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(l11);
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
            if (!m11) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((b11, c11) => {
            ViewStackProcessor.StartGetAccessRecordingFor(b11);
            If.create();
            if (this.title !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((j11, k11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(j11);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        if (!k11) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((h11, i11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(h11);
                        Text.create(this.title);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(this.subtitle !== undefined ? 1 : 2);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
                        if (!i11) {
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
            if (!c11) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((r10, s10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(r10);
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((z10, a11) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(z10);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        if (!a11) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((x10, y10) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(x10);
                        Text.create(this.subtitle);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
                        if (!y10) {
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
            if (!s10) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Column.pop();
        Row.pop();
        Row.pop();
        this.observeComponentCreation((g10, h10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(g10);
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation((l10, m10) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(l10);
                            if (m10) {
                                let n10 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ }, undefined, l10, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 167, col: 9 });
                                ViewPU.create(n10);
                                let o10 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + ComposeTitleBar.instanceCount++
                                    };
                                };
                                n10.paramsGenerator_ = o10;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l10, {});
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
            if (!h10) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Flex.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
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
    constructor(o9, p9, q9, r9 = -1, s9 = undefined, t9) {
        super(o9, q9, r9, t9);
        if (typeof s9 === 'function') {
            this.paramsGenerator_ = s9;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(p9.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let u9 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 218, col: 14 });
                u9.setController(this.dialogController);
                ViewPU.create(u9);
                let v9 = () => {
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
                u9.paramsGenerator_ = v9;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(p9);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(n9) {
        if (n9.menuItems !== undefined) {
            this.menuItems = n9.menuItems;
        }
        if (n9.item !== undefined) {
            this.item = n9.item;
        }
        if (n9.index !== undefined) {
            this.index = n9.index;
        }
        if (n9.minFontSize !== undefined) {
            this.minFontSize = n9.minFontSize;
        }
        if (n9.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = n9.isFollowingSystemFontScale;
        }
        if (n9.maxFontScale !== undefined) {
            this.maxFontScale = n9.maxFontScale;
        }
        if (n9.systemFontScale !== undefined) {
            this.systemFontScale = n9.systemFontScale;
        }
        if (n9.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = n9.firstFocusableIndex;
        }
        if (n9.isPopupShown !== undefined) {
            this.isPopupShown = n9.isPopupShown;
        }
        if (n9.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = n9.isMoreIconOnFocus;
        }
        if (n9.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = n9.isMoreIconOnHover;
        }
        if (n9.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = n9.isMoreIconOnClick;
        }
        if (n9.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (n9.dialogController !== undefined) {
            this.dialogController = n9.dialogController;
        }
        if (n9.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = n9.buttonGestureModifier;
        }
    }
    updateStateVars(m9) {
        this.__fontSize.reset(m9.fontSize);
    }
    purgeVariableDependenciesOnElmtId(l9) {
        this.__isPopupShown.purgeDependencyOnElmtId(l9);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(l9);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(l9);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(l9);
        this.__fontSize.purgeDependencyOnElmtId(l9);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(l9);
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
    set isPopupShown(k9) {
        this.__isPopupShown.set(k9);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(j9) {
        this.__isMoreIconOnFocus.set(j9);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(i9) {
        this.__isMoreIconOnHover.set(i9);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(h9) {
        this.__isMoreIconOnClick.set(h9);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(g9) {
        this.__fontSize.set(g9);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(f9) {
        this.__buttonGestureModifier.set(f9);
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
            let e9 = this.getUIContext();
            this.isFollowingSystemFontScale = e9.isFollowingSystemFontScale();
            this.maxFontScale = e9.getMaxFontScale();
        }
        catch (b9) {
            let c9 = b9.code;
            let d9 = b9.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${c9}, message: ${d9}`);
        }
        if (this.menuItems) {
            this.menuItems.forEach((z8, a9) => {
                if (z8.isEnabled && this.firstFocusableIndex == -1 &&
                    a9 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                    this.firstFocusableIndex = this.index * 1000 + a9 + 1;
                }
            });
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        try {
            let x8 = this.getUIContext();
            this.systemFontScale = x8.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (u8) {
            let v8 = u8.code;
            let w8 = u8.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${v8}, message: ${w8}`);
            return 1;
        }
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((s8, t8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s8);
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
            if (!t8) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((q8, r8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q8);
            Row.create();
            if (!r8) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((n6, o6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(n6);
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((s6, t6) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s6);
                        If.create();
                        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((c8, d8) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(c8);
                                    ForEach.create();
                                    const e8 = (g8, h8) => {
                                        const i8 = g8;
                                        {
                                            this.observeComponentCreation((k8, l8) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(k8);
                                                if (l8) {
                                                    let m8 = new ImageMenuItem(this, { item: i8, index: this.index * 1000 + h8 + 1 }, undefined, k8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 298, col: 15 });
                                                    ViewPU.create(m8);
                                                    let n8 = () => {
                                                        return {
                                                            item: i8,
                                                            index: this.index * 1000 + h8 + 1
                                                        };
                                                    };
                                                    m8.paramsGenerator_ = n8;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(k8, {});
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        }
                                    };
                                    this.forEachUpdateFunction(c8, this.menuItems, e8, undefined, true, false);
                                    if (!d8) {
                                        ForEach.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                ForEach.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((m7, n7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(m7);
                                    ForEach.create();
                                    const o7 = (q7, r7) => {
                                        const s7 = q7;
                                        {
                                            this.observeComponentCreation((u7, v7) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(u7);
                                                if (v7) {
                                                    let w7 = new ImageMenuItem(this, { item: s7, index: this.index * 1000 + r7 + 1 }, undefined, u7, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 303, col: 17 });
                                                    ViewPU.create(w7);
                                                    let x7 = () => {
                                                        return {
                                                            item: s7,
                                                            index: this.index * 1000 + r7 + 1
                                                        };
                                                    };
                                                    w7.paramsGenerator_ = x7;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(u7, {});
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        }
                                    };
                                    this.forEachUpdateFunction(m7, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), o7, undefined, true, false);
                                    if (!n7) {
                                        ForEach.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                ForEach.pop();
                                this.observeComponentCreation((a7, b7) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(a7);
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
                                    Button.onHover((l7) => this.isMoreIconOnHover = l7);
                                    Button.onKeyEvent((k7) => {
                                        if (k7.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            k7.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (k7.type === KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (k7.type === KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((j7) => {
                                        if (j7.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (j7.type === TouchType.Up || j7.type === TouchType.Cancel) {
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
                                        onStateChange: (i7) => {
                                            this.isPopupShown = i7.isVisible;
                                            if (!i7.isVisible) {
                                                this.isMoreIconOnClick = false;
                                            }
                                        }
                                    });
                                    if (!b7) {
                                        Button.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((y6, z6) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(y6);
                                    SymbolGlyph.create(PUBLIC_MORE);
                                    SymbolGlyph.fontSize(`${ImageMenuItem.imageSize}vp`);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(true);
                                    if (!z6) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Button.pop();
                            });
                        }
                        if (!t6) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!o6) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    popupBuilder(l5 = null) {
        this.observeComponentCreation((h6, i6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h6);
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth +
                CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix +
                this.firstFocusableIndex);
            });
            if (!i6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((o5, p5) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o5);
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((t5, u5) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(t5);
                        ForEach.create();
                        const v5 = (x5, y5) => {
                            const z5 = x5;
                            {
                                this.observeComponentCreation((b6, c6) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(b6);
                                    if (c6) {
                                        let d6 = new ImageMenuItem(this, {
                                            item: z5, index: this.index * 1000 +
                                            CollapsibleMenuSection.maxCountOfVisibleItems + y5,
                                            isPopup: true
                                        }, undefined, b6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 391, col: 13 });
                                        ViewPU.create(d6);
                                        let e6 = () => {
                                            return {
                                                item: z5,
                                                index: this.index * 1000 +
                                                CollapsibleMenuSection.maxCountOfVisibleItems + y5,
                                                isPopup: true
                                            };
                                        };
                                        d6.paramsGenerator_ = e6;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(b6, {});
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            }
                        };
                        this.forEachUpdateFunction(t5, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), v5, undefined, true, false);
                        if (!u5) {
                            ForEach.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    ForEach.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!p5) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
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
    constructor(b5, c5, d5, e5 = -1, f5 = undefined, g5) {
        super(b5, d5, e5, g5);
        if (typeof f5 === 'function') {
            this.paramsGenerator_ = f5;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(c5.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let h5 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 427, col: 14 });
                h5.setController(this.dialogController);
                ViewPU.create(h5);
                let i5 = () => {
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
                h5.paramsGenerator_ = i5;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(c5);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a5) {
        if (a5.item !== undefined) {
            this.item = a5.item;
        }
        if (a5.index !== undefined) {
            this.index = a5.index;
        }
        if (a5.minFontSize !== undefined) {
            this.minFontSize = a5.minFontSize;
        }
        if (a5.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = a5.isFollowingSystemFontScale;
        }
        if (a5.maxFontScale !== undefined) {
            this.maxFontScale = a5.maxFontScale;
        }
        if (a5.systemFontScale !== undefined) {
            this.systemFontScale = a5.systemFontScale;
        }
        if (a5.isPopup !== undefined) {
            this.isPopup = a5.isPopup;
        }
        if (a5.isOnFocus !== undefined) {
            this.isOnFocus = a5.isOnFocus;
        }
        if (a5.isOnHover !== undefined) {
            this.isOnHover = a5.isOnHover;
        }
        if (a5.isOnClick !== undefined) {
            this.isOnClick = a5.isOnClick;
        }
        if (a5.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (a5.dialogController !== undefined) {
            this.dialogController = a5.dialogController;
        }
        if (a5.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = a5.buttonGestureModifier;
        }
    }
    updateStateVars(z4) {
        this.__fontSize.reset(z4.fontSize);
    }
    purgeVariableDependenciesOnElmtId(y4) {
        this.__isOnFocus.purgeDependencyOnElmtId(y4);
        this.__isOnHover.purgeDependencyOnElmtId(y4);
        this.__isOnClick.purgeDependencyOnElmtId(y4);
        this.__fontSize.purgeDependencyOnElmtId(y4);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(y4);
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
    set isOnFocus(x4) {
        this.__isOnFocus.set(x4);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(w4) {
        this.__isOnHover.set(w4);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(v4) {
        this.__isOnClick.set(v4);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u4) {
        this.__fontSize.set(u4);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(t4) {
        this.__buttonGestureModifier.set(t4);
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
    toStringFormat(o4) {
        if (typeof o4 === 'string') {
            return o4;
        }
        else if (typeof o4 === 'undefined') {
            return '';
        }
        else {
            let p4 = '';
            try {
                p4 = getContext()?.resourceManager?.getStringSync(o4);
            }
            catch (q4) {
                let r4 = q4?.code;
                let s4 = q4?.message;
                hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBar toStringFormat,code: ${r4},message:${s4}`);
            }
            return p4;
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
    onPlaceChildren(j4, k4, l4) {
        k4.forEach((n4) => {
            n4.layout({ x: 0, y: 0 });
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
            let i4 = this.getUIContext();
            this.isFollowingSystemFontScale = i4.isFollowingSystemFontScale();
            this.maxFontScale = i4.getMaxFontScale();
        }
        catch (f4) {
            let g4 = f4.code;
            let h4 = f4.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${g4}, message: ${h4}`);
        }
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    decideFontScale() {
        try {
            let e4 = this.getUIContext();
            this.systemFontScale = e4.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (b4) {
            let c4 = b4.code;
            let d4 = b4.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${c4}, message: ${d4}`);
            return 1;
        }
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((q3, r3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q3);
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
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
            Button.onHover((a4) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                this.isOnHover = a4;
            });
            Button.onKeyEvent((z3) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (z3.keyCode !== KeyCode.KEYCODE_ENTER &&
                    z3.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (z3.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (z3.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((y3) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (y3.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (y3.type === TouchType.Up || y3.type === TouchType.Cancel) {
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
            if (!r3) {
                Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((y2, z2) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y2);
            If.create();
            if (this.item?.symbolStyle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((o3, p3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(o3);
                        SymbolGlyph.create();
                        SymbolGlyph.attributeModifier.bind(this)(this.item?.symbolStyle);
                        SymbolGlyph.fontSize(`${ImageMenuItem.imageSize}vp`);
                        SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                        SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                        SymbolGlyph.draggable(false);
                        SymbolGlyph.focusable(this.item?.isEnabled);
                        SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                        if (!p3) {
                            SymbolGlyph.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation((c3, d3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(c3);
                        If.create();
                        if (Util.isSymbolResource(this.item.value)) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((k3, l3) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(k3);
                                    SymbolGlyph.create(this.item.value);
                                    SymbolGlyph.fontSize(`${ImageMenuItem.imageSize}vp`);
                                    SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                    SymbolGlyph.draggable(false);
                                    SymbolGlyph.focusable(this.item?.isEnabled);
                                    SymbolGlyph.key(ImageMenuItem.focusablePrefix + this.index);
                                    if (!l3) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((g3, h3) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(g3);
                                    Image.create(this.item?.value);
                                    Image.matchTextDirection(this.item?.value === PUBLIC_BACK ? true : false);
                                    Image.width(ImageMenuItem.imageSize);
                                    Image.draggable(false);
                                    Image.height(ImageMenuItem.imageSize);
                                    Image.focusable(this.item?.isEnabled);
                                    Image.key(ImageMenuItem.focusablePrefix + this.index);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    if (!h3) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        if (!d3) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                });
            }
            if (!z2) {
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
ImageMenuItem.imageSize = 24;
ImageMenuItem.imageHotZoneWidth = 48;
ImageMenuItem.buttonBorderRadius = 8;
ImageMenuItem.focusBorderWidth = 2;
ImageMenuItem.focusablePrefix = 'Id-ComposeTitleBar-ImageMenuItem-';
class ComposeTitleBarDialog extends ViewPU {
    constructor(o2, p2, q2, r2 = -1, s2 = undefined, t2) {
        super(o2, q2, r2, t2);
        if (typeof s2 === 'function') {
            this.paramsGenerator_ = s2;
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
        this.setInitiallyProvidedValue(p2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(n2) {
        if (n2.itemComposeTitleDialog !== undefined) {
            this.itemComposeTitleDialog = n2.itemComposeTitleDialog;
        }
        if (n2.callbackId !== undefined) {
            this.callbackId = n2.callbackId;
        }
        if (n2.composeTitleBarDialog !== undefined) {
            this.composeTitleBarDialog = n2.composeTitleBarDialog;
        }
        if (n2.mainWindowStage !== undefined) {
            this.mainWindowStage = n2.mainWindowStage;
        }
        if (n2.controller !== undefined) {
            this.controller = n2.controller;
        }
        if (n2.minFontSize !== undefined) {
            this.minFontSize = n2.minFontSize;
        }
        if (n2.maxFontSize !== undefined) {
            this.maxFontSize = n2.maxFontSize;
        }
        if (n2.screenWidth !== undefined) {
            this.screenWidth = n2.screenWidth;
        }
        if (n2.verticalScreenLines !== undefined) {
            this.verticalScreenLines = n2.verticalScreenLines;
        }
        if (n2.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = n2.horizontalsScreenLines;
        }
        if (n2.fontSize !== undefined) {
            this.fontSize = n2.fontSize;
        }
        if (n2.maxLines !== undefined) {
            this.maxLines = n2.maxLines;
        }
        if (n2.cancel !== undefined) {
            this.cancel = n2.cancel;
        }
        if (n2.confirm !== undefined) {
            this.confirm = n2.confirm;
        }
    }
    updateStateVars(m2) {
    }
    purgeVariableDependenciesOnElmtId(l2) {
        this.__mainWindow.purgeDependencyOnElmtId(l2);
        this.__fontSize.purgeDependencyOnElmtId(l2);
        this.__maxLines.purgeDependencyOnElmtId(l2);
        this.__windowStandardHeight.purgeDependencyOnElmtId(l2);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(k2) {
        this.controller = k2;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(j2) {
        this.__mainWindow.set(j2);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(i2) {
        this.__fontSize.set(i2);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(h2) {
        this.__maxLines.set(h2);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(g2) {
        this.__windowStandardHeight.set(g2);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((e, f) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            if (this.composeTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((e2, f2) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(e2);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!f2) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((m1, n1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m1);
                        If.create();
                        if (this.itemComposeTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((c2, d2) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(c2);
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(`${IMAGE_SIZE}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    SymbolGlyph.margin({
                                        top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                        bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                    });
                                    if (!d2) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((q1, r1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(q1);
                                    If.create();
                                    if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation((y1, z1) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(y1);
                                                SymbolGlyph.create(this.itemComposeTitleDialog.value);
                                                SymbolGlyph.fontSize(`${IMAGE_SIZE}vp`);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                SymbolGlyph.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                                if (!z1) {
                                                    SymbolGlyph.pop();
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation((u1, v1) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(u1);
                                                Image.create(this.itemComposeTitleDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
                                                Image.margin({
                                                    top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                    bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                                                });
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                if (!v1) {
                                                    Image.pop();
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        });
                                    }
                                    if (!r1) {
                                        If.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                If.pop();
                            });
                        }
                        if (!n1) {
                            If.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    If.pop();
                    this.observeComponentCreation((k1, l1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(k1);
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        if (!l1) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((i1, j1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(i1);
                        Text.create(this.composeTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!j1) {
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
                    this.observeComponentCreation((b1, c1) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b1);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                        if (!c1) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((j, k) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(j);
                        If.create();
                        if (this.itemComposeTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((z, a1) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(z);
                                    SymbolGlyph.create();
                                    SymbolGlyph.attributeModifier.bind(this)(this.itemComposeTitleDialog.symbolStyle);
                                    SymbolGlyph.fontSize(`${IMAGE_SIZE}vp`);
                                    SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                    SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                    if (!a1) {
                                        SymbolGlyph.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((n, o) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(n);
                                    If.create();
                                    if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation((v, w) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(v);
                                                SymbolGlyph.create(this.itemComposeTitleDialog.value);
                                                SymbolGlyph.fontSize(`${IMAGE_SIZE}vp`);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                                if (!w) {
                                                    SymbolGlyph.pop();
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation((r, s) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(r);
                                                Image.create(this.itemComposeTitleDialog.value);
                                                Image.width(IMAGE_SIZE);
                                                Image.height(IMAGE_SIZE);
                                                Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                                if (!s) {
                                                    Image.pop();
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        });
                                    }
                                    if (!o) {
                                        If.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                If.pop();
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
export default { ComposeTitleBar };
