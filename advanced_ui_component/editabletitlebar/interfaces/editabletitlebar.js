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
export var EditableLeftIconType;
(function (h7) {
    h7[h7["Back"] = 0] = "Back";
    h7[h7["Cancel"] = 1] = "Cancel";
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (g7) {
    g7[g7["Image"] = 0] = "Image";
    g7[g7["Icon"] = 1] = "Icon";
    g7[g7["LeftIcon"] = 2] = "LeftIcon";
})(ItemType || (ItemType = {}));
const PUBLIC_CANCEL = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_cancel'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const PUBLIC_OK = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_public_ok'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
const PUBLIC_BACK = { "id": -1, "type": 20000, params: ['sys.media.ohos_ic_compnent_titlebar_back'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" };
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
    constructor(a7, b7, c7, d7 = -1, e7 = undefined, f7) {
        super(a7, c7, d7, f7);
        if (typeof e7 === "function") {
            this.paramsGenerator_ = e7;
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
        this.__titleMaxWidth = new ObservedPropertySimplePU(0, this, "titleMaxWidth");
        this.__backActive = new ObservedPropertySimplePU(false, this, "backActive");
        this.__editableTitleBarTheme = new ObservedPropertyObjectPU(new EditableTitleBarTheme(), this, "editableTitleBarTheme");
        this.addProvidedVar("editableTitleBarTheme", this.__editableTitleBarTheme, false);
        this.setInitiallyProvidedValue(b7);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(z6) {
        if (z6.leftIconStyle !== undefined) {
            this.leftIconStyle = z6.leftIconStyle;
        }
        if (z6.title !== undefined) {
            this.title = z6.title;
        }
        if (z6.subtitle !== undefined) {
            this.subtitle = z6.subtitle;
        }
        if (z6.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = z6.isSaveIconRequired;
        }
        if (z6.imageItem !== undefined) {
            this.imageItem = z6.imageItem;
        }
        if (z6.menuItems !== undefined) {
            this.menuItems = z6.menuItems;
        }
        if (z6.options !== undefined) {
            this.options = z6.options;
        }
        if (z6.onSave !== undefined) {
            this.onSave = z6.onSave;
        }
        if (z6.onCancel !== undefined) {
            this.onCancel = z6.onCancel;
        }
        if (z6.titleMaxWidth !== undefined) {
            this.titleMaxWidth = z6.titleMaxWidth;
        }
        if (z6.backActive !== undefined) {
            this.backActive = z6.backActive;
        }
        if (z6.editableTitleBarTheme !== undefined) {
            this.editableTitleBarTheme = z6.editableTitleBarTheme;
        }
    }
    updateStateVars(y6) {
    }
    purgeVariableDependenciesOnElmtId(x6) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(x6);
        this.__backActive.purgeDependencyOnElmtId(x6);
        this.__editableTitleBarTheme.purgeDependencyOnElmtId(x6);
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
    set titleMaxWidth(w6) {
        this.__titleMaxWidth.set(w6);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(v6) {
        this.__backActive.set(v6);
    }
    get editableTitleBarTheme() {
        return this.__editableTitleBarTheme.get();
    }
    set editableTitleBarTheme(u6) {
        this.__editableTitleBarTheme.set(u6);
    }
    onWillApplyTheme(t6) {
        this.editableTitleBarTheme.iconColor = t6.colors.iconPrimary;
        this.editableTitleBarTheme.titleColor = t6.colors.fontPrimary;
        this.editableTitleBarTheme.subTitleColor = t6.colors.fontSecondary;
        this.editableTitleBarTheme.iconBackgroundColor = t6.colors.compBackgroundTertiary;
        this.editableTitleBarTheme.iconBackgroundPressedColor = t6.colors.interactivePressed;
        this.editableTitleBarTheme.iconBackgroundHoverColor = t6.colors.interactiveHover;
        this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = t6.colors.interactiveFocus;
    }
    initialRender() {
        this.observeComponentCreation2((m6, n6) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.width('100%');
            Flex.backgroundColor(this.options.backgroundColor ? this.options.backgroundColor :
                EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ? this.options.backgroundBlurStyle : BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM], this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
            Flex.onAreaChange((p6, q6) => {
                let r6 = EditableTitleBar.commonZero;
                if (this.isSaveIconRequired) {
                    r6 = EditableTitleBar.maxOtherCountOfExtraItems;
                    EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonOne;
                }
                else {
                    r6 = EditableTitleBar.maxCountOfExtraItems;
                    EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonZero;
                }
                if (this.imageItem) {
                    EditableTitleBar.countOfImageItem = EditableTitleBar.commonOne;
                }
                else {
                    EditableTitleBar.countOfImageItem = EditableTitleBar.commonZero;
                }
                let s6 = Number(q6.width);
                s6 = s6 - EditableTitleBar.leftMargin -
                    EditableTitleBar.rightMargin - EditableTitleBar.titlePadding;
                s6 = s6 - ImageMenuItem.imageHotZoneWidth;
                if (this.menuItems === undefined) {
                    this.titleMaxWidth = s6 -
                        EditableTitleBar.countOfImageItem *
                        (ImageMenuItem.imageHotZoneWidth +
                            ImageMenuItem.iconBackgroundSpaceHorizontal) -
                        EditableTitleBar.countOfSaveIcon *
                        (ImageMenuItem.imageHotZoneWidth + ImageMenuItem.iconBackgroundSpaceHorizontal);
                    return;
                }
                if (this.menuItems?.length >= EditableTitleBar.maxCountOfExtraItems) {
                    this.titleMaxWidth = s6 -
                        ImageMenuItem.imageHotZoneWidth * EditableTitleBar.maxCountOfExtraItems -
                        EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
                        ImageMenuItem.iconBackgroundSpaceHorizontal *
                        (r6 + EditableTitleBar.countOfSaveIcon +
                            EditableTitleBar.countOfImageItem);
                }
                else {
                    this.titleMaxWidth = s6 -
                        ImageMenuItem.imageHotZoneWidth * this.menuItems?.length -
                        ImageMenuItem.imageHotZoneWidth * EditableTitleBar.countOfSaveIcon -
                        EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
                        ImageMenuItem.iconBackgroundSpaceHorizontal *
                        (this.menuItems?.length + EditableTitleBar.countOfSaveIcon +
                            EditableTitleBar.countOfImageItem);
                }
            });
        }, Flex);
        this.observeComponentCreation2((k6, l6) => {
            Row.create();
            Row.constraintSize({
                minHeight: EditableTitleBar.totalHeight,
            });
            Row.margin({
                left: EditableTitleBar.leftMargin,
                right: EditableTitleBar.rightMargin,
            });
        }, Row);
        this.observeComponentCreation2((p5, q5) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((i6, j6) => {
                        Navigator.create();
                        Navigator.active(this.backActive);
                    }, Navigator);
                    Navigator.pop();
                    {
                        this.observeComponentCreation2((c6, d6) => {
                            if (d6) {
                                let e6 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, c6, () => { }, { page: "library/src/main/ets/components/mainpage/editabletitlebar.ets", line: 111, col: 11 });
                                ViewPU.create(e6);
                                let f6 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                        },
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                e6.paramsGenerator_ = f6;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(c6, {});
                            }
                        }, { name: "ImageMenuItem" });
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((t5, u5) => {
                            if (u5) {
                                let v5 = new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, t5, () => { }, { page: "library/src/main/ets/components/mainpage/editabletitlebar.ets", line: 120, col: 11 });
                                ViewPU.create(v5);
                                let w5 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                        },
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                v5.paramsGenerator_ = w5;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(t5, {});
                            }
                        }, { name: "ImageMenuItem" });
                    }
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((e5, f5) => {
            If.create();
            if (this.imageItem !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((j5, k5) => {
                            if (k5) {
                                let l5 = new ImageMenuItem(this, {
                                    item: this.imageItem,
                                    attribute: ItemType.Image,
                                }, undefined, j5, () => { }, { page: "library/src/main/ets/components/mainpage/editabletitlebar.ets", line: 130, col: 11 });
                                ViewPU.create(l5);
                                let m5 = () => {
                                    return {
                                        item: this.imageItem,
                                        attribute: ItemType.Image
                                    };
                                };
                                l5.paramsGenerator_ = m5;
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(j5, {});
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
        this.observeComponentCreation2((c5, d5) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.padding({
                top: { "id": -1, "type": 10002, params: ['sys.float.titlebar_padding_top'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                bottom: { "id": -1, "type": 10002, params: ['sys.float.titlebar_padding_bottom'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Column.margin({
                left: { "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
            });
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
        }, Column);
        this.observeComponentCreation2((a5, b5) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((y4, z4) => {
            Text.create(this.title);
            Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.titlebar_title_tertiary_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Text.fontColor(this.editableTitleBarTheme.titleColor);
            Text.maxLines(1);
            Text.fontWeight(FontWeight.Bold);
            Text.textAlign(TextAlign.Start);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width(this.titleMaxWidth);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((o4, p4) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((w4, x4) => {
                        Row.create();
                        Row.margin({
                            top: { "id": -1, "type": 10002, params: ['sys.float.padding_level1'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((u4, v4) => {
                        Text.create(this.subtitle);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.titlebar_subheader_size'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor(this.editableTitleBarTheme.subTitleColor);
                        Text.maxLines(1);
                        Text.fontWeight(FontWeight.Regular);
                        Text.textAlign(TextAlign.Start);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.width(this.titleMaxWidth);
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
            this.observeComponentCreation2((i4, j4) => {
                if (j4) {
                    let k4 = new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                    }, undefined, i4, () => { }, { page: "library/src/main/ets/components/mainpage/editabletitlebar.ets", line: 178, col: 9 });
                    ViewPU.create(k4);
                    let l4 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired
                        };
                    };
                    k4.paramsGenerator_ = l4;
                }
                else {
                    this.updateStateVarsOfChildByElmtId(i4, {});
                }
            }, { name: "EditableTitleBarMenuSection" });
        }
        Row.pop();
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
EditableTitleBar.totalHeight = getNumberByResource('titlebar_default_height');
EditableTitleBar.leftMargin = getNumberByResource('titlebar_title_margin_left');
EditableTitleBar.rightMargin = getNumberByResource('titlebar_title_margin_right');
EditableTitleBar.titlePadding = getNumberByResource('titlebar_icon_background_space_horizontal');
class EditableTitleBarMenuSection extends ViewPU {
    constructor(t3, u3, v3, w3 = -1, x3 = undefined, y3) {
        super(t3, v3, w3, y3);
        if (typeof x3 === "function") {
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
                                        }, undefined, g3, () => { }, { page: "library/src/main/ets/components/mainpage/editabletitlebar.ets", line: 261, col: 15 });
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
                                }, { name: "ImageMenuItem" });
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
                                }, undefined, o2, () => { }, { page: "library/src/main/ets/components/mainpage/editabletitlebar.ets", line: 268, col: 11 });
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
    constructor(z1, a2, b2, c2 = -1, d2 = undefined, e2) {
        super(z1, b2, c2, e2);
        if (typeof d2 === "function") {
            this.paramsGenerator_ = d2;
        }
        this.item = {
            value: '',
            isEnabled: true,
        };
        this.attribute = ItemType.Image;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, "isOnFocus");
        this.__isOnHover = new ObservedPropertySimplePU(false, this, "isOnHover");
        this.__isOnClick = new ObservedPropertySimplePU(false, this, "isOnClick");
        this.__editableTitleBarTheme = this.initializeConsume("editableTitleBarTheme", "editableTitleBarTheme");
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
    IconBuilder(c1 = null) {
        this.observeComponentCreation2((h1, i1) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneHeight);
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_background_shape'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Button.margin({
                left: this.attribute === ItemType.LeftIcon ? EditableTitleBar.commonZero :
                    ImageMenuItem.iconBackgroundSpaceHorizontal,
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
            Image.width({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_width'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.height({ "id": -1, "type": 10002, params: ['sys.float.titlebar_icon_height'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.fillColor(this.editableTitleBarTheme.iconColor);
            Image.focusable(this.item.isEnabled);
            Image.enabled(this.item.isEnabled);
        }, Image);
        Button.pop();
    }
    ImageBuilder(j = null) {
        this.observeComponentCreation2((a1, b1) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                left: ImageMenuItem.iconBackgroundSpaceHorizontal,
            });
        }, Stack);
        this.observeComponentCreation2((y, z) => {
            Image.create(this.item.value);
            Image.width(ImageMenuItem.imageHotZoneWidth);
            Image.height(ImageMenuItem.imageHotZoneHeight);
            Image.borderRadius({ "id": -1, "type": 10002, params: ['sys.float.corner_radius_level10'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((n, o) => {
            Button.createWithLabel({ type: ButtonType.Circle });
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneHeight);
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
ImageMenuItem.imageHotZoneWidth = getNumberByResource('titlebar_icon_background_width');
ImageMenuItem.imageHotZoneHeight = getNumberByResource('titlebar_icon_background_height');
ImageMenuItem.iconBackgroundSpaceHorizontal = getNumberByResource('titlebar_icon_background_space_horizontal');
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