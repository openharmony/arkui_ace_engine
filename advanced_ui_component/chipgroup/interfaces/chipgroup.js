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

const noop = (y3) => {
};
const colorStops = [['rgba(0, 0, 0, 1)', 0], ['rgba(0, 0, 0, 0)', 1]];
const defaultTheme = {
    itemStyle: {
        size: ChipSize.NORMAL,
        backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        fontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        selectedFontColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary_contrary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
        selectedBackgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_emphasize'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    },
    chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 16 },
    leftPadding: 16,
    rightPadding: 16,
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
function parseDimension(t3, u3, v3) {
    if (u3 === void (0) || u3 === null) {
        return v3;
    }
    const w3 = t3.getHostContext()?.resourceManager;
    if (typeof u3 === "object") {
        let x3 = u3;
        if (x3.type === 10002) {
            if (w3.getNumber(x3.id) >= 0) {
                return u3;
            }
        }
        else if (x3.type === 10003) {
            if (isValidDimensionString(w3.getStringSync(x3.id))) {
                return u3;
            }
        }
    }
    else if (typeof u3 === "number") {
        if (u3 >= 0) {
            return u3;
        }
    }
    else if (typeof u3 === "string") {
        if (isValidDimensionString(u3)) {
            return u3;
        }
    }
    return v3;
}
function isValidDimensionString(p3) {
    const q3 = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
    const r3 = p3.match(q3);
    if (!r3 || r3.length < 3) {
        return false;
    }
    const s3 = Number.parseFloat(r3[1]);
    return s3 >= 0;
}
export class IconGroupSuffix extends ViewPU {
    constructor(j3, k3, l3, m3 = -1, n3 = undefined, o3) {
        super(j3, l3, m3, o3);
        if (typeof n3 === "function") {
            this.paramsGenerator_ = n3;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(k3.items, this, "items");
        this.setInitiallyProvidedValue(k3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(i3) {
        if (i3.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(h3) {
        this.__items.reset(h3.items);
    }
    purgeVariableDependenciesOnElmtId(g3) {
        this.__chipSize.purgeDependencyOnElmtId(g3);
        this.__items.purgeDependencyOnElmtId(g3);
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
    set chipSize(f3) {
        this.__chipSize.set(f3);
    }
    get items() {
        return this.__items.get();
    }
    set items(e3) {
        this.__items.set(e3);
    }
    getBackgroundSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return iconGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return iconGroupSuffixTheme.normalBackgroundSize;
        }
    }
    getIconSize(d3) {
        if (this.chipSize === ChipSize.SMALL) {
            return parseDimension(this.getUIContext(), d3, iconGroupSuffixTheme.smallIconSize);
        }
        else {
            return parseDimension(this.getUIContext(), d3, iconGroupSuffixTheme.normalIconSize);
        }
    }
    initialRender() {
        this.observeComponentCreation2((b3, c3) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((o2, p2) => {
            ForEach.create();
            const q2 = s2 => {
                const t2 = s2;
                this.observeComponentCreation2((y2, z2) => {
                    Button.createWithChild();
                    Button.size({
                        width: this.getBackgroundSize(),
                        height: this.getBackgroundSize()
                    });
                    Button.backgroundColor(iconGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                    Button.onClick(() => {
                        t2.action();
                    });
                    Button.borderRadius(iconGroupSuffixTheme.borderRadius);
                }, Button);
                this.observeComponentCreation2((w2, x2) => {
                    Image.create(t2.icon.src);
                    Image.fillColor(iconGroupSuffixTheme.fillColor);
                    Image.size({
                        width: this.getIconSize(t2.icon?.size?.width),
                        height: this.getIconSize(t2.icon?.size?.height)
                    });
                    Image.focusable(true);
                }, Image);
                Button.pop();
            };
            this.forEachUpdateFunction(o2, this.items, q2);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ChipGroup extends ViewPU {
    constructor(g2, h2, i2, j2 = -1, k2 = undefined, l2) {
        super(g2, i2, j2, l2);
        if (typeof k2 === "function") {
            this.paramsGenerator_ = k2;
        }
        this.__items = new SynchedPropertyObjectOneWayPU(h2.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(h2.itemStyle, this, "itemStyle");
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(h2.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(h2.multiple, this, "multiple");
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(h2.chipGroupSpace, this, "chipGroupSpace");
        this.suffix = undefined;
        this.onChange = noop;
        this.scroller = new Scroller();
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.chipCount = this.items.length;
        this.setInitiallyProvidedValue(h2);
        this.declareWatch("itemStyle", this.itemStyleOnChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(f2) {
        if (f2.items === undefined) {
            this.__items.set([]);
        }
        if (f2.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (f2.chipSize !== undefined) {
            this.chipSize = f2.chipSize;
        }
        if (f2.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (f2.multiple === undefined) {
            this.__multiple.set(false);
        }
        if (f2.chipGroupSpace === undefined) {
            this.__chipGroupSpace.set(defaultTheme.chipGroupSpace);
        }
        if (f2.suffix !== undefined) {
            this.suffix = f2.suffix;
        }
        if (f2.onChange !== undefined) {
            this.onChange = f2.onChange;
        }
        if (f2.scroller !== undefined) {
            this.scroller = f2.scroller;
        }
        if (f2.isReachEnd !== undefined) {
            this.isReachEnd = f2.isReachEnd;
        }
        if (f2.chipCount !== undefined) {
            this.chipCount = f2.chipCount;
        }
    }
    updateStateVars(e2) {
        this.__items.reset(e2.items);
        this.__itemStyle.reset(e2.itemStyle);
        this.__selectedIndexes.reset(e2.selectedIndexes);
        this.__multiple.reset(e2.multiple);
        this.__chipGroupSpace.reset(e2.chipGroupSpace);
    }
    purgeVariableDependenciesOnElmtId(d2) {
        this.__items.purgeDependencyOnElmtId(d2);
        this.__itemStyle.purgeDependencyOnElmtId(d2);
        this.__chipSize.purgeDependencyOnElmtId(d2);
        this.__selectedIndexes.purgeDependencyOnElmtId(d2);
        this.__multiple.purgeDependencyOnElmtId(d2);
        this.__chipGroupSpace.purgeDependencyOnElmtId(d2);
        this.__isReachEnd.purgeDependencyOnElmtId(d2);
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
    set items(c2) {
        this.__items.set(c2);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(b2) {
        this.__itemStyle.set(b2);
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(a2) {
        this.__chipSize.set(a2);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(z1) {
        this.__selectedIndexes.set(z1);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(y1) {
        this.__multiple.set(y1);
    }
    get chipGroupSpace() {
        return this.__chipGroupSpace.get();
    }
    set chipGroupSpace(x1) {
        this.__chipGroupSpace.set(x1);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(w1) {
        this.__isReachEnd.set(w1);
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
        let r1 = [];
        r1 = (this.selectedIndexes ?? [0]).filter((t1, u1, v1) => {
            return (t1 >= 0 && t1 % 1 == 0 && t1 <= this.chipCount);
        });
        return r1;
    }
    isMultiple() {
        return this.multiple ?? false;
    }
    getChipGroupItemSpace() {
        return parseDimension(this.getUIContext(), this.chipGroupSpace.itemSpace, defaultTheme.chipGroupSpace.itemSpace);
    }
    getChipGroupStartSpace() {
        return parseDimension(this.getUIContext(), this.chipGroupSpace.startSpace, defaultTheme.chipGroupSpace.startSpace);
    }
    getChipGroupEndSpace() {
        return parseDimension(this.getUIContext(), this.chipGroupSpace.endSpace, defaultTheme.chipGroupSpace.endSpace);
    }
    getOnChange() {
        return this.onChange ?? noop;
    }
    isSelected(m1) {
        if (!this.isMultiple()) {
            return m1 == this.getSelectedIndexes()[0];
        }
        else {
            console.log("zjw itemIndex = " + m1);
            return this.getSelectedIndexes().some((o1, p1, q1) => {
                return (o1 == m1);
            });
        }
    }
    initialRender() {
        this.observeComponentCreation2((k1, l1) => {
            Row.create();
            Row.align(Alignment.End);
            Row.width("100%");
            Row.height(64);
        }, Row);
        this.observeComponentCreation2((i1, j1) => {
            Stack.create();
            Stack.layoutWeight(1);
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
            Stack.alignContent(Alignment.End);
        }, Stack);
        this.observeComponentCreation2((f1, g1) => {
            Scroll.create(this.scroller);
            Scroll.scrollable(ScrollDirection.Horizontal);
            Scroll.scrollBar(BarState.Off);
            Scroll.align(Alignment.Start);
            Scroll.width('100%');
            Scroll.onScroll(() => {
                this.isReachEnd = this.scroller.isAtEnd();
            });
        }, Scroll);
        this.observeComponentCreation2((d1, e1) => {
            Row.create({ space: this.getChipGroupItemSpace() });
            Row.padding({ left: this.getChipGroupStartSpace(),
                right: this.getChipGroupEndSpace() });
            Row.constraintSize({ minWidth: '100%' });
        }, Row);
        this.observeComponentCreation2((v, w) => {
            ForEach.create();
            const x = (z, a1) => {
                const b1 = z;
                Chip.bind(this)(makeBuilderParameterProxy("Chip", { prefixIcon: () => ({
                        src: b1.prefixIcon?.src ?? "",
                        size: b1.prefixIcon?.size ?? undefined,
                    }), label: () => ({
                        text: b1?.label?.text ?? " ",
                        fontColor: this.getFontColor(),
                        activatedFontColor: this.getSelectedFontColor(),
                    }), suffixIcon: () => ({
                        src: b1.suffixIcon?.src ?? "",
                        size: b1.suffixIcon?.size ?? undefined,
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
            };
            this.forEachUpdateFunction(v, this.items, x, undefined, true, false);
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
                    this.suffix.bind(this)();
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
