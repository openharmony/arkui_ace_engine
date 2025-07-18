/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ArktsObject } from '../../../arkts-api/peers/ArktsObject';
import { global } from '../static/global';
import { KNativePointer } from '@koalaui/interop';
import { Es2pandaPluginDiagnosticType as PluginDiagnosticType } from '../../../generated/Es2pandaEnums';

export { PluginDiagnosticType }

export class DiagnosticKind extends ArktsObject {
  constructor(peer: KNativePointer) {
    super(peer);
  }

  static create(message: string, type: PluginDiagnosticType): DiagnosticKind {
    return new DiagnosticKind(
      global.es2panda._CreateDiagnosticKind(global.context, message, type)
    );
  }
}
