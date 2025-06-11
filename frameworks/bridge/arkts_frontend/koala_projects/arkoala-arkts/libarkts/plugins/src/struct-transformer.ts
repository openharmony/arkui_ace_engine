import * as arkts from "@koalaui/libarkts"
import { AbstractVisitor } from "./AbstractVisitor";
import { annotation } from "./arkts-utils";

function isCustomComponentClass(node: arkts.ClassDeclaration): boolean {
    const structCollection: Set<string> = arkts.GlobalInfo.getInfoInstance().getStructCollection();
    if (node.definition?.ident?.name && structCollection.has(node.definition?.ident?.name)) {
        return true;
    }
    return false;
}

function isKnownMethodDefinition(method: arkts.MethodDefinition, name: string): boolean {
    if (!method || !arkts.isMethodDefinition(method)) return false;

    // For now, we only considered matched method name.
    const isNameMatched: boolean = method.name?.name === name;
    return isNameMatched;
}

function createStyleArgInBuildMethod(className: string): arkts.ETSParameterExpression {
    const styleLambdaParams: arkts.ETSParameterExpression = arkts.factory.createParameterDeclaration(
        arkts.factory.createIdentifier(
            'instance',
            arkts.factory.createTypeReferencePart(
                arkts.factory.createIdentifier(className)
            )
        ),
        undefined
    );

    const styleLambda = arkts.factory.createFunctionType(
        arkts.FunctionSignature.createFunctionSignature(
            undefined,
            [
                styleLambdaParams
            ],
            arkts.factory.createTypeParameter1_(arkts.factory.createIdentifier(className), undefined, undefined),
            false
        ),
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW
    );

    const optionalStyleLambda: arkts.ETSUnionType = arkts.factory.createUnionType([
        styleLambda,
        arkts.factory.createETSUndefinedType()
    ]);

    const styleParam: arkts.Identifier = arkts.factory.createIdentifier(
        'style',
        optionalStyleLambda
    );

    const param = arkts.factory.createParameterDeclaration(styleParam, undefined);
    param.annotations = [annotation("memo")];

    return param;
}

function createContentArgInBuildMethod(): arkts.ETSParameterExpression {
    const contentLambda: arkts.ETSFunctionType = arkts.factory.createFunctionType(
        arkts.FunctionSignature.createFunctionSignature(
            undefined,
            [],
            arkts.factory.createPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
            false
        ),
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW
    );

    const optionalContentLambda: arkts.ETSUnionType = arkts.factory.createUnionType([
        contentLambda,
        arkts.factory.createETSUndefinedType()
    ]);

    const contentParam: arkts.Identifier = arkts.factory.createIdentifier(
        'content',
        optionalContentLambda
    );

    const param = arkts.factory.createParameterDeclaration(contentParam, undefined);
    param.annotations = [annotation("memo")];

    return param;
}

function createInitializerArgInBuildMethod(className: string): arkts.ETSParameterExpression {
    return arkts.factory.createParameterDeclaration(
        arkts.factory.createIdentifier(
            'initializers',
            arkts.factory.createTypeReference(
                arkts.factory.createTypeReferencePart(
                    arkts.factory.createIdentifier(`__Options_${className}`)
                )
            )
        ).setOptional(true),
        undefined
    );
}

function prepareArgsInBuildMethod(className: string): arkts.ETSParameterExpression[] {
    return [
        createStyleArgInBuildMethod(className),
        createContentArgInBuildMethod(),
        createInitializerArgInBuildMethod(className)
    ];
}

function transformBuildMethod(
    method: arkts.MethodDefinition,
    className: string
): arkts.MethodDefinition {
    const updateKey: arkts.Identifier = arkts.factory.createIdentifier(
        '_build'
    );

    const scriptFunction: arkts.ScriptFunction = method.scriptFunction;

    const params: arkts.ETSParameterExpression[] = prepareArgsInBuildMethod(className);

    const updateScriptFunction = arkts.factory.createScriptFunction(
        scriptFunction.body,
        scriptFunction.scriptFunctionFlags,
        scriptFunction.modifiers,
        false,
        undefined,
        params,
        undefined,
        undefined
    );

    updateScriptFunction.annotations = [annotation("memo")];

    // TODO: Currently, just return method itself. Remove this once createMethodDefinition is ready.
    return arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
        updateKey,
        arkts.factory.createFunctionExpression(updateScriptFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PROTECTED,
        false
    );
}

function tranformClassMembers(node: arkts.ClassDeclaration): arkts.ClassDeclaration {
    const definition = node.definition
    const className = node.definition?.ident?.name
    if (!definition || !className) {
        return node
    }

    const updateMembers: arkts.AstNode[] = definition.body.map((member: arkts.AstNode) => {
        if (arkts.isMethodDefinition(member) && isKnownMethodDefinition(member, "constructor")) {
            return arkts.factory.createMethodDefinition(
                arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_CONSTRUCTOR,
                member.name,
                arkts.factory.createFunctionExpression(member.scriptFunction),
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_CONSTRUCTOR,
                false
            );
        }
        if (arkts.isMethodDefinition(member) && isKnownMethodDefinition(member, "build")) {
            return transformBuildMethod(member, className);
        }

        return member;
    });

    const updateClassDef = arkts.factory.updateClassDefinition(
        definition,
        definition.ident,
        definition.typeParams,
        definition.superTypeParams,
        definition.implements,
        undefined,
        definition.super,
        updateMembers,
        definition.modifiers,
        arkts.classDefinitionFlags(definition)
    )

    return arkts.factory.updateClassDeclaration(node, updateClassDef);
}

export class StructTransformer extends AbstractVisitor {
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren);
        if (arkts.isClassDeclaration(node) && isCustomComponentClass(node)) {
            return tranformClassMembers(node);
        }
        return node;
    }
}
