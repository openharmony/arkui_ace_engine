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
const Start_DURATION = 250;
const End_DURATION = 200;

export class ExceptionPrompt extends ViewPU {
    constructor(t, e, o, s = -1) {
        super(t, o, s);
        this.__Type = new SynchedPropertySimpleOneWayPU(e.Type, this, "Type");
        this.__HardwareStatus = new SynchedPropertySimpleOneWayPU(e.HardwareStatus, this, "HardwareStatus");
        this.__Icon = new SynchedPropertySimpleOneWayPU(e.Icon, this, "Icon");
        this.__TipContent = new SynchedPropertySimpleOneWayPU(e.TipContent, this, "TipContent");
        this.__ContentText = new SynchedPropertySimpleOneWayPU(e.ContentText, this, "ContentText");
        this.__ThemeColorStatus = new SynchedPropertySimpleOneWayPU(e.ThemeColorStatus, this, "ThemeColorStatus");
        this.__ShowStatus = new ObservedPropertySimplePU(!1, this, "ShowStatus");
        this.__OpacityNum = new ObservedPropertySimplePU(.15, this, "OpacityNum");
        this.__HEIGHT = new ObservedPropertySimplePU(80, this, "HEIGHT");
        this.__BORDER_RADIUS = new ObservedPropertySimplePU(16, this, "BORDER_RADIUS");
        this.__BG_OPACITY = new ObservedPropertySimplePU(1, this, "BG_OPACITY");
        this.__state = new ObservedPropertySimplePU(!1, this, "state");
        this.__ErrorDefaultObj = new ObservedPropertyObjectPU({
            1: "网络未连接",
            2: "网络连接不稳定，请点击重试",
            3: "无法连接到服务器，请点击重试",
            4: "无法获取xxx，请点击重试"
        }, this, "ErrorDefaultObj");
        this.__text = new ObservedPropertySimplePU("", this, "text");
        this.ReconnectionFunction = () => {
        };
        this.ConfigureNetworkFunction = () => {
        };
        this.setInitiallyProvidedValue(e);
        this.declareWatch("Type", this.TypeStatusChange);
        this.declareWatch("ThemeColorStatus", this.OpacityStatusChange)
    }

    setInitiallyProvidedValue(t) {
            void 0 !== t.HardwareStatus ? this.__HardwareStatus.set(t.HardwareStatus) : this.__HardwareStatus.set(!0);
            void 0 !== t.Icon ? this.__Icon.set(t.Icon) : this.__Icon.set("");
            void 0 !== t.TipContent ? this.__TipContent.set(t.TipContent) : this.__TipContent.set("");
            void 0 !== t.ContentText ? this.__ContentText.set(t.ContentText) : this.__ContentText.set("");
            void 0 !== t.ThemeColorStatus ? this.__ThemeColorStatus.set(t.ThemeColorStatus) : this.__ThemeColorStatus.set(!0);
        void 0 !== t.ShowStatus && (this.ShowStatus = t.ShowStatus);
        void 0 !== t.OpacityNum && (this.OpacityNum = t.OpacityNum);
        void 0 !== t.HEIGHT && (this.HEIGHT = t.HEIGHT);
        void 0 !== t.BORDER_RADIUS && (this.BORDER_RADIUS = t.BORDER_RADIUS);
        void 0 !== t.BG_OPACITY && (this.BG_OPACITY = t.BG_OPACITY);
        void 0 !== t.state && (this.state = t.state);
        void 0 !== t.ErrorDefaultObj && (this.ErrorDefaultObj = t.ErrorDefaultObj);
        void 0 !== t.text && (this.text = t.text);
        void 0 !== t.ReconnectionFunction && (this.ReconnectionFunction = t.ReconnectionFunction);
        void 0 !== t.ConfigureNetworkFunction && (this.ConfigureNetworkFunction = t.ConfigureNetworkFunction)
    }

    updateStateVars(t) {
        this.__Type.reset(t.Type);
        this.__HardwareStatus.reset(t.HardwareStatus);
        this.__Icon.reset(t.Icon);
        this.__TipContent.reset(t.TipContent);
        this.__ContentText.reset(t.ContentText);
        this.__ThemeColorStatus.reset(t.ThemeColorStatus)
    }

    purgeVariableDependenciesOnElmtId(t) {
        this.__Type.purgeDependencyOnElmtId(t);
        this.__HardwareStatus.purgeDependencyOnElmtId(t);
        this.__Icon.purgeDependencyOnElmtId(t);
        this.__TipContent.purgeDependencyOnElmtId(t);
        this.__ContentText.purgeDependencyOnElmtId(t);
        this.__ThemeColorStatus.purgeDependencyOnElmtId(t);
        this.__ShowStatus.purgeDependencyOnElmtId(t);
        this.__OpacityNum.purgeDependencyOnElmtId(t);
        this.__HEIGHT.purgeDependencyOnElmtId(t);
        this.__BORDER_RADIUS.purgeDependencyOnElmtId(t);
        this.__BG_OPACITY.purgeDependencyOnElmtId(t);
        this.__state.purgeDependencyOnElmtId(t);
        this.__ErrorDefaultObj.purgeDependencyOnElmtId(t);
        this.__text.purgeDependencyOnElmtId(t)
    }

