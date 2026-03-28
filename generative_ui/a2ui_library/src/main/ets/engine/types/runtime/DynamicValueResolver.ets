/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { A2UIValueType } from '../types';
import { A2UIDataBinding } from '../DataBinding';
import { A2UIDynamicValue } from '../DynamicValue';
import { A2UIDynamicString } from '../DynamicString';
import { A2UIDynamicNumber } from '../DynamicNumber';
import { A2UIDynamicBoolean } from '../DynamicBoolean';
import { A2UIDynamicStringList } from '../DynamicStringList';
import { A2UIFunctionArgs, A2UIFunctionCall } from '../FunctionCall';
import { A2UIResolveContext, ResolveResult } from './ResolveContext';
import { TypeGuards } from './TypeGuards';

function okResult<T>(value: T, source: 'literal' | 'binding' | 'function'): ResolveResult<T> {
  return {
    success: true,
    source: source,
    value: value
  };
}

function failResult<T>(source: 'literal' | 'binding' | 'function', errorMessage: string): ResolveResult<T> {
  return {
    success: false,
    source: source,
    errorMessage: errorMessage
  };
}

export class DynamicValueResolver {
  static resolveValue(value: A2UIDynamicValue | undefined, context?: A2UIResolveContext): ResolveResult<A2UIValueType> {
    if (value === undefined) {
      return failResult<A2UIValueType>('literal', 'value is undefined');
    }
    if (TypeGuards.isDataBinding(value)) {
      return DynamicValueResolver.resolveBinding(value as A2UIDataBinding, context);
    }
    if (TypeGuards.isFunctionCall(value)) {
      return DynamicValueResolver.resolveFunctionCall(value as A2UIFunctionCall, context);
    }
    return okResult<A2UIValueType>(value as A2UIValueType, 'literal');
  }

  static resolveString(value: A2UIDynamicString | undefined, defaultValue: string = '',
    context?: A2UIResolveContext): string {
    let result = DynamicValueResolver.resolveValue(value, context);
    return result.success && typeof result.value === 'string' ? result.value : defaultValue;
  }

  static resolveNumber(value: A2UIDynamicNumber | undefined, defaultValue: number,
    context?: A2UIResolveContext): number {
    let result = DynamicValueResolver.resolveValue(value, context);
    return result.success && typeof result.value === 'number' && Number.isFinite(result.value)
      ? result.value
      : defaultValue;
  }

  static resolveBoolean(value: A2UIDynamicBoolean | undefined, defaultValue: boolean = false,
    context?: A2UIResolveContext): boolean {
    let result = DynamicValueResolver.resolveValue(value, context);
    return result.success && typeof result.value === 'boolean' ? result.value : defaultValue;
  }

  static resolveStringList(value: A2UIDynamicStringList | undefined, defaultValue: string[] = [],
    context?: A2UIResolveContext): string[] {
    let result = DynamicValueResolver.resolveValue(value, context);
    if (!result.success || !TypeGuards.isStringArray(result.value)) {
      return defaultValue.slice();
    }
    return (result.value as string[]).slice();
  }

  private static resolveBinding(binding: A2UIDataBinding,
    context?: A2UIResolveContext): ResolveResult<A2UIValueType> {
    if (context?.dataModel === undefined) {
      return failResult<A2UIValueType>('binding', `data model is unavailable for path: ${binding.path}`);
    }

    let resolved = DynamicValueResolver.readPath(context.dataModel, binding.path);
    if (resolved === undefined) {
      return failResult<A2UIValueType>('binding', `binding path not found: ${binding.path}`);
    }
    return okResult<A2UIValueType>(resolved, 'binding');
  }

  private static resolveFunctionCall(functionCall: A2UIFunctionCall,
    context?: A2UIResolveContext): ResolveResult<A2UIValueType> {
    if (context?.invokeFunction === undefined) {
      return failResult<A2UIValueType>('function', `function invoker is unavailable: ${functionCall.call}`);
    }

    let resolvedCall: A2UIFunctionCall = {
      call: functionCall.call,
      returnType: functionCall.returnType,
      args: DynamicValueResolver.resolveFunctionArgs(functionCall.args, context)
    };

    try {
      let result = context.invokeFunction(resolvedCall);
      return okResult<A2UIValueType>(result, 'function');
    } catch (error) {
      return failResult<A2UIValueType>('function', `function execution failed: ${JSON.stringify(error)}`);
    }
  }

  private static resolveFunctionArgs(
    args: A2UIFunctionArgs | undefined,
    context?: A2UIResolveContext): Record<string, A2UIValueType | Record<string, Object>> | undefined {
    if (args === undefined) {
      return undefined;
    }

    let resolved: Record<string, A2UIValueType | Record<string, Object>> = {};
    Object.keys(args).forEach((key: string) => {
      let current = args[key];
      if (TypeGuards.isRecord(current) && !TypeGuards.isDataBinding(current) && !TypeGuards.isFunctionCall(current)) {
        resolved[key] = current as Record<string, Object>;
        return;
      }

      let result = DynamicValueResolver.resolveValue(current as A2UIDynamicValue, context);
      resolved[key] = result.success ? result.value : undefined;
    });
    return resolved;
  }

  private static readPath(dataModel: ESObject, path: string): A2UIValueType | undefined {
    if (path.length === 0 || path === '/') {
      return dataModel as Object as A2UIValueType;
    }

    let normalizedPath: string = path.startsWith('/') ? path.substring(1) : path;
    if (normalizedPath.length === 0) {
      return dataModel as Object as A2UIValueType;
    }

    let current: Object | A2UIValueType = dataModel;
    for (const rawToken of normalizedPath.split('/')) {
      let token = rawToken.replace(/~1/g, '/').replace(/~0/g, '~');
      if (Array.isArray(current)) {
        let index: number = Number(token);
        if (!Number.isInteger(index) || index < 0 || index >= current.length) {
          return undefined;
        }
        current = current[index];
        continue;
      }

      if (!TypeGuards.isRecord(current)) {
        return undefined;
      }

      let record: ESObject = current as ESObject;
      current = record[token] as A2UIValueType | Object;
      if (current === undefined) {
        return undefined;
      }
    }

    return current as A2UIValueType;
  }
}
