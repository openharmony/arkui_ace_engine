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

  /**
 * Registers an environment value for the given key using the provided context.
 * Creates and stores the environment instance for later retrieval or cleanup.
 */
  public static registerEnv<K extends keyof EnvTypeMap>(key: K, context: UIContext, instanceId: number): IEnvironmentValue<EnvTypeMap[K]> {
    const envRegister =  EnvV2.envValues[instanceId] ??= {};
    let existingEnv = envRegister[key];
    if (existingEnv) {
        stateMgmtConsole.debug(`Instance ${instanceId} already has an IEnvironmentValue for key ${key}. Returning the existing one.`);
        return existingEnv;
    }

    const factory = envFactoryMap[key];
    if (!factory) {
        const message = `${key} has not been registered in factory envFactoryMap, internal error.`;
        stateMgmtConsole.error(message);
        throw new Error(message);
    }
    const newEnv :IEnvironmentValue<EnvTypeMap[K]> = factory(context);
    envRegister[key] = newEnv;
    return newEnv;
  }

  /**
 * Unregister the environment value for the given key.
 * Calls its destroy method if available and removes it from storage.
 */
  public static unregisterEnv<K extends keyof EnvTypeMap>(key: K, instanceId: number): void {
    const envRegister =  EnvV2.envValues[instanceId];
    if (envRegister) {
      const env = envRegister[key] as IEnvironmentValue<EnvTypeMap[K]> | undefined;
      if (env) {
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
    const envRegister =  EnvV2.envValues[instanceId];
    for (const key of Object.keys(envRegister) as Array<keyof EnvTypeMap>) {
      EnvV2.unregisterEnv(key, instanceId);
    }
    delete EnvV2.envValues[instanceId];
  }
}

function unregisterInstanceIdForEnv(instanceId: number): void {
  stateMgmtConsole.warn(`instanceid ${instanceId} destroy, unregister all key for @Env`);
  EnvV2.unregisterAll(instanceId);
}