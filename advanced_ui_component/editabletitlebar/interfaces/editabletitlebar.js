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
(function (f8) {
    f8[f8['Back'] = 0] = 'Back';
    f8[f8['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (e8) {
    e8[e8['Image'] = 0] = 'Image';
    e8[e8['Icon'] = 1] = 'Icon';
    e8[e8['LeftIcon'] = 2] = 'LeftIcon';
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
const DEFAULT_BREAKPOINT_S = 600;
const DEFAULT_BREAKPOINT_M = 840;
const MIN_SUBTITLE_SIZE = '10.0fp';
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
    constructor(y7, z7, a8, b8 = -1, c8 = undefined, d8) {
        super(y7, a8, b8, d8);
        if (typeof c8 === 'function') {
            this.paramsGenerator_ = c8;
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(z7.contentMargin, this, 'contentMargin');
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0),
        }, this, 'titleBarMargin');
        this.__backActive = new ObservedPropertySimplePU(false, this, 'backActive');
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, 'editableTitleBarTheme');
        this.addProvidedVar('editableTitleBarTheme', this.__editableTitleBarTheme, false);
        this.setInitiallyProvidedValue(z7);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(x7) {
        if (x7.leftIconStyle !== undefined) {
            this.leftIconStyle = x7.leftIconStyle;
        }
        if (x7.title !== undefined) {
            this.title = x7.title;
        }
        if (x7.subtitle !== undefined) {
            this.subtitle = x7.subtitle;
        }
        if (x7.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = x7.isSaveIconRequired;
        }
        if (x7.imageItem !== undefined) {
            this.imageItem = x7.imageItem;
        }
        if (x7.menuItems !== undefined) {
            this.menuItems = x7.menuItems;
        }
        if (x7.options !== undefined) {
            this.options = x7.options;
        }
        if (x7.onSave !== undefined) {
            this.onSave = x7.onSave;
        }
        if (x7.onCancel !== undefined) {
            this.onCancel = x7.onCancel;
        }
        if (x7.titleBarMargin !== undefined) {
            this.titleBarMargin = x7.titleBarMargin;
        }
        if (x7.backActive !== undefined) {
            this.backActive = x7.backActive;
        }
        if (x7.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = x7.editableTitleBarTheme;
        }
    }
    updateStateVars(w7) {
        this.__contentMargin.reset(w7.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(v7) {
        this.__contentMargin.purgeDependencyOnElmtId(v7);
        this.__titleBarMargin.purgeDependencyOnElmtId(v7);
        this.__backActive.purgeDependencyOnElmtId(v7);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(v7);
    }
    aboutToBeDeleted() {
        this.__contentMargin.aboutToBeDeleted();
        this.__titleBarMargin.aboutToBeDeleted();
        this.__backActive.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(u7) {
        this.__contentMargin.set(u7);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(t7) {
        this.__titleBarMargin.set(t7);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(s7) {
        this.__backActive.set(s7);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(r7) {
        this.__editableTitleBarTheme.set(r7);
    }
    onWillApplyTheme(q7) {
        this.editableTitleBarTheme.iconColor = q7.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = q7.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = q7.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundColor = q7.colors.compBackgroundTertiary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = q7.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = q7.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = q7.colors.interactiveFocus;
    }
    initialRender() {
        this.observeComponentCreation2((o7, p7) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes, this.options.safeAreaEdges);
        }, Flex);
        this.observeComponentCreation2((m7, n7) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((k7, l7) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((d7, e7) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i7, j7) => {
                        Row.create();
                        Row.flexShrink(0);
                    }, Row);
                    this.imageItemLayout.bind(this)(this);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((b7, c7) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((z6, a7) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)(this);
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    leftIconLayout(w5 = null) {
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
                                let n6 = new ImageMenuItem(typeof PUV2ViewBase !== 'undefined' && w5 instanceof PUV2ViewBase ? w5 : this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, l6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 181, col: 7 });
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
                                let e6 = new ImageMenuItem(typeof PUV2ViewBase !== 'undefined' && w5 instanceof PUV2ViewBase ? w5 : this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, c6, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 190, col: 7 });
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
    }
    imageItemLayout(o5 = null) {
        {
            this.observeComponentCreation2((q5, r5) => {
                if (r5) {
                    let s5 = new ImageMenuItem(typeof PUV2ViewBase !== 'undefined' && o5 instanceof PUV2ViewBase ? o5 : this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, q5, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 203, col: 5 });
                    ViewPU.create(s5);
                    let t5 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    s5.paramsGenerator_ = t5;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q5, {});
                }
            }, { name: 'ImageMenuItem' });
        }
    }
    titleLayout(t4 = null) {
        this.observeComponentCreation2((m5, n5) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.vp(EditableTitleBar.titlePadding),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((k5, l5) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((i5, j5) => {
            Text.create(this.title);
            Text.maxFontSize({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_title_tertiary_size'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Text.minFontSize({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_subheader_size'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
        this.observeComponentCreation2((y4, z4) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g5, h5) => {
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((e5, f5) => {
                        Text.create(this.subtitle);
                        Text.maxFontSize({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_subheader_size'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
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
    rightMenuItemsLayout(l4 = null) {
        {
            this.observeComponentCreation2((n4, o4) => {
                if (o4) {
                    let p4 = new EditableTitleBarMenuSection(typeof PUV2ViewBase !== 'undefined' && l4 instanceof PUV2ViewBase ? l4 : this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                    }, undefined, n4, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 260, col: 5 });
                    ViewPU.create(p4);
                    let q4 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired
                        };
                    };
                    p4.paramsGenerator_ = q4;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(n4, {});
                }
            }, { name: 'EditableTitleBarMenuSection' });
        }
    }
    onMeasureSize(e4, f4, g4) {
        let h4 = { width: e4.width, height: e4.height };
        f4.forEach((j4) => {
            let k4 = Number(g4.maxWidth);
            if (!this.contentMargin) {
                if (k4 < EditableTitleBar.breakpointS) {
                    this.titleBarMargin = {
                        start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level1'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                    };
                }
                else if (k4 >= EditableTitleBar.breakpointM) {
                    this.titleBarMargin = {
                        start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level3'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                    };
                }
                else {
                    this.titleBarMargin = {
                        start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                        end: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.margin_level2'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
                    };
                }
            }
            h4.height = j4.measure(g4).height;
            h4.width = Number(g4.maxWidth);
        });
        return h4;
    }
    onPlaceChildren(z3, a4, b4) {
        a4.forEach((d4) => {
            d4.layout({ x: 0, y: 0 });
        });
    }
    rerender() {
        this.updateDirtyElements();
    }
}
EditableTitleBar.maxCountOfExtraItems = 3;
EditableTitleBar.maxOtherCountOfExtraItems = 2;
EditableTitleBar.commonZero = 0;
EditableTitleBar.noneColor = '#00000000';
EditableTitleBar.defaultHeight = getNumberByResource('titlebar_default_height');
EditableTitleBar.defaultMarginLevel1 = getNumberByResource('margin_level1');
EditableTitleBar.defaultMarginLevel2 = getNumberByResource('margin_level2');
EditableTitleBar.defaultMarginLevel3 = getNumberByResource('margin_level3');
EditableTitleBar.defaultTitlePadding = getNumberByResource('titlebar_icon_background_space_horizontal');
EditableTitleBar.defaultBreakpointS = getNumberByResource('breakpoint_horizontal_s');
EditableTitleBar.defaultBreakpointM = getNumberByResource('breakpoint_horizontal_m');
EditableTitleBar.totalHeight = EditableTitleBar.defaultHeight === EditableTitleBar.commonZero ? DEFAULT_TITLE_BAR_HEIGHT :
    EditableTitleBar.defaultHeight;
EditableTitleBar.titlePadding = EditableTitleBar.defaultTitlePadding === EditableTitleBar.commonZero ?
    DEFAULT_TITLE_PADDING : EditableTitleBar.defaultTitlePadding;
EditableTitleBar.maxMainTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_MAIN_TITLE_PERCENT;
EditableTitleBar.maxSubTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * MAX_SUB_TITLE_PERCENT;
EditableTitleBar.breakpointS = EditableTitleBar.defaultBreakpointS === EditableTitleBar.commonZero ? DEFAULT_BREAKPOINT_S :
    EditableTitleBar.defaultBreakpointS;
EditableTitleBar.breakpointM = EditableTitleBar.defaultBreakpointM === EditableTitleBar.commonZero ? DEFAULT_BREAKPOINT_M :
    EditableTitleBar.defaultBreakpointM;
class EditableTitleBarMenuSection extends ViewPU {
    constructor(t3, u3, v3, w3 = -1, x3 = undefined, y3) {
        super(t3, v3, w3, y3);
        if (typeof x3 === 'function') {
            this.paramsGenerator_ = x3;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.setInitiallyProvidedValue(u3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(s3) {
        if (s3.menuItems !== undefined) {
            this.menuItems = s3.menuItems;
        }
        if (s3.onSave !== undefined) {
            this.onSave = s3.onSave;
        }
        if (s3.isSaveEnabled !== undefined) {
            this.isSaveEnabled = s3.isSaveEnabled;
        }
    }
    updateStateVars(r3) {
    }
    purgeVariableDependenciesOnElmtId(q3) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    initialRender() {
        this.observeComponentCreation2((o3, p3) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((m3, n3) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((u2, v2) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z2, a3) => {
                        ForEach.create();
                        const b3 = d3 => {
                            const e3 = d3;
                            {
                                this.observeComponentCreation2((g3, h3) => {
                                    if (h3) {
                                        let i3 = new ImageMenuItem(this, {
                                            item: e3,
                                            attribute: ItemType.Icon,
                                        }, undefined, g3, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 316, col: 15 });
                                        ViewPU.create(i3);
                                        let j3 = () => {
                                            return {
                                                item: e3,
                                                attribute: ItemType.Icon
                                            };
                                        };
                                        i3.paramsGenerator_ = j3;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(g3, {});
                                    }
                                }, { name: 'ImageMenuItem' });
                            }
                        };
                        this.forEachUpdateFunction(z2, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), b3);
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
        this.observeComponentCreation2((j2, k2) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((o2, p2) => {
                            if (p2) {
                                let q2 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    attribute: ItemType.Icon,
                                }, undefined, o2, () => { }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 323, col: 11 });
                                ViewPU.create(q2);
                                let r2 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                        },
                                        attribute: ItemType.Icon
                                    };
                                };
                                q2.paramsGenerator_ = r2;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o2, {});
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
    constructor(z1, a2, b2, c2 = -1, d2 = undefined, e2) {
        super(z1, b2, c2, e2);
        if (typeof d2 === 'function') {
            this.paramsGenerator_ = d2;
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
        this.setInitiallyProvidedValue(a2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(y1) {
        if (y1.item !== undefined) {
            this.item = y1.item;
        }
        if (y1.attribute !== undefined) {
            this.attribute = y1.attribute;
        }
        if (y1.isOnFocus !== undefined) {
            this.isOnFocus = y1.isOnFocus;
        }
        if (y1.isOnHover !== undefined) {
            this.isOnHover = y1.isOnHover;
        }
        if (y1.isOnClick !== undefined) {
            this.isOnClick = y1.isOnClick;
        }
    }
    updateStateVars(x1) {
    }
    purgeVariableDependenciesOnElmtId(w1) {
        this.__isOnFocus.purgeDependencyOnElmtId(w1);
        this.__isOnHover.purgeDependencyOnElmtId(w1);
        this.__isOnClick.purgeDependencyOnElmtId(w1);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(w1);
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
    set isOnFocus(v1) {
        this.__isOnFocus.set(v1);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(u1) {
        this.__isOnHover.set(u1);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(t1) {
        this.__isOnClick.set(t1);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(s1) {
        this.__editableTitleBarTheme.set(s1);
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
    IconBuilder(c1 = null) {
        this.observeComponentCreation2((h1, i1) => {
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
            Button.onHover((r1) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = r1;
            });
            Button.onKeyEvent((q1) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (q1.keyCode !== KeyCode.KEYCODE_ENTER && q1.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (q1.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (q1.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((p1) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (p1.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (p1.type === TouchType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
        }, Button);
        this.observeComponentCreation2((f1, g1) => {
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
    ImageBuilder(j = null) {
        this.observeComponentCreation2((a1, b1) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' }),
            });
        }, Stack);
        this.observeComponentCreation2((y, z) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_width'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_height'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '__harDefaultBundleName__', 'moduleName': '__harDefaultModuleName__' });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((n, o) => {
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
            Button.onHover((x) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = x;
            });
            Button.onKeyEvent((w) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (w.keyCode !== KeyCode.KEYCODE_ENTER && w.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (w.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (w.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((v) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (v.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (v.type === TouchType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((f, g) => {
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
function getNumberByResource(a) {
    try {
        return resourceManager.getSystemResourceManager().getNumberByName(a);
    }
    catch (b) {
        let c = b.code;
        let d = b.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${c},message:${d}`);
        return EditableTitleBar.commonZero;
    }
}

export default {
    EditableLeftIconType: EditableLeftIconType,
    EditableTitleBar: EditableTitleBar,
};