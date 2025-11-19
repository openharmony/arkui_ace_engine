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
type EnvMeta = Record<string, keyof EnvTypeMap>;

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


  public static addEnvKeyVariableDecoMeta<K extends keyof EnvTypeMap>(proto: Object, varName: string, key: K): void {
    // add decorator meta data to prototype
    const meta = proto[EnvV2.ENV_DECO_META] ??= {} as EnvMeta;
    // find varName -> key, key -> [varName1, varName2,..., varNameN]
    meta[varName] = key ;
    const prefixKey: string = `${EnvV2.ENV_KEY_PREFIX}${key}`;
    if (!meta[prefixKey]) {
      meta[prefixKey] = new Array<string>();
    }
    meta[prefixKey].push(varName);
  }

  public static findEnvValueFromView<K extends keyof EnvTypeMap>(key: K, view: ViewBuildNodeBase): IEnvironmentValue<EnvTypeMap[K]> | undefined {
    if (view instanceof PUV2ViewBase) {
      const meta = view[EnvV2.ENV_DECO_META];
      if (meta) {
        const prefixKey: string = `${EnvV2.ENV_KEY_PREFIX}${key}`;
        const varNames = meta[prefixKey];
        if (varNames && Array.isArray(varNames) && varNames.length > 0) {
          const varName: string = varNames[0];
          const storeProp = ObserveV2.ENV_PREFIX + varName;
          const existingEnvValue = view[storeProp];
          if (existingEnvValue) {
            stateMgmtConsole.debug(`find envValue key ${key} from view ${view.debugInfo__()}. Returning the existing one.`);
            return existingEnvValue;
          }
        }
      }
    }
    return undefined;
  }


  public static findEnvRecursively<K extends keyof EnvTypeMap>(key: K, view: ViewBuildNodeBase): IEnvironmentValue<EnvTypeMap[K]> | undefined {
    stateMgmtConsole.debug(`findEnv: searching '${key}' from view: ${view.debugInfo__()}`);

    // if view is viewpu or viewv2, check if it has the @Env(key)
    // if it contains @Env(key), return existingEnvValue
    const existingEnvValue = EnvV2.findEnvValueFromView(key, view);
    if (existingEnvValue) {
      return existingEnvValue;
    }

    let parent: ViewBuildNodeBase | undefined;
    if (view instanceof PUV2ViewBase) {
      // view may be created by view or buildernode
      parent = (view.getParent()  || view.__parentViewBuildNode__) as PUV2ViewBase;
    } else {
      // if view is buildernode
      parent = (view as any).__parentViewOfBuildNode?.deref();
    }

    if (parent) {
      stateMgmtConsole.debug(`findEnvRecursively: view ${view.debugInfo__()} has parent ${parent.debugInfo__()}, find @Env(${key}) in parent`);
      return EnvV2.findEnvRecursively(key, parent);
    }

    // if parent is undefined, stop finding and return undefined
    stateMgmtConsole.debug(`findEnvRecursively: view ${view.debugInfo__()} cannot find @Env(${key}) return undefined`);
    return undefined;
  }

/**
 * Registers an environment value for the specified key using the given context.
 * Creates and stores the corresponding environment instance, and it will be cleaned up when the associated context is destroyed.
 *
 * @param newInstanceId Optional. If provided, indicates that this call occurs during a UI context switch
 *                      and the environment binding should be re-associated with the new instance.
 */
  public static registerEnv<K extends keyof EnvTypeMap>(key: K, view: PUV2ViewBase, varName: string, newInstanceId?: number): IEnvironmentValue<EnvTypeMap[K]> {
    const instanceId = view.getMainInstanceId();

    stateMgmtConsole.debug(`registerEnv: Env '${key}' for view: ${view.debugInfo__()} view instanceId ${instanceId} newInstanceId: ${newInstanceId}`);

    const envRegister = newInstanceId ? EnvV2.envValues[newInstanceId] ??= {} : EnvV2.envValues[instanceId] ??= {};

    // step one: find EnvValue in parent recursively
    let parent: ViewBuildNodeBase | undefined;

    if (view instanceof PUV2ViewBase) {
      // view may be created by view or buildernode
      parent = (view.getParent()  || view.__parentViewBuildNode__) as PUV2ViewBase;
    } else {
      // if view is buildernode
      parent =(view as any).__parentViewOfBuildNode?.deref();
    }
    if (parent) {
      stateMgmtConsole.debug(`registerEnv: view ${view.debugInfo__()} has parent ${parent.debugInfo__()}, find @Env(${key}) ${varName} in parent`);
      const existingEnv = EnvV2.findEnvRecursively(key, parent);
      if (existingEnv) {
        return existingEnv;
      }
    }

    // step two: find EnvValue in envRegister Global
    const storeProp = ObserveV2.ENV_PREFIX + varName;
    const envValueInGlobal = envRegister[key];
    if (envValueInGlobal) {
        view[storeProp] = envValueInGlobal;
        return envValueInGlobal;
    }

    const factory = envFactoryMap[key];
    if (!factory) {
      const message = `${key} has not been registered in factory envFactoryMap, internal error.`;
      stateMgmtConsole.error(message);
      throw new Error(message);
    }
    const uiContext = newInstanceId ? getUIContextUsingInstanceId(newInstanceId): view.getUIContext();
    const newEnv: IEnvironmentValue<EnvTypeMap[K]> = factory(uiContext);
    envRegister[key] = newEnv;
    view[storeProp] = newEnv;
    return newEnv;
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