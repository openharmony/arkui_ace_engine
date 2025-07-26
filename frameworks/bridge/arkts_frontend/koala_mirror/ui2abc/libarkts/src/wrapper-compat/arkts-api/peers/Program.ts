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

import { ArktsObject } from "../../../arkts-api/peers/ArktsObject"
import { global } from "../static/global"
import { acceptNativeObjectArrayResult, unpackString } from "../utilities/private"
import { KNativePointer } from "@koalaui/interop"
import { EtsScript } from "../types"

enum SkipPhaseResult {
    NOT_COMPUTED,
    CAN_SKIP,
    CANNOT_SKIP,
}

export class Program extends ArktsObject {
    private canSkipPhaseResult: SkipPhaseResult;

    constructor(peer: KNativePointer) {
        super(peer);
        this.canSkipPhaseResult = SkipPhaseResult.NOT_COMPUTED;
    }

    get astNode(): EtsScript {
        return new EtsScript(global.es2panda._ProgramAst(global.context, this.peer));
    }

    get externalSources(): ExternalSource[] {
        return acceptNativeObjectArrayResult<ExternalSource>(
            global.es2panda._ProgramExternalSources(global.context, this.peer),
            (instance: KNativePointer) => new ExternalSource(instance)
        );
    }

    get directExternalSources(): ExternalSource[] {
        return acceptNativeObjectArrayResult<ExternalSource>(
            global.es2panda._ProgramDirectExternalSources(global.context, this.peer),
            (instance: KNativePointer) => new ExternalSource(instance)
        );
    }

    get fileName(): string {
        return unpackString(global.generatedEs2panda._ProgramFileNameConst(global.context, this.peer));
    }

    get fileNameWithExtension(): string {
        return unpackString(global.generatedEs2panda._ProgramFileNameWithExtensionConst(global.context, this.peer));
    }

    get globalAbsName(): string {
        return unpackString(global.es2panda._ETSParserGetGlobalProgramAbsName(global.context));
    }

    get moduleName(): string {
        return unpackString(global.generatedEs2panda._ProgramModuleNameConst(global.context, this.peer));
    }

    isASTLowered(): boolean {
        return global.generatedEs2panda._ProgramIsASTLoweredConst(global.context, this.peer);
    }

    canSkipPhases(): boolean {
        if (this.canSkipPhaseResult === SkipPhaseResult.CAN_SKIP) {
            return true;
        } else if (this.canSkipPhaseResult === SkipPhaseResult.CANNOT_SKIP) {
            return false;
        }
        if (global.es2panda._ProgramCanSkipPhases(global.context, this.peer)) {
            this.canSkipPhaseResult = SkipPhaseResult.CAN_SKIP;
            return true;
        } else {
            this.canSkipPhaseResult = SkipPhaseResult.CANNOT_SKIP;
            return false;
        }
    }
}

export class ExternalSource extends ArktsObject {
    constructor(peer: KNativePointer) {
        super(peer)
    }

    getName(): string {
        return unpackString(global.es2panda._ExternalSourceName(this.peer));
    }

    get programs(): Program[] {
        return acceptNativeObjectArrayResult<Program>(
            global.es2panda._ExternalSourcePrograms(this.peer),
            (instance: KNativePointer) => new Program(instance)
        );
    }
}
