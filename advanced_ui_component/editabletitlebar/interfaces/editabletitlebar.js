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
(function (h10) {
    h10[h10["Back"] = 0] = "Back";
    h10[h10["Cancel"] = 1] = "Cancel";
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (g10) {
    g10[g10["Image"] = 0] = "Image";
    g10[g10["Icon"] = 1] = "Icon";
    g10[g10["LeftIcon"] = 2] = "LeftIcon";
})(ItemType || (ItemType = {}));
const PUBLIC_CANCEL = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_cancel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const PUBLIC_OK = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_ok'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const PUBLIC_BACK = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_compnent_titlebar_back'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const DEFAULT_TITLE_BAR_HEIGHT = 56;
const DEFAULT_TITLE_PADDING = 2;
const MAX_LINE_ONE = 1;
const MAX_LINES_TWO = 2;
const MAX_MAIN_TITLE_PERCENT = 0.65;
const MAX_SUB_TITLE_PERCENT = 0.35;
const DEFAULT_BREAKPOINT_S = 600;
const DEFAULT_BREAKPOINT_M = 840;
const MIN_SUBTITLE_SIZE = '10.0vp';
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const TITLE_VP = 20;
const SUBTITLE_VP = 14;
const TITLE_F = getNumberByResource('titlebar_title_tertiary_size');
const SUBTITLE_F = getNumberByResource('titlebar_subheader_size');
const TITLE_F_VP = (TITLE_F > 0 ? TITLE_F : TITLE_VP) + 'vp';
const SUBTITLE_F_VP = (SUBTITLE_F > 0 ? SUBTITLE_F : SUBTITLE_VP) + 'vp';
class EditableTitleBarTheme {
    constructor() {
        this.iconColor = { "id": -1, "type": 10001, params: ['sys.color.titlebar_icon_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconBackgroundColor = { "id": -1, "type": 10001, params: ['sys.color.titlebar_icon_background_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconBackgroundPressedColor = { "id": -1, "type": 10001, params: ['sys.color.titlebar_icon_background_pressed_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconBackgroundHoverColor = { "id": -1, "type": 10001, params: ['sys.color.titlebar_icon_background_hover_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.iconBackgroundFocusOutlineColor = { "id": -1, "type": 10001, params: ['sys.color.titlebar_icon_background_focus_outline_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.titleColor = { "id": -1, "type": 10001, params: ['sys.color.titlebar_title_tertiary_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        this.subTitleColor = { "id": -1, "type": 10001, params: ['sys.color.titlebar_subheader_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
    }
}
export class EditableTitleBar extends ViewPU {
    constructor(a10, b10, c10, d10 = -1, e10 = undefined, f10) {
        super(a10, c10, d10, f10);
        if (typeof e10 === "function") {
            this.paramsGenerator_ = e10;
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(b10.contentMargin, this, "contentMargin");
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0),
        }, this, "titleBarMargin");
        this.__backActive = new ObservedPropertySimplePU(false, this, "backActive");
        this.__fontSize = new ObservedPropertySimplePU(1, this, "fontSize");
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, "editableTitleBarTheme");
        this.addProvidedVar("editableTitleBarTheme", this.__editableTitleBarTheme, false);
        this.setInitiallyProvidedValue(b10);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z9) {
        if (z9.leftIconStyle !== undefined) {
            this.leftIconStyle = z9.leftIconStyle;
        }
        if (z9.title !== undefined) {
            this.title = z9.title;
        }
        if (z9.subtitle !== undefined) {
            this.subtitle = z9.subtitle;
        }
        if (z9.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = z9.isSaveIconRequired;
        }
        if (z9.imageItem !== undefined) {
            this.imageItem = z9.imageItem;
        }
        if (z9.menuItems !== undefined) {
            this.menuItems = z9.menuItems;
        }
        if (z9.options !== undefined) {
            this.options = z9.options;
        }
        if (z9.onSave !== undefined) {
            this.onSave = z9.onSave;
        }
        if (z9.onCancel !== undefined) {
            this.onCancel = z9.onCancel;
        }
        if (z9.titleBarMargin !== undefined) {
            this.titleBarMargin = z9.titleBarMargin;
        }
        if (z9.backActive !== undefined) {
            this.backActive = z9.backActive;
        }
        if (z9.fontSize !== undefined) {
            this.fontSize = z9.fontSize;
        }
        if (z9.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = z9.editableTitleBarTheme;
        }
    }
    updateStateVars(y9) {
        this.__contentMargin.reset(y9.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(x9) {
        this.__contentMargin.purgeDependencyOnElmtId(x9);
        this.__titleBarMargin.purgeDependencyOnElmtId(x9);
        this.__backActive.purgeDependencyOnElmtId(x9);
        this.__fontSize.purgeDependencyOnElmtId(x9);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(x9);
    }
    aboutToBeDeleted() {
        this.__contentMargin.aboutToBeDeleted();
        this.__titleBarMargin.aboutToBeDeleted();
        this.__backActive.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__editableTitleBarTheme.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get contentMargin() {
        return this.__contentMargin.get();
    }
    set contentMargin(w9) {
        this.__contentMargin.set(w9);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(v9) {
        this.__titleBarMargin.set(v9);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(u9) {
        this.__backActive.set(u9);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(t9) {
        this.__fontSize.set(t9);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(s9) {
        this.__editableTitleBarTheme.set(s9);
    }
    onWillApplyTheme(r9) {
        this.editableTitleBarTheme.iconColor = r9.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = r9.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = r9.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundColor = r9.colors.compBackgroundTertiary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = r9.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = r9.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = r9.colors.interactiveFocus;
    }
    initialRender() {
        this.observeComponentCreation2((p9, q9) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes, this.options.safeAreaEdges);
        }, Flex);
        this.observeComponentCreation2((n9, o9) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((l9, m9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((e9, f9) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((j9, k9) => {
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
        this.observeComponentCreation2((c9, d9) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((a9, b9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)(this);
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    leftIconLayout(x7 = null) {
        this.observeComponentCreation2((z7, a8) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((s8, t8) => {
                        Navigator.create();
                        Navigator.active(this.backActive);
                    }, Navigator);
                    Navigator.pop();
                    {
                        this.observeComponentCreation2((m8, n8) => {
                            if (n8) {
                                let o8 = new ImageMenuItem(typeof PUV2ViewBase !== "undefined" && x7 instanceof PUV2ViewBase ? x7 : this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, m8, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 196, col: 7 });
                                ViewPU.create(o8);
                                let p8 = () => {
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
                                o8.paramsGenerator_ = p8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(m8, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: "ImageMenuItem" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((d8, e8) => {
                            if (e8) {
                                let f8 = new ImageMenuItem(typeof PUV2ViewBase !== "undefined" && x7 instanceof PUV2ViewBase ? x7 : this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, d8, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 206, col: 7 });
                                ViewPU.create(f8);
                                let g8 = () => {
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
                                f8.paramsGenerator_ = g8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(d8, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: "ImageMenuItem" });
                    }
                });
            }
        }, If);
        If.pop();
    }
    imageItemLayout(p7 = null) {
        {
            this.observeComponentCreation2((r7, s7) => {
                if (s7) {
                    let t7 = new ImageMenuItem(typeof PUV2ViewBase !== "undefined" && p7 instanceof PUV2ViewBase ? p7 : this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, r7, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 220, col: 5 });
                    ViewPU.create(t7);
                    let u7 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    t7.paramsGenerator_ = u7;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(r7, {});
                }
            }, { name: "ImageMenuItem" });
        }
    }
    titleLayout(u6 = null) {
        this.observeComponentCreation2((n7, o7) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.vp(EditableTitleBar.titlePadding),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((l7, m7) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((j7, k7) => {
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
        this.observeComponentCreation2((z6, a7) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((h7, i7) => {
                        Row.create();
                        Row.margin({
                            top: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((f7, g7) => {
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
    rightMenuItemsLayout(m6 = null) {
        {
            this.observeComponentCreation2((o6, p6) => {
                if (p6) {
                    let q6 = new EditableTitleBarMenuSection(typeof PUV2ViewBase !== "undefined" && m6 instanceof PUV2ViewBase ? m6 : this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, o6, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 277, col: 5 });
                    ViewPU.create(q6);
                    let r6 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    q6.paramsGenerator_ = r6;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(o6, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: "EditableTitleBarMenuSection" });
        }
    }
    onMeasureSize(f6, g6, h6) {
        let i6 = { width: f6.width, height: f6.height };
        g6.forEach((k6) => {
            let l6 = Number(h6.maxWidth);
            if (!this.contentMargin) {
                if (l6 < EditableTitleBar.breakpointS) {
                    this.titleBarMargin = {
                        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                    };
                }
                else if (l6 >= EditableTitleBar.breakpointM) {
                    this.titleBarMargin = {
                        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level3'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                    };
                }
                else {
                    this.titleBarMargin = {
                        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level2'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                    };
                }
            }
            i6.height = k6.measure(h6).height;
            i6.width = Number(h6.maxWidth);
        });
        return i6;
    }
    onPlaceChildren(a6, b6, c6) {
        b6.forEach((e6) => {
            e6.layout({ x: 0, y: 0 });
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
    constructor(u5, v5, w5, x5 = -1, y5 = undefined, z5) {
        super(u5, w5, x5, z5);
        if (typeof y5 === "function") {
            this.paramsGenerator_ = y5;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(v5.fontSize, this, "fontSize");
        this.setInitiallyProvidedValue(v5);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(t5) {
        if (t5.menuItems !== undefined) {
            this.menuItems = t5.menuItems;
        }
        if (t5.onSave !== undefined) {
            this.onSave = t5.onSave;
        }
        if (t5.isSaveEnabled !== undefined) {
            this.isSaveEnabled = t5.isSaveEnabled;
        }
        if (t5.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(s5) {
        this.__fontSize.reset(s5.fontSize);
    }
    purgeVariableDependenciesOnElmtId(r5) {
        this.__fontSize.purgeDependencyOnElmtId(r5);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(q5) {
        this.__fontSize.set(q5);
    }
    initialRender() {
        this.observeComponentCreation2((o5, p5) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((m5, n5) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((u4, v4) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z4, a5) => {
                        ForEach.create();
                        const b5 = d5 => {
                            const e5 = d5;
                            {
                                this.observeComponentCreation2((g5, h5) => {
                                    if (h5) {
                                        let i5 = new ImageMenuItem(this, {
                                            item: e5,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, g5, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 335, col: 15 });
                                        ViewPU.create(i5);
                                        let j5 = () => {
                                            return {
                                                item: e5,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        i5.paramsGenerator_ = j5;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(g5, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: "ImageMenuItem" });
                            }
                        };
                        this.forEachUpdateFunction(z4, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), b5);
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
        this.observeComponentCreation2((j4, k4) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((o4, p4) => {
                            if (p4) {
                                let q4 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                }, undefined, o4, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 343, col: 11 });
                                ViewPU.create(q4);
                                let r4 = () => {
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
                                q4.paramsGenerator_ = r4;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o4, {
                                    fontSize: this.fontSize
                                });
                            }
                        }, { name: "ImageMenuItem" });
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
    constructor(v3, w3, x3, y3 = -1, z3 = undefined, a4) {
        super(v3, x3, y3, a4);
        if (typeof z3 === "function") {
            this.paramsGenerator_ = z3;
        }
        this.item = {
            value: '',
            isEnabled: true,
            label: '',
        };
        this.attribute = ItemType.Image;
        this.callbackId = undefined;
        this.minFontSize = 1.75;
        this.maxFontSize = 3.25;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(w3.fontSize, this, "fontSize");
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, "isOnFocus");
        this.__isOnHover = new ObservedPropertySimplePU(false, this, "isOnHover");
        this.__isOnClick = new ObservedPropertySimplePU(false, this, "isOnClick");
        this.__editableTitleBarTheme = this.initializeConsume("editableTitleBarTheme", "editableTitleBarTheme");
        this.dialogController = new CustomDialogController({
            builder: () => {
                let b4 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 377, col: 14 });
                b4.setController(this.dialogController);
                ViewPU.create(b4);
                let c4 = () => {
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
                b4.paramsGenerator_ = c4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.setInitiallyProvidedValue(w3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(u3) {
        if (u3.item !== undefined) {
            this.item = u3.item;
        }
        if (u3.attribute !== undefined) {
            this.attribute = u3.attribute;
        }
        if (u3.callbackId !== undefined) {
            this.callbackId = u3.callbackId;
        }
        if (u3.minFontSize !== undefined) {
            this.minFontSize = u3.minFontSize;
        }
        if (u3.maxFontSize !== undefined) {
            this.maxFontSize = u3.maxFontSize;
        }
        if (u3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (u3.isOnFocus !== undefined) {
            this.isOnFocus = u3.isOnFocus;
        }
        if (u3.isOnHover !== undefined) {
            this.isOnHover = u3.isOnHover;
        }
        if (u3.isOnClick !== undefined) {
            this.isOnClick = u3.isOnClick;
        }
        if (u3.dialogController !== undefined) {
            this.dialogController = u3.dialogController;
        }
    }
    updateStateVars(t3) {
        this.__fontSize.reset(t3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(s3) {
        this.__fontSize.purgeDependencyOnElmtId(s3);
        this.__isOnFocus.purgeDependencyOnElmtId(s3);
        this.__isOnHover.purgeDependencyOnElmtId(s3);
        this.__isOnClick.purgeDependencyOnElmtId(s3);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(s3);
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
    set fontSize(r3) {
        this.__fontSize.set(r3);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(q3) {
        this.__isOnFocus.set(q3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(p3) {
        this.__isOnHover.set(p3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(o3) {
        this.__isOnClick.set(o3);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(n3) {
        this.__editableTitleBarTheme.set(n3);
    }
    textDialog() {
        if (this.item.value === PUBLIC_OK) {
            return { "id": -1, "type": 10003, params: ['sys.string.icon_save'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else if (this.item.value === PUBLIC_CANCEL) {
            return { "id": -1, "type": 10003, params: ['sys.string.icon_cancel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else if (this.item.value === PUBLIC_BACK) {
            return { "id": -1, "type": 10003, params: ['sys.string.icon_back'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else {
            return this.item.label ? this.item.label : '';
        }
    }
    getFgColor() {
        if (this.isOnClick) {
            return { "id": -1, "type": 10001, params: ['sys.color.titlebar_icon_background_pressed_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
        }
        else if (this.isOnHover) {
            return { "id": -1, "type": 10001, params: ['sys.color.titlebar_icon_background_hover_color'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
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
    IconBuilder(t2 = null) {
        this.observeComponentCreation2((y2, z2) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.width({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.height({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_shape'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.margin({
                start: this.attribute === ItemType.LeftIcon ? LengthMetrics.vp(EditableTitleBar.commonZero) :
                    LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(this.getBgColor());
            ViewStackProcessor.visualState("focused");
            Button.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_shape'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_focus_outline_weight'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState("normal");
            Button.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_shape'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState("pressed");
            Button.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_shape'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
            Button.onHover((m3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = m3;
            });
            Button.onKeyEvent((l3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (l3.keyCode !== KeyCode.KEYCODE_ENTER && l3.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (l3.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (l3.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((k3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (k3.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (k3.type === TouchType.Up) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.close();
                    }
                    this.isOnClick = false;
                }
            });
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Exclusive);
            LongPressGesture.create({ repeat: false, duration: 500 });
            LongPressGesture.onAction((i3) => {
                let j3 = this.getUIContext().getHostContext();
                this.fontSize = j3.config?.fontSizeScale ?? 1;
                if (i3) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            TapGesture.create();
            TapGesture.onAction((h3) => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            TapGesture.pop();
            GestureGroup.pop();
            Gesture.pop();
        }, Button);
        this.observeComponentCreation2((w2, x2) => {
            Image.create(this.item.value);
            Image.width({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.height({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.fillColor(this.editableTitleBarTheme.iconColor);
            Image.focusable(this.item.isEnabled);
            Image.enabled(this.item.isEnabled);
            Image.matchTextDirection(this.item.value === PUBLIC_BACK ? true : false);
            Image.draggable(false);
        }, Image);
        Button.pop();
    }
    ImageBuilder(w1 = null) {
        this.observeComponentCreation2((r2, s2) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Stack);
        this.observeComponentCreation2((p2, q2) => {
            Image.create(this.item.value);
            Image.width({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.height({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((a2, b2) => {
            Button.createWithLabel({ type: ButtonType.Circle });
            Button.width({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.height({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor(EditableTitleBar.noneColor);
            ViewStackProcessor.visualState("pressed");
            Button.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_shape'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState("normal");
            Button.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_shape'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState("focused");
            Button.border({
                radius: { "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_shape'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                width: { "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_focus_outline_weight'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
                if (m2.type === TouchType.Up) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.close();
                    }
                    this.isOnClick = false;
                }
            });
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Exclusive);
            LongPressGesture.create({ repeat: false, duration: 500 });
            LongPressGesture.onAction((k2) => {
                let l2 = this.getUIContext().getHostContext();
                this.fontSize = l2.config?.fontSizeScale ?? 1;
                if (k2) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            TapGesture.create();
            TapGesture.onAction((j2) => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            TapGesture.pop();
            GestureGroup.pop();
            Gesture.pop();
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((s1, t1) => {
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
class EditableTitleBarDialog extends ViewPU {
    constructor(j1, k1, l1, m1 = -1, n1 = undefined, o1) {
        super(j1, l1, m1, o1);
        if (typeof n1 === "function") {
            this.paramsGenerator_ = n1;
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
        this.maxFontSize = 3.25;
        this.__mainWindow = this.createStorageLink('mainWindow', undefined, "mainWindow");
        this.__fontSize = new SynchedPropertySimpleOneWayPU(k1.fontSize, this, "fontSize");
        this.__maxLines = new ObservedPropertySimplePU(1, this, "maxLines");
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, "windowStandardHeight");
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.setInitiallyProvidedValue(k1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(i1) {
        if (i1.itemEditableDialog !== undefined) {
            this.itemEditableDialog = i1.itemEditableDialog;
        }
        if (i1.callbackId !== undefined) {
            this.callbackId = i1.callbackId;
        }
        if (i1.textEditableTitleBarDialog !== undefined) {
            this.textEditableTitleBarDialog = i1.textEditableTitleBarDialog;
        }
        if (i1.mainWindowStage !== undefined) {
            this.mainWindowStage = i1.mainWindowStage;
        }
        if (i1.controller !== undefined) {
            this.controller = i1.controller;
        }
        if (i1.minFontSize !== undefined) {
            this.minFontSize = i1.minFontSize;
        }
        if (i1.maxFontSize !== undefined) {
            this.maxFontSize = i1.maxFontSize;
        }
        if (i1.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (i1.maxLines !== undefined) {
            this.maxLines = i1.maxLines;
        }
        if (i1.cancel !== undefined) {
            this.cancel = i1.cancel;
        }
        if (i1.confirm !== undefined) {
            this.confirm = i1.confirm;
        }
    }
    updateStateVars(h1) {
        this.__fontSize.reset(h1.fontSize);
    }
    purgeVariableDependenciesOnElmtId(g1) {
        this.__mainWindow.purgeDependencyOnElmtId(g1);
        this.__fontSize.purgeDependencyOnElmtId(g1);
        this.__maxLines.purgeDependencyOnElmtId(g1);
        this.__windowStandardHeight.purgeDependencyOnElmtId(g1);
    }
    aboutToBeDeleted() {
        this.__mainWindow.aboutToBeDeleted();
        this.__fontSize.aboutToBeDeleted();
        this.__maxLines.aboutToBeDeleted();
        this.__windowStandardHeight.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    setController(f1) {
        this.controller = f1;
    }
    get mainWindow() {
        return this.__mainWindow.get();
    }
    set mainWindow(e1) {
        this.__mainWindow.set(e1);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(d1) {
        this.__fontSize.set(d1);
    }
    get maxLines() {
        return this.__maxLines.get();
    }
    set maxLines(c1) {
        this.__maxLines.set(c1);
    }
    get windowStandardHeight() {
        return this.__windowStandardHeight.get();
    }
    set windowStandardHeight(b1) {
        this.__windowStandardHeight.set(b1);
    }
    initialRender() {
        this.observeComponentCreation2((i, j) => {
            If.create();
            if (this.textEditableTitleBarDialog) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((z, a1) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THIN);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }));
                    }, Column);
                    this.observeComponentCreation2((x, y) => {
                        Image.create(this.itemEditableDialog.value);
                        Image.width(IMAGE_SIZE);
                        Image.height(IMAGE_SIZE);
                        Image.margin({
                            top: { "id": -1, "type": 10002, params: ['sys.float.padding_level24'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level8'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                    }, Image);
                    this.observeComponentCreation2((v, w) => {
                        Text.create(this.textEditableTitleBarDialog);
                        Text.fontSize(TEXT_EDITABLE_DIALOG);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.maxLines(this.maxLines);
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.font_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({
                            left: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            right: { "id": -1, "type": 10002, params: ['sys.float.padding_level4'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            bottom: { "id": -1, "type": 10002, params: ['sys.float.padding_level12'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                    }, Text);
                    Text.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((p, q) => {
                        Column.create();
                        Column.width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG);
                        Column.constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG });
                        Column.backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THIN);
                        Column.shadow(ShadowStyle.OUTER_DEFAULT_LG);
                        Column.borderRadius(({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }));
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((n, o) => {
                        Image.create(this.itemEditableDialog.value);
                        Image.width(IMAGE_SIZE);
                        Image.height(IMAGE_SIZE);
                        Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.icon_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
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
        if (px2vp(g.height) > 640) {
            this.maxLines = 6;
        }
        else {
            this.maxLines = 1;
        }
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