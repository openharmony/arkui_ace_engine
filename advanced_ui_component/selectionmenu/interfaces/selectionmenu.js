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

const pasteboard = requireNapi("pasteboard");
const hilog = requireNapi("hilog");

const WITHOUT_BUILDER = -2;
const defaultTheme = {
    imageSize: 24,
    buttonSize: 48,
    menuSpacing: 8,
    editorOptionMargin: 1,
    expandedOptionPadding: 3,
    defaultMenuWidth: 256,
    imageFillColor: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_primary"],
        bundleName: "",
        moduleName: ""
    },
    backGroundColor: {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_dialog_bg"],
        bundleName: "",
        moduleName: ""
    },
    iconBorderRadius: {
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_corner_radius_default_m"],
        bundleName: "",
        moduleName: ""
    },
    containerBorderRadius: {
        id: -1,
        type: 10002,
        params: ["sys.float.ohos_id_corner_radius_card"],
        bundleName: "",
        moduleName: ""
    },
    cutIcon: {
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_cut"],
        bundleName: "",
        moduleName: ""
    },
    copyIcon: {
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_copy"],
        bundleName: "",
        moduleName: ""
    },
    pasteIcon: {
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_paste"],
        bundleName: "",
        moduleName: ""
    },
    selectAllIcon: {
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_select_all"],
        bundleName: "",
        moduleName: ""
    },
    shareIcon: {
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_share"],
        bundleName: "",
        moduleName: ""
    },
    translateIcon: {
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_translate_c2e"],
        bundleName: "",
        moduleName: ""
    },
    searchIcon: {
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_search_filled"],
        bundleName: "",
        moduleName: ""
    },
    arrowDownIcon: {
        id: -1,
        type: 2e4,
        params: ["sys.media.ohos_ic_public_arrow_down"],
        bundleName: "",
        moduleName: ""
    },
    iconPanelShadowStyle: ShadowStyle.OUTER_DEFAULT_MD
};

class SelectionMenuComponent extends ViewPU {
    constructor(e, t, o, n = -1, i = void 0) {
        super(e, o, n);
        "function" == typeof i && (this.paramsGenerator_ = i);
        this.editorMenuOptions = void 0;
        this.expandedMenuOptions = void 0;
        this.controller = void 0;
        this.onPaste = void 0;
        this.onCopy = void 0;
        this.onCut = void 0;
        this.onSelectAll = void 0;
        this.theme = defaultTheme;
        this.builder = this.CloserFun;
        this.__showExpandedMenuOptions = new ObservedPropertySimplePU(!1, this, "showExpandedMenuOptions");
        this.__showCustomerIndex = new ObservedPropertySimplePU(-1, this, "showCustomerIndex");
        this.__customerChange = new ObservedPropertySimplePU(!1, this, "customerChange");
        this.__cutAndCopyEnable = new ObservedPropertySimplePU(!1, this, "cutAndCopyEnable");
        this.__pasteEnable = new ObservedPropertySimplePU(!1, this, "pasteEnable");
        this.__visibilityValue = new ObservedPropertySimplePU(Visibility.Visible, this, "visibilityValue");
        this.__customMenuSize = new ObservedPropertySimplePU("100%", this, "customMenuSize");
        this.customMenuHeight = this.theme.menuSpacing;
        this.fontWeightTable = ["100", "200", "300", "400", "500", "600", "700", "800", "900", "bold", "normal", "bolder", "lighter", "medium", "regular"];
        this.setInitiallyProvidedValue(t)
    }

