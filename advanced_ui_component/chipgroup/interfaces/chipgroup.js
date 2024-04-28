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

const Chip = requireNapi("arkui.advanced.Chip").Chip;
const ChipSize = requireNapi("arkui.advanced.Chip").ChipSize;

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}

const noop = (h4) => {
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
function parseDimension(b4, c4, d4, e4) {
    if (c4 === void (0) || c4 === null) {
        return e4;
    }
    const f4 = b4.getHostContext()?.resourceManager;
    if (typeof c4 === "object") {
        let g4 = c4;
        if (g4.type === 10002) {
            if (f4.getNumber(g4.id) >= 0) {
                return c4;
            }
        }
        else if (g4.type === 10003) {
            if (isValidDimensionString(f4.getStringSync(g4.id))) {
                return c4;
            }
        }
    }
    else if (typeof c4 === "number") {
        if (c4 >= 0) {
            return c4;
        }
    }
    else if (typeof c4 === "string") {
        if (d4(c4)) {
            return c4;
        }
    }
    return e4;
}
function isValidString(x3, y3) {
    const z3 = x3.match(y3);
    if (!z3 || z3.length < 3) {
        return false;
    }
    const a4 = Number.parseFloat(z3[1]);
    return a4 >= 0;
}
function isValidDimensionString(w3) {
    return isValidString(w3, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i"));
}
function isValidDimensionNoPercentageString(v3) {
    return isValidString(v3, new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$", "i"));
}
export class IconGroupSuffix extends ViewPU {
    constructor(p3, q3, r3, s3 = -1, t3 = undefined, u3) {
        super(p3, r3, s3, u3);
        if (typeof t3 === "function") {
            this.paramsGenerator_ = t3;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(q3.items, this, "items");
        this.setInitiallyProvidedValue(q3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(o3) {
        if (o3.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(n3) {
        this.__items.reset(n3.items);
    }
    purgeVariableDependenciesOnElmtId(m3) {
        this.__chipSize.purgeDependencyOnElmtId(m3);
        this.__items.purgeDependencyOnElmtId(m3);
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
    set chipSize(l3) {
        this.__chipSize.set(l3);
    }
    get items() {
        return this.__items.get();
    }
    set items(k3) {
        this.__items.set(k3);
    }
    getBackgroundSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return iconGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return iconGroupSuffixTheme.normalBackgroundSize;
        }
    }
    getIconSize(i3) {
        let j3;
        if (this.chipSize === ChipSize.SMALL) {
            j3 = parseDimension(this.getUIContext(), i3, isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
        }
        else {
            j3 = parseDimension(this.getUIContext(), i3, isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
        }
        return j3;
    }
    initialRender() {
        this.observeComponentCreation2((g3, h3) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((t2, u2) => {
            ForEach.create();
            const v2 = x2 => {
                const y2 = x2;
                this.observeComponentCreation2((d3, e3) => {
                    Button.createWithChild();
                    Button.size({
                        width: this.getBackgroundSize(),
                        height: this.getBackgroundSize()
                    });
                    Button.backgroundColor(iconGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    Button.onClick(() => {
                        y2.action();
                    });
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                }, Button);
                this.observeComponentCreation2((b3, c3) => {
                    Image.create(y2.icon.src);
                    Image.fillColor(iconGroupSuffixTheme.fillColor);
                    Image.size({
                        width: this.getIconSize(y2.icon?.size?.width),
                        height: this.getIconSize(y2.icon?.size?.height)
                    });
                    Image.focusable(true);
                }, Image);
                Button.pop();
            };
            this.forEachUpdateFunction(t2, this.items || [], v2);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ChipGroup extends ViewPU {
    constructor(l2, m2, n2, o2 = -1, p2 = undefined, q2) {
        super(l2, n2, o2, q2);
        if (typeof p2 === "function") {
            this.paramsGenerator_ = p2;
        }
        this.__items = new SynchedPropertyObjectOneWayPU(m2.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(m2.itemStyle, this, "itemStyle");
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(m2.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(m2.multiple, this, "multiple");
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(m2.chipGroupSpace, this, "chipGroupSpace");
        this.suffix = undefined;
        this.onChange = noop;
        this.scroller = new Scroller();
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.setInitiallyProvidedValue(m2);
        this.declareWatch("itemStyle", this.itemStyleOnChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(k2) {
        if (k2.items === undefined) {
            this.__items.set([]);
        }
        if (k2.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (k2.chipSize !== undefined) {
            this.chipSize = k2.chipSize;
        }
        if (k2.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (k2.multiple === undefined) {
            this.__multiple.set(false);
        }
        if (k2.chipGroupSpace === undefined) {
            this.__chipGroupSpace.set(defaultTheme.chipGroupSpace);
        }
        if (k2.suffix !== undefined) {
            this.suffix = k2.suffix;
        }
        if (k2.onChange !== undefined) {
            this.onChange = k2.onChange;
        }
        if (k2.scroller !== undefined) {
            this.scroller = k2.scroller;
        }
        if (k2.isReachEnd !== undefined) {
            this.isReachEnd = k2.isReachEnd;
        }
    }
    updateStateVars(j2) {
        this.__items.reset(j2.items);
        this.__itemStyle.reset(j2.itemStyle);
        this.__selectedIndexes.reset(j2.selectedIndexes);
        this.__multiple.reset(j2.multiple);
        this.__chipGroupSpace.reset(j2.chipGroupSpace);
    }
    purgeVariableDependenciesOnElmtId(i2) {
        this.__items.purgeDependencyOnElmtId(i2);
        this.__itemStyle.purgeDependencyOnElmtId(i2);
        this.__chipSize.purgeDependencyOnElmtId(i2);
        this.__selectedIndexes.purgeDependencyOnElmtId(i2);
        this.__multiple.purgeDependencyOnElmtId(i2);
        this.__chipGroupSpace.purgeDependencyOnElmtId(i2);
        this.__isReachEnd.purgeDependencyOnElmtId(i2);
    }
    aboutToBeDeleted() {
        this.__items.aboutToBeDeleted();
        this.__itemStyle.aboutToBeDeleted();
        this.__chipSize.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__multiple.aboutToBeDeleted();
        this.__chipGroupSpace.aboutToBeDeleted();
        this.__isReachEnd.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get items() {
        return this.__items.get();
    }
    set items(h2) {
        this.__items.set(h2);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(g2) {
        this.__itemStyle.set(g2);
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(f2) {
        this.__chipSize.set(f2);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(e2) {
        this.__selectedIndexes.set(e2);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(d2) {
        this.__multiple.set(d2);
    }
    get chipGroupSpace() {
        return this.__chipGroupSpace.get();
    }
    set chipGroupSpace(c2) {
        this.__chipGroupSpace.set(c2);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(b2) {
        this.__isReachEnd.set(b2);
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
            return this.itemStyle.fontColor;
        }
        return defaultTheme.itemStyle.fontColor;
    }
    getSelectedFontColor() {
        if (this.itemStyle && this.itemStyle.selectedFontColor) {
            return this.itemStyle.selectedFontColor;
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
            return this.itemStyle.backgroundColor;
        }
        return defaultTheme.itemStyle.backgroundColor;
    }
    getSelectedBackgroundColor() {
        if (this.itemStyle && this.itemStyle.selectedBackgroundColor) {
            return this.itemStyle.selectedBackgroundColor;
        }
        return defaultTheme.itemStyle.selectedBackgroundColor;
    }
    getItemStyle() {
        return this.itemStyle ?? defaultTheme.itemStyle;
    }
    getSelectedIndexes() {
        let w1 = [];
        w1 = (this.selectedIndexes ?? [0]).filter((y1, z1, a2) => {
            return (y1 >= 0 &&
                y1 % 1 == 0 &&
                a2.indexOf(y1) === z1 &&
                y1 < (this.items || []).length);
        });
        return w1;
    }
    isMultiple() {
        return this.multiple ?? false;
    }
    getChipGroupItemSpace() {
        return parseDimension(this.getUIContext(), this.chipGroupSpace.itemSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.itemSpace);
    }
    getChipGroupStartSpace() {
        return parseDimension(this.getUIContext(), this.chipGroupSpace.startSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.startSpace);
    }
    getChipGroupEndSpace() {
        return parseDimension(this.getUIContext(), this.chipGroupSpace.endSpace, isValidDimensionNoPercentageString, defaultTheme.chipGroupSpace.endSpace);
    }
    getOnChange() {
        return this.onChange ?? noop;
    }
    isSelected(r1) {
        if (!this.isMultiple()) {
            return r1 == this.getSelectedIndexes()[0];
        }
        else {
            return this.getSelectedIndexes().some((t1, u1, v1) => {
                return (t1 == r1);
            });
        }
    }
    initialRender() {
        this.observeComponentCreation2((p1, q1) => {
            Row.create();
            Row.align(Alignment.End);
            Row.width("100%");
            Row.height(64);
        }, Row);
        this.observeComponentCreation2((n1, o1) => {
            Stack.create();
            Stack.layoutWeight(1);
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
            Stack.alignContent(Alignment.End);
        }, Stack);
        this.observeComponentCreation2((k1, l1) => {
            Scroll.create(this.scroller);
            Scroll.scrollable(ScrollDirection.Horizontal);
            Scroll.scrollBar(BarState.Off);
            Scroll.align(Alignment.Start);
            Scroll.width('100%');
            Scroll.onScroll(() => {
                this.isReachEnd = this.scroller.isAtEnd();
            });
        }, Scroll);
        this.observeComponentCreation2((i1, j1) => {
            Row.create({ space: this.getChipGroupItemSpace() });
            Row.padding({ left: this.getChipGroupStartSpace(),
                right: this.getChipGroupEndSpace() });
            Row.constraintSize({ minWidth: '100%' });
        }, Row);
        this.observeComponentCreation2((v, w) => {
            ForEach.create();
            const x = (z, a1) => {
                const b1 = z;
                this.observeComponentCreation2((d1, e1) => {
                    If.create();
                    if (b1) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            Chip.bind(this)(makeBuilderParameterProxy("Chip", { prefixIcon: () => ({
                                    src: b1.prefixIcon?.src ?? "",
                                    size: b1.prefixIcon?.size ?? undefined,
                                    fillColor: this.getFillColor(),
                                    activatedFillColor: this.getSelectedFillColor()
                                }), label: () => ({
                                    text: b1?.label?.text ?? " ",
                                    fontColor: this.getFontColor(),
                                    activatedFontColor: this.getSelectedFontColor(),
                                }), suffixIcon: () => ({
                                    src: b1.suffixIcon?.src ?? "",
                                    size: b1.suffixIcon?.size ?? undefined,
                                    fillColor: this.getFillColor(),
                                    activatedFillColor: this.getSelectedFillColor()
                                }), allowClose: () => b1.allowClose ?? false, enabled: () => true, activated: () => this.isSelected(a1), backgroundColor: () => this.getBackgroundColor(), size: () => this.getChipSize(), activatedBackgroundColor: () => this.getSelectedBackgroundColor(), onClicked: () => () => {
                                    if (this.isSelected(a1)) {
                                        this.selectedIndexes.splice(this.selectedIndexes.indexOf(a1), 1);
                                    }
                                    else {
                                        if (!this.isMultiple()) {
                                            this.selectedIndexes = [];
                                        }
                                        this.selectedIndexes.push(a1);
                                    }
                                    this.getOnChange()(this.getSelectedIndexes());
                                } }));
                        });
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(v, this.items || [], x, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
        Scroll.pop();
        this.observeComponentCreation2((o, p) => {
            If.create();
            if (this.suffix && !this.isReachEnd) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t, u) => {
                        Stack.create();
                        Stack.width(iconGroupSuffixTheme.normalBackgroundSize);
                        Stack.height(this.getChipSize() === ChipSize.SMALL ? iconGroupSuffixTheme.smallBackgroundSize : iconGroupSuffixTheme.normalBackgroundSize);
                        Stack.linearGradient({ angle: 90, colors: colorStops });
                        Stack.blendMode(BlendMode.DST_IN, BlendApplyType.OFFSCREEN);
                        Stack.hitTestBehavior(HitTestMode.None);
                    }, Stack);
                    Stack.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Stack.pop();
        this.observeComponentCreation2((h, i) => {
            If.create();
            if (this.suffix) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((m, n) => {
                        Row.create();
                        Row.padding({ left: iconGroupSuffixTheme.marginLeft, right: iconGroupSuffixTheme.marginRight, });
                    }, Row);
                    this.suffix.bind(this)(this);
                    Row.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
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