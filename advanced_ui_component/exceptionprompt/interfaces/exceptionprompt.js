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
const DEFAULT_HEIGHT = 48;
const FIT_HEIGHT = 58;
const ZINDEX_NUM = 999;

export var HardwareStatus;
!function(e){
    e[e.ON=0] = "ON";
    e[e.OFF=1] = "OFF"
}(HardwareStatus || (HardwareStatus = {}));

export var MarginType;
!function(e){
    e[e.DEFAULT_MARGIN=0] = "DEFAULT_MARGIN";
    e[e.FIT_MARGIN=1] = "FIT_MARGIN"
}(MarginType || (MarginType = {}));

export var PromptType;
!function(e){
    e[e.DEFAULT_HIDE=0] = "DEFAULT_HIDE";
    e[e.NETWORK_NOT_CONNECTED=1] = "NETWORK_NOT_CONNECTED";
    e[e.NETWORK_CONNECTED_UNSTABLE=2] = "NETWORK_CONNECTED_UNSTABLE";
    e[e.UNSTABLE_CONNECT_SERVER=3] = "UNSTABLE_CONNECT_SERVER";
    e[e.CUSTOM_NETWORK_TIPS=4] = "CUSTOM_NETWORK_TIPS";
    e[e.CUSTOM_TIPS=5] = "CUSTOM_TIPS"
}(PromptType || (PromptType = {}));

