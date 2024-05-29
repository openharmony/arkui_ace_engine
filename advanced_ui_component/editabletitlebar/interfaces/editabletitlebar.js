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
(function (i10) {
    i10[i10["Back"] = 0] = "Back";
    i10[i10["Cancel"] = 1] = "Cancel";
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (h10) {
    h10[h10["Image"] = 0] = "Image";
    h10[h10["Icon"] = 1] = "Icon";
    h10[h10["LeftIcon"] = 2] = "LeftIcon";
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
const TEXT_EDITABLE_DIALOG = '18.3vp';
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
    constructor(b10, c10, d10, e10 = -1, f10 = undefined, g10) {
        super(b10, d10, e10, g10);
        if (typeof f10 === "function") {
            this.paramsGenerator_ = f10;
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
        this.__contentMargin = new SynchedPropertyObjectOneWayPU(c10.contentMargin, this, "contentMargin");
        this.__titleBarMargin = new ObservedPropertyObjectPU({
            start: LengthMetrics.vp(0),
            end: LengthMetrics.vp(0),
        }, this, "titleBarMargin");
        this.__backActive = new ObservedPropertySimplePU(false, this, "backActive");
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, "editableTitleBarTheme");
        this.addProvidedVar("editableTitleBarTheme", this.__editableTitleBarTheme, false);
        this.setInitiallyProvidedValue(c10);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a10) {
        if (a10.leftIconStyle !== undefined) {
            this.leftIconStyle = a10.leftIconStyle;
        }
        if (a10.title !== undefined) {
            this.title = a10.title;
        }
        if (a10.subtitle !== undefined) {
            this.subtitle = a10.subtitle;
        }
        if (a10.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = a10.isSaveIconRequired;
        }
        if (a10.imageItem !== undefined) {
            this.imageItem = a10.imageItem;
        }
        if (a10.menuItems !== undefined) {
            this.menuItems = a10.menuItems;
        }
        if (a10.options !== undefined) {
            this.options = a10.options;
        }
        if (a10.onSave !== undefined) {
            this.onSave = a10.onSave;
        }
        if (a10.onCancel !== undefined) {
            this.onCancel = a10.onCancel;
        }
        if (a10.titleBarMargin !== undefined) {
            this.titleBarMargin = a10.titleBarMargin;
        }
        if (a10.backActive !== undefined) {
            this.backActive = a10.backActive;
        }
        if (a10.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = a10.editableTitleBarTheme;
        }
    }
    updateStateVars(z9) {
        this.__contentMargin.reset(z9.contentMargin);
    }
    purgeVariableDependenciesOnElmtId(y9) {
        this.__contentMargin.purgeDependencyOnElmtId(y9);
        this.__titleBarMargin.purgeDependencyOnElmtId(y9);
        this.__backActive.purgeDependencyOnElmtId(y9);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(y9);
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
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(u9) {
        this.__editableTitleBarTheme.set(u9);
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
        this.leftIconLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((g9, h9) => {
            If.create();
            if (this.imageItem) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((l9, m9) => {
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
        this.observeComponentCreation2((e9, f9) => {
            Row.create();
            Row.width('100%');
            Row.flexShrink(1);
        }, Row);
        this.titleLayout.bind(this)(this);
        Row.pop();
        this.observeComponentCreation2((c9, d9) => {
            Row.create();
            Row.flexShrink(0);
        }, Row);
        this.rightMenuItemsLayout.bind(this)(this);
        Row.pop();
        Row.pop();
        Flex.pop();
    }
    leftIconLayout(z7 = null) {
        this.observeComponentCreation2((b8, c8) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((u8, v8) => {
                        Navigator.create();
                        Navigator.active(this.backActive);
                    }, Navigator);
                    Navigator.pop();
                    {
                        this.observeComponentCreation2((o8, p8) => {
                            if (p8) {
                                let q8 = new ImageMenuItem(typeof PUV2ViewBase !== "undefined" && z7 instanceof PUV2ViewBase ? z7 : this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, o8, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 196, col: 7 });
                                ViewPU.create(q8);
                                let r8 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                        },
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                q8.paramsGenerator_ = r8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(o8, {});
                            }
                        }, { name: "ImageMenuItem" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((f8, g8) => {
                            if (g8) {
                                let h8 = new ImageMenuItem(typeof PUV2ViewBase !== "undefined" && z7 instanceof PUV2ViewBase ? z7 : this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, f8, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 205, col: 7 });
                                ViewPU.create(h8);
                                let i8 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                        },
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                h8.paramsGenerator_ = i8;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(f8, {});
                            }
                        }, { name: "ImageMenuItem" });
                    }
                });
            }
        }, If);
        If.pop();
    }
    imageItemLayout(r7 = null) {
        {
            this.observeComponentCreation2((t7, u7) => {
                if (u7) {
                    let v7 = new ImageMenuItem(typeof PUV2ViewBase !== "undefined" && r7 instanceof PUV2ViewBase ? r7 : this, {
                        item: this.imageItem,
                        attribute: ItemType.Image,
                    }, undefined, t7, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 218, col: 5 });
                    ViewPU.create(v7);
                    let w7 = () => {
                        return {
                            item: this.imageItem,
                            attribute: ItemType.Image
                        };
                    };
                    v7.paramsGenerator_ = w7;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(t7, {});
                }
            }, { name: "ImageMenuItem" });
        }
    }
    titleLayout(w6 = null) {
        this.observeComponentCreation2((p7, q7) => {
            Column.create();
            Column.height(EditableTitleBar.totalHeight);
            Column.justifyContent(FlexAlign.Center);
            Column.margin({
                start: LengthMetrics.vp(EditableTitleBar.titlePadding),
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
                            top: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
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
                    let s6 = new EditableTitleBarMenuSection(typeof PUV2ViewBase !== "undefined" && o6 instanceof PUV2ViewBase ? o6 : this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                    }, undefined, q6, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 275, col: 5 });
                    ViewPU.create(s6);
                    let t6 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired
                        };
                    };
                    s6.paramsGenerator_ = t6;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q6, {});
                }
            }, { name: "EditableTitleBarMenuSection" });
        }
    }
    onMeasureSize(h6, i6, j6) {
        let k6 = { width: h6.width, height: h6.height };
        i6.forEach((m6) => {
            let n6 = Number(j6.maxWidth);
            if (!this.contentMargin) {
                if (n6 < EditableTitleBar.breakpointS) {
                    this.titleBarMargin = {
                        start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                        end: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.margin_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
                    };
                }
                else if (n6 >= EditableTitleBar.breakpointM) {
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
            k6.height = m6.measure(j6).height;
            k6.width = Number(j6.maxWidth);
        });
        return k6;
    }
    onPlaceChildren(c6, d6, e6) {
        d6.forEach((g6) => {
            g6.layout({ x: 0, y: 0 });
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
    constructor(w5, x5, y5, z5 = -1, a6 = undefined, b6) {
        super(w5, y5, z5, b6);
        if (typeof a6 === "function") {
            this.paramsGenerator_ = a6;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.setInitiallyProvidedValue(x5);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(v5) {
        if (v5.menuItems !== undefined) {
            this.menuItems = v5.menuItems;
        }
        if (v5.onSave !== undefined) {
            this.onSave = v5.onSave;
        }
        if (v5.isSaveEnabled !== undefined) {
            this.isSaveEnabled = v5.isSaveEnabled;
        }
    }
    updateStateVars(u5) {
    }
    purgeVariableDependenciesOnElmtId(t5) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
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
                                        }, undefined, j5, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 331, col: 15 });
                                        ViewPU.create(l5);
                                        let m5 = () => {
                                            return {
                                                item: h5,
                                                attribute: ItemType.Icon
                                            };
                                        };
                                        l5.paramsGenerator_ = m5;
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(j5, {});
                                    }
                                }, { name: "ImageMenuItem" });
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
                                    attribute: ItemType.Icon,
                                }, undefined, r4, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 338, col: 11 });
                                ViewPU.create(t4);
                                let u4 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                        },
                                        attribute: ItemType.Icon
                                    };
                                };
                                t4.paramsGenerator_ = u4;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(r4, {});
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
    constructor(w3, x3, y3, z3 = -1, a4 = undefined, b4) {
        super(w3, y3, z3, b4);
        if (typeof a4 === "function") {
            this.paramsGenerator_ = a4;
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
        this.__fontSize = new ObservedPropertySimplePU(1, this, "fontSize");
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, "isOnFocus");
        this.__isOnHover = new ObservedPropertySimplePU(false, this, "isOnHover");
        this.__isOnClick = new ObservedPropertySimplePU(false, this, "isOnClick");
        this.__editableTitleBarTheme = this.initializeConsume("editableTitleBarTheme", "editableTitleBarTheme");
        this.dialogController = new CustomDialogController({
            builder: () => {
                let e4 = new EditableTitleBarDialog(this, {
                    cancel: () => {
                    },
                    confirm: () => {
                    },
                    itemEditableDialog: this.item,
                    textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
                }, undefined, -1, () => { }, { page: "library/src/main/ets/components/mainpage/MainPage.ets", line: 370, col: 14 });
                e4.setController(this.dialogController);
                ViewPU.create(e4);
                let f4 = () => {
                    return {
                        cancel: () => {
                        },
                        confirm: () => {
                        },
                        itemEditableDialog: this.item,
                        textEditableTitleBarDialog: this.item.label ? this.item.label : this.textDialog()
                    };
                };
                e4.paramsGenerator_ = f4;
            },
            maskColor: Color.Transparent,
            isModal: true,
            customStyle: true
        }, this);
        this.envCallback = {
            onConfigurationUpdated(d4) {
                AppStorage.setOrCreate('fontSizeScale', d4.fontSizeScale);
                hilog.error(0x3900, 'Ace', `fontSizeScale: ${Number(AppStorage.get('fontSizeScale'))}`);
            },
            onMemoryLevel(c4) {
            }
        };
        this.setInitiallyProvidedValue(x3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(v3) {
        if (v3.item !== undefined) {
            this.item = v3.item;
        }
        if (v3.attribute !== undefined) {
            this.attribute = v3.attribute;
        }
        if (v3.callbackId !== undefined) {
            this.callbackId = v3.callbackId;
        }
        if (v3.minFontSize !== undefined) {
            this.minFontSize = v3.minFontSize;
        }
        if (v3.maxFontSize !== undefined) {
            this.maxFontSize = v3.maxFontSize;
        }
        if (v3.fontSize !== undefined) {
            this.fontSize = v3.fontSize;
        }
        if (v3.isOnFocus !== undefined) {
            this.isOnFocus = v3.isOnFocus;
        }
        if (v3.isOnHover !== undefined) {
            this.isOnHover = v3.isOnHover;
        }
        if (v3.isOnClick !== undefined) {
            this.isOnClick = v3.isOnClick;
        }
        if (v3.dialogController !== undefined) {
            this.dialogController = v3.dialogController;
        }
        if (v3.envCallback !== undefined) {
            this.envCallback = v3.envCallback;
        }
    }
    updateStateVars(u3) {
    }
    purgeVariableDependenciesOnElmtId(t3) {
        this.__fontSize.purgeDependencyOnElmtId(t3);
        this.__isOnFocus.purgeDependencyOnElmtId(t3);
        this.__isOnHover.purgeDependencyOnElmtId(t3);
        this.__isOnClick.purgeDependencyOnElmtId(t3);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(t3);
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
    set fontSize(s3) {
        this.__fontSize.set(s3);
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(r3) {
        this.__isOnFocus.set(r3);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(q3) {
        this.__isOnHover.set(q3);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(p3) {
        this.__isOnClick.set(p3);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(o3) {
        this.__editableTitleBarTheme.set(o3);
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
    async aboutToAppear() {
        let n3 = this.getUIContext().getHostContext();
        hilog.info(0x3900, 'Ace', `initConfig context.config fontSizeScale: ${JSON.stringify(n3.config.fontSizeScale)}`);
        if (n3.config.fontSizeScale) {
            AppStorage.setOrCreate('fontSizeScale', n3.config.fontSizeScale);
        }
        this.callbackId = getContext().getApplicationContext().on('environment', this.envCallback);
    }
    aboutToDisappear() {
        if (this.callbackId) {
            getContext().getApplicationContext().off('environment', this.callbackId);
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
    IconBuilder(u2 = null) {
        this.observeComponentCreation2((z2, a3) => {
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
                    if (Number(AppStorage.get('fontSizeScale')) >= this.minFontSize) {
                        this.dialogController?.close();
                    }
                    this.isOnClick = false;
                }
            });
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Exclusive);
            LongPressGesture.create({ repeat: false, duration: 500 });
            LongPressGesture.onAction((j3) => {
                console.log('LongPressGesture success');
                if (j3) {
                    if (Number(AppStorage.get('fontSizeScale')) >= this.minFontSize) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            TapGesture.create();
            TapGesture.onAction((i3) => {
                this.item.isEnabled && this.item.action && this.item.action();
            });
            TapGesture.pop();
            GestureGroup.pop();
            Gesture.pop();
        }, Button);
        this.observeComponentCreation2((x2, y2) => {
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
    ImageBuilder(y1 = null) {
        this.observeComponentCreation2((s2, t2) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                start: LengthMetrics.resource({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }),
            });
        }, Stack);
        this.observeComponentCreation2((q2, r2) => {
            Image.create(this.item.value);
            Image.width({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.height({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((c2, d2) => {
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
            Button.onHover((p2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = p2;
            });
            Button.onKeyEvent((o2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (o2.keyCode !== KeyCode.KEYCODE_ENTER && o2.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (o2.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (o2.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((n2) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (n2.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (n2.type === TouchType.Up) {
                    if (Number(AppStorage.get('fontSizeScale')) >= this.minFontSize) {
                        this.dialogController?.close();
                    }
                    this.isOnClick = false;
                }
            });
            Gesture.create(GesturePriority.Low);
            GestureGroup.create(GestureMode.Exclusive);
            LongPressGesture.create({ repeat: false, duration: 500 });
            LongPressGesture.onAction((m2) => {
                console.log('LongPressGesture success');
                if (m2) {
                    if (Number(AppStorage.get('fontSizeScale')) >= this.minFontSize) {
                        this.dialogController?.open();
                    }
                }
            });
            LongPressGesture.pop();
            TapGesture.create();
            TapGesture.onAction((l2) => {
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
        this.observeComponentCreation2((u1, v1) => {
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
        this.__fontSize = new ObservedPropertySimplePU(1, this, "fontSize");
        this.__maxLines = new ObservedPropertySimplePU(1, this, "maxLines");
        this.__windowStandardHeight = this.createStorageProp('windowStandardHeight', 0, "windowStandardHeight");
        this.cancel = () => {
        };
        this.confirm = () => {
        };
        this.envCallback = {
            onConfigurationUpdated(s1) {
                AppStorage.setOrCreate('fontSizeScale', s1.fontSizeScale);
            },
            onMemoryLevel(r1) {
            }
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
        if (i1.fontSize !== undefined) {
            this.fontSize = i1.fontSize;
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
        if (i1.envCallback !== undefined) {
            this.envCallback = i1.envCallback;
        }
    }
    updateStateVars(h1) {
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
        if (e.config.fontSizeScale) {
            AppStorage.setOrCreate('fontSizeScale', e.config.fontSizeScale);
        }
        this.mainWindowStage = e.windowStage.getMainWindowSync();
        let f = this.mainWindowStage.getWindowProperties();
        let g = f.windowRect;
        if (px2vp(g.height) > 640) {
            this.maxLines = 6;
        }
        else {
            this.maxLines = 1;
        }
        this.callbackId = getContext().getApplicationContext().on('environment', this.envCallback);
    }
    aboutToDisappear() {
        if (this.callbackId) {
            getContext().getApplicationContext().off('environment', this.callbackId);
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