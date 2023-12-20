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
const BORDER_RADIUS = 12;
const OPACITY_NUM = .18;
const DEFAULT_HEIGHT = 48;
const FIT_HEIGHT = 58;
const ZINDEX_NUM = 999;

export var MarginType;
!function(e){
    e[e.DEFAULT_MARGIN=0] = "DEFAULT_MARGIN";
    e[e.FIT_MARGIN=1] = "FIT_MARGIN"
}(MarginType || (MarginType = {}));

export class ExceptionPrompt extends ViewPU {
    constructor(e, o, t, i = -1) {
        super(e, t, i);
        this.__options = new SynchedPropertyObjectOneWayPU(o.options, this, "options");
        this.touchBackgroundColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_sub_background_transparent"],
            bundleName: "",
            moduleName: ""
        };
        this.onTipClick = () => {
        };
        this.onActionTextClick = () => {
        };
        this.setInitiallyProvidedValue(o)
    }

    setInitiallyProvidedValue(e) {
        void 0 !== e.touchBackgroundColor && (this.touchBackgroundColor = e.touchBackgroundColor);
        void 0 !== e.onTipClick && (this.onTipClick = e.onTipClick);
        void 0 !== e.onActionTextClick && (this.onActionTextClick = e.onActionTextClick)
    }

    updateStateVars(e) {
        this.__options.reset(e.options)
    }

    purgeVariableDependenciesOnElmtId(e) {
        this.__options.purgeDependencyOnElmtId(e)
    }

    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
    }

    get options() {
        return this.__options.get()
    }

    set options(e) {
        this.__options.set(e)
    }

    FirstBuilder(e = null) {
        this.observeComponentCreation(((e, o) => {
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
            o || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Column.pop()
    }

    SecondBuilder(e = null) {
        this.observeComponentCreation(((e, o) => {
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
            Column.zIndex(999);
            o || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Column.pop()
    }

    TextBuilder(e = null) {
        this.observeComponentCreation(((e, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Flex.create({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center });
            Flex.padding({
                left: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_notification_margin_start"],
                    bundleName: "",
                    moduleName: ""
                },
                right: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_text_paragraph_margin_s"],
                    bundleName: "",
                    moduleName: ""
                }
            });
            Flex.position({});
            Flex.zIndex(999);
            Flex.width("100%");
            Flex.height("100%");
            o || Flex.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Flex.create({ alignItems: ItemAlign.Center });
            Flex.width("100%");
            Flex.height("100%");
            Flex.onClick((() => {
                this.onTipClick()
            }));
            o || Flex.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, o) => {
            var t;
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Image.create(null !== (t = this.options.icon) && void 0 !== t ? t : {
                                                                                    id: -1,
                                                                                    type: 2e4,
                                                                                    params: ["sys.media.ohos_ic_public_fail"],
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
            o || Image.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Text.create(this.options.tip);
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
            Text.margin({
                left: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_dialog_margin_end"],
                    bundleName: "",
                    moduleName: ""
                },
                right: {
                    id: -1,
                    type: 10002,
                    params: ["sys.float.ohos_id_dialog_margin_end"],
                    bundleName: "",
                    moduleName: ""
                }
            });
            o || Text.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Flex.pop();
        this.observeComponentCreation(((e, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.options.actionText ? this.ifElseBranchUpdateFunction(0, (() => {
                this.observeComponentCreation(((e, o) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Button.createWithChild({ stateEffect: !0, type: ButtonType.Normal });
                    Button.backgroundColor(this.touchBackgroundColor);
                    Button.width(this.options.actionText ? 120 : 0);
                    Button.height(32);
                    Button.borderRadius({
                        id: -1,
                        type: 10002,
                        params: ["sys.float.ohos_id_corner_radius_subtab"],
                        bundleName: "",
                        moduleName: ""
                    });
                    Button.padding({
                        right: {
                            id: -1,
                            type: 10002,
                            params: ["sys.float.ohos_id_elements_margin_vertical_l"],
                            bundleName: "",
                            moduleName: ""
                        },
                        left: {
                            id: -1,
                            type: 10002,
                            params: ["sys.float.ohos_id_elements_margin_vertical_l"],
                            bundleName: "",
                            moduleName: ""
                        }
                    });
                    Button.onTouch((e => {
                        if (e.type === TouchType.Down) {
                            this.touchBackgroundColor = {
                                id: -1,
                                type: 10001,
                                params: ["sys.color.ohos_id_color_click_effect"],
                                bundleName: "",
                                moduleName: ""
                            };
                            this.onActionTextClick()
                        } else e.type === TouchType.Up && (this.touchBackgroundColor = {
                            id: -1,
                            type: 10001,
                            params: ["sys.color.ohos_id_color_sub_background_transparent"],
                            bundleName: "",
                            moduleName: ""
                        })
                    }));
                    o || Button.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, o) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Row.create();
                    o || Row.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, o) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Text.create(this.options.actionText);
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
                    Text.margin({
                        right: {
                            id: -1,
                            type: 10002,
                            params: ["sys.float.ohos_id_text_paragraph_margin_s"],
                            bundleName: "",
                            moduleName: ""
                        }
                    });
                    Text.textAlign(TextAlign.End);
                    o || Text.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Text.pop();
                this.observeComponentCreation(((e, o) => {
                    ViewStackProcessor.StartGetAccessRecordingFor(e);
                    Image.create({
                        id: -1,
                        type: 2e4,
                        params: ["sys.media.ohos_ic_public_arrow_right"],
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
                    o || Image.pop();
                    ViewStackProcessor.StopGetAccessRecording()
                }));
                Row.pop();
                Button.pop()
            })) : If.branchId(1);
            o || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Flex.pop()
    }

    initialRender() {
        this.observeComponentCreation(((e, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Column.create();
            Column.width("100%");
            Column.height(this.options.actionText ? 58 : 48);
            Column.position({ y: this.options.marginTop });
            Column.zIndex(999);
            o || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((e, o) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Stack.create();
            Stack.padding(this.options.marginType === MarginType.DEFAULT_MARGIN ? {
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
            Stack.transition(TransitionEffect.OPACITY.animation({ duration: this.options.isShown ? 250 : 200 }));
            Stack.visibility(this.options.isShown ? Visibility.Visible : Visibility.None);
            o || Stack.pop();
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