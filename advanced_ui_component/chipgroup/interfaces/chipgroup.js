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

const noop = (q3) => {
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
    chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 0 },
    leftPadding: 0,
    rightPadding: 16,
};
const chipGroupSuffixTheme = {
    backgroundColor: { "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_button_normal'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    borderRadius: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_corner_radius_tips_instant_tip'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
    smallIconSize: 16,
    normalIconSize: 24,
    smallBackgroundSize: 28,
    normalbackgroundSize: 36,
    marginLeft: 8,
};
export class IconGroupSuffix extends ViewPU {
    constructor(k3, l3, m3, n3 = -1, o3 = undefined, p3) {
        super(k3, m3, n3, p3);
        if (typeof o3 === "function") {
            this.paramsGenerator_ = o3;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(l3.items, this, "items");
        this.setInitiallyProvidedValue(l3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(j3) {
        if (j3.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(i3) {
        this.__items.reset(i3.items);
    }
    purgeVariableDependenciesOnElmtId(h3) {
        this.__chipSize.purgeDependencyOnElmtId(h3);
        this.__items.purgeDependencyOnElmtId(h3);
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
    set chipSize(g3) {
        this.__chipSize.set(g3);
    }
    get items() {
        return this.__items.get();
    }
    set items(f3) {
        this.__items.set(f3);
    }
    getIconSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return chipGroupSuffixTheme.smallIconSize;
        }
        else {
            return chipGroupSuffixTheme.normalIconSize;
        }
    }
    getBackgroundSize() {
        if (this.chipSize === ChipSize.SMALL) {
            return chipGroupSuffixTheme.smallBackgroundSize;
        }
        else {
            return chipGroupSuffixTheme.normalbackgroundSize;
        }
    }
    initialRender() {
        this.observeComponentCreation2((d3, e3) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((o2, p2) => {
            ForEach.create();
            const q2 = (s2, t2) => {
                const u2 = s2;
                this.observeComponentCreation2((z2, a3) => {
                    Button.createWithChild();
                    Button.constraintSize({ maxWidth: this.getBackgroundSize(), maxHeight: this.getBackgroundSize() });
                    Button.size({ width: this.getBackgroundSize(), height: this.getBackgroundSize() });
                    Button.backgroundColor(chipGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(chipGroupSuffixTheme.borderRadius);
                    Button.margin({ left: chipGroupSuffixTheme.marginLeft });
                    Button.onClick((c3) => {
                        u2.action();
                    });
                    Button.borderRadius(chipGroupSuffixTheme.borderRadius);
                }, Button);
                this.observeComponentCreation2((x2, y2) => {
                    Image.create(u2.icon.src);
                    Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                    Image.constraintSize({ maxWidth: this.getIconSize(), maxHeight: this.getIconSize() });
                    Image.size({ width: this.getBackgroundSize(), height: this.getBackgroundSize() });
                }, Image);
                Button.pop();
            };
            this.forEachUpdateFunction(o2, this.items, q2, undefined, true, false);
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
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__items = new SynchedPropertyObjectOneWayPU(h2.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(h2.itemStyle, this, "itemStyle");
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(h2.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(h2.multiple, this, "multiple");
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(h2.chipGroupSpace, this, "chipGroupSpace");
        this.suffix = undefined;
        this.scroller = new Scroller();
        this.onChange = noop;
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.setInitiallyProvidedValue(h2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(f2) {
        if (f2.chipSize !== undefined) {
            this.chipSize = f2.chipSize;
        }
        if (f2.items === undefined) {
            this.__items.set([]);
        }
        if (f2.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
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
        if (f2.scroller !== undefined) {
            this.scroller = f2.scroller;
        }
        if (f2.onChange !== undefined) {
            this.onChange = f2.onChange;
        }
        if (f2.isReachEnd !== undefined) {
            this.isReachEnd = f2.isReachEnd;
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
        this.__chipSize.purgeDependencyOnElmtId(d2);
        this.__items.purgeDependencyOnElmtId(d2);
        this.__itemStyle.purgeDependencyOnElmtId(d2);
        this.__selectedIndexes.purgeDependencyOnElmtId(d2);
        this.__multiple.purgeDependencyOnElmtId(d2);
        this.__chipGroupSpace.purgeDependencyOnElmtId(d2);
        this.__isReachEnd.purgeDependencyOnElmtId(d2);
    }
    aboutToBeDeleted() {
        this.__chipSize.aboutToBeDeleted();
        this.__items.aboutToBeDeleted();
        this.__itemStyle.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__multiple.aboutToBeDeleted();
        this.__chipGroupSpace.aboutToBeDeleted();
        this.__isReachEnd.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(c2) {
        this.__chipSize.set(c2);
    }
    get items() {
        return this.__items.get();
    }
    set items(b2) {
        this.__items.set(b2);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(a2) {
        this.__itemStyle.set(a2);
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
    getChipSize() {
        this.chipSize = this.itemStyle.size;
        return this.itemStyle.size ?? defaultTheme.itemStyle.size;
    }
    getItemStyle() {
        return this.itemStyle ?? defaultTheme.itemStyle;
    }
    getSelectedIndexes() {
        this.selectedIndexes.forEach((t1, u1, v1) => {
            if (t1 >= 0) {
            }
            else {
                this.selectedIndexes.splice(u1, 1);
            }
        });
        return this.selectedIndexes ?? [0];
    }
    isMultiple() {
        return this.multiple ?? true;
    }
    getChipGroupSpaceSize() {
        return this.chipGroupSpace ?? defaultTheme.chipGroupSpace;
    }
    getOnChange() {
        return this.onChange ?? noop;
    }
    isSelected(m1) {
        let n1 = this.getSelectedIndexes()[0];
        if (!this.isMultiple()) {
            return m1 == n1;
        }
        else {
            return this.selectedIndexes.some((p1, q1, r1) => {
                return (p1 == m1);
            });
        }
    }
    initialRender() {
        this.observeComponentCreation2((k1, l1) => {
            Row.create();
            Row.align(Alignment.End);
            Row.width("100%");
            Row.padding({
                left: defaultTheme.leftPadding,
                right: this.suffix == null ? (this.getChipGroupSpaceSize()
                    .endSpace ?? defaultTheme.chipGroupSpace.endSpace) : defaultTheme.rightPadding
            });
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
            Row.create({ space: this.getChipGroupSpaceSize().itemSpace ?? defaultTheme.chipGroupSpace.itemSpace });
            Row.padding({ left: this.getChipGroupSpaceSize().startSpace ?? defaultTheme.chipGroupSpace.startSpace,
                right: this.getChipGroupSpaceSize().endSpace ?? defaultTheme.chipGroupSpace.endSpace });
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
                        fontColor: this.getItemStyle().fontColor ?? defaultTheme.itemStyle.fontColor,
                        activatedFontColor: this.getItemStyle().selectedFontColor ?? defaultTheme.itemStyle.selectedFontColor,
                    }), suffixIcon: () => ({
                        src: b1.suffixIcon?.src ?? "",
                        size: b1.suffixIcon?.size ?? undefined,
                    }), allowClose: () => b1.allowClose ?? false, enabled: () => true, activated: () => this.isSelected(a1), backgroundColor: () => this.getItemStyle().backgroundColor ?? defaultTheme.itemStyle.backgroundColor, size: () => this.getChipSize(), activatedBackgroundColor: () => this.getItemStyle()
                        .selectedBackgroundColor ?? defaultTheme.itemStyle.selectedBackgroundColor, onClicked: () => () => {
                        if (this.isSelected(a1)) {
                            this.selectedIndexes.splice(this.selectedIndexes.indexOf(a1), 1);
                        }
                        else {
                            if (!this.isMultiple()) {
                                this.selectedIndexes = [];
                            }
                            this.selectedIndexes.push(a1);
                        }
                        this.selectedIndexes.sort();
                        this.getOnChange()(this.selectedIndexes);
                    } }));
            };
            this.forEachUpdateFunction(v, this.items, x, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
        Scroll.pop();
        this.observeComponentCreation2((o, p) => {
            If.create();
            if (this.suffix) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t, u) => {
                        Stack.create();
                        Stack.width(chipGroupSuffixTheme.normalbackgroundSize);
                        Stack.height(this.chipSize === ChipSize.SMALL ? chipGroupSuffixTheme.smallBackgroundSize : chipGroupSuffixTheme.normalbackgroundSize);
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
