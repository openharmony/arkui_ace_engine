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
export var QrCodeState;
(function (QrCodeState) {
    QrCodeState[QrCodeState["QRCODE_NORMAL"] = 0] = "QRCODE_NORMAL";
    QrCodeState[QrCodeState["QRCODE_EXPIRE"] = 1] = "QRCODE_EXPIRE";
    QrCodeState[QrCodeState["QRCODE_LOADING"] = 2] = "QRCODE_LOADING";
})(QrCodeState || (QrCodeState = {}));
var ConfigData;
(function (ConfigData) {
    ConfigData[ConfigData["FIVE_HUNDRED"] = 500] = "FIVE_HUNDRED";
    ConfigData[ConfigData["DEFAULT_OPACITY"] = 0.4] = "DEFAULT_OPACITY";
    ConfigData[ConfigData["DEFAULT_TIMES"] = 200] = "DEFAULT_TIMES";
})(ConfigData || (ConfigData = {}));
var ConfigDataString;
(function (ConfigDataString) {
    ConfigDataString["TIPS"] = "\u4E8C\u7EF4\u7801\u5DF2\u5931\u6548\uFF0C\u8BF7\u5237\u65B0";
    ConfigDataString["ANIMATION_CURVE"] = "0.33,0,0.67,1";
    ConfigDataString["ONE_HUNDRED_TWENTY_FIVE_VP"] = "125vp";
    ConfigDataString["ONE_HUNDRED_ONE_VP"] = "101vp";
    ConfigDataString["TWENTY_EIGHT_VP"] = "28vp";
    ConfigDataString["THIRTY_FOUR_VP"] = "34vp";
    ConfigDataString["ELEVEN_FP"] = "11fp";
    ConfigDataString["SIX_VP"] = "6vp";
})(ConfigDataString || (ConfigDataString = {}));
export class QrcodeOptions {
    constructor(options) {
        this.edgeLength = options.edgeLength ?? ConfigDataString.ONE_HUNDRED_TWENTY_FIVE_VP;
        this.color = options.color ?? Color.Black;
        this.backgroundColor = options.backgroundColor ?? Color.White;
        this.textColor = options.textColor ?? Color.White;
        this.textContent = options.textContent ?? ConfigDataString.TIPS;
        this.borderRadius = options.borderRadius ?? $r('sys.float.ohos_id_corner_radius_default_s');
        this.opacity = options.opacity ?? ConfigData.DEFAULT_OPACITY;
        this.animationCurve = options.animationCurve ?? ConfigDataString.ANIMATION_CURVE;
        this.animationTime = options.animationTime ?? ConfigData.DEFAULT_TIMES;
        this.qrCodeLength = options.qrCodeLength ?? ConfigDataString.ONE_HUNDRED_ONE_VP;
        this.expireImageLength = options.expireImageLength ?? ConfigDataString.TWENTY_EIGHT_VP;
        this.textSize = options.textSize ?? ConfigDataString.ELEVEN_FP;
        this.textWeight = options.textWeight ?? FontWeight.Medium;
        this.space = options.space ?? ConfigDataString.SIX_VP;
        this.imageLoadLength = options.imageLoadLength ?? ConfigDataString.THIRTY_FOUR_VP;
    }
}
export class QrCode extends ViewPU {
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
        if (this.options === void 0) {
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
                if (this.state != QrCodeState.QRCODE_LOADING) {
                    return this.state = QrCodeState.QRCODE_LOADING;
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
                            duration: this.options.animationTime,
                            curve: this.options.animationCurve,
                            playMode: PlayMode.Normal
                        });
                        Column.height(this.options.edgeLength);
                        Column.width(this.options.edgeLength);
                        Column.backgroundColor(this.options.backgroundColor);
                        Column.borderRadius(this.options.borderRadius);
                        Column.opacity(this.state != QrCodeState.QRCODE_NORMAL ? this.options.opacity : 1);
                        Context.animation(null);
                        Column.justifyContent(FlexAlign.Center);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        QRCode.create(this.value);
                        QRCode.color(this.options.color);
                        QRCode.backgroundColor(Color.Transparent);
                        QRCode.width(this.options.qrCodeLength);
                        QRCode.height(this.options.qrCodeLength);
                    }, QRCode);
                    QRCode.pop();
                    Column.pop();
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Column.create();
                        Context.animation({
                            duration: this.options.animationTime,
                            curve: this.options.animationCurve,
                            playMode: PlayMode.Normal
                        });
                        Column.visibility(this.state == QrCodeState.QRCODE_NORMAL ? Visibility.None : Visibility.Visible);
                        Context.animation(null);
                    }, Column);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        Image.create($r('sys.media.ohos_qrcode_refresh_icon'));
                        Image.height(this.options.expireImageLength);
                        Image.width(this.options.expireImageLength);
                        Image.visibility(this.state == QrCodeState.QRCODE_EXPIRE ? Visibility.Visible : Visibility.None);
                    }, Image);
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.state == QrCodeState.QRCODE_LOADING) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    LoadingProgress.create();
                                    Context.animation({
                                        duration: this.options.animationTime,
                                        curve: this.options.animationCurve,
                                        playMode: PlayMode.Normal
                                    });
                                    LoadingProgress.color(Color.White);
                                    LoadingProgress.height(this.options.imageLoadLength);
                                    LoadingProgress.width(this.options.imageLoadLength);
                                    LoadingProgress.visibility(this.state == QrCodeState.QRCODE_LOADING ? Visibility.Visible : Visibility.None);
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
                        Text.fontColor(this.options.textColor);
                        Text.fontSize(this.options.textSize);
                        Text.fontWeight(this.options.textWeight);
                        Text.textAlign(TextAlign.Center);
                        Text.width(this.options.qrCodeLength);
                        Text.visibility(this.state == QrCodeState.QRCODE_EXPIRE ? Visibility.Visible : Visibility.None);
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
//# sourceMappingURL=QrCode.js.map
export default {QrCode,QrcodeOptions,QrCodeState}