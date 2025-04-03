import * as ts from "@koalaui/ets-tsc"

export enum MessageCode {
    EXPECTED_STRUCT_FIELD__TO_BE_EXPLICITLY_TYPED = 20001

}

export function reportError(code: number, text: string, node: ts.Node, sourceFile: ts.SourceFile, extras?: ts.TransformerExtras) {
    const lineAndChar = ts.getLineAndCharacterOfPosition(sourceFile, node.pos)
    extras?.addDiagnostic({
        code: code,
        messageText: text,
        category: ts.DiagnosticCategory.Error,
        file: sourceFile,
        start: node.pos,
        length: node.end - node.pos
    }) ?? console.log(text)
}
