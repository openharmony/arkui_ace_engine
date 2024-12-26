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
class stateMgmtDFX {
  // enable profile
  public static enableProfiler: boolean = false;
  public static inRenderingElementId: Array<number> = new Array<number>();
  private static readonly DUMP_MAX_PROPERTY_COUNT: number = 50;
  private static readonly DUMP_MAX_LENGTH: number = 10;
  private static readonly DUMP_LAST_LENGTH: number = 3;
  public static enableDebug: boolean = false;

  public static getObservedPropertyInfo<T>(observedProp: ObservedPropertyAbstractPU<T>, isProfiler: boolean,
    changedTrackPropertyName?: string): ObservedPropertyInfo<T> {
    return {
      decorator: observedProp.debugInfoDecorator(), propertyName: observedProp.info(), id: observedProp.id__(),
      changedTrackPropertyName: changedTrackPropertyName,
      value: stateMgmtDFX.getRawValue(observedProp),
      inRenderingElementId: stateMgmtDFX.inRenderingElementId.length === 0 ?
        -1 : stateMgmtDFX.inRenderingElementId[stateMgmtDFX.inRenderingElementId.length - 1],
      dependentElementIds: observedProp.dumpDependentElmtIdsObj(typeof observedProp.getUnmonitored() === 'object' ?
        !TrackedObject.isCompatibilityMode(observedProp.getUnmonitored()) : false, isProfiler),
      owningView: observedProp.getOwningView(),
      length: stateMgmtDFX.getRawValueLength(observedProp),
      syncPeers: observedProp.dumpSyncPeers(isProfiler, changedTrackPropertyName)
    };
  }

  /**
   * Dump decorated variable for v1 and v2
   *
   * @param view viewPU or ViewV2
   * @param dumpInfo contains state variable decorator, propertyName, etc.
   */
  public static getDecoratedVariableInfo(view: PUV2ViewBase, dumpInfo: DumpInfo): void {
    if (view instanceof ViewV2) {
      stateMgmtDFX.dumpV2VariableInfo(view, dumpInfo);
    } else if (view instanceof ViewPU) {
      stateMgmtDFX.dumpV1VariableInfo(view, dumpInfo);
    }
  }

  private static dumpV1VariableInfo(view: ViewPU, dumpInfo: DumpInfo): void {
    Object.getOwnPropertyNames(view)
      .filter((varName: string) => varName.startsWith('__') && !varName.startsWith(ObserveV2.OB_PREFIX))
      .forEach((varName) => {
        const prop: any = Reflect.get(view, varName);
        if (typeof prop === 'object' && 'debugInfoDecorator' in prop) {
          const observedProp: ObservedPropertyAbstractPU<any> = prop as ObservedPropertyAbstractPU<any>;
          dumpInfo.observedPropertiesInfo.push(stateMgmtDFX.getObservedPropertyInfo(observedProp, false));
        }
      });
  }

  private static dumpV2VariableInfo(view: ViewV2, dumpInfo: DumpInfo): void {
    const meta = view[ObserveV2.V2_DECO_META];
    // no decorated variables, return view info directly
    if (!meta) {
      return;
    }
    Object.getOwnPropertyNames(meta)
      .filter((varName) => !varName.startsWith(ProviderConsumerUtilV2.ALIAS_PREFIX)) // remove provider & consumer prefix
      .forEach((varName) => {
        dumpInfo.observedPropertiesInfo.push(stateMgmtDFX.dumpSingleV2VariableInfo(view, varName, meta));
      });
  }

