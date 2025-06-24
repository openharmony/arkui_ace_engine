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

import { ArktsObject } from './ArktsObject';
import { global } from '../static/global';
import { throwError, filterSource } from '../../../utils';
import { passString } from '../utilities/private';
import { KBoolean, KNativePointer } from '@koalaui/interop';
import { AstNode } from './AstNode';
import { Program } from './Program';
export class Context extends ArktsObject {
    constructor(peer: KNativePointer) {
        super(peer);
    }

    static createFromString(source: string): Context {
        if (!global.configIsInitialized()) {
            throwError(`Config not initialized`);
        }
        return new Context(
            global.es2panda._CreateContextFromString(global.config, passString(source), passString(global.filePath))
        );
    }

    static createCacheContextFromFile(
        configPtr: KNativePointer,
        fileName: string,
        globalContextPtr: KNativePointer,
        isExternal: KBoolean
    ): Context {
        return new Context(
            global.es2panda._CreateCacheContextFromFile(configPtr, passString(fileName), globalContextPtr, isExternal)
        );
    }

    static destroyAndRecreate(ast: AstNode): Context {
        console.log('[TS WRAPPER] DESTROY AND RECREATE');
        const source = filterSource(ast.dumpSrc());
        global.es2panda._DestroyContext(global.context);
        global.compilerContext = Context.createFromString(source) as any; // TODO commonize Context

        return new Context(global.context);
    }

    get program(): Program {
        return new Program(global.es2panda._ContextProgram(this.peer));
    }
}
