import * as ts from "@koalaui/libarkts"
import { ComponentTransformer, ComponentTransformerOptions } from './component-transformer'


export default function exampleTransformer(
    userPluginOptions?: ComponentTransformerOptions
) {
    console.log("WRAPPER: ", userPluginOptions)
    return (node: ts.EtsScript) => {
        return new ComponentTransformer(userPluginOptions).visitor(node)
    }
}
