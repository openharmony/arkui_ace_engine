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

import * as arkts from "@koalaui/libarkts"
import { annotation } from "./common/arkts-utils"

export const styledInstance = mangle("instance")

export function mangle(value: string): string {
    return `__${value}`
}

export enum CustomComponentNames {
    COMPONENT_BUILD_ORI = 'build',
    COMPONENT_CONSTRUCTOR_ORI = 'constructor',
    COMPONENT_CLASS_NAME = 'CustomComponent',
    COMPONENT_INTERFACE_PREFIX = '__Options_',
    COMPONENT_DISPOSE_STRUCT = '__disposeStruct',
    COMPONENT_INITIALIZE_STRUCT = '__initializeStruct',
    COMPONENT_UPDATE_STRUCT = '__updateStruct',
    COMPONENT_TO_RECORD = '__toRecord',
    COMPONENT_BUILD = '_build',
    REUSABLE_COMPONENT_REBIND_STATE = '__rebindStates',
    COMPONENT_INITIALIZERS_NAME_0 = 'initializers0',
    COMPONENT_INITIALIZERS_NAME = 'initializers',
    COMPONENT_IS_ENTRY = 'isEntry',
    COMPONENT_IS_CUSTOM_LAYOUT = 'isCustomLayoutComponent',
    COMPONENT_ONPLACECHILDREN_ORI = 'onPlaceChildren',
    COMPONENT_ONMEASURESIZE_ORI = 'onMeasureSize',
    COMPONENT_BUILDER_LAMBDA = 'CustomComponent.$_instantiate'
}

export enum BuilderLambdaNames {
    ANNOTATION_NAME = 'ComponentBuilder',
    BUILDER_LAMBDA_NAME = 'BuilderLambda',
    ORIGIN_METHOD_NAME = '$_instantiate',
    TRANSFORM_METHOD_NAME = '$_instantiate',
    STYLE_PARAM_NAME = 'style',
    STYLE_ARROW_PARAM_NAME = 'instance',
    CONTENT_PARAM_NAME = 'content',
}

export enum InternalAnnotations {
    MEMO = 'memo',
    MEMO_STABLE = 'memo_stable',
    BUILDER_LAMBDA = 'BuilderLambda'
}

function isKoalaWorkspace() {
    return process.env.KOALA_WORKSPACE == "1"
}

export function getRuntimePackage(): string {
    if (isKoalaWorkspace()) {
        return '@koalaui/runtime'
    } else {
        return 'arkui.stateManagement.runtime'
    }
}

export function getRuntimeAnnotationsPackage(): string {
    if (isKoalaWorkspace()) {
        return '@koalaui/runtime/annotations'
    } else {
        return 'arkui.stateManagement.runtime'
    }
}

export function getDecoratorPackage(): string {
    if (isKoalaWorkspace()) {
        return 'arkui'
    } else {
        return 'arkui.stateManagement.decorator'
    }
}

export function getComponentPackage(): string {
    if (isKoalaWorkspace()) {
        return 'arkui'
    } else {
        return 'arkui.component'
    }
}

export function uiAttributeName(componentName: string): string {
    return `${componentName}Attribute`
}
export function getCustomComponentOptionsName(className: string): string {
    return `${CustomComponentNames.COMPONENT_INTERFACE_PREFIX}${className}`
}

export function getTypeParamsFromClassDecl(node: arkts.ClassDeclaration | undefined): readonly arkts.TSTypeParameter[] {
    return node?.definition?.typeParams?.params ?? [];
}

export function getTypeNameFromTypeParameter(node: arkts.TSTypeParameter | undefined): string | undefined {
    return node?.name?.name;
}

export function createOptionalClassProperty(
    name: string,
    property: arkts.ClassProperty,
    stageManagementIdent: string,
    modifiers: arkts.Es2pandaModifierFlags
): arkts.ClassProperty {
    let newType: arkts.TypeNode | undefined = property.typeAnnotation;
    if (property.typeAnnotation && arkts.isETSFunctionType(property.typeAnnotation)) {
        newType = arkts.factory.createETSFunctionType(
            property.typeAnnotation.typeParams,
            property.typeAnnotation.params,
            property.typeAnnotation.returnType,
            false,
            property.typeAnnotation.flags
        );
    }
    const newProperty = arkts.factory.createClassProperty(
        arkts.factory.createIdentifier(name, undefined),
        undefined,
        stageManagementIdent.length ? createStageManagementType(stageManagementIdent, property) :
            newType,
        modifiers,
        false
    );
    return arkts.classPropertySetOptional(newProperty, true);
}