    setInitiallyProvidedValue(e) {
        void 0 !== e.editorMenuOptions && (this.editorMenuOptions = e.editorMenuOptions);
        void 0 !== e.expandedMenuOptions && (this.expandedMenuOptions = e.expandedMenuOptions);
        void 0 !== e.controller && (this.controller = e.controller);
        void 0 !== e.onPaste && (this.onPaste = e.onPaste);
        void 0 !== e.onCopy && (this.onCopy = e.onCopy);
        void 0 !== e.onCut && (this.onCut = e.onCut);
        void 0 !== e.onSelectAll && (this.onSelectAll = e.onSelectAll);
        void 0 !== e.theme && (this.theme = e.theme);
        void 0 !== e.builder && (this.builder = e.builder);
        void 0 !== e.showExpandedMenuOptions && (this.showExpandedMenuOptions = e.showExpandedMenuOptions);
        void 0 !== e.showCustomerIndex && (this.showCustomerIndex = e.showCustomerIndex);
        void 0 !== e.customerChange && (this.customerChange = e.customerChange);
        void 0 !== e.cutAndCopyEnable && (this.cutAndCopyEnable = e.cutAndCopyEnable);
        void 0 !== e.pasteEnable && (this.pasteEnable = e.pasteEnable);
        void 0 !== e.visibilityValue && (this.visibilityValue = e.visibilityValue);
        void 0 !== e.customMenuSize && (this.customMenuSize = e.customMenuSize);
        void 0 !== e.customMenuHeight && (this.customMenuHeight = e.customMenuHeight);
        void 0 !== e.fontWeightTable && (this.fontWeightTable = e.fontWeightTable)
    }

    updateStateVars(e) {
    }

    purgeVariableDependenciesOnElmtId(e) {
        this.__showExpandedMenuOptions.purgeDependencyOnElmtId(e);
        this.__showCustomerIndex.purgeDependencyOnElmtId(e);
        this.__customerChange.purgeDependencyOnElmtId(e);
        this.__cutAndCopyEnable.purgeDependencyOnElmtId(e);
        this.__pasteEnable.purgeDependencyOnElmtId(e);
        this.__visibilityValue.purgeDependencyOnElmtId(e);
        this.__customMenuSize.purgeDependencyOnElmtId(e)
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
        this.aboutToBeDeletedInternal()
    }

    CloserFun(e = null) {
    }

    get showExpandedMenuOptions() {
        return this.__showExpandedMenuOptions.get()
    }

    set showExpandedMenuOptions(e) {
        this.__showExpandedMenuOptions.set(e)
    }

    get showCustomerIndex() {
        return this.__showCustomerIndex.get()
    }

    set showCustomerIndex(e) {
        this.__showCustomerIndex.set(e)
    }

    get customerChange() {
        return this.__customerChange.get()
    }

    set customerChange(e) {
        this.__customerChange.set(e)
    }

    get cutAndCopyEnable() {
        return this.__cutAndCopyEnable.get()
    }

    set cutAndCopyEnable(e) {
        this.__cutAndCopyEnable.set(e)
    }

    get pasteEnable() {
        return this.__pasteEnable.get()
    }

    set pasteEnable(e) {
        this.__pasteEnable.set(e)
    }

    get visibilityValue() {
        return this.__visibilityValue.get()
    }

    set visibilityValue(e) {
        this.__visibilityValue.set(e)
    }

    get customMenuSize() {
        return this.__customMenuSize.get()
    }

    set customMenuSize(e) {
        this.__customMenuSize.set(e)
    }

    aboutToAppear() {
        if (this.controller) {
            let e = this.controller.getSelection();
            let t = e.selection[0];
            let o = e.selection[1];
            t !== o && (this.cutAndCopyEnable = !0);
            0 === t && 0 === this.controller.getSpans({
                start: o + 1,
                end: o + 1
            }).length ? this.visibilityValue = Visibility.None : this.visibilityValue = Visibility.Visible
        } else this.expandedMenuOptions && this.expandedMenuOptions.length > 0 && (this.showExpandedMenuOptions = !0);
        let e = pasteboard.getSystemPasteboard();
        e && e.hasDataSync() && (this.pasteEnable = !0);
        this.editorMenuOptions && this.editorMenuOptions.length > 0 || (this.customMenuHeight = 0)
    }

