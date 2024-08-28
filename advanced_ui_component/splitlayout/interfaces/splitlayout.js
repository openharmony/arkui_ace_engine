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

if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const TEXT_MARGIN_TOP_4 = 4;
const TEXT_MARGIN_BOTTOM_8 = 8;
const TEXT_MARGIN_BOTTOM_24 = 24;
const TEXT_MARGIN_LEFT_48 = 48;
const TEXT_MARGIN_RIGHT_48 = 48;
export class SplitLayout extends ViewPU {
    constructor(n4, o4, p4, q4 = -1, r4 = undefined, s4) {
        super(n4, p4, q4, s4);
        if (typeof r4 === "function") {
            this.paramsGenerator_ = r4;
        }
        this.container = undefined;
        this.__sizeValue = new ObservedPropertySimplePU('', this, "sizeValue");
        this.__areaWidth = new ObservedPropertySimplePU(0, this, "areaWidth");
        this.__imageBackgroundColor = new ObservedPropertySimplePU("#19000000", this, "imageBackgroundColor");
        this.__mainImage = new ObservedPropertyObjectPU(undefined, this, "mainImage");
        this.__primaryText = new SynchedPropertySimpleOneWayPU(o4.primaryText, this, "primaryText");
        this.secondaryText = "";
        this.tertiaryText = "";
        this.setInitiallyProvidedValue(o4);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(m4) {
        if (m4.container !== undefined) {
            this.container = m4.container;
        }
        if (m4.sizeValue !== undefined) {
            this.sizeValue = m4.sizeValue;
        }
        if (m4.areaWidth !== undefined) {
            this.areaWidth = m4.areaWidth;
        }
        if (m4.imageBackgroundColor !== undefined) {
            this.imageBackgroundColor = m4.imageBackgroundColor;
        }
        if (m4.mainImage !== undefined) {
            this.mainImage = m4.mainImage;
        }
        if (m4.primaryText === undefined) {
            this.__primaryText.set("");
        }
        if (m4.secondaryText !== undefined) {
            this.secondaryText = m4.secondaryText;
        }
        if (m4.tertiaryText !== undefined) {
            this.tertiaryText = m4.tertiaryText;
        }
    }
    updateStateVars(l4) {
        this.__primaryText.reset(l4.primaryText);
    }
    purgeVariableDependenciesOnElmtId(k4) {
        this.__sizeValue.purgeDependencyOnElmtId(k4);
        this.__areaWidth.purgeDependencyOnElmtId(k4);
        this.__imageBackgroundColor.purgeDependencyOnElmtId(k4);
        this.__mainImage.purgeDependencyOnElmtId(k4);
        this.__primaryText.purgeDependencyOnElmtId(k4);
    }
    aboutToBeDeleted() {
        this.__sizeValue.aboutToBeDeleted();
        this.__areaWidth.aboutToBeDeleted();
        this.__imageBackgroundColor.aboutToBeDeleted();
        this.__mainImage.aboutToBeDeleted();
        this.__primaryText.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get sizeValue() {
        return this.__sizeValue.get();
    }
    set sizeValue(j4) {
        this.__sizeValue.set(j4);
    }
    get areaWidth() {
        return this.__areaWidth.get();
    }
    set areaWidth(i4) {
        this.__areaWidth.set(i4);
    }
    get imageBackgroundColor() {
        return this.__imageBackgroundColor.get();
    }
    set imageBackgroundColor(h4) {
        this.__imageBackgroundColor.set(h4);
    }
    get mainImage() {
        return this.__mainImage.get();
    }
    set mainImage(g4) {
        this.__mainImage.set(g4);
    }
    get primaryText() {
        return this.__primaryText.get();
    }
    set primaryText(f4) {
        this.__primaryText.set(f4);
    }
    initialRender() {
        this.observeComponentCreation2((a4, b4) => {
            Column.create();
            Column.onAreaChange((d4, e4) => {
                console.info(`Ace: on area change, oldValue is ${JSON.stringify(d4)} value is ${JSON.stringify(e4)}`);
                this.sizeValue = JSON.stringify(e4);
                this.areaWidth = parseInt(e4.width.toString(), 0);
                console.info(`pingAce: on area change, oldValue is` + this.areaWidth);
                console.info(`pingAce: on area change, oldValue is` + parseInt(e4.height.toString(), 0));
            });
        }, Column);
        this.observeComponentCreation2((c, d) => {
            If.create();
            if (this.areaWidth < 600) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((y3, z3) => {
                        GridRow.create({
                            columns: 4,
                            breakpoints: {
                                reference: BreakpointsReference.WindowSize
                            },
                            direction: GridRowDirection.Row
                        });
                    }, GridRow);
                    this.observeComponentCreation2((w3, x3) => {
                        GridCol.create({ span: { xs: 4, sm: 4, md: 4, lg: 4 } });
                    }, GridCol);
                    this.observeComponentCreation2((u3, v3) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((s3, t3) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.height('34%');
                        Stack.width('100%');
                    }, Stack);
                    this.observeComponentCreation2((q3, r3) => {
                        Image.create(this.mainImage);
                        Image.height('100%');
                        Image.width('100%');
                    }, Image);
                    this.observeComponentCreation2((o3, p3) => {
                        Scroll.create();
                        Scroll.scrollBar(BarState.On);
                        Scroll.nestedScroll({
                            scrollForward: NestedScrollMode.SELF_FIRST,
                            scrollBackward: NestedScrollMode.SELF_FIRST,
                        });
                    }, Scroll);
                    this.observeComponentCreation2((m3, n3) => {
                        Column.create();
                        Column.alignItems(HorizontalAlign.Center);
                        Column.margin({
                            left: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_max_padding_start'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_max_padding_end'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                    }, Column);
                    this.observeComponentCreation2((k3, l3) => {
                        Text.create(this.primaryText);
                        Text.fontWeight(FontWeight.Medium);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Title_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((i3, j3) => {
                        Text.create(this.secondaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Body_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ top: TEXT_MARGIN_TOP_4, bottom: TEXT_MARGIN_BOTTOM_8 });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((g3, h3) => {
                        Text.create(this.tertiaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Caption_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ bottom: TEXT_MARGIN_BOTTOM_24 });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Scroll.pop();
                    Stack.pop();
                    this.observeComponentCreation2((e3, f3) => {
                        Column.create();
                        Column.height('66%');
                        Column.width('100%');
                    }, Column);
                    this.container.bind(this)();
                    Column.pop();
                    Column.pop();
                    GridCol.pop();
                    GridRow.pop();
                });
            }
            else if (600 < this.areaWidth && this.areaWidth < 840) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((q2, r2) => {
                        GridRow.create({
                            columns: 8,
                            breakpoints: {
                                reference: BreakpointsReference.WindowSize
                            },
                            direction: GridRowDirection.Row
                        });
                    }, GridRow);
                    this.observeComponentCreation2((o2, p2) => {
                        GridCol.create({ span: { xs: 8, sm: 8, md: 8, lg: 8 } });
                    }, GridCol);
                    this.observeComponentCreation2((m2, n2) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((k2, l2) => {
                        Row.create();
                        Row.backgroundColor(this.imageBackgroundColor);
                        Row.height('34%');
                        Row.width('100%');
                    }, Row);
                    this.observeComponentCreation2((i2, j2) => {
                        Image.create(this.mainImage);
                        Image.margin({ start: LengthMetrics.vp(96), end: LengthMetrics.vp(36) });
                        Image.height('60%');
                        Image.width('20%');
                    }, Image);
                    this.observeComponentCreation2((g2, h2) => {
                        Scroll.create();
                        Scroll.scrollBar(BarState.On);
                        Scroll.nestedScroll({
                            scrollForward: NestedScrollMode.SELF_FIRST,
                            scrollBackward: NestedScrollMode.SELF_FIRST,
                        });
                    }, Scroll);
                    this.observeComponentCreation2((e2, f2) => {
                        Column.create();
                        Column.width('42%');
                        Column.alignItems(HorizontalAlign.Start);
                        Column.margin({ end: LengthMetrics.vp(96) });
                    }, Column);
                    this.observeComponentCreation2((c2, d2) => {
                        Text.create(this.primaryText);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Title_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((a2, b2) => {
                        Text.create(this.secondaryText);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Body_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ top: TEXT_MARGIN_TOP_4, bottom: TEXT_MARGIN_BOTTOM_8 });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((y1, z1) => {
                        Text.create(this.tertiaryText);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Caption_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ bottom: TEXT_MARGIN_BOTTOM_24 });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Scroll.pop();
                    Row.pop();
                    this.observeComponentCreation2((w1, x1) => {
                        Column.create();
                        Column.width('100%');
                        Column.height('66%');
                    }, Column);
                    this.container.bind(this)();
                    Column.pop();
                    Column.pop();
                    GridCol.pop();
                    GridRow.pop();
                });
            }
            else if (this.areaWidth > 840) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((i1, j1) => {
                        GridRow.create({
                            columns: 12,
                            breakpoints: {
                                reference: BreakpointsReference.WindowSize
                            },
                            direction: GridRowDirection.Row
                        });
                        GridRow.width('100%');
                    }, GridRow);
                    this.observeComponentCreation2((g1, h1) => {
                        GridCol.create({ span: { xs: 4, sm: 4, md: 4, lg: 4 } });
                        GridCol.height('100%');
                    }, GridCol);
                    this.observeComponentCreation2((e1, f1) => {
                        Flex.create({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center, direction: FlexDirection.Column });
                        Flex.width('100%');
                        Flex.height('100%');
                        Flex.backgroundColor(this.imageBackgroundColor);
                    }, Flex);
                    this.observeComponentCreation2((c1, d1) => {
                        Image.create(this.mainImage);
                        Image.height('17%');
                        Image.width('34%');
                        Image.margin({ bottom: 36 });
                    }, Image);
                    this.observeComponentCreation2((a1, b1) => {
                        Scroll.create();
                        Scroll.scrollBar(BarState.On);
                        Scroll.nestedScroll({
                            scrollForward: NestedScrollMode.SELF_FIRST,
                            scrollBackward: NestedScrollMode.SELF_FIRST,
                        });
                    }, Scroll);
                    this.observeComponentCreation2((y, z) => {
                        Column.create();
                        Column.alignItems(HorizontalAlign.Center);
                        Column.margin({
                            left: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_max_padding_start'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                            right: { "id": -1, "type": 10002, params: ['sys.float.ohos_id_max_padding_end'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" },
                        });
                    }, Column);
                    this.observeComponentCreation2((w, x) => {
                        Text.create(this.primaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Title_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ left: TEXT_MARGIN_LEFT_48, right: TEXT_MARGIN_RIGHT_48 });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((u, v) => {
                        Text.create(this.secondaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Body_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_primary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ top: TEXT_MARGIN_TOP_4, bottom: TEXT_MARGIN_BOTTOM_8,
                            left: TEXT_MARGIN_LEFT_48, right: TEXT_MARGIN_RIGHT_48 });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((s, t) => {
                        Text.create(this.tertiaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({ "id": -1, "type": 10002, params: ['sys.float.Caption_M'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.fontColor({ "id": -1, "type": 10001, params: ['sys.color.ohos_id_color_text_secondary'], "bundleName": "__harDefaultBundleName__", "moduleName": "__harDefaultModuleName__" });
                        Text.margin({ left: TEXT_MARGIN_LEFT_48, right: TEXT_MARGIN_RIGHT_48, bottom: TEXT_MARGIN_BOTTOM_24 });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Scroll.pop();
                    Flex.pop();
                    GridCol.pop();
                    this.observeComponentCreation2((q, r) => {
                        GridCol.create({ span: { xs: 8, sm: 8, md: 8, lg: 8 } });
                    }, GridCol);
                    this.container.bind(this)();
                    GridCol.pop();
                    GridRow.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(3, () => {
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

export default { SplitLayout };