export function createStageManagementType(stageManagementIdent: string, property: arkts.ClassProperty): arkts.ETSTypeReference {
    let newType: arkts.TypeNode | undefined = property.typeAnnotation;
    if (property.typeAnnotation && arkts.isETSFunctionType(property.typeAnnotation)) {
        newType = arkts.factory.createETSFunctionType(
            property.typeAnnotation.typeParams,
            property.typeAnnotation.params,
            property.typeAnnotation.returnType,
            false,
            property.typeAnnotation.flags
        );
    }
    return arkts.factory.createETSTypeReference(
        arkts.factory.createETSTypeReferencePart(
            arkts.factory.createIdentifier(stageManagementIdent, undefined),
            arkts.factory.createTSTypeParameterInstantiation(
                [
                    newType ? newType :
                        arkts.factory.createETSUndefinedType(),
                ]
            ),
            undefined
        )
    );
}

export function makeImport(what: string, asWhat: string, where: string) {
    const source: arkts.StringLiteral = arkts.factory.createStringLiteral(where)
    return arkts.factory.createETSImportDeclaration(
        source,
        [
            arkts.factory.createImportSpecifier(
                arkts.factory.createIdentifier(what),
                arkts.factory.createIdentifier(asWhat)
            )
        ],
        arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL
    )
}

export class Importer {
    storage = new Map<string, [string, string]>()
    private defaultArkUIImports1 = [
        'Color',
        'ClickEvent', 'FlexAlign',
        'Image', 'Button', 'List',
        'PageTransitionEnter', 'PageTransitionExit', 'PageTransitionOptions',
        'Column', 'ColumnOptions', 'Row', 'RowOptions',
        'FlexOptions', 'TabsOptions', 'StackOptions', 'ToggleOptions', 'TextInputOptions',
        'TestComponent', 'TestComponentOptions', 'ForEach', 'Text',
        'Margin', 'Padding', 'BorderOptions', 'Curve', 'RouteType', 'TextOverflowOptions',
        'Flex', 'FlexWrap', 'HorizontalAlign', 'Scroll', 'Tabs', 'TabsController', 'TabContent',
        'NavDestination', 'NavPathStack',
        'IDataSource', 'DataChangeListener', 'ItemAlign', 'ImageFit', 'FlexDirection',
        'FontWeight', 'Counter', 'Toggle', 'ToggleType', 'BarMode', 'TextAlign', 'VerticalAlign',
        'TextOverflow', 'BarState', 'NavPathInfo', 'Stack', 'Swiper',
        'ListItem', 'Navigator', 'Position', 'Axis',
        'TextInput', 'Font', 'Alignment', 'Visibility', 'ImageRepeat', 'SizeOptions', 'Divider',
        'TabBarOptions', 'Navigation', 'Span', 'NavigationMode', 'BarPosition', 'EnterKeyType',
        'LazyForEach',
        'UITestComponentAttribute', 'ForEach', 'Text',
        'AppStorage', 'LocalStorage', 'AbstractProperty', 'SubscribedAbstractProperty',
    ]
    private defaultArkUIImports2 = [ 'TestComponentOptions' ]

    constructor() {
        const withDefaultImports = isKoalaWorkspace() ? true : false
        if (withDefaultImports) {
            this.defaultArkUIImports2.forEach(it => {
                this.add(it, 'arkui')
            })
        }
    }
    add(what: string, where: string, asWhat?: string) {
        const previous = this.storage.get(what)
        if (!asWhat)
            asWhat = what
        if (previous != undefined && (previous[0] != where || previous[1] != asWhat))
            throw new Error(`Mismatching import ${what} from ${where}`)
        this.storage.set(what, [where, asWhat])
    }
    emit(statements: readonly arkts.Statement[]): arkts.Statement[] {
        const newStatements = [...statements]
        this.storage.forEach(([where, asWhat], what) => {
            newStatements.unshift(makeImport(what, asWhat, where))
        })
        return newStatements
    }
}

export interface ImportingTransformer {
    collectImports(imports: Importer): void
}

