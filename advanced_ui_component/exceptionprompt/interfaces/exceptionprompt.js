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
const PUBLIC_TIPS = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAAXNSR0IArs4c6QAAA7ZJREFUSEu1VU1oXFUU/s6dSVK1xUlnbmKsKdZCJRFrmZmX5r20ZSIopf51U4pZ6EKlqIgLsViQIioiiuJC8G/ThWJXNSpR/Fm0tJM7mbmv01JMMVASm4AkM2ltK9XMzHtH32RmMOmbl2y82/ud853znXu/Q/ifDwXln0yl1qy79vd+JtoP4G4AdwBwAJom8FmAvoiubR2h48crzfL4EnAqFZ7/c+EAA68DWA9gkgDbJb4gWDgM3gTgHgBbAcwAOBjT6igBvJzoBoJCYmcXqDIMYBsDn7mMT26z1Tm/CucNo9tFyyEwPwtgRITcoejY2NX/YpcQzCaszYI4DUAw0YMdudEzqxnRnGHuJsZXAKZaFkJW5Nypy/W4BsGlROJWB605ELVDVAZkNjuxmuR1zKxhWoLxMwH56PUrgzQ+XvLuGgTFpPUmgw8RYMa0yi5PPm2aN60p0xmAW2Jr27b4DbaYtB5j8DCYX5J25v0GwR/37mgvtzkXGTjSodULfpXPGjvuEuxc8O4qYd7UlclM+eEKSfN7AANoExtkOn2t2kHBsJ4B86eCKhujudy0X2CtiEveXYhLkfW2fcV38MntD7gQPwIYklp9uUiwyNoutepvpjsDVEya3nt3pVYtTXH79oWKkzPzAL6TWg3VCX77t62fpFZPBw12LmkWieDInOoMwhUM81swNkqt7qsTlAj0TkyPvhoYmDAn4BFo1ROEKybMD5jwlNRqXZ3gLzA+lLZ6ObADo18RqCxzalcgLmG+RYQXpVa31AisXwG2Pc0CO0j2j8Aj0GpvMM46Cua4tNWW2iuqahaXWm0I7sDczQ6487T6YQWJJplwXmq1py7RAQAfQwhDZtO6WXAxaT4PZjdmZz5qijEsg5mzxPych6sSXO3riy64oRmAh6XOPO770eLbtwohzlZ/p8u9sdOZ8364uYR5jAh7Kk64uyt/stCwikLSeg3gwyAMypw6sTz48rZUpBJe8PypLEJuz3LXXPxP/Y8C9DUIb8icOrzEi6peU2IFojuZKLVaJ60XUrOSvOeoZS6Zt9v29SUE1QoWd4ECEHHBD3XqjGfdK55i3LqfBX9e3XYc7pP2yd/rQTcsnNo8jgHYBeL3XMHvdo6NzfrqHR/YSSH3IBgPe1sv7NBge37Uc4XG8V+ZgCgY1pMEfhuMDgB5MI0TYYqBCpgJVE0ar8rAdMQJO6/4FRK49Lm3t3Xu5sgjAngCzD0gdHvbDsBFgCeI6BRBfBPNpX9ppmMgwYrirwLwDyWbkigJz8KuAAAAAElFTkSuQmCC";
const RIGHT_ICON = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAAXNSR0IArs4c6QAAAR1JREFUSEvt1E9Kw1AQBvBvxgpexIUbN7pRiHgDKYFuBaWW0jaXiQmxWXgAE72BxVJPIf5ZiAgKQheC6MuUtxCCCzMPkl2zHr4ffJN5hIY/ajgfS6CyYVVF2Vl8WLCZdrqjx8rEPwMqIB9HdwDW2LDX7vefXBAVkCXJOrG5BfAFMjt+N3jWIirAhl2m0YaIzACag4ynRdSARbI03iSRKYAPLeIEWOQqjbcKkQmAd/ON3c5g8PpfXc6ADcuT0z0w3UDk3O8Nj2oHLtJwn4UngIT+yTCoFciScJuYryF4a7UK7+B49FIb0OiSS7/pp8stqJZcPjTXa1YB+Th6ALDqGm53owLsY7eCn1m7F9xrn4jfORXgGlqeXwKV7TVe0QK81HAZuzhflQAAAABJRU5ErkJggg==";
const DURATION = 230;