    aboutToBeDeleted() {
        this.__Type.aboutToBeDeleted();
        this.__HardwareStatus.aboutToBeDeleted();
        this.__Icon.aboutToBeDeleted();
        this.__TipContent.aboutToBeDeleted();
        this.__ContentText.aboutToBeDeleted();
        this.__ThemeColorStatus.aboutToBeDeleted();
        this.__ShowStatus.aboutToBeDeleted();
        this.__OpacityNum.aboutToBeDeleted();
        this.__HEIGHT.aboutToBeDeleted();
        this.__BORDER_RADIUS.aboutToBeDeleted();
        this.__BG_OPACITY.aboutToBeDeleted();
        this.__state.aboutToBeDeleted();
        this.__ErrorDefaultObj.aboutToBeDeleted();
        this.__text.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get Type() {
        return this.__Type.get()
    }

    set Type(t) {
        this.__Type.set(t)
    }

    get HardwareStatus() {
        return this.__HardwareStatus.get()
    }

    set HardwareStatus(t) {
        this.__HardwareStatus.set(t)
    }

    get Icon() {
        return this.__Icon.get()
    }

    set Icon(t) {
        this.__Icon.set(t)
    }

    get TipContent() {
        return this.__TipContent.get()
    }

    set TipContent(t) {
        this.__TipContent.set(t)
    }

    get ContentText() {
        return this.__ContentText.get()
    }

    set ContentText(t) {
        this.__ContentText.set(t)
    }

    get ThemeColorStatus() {
        return this.__ThemeColorStatus.get()
    }

    set ThemeColorStatus(t) {
        this.__ThemeColorStatus.set(t)
    }

    get ShowStatus() {
        return this.__ShowStatus.get()
    }

    set ShowStatus(t) {
        this.__ShowStatus.set(t)
    }

    get OpacityNum() {
        return this.__OpacityNum.get()
    }

    set OpacityNum(t) {
        this.__OpacityNum.set(t)
    }

    get HEIGHT() {
        return this.__HEIGHT.get()
    }

    set HEIGHT(t) {
        this.__HEIGHT.set(t)
    }

    get BORDER_RADIUS() {
        return this.__BORDER_RADIUS.get()
    }

    set BORDER_RADIUS(t) {
        this.__BORDER_RADIUS.set(t)
    }

    get BG_OPACITY() {
        return this.__BG_OPACITY.get()
    }

    set BG_OPACITY(t) {
        this.__BG_OPACITY.set(t)
    }

    get state() {
        return this.__state.get()
    }

    set state(t) {
        this.__state.set(t)
    }

    get ErrorDefaultObj() {
        return this.__ErrorDefaultObj.get()
    }

    set ErrorDefaultObj(t) {
        this.__ErrorDefaultObj.set(t)
    }

    get text() {
        return this.__text.get()
    }

    set text(t) {
        this.__text.set(t)
    }

    OpacityStatusChange(t) {
        this.ThemeColorStatus ? this.OpacityNum = .15 : this.OpacityNum = .2
    }

    TypeStatusChange(t) {
        if (this.Type) {
            this.state && 1 !== this.Type && 2 !== this.Type && setTimeout((() => {
                this.state = !1
            }), 200);
            1 !== this.Type && 2 !== this.Type || (this.ShowStatus ? setTimeout((() => {
                this.state = !0
            }), 250) : this.state = !0);
            if (this.ShowStatus) {
                this.ShowStatus = !1;
                setTimeout((() => {
                    this.text = this.ErrorDefaultObj[this.Type];
                    4 === this.Type && (this.text = `无法获取${this.ContentText || ""}，请点击重试`);
                    this.ShowStatus = !0
                }), 200)
            } else {
                this.text = this.ErrorDefaultObj[this.Type];
                4 === this.Type && (this.text = `无法获取${this.ContentText || ""}，请点击重试`);
                this.ShowStatus = !0
            }
        } else this.ShowStatus = !1
    }

    initialRender() {
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Column.create();
            Column.width("100%");
            Column.height(3 === this.Type || 4 === this.Type || this.text.length < 8 ? 48 : 58);
            Column.position({ y: this.HEIGHT });
            Column.zIndex(999);
            Column.opacity(.92);
            e || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Row.create();
            Context.animation({ duration: 250 });
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
            e || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
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
            e || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Column.pop();
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
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
            e || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Column.pop();
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
            Flex.padding({ left: 12, right: 12 });
            Flex.position({});
            Flex.zIndex(999);
            Flex.width("100%");
            Flex.height("100%");
            Flex.onClick((() => {
                this.HardwareStatus && this.ReconnectionFunction()
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
            Image.create(this.Icon || PUBLIC_TIPS);
            Image.width("24vp");
            Image.height("24vp");
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
            Text.create(this.TipContent || this.text);
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
            Text.margin({ left: 16 });
            e || Text.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Flex.pop();
        this.observeComponentCreation(((t, e) => {
            ViewStackProcessor.StartGetAccessRecordingFor(t);
            If.create();
            this.TipContent ? If.branchId(1) : this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Flex.create({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.End });
                    Flex.margin({ left: 16 });
                    Flex.width(this.state ? 120 : 0);
                    Flex.height("100%");
                    Flex.onClick((() => {
                        this.ConfigureNetworkFunction()
                    }));
                    e || Flex.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
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
                    Text.width(65);
                    e || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                this.observeComponentCreation(((t, e) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(t);
                    Image.create(RIGHT_ICON);
                    Image.margin({ left: 4 });
                    Image.width("15vp");
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
                Flex.pop()
            }));
            e || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Flex.pop();
        Row.pop();
        Column.pop()
    }

    rerender() {
        this.updateDirtyElements()
    }
}