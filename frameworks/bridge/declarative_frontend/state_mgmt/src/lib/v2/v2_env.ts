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

/**
 * Internal System Environment Management (statemgmt framework)
 *
 * This file is **internal to the statemgmt framework** and is not exposed
 * to application code or external repositories.
 *
 * Purpose:
 * - Maintain a central registry of environment property instances
 * - Provide a controlled mechanism for creating and registering environment values
 * - Use `envFactoryMap` to ensure consistent construction of environment value objects
 *
 * Notes:
 * - Environment definitions and factory map (`EnvTypeMap` and `envFactoryMap`)
 *   are expected to come from the platform environment provider layer.
 * - This registry acts only as an internal store and initializer for EnvV2.
 */

/**
 * key -> EnvValue
 * eg. 'System.Breakpoint' -> IEnvironmentValue<WindowSizeLayoutBreakpointInfo>
 * In the same UIContext, one key corresponds to one instance.
 */
type EnvRegistry = { [K in keyof EnvTypeMap]?: IEnvironmentValue<EnvTypeMap[K]> };

// UIContext id -> EnvRegistry
// need to be unregister when UIContext destroyed
type SystemEnvRegistry = { number?: EnvRegistry };

// varName -> envKey
// key -> [ varName0, varName1, ..., varNameN ]
interface EnvMeta {
  // varName -> envKey
  varToKey: Record<string, string>;
  // key -> [ varName0, varName1, ..., varNameN ]
  keyToVars: Record<string, string[]>;
}

/**
 * EnvV2
 *
 * Internal environment manager for statemgmt.
 *
 * Responsibilities:
 * - Keep a singleton registry of all environment values used in the framework
 * - Initialize environment values via the `envFactoryMap` factories
 * - Allow internal code to register an environment value for a given key
 *
 */
class EnvV2 {
  private static envValues: SystemEnvRegistry = {};
  public static readonly ENV_DECO_META = Symbol('__env_deco_meta__');
  public static readonly ENV_KEY_PREFIX: string = '__env_key__';


  public static addEnvKeyVariableDecoMeta<K extends string>(proto: Object, varName: string, key: K): void {
    // add decorator meta data to prototype
  const meta = proto[EnvV2.ENV_DECO_META] ??= {
    varToKey: {},
    keyToVars: {},
  } as EnvMeta;
    // find varName -> key
    meta.varToKey[varName] = key ;
    const prefixKey: string = `${EnvV2.ENV_KEY_PREFIX}${key}`;
    // key -> [varName1, varName2,..., varNameN]
    (meta.keyToVars[prefixKey] ??= []).push(varName);
  }

  public static getEnvVarNameFromView<K extends string>(key: K, view: ViewBuildNodeBase): Array<string> | undefined {
    const meta = view[EnvV2.ENV_DECO_META];
    if (!meta) {
      return undefined;
    }

    const prefixKey: string = `${EnvV2.ENV_KEY_PREFIX}${key}`;
    const varNames = meta.keyToVars[prefixKey];
    if (!varNames || !Array.isArray(varNames) || varNames.length === 0) {
      return undefined;
    }
    stateMgmtConsole.debug(`find @Env ${key} from view ${view.debugInfo__()}, varsName ${JSON.stringify(varNames)}`);
    return varNames;
  }


  public static findEnvValueFromView<K extends keyof EnvTypeMap>(key: K, view: PUV2ViewBase): IEnvironmentValue<EnvTypeMap[K]> | undefined {
    const varNames = EnvV2.getEnvVarNameFromView(key, view);
    if (!varNames) {
      stateMgmtConsole.debug(`cannot find @Env ${key} from view ${view.debugInfo__()}`);
      return undefined;
    }

    stateMgmtConsole.debug(`find @Env ${key} from view ${view.debugInfo__()}, varsName ${JSON.stringify(varNames)}`);
    const varName: string = varNames[0];
    const storeProp = ObserveV2.ENV_PREFIX + varName;
    const existingEnvValue = view[storeProp];
    if (!existingEnvValue) {
      return undefined;
    }

    stateMgmtConsole.debug(`find envValue key ${key} from view ${view.debugInfo__()}. Returning the existing one.`);
    if (typeof existingEnvValue === 'object' || !EnvV2.isSimpleTypeKey(key)) {
      return existingEnvValue;
    }

    const simpleKeyEntry = view.__getAnonymousEnvMonitorFuncBySpeficKey__Internal(key);
    if (!simpleKeyEntry) {
      stateMgmtConsole.warn(`simple type env ${key} should exist in view ${view.debugInfo__()}, internal error`);
      return existingEnvValue as IEnvironmentValue<EnvTypeMap[K]>;
    }

    return simpleKeyEntry.envValue;
  }


