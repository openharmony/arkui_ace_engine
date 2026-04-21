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

import { common } from '@kit.AbilityKit';

import { A2UIValueType } from '../types/types';
import { BuiltinFunctionBase } from './BuiltinFunctionBase';
import { LocalFunctionArgs, LocalFunctionContext, LocalFunctionHandler, LocalFunctionResult } from './LocalFunction';

class OpenUrlFunction extends BuiltinFunctionBase {
  private hostContext?: common.UIAbilityContext;

  constructor() {
    super('openUrl');
  }

  public override setHostContext(hostContext: common.UIAbilityContext | undefined): void {
    this.hostContext = hostContext;
  }

  public override createHandler(): LocalFunctionHandler {
    return (args: LocalFunctionArgs, context: LocalFunctionContext): LocalFunctionResult => this.execute(args, context);
  }

  private execute(args: LocalFunctionArgs, context: LocalFunctionContext): LocalFunctionResult {
    let url: string = this.resolveUrl(args);
    if (!url.startsWith('https://')) {
      throw new Error('openUrl only supports non-empty https URLs');
    }

    if (this.hostContext === undefined) {
      throw new Error('host context is not ready');
    }

    this.hostContext.startAbility({
      action: 'ohos.want.action.viewData',
      entities: ['entity.system.browsable'],
      uri: url,
      parameters: {
        'ohos.ability.params.showDefaultPicker': true
      }
    }).then(() => {
      console.info(`[FunctionBridge] openUrl dispatched, surfaceId=${context.surfaceId}, componentId=${context.componentId}, url=${url}`);
    }).catch((error: Error) => {
      console.error(`[FunctionBridge] openUrl failed asynchronously, url=${url}, error=${JSON.stringify(error)}`);
    });

    return undefined;
  }

  private resolveUrl(args: LocalFunctionArgs): string {
    if (typeof args !== 'object' || args === null || Array.isArray(args)) {
      return '';
    }

    let record = args as Record<string, A2UIValueType>;
    let value = record['url'];
    if (typeof value !== 'string') {
      return '';
    }
    return value;
  }
}

export const openUrlFunction: OpenUrlFunction = new OpenUrlFunction();
