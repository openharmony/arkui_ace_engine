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

  private static getRawValue<T>(observedProp: ObservedPropertyAbstractPU<T>): DumpObjectType | Array<DumpBuildInType> | T | string {
    let wrappedValue: T = observedProp.getUnmonitored();
    if (typeof wrappedValue !== 'object') {
      return wrappedValue;
    }
    let rawObject: T = ObservedObject.GetRawObject(wrappedValue);
    if (rawObject instanceof Map) {
      return stateMgmtDFX.dumpMap(rawObject);
    } else if (rawObject instanceof Set) {
      return stateMgmtDFX.dumpItems(Array.from(rawObject.values()));
    } else if (rawObject instanceof Array) {
      return stateMgmtDFX.dumpItems(Array.from(rawObject));
    } else if (rawObject instanceof Date) {
      return rawObject;
    } else {
      return stateMgmtDFX.dumpObjectProperty(rawObject);
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
  propertyDependencies: Array<ElementType>
}

type ElementType = {
  elementId: number,
  elementTag: string,
  isCustomNode: boolean,
}

// Data struct send to profiler or Inspector
type ViewPUInfo = { componentName: string, id: number };
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