export function createETSTypeReference(typeName: string, typeParamsName?: string[]) {
    const typeParams = typeParamsName
        ? arkts.factory.createTSTypeParameterInstantiation(
            typeParamsName.map(name => arkts.factory.createETSTypeReference(
                arkts.factory.createETSTypeReferencePart(arkts.factory.createIdentifier(name))
            ))
        ) : undefined
    return arkts.factory.createETSTypeReference(
        arkts.factory.createETSTypeReferencePart(arkts.factory.createIdentifier(typeName), typeParams)
    )
}

export enum DecoratorNames {
    ENTRY = "Entry",
    COMPONENT = "Component",
    REUSABLE = "Reusable",
    STATE = "State",
    STORAGE_LINK = "StorageLink",
    STORAGE_PROP = "StorageProp",
    LINK = "Link",
    PROP = "Prop",
    PROVIDE = "Provide",
    CONSUME = "Consume",
    OBJECT_LINK = "ObjectLink",
    OBSERVED = "Observed",
    OBSERVED_V2 = "ObservedV2",
    WATCH = "Watch",
    BUILDER_PARAM = "BuilderParam",
    BUILDER = "Builder",
    CUSTOM_DIALOG = "CustomDialog",
    LOCAL_STORAGE_PROP = "LocalStorageProp",
    LOCAL_STORAGE_LINK = "LocalStorageLink",
    LOCAL_BUILDER = "LocalBuilder",
    TRACK = "Track",
    TRACE = "Trace",
}

export enum DecoratorParameters {
    USE_SHARED_STORAGE = "useSharedStorage",
    ALLOW_OVERRIDE = "allowOverride",
}

export function hasEntryAnnotation(node: arkts.ClassDefinition): boolean {
    return node.annotations.some((it) =>
        it.expr !== undefined && arkts.isIdentifier(it.expr) && it.expr.name === DecoratorNames.ENTRY
    )
}

export function isDecoratorAnnotation(anno: arkts.AnnotationUsage, decoratorName: DecoratorNames): boolean {
    return !!anno.expr && arkts.isIdentifier(anno.expr) && anno.expr.name === decoratorName;
}

export function hasDecorator(property: arkts.ClassProperty | arkts.ClassDefinition | arkts.ClassDeclaration | arkts.MethodDefinition | arkts.FunctionDeclaration | arkts.ETSParameterExpression, decoratorName: DecoratorNames): boolean {
    if (arkts.isMethodDefinition(property)) {
        return property.function!.annotations.some((anno) => isDecoratorAnnotation(anno, decoratorName));
    }
    if (arkts.isClassDeclaration(property)) {
        return property.decorators.some((anno) => arkts.isIdentifier(anno.expr) && anno.expr.name === decoratorName)
    }
    return property.annotations.some((anno) => isDecoratorAnnotation(anno, decoratorName));
}

export function replaceDecorator(node: arkts.ETSParameterExpression, oldName: DecoratorNames, newName: string) {
    if (node.annotations.find(annotation => annotation.baseName?.name == oldName) == undefined) return node
    let newAnnotations = node.annotations?.map(anno => isDecoratorAnnotation(anno, oldName) ? annotation(newName) : anno)
    return arkts.factory.updateETSParameterExpression(node, node.ident, node.isOptional, node.initializer, newAnnotations)
}

export function hasBuilderDecorator(property: arkts.ClassProperty | arkts.ClassDefinition | arkts.ClassDeclaration | arkts.MethodDefinition | arkts.FunctionDeclaration): boolean {
    return hasDecorator(property, DecoratorNames.BUILDER) || hasDecorator(property, DecoratorNames.LOCAL_BUILDER)
}

export function getStageManagmentType(node: arkts.ClassProperty): string {
    if (hasDecorator(node, DecoratorNames.STATE)) {
        return "StateDecoratedVariable";
    } else if (hasDecorator(node, DecoratorNames.PROP) || hasDecorator(node, DecoratorNames.STORAGE_PROP) ||
    hasDecorator(node, DecoratorNames.LOCAL_STORAGE_PROP) || hasDecorator(node, DecoratorNames.OBJECT_LINK)
    ) {
        return "SyncedProperty";
    }
    return "MutableState";
}

