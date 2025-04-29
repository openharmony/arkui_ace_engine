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
const PUBLIC_MORE = { 'id': -1, 'type': 40000, params: ['sys.symbol.dot_grid_2x2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 40000, params: ['sys.symbol.arrow_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const RESOURCE_TYPE_SYMBOL = 40000;
class Util {
    static isSymbolResource(q21) {
        if (!Util.isResourceType(q21)) {
            return false;
        }
        let r21 = q21;
        return r21.type === RESOURCE_TYPE_SYMBOL;
    }
    static isResourceType(p21) {
        if (!p21) {
            return false;
        }
        if (typeof p21 === 'string' || typeof p21 === 'undefined') {
            return false;
        }
        return true;
    }
}
class ButtonGestureModifier {
    constructor(o21) {
        this.fontSize = 1;
        this.controller = null;
        this.controller = o21;
    }
    applyGesture(n21) {
        if (this.fontSize >= ButtonGestureModifier.minFontSize) {
            n21.addGesture(new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
                .onAction(() => {
                    if (n21) {
                        this.controller?.open();
                    }
                })
                .onActionEnd(() => {
                    this.controller?.close();
                }));
        }
        else {
            n21.clearGestures();
        }
    }
}
ButtonGestureModifier.longPressTime = 500;
ButtonGestureModifier.minFontSize = 1.75;
class ComposeTitleBar extends ViewPU {
    constructor(h21, i21, j21, k21 = -1, l21 = undefined, m21) {
        super(h21, j21, k21, m21);
        if (typeof l21 === 'function') {
            this.paramsGenerator_ = l21;
        }
        this.item = undefined;
        this.title = '';
        this.subtitle = '';
        this.menuItems = [];
        this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, 'titleMaxWidth');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.__uniqueId = new ObservedPropertySimplePU(-1, this, 'uniqueId');
        this.addProvidedVar('uniqueId', this.__uniqueId, false);
        this.setInitiallyProvidedValue(i21);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(g21) {
        if (g21.item !== undefined) {
            this.item = g21.item;
        }
        if (g21.title !== undefined) {
            this.title = g21.title;
        }
        if (g21.subtitle !== undefined) {
            this.subtitle = g21.subtitle;
        }
        if (g21.menuItems !== undefined) {
            this.menuItems = g21.menuItems;
        }
        if (g21.titleMaxWidth !== undefined) {
            this.titleMaxWidth = g21.titleMaxWidth;
        }
        if (g21.fontSize !== undefined) {
            this.fontSize = g21.fontSize;
        }
        if (g21.uniqueId !== undefined) {
            this.uniqueId = g21.uniqueId;
        }
    }
    updateStateVars(f21) {
    }
    purgeVariableDependenciesOnElmtId(e21) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(e21);
        this.__fontSize.purgeDependencyOnElmtId(e21);
        this.__uniqueId.purgeDependencyOnElmtId(e21);
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
    set titleMaxWidth(d21) {
        this.__titleMaxWidth.set(d21);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(c21) {
        this.__fontSize.set(c21);
    }
    get uniqueId() {
        return this.__uniqueId.get();
    }
    set uniqueId(b21) {
        this.__uniqueId.set(b21);
    }
    initialRender() {
        this.observeComponentCreation2((v20, w20) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch
            });
            Flex.onAppear(() => {
                try {
                    this.uniqueId =
                        this.getUIContext().getFrameNodeByUniqueId(this.getUniqueId())?.getFirstChild()?.getUniqueId();
                } catch (u18) {
                    let v18 = u18?.code;
                    let w18 = u18?.message;
                    hilog.error(0x3900, 'ComposeTitleBar',
                        `Failed to init getFrameNodeByUniqueId info, cause, code: ${v18}, message: ${w18}`);
                }
            });
            Flex.width('100%');
            Flex.height(ComposeTitleBar.totalHeight);
            Flex.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.ohos_id_color_background'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Flex.onAreaChange((x20, y20) => {
                let z20 = Number(y20.width);
                if (this.menuItems !== undefined) {
                    let a21 = this.menuItems.length;
                    if (a21 >= CollapsibleMenuSection.maxCountOfVisibleItems) {
                        z20 = z20 - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
                    }
                    else if (a21 > 0) {
                        z20 = z20 - ImageMenuItem.imageHotZoneWidth * a21;
                    }
                }
                this.titleMaxWidth = z20;
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
        this.observeComponentCreation2((t20, u20) => {
            Row.create();
            Row.margin({ left: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_start'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
        }, Row);
        {
            this.observeComponentCreation2((p20, q20) => {
                if (q20) {
                    let r20 = new ImageMenuItem(this, {
                        item: {
                            value: PUBLIC_BACK,
                            isEnabled: true,
                            action: () => this.getUIContext()?.getRouter()?.back()
                        },
                        index: -1,
                        itemIndex: -1
                    }, undefined, p20, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 113, col: 9 });
                    ViewPU.create(r20);
                    let j = () => {
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
                    r20.paramsGenerator_ = j;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(p20, {});
                }
            }, { name: 'ImageMenuItem' });
        }
        this.observeComponentCreation2((n20, o20) => {
            Row.create();
            Row.accessibilityGroup(true);
            Row.accessibilityDescription({
                'id': -1,
                'type': 10003,
                params: ['sys.string.subheader_accessibility_title'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
        }, Row);
        this.observeComponentCreation2((j20, k20) => {
            If.create();
            if (this.item !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l20, m20) => {
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
        this.observeComponentCreation2((h20, i20) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
        }, Column);
        this.observeComponentCreation2((b20, c20) => {
            If.create();
            if (this.title !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f20, g20) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((d20, e20) => {
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
        this.observeComponentCreation2((v19, w19) => {
            If.create();
            if (this.subtitle !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z19, a20) => {
                        Row.create();
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((x19, y19) => {
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
        this.observeComponentCreation2((p19, q19) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((r19, s19) => {
                            if (s19) {
                                let t19 = new CollapsibleMenuSection(this, { menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ }, undefined, r19, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 170, col: 9 });
                                ViewPU.create(t19);
                                let i = () => {
                                    return {
                                        menuItems: this.menuItems,
                                        index: 1 + ComposeTitleBar.instanceCount++
                                    };
                                };
                                t19.paramsGenerator_ = i;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(r19, {});
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
    constructor(h19, i19, j19, k19 = -1, l19 = undefined, m19) {
        super(h19, j19, k19, m19);
        if (typeof l19 === 'function') {
            this.paramsGenerator_ = l19;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(i19.fontSize, this, 'fontSize');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let n19 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : '',
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 224, col: 14 });
                n19.setController(this.dialogController);
                ViewPU.create(n19);
                let h = () => {
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
                n19.paramsGenerator_ = h;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(i19);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(g19) {
        if (g19.menuItems !== undefined) {
            this.menuItems = g19.menuItems;
        }
        if (g19.item !== undefined) {
            this.item = g19.item;
        }
        if (g19.index !== undefined) {
            this.index = g19.index;
        }
        if (g19.minFontSize !== undefined) {
            this.minFontSize = g19.minFontSize;
        }
        if (g19.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = g19.isFollowingSystemFontScale;
        }
        if (g19.maxFontScale !== undefined) {
            this.maxFontScale = g19.maxFontScale;
        }
        if (g19.systemFontScale !== undefined) {
            this.systemFontScale = g19.systemFontScale;
        }
        if (g19.firstFocusableIndex !== undefined) {
            this.firstFocusableIndex = g19.firstFocusableIndex;
        }
        if (g19.isPopupShown !== undefined) {
            this.isPopupShown = g19.isPopupShown;
        }
        if (g19.isMoreIconOnFocus !== undefined) {
            this.isMoreIconOnFocus = g19.isMoreIconOnFocus;
        }
        if (g19.isMoreIconOnHover !== undefined) {
            this.isMoreIconOnHover = g19.isMoreIconOnHover;
        }
        if (g19.isMoreIconOnClick !== undefined) {
            this.isMoreIconOnClick = g19.isMoreIconOnClick;
        }
        if (g19.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (g19.dialogController !== undefined) {
            this.dialogController = g19.dialogController;
        }
        if (g19.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = g19.buttonGestureModifier;
        }
    }
    updateStateVars(f19) {
        this.__fontSize.reset(f19.fontSize);
    }
    purgeVariableDependenciesOnElmtId(e19) {
        this.__isPopupShown.purgeDependencyOnElmtId(e19);
        this.__isMoreIconOnFocus.purgeDependencyOnElmtId(e19);
        this.__isMoreIconOnHover.purgeDependencyOnElmtId(e19);
        this.__isMoreIconOnClick.purgeDependencyOnElmtId(e19);
        this.__fontSize.purgeDependencyOnElmtId(e19);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(e19);
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
    set isPopupShown(d19) {
        this.__isPopupShown.set(d19);
    }
    get isMoreIconOnFocus() {
        return this.__isMoreIconOnFocus.get();
    }
    set isMoreIconOnFocus(c19) {
        this.__isMoreIconOnFocus.set(c19);
    }
    get isMoreIconOnHover() {
        return this.__isMoreIconOnHover.get();
    }
    set isMoreIconOnHover(b19) {
        this.__isMoreIconOnHover.set(b19);
    }
    get isMoreIconOnClick() {
        return this.__isMoreIconOnClick.get();
    }
    set isMoreIconOnClick(a19) {
        this.__isMoreIconOnClick.set(a19);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(z18) {
        this.__fontSize.set(z18);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(y18) {
        this.__buttonGestureModifier.set(y18);
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
            let x18 = this.getUIContext();
            this.isFollowingSystemFontScale = x18.isFollowingSystemFontScale();
            this.maxFontScale = x18.getMaxFontScale();
        }
        catch (u18) {
            let v18 = u18?.code;
            let w18 = u18?.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${v18}, message: ${w18}`);
        }
        if (this.menuItems) {
            this.menuItems.forEach((s18, t18) => {
                if (s18.isEnabled && this.firstFocusableIndex === -1 &&
                    t18 > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
                    this.firstFocusableIndex = this.index * 1000 + t18 + 1;
                }
            });
        }
        this.fontSize = this.decideFontScale();
    }
    decideFontScale() {
        try {
            let r18 = this.getUIContext();
            this.systemFontScale = r18.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (o18) {
            let p18 = o18?.code;
            let q18 = o18?.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${p18}, message: ${q18}`);
            return 1;
        }
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    initialRender() {
        this.observeComponentCreation2((m18, n18) => {
            Column.create();
            Column.height('100%');
            Column.margin({ right: { 'id': -1, 'type': 10002, params: ['sys.float.ohos_id_default_padding_end'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' } });
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((k18, l18) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((e17, f17) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g17, h17) => {
                        If.create();
                        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((a18, b18) => {
                                    ForEach.create();
                                    const f = (d18, e18) => {
                                        const f18 = d18;
                                        {
                                            this.observeComponentCreation2((g18, h18) => {
                                                if (h18) {
                                                    let i18 = new ImageMenuItem(this, { item: f18, index: this.index * 1000 + e18 + 1, itemIndex: e18 }, undefined, g18, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 304, col: 15 });
                                                    ViewPU.create(i18);
                                                    let g = () => {
                                                        return {
                                                            item: f18,
                                                            index: this.index * 1000 + e18 + 1,
                                                            itemIndex: e18
                                                        };
                                                    };
                                                    i18.paramsGenerator_ = g;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(g18, {});
                                                }
                                            }, { name: 'ImageMenuItem' });
                                        }
                                    };
                                    this.forEachUpdateFunction(a18, this.menuItems, f, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((q17, r17) => {
                                    ForEach.create();
                                    const d = (t17, u17) => {
                                        const v17 = t17;
                                        {
                                            this.observeComponentCreation2((w17, x17) => {
                                                if (x17) {
                                                    let y17 = new ImageMenuItem(this, { item: v17, index: this.index * 1000 + u17 + 1, itemIndex: u17 }, undefined, w17, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 309, col: 17 });
                                                    ViewPU.create(y17);
                                                    let e = () => {
                                                        return {
                                                            item: v17,
                                                            index: this.index * 1000 + u17 + 1,
                                                            itemIndex: u17
                                                        };
                                                    };
                                                    y17.paramsGenerator_ = e;
                                                }
                                                else {
                                                    this.updateStateVarsOfChildByElmtId(w17, {});
                                                }
                                            }, { name: 'ImageMenuItem' });
                                        }
                                    };
                                    this.forEachUpdateFunction(q17, this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1), d, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                                this.observeComponentCreation2((k17, l17) => {
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
                                    Button.onHover((p17) => this.isMoreIconOnHover = p17);
                                    Button.onKeyEvent((o17) => {
                                        if (o17.keyCode !== KeyCode.KEYCODE_ENTER &&
                                            o17.keyCode !== KeyCode.KEYCODE_SPACE) {
                                            return;
                                        }
                                        if (o17.type === KeyType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (o17.type === KeyType.Up) {
                                            this.isMoreIconOnClick = false;
                                        }
                                    });
                                    Button.onTouch((n17) => {
                                        if (n17.type === TouchType.Down) {
                                            this.isMoreIconOnClick = true;
                                        }
                                        if (n17.type === TouchType.Up || n17.type === TouchType.Cancel) {
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
                                        onStateChange: (m17) => {
                                            this.isPopupShown = m17.isVisible;
                                            if (!m17.isVisible) {
                                                this.isMoreIconOnClick = false;
                                            }
                                        }
                                    });
                                }, Button);
                                this.observeComponentCreation2((i17, j17) => {
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
    onPlaceChildren(a17, b17, c17) {
        b17.forEach((d17) => {
            d17.layout({ x: 0, y: 0 });
        });
        this.fontSize = this.decideFontScale();
    }
    popupBuilder(l16 = null) {
        this.observeComponentCreation2((y16, z16) => {
            Column.create();
            Column.width(ImageMenuItem.imageHotZoneWidth +
                CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum);
            Column.margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding });
            Column.onAppear(() => {
                focusControl.requestFocus(ImageMenuItem.focusablePrefix +
                this.firstFocusableIndex);
            });
        }, Column);
        this.observeComponentCreation2((m16, n16) => {
            If.create();
            if (this.menuItems) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((o16, p16) => {
                        ForEach.create();
                        const b = (r16, s16) => {
                            const t16 = r16;
                            {
                                this.observeComponentCreation2((u16, v16) => {
                                    if (v16) {
                                        let w16 = new ImageMenuItem(this, {
                                            item: t16, index: this.index * 1000 +
                                            CollapsibleMenuSection.maxCountOfVisibleItems + s16,
                                            isPopup: false
                                        }, undefined, u16, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 404, col: 13 });
                                        ViewPU.create(w16);
                                        let c = () => {
                                            return {
                                                item: t16,
                                                index: this.index * 1000 +
                                                CollapsibleMenuSection.maxCountOfVisibleItems + s16,
                                                isPopup: false
                                            };
                                        };
                                        w16.paramsGenerator_ = c;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(u16, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(o16, this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length), b, undefined, true, false);
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
    constructor(d16, e16, f16, g16 = -1, h16 = undefined, i16) {
        super(d16, f16, g16, i16);
        if (typeof h16 === 'function') {
            this.paramsGenerator_ = h16;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(e16.fontSize, this, 'fontSize');
        this.__parentParentUniqueId = this.initializeConsume('uniqueId', 'parentParentUniqueId');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let j16 = new ComposeTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemComposeTitleDialog: this.item,
                    composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/ComposeTitleBar.ets', line: 442, col: 14 });
                j16.setController(this.dialogController);
                ViewPU.create(j16);
                let a = () => {
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
                j16.paramsGenerator_ = a;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.__buttonGestureModifier = new ObservedPropertyObjectPU(new ButtonGestureModifier(this.dialogController), this, 'buttonGestureModifier');
        this.setInitiallyProvidedValue(e16);
        this.declareWatch('fontSize', this.onFontSizeUpdated);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c16) {
        if (c16.item !== undefined) {
            this.item = c16.item;
        }
        if (c16.index !== undefined) {
            this.index = c16.index;
        }
        if (c16.itemIndex !== undefined) {
            this.itemIndex = c16.itemIndex;
        }
        if (c16.minFontSize !== undefined) {
            this.minFontSize = c16.minFontSize;
        }
        if (c16.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = c16.isFollowingSystemFontScale;
        }
        if (c16.maxFontScale !== undefined) {
            this.maxFontScale = c16.maxFontScale;
        }
        if (c16.systemFontScale !== undefined) {
            this.systemFontScale = c16.systemFontScale;
        }
        if (c16.isPopup !== undefined) {
            this.isPopup = c16.isPopup;
        }
        if (c16.isOnFocus !== undefined) {
            this.isOnFocus = c16.isOnFocus;
        }
        if (c16.isOnHover !== undefined) {
            this.isOnHover = c16.isOnHover;
        }
        if (c16.isOnClick !== undefined) {
            this.isOnClick = c16.isOnClick;
        }
        if (c16.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (c16.dialogController !== undefined) {
            this.dialogController = c16.dialogController;
        }
        if (c16.buttonGestureModifier !== undefined) {
            this.buttonGestureModifier = c16.buttonGestureModifier;
        }
    }
    updateStateVars(b16) {
        this.__fontSize.reset(b16.fontSize);
    }
    purgeVariableDependenciesOnElmtId(a16) {
        this.__isOnFocus.purgeDependencyOnElmtId(a16);
        this.__isOnHover.purgeDependencyOnElmtId(a16);
        this.__isOnClick.purgeDependencyOnElmtId(a16);
        this.__fontSize.purgeDependencyOnElmtId(a16);
        this.__parentParentUniqueId.purgeDependencyOnElmtId(a16);
        this.__buttonGestureModifier.purgeDependencyOnElmtId(a16);
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
    set isOnFocus(z15) {
        this.__isOnFocus.set(z15);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(y15) {
        this.__isOnHover.set(y15);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(x15) {
        this.__isOnClick.set(x15);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(w15) {
        this.__fontSize.set(w15);
    }
    get parentParentUniqueId() {
        return this.__parentParentUniqueId.get();
    }
    set parentParentUniqueId(v15) {
        this.__parentParentUniqueId.set(v15);
    }
    get buttonGestureModifier() {
        return this.__buttonGestureModifier.get();
    }
    set buttonGestureModifier(u15) {
        this.__buttonGestureModifier.set(u15);
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
    toStringFormat(p15) {
        if (typeof p15 === 'string') {
            return p15;
        }
        else if (typeof p15 === 'undefined') {
            return '';
        }
        else {
            let q15 = '';
            try {
                if (p15.id === -1) {
                    q15 = getContext()?.resourceManager?.getStringByNameSync(p15.params?.[0].split('.').pop());
                }
                else {
                    q15 = getContext()?.resourceManager?.getStringSync(p15);
                }
            }
            catch (r15) {
                let s15 = r15?.code;
                let t15 = r15?.message;
                hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBar toStringFormat,code: ${s15},message:${t15}`);
            }
            return q15;
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
            return this.item.accessibilityText;
        }
        else if (this.item.label) {
            return this.item.label;
        }
        return ' ';
    }
    onPlaceChildren(l15, m15, n15) {
        m15.forEach((o15) => {
            o15.layout({ x: 0, y: 0 });
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
            let k15 = this.getUIContext();
            this.isFollowingSystemFontScale = k15.isFollowingSystemFontScale();
            this.maxFontScale = k15.getMaxFontScale();
        }
        catch (h15) {
            let i15 = h15?.code;
            let j15 = h15?.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Failed to init fontsizescale info, cause, code: ${i15}, message: ${j15}`);
        }
        this.fontSize = this.decideFontScale();
    }
    onFontSizeUpdated() {
        this.buttonGestureModifier.fontSize = this.fontSize;
    }
    decideFontScale() {
        try {
            let g15 = this.getUIContext();
            this.systemFontScale = g15.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(this.systemFontScale, this.maxFontScale);
        }
        catch (d15) {
            let e15 = d15?.code;
            let f15 = d15?.message;
            hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${e15}, message: ${f15}`);
            return 1;
        }
    }
    initialRender() {
        this.observeComponentCreation2((x13, y13) => {
            If.create();
            if (this.isPopup) {
                this.ifElseBranchUpdateFunction(0, () => {
                    if (!If.canRetake(`ComposeTitleBar_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`)) {
                        this.observeComponentCreation2((y14, z14) => {
                            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
                            Button.id(`ComposeTitleBar_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`);
                            Button.accessibilityText(this.getAccessibilityReadText());
                            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
                            Button.accessibilityDescription(this.item?.accessibilityDescription);
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
                            Button.onHover((c15) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnHover = c15;
                            });
                            Button.onKeyEvent((b15) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (b15.keyCode !== KeyCode.KEYCODE_ENTER &&
                                    b15.keyCode !== KeyCode.KEYCODE_SPACE) {
                                    return;
                                }
                                if (b15.type === KeyType.Down) {
                                    this.isOnClick = true;
                                }
                                if (b15.type === KeyType.Up) {
                                    this.isOnClick = false;
                                }
                            });
                            Button.onTouch((a15) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (a15.type === TouchType.Down) {
                                    this.isOnClick = true;
                                }
                                if (a15.type === TouchType.Up || a15.type === TouchType.Cancel) {
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
                        this.observeComponentCreation2((o14, p14) => {
                            If.create();
                            if (this.item?.symbolStyle) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((w14, x14) => {
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
                                    this.observeComponentCreation2((q14, r14) => {
                                        If.create();
                                        if (Util.isSymbolResource(this.item.value)) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((u14, v14) => {
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
                                                this.observeComponentCreation2((s14, t14) => {
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
                        this.observeComponentCreation2((j14, k14) => {
                            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
                            Button.id(`ComposeTitleBar_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`);
                            Button.accessibilityText(this.getAccessibilityReadText());
                            Button.accessibilityLevel(this.item?.accessibilityLevel ?? 'auto');
                            Button.accessibilityDescription(this.item?.accessibilityDescription);
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
                            Button.onHover((n14) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                this.isOnHover = n14;
                            });
                            Button.onKeyEvent((m14) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (m14.keyCode !== KeyCode.KEYCODE_ENTER &&
                                    m14.keyCode !== KeyCode.KEYCODE_SPACE) {
                                    return;
                                }
                                if (m14.type === KeyType.Down) {
                                    this.isOnClick = true;
                                }
                                if (m14.type === KeyType.Up) {
                                    this.isOnClick = false;
                                }
                            });
                            Button.onTouch((l14) => {
                                if (!this.item?.isEnabled) {
                                    return;
                                }
                                if (l14.type === TouchType.Down) {
                                    this.isOnClick = true;
                                }
                                if (l14.type === TouchType.Up || l14.type === TouchType.Cancel) {
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
                        this.observeComponentCreation2((z13, a14) => {
                            If.create();
                            if (this.item?.symbolStyle) {
                                this.ifElseBranchUpdateFunction(0, () => {
                                    this.observeComponentCreation2((h14, i14) => {
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
                                    this.observeComponentCreation2((b14, c14) => {
                                        If.create();
                                        if (Util.isSymbolResource(this.item.value)) {
                                            this.ifElseBranchUpdateFunction(0, () => {
                                                this.observeComponentCreation2((f14, g14) => {
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
                                                this.observeComponentCreation2((d14, e14) => {
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
    constructor(r13, s13, t13, u13 = -1, v13 = undefined, w13) {
        super(r13, t13, u13, w13);
        if (typeof v13 === 'function') {
            this.paramsGenerator_ = v13;
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
        this.setInitiallyProvidedValue(s13);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(q13) {
        if (q13.itemComposeTitleDialog !== undefined) {
            this.itemComposeTitleDialog = q13.itemComposeTitleDialog;
        }
        if (q13.callbackId !== undefined) {
            this.callbackId = q13.callbackId;
        }
        if (q13.composeTitleBarDialog !== undefined) {
            this.composeTitleBarDialog = q13.composeTitleBarDialog;
        }
        if (q13.mainWindowStage !== undefined) {
            this.mainWindowStage = q13.mainWindowStage;
        }
        if (q13.controller !== undefined) {
            this.controller = q13.controller;
        }
        if (q13.minFontSize !== undefined) {
            this.minFontSize = q13.minFontSize;
        }
        if (q13.maxFontSize !== undefined) {
            this.maxFontSize = q13.maxFontSize;
        }
        if (q13.screenWidth !== undefined) {
            this.screenWidth = q13.screenWidth;
        }
        if (q13.verticalScreenLines !== undefined) {
            this.verticalScreenLines = q13.verticalScreenLines;
        }
        if (q13.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = q13.horizontalsScreenLines;
        }
        if (q13.fontSize !== undefined) {
            this.fontSize = q13.fontSize;
        }
        if (q13.maxLines !== undefined) {
            this.maxLines = q13.maxLines;
        }
        if (q13.cancel !== undefined) {
            this.cancel = q13.cancel;
        }
        if (q13.confirm !== undefined) {
            this.confirm = q13.confirm;
        }
    }
    updateStateVars(p13) {
    }
    purgeVariableDependenciesOnElmtId(o13) {
        this.__mainWindow.purgeDependencyOnElmtId(o13);
        this.__fontSize.purgeDependencyOnElmtId(o13);
        this.__maxLines.purgeDependencyOnElmtId(o13);
        this.__windowStandardHeight.purgeDependencyOnElmtId(o13);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(n13) {
        this.controller = n13;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(m13) {
        this.__mainWindow.set(m13);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(l13) {
        this.__fontSize.set(l13);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(k13) {
        this.__maxLines.set(k13);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(j13) {
        this.__windowStandardHeight.set(j13);
    }
    initialRender() {
        this.observeComponentCreation2((f12, g12) => {
            If.create();
            if (this.composeTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h13, i13) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true });
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Column);
                    this.observeComponentCreation2((x12, y12) => {
                        If.create();
                        if (this.itemComposeTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((f13, g13) => {
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
                                this.observeComponentCreation2((z12, a13) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((d13, e13) => {
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
                                            this.observeComponentCreation2((b13, c13) => {
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
                    this.observeComponentCreation2((v12, w12) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((t12, u12) => {
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
                    this.observeComponentCreation2((r12, s12) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true });
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((h12, i12) => {
                        If.create();
                        if (this.itemComposeTitleDialog.symbolStyle) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((p12, q12) => {
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
                                this.observeComponentCreation2((j12, k12) => {
                                    If.create();
                                    if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((n12, o12) => {
                                                SymbolGlyph.create(this.itemComposeTitleDialog.value);
                                                SymbolGlyph.fontSize(IMAGE_SIZE);
                                                SymbolGlyph.fontColor([{ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }]);
                                            }, SymbolGlyph);
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((l12, m12) => {
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
        try {
            let c12 = this.getUIContext().getHostContext();
            this.mainWindowStage = c12.windowStage.getMainWindowSync();
            let d12 = this.mainWindowStage.getWindowProperties();
            let e12 = d12.windowRect;
            if (px2vp(e12.height) > this.screenWidth) {
                this.maxLines = this.verticalScreenLines;
            } else {
                this.maxLines = this.horizontalsScreenLines;
            }
        } catch (u18) {
            let v18 = u18?.code;
            let w18 = u18?.message;
            hilog.error(0x3900, 'ComposeTitleBar',
                `Failed to init getMainWindowSync info, cause, code: ${v18}, message: ${w18}`);
        }
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export default { ComposeTitleBar };