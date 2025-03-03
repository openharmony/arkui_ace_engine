/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

let j1 = (this && this.j1) || function (d5, target, key, desc) {
    let c = arguments.length,
        r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === 'object' && typeof Reflect.f5 === 'function') {
        r = Reflect.f5(d5, target, key, desc);
    } else {
        for (let e5 = d5.length - 1; e5 >= 0; e5--) {
            if (d = d5[e5]) {
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
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const curves = requireNativeModule('ohos.curves');
const measure = requireNapi('measure');
const hilog = requireNapi('hilog');
const JSON = requireNapi('util.json');
const accessibility = requireNapi('accessibility');

const l1 = 8;
const m1 = 40;
const n1 = 24;
const o1 = 24;
const q1 = 150;
const s1 = 200;
const t1 = 250;
const u1 = 100;
const v1 = 8;
const w1 = 8;
const z1 = 16;
const a2 = 1;
const b2 = 0.95;
const c2 = 12;
const d2 = 2;
const e2 = 300;
const f2 = '100%';
const g2 = curves.cubicBezierCurve(0.33, 0, 0.67, 1);
const h2 = curves.interpolatingSpring(0, 1, 328, 34);
const i2 = curves.cubicBezierCurve(0.2, 0, 0.2, 1);
const j2 = '#00FFFFFF';
const l2 = 16;
const m2 = 2;
const n2 = 0x3900;
const t = 24;
const u = 1.45;
const a1 = 1;
const b1 = 1;

export let FilterType;
(function (FilterType) {
    FilterType[FilterType.MULTI_LINE_FILTER = 0] = 'MULTI_LINE_FILTER';
    FilterType[FilterType.LIST_FILTER = 1] = 'LIST_FILTER';
})(FilterType || (FilterType = {}));
let o2;
(function (c5) {
    c5[c5.ACCESSIBILITY_TEXT = 0] = 'ACCESSIBILITY_TEXT';
    c5[c5.ACCESSIBILITY_DESC = 1] = 'ACCESSIBILITY_DESC';
    c5[c5.SEND_ACCESSIBILITY = 2] = 'SEND_ACCESSIBILITY';
})(o2 || (o2 = {}));
let q2 = class FontWeightArray extends Array {
};
q2 = j1([
    Observed
], q2);
let s2 = class ResourceArray extends Array {
};
s2 = j1([
    Observed
], s2);
let t2 = class BooleanArray extends Array {
};
t2 = j1([
    Observed
], t2);
let u2 = class ObservedBoolean {
    constructor(value) {
        this.value = value;
    }
};
u2 = j1([
    Observed
], u2);

export { u2 };
let v2 = class ObservedNumber {
    constructor(value) {
        this.value = value;
    }
};
v2 = j1([
    Observed
], v2);
let w2 = class FilterAccessibilityText {
    constructor() {
        this.g5 = '';
        this.h5 = '';
        this.i5 = '';
        this.j5 = '';
        this.k5 = '';
        this.l5 = '';
        this.m5 = '';
        this.n5 = '';
        this.o5 = '';
        this.p5 = '';
    }
};
w2 = j1([
    Observed
], w2);

class z2 extends ViewPU {
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
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.blendMode(BlendMode.DST_OUT);
            Column.width(l2);
            Column.height(m1);
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Canvas.create(this.context2D);
            Canvas.width(l2);
            Canvas.height(m1);
            Canvas.onReady(() => {
                let b5 = this.context2D.createLinearGradient(this.x0, this.y0, this.x1, this.y1);
                b5.addColorStop(0.0, '#ffffffff');
                b5.addColorStop(1, '#00ffffff');
                this.context2D.fillStyle = b5;
                this.context2D.fillRect(0, 0, l2, m1);
            });
        }, Canvas);
        Canvas.pop();
        Column.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class a3 extends ViewPU {
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
        this.__isSelectedRow = new SynchedPropertyNesedObjectPU(params.isSelectedRow, this, 'isSelectedRow');
        this.__filterAccessibilityText =
            new SynchedPropertyNesedObjectPU(params.filterAccessibilityText, this, 'filterAccessibilityText');
        this.filterRow = { name: '', options: [] };
        this.onItemClick = () => {
        };
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.bundleName = '';
        this.filterId = this.getUniqueId();
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }

    setInitiallyProvidedValue(params) {
        this.__colorRow.set(params.colorRow);
        this.__fontWeightRow.set(params.fontWeightRow);
        this.__backgroundColorRow.set(params.backgroundColorRow);
        this.__isBackgroundHoverRow.set(params.isBackgroundHoverRow);
        this.__isSelectedRow.set(params.isSelectedRow);
        this.__filterAccessibilityText.set(params.filterAccessibilityText);
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
        this.__isSelectedRow.set(params.isSelectedRow);
        this.__filterAccessibilityText.set(params.filterAccessibilityText);
    }

    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__colorRow.purgeDependencyOnElmtId(rmElmtId);
        this.__fontWeightRow.purgeDependencyOnElmtId(rmElmtId);
        this.__backgroundColorRow.purgeDependencyOnElmtId(rmElmtId);
        this.__isBackgroundHoverRow.purgeDependencyOnElmtId(rmElmtId);
        this.__isSelectedRow.purgeDependencyOnElmtId(rmElmtId);
        this.__filterAccessibilityText.purgeDependencyOnElmtId(rmElmtId);
    }

    aboutToBeDeleted() {
        this.__colorRow.aboutToBeDeleted();
        this.__fontWeightRow.aboutToBeDeleted();
        this.__backgroundColorRow.aboutToBeDeleted();
        this.__isBackgroundHoverRow.aboutToBeDeleted();
        this.__isSelectedRow.aboutToBeDeleted();
        this.__filterAccessibilityText.aboutToBeDeleted();
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

    get isSelectedRow() {
        return this.__isSelectedRow.get();
    }

    get filterAccessibilityText() {
        return this.__filterAccessibilityText.get();
    }

    aboutToAppear() {
        try {
            let a5 = this.getUIContext();
            this.isFollowingSystemFontScale = a5.isFollowingSystemFontScale();
            this.maxAppFontScale = a5.getMaxFontScale();
        } catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(n2, 'Ace', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
        }
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
    }

    updateFontScale() {
        let y4 = this.getUIContext();
        let z4 = y4.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(z4, this.maxAppFontScale);
    }

    getAccessibilityText(resource, selected, type) {
        let accessibilityText = '';
        try {
            let x4 = '';
            if (typeof resource === 'string') {
                x4 = resource;
            } else {
                x4 = getContext()?.resourceManager?.getStringSync(resource?.id);
            }
            switch (type) {
                case o2.ACCESSIBILITY_TEXT:
                    accessibilityText = selected ? this.filterAccessibilityText.g5 : x4;
                    break;
                case o2.ACCESSIBILITY_DESC:
                    accessibilityText = selected ? x4 : '';
                    break;
                case o2.SEND_ACCESSIBILITY:
                    accessibilityText =
                        selected ? `${this.filterAccessibilityText.g5},${x4}` : '';
                    break;
                default:
                    break;
            }
        } catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
        }
        return accessibilityText;
    }

    sendAccessibility(resource, selected) {
        let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(resource, selected, o2.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
            hilog.info(0x3900, 'Ace',
                `ListFilter sendAccessibility send event, event info is ${JSON.stringify(eventInfo)}`);
        });
    }

    initialRender() {
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
            List.width(f2);
            List.height(m1);
            List.align(Alignment.Start);
        }, List);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, w4) => {
                const option = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (w4 === 0) {
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
                                    ListItem.height(m1);
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
                        ListItem.accessibilityText(this.getAccessibilityText(option, this.isSelectedRow[w4],
                            o2.ACCESSIBILITY_TEXT));
                        ListItem.accessibilityDescription(this.getAccessibilityText(option, this.isSelectedRow[w4],
                            o2.ACCESSIBILITY_DESC));
                        ListItem.id(`filterListFilterRow_${this.filterId}_${this.rowIndex}`);
                        ListItem.height(f2);
                        ListItem.onClick(() => {
                            this.onItemClick(w4);
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
                            width: d2,
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
                            start: LengthMetrics.vp(l1 - d2),
                            end: LengthMetrics.vp(l1 - d2)
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
                        ListItem.padding({ start: LengthMetrics.vp(l1), end: LengthMetrics.vp(l1) });
                        ViewStackProcessor.visualState();
                        ListItem.backgroundColor(this.isBackgroundHoverRow[w4] ? this.backgroundColorRow[w4] : j2);
                        ListItem.onHover((isHover) => {
                            Context.animateTo({
                                curve: i2,
                                duration: t1
                            }, () => {
                                if (isHover) {
                                    this.backgroundColorRow[w4] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_hover'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[w4] = true;
                                } else {
                                    this.isBackgroundHoverRow[w4] = false;
                                }
                            });
                        });
                        ListItem.onTouch((event) => {
                            if (event.type === TouchType.Down) {
                                Context.animateTo({
                                    curve: g2,
                                    duration: u1
                                }, () => {
                                    this.backgroundColorRow[w4] = {
                                        'id': -1,
                                        'type': 10001,
                                        params: ['sys.color.ohos_id_color_click_effect'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    };
                                    this.isBackgroundHoverRow[w4] = true;
                                });
                            } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                                Context.animateTo({
                                    curve: g2,
                                    duration: u1
                                }, () => {
                                    this.isBackgroundHoverRow[w4] = false;
                                });
                            }
                        });
                        ListItem.margin({ start: LengthMetrics.vp(w4 === 0 ? -l1 : 0) });
                        ListItem.tabIndex(w4 === 0 ? 1 : -1);
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
                            Text.maxFontScale(Math.min(this.updateFontScale(), m2));
                            Text.fontColor(this.colorRow[w4]);
                            Text.fontWeight(this.fontWeightRow[w4]);
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
                    let componentCall = new z2(this, {
                        x0: 0,
                        y0: m1 / 2,
                        x1: l2,
                        y1: m1 / 2
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/filter.ets', line: 322, q5: 9 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            x0: 0,
                            y0: m1 / 2,
                            x1: l2,
                            y1: m1 / 2
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
                    let componentCall = new z2(this, {
                        x0: l2,
                        y0: m1 / 2,
                        x1: 0,
                        y1: m1 / 2
                    }, undefined, elmtId, () => {
                    }, { page: 'library/src/main/ets/components/filter.ets', line: 330, q5: 7 });
                    ViewPU.create(componentCall);
                    let paramsLambda = () => {
                        return {
                            x0: l2,
                            y0: m1 / 2,
                            x1: 0,
                            y1: m1 / 2
                        };
                    };
                    componentCall.paramsGenerator_ = paramsLambda;
                } else {
                    this.updateStateVarsOfChildByElmtId(elmtId, {});
                }
            }, { name: 'GradientMask' });
        }
        Stack.pop();
    }

    rerender() {
        this.updateDirtyElements();
    }
}