    initialRender() {
        this.observeComponentCreation2(((e, t) => {
            Column.create();
            Column.flexShrink(1);
            Column.height(this.customMenuSize)
        }), Column);
        this.observeComponentCreation2(((e, t) => {
            If.create();
            this.editorMenuOptions && this.editorMenuOptions.length > 0 ? this.ifElseBranchUpdateFunction(0, (() => {
                this.IconPanel.bind(this)()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }))
        }), If);
        If.pop();
        this.observeComponentCreation2(((e, t) => {
            Scroll.create();
            Scroll.backgroundColor(this.theme.backGroundColor);
            Scroll.flexShrink(1);
            Scroll.shadow(this.theme.iconPanelShadowStyle);
            Scroll.borderRadius(this.theme.containerBorderRadius);
            Scroll.onAreaChange(((e, t) => {
                let o = t.height;
                let n = e.height;
                this.customMenuHeight += o - n;
                this.customMenuSize = this.customMenuHeight
            }))
        }), Scroll);
        this.SystemMenu.bind(this)();
        Scroll.pop();
        Column.pop()
    }

    pushDataToPasteboard(e) {
        let t = pasteboard.getSystemPasteboard();
        let o = pasteboard.createData(pasteboard.MIMETYPE_TEXT_PLAIN, "");
        if (e.spans && e.spans.length > 0) {
            for (let t = e.spans.length - 1; t >= 0; t--) {
                let n = e.spans[t];
                if (null == n ? void 0 : n.textStyle) {
                    let e = n;
                    let i = e.textStyle;
                    let s = pasteboard.createRecord(pasteboard.MIMETYPE_TEXT_PLAIN, e.value.substring(e.offsetInSpan[0], e.offsetInSpan[1]));
                    let a = o.getProperty();
                    let l = {
                        color: i.fontColor,
                        size: i.fontSize,
                        style: i.fontStyle,
                        weight: this.fontWeightTable[i.fontWeight],
                        fontFamily: i.fontFamily,
                        decorationType: i.decoration.type,
                        decorationColor: i.decoration.color
                    };
                    a.additions[t] = l;
                    o.addRecord(s);
                    o.setProperty(a)
                }
            }
        }
        t.clearData();
        t.setData(o).then((() => {
            hilog.info(14592, "Ace", "SelectionMenu copy option, Succeeded in setting PasteData.")
        })).catch((e => {
            hilog.info(14592, "Ace", "SelectionMenu copy option, Failed to set PasteData. Cause:" + e.message)
        }))
    }

    popDataFromPasteboard(e) {
        let t = e.selection[0];
        let o = e.selection[1];
        if (t === o && this.controller) {
            t = this.controller.getCaretOffset();
            o = this.controller.getCaretOffset()
        }
        let n = 0;
        pasteboard.getSystemPasteboard().getData(((e, i) => {
            if (e) return;
            let s = i.getRecordCount();
            for (let e = 0; e < s; e++) {
                const o = i.getRecord(e);
                let s = {
                    fontSize: 16,
                    fontColor: Color.Black,
                    fontWeight: FontWeight.Normal,
                    fontFamily: "HarmonyOS Sans",
                    fontStyle: FontStyle.Normal,
                    decoration: { type: TextDecorationType.None, color: "#FF000000" }
                };
                if (i.getProperty() && i.getProperty().additions[e]) {
                    const t = i.getProperty().additions[e];
                    t.color && (s.fontColor = t.color);
                    t.size && (s.fontSize = t.size);
                    t.style && (s.fontStyle = t.style);
                    t.weight && (s.fontWeight = t.weight);
                    t.fontFamily && (s.fontFamily = t.fontFamily);
                    t.decorationType && s.decoration && (s.decoration.type = t.decorationType);
                    t.decorationColor && s.decoration && (s.decoration.color = t.decorationColor);
                    s.decoration && (s.decoration = { type: s.decoration.type, color: s.decoration.color })
                }
                if (o && o.plainText && o.mimeType === pasteboard.MIMETYPE_TEXT_PLAIN && this.controller) {
                    this.controller.addTextSpan(o.plainText, { style: s, offset: t + n });
                    n += o.plainText.length
                }
            }
            if (this.controller) {
                this.controller.setCaretOffset(t + n);
                this.controller.closeSelectionMenu()
            }
            t !== o && this.controller && this.controller.deleteSpans({ start: t + n, end: o + n })
        }))
    }

