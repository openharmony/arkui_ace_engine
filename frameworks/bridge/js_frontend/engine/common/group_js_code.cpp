/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/js_frontend/engine/common/group_js_code.h"

namespace OHOS::Ace {

void GroupJsCode::LoadJsCode(std::string& jsCode)
{
    LoadGlobalObjJsCode(jsCode);
    LoadGroupMessengerJsCode(jsCode);
    LoadModuleGroupJsCode(jsCode);
    LoadFeatureAbilityJsCode(jsCode);
    LoadInvokeInterfaceJsCode(jsCode);
    LoadCommonCallbackJsCode(jsCode);
    LoadCommonCallbackExJsCode(jsCode);
}

void GroupJsCode::LoadGlobalObjJsCode(std::string& jsCode)
{
    jsCode += R"(
        var global = globalThis;
        global.sendGroupMessage = global.group.sendGroupMessage;
        global.systemplugin = {};
    )";
}

void GroupJsCode::LoadModuleGroupJsCode(std::string& jsCode)
{
    jsCode += R"(
        var PluginGroup = {
            getGroup: function(name) {
                var group = {};
                group.messenger = GroupMessenger.create();
                group.name = name;
                group.call = function(...args) {
                    return this.messenger.send(this.name, '', ...args);
                };
                group.callNative = function(functionName, ...args) {
                    return this.messenger.send(this.name, functionName, ...args);
                };
                group.callNativeDiscard = function(functionName, ...args) {
                    return this.messenger.sendDiscard(this.name, functionName, ...args);
                };
                group.subscribe = function(callback, ...args) {
                    return this.messenger.sendDiscard(this.name, 'subscribe', callback, ...args);
                };
                group.unsubscribe = function(...args) {
                    return this.messenger.sendDiscard(this.name, 'unsubscribe', ...args);
                };
                return group;
            }
        };
        global.PluginGroup = PluginGroup;
        global.ModuleGroup = PluginGroup;
        global.EventGroup = PluginGroup;
    )";
}

void GroupJsCode::LoadFeatureAbilityJsCode(std::string& jsCode)
{
    jsCode += R"(
        var FeatureAbility = {
            getPlugin: function() {
                var plugin = {};
                plugin.feature = PluginGroup.getGroup('AcePluginGroup/FeatureAbility');
                plugin.distribute = PluginGroup.getGroup('AcePluginGroup/Distribute');
                plugin.call = async function(header, ...data) {
                    return await this.feature.call(header, ...data);
                };

                plugin.catching = function(promise) {
                    return promise.then(ret => ret).catch(err => err);
                };
                plugin.callAbility = async function(action) {
                    var requestHeader = this.extractHeader(action);
                    return await this.catching(this.feature.callNativeDiscard('', requestHeader, action.data));
                };
                plugin.subscribeAbilityEvent = async function(action, callbackFunc) {
                    var requestHeader = this.extractHeader(action);
                    return await this.catching(this.feature.subscribe(requestHeader, callbackFunc, action.data));
                };
                plugin.unsubscribeAbilityEvent = async function(action) {
                    var requestHeader = this.extractHeader(action);
                    return await this.catching(this.feature.unsubscribe(requestHeader, action.data));
                };
                plugin.extractHeader = function(action) {
                    action = (action.constructor === Object) ? action : {};
                    var requestHeader = {
                        element: {
                            name: action.abilityName
                        },
                        code: action.messageCode
                    };

                    if ('bundleName' in action) {
                        requestHeader.element.bundleName = action.bundleName;
                    }

                    if ('abilityType' in action) {
                        requestHeader.element.type = action.abilityType;
                    }

                    if ('syncOption' in action) {
                        requestHeader.type = action.syncOption;
                    }

                    return requestHeader;
                };

                plugin.startAbility = async function(...data) {
                    return await this.catching(this.distribute.call('startAbility', ...data));
                };
                plugin.startAbilityForResult = async function(...data) {
                    return await this.catching(this.distribute.call('startAbilityForResult', ...data));
                };
                plugin.finishWithResult = async function(...data) {
                    return await this.catching(this.distribute.call('finishWithResult', ...data));
                };
                plugin.continueAbility = async function(...data) {
                    return await this.catching(this.distribute.call('continueAbility'));
                };
                return plugin;
            },
        };
        global.FeatureAbility = FeatureAbility.getPlugin();
    )";
}
void GroupJsCode::LoadInvokeInterfaceJsCode(std::string& jsCode)
{
    jsCode += R"(
        var FeaturePlugin = global.FeatureAbility;
        var InvokeInterfaceManager = {
            __UserServiceMap: {},
            createInvokeInterface: function(interfaceName, skipInit) {
                var jsInterface = {
                    name: interfaceName
                };
                jsInterface.__getHeader = function() {
                    return {
                        element: {
                            name: jsInterface.name,
                            type: 0B11
                        },
                        type: 0,
                        code: 0
                    };
                },
                jsInterface.__invoke = function(method, ...data) {
                    var header = this.__getHeader();
                    return FeaturePlugin.call(header, method, ...data);
                }
                jsInterface.__release = function() {
                    delete InvokeInterfaceManager.__UserServiceMap[jsInterface.name];
                }

                InvokeInterfaceManager.__UserServiceMap[jsInterface.name] = jsInterface;
                if (!skipInit) {
                    InvokeInterfaceManager.initInvokeInterface(jsInterface);
                }

                return jsInterface;
            },
            initInvokeInterface: function(interfaceInfo) {
                console.info("init js interface '" + interfaceInfo.name + "' start...");
                return FeaturePlugin.call(interfaceInfo.__getHeader(), "__INIT__")
                    .catch(error => error).then(data => {
                    console.info("init js interface '" + interfaceInfo.name + "' finished");
                    return true;
                });
            },
            getInvokeInterface: function(name, init) {
                if (typeof name == "undefined" || name == null || name == "") {
                    return null;
                }
                var jsInterface = InvokeInterfaceManager.__UserServiceMap[name];
                if (!jsInterface) {
                    jsInterface = InvokeInterfaceManager.createInvokeInterface(name, init);
                }
                return jsInterface;
            },
        };
        global.createLocalParticleAbility = InvokeInterfaceManager.getInvokeInterface;
    )";
}

