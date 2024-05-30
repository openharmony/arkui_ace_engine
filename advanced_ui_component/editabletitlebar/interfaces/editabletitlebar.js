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
const BusinessError = requireNapi('base');
const common = requireNapi('app.ability.common');
const EnvironmentCallback = requireNapi('app.ability.EnvironmentCallback');
const window = requireNapi('window');

export var EditableLeftIconType;
(function (g10) {
    g10[g10["Back"] = 0] = "Back";
    g10[g10["Cancel"] = 1] = "Cancel";
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (f10) {
    f10[f10["Image"] = 0] = "Image";
    f10[f10["Icon"] = 1] = "Icon";
    f10[f10["LeftIcon"] = 2] = "LeftIcon";
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
    constructor(z9, a10, b10, c10 = -1, d10 = undefined, e10) {
        super(z9, b10, c10, e10);
        if (typeof d10 === "function") {
            this.paramsGenerator_ = d10;
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(a10.contentMargin, this, "contentMargin");
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0),
        }, this, "titleBarMargin");
        this.__backActive = new ObservedPropertySimplePU(false, this, "backActive");
        this.__fontSize = new ObservedPropertySimplePU(1, this, "fontSize");
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, "editableTitleBarTheme");
        this.addProvidedVar("editableTitleBarTheme", this.__editableTitleBarTheme, false);
        this.setInitiallyProvidedValue(a10);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(y9) {
        if (y9.leftIconStyle !== undefined) {
            this.leftIconStyle = y9.leftIconStyle;
        }
        if (y9.title !== undefined) {
            this.title = y9.title;
        }
        if (y9.subtitle !== undefined) {
            this.subtitle = y9.subtitle;
        }
        if (y9.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = y9.isSaveIconRequired;
        }
        if (y9.imageItem !== undefined) {
            this.imageItem = y9.imageItem;
        }
        if (y9.menuItems !== undefined) {
            this.menuItems = y9.menuItems;
        }
        if (y9.options !== undefined) {
            this.options = y9.options;
        }
        if (y9.onSave !== undefined) {
            this.onSave = y9.onSave;
        }
        if (y9.onCancel !== undefined) {
            this.onCancel = y9.onCancel;
        }
        if (y9.titleBarMargin !== undefined) {
            this.titleBarMargin = y9.titleBarMargin;
        }
        if (y9.backActive !== undefined) {
            this.backActive = y9.backActive;
        }
        if (y9.fontSize !== undefined) {
            this.fontSize = y9.fontSize;
        }
        if (y9.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = y9.editableTitleBarTheme;
        }
    }
    updateStateVars(x9) {
        this.__contentMargin.reset(x9.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(w9) {
        this.__contentMargin.purgeDependencyOnElmtId(w9);
        this.__titleBarMargin.purgeDependencyOnElmtId(w9);
        this.__backActive.purgeDependencyOnElmtId(w9);
        this.__fontSize.purgeDependencyOnElmtId(w9);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(w9);
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
    set contentMargin(v9) {
        this.__contentMargin.set(v9);
    }
    get titleBarMargin() {
        return this.__titleBarMargin.get();
    }
    set titleBarMargin(u9) {
        this.__titleBarMargin.set(u9);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(t9) {
        this.__backActive.set(t9);
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(s9) {
        this.__fontSize.set(s9);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(r9) {
        this.__editableTitleBarTheme.set(r9);
    }
    onWillApplyTheme(q9) {
        this.editableTitleBarTheme.iconColor = q9.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = q9.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = q9.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundColor = q9.colors.compBackgroundTertiary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = q9.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = q9.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = q9.colors.interactiveFocus;
    }
    initialRender() {
        this.observeComponentCreation2((o9, p9) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ?? BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes, this.options.safeAreaEdges);
        }, Flex);
        this.observeComponentCreation2((m9, n9) => {
            Row.create();
            Row.width('100%');
            Row.margin(this.contentMargin ?? this.titleBarMargin);
            Row.height(EditableTitleBar.totalHeight);
        }, Row);
        this.observeComponentCreation2((k9, l9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.leftIconLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((d9, e9) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i9, j9) => {
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
        this.observeComponentCreation2((b9, c9) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((z8, a9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)(this);
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    leftIconLayout(w7 = null) {
        this.observeComponentCreation2((y7, z7) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((r8, s8) => {
                        Navigator.create();
                        Navigator.active(this.backActive);
                    }, Navigator);
                    Navigator.pop();
                    {
                        this.observeComponentCreation2((l8, m8) => {
                            if (m8) {
                                let n8 = new ImageMenuItem(typeof PUV2ViewBase !== "undefined" && w7 instanceof PUV2ViewBase ? w7 : this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, l8, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 197, col: 7 });
                                ViewPU.create(n8);
                                let o8 = () => {
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
                                n8.paramsGenerator_ = o8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(l8, {
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
                        this.observeComponentCreation2((c8, d8) => {
                            if (d8) {
                                let e8 = new ImageMenuItem(typeof PUV2ViewBase !== "undefined" && w7 instanceof PUV2ViewBase ? w7 : this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.LeftIcon,
                                }, undefined, c8, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 207, col: 7 });
                                ViewPU.create(e8);
                                let f8 = () => {
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
                                e8.paramsGenerator_ = f8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(c8, {
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
    imageItemLayout(o7 = null) {
        {
            this.observeComponentCreation2((q7, r7) => {
                if (r7) {
                    let s7 = new ImageMenuItem(typeof PUV2ViewBase !== "undefined" && o7 instanceof PUV2ViewBase ? o7 : this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, q7, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 221, col: 5 });
                    ViewPU.create(s7);
                    let t7 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    s7.paramsGenerator_ = t7;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q7, {});
                }
            }, { name: "ImageMenuItem" });
        }
    }
    titleLayout(t6 = null) {
        this.observeComponentCreation2((m7, n7) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.vp(EditableTitleBar.titlePadding),
            });
            Column.alignItems(HorizontalAlign.Start);
        }, Column);
        this.observeComponentCreation2((k7, l7) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((i7, j7) => {
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
        this.observeComponentCreation2((y6, z6) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((g7, h7) => {
                        Row.create();
                        Row.margin({
                            top: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((e7, f7) => {
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
    rightMenuItemsLayout(l6 = null) {
        {
            this.observeComponentCreation2((n6, o6) => {
                if (o6) {
                    let p6 = new EditableTitleBarMenuSection(typeof PUV2ViewBase !== "undefined" && l6 instanceof PUV2ViewBase ? l6 : this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                        fontSize: this.fontSize,
                    }, undefined, n6, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 278, col: 5 });
                    ViewPU.create(p6);
                    let q6 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired,
                            fontSize: this.fontSize
                        };
                    };
                    p6.paramsGenerator_ = q6;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(n6, {
                        fontSize: this.fontSize
                    });
                }
            }, { name: "EditableTitleBarMenuSection" });
        }
    }
    onMeasureSize(d6, e6, f6) {
        let g6 = { width: d6.width, height: d6.height };
        let h6 = this.getUIContext().getHostContext();
        this.fontSize = h6.config?.fontSizeScale ?? 1;
        e6.forEach((j6) => {
            let k6 = Number(f6.maxWidth);
            if (!this.contentMargin) {
                if (k6 < EditableTitleBar.breakpointS) {
                    this.titleBarMargin = {
                        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                    };
                }
                else if (k6 >= EditableTitleBar.breakpointM) {
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
            g6.height = j6.measure(f6).height;
            g6.width = Number(f6.maxWidth);
        });
        return g6;
    }
    onPlaceChildren(y5, z5, a6) {
        z5.forEach((c6) => {
            c6.layout({ x: 0, y: 0 });
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
    constructor(s5, t5, u5, v5 = -1, w5 = undefined, x5) {
        super(s5, u5, v5, x5);
        if (typeof w5 === "function") {
            this.paramsGenerator_ = w5;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.__fontSize = new SynchedPropertySimpleOneWayPU(t5.fontSize, this, "fontSize");
        this.setInitiallyProvidedValue(t5);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r5) {
        if (r5.menuItems !== undefined) {
            this.menuItems = r5.menuItems;
        }
        if (r5.onSave !== undefined) {
            this.onSave = r5.onSave;
        }
        if (r5.isSaveEnabled !== undefined) {
            this.isSaveEnabled = r5.isSaveEnabled;
        }
        if (r5.fontSize === undefined) {
            this.__fontSize.set(1);
        }
    }
    updateStateVars(q5) {
        this.__fontSize.reset(q5.fontSize);
    }
    purgeVariableDependenciesOnElmtId(p5) {
        this.__fontSize.purgeDependencyOnElmtId(p5);
    }
    aboutToBeDeleted() {
        this.__fontSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get fontSize() {
        return this.__fontSize.get();
    }
    set fontSize(o5) {
        this.__fontSize.set(o5);
    }
    initialRender() {
        this.observeComponentCreation2((m5, n5) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((k5, l5) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((s4, t4) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x4, y4) => {
                        ForEach.create();
                        const z4 = b5 => {
                            const c5 = b5;
                            {
                                this.observeComponentCreation2((e5, f5) => {
                                    if (f5) {
                                        let g5 = new ImageMenuItem(this, {
                                            item: c5,
                                            attribute: ItemType.Icon,
                                            fontSize: this.fontSize,
                                        }, undefined, e5, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 338, col: 15 });
                                        ViewPU.create(g5);
                                        let h5 = () => {
                                            return {
                                                item: c5,
                                                attribute: ItemType.Icon,
                                                fontSize: this.fontSize
                                            };
                                        };
                                        g5.paramsGenerator_ = h5;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(e5, {
                                            fontSize: this.fontSize
                                        });
                                    }
                                }, { name: "ImageMenuItem" });
                            }
                        };
                        this.forEachUpdateFunction(x4, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), z4);
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
        this.observeComponentCreation2((h4, i4) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((m4, n4) => {
                            if (n4) {
                                let o4 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    fontSize: this.fontSize,
                                    attribute: ItemType.Icon,
                                }, undefined, m4, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 346, col: 11 });
                                ViewPU.create(o4);
                                let p4 = () => {
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
                                o4.paramsGenerator_ = p4;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(m4, {
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
    constructor(t3, u3, v3, w3 = -1, x3 = undefined, y3) {
        super(t3, v3, w3, y3);
        if (typeof x3 === "function") {
            this.paramsGenerator_ = x3;
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
        this.__fontSize = new SynchedPropertySimpleOneWayPU(u3.fontSize, this, "fontSize");
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, "isOnFocus");
        this.__isOnHover = new ObservedPropertySimplePU(false, this, "isOnHover");
        this.__isOnClick = new ObservedPropertySimplePU(false, this, "isOnClick");
        this.__editableTitleBarTheme = this.initializeConsume("editableTitleBarTheme", "editableTitleBarTheme");
        this.dialogController = new CustomDialogController({
            builder: () => {
                let z3 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                    fontSize: this.fontSize,
                }, undefined, -1, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 380, col: 14 });
                z3.setController(this.dialogController);
                ViewPU.create(z3);
                let a4 = () => {
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
                z3.paramsGenerator_ = a4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.setInitiallyProvidedValue(u3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(s3) {
        if (s3.item !== undefined) {
            this.item = s3.item;
        }
        if (s3.attribute !== undefined) {
            this.attribute = s3.attribute;
        }
        if (s3.callbackId !== undefined) {
            this.callbackId = s3.callbackId;
        }
        if (s3.minFontSize !== undefined) {
            this.minFontSize = s3.minFontSize;
        }
        if (s3.maxFontSize !== undefined) {
            this.maxFontSize = s3.maxFontSize;
        }
        if (s3.fontSize === undefined) {
            this.__fontSize.set(1);
        }
        if (s3.isOnFocus !== undefined) {
            this.isOnFocus = s3.isOnFocus;
        }
        if (s3.isOnHover !== undefined) {
            this.isOnHover = s3.isOnHover;
        }
        if (s3.isOnClick !== undefined) {
            this.isOnClick = s3.isOnClick;
        }
        if (s3.dialogController !== undefined) {
            this.dialogController = s3.dialogController;
        }
    }
    updateStateVars(r3) {
        this.__fontSize.reset(r3.fontSize);
    }
    purgeVariableDependenciesOnElmtId(q3) {
        this.__fontSize.purgeDependencyOnElmtId(q3);
        this.__isOnFocus.purgeDependencyOnElmtId(q3);
        this.__isOnHover.purgeDependencyOnElmtId(q3);
        this.__isOnClick.purgeDependencyOnElmtId(q3);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(q3);
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
    set fontSize(p3) {
        this.__fontSize.set(p3);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(o3) {
        this.__isOnFocus.set(o3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(n3) {
        this.__isOnHover.set(n3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(m3) {
        this.__isOnClick.set(m3);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(l3) {
        this.__editableTitleBarTheme.set(l3);
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
    IconBuilder(s2 = null) {
        this.observeComponentCreation2((x2, y2) => {
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
            Button.onHover((k3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = k3;
            });
            Button.onKeyEvent((j3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (j3.keyCode !== KeyCode.KEYCODE_ENTER && j3.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (j3.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (j3.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((i3) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (i3.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (i3.type === TouchType.Up) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.close();
                    }
                    this.isOnClick = false;
                }
            });
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Exclusive);
            LongPressGesture.create({ repeat: false, duration: 500 });
            LongPressGesture.onAction((h3) => {
                console.log('LongPressGesture success');
                if (h3) {
                    if (this.fontSize >= this.minFontSize) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            TapGesture.create();
            TapGesture.onAction((g3) => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            TapGesture.pop();
            GestureGroup.pop();
            Gesture.pop();
        }, Button);
        this.observeComponentCreation2((v2, w2) => {
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
        this.observeComponentCreation2((q2, r2) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Stack);
        this.observeComponentCreation2((o2, p2) => {
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
            Button.onHover((n2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = n2;
            });
            Button.onKeyEvent((m2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (m2.keyCode !== KeyCode.KEYCODE_ENTER && m2.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (m2.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (m2.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((l2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (l2.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (l2.type === TouchType.Up) {
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
                console.log('LongPressGesture success');
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