class b3 extends ViewPU {
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
        this.__isSelectedRow = new SynchedPropertyNesedObjectPU(params.isSelectedRow, this, 'isSelectedRow');
        this.__filterAccessibilityText =
            new SynchedPropertyNesedObjectPU(params.filterAccessibilityText, this, 'filterAccessibilityText');
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
        this.__fontSizeScale = new SynchedPropertyObjectOneWayPU(params.fontSizeScale, this, 'fontSizeScale');
        this.__replaceEffect = new ObservedPropertySimplePU(0, this, 'replaceEffect');
        this.__isSendArrowAccessibility = new ObservedPropertySimplePU(false, this, 'isSendArrowAccessibility');
        this.filterColumnWidth = 0;
        this.lastFilterColumnWidth = 0;
        this.rowIndex = 0;
        this.maxAppFontScale = 1;
        this.isFollowingSystemFontScale = false;
        this.bundleName = '';
        this.filterId = this.getUniqueId();
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
        this.__isSelectedRow.set(params.isSelectedRow);
        this.__filterAccessibilityText.set(params.filterAccessibilityText);
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
        if (params.replaceEffect !== undefined) {
            this.replaceEffect = params.replaceEffect;
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
        this.__isSelectedRow.set(params.isSelectedRow);
        this.__filterAccessibilityText.set(params.filterAccessibilityText);
        this.__fontSizeScale.reset(params.fontSizeScale);
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
        this.__isSelectedRow.purgeDependencyOnElmtId(rmElmtId);
        this.__filterAccessibilityText.purgeDependencyOnElmtId(rmElmtId);
        this.__arrowBgColorRow.purgeDependencyOnElmtId(rmElmtId);
        this.__isArrowBgHoverRow.purgeDependencyOnElmtId(rmElmtId);
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__replaceEffect.purgeDependencyOnElmtId(rmElmtId);
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
        this.__isSelectedRow.aboutToBeDeleted();
        this.__filterAccessibilityText.aboutToBeDeleted();
        this.__arrowBgColorRow.aboutToBeDeleted();
        this.__isArrowBgHoverRow.aboutToBeDeleted();
        this.__fontSizeScale.aboutToBeDeleted();
        this.__replaceEffect.aboutToBeDeleted();
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

    get isSelectedRow() {
        return this.__isSelectedRow.get();
    }

    get filterAccessibilityText() {
        return this.__filterAccessibilityText.get();
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

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    get replaceEffect() {
        return this.__replaceEffect.get();
    }

    set replaceEffect(newValue) {
        this.__replaceEffect.set(newValue);
    }

    get isSendArrowAccessibility() {
        return this.__isSendArrowAccessibility.get();
    }

    set isSendArrowAccessibility(newValue) {
        this.__isSendArrowAccessibility.set(newValue);
    }

    aboutToAppear() {
        try {
            let v4 = this.getUIContext();
            this.isFollowingSystemFontScale = v4.isFollowingSystemFontScale();
            this.maxAppFontScale = v4.getMaxFontScale();
        } catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(n2, 'Ace', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
        }
        this.bundleName = getContext(this)?.abilityInfo?.bundleName;
    }

    updateFontScale() {
        let t4 = this.getUIContext();
        let u4 = t4.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(u4, this.maxAppFontScale);
    }

    calcMultiFilterRowItemNum() {
        let p4 = this.filterColumnWidth;
        let q4 = 0;
        let r4 = 1;
        if (this.filterRow) {
            for (let s4 = 0; s4 < this.filterRow.options.length; s4++) {
                let option = this.filterRow.options[s4];
                let itemWidth = measure.measureText({
                    textContent: option,
                    fontSize: `${c2 * Math.min(this.updateFontScale(), m2)}vp`,
                });
                if (s4 === 0) {
                    continue;
                } else {
                    itemWidth += vp2px(l1 * 2);
                }
                if (p4 - itemWidth >= 0) {
                    p4 -= itemWidth;
                    q4 += 1;
                } else {
                    if (q4 === 0) {
                        q4++;
                        p4 = 0;
                    }
                    if (r4 === 1) {
                        r4 += 1;
                        p4 =
                            this.filterColumnWidth - vp2px(n1 * (this.fontSizeScale ?? b1));
                        s4--;
                    } else {
                        break;
                    }
                }
            }
        }
        return q4;
    }

    getAccessibilityText(resource, selected, type) {
        let accessibilityText = '';
        try {
            let o4 = '';
            if (typeof resource === 'string') {
                o4 = resource;
            } else {
                o4 = getContext()?.resourceManager?.getStringSync(resource?.id);
            }
            switch (type) {
                case o2.ACCESSIBILITY_TEXT:
                    accessibilityText = selected ? this.filterAccessibilityText.g5 : o4;
                    break;
                case o2.ACCESSIBILITY_DESC:
                    accessibilityText = selected ? o4 : '';
                    break;
                case o2.SEND_ACCESSIBILITY:
                    accessibilityText =
                        selected ? `${this.filterAccessibilityText.g5},${o4}` : '';
                    break;
                default:
                    break;
            }
        } catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
        }
        return accessibilityText;
    }

    sendAccessibility(resource, selected) {
        let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(resource, selected, o2.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(eventInfo);
    }

    sendArrowAccessibility(id) {
        if (this.isSendArrowAccessibility) {
            let eventInfo = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: id,
            });
            accessibility.sendAccessibilityEvent(eventInfo).then(() => {
                setTimeout(() => {
                    this.isSendArrowAccessibility = false;
                }, 200);
            });
        }
    }

