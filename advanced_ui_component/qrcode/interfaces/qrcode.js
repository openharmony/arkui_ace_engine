/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
const ColorMetrics = requireNapi('arkui.node').ColorMetrics;
const LengthUnit = requireNapi('arkui.node').LengthUnit;
export var QrcodeState;
(function (QrcodeState) {
    QrcodeState[QrcodeState["NORMAL"] = 0] = "NORMAL";
    QrcodeState[QrcodeState["EXPIRED"] = 1] = "EXPIRED";
    QrcodeState[QrcodeState["LOADING"] = 2] = "LOADING";
})(QrcodeState || (QrcodeState = {}));
class ConfigDataConstants {
}
ConfigDataConstants.TIPS = '二维码已失效，请刷新';
ConfigDataConstants.ANIMATION_CURVE = '0.33,0,0.67,1';
ConfigDataConstants.ONE_HUNDRED_TWENTY_FIVE_VP = 125;
ConfigDataConstants.ONE_HUNDRED_ONE_VP = 101;
ConfigDataConstants.TWENTY_EIGHT_VP = 28;
ConfigDataConstants.THIRTY_FOUR_VP = 34;
ConfigDataConstants.ELEVEN_FP = '11fp';
ConfigDataConstants.SIX_VP = '6vp';
ConfigDataConstants.FIVE_HUNDRED = 500;
ConfigDataConstants.DEFAULT_OPACITY = 0.4;
ConfigDataConstants.DEFAULT_TIMES = 200;
export class QrcodeOptions {
    constructor(options) {
        this.edgeLength = options.edgeLength ?? new LengthMetrics(ConfigDataConstants.ONE_HUNDRED_TWENTY_FIVE_VP, LengthUnit.VP);
        this.color = options.color ?? ColorMetrics.resourceColor(Color.Black);
        this.backgroundColor = options.backgroundColor ?? ColorMetrics.resourceColor(Color.White);
        this.textColor = options.textColor ?? ColorMetrics.resourceColor(Color.White);
        this.textContent = options.textContent ?? ConfigDataConstants.TIPS;
        this.borderRadius = options.borderRadius ?? $r('sys.float.ohos_id_corner_radius_default_s');
        this.opacity = options.opacity ?? ConfigDataConstants.DEFAULT_OPACITY;
        this.animationCurve = options.animationCurve ?? ConfigDataConstants.ANIMATION_CURVE;
        this.animationDuration = options.animationDuration ?? ConfigDataConstants.DEFAULT_TIMES;
        this.qrcodeSideLength = options.qrcodeSideLength ?? new LengthMetrics(ConfigDataConstants.ONE_HUNDRED_ONE_VP, LengthUnit.VP);
        this.expiredImageLength = options.expiredImageLength ?? new LengthMetrics(ConfigDataConstants.TWENTY_EIGHT_VP, LengthUnit.VP);
        this.textSize = options.textSize ?? ConfigDataConstants.ELEVEN_FP;
        this.textWeight = options.textWeight ?? FontWeight.Medium;
        this.space = options.space ?? ConfigDataConstants.SIX_VP;
        this.loadingImageLength = options.loadingImageLength ?? new LengthMetrics(ConfigDataConstants.THIRTY_FOUR_VP, LengthUnit.VP);
    }
}
export class Qrcode extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__options = new SynchedPropertyObjectTwoWayPU(params.options, this, "options");
        this.__value = new SynchedPropertySimpleTwoWayPU(params.value, this, "value");
        this.__state = new SynchedPropertySimpleTwoWayPU(params.state, this, "state");
        this.setInitiallyProvidedValue(params);
        this.declareWatch("options", this.optionsChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__value.purgeDependencyOnElmtId(rmElmtId);
        this.__state.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__value.aboutToBeDeleted();
        this.__state.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get options() {
        return this.__options.get();
    }
    set options(newValue) {
        this.__options.set(newValue);
    }
    get value() {
        return this.__value.get();
    }
    set value(newValue) {
        this.__value.set(newValue);
    }
    get state() {
        return this.__state.get();
    }
    set state(newValue) {
        this.__state.set(newValue);
    }
    //监听组件状态变化
    optionsChange() {
        console.info('optionsChange end');
    }
    aboutToAppear() {
        if (this.options === undefined) {
            return;
        }
        else {
            console.info('aboutToAppear:' + JSON.stringify(this.options));
            this.optionsChange();
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Stack.create();
            Stack.onClick(() => {
                if (this.state != QrcodeState.LOADING) {
                    return this.state = QrcodeState.LOADING;
                }
                else {
                    return this.state;
                }
            });
        }, Stack);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.options !== void 0) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Context.animation({
                            duration: this.options.animationDuration,
                            curve: this.options.animationCurve,
                            playMode: PlayMode.Normal
                        });
                        Column.height(this.options.edgeLength?.value);
                        Column.width(this.options.edgeLength?.value);
                        Column.backgroundColor(this.options.backgroundColor?.color);
                        Column.borderRadius(this.options.borderRadius);
                        Column.opacity(this.state != QrcodeState.NORMAL ? this.options.opacity : 1);
                        Context.animation(null);
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        QRCode.create(this.value);
                        QRCode.color(this.options.color?.color);
                        QRCode.backgroundColor(Color.Transparent);
                        QRCode.width(this.options.qrcodeSideLength?.value);
                        QRCode.height(this.options.qrcodeSideLength?.value);
                    }, QRCode);
                    QRCode.pop();
                    Column.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Context.animation({
                            duration: this.options.animationDuration,
                            curve: this.options.animationCurve,
                            playMode: PlayMode.Normal
                        });
                        Column.visibility(this.state == QrcodeState.NORMAL ? Visibility.None : Visibility.Visible);
                        Context.animation(null);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create($r('sys.media.ohos_qrcode_refresh_icon'));
                        Image.height(this.options.expiredImageLength?.value);
                        Image.width(this.options.expiredImageLength?.value);
                        Image.visibility(this.state == QrcodeState.EXPIRED ? Visibility.Visible : Visibility.None);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.state == QrcodeState.LOADING) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    LoadingProgress.create();
                                    Context.animation({
                                        duration: this.options.animationDuration,
                                        curve: this.options.animationCurve,
                                        playMode: PlayMode.Normal
                                    });
                                    LoadingProgress.color(Color.White);
                                    LoadingProgress.height(this.options.loadingImageLength?.value);
                                    LoadingProgress.width(this.options.loadingImageLength?.value);
                                    LoadingProgress.visibility(this.state == QrcodeState.LOADING ? Visibility.Visible : Visibility.None);
                                    Context.animation(null);
                                }, LoadingProgress);
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(1, () => {
                            });
                        }
                    }, If);
                    If.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Text.create(this.options.textContent);
                        Text.margin({ top: this.options.space });
                        Text.fontColor(this.options.textColor?.color);
                        Text.fontSize(this.options.textSize);
                        Text.fontWeight(this.options.textWeight);
                        Text.textAlign(TextAlign.Center);
                        Text.width(this.options.qrcodeSideLength?.value);
                        Text.visibility(this.state == QrcodeState.EXPIRED ? Visibility.Visible : Visibility.None);
                    }, Text);
                    Text.pop();
                    Column.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Stack.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}
//# sourceMappingURL=Qrcode.js.map
export default {Qrcode,QrcodeOptions,QrcodeState}