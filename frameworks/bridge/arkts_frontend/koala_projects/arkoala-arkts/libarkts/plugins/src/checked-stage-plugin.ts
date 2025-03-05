import * as ts from "@koalaui/libarkts"
import { PrintVisitor } from './print-visitor'
import { BuilderLambdaTransformer } from './builder-lambda-transformer'
import { ComponentTransformer } from './component-transformer'
import { StructTransformer } from './struct-transformer'

export interface TransformerOptions {
    trace?: boolean,
}

export default function exampleTransformer(
    userPluginOptions?: TransformerOptions
) {
    return (node: ts.EtsScript) => {
        const builderLambdaTransformer = new BuilderLambdaTransformer();
        const structTransformer = new StructTransformer();

        let script: ts.EtsScript = node;
        script = builderLambdaTransformer.visitor(script) as ts.EtsScript;
        script = structTransformer.visitor(script) as ts.EtsScript;

        return script;
    }
}
