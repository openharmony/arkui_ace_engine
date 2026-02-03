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
import { AceTrace } from '../../base/AceTrace';
import { UIUtils } from '../utils';
import { ExtendableComponent } from '../../component/extendableComponent';

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

class MapItem {
    key?: string;
    value?: string[];
}

class PropertyDependenciesInfo {
    mode?: string;
    propertyDependencies?: string[];
    trackPropertiesDependencies?: MapItem[];
}

type SimpleAndNonType = string | int | double | long | boolean | undefined | null;
type DumpObjectType = Array<[string, Any]>;

class DecoratorInfo {
    decorator?: string;
    propertyName?: string;
    value?: Any;
    syncPeers?: DecoratorInfo[];
    id?: int;
    dependentElementIds?: PropertyDependenciesInfo;
}

export class DumpInfo {
    viewinfo: ViewInfo = new ViewInfo();
    observedPropertiesInfo: Array<DecoratorInfo> = [];
}

export class StateMgmtDFX {
    public static enableDebug: boolean = false;
    private static readonly DUMP_MAX_PROPERTY_COUNT: int = 50;
    private static readonly DUMP_MAX_LENGTH: int = 10;
    private static readonly DUMP_LAST_LENGTH: int = 3;

    private static getField(varName: string, value: Object): reflect.InstanceField | undefined {
        let field: reflect.InstanceField | undefined = undefined;
        let currClass: Class | undefined = Class.of(value);
        while(currClass !== undefined) {
            field = currClass!.getInstanceField(varName);
            if (field !== undefined) {
                break;
            }
            currClass = currClass!.getSuper();
        }
        return field;
    }

    public static functionTrace(content: string): boolean {
        AceTrace.begin(content); 
        AceTrace.end();
        return true;
    }
    
    static getDecoratedVariableInfo(view: Any, dumpInfo: DumpInfo, isV2: boolean): void {
        if (isV2) {
            StateMgmtDFX.dumpV2VariableInfo(view, dumpInfo);
        } else {
            StateMgmtDFX.dumpV1VariableInfo(view, dumpInfo);
        }
    }

    static dumpV1VariableInfo(view: Any, dumpInfo: DumpInfo): void {
        try {
            if (view instanceof ExtendableComponent) {
                const viewOwnPropertyArray = view.getownedStateVariables();
                if (viewOwnPropertyArray === undefined) {
                    return;
                }
                viewOwnPropertyArray
                    .forEach((ownProperty) => {
                        if (ownProperty && ownProperty instanceof DecoratedV1VariableBase) {
                            dumpInfo.observedPropertiesInfo.push({
                                decorator: ownProperty.decorator,
                                propertyName: ownProperty.varName,
                                value: StateMgmtDFX.getRawValue(ownProperty),
                                syncPeers: [],
                                id: -1,
                                dependentElementIds: {
                                    mode: 'Compatible Mode',
                                    propertyDependencies: [],
                                    trackPropertiesDependencies: []
                                }
                            });
                        }
                    });
            }
        } catch(e) {
            StateMgmtConsole.warn(`dumpV1VariableInfo failed, error message is ${e.message}`);
        }
    }

    static dumpV2ComputedAndMonitor(view: Any, dumpInfo: DumpInfo): void {
        Object.getOwnPropertyNames(view as Object)
            .filter((varName) => {
                return (
                    varName.startsWith('__computed') ||
                    varName.startsWith('__monitor')
                );
            })
            .forEach((varName) => {
                const field = StateMgmtDFX.getField(varName, view as Object);
                if (field !== undefined) {
                    const value = field!.getValue(view as Object);
                    if (value && value instanceof ComputedDecoratedVariable) {
                        dumpInfo.observedPropertiesInfo.push({
                            decorator: value.decorator,
                            propertyName: value.varName,
                            value: StateMgmtDFX.getRawValue(value),
                            syncPeers: [],
                            id: -1,
                            dependentElementIds: {
                                mode: 'Compatible Mode',
                                propertyDependencies: [],
                                trackPropertiesDependencies: []
                            }
                        });
                    } else if (value && value instanceof MonitorFunctionDecorator) {
                        const propertyName = varName.replace('__monitor_', '');
                        dumpInfo.observedPropertiesInfo.push({
                            decorator: value.decorator,
                            propertyName: propertyName,
                            syncPeers: [],
                            id: -1,
                            dependentElementIds: {
                                mode: 'Compatible Mode',
                                propertyDependencies: [],
                                trackPropertiesDependencies: []
                            }
                        });
                    }
                }
            });
    }

    static dumpV2VariableInfo(view: Any, dumpInfo: DumpInfo): void {
        try {
            if (view instanceof ExtendableComponent) {
                const viewOwnPropertyArray = view.getownedStateVariables();
                if (viewOwnPropertyArray === undefined) {
                    return;
                }
                viewOwnPropertyArray
                    .forEach((ownProperty) => {
                        if (ownProperty && ownProperty instanceof DecoratedV2VariableBase) {
                            dumpInfo.observedPropertiesInfo.push({
                                decorator: ownProperty.decorator,
                                propertyName: ownProperty.varName,
                                value: StateMgmtDFX.getRawValue(ownProperty),
                                syncPeers: [],
                                id: -1,
                                dependentElementIds: {
                                    mode: 'Compatible Mode',
                                    propertyDependencies: [],
                                    trackPropertiesDependencies: []
                                }
                            });
                        }
                    });
                StateMgmtDFX.dumpV2ComputedAndMonitor(view, dumpInfo);
            }
        } catch(e) {
            StateMgmtConsole.warn(`dumpV2VariableInfo failed, error message is ${e.message}`);
        }
    }

