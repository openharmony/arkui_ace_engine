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
const hilog = requireNapi('hilog');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const resourceManager = requireNapi('resourceManager');
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
export var EditableLeftIconType;
(function (j10) {
    j10[j10['Back'] = 0] = 'Back';
    j10[j10['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (i10) {
    i10[i10['Image'] = 0] = 'Image';
    i10[i10['Icon'] = 1] = 'Icon';
    i10[i10['LeftIcon'] = 2] = 'LeftIcon';
})(ItemType || (ItemType = {}));
const PUBLIC_CANCEL = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_cancel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_OK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_ok'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const PUBLIC_BACK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_compnent_titlebar_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
const DEFAULT_TITLE_BAR_HEIGHT = 56;
const DEFAULT_TITLE_PADDING = 2;
const MAX_LINE_ONE = 1;
const MAX_LINES_TWO = 2;
const MAX_MAIN_TITLE_PERCENT = 0.65;
const MAX_SUB_TITLE_PERCENT = 0.35;
const MIN_SUBTITLE_SIZE = '10.0vp';
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const TITLE_VP = 20;
const SUBTITLE_VP = 14;
const TITLE_F = getNumberByResource(125831095) ?? 20;
const SUBTITLE_F = getNumberByResource(125831097) ?? 14;
const TITLE_F_VP = (TITLE_F > 0 ? TITLE_F : TITLE_VP) + 'vp';
const SUBTITLE_F_VP = (SUBTITLE_F > 0 ? SUBTITLE_F : SUBTITLE_VP) + 'vp';
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
    constructor(c10, d10, e10, f10 = -1, g10 = undefined, h10) {
        super(c10, e10, f10, h10);
        if (typeof g10 === 'function') {
            this.paramsGenerator_ = g10;
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
        this.constraintWidth = 0;
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(d10.contentMargin, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_left'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_right'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
        }, this, 'titleBarMargin');
        this.__backActive = new ObservedPropertySimplePU(false, this, 'backActive');
        this.__fontSize = new ObservedPropertySimplePU(1, this, 'fontSize');
        this.setInitiallyProvidedValue(d10);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(b10) {
        if (b10.leftIconStyle !== undefined) {
            this.leftIconStyle = b10.leftIconStyle;
        }
        if (b10.title !== undefined) {
            this.title = b10.title;
        }
        if (b10.subtitle !== undefined) {
            this.subtitle = b10.subtitle;
        }
        if (b10.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = b10.isSaveIconRequired;
        }
        if (b10.imageItem !== undefined) {
            this.imageItem = b10.imageItem;
        }
        if (b10.menuItems !== undefined) {
            this.menuItems = b10.menuItems;
        }
        if (b10.options !== undefined) {
            this.options = b10.options;
        }
        if (b10.onSave !== undefined) {
            this.onSave = b10.onSave;
        }
        if (b10.onCancel !== undefined) {
            this.onCancel = b10.onCancel;
        }
        if (b10.constraintWidth !== undefined) {
            this.constraintWidth = b10.constraintWidth;
        }
        if (b10.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = b10.editableTitleBarTheme;
        }
        if (b10.titleBarMargin !== undefined) {
            this.titleBarMargin = b10.titleBarMargin;
        }
        if (b10.backActive !== undefined) {
            this.backActive = b10.backActive;
        }
        if (b10.fontSize !== undefined) {
            this.fontSize = b10.fontSize;
        }
    }
    updateStateVars(a10) {
        this.__contentMargin.reset(a10.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(z9) {
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(z9);
        this.__contentMargin.purgeDependencyOnElmtId(z9);
        this.__titleBarMargin.purgeDependencyOnElmtId(z9);
        this.__backActive.purgeDependencyOnElmtId(z9);
        this.__fontSize.purgeDependencyOnElmtId(z9);
    }
    aboutToBeDeleted() {
        this.__editableTitleBarTheme.aboutToBeDeleted();
        this.__contentMargin.aboutToBeDeleted();
        this.__titleBarMargin.aboutToBeDeleted();
        this.__backActive.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(y9) {
        this.__editableTitleBarTheme.set(y9);
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(x9) {
        this.__contentMargin.set(x9);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(w9) {
        this.__titleBarMargin.set(w9);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(v9) {
        this.__backActive.set(v9);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u9) {
        this.__fontSize.set(u9);
    }
    onWillApplyTheme(t9) {
        this.editableTitleBarTheme.iconColor = t9.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = t9.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = t9.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundColor = t9.colors.compBackgroundTertiary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = t9.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = t9.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = t9.colors.interactiveFocus;
    }
    initialRender() {
        this.observeComponentCreation2((r9, s9) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes, this.options.safeAreaEdges);
        }, Flex);
        this.observeComponentCreation2((p9, q9) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((n9, o9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((g9, h9) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l9, m9) => {
                        Row.create();
                        Row.flexShrink(0);
                    }, Row);
                    this.imageItemLayout.bind(this)();
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((e9, f9) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)();
        Row.pop();
        this.observeComponentCreation2((c9, d9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)();
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    imageItemLayout(o8 = null) {
        {
            this.observeComponentCreation2((q8, r8) => {
                if (r8) {
                    let s8 = new ImageMenuItem(this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, q8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 186, col: 5 });
                    ViewPU.create(s8);
                    let t8 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    s8.paramsGenerator_ = t8;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q8, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    leftIconLayout(r7 = null) {
        this.observeComponentCreation2((t7, u7) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m8, n8) => {
                        Navigator.create();
                        Navigator.active(this.backActive);
                    }, Navigator);
                    Navigator.pop();
                    {
                        this.observeComponentCreation2((g8, h8) => {
                            if (h8) {
                                let i8 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, g8, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 198, col: 7 });
                                ViewPU.create(i8);
                                let j8 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                i8.paramsGenerator_ = j8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(g8, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((x7, y7) => {
                            if (y7) {
                                let z7 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, x7, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 208, col: 7 });
                                ViewPU.create(z7);
                                let a8 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                z7.paramsGenerator_ = a8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(x7, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: 'ImageMenuItem' });
                    }
                });
            }
        }, If);
        If.pop();
    }
    titleLayout(w6 = null) {
        this.observeComponentCreation2((p7, q7) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.vp(getNumberByResource(125831103) ?? 8),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((n7, o7) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((l7, m7) => {
            Text.create(this.title);
            Text.maxFontSize(TITLE_F_VP);
            Text.minFontSize(SUBTITLE_F_VP);
            Text.fontColor(this.editableTitleBarTheme.titleColor);
            Text.maxLines(this.subtitle ? MAX_LINE_ONE : MAX_LINES_TWO);
            Text.fontWeight(FontWeight.Bold);
            Text.textAlign(TextAlign.Start);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.heightAdaptivePolicy(this.subtitle ?
                TextHeightAdaptivePolicy.MAX_LINES_FIRST : TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST);
            Text.constraintSize({
                maxHeight: this.subtitle ? EditableTitleBar.maxMainTitleHeight : EditableTitleBar.totalHeight,
            });
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((b7, c7) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j7, k7) => {
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((h7, i7) => {
                        Text.create(this.subtitle);
                        Text.maxFontSize(SUBTITLE_F_VP);
                        Text.minFontSize(MIN_SUBTITLE_SIZE);
                        Text.fontColor(this.editableTitleBarTheme.subTitleColor);
                        Text.maxLines(MAX_LINE_ONE);
                        Text.fontWeight(FontWeight.Regular);
                        Text.textAlign(TextAlign.Start);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST);
                        Text.constraintSize({
                            maxHeight: this.title ? EditableTitleBar.maxSubTitleHeight : EditableTitleBar.totalHeight,
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
    }
    rightMenuItemsLayout(o6 = null) {
        {
            this.observeComponentCreation2((q6, r6) => {
                if (r6) {
                    let s6 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, q6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 272, col: 5 });
                    ViewPU.create(s6);
                    let t6 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    s6.paramsGenerator_ = t6;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q6, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onPlaceChildren(j6, k6, l6) {
        k6.forEach((n6) => {
            n6.layout({ x: 0, y: 0 });
        });
    }
    onMeasureSize(d6, e6, f6) {
        let g6 = { width: d6.width, height: d6.height };
        e6.forEach((i6) => {
            g6.height = i6.measure(f6).height;
            g6.width = Number(f6.maxWidth);
        });
        return g6;
    }
    rerender() {
        this.updateDirtyElements();
    }
}
EditableTitleBar.maxCountOfExtraItems = 3;
EditableTitleBar.maxOtherCountOfExtraItems = 2;
EditableTitleBar.commonZero = 0;
EditableTitleBar.noneColor = '#00000000';
EditableTitleBar.defaultHeight = getNumberByResource(125831115) ?? 56;
EditableTitleBar.defaultTitlePadding = getNumberByResource(125830920) ?? 2;
EditableTitleBar.totalHeight = EditableTitleBar.defaultHeight === EditableTitleBar.commonZero ? DEFAULT_TITLE_BAR_HEIGHT :
    EditableTitleBar.defaultHeight;
EditableTitleBar.titlePadding = EditableTitleBar.defaultTitlePadding === EditableTitleBar.commonZero ?
    DEFAULT_TITLE_PADDING : EditableTitleBar.defaultTitlePadding;
EditableTitleBar.maxMainTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_MAIN_TITLE_PERCENT;
EditableTitleBar.maxSubTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_SUB_TITLE_PERCENT;
class EditableTitleBarMenuSection extends ViewPU {
    constructor(x5, y5, z5, a6 = -1, b6 = undefined, c6) {
        super(x5, z5, a6, c6);
        if (typeof b6 === 'function') {
            this.paramsGenerator_ = b6;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(y5.fontSize, this, 'fontSize');
        this.setInitiallyProvidedValue(y5);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(w5) {
        if (w5.menuItems !== undefined) {
            this.menuItems = w5.menuItems;
        }
        if (w5.onSave !== undefined) {
            this.onSave = w5.onSave;
        }
        if (w5.isSaveEnabled !== undefined) {
            this.isSaveEnabled = w5.isSaveEnabled;
        }
        if (w5.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(v5) {
        this.__fontSize.reset(v5.fontSize);
    }
    purgeVariableDependenciesOnElmtId(u5) {
        this.__fontSize.purgeDependencyOnElmtId(u5);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(t5) {
        this.__fontSize.set(t5);
    }
    initialRender() {
        this.observeComponentCreation2((r5, s5) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((p5, q5) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((x4, y4) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c5, d5) => {
                        ForEach.create();
                        const e5 = g5 => {
                            const h5 = g5;
                            {
                                this.observeComponentCreation2((j5, k5) => {
                                    if (k5) {
                                        let l5 = new ImageMenuItem(this, {
                                            item: h5,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, j5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 311, col: 15 });
                                        ViewPU.create(l5);
                                        let m5 = () => {
                                            return {
                                                item: h5,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        l5.paramsGenerator_ = m5;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(j5, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(c5, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), e5);
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
        this.observeComponentCreation2((m4, n4) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((r4, s4) => {
                            if (s4) {
                                let t4 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                }, undefined, r4, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 319, col: 11 });
                                ViewPU.create(t4);
                                let u4 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                        },
                                        fontSize: this.fontSize,
                                        attribute: ItemType.Icon
                                    };
                                };
                                t4.paramsGenerator_ = u4;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(r4, {
                                    fontSize: this.fontSize
                                });
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
    constructor(y3, z3, a4, b4 = -1, c4 = undefined, d4) {
        super(y3, a4, b4, d4);
        if (typeof c4 === 'function') {
            this.paramsGenerator_ = c4;
        }
        this.item = {
            value: '',
            isEnabled: true,
            label: '',
        };
        this.attribute = ItemType.Image;
        this.callbackId = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.longPressTime = 500;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(z3.fontSize, this, 'fontSize');
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.__editableTitleBarTheme = this.initializeConsume('editableTitleBarTheme', 'editableTitleBarTheme');
        this.dialogController = new CustomDialogController({
            builder: () => {
                let e4 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 353, col: 14 });
                e4.setController(this.dialogController);
                ViewPU.create(e4);
                let f4 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        itemEditableDialog: this.item,
                        textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                        fontSize: this.fontSize
                    };
                };
                e4.paramsGenerator_ = f4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.setInitiallyProvidedValue(z3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(x3) {
        if (x3.item !== undefined) {
            this.item = x3.item;
        }
        if (x3.attribute !== undefined) {
            this.attribute = x3.attribute;
        }
        if (x3.callbackId !== undefined) {
            this.callbackId = x3.callbackId;
        }
        if (x3.minFontSize !== undefined) {
            this.minFontSize = x3.minFontSize;
        }
        if (x3.maxFontSize !== undefined) {
            this.maxFontSize = x3.maxFontSize;
        }
        if (x3.longPressTime !== undefined) {
            this.longPressTime = x3.longPressTime;
        }
        if (x3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (x3.isOnFocus !== undefined) {
            this.isOnFocus = x3.isOnFocus;
        }
        if (x3.isOnHover !== undefined) {
            this.isOnHover = x3.isOnHover;
        }
        if (x3.isOnClick !== undefined) {
            this.isOnClick = x3.isOnClick;
        }
        if (x3.dialogController !== undefined) {
            this.dialogController = x3.dialogController;
        }
    }
    updateStateVars(w3) {
        this.__fontSize.reset(w3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(v3) {
        this.__fontSize.purgeDependencyOnElmtId(v3);
        this.__isOnFocus.purgeDependencyOnElmtId(v3);
        this.__isOnHover.purgeDependencyOnElmtId(v3);
        this.__isOnClick.purgeDependencyOnElmtId(v3);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(v3);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(u3) {
        this.__fontSize.set(u3);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(t3) {
        this.__isOnFocus.set(t3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(s3) {
        this.__isOnHover.set(s3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(r3) {
        this.__isOnClick.set(r3);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(q3) {
        this.__editableTitleBarTheme.set(q3);
    }
    textDialog() {
        if (this.item.value === PUBLIC_OK) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_save'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.value === PUBLIC_CANCEL) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_cancel'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else if (this.item.value === PUBLIC_BACK) {
            return { 'id': -1, 'type': 10003, params: ['sys.string.icon_back'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' };
        }
        else {
            return this.item.label ? this.item.label : '';
        }
    }
    touchEventAction(p3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (p3.type === TouchType.Down) {
            this.isOnClick = true;
        }
        if (p3.type === TouchType.Up || p3.type === TouchType.Cancel) {
            if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
            }
            this.isOnClick = false;
        }
    }
    keyEventAction(o3) {
        if (!this.item.isEnabled) {
            return;
        }
        if (o3.keyCode !== KeyCode.KEYCODE_ENTER && o3.keyCode !== KeyCode.KEYCODE_SPACE) {
            return;
        }
        if (o3.type === KeyType.Down) {
            this.isOnClick = true;
        }
        if (o3.type === KeyType.Up) {
            this.isOnClick = false;
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
    IconBuilder(v2 = null) {
        this.observeComponentCreation2((a3, b3) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.margin({
                start: this.attribute === ItemType.LeftIcon ? LengthMetrics.vp(EditableTitleBar.commonZero) :
                    LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
            Button.focusOnTouch(true);
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
            Button.onHover((n3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = n3;
            });
            Button.onKeyEvent((m3) => {
                this.keyEventAction(m3);
            });
            Button.onTouch((l3) => {
                this.touchEventAction(l3);
            });
            Button.onClick(() => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: false, duration: this.longPressTime });
            LongPressGesture.onAction((j3) => {
                let k3 = this.getUIContext().getHostContext();
                this.fontSize = k3.config?.fontSizeScale ?? 1;
                if (j3) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            Gesture.pop();
        }, Button);
        this.observeComponentCreation2((y2, z2) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.fillColor(this.editableTitleBarTheme.iconColor);
            Image.focusable(this.item.isEnabled);
            Image.enabled(this.item.isEnabled);
            Image.matchTextDirection(this.item.value === PUBLIC_BACK ? true : false);
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    ImageBuilder(z1 = null) {
        this.observeComponentCreation2((t2, u2) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Stack);
        this.observeComponentCreation2((r2, s2) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((d2, e2) => {
            Button.createWithLabel({ type: ButtonType.Circle });
            Button.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Button.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
            Button.onHover((q2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = q2;
            });
            Button.onKeyEvent((p2) => {
                this.keyEventAction(p2);
            });
            Button.onTouch((o2) => {
                this.touchEventAction(o2);
            });
            Button.onClick(() => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            Gesture.create(GesturePriority.Low);
            LongPressGesture.create({ repeat: false, duration: this.longPressTime });
            LongPressGesture.onAction((m2) => {
                let n2 = this.getUIContext().getHostContext();
                this.fontSize = n2.config?.fontSizeScale ?? 1;
                if (m2) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            Gesture.pop();
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((v1, w1) => {
            If.create();
            if (this.attribute === ItemType.Icon || this.attribute === ItemType.LeftIcon) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconBuilder.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.ImageBuilder.bind(this)();
                });
            }
        }, If);
        If.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
class EditableTitleBarDialog extends ViewPU {
    constructor(m1, n1, o1, p1 = -1, q1 = undefined, r1) {
        super(m1, o1, p1, r1);
        if (typeof q1 === 'function') {
            this.paramsGenerator_ = q1;
        }
        this.itemEditableDialog = {
            value: '',
            isEnabled: true,
        };
        this.callbackId = undefined;
        this.textEditableTitleBarDialog = '';
        this.mainWindowStage = undefined;
        this.controller = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.2;
        this.screenWidth = 640;
        this.verticalScreenLines = 6;
        this.horizontalsScreenLines = 1;
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.__mainWindow = this.createStorageLink('mainWindow', undefined, 'mainWindow');
        this.__fontSize = new SynchedPropertySimpleOneWayPU(n1.fontSize, this, 'fontSize');
        this.__maxLines = new ObservedPropertySimplePU(1, this, 'maxLines');
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, 'windowStandardHeight');
        this.setInitiallyProvidedValue(n1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l1) {
        if (l1.itemEditableDialog !== undefined) {
            this.itemEditableDialog = l1.itemEditableDialog;
        }
        if (l1.callbackId !== undefined) {
            this.callbackId = l1.callbackId;
        }
        if (l1.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = l1.textEditableTitleBarDialog;
        }
        if (l1.mainWindowStage !== undefined) {
            this.mainWindowStage = l1.mainWindowStage;
        }
        if (l1.controller !== undefined) {
            this.controller = l1.controller;
        }
        if (l1.minFontSize !== undefined) {
            this.minFontSize = l1.minFontSize;
        }
        if (l1.maxFontSize !== undefined) {
            this.maxFontSize = l1.maxFontSize;
        }
        if (l1.screenWidth !== undefined) {
            this.screenWidth = l1.screenWidth;
        }
        if (l1.verticalScreenLines !== undefined) {
            this.verticalScreenLines = l1.verticalScreenLines;
        }
        if (l1.horizontalsScreenLines !== undefined) {
            this.horizontalsScreenLines = l1.horizontalsScreenLines;
        }
        if (l1.cancel !== undefined) {
            this.cancel = l1.cancel;
        }
        if (l1.confirm !== undefined) {
            this.confirm = l1.confirm;
        }
        if (l1.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (l1.maxLines !== undefined) {
            this.maxLines = l1.maxLines;
        }
    }
    updateStateVars(k1) {
        this.__fontSize.reset(k1.fontSize);
    }
    purgeVariableDependenciesOnElmtId(j1) {
        this.__mainWindow.purgeDependencyOnElmtId(j1);
        this.__fontSize.purgeDependencyOnElmtId(j1);
        this.__maxLines.purgeDependencyOnElmtId(j1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(j1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(i1) {
        this.controller = i1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(h1) {
        this.__mainWindow.set(h1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(g1) {
        this.__fontSize.set(g1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(f1) {
        this.__maxLines.set(f1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(e1) {
        this.__windowStandardHeight.set(e1);
    }
    initialRender() {
        this.observeComponentCreation2((i, j) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((c1, d1) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                    }, Column);
                    this.observeComponentCreation2((a1, b1) => {
                        Image.create(this.itemEditableDialog.value);
                        Image.width(IMAGE_SIZE);
                        Image.height(IMAGE_SIZE);
                        Image.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level24'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level8'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Image);
                    this.observeComponentCreation2((y, z) => {
                        Column.create();
                        Column.width('100%');
                        Column.padding({
                            left: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            right: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level4'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                            bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level12'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                    }, Column);
                    this.observeComponentCreation2((w, x) => {
                        Text.create(this.textEditableTitleBarDialog);
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
                        Column.borderRadius(({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }));
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((n, o) => {
                        Image.create(this.itemEditableDialog.value);
                        Image.width(IMAGE_SIZE);
                        Image.height(IMAGE_SIZE);
                        Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.icon_primary'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
                    }, Image);
                    Column.pop();
                });
            }
        }, If);
        If.pop();
    }
    async aboutToAppear() {
        let e = this.getUIContext().getHostContext();
        this.mainWindowStage = e.windowStage.getMainWindowSync();
        let f = this.mainWindowStage.getWindowProperties();
        let g = f.windowRect;
        if (px2vp(g.height) > this.screenWidth) {
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
function getNumberByResource(a) {
    try {
        return resourceManager.getSystemResourceManager().getNumber(a);
    }
    catch (b) {
        let c = b.code;
        let d = b.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${c},message:${d}`);
        return null;
    }
}

export default {
  EditableLeftIconType: EditableLeftIconType,
  EditableTitleBar: EditableTitleBar,
};