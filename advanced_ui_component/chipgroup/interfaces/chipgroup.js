/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to  in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

const Chip = requireNapi('arkui.advanced.Chip').Chip;
const ChipSize = requireNapi('arkui.advanced.Chip').ChipSize;
const SymbolOptions = requireNapi('arkui.advanced.Chip').SymbolOptions;
const SymbolGlyphModifier = requireNapi('arkui.modifier').SymbolGlyphModifier;

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}

const noop = (x4) => {
};
const colorStops = [['rgba(0, 0, 0, 1)', 0], ['rgba(0, 0, 0, 0)', 1]];
const defaultTheme = {
    itemStyle: {
        size: ChipSize.NORMAL,
        backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        selectedFontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        selectedBackgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        selectedFillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    },
    chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 16 },
    chipGroupPadding: { top: 14, bottom: 14 }
};
const iconGroupSuffixTheme = {
    backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    borderRadius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_tips_instant_tip'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    smallIconSize: 16,
    normalIconSize: 24,
    smallBackgroundSize: 28,
    normalBackgroundSize: 36,
    marginLeft: 8,
    marginRight: 16,
    fillColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" }
};
var ChipGroupHeight;
(function (w4) {
    w4[w4["NORMAL"] = 64] = "NORMAL";
    w4[w4["SMALL"] = 52] = "SMALL";
    w4[w4["DEFAULT"] = 64] = "DEFAULT";
    w4[w4["AMEND"] = 32] = "AMEND";
})(ChipGroupHeight || (ChipGroupHeight = {}));
function parseDimension(q4, r4, s4, t4) {
    if (r4 === void (0) || r4 === null) {
        return t4;
    }
    const u4 = q4.getHostContext()?.resourceManager;
    if (typeof r4 === "object") {
        let v4 = r4;
        if (v4.type === 10002 || v4.type === 10007) {
            if (u4.getNumber(v4.id) >= 0) {
                return r4;
            }
        }
        else if (v4.type === 10003) {
            if (isValidDimensionString(u4.getStringSync(v4.id))) {
                return r4;
            }
        }
    }
    else if (typeof r4 === "number") {
        if (r4 >= 0) {
            return r4;
        }
    }
    else if (typeof r4 === "string") {
        if (s4(r4)) {
            return r4;
        }
    }
    return t4;
}
function isValidString(m4, n4) {
    const o4 = m4.match(n4);
    if (!o4 || o4.length < 3) {
        return false;
    }
    const p4 = Number.parseFloat(o4[1]);
    return p4 >= 0;
}
function isValidDimensionString(l4) {
    return isValidString(l4, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i"));
}
function isValidDimensionNoPercentageString(k4) {
    return isValidString(k4, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$", "i"));
}
export class IconGroupSuffix extends ViewPU {
    constructor(e4, f4, g4, h4 = -1, i4 = undefined, j4) {
        super(e4, g4, h4, j4);
        if (typeof i4 === "function") {
            this.paramsGenerator_ = i4;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(f4.items, this, "items");
        this.setInitiallyProvidedValue(f4);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(d4) {
        if (d4.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(c4) {
        this.__items.reset(c4.items);
    }
    purgeVariableDependenciesOnElmtId(b4) {
        this.__chipSize.purgeDependencyOnElmtId(b4);
        this.__items.purgeDependencyOnElmtId(b4);
    }
    aboutToBeDeleted() {
        this.__chipSize.aboutToBeDeleted();
        this.__items.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(a4) {
        this.__chipSize.set(a4);
    }
    get items() {
        return this.__items.get();
    }
    set items(z3) {
        this.__items.set(z3);
    }
    getBackgroundSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return iconGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return iconGroupSuffixTheme.normalBackgroundSize;
        }
    }
    getIconSize(x3) {
        if (x3 === undefined) {
            return this.chipSize === ChipSize.SMALL ? iconGroupSuffixTheme.smallIconSize : iconGroupSuffixTheme.normalIconSize;
        }
        let y3;
        if (this.chipSize === ChipSize.SMALL) {
            y3 = parseDimension(this.getUIContext(), x3, isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
        }
        else {
            y3 = parseDimension(this.getUIContext(), x3, isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
        }
        return y3;
    }
    initialRender() {
        this.observeComponentCreation((v3, w3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v3);
            Row.create();
            if (!w3) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((a3, b3) => {
            ViewStackProcessor.StartGetAccessRecordingFor(a3);
            ForEach.create();
            const c3 = e3 => {
                const f3 = e3;
                this.observeComponentCreation((s3, t3) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(s3);
                    Button.createWithChild();
                    Button.size({
                        width: this.getBackgroundSize(),
                        height: this.getBackgroundSize()
                    });
                    Button.backgroundColor(iconGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    Button.onClick(() => {
                        if (!(f3 instanceof SymbolGlyphModifier)) {
                            f3.action();
                        }
                    });
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    if (!t3) {
                        Button.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                });
                this.observeComponentCreation((i3, j3) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(i3);
                    If.create();
                    if (f3 instanceof SymbolGlyphModifier) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation((q3, r3) => {
                                ViewStackProcessor.StartGetAccessRecordingFor(q3);
                                SymbolGlyph.create();
                                SymbolGlyph.fontColor([iconGroupSuffixTheme.fillColor]);
                                SymbolGlyph.fontSize(this.getIconSize());
                                SymbolGlyph.attributeModifier.bind(this)(f3);
                                SymbolGlyph.focusable(true);
                                if (!r3) {
                                    SymbolGlyph.pop();
                                }
                                ViewStackProcessor.StopGetAccessRecording();
                            });
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                            this.observeComponentCreation((m3, n3) => {
                                ViewStackProcessor.StartGetAccessRecordingFor(m3);
                                Image.create(f3.icon.src);
                                Image.fillColor(iconGroupSuffixTheme.fillColor);
                                Image.size({
                                    width: this.getIconSize(f3.icon?.size?.width),
                                    height: this.getIconSize(f3.icon?.size?.height)
                                });
                                Image.focusable(true);
                                if (!n3) {
                                    Image.pop();
                                }
                                ViewStackProcessor.StopGetAccessRecording();
                            });
                        });
                    }
                    if (!j3) {
                        If.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                });
                If.pop();
                Button.pop();
            };
            this.forEachUpdateFunction(a3, this.items || [], c3);
            if (!b3) {
                ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ChipGroup extends ViewPU {
    constructor(s2, t2, u2, v2 = -1, w2 = undefined, x2) {
        super(s2, u2, v2, x2);
        if (typeof w2 === "function") {
            this.paramsGenerator_ = w2;
        }
        this.__items = new SynchedPropertyObjectOneWayPU(t2.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(t2.itemStyle, this, "itemStyle");
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(t2.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(t2.multiple, this, "multiple");
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(t2.chipGroupSpace, this, "chipGroupSpace");
        this.scroller = new Scroller();
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.suffix = undefined;
        this.onChange = noop;
        this.__chipGroupPadding = new SynchedPropertyObjectOneWayPU(t2.chipGroupPadding, this, "chipGroupPadding");
        this.__isRefresh = new ObservedPropertySimplePU(true, this, "isRefresh");
        this.setInitiallyProvidedValue(t2);
        this.declareWatch("items", this.onItemsChange);
        this.declareWatch("itemStyle", this.itemStyleOnChange);
        this.declareWatch("multiple", this.onMultipleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(r2) {
        if (r2.items === undefined) {
            this.__items.set([]);
        }
        if (r2.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (r2.chipSize !== undefined) {
            this.chipSize = r2.chipSize;
        }
        if (r2.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (r2.multiple === undefined) {
            this.__multiple.set(false);
        }
        if (r2.chipGroupSpace === undefined) {
            this.__chipGroupSpace.set(defaultTheme.chipGroupSpace);
        }
        if (r2.suffix !== undefined) {
            this.suffix = r2.suffix;
        }
        if (r2.onChange !== undefined) {
            this.onChange = r2.onChange;
        }
        if (r2.scroller !== undefined) {
            this.scroller = r2.scroller;
        }
        if (r2.isReachEnd !== undefined) {
            this.isReachEnd = r2.isReachEnd;
        }
        if (r2.chipGroupPadding === undefined) {
            this.__chipGroupPadding.set(defaultTheme.chipGroupPadding);
        }
        if (r2.isRefresh !== undefined) {
            this.isRefresh = r2.isRefresh;
        }
    }
    updateStateVars(q2) {
        this.__items.reset(q2.items);
        this.__itemStyle.reset(q2.itemStyle);
        this.__selectedIndexes.reset(q2.selectedIndexes);
        this.__multiple.reset(q2.multiple);
        this.__chipGroupSpace.reset(q2.chipGroupSpace);
        this.__chipGroupPadding.reset(q2.chipGroupPadding);
    }
    purgeVariableDependenciesOnElmtId(p2) {
        this.__items.purgeDependencyOnElmtId(p2);
        this.__itemStyle.purgeDependencyOnElmtId(p2);
        this.__chipSize.purgeDependencyOnElmtId(p2);
        this.__selectedIndexes.purgeDependencyOnElmtId(p2);
        this.__multiple.purgeDependencyOnElmtId(p2);
        this.__chipGroupSpace.purgeDependencyOnElmtId(p2);
        this.__isReachEnd.purgeDependencyOnElmtId(p2);
        this.__chipGroupPadding.purgeDependencyOnElmtId(p2);
        this.__isRefresh.purgeDependencyOnElmtId(p2);
    }
    aboutToBeDeleted() {
        this.__items.aboutToBeDeleted();
        this.__itemStyle.aboutToBeDeleted();
        this.__chipSize.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__multiple.aboutToBeDeleted();
        this.__chipGroupSpace.aboutToBeDeleted();
        this.__isReachEnd.aboutToBeDeleted();
        this.__chipGroupPadding.aboutToBeDeleted();
        this.__isRefresh.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get items() {
        return this.__items.get();
    }
    set items(o2) {
        this.__items.set(o2);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(n2) {
        this.__itemStyle.set(n2);
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(m2) {
        this.__chipSize.set(m2);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(l2) {
        this.__selectedIndexes.set(l2);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(k2) {
        this.__multiple.set(k2);
    }
    get chipGroupSpace() {
        return this.__chipGroupSpace.get();
    }
    set chipGroupSpace(j2) {
        this.__chipGroupSpace.set(j2);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(i2) {
        this.__isReachEnd.set(i2);
    }
    get chipGroupPadding() {
        return this.__chipGroupPadding.get();
    }
    set chipGroupPadding(h2) {
        this.__chipGroupPadding.set(h2);
    }
    get isRefresh() {
        return this.__isRefresh.get();
    }
    set isRefresh(g2) {
        this.__isRefresh.set(g2);
    }
    onItemsChange() {
        this.isRefresh = !this.isRefresh;
    }
    onMultipleChange() {
        this.selectedIndexes = this.getSelectedIndexes();
    }
    itemStyleOnChange() {
        this.chipSize = this.getChipSize();
    }
    aboutToAppear() {
        this.itemStyleOnChange();
    }
    getChipSize() {
        if (this.itemStyle && this.itemStyle.size) {
            return this.itemStyle.size;
        }
        return defaultTheme.itemStyle.size;
    }
    getFontColor() {
        if (this.itemStyle && this.itemStyle.fontColor) {
            if (typeof this.itemStyle.fontColor == 'object') {
                let f2 = this.itemStyle.fontColor;
                if (f2 == undefined || f2 == null) {
                    return defaultTheme.itemStyle.fontColor;
                }
                if (f2.type === 10001) {
                    return this.itemStyle.fontColor;
                }
                return defaultTheme.itemStyle.fontColor;
            }
        }
        return defaultTheme.itemStyle.fontColor;
    }
    getSelectedFontColor() {
        if (this.itemStyle && this.itemStyle.selectedFontColor) {
            if (typeof this.itemStyle.selectedFontColor == 'object') {
                let e2 = this.itemStyle.selectedFontColor;
                if (e2 == undefined || e2 == null) {
                    return defaultTheme.itemStyle.selectedFontColor;
                }
                if (e2.type === 10001) {
                    return this.itemStyle.selectedFontColor;
                }
                return defaultTheme.itemStyle.selectedFontColor;
            }
        }
        return defaultTheme.itemStyle.selectedFontColor;
    }
    getFillColor() {
        if (this.itemStyle && this.itemStyle.fontColor) {
            return this.itemStyle.fontColor;
        }
        return defaultTheme.itemStyle.fillColor;
    }
    getSelectedFillColor() {
        if (this.itemStyle && this.itemStyle.selectedFontColor) {
            return this.itemStyle.selectedFontColor;
        }
        return defaultTheme.itemStyle.selectedFillColor;
    }
    getBackgroundColor() {
        if (this.itemStyle && this.itemStyle.backgroundColor) {
            if (typeof this.itemStyle.backgroundColor == 'object') {
                let d2 = this.itemStyle.backgroundColor;
                if (d2 == undefined || d2 == null) {
                    return defaultTheme.itemStyle.backgroundColor;
                }
                if (d2.type === 10001) {
                    return this.itemStyle.backgroundColor;
                }
                return defaultTheme.itemStyle.backgroundColor;
            }
        }
        return defaultTheme.itemStyle.backgroundColor;
    }
    getSelectedBackgroundColor() {
        if (this.itemStyle && this.itemStyle.selectedBackgroundColor) {
            if (typeof this.itemStyle.selectedBackgroundColor == 'object') {
                let c2 = this.itemStyle.selectedBackgroundColor;
                if (c2 == undefined || c2 == null) {
                    return defaultTheme.itemStyle.selectedBackgroundColor;
                }
                if (c2.type === 10001) {
                    return this.itemStyle.selectedBackgroundColor;
                }
                return defaultTheme.itemStyle.selectedBackgroundColor;
            }
        }
        return defaultTheme.itemStyle.selectedBackgroundColor;
    }
    getSelectedIndexes() {
        let x1 = [];
        x1 = (this.selectedIndexes ?? [0]).filter((z1, a2, b2) => {
            return (z1 >= 0 &&
                z1 % 1 == 0 &&
                z1 != null &&
                z1 != undefined &&
                b2.indexOf(z1) === a2 &&
                z1 < (this.items || []).length);
        });
        if (x1.length == 0) {
            x1 = [0];
        }
        return x1;
    }
    isMultiple() {
        return this.multiple ?? false;
    }
    getChipGroupItemSpace() {
        if (this.chipGroupSpace == undefined) {
            return defaultTheme.chipGroupSpace.itemSpace;
        }
        return parseDimension(this.getUIContext(), this.chipGroupSpace.itemSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.itemSpace);
    }
    getChipGroupStartSpace() {
        if (this.chipGroupSpace == undefined) {
            return defaultTheme.chipGroupSpace.startSpace;
        }
        return parseDimension(this.getUIContext(), this.chipGroupSpace.startSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.startSpace);
    }
    getChipGroupEndSpace() {
        if (this.chipGroupSpace == undefined) {
            return defaultTheme.chipGroupSpace.endSpace;
        }
        return parseDimension(this.getUIContext(), this.chipGroupSpace.endSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.endSpace);
    }
    getOnChange() {
        return this.onChange ?? noop;
    }
    isSelected(s1) {
        if (!this.isMultiple()) {
            return s1 == this.getSelectedIndexes()[0];
        }
        else {
            return this.getSelectedIndexes().some((u1, v1, w1) => {
                return (u1 == s1);
            });
        }
    }
    getChipGroupHeight() {
        if (typeof this.chipSize === 'string') {
            if (this.chipSize === ChipSize.NORMAL) {
                return ChipGroupHeight.NORMAL;
            }
            else {
                return ChipGroupHeight.SMALL;
            }
        }
        else if (typeof this.chipSize === 'object') {
            return this.chipSize.height + ChipGroupHeight.AMEND;
        }
        else {
            return ChipGroupHeight.DEFAULT;
        }
    }
    getIconGroupSuffixHeight() {
        if (typeof this.chipSize === 'string') {
            if (this.chipSize === ChipSize.SMALL) {
                return iconGroupSuffixTheme.smallBackgroundSize;
            }
            else {
                return iconGroupSuffixTheme.normalBackgroundSize;
            }
        }
        else if (typeof this.chipSize === 'object') {
            return this.chipSize.height + ChipGroupHeight.AMEND;
        }
        else {
            return ChipGroupHeight.DEFAULT;
        }
    }
    getPaddingTop() {
        return parseDimension(this.getUIContext(), this.chipGroupPadding.top, isValidDimensionNoPercentageString, defaultTheme.chipGroupPadding.top);
    }
    getPaddingBottom() {
        return parseDimension(this.getUIContext(), this.chipGroupPadding.bottom, isValidDimensionNoPercentageString, defaultTheme.chipGroupPadding.bottom);
    }
    initialRender() {
        this.observeComponentCreation((q1, r1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(q1);
            Row.create();
            Row.align(Alignment.End);
            Row.width("100%");
            Row.height(this.getChipGroupHeight());
            Row.padding({ top: this.getPaddingTop(), bottom: this.getPaddingBottom() });
            if (!r1) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((o1, p1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o1);
            Stack.create();
            Stack.layoutWeight(1);
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
            Stack.alignContent(Alignment.End);
            if (!p1) {
                Stack.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((l1, m1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(l1);
            Scroll.create(this.scroller);
            Scroll.scrollable(ScrollDirection.Horizontal);
            Scroll.scrollBar(BarState.Off);
            Scroll.align(Alignment.Start);
            Scroll.width('100%');
            Scroll.onScroll(() => {
                this.isReachEnd = this.scroller.isAtEnd();
            });
            if (!m1) {
                Scroll.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((j1, k1) => {
            ViewStackProcessor.StartGetAccessRecordingFor(j1);
            Row.create({ space: this.getChipGroupItemSpace() });
            Row.padding({ left: this.getChipGroupStartSpace(),
                right: this.getChipGroupEndSpace() });
            Row.constraintSize({ minWidth: '100%' });
            if (!k1) {
                Row.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        this.observeComponentCreation((v, w) => {
            ViewStackProcessor.StartGetAccessRecordingFor(v);
            ForEach.create();
            const x = (a1, b1) => {
                const c1 = a1;
                this.observeComponentCreation((e1, f1) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e1);
                    If.create();
                    if (c1) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            Chip.bind(this)(makeBuilderParameterProxy("Chip", { prefixIcon: () => ({
                                src: c1.prefixIcon?.src ?? "",
                                size: c1.prefixIcon?.size ?? undefined,
                                fillColor: this.getFillColor(),
                                activatedFillColor: this.getSelectedFillColor()
                            }), prefixSymbol: () => c1?.prefixSymbol, label: () => ({
                                text: c1?.label?.text ?? " ",
                                fontColor: this.getFontColor(),
                                activatedFontColor: this.getSelectedFontColor(),
                            }), suffixIcon: () => ({
                                src: c1.suffixIcon?.src ?? "",
                                size: c1.suffixIcon?.size ?? undefined,
                                fillColor: this.getFillColor(),
                                activatedFillColor: this.getSelectedFillColor()
                            }), suffixSymbol: () => c1?.suffixSymbol, allowClose: () => c1.allowClose ?? false, enabled: () => true, activated: () => this.isSelected(b1), backgroundColor: () => this.getBackgroundColor(), size: () => this.getChipSize(), activatedBackgroundColor: () => this.getSelectedBackgroundColor(), onClicked: () => () => {
                                if (this.isSelected(b1)) {
                                    if (!(!this.isMultiple())) {
                                        if (this.getSelectedIndexes().length > 1) {
                                            this.selectedIndexes.splice(this.selectedIndexes.indexOf(b1), 1);
                                        }
                                    }
                                }
                                else {
                                    if (!this.isMultiple()) {
                                        this.selectedIndexes = [];
                                    }
                                    this.selectedIndexes.push(b1);
                                }
                                this.getOnChange()(this.getSelectedIndexes());
                            } }), this);
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                    if (!f1) {
                        If.pop();
                    }
                    ViewStackProcessor.StopGetAccessRecording();
                });
                If.pop();
            };
            this.forEachUpdateFunction(v, this.items || [], x, () => {
                return JSON.stringify(this.isRefresh);
            }, true, false);
            if (!w) {
                ForEach.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        ForEach.pop();
        Row.pop();
        Scroll.pop();
        this.observeComponentCreation((o, p) => {
            ViewStackProcessor.StartGetAccessRecordingFor(o);
            If.create();
            if (this.suffix && !this.isReachEnd) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((t, u) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(t);
                        Stack.create();
                        Stack.width(iconGroupSuffixTheme.normalBackgroundSize);
                        Stack.height(this.getIconGroupSuffixHeight());
                        Stack.linearGradient({ angle: 90, colors: colorStops });
                        Stack.blendMode(BlendMode.DST_IN, BlendApplyType.OFFSCREEN);
                        Stack.hitTestBehavior(HitTestMode.None);
                        if (!u) {
                            Stack.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!p) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Stack.pop();
        this.observeComponentCreation((h, i) => {
            ViewStackProcessor.StartGetAccessRecordingFor(h);
            If.create();
            if (this.suffix) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation((m, n) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(m);
                        Row.create();
                        Row.padding({ left: iconGroupSuffixTheme.marginLeft, right: iconGroupSuffixTheme.marginRight });
                        if (!n) {
                            Row.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    });
                    this.suffix.bind(this)(this);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
            if (!i) {
                If.pop();
            }
            ViewStackProcessor.StopGetAccessRecording();
        });
        If.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    ChipGroup,
    IconGroupSuffix
}
