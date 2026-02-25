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
import { DecoratedV1VariableBase, DecoratedV2VariableBase, DecoratedVariableBase } from '../decoratorImpl/decoratorBase';
import { MonitorFunctionDecorator } from '../decoratorImpl/decoratorMonitor';
import { AceTrace } from '../../base/AceTrace';
import { UIUtils } from '../utils';
import { ExtendableComponent } from '../../component/extendableComponent';
import { MutableStateMeta } from '../base/mutableStateMeta';
import { IObservedObject } from '../decorator';
import { ElementInfo, DecoratorInfo, ObservedResult } from '../utils';
import { IncrementalNode } from '@koalaui/runtime';
import { PeerNode } from '../../PeerNode';
import { transferTypeName } from '../storage/persistenceV2';
import { InterfaceProxyHandler, StateMgmtTool } from './arkts';
import { ObserveWrappedBase } from '../base/observeWrappedBase';

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

class DFXDecoratorInfo {
    decorator?: string;
    propertyName?: string | Array<string>;
    value?: Any;
    syncPeers?: DFXDecoratorInfo[];
    id?: int;
    dependentElementIds?: PropertyDependenciesInfo;
}

export class DumpInfo {
    viewinfo: ViewInfo = new ViewInfo();
    observedPropertiesInfo: Array<DFXDecoratorInfo> = [];
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