  private static dumpSingleV2VariableInfo<T>(view: ViewV2, varName: string, meta: Object): ObservedPropertyInfo<T> {
    let decorators: string = '';
    const decorator: any = Reflect.get(meta, varName);
    let prop: any = Reflect.get(view, ObserveV2.OB_PREFIX + varName);
    if ('deco' in decorator) {
      decorators = decorator.deco as string;
      if (decorators === '@Consumer') {
        prop = Reflect.get(view, varName);
      }
      if (decorators === '@Computed') {
        prop = Reflect.get(view, ComputedV2.COMPUTED_CACHED_PREFIX + varName);
      }
      if (decorators === '@Monitor' || decorators === '@Event') {
        prop = `${Reflect.get(view, varName)}`;
      }
    }
    if ('deco2' in decorator) {
      decorators += decorator.deco2 as string;
    }
    if ('aliasName' in decorator) {
      decorators += `(${decorator.aliasName})`;
    }
    let dependentElmIds: Set<number> | undefined = undefined;
    if (view[ObserveV2.SYMBOL_REFS]) {
      dependentElmIds = view[ObserveV2.SYMBOL_REFS][varName];
    }

    return {
      decorator: decorators, propertyName: varName, id: -1, value: stateMgmtDFX.getRawValue(prop),
      dependentElementIds:
        { mode: 'V2', trackPropertiesDependencies: [], propertyDependencies: stateMgmtDFX.dumpDepenetElementV2(dependentElmIds) }
      , syncPeers: []
    };
  }

  private static dumpDepenetElementV2(dependentElmIds: Set<number> | undefined): string[] {
    let dumpElementIds: string[] = [];
    dependentElmIds?.forEach((elmtId: number) => {
      if (elmtId < ComputedV2.MIN_COMPUTED_ID) {
        dumpElementIds.push(ObserveV2.getObserve().getElementInfoById(elmtId));
      } else if (elmtId < MonitorV2.MIN_WATCH_ID) {
        dumpElementIds.push(`@Computed ${ObserveV2.getObserve().getComputedInfoById(elmtId)}`);
      } else if (elmtId < PersistenceV2Impl.MIN_PERSISTENCE_ID) {
        dumpElementIds.push(`@Monitor ${ObserveV2.getObserve().getMonitorInfoById(elmtId)}`);
      } else {
        dumpElementIds.push(`PersistenceV2[${elmtId}]`);
      }
    });
    return dumpElementIds;
  }

  private static getType(item: RawValue): string {
    try {
      return Object.prototype.toString.call(item);
    } catch (e) {
      stateMgmtConsole.warn(`Cannot get the type of current value, error message is: ${e.message}`);
      return 'unknown type';
    }
  }

  /**
   * Dump 10 items at most.
   * If length > 10, the output will be the first 7 and last 3 items.
   * eg: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
   * output: [0, 1, 2, 3, 4, 5, 6, '...', 9, 10, 11]
   * 
   */
  private static dumpItems(arr: Array<RawValue>): Array<DumpBuildInType> {
    let dumpArr = arr.slice(0, stateMgmtDFX.DUMP_MAX_LENGTH);
    if (arr.length > stateMgmtDFX.DUMP_MAX_LENGTH) {
      dumpArr.splice(stateMgmtDFX.DUMP_MAX_LENGTH - stateMgmtDFX.DUMP_LAST_LENGTH, stateMgmtDFX.DUMP_LAST_LENGTH, '...', ...arr.slice(-stateMgmtDFX.DUMP_LAST_LENGTH));
    }
    return dumpArr.map(item => typeof item === 'object' ? this.getType(item) : item);
  }

  private static dumpMap(map: Map<RawValue, RawValue>): Array<DumpBuildInType> {
    let dumpKey = this.dumpItems(Array.from(map.keys()));
    let dumpValue = this.dumpItems(Array.from(map.values()));
    return dumpKey.map((item: any, index: number) => [item, dumpValue[index]])
  }

  private static dumpObjectProperty(value: any): DumpObjectType | string {
    let tempObj: DumpObjectType = {};
    try {
      let properties: string[] = Object.getOwnPropertyNames(value);
      properties
        .slice(0, stateMgmtDFX.DUMP_MAX_PROPERTY_COUNT)
        .forEach((varName: string) => {
          const propertyValue = Reflect.get(value as Object, varName);
          tempObj[varName] = typeof propertyValue === 'object' ? this.getType(propertyValue) : propertyValue;
        });
      if (properties.length > stateMgmtDFX.DUMP_MAX_PROPERTY_COUNT) {
        tempObj['...'] = '...';
      }
    } catch (e) {
      stateMgmtConsole.warn(`can not dump Obj, error msg ${e.message}`);
      return "unknown type";
    }
    return tempObj;
  }