export var HardwareStatusType;
!function(e){
    e[e.on=1] = "on";
    e[e.off=0] = "off"
}(HardwareStatusType || (HardwareStatusType = {}));

export var TypeEnum;
!function(e){
    e[e.DEFAULT_HIDE=0] = "DEFAULT_HIDE";
    e[e.NETWORK_NOT_CONNECTED=1] = "NETWORK_NOT_CONNECTED";
    e[e.NETWORK_CONNECTED_UNSTABLE=2] = "NETWORK_CONNECTED_UNSTABLE";
    e[e.UNSTABLE_CONNECT_SERVER=3] = "UNSTABLE_CONNECT_SERVER";
    e[e.CUSTOM_NETWORK_TIPS=4] = "CUSTOM_NETWORK_TIPS";
    e[e.CUSTOM_TIPS=5] = "CUSTOM_TIPS"
}(TypeEnum || (TypeEnum = {}));

export class ExceptionPrompt extends ViewPU {
    constructor(e, t, o, s = -1) {
        super(e, o, s);
        this.__Type = new SynchedPropertySimpleTwoWayPU(t.Type, this, "Type");
        this.__Options = new SynchedPropertyObjectTwoWayPU(t.Options, this, "Options");
        this.__ShowStatus = new ObservedPropertySimplePU(!1, this, "ShowStatus");
        this.__ThemeColorStatus = new ObservedPropertySimplePU(!0, this, "ThemeColorStatus");
        this.__OpacityNum = new ObservedPropertySimplePU(.15, this, "OpacityNum");
        this.__HEIGHT = new ObservedPropertySimplePU(80, this, "HEIGHT");
        this.__BORDER_RADIUS = new ObservedPropertySimplePU(12, this, "BORDER_RADIUS");
        this.__DURATION = new ObservedPropertySimplePU(1500, this, "DURATION");
        this.__BG_OPACITY = new ObservedPropertySimplePU(1, this, "BG_OPACITY");
        this.__state = new ObservedPropertySimplePU(!1, this, "state");
        this.__text = new ObservedPropertySimplePU("", this, "text");
        this.__ErrorDefaultObj = new ObservedPropertyObjectPU({
            NETWORK_NOT_CONNECTED: "网络未连接",
            NETWORK_CONNECTED_UNSTABLE: "网络连接不稳定，请点击重试",
            UNSTABLE_CONNECT_SERVER: "无法连接到服务器，请点击重试",
            CUSTOM_NETWORK_TIPS: "无法获取xxx，请点击重试",
            CUSTOM_TIPS: "自定义提示内容"
        }, this, "ErrorDefaultObj");
        this.ReconnectionFunction = () => {
        };
        this.ConfigureNetworkFunction = () => {
        };
        this.setInitiallyProvidedValue(t);
        this.declareWatch("Type", this.TypeStatusChange);
        this.declareWatch("ThemeColorStatus", this.OpacityStatusChange)
    }

    setInitiallyProvidedValue(e) {
        void 0 !== e.ShowStatus && (this.ShowStatus = e.ShowStatus);
        void 0 !== e.ThemeColorStatus && (this.ThemeColorStatus = e.ThemeColorStatus);
        void 0 !== e.OpacityNum && (this.OpacityNum = e.OpacityNum);
        void 0 !== e.HEIGHT && (this.HEIGHT = e.HEIGHT);
        void 0 !== e.BORDER_RADIUS && (this.BORDER_RADIUS = e.BORDER_RADIUS);
        void 0 !== e.DURATION && (this.DURATION = e.DURATION);
        void 0 !== e.BG_OPACITY && (this.BG_OPACITY = e.BG_OPACITY);
        void 0 !== e.state && (this.state = e.state);
        void 0 !== e.text && (this.text = e.text);
        void 0 !== e.ErrorDefaultObj && (this.ErrorDefaultObj = e.ErrorDefaultObj);
        void 0 !== e.ReconnectionFunction && (this.ReconnectionFunction = e.ReconnectionFunction);
        void 0 !== e.ConfigureNetworkFunction && (this.ConfigureNetworkFunction = e.ConfigureNetworkFunction)
    }