    private static getType(item: Any): string {
        try {
            return (Class.of(item as Object)).toString();
        } catch (e) {
            StateMgmtConsole.warn(`Cannot get the type of current value, error message is: ${e.message}`);
            return 'unknown type';
        }
    }

    /**
     * Dump 10 items at most.
     * If length > 10, output will be the first 7 and last 3 items.
     * eg: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
     * output: [0, 1, 2, 3, 4, 5, 6, '...', 9, 10, 11]
     */
    private static dumpItems(arr: Array<Object>): Array<SimpleAndNonType> {
        const dumpArr = arr.slice(0, StateMgmtDFX.DUMP_MAX_LENGTH);
        if (arr.length > StateMgmtDFX.DUMP_MAX_LENGTH) {
            dumpArr.splice(StateMgmtDFX.DUMP_MAX_LENGTH - StateMgmtDFX.DUMP_LAST_LENGTH, 
                          StateMgmtDFX.DUMP_LAST_LENGTH, '...', 
                          ...arr.slice(-StateMgmtDFX.DUMP_LAST_LENGTH));
        }
        const dumpItemsArr: Array<SimpleAndNonType> = [];
        for (let i = 0; i < dumpArr.length; i++) {
            if (dumpArr[i] && typeof dumpArr[i] === 'object') {
                dumpItemsArr.push(StateMgmtDFX.getType(dumpArr[i]) as SimpleAndNonType);
            } else {
                dumpItemsArr.push(dumpArr[i] as SimpleAndNonType);
            }
        }
        return dumpItemsArr;
    }

    private static dumpMap(map: Map<Object, Object>): Array<[SimpleAndNonType, SimpleAndNonType]> {
        const dumpKey = StateMgmtDFX.dumpItems(Array.from(map.keys()));
        const dumpValue = StateMgmtDFX.dumpItems(Array.from(map.values()));
        const dumpMapArr: Array<[SimpleAndNonType, SimpleAndNonType]> = [];
        for (let i = 0; i < dumpKey.length; i++) {
            dumpMapArr.push([dumpKey[i], dumpValue[i]]);
        }
        return dumpMapArr;
    }

    private static dumpObjectProperty(value: Object): DumpObjectType | string {
        const tempObj: DumpObjectType = new Array<[string, Any]>();
        try {
            let properties: string[] = Object.getOwnPropertyNames(value);
            properties
                .slice(0, StateMgmtDFX.DUMP_MAX_PROPERTY_COUNT)
                .forEach((varName: string) => {
                    const field = StateMgmtDFX.getField(varName, value);
                    if (field !== undefined) {
                        const propertyValue = field!.getValue(value);
                        tempObj.push([varName, (propertyValue && typeof propertyValue === 'object') ? 
                                           StateMgmtDFX.getType(propertyValue) as Any : propertyValue as Any]);
                    }
                });
            if (properties.length > StateMgmtDFX.DUMP_MAX_PROPERTY_COUNT) {
                tempObj.push(['...', '...' as Any]);
            }
            return tempObj;
        } catch (e) {
            StateMgmtConsole.warn(`can not dump Obj, error message is ${e.message}`);
            return 'unknown type';
        }
    }

    /**
     * Get raw value from decorated variable
     */
    public static getRawValue<T>(prop: T): Any {
        try {
            let rawValue: T;
            
            // Check if it's a decorated variable and unwrap it
            if (prop instanceof DecoratedV1VariableBase) {
                rawValue = prop.get() as T;
            } else if (prop instanceof DecoratedV2VariableBase) {
                rawValue = prop.get() as T;
            } else {
                rawValue = prop;
            }
            
            // Return early for null, undefined, or non-object values (string, int, double, long, boolean)
            if (!rawValue || typeof rawValue !== 'object') {
                return rawValue as Any;
            }

            // Get original object
            rawValue = UIUtils.getTarget(rawValue);
            
            if (rawValue instanceof Map) {
                return StateMgmtDFX.dumpMap(rawValue as Any as Map<Object, Object>) as Any;
            } else if (rawValue instanceof Set) {
                return StateMgmtDFX.dumpItems(Array.from(rawValue.values()) as Any as Array<Object>) as Any;
            } else if (rawValue instanceof Array) {
                return StateMgmtDFX.dumpItems(Array.from(rawValue) as Any as Array<Object>) as Any;
            } else if (rawValue instanceof Date) {
                return rawValue as Any;
            } else {
                return StateMgmtDFX.dumpObjectProperty(rawValue as Any as Object) as Any;
            }
        } catch(e) {
            StateMgmtConsole.warn(`getRawValue failed, error message is ${e.message}`);
            return 'error value' as Any;
        }
    } 
}
