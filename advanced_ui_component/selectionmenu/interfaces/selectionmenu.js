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
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}

const WITHOUT_BUILDER = -2;
const MAX_FONT_STANDARD = 1.0;
const MAX_FONT_SCALE = 1.75;
const SYMBOL_SIZE = 24;
const defaultTheme = {
    imageSize: 24,
    buttonSize: 40,
    menuSpacing: 8,
    expandedOptionPadding: 4,
    defaultMenuWidth: 224,
    menuItemPadding: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.padding_level1'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
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
        params: ['sys.float.corner_radius_level2'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    containerBorderRadius: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.corner_radius_level4'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    borderWidth: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_menu_inner_border_width'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    borderColor: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_menu_inner_border_color'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    outlineWidth: {
        'id': -1,
        'type': 10002,
        params: ['sys.float.ohos_id_menu_outer_border_width'],
        'bundleName': '__harDefaultBundleName__',
        'moduleName': '__harDefaultModuleName__'
    },
    outlineColor: {
        'id': -1,
        'type': 10001,
        params: ['sys.color.ohos_id_menu_outer_border_color'],
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
    iconPanelShadowStyle: ShadowStyle.OUTER_DEFAULT_SM,
    defaultSymbolTheme: {
        fontSize: `${SYMBOL_SIZE}vp`,
        fontColor: [{
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }],
        symbolCutIcon: new SymbolGlyphModifier({
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.cut'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }),
        symbolCopyIcon: new SymbolGlyphModifier({
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.plus_square_on_square'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }),
        symbolPasteIcon: new SymbolGlyphModifier({
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.plus_square_dashed_on_square'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }),
        symbolSelectAllIcon: new SymbolGlyphModifier({
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.checkmark_square_on_square'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }),
        symbolShareIcon: new SymbolGlyphModifier({
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.share'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }),
        symbolTranslateIcon: new SymbolGlyphModifier({
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.translate_c2e'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }),
        symbolSearchIcon: new SymbolGlyphModifier({
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.magnifyingglass'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }),
        symbolArrowDownIcon: new SymbolGlyphModifier({
            'id': -1,
            'type': 40000,
            params: ['sys.symbol.chevron_down'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }),
    },
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
        this.__fontScale = new ObservedPropertySimplePU(1, this, 'fontScale');
        this.__customMenuWidth = new ObservedPropertySimplePU(this.theme.defaultMenuWidth, this, 'customMenuWidth');
        this.__horizontalMenuHeight = new ObservedPropertySimplePU(0, this, 'horizontalMenuHeight');
        this.__horizontalMenuWidth =
            new ObservedPropertySimplePU(this.theme.defaultMenuWidth, this, 'horizontalMenuWidth');
        this.fontWeightTable =
            ['100', '200', '300', '400', '500', '600', '700', '800', '900', 'bold', 'normal', 'bolder', 'lighter',
                'medium',
                'regular'];
        this.isFollowingSystemFontScale = false;
        this.appMaxFontScale = 3.2;
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
        if (params.fontScale !== undefined) {
            this.fontScale = params.fontScale;
        }
        if (params.customMenuWidth !== undefined) {
            this.customMenuWidth = params.customMenuWidth;
        }
        if (params.horizontalMenuHeight !== undefined) {
            this.horizontalMenuHeight = params.horizontalMenuHeight;
        }
        if (params.horizontalMenuWidth !== undefined) {
            this.horizontalMenuWidth = params.horizontalMenuWidth;
        }
        if (params.fontWeightTable !== undefined) {
            this.fontWeightTable = params.fontWeightTable;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.appMaxFontScale !== undefined) {
            this.appMaxFontScale = params.appMaxFontScale;
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
        this.__fontScale.purgeDependencyOnElmtId(rmElmtId);
        this.__customMenuWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__horizontalMenuHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__horizontalMenuWidth.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__showExpandedMenuOptions.aboutToBeDeleted();
        this.__showCustomerIndex.aboutToBeDeleted();
        this.__customerChange.aboutToBeDeleted();
        this.__cutAndCopyEnable.aboutToBeDeleted();
        this.__pasteEnable.aboutToBeDeleted();
        this.__visibilityValue.aboutToBeDeleted();
        this.__fontScale.aboutToBeDeleted();
        this.__customMenuWidth.aboutToBeDeleted();
        this.__horizontalMenuHeight.aboutToBeDeleted();
        this.__horizontalMenuWidth.aboutToBeDeleted();
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

    get fontScale() {
        return this.__fontScale.get();
    }

    set fontScale(newValue) {
        this.__fontScale.set(newValue);
    }

    get customMenuWidth() {
        return this.__customMenuWidth.get();
    }

    set customMenuWidth(newValue) {
        this.__customMenuWidth.set(newValue);
    }

    get horizontalMenuHeight() {
        return this.__horizontalMenuHeight.get();
    }

    set horizontalMenuHeight(newValue) {
        this.__horizontalMenuHeight.set(newValue);
    }

    get horizontalMenuWidth() {
        return this.__horizontalMenuWidth.get();
    }

    set horizontalMenuWidth(newValue) {
        this.__horizontalMenuWidth.set(newValue);
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
            } else {
                this.visibilityValue = Visibility.Visible;
            }
        } else if (this.expandedMenuOptions && this.expandedMenuOptions.length > 0) {
            this.showExpandedMenuOptions = true;
        }
        let sysBoard = pasteboard.getSystemPasteboard();
        if (sysBoard && sysBoard.hasDataSync()) {
            this.pasteEnable = true;
        }
        let uiContext = this.getUIContext();
        if (uiContext) {
            this.isFollowingSystemFontScale = uiContext.isFollowingSystemFontScale();
            this.appMaxFontScale = uiContext.getMaxFontScale();
        }
        this.fontScale = this.getFontScale();
    }

    hasSystemMenu() {
        let showMenuOption = this.showCustomerIndex === -1 &&
            (this.controller || (this.expandedMenuOptions && this.expandedMenuOptions.length > 0));
        let showBuilder = this.showCustomerIndex > -1 && this.builder;
        return Boolean(showMenuOption || showBuilder);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.useShadowBatching(true);
            Column.constraintSize({
                maxHeight: '100%',
                minWidth: this.theme.defaultMenuWidth
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.editorMenuOptions && this.editorMenuOptions.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.IconPanel.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create();
            Scroll.backgroundColor(this.theme.backGroundColor);
            Scroll.shadow(this.theme.iconPanelShadowStyle);
            Scroll.borderRadius(this.theme.containerBorderRadius);
            Scroll.outline(this.hasSystemMenu() ? {
                width: this.theme.outlineWidth, color: this.theme.outlineColor,
                radius: this.theme.containerBorderRadius
            } : undefined);
            Scroll.constraintSize({
                maxHeight: `calc(100% - ${this.horizontalMenuHeight > 0 ?
                    this.horizontalMenuHeight + this.theme.menuSpacing : 0}vp)`,
                minWidth: this.theme.defaultMenuWidth
            });
        }, Scroll);
        this.SystemMenu.bind(this)();
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
                    let data = pasteboard.createRecord(pasteboard.MIMETYPE_TEXT_PLAIN,
                        span.value.substring(span.offsetInSpan[0], span.offsetInSpan[1]));
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
                if (element && element.plainText && element.mimeType === pasteboard.MIMETYPE_TEXT_PLAIN &&
                this.controller) {
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
        let numOfBtnPerRow = 5;
        let width = this.fontScale > MAX_FONT_SCALE ? this.customMenuWidth : this.theme.defaultMenuWidth;
        if (this.editorMenuOptions && this.editorMenuOptions.length <= numOfBtnPerRow) {
            return (width - this.theme.expandedOptionPadding * 2) / this.editorMenuOptions.length;
        }
        return (width - this.theme.expandedOptionPadding * 2) / numOfBtnPerRow;
    }

    measureFlexPadding() {
        return Math.floor((this.theme.expandedOptionPadding - px2vp(2.0)) * 10) / 10;
    }

    getFontScale() {
        try {
            let uiContext = this.getUIContext();
            let systemFontScale = uiContext.getHostContext()?.config?.fontSizeScale ?? 1;
            if (!this.isFollowingSystemFontScale) {
                return 1;
            }
            return Math.min(systemFontScale, this.appMaxFontScale);
        } catch (exception) {
            let code = exception.code;
            let message = exception.message;
            hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
            return 1;
        }
    }

    onMeasureSize(selfLayoutInfo, children, constraint) {
        this.fontScale = this.getFontScale();
        let sizeResult = { height: 0, width: 0 };
        children.forEach((child) => {
            let childMeasureResult = child.measure(constraint);
            sizeResult.width = childMeasureResult.width;
            sizeResult.height = childMeasureResult.height;
        });
        return sizeResult;
    }

    updateMenuItemVisibility() {
        if (!this.controller) {
            return;
        }
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

    IconPanel(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ wrap: FlexWrap.Wrap });
            Flex.onAreaChange((oldValue, newValue) => {
                let newValueHeight = newValue.height;
                let newValueWidth = newValue.width;
                this.horizontalMenuHeight = newValueHeight;
                this.horizontalMenuWidth = newValueWidth;
            });
            Flex.clip(true);
            Flex.width(this.fontScale > MAX_FONT_SCALE ? this.customMenuWidth : this.theme.defaultMenuWidth);
            Flex.padding({
                top: this.measureFlexPadding(),
                bottom: this.measureFlexPadding(),
                left: this.measureFlexPadding() - 0.1,
                right: this.measureFlexPadding() - 0.1
            });
            Flex.borderRadius(this.theme.containerBorderRadius);
            Flex.margin({ bottom: this.theme.menuSpacing });
            Flex.backgroundColor(this.theme.backGroundColor);
            Flex.shadow(this.theme.iconPanelShadowStyle);
            Flex.border({
                width: this.theme.borderWidth, color: this.theme.borderColor,
                radius: this.theme.containerBorderRadius
            });
            Flex.outline({
                width: this.theme.outlineWidth, color: this.theme.outlineColor,
                radius: this.theme.containerBorderRadius
            });
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
                                Button.backgroundColor(this.theme.backGroundColor);
                                Button.onClick(() => {
                                    if (item.builder) {
                                        this.builder = item.builder;
                                        this.showCustomerIndex = index;
                                        this.showExpandedMenuOptions = false;
                                        this.customerChange = !this.customerChange;
                                    } else {
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
                                If.create();
                                if (item.symbolStyle !== undefined) {
                                    this.ifElseBranchUpdateFunction(0, () => {
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            SymbolGlyph.create();
                                            SymbolGlyph.fontColor(this.theme.defaultSymbolTheme.fontColor);
                                            SymbolGlyph.attributeModifier.bind(this)(item.symbolStyle);
                                            SymbolGlyph.focusable(true);
                                            SymbolGlyph.draggable(false);
                                            SymbolGlyph.effectStrategy(SymbolEffectStrategy.NONE);
                                            SymbolGlyph.symbolEffect(new SymbolEffect(), false);
                                            SymbolGlyph.fontSize(this.theme.defaultSymbolTheme.fontSize);
                                        }, SymbolGlyph);
                                    });
                                } else {
                                    this.ifElseBranchUpdateFunction(1, () => {
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            If.create();
                                            if (Util.isSymbolResource(item.icon)) {
                                                this.ifElseBranchUpdateFunction(0, () => {
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        SymbolGlyph.create(item.icon);
                                                        SymbolGlyph.fontColor(this.theme.defaultSymbolTheme.fontColor);
                                                        SymbolGlyph.focusable(true);
                                                        SymbolGlyph.draggable(false);
                                                        SymbolGlyph.fontSize(this.theme.defaultSymbolTheme.fontSize);
                                                    }, SymbolGlyph);
                                                });
                                            } else {
                                                this.ifElseBranchUpdateFunction(1, () => {
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Image.create(item.icon);
                                                        Image.width(this.theme.imageSize);
                                                        Image.height(this.theme.imageSize);
                                                        Image.fillColor(this.theme.imageFillColor);
                                                        Image.focusable(true);
                                                        Image.draggable(false);
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
                        };
                        this.forEachUpdateFunction(elmtId, this.editorMenuOptions, forEachItemGenFunction, undefined,
                            true, false);
                    }, ForEach);
                    ForEach.pop();
                });
            } else {
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
            Column.width(this.fontScale > MAX_FONT_SCALE ? 'auto' : this.theme.defaultMenuWidth);
            Column.shadow(this.theme.iconPanelShadowStyle);
            Column.border({
                width: this.theme.borderWidth, color: this.theme.borderColor,
                radius: this.theme.containerBorderRadius
            });
            Column.constraintSize({
                minWidth: this.theme.defaultMenuWidth
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.showCustomerIndex === -1 &&
                (this.controller || (this.expandedMenuOptions && this.expandedMenuOptions.length > 0))) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Menu.create();
                        Menu.radius(this.theme.containerBorderRadius);
                        Menu.clip(true);
                        Menu.width(this.fontScale > MAX_FONT_SCALE ? 'auto' : this.theme.defaultMenuWidth);
                        Menu.constraintSize({
                            minWidth: this.theme.defaultMenuWidth
                        });
                        Menu.onVisibleAreaChange([0.0, 1.0], () => {
                            this.updateMenuItemVisibility();
                        });
                        Menu.onAreaChange((oldValue, newValue) => {
                            let newValueWidth = newValue.width;
                            this.customMenuWidth =
                                this.fontScale > MAX_FONT_SCALE && newValueWidth > this.theme.defaultMenuWidth ? newValueWidth :
                                    this.theme.defaultMenuWidth;
                            this.updateMenuItemVisibility();
                        });
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
                                        symbolStartIcon: this.theme.defaultSymbolTheme.symbolCutIcon,
                                        content: '剪切',
                                        labelInfo: 'Ctrl+X'
                                    });
                                    MenuItem.enabled(this.cutAndCopyEnable);
                                    MenuItem.height(this.fontScale > MAX_FONT_STANDARD ? 'auto' :
                                    this.theme.buttonSize);
                                    MenuItem.borderRadius(this.theme.iconBorderRadius);
                                    MenuItem.onClick(() => {
                                        if (!this.controller) {
                                            return;
                                        }
                                        let richEditorSelection = this.controller.getSelection();
                                        if (this.onCut) {
                                            this.onCut({ content: richEditorSelection });
                                        } else {
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
                                        symbolStartIcon: this.theme.defaultSymbolTheme.symbolCopyIcon,
                                        content: '复制',
                                        labelInfo: 'Ctrl+C'
                                    });
                                    MenuItem.enabled(this.cutAndCopyEnable);
                                    MenuItem.height(this.fontScale > MAX_FONT_STANDARD ? 'auto' :
                                    this.theme.buttonSize);
                                    MenuItem.borderRadius(this.theme.iconBorderRadius);
                                    MenuItem.margin({ top: this.theme.menuItemPadding });
                                    MenuItem.onClick(() => {
                                        if (!this.controller) {
                                            return;
                                        }
                                        let richEditorSelection = this.controller.getSelection();
                                        if (this.onCopy) {
                                            this.onCopy({ content: richEditorSelection });
                                        } else {
                                            this.pushDataToPasteboard(richEditorSelection);
                                            this.controller.closeSelectionMenu();
                                        }
                                    });
                                }, MenuItem);
                                MenuItem.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    MenuItem.create({
                                        startIcon: this.theme.pasteIcon,
                                        symbolStartIcon: this.theme.defaultSymbolTheme.symbolPasteIcon,
                                        content: '粘贴',
                                        labelInfo: 'Ctrl+V'
                                    });
                                    MenuItem.enabled(this.pasteEnable);
                                    MenuItem.height(this.fontScale > MAX_FONT_STANDARD ? 'auto' :
                                    this.theme.buttonSize);
                                    MenuItem.borderRadius(this.theme.iconBorderRadius);
                                    MenuItem.margin({ top: this.theme.menuItemPadding });
                                    MenuItem.onClick(() => {
                                        if (!this.controller) {
                                            return;
                                        }
                                        let richEditorSelection = this.controller.getSelection();
                                        if (this.onPaste) {
                                            this.onPaste({ content: richEditorSelection });
                                        } else {
                                            this.popDataFromPasteboard(richEditorSelection);
                                            this.controller.closeSelectionMenu();
                                        }
                                    });
                                }, MenuItem);
                                MenuItem.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    MenuItem.create({
                                        startIcon: this.theme.selectAllIcon,
                                        symbolStartIcon: this.theme.defaultSymbolTheme.symbolSelectAllIcon,
                                        content: '全选',
                                        labelInfo: 'Ctrl+A'
                                    });
                                    MenuItem.visibility(this.visibilityValue);
                                    MenuItem.height(this.fontScale > MAX_FONT_STANDARD ? 'auto' :
                                    this.theme.buttonSize);
                                    MenuItem.borderRadius(this.theme.iconBorderRadius);
                                    MenuItem.margin({ top: this.theme.menuItemPadding });
                                    MenuItem.onClick(() => {
                                        if (!this.controller) {
                                            return;
                                        }
                                        if (this.onSelectAll) {
                                            let richEditorSelection = this.controller.getSelection();
                                            this.onSelectAll({ content: richEditorSelection });
                                        } else {
                                            this.controller.setSelection(-1, -1);
                                            this.visibilityValue = Visibility.None;
                                        }
                                        this.controller.closeSelectionMenu();
                                    });
                                }, MenuItem);
                                MenuItem.pop();
                                MenuItemGroup.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.controller && !this.showExpandedMenuOptions &&
                        this.expandedMenuOptions && this.expandedMenuOptions.length > 0) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    MenuItem.create({
                                        content: '更多',
                                        endIcon: this.theme.arrowDownIcon,
                                        symbolEndIcon: this.theme.defaultSymbolTheme.symbolArrowDownIcon
                                    });
                                    MenuItem.height(this.fontScale > MAX_FONT_STANDARD ? 'auto' :
                                    this.theme.buttonSize);
                                    MenuItem.borderRadius(this.theme.iconBorderRadius);
                                    MenuItem.margin({ top: this.theme.menuItemPadding });
                                    MenuItem.onClick(() => {
                                        this.showExpandedMenuOptions = true;
                                    });
                                }, MenuItem);
                                MenuItem.pop();
                            });
                        } else if (this.showExpandedMenuOptions && this.expandedMenuOptions &&
                            this.expandedMenuOptions.length > 0) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = (_item, index) => {
                                        const expandedMenuOptionItem = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            MenuItem.create({
                                                startIcon: expandedMenuOptionItem.startIcon,
                                                symbolStartIcon: expandedMenuOptionItem.symbolStartIcon,
                                                content: expandedMenuOptionItem.content,
                                                endIcon: expandedMenuOptionItem.endIcon,
                                                symbolEndIcon: expandedMenuOptionItem.symbolEndIcon,
                                                labelInfo: expandedMenuOptionItem.labelInfo,
                                                builder: expandedMenuOptionItem.builder
                                            });
                                            MenuItem.height(this.fontScale > MAX_FONT_STANDARD ? 'auto' :
                                            this.theme.buttonSize);
                                            MenuItem.borderRadius(this.theme.iconBorderRadius);
                                            MenuItem.margin({ top: this.theme.menuItemPadding });
                                            MenuItem.onClick(() => {
                                                if (expandedMenuOptionItem.action) {
                                                    expandedMenuOptionItem.action();
                                                }
                                            });
                                        }, MenuItem);
                                        MenuItem.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.expandedMenuOptions, forEachItemGenFunction,
                                        undefined, true, false);
                                }, ForEach);
                                ForEach.pop();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    Menu.pop();
                });
            } else if (this.showCustomerIndex > -1 && this.builder) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width(this.horizontalMenuWidth);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.customerChange) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.builder.bind(this)();
                            });
                        } else {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.builder.bind(this)();
                            });
                        }
                    }, If);
                    If.pop();
                    Column.pop();
                });
            } else {
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
                let componentCall = new SelectionMenuComponent(parent ? parent : this, {
                    editorMenuOptions: options.editorMenuOptions,
                    expandedMenuOptions: options.expandedMenuOptions,
                    controller: options.controller,
                    onPaste: options.onPaste,
                    onCopy: options.onCopy,
                    onCut: options.onCut,
                    onSelectAll: options.onSelectAll
                }, undefined, elmtId, () => {
                }, { page: 'SelectionMenu/src/main/ets/components/MainPage.ets', line: 633, col: 3 });
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
            } else {
                (parent ? parent : this).updateStateVarsOfChildByElmtId(elmtId, {});
            }
        }, { name: 'SelectionMenuComponent' });
    }
}

class Util {
    static isSymbolResource(resourceStr) {
        if (!Util.isResourceType(resourceStr)) {
            return false;
        }
        let resource = resourceStr;
        return resource.type === Util.RESOURCE_TYPE_SYMBOL;
    }

    static isResourceType(resource) {
        if (!resource) {
            return false;
        }
        if (typeof resource === 'string' || typeof resource === 'undefined') {
            return false;
        }
        return true;
    }
}

Util.RESOURCE_TYPE_SYMBOL = 40000;

export default { SelectionMenu };