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

let __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    let c = arguments.length, r = c < 3 ? target : desc === null ?
        desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === 'object' && typeof Reflect.decorate === 'function') {
        r = Reflect.decorate(decorators, target, key, desc);
    } else {
        for (let i = decorators.length - 1; i >= 0; i--) {
            if (d = decorators[i]) {
                r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
            }
        }
    }
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
if (!('finalizeConstruction' in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, 'finalizeConstruction', () => {
    });
}
if (PUV2ViewBase.contextStack === undefined) {
    Reflect.set(PUV2ViewBase, 'contextStack', []);
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const curves = requireNativeModule('ohos.curves');
const measure = requireNapi('measure');
const hilog = requireNapi('ohos.hilog');
const TEXT_HOT_AREA_WIDTH = 8;
const LIST_ROW_HEIGHT = 40;
const ARROW_IMG_SIZE = 24;
const MULTI_LINE_PADDING = 24;
const BAR_ANIMATION_DURATION = 150;
const ARROW_ANIMATION_DURATION = 200;
const ANIMATION_DURATION_250 = 250;
const ANIMATION_DURATION_100 = 100;
const FILTER_TOP_PADDING = 8;
const FILTER_BAR_MARGIN = 8;
const SEPARATOR_HEIGHT = 16;
const SEPARATOR_WIDTH = 1;
const FLOAT_OPACITY = 0.95;
const FILTER_FONT_SIZE = 12;
const FOCUS_BORDER_WIDTH = 2;
const ARROW_SHOW_DELAY = 300;
const PERCENT_100 = '100%';
const SHARP_CUBIC_BEZIER = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const INTER_POLATING_SPRING = curves.interpolatingSpring(0, 1, 328, 34);
const FRICTION_CUBIC_BEZIER = curves.cubicBezierCurve(0.2, 0, 0.2, 1);
const TRANS_COLOR = '#00FFFFFF';
const GRADIENT_WIDTH = 16;
const MAX_FONT_SCALE = 2;
const ERROR_CODE = 0x3900;
export let FilterType;
(function (FilterType) {
    FilterType[FilterType.MULTI_LINE_FILTER = 0] = 'MULTI_LINE_FILTER';
    FilterType[FilterType.LIST_FILTER = 1] = 'LIST_FILTER';
})(FilterType || (FilterType = {}));
let FontWeightArray = class FontWeightArray extends Array {
};
FontWeightArray = __decorate([
    Observed
], FontWeightArray);
let ResourceArray = class ResourceArray extends Array {
};
ResourceArray = __decorate([
    Observed
], ResourceArray);
let BooleanArray = class BooleanArray extends Array {
};
BooleanArray = __decorate([
    Observed
], BooleanArray);
let ObservedBoolean = class ObservedBoolean {
    constructor(value) {
        this.value = value;
    }
};
ObservedBoolean = __decorate([
    Observed
], ObservedBoolean);

export { ObservedBoolean };
let ObservedNumber = class ObservedNumber {
    constructor(value) {
        this.value = value;
    }
};
ObservedNumber = __decorate([
    Observed
], ObservedNumber);

class GradientMask extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.x0 = 0;
        this.y0 = 0;
        this.x1 = 0;
        this.y1 = 0;
        this.settings = new RenderingContextSettings(true);
        this.context2D = new CanvasRenderingContext2D(this.settings);
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.x0 !== undefined) {
            this.x0 = params.x0;
        }
        if (params.y0 !== undefined) {
            this.y0 = params.y0;
        }
        if (params.x1 !== undefined) {
            this.x1 = params.x1;
        }
        if (params.y1 !== undefined) {
            this.y1 = params.y1;
        }
        if (params.settings !== undefined) {
            this.settings = params.settings;
        }
        if (params.context2D !== undefined) {
            this.context2D = params.context2D;
        }
    }

    updateStateVars(params) {
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
    }

    aboutToBeDeleted() {
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.blendMode(BlendMode.DST_OUT);
            Column.width(GRADIENT_WIDTH);
            Column.height(LIST_ROW_HEIGHT);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Canvas.create(this.context2D);
            Canvas.width(GRADIENT_WIDTH);
            Canvas.height(LIST_ROW_HEIGHT);
            Canvas.onReady(() => {
                let grad = this.context2D.createLinearGradient(this.x0, this.y0, this.x1, this.y1);
                grad.addColorStop(0.0, '#ffffffff');
                grad.addColorStop(1, '#00ffffff');
                this.context2D.fillStyle = grad;
                this.context2D.fillRect(0, 0, GRADIENT_WIDTH, LIST_ROW_HEIGHT);
            });
        }, Canvas);
        Canvas.pop();
        Column.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

