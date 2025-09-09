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
        return '@ohos.arkui'
    } else {
        return 'arkui.stateManagement.decorator'
    }
}

export function getComponentPackage(): string {
    if (isKoalaWorkspace()) {
        return '@ohos.arkui'
    } else {
        return '@ohos.arkui.component'
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
                this.add(it, '@ohos.arkui')
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