    /**
     * Extract IObservedObject from a value if it is an observed object.
     * Handles both proxied objects and wrapped objects (Array/Map/Set/Date).
     * @param value The value to extract from
     * @returns The IObservedObject if the value is observed, otherwise undefined
     */
    public static getObservedObjectFromValue(value: Any): IObservedObject | undefined {
        if (!value || typeof value !== 'object') {
            return undefined;
        }

        // Check if it's an IObservedObject using instanceof
        if (value instanceof IObservedObject) {
            return value as IObservedObject;
        }
        const handler = StateMgmtTool.tryGetHandler(value as Object);
        if (StateMgmtTool.isInterfaceProxyHandler(handler)) {
            return handler as IObservedObject;
        }

        return undefined;
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
                        } else if (ownProperty && ownProperty instanceof ComputedDecoratedVariable) {
                            dumpInfo.observedPropertiesInfo.push({
                                decorator: ownProperty.decorator,
                                propertyName: ownProperty.varName,
                                value: StateMgmtDFX.getRawValue(ownProperty.get()),
                                syncPeers: [],
                                id: -1,
                                dependentElementIds: {
                                    mode: 'Compatible Mode',
                                    propertyDependencies: [],
                                    trackPropertiesDependencies: []
                                }
                            });
                        } else if (ownProperty && ownProperty instanceof MonitorFunctionDecorator) {
                            dumpInfo.observedPropertiesInfo.push({
                                decorator: ownProperty.decorator,
                                propertyName: StateMgmtDFX.getRawValue(ownProperty.path) as Array<string>,
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

    /**
     * Extract decorator information from a DecoratedVariableBase instance.
     * @internal
     */
    public static extractDecoratorInfoFromVariable(decoratedVar: DecoratedVariableBase): DecoratorInfo | undefined {
        try {
            // Get basic information from DecoratedVariableBase
            const decoratorName = decoratedVar.decorator;
            const stateVariableName = decoratedVar.varName;
            const owningView = decoratedVar.owningComponent;
            const dependentInfo = decoratedVar.getDependentInfo();
            // Get component information
            let owningComponentOrClassName = 'Unknown Component';
            let owningComponentId = -1;

            if (owningView && owningView instanceof ExtendableComponent) {
                const ex = owningView as ExtendableComponent;
                owningComponentId = ex.getUniqueId();
                owningComponentOrClassName = transferTypeName(Class.of(ex).getName());
                return {
                    decoratorName: decoratorName,
                    stateVariableName: stateVariableName,
                    owningComponentOrClassName: owningComponentOrClassName,
                    owningComponentId: owningComponentId,
                    dependentInfo: transferNodeInfoToElementInfo(dependentInfo)
                };
            }
            return undefined
        } catch (e) {
            StateMgmtConsole.warn(`Failed to extract decorator info: ${e.message}`);
            return undefined;
        }
    }

    /**
     * Extract dependent element information from a MutableStateMeta instance.
     * This accesses the dependency tracking through __metaDependency.
     * Note: MutableStateMeta does not contain decorator info, only dependency info.
     * @internal
     */
    public static extractDecoratorInfoFromMutableStateMeta(meta: MutableStateMeta): DecoratorInfo | undefined {
        try {
            const dependency = meta.getDependentNodeInfo() as Set<IncrementalNode> | undefined;
            let elementsInfo: Array<ElementInfo> = transferNodeInfoToElementInfo(dependency);
            elementsInfo = meta.getMonitorAndComputedInfo(elementsInfo);
            // Return minimal DecoratorInfo with dependency info only
            // MutableStateMeta doesn't have decorator-specific information
            return {
                decoratorName: '',
                stateVariableName: meta.info_,
                owningComponentOrClassName: '',
                owningComponentId: -1,
                dependentInfo: elementsInfo
            };
        } catch (e) {
            StateMgmtConsole.warn(`Failed to extract MutableStateMeta dependency info: ${e.message}`);
            return undefined;
        }
    }
}

function transferNodeInfoToElementInfo(nodes: Set<IncrementalNode> | undefined): Array<ElementInfo> {
    const dependentInfo: Array<ElementInfo> = [];
    if (nodes && nodes.size > 0) {
        nodes.forEach((node: IncrementalNode) => {
            const peer = node as PeerNode;
            const elementInfo = peer.getElementInfo();
            if (elementInfo) {
                dependentInfo.push(elementInfo);
            }
        });
    }
    return dependentInfo;
}

export enum ObservedType {
    NON,
    OBSERVED,
    TRACK,
    TRACE,
    BUILTIN_V1,
    BUILTIN_V2,
    BUILTIN_MAKEOBSERVED,
    INTERFACE_V1,
    INTERFACE_MAKEOBSERVED,
}

export function GetObservedTypeInfo(info: string): ObservedType {
    if (info.startsWith('__meta_')) {
        if (info.length === 7) {
            return ObservedType.OBSERVED;
        } else {
            return ObservedType.TRACK;
        }
    } else if (info.startsWith('__metaV2_')) {
        return ObservedType.TRACE;
    } else if (info.startsWith('__metaInterfaceV1_')) {
        return ObservedType.INTERFACE_V1;
    } else if (info.startsWith('__metaInterfaceMakeObserved_')) {
        return ObservedType.INTERFACE_MAKEOBSERVED;
    } else if (info.startsWith('__metaBuiltInV1Key_') || info.startsWith('__metaBuiltInV1_')) {
        return ObservedType.BUILTIN_V1;
    } else if (info.startsWith('__metaBuiltInV2Key_')) {
        return ObservedType.BUILTIN_V2;
    } else if (info.startsWith('__metaMakeObservedKey_') || info.startsWith('__metaBuiltInMakeObserved_')) {
        return ObservedType.BUILTIN_MAKEOBSERVED;
    } else {
        return ObservedType.NON;
    }
}

export enum ObservedReason {
    V1_UI = 'The object data is decorated with @Observed',
    V2_UI = 'The object data is decorated with V2 @ObservedV2 and @Trace',
    INTERFACE_UI = 'The object data is object literal decorated with V1 decorators or wrapped by makeObserved',
    BUILTIN_UI = 'The object data is built-in type data (Array/Map/Set/Date) decorated with V1/V2 decorators or wrapped by makeObserved',
    V1_NO_UI = 'The object data is decorated with @Observed, but not used in UI',
    V2_NO_UI = 'The object data is decorated with V2 @ObservedV2 and @Trace, but not used in UI',
    INTERFACE_NO_UI = 'The object data is object literal decorated with V1 decorators or wrapped by makeObserved, but not used in UI',
    BUILTIN_NO_UI = 'The object data is built-in type data (Array/Map/Set/Date) decorated with V1/V2 decorators or wrapped by makeObserved, but not used in UI',
    NOT_OBSERVED = 'The object data is not an observable object'
}

export class ObservedObjectInfo {
    private bindingDecoratedVariables: Set<DecoratedVariableBase> | undefined = undefined;
    private bindingMutableStateMeta: Set<MutableStateMeta> | undefined = undefined;
    private observedType: ObservedType | undefined = undefined;

    public setType(name: string): void {
        this.observedType = GetObservedTypeInfo(name);
    }

    public registerDecoratedVariable(base: DecoratedVariableBase): void {
        if (!this.bindingDecoratedVariables) {
            this.bindingDecoratedVariables = new Set<DecoratedVariableBase>();
        }
        this.bindingDecoratedVariables!.add(base);
    }

    public unregisterDecoratedVariable(base: DecoratedVariableBase): void {
        if (this.bindingDecoratedVariables) {
            this.bindingDecoratedVariables!.delete(base);
        }
    }

    public registerMutableStateMeta(meta: MutableStateMeta): void {
        if (!this.bindingMutableStateMeta) {
            this.bindingMutableStateMeta = new Set<MutableStateMeta>();
        }
        this.bindingMutableStateMeta!.add(meta);
    }

    public unregisterMutableStateMeta(meta: MutableStateMeta): void {
        this.bindingMutableStateMeta?.delete(meta);
    }

    public getDecoratedVariables(): Set<DecoratedVariableBase> | undefined {
        return this.bindingDecoratedVariables;
    }

    public getMutableStateMetas(): Set<MutableStateMeta> | undefined {
        return this.bindingMutableStateMeta;
    }

    public getObservedType(): ObservedType | undefined {
        return this.observedType;
    }
    public addV1InnerRef(): void {
        if (!(this.observedType === ObservedType.OBSERVED)) {
            return;
        }
        this.bindingMutableStateMeta?.forEach((meta) => {
            meta.addRef();
        });
    }
}

export class ObservedObjectRegistry {
    private static registry: WeakMap<IObservedObject, ObservedObjectInfo> = new WeakMap<IObservedObject, ObservedObjectInfo>();

    public static getOrRegister(observed: IObservedObject): ObservedObjectInfo {
        if (ObservedObjectRegistry.registry.has(observed)) {
            return ObservedObjectRegistry.registry.get(observed)!;
        }
        const info = new ObservedObjectInfo();
        ObservedObjectRegistry.registry.set(observed, info);
        return info;
    }

    public static get(observed: IObservedObject | undefined): ObservedObjectInfo | undefined {
        return observed ? ObservedObjectRegistry.registry.get(observed!) : undefined;
    }

    /**
     * Register a decorated variable to an observed object.
     * This establishes the relationship: DecoratedVariable uses IObservedObject.
     */
    public static registerDecoratedVariable(observed: IObservedObject, base: DecoratedVariableBase): void {
        const info = ObservedObjectRegistry.getOrRegister(observed);
        info.registerDecoratedVariable(base);
    }

    /**
     * Unregister a decorated variable from an observed object.
     * This removes the relationship: DecoratedVariable uses IObservedObject.
     */
    public static unregisterDecoratedVariable(observed: IObservedObject, base: DecoratedVariableBase): void {
        const info = ObservedObjectRegistry.get(observed);
        if (info) {
            info.unregisterDecoratedVariable(base);
        }
    }

    /**
     * Update the registration when a decorated variable changes its value.
     * Unregisters from the old value and registers to the new value.
     * @param oldValue The old observed object value (can be undefined or non-object)
     * @param newValue The new observed object value (can be undefined or non-object)
     * @param base The decorated variable that is changing
     */
    public static updateDecoratedVariableRegistration(oldValue: Any, newValue: Any, base: DecoratedVariableBase): void {
        // Unregister from old value if it was an observed object
        const oldObserved = StateMgmtDFX.getObservedObjectFromValue(oldValue);
        if (oldObserved) {
            ObservedObjectRegistry.unregisterDecoratedVariable(oldObserved!, base);
        }

        // Register to new value if it is an observed object
        const newObserved = StateMgmtDFX.getObservedObjectFromValue(newValue);
        if (newObserved) {
            ObservedObjectRegistry.registerDecoratedVariable(newObserved!, base);
        }
    }

    /**
     * Register a MutableStateMeta to an observed object.
     * This establishes the relationship: MutableStateMeta uses IObservedObject.
     */
    public static registerMutableStateMeta(observed: IObservedObject, meta: MutableStateMeta): void {
        const info = ObservedObjectRegistry.getOrRegister(observed);
        info.registerMutableStateMeta(meta);
    }

    /**
     * Unregister a MutableStateMeta from an observed object.
     * This removes the relationship: MutableStateMeta uses IObservedObject.
     */
    public static unregisterMutableStateMeta(observed: IObservedObject, meta: MutableStateMeta): void {
        const info = ObservedObjectRegistry.get(observed);
        if (info) {
            info.unregisterMutableStateMeta(meta);
        }
    }
}

/**
 * Check if an object can be observed by the state management framework.
 * This function analyzes the object and returns detailed information about
 * its relationship with decorators and components.
 *
 * @param obj The object to check
 * @returns ObservedResult containing observation status and related information
 */
export function canBeObserved(obj: Object): ObservedResult {
    // Step 1: Check if the object is an IObservedObject
    const observed = StateMgmtDFX.getObservedObjectFromValue(obj);
    if (!observed) {
        return {
            isObserved: false,
            reason: ObservedReason.NOT_OBSERVED,
            decoratorInfo: []
        };
    }

    // Step 2: Get ObservedObjectInfo from registry
    const objectInfo = ObservedObjectRegistry.get(observed);
    if (!objectInfo) {
        return {
            isObserved: false,
            reason: ObservedReason.NOT_OBSERVED,
            decoratorInfo: []
        };
    }

    // Step 3: Collect all decorator information
    const decoratorInfoArray: Array<DecoratorInfo> = [];

    // 3.1: Process DecoratedVariableBase (V1 and V2 decorators)
    const decoratedVariables = objectInfo.getDecoratedVariables() as Set<DecoratedVariableBase> | undefined;
    if (decoratedVariables && decoratedVariables.size > 0) {
        decoratedVariables!.forEach((decoratedVar: DecoratedVariableBase) => {
            const info = StateMgmtDFX.extractDecoratorInfoFromVariable(decoratedVar);
            if (info) {
                decoratorInfoArray.push(info);
            }
        });
    }
    const observedType0 = objectInfo.getObservedType() as ObservedType | undefined;
    if (!observedType0) {
        return {
            isObserved: false,
            reason: ObservedReason.NOT_OBSERVED,
            decoratorInfo: []
        };
    }
    const observedType = observedType0 as ObservedType;
    let reason = ObservedReason.NOT_OBSERVED;
    if (observedType === ObservedType.OBSERVED || observedType === ObservedType.BUILTIN_V1 || observedType === ObservedType.INTERFACE_V1) {
        return extractMixusageCaseForV1Result(objectInfo, decoratorInfoArray, observedType, observed);
    }

    if (observedType === ObservedType.TRACK || observedType === ObservedType.INTERFACE_MAKEOBSERVED || observedType === ObservedType.TRACE ||
            observedType === ObservedType.BUILTIN_V2 || observedType === ObservedType.BUILTIN_MAKEOBSERVED) {
        return extractMetaInfos(objectInfo, observedType, observed);
    }

    return {
        isObserved: false,
        reason: reason,
        decoratorInfo: []
    };
}

const V2Decorators: Set<string> = new Set<string>(['@Local', '@Param', '@Provider', '@Consumer', '@Param @Once']);
const ObservedTypeToDecoratorName: Map<ObservedType, string> = new Map<ObservedType, string>([
    [ObservedType.OBSERVED, '@Observed(mix used in V2)'],
    [ObservedType.INTERFACE_V1, 'V1 Decorated ObjectLiteral(mix used in V2)'],
    [ObservedType.BUILTIN_V1, 'V1 Decorated BuiltInType(mix used in V2)'],
    [ObservedType.TRACK, '@Track'],
    [ObservedType.TRACE, '@Trace'],
    [ObservedType.INTERFACE_MAKEOBSERVED, 'MakeObserved'],
    [ObservedType.BUILTIN_MAKEOBSERVED, 'MakeObserved'],
    [ObservedType.BUILTIN_V2, 'V2 Decorated BuiltInType']
]);

const V1CaseMixusageStateVariableName: Map<ObservedType, string> = new Map<ObservedType, string>([
    [ObservedType.OBSERVED, 'Unknown @Observed Object Property'],
    [ObservedType.INTERFACE_V1, 'Unknown Object Literal Property'],
    [ObservedType.BUILTIN_V1, 'Unknown BuiltIn Object Property']
]);

const ObservedTypeToReasonUI: Map<ObservedType, ObservedReason> = new Map<ObservedType, ObservedReason>([
    [ObservedType.OBSERVED, ObservedReason.V1_UI],
    [ObservedType.TRACK, ObservedReason.V1_UI],
    [ObservedType.INTERFACE_V1, ObservedReason.INTERFACE_UI],
    [ObservedType.BUILTIN_V1, ObservedReason.BUILTIN_UI],
    [ObservedType.TRACE, ObservedReason.V2_UI],
    [ObservedType.BUILTIN_V2, ObservedReason.BUILTIN_UI],
    [ObservedType.INTERFACE_MAKEOBSERVED, ObservedReason.INTERFACE_UI],
    [ObservedType.BUILTIN_MAKEOBSERVED, ObservedReason.BUILTIN_UI]
]);

const ObservedTypeToReasonNOUI: Map<ObservedType, ObservedReason> = new Map<ObservedType, ObservedReason>([
    [ObservedType.OBSERVED, ObservedReason.V1_NO_UI],
    [ObservedType.TRACK, ObservedReason.V1_NO_UI],
    [ObservedType.INTERFACE_V1, ObservedReason.INTERFACE_NO_UI],
    [ObservedType.BUILTIN_V1, ObservedReason.BUILTIN_NO_UI],
    [ObservedType.TRACE, ObservedReason.V2_NO_UI],
    [ObservedType.BUILTIN_V2, ObservedReason.BUILTIN_NO_UI],
    [ObservedType.INTERFACE_MAKEOBSERVED, ObservedReason.INTERFACE_NO_UI],
    [ObservedType.BUILTIN_MAKEOBSERVED, ObservedReason.BUILTIN_NO_UI]
]);

function extractMixusageCaseForV1Result(objectInfo: ObservedObjectInfo,
    decoratorInfoArray: Array<DecoratorInfo>, observedType: ObservedType, obj: Object): ObservedResult {
    const infoArrays: ElementInfoAndMetaArray = collectElementInfoAndMetaArray(objectInfo);
    const elementInfos = infoArrays.elementInfos;
    const metaInfos = infoArrays.metaInfos;
    const clearArrays = filterAndClearDecoratorInfo(decoratorInfoArray, elementInfos);

    if (elementInfos.size > 0) {
        processMetaInfosWhenElementsExist(metaInfos, elementInfos, observedType, obj, clearArrays);
    }

    const elementsCount = calculateElementsCount(clearArrays);

    return {
        isObserved: true,
        reason: elementsCount > 0 ? ObservedTypeToReasonUI.get(observedType)! : ObservedTypeToReasonNOUI.get(observedType)!,
        decoratorInfo: clearArrays
    };
}

interface ElementInfoAndMetaArray {
    elementInfos: Map<int, ElementInfo>;
    metaInfos: Array<DecoratorInfo>;
}

function collectElementInfoAndMetaArray(objectInfo: ObservedObjectInfo): ElementInfoAndMetaArray {
    const elementInfos = new Map<int, ElementInfo>();
    const metaInfos: Array<DecoratorInfo> = [];
    const mutableStateMetas = objectInfo.getMutableStateMetas();

    if (!mutableStateMetas || mutableStateMetas.size === 0) {
        return { elementInfos, metaInfos };
    }

    mutableStateMetas.forEach((meta: MutableStateMeta) => {
        const info = StateMgmtDFX.extractDecoratorInfoFromMutableStateMeta(meta);
        if (info) {
            info.dependentInfo.forEach((element) => {
                elementInfos.set(element.elementId, element);
            });
            metaInfos.push(info);
        }
    });

    return { elementInfos: elementInfos, metaInfos: metaInfos };
}

function filterAndClearDecoratorInfo(decoratorInfoArray: Array<DecoratorInfo>, elementInfos: Map<int, ElementInfo>): Array<DecoratorInfo> {
    const clearArrays: Array<DecoratorInfo> = [];
    decoratorInfoArray.forEach((info) => {
        if (!V2Decorators.has(info.decoratorName)) {
            info.dependentInfo.forEach((element) => {
                elementInfos.delete(element.elementId);
            });
            clearArrays.push(info);
        }
    });
    return clearArrays;
}

function processMetaInfosWhenElementsExist(
    metaInfos: Array<DecoratorInfo>,
    elementInfos: Map<int, ElementInfo>,
    observedType: ObservedType,
    obj: Object,
    clearArrays: Array<DecoratorInfo>
): void {
    if (!metaInfos || metaInfos.length === 0) {
        return;
    }

    if (metaInfos.length !== 1 && observedType !== ObservedType.BUILTIN_V1) {
        return;
    }

    metaInfos.forEach((meta) => {
        const related = filterRelatedElements(meta.dependentInfo, elementInfos);
        if (related.length === 0) {
            return;
        }

        updateMetaInfo(meta, related, observedType, obj);
        clearArrays.push(meta);
    });
}

function filterRelatedElements(dependentInfo: Array<ElementInfo>, elementInfos: Map<int, ElementInfo>): Array<ElementInfo> {
    const related: Array<ElementInfo> = [];
    dependentInfo.forEach((element) => {
        if (elementInfos.has(element.elementId)) {
            related.push(element);
        }
    });
    return related;
}

function updateMetaInfo(meta: DecoratorInfo, related: Array<ElementInfo>, observedType: ObservedType, obj: Object): void {
    meta.dependentInfo = related;
    meta.decoratorName = ObservedTypeToDecoratorName.get(observedType)!;

    if (meta.stateVariableName === '__metaBuiltInV1_WrappedDate') {
        meta.stateVariableName = 'Date Inner Property';
    } else {
        meta.stateVariableName = (observedType === ObservedType.BUILTIN_V1)
            ? meta.stateVariableName : V1CaseMixusageStateVariableName.get(observedType)!;
    }

    meta.owningComponentId = -1;
    meta.owningComponentOrClassName = determineClassName(observedType, obj);
}

function calculateElementsCount(decoratorInfos: Array<DecoratorInfo>): int {
    let elementsCount: int = 0;
    decoratorInfos.forEach((meta) => {
        elementsCount += meta.dependentInfo.length;
    });
    return elementsCount;
}

function determineVariableNameByType(observedType: ObservedType, info: string): string {
    if (observedType === ObservedType.TRACK) {
        return info.substring(7);
    } else if (observedType === ObservedType.TRACE) {
        return info.substring(9);
    } else if (observedType === ObservedType.BUILTIN_V2) {
        if (info === '__metaBuiltInV2Key_WrappedDate') {
            return 'Date Inner Property';
        }
        return info;
    } else if (observedType === ObservedType.BUILTIN_MAKEOBSERVED) {
        if (info === '__metaBuiltInMakeObserved_WrappedDate') {
            return 'Date Inner Property';
        }
        return info;
    } else if (observedType === ObservedType.INTERFACE_MAKEOBSERVED) {
        return 'Unknown Object Literal Property';
    } else {
        return 'Unknown Variable Name';
    }
}

function determineClassName(observedType: ObservedType, obj: Object): string {
    if (observedType === ObservedType.TRACK) {
        return transferTypeName(Class.of(obj).getName());
    } else if (observedType === ObservedType.OBSERVED) {
        return transferTypeName(Class.of(obj).getName());
    } else if (observedType === ObservedType.INTERFACE_MAKEOBSERVED) {
        return transferTypeName(Class.of((obj as InterfaceProxyHandler).target).getName());
    } else if (observedType === ObservedType.TRACE) {
        return transferTypeName(Class.of(obj).getName());
    } else if (observedType === ObservedType.BUILTIN_V2) {
        return transferTypeName(Class.of((obj as ObserveWrappedBase).getRaw()).getName());
    } else if (observedType === ObservedType.BUILTIN_MAKEOBSERVED) {
        return transferTypeName(Class.of((obj as ObserveWrappedBase).getRaw()).getName());
    } else if (observedType === ObservedType.BUILTIN_V1) {
        return transferTypeName(Class.of((obj as ObserveWrappedBase).getRaw()).getName());
    } else if (observedType === ObservedType.INTERFACE_V1) {
        return transferTypeName(Class.of((obj as InterfaceProxyHandler).target).getName());
    } else {
        return 'Unknown Class Name';
    }
}

function extractMetaInfos(objectInfo: ObservedObjectInfo, observedType: ObservedType, obj: Object): ObservedResult {
    const metaInfos: Array<DecoratorInfo> = [];
    let elementsCount: int = 0;
    const mutableStateMetas = objectInfo.getMutableStateMetas();
    if (mutableStateMetas && mutableStateMetas.size > 0) {
        mutableStateMetas.forEach((meta: MutableStateMeta) => {
            const info = StateMgmtDFX.extractDecoratorInfoFromMutableStateMeta(meta);
            if (info) {
                info.decoratorName = ObservedTypeToDecoratorName.get(observedType)!;
                info.stateVariableName = determineVariableNameByType(observedType, meta.info_);
                info.owningComponentId = -1;
                info.owningComponentOrClassName = determineClassName(observedType, obj);
                metaInfos.push(info);
                elementsCount += info.dependentInfo.length;
            }
        });
    }

    return {
        isObserved: true,
        reason: elementsCount > 0 ? ObservedTypeToReasonUI.get(observedType)! : ObservedTypeToReasonNOUI.get(observedType)!,
        decoratorInfo: metaInfos
    }
}