  public static findEnvRecursively<K extends keyof EnvTypeMap>(
    key: K, view: ViewBuildNodeBase, viewInstanceId: number): IEnvironmentValue<EnvTypeMap[K]> | undefined {
    stateMgmtConsole.debug(`findEnvRecursively: searching '${key}' from view: ${view.debugInfo__()}`);

    let parent: ViewBuildNodeBase | undefined;
    if (view instanceof PUV2ViewBase) {
      // view may be created by view or buildernode
      parent = (view.getParent()  || view.__parentViewBuildNode__) as PUV2ViewBase;
    } else {
      // if view is buildernode
      parent = (view as any).__parentViewOfBuildNode?.deref();
    }

    if (parent && parent instanceof PUV2ViewBase && parent.__latestInstanceId__Internal === viewInstanceId) {
      stateMgmtConsole.debug(`findEnvRecursively: view ${view.debugInfo__()} has parent ${parent.debugInfo__()}, find @Env(${key}) in parent`);
      // if view is viewpu or viewv2, check if it has the @Env(key)
      // if it contains @Env(key), return existingEnvValue
      const existingEnvValue = EnvV2.findEnvValueFromView(key, parent);
      if (existingEnvValue) {
        return existingEnvValue;
      }
      return EnvV2.findEnvRecursively(key, parent, viewInstanceId);
    }

    // if parent is undefined, stop finding and return undefined
    stateMgmtConsole.debug(`findEnvRecursively: view ${view.debugInfo__()} cannot find @Env(${key}) return undefined`);
    return undefined;
  }

  public static isDirectQuerySystemEnvKey(key: string): boolean {
  return key === 'system.arkui.layout.direction' || key === 'system.arkui.fontScale';
}

  public static registerSimpleTypeMonitorFunc<K extends SimpleTypeEnvKey>(key: K, envValue: IEnvironmentValue<EnvTypeMap[K]>, view: PUV2ViewBase, varName: string): void {
    stateMgmtConsole.debug(`registerSimpleTypeMonitorFunc: Env ${key} ${varName} ${view.debugInfo__()}.`);
    const prop = EnvV2.getSimpleEnvProp(key);
    const simpleValue = (envValue as any)[prop];
    if (typeof simpleValue !== simpleEnvMetaMap[key].type) {
      const message = `Created env value in ${view.debugInfo__()} for key ${key} has type ${typeof simpleValue} which is different from expected ${simpleEnvMetaMap[key].type}, internal error.`;
      stateMgmtConsole.error(message);
      throw Error(message);
    }
    stateMgmtConsole.debug(`registerEnv: Env ${key} is simple type, and value is ${simpleValue}`);
    const envValueMonitorEntry = view.__getAnonymousEnvMonitorFuncBySpeficKey__Internal(key);
    if (envValueMonitorEntry && envValueMonitorEntry.envValue === envValue) {
      stateMgmtConsole.debug(`Env ${key} ${varName} is simple type, view ${view.debugInfo__()} already has anonymous monitor function for env`);
      return;
    }

    if (envValueMonitorEntry && envValueMonitorEntry.envValue !== envValue) {
      stateMgmtConsole.debug(`envValue ${key} in view ${view.debugInfo__()} has changed, may happen instance change, unregister from the old envValue`);
      ObserveV2.getObserve().clearMonitorPath(envValueMonitorEntry.envValue, prop, envValueMonitorEntry.anonymousMonitorFunc);
    }

    const anonymousMonitorFunc = (mon: IMonitor): void => {
      mon.dirty.forEach((path: string) => {
        stateMgmtConsole.debug(`Env ${key} ${envValue.constructor.name}'s property ${path} varname ${varName} change from ${mon.value(path)?.before} to ${mon.value(path)?.now}`);
        const varNames = EnvV2.getEnvVarNameFromView(key, view);
        if (!varNames) {
          stateMgmtConsole.debug(`anonymousMonitorFunc cannot find @Env ${key} from view ${view.debugInfo__()}`);
          return;
        }
        varNames.forEach((varNameInView: string) => {
          stateMgmtConsole.debug(`anonymousMonitorFunc fireChange cannot find @Env ${key} for ${varNameInView} in ${view.debugInfo__()}`);
          const storeProp = ObserveV2.ENV_PREFIX + varNameInView;
          view[storeProp] = mon.value(path)?.now;
          ObserveV2.getObserve().fireChange(view, varNameInView);
        });
      });
    };
    view.__setAnonymousEnvMonitorFunc__Internal(key, anonymousMonitorFunc, envValue);
    stateMgmtConsole.debug(`registerSimpleTypeMonitorFunc AddMonitorPath ${key} ${prop} ${varName} in ${view.debugInfo__()}`);
    ObserveV2.getObserve().AddMonitorPath(envValue, prop, anonymousMonitorFunc, true, false);
  }
/**
 * Registers an environment value for the specified key using the given context.
 * Creates and stores the corresponding environment instance, and it will be cleaned up when the associated context is destroyed.
 *
 * @param newInstanceId Optional. If provided, indicates that this call occurs during a UI context switch
 *                      and the environment binding should be re-associated with the new instance.
 */
  public static registerEnv<K extends keyof EnvTypeMap>(key: K, view: PUV2ViewBase, varName: string, newInstanceId?: number): IEnvironmentValue<EnvTypeMap[K]> | SimpleEnvValueType {
    const instanceId = view.getMainInstanceId();

    stateMgmtConsole.debug(`registerEnv: Env '${key}' for view: ${view.debugInfo__()} view instanceId ${instanceId} newInstanceId: ${newInstanceId}`);

    const envRegister = newInstanceId ? EnvV2.envValues[newInstanceId] ??= {} : EnvV2.envValues[instanceId] ??= {};

    // step one: find EnvValue in parent recursively
    const existingEnv = EnvV2.findEnvRecursively(key, view, view.__latestInstanceId__Internal);
    if (existingEnv) {
      if (EnvV2.isSimpleTypeKey(key)) {
        const simpleEnv = existingEnv as IEnvironmentValue<EnvTypeMap[typeof key]>;
        EnvV2.registerSimpleTypeMonitorFunc(key, simpleEnv, view, varName);
        return (existingEnv as any)[EnvV2.getSimpleEnvProp(key)];
      }
      stateMgmtConsole.debug(`registerEnv: view ${view.debugInfo__()} 1. find @Env(${key}) ${varName} in parent, return existing one`);
      return existingEnv;
    }

    // step two: find EnvValue in envRegister Global
    const envValueInGlobal = envRegister[key];
    if (envValueInGlobal) {
      stateMgmtConsole.debug(`registerEnv: view ${view.debugInfo__()} 2. find @Env(${key}) ${varName} in global, return existing one`);
      if (EnvV2.isSimpleTypeKey(key)) {
        const simpleEnv = envValueInGlobal as IEnvironmentValue<EnvTypeMap[typeof key]>;
        EnvV2.registerSimpleTypeMonitorFunc(key, simpleEnv, view, varName);
        return (envValueInGlobal as any)[EnvV2.getSimpleEnvProp(key)];
      }
      return envValueInGlobal;
    }

    // step three: if cannot find both in parent and global, create new one
    const factory = envFactoryMap[key];
    if (!factory) {
      const message = `${key} has not been registered in factory envFactoryMap, internal error.`;
      stateMgmtConsole.error(message);
      // toolchain can check
      throw new BusinessError(UNSUPPORTED_KEY_IN_ENV, message);
    }
    const uiContext = newInstanceId ? getUIContextUsingInstanceId(newInstanceId): view.getUIContext();
    stateMgmtConsole.debug(`registerEnv: view ${view.debugInfo__()} 3. cannot find @Env(${key}) ${varName} in parent/global, create new one`);
    const newEnv: IEnvironmentValue<EnvTypeMap[K]> = factory(uiContext);
    envRegister[key] = newEnv;
    if (EnvV2.isSimpleTypeKey(key)) {
      const simpleEnv = newEnv as IEnvironmentValue<EnvTypeMap[typeof key]>;
      EnvV2.registerSimpleTypeMonitorFunc(key, simpleEnv, view, varName);
      return (newEnv as any)[EnvV2.getSimpleEnvProp(key)];
    }
    return newEnv;
  }

