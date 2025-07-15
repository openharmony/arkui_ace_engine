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
import { DiagnosticKind } from './DiagnosticKind';
import { passStringArray } from '../utilities/private';
import { SourcePosition } from '../../../arkts-api/peers/SourcePosition';
import { SourceRange } from './SourceRange';
import { DiagnosticInfo } from './DiagnosticInfo';
import { SuggestionInfo } from './SuggestionInfo';

export class Diagnostic extends ArktsObject {
  constructor(peer: KNativePointer) {
    super(peer);
  }
  static logDiagnostic(kind: DiagnosticKind, pos: SourcePosition, ...args: string[]): void {
    global.es2panda._LogDiagnostic(global.context, kind.peer, passStringArray(args), args.length, pos.peer);
  }

  static logDiagnosticWithSuggestion(diagnosticInfo: DiagnosticInfo, suggestionInfo: SuggestionInfo,
    range: SourceRange): void {
    global.es2panda._LogDiagnosticWithSuggestion(global.context, diagnosticInfo.peer, suggestionInfo.peer, range.peer);
  }

}