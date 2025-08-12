/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
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

if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;

const o19 = 4;
const p19 = 8;
const q19 = 24;
const r19 = 48;
const s19 = 48;

export class SplitLayout extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.container = undefined;
        this.__sizeValue = new ObservedPropertySimplePU('', this, 'sizeValue');
        this.__areaWidth = new ObservedPropertySimplePU(0, this, 'areaWidth');
        this.__imageBackgroundColor = new ObservedPropertySimplePU('#19000000', this, 'imageBackgroundColor');
        this.__mainImage = new ObservedPropertyObjectPU(undefined, this, 'mainImage');
        this.__primaryText = new SynchedPropertySimpleOneWayPU(params.primaryText, this, 'primaryText');
        this.secondaryText = '';
        this.tertiaryText = '';
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.container !== undefined) {
            this.container = params.container;
        }
        if (params.sizeValue !== undefined) {
            this.sizeValue = params.sizeValue;
        }
        if (params.areaWidth !== undefined) {
            this.areaWidth = params.areaWidth;
        }
        if (params.imageBackgroundColor !== undefined) {
            this.imageBackgroundColor = params.imageBackgroundColor;
        }
        if (params.mainImage !== undefined) {
            this.mainImage = params.mainImage;
        }
        if (params.primaryText === undefined) {
            this.__primaryText.set('');
        }
        if (params.secondaryText !== undefined) {
            this.secondaryText = params.secondaryText;
        }
        if (params.tertiaryText !== undefined) {
            this.tertiaryText = params.tertiaryText;
        }
    }

    updateStateVars(params) {
        this.__primaryText.reset(params.primaryText);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__sizeValue.purgeDependencyOnElmtId(rmElmtId);
        this.__areaWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__imageBackgroundColor.purgeDependencyOnElmtId(rmElmtId);
        this.__mainImage.purgeDependencyOnElmtId(rmElmtId);
        this.__primaryText.purgeDependencyOnElmtId(rmElmtId);
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

    set sizeValue(newValue) {
        this.__sizeValue.set(newValue);
    }

    get areaWidth() {
        return this.__areaWidth.get();
    }

    set areaWidth(newValue) {
        this.__areaWidth.set(newValue);
    }

    get imageBackgroundColor() {
        return this.__imageBackgroundColor.get();
    }

    set imageBackgroundColor(newValue) {
        this.__imageBackgroundColor.set(newValue);
    }

    get mainImage() {
        return this.__mainImage.get();
    }

    set mainImage(newValue) {
        this.__mainImage.set(newValue);
    }

    get primaryText() {
        return this.__primaryText.get();
    }

    set primaryText(newValue) {
        this.__primaryText.set(newValue);
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.onAreaChange((oldValue, newValue) => {
                console.info(`Ace: on area change, oldValue is ${JSON.stringify(oldValue)} value is ${JSON.stringify(newValue)}`);
                this.sizeValue = JSON.stringify(newValue);
                this.areaWidth = parseInt(newValue.width.toString(), 0);
                console.info(`pingAce: on area change, oldValue is` + this.areaWidth);
                console.info(`pingAce: on area change, oldValue is` + parseInt(newValue.height.toString(), 0));
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.areaWidth <= 600) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        GridRow.create({
                            columns: 4,
                            breakpoints: {
                                reference: BreakpointsReference.WindowSize
                            },
                            direction: GridRowDirection.Row
                        });
                    }, GridRow);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        GridCol.create({
                            span: {
                                xs: 4,
                                sm: 4,
                                md: 4,
                                lg: 4
                            }
                        });
                    }, GridCol);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create({ alignContent: Alignment.Bottom });
                        Stack.height('34%');
                        Stack.width('100%');
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.mainImage);
                        Image.height('100%');
                        Image.width('100%');
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Scroll.create();
                        Scroll.scrollBar(BarState.On);
                        Scroll.nestedScroll({
                            scrollForward: NestedScrollMode.SELF_FIRST,
                            scrollBackward: NestedScrollMode.SELF_FIRST,
                        });
                    }, Scroll);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.alignItems(HorizontalAlign.Center);
                        Column.margin({
                            left: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_max_padding_start'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_max_padding_end'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                        });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.primaryText);
                        Text.fontWeight(FontWeight.Medium);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Title_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.secondaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Body_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.margin({ top: o19, bottom: p19 });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.tertiaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Caption_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_secondary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.margin({ bottom: q19 });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Scroll.pop();
                    Stack.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            } else if (600 < this.areaWidth && this.areaWidth <= 840) {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        GridRow.create({
                            columns: 8,
                            breakpoints: {
                                reference: BreakpointsReference.WindowSize
                            },
                            direction: GridRowDirection.Row
                        });
                    }, GridRow);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        GridCol.create({
                            span: {
                                xs: 8,
                                sm: 8,
                                md: 8,
                                lg: 8
                            }
                        });
                    }, GridCol);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Row.create();
                        Row.backgroundColor(this.imageBackgroundColor);
                        Row.height('34%');
                        Row.width('100%');
                    }, Row);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.mainImage);
                        Image.margin({ start: LengthMetrics.vp(96), end: LengthMetrics.vp(36) });
                        Image.height('60%');
                        Image.width('20%');
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Scroll.create();
                        Scroll.scrollBar(BarState.On);
                        Scroll.nestedScroll({
                            scrollForward: NestedScrollMode.SELF_FIRST,
                            scrollBackward: NestedScrollMode.SELF_FIRST,
                        });
                    }, Scroll);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.width('42%');
                        Column.alignItems(HorizontalAlign.Start);
                        Column.margin({ end: LengthMetrics.vp(96) });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.primaryText);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Title_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.secondaryText);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Body_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.margin({ top: o19, bottom: p19 });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.tertiaryText);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Caption_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_secondary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.margin({ bottom: q19 });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Scroll.pop();
                    Row.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
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
            } else if (this.areaWidth > 840) {
                this.ifElseBranchUpdateFunction(2, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        GridRow.create({
                            columns: 12,
                            breakpoints: {
                                reference: BreakpointsReference.WindowSize
                            },
                            direction: GridRowDirection.Row
                        });
                        GridRow.width('100%');
                    }, GridRow);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        GridCol.create({
                            span: {
                                xs: 4,
                                sm: 4,
                                md: 4,
                                lg: 4
                            }
                        });
                        GridCol.height('100%');
                    }, GridCol);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Flex.create({
                            justifyContent: FlexAlign.Center,
                            alignItems: ItemAlign.Center,
                            direction: FlexDirection.Column
                        });
                        Flex.width('100%');
                        Flex.height('100%');
                        Flex.backgroundColor(this.imageBackgroundColor);
                    }, Flex);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create(this.mainImage);
                        Image.height('17%');
                        Image.width('34%');
                        Image.margin({ bottom: 36 });
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Scroll.create();
                        Scroll.scrollBar(BarState.On);
                        Scroll.nestedScroll({
                            scrollForward: NestedScrollMode.SELF_FIRST,
                            scrollBackward: NestedScrollMode.SELF_FIRST,
                        });
                    }, Scroll);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Column.alignItems(HorizontalAlign.Center);
                        Column.margin({
                            left: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_max_padding_start'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            right: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_max_padding_end'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                        });
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.primaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontWeight(FontWeight.Medium);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Title_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.margin({ left: r19, right: s19 });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.secondaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Body_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.margin({
                            top: o19,
                            bottom: p19,
                            left: r19,
                            right: s19
                        });
                    }, Text);
                    Text.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.tertiaryText);
                        Text.textAlign(TextAlign.Center);
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.Caption_M'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.fontColor({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_secondary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.margin({ left: r19, right: s19, bottom: q19 });
                    }, Text);
                    Text.pop();
                    Column.pop();
                    Scroll.pop();
                    Flex.pop();
                    GridCol.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        GridCol.create({
                            span: {
                                xs: 8,
                                sm: 8,
                                md: 8,
                                lg: 8
                            }
                        });
                    }, GridCol);
                    this.container.bind(this)();
                    GridCol.pop();
                    GridRow.pop();
                });
            } else {
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