'use static'

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

import { Resource } from '@ohos.arkui.component'
import common from '@ohos.app.ability.common';
import hilog from '@ohos.hilog';

export class ResourceManager {
  private context: common.UIAbilityContext | undefined = undefined;

  public resourceToString(resource: Resource): string {
    const ctx = this.context;
    if (ctx) {
      try {
        return ctx.resourceManager.getStringSync(resource.id);
      } catch (error) {
        hilog.error(0x0000, 'testTag',
          `resourceToString failed. error code: ${error.code}, error message: ${error.message}`);
      }
    }
    return 'undefined|null';
  }

  public setContext(context: common.UIAbilityContext): void {
    this.context = context;
  }
}

// Default export let
let resourceToStringManager: ResourceManager = new ResourceManager();

export default resourceToStringManager;