    measureButtonWidth() {
        return this.editorMenuOptions && this.editorMenuOptions.length < 5 ? (this.theme.defaultMenuWidth - 2 * this.theme.expandedOptionPadding - 2 * this.theme.editorOptionMargin * this.editorMenuOptions.length) / this.editorMenuOptions.length : this.theme.buttonSize
    }

    IconPanel(e = null) {
        this.observeComponentCreation2(((e, t) => {
            Flex.create({ wrap: FlexWrap.Wrap });
            Flex.onAreaChange(((e, t) => {
                let o = t.height;
                let n = e.height;
                this.customMenuHeight += o - n;
                this.customMenuSize = this.customMenuHeight
            }));
            Flex.clip(!0);
            Flex.width(this.theme.defaultMenuWidth);
            Flex.padding(this.theme.expandedOptionPadding);
            Flex.borderRadius(this.theme.containerBorderRadius);
            Flex.margin({ bottom: this.theme.menuSpacing });
            Flex.backgroundColor(this.theme.backGroundColor);
            Flex.shadow(this.theme.iconPanelShadowStyle)
        }), Flex);
        this.observeComponentCreation2(((e, t) => {
            If.create();
            this.editorMenuOptions ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((e, t) => {
                    ForEach.create();
                    this.forEachUpdateFunction(e, this.editorMenuOptions, ((e, t) => {
                        const o = e;
                        this.observeComponentCreation2(((e, n) => {
                            Button.createWithChild();
                            Button.enabled(!(!o.action && !o.builder));
                            Button.type(ButtonType.Normal);
                            Button.margin(this.theme.editorOptionMargin);
                            Button.backgroundColor(this.theme.backGroundColor);
                            Button.onClick((() => {
                                if (o.builder) {
                                    this.builder = o.builder;
                                    this.showCustomerIndex = t;
                                    this.showExpandedMenuOptions = !1;
                                    this.customerChange = !this.customerChange
                                } else {
                                    this.showCustomerIndex = -2;
                                    this.controller || (this.showExpandedMenuOptions = !0)
                                }
                                o.action && o.action()
                            }));
                            Button.borderRadius(this.theme.iconBorderRadius);
                            Button.width(this.measureButtonWidth());
                            Button.height(this.theme.buttonSize)
                        }), Button);
                        this.observeComponentCreation2(((e, t) => {
                            Image.create(o.icon);
                            Image.width(this.theme.imageSize);
                            Image.height(this.theme.imageSize);
                            Image.fillColor(this.theme.imageFillColor);
                            Image.focusable(!0);
                            Image.draggable(!1)
                        }), Image);
                        Button.pop()
                    }), void 0,!0,!1)
                }), ForEach);
                ForEach.pop()
            })) : this.ifElseBranchUpdateFunction(1, (() => {
            }))
        }), If);
        If.pop();
        Flex.pop()
    }

    SystemMenu(e = null) {
        this.observeComponentCreation2(((e, t) => {
            Column.create();
            Column.width(this.theme.defaultMenuWidth)
        }), Column);
        this.observeComponentCreation2(((e, t) => {
            If.create();
            -1 === this.showCustomerIndex && (this.controller || this.expandedMenuOptions && this.expandedMenuOptions.length > 0) ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation2(((e, t) => {
                    Menu.create();
                    Menu.onVisibleAreaChange([0, 1], (() => {
                        if (!this.controller) return;
                        let e = this.controller.getSelection();
                        let t = e.selection[0];
                        let o = e.selection[1];
                        t !== o && (this.cutAndCopyEnable = !0);
                        0 === t && 0 === this.controller.getSpans({
                            start: o + 1,
                            end: o + 1
                        }).length ? this.visibilityValue = Visibility.None : this.visibilityValue = Visibility.Visible
                    }));
                    Menu.radius(this.theme.containerBorderRadius);
                    Menu.clip(!0);
                    Menu.width(this.theme.defaultMenuWidth)
                }), Menu);
                this.observeComponentCreation2(((e, t) => {
                    If.create();
                    this.controller ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation2(((e, t) => {
                            MenuItemGroup.create()
                        }), MenuItemGroup);
                        this.observeComponentCreation2(((e, t) => {
                            MenuItem.create({ startIcon: this.theme.cutIcon, content: "剪切", labelInfo: "Ctrl+X" });
                            MenuItem.enabled(this.cutAndCopyEnable);
                            MenuItem.onClick((() => {
                                if (!this.controller) return;
                                let e = this.controller.getSelection();
                                if (this.onCut) this.onCut({ content: e }); else {
                                    this.pushDataToPasteboard(e);
                                    this.controller.deleteSpans({ start: e.selection[0], end: e.selection[1] })
                                }
                            }))
                        }), MenuItem);
                        MenuItem.pop();
                        this.observeComponentCreation2(((e, t) => {
                            MenuItem.create({ startIcon: this.theme.copyIcon, content: "复制", labelInfo: "Ctrl+C" });
                            MenuItem.enabled(this.cutAndCopyEnable);
                            MenuItem.onClick((() => {
                                if (!this.controller) return;
                                let e = this.controller.getSelection();
                                if (this.onCopy) this.onCopy({ content: e }); else {
                                    this.pushDataToPasteboard(e);
                                    this.controller.closeSelectionMenu()
                                }
                            }))
                        }), MenuItem);
                        MenuItem.pop();
                        this.observeComponentCreation2(((e, t) => {
                            MenuItem.create({ startIcon: this.theme.pasteIcon, content: "粘贴", labelInfo: "Ctrl+V" });
                            MenuItem.enabled(this.pasteEnable);
                            MenuItem.onClick((() => {
                                if (!this.controller) return;
                                let e = this.controller.getSelection();
                                this.onPaste ? this.onPaste({ content: e }) : this.popDataFromPasteboard(e)
                            }))
                        }), MenuItem);
                        MenuItem.pop();
                        this.observeComponentCreation2(((e, t) => {
                            MenuItem.create({
                                startIcon: this.theme.selectAllIcon,
                                content: "全选",
                                labelInfo: "Ctrl+A"
                            });
                            MenuItem.visibility(this.visibilityValue);
                            MenuItem.onClick((() => {
                                if (this.controller) {
                                    if (this.onSelectAll) {
                                        let e = this.controller.getSelection();
                                        this.onSelectAll({ content: e })
                                    } else {
                                        this.controller.setSelection(-1, -1);
                                        this.visibilityValue = Visibility.None
                                    }
                                    this.controller.closeSelectionMenu()
                                }
                            }))
                        }), MenuItem);
                        MenuItem.pop();
                        this.observeComponentCreation2(((e, t) => {
                            If.create();
                            this.showExpandedMenuOptions ? this.ifElseBranchUpdateFunction(0, (() => {
                                this.observeComponentCreation2(((e, t) => {
                                    MenuItem.create({
                                        startIcon: this.theme.shareIcon,
                                        content: "分享",
                                        labelInfo: ""
                                    });
                                    MenuItem.enabled(!1)
                                }), MenuItem);
                                MenuItem.pop();
                                this.observeComponentCreation2(((e, t) => {
                                    MenuItem.create({
                                        startIcon: this.theme.translateIcon,
                                        content: "翻译",
                                        labelInfo: ""
                                    });
                                    MenuItem.enabled(!1)
                                }), MenuItem);
                                MenuItem.pop();
                                this.observeComponentCreation2(((e, t) => {
                                    MenuItem.create({
                                        startIcon: this.theme.searchIcon,
                                        content: "搜索",
                                        labelInfo: ""
                                    });
                                    MenuItem.enabled(!1)
                                }), MenuItem);
                                MenuItem.pop()
                            })) : this.ifElseBranchUpdateFunction(1, (() => {
                            }))
                        }), If);
                        If.pop();
                        MenuItemGroup.pop()
                    })) : this.ifElseBranchUpdateFunction(1, (() => {
                    }))
                }), If);
                If.pop();
                this.observeComponentCreation2(((e, t) => {
                    If.create();
                    this.controller && !this.showExpandedMenuOptions ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.observeComponentCreation2(((e, t) => {
                            MenuItem.create({ content: "更多", endIcon: this.theme.arrowDownIcon });
                            MenuItem.onClick((() => {
                                this.showExpandedMenuOptions = !0;
                                this.customMenuSize = "100%"
                            }))
                        }), MenuItem);
                        MenuItem.pop()
                    })) : this.showExpandedMenuOptions && this.expandedMenuOptions && this.expandedMenuOptions.length > 0 ? this.ifElseBranchUpdateFunction(1, (() => {
                        this.observeComponentCreation2(((e, t) => {
                            ForEach.create();
                            this.forEachUpdateFunction(e, this.expandedMenuOptions, ((e, t) => {
                                const o = e;
                                this.observeComponentCreation2(((e, t) => {
                                    MenuItem.create({
                                        startIcon: o.startIcon,
                                        content: o.content,
                                        endIcon: o.endIcon,
                                        labelInfo: o.labelInfo,
                                        builder: o.builder
                                    });
                                    MenuItem.onClick((() => {
                                        o.action && o.action()
                                    }))
                                }), MenuItem);
                                MenuItem.pop()
                            }), void 0,!0,!1)
                        }), ForEach);
                        ForEach.pop()
                    })) : this.ifElseBranchUpdateFunction(2, (() => {
                    }))
                }), If);
                If.pop();
                Menu.pop()
            })) : this.showCustomerIndex > -1 && this.builder ? this.ifElseBranchUpdateFunction(1, (() => {
                this.observeComponentCreation2(((e, t) => {
                    If.create();
                    this.customerChange ? this.ifElseBranchUpdateFunction(0, (() => {
                        this.builder.bind(this)()
                    })) : this.ifElseBranchUpdateFunction(1, (() => {
                        this.builder.bind(this)()
                    }))
                }), If);
                If.pop()
            })) : this.ifElseBranchUpdateFunction(2, (() => {
            }))
        }), If);
        If.pop();
        Column.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}

export function SelectionMenu(e, t = null) {
    (t || this).observeComponentCreation2(((o, n) => {
        if (n) {
            let n = () => ({
                editorMenuOptions: e.editorMenuOptions,
                expandedMenuOptions: e.expandedMenuOptions,
                controller: e.controller,
                onPaste: e.onPaste,
                onCopy: e.onCopy,
                onCut: e.onCut,
                onSelectAll: e.onSelectAll
            });
            ViewPU.create(new SelectionMenuComponent(t || this, {
                editorMenuOptions: e.editorMenuOptions,
                expandedMenuOptions: e.expandedMenuOptions,
                controller: e.controller,
                onPaste: e.onPaste,
                onCopy: e.onCopy,
                onCut: e.onCut,
                onSelectAll: e.onSelectAll
            }, void 0, o, n))
        } else (t || this).updateStateVarsOfChildByElmtId(o, {})
    }), null)
}
export default { SelectionMenu };