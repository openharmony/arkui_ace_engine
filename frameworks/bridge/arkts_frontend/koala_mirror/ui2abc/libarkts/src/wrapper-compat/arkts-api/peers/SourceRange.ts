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
import { SourcePosition } from '../../../arkts-api/peers/SourcePosition';
import { ArktsObject } from '../../../arkts-api/peers/ArktsObject';
import { global } from '../static/global';
import { KNativePointer } from '@koalaui/interop';

export class SourceRange extends ArktsObject {
    constructor(peer: KNativePointer) {
        super(peer);
    }

    static create(start: SourcePosition, end: SourcePosition): SourceRange {
        return new SourceRange(
            global.es2panda._CreateSourceRange(global.context, start.peer, end.peer)
        );
    }

    start(): SourcePosition {
        return new SourcePosition(global.es2panda._SourceRangeStart(global.context, this.peer));
    }

    end(): SourcePosition {
        return new SourcePosition(global.es2panda._SourceRangeEnd(global.context, this.peer));
    }
}