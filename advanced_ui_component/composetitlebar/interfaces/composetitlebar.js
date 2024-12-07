if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => { });
}
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const hilog = requireNapi('ohos.hilog');
const PUBLIC_MORE = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
class ButtonGestureModifier {
    constructor(e11) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = e11;
    }
    applyGesture(b11) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            b11.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (b11) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            b11.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
class ComposeTitleBar extends ViewPU {
    constructor(v10, w10, x10, y10 = -1, z10 = undefined, a11) {
        super(v10, x10, y10, a11);
        if (typeof z10 === 'function') {
            this.paramsGenerator_ = z10;
        }
        this.item = undefined;
        this.title = '';
        this.subtitle = '';
        this.menuItems = [];
        this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, 'titleMaxWidth');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(w10);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u10) {
        if (u10.item !== undefined) {
            this.item = u10.item;
        }
        if (u10.title !== undefined) {
            this.title = u10.title;
        }
        if (u10.subtitle !== undefined) {
            this.subtitle = u10.subtitle;
        }
        if (u10.menuItems !== undefined) {
            this.menuItems = u10.menuItems;
        }
        if (u10.titleMaxWidth !== undefined) {
            this.titleMaxWidth = u10.titleMaxWidth;
        }
        if (u10.fontSize !== undefined) {
            this.fontSize = u10.fontSize;
        }
    }
    updateStateVars(t10) {
    }
    purgeVariableDependenciesOnElmtId(s10) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(s10);
        this.__fontSize.purgeDependencyOnElmtId(s10);
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
    set titleMaxWidth(r10) {
        this.__titleMaxWidth.set(r10);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(q10) {
        this.__fontSize.set(q10);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((j10, k10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j10);
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.width('100%');
            Flex.height(ComposeTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((m10, n10) => {
                let o10 = Number(n10.width);
                if (this.menuItems !== undefined) {
                    let p10 = this.menuItems.length;
                    if (p10 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        o10 = o10 - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (p10 > 0) {
                        o10 = o10 - ImageMenuItem.imageHotZoneWidth * p10;
                    }
                }
                this.titleMaxWidth = o10;
                this.titleMaxWidth -= ComposeTitleBar.leftPadding;
                this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth;
                if (this.item !== undefined) {
                    this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
                    ComposeTitleBar.portraitImageSize +
                    ComposeTitleBar.portraitImageRightPadding;
                }
                this.titleMaxWidth -= ComposeTitleBar.rightPadding;
            });
            if (!k10) {
                Flex.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((h10, i10) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h10);
            Row.create();
            Row.margin({ left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            if (!i10) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        {
            this.observeComponentCreation((b10, c10) => {
                ViewStackProcessor.StartGetAccessRecordingFor(b10);
                if (c10) {
                    let d10 = new ImageMenuItem(this, { item: {
                        value: PUBLIC_BACK,
                        isEnabled: true,
                        action: () => this.getUIContext()?.getRouter()?.back()
                    }, index: -1 }, undefined, b10, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 92, col: 9 });
                    ViewPU.create(d10);
                    let e10 = () => {
                        return {
                            item: {
                                value: PUBLIC_BACK,
                                isEnabled: true,
                                action: () => this.getUIContext()?.getRouter()?.back()
                            },
                            index: -1
                        };
                    };
                    d10.paramsGenerator_ = e10;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(b10, {});
                }
                ViewStackProcessor.StopGetAccessRecording();
            });
        }
        this.observeComponentCreation((y9, z9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(y9);
            Row.create();
            Row.accessibilityGroup(true);
            if (!z9) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((r9, s9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(r9);
            If.create();
            if (this.item !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((w9, x9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(w9);
                        Image.create(this.item.value);
                        Image.width(ComposeTitleBar.portraitImageSize);
                        Image.height(ComposeTitleBar.portraitImageSize);
                        Image.margin({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_xs'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_paragraph_margin_m'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }
                        });
                        Image.focusable(false);
                        Image.borderRadius(ImageMenuItem.buttonBorderRadius);
                        if (!x9) {
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
            if (!s9) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        this.observeComponentCreation((p9, q9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(p9);
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
            if (!q9) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((f9, g9) => {
            ViewStackProcessor.StartGetAccessRecordingFor(f9);
            If.create();
            if (this.title !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((n9, o9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(n9);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        if (!o9) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((l9, m9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(l9);
                        Text.create(this.title);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_headline8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(this.subtitle !== undefined ? 1 : 2);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
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
        this.observeComponentCreation((v8, w8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v8);
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((d9, e9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(d9);
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                        if (!e9) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((b9, c9) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(b9);
                        Text.create(this.subtitle);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_text_size_over_line'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_titlebar_subtitle_text'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.constraintSize({ maxWidth: this.titleMaxWidth });
                        if (!c9) {
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
            if (!w8) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Column.pop();
        Row.pop();
        Row.pop();
        this.observeComponentCreation((k8, l8) => {
            ViewStackProcessor.StartGetAccessRecordingFor(k8);
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation((p8, q8) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(p8);
                            if (q8) {
                                let r8 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ }, undefined, p8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 145, col: 9 });
                                ViewPU.create(r8);
                                let s8 = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + ComposeTitleBar.instanceCount++
                                    };
                                };
                                r8.paramsGenerator_ = s8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(p8, {});
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
            if (!l8) {
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
    constructor(s7, t7, u7, v7 = -1, w7 = undefined, x7) {
        super(s7, u7, v7, x7);
        if (typeof w7 === 'function') {
            this.paramsGenerator_ = w7;
        }
        this.menuItems = [];
        this.item = {
            value: PUBLIC_MORE,
            label: { 'id': -1, 'type': 10003, params: ['sys.string.ohos_toolbar_more'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
        };
        this.index = 0;
        this.longPressTime = 500;
        this.minFontSize = 1.75;
        this.isFollowingSystemFontScale = false;
        this.maxFontScale = 1;
        this.systemFontScale = 1;
        this.firstFocusableIndex = -1;
        this.__isPopupShown = new ObservedPropertySimplePU(false, this, 'isPopupShown');
        this.__isMoreIconOnFocus = new ObservedPropertySimplePU(false, this, 'isMoreIconOnFocus');
        this.__isMoreIconOnHover = new ObservedPropertySimplePU(false, this, 'isMoreIconOnHover');
        this.__isMoreIconOnClick = new ObservedPropertySimplePU(false, this, 'isMoreIconOnClick');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(t7.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let y7 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 202, col: 14 });
                y7.setController(this.dialogController);
                ViewPU.create(y7);
                let z7 = () => {
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
                y7.paramsGenerator_ = z7;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(t7);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r7) {
        if (r7.menuItems !== undefined) {
            this.menuItems = r7.menuItems;
        }
        if (r7.item !== undefined) {
            this.item = r7.item;
        }
        if (r7.index !== undefined) {
            this.index = r7.index;
        }
        if (r7.longPressTime !== undefined) {
            this.longPressTime = r7.longPressTime;
        }
        if (r7.minFontSize !== undefined) {
            this.minFontSize = r7.minFontSize;
        }
        if (r7.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = r7.isFollowingSystemFontScale;
        }
        if (r7.maxFontScale !== undefined) {
            this.maxFontScale = r7.maxFontScale;
        }
        if (r7.systemFontScale !== undefined) {
            this.systemFontScale = r7.systemFontScale;
        }
        if (r7.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = r7.firstFocusableIndex;
        }
        if (r7.isPopupShown !== undefined) {
            this.isPopupShown = r7.isPopupShown;
        }
        if (r7.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = r7.isMoreIconOnFocus;
        }
        if (r7.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = r7.isMoreIconOnHover;
        }
        if (r7.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = r7.isMoreIconOnClick;
        }
        if (r7.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (r7.dialogController !== undefined) {
            this.dialogController = r7.dialogController;
        }
        if (r7.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = r7.buttonGestureModifier;
        }
    }
    updateStateVars(q7) {
        this.__fontSize.reset(q7.fontSize);
    }
    purgeVariableDependenciesOnElmtId(p7) {
        this.__isPopupShown.purgeDependencyOnElmtId(p7);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(p7);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(p7);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(p7);
        this.__fontSize.purgeDependencyOnElmtId(p7);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(p7);
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
    set isPopupShown(o7) {
        this.__isPopupShown.set(o7);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(n7) {
        this.__isMoreIconOnFocus.set(n7);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(m7) {
        this.__isMoreIconOnHover.set(m7);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(l7) {
        this.__isMoreIconOnClick.set(l7);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(k7) {
        this.__fontSize.set(k7);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(j7) {
        this.__buttonGestureModifier.set(j7);
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
            let i7 = this.getUIContext();
            this.isFollowingSystemFontScale = i7.isFollowingSystemFontScale();
            this.maxFontScale = i7.getMaxFontScale();
        }
        catch (f7) {
            let g7 = f7.code;
            let h7 = f7.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${g7}, message: ${h7}`);
        }
        if (this.menuItems) {
            this.menuItems.forEach((d7, e7) => {
                if (d7.isEnabled && this.firstFocusableIndex == -1 &&
                    e7 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                    this.firstFocusableIndex = this.index * 1000 + e7 + 1;
                }
            });
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        try {
            let b7 = this.getUIContext();
            this.systemFontScale = b7.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (y6) {
            let z6 = y6.code;
            let a7 = y6.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${z6}, message: ${a7}`);
            return 1;
        }
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((w6, x6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(w6);
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
            if (!x6) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((u6, v6) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u6);
            Row.create();
            if (!v6) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((r4, s4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(r4);
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((w4, x4) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(w4);
                        If.create();
                        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation((g6, h6) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(g6);
                                    ForEach.create();
                                    const i6 = (k6, l6) => {
                                        const m6 = k6;
                                        {
                                            this.observeComponentCreation((o6, p6) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(o6);
                                                if (p6) {
                                                    let q6 = new ImageMenuItem(this, { item: m6, index: this.index * 1000 + l6 + 1 }, undefined, o6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 281, col: 15 });
                                                    ViewPU.create(q6);
                                                    let r6 = () => {
                                                        return {
                                                            item: m6,
                                                            index: this.index * 1000 + l6 + 1
                                                        };
                                                    };
                                                    q6.paramsGenerator_ = r6;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(o6, {});
                                                }
                                                ViewStackProcessor.StopGetAccessRecording();
                                            });
                                        }
                                    };
                                    this.forEachUpdateFunction(g6, this.menuItems, i6, undefined, true, false);
                                    if (!h6) {
                                        ForEach.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                ForEach.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation((q5, r5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(q5);
                                    ForEach.create();
                                    const s5 = (u5, v5) => {
                                        const w5 = u5;
                                        {
                                            this.observeComponentCreation((y5, z5) => {
                                                ViewStackProcessor.StartGetAccessRecordingFor(y5);
                                                if (z5) {
                                                    let a6 = new ImageMenuItem(this, { item: w5, index: this.index * 1000 + v5 + 1 }, undefined, y5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 286, col: 17 });
                                                    ViewPU.create(a6);
                                                    let b6 = () => {
                                                        return {
                                                            item: w5,
                                                            index: this.index * 1000 + v5 + 1
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
                                    this.forEachUpdateFunction(q5, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), s5, undefined, true, false);
                                    if (!r5) {
                                        ForEach.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                ForEach.pop();
                                this.observeComponentCreation((e5, f5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(e5);
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
                                    Button.onHover((p5) => this.isMoreIconOnHover = p5);
                                    Button.onKeyEvent((o5) => {
                                        if (o5.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            o5.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (o5.type === KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (o5.type === KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((n5) => {
                                        if (n5.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (n5.type === TouchType.Up || n5.type === TouchType.Cancel) {
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
                                        onStateChange: (m5) => {
                                            this.isPopupShown = m5.isVisible;
                                            if (!m5.isVisible) {
                                                this.isMoreIconOnClick = false;
                                            }
                                        }
                                    });
                                    if (!f5) {
                                        Button.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                this.observeComponentCreation((c5, d5) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(c5);
                                    Image.create(PUBLIC_MORE);
                                    Image.width(ImageMenuItem.imageSize);
                                    Image.draggable(false);
                                    Image.height(ImageMenuItem.imageSize);
                                    Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                                    Image.focusable(true);
                                    if (!d5) {
                                        Image.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                                Button.pop();
                            });
                        }
                        if (!x4) {
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
            if (!s4) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
    popupBuilder(p3 = null) {
        this.observeComponentCreation((l4, m4) => {
            ViewStackProcessor.StartGetAccessRecordingFor(l4);
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth +
                CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix +
                this.firstFocusableIndex);
            });
            if (!m4) {
                Column.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((s3, t3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s3);
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((x3, y3) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(x3);
                        ForEach.create();
                        const z3 = (b4, c4) => {
                            const d4 = b4;
                            {
                                this.observeComponentCreation((f4, g4) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(f4);
                                    if (g4) {
                                        let h4 = new ImageMenuItem(this, { item: d4, index: this.index * 1000 +
                                        CollapsibleMenuSection.maxCountOfVisibleItems + c4, isPopup: true }, undefined, f4, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 375, col: 13 });
                                        ViewPU.create(h4);
                                        let i4 = () => {
                                            return {
                                                item: d4,
                                                index: this.index * 1000 +
                                                CollapsibleMenuSection.maxCountOfVisibleItems + c4,
                                                isPopup: true
                                            };
                                        };
                                        h4.paramsGenerator_ = i4;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(f4, {});
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                });
                            }
                        };
                        this.forEachUpdateFunction(x3, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), z3, undefined, true, false);
                        if (!y3) {
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
            if (!t3) {
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
    constructor(f3, g3, h3, i3 = -1, j3 = undefined, k3) {
        super(f3, h3, i3, k3);
        if (typeof j3 === 'function') {
            this.paramsGenerator_ = j3;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(g3.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let l3 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 414, col: 14 });
                l3.setController(this.dialogController);
                ViewPU.create(l3);
                let m3 = () => {
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
                l3.paramsGenerator_ = m3;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(g3);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(e3) {
        if (e3.item !== undefined) {
            this.item = e3.item;
        }
        if (e3.index !== undefined) {
            this.index = e3.index;
        }
        if (e3.minFontSize !== undefined) {
            this.minFontSize = e3.minFontSize;
        }
        if (e3.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = e3.isFollowingSystemFontScale;
        }
        if (e3.maxFontScale !== undefined) {
            this.maxFontScale = e3.maxFontScale;
        }
        if (e3.systemFontScale !== undefined) {
            this.systemFontScale = e3.systemFontScale;
        }
        if (e3.isPopup !== undefined) {
            this.isPopup = e3.isPopup;
        }
        if (e3.isOnFocus !== undefined) {
            this.isOnFocus = e3.isOnFocus;
        }
        if (e3.isOnHover !== undefined) {
            this.isOnHover = e3.isOnHover;
        }
        if (e3.isOnClick !== undefined) {
            this.isOnClick = e3.isOnClick;
        }
        if (e3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (e3.dialogController !== undefined) {
            this.dialogController = e3.dialogController;
        }
        if (e3.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = e3.buttonGestureModifier;
        }
    }
    updateStateVars(d3) {
        this.__fontSize.reset(d3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(c3) {
        this.__isOnFocus.purgeDependencyOnElmtId(c3);
        this.__isOnHover.purgeDependencyOnElmtId(c3);
        this.__isOnClick.purgeDependencyOnElmtId(c3);
        this.__fontSize.purgeDependencyOnElmtId(c3);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(c3);
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
    set isOnFocus(b3) {
        this.__isOnFocus.set(b3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(a3) {
        this.__isOnHover.set(a3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(z2) {
        this.__isOnClick.set(z2);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(y2) {
        this.__fontSize.set(y2);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(x2) {
        this.__buttonGestureModifier.set(x2);
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
    toStringFormat(s2) {
        if (typeof s2 === 'string') {
            return s2;
        }
        else if (typeof s2 === 'undefined') {
            return '';
        }
        else {
            let t2 = '';
            try {
                t2 = getContext()?.resourceManager?.getStringSync(s2);
            }
            catch (u2) {
                let v2 = u2?.code;
                let w2 = u2?.message;
                hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBar toStringFormat,code: ${v2},message:${w2}`);
            }
            return t2;
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
    onPlaceChildren(n2, o2, p2) {
        o2.forEach((r2) => {
            r2.layout({ x: 0, y: 0 });
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
            let m2 = this.getUIContext();
            this.isFollowingSystemFontScale = m2.isFollowingSystemFontScale();
            this.maxFontScale = m2.getMaxFontScale();
        }
        catch (j2) {
            let k2 = j2.code;
            let l2 = j2.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${k2}, message: ${l2}`);
        }
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    decideFontScale() {
        try {
            let i2 = this.getUIContext();
            this.systemFontScale = i2.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (f2) {
            let g2 = f2.code;
            let h2 = f2.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${g2}, message: ${h2}`);
            return 1;
        }
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((u1, v1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(u1);
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
            Button.opacity(this.item?.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity);
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
            Button.onHover((e2) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                this.isOnHover = e2;
            });
            Button.onKeyEvent((d2) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (d2.keyCode !== KeyCode.KEYCODE_ENTER &&
                    d2.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (d2.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (d2.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((c2) => {
                if (!this.item?.isEnabled) {
                    return;
                }
                if (c2.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (c2.type === TouchType.Up || c2.type === TouchType.Cancel) {
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
            if (!v1) {
                Button.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((s1, t1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(s1);
            Image.create(this.item?.value);
            Image.matchTextDirection(this.item?.value === PUBLIC_BACK ? true : false);
            Image.width(ImageMenuItem.imageSize);
            Image.draggable(false);
            Image.height(ImageMenuItem.imageSize);
            Image.focusable(this.item?.isEnabled);
            Image.key(ImageMenuItem.focusablePrefix + this.index);
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_text_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            if (!t1) {
                Image.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
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
ImageMenuItem.disabledImageOpacity = 0.4;
ImageMenuItem.focusablePrefix = 'Id-ComposeTitleBar-ImageMenuItem-';
class ComposeTitleBarDialog extends ViewPU {
    constructor(i1, j1, k1, l1 = -1, m1 = undefined, n1) {
        super(i1, k1, l1, n1);
        if (typeof m1 === 'function') {
            this.paramsGenerator_ = m1;
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
        this.setInitiallyProvidedValue(j1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(h1) {
        if (h1.itemComposeTitleDialog !== undefined) {
            this.itemComposeTitleDialog = h1.itemComposeTitleDialog;
        }
        if (h1.callbackId !== undefined) {
            this.callbackId = h1.callbackId;
        }
        if (h1.composeTitleBarDialog !== undefined) {
            this.composeTitleBarDialog = h1.composeTitleBarDialog;
        }
        if (h1.mainWindowStage !== undefined) {
            this.mainWindowStage = h1.mainWindowStage;
        }
        if (h1.controller !== undefined) {
            this.controller = h1.controller;
        }
        if (h1.minFontSize !== undefined) {
            this.minFontSize = h1.minFontSize;
        }
        if (h1.maxFontSize !== undefined) {
            this.maxFontSize = h1.maxFontSize;
        }
        if (h1.screenWidth !== undefined) {
            this.screenWidth = h1.screenWidth;
        }
        if (h1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = h1.verticalScreenLines;
        }
        if (h1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = h1.horizontalsScreenLines;
        }
        if (h1.fontSize !== undefined) {
            this.fontSize = h1.fontSize;
        }
        if (h1.maxLines !== undefined) {
            this.maxLines = h1.maxLines;
        }
        if (h1.cancel !== undefined) {
            this.cancel = h1.cancel;
        }
        if (h1.confirm !== undefined) {
            this.confirm = h1.confirm;
        }
    }
    updateStateVars(g1) {
    }
    purgeVariableDependenciesOnElmtId(f1) {
        this.__mainWindow.purgeDependencyOnElmtId(f1);
        this.__fontSize.purgeDependencyOnElmtId(f1);
        this.__maxLines.purgeDependencyOnElmtId(f1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(f1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(e1) {
        this.controller = e1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(d1) {
        this.__mainWindow.set(d1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(c1) {
        this.__fontSize.set(c1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(b1) {
        this.__maxLines.set(b1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(a1) {
        this.__windowStandardHeight.set(a1);
    }
    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation((e, f) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            if (this.composeTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((y, z) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(y);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!z) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((w, x) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(w);
                        Image.create(this.itemComposeTitleDialog.value);
                        Image.width(IMAGE_SIZE);
                        Image.height(IMAGE_SIZE);
                        Image.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!x) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((u, v) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(u);
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        if (!v) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((s, t) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(s);
                        Text.create(this.composeTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.width('100%');
                        Text.textAlign(TextAlign.Center);
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.font_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!t) {
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
                    this.observeComponentCreation((l, m) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(l);
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                        if (!m) {
                            Column.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.observeComponentCreation((j, k) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(j);
                        Image.create(this.itemComposeTitleDialog.value);
                        Image.width(IMAGE_SIZE);
                        Image.height(IMAGE_SIZE);
                        Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        if (!k) {
                            Image.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
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
    ComposeTitleBar: ComposeTitleBar
};
