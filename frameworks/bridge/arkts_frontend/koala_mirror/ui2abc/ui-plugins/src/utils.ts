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
    COMPONENT_DEFAULT_IMPORT = '@ohos.arkui',
    COMPONENT_CLASS_NAME = 'StructBase',
    COMPONENT_INTERFACE_PREFIX = '__Options_',
    COMPONENT_DISPOSE_STRUCT = '__disposeStruct',
    COMPONENT_INITIALIZE_STRUCT = '__initializeStruct',
    COMPONENT_UPDATE_STRUCT = '__updateStruct',
    COMPONENT_BUILD = '_build',
    REUSABLE_COMPONENT_REBIND_STATE = '__rebindStates',
    COMPONENT_INITIALIZERS_NAME = 'initializers'
}

export enum BuilderLambdaNames {
    ANNOTATION_NAME = 'ComponentBuilder',
    ORIGIN_METHOD_NAME = '$_instantiate',
    TRANSFORM_METHOD_NAME = '_instantiateImpl',
    STYLE_PARAM_NAME = 'style',
    STYLE_ARROW_PARAM_NAME = 'instance',
    CONTENT_PARAM_NAME = 'content',
}

export enum InternalAnnotations {
    MEMO = 'memo',
    MEMO_STABLE = 'memo_stable',
}

export function uiAttributeName(componentName: string): string {
    return `UI${componentName}Attribute`
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
    private defaultArkUIImports = [
        'Color',
        'ClickEvent', 'FlexAlign',
        'Image', 'Button', 'List',
        'PageTransitionEnter', 'PageTransitionExit', 'PageTransitionOptions',
        'Column', 'ColumnOptions', 'Row', 'RowOptions',
        'FlexOptions', 'TabsOptions', 'StackOptions', 'ToggleOptions', 'TextInputOptions',
        'TestComponent', 'TestComponentOptions', 'ForEach', 'Text',
        'Margin', 'Padding', 'BorderOptions', 'Curve', 'RouteType', 'TextOverflowOptions',
        'Flex', 'FlexWrap', 'HorizontalAlign', 'Scroll', 'Tabs', 'TabsController', 'TabContent',
        'NavDestination', 'NavPathStack', 'Literal_String_target_NavigationType_type',
        'IDataSource', 'DataChangeListener', 'ItemAlign', 'ImageFit', 'FlexDirection',
        'FontWeight', 'Counter', 'Toggle', 'ToggleType', 'BarMode', 'TextAlign', 'VerticalAlign',
        'TextOverflow', 'BarState', 'NavPathInfo', 'Stack', 'Swiper',
        'ListItem', 'Grid', 'GridItem', 'Navigator', 'Position', 'Axis',
        'TextInput', 'Font', 'Alignment', 'Visibility', 'ImageRepeat', 'SizeOptions', 'Divider',
        'TabBarOptions', 'Navigation', 'Span', 'NavigationMode', 'BarPosition', 'EnterKeyType',
        'LazyForEach',
        'TestComponent', 'TestComponentOptions', 'UITestComponentAttribute', 'ForEach', 'Text',
        'AppStorage', 'LocalStorage', 'AbstractProperty', 'SubscribedAbstractProperty',
    ]
    constructor() {
        const withDefaultImports = true
        if (withDefaultImports) {
            this.defaultArkUIImports.forEach(it => {
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
