/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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
const pasteboard = requireNapi('pasteboard');
const hilog = requireNapi('hilog');

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

const WITHOUT_BUILDER = -2;
const defaultTheme = {
    imageSize: 24,
    buttonSize: 48,
    menuSpacing: 8,
    editorOptionMargin: 1,
    expandedOptionPadding: 3,
    defaultMenuWidth: 256,
    imageFillColor: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_primary'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    backGroundColor: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_color_dialog_bg'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    iconBorderRadius: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_default_m'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    containerBorderRadius: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_corner_radius_card'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    cutIcon: {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_cut'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    copyIcon: {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_copy'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    pasteIcon: {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_paste'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    selectAllIcon: {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_select_all'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    shareIcon: {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_share'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    translateIcon: {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_translate_c2e'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    searchIcon: {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_search_filled'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    arrowDownIcon: {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ohos_ic_public_arrow_down'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    aiWriteIcon: {
        'id': -1,
        'type': 20000,
        params: ['sys.media.ic_public_ai_write'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    iconPanelShadowStyle: ShadowStyle.OUTER_DEFAULT_MD,
};

class SelectionMenuComponent extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.editorMenuOptions = undefined;
        this.expandedMenuOptions = undefined;
        this.controller = undefined;
        this.onPaste = undefined;
        this.onCopy = undefined;
        this.onCut = undefined;
        this.onSelectAll = undefined;
        this.theme = defaultTheme;
        this.builder = this.CloserFun;
        this.__showExpandedMenuOptions = new ObservedPropertySimplePU(false, this, 'showExpandedMenuOptions');
        this.__showCustomerIndex = new ObservedPropertySimplePU(-1, this, 'showCustomerIndex');
        this.__customerChange = new ObservedPropertySimplePU(false, this, 'customerChange');
        this.__cutAndCopyEnable = new ObservedPropertySimplePU(false, this, 'cutAndCopyEnable');
        this.__pasteEnable = new ObservedPropertySimplePU(false, this, 'pasteEnable');
        this.__visibilityValue = new ObservedPropertySimplePU(Visibility.Visible, this, 'visibilityValue');
        this.__customMenuSize = new ObservedPropertySimplePU('100%', this, 'customMenuSize');
        this.customMenuHeight = this.theme.menuSpacing;
        this.fontWeightTable = ['100', '200', '300', '400', '500', '600', '700', '800', '900', 'bold', 'normal', 'bolder', 'lighter', 'medium', 'regular'];
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.editorMenuOptions !== undefined) {
            this.editorMenuOptions = params.editorMenuOptions;
        }
        if (params.expandedMenuOptions !== undefined) {
            this.expandedMenuOptions = params.expandedMenuOptions;
        }
        if (params.controller !== undefined) {
            this.controller = params.controller;
        }
        if (params.onPaste !== undefined) {
            this.onPaste = params.onPaste;
        }
        if (params.onCopy !== undefined) {
            this.onCopy = params.onCopy;
        }
        if (params.onCut !== undefined) {
            this.onCut = params.onCut;
        }
        if (params.onSelectAll !== undefined) {
            this.onSelectAll = params.onSelectAll;
        }
        if (params.theme !== undefined) {
            this.theme = params.theme;
        }
        if (params.builder !== undefined) {
            this.builder = params.builder;
        }
        if (params.showExpandedMenuOptions !== undefined) {
            this.showExpandedMenuOptions = params.showExpandedMenuOptions;
        }
        if (params.showCustomerIndex !== undefined) {
            this.showCustomerIndex = params.showCustomerIndex;
        }
        if (params.customerChange !== undefined) {
            this.customerChange = params.customerChange;
        }
        if (params.cutAndCopyEnable !== undefined) {
            this.cutAndCopyEnable = params.cutAndCopyEnable;
        }
        if (params.pasteEnable !== undefined) {
            this.pasteEnable = params.pasteEnable;
        }
        if (params.visibilityValue !== undefined) {
            this.visibilityValue = params.visibilityValue;
        }
        if (params.customMenuSize !== undefined) {
            this.customMenuSize = params.customMenuSize;
        }
        if (params.customMenuHeight !== undefined) {
            this.customMenuHeight = params.customMenuHeight;
        }
        if (params.fontWeightTable !== undefined) {
            this.fontWeightTable = params.fontWeightTable;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__showExpandedMenuOptions.purgeDependencyOnElmtId(rmElmtId);
        this.__showCustomerIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__customerChange.purgeDependencyOnElmtId(rmElmtId);
        this.__cutAndCopyEnable.purgeDependencyOnElmtId(rmElmtId);
        this.__pasteEnable.purgeDependencyOnElmtId(rmElmtId);
        this.__visibilityValue.purgeDependencyOnElmtId(rmElmtId);
        this.__customMenuSize.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__showExpandedMenuOptions.aboutToBeDeleted();
        this.__showCustomerIndex.aboutToBeDeleted();
        this.__customerChange.aboutToBeDeleted();
        this.__cutAndCopyEnable.aboutToBeDeleted();
        this.__pasteEnable.aboutToBeDeleted();
        this.__visibilityValue.aboutToBeDeleted();
        this.__customMenuSize.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    CloserFun(parent = null) {
    }

    get showExpandedMenuOptions() {
        return this.__showExpandedMenuOptions.get();
    }

    set showExpandedMenuOptions(newValue) {
        this.__showExpandedMenuOptions.set(newValue);
    }

    get showCustomerIndex() {
        return this.__showCustomerIndex.get();
    }

    set showCustomerIndex(newValue) {
        this.__showCustomerIndex.set(newValue);
    }

    get customerChange() {
        return this.__customerChange.get();
    }

    set customerChange(newValue) {
        this.__customerChange.set(newValue);
    }

    get cutAndCopyEnable() {
        return this.__cutAndCopyEnable.get();
    }

    set cutAndCopyEnable(newValue) {
        this.__cutAndCopyEnable.set(newValue);
    }

    get pasteEnable() {
        return this.__pasteEnable.get();
    }

    set pasteEnable(newValue) {
        this.__pasteEnable.set(newValue);
    }

    get visibilityValue() {
        return this.__visibilityValue.get();
    }

    set visibilityValue(newValue) {
        this.__visibilityValue.set(newValue);
    }

    get customMenuSize() {
        return this.__customMenuSize.get();
    }

    set customMenuSize(newValue) {
        this.__customMenuSize.set(newValue);
    }

    aboutToAppear() {
        if (this.controller) {
            let richEditorSelection = this.controller.getSelection();
            let start = richEditorSelection.selection[0];
            let end = richEditorSelection.selection[1];
            if (start !== end) {
                this.cutAndCopyEnable = true;
            }
            if (start === 0 && this.controller.getSpans({ start: end + 1, end: end + 1 }).length === 0) {
                this.visibilityValue = Visibility.None;
            }
            else {
                this.visibilityValue = Visibility.Visible;
            }
        }
        else if (this.expandedMenuOptions && this.expandedMenuOptions.length > 0) {
            this.showExpandedMenuOptions = true;
        }
        let sysBoard = pasteboard.getSystemPasteboard();
        if (sysBoard && sysBoard.hasDataSync()) {
            this.pasteEnable = true;
        }
        if (!(this.editorMenuOptions && this.editorMenuOptions.length > 0)) {
            this.customMenuHeight = 0;
        }
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.useShadowBatching(true);
            Column.flexShrink(1);
            Column.height(this.customMenuSize);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.editorMenuOptions && this.editorMenuOptions.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconPanel.bind(this)(this);
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create();
            Scroll.backgroundColor(this.theme.backGroundColor);
            Scroll.flexShrink(1);
            Scroll.shadow(this.theme.iconPanelShadowStyle);
            Scroll.borderRadius(this.theme.containerBorderRadius);
            Scroll.onAreaChange((oldValue, newValue) => {
                let newValueHeight = newValue.height;
                let oldValueHeight = oldValue.height;
                this.customMenuHeight += newValueHeight - oldValueHeight;
                this.customMenuSize = this.customMenuHeight;
            });
        }, Scroll);
        this.SystemMenu.bind(this)(this);
        Scroll.pop();
        Column.pop();
    }

    pushDataToPasteboard(richEditorSelection) {
        let sysBoard = pasteboard.getSystemPasteboard();
        let pasteData = pasteboard.createData(pasteboard.MIMETYPE_TEXT_PLAIN, '');
        if (richEditorSelection.spans && richEditorSelection.spans.length > 0) {
            let count = richEditorSelection.spans.length;
            for (let i = count - 1; i >= 0; i--) {
                let item = richEditorSelection.spans[i];
                if (item?.textStyle) {
                    let span = item;
                    let style = span.textStyle;
                    let data = pasteboard.createRecord(pasteboard.MIMETYPE_TEXT_PLAIN, span.value.substring(span.offsetInSpan[0], span.offsetInSpan[1]));
                    let prop = pasteData.getProperty();
                    let temp = {
                        'color': style.fontColor,
                        'size': style.fontSize,
                        'style': style.fontStyle,
                        'weight': this.fontWeightTable[style.fontWeight],
                        'fontFamily': style.fontFamily,
                        'decorationType': style.decoration.type,
                        'decorationColor': style.decoration.color
                    };
                    prop.additions[i] = temp;
                    pasteData.addRecord(data);
                    pasteData.setProperty(prop);
                }
            }
        }
        sysBoard.clearData();
        sysBoard.setData(pasteData).then(() => {
            hilog.info(0x3900, 'Ace', 'SelectionMenu copy option, Succeeded in setting PasteData.');
        }).catch((err) => {
            hilog.info(0x3900, 'Ace', 'SelectionMenu copy option, Failed to set PasteData. Cause:' + err.message);
        });
    }

    popDataFromPasteboard(richEditorSelection) {
        let start = richEditorSelection.selection[0];
        let end = richEditorSelection.selection[1];
        if (start === end && this.controller) {
            start = this.controller.getCaretOffset();
            end = this.controller.getCaretOffset();
        }
        let moveOffset = 0;
        let sysBoard = pasteboard.getSystemPasteboard();
        sysBoard.getData((err, data) => {
            if (err) {
                return;
            }
            let count = data.getRecordCount();
            for (let i = 0; i < count; i++) {
                const element = data.getRecord(i);
                let tex = {
                    fontSize: 16,
                    fontColor: Color.Black,
                    fontWeight: FontWeight.Normal,
                    fontFamily: 'HarmonyOS Sans',
                    fontStyle: FontStyle.Normal,
                    decoration: { type: TextDecorationType.None, color: '#FF000000' }
                };
                if (data.getProperty() && data.getProperty().additions[i]) {
                    const tmp = data.getProperty().additions[i];
                    if (tmp.color) {
                        tex.fontColor = tmp.color;
                    }
                    if (tmp.size) {
                        tex.fontSize = tmp.size;
                    }
                    if (tmp.style) {
                        tex.fontStyle = tmp.style;
                    }
                    if (tmp.weight) {
                        tex.fontWeight = tmp.weight;
                    }
                    if (tmp.fontFamily) {
                        tex.fontFamily = tmp.fontFamily;
                    }
                    if (tmp.decorationType && tex.decoration) {
                        tex.decoration.type = tmp.decorationType;
                    }
                    if (tmp.decorationColor && tex.decoration) {
                        tex.decoration.color = tmp.decorationColor;
                    }
                    if (tex.decoration) {
                        tex.decoration = { type: tex.decoration.type, color: tex.decoration.color };
                    }
                }
                if (element && element.plainText && element.mimeType === pasteboard.MIMETYPE_TEXT_PLAIN && this.controller) {
                    this.controller.addTextSpan(element.plainText, {
                        style: tex,
                        offset: start + moveOffset
                    });
                    moveOffset += element.plainText.length;
                }
            }
            if (this.controller) {
                this.controller.setCaretOffset(start + moveOffset);
            }
            if (start !== end && this.controller) {
                this.controller.deleteSpans({ start: start + moveOffset, end: end + moveOffset });
            }
        });
    }

    measureButtonWidth() {
        if (this.editorMenuOptions && this.editorMenuOptions.length < 5) {
            return (this.theme.defaultMenuWidth - this.theme.expandedOptionPadding * 2 -
                this.theme.editorOptionMargin * 2 * this.editorMenuOptions.length) / this.editorMenuOptions.length;
        }
        return this.theme.buttonSize;
    }

    IconPanel(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ wrap: FlexWrap.Wrap });
            Flex.onAreaChange((oldValue, newValue) => {
                let newValueHeight = newValue.height;
                let oldValueHeight = oldValue.height;
                this.customMenuHeight += newValueHeight - oldValueHeight;
                this.customMenuSize = this.customMenuHeight;
            });
            Flex.clip(true);
            Flex.width(this.theme.defaultMenuWidth);
            Flex.padding(this.theme.expandedOptionPadding);
            Flex.borderRadius(this.theme.containerBorderRadius);
            Flex.margin({ bottom: this.theme.menuSpacing });
            Flex.backgroundColor(this.theme.backGroundColor);
            Flex.shadow(this.theme.iconPanelShadowStyle);
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.editorMenuOptions) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        ForEach.create();
                        const forEachItemGenFunction = (_item, index) => {
                            const item = _item;
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Button.createWithChild();
                                Button.enabled(!(!item.action && !item.builder));
                                Button.type(ButtonType.Normal);
                                Button.margin(this.theme.editorOptionMargin);
                                Button.backgroundColor(this.theme.backGroundColor);
                                Button.onClick(() => {
                                    if (item.builder) {
                                        this.builder = item.builder;
                                        this.showCustomerIndex = index;
                                        this.showExpandedMenuOptions = false;
                                        this.customerChange = !this.customerChange;
                                    }
                                    else {
                                        this.showCustomerIndex = WITHOUT_BUILDER;
                                        if (!this.controller) {
                                            this.showExpandedMenuOptions = true;
                                        }
                                    }
                                    if (item.action) {
                                        item.action();
                                    }
                                });
                                Button.borderRadius(this.theme.iconBorderRadius);
                                Button.width(this.measureButtonWidth());
                                Button.height(this.theme.buttonSize);
                            }, Button);
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Image.create(item.icon);
                                Image.width(this.theme.imageSize);
                                Image.height(this.theme.imageSize);
                                Image.fillColor(this.theme.imageFillColor);
                                Image.focusable(true);
                                Image.draggable(false);
                            }, Image);
                            Button.pop();
                        };
                        this.forEachUpdateFunction(elmtId, this.editorMenuOptions, forEachItemGenFunction, undefined, true, false);
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
        Flex.pop();
    }

    SystemMenu(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(this.theme.defaultMenuWidth);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.showCustomerIndex === -1 &&
                (this.controller || (this.expandedMenuOptions && this.expandedMenuOptions.length > 0))) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Menu.create();
                        Menu.onVisibleAreaChange([0.0, 1.0], () => {
                            if (!this.controller) {
                                return;
                            }
                            let richEditorSelection = this.controller.getSelection();
                            let start = richEditorSelection.selection[0];
                            let end = richEditorSelection.selection[1];
                            if (start !== end) {
                                this.cutAndCopyEnable = true;
                            }
                            if (start === 0 && this.controller.getSpans({
                                start: end + 1,
                                end: end + 1
                            }).length === 0) {
                                this.visibilityValue = Visibility.None;
                            }
                            else {
                                this.visibilityValue = Visibility.Visible;
                            }
                        });
                        Menu.radius(this.theme.containerBorderRadius);
                        Menu.clip(true);
                        Menu.width(this.theme.defaultMenuWidth);
                    }, Menu);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.controller) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    MenuItemGroup.create();
                                }, MenuItemGroup);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    MenuItem.create({
                                        startIcon: this.theme.cutIcon,
                                        content: '剪切',
                                        labelInfo: 'Ctrl+X'
                                    });
                                    MenuItem.enabled(this.cutAndCopyEnable);
                                    MenuItem.onClick(() => {
                                        if (!this.controller) {
                                            return;
                                        }
                                        let richEditorSelection = this.controller.getSelection();
                                        if (this.onCut) {
                                            this.onCut({ content: richEditorSelection });
                                        }
                                        else {
                                            this.pushDataToPasteboard(richEditorSelection);
                                            this.controller.deleteSpans({
                                                start: richEditorSelection.selection[0],
                                                end: richEditorSelection.selection[1]
                                            });
                                        }
                                    });
                                }, MenuItem);
                                MenuItem.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    MenuItem.create({
                                        startIcon: this.theme.copyIcon,
                                        content: '复制',
                                        labelInfo: 'Ctrl+C'
                                    });
                                    MenuItem.enabled(this.cutAndCopyEnable);
                                    MenuItem.onClick(() => {
                                        if (!this.controller) {
                                            return;
                                        }
                                        let richEditorSelection = this.controller.getSelection();
                                        if (this.onCopy) {
                                            this.onCopy({ content: richEditorSelection });
                                        }
                                        else {
                                            this.pushDataToPasteboard(richEditorSelection);
                                            this.controller.closeSelectionMenu();
                                        }
                                    });
                                }, MenuItem);
                                MenuItem.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    MenuItem.create({
                                        startIcon: this.theme.pasteIcon,
                                        content: '粘贴',
                                        labelInfo: 'Ctrl+V'
                                    });
                                    MenuItem.enabled(this.pasteEnable);
                                    MenuItem.onClick(() => {
                                        if (!this.controller) {
                                            return;
                                        }
                                        let richEditorSelection = this.controller.getSelection();
                                        if (this.onPaste) {
                                            this.onPaste({ content: richEditorSelection });
                                        }
                                        else {
                                            this.popDataFromPasteboard(richEditorSelection);
                                            this.controller.closeSelectionMenu();
                                        }
                                    });
                                }, MenuItem);
                                MenuItem.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    MenuItem.create({
                                        startIcon: this.theme.selectAllIcon,
                                        content: '全选',
                                        labelInfo: 'Ctrl+A'
                                    });
                                    MenuItem.visibility(this.visibilityValue);
                                    MenuItem.onClick(() => {
                                        if (!this.controller) {
                                            return;
                                        }
                                        if (this.onSelectAll) {
                                            let richEditorSelection = this.controller.getSelection();
                                            this.onSelectAll({ content: richEditorSelection });
                                        }
                                        else {
                                            this.controller.setSelection(-1, -1);
                                            this.visibilityValue = Visibility.None;
                                        }
                                        this.controller.closeSelectionMenu();
                                    });
                                }, MenuItem);
                                MenuItem.pop();
                                MenuItemGroup.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.controller && !this.showExpandedMenuOptions && this.expandedMenuOptions && this.expandedMenuOptions.length > 0) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    MenuItem.create({ content: '更多', endIcon: this.theme.arrowDownIcon });
                                    MenuItem.onClick(() => {
                                        this.showExpandedMenuOptions = true;
                                        this.customMenuSize = '100%';
                                    });
                                }, MenuItem);
                                MenuItem.pop();
                            });
                        }
                        else if (this.showExpandedMenuOptions && this.expandedMenuOptions && this.expandedMenuOptions.length > 0) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = (_item, index) => {
                                        const expandedMenuOptionItem = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            MenuItem.create({
                                                startIcon: expandedMenuOptionItem.startIcon,
                                                content: expandedMenuOptionItem.content,
                                                endIcon: expandedMenuOptionItem.endIcon,
                                                labelInfo: expandedMenuOptionItem.labelInfo,
                                                builder: expandedMenuOptionItem.builder
                                            });
                                            MenuItem.onClick(() => {
                                                if (expandedMenuOptionItem.action) {
                                                    expandedMenuOptionItem.action();
                                                }
                                            });
                                        }, MenuItem);
                                        MenuItem.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.expandedMenuOptions, forEachItemGenFunction, undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Menu.pop();
                });
            }
            else if (this.showCustomerIndex > -1 && this.builder) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.customerChange) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.builder.bind(this)(parent ? parent : this);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.builder.bind(this)(parent ? parent : this);
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(2, () => {
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

export function SelectionMenu(options, parent = null) {
    const __options__ = options;
    {
        (parent ? parent : this).observeComponentCreation2((elmtId, isInitialRender, options = __options__) => {
            if (isInitialRender) {
                let componentCall = new SelectionMenuComponent(typeof PUV2ViewBase !== 'undefined' && parent instanceof PUV2ViewBase ? parent : this, {
                    editorMenuOptions: options.editorMenuOptions,
                    expandedMenuOptions: options.expandedMenuOptions,
                    controller: options.controller,
                    onPaste: options.onPaste,
                    onCopy: options.onCopy,
                    onCut: options.onCut,
                    onSelectAll: options.onSelectAll
                }, undefined, elmtId, () => {
                }, { page: 'library/src/main/ets/components/mainpage/MainPage.ets', line: 459, col: 3 });
                ViewPU.create(componentCall);
                let paramsLambda = () => {
                    return {
                        editorMenuOptions: options.editorMenuOptions,
                        expandedMenuOptions: options.expandedMenuOptions,
                        controller: options.controller,
                        onPaste: options.onPaste,
                        onCopy: options.onCopy,
                        onCut: options.onCut,
                        onSelectAll: options.onSelectAll
                    };
                };
                componentCall.paramsGenerator_ = paramsLambda;
            }
            else {
                (parent ? parent : this).updateStateVarsOfChildByElmtId(elmtId, {});
            }
        }, { name: 'SelectionMenuComponent' });
    }
}
export default { SelectionMenu };