  private static getRawValue<T>(prop: T): DumpObjectType | Array<DumpBuildInType> | T | string {
    let rawValue: T;
    if (prop instanceof ObservedPropertyAbstract) {
      let wrappedValue: T = prop.getUnmonitored();
      rawValue = ObservedObject.GetRawObject(wrappedValue);
    } else {
      rawValue = ObserveV2.IsProxiedObservedV2(prop) ? prop[ObserveV2.SYMBOL_PROXY_GET_TARGET] : prop;
    }
    if (typeof rawValue !== 'object') {
      return rawValue;
    }
    if (rawValue instanceof Map) {
      return stateMgmtDFX.dumpMap(rawValue);
    } else if (rawValue instanceof Set) {
      return stateMgmtDFX.dumpItems(Array.from(rawValue.values()));
    } else if (rawValue instanceof Array) {
      return stateMgmtDFX.dumpItems(Array.from(rawValue));
    } else if (rawValue instanceof Date) {
      return rawValue;
    } else {
      return stateMgmtDFX.dumpObjectProperty(rawValue);
    }
  }

  private static getRawValueLength<T>(observedProp: ObservedPropertyAbstractPU<T>): number {
    let wrappedValue: T = observedProp.getUnmonitored();
    if (typeof wrappedValue !== 'object') {
      return -1;
    }
    let rawObject: T = ObservedObject.GetRawObject(wrappedValue);
    if (rawObject instanceof Map || rawObject instanceof Set) {
      return rawObject.size;
    } else if (rawObject instanceof Array) {
      return rawObject.length;
    }
    try {
      return Object.getOwnPropertyNames(rawObject).length;
    } catch (e) {
      return -1;
    }
  }
}

function setProfilerStatus(profilerStatus: boolean): void {
  stateMgmtConsole.warn(`${profilerStatus ? `start` : `stop`} stateMgmt Profiler`);
  stateMgmtDFX.enableProfiler = profilerStatus;
}
type PropertyDependenciesInfo = {
  mode: string,
  trackPropertiesDependencies: MapItem<string, Array<ElementType | number | string>>[],
  propertyDependencies: Array<ElementType | string>
}

type ElementType = {
  elementId: number,
  elementTag: string,
  isCustomNode: boolean,
}

// Data struct send to profiler or Inspector
type ViewPUInfo = {
  componentName: string, id: number, isV2?: boolean,
  isCompFreezeAllowed_?: boolean, isViewActive_?: boolean
};
type ObservedPropertyInfo<T> = {
  decorator: string, propertyName: string, value: any, id: number, changeId?: number, inRenderingElementId?: number,
  changedTrackPropertyName?: string | undefined,
  dependentElementIds: PropertyDependenciesInfo,
  length?: number
  owningView?: ViewPUInfo, syncPeers?: ObservedPropertyInfo<T>[]
};

type SimpleType = string | number | boolean;
type DumpObjectType = Record<string, SimpleType>;
type DumpBuildInType = Array<SimpleType> | Array<[SimpleType, SimpleType]>;
type RawValue = any;

class DumpInfo {
  public viewInfo?: ViewPUInfo;
  public observedPropertiesInfo: ObservedPropertyInfo<any>[] = []
}

// global function used to throw error in Promise
declare function _arkUIUncaughtPromiseError(error: any);

function setAceDebugMode(): void {
  stateMgmtDFX.enableDebug = true;
}

class aceDebugTrace {
  public static begin(...args: any): void {
    if (stateMgmtDFX.enableDebug) {
      aceTrace.begin(...args);
    }
  }
  public static end(): void {
    if (stateMgmtDFX.enableDebug) {
      aceTrace.end();
    }
  }
}