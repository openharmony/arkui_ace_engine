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
const hilog = requireNapi('hilog');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const resourceManager = requireNapi('resourceManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
export var EditableLeftIconType;
(function (r8) {
    r8[r8['Back'] = 0] = 'Back';
    r8[r8['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (q8) {
    q8[q8['Image'] = 0] = 'Image';
    q8[q8['Icon'] = 1] = 'Icon';
    q8[q8['LeftIcon'] = 2] = 'LeftIcon';
})(ItemType || (ItemType = {}));
const PUBLIC_CANCEL = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_cancel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_OK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_ok'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_compnent_titlebar_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
class EditableTitleBarTheme {
    constructor() {
        this.iconColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconBackgroundColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconBackgroundPressedColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_pressed_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconBackgroundHoverColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_hover_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.iconBackgroundFocusOutlineColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_focus_outline_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.titleColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_title_tertiary_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        this.subTitleColor = { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_subheader_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
    }
}
export class EditableTitleBar extends ViewPU {
    constructor(k8, l8, m8, n8 = -1, o8 = undefined, p8) {
        super(k8, m8, n8, p8);
        if (typeof o8 === 'function') {
            this.paramsGenerator_ = o8;
        }
        this.leftIconStyle = EditableLeftIconType.Back;
        this.title = '';
        this.subtitle = '';
        this.isSaveIconRequired = true;
        this.imageItem = undefined;
        this.menuItems = undefined;
        this.options = {
            safeAreaTypes: [SafeAreaType.SYSTEM],
            safeAreaEdges: [SafeAreaEdge.TOP],
        };
        this.onSave = undefined;
        this.onCancel = undefined;
        this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, 'titleMaxWidth');
        this.__contentMargin = new ObservedPropertyObjectPU(undefined, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0),
        }, this, 'titleBarMargin');
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.setInitiallyProvidedValue(l8);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(j8) {
        if (j8.leftIconStyle !== undefined) {
            this.leftIconStyle = j8.leftIconStyle;
        }
        if (j8.title !== undefined) {
            this.title = j8.title;
        }
        if (j8.subtitle !== undefined) {
            this.subtitle = j8.subtitle;
        }
        if (j8.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = j8.isSaveIconRequired;
        }
        if (j8.imageItem !== undefined) {
            this.imageItem = j8.imageItem;
        }
        if (j8.menuItems !== undefined) {
            this.menuItems = j8.menuItems;
        }
        if (j8.options !== undefined) {
            this.options = j8.options;
        }
        if (j8.onSave !== undefined) {
            this.onSave = j8.onSave;
        }
        if (j8.onCancel !== undefined) {
            this.onCancel = j8.onCancel;
        }
        if (j8.titleMaxWidth !== undefined) {
            this.titleMaxWidth = j8.titleMaxWidth;
        }
        if (j8.contentMargin !== undefined) {
            this.contentMargin = j8.contentMargin;
        }
        if (j8.titleBarMargin !== undefined) {
            this.titleBarMargin = j8.titleBarMargin;
        }
        if (j8.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = j8.editableTitleBarTheme;
        }
    }
    updateStateVars(i8) {
    }
    purgeVariableDependenciesOnElmtId(h8) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(h8);
        this.__contentMargin.purgeDependencyOnElmtId(h8);
        this.__titleBarMargin.purgeDependencyOnElmtId(h8);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(h8);
    }
    aboutToBeDeleted() {
        this.__titleMaxWidth.aboutToBeDeleted();
        this.__contentMargin.aboutToBeDeleted();
        this.__titleBarMargin.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get titleMaxWidth() {
        return this.__titleMaxWidth.get();
    }
    set titleMaxWidth(g8) {
        this.__titleMaxWidth.set(g8);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(f8) {
        this.__contentMargin.set(f8);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(e8) {
        this.__titleBarMargin.set(e8);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(d8) {
        this.__editableTitleBarTheme.set(d8);
    }
    onWillApplyTheme(c8) {
        this.editableTitleBarTheme.iconColor = c8.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = c8.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = c8.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundColor = c8.colors.compBackgroundTertiary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = c8.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = c8.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = c8.colors.interactiveFocus;
    }
    initialRender() {
        this.observeComponentCreation2((a8, b8) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.width('100%');
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes, this.options.safeAreaEdges);
        }, Flex);
        this.observeComponentCreation2((t7, u7) => {
            GridRow.create({
                columns: 1,
                breakpoints: { reference: BreakpointsReference.ComponentSize },
            });
            GridRow.onBreakpointChange((z7) => {
                this.titleBarMargin = updateTitleBarMargin(z7, this.contentMargin);
            });
            GridRow.margin(ObservedObject.GetRawObject(this.titleBarMargin));
            GridRow.height(EditableTitleBar.totalHeight);
            GridRow.onSizeChange((x7, y7) => {
                this.titleMaxWidth = updateTitleWidth(this.isSaveIconRequired, this.imageItem, this.menuItems, y7);
            });
        }, GridRow);
        this.observeComponentCreation2((r7, s7) => {
            GridCol.create({});
        }, GridCol);
        {
            this.observeComponentCreation2((l7, m7) => {
                if (m7) {
                    let n7 = new TitleBarSection(this, {
                        leftIconStyle: this.leftIconStyle,
                        imageItem: this.imageItem,
                        title: this.title,
                        subtitle: this.subtitle,
                        menuItems: this.menuItems,
                        isSaveIconRequired: this.isSaveIconRequired,
                        onSave: this.onSave,
                        onCancel: this.onCancel,
                        options: this.options,
                        titleMaxWidth: this.__titleMaxWidth
                    }, undefined, l7, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 129, col: 11 });
                    ViewPU.create(n7);
                    let o7 = () => {
                        return {
                            leftIconStyle: this.leftIconStyle,
                            imageItem: this.imageItem,
                            title: this.title,
                            subtitle: this.subtitle,
                            menuItems: this.menuItems,
                            isSaveIconRequired: this.isSaveIconRequired,
                            onSave: this.onSave,
                            onCancel: this.onCancel,
                            options: this.options,
                            titleMaxWidth: this.titleMaxWidth
                        };
                    };
                    n7.paramsGenerator_ = o7;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(l7, {});
                }
            }, { name: 'TitleBarSection' });
        }
        GridCol.pop();
        GridRow.pop();
        Flex.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
EditableTitleBar.maxCountOfExtraItems = 3;
EditableTitleBar.maxOtherCountOfExtraItems = 2;
EditableTitleBar.countOfImageItem = 0;
EditableTitleBar.countOfSaveIcon = 0;
EditableTitleBar.commonOne = 1;
EditableTitleBar.commonZero = 0;
EditableTitleBar.noneColor = '#00000000';
EditableTitleBar.defaultHeight = getNumberByResource('titlebar_default_height');
EditableTitleBar.default_margin_level1 = getNumberByResource('margin_level1');
EditableTitleBar.default_margin_level2 = getNumberByResource('margin_level2');
EditableTitleBar.default_margin_level3 = getNumberByResource('margin_level3');
EditableTitleBar.default_title_padding = getNumberByResource('titlebar_icon_background_space_horizontal');
EditableTitleBar.totalHeight = EditableTitleBar.defaultHeight === 0 ? 56 : EditableTitleBar.defaultHeight;
EditableTitleBar.margin_level1 = EditableTitleBar.default_margin_level1 === 0 ? 12 : EditableTitleBar.default_margin_level1;
EditableTitleBar.margin_level2 = EditableTitleBar.default_margin_level2 === 0 ? 24 : EditableTitleBar.default_margin_level2;
EditableTitleBar.margin_level3 = EditableTitleBar.default_margin_level3 === 0 ? 32 : EditableTitleBar.default_margin_level3;
EditableTitleBar.titlePadding = EditableTitleBar.default_title_padding === 0 ? 2 : EditableTitleBar.default_title_padding;
class TitleBarSection extends ViewPU {
    constructor(b7, c7, d7, e7 = -1, f7 = undefined, g7) {
        super(b7, d7, e7, g7);
        if (typeof f7 === 'function') {
            this.paramsGenerator_ = f7;
        }
        this.leftIconStyle = EditableLeftIconType.Back;
        this.title = '';
        this.subtitle = '';
        this.isSaveIconRequired = true;
        this.imageItem = undefined;
        this.menuItems = undefined;
        this.options = {
            safeAreaTypes: [SafeAreaType.SYSTEM],
            safeAreaEdges: [SafeAreaEdge.TOP],
        };
        this.onSave = undefined;
        this.onCancel = undefined;
        this.__titleMaxWidth = new SynchedPropertySimpleTwoWayPU(c7.titleMaxWidth, this, 'titleMaxWidth');
        this.__backActive = new ObservedPropertySimplePU(false, this, 'backActive');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.setInitiallyProvidedValue(c7);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a7) {
        if (a7.leftIconStyle !== undefined) {
            this.leftIconStyle = a7.leftIconStyle;
        }
        if (a7.title !== undefined) {
            this.title = a7.title;
        }
        if (a7.subtitle !== undefined) {
            this.subtitle = a7.subtitle;
        }
        if (a7.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = a7.isSaveIconRequired;
        }
        if (a7.imageItem !== undefined) {
            this.imageItem = a7.imageItem;
        }
        if (a7.menuItems !== undefined) {
            this.menuItems = a7.menuItems;
        }
        if (a7.options !== undefined) {
            this.options = a7.options;
        }
        if (a7.onSave !== undefined) {
            this.onSave = a7.onSave;
        }
        if (a7.onCancel !== undefined) {
            this.onCancel = a7.onCancel;
        }
        if (a7.backActive !== undefined) {
            this.backActive = a7.backActive;
        }
    }
    updateStateVars(z6) {
    }
    purgeVariableDependenciesOnElmtId(y6) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(y6);
        this.__backActive.purgeDependencyOnElmtId(y6);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(y6);
    }
    aboutToBeDeleted() {
        this.__titleMaxWidth.aboutToBeDeleted();
        this.__backActive.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get titleMaxWidth() {
        return this.__titleMaxWidth.get();
    }
    set titleMaxWidth(x6) {
        this.__titleMaxWidth.set(x6);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(w6) {
        this.__backActive.set(w6);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(v6) {
        this.__editableTitleBarTheme.set(v6);
    }
    initialRender() {
        this.observeComponentCreation2((t6, u6) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((y5, z5) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r6, s6) => {
                        Navigator.create();
                        Navigator.active(this.backActive);
                    }, Navigator);
                    Navigator.pop();
                    {
                        this.observeComponentCreation2((l6, m6) => {
                            if (m6) {
                                let n6 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, l6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 191, col: 9 });
                                ViewPU.create(n6);
                                let o6 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                        },
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                n6.paramsGenerator_ = o6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l6, {});
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((c6, d6) => {
                            if (d6) {
                                let e6 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, c6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 200, col: 9 });
                                ViewPU.create(e6);
                                let f6 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                        },
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                e6.paramsGenerator_ = f6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(c6, {});
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((n5, o5) => {
            If.create();
            if (this.imageItem !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((s5, t5) => {
                            if (t5) {
                                let u5 = new ImageMenuItem(this, {
                                    item: this.imageItem,
                                    attribute: ItemType.Image,
                                }, undefined, s5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 210, col: 9 });
                                ViewPU.create(u5);
                                let v5 = () => {
                                    return {
                                        item: this.imageItem,
                                        attribute: ItemType.Image
                                    };
                                };
                                u5.paramsGenerator_ = v5;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(s5, {});
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
        this.observeComponentCreation2((l5, m5) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.vp(EditableTitleBar.titlePadding),
            });
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
        }, Column);
        this.observeComponentCreation2((j5, k5) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((h5, i5) => {
            Text.create(this.title);
            Text.maxFontSize({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_title_tertiary_size'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.minFontSize({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_subheader_size'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.fontColor(this.editableTitleBarTheme.titleColor);
            Text.maxLines(this.subtitle ? TitleBarSection.maxLineOne : TitleBarSection.maxLineTwo);
            Text.fontWeight(FontWeight.Bold);
            Text.textAlign(TextAlign.Start);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width(this.titleMaxWidth);
            Text.heightAdaptivePolicy(this.subtitle ? TextHeightAdaptivePolicy.MAX_LINES_FIRST :
                TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.constraintSize({
                maxHeight: this.subtitle ? TitleBarSection.maxMainTitleHeight : EditableTitleBar.totalHeight,
            });
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((x4, y4) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((f5, g5) => {
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((d5, e5) => {
                        Text.create(this.subtitle);
                        Text.maxFontSize({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_subheader_size'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.minFontSize({ 'id': -1, 'type': 10002, params: ['sys.float.Caption_S'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                        Text.fontColor(this.editableTitleBarTheme.subTitleColor);
                        Text.maxLines(1);
                        Text.fontWeight(FontWeight.Regular);
                        Text.textAlign(TextAlign.Start);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.width(this.titleMaxWidth);
                        Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST);
                        Text.constraintSize({
                            maxHeight: this.title ? TitleBarSection.maxSubTitleHeight : EditableTitleBar.totalHeight,
                        });
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
        {
            this.observeComponentCreation2((r4, s4) => {
                if (s4) {
                    let t4 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                    }, undefined, r4, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 265, col: 7 });
                    ViewPU.create(t4);
                    let u4 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired
                        };
                    };
                    t4.paramsGenerator_ = u4;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(r4, {});
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
TitleBarSection.maxMainTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * 0.65;
TitleBarSection.maxSubTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * 0.35;
TitleBarSection.maxLineOne = 1;
TitleBarSection.maxLineTwo = 2;
class EditableTitleBarMenuSection extends ViewPU {
    constructor(d4, e4, f4, g4 = -1, h4 = undefined, i4) {
        super(d4, f4, g4, i4);
        if (typeof h4 === 'function') {
            this.paramsGenerator_ = h4;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.setInitiallyProvidedValue(e4);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c4) {
        if (c4.menuItems !== undefined) {
            this.menuItems = c4.menuItems;
        }
        if (c4.onSave !== undefined) {
            this.onSave = c4.onSave;
        }
        if (c4.isSaveEnabled !== undefined) {
            this.isSaveEnabled = c4.isSaveEnabled;
        }
    }
    updateStateVars(b4) {
    }
    purgeVariableDependenciesOnElmtId(a4) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    initialRender() {
        this.observeComponentCreation2((y3, z3) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((w3, x3) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((e3, f3) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j3, k3) => {
                        ForEach.create();
                        const l3 = n3 => {
                            const o3 = n3;
                            {
                                this.observeComponentCreation2((q3, r3) => {
                                    if (r3) {
                                        let s3 = new ImageMenuItem(this, {
                                            item: o3,
                                            attribute: ItemType.Icon,
                                        }, undefined, q3, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 288, col: 15 });
                                        ViewPU.create(s3);
                                        let t3 = () => {
                                            return {
                                                item: o3,
                                                attribute: ItemType.Icon
                                            };
                                        };
                                        s3.paramsGenerator_ = t3;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(q3, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(j3, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), l3);
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
        this.observeComponentCreation2((t2, u2) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((y2, z2) => {
                            if (z2) {
                                let a3 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    attribute: ItemType.Icon,
                                }, undefined, y2, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 295, col: 11 });
                                ViewPU.create(a3);
                                let b3 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                        },
                                        attribute: ItemType.Icon
                                    };
                                };
                                a3.paramsGenerator_ = b3;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(y2, {});
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
        Row.pop();
        Column.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class ImageMenuItem extends ViewPU {
    constructor(j2, k2, l2, m2 = -1, n2 = undefined, o2) {
        super(j2, l2, m2, o2);
        if (typeof n2 === 'function') {
            this.paramsGenerator_ = n2;
        }
        this.item = {
            value: '',
            isEnabled: true,
        };
        this.attribute = ItemType.Image;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.setInitiallyProvidedValue(k2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(i2) {
        if (i2.item !== undefined) {
            this.item = i2.item;
        }
        if (i2.attribute !== undefined) {
            this.attribute = i2.attribute;
        }
        if (i2.isOnFocus !== undefined) {
            this.isOnFocus = i2.isOnFocus;
        }
        if (i2.isOnHover !== undefined) {
            this.isOnHover = i2.isOnHover;
        }
        if (i2.isOnClick !== undefined) {
            this.isOnClick = i2.isOnClick;
        }
    }
    updateStateVars(h2) {
    }
    purgeVariableDependenciesOnElmtId(g2) {
        this.__isOnFocus.purgeDependencyOnElmtId(g2);
        this.__isOnHover.purgeDependencyOnElmtId(g2);
        this.__isOnClick.purgeDependencyOnElmtId(g2);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(g2);
    }
    aboutToBeDeleted() {
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(f2) {
        this.__isOnFocus.set(f2);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(e2) {
        this.__isOnHover.set(e2);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(d2) {
        this.__isOnClick.set(d2);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(c2) {
        this.__editableTitleBarTheme.set(c2);
    }
    getFgColor() {
        if (this.isOnClick) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_pressed_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.isOnHover) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_hover_color'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return EditableTitleBar.noneColor;
        }
    }
    getBgColor() {
        if (this.isOnClick) {
            return this.editableTitleBarTheme.iconBackgroundPressedColor;
        }
        else if (this.isOnHover) {
            return this.editableTitleBarTheme.iconBackgroundHoverColor;
        }
        else {
            return this.editableTitleBarTheme.iconBackgroundColor;
        }
    }
    IconBuilder(m1 = null) {
        this.observeComponentCreation2((r1, s1) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneHeight);
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.margin({
                start: LengthMetrics.vp(this.attribute === ItemType.LeftIcon ? EditableTitleBar.commonZero :
                    ImageMenuItem.iconBackgroundSpaceHorizontal),
            });
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_focus_outline_weight'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState();
            Button.onFocus(() => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((b2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = b2;
            });
            Button.onKeyEvent((a2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (a2.keyCode !== KeyCode.KEYCODE_ENTER && a2.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (a2.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (a2.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((z1) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (z1.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (z1.type === TouchType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
        }, Button);
        this.observeComponentCreation2((p1, q1) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.fillColor(this.editableTitleBarTheme.iconColor);
            Image.focusable(this.item.isEnabled);
            Image.enabled(this.item.isEnabled);
            Image.matchTextDirection(this.item.value === PUBLIC_BACK ? true : false);
        }, Image);
        Button.pop();
    }
    ImageBuilder(t = null) {
        this.observeComponentCreation2((k1, l1) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.vp(ImageMenuItem.iconBackgroundSpaceHorizontal),
            });
        }, Stack);
        this.observeComponentCreation2((i1, j1) => {
            Image.create(this.item.value);
            Image.width(ImageMenuItem.imageHotZoneWidth);
            Image.height(ImageMenuItem.imageHotZoneHeight);
            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((x, y) => {
            Button.createWithLabel({ type: ButtonType.Circle });
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneHeight);
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(EditableTitleBar.noneColor);
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_focus_outline_weight'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState();
            Button.onFocus(() => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnFocus = true;
            });
            Button.onBlur(() => this.isOnFocus = false);
            Button.onHover((h1) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = h1;
            });
            Button.onKeyEvent((g1) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (g1.keyCode !== KeyCode.KEYCODE_ENTER && g1.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (g1.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (g1.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((f1) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (f1.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (f1.type === TouchType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((p, q) => {
            If.create();
            if (this.attribute === ItemType.Icon || this.attribute === ItemType.LeftIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconBuilder.bind(this)(this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ImageBuilder.bind(this)(this);
                });
            }
        }, If);
        If.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
ImageMenuItem.imageHotZoneWidth = getNumberByResource('titlebar_icon_background_width');
ImageMenuItem.imageHotZoneHeight = getNumberByResource('titlebar_icon_background_height');
ImageMenuItem.iconBackgroundSpaceHorizontal = getNumberByResource('titlebar_icon_background_space_horizontal');
function getNumberByResource(k) {
    try {
        return resourceManager.getSystemResourceManager().getNumberByName(k);
    }
    catch (l) {
        let m = l.code;
        let n = l.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${m},message:${n}`);
        return EditableTitleBar.commonZero;
    }
}
function updateTitleWidth(d, e, f, g) {
    let h = EditableTitleBar.commonZero;
    let i = 0;
    if (d) {
        h = EditableTitleBar.maxOtherCountOfExtraItems;
        EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonOne;
    }
    else {
        h = EditableTitleBar.maxCountOfExtraItems;
        EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonZero;
    }
    if (e) {
        EditableTitleBar.countOfImageItem = EditableTitleBar.commonOne;
    }
    else {
        EditableTitleBar.countOfImageItem = EditableTitleBar.commonZero;
    }
    let j = Number(g.width);
    j = j - EditableTitleBar.titlePadding - ImageMenuItem.imageHotZoneWidth;
    if (f === undefined) {
        i = j - EditableTitleBar.countOfImageItem *
            (ImageMenuItem.imageHotZoneWidth + ImageMenuItem.iconBackgroundSpaceHorizontal) -
            EditableTitleBar.countOfSaveIcon *
                (ImageMenuItem.imageHotZoneWidth + ImageMenuItem.iconBackgroundSpaceHorizontal);
        return i;
    }
    if (f?.length >= EditableTitleBar.maxCountOfExtraItems) {
        i = j -
            ImageMenuItem.imageHotZoneWidth * EditableTitleBar.maxCountOfExtraItems -
            EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
            ImageMenuItem.iconBackgroundSpaceHorizontal *
                (h + EditableTitleBar.countOfSaveIcon +
                    EditableTitleBar.countOfImageItem);
    }
    else {
        i = j -
            ImageMenuItem.imageHotZoneWidth * f?.length -
            ImageMenuItem.imageHotZoneWidth * EditableTitleBar.countOfSaveIcon -
            EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
            ImageMenuItem.iconBackgroundSpaceHorizontal *
                (f?.length + EditableTitleBar.countOfSaveIcon +
                    EditableTitleBar.countOfImageItem);
    }
    return i;
}
function updateTitleBarMargin(a, b) {
    let c = {};
    if (a === 'xs' || a === 'sm') {
        c = {
            start: b?.start ?? LengthMetrics.vp(EditableTitleBar.margin_level1),
            end: b?.end ?? LengthMetrics.vp(EditableTitleBar.margin_level1),
            top: b?.top ?? LengthMetrics.vp(0),
            bottom: b?.bottom ?? LengthMetrics.vp(0),
        };
    }
    else if (a === 'md') {
        c = {
            start: b?.start ?? LengthMetrics.vp(EditableTitleBar.margin_level2),
            end: b?.end ?? LengthMetrics.vp(EditableTitleBar.margin_level2),
            top: b?.top ?? LengthMetrics.vp(0),
            bottom: b?.bottom ?? LengthMetrics.vp(0),
        };
    }
    else {
        c = {
            start: b?.start ?? LengthMetrics.vp(EditableTitleBar.margin_level3),
            end: b?.end ?? LengthMetrics.vp(EditableTitleBar.margin_level3),
            top: b?.top ?? LengthMetrics.vp(0),
            bottom: b?.bottom ?? LengthMetrics.vp(0),
        };
    }
    return c;
}

export default {
    EditableLeftIconType: EditableLeftIconType,
    EditableTitleBar: EditableTitleBar,
};