    updateStateVars(e) {
    }

    purgeVariableDependenciesOnElmtId(e) {
        this.__Type.purgeDependencyOnElmtId(e);
        this.__Options.purgeDependencyOnElmtId(e);
        this.__ShowStatus.purgeDependencyOnElmtId(e);
        this.__ThemeColorStatus.purgeDependencyOnElmtId(e);
        this.__OpacityNum.purgeDependencyOnElmtId(e);
        this.__HEIGHT.purgeDependencyOnElmtId(e);
        this.__BORDER_RADIUS.purgeDependencyOnElmtId(e);
        this.__DURATION.purgeDependencyOnElmtId(e);
        this.__BG_OPACITY.purgeDependencyOnElmtId(e);
        this.__state.purgeDependencyOnElmtId(e);
        this.__text.purgeDependencyOnElmtId(e);
        this.__ErrorDefaultObj.purgeDependencyOnElmtId(e)
    }

    aboutToBeDeleted() {
        this.__Type.aboutToBeDeleted();
        this.__Options.aboutToBeDeleted();
        this.__ShowStatus.aboutToBeDeleted();
        this.__ThemeColorStatus.aboutToBeDeleted();
        this.__OpacityNum.aboutToBeDeleted();
        this.__HEIGHT.aboutToBeDeleted();
        this.__BORDER_RADIUS.aboutToBeDeleted();
        this.__DURATION.aboutToBeDeleted();
        this.__BG_OPACITY.aboutToBeDeleted();
        this.__state.aboutToBeDeleted();
        this.__text.aboutToBeDeleted();
        this.__ErrorDefaultObj.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get Type() {
        return this.__Type.get()
    }

    set Type(e) {
        this.__Type.set(e)
    }

    get Options() {
        return this.__Options.get()
    }

    set Options(e) {
        this.__Options.set(e)
    }

    get ShowStatus() {
        return this.__ShowStatus.get()
    }

    set ShowStatus(e) {
        this.__ShowStatus.set(e)
    }

    get ThemeColorStatus() {
        return this.__ThemeColorStatus.get()
    }

    set ThemeColorStatus(e) {
        this.__ThemeColorStatus.set(e)
    }

    get OpacityNum() {
        return this.__OpacityNum.get()
    }

    set OpacityNum(e) {
        this.__OpacityNum.set(e)
    }

    get HEIGHT() {
        return this.__HEIGHT.get()
    }

    set HEIGHT(e) {
        this.__HEIGHT.set(e)
    }

    get BORDER_RADIUS() {
        return this.__BORDER_RADIUS.get()
    }

    set BORDER_RADIUS(e) {
        this.__BORDER_RADIUS.set(e)
    }

    get DURATION() {
        return this.__DURATION.get()
    }

    set DURATION(e) {
        this.__DURATION.set(e)
    }

    get BG_OPACITY() {
        return this.__BG_OPACITY.get()
    }

    set BG_OPACITY(e) {
        this.__BG_OPACITY.set(e)
    }

    get state() {
        return this.__state.get()
    }

    set state(e) {
        this.__state.set(e)
    }

    get text() {
        return this.__text.get()
    }

    set text(e) {
        this.__text.set(e)
    }

    get ErrorDefaultObj() {
        return this.__ErrorDefaultObj.get()
    }

    set ErrorDefaultObj(e) {
        this.__ErrorDefaultObj.set(e)
    }

    OpacityStatusChange(e) {
        this.ThemeColorStatus ? this.OpacityNum = .15 : this.OpacityNum = .2
    }

    SetText() {
        this.Type === TypeEnum.NETWORK_NOT_CONNECTED && (this.text = this.ErrorDefaultObj.NETWORK_NOT_CONNECTED);
        this.Type === TypeEnum.NETWORK_CONNECTED_UNSTABLE && (this.text = this.ErrorDefaultObj.NETWORK_CONNECTED_UNSTABLE);
        this.Type === TypeEnum.UNSTABLE_CONNECT_SERVER && (this.text = this.ErrorDefaultObj.UNSTABLE_CONNECT_SERVER);
        this.Type === TypeEnum.CUSTOM_NETWORK_TIPS && (this.text = `无法获取${this.Options.ContentText || ""}，请点击重试`);
        this.Type === TypeEnum.CUSTOM_TIPS && (this.text = `${this.Options.TipContent}` || this.ErrorDefaultObj.CUSTOM_TIPS)
    }

    TypeStatusChange(e) {
        if (this.Type !== TypeEnum.DEFAULT_HIDE) {
            console.log("=========TypeStatusChange=========>", e);
            this.state && this.Type !== TypeEnum.NETWORK_NOT_CONNECTED && this.Type !== TypeEnum.NETWORK_CONNECTED_UNSTABLE && setTimeout((() => {
                this.state = !1
            }), 230);
            this.Type !== TypeEnum.NETWORK_NOT_CONNECTED && this.Type !== TypeEnum.NETWORK_CONNECTED_UNSTABLE || (this.ShowStatus ? setTimeout((() => {
                this.state = !0
            }), 230) : this.state = !0);
            if (this.ShowStatus) {
                this.ShowStatus = !1;
                setTimeout((() => {
                    this.SetText();
                    this.ShowStatus = !0
                }), 230)
            } else {
                this.SetText();
                this.ShowStatus = !0
            }
        } else this.ShowStatus = !1
    }

    aboutToAppear() {
        if (this.Type !== TypeEnum.DEFAULT_HIDE) {
            this.ShowStatus = !0;
            this.SetText()
        }
        this.Type !== TypeEnum.NETWORK_NOT_CONNECTED && this.Type !== TypeEnum.NETWORK_CONNECTED_UNSTABLE || (this.state = !0)
    }

    FirstBuilder(e = null) {
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Column.create();
            Column.height("100%");
            Column.width("100%");
            Column.borderRadius(this.BORDER_RADIUS);
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
            Column.borderRadius(this.BORDER_RADIUS);
            Column.backgroundColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_warning"],
                bundleName: "",
                moduleName: ""
            });
            Column.opacity(this.OpacityNum);
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
            Flex.padding({ left: 12, right: 12 });
            Flex.position({});
            Flex.zIndex(999);
            Flex.width("100%");
            Flex.height("100%");
            Flex.onClick((() => {
                this.Options.HardwareStatus && this.ReconnectionFunction()
            }));
            t || Flex.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Flex.create({ alignItems: ItemAlign.Center });
            Flex.width("100%");
            Flex.height("100%");
            t || Flex.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Image.create(this.Options.Icon || {
                id: -1,
                type: 2e4,
                params: ["app.media.ic_public_fail"],
                bundleName: "",
                moduleName: ""
            } || PUBLIC_TIPS);
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
            Text.create(this.text);
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
        Flex.pop();
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
                TypeEnum.NETWORK_NOT_CONNECTED || TypeEnum.NETWORK_CONNECTED_UNSTABLE ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Flex.create({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.End });
                    Flex.width(this.state ? 105 : 0);
                    Flex.height("100%");
                    Flex.onClick((() => {
                        this.ConfigureNetworkFunction()
                    }));
                    t || Flex.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Text.create("设置网络");
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
                    Text.width(58);
                    Text.maxLines(1);
                    Text.padding(0);
                    Text.margin({ right: 4 });
                    t || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                this.observeComponentCreation(((e, t) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["sys.media.ohos_ic_public_arrow_right"],
                        bundleName: "",
                        moduleName: ""
                    } || RIGHT_ICON);
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
                Flex.pop()
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
            Column.height(this.Type === TypeEnum.UNSTABLE_CONNECT_SERVER || this.Type === TypeEnum.CUSTOM_NETWORK_TIPS || this.text.length < 10 ? 48 : 58);
            Column.position({ y: this.HEIGHT });
            Column.zIndex(999);
            Column.opacity(.9);
            t || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Row.create();
            Context.animation({ duration: 230 });
            Row.padding({
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
            Row.position({});
            Row.zIndex(999);
            Row.opacity(this.ShowStatus ? 1 : 0);
            Context.animation(null);
            t || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.FirstBuilder.bind(this)();
        this.SecondBuilder.bind(this)();
        this.TextBuilder.bind(this)();
        Row.pop();
        Column.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}