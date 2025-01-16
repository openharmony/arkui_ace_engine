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
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => {
    });
}
const hilog = requireNapi('hilog');
const abilityManager = requireNapi('app.ability.abilityManager');
const commonEventManager = requireNapi('commonEventManager');
const j = 100014;

export class FullScreenLaunchComponent extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.content = this.doNothingBuilder;
        this.context = getContext(this);
        this.appId = "";
        this.options = undefined;
        this.__isShow = new ObservedPropertySimplePU(false, this, "isShow");
        this.subscriber = null;
        this.onError = undefined;
        this.onTerminated = undefined;
        this.setInitiallyProvidedValue(params);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.content !== undefined) {
            this.content = params.content;
        }
        if (params.context !== undefined) {
            this.context = params.context;
        }
        if (params.appId !== undefined) {
            this.appId = params.appId;
        }
        if (params.options !== undefined) {
            this.options = params.options;
        }
        if (params.isShow !== undefined) {
            this.isShow = params.isShow;
        }
        if (params.subscriber !== undefined) {
            this.subscriber = params.subscriber;
        }
        if (params.onError !== undefined) {
            this.onError = params.onError;
        }
        if (params.onTerminated !== undefined) {
            this.onTerminated = params.onTerminated;
        }
    }
    updateStateVars(params) {
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__isShow.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__isShow.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get isShow() {
        return this.__isShow.get();
    }
    set isShow(newValue) {
        this.__isShow.set(newValue);
    }
    aboutToAppear() {
        let subscribeInfo = {
            events: [commonEventManager.Support.COMMON_EVENT_DISTRIBUTED_ACCOUNT_LOGOUT],
        };
        commonEventManager.createSubscriber(subscribeInfo, (err, data) => {
            if (err) {
                hilog.error(0x3900, 'FullScreenLaunchComponent', 'Failed to create subscriber, err: %{public}s.', JSON.stringify(err));
                return;
            }
            if (data == null || data == undefined) {
                hilog.error(0x3900, 'FullScreenLaunchComponent', 'Failed to create subscriber, data is null.');
                return;
            }
            this.subscriber = data;
            commonEventManager.subscribe(this.subscriber, (err, data) => {
                if (err) {
                    hilog.error(0x3900, 'FullScreenLaunchComponent', 'Failed to subscribe common event, err: %{public}s.', JSON.stringify(err));
                    return;
                }
                hilog.info(0x3900, 'FullScreenLaunchComponent', 'Received account logout event.');
                this.isShow = false;
            });
        });
    }
    aboutToDisappear() {
        if (this.subscriber !== null) {
            commonEventManager.unsubscribe(this.subscriber, (err) => {
                if (err) {
                    hilog.error(0x3900, 'FullScreenLaunchComponent', 'UnsubscribeCallBack, err: %{public}s.', JSON.stringify(err));
                }
                else {
                    hilog.info(0x3900, 'FullScreenLaunchComponent', 'Unsubscribe.');
                    this.subscriber = null;
                }
            });
        }
    }
    doNothingBuilder(parent = null) {
    }
    resetOptions() {
        if (this.options?.parameters) {
            this.options.parameters['ohos.extra.param.key.showMode'] = 1;
            this.options.parameters['ability.want.params.IsNotifyOccupiedAreaChange'] = true;
            this.options.parameters['ability.want.params.IsModal'] = true;
            hilog.info(0x3900, 'FullScreenLaunchComponent', 'replaced options is %{public}s !', JSON.stringify(this.options));
        }
        else {
            this.options = {
                parameters: {
                    'ohos.extra.param.key.showMode': 1,
                    'ability.want.params.IsNotifyOccupiedAreaChange': true,
                    'ability.want.params.IsModal': true
                }
            };
        }
    }
    async checkAbility() {
        this.resetOptions();
        try {
            const i = await abilityManager.isEmbeddedOpenAllowed(this.context, this.appId);
            if (i) {
                this.isShow = true;
                hilog.info(0x3900, 'FullScreenLaunchComponent', ' EmbeddedOpen is Allowed!');
            }
            else {
                this.popUp();
            }
        }
        catch (e) {
            hilog.error(0x3900, 'FullScreenLaunchComponent', 'isEmbeddedOpenAllowed called error!%{public}s', e.message);
        }
    }
    async popUp() {
        this.isShow = false;
        try {
            const ability = await this.context.openAtomicService(this.appId, this.options);
            hilog.info(0x3900, 'FullScreenLaunchComponent', '%{public}s open service success!', ability.want);
        }
        catch (e) {
            hilog.error(0x3900, 'FullScreenLaunchComponent', '%{public}s open service error!', e.message);
        }
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.justifyContent(FlexAlign.Center);
            Row.onClick(() => {
                this.checkAbility();
            });
            Row.bindContentCover({ value: this.isShow, changeEvent: newValue => { this.isShow = newValue; } }, { builder: () => {
                    this.uiExtensionBuilder.call(this);
                } });
        }, Row);
        this.content.bind(this)();
        Row.pop();
    }
    uiExtensionBuilder(parent = null) {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            UIExtensionComponent.create({
                bundleName: `com.atomicservice.${this.appId}`,
                flags: this.options?.flags,
                parameters: this.options?.parameters
            });
            UIExtensionComponent.height('100%');
            UIExtensionComponent.width('100%');
            UIExtensionComponent.onError(err => {
                if (this.onError != undefined) {
                    this.onError(err);
                }
                this.isShow = false;
                hilog.error(0x3900, 'FullScreenLaunchComponent', 'call up UIExtension error:%{public}d!%{public}s', err.code, err.message);
                if (err.code != j) {
                    this.getUIContext().showAlertDialog({
                        message: err.message
                    });
                }
            });
            UIExtensionComponent.onTerminated(info => {
                this.isShow = false;
                if (this.onTerminated != undefined) {
                    this.onTerminated(info);
                }
            });
        }, UIExtensionComponent);
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default { FullScreenLaunchComponent }