/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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
const START_TIME = 250;
const END_TIME = 200;
const HEIGHT = 80;
const BORDER_RADIUS = 12;
const OPACITY_NUM = .18;

export var HardwareStatusType;
!function(t){
    t[t.ON=0] = "ON";
    t[t.OFF=1] = "OFF"
}(HardwareStatusType || (HardwareStatusType = {}));

export var MarginStateType;
!function(t){
    t[t.DEFAULT_MARGIN=0] = "DEFAULT_MARGIN";
    t[t.FIT_MARGIN=1] = "FIT_MARGIN"
}(MarginStateType || (MarginStateType = {}));

export var PromptType;
!function(t){
    t[t.DEFAULT_HIDE=0] = "DEFAULT_HIDE";
    t[t.NETWORK_NOT_CONNECTED=1] = "NETWORK_NOT_CONNECTED";
    t[t.NETWORK_CONNECTED_UNSTABLE=2] = "NETWORK_CONNECTED_UNSTABLE";
    t[t.UNSTABLE_CONNECT_SERVER=3] = "UNSTABLE_CONNECT_SERVER";
    t[t.CUSTOM_NETWORK_TIPS=4] = "CUSTOM_NETWORK_TIPS";
    t[t.CUSTOM_TIPS=5] = "CUSTOM_TIPS"
}(PromptType || (PromptType = {}));

