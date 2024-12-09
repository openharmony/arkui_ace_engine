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
const JSON = requireNapi('util.json');
const accessibility = requireNapi('accessibility');

const TEXT_HOT_AREA_WIDTH = 8;
const LIST_ROW_HEIGHT = 40;
const ARROW_IMG_SIZE = 24;
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
export let FilterAccessibilityType;
(function (n21) {
    n21[n21['ACCESSIBILITY_TEXT'] = 0] = 'ACCESSIBILITY_TEXT';
    n21[n21['ACCESSIBILITY_DESC'] = 1] = 'ACCESSIBILITY_DESC';
    n21[n21['SEND_ACCESSIBILITY'] = 2] = 'SEND_ACCESSIBILITY';
})(FilterAccessibilityType || (FilterAccessibilityType = {}));
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
        this.__listFiltersSelectedIndex = new ObservedPropertySimplePU(0, this, 'listFiltersSelectedIndex');
        this.accessibilitySelectedText = '';
        this.bundleName = '';
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
        if (params.listFiltersSelectedIndex !== undefined) {
            this.listFiltersSelectedIndex = params.listFiltersSelectedIndex;
        }
        if (params.accessibilitySelectedText !== undefined) {
            this.accessibilitySelectedText = params.accessibilitySelectedText;
        }
        if (params.bundleName !== undefined) {
            this.bundleName = params.bundleName;
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
        this.__listFiltersSelectedIndex.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__colorRow.aboutToBeDeleted();
        this.__fontWeightRow.aboutToBeDeleted();
        this.__backgroundColorRow.aboutToBeDeleted();
        this.__isBackgroundHoverRow.aboutToBeDeleted();
        this.__listFiltersSelectedIndex.aboutToBeDeleted();
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

    get listFiltersSelectedIndex() {
        return this.__listFiltersSelectedIndex.get();
    }

    set listFiltersSelectedIndex(j20) {
        this.__listFiltersSelectedIndex.set(j20);
    }

    aboutToAppear() {
        try {
            this.bundleName = getContext(this)?.abilityInfo?.bundleName;
            let resourceManager = getContext()?.resourceManager;
            this.accessibilitySelectedText = resourceManager?.getStringByNameSync('filter_accessibility_selected');
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

    getAccessibilityText(u19, v19, w19) {
        let x19 = '';
        try {
            let b20 = '';
            if (typeof u19 === 'string') {
                b20 = u19;
            }
            else {
                b20 = getContext()?.resourceManager?.getStringSync(u19?.id);
            }
            switch (w19) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    x19 = v19 ? this.accessibilitySelectedText : b20;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    x19 = v19 ? b20 : '';
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    x19 = v19 ? `${this.accessibilitySelectedText},${b20}` : '';
                    break;
                default:
                    break;
            }
        }
        catch (y19) {
            let z19 = y19.code;
            let a20 = y19.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${z19}, message: ${a20}`);
        }
        return x19;
    }

    sendAccessibility(q19, r19) {
        let s19 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(q19, r19,
                FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(s19).then(() => {
            hilog.info(0x3900, 'Ace', `ListFilter sendAccessibility send event, event info is ${JSON.stringify(s19)}`);
        });
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
                        ListItem.accessibilityText(this.getAccessibilityText(option,
                            this.listFiltersSelectedIndex === colIndex, FilterAccessibilityType.ACCESSIBILITY_TEXT));
                        ListItem.accessibilityDescription(this.getAccessibilityText(option,
                            this.listFiltersSelectedIndex === colIndex, FilterAccessibilityType.ACCESSIBILITY_DESC));
                        ListItem.height(PERCENT_100);
                        ListItem.onClick(() => {
                            this.onItemClick(colIndex);
                            this.listFiltersSelectedIndex = colIndex;
                            this.sendAccessibility(option, true);
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
        this.__multiFiltersSelectedIndex = new ObservedPropertySimplePU(0, this, 'multiFiltersSelectedIndex');
        this.__isSendArrowAccessibility = new ObservedPropertySimplePU(false, this, 'isSendArrowAccessibility');
        this.accessibilityExpand = '';
        this.accessibilitySelectedText = '';
        this.accessibilityCollapse = '';
        this.accessibilityExpanded = '';
        this.accessibilityCollapsed = '';
        this.bundleName = '';
        this.filterId = this.getUniqueId();
        this.rowIndex = 0;
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
        if (params.multiFiltersSelectedIndex !== undefined) {
            this.multiFiltersSelectedIndex = params.multiFiltersSelectedIndex;
        }
        if (params.isSendArrowAccessibility !== undefined) {
            this.isSendArrowAccessibility = params.isSendArrowAccessibility;
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
        if (params.accessibilityExpand !== undefined) {
            this.accessibilityExpand = params.accessibilityExpand;
        }
        if (params.accessibilitySelectedText !== undefined) {
            this.accessibilitySelectedText = params.accessibilitySelectedText;
        }
        if (params.accessibilityCollapse !== undefined) {
            this.accessibilityCollapse = params.accessibilityCollapse;
        }
        if (params.accessibilityExpanded !== undefined) {
            this.accessibilityExpanded = params.accessibilityExpanded;
        }
        if (params.accessibilityCollapsed !== undefined) {
            this.accessibilityCollapsed = params.accessibilityCollapsed;
        }
        if (params.maxAppFontScale !== undefined) {
            this.maxAppFontScale = params.maxAppFontScale;
        }
        if (params.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = params.isFollowingSystemFontScale;
        }
        if (params.bundleName !== undefined) {
            this.bundleName = params.bundleName;
        }
        if (params.filterId !== undefined) {
            this.filterId = params.filterId;
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
        this.__multiFiltersSelectedIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__isSendArrowAccessibility.purgeDependencyOnElmtId(rmElmtId);
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
        this.__multiFiltersSelectedIndex.aboutToBeDeleted();
        this.__isSendArrowAccessibility.aboutToBeDeleted();
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

    set arrowBgColorRow(m16) {
        this.__arrowBgColorRow.set(m16);
    }

    get isArrowBgHoverRow() {
        return this.__isArrowBgHoverRow.get();
    }

    set isArrowBgHoverRow(l16) {
        this.__isArrowBgHoverRow.set(l16);
    }

    get multiFiltersSelectedIndex() {
        return this.__multiFiltersSelectedIndex.get();
    }

    set multiFiltersSelectedIndex(k16) {
        this.__multiFiltersSelectedIndex.set(k16);
    }

    get isSendArrowAccessibility() {
        return this.__isSendArrowAccessibility.get();
    }

    set isSendArrowAccessibility(j16) {
        this.__isSendArrowAccessibility.set(j16);
    }

    aboutToAppear() {
        try {
            this.bundleName = getContext(this)?.abilityInfo?.bundleName;
            let h16 = getContext()?.resourceManager;
            this.accessibilitySelectedText = h16?.getStringByNameSync('filter_accessibility_selected');
            this.accessibilityExpand = h16?.getStringByNameSync('filter_accessibility_expand');
            this.accessibilityCollapse = h16?.getStringByNameSync('filter_accessibility_collapse');
            this.accessibilityExpanded = h16?.getStringByNameSync('filter_accessibility_expanded');
            this.accessibilityCollapsed = h16?.getStringByNameSync('filter_accessibility_collapsed');
            let i16 = this.getUIContext();
            this.isFollowingSystemFontScale = i16.isFollowingSystemFontScale();
            this.maxAppFontScale = i16.getMaxFontScale();
        }
        catch (e16) {
            let f16 = e16.code;
            let g16 = e16.message;
            hilog.error(ERROR_CODE, 'Ace', `Filter failed to init info, cause, code: ${f16}, message: ${g16}`);
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

    getAccessibilityText(o15, p15, q15) {
        let r15 = '';
        try {
            let v15 = '';
            if (typeof o15 === 'string') {
                v15 = o15;
            }
            else {
                v15 = getContext()?.resourceManager?.getStringSync(o15?.id);
            }
            switch (q15) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    r15 = p15 ? this.accessibilitySelectedText : v15;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    r15 = p15 ? v15 : '';
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    r15 = p15 ? `${this.accessibilitySelectedText},${v15}` : '';
                    break;
                default:
                    break;
            }
        }
        catch (s15) {
            let t15 = s15.code;
            let u15 = s15.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${t15}, message: ${u15}`);
        }
        return r15;
    }

    sendAccessibility(l15, m15) {
        let n15 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(l15, m15, FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(n15);
    }

    sendArrowAccessibility(g15) {
        this.isSendArrowAccessibility = true;
        setTimeout(() => {
            let j15 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: g15,
            });
            accessibility.sendAccessibilityEvent(j15);
        }, 100);
        setTimeout(() => {
            this.isSendArrowAccessibility = false;
        }, 200);
    }

    DownAndUpArrow(n14 = null) {
        this.observeComponentCreation2((s14, t14) => {
            Button.createWithChild({ stateEffect: false, type: ButtonType.Normal });
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__',
                }
            });
            Button.height(LIST_ROW_HEIGHT);
            Button.width(ARROW_IMG_SIZE);
            Button.backgroundColor(this.isArrowBgHoverRow ? this.arrowBgColorRow : TRANS_COLOR);
            Button.focusable(true);
            Button.accessibilityGroup(true);
            Button.accessibilityText(this.isSendArrowAccessibility ?
                (this.isArrowIconDown?.value ? this.accessibilityCollapsed : this.accessibilityExpanded) :
                (this.isArrowIconDown?.value ? this.accessibilityExpand : this.accessibilityCollapse));
            Button.accessibilityDescription(this.isSendArrowAccessibility ? ' ' : '');
            Button.id(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`);
            Button.visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden);
            Button.onHover((e15) => {
                Context.animateTo({
                    curve: FRICTION_CUBIC_BEZIER,
                    duration: ANIMATION_DURATION_250
                }, () => {
                    if (e15) {
                        this.arrowBgColorRow = {
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_hover'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        };
                        this.isArrowBgHoverRow = true;
                    }
                    else {
                        this.isArrowBgHoverRow = false;
                    }
                });
            });
            Button.onTouch((b15) => {
                if (b15.type === TouchType.Down) {
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
                }
                else if (b15.type === TouchType.Up || b15.type === TouchType.Cancel) {
                    Context.animateTo({
                        curve: SHARP_CUBIC_BEZIER,
                        duration: ANIMATION_DURATION_100
                    }, () => {
                        this.isArrowBgHoverRow = false;
                    });
                }
            });
            Button.onClick(() => {
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
                }
                else {
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
                this.sendArrowAccessibility(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`);
            });
        }, Button);
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
        Button.pop();
    }

    initialRender() {
        this.observeComponentCreation2((l14, m14) => {
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
        this.observeComponentCreation2((w13, x13) => {
            If.create();
            if (this.filterRow?.options && this.filterRow?.options.length > 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    if (!If.canRetake(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`)) {
                        this.observeComponentCreation2((b14, c14) => {
                            Text.create(this.filterRow?.options[0]);
                            Text.height(LIST_ROW_HEIGHT);
                            Text.margin({ start: LengthMetrics.vp(-TEXT_HOT_AREA_WIDTH) });
                            Text.fontSize({ 'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_text_size_body3'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__' });
                            Text.minFontScale(1);
                            Text.maxFontScale(Math.min(this.updateFontScale(), MAX_FONT_SCALE));
                            Text.maxLines(1);
                            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                            Text.fontColor(this.colorRow[0]);
                            Text.fontWeight(this.fontWeightRow[0]);
                            Text.backgroundColor(this.isBackgroundHoverRow[0] ?
                            this.backgroundColorRow[0] : TRANS_COLOR);
                            Text.accessibilityText(this.getAccessibilityText(this.filterRow?.options[0],
                                this.multiFiltersSelectedIndex === 0, FilterAccessibilityType.ACCESSIBILITY_TEXT));
                            Text.accessibilityDescription(this.getAccessibilityText(this.filterRow?.options[0],
                                this.multiFiltersSelectedIndex === 0, FilterAccessibilityType.ACCESSIBILITY_DESC));
                            Text.onClick(() => {
                                this.onItemClick(0);
                                this.multiFiltersSelectedIndex = 0;
                                this.sendAccessibility(this.filterRow?.options[0], true);
                            });
                            Text.id(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`);
                            Text.focusable(true);
                            Text.onHover((j14) => {
                                Context.animateTo({
                                    curve: FRICTION_CUBIC_BEZIER,
                                    duration: ANIMATION_DURATION_250
                                }, () => {
                                    if (j14) {
                                        this.backgroundColorRow[0] = { 'id': -1,
                                            'type': 10001, params: ['sys.color.ohos_id_color_hover'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__' };
                                        this.isBackgroundHoverRow[0] = true;
                                    }
                                    else {
                                        this.isBackgroundHoverRow[0] = false;
                                    }
                                });
                            });
                            Text.onTouch((g14) => {
                                if (g14.type === TouchType.Down) {
                                    Context.animateTo({
                                        curve: SHARP_CUBIC_BEZIER,
                                        duration: ANIMATION_DURATION_100
                                    }, () => {
                                        this.backgroundColorRow[0] = { 'id': -1,
                                            'type': 10001,
                                            params: ['sys.color.ohos_id_color_click_effect'],
                                            'bundleName': '__harDefaultBundleName__',
                                            'moduleName': '__harDefaultModuleName__' };
                                        this.isBackgroundHoverRow[0] = true;
                                    });
                                }
                                else if (g14.type === TouchType.Up || g14.type === TouchType.Cancel) {
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
                                radius: { 'id': -1,
                                    'type': 10002,
                                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__' },
                                width: FOCUS_BORDER_WIDTH,
                                color: { 'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_focused_outline'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__' },
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
                                    'moduleName': '__harDefaultModuleName__' },
                                width: 0
                            });
                            Text.padding({ start: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH),
                                end: LengthMetrics.vp(TEXT_HOT_AREA_WIDTH) });
                            ViewStackProcessor.visualState();
                            Text.constraintSize({ maxWidth: '50%' });
                            Text.flexShrink(0);
                            Text.tabIndex(this.rowIndex);
                        }, Text);
                        Text.pop();
                    }
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((p13, q13) => {
            Row.create();
            Row.width(PERCENT_100);
            Row.onAreaChange((s13, t13) => {
                this.filterColumnWidth = vp2px(parseInt(t13.width.toString(), 0));
                if (this.twoLineModeItemNumRow.value === 0) {
                    let v13 = this.calcMultiFilterRowItemNum();
                    this.twoLineModeItemNumRow.value = v13;
                    this.twoLineModeItemNumRecordRow.value = v13;
                    if (this.filterRow && v13 < this.filterRow.options.length - 1) {
                        this.arrowShowStateRow.value = true;
                    }
                    else {
                        this.arrowShowStateRow.value = false;
                    }
                }
                else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
                    let u13 = this.calcMultiFilterRowItemNum();
                    if (this.filterRow && u13 < this.filterRow.options.length - 1) {
                        if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
                            this.arrowShowStateRow.value = true;
                            this.isArrowIconDown.value = true;
                            this.twoLineModeItemNumRow.value = u13;
                        }
                    }
                    else {
                        this.arrowShowStateRow.value = false;
                        this.isArrowIconDown.value = false;
                        this.twoLineModeItemNumRow.value = u13;
                    }
                    this.twoLineModeItemNumRecordRow.value = u13;
                }
                this.lastFilterColumnWidth = this.filterColumnWidth;
            });
        }, Row);
        this.observeComponentCreation2((n13, o13) => {
            Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
        }, Flex);
        this.observeComponentCreation2((q12, r12) => {
            ForEach.create();
            const s12 = (u12, v12) => {
                const w12 = u12;
                this.observeComponentCreation2((y12, z12) => {
                    If.create();
                    if (v12 > 0) {
                        this.ifElseBranchUpdateFunction(0, () => {
                            this.observeComponentCreation2((d13, e13) => {
                                Text.create(w12);
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
                                Text.fontColor(this.colorRow[v12]);
                                Text.fontWeight(this.fontWeightRow[v12]);
                                Text.accessibilityText(this.getAccessibilityText(w12,
                                    this.multiFiltersSelectedIndex === v12,
                                    FilterAccessibilityType.ACCESSIBILITY_TEXT));
                                Text.accessibilityDescription(this.getAccessibilityText(w12,
                                    this.multiFiltersSelectedIndex === v12,
                                    FilterAccessibilityType.ACCESSIBILITY_DESC));
                                Text.backgroundColor(this.isBackgroundHoverRow[v12] ?
                                this.backgroundColorRow[v12] : TRANS_COLOR);
                                Text.onClick(() => {
                                    this.onItemClick(v12);
                                    this.multiFiltersSelectedIndex = v12;
                                    this.sendAccessibility(w12, true);
                                });
                                Text.onHover((l13) => {
                                    Context.animateTo({
                                        curve: FRICTION_CUBIC_BEZIER,
                                        duration: ANIMATION_DURATION_250
                                    }, () => {
                                        if (l13) {
                                            this.backgroundColorRow[v12] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_hover'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[v12] = true;
                                        }
                                        else {
                                            this.isBackgroundHoverRow[v12] = false;
                                        }
                                    });
                                });
                                Text.onTouch((i13) => {
                                    if (i13.type === TouchType.Down) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.backgroundColorRow[v12] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_click_effect'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[v12] = true;
                                        });
                                    }
                                    else if (i13.type === TouchType.Up || i13.type === TouchType.Cancel) {
                                        Context.animateTo({
                                            curve: SHARP_CUBIC_BEZIER,
                                            duration: ANIMATION_DURATION_100
                                        }, () => {
                                            this.isBackgroundHoverRow[v12] = false;
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
                    }
                    else {
                        this.ifElseBranchUpdateFunction(1, () => {
                        });
                    }
                }, If);
                If.pop();
            };
            this.forEachUpdateFunction(q12, this.filterRow?.options.slice(0, this.twoLineModeItemNumRow.value + 1),
                s12, undefined, true, false);
        }, ForEach);
        ForEach.pop();
        this.observeComponentCreation2((m12, n12) => {
            If.create();
            if (this.arrowShowStateRow.value) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.DownAndUpArrow.bind(this)();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Flex.pop();
        Row.pop();
        Flex.pop();
    }

    rerender() {
        this.updateDirtyElements();
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
        this.__additionFiltersSelectedIndex = new ObservedPropertySimplePU(-1, this, 'additionFiltersSelectedIndex');
        this.__floatFilterBarAccessibilityText =
            new ObservedPropertySimplePU('', this, 'floatFilterBarAccessibilityText');
        this.accessibilityUnselectedText = '';
        this.accessibilitySelectedText = '';
        this.accessibilityExpanded = '';
        this.accessibilityCollapsed = '';
        this.accessibilityFilters = '';
        this.accessibilitySelectedDesc = '';
        this.accessibilityUnselectedDesc = '';
        this.accessibilityExpandDesc = '';
        this.bundleName = '';
        this.filterId = this.getUniqueId();
        this.setInitiallyProvidedValue(params);
        this.declareWatch('isFloatBarShow', this.updateFocusForAccessibility);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(z11) {
        if (z11.container !== undefined) {
            this.container = z11.container;
        }
        if (z11.multiFilters === undefined) {
            this.__multiFilters.set([]);
        }
        if (z11.additionFilters === undefined) {
            this.__additionFilters.set(null);
        }
        if (z11.onFilterChanged !== undefined) {
            this.onFilterChanged = z11.onFilterChanged;
        }
        if (z11.filterType === undefined) {
            this.__filterType.set(FilterType.LIST_FILTER);
        }
        if (z11.selectedFilters !== undefined) {
            this.selectedFilters = z11.selectedFilters;
        }
        if (z11.colorArr !== undefined) {
            this.colorArr = z11.colorArr;
        }
        if (z11.fontWeightArr !== undefined) {
            this.fontWeightArr = z11.fontWeightArr;
        }
        if (z11.backgroundColorArr !== undefined) {
            this.backgroundColorArr = z11.backgroundColorArr;
        }
        if (z11.isBackgroundHover !== undefined) {
            this.isBackgroundHover = z11.isBackgroundHover;
        }
        if (z11.floatArrowBgColor !== undefined) {
            this.floatArrowBgColor = z11.floatArrowBgColor;
        }
        if (z11.isFloatArrowBgHover !== undefined) {
            this.isFloatArrowBgHover = z11.isFloatArrowBgHover;
        }
        if (z11.isArrowIconDownArr !== undefined) {
            this.isArrowIconDownArr = z11.isArrowIconDownArr;
        }
        if (z11.additionColorArr !== undefined) {
            this.additionColorArr = z11.additionColorArr;
        }
        if (z11.additionFontWeightArr !== undefined) {
            this.additionFontWeightArr = z11.additionFontWeightArr;
        }
        if (z11.additionBackgroundColorArr !== undefined) {
            this.additionBackgroundColorArr = z11.additionBackgroundColorArr;
        }
        if (z11.isAdditionBackgroundHover !== undefined) {
            this.isAdditionBackgroundHover = z11.isAdditionBackgroundHover;
        }
        if (z11.colorRefresh !== undefined) {
            this.colorRefresh = z11.colorRefresh;
        }
        if (z11.isFloatBarShow !== undefined) {
            this.isFloatBarShow = z11.isFloatBarShow;
        }
        if (z11.isFloatBarShowWithoutAnimation !== undefined) {
            this.isFloatBarShowWithoutAnimation = z11.isFloatBarShowWithoutAnimation;
        }
        if (z11.isFloatShowAllFilter !== undefined) {
            this.isFloatShowAllFilter = z11.isFloatShowAllFilter;
        }
        if (z11.isFloatShowAllFilterWithoutAnimation !== undefined) {
            this.isFloatShowAllFilterWithoutAnimation = z11.isFloatShowAllFilterWithoutAnimation;
        }
        if (z11.floatFilterPosition !== undefined) {
            this.floatFilterPosition = z11.floatFilterPosition;
        }
        if (z11.floatFilterBarHeight !== undefined) {
            this.floatFilterBarHeight = z11.floatFilterBarHeight;
        }
        if (z11.floatFilterBarPosition !== undefined) {
            this.floatFilterBarPosition = z11.floatFilterBarPosition;
        }
        if (z11.filterDynamicHeight !== undefined) {
            this.filterDynamicHeight = z11.filterDynamicHeight;
        }
        if (z11.twoLineModeItemNum !== undefined) {
            this.twoLineModeItemNum = z11.twoLineModeItemNum;
        }
        if (z11.twoLineModeItemNumRecord !== undefined) {
            this.twoLineModeItemNumRecord = z11.twoLineModeItemNumRecord;
        }
        if (z11.downArrowShowState !== undefined) {
            this.downArrowShowState = z11.downArrowShowState;
        }
        if (z11.floatFilterBarText !== undefined) {
            this.floatFilterBarText = z11.floatFilterBarText;
        }
        if (z11.maxAppFontScale !== undefined) {
            this.maxAppFontScale = z11.maxAppFontScale;
        }
        if (z11.isFollowingSystemFontScale !== undefined) {
            this.isFollowingSystemFontScale = z11.isFollowingSystemFontScale;
        }
        if (z11.additionFiltersSelectedIndex !== undefined) {
            this.additionFiltersSelectedIndex = z11.additionFiltersSelectedIndex;
        }
        if (z11.floatFilterBarAccessibilityText !== undefined) {
            this.floatFilterBarAccessibilityText = z11.floatFilterBarAccessibilityText;
        }
        if (z11.accessibilityUnselectedText !== undefined) {
            this.accessibilityUnselectedText = z11.accessibilityUnselectedText;
        }
        if (z11.accessibilitySelectedText !== undefined) {
            this.accessibilitySelectedText = z11.accessibilitySelectedText;
        }
        if (z11.accessibilityExpanded !== undefined) {
            this.accessibilityExpanded = z11.accessibilityExpanded;
        }
        if (z11.accessibilityCollapsed !== undefined) {
            this.accessibilityCollapsed = z11.accessibilityCollapsed;
        }
        if (z11.accessibilityFilters !== undefined) {
            this.accessibilityFilters = z11.accessibilityFilters;
        }
        if (z11.accessibilitySelectedDesc !== undefined) {
            this.accessibilitySelectedDesc = z11.accessibilitySelectedDesc;
        }
        if (z11.accessibilityUnselectedDesc !== undefined) {
            this.accessibilityUnselectedDesc = z11.accessibilityUnselectedDesc;
        }
        if (z11.accessibilityExpandDesc !== undefined) {
            this.accessibilityExpandDesc = z11.accessibilityExpandDesc;
        }
        if (z11.bundleName !== undefined) {
            this.bundleName = z11.bundleName;
        }
        if (z11.filterId !== undefined) {
            this.filterId = z11.filterId;
        }
    }

    updateStateVars(y11) {
        this.__multiFilters.reset(y11.multiFilters);
        this.__additionFilters.reset(y11.additionFilters);
        this.__filterType.reset(y11.filterType);
    }

    purgeVariableDependenciesOnElmtId(x11) {
        this.__multiFilters.purgeDependencyOnElmtId(x11);
        this.__additionFilters.purgeDependencyOnElmtId(x11);
        this.__filterType.purgeDependencyOnElmtId(x11);
        this.__colorArr.purgeDependencyOnElmtId(x11);
        this.__fontWeightArr.purgeDependencyOnElmtId(x11);
        this.__backgroundColorArr.purgeDependencyOnElmtId(x11);
        this.__isBackgroundHover.purgeDependencyOnElmtId(x11);
        this.__floatArrowBgColor.purgeDependencyOnElmtId(x11);
        this.__isFloatArrowBgHover.purgeDependencyOnElmtId(x11);
        this.__isArrowIconDownArr.purgeDependencyOnElmtId(x11);
        this.__additionColorArr.purgeDependencyOnElmtId(x11);
        this.__additionFontWeightArr.purgeDependencyOnElmtId(x11);
        this.__additionBackgroundColorArr.purgeDependencyOnElmtId(x11);
        this.__isAdditionBackgroundHover.purgeDependencyOnElmtId(x11);
        this.__colorRefresh.purgeDependencyOnElmtId(x11);
        this.__isFloatBarShow.purgeDependencyOnElmtId(x11);
        this.__isFloatShowAllFilter.purgeDependencyOnElmtId(x11);
        this.__floatFilterPosition.purgeDependencyOnElmtId(x11);
        this.__floatFilterBarHeight.purgeDependencyOnElmtId(x11);
        this.__floatFilterBarPosition.purgeDependencyOnElmtId(x11);
        this.__twoLineModeItemNum.purgeDependencyOnElmtId(x11);
        this.__twoLineModeItemNumRecord.purgeDependencyOnElmtId(x11);
        this.__downArrowShowState.purgeDependencyOnElmtId(x11);
        this.__floatFilterBarText.purgeDependencyOnElmtId(x11);
        this.__additionFiltersSelectedIndex.purgeDependencyOnElmtId(x11);
        this.__floatFilterBarAccessibilityText.purgeDependencyOnElmtId(x11);
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
        this.__additionFiltersSelectedIndex.aboutToBeDeleted();
        this.__floatFilterBarAccessibilityText.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }

    get multiFilters() {
        return this.__multiFilters.get();
    }

    set multiFilters(w11) {
        this.__multiFilters.set(w11);
    }

    get additionFilters() {
        return this.__additionFilters.get();
    }

    set additionFilters(v11) {
        this.__additionFilters.set(v11);
    }

    get filterType() {
        return this.__filterType.get();
    }

    set filterType(u11) {
        this.__filterType.set(u11);
    }

    get colorArr() {
        return this.__colorArr.get();
    }

    set colorArr(t11) {
        this.__colorArr.set(t11);
    }

    get fontWeightArr() {
        return this.__fontWeightArr.get();
    }

    set fontWeightArr(s11) {
        this.__fontWeightArr.set(s11);
    }

    get backgroundColorArr() {
        return this.__backgroundColorArr.get();
    }

    set backgroundColorArr(r11) {
        this.__backgroundColorArr.set(r11);
    }

    get isBackgroundHover() {
        return this.__isBackgroundHover.get();
    }

    set isBackgroundHover(q11) {
        this.__isBackgroundHover.set(q11);
    }

    get floatArrowBgColor() {
        return this.__floatArrowBgColor.get();
    }

    set floatArrowBgColor(p11) {
        this.__floatArrowBgColor.set(p11);
    }

    get isFloatArrowBgHover() {
        return this.__isFloatArrowBgHover.get();
    }

    set isFloatArrowBgHover(o11) {
        this.__isFloatArrowBgHover.set(o11);
    }

    get isArrowIconDownArr() {
        return this.__isArrowIconDownArr.get();
    }

    set isArrowIconDownArr(n11) {
        this.__isArrowIconDownArr.set(n11);
    }

    get additionColorArr() {
        return this.__additionColorArr.get();
    }

    set additionColorArr(m11) {
        this.__additionColorArr.set(m11);
    }

    get additionFontWeightArr() {
        return this.__additionFontWeightArr.get();
    }

    set additionFontWeightArr(l11) {
        this.__additionFontWeightArr.set(l11);
    }

    get additionBackgroundColorArr() {
        return this.__additionBackgroundColorArr.get();
    }

    set additionBackgroundColorArr(k11) {
        this.__additionBackgroundColorArr.set(k11);
    }

    get isAdditionBackgroundHover() {
        return this.__isAdditionBackgroundHover.get();
    }

    set isAdditionBackgroundHover(j11) {
        this.__isAdditionBackgroundHover.set(j11);
    }

    get colorRefresh() {
        return this.__colorRefresh.get();
    }

    set colorRefresh(i11) {
        this.__colorRefresh.set(i11);
    }

    get isFloatBarShow() {
        return this.__isFloatBarShow.get();
    }

    set isFloatBarShow(h11) {
        this.__isFloatBarShow.set(h11);
    }

    get isFloatShowAllFilter() {
        return this.__isFloatShowAllFilter.get();
    }

    set isFloatShowAllFilter(g11) {
        this.__isFloatShowAllFilter.set(g11);
    }

    get floatFilterPosition() {
        return this.__floatFilterPosition.get();
    }

    set floatFilterPosition(f11) {
        this.__floatFilterPosition.set(f11);
    }

    get floatFilterBarHeight() {
        return this.__floatFilterBarHeight.get();
    }

    set floatFilterBarHeight(e11) {
        this.__floatFilterBarHeight.set(e11);
    }

    get floatFilterBarPosition() {
        return this.__floatFilterBarPosition.get();
    }

    set floatFilterBarPosition(d11) {
        this.__floatFilterBarPosition.set(d11);
    }

    get twoLineModeItemNum() {
        return this.__twoLineModeItemNum.get();
    }

    set twoLineModeItemNum(c11) {
        this.__twoLineModeItemNum.set(c11);
    }

    get twoLineModeItemNumRecord() {
        return this.__twoLineModeItemNumRecord.get();
    }

    set twoLineModeItemNumRecord(b11) {
        this.__twoLineModeItemNumRecord.set(b11);
    }

    get downArrowShowState() {
        return this.__downArrowShowState.get();
    }

    set downArrowShowState(a11) {
        this.__downArrowShowState.set(a11);
    }

    get floatFilterBarText() {
        return this.__floatFilterBarText.get();
    }

    set floatFilterBarText(z10) {
        this.__floatFilterBarText.set(z10);
    }

    get additionFiltersSelectedIndex() {
        return this.__additionFiltersSelectedIndex.get();
    }

    set additionFiltersSelectedIndex(y10) {
        this.__additionFiltersSelectedIndex.set(y10);
    }

    get floatFilterBarAccessibilityText() {
        return this.__floatFilterBarAccessibilityText.get();
    }

    set floatFilterBarAccessibilityText(x10) {
        this.__floatFilterBarAccessibilityText.set(x10);
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
            this.bundleName = getContext(this)?.abilityInfo?.bundleName;
            let resourceManager = getContext()?.resourceManager;
            this.accessibilitySelectedText = resourceManager?.getStringByNameSync('filter_accessibility_selected');
            this.accessibilityUnselectedText = resourceManager?.getStringByNameSync('filter_accessibility_unselected');
            this.accessibilityFilters = resourceManager?.getStringByNameSync('filter_accessibility_filters');
            this.accessibilitySelectedDesc = resourceManager?.getStringByNameSync('filter_accessibility_select_desc');
            this.accessibilityUnselectedDesc =
            resourceManager?.getStringByNameSync('filter_accessibility_unselect_desc');
            this.accessibilityExpandDesc = resourceManager?.getStringByNameSync('filter_accessibility_expand_desc');
            this.accessibilityExpanded = resourceManager?.getStringByNameSync('filter_accessibility_expanded');
            this.accessibilityCollapsed = resourceManager?.getStringByNameSync('filter_accessibility_collapsed');
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

    updateFocusForAccessibility() {
        if (this.isFloatBarShow) {
            let p10 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `FiliterFloatFilterBar_${this.getUniqueId()}`,
            });
            accessibility.sendAccessibilityEvent(p10);
        }
    }

    getAccessibilityText(f10, g10, h10) {
        let i10 = '';
        try {
            let m10 = '';
            if (typeof f10 === 'string') {
                m10 = f10;
            }
            else {
                m10 = getContext().resourceManager.getStringSync(f10?.id);
            }
            switch (h10) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    i10 = g10 ? `${this.accessibilitySelectedText},${m10}` : m10;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    i10 = g10 ? this.accessibilityUnselectedDesc : this.accessibilitySelectedDesc;
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    i10 = g10 ? `${this.accessibilitySelectedText},${m10}` :
                        `${this.accessibilityUnselectedText},${m10}`;
                    break;
                default:
                    break;
            }
        }
        catch (j10) {
            let k10 = j10.code;
            let l10 = j10.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${k10}, message: ${l10}`);
        }
        return i10;
    }

    sendAccessibility(b10, c10) {
        let d10 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(b10, c10,
                FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(d10).then(() => {
            hilog.info(0x3900, 'Ace', `ListFilter sendAccessibility send event, event info is ${JSON.stringify(d10)}`);
        });
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
        this.floatFilterBarAccessibilityText = '';
        if (this.selectedFilters) {
            const s9 = this.selectedFilters?.filter(w9 => w9?.value).map((v9) => {
                if (typeof v9.value !== 'string') {
                    return getContext()?.resourceManager?.getStringSync(v9.value?.id);
                }
                else {
                    return v9.value;
                }
            });
            this.floatFilterBarText = s9.join('/');
            this.floatFilterBarAccessibilityText = s9.join(' ');
        }
    }

    getFloatAccessibilityText(l9, m9) {
        let n9 = '';
        try {
            let r9 = '';
            if (typeof l9 === 'string') {
                r9 = l9;
            }
            else {
                r9 = getContext()?.resourceManager?.getStringSync(l9?.id);
            }
            switch (m9) {
                case FilterAccessibilityType.ACCESSIBILITY_TEXT:
                    n9 = `${this.accessibilityFilters},${this.accessibilityCollapsed},${r9}`;
                    break;
                case FilterAccessibilityType.ACCESSIBILITY_DESC:
                    n9 = this.accessibilityExpandDesc;
                    break;
                case FilterAccessibilityType.SEND_ACCESSIBILITY:
                    n9 = this.accessibilityExpanded;
                    break;
                default:
                    break;
            }
        }
        catch (o9) {
            let p9 = o9.code;
            let q9 = o9.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${p9}, message: ${q9}`);
        }
        return n9;
    }

    sendFloatAccessibility(i9) {
        let j9 = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility:
            this.getFloatAccessibilityText(i9, FilterAccessibilityType.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(j9);
        let k9 = ({
            type: 'requestFocusForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            customId: `filterMultiFilterRow_${this.filterId}_0`,
        });
        accessibility.sendAccessibilityEvent(k9);
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
                                filterId: this.filterId,
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
                this.additionFiltersSelectedIndex = index;
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
                this.additionFiltersSelectedIndex = index;
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
            this.additionFiltersSelectedIndex = -1;
        }
        if (this.selectedFilters) {
            this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
        }
        this.colorRefresh = !this.colorRefresh;
        this.refreshFloatFilterBarText();
    }

    getSelected(w6) {
        let x6 = this.multiFilters.length;
        if (this.selectedFilters && this.selectedFilters[x6].index !== w6) {
            return false;
        }
        else {
            return true;
        }
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
                                    ListItem.accessibilityText(this.getAccessibilityText(option,
                                        this.additionFiltersSelectedIndex === index,
                                        FilterAccessibilityType.ACCESSIBILITY_TEXT));
                                    ListItem.accessibilityDescription(this.getAccessibilityText(option,
                                        this.additionFiltersSelectedIndex === index,
                                        FilterAccessibilityType.ACCESSIBILITY_DESC));
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
                                        this.sendAccessibility(option, this.getSelected(index));
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
            Column.id(`FiliterFloatFilterBar_${this.getUniqueId()}`);
            Column.accessibilityText(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText,
                FilterAccessibilityType.ACCESSIBILITY_TEXT));
            Column.accessibilityDescription(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText,
                FilterAccessibilityType.ACCESSIBILITY_DESC));
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
                this.sendFloatAccessibility(this.floatFilterBarAccessibilityText);
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