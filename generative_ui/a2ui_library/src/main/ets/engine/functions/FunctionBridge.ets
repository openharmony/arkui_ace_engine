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

import nativeEngine from 'libentry.so';
import { common } from '@kit.AbilityKit';
import { Catalog } from '../core/Catalog';
import { A2UIValueType } from '../types/types';
import { applyHostContextToBuiltinFunctions, registerA2UIBuiltinFunctionHandlers } from './A2UIBasicFunctions';
import {
  LocalFunctionArgs,
  LocalFunctionContext,
  LocalFunctionHandler,
  LocalFunctionRequest,
  LocalFunctionResponse,
  LocalFunctionResult
} from './LocalFunction';

export class FunctionBridge {
  private static installed: boolean = false;
  private static builtinInstalled: boolean = false;
  private static handlers: Map<string, LocalFunctionHandler> = new Map();
  private static catalogs: Map<string, Catalog> = new Map();
  private static hostContext: common.UIAbilityContext | undefined = undefined;

  public static install(): void {
    if (FunctionBridge.installed) {
      return;
    }
    nativeEngine.registerInvokeLocalFunction(FunctionBridge.invokeLocalFunction);
    FunctionBridge.installed = true;
    FunctionBridge.installBuiltinFunctions();
  }

  public static register(functionName: string, handler: LocalFunctionHandler): void {
    if (functionName.length === 0) {
      return;
    }
    FunctionBridge.handlers.set(functionName, handler);
  }

  public static registerCatalog(catalog: Catalog): void {
    FunctionBridge.catalogs.set(catalog.getCatalogId(), catalog);
  }

  public static setHostContext(hostContext: common.UIAbilityContext): void {
    FunctionBridge.hostContext = hostContext;
    applyHostContextToBuiltinFunctions(hostContext);
  }

  public static installBuiltinFunctions(): void {
    if (FunctionBridge.builtinInstalled) {
      return;
    }

    registerA2UIBuiltinFunctionHandlers((name: string, handler: LocalFunctionHandler) => {
      FunctionBridge.register(name, handler);
    });

    FunctionBridge.builtinInstalled = true;
  }

  public static invokeLocalFunction(request: LocalFunctionRequest): LocalFunctionResponse {
    let handler = FunctionBridge.handlers.get(request.functionName);
    if (handler === undefined) {
      return FunctionBridge.fail(request.returnType, 'FUNCTION_NOT_REGISTERED',
        `Local function is not registered: ${request.functionName}`);
    }

    let args: LocalFunctionArgs = FunctionBridge.parseArgs(request.argsJson);
    let context: LocalFunctionContext = {
      surfaceId: request.surfaceId,
      componentId: request.componentId,
      returnType: request.returnType
    };

    try {
      let result: LocalFunctionResult = handler(args, context);
      if (!FunctionBridge.validateReturnType(request.returnType, result)) {
        return FunctionBridge.fail(request.returnType, 'RETURN_TYPE_MISMATCH',
          `Function ${request.functionName} returned mismatched value for type ${request.returnType}`);
      }
      return {
        success: true,
        returnType: request.returnType,
        value: result
      };
    } catch (error) {
      return FunctionBridge.fail(request.returnType, 'FUNCTION_EXECUTION_FAILED',
        `Function ${request.functionName} execution failed: ${JSON.stringify(error)}`);
    }
  }

  private static parseArgs(argsJson: string): LocalFunctionArgs {
    if (argsJson.length === 0) {
      return undefined;
    }
    try {
      return JSON.parse(argsJson) as A2UIValueType;
    } catch (error) {
      console.error(`[FunctionBridge] parse args failed: ${argsJson}, error=${JSON.stringify(error)}`);
      return undefined;
    }
  }

  private static validateReturnType(returnType: string, value: LocalFunctionResult): boolean {
    switch (returnType) {
      case 'void':
        return value === undefined;
      case 'string':
        return typeof value === 'string';
      case 'number':
        return typeof value === 'number';
      case 'boolean':
        return typeof value === 'boolean';
      case 'null':
        return value === null;
      case 'array':
        return Array.isArray(value);
      case 'object':
        return typeof value === 'object' && value !== null && !Array.isArray(value);
      default:
        return true;
    }
  }

  private static fail(returnType: string, errorCode: string, errorMessage: string): LocalFunctionResponse {
    console.error(`[FunctionBridge] ${errorCode}: ${errorMessage}`);
    return {
      success: false,
      returnType: returnType,
      errorCode: errorCode,
      errorMessage: errorMessage
    };
  }
}