export class ExceptionPrompt extends ViewPU {
    constructor(e, t, o, s = -1) {
        super(e, o, s);
        this.__type = new SynchedPropertySimpleOneWayPU(t.type, this, "type");
        this.__options = new SynchedPropertyObjectOneWayPU(t.options, this, "options");
        this.__isShowStatus = new ObservedPropertySimplePU(!1, this, "isShowStatus");
        this.__isState = new ObservedPropertySimplePU(!1, this, "isState");
        this.tipText = "";
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
            networkConnected: {
                id: -1,
                type: 10003,
                params: ["sys.string.ohos_lab_send_messages"],
                bundleName: "",
                moduleName: ""
            },
            networkConnectedUnstable: {
                id: -1,
                type: 10003,
                params: ["sys.string.ohos_desc_access_biometric"],
                bundleName: "",
                moduleName: ""
            },
            unstableConnectServer: {
                id: -1,
                type: 10003,
                params: ["sys.string.ohos_lab_write_audio"],
                bundleName: "",
                moduleName: ""
            },
            customNetwork: {
                id: -1,
                type: 10003,
                params: ["sys.string.ohos_lab_read_call_log"],
                bundleName: "",
                moduleName: ""
            },
            customTips: {
                id: -1,
                type: 10003,
                params: ["sys.string.ohos_lab_write_call_log"],
                bundleName: "",
                moduleName: ""
            }
        }, this, "errorDefaultObj");
        this.onReconnectionCallback = () => {
        };
        this.onConfigureCallback = () => {
        };
        this.setInitiallyProvidedValue(t);
        this.declareWatch("type", this.typeStatusChange)
    }

    setInitiallyProvidedValue(e) {
        void 0 !== e.isShowStatus && (this.isShowStatus = e.isShowStatus);
        void 0 !== e.isState && (this.isState = e.isState);
        void 0 !== e.tipText && (this.tipText = e.tipText);
        void 0 !== e.touchBackgroundColor && (this.touchBackgroundColor = e.touchBackgroundColor);
        void 0 !== e.setNetwork && (this.setNetwork = e.setNetwork);
        void 0 !== e.errorDefaultObj && (this.errorDefaultObj = e.errorDefaultObj);
        void 0 !== e.onReconnectionCallback && (this.onReconnectionCallback = e.onReconnectionCallback);
        void 0 !== e.onConfigureCallback && (this.onConfigureCallback = e.onConfigureCallback)
    }

    updateStateVars(e) {
        this.__type.reset(e.type);
        this.__options.reset(e.options)
    }

    purgeVariableDependenciesOnElmtId(e) {
        this.__type.purgeDependencyOnElmtId(e);
        this.__options.purgeDependencyOnElmtId(e);
        this.__isShowStatus.purgeDependencyOnElmtId(e);
        this.__isState.purgeDependencyOnElmtId(e);
        this.__errorDefaultObj.purgeDependencyOnElmtId(e)
    }

    aboutToBeDeleted() {
        this.__type.aboutToBeDeleted();
        this.__options.aboutToBeDeleted();
        this.__isShowStatus.aboutToBeDeleted();
        this.__isState.aboutToBeDeleted();
        this.__errorDefaultObj.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get type() {
        return this.__type.get()
    }

    set type(e) {
        this.__type.set(e)
    }

    get options() {
        return this.__options.get()
    }

    set options(e) {
        this.__options.set(e)
    }

    get isShowStatus() {
        return this.__isShowStatus.get()
    }

    set isShowStatus(e) {
        this.__isShowStatus.set(e)
    }

    get isState() {
        return this.__isState.get()
    }

    set isState(e) {
        this.__isState.set(e)
    }

    get errorDefaultObj() {
        return this.__errorDefaultObj.get()
    }

    set errorDefaultObj(e) {
        this.__errorDefaultObj.set(e)
    }

    setText() {
        this.type === PromptType.NETWORK_NOT_CONNECTED && (this.tipText = this.errorDefaultObj.networkConnected);
        this.type === PromptType.NETWORK_CONNECTED_UNSTABLE && (this.tipText = this.errorDefaultObj.networkConnectedUnstable);
        this.type === PromptType.UNSTABLE_CONNECT_SERVER && (this.tipText = this.errorDefaultObj.unstableConnectServer);
        this.type === PromptType.CUSTOM_NETWORK_TIPS && (this.tipText = this.options.networkTip || this.errorDefaultObj.customNetwork);
        this.type === PromptType.CUSTOM_TIPS && (this.tipText = this.options.tip || this.errorDefaultObj.customTips)
    }

    typeStatusChange(e) {
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
                    this.setText();
                    this.isShowStatus = !0
                }), 250)
            } else {
                this.setText();
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
            this.setText()
        }
        this.type !== PromptType.NETWORK_NOT_CONNECTED && this.type !== PromptType.NETWORK_CONNECTED_UNSTABLE || (this.isState = !0)
    }

    isOneColum() {
        return this.type === PromptType.UNSTABLE_CONNECT_SERVER || this.type === PromptType.CUSTOM_NETWORK_TIPS
    }

    FirstBuilder(e = null) {
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
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
            t || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Column.pop()
    }

    SecondBuilder(e = null) {
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
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
            t || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Column.pop()
    }

    TextBuilder(e = null) {
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
            Flex.padding({ left: 12, right: 4 });
            Flex.position({});
            Flex.zIndex(999);
            Flex.width("100%");
            Flex.height("100%");
            t || Flex.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.isShowStatus ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Flex.create({ alignItems: ItemAlign.Center });
                    Flex.width("100%");
                    Flex.height("100%");
                    Flex.onClick((() => {
                        this.options.hardwareStatus === HardwareStatus.ON && this.onReconnectionCallback()
                    }));
                    t || Flex.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    var o;
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Image.create(null !== (o = this.options.icon) && void 0 !== o ? o : {
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
                    t || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
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
                    t || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                Flex.pop()
            })) : If.branchId(1);
            t || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.isState ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
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
                    Button.onTouch((e => {
                        this.onConfigureCallback();
                            e.type === TouchType.Down ? this.touchBackgroundColor = {
                            id: -1,
                            type: 10001,
                            params: ["sys.color.ohos_id_color_click_effect"],
                            bundleName: "",
                            moduleName: ""
                        } : e.type === TouchType.Up && (this.touchBackgroundColor = {
                            id: -1,
                            type: 10001,
                            params: ["sys.color.ohos_id_color_sub_background_transparent"],
                            bundleName: "",
                            moduleName: ""
                        })
                    }));
                    t || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Row.create();
                    t || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
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
                    t || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
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
                    t || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Row.pop();
                Button.pop()
            })) : If.branchId(1);
            t || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Flex.pop()
    }

    initialRender() {
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Column.create();
            Column.width("100%");
            Column.height(this.isOneColum() ? 48 : 58);
            Column.position({ y: 80 });
            Column.zIndex(999);
            t || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Stack.create();
            Stack.padding(this.options.marginState === MarginType.DEFAULT_MARGIN ? {
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
            t || Stack.pop();
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