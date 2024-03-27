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

const hilog = requireNapi('hilog');
const KeyCode = requireNapi('multimodalInput.keyCode').KeyCode;
const resourceManager = requireNapi('resourceManager');
export var EditableLeftIconType;
(function (a) {
    a[a['Back'] = 0] = 'Back';
    a[a['Cancel'] = 1] = 'Cancel';
})(EditableLeftIconType || (EditableLeftIconType = {}));
var ItemType;
(function (b) {
    b[b['Image'] = 0] = 'Image';
    b[b['Icon'] = 1] = 'Icon';
    b[b['LeftIcon'] = 2] = 'LeftIcon';
})(ItemType || (ItemType = {}));
const PUBLIC_CANCEL = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_cancel'], 'bundleName': '', 'moduleName': '' };
const PUBLIC_OK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_public_ok'], 'bundleName': '', 'moduleName': '' };
const PUBLIC_BACK = { 'id': -1, 'type': 20000, params: ['sys.media.ohos_ic_compnent_titlebar_back'], 'bundleName': '', 'moduleName': '' };
export class EditableTitleBar extends ViewPU {
    constructor(c, d, e, f = -1, g = undefined, h) {
        super(c, e, f, h);
        if (typeof g === 'function') {
            this.paramsGenerator_ = g;
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
        this.__backActive = new ObservedPropertySimplePU(false, this, 'backActive');
        this.setInitiallyProvidedValue(d);
    }
    setInitiallyProvidedValue(i) {
        if (i.leftIconStyle !== undefined) {
            this.leftIconStyle = i.leftIconStyle;
        }
        if (i.title !== undefined) {
            this.title = i.title;
        }
        if (i.subtitle !== undefined) {
            this.subtitle = i.subtitle;
        }
        if (i.isSaveIconRequired !== undefined) {
            this.isSaveIconRequired = i.isSaveIconRequired;
        }
        if (i.imageItem !== undefined) {
            this.imageItem = i.imageItem;
        }
        if (i.menuItems !== undefined) {
            this.menuItems = i.menuItems;
        }
        if (i.options !== undefined) {
            this.options = i.options;
        }
        if (i.onSave !== undefined) {
            this.onSave = i.onSave;
        }
        if (i.onCancel !== undefined) {
            this.onCancel = i.onCancel;
        }
        if (i.titleMaxWidth !== undefined) {
            this.titleMaxWidth = i.titleMaxWidth;
        }
        if (i.backActive !== undefined) {
            this.backActive = i.backActive;
        }
    }
    updateStateVars(j) {
    }
    purgeVariableDependenciesOnElmtId(k) {
        this.__titleMaxWidth.purgeDependencyOnElmtId(k);
        this.__backActive.purgeDependencyOnElmtId(k);
    }
    aboutToBeDeleted() {
        this.__titleMaxWidth.aboutToBeDeleted();
        this.__backActive.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get titleMaxWidth() {
        return this.__titleMaxWidth.get();
    }
    set titleMaxWidth(l) {
        this.__titleMaxWidth.set(l);
    }
    get backActive() {
        return this.__backActive.get();
    }
    set backActive(m) {
        this.__backActive.set(m);
    }
    initialRender() {
        this.observeComponentCreation2((o, p) => {
            Flex.create({
                justifyContent: FlexAlign.SpaceBetween,
                alignItems: ItemAlign.Stretch,
            });
            Flex.width('100%');
            Flex.backgroundColor(this.options.backgroundColor ? this.options.backgroundColor :
                EditableTitleBar.noneColor);
            Flex.backgroundBlurStyle(this.options.backgroundBlurStyle ? this.options.backgroundBlurStyle :
                BlurStyle.NONE);
            Flex.expandSafeArea(this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM],
                this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP]);
            Flex.onAreaChange((r, s) => {
                var t, u, v;
                let w = EditableTitleBar.commonZero;
                if (this.isSaveIconRequired) {
                    w = EditableTitleBar.maxOtherCountOfExtraItems;
                    EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonOne;
                }
                else {
                    w = EditableTitleBar.maxCountOfExtraItems;
                    EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonZero;
                }
                if (this.imageItem) {
                    EditableTitleBar.countOfImageItem = EditableTitleBar.commonOne;
                }
                else {
                    EditableTitleBar.countOfImageItem = EditableTitleBar.commonZero;
                }
                let x = Number(s.width);
                x = x - EditableTitleBar.leftMargin -
                    EditableTitleBar.rightMargin - EditableTitleBar.titlePadding;
                x = x - ImageMenuItem.imageHotZoneWidth;
                if (this.menuItems === undefined) {
                    this.titleMaxWidth = x -
                        EditableTitleBar.countOfImageItem *
                            (ImageMenuItem.imageHotZoneWidth +
                                ImageMenuItem.iconBackgroundSpaceHorizontal) -
                        EditableTitleBar.countOfSaveIcon *
                            (ImageMenuItem.imageHotZoneWidth + ImageMenuItem.iconBackgroundSpaceHorizontal);
                    return;
                }
                if (((t = this.menuItems) === null || t === void 0 ? void 0 : t.length) >= EditableTitleBar.maxCountOfExtraItems) {
                    this.titleMaxWidth = x -
                        ImageMenuItem.imageHotZoneWidth * EditableTitleBar.maxCountOfExtraItems -
                        EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
                        ImageMenuItem.iconBackgroundSpaceHorizontal *
                            (w + EditableTitleBar.countOfSaveIcon +
                                EditableTitleBar.countOfImageItem);
                }
                else {
                    this.titleMaxWidth = x -
                        ImageMenuItem.imageHotZoneWidth * ((u = this.menuItems) === null || u === void 0 ? void 0 : u.length) -
                        ImageMenuItem.imageHotZoneWidth * EditableTitleBar.countOfSaveIcon -
                        EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
                        ImageMenuItem.iconBackgroundSpaceHorizontal *
                            (((v = this.menuItems) === null || v === void 0 ? void 0 : v.length) + EditableTitleBar.countOfSaveIcon +
                                EditableTitleBar.countOfImageItem);
                }
            });
        }, Flex);
        this.observeComponentCreation2((y, z) => {
            Row.create();
            Row.constraintSize({
                minHeight: EditableTitleBar.totalHeight,
            });
            Row.margin({
                left: EditableTitleBar.leftMargin,
                right: EditableTitleBar.rightMargin,
            });
        }, Row);
        this.observeComponentCreation2((a1, b1) => {
            If.create();
            if (this.leftIconStyle === EditableLeftIconType.Back) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e1, f1) => {
                        Navigator.create();
                        Navigator.active(this.backActive);
                    }, Navigator);
                    Navigator.pop();
                    {
                        this.observeComponentCreation2((h1, i1) => {
                            if (i1) {
                                let j1 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_BACK,
                                            isEnabled: true,
                                            action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                        },
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                ViewPU.create(new ImageMenuItem(this, { item: {
                                        value: PUBLIC_BACK,
                                        isEnabled: true,
                                        action: () => this.onCancel ? this.onCancel() : this.backActive = true,
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, h1, j1, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 91 }));
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(h1, {});
                            }
                        }, null);
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                    {
                        this.observeComponentCreation2((n1, o1) => {
                            if (o1) {
                                let p1 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_CANCEL,
                                            isEnabled: true,
                                            action: () => this.onCancel && this.onCancel(),
                                        },
                                        attribute: ItemType.LeftIcon
                                    };
                                };
                                ViewPU.create(new ImageMenuItem(this, { item: {
                                        value: PUBLIC_CANCEL,
                                        isEnabled: true,
                                        action: () => this.onCancel && this.onCancel(),
                                    },
                                    attribute: ItemType.LeftIcon,
                                }, undefined, n1, p1, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 99 }));
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(n1, {});
                            }
                        }, null);
                    }
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((r1, s1) => {
            If.create();
            if (this.imageItem !== undefined) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((v1, w1) => {
                            if (w1) {
                                let x1 = () => {
                                    return {
                                        item: this.imageItem,
                                        attribute: ItemType.Image
                                    };
                                };
                                ViewPU.create(new ImageMenuItem(this, {
                                    item: this.imageItem,
                                    attribute: ItemType.Image,
                                }, undefined, v1, x1, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 108 }));
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(v1, {});
                            }
                        }, null);
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((a2, b2) => {
            Column.create();
            Column.justifyContent(FlexAlign.Start);
            Column.padding({
                top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '', 'moduleName': '' },
                bottom: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level2'], 'bundleName': '', 'moduleName': '' },
            });
            Column.margin({
                left: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_space_horizontal'], 'bundleName': '', 'moduleName': '' },
            });
            Column.alignItems(HorizontalAlign.Start);
            Column.constraintSize({ maxWidth: this.titleMaxWidth });
        }, Column);
        this.observeComponentCreation2((c2, d2) => {
            Row.create();
            Row.justifyContent(FlexAlign.Start);
        }, Row);
        this.observeComponentCreation2((e2, f2) => {
            Text.create(this.title);
            Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_title_tertiary_size'], 'bundleName': '', 'moduleName': '' });
            Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.titlebar_title_tertiary_color'], 'bundleName': '', 'moduleName': '' });
            Text.maxLines(1);
            Text.fontWeight(FontWeight.Bold);
            Text.textAlign(TextAlign.Start);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.width(this.titleMaxWidth);
        }, Text);
        Text.pop();
        Row.pop();
        this.observeComponentCreation2((g2, h2) => {
            If.create();
            if (this.subtitle) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((k2, l2) => {
                        Row.create();
                        Row.margin({
                            top: { 'id': -1, 'type': 10002, params: ['sys.float.padding_level1'], 'bundleName': '', 'moduleName': '' },
                        });
                        Row.justifyContent(FlexAlign.Start);
                    }, Row);
                    this.observeComponentCreation2((m2, n2) => {
                        Text.create(this.subtitle);
                        Text.fontSize({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_subheader_size'], 'bundleName': '', 'moduleName': '' });
                        Text.fontColor({ 'id': -1, 'type': 10001, params: ['sys.color.titlebar_subheader_color'], 'bundleName': '', 'moduleName': '' });
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
            this.observeComponentCreation2((q2, r2) => {
                if (r2) {
                    let s2 = () => {
                        return {
                            menuItems: this.menuItems,
                            onSave: this.onSave,
                            isSaveEnabled: this.isSaveIconRequired
                        };
                    };
                    ViewPU.create(new EditableTitleBarMenuSection(this, {
                        menuItems: this.menuItems,
                        onSave: this.onSave,
                        isSaveEnabled: this.isSaveIconRequired,
                    }, undefined, q2, s2, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 156 }));
                }
                else {
                    this.updateStateVarsOfChildByElmtId(q2, {});
                }
            }, null);
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
    constructor(u2, v2, w2, x2 = -1, y2 = undefined, z2) {
        super(u2, w2, x2, z2);
        if (typeof y2 === 'function') {
            this.paramsGenerator_ = y2;
        }
        this.menuItems = undefined;
        this.onSave = undefined;
        this.isSaveEnabled = true;
        this.setInitiallyProvidedValue(v2);
    }
    setInitiallyProvidedValue(a3) {
        if (a3.menuItems !== undefined) {
            this.menuItems = a3.menuItems;
        }
        if (a3.onSave !== undefined) {
            this.onSave = a3.onSave;
        }
        if (a3.isSaveEnabled !== undefined) {
            this.isSaveEnabled = a3.isSaveEnabled;
        }
    }
    updateStateVars(b3) {
    }
    purgeVariableDependenciesOnElmtId(c3) {
    }
    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    initialRender() {
        this.observeComponentCreation2((e3, f3) => {
            Column.create();
            Column.justifyContent(FlexAlign.Center);
        }, Column);
        this.observeComponentCreation2((g3, h3) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((i3, j3) => {
            If.create();
            if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m3, n3) => {
                        ForEach.create();
                        const o3 = q3 => {
                            const r3 = q3;
                            {
                                this.observeComponentCreation2((t3, u3) => {
                                    if (u3) {
                                        let v3 = () => {
                                            return {
                                                item: r3,
                                                attribute: ItemType.Icon
                                            };
                                        };
                                        ViewPU.create(new ImageMenuItem(this, {
                                            item: r3,
                                            attribute: ItemType.Icon,
                                        }, undefined, t3, v3, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 239 }));
                                    }
                                    else {
                                        this.updateStateVarsOfChildByElmtId(t3, {});
                                    }
                                }, null);
                            }
                        };
                        this.forEachUpdateFunction(m3, this.menuItems.slice(EditableTitleBar.commonZero, this.isSaveEnabled ?
                            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems), o3);
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
        this.observeComponentCreation2((y3, z3) => {
            If.create();
            if (this.isSaveEnabled) {
                this.ifElseBranchUpdateFunction(0, () => {
                    {
                        this.observeComponentCreation2((c4, d4) => {
                            if (d4) {
                                let e4 = () => {
                                    return {
                                        item: {
                                            value: PUBLIC_OK,
                                            isEnabled: true,
                                            action: () => this.onSave && this.onSave(),
                                        },
                                        attribute: ItemType.Icon
                                    };
                                };
                                ViewPU.create(new ImageMenuItem(this, {
                                    item: {
                                        value: PUBLIC_OK,
                                        isEnabled: true,
                                        action: () => this.onSave && this.onSave(),
                                    },
                                    attribute: ItemType.Icon,
                                }, undefined, c4, e4, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 246 }));
                            }
                            else {
                                this.updateStateVarsOfChildByElmtId(c4, {});
                            }
                        }, null);
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
    constructor(h4, i4, j4, k4 = -1, l4 = undefined, m4) {
        super(h4, j4, k4, m4);
        if (typeof l4 === 'function') {
            this.paramsGenerator_ = l4;
        }
        this.item = {
            value: '',
            isEnabled: true,
        };
        this.attribute = ItemType.Image;
        this.__isOnFocus = new ObservedPropertySimplePU(false, this, 'isOnFocus');
        this.__isOnHover = new ObservedPropertySimplePU(false, this, 'isOnHover');
        this.__isOnClick = new ObservedPropertySimplePU(false, this, 'isOnClick');
        this.setInitiallyProvidedValue(i4);
    }
    setInitiallyProvidedValue(n4) {
        if (n4.item !== undefined) {
            this.item = n4.item;
        }
        if (n4.attribute !== undefined) {
            this.attribute = n4.attribute;
        }
        if (n4.isOnFocus !== undefined) {
            this.isOnFocus = n4.isOnFocus;
        }
        if (n4.isOnHover !== undefined) {
            this.isOnHover = n4.isOnHover;
        }
        if (n4.isOnClick !== undefined) {
            this.isOnClick = n4.isOnClick;
        }
    }
    updateStateVars(o4) {
    }
    purgeVariableDependenciesOnElmtId(p4) {
        this.__isOnFocus.purgeDependencyOnElmtId(p4);
        this.__isOnHover.purgeDependencyOnElmtId(p4);
        this.__isOnClick.purgeDependencyOnElmtId(p4);
    }
    aboutToBeDeleted() {
        this.__isOnFocus.aboutToBeDeleted();
        this.__isOnHover.aboutToBeDeleted();
        this.__isOnClick.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isOnFocus() {
        return this.__isOnFocus.get();
    }
    set isOnFocus(q4) {
        this.__isOnFocus.set(q4);
    }
    get isOnHover() {
        return this.__isOnHover.get();
    }
    set isOnHover(r4) {
        this.__isOnHover.set(r4);
    }
    get isOnClick() {
        return this.__isOnClick.get();
    }
    set isOnClick(s4) {
        this.__isOnClick.set(s4);
    }
    getFgColor() {
        if (this.isOnClick) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_pressed_color'], 'bundleName': '', 'moduleName': '' };
        }
        else if (this.isOnHover) {
            return { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_hover_color'], 'bundleName': '', 'moduleName': '' };
        }
        else {
            return EditableTitleBar.noneColor;
        }
    }
    IconBuilder(t4 = null) {
        this.observeComponentCreation2((v4, w4) => {
            Button.createWithChild({ type: ButtonType.Normal, stateEffect: this.item.isEnabled });
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneWidth);
            Button.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '', 'moduleName': '' });
            Button.margin({
                left: this.attribute === ItemType.LeftIcon ? EditableTitleBar.commonZero :
                    ImageMenuItem.iconBackgroundSpaceHorizontal,
            });
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            Button.foregroundColor(this.getFgColor());
            Button.backgroundColor({ 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_color'], 'bundleName': '', 'moduleName': '' });
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '', 'moduleName': '' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_focus_outline_weight'], 'bundleName': '', 'moduleName': '' },
                color: { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_focus_outline_color'], 'bundleName': '', 'moduleName': '' },
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '', 'moduleName': '' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '', 'moduleName': '' },
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
            Button.onHover((y4) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = y4;
            });
            Button.onKeyEvent((z4) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (z4.keyCode !== KeyCode.KEYCODE_ENTER && z4.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (z4.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (z4.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((a5) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (a5.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (a5.type === TouchType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
        }, Button);
        this.observeComponentCreation2((b5, c5) => {
            Image.create(this.item.value);
            Image.width({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_width'], 'bundleName': '', 'moduleName': '' });
            Image.height({ 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_height'], 'bundleName': '', 'moduleName': '' });
            Image.fillColor({ 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_color'], 'bundleName': '', 'moduleName': '' });
            Image.focusable(this.item.isEnabled);
            Image.enabled(this.item.isEnabled);
        }, Image);
        Button.pop();
    }
    ImageBuilder(d5 = null) {
        this.observeComponentCreation2((f5, g5) => {
            Stack.create({ alignContent: Alignment.Center });
            Stack.margin({
                left: ImageMenuItem.iconBackgroundSpaceHorizontal,
            });
        }, Stack);
        this.observeComponentCreation2((h5, i5) => {
            Image.create(this.item.value);
            Image.width(ImageMenuItem.imageHotZoneWidth);
            Image.height(ImageMenuItem.imageHotZoneHeight);
            Image.borderRadius({ 'id': -1, 'type': 10002, params: ['sys.float.corner_radius_level10'], 'bundleName': '', 'moduleName': '' });
            Image.focusable(false);
            Image.enabled(this.item.isEnabled);
            Image.objectFit(ImageFit.Cover);
        }, Image);
        this.observeComponentCreation2((j5, k5) => {
            Button.createWithLabel({ type: ButtonType.Circle });
            Button.width(ImageMenuItem.imageHotZoneWidth);
            Button.height(ImageMenuItem.imageHotZoneHeight);
            Button.backgroundColor(EditableTitleBar.noneColor);
            Button.focusable(this.item.isEnabled);
            Button.enabled(this.item.isEnabled);
            ViewStackProcessor.visualState('focused');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '', 'moduleName': '' },
                width: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_focus_outline_weight'], 'bundleName': '', 'moduleName': '' },
                color: { 'id': -1, 'type': 10001, params: ['sys.color.titlebar_icon_background_focus_outline_color'], 'bundleName': '', 'moduleName': '' },
                style: BorderStyle.Solid,
            });
            ViewStackProcessor.visualState('normal');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '', 'moduleName': '' },
                width: EditableTitleBar.commonZero,
            });
            ViewStackProcessor.visualState('pressed');
            Button.border({
                radius: { 'id': -1, 'type': 10002, params: ['sys.float.titlebar_icon_background_shape'], 'bundleName': '', 'moduleName': '' },
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
            Button.onHover((m5) => {
                if (!this.item.isEnabled) {
                    return;
                }
                this.isOnHover = m5;
            });
            Button.onKeyEvent((n5) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (n5.keyCode !== KeyCode.KEYCODE_ENTER && n5.keyCode !== KeyCode.KEYCODE_SPACE) {
                    return;
                }
                if (n5.type === KeyType.Down) {
                    this.isOnClick = true;
                }
                if (n5.type === KeyType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onTouch((o5) => {
                if (!this.item.isEnabled) {
                    return;
                }
                if (o5.type === TouchType.Down) {
                    this.isOnClick = true;
                }
                if (o5.type === TouchType.Up) {
                    this.isOnClick = false;
                }
            });
            Button.onClick(() => this.item.isEnabled && this.item.action && this.item.action());
        }, Button);
        Button.pop();
        Stack.pop();
    }
    initialRender() {
        this.observeComponentCreation2((q5, r5) => {
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
function getNumberByResource(u5) {
    try {
        return resourceManager.getSystemResourceManager().getNumberByName(u5);
    }
    catch (v5) {
        let w5 = v5.code;
        let x5 = v5.message;
        hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${w5},message:${x5}`);
        return EditableTitleBar.commonZero;
    }
}
export default {
  EditableLeftIconType: EditableLeftIconType,
  EditableTitleBar: EditableTitleBar,
};