  static isSimpleTypeKey(key: keyof EnvTypeMap): key is SimpleTypeEnvKey {
    return key in simpleEnvMetaMap;
  }

  static getSimpleEnvProp(key: SimpleTypeEnvKey): string {
    return simpleEnvMetaMap[key].prop;
  }
  /**
   * Registers an environment value for the given key using the provided context.
   * Creates and stores the environment instance for later retrieval or cleanup.
   */
  public static unregisterEnv<K extends keyof EnvTypeMap>(key: K, instanceId: number): void {
    const envRegister = EnvV2.envValues[instanceId];
    if (envRegister && typeof envRegister === 'object') {
      const env = envRegister[key] as IEnvironmentValue<EnvTypeMap[K]> | undefined;
      if (env && typeof env === 'object' && 'destroy' in env) {
        env.destroy();
        delete envRegister[key];
      }
    }
  }

  /**
   * Unregister all registered environment values.
   * Iterates over stored keys and delegates cleanup to unregisterEnv.
   */
  public static unregisterAll(instanceId: number): void {
    const envRegister = EnvV2.envValues[instanceId];
    if (envRegister && typeof envRegister === 'object') {
      for (const key of Object.keys(envRegister) as Array<keyof EnvTypeMap>) {
        EnvV2.unregisterEnv(key, instanceId);
      }
      delete EnvV2.envValues[instanceId];
    }
  }
}

function unregisterInstanceIdForEnv(instanceId: number): void {
  stateMgmtConsole.debug(`instanceid ${instanceId} destroy, unregister all key for @Env`);
  try {
    EnvV2.unregisterAll(instanceId);
  } catch (e) {
    stateMgmtConsole.error(`Failed to unregister all environment keys for instance ${instanceId}: ${e.message} ${e.stack}`);
  }
}

function getUIContextUsingInstanceId(instanceId: number): UIContext {
  if (typeof globalThis.__getUIContext__ !== 'function') {
    throw Error(`there is no __getUIContext__ in globalThis, internal error`)
  }
  return globalThis.__getUIContext__(instanceId);
}
