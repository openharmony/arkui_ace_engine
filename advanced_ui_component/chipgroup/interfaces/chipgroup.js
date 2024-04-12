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

const noop = (l3) => {
};
const alpha = [['rgba(0, 0, 0, 1)', 0.5], ['rgba(0, 0, 0, 0)', 1]];
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
    rightPadding: 8,
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
    constructor(f3, g3, h3, i3 = -1, j3 = undefined, k3) {
        super(f3, h3, i3, k3);
        if (typeof j3 === "function") {
            this.paramsGenerator_ = j3;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(g3.items, this, "items");
        this.setInitiallyProvidedValue(g3);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(e3) {
        if (e3.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(d3) {
        this.__items.reset(d3.items);
    }
    purgeVariableDependenciesOnElmtId(c3) {
        this.__chipSize.purgeDependencyOnElmtId(c3);
        this.__items.purgeDependencyOnElmtId(c3);
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
    set chipSize(b3) {
        this.__chipSize.set(b3);
    }
    get items() {
        return this.__items.get();
    }
    set items(a3) {
        this.__items.set(a3);
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
        this.observeComponentCreation2((y2, z2) => {
            Stack.create();
            Stack.margin({ left: chipGroupSuffixTheme.marginLeft });
            Stack.borderRadius(chipGroupSuffixTheme.borderRadius);
            Stack.backgroundColor(chipGroupSuffixTheme.backgroundColor);
            Stack.constraintSize({ maxWidth: this.getBackgroundSize(), maxHeight: this.getBackgroundSize() });
            Stack.size({ width: this.getBackgroundSize(), height: this.getBackgroundSize() });
            Stack.align(Alignment.Center);
        }, Stack);
        this.observeComponentCreation2((w2, x2) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((k2, l2) => {
            ForEach.create();
            const m2 = (o2, p2) => {
                const q2 = o2;
                this.observeComponentCreation2((s2, t2) => {
                    Image.create(q2.icon.src);
                    Image.size(q2.icon.size ?? { width: this.getIconSize(), height: this.getIconSize() });
                    Image.constraintSize({ maxWidth: this.getIconSize(), maxHeight: this.getIconSize() });
                    Image.backgroundColor(chipGroupSuffixTheme.backgroundColor);
                    Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                    Image.onClick((v2) => {
                        q2.action();
                    });
                }, Image);
            };
            this.forEachUpdateFunction(k2, this.items, m2, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
        Stack.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ChipGroup extends ViewPU {
    constructor(b2, c2, d2, e2 = -1, f2 = undefined, g2) {
        super(b2, d2, e2, g2);
        if (typeof f2 === "function") {
            this.paramsGenerator_ = f2;
        }
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__items = new SynchedPropertyObjectOneWayPU(c2.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(c2.itemStyle, this, "itemStyle");
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(c2.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(c2.multiple, this, "multiple");
        this.__chipGroupSpaceSize = new SynchedPropertyObjectOneWayPU(c2.chipGroupSpaceSize, this, "chipGroupSpaceSize");
        this.suffix = undefined;
        this.scroller = new Scroller();
        this.onChange = noop;
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.setInitiallyProvidedValue(c2);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(a2) {
        if (a2.chipSize !== undefined) {
            this.chipSize = a2.chipSize;
        }
        if (a2.items === undefined) {
            this.__items.set([]);
        }
        if (a2.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (a2.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (a2.multiple === undefined) {
            this.__multiple.set(true);
        }
        if (a2.chipGroupSpaceSize === undefined) {
            this.__chipGroupSpaceSize.set(defaultTheme.chipGroupSpace);
        }
        if (a2.suffix !== undefined) {
            this.suffix = a2.suffix;
        }
        if (a2.scroller !== undefined) {
            this.scroller = a2.scroller;
        }
        if (a2.onChange !== undefined) {
            this.onChange = a2.onChange;
        }
        if (a2.isReachEnd !== undefined) {
            this.isReachEnd = a2.isReachEnd;
        }
    }
    updateStateVars(z1) {
        this.__items.reset(z1.items);
        this.__itemStyle.reset(z1.itemStyle);
        this.__selectedIndexes.reset(z1.selectedIndexes);
        this.__multiple.reset(z1.multiple);
        this.__chipGroupSpaceSize.reset(z1.chipGroupSpaceSize);
    }
    purgeVariableDependenciesOnElmtId(y1) {
        this.__chipSize.purgeDependencyOnElmtId(y1);
        this.__items.purgeDependencyOnElmtId(y1);
        this.__itemStyle.purgeDependencyOnElmtId(y1);
        this.__selectedIndexes.purgeDependencyOnElmtId(y1);
        this.__multiple.purgeDependencyOnElmtId(y1);
        this.__chipGroupSpaceSize.purgeDependencyOnElmtId(y1);
        this.__isReachEnd.purgeDependencyOnElmtId(y1);
    }
    aboutToBeDeleted() {
        this.__chipSize.aboutToBeDeleted();
        this.__items.aboutToBeDeleted();
        this.__itemStyle.aboutToBeDeleted();
        this.__selectedIndexes.aboutToBeDeleted();
        this.__multiple.aboutToBeDeleted();
        this.__chipGroupSpaceSize.aboutToBeDeleted();
        this.__isReachEnd.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get chipSize() {
        return this.__chipSize.get();
    }
    set chipSize(x1) {
        this.__chipSize.set(x1);
    }
    get items() {
        return this.__items.get();
    }
    set items(w1) {
        this.__items.set(w1);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(v1) {
        this.__itemStyle.set(v1);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(u1) {
        this.__selectedIndexes.set(u1);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(t1) {
        this.__multiple.set(t1);
    }
    get chipGroupSpaceSize() {
        return this.__chipGroupSpaceSize.get();
    }
    set chipGroupSpaceSize(s1) {
        this.__chipGroupSpaceSize.set(s1);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(r1) {
        this.__isReachEnd.set(r1);
    }
    init() {
        this.chipSize = this.itemStyle.size;
        return true;
    }
    getChipSize() {
        return this.itemStyle.size ?? defaultTheme.itemStyle.size;
    }
    getItemStyle() {
        return this.itemStyle ?? defaultTheme.itemStyle;
    }
    getSelectedIndexes() {
        return this.selectedIndexes ?? [0];
    }
    getMultiple() {
        return this.multiple ?? true;
    }
    getChipGroupSpaceSize() {
        return this.chipGroupSpaceSize ?? defaultTheme.chipGroupSpace;
    }
    getOnChange() {
        return this.onChange ?? noop;
    }
    isSelected(m1) {
        if (!this.getMultiple()) {
            return m1 == this.getSelectedIndexes()[0];
        }
        else {
            return this.selectedIndexes.some((o1, p1, q1) => {
                return (o1 == m1);
            });
        }
    }
    initialRender() {
        this.observeComponentCreation2((k1, l1) => {
            Row.create();
            Row.align(Alignment.End);
            Row.width("100%");
            Row.padding({ left: defaultTheme.leftPadding, right: this.suffix == null ? 0 : defaultTheme.rightPadding });
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
            Row.create({ space: this.getChipGroupSpaceSize().itemSpace });
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
                    }), label: () => ({
                        text: b1.label.text,
                        fontColor: this.getItemStyle().fontColor ?? defaultTheme.itemStyle.fontColor,
                        activatedFontColor: this.getItemStyle().selectedFontColor ?? defaultTheme.itemStyle.selectedFontColor,
                    }), suffixIcon: () => ({
                        src: b1.suffixIcon?.src ?? "",
                    }), allowClose: () => b1.allowClose, enabled: () => true, activated: () => this.isSelected(a1), backgroundColor: () => this.getItemStyle().backgroundColor ?? defaultTheme.itemStyle.backgroundColor, size: () => this.getChipSize(), activatedBackgroundColor: () => this.getItemStyle()
                        .selectedBackgroundColor ?? defaultTheme.itemStyle.selectedBackgroundColor, onClicked: () => () => {
                        if (this.isSelected(a1)) {
                            this.selectedIndexes.splice(this.selectedIndexes.indexOf(a1), 1);
                            if (this.getMultiple() == false) {
                                this.selectedIndexes = [];
                            }
                        }
                        else {
                            this.selectedIndexes.push(a1);
                            if (!this.getMultiple()) {
                                this.selectedIndexes = [];
                                this.selectedIndexes.push(a1);
                            }
                        }
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
            if (this.init()) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((t, u) => {
                        Stack.create();
                        Stack.width(chipGroupSuffixTheme.normalbackgroundSize);
                        Stack.height(this.chipSize === ChipSize.SMALL ? chipGroupSuffixTheme.smallBackgroundSize : chipGroupSuffixTheme.normalbackgroundSize);
                        Stack.linearGradient({ angle: 90, colors: alpha });
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
