/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
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
const hilog = requireNapi('hilog');
const abilityManager = requireNapi('app.ability.abilityManager');
const commonEventManager = requireNapi('commonEventManager');
export class LaunchController {
    constructor() {
        this.launchAtomicService = (n1, o1) => { };
    }
}

const EMBEDDED_FULL_MODE = 1;
export class InnerFullScreenLaunchComponent extends ViewPU {
    constructor(d1, e1, f1, g1 = -1, h1 = undefined, i1) {
        super(d1, f1, g1, i1);
        if (typeof h1 === "function") {
            this.paramsGenerator_ = h1;
        }
        this.content = this.doNothingBuilder;
        this.context = getContext(this);
        this.controller = new LaunchController();
        this.appId = '';
        this.options = undefined;
        this.__isShow = new ObservedPropertySimplePU(false, this, "isShow");
        this.subscriber = null;
        this.launchAtomicService = (k1, l1) => {
            hilog.info(0x3900, 'InnerFullScreenLaunchComponent', 'launchAtomicService, appId: %{public}s.', k1);
            this.appId = k1;
            this.options = l1;
            this.checkAbility();
        };
        this.setInitiallyProvidedValue(e1);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(c1) {
        if (c1.content !== undefined) {
            this.content = c1.content;
        }
        if (c1.context !== undefined) {
            this.context = c1.context;
        }
        if (c1.controller !== undefined) {
            this.controller = c1.controller;
        }
        if (c1.appId !== undefined) {
            this.appId = c1.appId;
        }
        if (c1.options !== undefined) {
            this.options = c1.options;
        }
        if (c1.isShow !== undefined) {
            this.isShow = c1.isShow;
        }
        if (c1.subscriber !== undefined) {
            this.subscriber = c1.subscriber;
        }
        if (c1.launchAtomicService !== undefined) {
            this.launchAtomicService = c1.launchAtomicService;
        }
    }
    updateStateVars(b1) {
    }
    purgeVariableDependenciesOnElmtId(a1) {
        this.__isShow.purgeDependencyOnElmtId(a1);
    }
    aboutToBeDeleted() {
        this.__isShow.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isShow() {
        return this.__isShow.get();
    }
    set isShow(z) {
        this.__isShow.set(z);
    }
    aboutToAppear() {
        let s = {
            events: [commonEventManager.Support.COMMON_EVENT_DISTRIBUTED_ACCOUNT_LOGOUT],
        };
        commonEventManager.createSubscriber(s, (u, v) => {
            if (u) {
                hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'Failed to create subscriber, err: %{public}s.', u.message);
                return;
            }
            if (v == null || v == undefined) {
                hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'Failed to create subscriber, data is null.');
                return;
            }
            this.subscriber = v;
            commonEventManager.subscribe(this.subscriber, (x, y) => {
                if (x) {
                    hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'Failed to subscribe common event, err: %{public}s.', x.message);
                    return;
                }
                hilog.info(0x3900, 'InnerFullScreenLaunchComponent', 'Received account logout event.');
                this.isShow = false;
            });
        });
        this.controller.launchAtomicService = this.launchAtomicService;
    }
    aboutToDisappear() {
        if (this.subscriber !== null) {
            commonEventManager.unsubscribe(this.subscriber, (r) => {
                if (r) {
                    hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'UnsubscribeCallBack, err: %{public}s.', r.message);
                }
                else {
                    hilog.info(0x3900, 'InnerFullScreenLaunchComponent', 'Unsubscribe.');
                    this.subscriber = null;
                }
            });
        }
    }
    doNothingBuilder(p = null) {
    }
    resetOptions() {
        if (this.options?.parameters) {
            this.options.parameters['ohos.extra.param.key.showMode'] = EMBEDDED_FULL_MODE;
            this.options.parameters['ability.want.params.IsNotifyOccupiedAreaChange'] = true;
            hilog.info(0x3900, 'InnerFullScreenLaunchComponent', 'replaced options is %{public}s !', JSON.stringify(this.options));
        }
        else {
            this.options = {
                parameters: {
                    'ohos.extra.param.key.showMode': EMBEDDED_FULL_MODE,
                    'ability.want.params.IsNotifyOccupiedAreaChange': true,
                }
            };
        }
    }
    async checkAbility() {
        this.resetOptions();
        try {
            const o = await abilityManager.isEmbeddedOpenAllowed(this.context, this.appId);
            if (o) {
                this.isShow = true;
                hilog.info(0x3900, 'InnerFullScreenLaunchComponent', ' EmbeddedOpen is Allowed!');
            }
            else {
                hilog.info(0x3900, 'InnerFullScreenLaunchComponent', ' EmbeddedOpen is not Allowed!');
                this.popUp();
            }
        }
        catch (n) {
            hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'isEmbeddedOpenAllowed called error!%{public}s', n.message);
        }
    }
    async popUp() {
        this.isShow = false;
        try {
            const m = await this.context.openAtomicService(this.appId, this.options);
            hilog.info(0x3900, 'InnerFullScreenLaunchComponent', '%{public}s open service success!', m.want);
        }
        catch (l) {
            hilog.error(0x3900, 'InnerFullScreenLaunchComponent', '%{public}s open service error!', l.message);
        }
    }
    initialRender() {
        this.observeComponentCreation2((i, j) => {
            Row.create();
            Row.justifyContent(FlexAlign.Center);
            Row.bindContentCover({ value: this.isShow, changeEvent: k => { this.isShow = k; } }, { builder: () => {
                    this.uiExtensionBuilder.call(this);
                } }, { modalTransition: ModalTransition.DEFAULT });
        }, Row);
        this.content.bind(this)(this);
        Row.pop();
    }
    uiExtensionBuilder(a = null) {
        this.observeComponentCreation2((c, d) => {
            UIExtensionComponent.create({
                bundleName: `com.atomicservice.${this.appId}`,
                flags: this.options?.flags,
                parameters: this.options?.parameters
            });
            UIExtensionComponent.height('100%');
            UIExtensionComponent.width('100%');
            UIExtensionComponent.onRelease(() => {
                hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'onRelease');
                this.isShow = false;
            });
            UIExtensionComponent.onError(g => {
                this.isShow = false;
                hilog.error(0x3900, 'InnerFullScreenLaunchComponent', 'call up UIExtension error!%{public}s', g.message);
                this.getUIContext().showAlertDialog({
                    message: g.message
                });
            });
        }, UIExtensionComponent);
    }
    rerender() {
        this.updateDirtyElements();
    }
}


export default { InnerFullScreenLaunchComponent, LaunchController};