export function createGetter(
    name: string,
    type: arkts.TypeNode | undefined,
    returns: arkts.Expression
): arkts.MethodDefinition {
    const body = arkts.factory.createBlockStatement(
        [arkts.factory.createReturnStatement(returns)]
    )

    const scriptFunction = arkts.factory.createScriptFunction(
        body,
        undefined,
        [],
        type?.clone(),
        false,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_GETTER,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(name),
        undefined
    )

    return arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_GET,
        arkts.factory.createIdentifier(name),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(name), scriptFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false
    );
}

export function createSetter(
    name: string,
    type: arkts.TypeNode | undefined,
    left: arkts.Expression,
    right: arkts.Expression,
    needMemo: boolean = false
): arkts.MethodDefinition {
    const body = arkts.factory.createBlockStatement(
        [
            arkts.factory.createExpressionStatement(arkts.factory.createAssignmentExpression(
                left,
                right,
                arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_SUBSTITUTION
            ))
        ]
    )
    const param: arkts.ETSParameterExpression = arkts.factory.createETSParameterExpression(
        arkts.factory.createIdentifier('value', type?.clone()),
        false
    );
    if (needMemo) {
        param.setAnnotations([annotation(InternalAnnotations.MEMO)])
    }
    const scriptFunction = arkts.factory.createScriptFunction(
        body,
        undefined,
        [param],
        undefined,
        false,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_SETTER,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(name),
        undefined
    )

    return arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_SET,
        arkts.factory.createIdentifier(name),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(name), scriptFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false
    );
}

export function createSetter2(
    name: string,
    type: arkts.TypeNode | undefined,
    statement: arkts.Statement
): arkts.MethodDefinition {
    const body = arkts.factory.createBlockStatement([statement]);
    const param: arkts.ETSParameterExpression = arkts.factory.createETSParameterExpression(
        arkts.factory.createIdentifier('value', type?.clone()),
        false
    );
    const scriptFunction = arkts.factory.createScriptFunction(
        body,
        undefined,
        [param],
        undefined,
        false,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_SETTER,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(name),
        undefined
    );

    return arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_SET,
        arkts.factory.createIdentifier(name),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(name), scriptFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false
    );
}

export function generateThisBackingValue(
    name: string,
    optional: boolean = false,
    nonNull: boolean = false
): arkts.MemberExpression {
    const member: arkts.Expression = generateThisBacking(name, optional, nonNull);
    return arkts.factory.createMemberExpression(
        member,
        arkts.factory.createIdentifier('value', undefined),
        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
        false,
        false
    );
}

export function generateThisBacking(
    name: string,
    optional: boolean = false,
    nonNull: boolean = false
): arkts.Expression {
    const member: arkts.Expression = arkts.factory.createMemberExpression(
        arkts.factory.createThisExpression(),
        arkts.factory.createIdentifier(name, undefined),
        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
        false,
        optional
    );
    return nonNull ? arkts.factory.createTSNonNullExpression(member) : member;
}

function getValueStr(node: arkts.AstNode): string | undefined {
    if (!arkts.isClassProperty(node) || !node.value) return undefined;
    return arkts.isStringLiteral(node.value) ? node.value.str : undefined;
}

function getAnnotationValue(anno: arkts.AnnotationUsage, decoratorName: DecoratorNames): string | undefined {
    const isSuitableAnnotation: boolean = !!anno.expr
        && arkts.isIdentifier(anno.expr)
        && anno.expr.name === decoratorName;
    if (isSuitableAnnotation && anno.properties.length === 1) {
        return getValueStr(anno.properties.at(0)!);
    }
    return undefined;
}

export function getValueInDecorator(node: arkts.ClassProperty, decoratorName: DecoratorNames): string | undefined {
    const annotations: readonly arkts.AnnotationUsage[] = node.annotations;
    for (let i = 0; i < annotations.length; i++) {
        const anno: arkts.AnnotationUsage = annotations[i];
        const str: string | undefined = getAnnotationValue(anno, decoratorName);
        if (!!str) {
            return str;
        }
    }
    return undefined;
}

export function generateGetOrSetCall(beforCall: arkts.Expression, type: string) {
    return arkts.factory.createCallExpression(
        arkts.factory.createMemberExpression(
            beforCall,
            arkts.factory.createIdentifier(type, undefined),
            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
            false,
            false
        ),
        type === "set" ? [arkts.factory.createIdentifier("value", undefined)] : [],
        undefined,
        false,
        false,
        undefined,
    );
}