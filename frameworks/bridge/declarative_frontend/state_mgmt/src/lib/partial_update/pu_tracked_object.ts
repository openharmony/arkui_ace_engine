/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

// @Track class property decorator
// indicates to framework to track individual object property value changes
function Track(target: Object, property: string) {
  ConfigureStateMgmt.instance.usingPUObservedTrack(`@Track`, property);
  Reflect.set(target, `${TrackedObject.___TRACKED_PREFIX}${property}`, true);
  Reflect.set(target, TrackedObject.___IS_TRACKED_OPTIMISED, true);
  stateMgmtConsole.debug(`class ${target.constructor?.name}: property @Track ${property}`);
}

class TrackedObject {
  public static readonly ___IS_TRACKED_OPTIMISED = `___IS_TRACKED_OPTIMISED`;
  public static readonly ___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY = `___OPTI_TRACKED_ASSIGNMENT_FAKE_PROP_PROPERTY`;
  public static readonly ___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY = `___OPTI_TRACKED_ASSIGNMENT_FAKE_OBJLINK_PROPERTY`;
  public static readonly ___TRACKED_PREFIX = `___TRACKED_`;
  private static readonly ___TRACKED_PREFIX_LEN = TrackedObject.___TRACKED_PREFIX.length;

  public static isCompatibilityMode(obj: Object): boolean {
    return !obj || (typeof obj !== 'object') || !Reflect.has(obj, TrackedObject.___IS_TRACKED_OPTIMISED);
  }

  public static needsPropertyReadCb(obj: Object): boolean {
    return obj && (typeof obj === 'object') && Reflect.has(obj, TrackedObject.___IS_TRACKED_OPTIMISED);
  }

  /**
   * @Track new object assignment optimization
   * can apply if old and new value are object, instance of same class, do not use compat mode.
   * in this case function returns true and calls supplied notifyTrackedPropertyChanged cb function
   * for each @Tracked'ed property whose value actually changed. 
   * if optimisation can not be applied calls notifyPropertyChanged and returns false
   */
  public static notifyObjectValueAssignment(obj1: Object, obj2: Object,
    notifyPropertyChanged: (isFromSource) => void, // notify as assignment (none-optimised)
    notifyTrackedPropertyChange: (propName) => void, obSelf: ObservedPropertyAbstractPU<any>): boolean {
    if (!obj1 || !obj2 || (typeof obj1 !== 'object') || (typeof obj2 !== 'object') ||
      (obj1.constructor !== obj2.constructor) ||
      TrackedObject.isCompatibilityMode(obj1)) {
      stateMgmtConsole.debug(`TrackedObject.notifyObjectValueAssignment notifying change as assignment (non-optimised)`);
      notifyPropertyChanged.call(obSelf);
      return false;
    }

    stateMgmtConsole.debug(`TrackedObject.notifyObjectValueAssignment notifying actually changed properties (optimised)`);
    const obj1Raw = ObservedObject.GetRawObject(obj1);
    const obj2Raw = ObservedObject.GetRawObject(obj2);
    let shouldFakePropPropertyBeNotified: boolean = false;
    Object.keys(obj2Raw)
      .forEach(propName => {
        // Collect only @Track'ed changed properties
        if (Reflect.has(obj1Raw, `${TrackedObject.___TRACKED_PREFIX}${propName}`) &&
          (Reflect.get(obj1Raw, propName) !== Reflect.get(obj2Raw, propName))) {
          stateMgmtConsole.debug(`   ... '@Track ${propName}' value changed - notifying`);
          notifyTrackedPropertyChange.call(obSelf, propName);
          shouldFakePropPropertyBeNotified = true;
        } else {
          stateMgmtConsole.debug(`   ... '${propName}' value unchanged or not @Track'ed - not notifying`);
        }
      });
    // notify this non-existing object property has changed only if some of the tracked properties changed.
    // SynchedPropertyOneWay reset() report a 'read' on this property, thereby creating a dependency
    // reporting the property as changed causes @Prop sync from source
    if (shouldFakePropPropertyBeNotified) {
      stateMgmtConsole.debug(`   ... TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY - notifying`);
      notifyTrackedPropertyChange.call(obSelf, TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_PROP_PROPERTY);
    }

    // always notify this non-existing object property has changed for SynchedPropertyNestedObject as 
    // the object has changed in assigment.
    // SynchedPropertyNestedObject set() reports a 'read' on this property, thereby creating a dependency
    // reporting the property as changed causes @ObjectLink sync from source
    stateMgmtConsole.debug(`   ... TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY - notifying`);
    notifyTrackedPropertyChange.call(obSelf, TrackedObject.___TRACKED_OPTI_ASSIGNMENT_FAKE_OBJLINK_PROPERTY);
    return true;
  }
}