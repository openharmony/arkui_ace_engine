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
 * Maps environment property keys to their corresponding value types.
 *
 * This mapping should be maintained in a **common central location**.
 * Each environment property provider (platform/system team) is expected to:
 * - Add the key for the environment property they provide
 * - Map it to its respective type interface
 *
 */
interface EnvTypeMap {
  'system.arkui.breakpoint': WindowSizeLayoutBreakpoint;
  'system.window.size': WindowSizeVpEnv;
  'system.window.size.px': WindowSizePxEnv;
  'system.window.avoidarea': WindowAvoidAreaVpEnv;
  'system.window.avoidarea.px': WindowAvoidAreaPxEnv;
  'system.window.focused': WindowFocusedEnv;
  'system.window.highlighted': WindowHighlightedEnv;
  'system.window.systemdensity': SystemDensityEnv;
  'system.window.displayid': DisplayIdEnv;
}

/**
 * Factory map for creating environment property value instances.
 *
 * Keys match the entries in `EnvTypeMap`, and each factory function:
 * - Accepts a `context` object
 * - Returns the corresponding `IEnvironmentValue` instance
 *
 * This enables:
 * - On-demand creation of environment value providers
 * - Consistent construction logic for all environment properties
 *
 * To be updated by Platform Environment Provider for each environment property newly introduced(mocked here for testing)
 */

const envFactoryMap: {
  [K in keyof EnvTypeMap]: (context: UIContext) => IEnvironmentValue<EnvTypeMap[K]>;
} = {
  'system.arkui.breakpoint': (context: UIContext) => {
    const WindowSizeLayoutBreakpoint = requireNapi('arkui.windowsizelayoutbreakpoint').WindowSizeLayoutBreakpoint;
    if (typeof WindowSizeLayoutBreakpoint !== 'function') {
      // internal error
      throw new BusinessError(REQUIRE_INTERNAL_ERROR, 'WindowSizeLayoutBreakpoint not found (requireNapi failed).');
    }
    stateMgmtConsole.debug(`create WindowSizeLayoutBreakpoint.`);
    return new WindowSizeLayoutBreakpoint(context);
  },
  'system.window.size': (context: UIContext) => {
    const WindowSizeVpEnv = requireNapi('window.windowsizeenv').WindowSizeVpEnv;
    if (typeof WindowSizeVpEnv !== 'function') {
      // internal error
      throw new BusinessError(REQUIRE_INTERNAL_ERROR, 'WindowSizeVpEnv not found (requireNapi failed).');
    }
    stateMgmtConsole.debug(`create WindowSizeVpEnv.`);
    return new WindowSizeVpEnv(context);
  },
  'system.window.size.px': (context: UIContext) => {
    const WindowSizePxEnv = requireNapi('window.windowsizeenv').WindowSizePxEnv;
    if (typeof WindowSizePxEnv !== 'function') {
      // internal error
      throw new BusinessError(REQUIRE_INTERNAL_ERROR, 'WindowSizePxEnv not found (requireNapi failed).');
    }
    stateMgmtConsole.debug(`create WindowSizePxEnv.`);
    return new WindowSizePxEnv(context);
  },
  'system.window.avoidarea': (context: UIContext) => {
    const WindowAvoidAreaVpEnv = requireNapi('window.windowavoidareaenv').WindowAvoidAreaVpEnv;
    if (typeof WindowAvoidAreaVpEnv !== 'function') {
      // internal error
      throw new BusinessError(REQUIRE_INTERNAL_ERROR, 'WindowAvoidAreaVpEnv not found (requireNapi failed).');
    }
    stateMgmtConsole.debug(`create WindowAvoidAreaVpEnv.`);
    return new WindowAvoidAreaVpEnv(context);
  },
  'system.window.avoidarea.px': (context: UIContext) => {
    const WindowAvoidAreaPxEnv = requireNapi('window.windowavoidareaenv').WindowAvoidAreaPxEnv;
    if (typeof WindowAvoidAreaPxEnv !== 'function') {
      // internal error
      throw new BusinessError(REQUIRE_INTERNAL_ERROR, 'WindowAvoidAreaPxEnv not found (requireNapi failed).');
    }
    stateMgmtConsole.debug(`create WindowAvoidAreaPxEnv.`);
    return new WindowAvoidAreaPxEnv(context);
  },
  'system.window.focused': (context: UIContext) => {
    const WindowFocusedEnv = requireNapi('window.windowfocusenv').WindowFocusedEnv;
    if (typeof WindowFocusedEnv !== 'function') {
      // internal error
      throw new BusinessError(REQUIRE_INTERNAL_ERROR, 'WindowFocusedEnv not found (requireNapi failed).');
    }
    stateMgmtConsole.debug(`create WindowFocusedEnv.`);
    return new WindowFocusedEnv(context);
  },
  'system.window.highlighted': (context: UIContext) => {
    const WindowHighlightedEnv = requireNapi('window.windowfocusenv').WindowHighlightedEnv;
    if (typeof WindowHighlightedEnv !== 'function') {
      // internal error
      throw new BusinessError(REQUIRE_INTERNAL_ERROR, 'WindowHighlightedEnv not found (requireNapi failed).');
    }
    stateMgmtConsole.debug(`create WindowHighlightedEnv.`);
    return new WindowHighlightedEnv(context);
  },
  'system.window.systemdensity': (context: UIContext) => {
    const SystemDensityEnv = requireNapi('window.systemdensityenv').SystemDensityEnv;
    if (typeof SystemDensityEnv !== 'function') {
      // internal error
      throw new BusinessError(REQUIRE_INTERNAL_ERROR, 'SystemDensityEnv not found (requireNapi failed).');
    }
    stateMgmtConsole.debug(`create SystemDensityEnv.`);
    return new SystemDensityEnv(context);
  },
  'system.window.displayid': (context: UIContext) => {
    const DisplayIdEnv = requireNapi('window.displayidenv').DisplayIdEnv;
    if (typeof DisplayIdEnv !== 'function') {
      // internal error
      throw new BusinessError(REQUIRE_INTERNAL_ERROR, 'DisplayIdEnv not found (requireNapi failed).');
    }
    stateMgmtConsole.debug(`create DisplayIdEnv.`);
    return new DisplayIdEnv(context);
  },
};


type SimpleEnvValueType = 'number' | 'boolean';

interface SimpleEnvMetaItem<K extends keyof EnvTypeMap> {
  prop: keyof EnvTypeMap[K];
  type: SimpleEnvValueType;
}

type SimpleEnvMeta = Partial<{
  [K in keyof EnvTypeMap]: SimpleEnvMetaItem<K>;
}>;

// add env key and property name and type here
const simpleEnvMetaMap = {
  'system.window.systemdensity': {
    prop: 'systemDensity',
    type: 'number',
  },
  'system.window.displayid': {
    prop: 'displayId',
    type: 'number',
  },
} as const satisfies SimpleEnvMeta;

type SimpleTypeEnvKey = keyof typeof simpleEnvMetaMap;