void GroupJsCode::LoadGroupMessengerJsCode(std::string& jsCode)
{
    jsCode += R"(
        var GroupMessenger = {
            create: function() {
                var messenger = {};
                messenger.callbackId = 0;
                messenger.callbackMap = new Map();
                messenger.callbackUserMap = new Map();
                messenger.sendDiscard = function(groupName, functionName, ...args) {
                    return new Promise (function(resolve, reject) {
                        sendGroupMessage(function(result) {
                            resolve(result);
                        }, function(error) {
                            reject(error);
                        }, groupName, functionName, ...args);
                    });
                };
                messenger.send = function(groupName, functionName, ...args) {
                    return new Promise (function(resolve, reject) {
                        var params = messenger.prepareArgs(...args);
                        sendGroupMessage(function(result) {
                            resolve(messenger.parseJsonResult(result));
                        }, function(error) {
                            reject(messenger.parseJsonResult(error));
                        }, groupName, functionName, ...params);
                    })
                };
                messenger.parseJsonResult = function(data) {
                    if (data && data.constructor == String) {
                        try {
                            data = JSON.parse(data);
                        } catch (jsonParseErr) {
                            console.warn("parse result exception: " + JSON.stringify(jsonParseErr));
                        }
                    }

                    return data;
                };
                messenger.prepareArgs = function(...args) {
                    var result = [...args];
                    for (var i = 0; i < result.length; i++) {
                        if (typeof result[i] === 'function') {
                            result[i] = messenger.packageCallback(result[i]);
                        }
                    }
                    return result;
                };
                messenger.packageCallback = function(func) {
                    return function(data) {
                        data = messenger.parseJsonResult(data);
                        if (!Array.isArray(data)) {
                            func(data);
                        } else {
                            func(...data);
                        }
                    };
                };
                return messenger;
            }
        };
        global.GroupMessenger = GroupMessenger;
    )";
}

void GroupJsCode::LoadCommonCallbackJsCode(std::string& jsCode)
{
    jsCode += R"(
        var CommonCallback = {
            systemPluginException: function systemPluginException(code, data) {
                this.code = code;
                this.data = data;
            },
            commonCallback: function commonCallback(callback, flag, data, code) {
                if (typeof callback === 'function') {
                    switch (flag) {
                        case 'success':
                            callback(data);
                            break;
                        case 'fail':
                            callback(data, code);
                            break;
                        case 'cancel':
                            callback(data);
                            break;
                        case 'complete':
                            callback();
                            break;
                        default:
                            break;
                    }
                } else {
                    console.warn('callback.' + flag + ' is not function or not present');
                }
            }
        };
        global.commonCallback = CommonCallback.commonCallback;
        global.systemPluginException = CommonCallback.systemPluginException;
    )";
}

void GroupJsCode::LoadCommonCallbackExJsCode(std::string& jsCode)
{
    jsCode += R"(
        var CommonCallbackEx = {
            commonCallbackEx: function commonCallbackEx(callback, result, pluginError) {
                if ((callback === undefined) || ((callback.success === undefined) && (callback.fail === undefined) &&
                    (callback.complete === undefined))) {
                    return CommonCallbackEx.promiseMethod(result, pluginError);
                } else {
                    return CommonCallbackEx.callbackMethod(callback, result, pluginError);
                }
            },
            promiseMethod: function promiseMethod(result, pluginError) {
                if (pluginError != undefined) {
                    throw pluginError;
                }
                return result;
            },
             callbackMethod: function callbackMethod(callback, result, pluginError) {
                if (pluginError != undefined) {
                    commonCallback(callback.fail, 'fail', pluginError.data, pluginError.code);
                    commonCallback(callback.complete, 'complete');
                    throw pluginError;
                }

                commonCallback(callback.success, 'success', result.data);
                commonCallback(callback.complete, 'complete');
                return result;
            },
            catching: function catching(promise, param) {
                return promise.then(ret => commonCallbackEx(param, ret))
                    .catch(err => commonCallbackEx(param, null, err));
            }
        };
        global.commonCallbackEx = CommonCallbackEx.commonCallbackEx;
        global.systemplugin.catching = CommonCallbackEx.catching;
    )";
}
} // namespace OHOS::Ace
