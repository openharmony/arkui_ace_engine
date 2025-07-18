/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { ArktsObject } from "./ArktsObject"
import { Program } from "../../generated"
import { global } from "../static/global"
import { passString, passStringArray } from "../utilities/private"
import { KNativePointer, nullptr, KBoolean } from "@koalaui/interop"
import { Config } from "./Config"
import { filterSource, throwError } from "../../utils"
import { AstNode } from "./AstNode"

export class Context extends ArktsObject {
    constructor(peer: KNativePointer) {
        super(peer)
    }

    static createFromString(source: string): Context {
        if (!global.configIsInitialized()) {
            throw new Error(`Config not initialized`)
        }
        return new Context(
            global.es2panda._CreateContextFromString(
                global.config,
                passString(source),
                passString(global.filePath)
            )
        )
    }
    
    /** @deprecated Use {@link createCacheFromFile} instead */
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

    static createFromFile(filePath: string, configPath: string, stdlibPath: string, outputPath: string): Context | undefined {
        const config = Config.create([
            "",
            "--arktsconfig",
            configPath,
            '--extension',
            'ets',
            '--stdlib',
            stdlibPath,
            filePath,
            '--output',
            outputPath,
        ])
        return new Context(
            global.es2panda._CreateContextFromFile(
                config.peer,
                passString(filePath)
            )
        )
    }

    static createCacheFromFile(filePath: string, config: Config, globalContext: GlobalContext, isExternal: boolean) {
        return new Context(
            global.es2panda._CreateCacheContextFromFile(
                config.peer,
                passString(filePath),
                globalContext.peer,
                isExternal
            )
        )
    }

    static createContextGenerateAbcForExternalSourceFiles(
        filenames: string[]): Context {
        if (!global.configIsInitialized()) {
            throwError(`Config not initialized`);
        }
        return new Context(
            global.es2panda._CreateContextGenerateAbcForExternalSourceFiles(global.config, filenames.length, passStringArray(filenames))
        );
    }

    destroy() {
        if (this.peer != nullptr) {
            global.es2panda._DestroyContext(this.peer)
            this.peer = nullptr
        }
    }
    
    /** @deprecated */
    static destroyAndRecreate(ast: AstNode): Context {
        console.log('[TS WRAPPER] DESTROY AND RECREATE');
        const source = filterSource(ast.dumpSrc());
        global.es2panda._DestroyContext(global.context);
        global.compilerContext = Context.createFromString(source) as any; // Improve: commonize Context

        return new Context(global.context);
    }

    get program(): Program {
        return new Program(global.es2panda._ContextProgram(this.peer));
    }
}

export class GlobalContext extends ArktsObject {
    static create(
        config: Config, externalFileList: string[]
    ): GlobalContext {
        return new GlobalContext(
            global.es2panda._CreateGlobalContext(
                config.peer,
                passStringArray(externalFileList),
                externalFileList.length,
                false
            )
        )
    }

    constructor(peer: KNativePointer) {
        super(peer)
    }

    destroy() {
        if (this.peer != nullptr) {
            global.es2panda._DestroyGlobalContext(this.peer)
            this.peer = nullptr
        }
    }
}