export class ExceptionPrompt extends ViewPU {
    constructor(t, e, o, i = -1) {
        super(t, o, i);
        this.__type = new SynchedPropertySimpleOneWayPU(e.type, this, "type");
        this.__options = new SynchedPropertyObjectOneWayPU(e.options, this, "options");
        this.__isShowStatus = new ObservedPropertySimplePU(!1, this, "isShowStatus");
        this.__isState = new ObservedPropertySimplePU(!1, this, "isState");
        this.__tipText = new ObservedPropertySimplePU("", this, "tipText");
        this.touchBackgroundColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_sub_background_transparent"],
            bundleName: "",
            moduleName: ""
        };
        this.setNetwork = {
            id: -1,
            type: 10003,
            params: ["app.string.test"],
            bundleName: "",
            moduleName: ""
        };
        this.__errorDefaultObj = new ObservedPropertyObjectPU({
            networkConnected: "网络未连接",
            networkConnectedUnstable: "网络连接不稳定，请点击重试",
            unstableConnectServer: "无法连接到服务器，请点击重试",
            customNetworkLeft: "无法获取",
            customNetworkRight: "请点击重试",
            customTips: ""
        }, this, "errorDefaultObj");
        this.onReconnectionFunction = () => {
        };
        this.onConfigureNetworkFunction = () => {
        };
        this.setInitiallyProvidedValue(e);
        this.declareWatch("type", this.typeStatusChange)
    }

    setInitiallyProvidedValue(t) {
        void 0 !== t.isShowStatus && (this.isShowStatus = t.isShowStatus);
        void 0 !== t.isState && (this.isState = t.isState);
        void 0 !== t.tipText && (this.tipText = t.tipText);
        void 0 !== t.touchBackgroundColor && (this.touchBackgroundColor = t.touchBackgroundColor);
        void 0 !== t.setNetwork && (this.setNetwork = t.setNetwork);
        void 0 !== t.errorDefaultObj && (this.errorDefaultObj = t.errorDefaultObj);
        void 0 !== t.onReconnectionFunction && (this.onReconnectionFunction = t.onReconnectionFunction);
        void 0 !== t.onConfigureNetworkFunction && (this.onConfigureNetworkFunction = t.onConfigureNetworkFunction)
    }

    updateStateVars(t) {
        this.__type.reset(t.type);
        this.__options.reset(t.options)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__type.purgeDependencyOnElmtId(t);
        this.__options.purgeDependencyOnElmtId(t);
        this.__isShowStatus.purgeDependencyOnElmtId(t);
        this.__isState.purgeDependencyOnElmtId(t);
        this.__tipText.purgeDependencyOnElmtId(t);
        this.__errorDefaultObj.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__type.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__isShowStatus.aboutToBeDeleted();
        this.__isState.aboutToBeDeleted();
        this.__tipText.aboutToBeDeleted();
        this.__errorDefaultObj.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get type() {
        return this.__type.get()
    }

    set type(t) {
        this.__type.set(t)
    }

    get options() {
        return this.__options.get()
    }

    set options(t) {
        this.__options.set(t)
    }

    get isShowStatus() {
        return this.__isShowStatus.get()
    }

    set isShowStatus(t) {
        this.__isShowStatus.set(t)
    }

    get isState() {
        return this.__isState.get()
    }

    set isState(t) {
        this.__isState.set(t)
    }

    get tipText() {
        return this.__tipText.get()
    }

    set tipText(t) {
        this.__tipText.set(t)
    }

    get errorDefaultObj() {
        return this.__errorDefaultObj.get()
    }

    set errorDefaultObj(t) {
        this.__errorDefaultObj.set(t)
    }

    SetText() {
        this.type === PromptType.NETWORK_NOT_CONNECTED && (this.tipText = `${this.errorDefaultObj.networkConnected}`);
        this.type === PromptType.NETWORK_CONNECTED_UNSTABLE && (this.tipText = `${this.errorDefaultObj.networkConnectedUnstable}`);
        this.type === PromptType.UNSTABLE_CONNECT_SERVER && (this.tipText = `${this.errorDefaultObj.unstableConnectServer}`);
        this.type === PromptType.CUSTOM_NETWORK_TIPS && (this.tipText = `${this.errorDefaultObj.customNetworkLeft}${this.options.networkTip || ""}，${this.errorDefaultObj.customNetworkRight}`);
        this.type === PromptType.CUSTOM_TIPS && (this.tipText = `${this.options.tip}` || `${this.errorDefaultObj.customTips}`)
    }

    typeStatusChange(t) {
        if (this.type !== PromptType.DEFAULT_HIDE) {
            this.isState && this.type !== PromptType.NETWORK_NOT_CONNECTED && this.type !== PromptType.NETWORK_CONNECTED_UNSTABLE && setTimeout((() => {
                this.isState = !1
            }), 200);
            this.type !== PromptType.NETWORK_NOT_CONNECTED && this.type !== PromptType.NETWORK_CONNECTED_UNSTABLE || (this.isShowStatus ? setTimeout((() => {
                this.isState = !0
            }), 250) : this.isState = !0);
            if (this.isShowStatus) {
                this.isShowStatus = !1;
                setTimeout((() => {
                    this.SetText();
                    this.isShowStatus = !0
                }), 250)
            } else {
                this.SetText();
                this.isShowStatus = !0
            }
        } else {
            this.isShowStatus = !1;
            setTimeout((() => {
                this.isState = !1
            }), 250)
        }
    }

    aboutToAppear() {
        if (this.type !== PromptType.DEFAULT_HIDE) {
            this.isShowStatus = !0;
            this.SetText()
        }
        this.type !== PromptType.NETWORK_NOT_CONNECTED && this.type !== PromptType.NETWORK_CONNECTED_UNSTABLE || (this.isState = !0)
    }

    isOneColum() {
        return this.type === PromptType.UNSTABLE_CONNECT_SERVER || this.type === PromptType.CUSTOM_NETWORK_TIPS || JSON.stringify(this.tipText).length < 10
    }

    OptionalMargins() {
        return this.options.marginState === MarginStateType.DEFAULT_MARGIN ? {
                                                                                 left: {
                                                                                     id: -1,
                                                                                     type: 10002,
                                                                                     params: ["sys.float.ohos_id_card_margin_start"],
                                                                                     bundleName: "",
                                                                                     moduleName: ""
                                                                                 },
                                                                                 right: {
                                                                                     id: -1,
                                                                                     type: 10002,
                                                                                     params: ["sys.float.ohos_id_card_margin_end"],
                                                                                     bundleName: "",
                                                                                     moduleName: ""
                                                                                 }
                                                                             } : {
                                                                                     left: {
                                                                                         id: -1,
                                                                                         type: 10002,
                                                                                         params: ["sys.float.ohos_id_max_padding_start"],
                                                                                         bundleName: "",
                                                                                         moduleName: ""
                                                                                     },
                                                                                     right: {
                                                                                         id: -1,
                                                                                         type: 10002,
                                                                                         params: ["sys.float.ohos_id_max_padding_end"],
                                                                                         bundleName: "",
                                                                                         moduleName: ""
                                                                                     }
                                                                                 }
    }

    FirstBuilder(t = null) {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Column.create();
            Column.height("100%");
            Column.width("100%");
            Column.borderRadius(12);
            Column.backgroundColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_background"],
                bundleName: "",
                moduleName: ""
            });
            e || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Column.pop()
    }

    SecondBuilder(t = null) {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Column.create();
            Column.height("100%");
            Column.width("100%");
            Column.borderRadius(12);
            Column.backgroundColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_warning"],
                bundleName: "",
                moduleName: ""
            });
            Column.opacity(.18);
            Column.position({});
            Column.zIndex(999);
            e || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Column.pop()
    }

    TextBuilder(t = null) {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
            Flex.padding({ left: 12, right: 4 });
            Flex.position({});
            Flex.zIndex(999);
            Flex.width("100%");
            Flex.height("100%");
            Flex.onClick((() => {
                this.options.hardwareStatus === HardwareStatusType.ON && this.onReconnectionFunction()
            }));
            e || Flex.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Flex.create({ alignItems: ItemAlign.Center });
            Flex.width("100%");
            Flex.height("100%");
            e || Flex.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Image.create(this.options.icon || {
                id: -1,
                type: 2e4,
                params: ["app.media.ic_public_fail"],
                bundleName: "",
                moduleName: ""
            });
            Image.width("24vp");
            Image.height("24vp");
            Image.objectFit(ImageFit.Contain);
            Image.fillColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_warning"],
                bundleName: "",
                moduleName: ""
            });
            e || Image.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Text.create(this.tipText);
            Text.fontSize({
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_text_size_body1"],
                bundleName: "",
                moduleName: ""
            });
            Text.fontColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_warning"],
                bundleName: "",
                moduleName: ""
            });
            Text.textOverflow({ overflow: TextOverflow.Ellipsis });
            Text.maxLines(2);
            Text.margin({ left: 16, right: 16 });
            e || Text.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Flex.pop();
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            this.isState ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Button.createWithChild({ stateEffect: !0, type: ButtonType.Normal });
                    Button.backgroundColor(this.touchBackgroundColor);
                    Button.width(this.isState ? 120 : 0);
                    Button.height(32);
                    Button.borderRadius({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_corner_radius_subtab"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Button.padding({ right: 8, left: 8 });
                    Button.onTouch((t => {
                            t.type === TouchType.Down ? this.touchBackgroundColor = {
                            id: -1,
                            type: 10001,
                            params: ["sys.color.ohos_id_color_click_effect"],
                            bundleName: "",
                            moduleName: ""
                        } : t.type === TouchType.Up && (this.touchBackgroundColor = {
                            id: -1,
                            type: 10001,
                            params: ["sys.color.ohos_id_color_sub_background_transparent"],
                            bundleName: "",
                            moduleName: ""
                        })
                    }));
                    Button.onClick((() => {
                        this.onConfigureNetworkFunction()
                    }));
                    e || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Row.create();
                    e || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Text.create(this.setNetwork);
                    Text.fontSize({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_text_size_body2"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.fontColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_text_secondary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Text.maxLines(1);
                    Text.padding(0);
                    Text.margin({ right: 4 });
                    Text.textAlign(TextAlign.End);
                    e || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["app.media.ic_public_arrow_right"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Image.width("12vp");
                    Image.height("24vp");
                    Image.fillColor({
                        id: -1,
                        type: 10001,
                        params: ["sys.color.ohos_id_color_tertiary"],
                        bundleName: "",
                        moduleName: ""
                    });
                    e || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Row.pop();
                Button.pop()
            })) : If.branchId(1);
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Flex.pop()
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Column.create();
            Column.width("100%");
            Column.height(this.isOneColum() ? 48 : 58);
            Column.position({ y: 80 });
            Column.zIndex(999);
            e || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Stack.create();
            Stack.padding(this.options.marginState === MarginStateType.DEFAULT_MARGIN ? {
                                                                                            left: {
                                                                                                id: -1,
                                                                                                type: 10002,
                                                                                                params: ["sys.float.ohos_id_card_margin_start"],
                                                                                                bundleName: "",
                                                                                                moduleName: ""
                                                                                            },
                                                                                            right: {
                                                                                                id: -1,
                                                                                                type: 10002,
                                                                                                params: ["sys.float.ohos_id_card_margin_end"],
                                                                                                bundleName: "",
                                                                                                moduleName: ""
                                                                                            }
                                                                                        } : {
                                                                                                left: {
                                                                                                    id: -1,
                                                                                                    type: 10002,
                                                                                                    params: ["sys.float.ohos_id_max_padding_start"],
                                                                                                    bundleName: "",
                                                                                                    moduleName: ""
                                                                                                },
                                                                                                right: {
                                                                                                    id: -1,
                                                                                                    type: 10002,
                                                                                                    params: ["sys.float.ohos_id_max_padding_end"],
                                                                                                    bundleName: "",
                                                                                                    moduleName: ""
                                                                                                }
                                                                                            });
            Stack.transition(TransitionEffect.OPACITY.animation({ duration: this.isShowStatus ? 250 : 200 }));
            Stack.visibility(this.isShowStatus ? Visibility.Visible : Visibility.None);
            e || Stack.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.FirstBuilder.bind(this)();
        this.SecondBuilder.bind(this)();
        this.TextBuilder.bind(this)();
        Stack.pop();
        Column.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}