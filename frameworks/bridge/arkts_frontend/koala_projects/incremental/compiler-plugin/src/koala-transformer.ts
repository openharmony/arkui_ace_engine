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

import * as ts from '@koalaui/ets-tsc';
import * as path from "path"
import { AnalysisVisitor } from './analysis-visitor';
import { DiagnosticsVisitor } from './diagnostics-visitor';
import { FunctionTransformer } from "./function-transformer"
import { ParameterTransformer } from "./parameter-transformer"
import { Rewrite } from './transformation-context';
import { VariableTypeTransformer } from './variable-type-transformer';
import { Tracer, TransformerOptions } from "./util"
import { DumpVisitor } from './dump-visitor';
import { ThisTransformer } from './this-transformer';
import { ReturnTransformer } from './return-transformer';

function getUnmemoizedPath(sourcePath: string, root: string, extension: string | undefined, unmemoizedDir?: string) {
    let relativePath = path.relative(root, sourcePath)
    if (extension) {
        relativePath = relativePath.replace(new RegExp(`${path.extname(relativePath)}$`), extension)
    }
    let outDir = path.join(root, unmemoizedDir ?? "unmemoized") // TODO add to plugin config
    return path.join(outDir, relativePath)
}

export function memoTransform(
    sourceFile: ts.SourceFile,
    typeChecker: ts.TypeChecker,
    ctx: ts.TransformationContext,
    extras: ts.TransformerExtras | undefined,
    tracer: Tracer,
    rewrite: Rewrite
): ts.SourceFile {
    const analysisVisitor = new AnalysisVisitor(tracer, typeChecker, sourceFile, rewrite, ctx)
    const diagnosticsVisitor = new DiagnosticsVisitor(tracer, typeChecker, sourceFile, rewrite, extras, ctx)
    const functionTransformer = new FunctionTransformer(tracer, typeChecker, sourceFile, rewrite, ctx)
    const parameterTransformer = new ParameterTransformer(tracer, typeChecker, sourceFile, rewrite.positionalIdTracker, rewrite.functionTable, ctx)
    const thisTransformer = new ThisTransformer(tracer, typeChecker, sourceFile, rewrite.positionalIdTracker, rewrite.functionTable, ctx)
    const variableTransformer = new VariableTypeTransformer(tracer, typeChecker, sourceFile, rewrite, ctx)
    const returnTransformer = new ReturnTransformer(typeChecker, sourceFile, rewrite.functionTable, ctx)

    analysisVisitor.visitor(sourceFile)
    diagnosticsVisitor.visitor(sourceFile)

    // The AST tree should be intact above this line.

    const transformedFunctions = functionTransformer.visitor(sourceFile)
    const transformedParameters = parameterTransformer.visitor(transformedFunctions)
    const transformedThis = thisTransformer.visitor(transformedParameters)
    const transformedReturn = returnTransformer.visitor(transformedThis)
    return variableTransformer.visitor(transformedReturn) as ts.SourceFile
}

export default function koala_transformer(program: ts.Program, pluginOptions: TransformerOptions, extras: ts.TransformerExtras) {
    const printer = ts.createPrinter()
    const tracer = new Tracer(pluginOptions, printer)
    return (ctx: ts.TransformationContext) => {
        const typechecker = program.getTypeChecker();
        return (sourceFile: ts.SourceFile) => {
            console.log("Koala rewrite: " + path.normalize(sourceFile.fileName))
            const rewrite = new Rewrite(sourceFile, pluginOptions)
            const dumpVisitor = new DumpVisitor(tracer, sourceFile, rewrite.functionTable, ctx)
            const result = memoTransform(sourceFile, typechecker, ctx, extras, tracer, rewrite)
            dumpVisitor.visitor(result)
            if (pluginOptions.only_unmemoize) {
                const content = tracer.printer.printNode(ts.EmitHint.Unspecified, result, sourceFile)
                const projectRoot = path.dirname(ctx.getCompilerOptions().configFilePath as string)
                const rewritePath = getUnmemoizedPath(path.normalize(sourceFile.fileName), projectRoot, pluginOptions.extension, pluginOptions.unmemoizeDir);
                tracer.createDirs(rewritePath.slice(0, rewritePath.lastIndexOf(path.sep)))
                tracer.writeTextToFile(content+"\n", rewritePath)
            } else if (pluginOptions.trace) {
                tracer.trace("OUTPUT:\n" + printer.printNode(ts.EmitHint.SourceFile, result, sourceFile))
            }
            return result
        }
    }
}