    DownAndUpArrow(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height(m1);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Button.createWithChild({ stateEffect: false, type: ButtonType.Normal });
            Button.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                }
            });
            Button.height(m1);
            Button.backgroundColor(this.isArrowBgHoverRow ? this.arrowBgColorRow : j2);
            Button.focusable(true);
            Button.accessibilityGroup(true);
            Button.accessibilityText(this.isSendArrowAccessibility ?
                (this.isArrowIconDown?.value ? this.filterAccessibilityText.k5 :
                this.filterAccessibilityText.j5) :
                (this.isArrowIconDown?.value ? this.filterAccessibilityText.h5 :
                this.filterAccessibilityText.i5));
            Button.accessibilityDescription(this.isSendArrowAccessibility ? ' ' : '');
            Button.accessibilityRole(this.isSendArrowAccessibility ? AccessibilityRoleType.ROLE_NONE :
            AccessibilityRoleType.BUTTON);
            Button.id(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`);
            Button.visibility(this.arrowShowStateRow.value ? Visibility.Visible : Visibility.Hidden);
            Button.onHover((isHover) => {
                Context.animateTo({
                    curve: i2,
                    duration: t1
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
            Button.onTouch((event) => {
                if (event.type === TouchType.Down) {
                    Context.animateTo({
                        curve: g2,
                        duration: u1
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
                        curve: g2,
                        duration: u1
                    }, () => {
                        this.isArrowBgHoverRow = false;
                    });
                }
            });
            Button.onClick(() => {
                this.isSendArrowAccessibility = true;
                this.replaceEffect += 1;
                if (this.isArrowIconDown.value) {
                    this.isArrowIconDown.value = false;
                    this.arrowShowStateRow.value = false;
                    Context.animateTo({
                        curve: h2,
                    }, () => {
                        this.twoLineModeItemNumRow.value = this.filterRow?.options.length;
                    });
                    Context.animateTo({
                        delay: 300,
                        duration: s1,
                        curve: g2
                    }, () => {
                        this.arrowShowStateRow.value = true;
                    });
                } else {
                    this.isArrowIconDown.value = true;
                    this.arrowShowStateRow.value = false;
                    Context.animateTo({
                        curve: h2,
                    }, () => {
                        this.twoLineModeItemNumRow.value = this.twoLineModeItemNumRecordRow.value;
                    });
                    Context.animateTo({
                        delay: e2,
                        duration: s1,
                        curve: g2
                    }, () => {
                        this.arrowShowStateRow.value = true;
                    });
                }
                this.sendArrowAccessibility(`filterDownAndUpArrow_${this.getUniqueId()}_${this.rowIndex}`);
            });
        }, Button);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create(this.isArrowIconDown.value ? {
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.chevron_down'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            } : {
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.chevron_up'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            SymbolGlyph.fontSize(`${(this.fontSizeScale ?? b1) * t}vp`);
            SymbolGlyph.height(m1);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_tertiary'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }]);
            SymbolGlyph.symbolEffect(new ReplaceSymbolEffect(EffectScope.WHOLE), this.replaceEffect);
            SymbolGlyph.focusable(true);
            SymbolGlyph.draggable(false);
            ViewStackProcessor.visualState('focused');
            SymbolGlyph.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: d2,
                color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_focused_outline'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                style: BorderStyle.Solid
            });
            SymbolGlyph.offset({ x: -d2 });
            ViewStackProcessor.visualState('normal');
            SymbolGlyph.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: 0
            });
            SymbolGlyph.offset({ x: 0 });
            ViewStackProcessor.visualState();
            SymbolGlyph.tabIndex(-1);
        }, SymbolGlyph);
        Button.pop();
        Row.pop();
    }

    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create();
            Flex.width(f2);
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
                    if (!If.canRetake(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`)) {
                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                            Text.create(this.filterRow?.options[0]);
                            Text.height(m1);
                            Text.margin({ start: LengthMetrics.vp(-l1) });
                            Text.fontSize({
                                'id': -1,
                                'type': 10002,
                                params: ['sys.float.ohos_id_text_size_body3'],
                                'bundleName': '__harDefaultBundleName__',
                                'moduleName': '__harDefaultModuleName__'
                            });
                            Text.minFontScale(1);
                            Text.maxFontScale(Math.min(this.updateFontScale(), m2));
                            Text.maxLines(1);
                            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                            Text.fontColor(this.colorRow[0]);
                            Text.fontWeight(this.fontWeightRow[0]);
                            Text.backgroundColor(this.isBackgroundHoverRow[0] ? this.backgroundColorRow[0] : j2);
                            Text.accessibilityText(this.getAccessibilityText(this.filterRow?.options[0],
                                this.isSelectedRow[0], o2.ACCESSIBILITY_TEXT));
                            Text.accessibilityDescription(this.getAccessibilityText(this.filterRow?.options[0],
                                this.isSelectedRow[0], o2.ACCESSIBILITY_DESC));
                            Text.onClick(() => {
                                this.onItemClick(0);
                                this.sendAccessibility(this.filterRow?.options[0], true);
                            });
                            Text.id(`filterMultiFilterRow_${this.filterId}_${this.rowIndex}`);
                            Text.focusable(true);
                            Text.onHover((isHover) => {
                                Context.animateTo({
                                    curve: i2,
                                    duration: t1
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
                                        curve: g2,
                                        duration: u1
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
                                        curve: g2,
                                        duration: u1
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
                                width: d2,
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
                                start: LengthMetrics.vp(l1 - d2),
                                end: LengthMetrics.vp(l1 - d2)
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
                            Text.padding({ start: LengthMetrics.vp(l1), end: LengthMetrics.vp(l1) });
                            ViewStackProcessor.visualState();
                            Text.constraintSize({ maxWidth: '50%' });
                            Text.flexShrink(0);
                            Text.tabIndex(1);
                        }, Text);
                        Text.pop();
                    }
                });
            } else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width(f2);
            Row.onAreaChange((l4, newValue) => {
                this.filterColumnWidth = vp2px(parseInt(newValue.width.toString(), 0));
                if (this.twoLineModeItemNumRow.value === 0) {
                    let n4 = this.calcMultiFilterRowItemNum();
                    this.twoLineModeItemNumRow.value = n4;
                    this.twoLineModeItemNumRecordRow.value = n4;
                    if (this.filterRow && n4 < this.filterRow.options.length - 1) {
                        this.arrowShowStateRow.value = true;
                    } else {
                        this.arrowShowStateRow.value = false;
                    }
                } else if (this.filterColumnWidth !== this.lastFilterColumnWidth) {
                    let m4 = this.calcMultiFilterRowItemNum();
                    if (this.filterRow && m4 < this.filterRow.options.length - 1) {
                        if (!this.arrowShowStateRow.value || this.isArrowIconDown.value) {
                            this.arrowShowStateRow.value = true;
                            this.isArrowIconDown.value = true;
                            this.twoLineModeItemNumRow.value = m4;
                        }
                    } else {
                        this.arrowShowStateRow.value = false;
                        this.isArrowIconDown.value = false;
                        this.twoLineModeItemNumRow.value = m4;
                    }
                    this.twoLineModeItemNumRecordRow.value = m4;
                }
                this.lastFilterColumnWidth = this.filterColumnWidth;
            });
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Flex.create({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap });
        }, Flex);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, k4) => {
                const option = _item;
                this.observeComponentCreation2((elmtId, isInitialRender) => {
                    If.create();
                    if (k4 > 0) {
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
                                Text.maxFontScale(Math.min(this.updateFontScale(), m2));
                                Text.maxLines(1);
                                Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                                Text.height(m1);
                                Text.fontColor(this.colorRow[k4]);
                                Text.fontWeight(this.fontWeightRow[k4]);
                                Text.accessibilityText(this.getAccessibilityText(option, this.isSelectedRow[k4],
                                    o2.ACCESSIBILITY_TEXT));
                                Text.accessibilityDescription(this.getAccessibilityText(option, this.isSelectedRow[k4],
                                    o2.ACCESSIBILITY_DESC));
                                Text.backgroundColor(this.isBackgroundHoverRow[k4] ?
                                this.backgroundColorRow[k4] : j2);
                                Text.onClick(() => {
                                    this.onItemClick(k4);
                                    this.sendAccessibility(option, true);
                                });
                                Text.onHover((isHover) => {
                                    Context.animateTo({
                                        curve: i2,
                                        duration: t1
                                    }, () => {
                                        if (isHover) {
                                            this.backgroundColorRow[k4] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_hover'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[k4] = true;
                                        } else {
                                            this.isBackgroundHoverRow[k4] = false;
                                        }
                                    });
                                });
                                Text.onTouch((event) => {
                                    if (event.type === TouchType.Down) {
                                        Context.animateTo({
                                            curve: g2,
                                            duration: u1
                                        }, () => {
                                            this.backgroundColorRow[k4] = {
                                                'id': -1,
                                                'type': 10001,
                                                params: ['sys.color.ohos_id_color_click_effect'],
                                                'bundleName': '__harDefaultBundleName__',
                                                'moduleName': '__harDefaultModuleName__'
                                            };
                                            this.isBackgroundHoverRow[k4] = true;
                                        });
                                    } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                                        Context.animateTo({
                                            curve: g2,
                                            duration: u1
                                        }, () => {
                                            this.isBackgroundHoverRow[k4] = false;
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
                                    width: d2,
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
                                    start: LengthMetrics.vp(l1 - d2),
                                    end: LengthMetrics.vp(l1 - d2)
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
                                    start: LengthMetrics.vp(l1),
                                    end: LengthMetrics.vp(l1)
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
        this.__isSelectedArr = new ObservedPropertyObjectPU(null, this, 'isSelectedArr');
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
        this.__fontSizeScale = new ObservedPropertyObjectPU(undefined, this, 'fontSizeScale');
        this.callbackId = undefined;
        this.callbacks = {
            onConfigurationUpdated: (config) => {
                this.fontSizeScale = Math.min(this.updateFontScale(), u);
                this.fontSizeScale = Math.max(this.fontSizeScale, a1);
                this.initAccessibilityResource();
            },
            onMemoryLevel() {
            }
        };
        this.__additionFiltersSelectedIndex = new ObservedPropertySimplePU(-1, this, 'additionFiltersSelectedIndex');
        this.__floatFilterBarAccessibilityText =
            new ObservedPropertySimplePU('', this, 'floatFilterBarAccessibilityText');
        this.__filterAccessibilityText = new ObservedPropertyObjectPU(new w2(), this, 'filterAccessibilityText');
        this.bundleName = '';
        this.filterId = this.getUniqueId();
        this.setInitiallyProvidedValue(params);
        this.declareWatch('isFloatBarShow', this.updateFocusForAccessibility);
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
        if (params.isSelectedArr !== undefined) {
            this.isSelectedArr = params.isSelectedArr;
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
        if (params.fontSizeScale !== undefined) {
            this.fontSizeScale = params.fontSizeScale;
        }
        if (params.callbackId !== undefined) {
            this.callbackId = params.callbackId;
        }
        if (params.callbacks !== undefined) {
            this.callbacks = params.callbacks;
        }
        if (params.additionFiltersSelectedIndex !== undefined) {
            this.additionFiltersSelectedIndex = params.additionFiltersSelectedIndex;
        }
        if (params.floatFilterBarAccessibilityText !== undefined) {
            this.floatFilterBarAccessibilityText = params.floatFilterBarAccessibilityText;
        }
        if (params.filterAccessibilityText !== undefined) {
            this.filterAccessibilityText = params.filterAccessibilityText;
        }
        if (params.bundleName !== undefined) {
            this.bundleName = params.bundleName;
        }
        if (params.filterId !== undefined) {
            this.filterId = params.filterId;
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
        this.__isSelectedArr.purgeDependencyOnElmtId(rmElmtId);
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
        this.__fontSizeScale.purgeDependencyOnElmtId(rmElmtId);
        this.__additionFiltersSelectedIndex.purgeDependencyOnElmtId(rmElmtId);
        this.__floatFilterBarAccessibilityText.purgeDependencyOnElmtId(rmElmtId);
        this.__filterAccessibilityText.purgeDependencyOnElmtId(rmElmtId);
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
        this.__isSelectedArr.aboutToBeDeleted();
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
        this.__fontSizeScale.aboutToBeDeleted();
        this.__additionFiltersSelectedIndex.aboutToBeDeleted();
        this.__floatFilterBarAccessibilityText.aboutToBeDeleted();
        this.__filterAccessibilityText.aboutToBeDeleted();
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

    get isSelectedArr() {
        return this.__isSelectedArr.get();
    }

    set isSelectedArr(newValue) {
        this.__isSelectedArr.set(newValue);
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

    get fontSizeScale() {
        return this.__fontSizeScale.get();
    }

    set fontSizeScale(newValue) {
        this.__fontSizeScale.set(newValue);
    }

    get additionFiltersSelectedIndex() {
        return this.__additionFiltersSelectedIndex.get();
    }

    set additionFiltersSelectedIndex(newValue) {
        this.__additionFiltersSelectedIndex.set(newValue);
    }

    get floatFilterBarAccessibilityText() {
        return this.__floatFilterBarAccessibilityText.get();
    }

    set floatFilterBarAccessibilityText(newValue) {
        this.__floatFilterBarAccessibilityText.set(newValue);
    }

    get filterAccessibilityText() {
        return this.__filterAccessibilityText.get();
    }

    set filterAccessibilityText(newValue) {
        this.__filterAccessibilityText.set(newValue);
    }

    textColor(rowIndex, j4) {
        if (this.selectedFilters && this.selectedFilters.length > rowIndex &&
            this.selectedFilters[rowIndex].index === j4) {
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
        this.initAccessibilityResource();
        try {
            let i4 = this.getUIContext();
            this.isFollowingSystemFontScale = i4.isFollowingSystemFontScale();
            this.maxAppFontScale = i4.getMaxFontScale();
            this.fontSizeScale = Math.min(this.updateFontScale(), u);
            this.fontSizeScale = Math.max(this.fontSizeScale, a1);
            this.callbackId = i4.getHostContext()?.getApplicationContext()?.on('environment', this.callbacks);
        } catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(n2, 'Ace', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
        }
    }

    aboutToDisappear() {
        if (this.callbackId) {
            this.getUIContext()
                .getHostContext()
            ?.getApplicationContext()
            ?.off('environment', this.callbackId);
            this.callbackId = void (0);
        }
    }

    initAccessibilityResource() {
        try {
            this.bundleName = getContext(this)?.abilityInfo?.bundleName;
            let resourceManager = getContext()?.resourceManager;
            this.filterAccessibilityText.g5 =
                resourceManager?.getStringByNameSync('filter_accessibility_selected');
            this.filterAccessibilityText.l5 =
                resourceManager?.getStringByNameSync('filter_accessibility_unselected');
            this.filterAccessibilityText.m5 =
                resourceManager?.getStringByNameSync('filter_accessibility_filters');
            this.filterAccessibilityText.n5 =
                resourceManager?.getStringByNameSync('filter_accessibility_select_desc');
            this.filterAccessibilityText.o5 =
                resourceManager?.getStringByNameSync('filter_accessibility_unselect_desc');
            this.filterAccessibilityText.p5 =
                resourceManager?.getStringByNameSync('filter_accessibility_expand_desc');
            this.filterAccessibilityText.j5 =
                resourceManager?.getStringByNameSync('filter_accessibility_expanded');
            this.filterAccessibilityText.k5 =
                resourceManager?.getStringByNameSync('filter_accessibility_collapsed');
            this.filterAccessibilityText.h5 =
                resourceManager?.getStringByNameSync('filter_accessibility_expand');
            this.filterAccessibilityText.i5 =
                resourceManager?.getStringByNameSync('filter_accessibility_collapse');
        } catch (err) {
            let code = err.code;
            let message = err.message;
            hilog.error(n2, 'Ace', `Filter failed to initAccessibilityResource, code: ${code}, message: ${message}`);
        }
    }

    updateFocusForAccessibility() {
        if (this.isFloatBarShow) {
            let eventInfo = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `FiliterFloatFilterBar_${this.getUniqueId()}`,
            });
            accessibility.sendAccessibilityEvent(eventInfo);
        }
    }

    updateFontScale() {
        let g4 = this.getUIContext();
        let h4 = g4.getHostContext()?.config?.fontSizeScale ?? 1;
        if (!this.isFollowingSystemFontScale) {
            return 1;
        }
        return Math.min(h4, this.maxAppFontScale);
    }

    getAccessibilityText(resource, selected, type) {
        let accessibilityText = '';
        try {
            let f4 = '';
            if (typeof resource === 'string') {
                f4 = resource;
            } else {
                f4 = getContext().resourceManager.getStringSync(resource?.id);
            }
            switch (type) {
                case o2.ACCESSIBILITY_TEXT:
                    accessibilityText = selected ? `${this.filterAccessibilityText.g5},${f4}` : f4;
                    break;
                case o2.ACCESSIBILITY_DESC:
                    accessibilityText = selected ? this.filterAccessibilityText.o5 :
                    this.filterAccessibilityText.n5;
                    break;
                case o2.SEND_ACCESSIBILITY:
                    accessibilityText = selected ? `${this.filterAccessibilityText.g5},${f4}` :
                        `${this.filterAccessibilityText.l5},${f4}`;
                    break;
                default:
                    break;
            }
        } catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
        }
        return accessibilityText;
    }

    sendAccessibility(resource, selected) {
        let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getAccessibilityText(resource, selected, o2.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
            hilog.info(0x3900, 'Ace',
                `ListFilter sendAccessibility send event, event info is ${JSON.stringify(eventInfo)}`);
        });
    }

    filterItemClick(rowIndex, c4) {
        let d4 = this.multiFilters[rowIndex].options[c4];
        if (this.selectedFilters && c4 !== this.selectedFilters[rowIndex].index) {
            if (this.colorArr) {
                this.colorArr[rowIndex][c4] = {
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
                this.fontWeightArr[rowIndex][c4] = FontWeight.Medium;
                this.fontWeightArr[rowIndex][this.selectedFilters[rowIndex].index] = FontWeight.Regular;
            }
            if (this.isSelectedArr) {
                this.isSelectedArr[rowIndex][c4] = true;
                this.isSelectedArr[rowIndex][this.selectedFilters[rowIndex].index] = false;
            }
            this.colorRefresh = !this.colorRefresh;
            this.selectedFilters[rowIndex].value = d4;
            this.selectedFilters[rowIndex].index = c4;
            let e4 = this.onFilterChanged;
            e4 && e4(this.selectedFilters);
        }
        this.refreshFloatFilterBarText();
    }

    refreshFloatFilterBarText() {
        this.floatFilterBarText = '';
        this.floatFilterBarAccessibilityText = '';
        if (this.selectedFilters) {
            const b4 = this.selectedFilters?.filter(item => item?.value).map((item) => {
                if (typeof item.value !== 'string') {
                    return getContext()?.resourceManager?.getStringSync(item.value?.id);
                } else {
                    return item.value;
                }
            });
            this.floatFilterBarText = b4.join('/');
            this.floatFilterBarAccessibilityText = b4.join(' ');
        }
    }

    getFloatAccessibilityText(resource, type) {
        let accessibilityText = '';
        let y3 = this.filterAccessibilityText.m5;
        let z3 = this.filterAccessibilityText.k5;
        try {
            let a4 = '';
            if (typeof resource === 'string') {
                a4 = resource;
            } else {
                a4 = getContext()?.resourceManager?.getStringSync(resource?.id);
            }
            switch (type) {
                case o2.ACCESSIBILITY_TEXT:
                    accessibilityText =
                        `${y3},${z3},${a4}`;
                    break;
                case o2.ACCESSIBILITY_DESC:
                    accessibilityText = this.filterAccessibilityText.p5;
                    break;
                case o2.SEND_ACCESSIBILITY:
                    accessibilityText = this.filterAccessibilityText.j5;
                    break;
                default:
                    break;
            }
        } catch (error) {
            let code = error.code;
            let message = error.message;
            hilog.error(0x3900, 'Ace', `Filter getAccessibilityText error, code: ${code}, message: ${message}`);
        }
        return accessibilityText;
    }

    sendFloatAccessibility(resource) {
        let eventInfo = ({
            type: 'announceForAccessibility',
            bundleName: this.bundleName,
            triggerAction: 'common',
            textAnnouncedForAccessibility: this.getFloatAccessibilityText(resource, o2.SEND_ACCESSIBILITY),
        });
        accessibility.sendAccessibilityEvent(eventInfo);
        if (this.multiFilters && this.multiFilters.length > 0) {
            if (this.filterType === FilterType.LIST_FILTER) {
                let x3 = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: this.bundleName,
                    triggerAction: 'common',
                    customId: `filterListFilterRow_${this.filterId}_0`,
                });
                accessibility.sendAccessibilityEvent(x3);
            } else if (this.filterType === FilterType.MULTI_LINE_FILTER) {
                let w3 = ({
                    type: 'requestFocusForAccessibility',
                    bundleName: this.bundleName,
                    triggerAction: 'common',
                    customId: `filterMultiFilterRow_${this.filterId}_0`,
                });
                accessibility.sendAccessibilityEvent(w3);
            }
        } else if (this.additionFilters && this.additionFilters.name) {
            let v3 = ({
                type: 'requestFocusForAccessibility',
                bundleName: this.bundleName,
                triggerAction: 'common',
                customId: `filterAdditionFiltersName_${this.filterId}`,
            });
            accessibility.sendAccessibilityEvent(v3);
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
            this.isSelectedArr = [];
            this.floatArrowBgColor = {
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            };
            for (let filter of this.multiFilters) {
                let q3 = new s2();
                let r3 = new q2();
                let s3 = new s2();
                let t3 = new t2();
                let u3 = new t2();
                for (let index of filter.options.keys()) {
                    if (index === 0) {
                        q3.push({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary_activated'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        r3.push(FontWeight.Medium);
                        u3.push(true);
                    } else {
                        q3.push({
                            'id': -1,
                            'type': 10001,
                            params: ['sys.color.ohos_id_color_text_primary'],
                            'bundleName': '__harDefaultBundleName__',
                            'moduleName': '__harDefaultModuleName__'
                        });
                        r3.push(FontWeight.Regular);
                        u3.push(false);
                    }
                    s3.push({
                        'id': -1,
                        'type': 10001,
                        params: ['sys.color.ohos_id_color_hover'],
                        'bundleName': '__harDefaultBundleName__',
                        'moduleName': '__harDefaultModuleName__'
                    });
                }
                this.colorArr.push(q3);
                this.fontWeightArr.push(r3);
                this.backgroundColorArr.push(s3);
                this.isBackgroundHover.push(t3);
                this.isArrowIconDownArr.push(new u2(true));
                this.isSelectedArr.push(u3);
            }
        }
        if (this.additionFilters && this.additionFilters.options) {
            this.additionColorArr = [];
            this.additionFontWeightArr = [];
            this.additionBackgroundColorArr = [];
            this.isAdditionBackgroundHover = [];
            for (let p3 = 0; p3 < this.additionFilters.options.length; p3++) {
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
            for (let o3 = 0; o3 < this.multiFilters.length; o3++) {
                this.twoLineModeItemNum.push(new v2(this.multiFilters[o3].options.length));
                this.twoLineModeItemNumRecord.push(new v2(this.multiFilters[o3].options.length));
                this.downArrowShowState.push(new u2(false));
            }
        }
    }

    ListFilter(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Column.create();
            Column.width(f2);
            Column.align(Alignment.Start);
            Column.onAreaChange((n3, newValue) => {
                if (!this.isFloatShowAllFilterWithoutAnimation && !this.isFloatBarShowWithoutAnimation) {
                    if (this.additionFilters !== null) {
                        this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + m1 + v1;
                    } else {
                        this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + v1;
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
                            let componentCall = new a3(this, {
                                colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[rowIndex] : [],
                                filterRow: filter,
                                onItemClick: (m3) => {
                                    this.filterItemClick(rowIndex, m3);
                                },
                                rowIndex: rowIndex,
                                filterAccessibilityText: this.filterAccessibilityText,
                            }, undefined, elmtId, () => {
                            }, { page: 'library/src/main/ets/components/filter.ets', line: 1183, q5: 9 });
                            ViewPU.create(componentCall);
                            let paramsLambda = () => {
                                return {
                                    colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                    fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                    backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] :
                                        [],
                                    isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] :
                                        [],
                                    isSelectedRow: this.isSelectedArr ? this.isSelectedArr[rowIndex] : [],
                                    filterRow: filter,
                                    onItemClick: (l3) => {
                                        this.filterItemClick(rowIndex, l3);
                                    },
                                    rowIndex: rowIndex,
                                    filterAccessibilityText: this.filterAccessibilityText
                                };
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                        } else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {
                                colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[rowIndex] : [],
                                filterAccessibilityText: this.filterAccessibilityText
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
            Column.width(f2);
            Column.onAreaChange((k3, newValue) => {
                if (this.additionFilters !== null) {
                    this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + m1 + v1;
                } else {
                    this.filterDynamicHeight = parseInt(newValue.height.toString(), 0) + v1;
                }
                if (!this.isFloatBarShowWithoutAnimation && !this.isFloatShowAllFilterWithoutAnimation) {
                    this.floatFilterPosition = -this.filterDynamicHeight;
                }
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            ForEach.create();
            const forEachItemGenFunction = (_item, rowIndex) => {
                const h3 = _item;
                {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        if (isInitialRender) {
                            let componentCall = new b3(this, {
                                colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
                                arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[rowIndex] :
                                    new u2(false),
                                twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[rowIndex] :
                                    new v2(0),
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[rowIndex] : [],
                                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
                                this.twoLineModeItemNumRecord[rowIndex] :
                                    new v2(0),
                                isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[rowIndex] :
                                    new u2(false),
                                filterRow: h3,
                                onItemClick: (j3) => {
                                    this.filterItemClick(rowIndex, j3);
                                },
                                rowIndex: rowIndex,
                                fontSizeScale: this.fontSizeScale,
                                filterId: this.filterId,
                                filterAccessibilityText: this.filterAccessibilityText,
                            }, undefined, elmtId, () => {
                            }, { page: 'library/src/main/ets/components/filter.ets', line: 1215, q5: 9 });
                            ViewPU.create(componentCall);
                            let paramsLambda = () => {
                                return {
                                    colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                    fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                    backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] :
                                        [],
                                    isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] :
                                        [],
                                    arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[rowIndex] :
                                        new u2(false),
                                    twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[rowIndex] :
                                        new v2(0),
                                    isSelectedRow: this.isSelectedArr ? this.isSelectedArr[rowIndex] : [],
                                    twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
                                    this.twoLineModeItemNumRecord[rowIndex] :
                                        new v2(0),
                                    isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[rowIndex] :
                                        new u2(false),
                                    filterRow: h3,
                                    onItemClick: (i3) => {
                                        this.filterItemClick(rowIndex, i3);
                                    },
                                    rowIndex: rowIndex,
                                    fontSizeScale: this.fontSizeScale,
                                    filterId: this.filterId,
                                    filterAccessibilityText: this.filterAccessibilityText
                                };
                            };
                            componentCall.paramsGenerator_ = paramsLambda;
                        } else {
                            this.updateStateVarsOfChildByElmtId(elmtId, {
                                colorRow: this.colorArr ? this.colorArr[rowIndex] : [],
                                fontWeightRow: this.fontWeightArr ? this.fontWeightArr[rowIndex] : [],
                                backgroundColorRow: this.backgroundColorArr ? this.backgroundColorArr[rowIndex] : [],
                                isBackgroundHoverRow: this.isBackgroundHover ? this.isBackgroundHover[rowIndex] : [],
                                arrowShowStateRow: this.downArrowShowState ? this.downArrowShowState[rowIndex] :
                                    new u2(false),
                                twoLineModeItemNumRow: this.twoLineModeItemNum ? this.twoLineModeItemNum[rowIndex] :
                                    new v2(0),
                                isSelectedRow: this.isSelectedArr ? this.isSelectedArr[rowIndex] : [],
                                twoLineModeItemNumRecordRow: this.twoLineModeItemNumRecord ?
                                this.twoLineModeItemNumRecord[rowIndex] :
                                    new v2(0),
                                isArrowIconDown: this.isArrowIconDownArr ? this.isArrowIconDownArr[rowIndex] :
                                    new u2(false),
                                fontSizeScale: this.fontSizeScale,
                                filterAccessibilityText: this.filterAccessibilityText
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
        let f3 = this.multiFilters.length;
        if (this.selectedFilters && this.selectedFilters[f3].index !== index) {
            if (this.selectedFilters[f3].index === -1) {
                this.additionColorArr && (this.additionColorArr[index] = {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_text_primary_activated'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                });
                this.additionFontWeightArr && (this.additionFontWeightArr[index] = FontWeight.Medium);
                this.selectedFilters[f3].value = this.additionFilters ? this.additionFilters.options[index] : '';
                this.selectedFilters[f3].index = index;
                this.additionFiltersSelectedIndex = index;
            } else {
                let g3 = this.selectedFilters[f3].index;
                this.additionColorArr && (this.additionColorArr[g3] = {
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
                this.additionFontWeightArr && (this.additionFontWeightArr[g3] = FontWeight.Regular);
                this.additionFontWeightArr && (this.additionFontWeightArr[index] = FontWeight.Medium);
                this.selectedFilters && (this.selectedFilters[f3].value = this.additionFilters ?
                this.additionFilters.options[index] : '');
                this.selectedFilters && (this.selectedFilters[f3].index = index);
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
            this.selectedFilters && (this.selectedFilters[f3].value = '');
            this.selectedFilters && (this.selectedFilters[f3].index = -1);
            this.additionFiltersSelectedIndex = -1;
        }
        if (this.selectedFilters) {
            this.onFilterChanged && this.onFilterChanged(this.selectedFilters);
        }
        this.colorRefresh = !this.colorRefresh;
        this.refreshFloatFilterBarText();
    }

    getSelected(index) {
        let e3 = this.multiFilters.length;
        if (this.selectedFilters && this.selectedFilters[e3].index !== index) {
            return false;
        } else {
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
                        List.width(f2);
                        List.height(m1);
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
                            ListItem.height(f2);
                            ListItem.margin({ start: LengthMetrics.vp(-l1) });
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
                                Text.maxFontScale(Math.min(this.updateFontScale(), m2));
                                Text.fontColor({
                                    'id': -1,
                                    'type': 10001,
                                    params: ['sys.color.ohos_id_color_text_secondary'],
                                    'bundleName': '__harDefaultBundleName__',
                                    'moduleName': '__harDefaultModuleName__'
                                });
                                Text.margin({ start: LengthMetrics.vp(l1), end: LengthMetrics.vp(l1) });
                                Text.padding({
                                    start: LengthMetrics.resource({
                                        'id': -1,
                                        'type': 10002,
                                        params: ['sys.float.ohos_id_max_padding_start'],
                                        'bundleName': '__harDefaultBundleName__',
                                        'moduleName': '__harDefaultModuleName__'
                                    })
                                });
                                Text.id(`filterAdditionFiltersName_${this.filterId}`);
                            }, Text);
                            Text.pop();
                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                Row.create();
                                Row.width(a2);
                                Row.height(z1);
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
                                        this.additionFiltersSelectedIndex === index, o2.ACCESSIBILITY_TEXT));
                                    ListItem.accessibilityDescription(this.getAccessibilityText(option,
                                        this.additionFiltersSelectedIndex === index, o2.ACCESSIBILITY_DESC));
                                    ListItem.height(f2);
                                    ListItem.backgroundColor(this.isAdditionBackgroundHover &&
                                    this.isAdditionBackgroundHover[index] ?
                                        this.additionBackgroundColorArr ? this.additionBackgroundColorArr[index] : '' :
                                        j2);
                                    ListItem.onHover((isHover) => {
                                        Context.animateTo({
                                            curve: i2,
                                            duration: t1
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
                                                curve: g2,
                                                duration: u1
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
                                                curve: g2,
                                                duration: u1
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
                                        width: d2,
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
                                        start: LengthMetrics.vp(l1 - d2),
                                        end: LengthMetrics.vp(l1 - d2)
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
                                    ListItem.padding({ start: LengthMetrics.vp(l1), end: LengthMetrics.vp(l1) });
                                    ViewStackProcessor.visualState();
                                    ListItem.onClick(() => {
                                        this.additionItemClick(index);
                                        this.sendAccessibility(option, this.getSelected(index));
                                    });
                                    ListItem.tabIndex(index === 0 ? 1 : -1);
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
                                        Text.maxFontScale(Math.min(this.updateFontScale(), m2));
                                        Text.fontColor(this.additionColorArr ? this.additionColorArr[index] : '');
                                        Text.fontWeight(this.additionFontWeightArr ? this.additionFontWeightArr[index] :
                                            '');
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
                                let componentCall = new z2(this, {
                                    x0: 0,
                                    y0: m1 / 2,
                                    x1: l2,
                                    y1: m1 / 2
                                }, undefined, elmtId, () => {
                                }, { page: 'library/src/main/ets/components/filter.ets', line: 1400, q5: 11 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        x0: 0,
                                        y0: m1 / 2,
                                        x1: l2,
                                        y1: m1 / 2
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
                                let componentCall = new z2(this, {
                                    x0: l2,
                                    y0: m1 / 2,
                                    x1: 0,
                                    y1: m1 / 2
                                }, undefined, elmtId, () => {
                                }, { page: 'library/src/main/ets/components/filter.ets', line: 1408, q5: 9 });
                                ViewPU.create(componentCall);
                                let paramsLambda = () => {
                                    return {
                                        x0: l2,
                                        y0: m1 / 2,
                                        x1: 0,
                                        y1: m1 / 2
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
            Column.padding({ top: v1 });
            Column.onVisibleAreaChange([0.0, 1.0], (d3, currentRatio) => {
                if (currentRatio > 0) {
                    this.isFloatShowAllFilter = false;
                    this.isFloatShowAllFilterWithoutAnimation = false;
                    this.isFloatBarShowWithoutAnimation = false;
                    Context.animateTo({
                        curve: h2,
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
                        curve: h2
                    }, () => {
                        this.floatFilterBarPosition = 0;
                        this.floatFilterBarHeight = m1 + v1;
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
            Column.padding({ top: v1 });
            Column.width(f2);
            Column.constraintSize({ maxHeight: '80%' });
            Column.clip(true);
            Column.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Column.opacity(b2);
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
            Row.width(f2);
            Row.height(this.floatFilterBarHeight);
            Row.padding({ start: LengthMetrics.vp(d2), end: LengthMetrics.vp(d2) });
            Row.backgroundColor({
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_background'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            Row.opacity(b2);
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
                o2.ACCESSIBILITY_TEXT));
            Column.accessibilityDescription(this.getFloatAccessibilityText(this.floatFilterBarAccessibilityText,
                o2.ACCESSIBILITY_DESC));
            Column.backgroundColor(this.isFloatArrowBgHover ? this.floatArrowBgColor : j2);
            ViewStackProcessor.visualState('focused');
            Column.border({
                radius: {
                    'id': -1,
                    'type': 10002,
                    params: ['sys.float.ohos_id_corner_radius_clicked'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                width: d2,
                color: {
                    'id': -1,
                    'type': 10001,
                    params: ['sys.color.ohos_id_color_focused_outline'],
                    'bundleName': '__harDefaultBundleName__',
                    'moduleName': '__harDefaultModuleName__'
                },
                style: BorderStyle.Solid
            });
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
            ViewStackProcessor.visualState();
            Column.alignItems(HorizontalAlign.Center);
            Column.width(f2);
            Column.height(m1);
            Column.onTouch((event) => {
                if (event.type === TouchType.Down) {
                    Context.animateTo({
                        curve: g2,
                        duration: u1
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
                        curve: g2,
                        duration: u1
                    }, () => {
                        this.isFloatArrowBgHover = false;
                    });
                }
            });
            Column.onClick(() => {
                Context.animateTo({
                    duration: q1,
                    curve: g2
                }, () => {
                    this.isFloatBarShow = false;
                    this.isFloatBarShowWithoutAnimation = false;
                });
                this.isFloatShowAllFilter = true;
                this.isFloatShowAllFilterWithoutAnimation = true;
                Context.animateTo({
                    curve: h2,
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
                        curve: i2,
                        duration: t1
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
                        curve: i2,
                        duration: t1
                    }, () => {
                        this.isFloatArrowBgHover = false;
                    });
                }
            });
        }, Column);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height(f2);
            Row.alignItems(VerticalAlign.Center);
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.height(m1);
            Row.margin({ start: LengthMetrics.vp(w1) });
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
            Text.maxFontScale(Math.min(this.updateFontScale(), m2));
            Text.constraintSize({ maxWidth: '85%' });
            Text.maxLines(1);
        }, Text);
        Text.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            SymbolGlyph.create({
                'id': -1,
                'type': 40000,
                params: ['sys.symbol.chevron_down'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            });
            SymbolGlyph.fontSize(`${(this.fontSizeScale ?? b1) * t}vp`);
            SymbolGlyph.fontColor([{
                'id': -1,
                'type': 10001,
                params: ['sys.color.ohos_id_color_text_primary_activated'],
                'bundleName': '__harDefaultBundleName__',
                'moduleName': '__harDefaultModuleName__'
            }]);
            SymbolGlyph.focusable(true);
            SymbolGlyph.draggable(false);
        }, SymbolGlyph);
        Row.pop();
        Row.pop();
        Column.pop();
        Row.pop();
    }

    initialRender() {
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
            List.width(f2);
            List.height(f2);
            List.edgeEffect(EdgeEffect.Spring);
            List.onScroll((c3, scrollState) => {
                if (this.isFloatShowAllFilterWithoutAnimation && scrollState === ScrollState.Scroll) {
                    this.isFloatBarShowWithoutAnimation = true;
                    this.isFloatShowAllFilterWithoutAnimation = false;
                    Context.animateTo({
                        duration: q1,
                        curve: g2
                    }, () => {
                        this.isFloatBarShow = true;
                    });
                    Context.animateTo({
                        curve: h2,
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
    }

    rerender() {
        this.updateDirtyElements();
    }
}

export default {
    Filter, FilterType
};