/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { ComputedDecoratedVariable } from '../decoratorImpl/decoratorComputed';
import { DecoratedV1VariableBase, DecoratedV2VariableBase } from '../decoratorImpl/decoratorBase';
import { MonitorFunctionDecorator } from '../decoratorImpl/decoratorMonitor';

export class StateMgmtConsole {
    static log(str: string): void {
        console.log('StateManagement: [' + str + ']');
    }
    static warn(str: string): void {
        console.warn('StateManagement: [' + str + ']');
    }
    static error(str: string): void {
        console.error('StateManagement: [' + str + ']');
    }
    static traceBegin(str: string): void {}
    static traceEnd(): void {}
    static scopedTrace(str: string, cb: () => void): void {
        cb();
    }
}

class ViewInfo {
    componentName?: string;
    isV2?: boolean;
}

class DecoratorInfo {
    decorator?: string;
    propertyName?: string;
    value?: Any;
}

export class DumpInfo {
    viewinfo: ViewInfo = new ViewInfo();
    observedPropertiesInfo: Array<DecoratorInfo> = [];
}

export class StateMgmtDFX {
    public static enableDebug: boolean = false;
    static getDecoratedVariableInfo(view: Any, dumpInfo: DumpInfo, isV2: boolean): void {
        if (isV2) {
            StateMgmtDFX.dumpV2VariableInfo(view, dumpInfo);
        } else {
            StateMgmtDFX.dumpV1VariableInfo(view, dumpInfo);
        }
    }

    static dumpV1VariableInfo(view: Any, dumpInfo: DumpInfo): void {
        if (view instanceof Object) {
            Object.getOwnPropertyNames(view)
                .filter((varName) => {
                    return varName.startsWith('__backing');
                })
                .forEach((varName) => {
                    const value = (reflect.Value.of(view) as ClassValue).getFieldByName(varName).getData();
                    if (value && value instanceof DecoratedV1VariableBase) {
                        dumpInfo.observedPropertiesInfo.push({
                            decorator: value.decorator,
                            propertyName: value.varName,
                            value: value.get(),
                        });
                    }
                });
        }
    }

    static dumpV2VariableInfo(view: Any, dumpInfo: DumpInfo): void {
        if (view instanceof Object) {
            Object.getOwnPropertyNames(view)
                .filter((varName) => {
                    return (
                        varName.startsWith('__backing') ||
                        varName.startsWith('__computed') ||
                        varName.startsWith('__monitor')
                    );
                })
                .forEach((varName) => {
                    const value = (reflect.Value.of(view) as ClassValue).getFieldByName(varName).getData();
                    if (value && value instanceof DecoratedV2VariableBase) {
                        dumpInfo.observedPropertiesInfo.push({
                            decorator: value.decorator,
                            propertyName: value.varName,
                            value: value.get(),
                        });
                    } else if (value && value instanceof ComputedDecoratedVariable) {
                        dumpInfo.observedPropertiesInfo.push({
                            decorator: value.decorator,
                            propertyName: value.varName,
                            value: value.get(),
                        });
                    } else if (value && value instanceof MonitorFunctionDecorator) {
                        const propertyName = varName.replace('__monitor_', '');
                        dumpInfo.observedPropertiesInfo.push({
                            decorator: value.decorator,
                            propertyName: propertyName,
                        });
                    }
                });
        }
    }
}
