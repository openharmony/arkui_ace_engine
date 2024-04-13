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

const noop = (w7) => {
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
    constructor(q7, r7, s7, t7 = -1, u7 = undefined, v7) {
        super(q7, s7, t7, v7);
        if (typeof u7 === "function") {
            this.paramsGenerator_ = u7;
        }
        this.__chipSize = this.initializeConsume("chipSize", "chipSize");
        this.__items = new SynchedPropertyObjectOneWayPU(r7.items, this, "items");
        this.setInitiallyProvidedValue(r7);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(p7) {
        if (p7.items === undefined) {
            this.__items.set([]);
        }
    }
    updateStateVars(o7) {
        this.__items.reset(o7.items);
    }
    purgeVariableDependenciesOnElmtId(n7) {
        this.__chipSize.purgeDependencyOnElmtId(n7);
        this.__items.purgeDependencyOnElmtId(n7);
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
    set chipSize(m7) {
        this.__chipSize.set(m7);
    }
    get items() {
        return this.__items.get();
    }
    set items(l7) {
        this.__items.set(l7);
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
        this.observeComponentCreation2((j7, k7) => {
            Row.create();
        }, Row);
        this.observeComponentCreation2((u6, v6) => {
            ForEach.create();
            const w6 = (y6, z6) => {
                const a7 = y6;
                this.observeComponentCreation2((f7, g7) => {
                    Button.createWithChild();
                    Button.constraintSize({ maxWidth: this.getBackgroundSize(), maxHeight: this.getBackgroundSize() });
                    Button.size({ width: this.getBackgroundSize(), height: this.getBackgroundSize() });
                    Button.backgroundColor(chipGroupSuffixTheme.backgroundColor);
                    Button.borderRadius(chipGroupSuffixTheme.borderRadius);
                    Button.margin({ left: chipGroupSuffixTheme.marginLeft });
                    Button.onClick((i7) => {
                        a7.action();
                    });
                    Button.borderRadius(chipGroupSuffixTheme.borderRadius);
                }, Button);
                this.observeComponentCreation2((d7, e7) => {
                    Image.create(a7.icon.src);
                    Image.fillColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                    Image.constraintSize({ maxWidth: this.getIconSize(), maxHeight: this.getIconSize() });
                    Image.size({ width: this.getBackgroundSize(), height: this.getBackgroundSize() });
                }, Image);
                Button.pop();
            };
            this.forEachUpdateFunction(u6, this.items, w6, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
export class ChipGroup extends ViewPU {
    constructor(m6, n6, o6, p6 = -1, q6 = undefined, r6) {
        super(m6, o6, p6, r6);
        if (typeof q6 === "function") {
            this.paramsGenerator_ = q6;
        }
        this.__chipSize = new ObservedPropertyObjectPU(defaultTheme.itemStyle.size, this, "chipSize");
        this.addProvidedVar("chipSize", this.__chipSize, false);
        this.__items = new SynchedPropertyObjectOneWayPU(n6.items, this, "items");
        this.__itemStyle = new SynchedPropertyObjectOneWayPU(n6.itemStyle, this, "itemStyle");
        this.__selectedIndexes = new SynchedPropertyObjectOneWayPU(n6.selectedIndexes, this, "selectedIndexes");
        this.__multiple = new SynchedPropertySimpleOneWayPU(n6.multiple, this, "multiple");
        this.__chipGroupSpace = new SynchedPropertyObjectOneWayPU(n6.chipGroupSpace, this, "chipGroupSpace");
        this.suffix = undefined;
        this.scroller = new Scroller();
        this.onChange = noop;
        this.__isReachEnd = new ObservedPropertySimplePU(this.scroller.isAtEnd(), this, "isReachEnd");
        this.setInitiallyProvidedValue(n6);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(l6) {
        if (l6.chipSize !== undefined) {
            this.chipSize = l6.chipSize;
        }
        if (l6.items === undefined) {
            this.__items.set([]);
        }
        if (l6.itemStyle === undefined) {
            this.__itemStyle.set(defaultTheme.itemStyle);
        }
        if (l6.selectedIndexes === undefined) {
            this.__selectedIndexes.set([0]);
        }
        if (l6.multiple === undefined) {
            this.__multiple.set(false);
        }
        if (l6.chipGroupSpace === undefined) {
            this.__chipGroupSpace.set(defaultTheme.chipGroupSpace);
        }
        if (l6.suffix !== undefined) {
            this.suffix = l6.suffix;
        }
        if (l6.scroller !== undefined) {
            this.scroller = l6.scroller;
        }
        if (l6.onChange !== undefined) {
            this.onChange = l6.onChange;
        }
        if (l6.isReachEnd !== undefined) {
            this.isReachEnd = l6.isReachEnd;
        }
    }
    updateStateVars(k6) {
        this.__items.reset(k6.items);
        this.__itemStyle.reset(k6.itemStyle);
        this.__selectedIndexes.reset(k6.selectedIndexes);
        this.__multiple.reset(k6.multiple);
        this.__chipGroupSpace.reset(k6.chipGroupSpace);
    }
    purgeVariableDependenciesOnElmtId(j6) {
        this.__chipSize.purgeDependencyOnElmtId(j6);
        this.__items.purgeDependencyOnElmtId(j6);
        this.__itemStyle.purgeDependencyOnElmtId(j6);
        this.__selectedIndexes.purgeDependencyOnElmtId(j6);
        this.__multiple.purgeDependencyOnElmtId(j6);
        this.__chipGroupSpace.purgeDependencyOnElmtId(j6);
        this.__isReachEnd.purgeDependencyOnElmtId(j6);
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
    set chipSize(i6) {
        this.__chipSize.set(i6);
    }
    get items() {
        return this.__items.get();
    }
    set items(h6) {
        this.__items.set(h6);
    }
    get itemStyle() {
        return this.__itemStyle.get();
    }
    set itemStyle(g6) {
        this.__itemStyle.set(g6);
    }
    get selectedIndexes() {
        return this.__selectedIndexes.get();
    }
    set selectedIndexes(f6) {
        this.__selectedIndexes.set(f6);
    }
    get multiple() {
        return this.__multiple.get();
    }
    set multiple(e6) {
        this.__multiple.set(e6);
    }
    get chipGroupSpace() {
        return this.__chipGroupSpace.get();
    }
    set chipGroupSpace(d6) {
        this.__chipGroupSpace.set(d6);
    }
    get isReachEnd() {
        return this.__isReachEnd.get();
    }
    set isReachEnd(c6) {
        this.__isReachEnd.set(c6);
    }
    getChipSize() {
        this.chipSize = this.itemStyle.size;
        return this.itemStyle.size ?? defaultTheme.itemStyle.size;
    }
    getItemStyle() {
        return this.itemStyle ?? defaultTheme.itemStyle;
    }
    getSelectedIndexes() {
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
    isSelected(x5) {
        if (!this.isMultiple()) {
            return x5 == this.getSelectedIndexes()[0];
        }
        else {
            return this.selectedIndexes.some((z5, a6, b6) => {
                return (z5 == x5);
            });
        }
    }
    initialRender() {
        this.observeComponentCreation2((v5, w5) => {
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
        this.observeComponentCreation2((t5, u5) => {
            Stack.create();
            Stack.layoutWeight(1);
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
            Stack.alignContent(Alignment.End);
        }, Stack);
        this.observeComponentCreation2((q5, r5) => {
            Scroll.create(this.scroller);
            Scroll.scrollable(ScrollDirection.Horizontal);
            Scroll.scrollBar(BarState.Off);
            Scroll.align(Alignment.Start);
            Scroll.width('100%');
            Scroll.onScroll(() => {
                this.isReachEnd = this.scroller.isAtEnd();
            });
        }, Scroll);
        this.observeComponentCreation2((o5, p5) => {
            Row.create({ space: this.getChipGroupSpaceSize().itemSpace ?? defaultTheme.chipGroupSpace.itemSpace });
            Row.padding({ left: this.getChipGroupSpaceSize().startSpace ?? defaultTheme.chipGroupSpace.startSpace,
                right: this.getChipGroupSpaceSize().endSpace ?? defaultTheme.chipGroupSpace.endSpace });
            Row.constraintSize({ minWidth: '100%' });
        }, Row);
        this.observeComponentCreation2((g5, h5) => {
            ForEach.create();
            const i5 = (k5, l5) => {
                const m5 = k5;
                Chip.bind(this)(makeBuilderParameterProxy("Chip", { prefixIcon: () => ({
                        src: m5.prefixIcon?.src ?? "",
                    }), label: () => ({
                        text: m5.label.text,
                        fontColor: this.getItemStyle().fontColor ?? defaultTheme.itemStyle.fontColor,
                        activatedFontColor: this.getItemStyle().selectedFontColor ?? defaultTheme.itemStyle.selectedFontColor,
                    }), suffixIcon: () => ({
                        src: m5.suffixIcon?.src ?? "",
                    }), allowClose: () => m5.allowClose ?? false, enabled: () => true, activated: () => this.isSelected(l5), backgroundColor: () => this.getItemStyle().backgroundColor ?? defaultTheme.itemStyle.backgroundColor, size: () => this.getChipSize(), activatedBackgroundColor: () => this.getItemStyle()
                        .selectedBackgroundColor ?? defaultTheme.itemStyle.selectedBackgroundColor, onClicked: () => () => {
                        if (this.isSelected(l5)) {
                            this.selectedIndexes.splice(this.selectedIndexes.indexOf(l5), 1);
                        }
                        else {
                            if (!this.isMultiple()) {
                                this.selectedIndexes = [];
                            }
                            this.selectedIndexes.push(l5);
                        }
                        this.getOnChange()(this.selectedIndexes);
                    } }));
            };
            this.forEachUpdateFunction(g5, this.items, i5, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Row.pop();
        Scroll.pop();
        this.observeComponentCreation2((z4, a5) => {
            If.create();
            if (this.suffix) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((e5, f5) => {
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
        this.observeComponentCreation2((s4, t4) => {
            If.create();
            if (this.suffix) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((x4, y4) => {
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