class ListFilterRow extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__colorRow = new SynchedPropertyNesedObjectPU(params.colorRow, this, 'colorRow');
        this.__fontWeightRow = new SynchedPropertyNesedObjectPU(params.fontWeightRow, this, 'fontWeightRow');
        this.__backgroundColorRow =
            new SynchedPropertyNesedObjectPU(params.backgroundColorRow, this, 'backgroundColorRow');
        this.__isBackgroundHoverRow =
            new SynchedPropertyNesedObjectPU(params.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
        this.filterRow = { name: '', options: [] };
        this.onItemClick = () => {
        };
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__colorRow.set(params.colorRow);
        this.__fontWeightRow.set(params.fontWeightRow);
        this.__backgroundColorRow.set(params.backgroundColorRow);
        this.__isBackgroundHoverRow.set(params.isBackgroundHoverRow);
        if (params.filterRow !== undefined) {
            this.filterRow = params.filterRow;
        }
        if (params.onItemClick !== undefined) {
            this.onItemClick = params.onItemClick;
        }
        if (params.rowIndex !== undefined) {
            this.rowIndex = params.rowIndex;
        }
        if (params.maxAppFontScale !== undefined) {
            this.maxAppFontScale = params.maxAppFontScale;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
    }

    updateStateVars(params) {
        this.__colorRow.set(params.colorRow);
        this.__fontWeightRow.set(params.fontWeightRow);
        this.__backgroundColorRow.set(params.backgroundColorRow);
        this.__isBackgroundHoverRow.set(params.isBackgroundHoverRow);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__colorRow.purgeDependencyOnElmtId(rmElmtId);
        this.__fontWeightRow.purgeDependencyOnElmtId(rmElmtId);
        this.__backgroundColorRow.purgeDependencyOnElmtId(rmElmtId);
        this.__isBackgroundHoverRow.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__colorRow.aboutToBeDeleted();
        this.__fontWeightRow.aboutToBeDeleted();
        this.__backgroundColorRow.aboutToBeDeleted();
        this.__isBackgroundHoverRow.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get colorRow() {
        return this.__colorRow.get();
    }

    get fontWeightRow() {
        return this.__fontWeightRow.get();
    }

    get backgroundColorRow() {
        return this.__backgroundColorRow.get();
    }

    get isBackgroundHoverRow() {
        return this.__isBackgroundHoverRow.get();
    }

    aboutToAppear() {
        try {
            let uiContent = this.getUIContext();
            this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
            this.maxAppFontScale = uiContent.getMaxFontScale();
        } catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause,
             code: ${code}, message: ${message}`);
        }
    }

    updateFontScale() {
        let uiContent = this.getUIContext();
        let systemFontScale = uiContent.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(systemFontScale, this.maxAppFontScale);
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create({ alignContent: Alignment.End });
            Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create({ alignContent: Alignment.Start });
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            List.create();
            List.listDirection(Axis.Horizontal);
            List.scrollBar(BarState.Off);
            List.width(PERCENT_100);
            List.height(LIST_ROW_HEIGHT);
            List.align(Alignment.Start);
        }, List);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, colIndex) => {
                const option = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (colIndex === 0) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            {
                                const itemCreation = (elmtId, isInitialRender) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
                                    itemCreation2(elmtId, isInitialRender);
                                    if (!isInitialRender) {
                                        ListItem.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                };
                                const itemCreation2 = (elmtId, isInitialRender) => {
                                    ListItem.create(deepRenderFunction, true);
                                    ListItem.width({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.ohos_id_max_padding_start'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    });
                                    ListItem.height(LIST_ROW_HEIGHT);
                                };
                                const deepRenderFunction = (elmtId, isInitialRender) => {
                                    itemCreation(elmtId, isInitialRender);
                                    ListItem.pop();
                                };
                                this.observeComponentCreation2(itemCreation2, ListItem);
                                ListItem.pop();
                            }
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
                {
                    const itemCreation = (elmtId, isInitialRender) => {
                        ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
                        itemCreation2(elmtId, isInitialRender);
                        if (!isInitialRender) {
                            ListItem.pop();
                        }
                        ViewStackProcessor.StopGetAccessRecording();
                    };
                    const itemCreation2 = (elmtId, isInitialRender) => {
                        ListItem.create(deepRenderFunction, true);
                        ListItem.height(PERCENT_100);
                        ListItem.onClick(() => {
                            this.onItemClick(colIndex);
                        });
                        ListItem.focusable(true);
                        ViewStackProcessor.visualState('focused');
                        ListItem.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: FOCUS_BORDER_WIDTH,
                            color: {
                                'id': -1,
                                'type': 10001,
                                params: ['sys.color.ohos_id_color_focused_outline'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            style: BorderStyle.Solid
                        });
                        ListItem.padding({
                            start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                            end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                        });
                        ViewStackProcessor.visualState('normal');
                        ListItem.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: 0
                        });
                        ListItem.padding({
                            start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                            end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                        });
                        ViewStackProcessor.visualState();
                        ListItem.backgroundColor(this.isBackgroundHoverRow[colIndex] ?
                            this.backgroundColorRow[colIndex] : TRANS_COLOR);
                        ListItem.onHover((isHover) => {
                            Context.animateTo({
                                curve: FRICTION_CUBIC_BEZIER,
                                duration: ANIMATION_DURATION_250
                            }, () => {
                                if (isHover) {
                                    this.backgroundColorRow[colIndex] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_hover'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[colIndex] = true;
                                } else {
                                    this.isBackgroundHoverRow[colIndex] = false;
                                }
                            });
                        });
                        ListItem.onTouch((event) => {
                            if (event.type === TouchType.Down) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.backgroundColorRow[colIndex] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_click_effect'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[colIndex] = true;
                                });
                            } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.isBackgroundHoverRow[colIndex] = false;
                                });
                            }
                        });
                        ListItem.margin({ start: LengthMetrics.vp(colIndex === 0 ? -TEXT_HOT_AREA_WIDTH : 0) });
                        ListItem.tabIndex(colIndex === 0 ? this.rowIndex : -1);
                    };
                    const deepRenderFunction = (elmtId, isInitialRender) => {
                        itemCreation(elmtId, isInitialRender);
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Text.create(option);
                            Text.fontSize({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_text_size_body3'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            });
                            Text.minFontScale(1);
                            Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                            Text.fontColor(this.colorRow[colIndex]);
                            Text.fontWeight(this.fontWeightRow[colIndex]);
                            Text.focusable(true);
                        }, Text);
                        Text.pop();
                        ListItem.pop();
                    };
                    this.observeComponentCreation2(itemCreation2, ListItem);
                    ListItem.pop();
                }
            };
            this.forEachUpdateFunction(elmtId, this.filterRow.options, forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        List.pop();
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new GradientMask(this, {
                        x0: 0,
                        y0: LIST_ROW_HEIGHT / 2,
                        x1: GRADIENT_WIDTH,
                        y1: LIST_ROW_HEIGHT / 2
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/filter.ets', line: 242, col: 9 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            x0: 0,
                            y0: LIST_ROW_HEIGHT / 2,
                            x1: GRADIENT_WIDTH,
                            y1: LIST_ROW_HEIGHT / 2
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'GradientMask' });
        }
        Stack.pop();
        {
            this.observeComponentCreation2((elmtId, isInitialRender) => {
                if (isInitialRender) {
                    let componentCall = new GradientMask(this, {
                        x0: GRADIENT_WIDTH,
                        y0: LIST_ROW_HEIGHT / 2,
                        x1: 0,
                        y1: LIST_ROW_HEIGHT / 2
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/mainpage/filter.ets', line: 249, col: 7 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            x0: GRADIENT_WIDTH,
                            y0: LIST_ROW_HEIGHT / 2,
                            x1: 0,
                            y1: LIST_ROW_HEIGHT / 2
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'GradientMask' });
        }
        Stack.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

class MultiFilterRow extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__colorRow = new SynchedPropertyNesedObjectPU(params.colorRow, this, 'colorRow');
        this.__fontWeightRow = new SynchedPropertyNesedObjectPU(params.fontWeightRow, this, 'fontWeightRow');
        this.__backgroundColorRow =
            new SynchedPropertyNesedObjectPU(params.backgroundColorRow, this, 'backgroundColorRow');
        this.__isBackgroundHoverRow =
            new SynchedPropertyNesedObjectPU(params.isBackgroundHoverRow, this, 'isBackgroundHoverRow');
        this.__twoLineModeItemNumRow =
            new SynchedPropertyNesedObjectPU(params.twoLineModeItemNumRow, this, 'twoLineModeItemNumRow');
        this.__twoLineModeItemNumRecordRow =
            new SynchedPropertyNesedObjectPU(params.twoLineModeItemNumRecordRow, this, 'twoLineModeItemNumRecordRow');
        this.__arrowShowStateRow =
            new SynchedPropertyNesedObjectPU(params.arrowShowStateRow, this, 'arrowShowStateRow');
        this.__isArrowIconDown = new SynchedPropertyNesedObjectPU(params.isArrowIconDown, this, 'isArrowIconDown');
        this.filterRow = null;
        this.onItemClick = () => {
        };
        this.__arrowBgColorRow = new ObservedPropertyObjectPU({
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_hover'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        }, this, 'arrowBgColorRow');
        this.__isArrowBgHoverRow = new ObservedPropertySimplePU(false, this, 'isArrowBgHoverRow');
        this.filterColumnWidth = 0;
        this.lastFilterColumnWidth = 0;
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__colorRow.set(params.colorRow);
        this.__fontWeightRow.set(params.fontWeightRow);
        this.__backgroundColorRow.set(params.backgroundColorRow);
        this.__isBackgroundHoverRow.set(params.isBackgroundHoverRow);
        this.__twoLineModeItemNumRow.set(params.twoLineModeItemNumRow);
        this.__twoLineModeItemNumRecordRow.set(params.twoLineModeItemNumRecordRow);
        this.__arrowShowStateRow.set(params.arrowShowStateRow);
        this.__isArrowIconDown.set(params.isArrowIconDown);
        if (params.filterRow !== undefined) {
            this.filterRow = params.filterRow;
        }
        if (params.onItemClick !== undefined) {
            this.onItemClick = params.onItemClick;
        }
        if (params.arrowBgColorRow !== undefined) {
            this.arrowBgColorRow = params.arrowBgColorRow;
        }
        if (params.isArrowBgHoverRow !== undefined) {
            this.isArrowBgHoverRow = params.isArrowBgHoverRow;
        }
        if (params.filterColumnWidth !== undefined) {
            this.filterColumnWidth = params.filterColumnWidth;
        }
        if (params.lastFilterColumnWidth !== undefined) {
            this.lastFilterColumnWidth = params.lastFilterColumnWidth;
        }
        if (params.rowIndex !== undefined) {
            this.rowIndex = params.rowIndex;
        }
        if (params.maxAppFontScale !== undefined) {
            this.maxAppFontScale = params.maxAppFontScale;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
    }

    updateStateVars(params) {
        this.__colorRow.set(params.colorRow);
        this.__fontWeightRow.set(params.fontWeightRow);
        this.__backgroundColorRow.set(params.backgroundColorRow);
        this.__isBackgroundHoverRow.set(params.isBackgroundHoverRow);
        this.__twoLineModeItemNumRow.set(params.twoLineModeItemNumRow);
        this.__twoLineModeItemNumRecordRow.set(params.twoLineModeItemNumRecordRow);
        this.__arrowShowStateRow.set(params.arrowShowStateRow);
        this.__isArrowIconDown.set(params.isArrowIconDown);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__colorRow.purgeDependencyOnElmtId(rmElmtId);
        this.__fontWeightRow.purgeDependencyOnElmtId(rmElmtId);
        this.__backgroundColorRow.purgeDependencyOnElmtId(rmElmtId);
        this.__isBackgroundHoverRow.purgeDependencyOnElmtId(rmElmtId);
        this.__twoLineModeItemNumRow.purgeDependencyOnElmtId(rmElmtId);
        this.__twoLineModeItemNumRecordRow.purgeDependencyOnElmtId(rmElmtId);
        this.__arrowShowStateRow.purgeDependencyOnElmtId(rmElmtId);
        this.__isArrowIconDown.purgeDependencyOnElmtId(rmElmtId);
        this.__arrowBgColorRow.purgeDependencyOnElmtId(rmElmtId);
        this.__isArrowBgHoverRow.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__colorRow.aboutToBeDeleted();
        this.__fontWeightRow.aboutToBeDeleted();
        this.__backgroundColorRow.aboutToBeDeleted();
        this.__isBackgroundHoverRow.aboutToBeDeleted();
        this.__twoLineModeItemNumRow.aboutToBeDeleted();
        this.__twoLineModeItemNumRecordRow.aboutToBeDeleted();
        this.__arrowShowStateRow.aboutToBeDeleted();
        this.__isArrowIconDown.aboutToBeDeleted();
        this.__arrowBgColorRow.aboutToBeDeleted();
        this.__isArrowBgHoverRow.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get colorRow() {
        return this.__colorRow.get();
    }

    get fontWeightRow() {
        return this.__fontWeightRow.get();
    }

    get backgroundColorRow() {
        return this.__backgroundColorRow.get();
    }

    get isBackgroundHoverRow() {
        return this.__isBackgroundHoverRow.get();
    }

    get twoLineModeItemNumRow() {
        return this.__twoLineModeItemNumRow.get();
    }

    get twoLineModeItemNumRecordRow() {
        return this.__twoLineModeItemNumRecordRow.get();
    }

    get arrowShowStateRow() {
        return this.__arrowShowStateRow.get();
    }

    get isArrowIconDown() {
        return this.__isArrowIconDown.get();
    }

    get arrowBgColorRow() {
        return this.__arrowBgColorRow.get();
    }

    set arrowBgColorRow(newValue) {
        this.__arrowBgColorRow.set(newValue);
    }

    get isArrowBgHoverRow() {
        return this.__isArrowBgHoverRow.get();
    }

    set isArrowBgHoverRow(newValue) {
        this.__isArrowBgHoverRow.set(newValue);
    }

    aboutToAppear() {
        try {
            let uiContent = this.getUIContext();
            this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
            this.maxAppFontScale = uiContent.getMaxFontScale();
        } catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause,
             code: ${code}, message: ${message}`);
        }
    }

    updateFontScale() {
        let uiContent = this.getUIContext();
        let systemFontScale = uiContent.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(systemFontScale, this.maxAppFontScale);
    }

    calcMultiFilterRowItemNum() {
        let curLineRetainWidth = this.filterColumnWidth;
        let curLineSum = 0;
        let curLine = 1;
        if (this.filterRow) {
            for (let i = 0; i < this.filterRow.options.length; i++) {
                let option = this.filterRow.options[i];
                let itemWidth = measure.measureText({
                    textContent: option,
                    fontSize: `${FILTER_FONT_SIZE * Math.min(this.updateFontScale(), MAX_FONT_SCALE)}vp`,
                });
                if (i === 0) {
                    continue;
                } else {
                    itemWidth += vp2px(TEXT_HOT_AREA_WIDTH * 2);
                }
                if (curLineRetainWidth - itemWidth >= 0) {
                    curLineRetainWidth -= itemWidth;
                    curLineSum += 1;
                } else {
                    if (curLineSum === 0) {
                        curLineSum++;
                        curLineRetainWidth = 0;
                    }
                    if (curLine === 1) {
                        curLine += 1;
                        curLineRetainWidth = this.filterColumnWidth - vp2px(ARROW_IMG_SIZE);
                        i--;
                    } else {
                        break;
                    }
                }
            }
        }
        return curLineSum;
    }

    DownAndUpArrow(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Row.height(LIST_ROW_HEIGHT);
            Row.width(ARROW_IMG_SIZE);
            Row.backgroundColor(this.isArrowBgHoverRow ? this.arrowBgColorRow : TRANS_COLOR);
            Row.focusable(true);
            Row.visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden);
            Row.onHover((isHover) => {
                Context.animateTo({
                    curve: FRICTION_CUBIC_BEZIER,
                    duration: ANIMATION_DURATION_250
                }, () => {
                    if (isHover) {
                        this.arrowBgColorRow = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_hover'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isArrowBgHoverRow = true;
                    } else {
                        this.isArrowBgHoverRow = false;
                    }
                });
            });
            Row.onTouch((event) => {
                if (event.type === TouchType.Down) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.arrowBgColorRow = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_click_effect'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isArrowBgHoverRow = true;
                    });
                } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.isArrowBgHoverRow = false;
                    });
                }
            });
            Row.onClick(() => {
                if (this.isArrowIconDown.value) {
                    this.isArrowIconDown.value = false;
                    this.arrowShowStateRow.value = false;
                    Context.animateTo({
                        curve: INTER_POLATING_SPRING,
                    }, () => {
                        this.twoLineModeItemNumRow.value = this.filterRow?.options.length;
                    });
                    Context.animateTo({
                        delay: 300,
                        duration: ARROW_ANIMATION_DURATION,
                        curve: SHARP_CUBIC_BEZIER
                    }, () => {
                        this.arrowShowStateRow.value = true;
                    });
                } else {
                    this.isArrowIconDown.value = true;
                    this.arrowShowStateRow.value = false;
                    Context.animateTo({
                        curve: INTER_POLATING_SPRING,
                    }, () => {
                        this.twoLineModeItemNumRow.value = this.twoLineModeItemNumRecordRow.value;
                    });
                    Context.animateTo({
                        delay: ARROW_SHOW_DELAY,
                        duration: ARROW_ANIMATION_DURATION,
                        curve: SHARP_CUBIC_BEZIER
                    }, () => {
                        this.arrowShowStateRow.value = true;
                    });
                }
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create(this.isArrowIconDown.value ? {
                'id': -1,
                'type': 20000,
                params: ['sys.media.ohos_ic_public_arrow_down'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : {
                'id': -1,
                'type': 20000,
                params: ['sys.media.ohos_ic_public_arrow_up'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Image.width(ARROW_IMG_SIZE);
            Image.height(LIST_ROW_HEIGHT);
            Image.fillColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_tertiary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Image.focusable(true);
            Image.draggable(false);
            ViewStackProcessor.visualState('focused');
            Image.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: FOCUS_BORDER_WIDTH,
                color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_focused_outline'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                style: BorderStyle.Solid
            });
            Image.width(ARROW_IMG_SIZE + FOCUS_BORDER_WIDTH * 2);
            Image.offset({ x: -FOCUS_BORDER_WIDTH });
            ViewStackProcessor.visualState('normal');
            Image.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: 0
            });
            Image.width(ARROW_IMG_SIZE);
            Image.offset({ x: 0 });
            ViewStackProcessor.visualState();
            Image.tabIndex(-1);
        }, Image);
        Row.pop();
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create();
            Flex.width(PERCENT_100);
            Flex.padding({
                start: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_max_padding_start'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }),
                end: LengthMetrics.resource({
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_max_padding_end'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                })
            });
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.filterRow?.options && this.filterRow?.options.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.filterRow?.options[0]);
                        Text.height(LIST_ROW_HEIGHT);
                        Text.margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) });
                        Text.fontSize({
                            'id': -1,
                            'type': 10002,
                            params: ['sys.float.ohos_id_text_size_body3'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        Text.minFontScale(1);
                        Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                        Text.maxLines(1);
                        Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                        Text.fontColor(this.colorRow[0]);
                        Text.fontWeight(this.fontWeightRow[0]);
                        Text.backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] : TRANS_COLOR);
                        Text.onClick(() => {
                            this.onItemClick(0);
                        });
                        Text.focusable(true);
                        Text.onHover((isHover) => {
                            Context.animateTo({
                                curve: FRICTION_CUBIC_BEZIER,
                                duration: ANIMATION_DURATION_250
                            }, () => {
                                if (isHover) {
                                    this.backgroundColorRow[0] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_hover'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[0] = true;
                                } else {
                                    this.isBackgroundHoverRow[0] = false;
                                }
                            });
                        });
                        Text.onTouch((event) => {
                            if (event.type === TouchType.Down) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.backgroundColorRow[0] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_click_effect'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[0] = true;
                                });
                            } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                                Context.animateTo({
                                    curve: SHARP_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_100
                                }, () => {
                                    this.isBackgroundHoverRow[0] = false;
                                });
                            }
                        });
                        ViewStackProcessor.visualState('focused');
                        Text.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: FOCUS_BORDER_WIDTH,
                            color: {
                                'id': -1,
                                'type': 10001,
                                params: ['sys.color.ohos_id_color_focused_outline'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            style: BorderStyle.Solid
                        });
                        Text.padding({
                            start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                            end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                        });
                        ViewStackProcessor.visualState('normal');
                        Text.border({
                            radius: {
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_corner_radius_clicked'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            },
                            width: 0
                        });
                        Text.padding({
                            start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                            end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                        });
                        ViewStackProcessor.visualState();
                        Text.constraintSize({ maxWidth: '50%' });
                        Text.flexShrink(0);
                        Text.tabIndex(this.rowIndex);
                    }, Text);
                    Text.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width(PERCENT_100);
            Row.onAreaChange((_oldValue, newValue) => {
                this.filterColumnWidth = vp2px(parseInt(newValue.width.toString(), 0));
                if (this.twoLineModeItemNumRow.value === 0) {
                    let curLineSum = this.calcMultiFilterRowItemNum();
                    this.twoLineModeItemNumRow.value = curLineSum;
                    this.twoLineModeItemNumRecordRow.value = curLineSum;
                    if (this.filterRow && curLineSum < this.filterRow.options.length - 1) {
                        this.arrowShowStateRow.value = true;
                    } else {
                        this.arrowShowStateRow.value = false;
                    }
                } else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
                    let curLineSum = this.calcMultiFilterRowItemNum();
                    if (this.filterRow && curLineSum < this.filterRow.options.length - 1) {
                        if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
                            this.arrowShowStateRow.value = true;
                            this.isArrowIconDown.value = true;
                            this.twoLineModeItemNumRow.value = curLineSum;
                        }
                    } else {
                        this.arrowShowStateRow.value = false;
                        this.isArrowIconDown.value = false;
                        this.twoLineModeItemNumRow.value = curLineSum;
                    }
                    this.twoLineModeItemNumRecordRow.value = curLineSum;
                }
                this.lastFilterColumnWidth = this.filterColumnWidth;
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, colIndex) => {
                const option = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (colIndex > 0) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Text.create(option);
                                Text.transition(TransitionEffect.OPACITY);
                                Text.fontSize({
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.ohos_id_text_size_body3'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                                Text.minFontScale(1);
                                Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                                Text.maxLines(1);
                                Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                Text.height(LIST_ROW_HEIGHT);
                                Text.fontColor(this.colorRow[colIndex]);
                                Text.fontWeight(this.fontWeightRow[colIndex]);
                                Text.backgroundColor(this.isBackgroundHoverRow[colIndex] ?
                                    this.backgroundColorRow[colIndex] : TRANS_COLOR);
                                Text.onClick(() => {
                                    this.onItemClick(colIndex);
                                });
                                Text.onHover((isHover) => {
                                    Context.animateTo({
                                        curve: FRICTION_CUBIC_BEZIER,
                                        duration: ANIMATION_DURATION_250
                                    }, () => {
                                        if (isHover) {
                                            this.backgroundColorRow[colIndex] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_hover'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[colIndex] = true;
                                        } else {
                                            this.isBackgroundHoverRow[colIndex] = false;
                                        }
                                    });
                                });
                                Text.onTouch((event) => {
                                    if (event.type === TouchType.Down) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.backgroundColorRow[colIndex] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_click_effect'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[colIndex] = true;
                                        });
                                    } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.isBackgroundHoverRow[colIndex] = false;
                                        });
                                    }
                                });
                                Text.focusable(true);
                                ViewStackProcessor.visualState('focused');
                                Text.border({
                                    radius: {
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.ohos_id_corner_radius_clicked'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    },
                                    width: FOCUS_BORDER_WIDTH,
                                    color: {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_focused_outline'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    },
                                    style: BorderStyle.Solid
                                });
                                Text.padding({
                                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                                });
                                ViewStackProcessor.visualState('normal');
                                Text.border({
                                    radius: {
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.ohos_id_corner_radius_clicked'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    },
                                    width: 0
                                });
                                Text.padding({
                                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                                });
                                ViewStackProcessor.visualState();
                                Text.tabIndex(-1);
                            }, Text);
                            Text.pop();
                        });
                    } else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(elmtId, this.filterRow?.options.slice(0, this.twoLineModeItemNumRow.value + 1),
                forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.arrowShowStateRow.value) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.DownAndUpArrow.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Row.pop();
        Flex.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export class Filter extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === 'function') {
            this.paramsGenerator_ = paramsLambda;
        }
        this.container = undefined;
        this.__multiFilters = new SynchedPropertyObjectOneWayPU(params.multiFilters, this, 'multiFilters');
        this.__additionFilters = new SynchedPropertyObjectOneWayPU(params.additionFilters, this, 'additionFilters');
        this.onFilterChanged = null;
        this.__filterType = new SynchedPropertySimpleOneWayPU(params.filterType, this, 'filterType');
        this.selectedFilters = null;
        this.__colorArr = new ObservedPropertyObjectPU(null, this, 'colorArr');
        this.__fontWeightArr = new ObservedPropertyObjectPU(null, this, 'fontWeightArr');
        this.__backgroundColorArr = new ObservedPropertyObjectPU(null, this, 'backgroundColorArr');
        this.__isBackgroundHover = new ObservedPropertyObjectPU(null, this, 'isBackgroundHover');
        this.__floatArrowBgColor = new ObservedPropertyObjectPU(null, this, 'floatArrowBgColor');
        this.__isFloatArrowBgHover = new ObservedPropertySimplePU(false, this, 'isFloatArrowBgHover');
        this.__isArrowIconDownArr = new ObservedPropertyObjectPU(null, this, 'isArrowIconDownArr');
        this.__additionColorArr = new ObservedPropertyObjectPU(null, this, 'additionColorArr');
        this.__additionFontWeightArr = new ObservedPropertyObjectPU(null, this, 'additionFontWeightArr');
        this.__additionBackgroundColorArr = new ObservedPropertyObjectPU(null, this, 'additionBackgroundColorArr');
        this.__isAdditionBackgroundHover = new ObservedPropertyObjectPU(null, this, 'isAdditionBackgroundHover');
        this.__colorRefresh = new ObservedPropertySimplePU(false, this, 'colorRefresh');
        this.__isFloatBarShow = new ObservedPropertySimplePU(false, this, 'isFloatBarShow');
        this.isFloatBarShowWithoutAnimation = false;
        this.__isFloatShowAllFilter = new ObservedPropertySimplePU(false, this, 'isFloatShowAllFilter');
        this.isFloatShowAllFilterWithoutAnimation = false;
        this.__floatFilterPosition = new ObservedPropertySimplePU(0, this, 'floatFilterPosition');
        this.__floatFilterBarHeight = new ObservedPropertySimplePU(0, this, 'floatFilterBarHeight');
        this.__floatFilterBarPosition = new ObservedPropertySimplePU(0, this, 'floatFilterBarPosition');
        this.filterDynamicHeight = 0;
        this.__twoLineModeItemNum = new ObservedPropertyObjectPU(null, this, 'twoLineModeItemNum');
        this.__twoLineModeItemNumRecord = new ObservedPropertyObjectPU(null, this, 'twoLineModeItemNumRecord');
        this.__downArrowShowState = new ObservedPropertyObjectPU(null, this, 'downArrowShowState');
        this.__floatFilterBarText = new ObservedPropertySimplePU('', this, 'floatFilterBarText');
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        if (params.container !== undefined) {
            this.container = params.container;
        }
        if (params.multiFilters === undefined) {
            this.__multiFilters.set([]);
        }
        if (params.additionFilters === undefined) {
            this.__additionFilters.set(null);
        }
        if (params.onFilterChanged !== undefined) {
            this.onFilterChanged = params.onFilterChanged;
        }
        if (params.filterType === undefined) {
            this.__filterType.set(FilterType.LIST_FILTER);
        }
        if (params.selectedFilters !== undefined) {
            this.selectedFilters = params.selectedFilters;
        }
        if (params.colorArr !== undefined) {
            this.colorArr = params.colorArr;
        }
        if (params.fontWeightArr !== undefined) {
            this.fontWeightArr = params.fontWeightArr;
        }
        if (params.backgroundColorArr !== undefined) {
            this.backgroundColorArr = params.backgroundColorArr;
        }
        if (params.isBackgroundHover !== undefined) {
            this.isBackgroundHover = params.isBackgroundHover;
        }
        if (params.floatArrowBgColor !== undefined) {
            this.floatArrowBgColor = params.floatArrowBgColor;
        }
        if (params.isFloatArrowBgHover !== undefined) {
            this.isFloatArrowBgHover = params.isFloatArrowBgHover;
        }
        if (params.isArrowIconDownArr !== undefined) {
            this.isArrowIconDownArr = params.isArrowIconDownArr;
        }
        if (params.additionColorArr !== undefined) {
            this.additionColorArr = params.additionColorArr;
        }
        if (params.additionFontWeightArr !== undefined) {
            this.additionFontWeightArr = params.additionFontWeightArr;
        }
        if (params.additionBackgroundColorArr !== undefined) {
            this.additionBackgroundColorArr = params.additionBackgroundColorArr;
        }
        if (params.isAdditionBackgroundHover !== undefined) {
            this.isAdditionBackgroundHover = params.isAdditionBackgroundHover;
        }
        if (params.colorRefresh !== undefined) {
            this.colorRefresh = params.colorRefresh;
        }
        if (params.isFloatBarShow !== undefined) {
            this.isFloatBarShow = params.isFloatBarShow;
        }
        if (params.isFloatBarShowWithoutAnimation !== undefined) {
            this.isFloatBarShowWithoutAnimation = params.isFloatBarShowWithoutAnimation;
        }
        if (params.isFloatShowAllFilter !== undefined) {
            this.isFloatShowAllFilter = params.isFloatShowAllFilter;
        }
        if (params.isFloatShowAllFilterWithoutAnimation !== undefined) {
            this.isFloatShowAllFilterWithoutAnimation = params.isFloatShowAllFilterWithoutAnimation;
        }
        if (params.floatFilterPosition !== undefined) {
            this.floatFilterPosition = params.floatFilterPosition;
        }
        if (params.floatFilterBarHeight !== undefined) {
            this.floatFilterBarHeight = params.floatFilterBarHeight;
        }
        if (params.floatFilterBarPosition !== undefined) {
            this.floatFilterBarPosition = params.floatFilterBarPosition;
        }
        if (params.filterDynamicHeight !== undefined) {
            this.filterDynamicHeight = params.filterDynamicHeight;
        }
        if (params.twoLineModeItemNum !== undefined) {
            this.twoLineModeItemNum = params.twoLineModeItemNum;
        }
        if (params.twoLineModeItemNumRecord !== undefined) {
            this.twoLineModeItemNumRecord = params.twoLineModeItemNumRecord;
        }
        if (params.downArrowShowState !== undefined) {
            this.downArrowShowState = params.downArrowShowState;
        }
        if (params.floatFilterBarText !== undefined) {
            this.floatFilterBarText = params.floatFilterBarText;
        }
        if (params.maxAppFontScale !== undefined) {
            this.maxAppFontScale = params.maxAppFontScale;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
    }

    updateStateVars(params) {
        this.__multiFilters.reset(params.multiFilters);
        this.__additionFilters.reset(params.additionFilters);
        this.__filterType.reset(params.filterType);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__multiFilters.purgeDependencyOnElmtId(rmElmtId);
        this.__additionFilters.purgeDependencyOnElmtId(rmElmtId);
        this.__filterType.purgeDependencyOnElmtId(rmElmtId);
        this.__colorArr.purgeDependencyOnElmtId(rmElmtId);
        this.__fontWeightArr.purgeDependencyOnElmtId(rmElmtId);
        this.__backgroundColorArr.purgeDependencyOnElmtId(rmElmtId);
        this.__isBackgroundHover.purgeDependencyOnElmtId(rmElmtId);
        this.__floatArrowBgColor.purgeDependencyOnElmtId(rmElmtId);
        this.__isFloatArrowBgHover.purgeDependencyOnElmtId(rmElmtId);
        this.__isArrowIconDownArr.purgeDependencyOnElmtId(rmElmtId);
        this.__additionColorArr.purgeDependencyOnElmtId(rmElmtId);
        this.__additionFontWeightArr.purgeDependencyOnElmtId(rmElmtId);
        this.__additionBackgroundColorArr.purgeDependencyOnElmtId(rmElmtId);
        this.__isAdditionBackgroundHover.purgeDependencyOnElmtId(rmElmtId);
        this.__colorRefresh.purgeDependencyOnElmtId(rmElmtId);
        this.__isFloatBarShow.purgeDependencyOnElmtId(rmElmtId);
        this.__isFloatShowAllFilter.purgeDependencyOnElmtId(rmElmtId);
        this.__floatFilterPosition.purgeDependencyOnElmtId(rmElmtId);
        this.__floatFilterBarHeight.purgeDependencyOnElmtId(rmElmtId);
        this.__floatFilterBarPosition.purgeDependencyOnElmtId(rmElmtId);
        this.__twoLineModeItemNum.purgeDependencyOnElmtId(rmElmtId);
        this.__twoLineModeItemNumRecord.purgeDependencyOnElmtId(rmElmtId);
        this.__downArrowShowState.purgeDependencyOnElmtId(rmElmtId);
        this.__floatFilterBarText.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__multiFilters.aboutToBeDeleted();
        this.__additionFilters.aboutToBeDeleted();
        this.__filterType.aboutToBeDeleted();
        this.__colorArr.aboutToBeDeleted();
        this.__fontWeightArr.aboutToBeDeleted();
        this.__backgroundColorArr.aboutToBeDeleted();
        this.__isBackgroundHover.aboutToBeDeleted();
        this.__floatArrowBgColor.aboutToBeDeleted();
        this.__isFloatArrowBgHover.aboutToBeDeleted();
        this.__isArrowIconDownArr.aboutToBeDeleted();
        this.__additionColorArr.aboutToBeDeleted();
        this.__additionFontWeightArr.aboutToBeDeleted();
        this.__additionBackgroundColorArr.aboutToBeDeleted();
        this.__isAdditionBackgroundHover.aboutToBeDeleted();
        this.__colorRefresh.aboutToBeDeleted();
        this.__isFloatBarShow.aboutToBeDeleted();
        this.__isFloatShowAllFilter.aboutToBeDeleted();
        this.__floatFilterPosition.aboutToBeDeleted();
        this.__floatFilterBarHeight.aboutToBeDeleted();
        this.__floatFilterBarPosition.aboutToBeDeleted();
        this.__twoLineModeItemNum.aboutToBeDeleted();
        this.__twoLineModeItemNumRecord.aboutToBeDeleted();
        this.__downArrowShowState.aboutToBeDeleted();
        this.__floatFilterBarText.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get multiFilters() {
        return this.__multiFilters.get();
    }

    set multiFilters(newValue) {
        this.__multiFilters.set(newValue);
    }

    get additionFilters() {
        return this.__additionFilters.get();
    }

    set additionFilters(newValue) {
        this.__additionFilters.set(newValue);
    }

    get filterType() {
        return this.__filterType.get();
    }

    set filterType(newValue) {
        this.__filterType.set(newValue);
    }

    get colorArr() {
        return this.__colorArr.get();
    }

    set colorArr(newValue) {
        this.__colorArr.set(newValue);
    }

    get fontWeightArr() {
        return this.__fontWeightArr.get();
    }

    set fontWeightArr(newValue) {
        this.__fontWeightArr.set(newValue);
    }

    get backgroundColorArr() {
        return this.__backgroundColorArr.get();
    }

    set backgroundColorArr(newValue) {
        this.__backgroundColorArr.set(newValue);
    }

    get isBackgroundHover() {
        return this.__isBackgroundHover.get();
    }

    set isBackgroundHover(newValue) {
        this.__isBackgroundHover.set(newValue);
    }

    get floatArrowBgColor() {
        return this.__floatArrowBgColor.get();
    }

    set floatArrowBgColor(newValue) {
        this.__floatArrowBgColor.set(newValue);
    }

    get isFloatArrowBgHover() {
        return this.__isFloatArrowBgHover.get();
    }

    set isFloatArrowBgHover(newValue) {
        this.__isFloatArrowBgHover.set(newValue);
    }

    get isArrowIconDownArr() {
        return this.__isArrowIconDownArr.get();
    }

    set isArrowIconDownArr(newValue) {
        this.__isArrowIconDownArr.set(newValue);
    }

    get additionColorArr() {
        return this.__additionColorArr.get();
    }

    set additionColorArr(newValue) {
        this.__additionColorArr.set(newValue);
    }

    get additionFontWeightArr() {
        return this.__additionFontWeightArr.get();
    }

    set additionFontWeightArr(newValue) {
        this.__additionFontWeightArr.set(newValue);
    }

    get additionBackgroundColorArr() {
        return this.__additionBackgroundColorArr.get();
    }

    set additionBackgroundColorArr(newValue) {
        this.__additionBackgroundColorArr.set(newValue);
    }

    get isAdditionBackgroundHover() {
        return this.__isAdditionBackgroundHover.get();
    }

    set isAdditionBackgroundHover(newValue) {
        this.__isAdditionBackgroundHover.set(newValue);
    }

    get colorRefresh() {
        return this.__colorRefresh.get();
    }

    set colorRefresh(newValue) {
        this.__colorRefresh.set(newValue);
    }

    get isFloatBarShow() {
        return this.__isFloatBarShow.get();
    }

    set isFloatBarShow(newValue) {
        this.__isFloatBarShow.set(newValue);
    }

    get isFloatShowAllFilter() {
        return this.__isFloatShowAllFilter.get();
    }

    set isFloatShowAllFilter(newValue) {
        this.__isFloatShowAllFilter.set(newValue);
    }

    get floatFilterPosition() {
        return this.__floatFilterPosition.get();
    }

    set floatFilterPosition(newValue) {
        this.__floatFilterPosition.set(newValue);
    }

    get floatFilterBarHeight() {
        return this.__floatFilterBarHeight.get();
    }

    set floatFilterBarHeight(newValue) {
        this.__floatFilterBarHeight.set(newValue);
    }

    get floatFilterBarPosition() {
        return this.__floatFilterBarPosition.get();
    }

    set floatFilterBarPosition(newValue) {
        this.__floatFilterBarPosition.set(newValue);
    }

    get twoLineModeItemNum() {
        return this.__twoLineModeItemNum.get();
    }

    set twoLineModeItemNum(newValue) {
        this.__twoLineModeItemNum.set(newValue);
    }

    get twoLineModeItemNumRecord() {
        return this.__twoLineModeItemNumRecord.get();
    }

    set twoLineModeItemNumRecord(newValue) {
        this.__twoLineModeItemNumRecord.set(newValue);
    }

    get downArrowShowState() {
        return this.__downArrowShowState.get();
    }

    set downArrowShowState(newValue) {
        this.__downArrowShowState.set(newValue);
    }

    get floatFilterBarText() {
        return this.__floatFilterBarText.get();
    }

    set floatFilterBarText(newValue) {
        this.__floatFilterBarText.set(newValue);
    }

    textColor(rowIndex, colIndex) {
        if (this.selectedFilters && this.selectedFilters.length > rowIndex &&
            this.selectedFilters[rowIndex].index === colIndex) {
            return {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
        }
        return {
            'id': -1,
            'type': 10001,
            params: ['sys.color.ohos_id_color_text_primary'],
            'bundleName': '__harDefaultBundleName__',
            'moduleName': '__harDefaultModuleName__'
        };
    }

    aboutToAppear() {
        this.initParams();
        try {
            let uiContent = this.getUIContext();
            this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
            this.maxAppFontScale = uiContent.getMaxFontScale();
        } catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(ERROR_CODE, 'Ace', `Failed to init fontsizescale info, cause,
             code: ${code}, message: ${message}`);
        }
    }

    updateFontScale() {
        let uiContent = this.getUIContext();
        let systemFontScale = uiContent.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(systemFontScale, this.maxAppFontScale);
    }

    filterItemClick(rowIndex, colIndex) {
        let selectedFilterValue = this.multiFilters[rowIndex].options[colIndex];
        if (this.selectedFilters && colIndex !== this.selectedFilters[rowIndex].index) {
            if (this.colorArr) {
                this.colorArr[rowIndex][colIndex] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary_activated'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                };
                this.colorArr[rowIndex][this.selectedFilters[rowIndex].index] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                };
            }
            if (this.fontWeightArr) {
                this.fontWeightArr[rowIndex][colIndex] = FontWeight.Medium;
                this.fontWeightArr[rowIndex][this.selectedFilters[rowIndex].index] = FontWeight.Regular;
            }
            this.colorRefresh = !this.colorRefresh;
            this.selectedFilters[rowIndex].value = selectedFilterValue;
            this.selectedFilters[rowIndex].index = colIndex;
            let filterChanged = this.onFilterChanged;
            filterChanged && filterChanged(this.selectedFilters);
        }
        this.refreshFloatFilterBarText();
    }

    refreshFloatFilterBarText() {
        this.floatFilterBarText = '';
        if (this.selectedFilters) {
            for (let i = 0; i < this.selectedFilters.length; i++) {
                if (this.selectedFilters[i].value !== null) {
                    if (typeof this.selectedFilters[i].value !== 'string') {
                        this.selectedFilters[i].value =
                          getContext()?.resourceManager?.getStringSync(this.selectedFilters[i].value);
                    }
                    if (i === 0) {
                        this.floatFilterBarText += this.selectedFilters[i].value;
                    } else {
                        this.floatFilterBarText += '/' + this.selectedFilters[i].value;
                    }
                }
            }
        }
    }

    initParams() {
        if (!this.selectedFilters) {
            this.selectedFilters = [];
            for (let filter of this.multiFilters) {
                let result = { name: filter.name, index: -1, value: '' };
                if (filter.options.length > 0) {
                    result.index = 0;
                    result.value = filter.options[0];
                }
                this.selectedFilters.push(result);
            }
            if (this.additionFilters && this.additionFilters.name) {
                let result = { name: this.additionFilters.name, index: -1, value: '' };
                this.selectedFilters.push(result);
            }
            this.refreshFloatFilterBarText();
        }
        if (!this.colorArr) {
            this.colorArr = [];
            this.backgroundColorArr = [];
            this.isBackgroundHover = [];
            this.fontWeightArr = [];
            this.isArrowIconDownArr = [];
            this.floatArrowBgColor = {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
            for (let filter of this.multiFilters) {
                let colorRow = new ResourceArray();
                let fontWeightRow = new FontWeightArray();
                let backgroundColorRow = new ResourceArray();
                let isBackgroundHoverRow = new BooleanArray();
                for (let index of filter.options.keys()) {
                    if (index === 0) {
                        colorRow.push({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary_activated'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        fontWeightRow.push(FontWeight.Medium);
                    } else {
                        colorRow.push({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        fontWeightRow.push(FontWeight.Regular);
                    }
                    backgroundColorRow.push({
                        'id': -1,
                        'type': 10001,
                        params: ['sys.color.ohos_id_color_hover'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    });
                }
                this.colorArr.push(colorRow);
                this.fontWeightArr.push(fontWeightRow);
                this.backgroundColorArr.push(backgroundColorRow);
                this.isBackgroundHover.push(isBackgroundHoverRow);
                this.isArrowIconDownArr.push(new ObservedBoolean(true));
            }
        }
        if (this.additionFilters && this.additionFilters.options) {
            this.additionColorArr = [];
            this.additionFontWeightArr = [];
            this.additionBackgroundColorArr = [];
            this.isAdditionBackgroundHover = [];
            for (let i = 0; i < this.additionFilters.options.length; i++) {
                this.additionColorArr.push({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.additionFontWeightArr.push(FontWeight.Regular);
                this.additionBackgroundColorArr.push({
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_hover'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.isAdditionBackgroundHover.push(false);
            }
        }
        if (!this.twoLineModeItemNum) {
            this.twoLineModeItemNum = [];
            this.twoLineModeItemNumRecord = [];
            this.downArrowShowState = [];
            for (let i = 0; i < this.multiFilters.length; i++) {
                this.twoLineModeItemNum.push(new ObservedNumber(this.multiFilters[i].options.length));
                this.twoLineModeItemNumRecord.push(new ObservedNumber(this.multiFilters[i].options.length));
                this.downArrowShowState.push(new ObservedBoolean(false));
            }
        }
    }

    ListFilter(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(PERCENT_100);
            Column.align(Alignment.Start);
            Column.onAreaChange((_oldValue, newValue) => {
                if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
                    if (this.additionFilters !== null) {
                        this.filterDynamicHeight =
                            parseInt(newValue.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
                    } else {
                        this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + FILTER_TOP_PADDING;
                    }
                    this.floatFilterPosition = -this.filterDynamicHeight;
                }
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, rowIndex) => {
                const filter = _item;
                {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        if (isInitialRender) {
                            let componentCall = new ListFilterRow(this, {
                                colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
                                filterRow: filter,
                                onItemClick: (colIndex) => {
                                    this.filterItemClick(rowIndex, colIndex);
                                },
                                rowIndex: rowIndex,
                            }, undefined, elmtId, () => {
                            }, { page: 'library/src/main/ets/components/mainpage/filter.ets', line: 815, col: 9 });
                            ViewPU.create(componentCall);
                            let paramsLambda = () => {
                                return {
                                    colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                    fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                    backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                    isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
                                    filterRow: filter,
                                    onItemClick: (colIndex) => {
                                        this.filterItemClick(rowIndex, colIndex);
                                    },
                                    rowIndex: rowIndex
                                };
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                        } else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {
                                colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : []
                            });
                        }
                    }, { name: 'ListFilterRow' });
                }
            };
            this.forEachUpdateFunction(elmtId, this.multiFilters, forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Column.pop();
    }

    MultiLineFilter(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(PERCENT_100);
            Column.onAreaChange((_oldValue, newValue) => {
                if (this.additionFilters !== null) {
                    this.filterDynamicHeight =
                        parseInt(newValue.height.toString(), 0) + LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
                } else {
                    this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + FILTER_TOP_PADDING;
                }
                if (!this.isFloatBarShowWithoutAnimation && !this.isFloatShowAllFilterWithoutAnimation) {
                    this.floatFilterPosition = -this.filterDynamicHeight;
                }
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, rowIndex) => {
                const filterItem = _item;
                {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        if (isInitialRender) {
                            let componentCall = new MultiFilterRow(this, {
                                colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
                                arrowShowStateRow: this.downArrowShowState ?
                                    this.downArrowShowState[rowIndex] : new ObservedBoolean(false),
                                twoLineModeItemNumRow: this.twoLineModeItemNum ?
                                    this.twoLineModeItemNum[rowIndex] : new ObservedNumber(0),
                                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
                                    this.twoLineModeItemNumRecord[rowIndex] : new ObservedNumber(0),
                                isArrowIconDown: this.isArrowIconDownArr ?
                                    this.isArrowIconDownArr[rowIndex] : new ObservedBoolean(false),
                                filterRow: filterItem,
                                onItemClick: (colIndex) => {
                                    this.filterItemClick(rowIndex, colIndex);
                                },
                                rowIndex: rowIndex,
                            }, undefined, elmtId, () => {
                            }, { page: 'library/src/main/ets/components/mainpage/filter.ets', line: 844, col: 9 });
                            ViewPU.create(componentCall);
                            let paramsLambda = () => {
                                return {
                                    colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                    fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                    backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                    isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
                                    arrowShowStateRow: this.downArrowShowState ?
                                        this.downArrowShowState[rowIndex] : new ObservedBoolean(false),
                                    twoLineModeItemNumRow: this.twoLineModeItemNum ?
                                        this.twoLineModeItemNum[rowIndex] : new ObservedNumber(0),
                                    twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
                                        this.twoLineModeItemNumRecord[rowIndex] : new ObservedNumber(0),
                                    isArrowIconDown: this.isArrowIconDownArr ?
                                        this.isArrowIconDownArr[rowIndex] : new ObservedBoolean(false),
                                    filterRow: filterItem,
                                    onItemClick: (colIndex) => {
                                        this.filterItemClick(rowIndex, colIndex);
                                    },
                                    rowIndex: rowIndex
                                };
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                        } else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {
                                colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
                                arrowShowStateRow: this.downArrowShowState ?
                                    this.downArrowShowState[rowIndex] : new ObservedBoolean(false),
                                twoLineModeItemNumRow: this.twoLineModeItemNum ?
                                    this.twoLineModeItemNum[rowIndex] : new ObservedNumber(0),
                                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
                                    this.twoLineModeItemNumRecord[rowIndex] : new ObservedNumber(0),
                                isArrowIconDown: this.isArrowIconDownArr ?
                                    this.isArrowIconDownArr[rowIndex] : new ObservedBoolean(false)
                            });
                        }
                    }, { name: 'MultiFilterRow' });
                }
            };
            this.forEachUpdateFunction(elmtId, this.multiFilters, forEachItemGenFunction, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        Column.pop();
    }

    additionItemClick(index) {
        let additionRowIndex = this.multiFilters.length;
        if (this.selectedFilters && this.selectedFilters[additionRowIndex].index !== index) {
            if (this.selectedFilters[additionRowIndex].index === -1) {
                this.additionColorArr && (this.additionColorArr[index] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary_activated'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.additionFontWeightArr && (this.additionFontWeightArr[index] = FontWeight.Medium);
                this.selectedFilters[additionRowIndex].value =
                    this.additionFilters ? this.additionFilters.options[index] : '';
                this.selectedFilters[additionRowIndex].index = index;
            } else {
                let lastIndex = this.selectedFilters[additionRowIndex].index;
                this.additionColorArr && (this.additionColorArr[lastIndex] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.additionColorArr && (this.additionColorArr[index] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary_activated'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.additionFontWeightArr && (this.additionFontWeightArr[lastIndex] = FontWeight.Regular);
                this.additionFontWeightArr && (this.additionFontWeightArr[index] = FontWeight.Medium);
                this.selectedFilters && (this.selectedFilters[additionRowIndex].value = this.additionFilters ?
                this.additionFilters.options[index] : '');
                this.selectedFilters && (this.selectedFilters[additionRowIndex].index = index);
            }
        } else {
            this.additionColorArr && (this.additionColorArr[index] = {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            this.additionFontWeightArr && (this.additionFontWeightArr[index] = FontWeight.Regular);
            this.selectedFilters && (this.selectedFilters[additionRowIndex].value = '');
            this.selectedFilters && (this.selectedFilters[additionRowIndex].index = -1);
        }
        if (this.selectedFilters) {
            this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
        }
        this.colorRefresh = !this.colorRefresh;
        this.refreshFloatFilterBarText();
    }

    AdditionFilterList(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.additionFilters && this.additionFilters.name && this.additionFilters.options &&
                this.additionFilters.options.length !== 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create({ alignContent: Alignment.End });
                        Stack.blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN);
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Stack.create({ alignContent: Alignment.Start });
                    }, Stack);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        List.create();
                        List.listDirection(Axis.Horizontal);
                        List.scrollBar(BarState.Off);
                        List.width(PERCENT_100);
                        List.height(LIST_ROW_HEIGHT);
                    }, List);
                    {
                        const itemCreation = (elmtId, isInitialRender) => {
                            ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
                            itemCreation2(elmtId, isInitialRender);
                            if (!isInitialRender) {
                                ListItem.pop();
                            }
                            ViewStackProcessor.StopGetAccessRecording();
                        };
                        const itemCreation2 = (elmtId, isInitialRender) => {
                            ListItem.create(deepRenderFunction, true);
                            ListItem.height(PERCENT_100);
                            ListItem.margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) });
                        };
                        const deepRenderFunction = (elmtId, isInitialRender) => {
                            itemCreation(elmtId, isInitialRender);
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Row.create();
                            }, Row);
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Text.create(this.additionFilters.name);
                                Text.fontSize({
                                    'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.ohos_id_text_size_body3'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                                Text.minFontScale(1);
                                Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                                Text.fontColor({
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_text_secondary'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                                Text.margin({
                                    start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                                    end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                                });
                                Text.padding({
                                    start: LengthMetrics.resource({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.ohos_id_max_padding_start'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    })
                                });
                            }, Text);
                            Text.pop();
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Row.create();
                                Row.width(SEPARATOR_WIDTH);
                                Row.height(SEPARATOR_HEIGHT);
                                Row.backgroundColor({
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_list_separator'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                            }, Row);
                            Row.pop();
                            Row.pop();
                            ListItem.pop();
                        };
                        this.observeComponentCreation2(itemCreation2, ListItem);
                        ListItem.pop();
                    }
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        ForEach.create();
                        const forEachItemGenFunction = (_item, index) => {
                            const option = _item;
                            {
                                const itemCreation = (elmtId, isInitialRender) => {
                                    ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
                                    itemCreation2(elmtId, isInitialRender);
                                    if (!isInitialRender) {
                                        ListItem.pop();
                                    }
                                    ViewStackProcessor.StopGetAccessRecording();
                                };
                                const itemCreation2 = (elmtId, isInitialRender) => {
                                    ListItem.create(deepRenderFunction, true);
                                    ListItem.height(PERCENT_100);
                                    ListItem.backgroundColor(this.isAdditionBackgroundHover &&
                                        this.isAdditionBackgroundHover[index] ? this.additionBackgroundColorArr ?
                                        this.additionBackgroundColorArr[index] : '' : TRANS_COLOR);
                                    ListItem.onHover((isHover) => {
                                        Context.animateTo({
                                            curve: FRICTION_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_250
                                        }, () => {
                                            if (isHover) {
                                                this.additionBackgroundColorArr &&
                                                    (this.additionBackgroundColorArr[index] = {
                                                        'id': -1,
                                                        'type': 10001,
                                                        params: ['sys.color.ohos_id_color_hover'],
                                                        'bundleName': '__harDefaultBundleName__',
                                                        'moduleName': '__harDefaultModuleName__'
                                                    });
                                                this.isAdditionBackgroundHover &&
                                                    (this.isAdditionBackgroundHover[index] = true);
                                            } else {
                                                this.isAdditionBackgroundHover &&
                                                    (this.isAdditionBackgroundHover[index] = false);
                                            }
                                        });
                                    });
                                    ListItem.onTouch((event) => {
                                        if (event.type === TouchType.Down) {
                                            Context.animateTo({
                                                curve: SHARP_CUBIC_BEZIER,
                                                duration: ANIMATION_DURATION_100
                                            }, () => {
                                                this.additionBackgroundColorArr &&
                                                    (this.additionBackgroundColorArr[index] = {
                                                        'id': -1,
                                                        'type': 10001,
                                                        params: ['sys.color.ohos_id_color_click_effect'],
                                                        'bundleName': '__harDefaultBundleName__',
                                                        'moduleName': '__harDefaultModuleName__'
                                                    });
                                                this.isAdditionBackgroundHover &&
                                                    (this.isAdditionBackgroundHover[index] = true);
                                            });
                                        } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                                            Context.animateTo({
                                                curve: SHARP_CUBIC_BEZIER,
                                                duration: ANIMATION_DURATION_100
                                            }, () => {
                                                this.isAdditionBackgroundHover &&
                                                    (this.isAdditionBackgroundHover[index] = false);
                                            });
                                        }
                                    });
                                    ListItem.focusable(true);
                                    ViewStackProcessor.visualState('focused');
                                    ListItem.border({
                                        radius: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.ohos_id_corner_radius_clicked'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        width: FOCUS_BORDER_WIDTH,
                                        color: {
                                            'id': -1,
                                            'type': 10001,
                                            params: ['sys.color.ohos_id_color_focused_outline'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        style: BorderStyle.Solid
                                    });
                                    ListItem.padding({
                                        start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH),
                                        end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH - FOCUS_BORDER_WIDTH)
                                    });
                                    ViewStackProcessor.visualState('normal');
                                    ListItem.border({
                                        radius: {
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.ohos_id_corner_radius_clicked'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        },
                                        width: 0
                                    });
                                    ListItem.padding({
                                        start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                                        end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH)
                                    });
                                    ViewStackProcessor.visualState();
                                    ListItem.onClick(() => {
                                        this.additionItemClick(index);
                                    });
                                    ListItem.tabIndex(index === 0 ? this.multiFilters.length : -1);
                                };
                                const deepRenderFunction = (elmtId, isInitialRender) => {
                                    itemCreation(elmtId, isInitialRender);
                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                        Text.create(option);
                                        Text.fontSize({
                                            'id': -1,
                                            'type': 10002,
                                            params: ['sys.float.ohos_id_text_size_body3'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__'
                                        });
                                        Text.minFontScale(1);
                                        Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                                        Text.fontColor(this.additionColorArr ? this.additionColorArr[index] : '');
                                        Text.fontWeight(this.additionFontWeightArr ?
                                            this.additionFontWeightArr[index] : '');
                                        Text.focusable(true);
                                    }, Text);
                                    Text.pop();
                                    ListItem.pop();
                                };
                                this.observeComponentCreation2(itemCreation2, ListItem);
                                ListItem.pop();
                            }
                        };
                        this.forEachUpdateFunction(elmtId, this.additionFilters.options, forEachItemGenFunction,
                            undefined, true, false);
                    }, ForEach);
                    ForEach.pop();
                    List.pop();
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new GradientMask(this, {
                                    x0: 0,
                                    y0: LIST_ROW_HEIGHT / 2,
                                    x1: GRADIENT_WIDTH,
                                    y1: LIST_ROW_HEIGHT / 2
                                }, undefined, elmtId, () => {
                                }, {
                                    page: 'library/src/main/ets/components/mainpage/filter.ets',
                                    line: 1006,
                                    col: 11
                                });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        x0: 0,
                                        y0: LIST_ROW_HEIGHT / 2,
                                        x1: GRADIENT_WIDTH,
                                        y1: LIST_ROW_HEIGHT / 2
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            } else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {});
                            }
                        }, { name: 'GradientMask' });
                    }
                    Stack.pop();
                    {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            if (isInitialRender) {
                                let componentCall = new GradientMask(this, {
                                    x0: GRADIENT_WIDTH,
                                    y0: LIST_ROW_HEIGHT / 2,
                                    x1: 0,
                                    y1: LIST_ROW_HEIGHT / 2
                                }, undefined, elmtId, () => {
                                }, { page: 'library/src/main/ets/components/mainpage/filter.ets', line: 1013, col: 9 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        x0: GRADIENT_WIDTH,
                                        y0: LIST_ROW_HEIGHT / 2,
                                        x1: 0,
                                        y1: LIST_ROW_HEIGHT / 2
                                    };
                                };
                                componentCall.paramsGenerator_ = paramsLambda;
                            } else {
                                this.updateStateVarsOfChildByElmtId(elmtId, {});
                            }
                        }, { name: 'GradientMask' });
                    }
                    Stack.pop();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
    }

    FilterHeader(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.padding({ top: FILTER_TOP_PADDING });
            Column.onVisibleAreaChange([0.0, 1.0], (_isVisible, currentRatio) => {
                if (currentRatio > 0) {
                    this.isFloatShowAllFilter = false;
                    this.isFloatShowAllFilterWithoutAnimation = false;
                    this.isFloatBarShowWithoutAnimation = false;
                    Context.animateTo({
                        curve: INTER_POLATING_SPRING,
                        onFinish: () => {
                            if (!this.isFloatBarShowWithoutAnimation) {
                                this.isFloatBarShow = false;
                            }
                        }
                    }, () => {
                        this.floatFilterBarHeight = 0;
                    });
                } else {
                    this.isFloatBarShow = true;
                    this.isFloatBarShowWithoutAnimation = true;
                    Context.animateTo({
                        curve: INTER_POLATING_SPRING
                    }, () => {
                        this.floatFilterBarPosition = 0;
                        this.floatFilterBarHeight = LIST_ROW_HEIGHT + FILTER_TOP_PADDING;
                    });
                }
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.filterType === FilterType.LIST_FILTER) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ListFilter.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.MultiLineFilter.bind(this)();
                });
            }
        }, If);
        If.pop();
        this.AdditionFilterList.bind(this)();
        Column.pop();
    }

    FloatFilterHeader(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.padding({ top: FILTER_TOP_PADDING });
            Column.width(PERCENT_100);
            Column.constraintSize({ maxHeight: '80%' });
            Column.clip(true);
            Column.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Column.opacity(FLOAT_OPACITY);
            Column.backgroundBlurStyle(BlurStyle.Thin);
            Column.visibility(this.isFloatShowAllFilter ? Visibility.Visible : Visibility.Hidden);
            Column.position({ x: 0, y: this.floatFilterPosition });
            Column.zIndex(2);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Scroll.create();
        }, Scroll);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.filterType === FilterType.LIST_FILTER) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.ListFilter.bind(this)();
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                    this.MultiLineFilter.bind(this)();
                });
            }
        }, If);
        If.pop();
        this.AdditionFilterList.bind(this)();
        Column.pop();
        Scroll.pop();
        Column.pop();
    }

    FloatFilterBar(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width(PERCENT_100);
            Row.height(this.floatFilterBarHeight);
            Row.padding({ start: LengthMetrics.vp(FOCUS_BORDER_WIDTH), end: LengthMetrics.vp(FOCUS_BORDER_WIDTH) });
            Row.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Row.opacity(FLOAT_OPACITY);
            Row.clip(true);
            Row.backgroundBlurStyle(BlurStyle.Thin);
            Row.visibility(this.isFloatBarShow ? Visibility.Visible : Visibility.Hidden);
            Row.alignItems(VerticalAlign.Bottom);
            Row.position({ x: 0, y: this.floatFilterBarPosition });
            Row.zIndex(1);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor : TRANS_COLOR);
            ViewStackProcessor.visualState('focused');
            Column.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: FOCUS_BORDER_WIDTH,
                color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_focused_outline'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                style: BorderStyle.Solid
            });
            Column.width(ARROW_IMG_SIZE + FOCUS_BORDER_WIDTH * 2);
            ViewStackProcessor.visualState('normal');
            Column.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: 0
            });
            Column.width(ARROW_IMG_SIZE);
            ViewStackProcessor.visualState();
            Column.alignItems(HorizontalAlign.Center);
            Column.width(PERCENT_100);
            Column.height(LIST_ROW_HEIGHT);
            Column.onTouch((event) => {
                if (event.type === TouchType.Down) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.floatArrowBgColor = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_click_effect'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isFloatArrowBgHover = true;
                    });
                } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.isFloatArrowBgHover = false;
                    });
                }
            });
            Column.onClick(() => {
                Context.animateTo({
                    duration: BAR_ANIMATION_DURATION,
                    curve: SHARP_CUBIC_BEZIER
                }, () => {
                    this.isFloatBarShow = false;
                    this.isFloatBarShowWithoutAnimation = false;
                });
                this.isFloatShowAllFilter = true;
                this.isFloatShowAllFilterWithoutAnimation = true;
                Context.animateTo({
                    curve: INTER_POLATING_SPRING,
                    onFinish: () => {
                        this.floatFilterBarPosition = 0;
                    }
                }, () => {
                    this.floatFilterPosition = 0;
                    this.floatFilterBarPosition = this.filterDynamicHeight;
                });
            });
            Column.onHover((isHover) => {
                if (isHover) {
                    Context.animateTo({
                        curve: FRICTION_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_250
                    }, () => {
                        this.floatArrowBgColor = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_hover'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isFloatArrowBgHover = true;
                    });
                } else {
                    Context.animateTo({
                        curve: FRICTION_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_250
                    }, () => {
                        this.isFloatArrowBgHover = false;
                    });
                }
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height(PERCENT_100);
            Row.alignItems(VerticalAlign.Center);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height(LIST_ROW_HEIGHT);
            Row.margin({ start: LengthMetrics.vp(FILTER_BAR_MARGIN) });
            Row.focusable(true);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Text.create(this.floatFilterBarText);
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.fontColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.fontSize({
                'id': -1,
                'type': 10002,
                params: ['sys.float.ohos_id_text_size_body3'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Text.minFontScale(1);
            Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
            Text.constraintSize({ maxWidth: '85%' });
            Text.maxLines(1);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Image.create({
                'id': -1,
                'type': 20000,
                params: ['sys.media.ohos_ic_public_arrow_down'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Image.width(ARROW_IMG_SIZE);
            Image.height(ARROW_IMG_SIZE);
            Image.fillColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Image.focusable(true);
            Image.draggable(false);
        }, Image);
        Row.pop();
        Row.pop();
        Column.pop();
        Row.pop();
    }

    initialRender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create({ alignContent: Alignment.Top });
            Stack.clip(true);
        }, Stack);
        this.FloatFilterBar.bind(this)();
        this.FloatFilterHeader.bind(this)();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.zIndex(0);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            List.create({ initialIndex: 0 });
            List.listDirection(Axis.Vertical);
            List.width(PERCENT_100);
            List.height(PERCENT_100);
            List.edgeEffect(EdgeEffect.Spring);
            List.onScroll((_scrollOffset, scrollState) => {
                if (this.isFloatShowAllFilterWithoutAnimation && scrollState === ScrollState.Scroll) {
                    this.isFloatBarShowWithoutAnimation = true;
                    this.isFloatShowAllFilterWithoutAnimation = false;
                    Context.animateTo({
                        duration: BAR_ANIMATION_DURATION,
                        curve: SHARP_CUBIC_BEZIER
                    }, () => {
                        this.isFloatBarShow = true;
                    });
                    Context.animateTo({
                        curve: INTER_POLATING_SPRING,
                        onFinish: () => {
                            if (!this.isFloatShowAllFilterWithoutAnimation) {
                                this.isFloatShowAllFilter = false;
                            }
                        }
                    }, () => {
                        this.floatFilterPosition = -this.filterDynamicHeight;
                        this.floatFilterBarPosition = 0;
                    });
                }
            });
        }, List);
        {
            const itemCreation = (elmtId, isInitialRender) => {
                ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
                itemCreation2(elmtId, isInitialRender);
                if (!isInitialRender) {
                    ListItem.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
            };
            const itemCreation2 = (elmtId, isInitialRender) => {
                ListItem.create(deepRenderFunction, true);
                ListItem.focusable(true);
            };
            const deepRenderFunction = (elmtId, isInitialRender) => {
                itemCreation(elmtId, isInitialRender);
                this.FilterHeader.bind(this)();
                ListItem.pop();
            };
            this.observeComponentCreation2(itemCreation2, ListItem);
            ListItem.pop();
        }
        {
            const itemCreation = (elmtId, isInitialRender) => {
                ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
                itemCreation2(elmtId, isInitialRender);
                if (!isInitialRender) {
                    ListItem.pop();
                }
                ViewStackProcessor.StopGetAccessRecording();
            };
            const itemCreation2 = (elmtId, isInitialRender) => {
                ListItem.create(deepRenderFunction, true);
                ListItem.focusable(true);
            };
            const deepRenderFunction = (elmtId, isInitialRender) => {
                itemCreation(elmtId, isInitialRender);
                this.container.bind(this)();
                ListItem.pop();
            };
            this.observeComponentCreation2(itemCreation2, ListItem);
            ListItem.pop();
        }
        List.pop();
        Column.pop();
        Stack.pop();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }

    rerender() {
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.push(this);
        this.updateDirtyElements();
        PUV2ViewBase.contextStack && PUV2ViewBase.contextStack.pop();
    }
}

export default {
    Filter, FilterType
};