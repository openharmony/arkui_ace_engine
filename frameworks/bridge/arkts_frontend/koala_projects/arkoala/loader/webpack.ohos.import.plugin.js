/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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


const ReplaceSource = require("webpack").sources.ReplaceSource
class OHOSCompilationHookPlugin {
    /**
     * 
     * @param {{assetName: string;}} options 
     */
    constructor({assetName,separateFramework = false}) {
        this.assetName = assetName
        this.separateFramework = separateFramework
    }
    apply(compiler) {
        compiler.hooks.compilation.tap('OHOSCompilationHook', (compilation) => {
            // before minification
            // Erase 'default' reference in accessing @ohos modules internals
            compilation.hooks.processAssets.tap('OHOSPreprocessHook', (assets) => {
                let source = assets[`${this.assetName}`]
                let patched = new ReplaceSource(source)
                let text = source.source()
                // '_ohos_*.default.*' ==> '_ohos_*.'
                for (const match of text.matchAll(/(_ohos_[\w_$]+?)\.default\./g)) {
                    patched.replace(match.index, match.index + match[0].length - 1, `${match[1]}\.`)
                }
                compilation.updateAsset(`${this.assetName}`, patched)
            })
            // after minification
            // Replace import * as <name> with import <name> for hvigor
            compilation.hooks.afterProcessAssets.tap('OHOSImportReplaceHook', (assets) => {
                let source = assets[`${this.assetName}`]
                let patched = new ReplaceSource(source)
                let text = source.source()
                // 'import * as match_1 from"@ohos.blah.blah"' ==> '\nimport match_1 from "@ohos.blah.blah"'
                for (const match of text.matchAll(/import\s*\*\s*as\s*([\w_$]+)\s*from(?=\s*"@ohos\.)/g)) {
                    patched.replace(match.index, match.index + match[0].length - 1, `\nimport ${match[1]} from `)
                }
                assets[`${this.assetName}`] = patched
            })
        })
    }
    
}
module.exports = OHOSCompilationHookPlugin
