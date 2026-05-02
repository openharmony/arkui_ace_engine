/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { int32 } from '@koalaui/common';
import { ExtendableComponent } from './extendableComponent';
import { CustomComponentV2 } from './customComponent';
import { InteropNativeModule } from '@koalaui/interop';
import { ArkUIAniModule } from '../ani/arkts/ArkUIAniModule';
import {
    IVariableOwner,
    StateMgmtDFX,
    StringUtils,
    DumpInfo,
    DFXDecoratorInfo,
    ElementInfo
} from '@ohos.arkui.stateManagement';

export interface ElementCounter {
    total: number
}

export interface StaticDFXCommand {
    what: string;
    viewId: int32 | undefined;
    isRecursive: boolean;
}

export class ExtendableComponentDFX {
    static onDumpInspector(component: ExtendableComponent): string {
        const dumpInfo: DumpInfo = new DumpInfo();
        const isV2 = component instanceof CustomComponentV2;
        dumpInfo.viewinfo = {
            componentName: Class.of(component).getName(),
            isV2: isV2
        };
        let ret: string = '';
        try {
            StateMgmtDFX.getDecoratedVariableInfo(component, dumpInfo, isV2);
            ret = JSON.stringify(dumpInfo);
        } catch (error) {
            InteropNativeModule._NativeLog(`dump component ${ dumpInfo.viewinfo.componentName} error: ${(error as Error).message}`);
        }
        return ret;
    }

    static onDumpInfo(component: ExtendableComponent, commands: string[]): void {
        const dfxCommands: StaticDFXCommand[] = ExtendableComponentDFX.processOnDumpCommands(commands);
        const isV2 = component instanceof CustomComponentV2;
        const headerStr = isV2 ? 'Static ComponentV2' : 'Static Component';
        for (const command of dfxCommands) {
            let targetView: ExtendableComponent = component;
            if (command.viewId !== undefined) {
                const found = ExtendableComponentDFX.findViewInHierarchy(component, command.viewId as int32);
                if (!found) {
                    ArkUIAniModule._DumpLogPrint(0, `\nTarget view: ${command.viewId} not found for command: ${command.what}\n`);
                    continue;
                }
                targetView = found as ExtendableComponent;
            } else {
                targetView = component;
                command.viewId = component.getUniqueId();
            }
            switch (command.what) {
              case '-dumpAll': {
                  ExtendableComponentDFX.printDFXHeader(headerStr + 'Info', command);
                  ExtendableComponentDFX.debugInfoView(targetView, command.isRecursive);
                  break;
              }
              case '-viewHierarchy': {
                  ExtendableComponentDFX.printDFXHeader(headerStr + 'Hierarchy', command);
                  ExtendableComponentDFX.debugInfoViewHierarchy(targetView, 0, command.isRecursive);
                  break;
              }
              case '-stateVariables': {
                  ExtendableComponentDFX.printDFXHeader(headerStr + 'State Variables', command);
                  ExtendableComponentDFX.debugInfoStateVars(targetView, command.isRecursive);
                  break;
              }
              case '-registeredElementIds': {
                  ExtendableComponentDFX.printDFXHeader(headerStr + 'Registered Element IDs', command);
                  ExtendableComponentDFX.debugInfoRegisteredElementIds(targetView, 0, command.isRecursive, { total: 0 });
                  break;
              }
              case '-dirtyElementIds': {
                  ExtendableComponentDFX.printDFXHeader(headerStr + 'Dirty Registered Element IDs', command);
                  ArkUIAniModule._DumpLogPrint(0, '\nDirty Element IDs are not supported on static (ArkTS) components.\n');
                  break;
              }
              case '-inactiveComponents': {
                  ExtendableComponentDFX.printDFXHeader('List of Inactive Components', command);
                  ExtendableComponentDFX.debugInfoInactiveComponents(targetView, command.isRecursive);
                  break;
              }
              case '-profiler': {
                  ExtendableComponentDFX.printDFXHeader('Profiler Info', command);
                  ArkUIAniModule._DumpLogPrint(0, '\nProfiler is not supported on static (ArkTS) components.\n');
                  break;
              }
              case 'RecyclePool': {
                  ArkUIAniModule._DumpLogPrint(0, 'RecyclePool: [Not supported on static side]\n');
                  break;
              }
              default:
                  if (command.what) {
                      ArkUIAniModule._DumpLogPrint(0, `\nUnsupported JS DFX dump command: [${command.what}, viewId=${command.viewId}, isRecursive=${command.isRecursive}]\n`);
                  }
                  break;
            }
        }
    }

    private static processOnDumpCommands(commands: string[]): StaticDFXCommand[] {
        let dfxCommands: StaticDFXCommand[] = [];
        for (let i = 0; i < commands.length; i++) {
            const command = commands[i];
            if (command === '-r') {
                const dfxCommand = dfxCommands[dfxCommands.length - 1];
                if (dfxCommand) {
                    dfxCommand.isRecursive = true;
                }
            } else if (command.startsWith('-viewId=')) {
                const dfxCommand = dfxCommands[dfxCommands.length - 1];
                if (dfxCommand) {
                    const input = command.split('=');
                    if (input[1]) {
                        const viewId = Number.parseInt(input[1]);
                        dfxCommand.viewId = Number.isNaN(viewId) ? undefined : Double.toInt(viewId);
                    }
                }
            } else {
                dfxCommands.push({
                    what: command,
                    viewId: undefined,
                    isRecursive: false,
                });
            }
        }
        return dfxCommands;
    }

    private static findViewInHierarchy(component: ExtendableComponent, viewId: int32): ExtendableComponent | undefined {
        const childrenMap = component.__getChildrenWeakRefMap__Internal();
        const weakChild = childrenMap.get(viewId);
        if (weakChild) {
            const child = weakChild.deref();
            if (child) {
                return child;
            }
        }
        let result: ExtendableComponent | undefined = undefined;
        childrenMap.forEach((weak: WeakRef<ExtendableComponent>, _: int32) => {
            if (!result) {
                const child = weak.deref();
                if (child) {
                    result = ExtendableComponentDFX.findViewInHierarchy(child, viewId);
                }
            }
        });
        return result;
    }

    private static printDFXHeader(header: string, command: StaticDFXCommand): void {
        const length = 50;
        const remainder = length - header.length < 0 ? 0 : length - header.length;
        const half = Math.floor(remainder / 2);
        ArkUIAniModule._DumpLogPrint(0, `\n${StringUtils.repeat('-', half)}${header}${StringUtils.repeat('-', half)}`);
        ArkUIAniModule._DumpLogPrint(0, `[${command.what}, viewId=${command.viewId}, isRecursive=${command.isRecursive}]\n`);
    }

    private static debugInfoViewHierarchy(component: ExtendableComponent, depth: number, isRecursive: boolean): void {
        const componentName = Class.of(component).getName();
        const isV2 = component instanceof CustomComponentV2;
        let output = `\n${StringUtils.repeat('  ', depth)}|--${componentName}[${component.getUniqueId()}]`;
        output += isV2 ? 'StaticComponentV2' : 'StaticComponent';
        output += ` {isViewActive: ${component.__isViewActive__Internal()}}`;
        ArkUIAniModule._DumpLogPrint(0, output);
        if (depth < 1 || isRecursive) {
            const childrenMap = component.__getChildrenWeakRefMap__Internal();
            childrenMap.forEach((weak: WeakRef<ExtendableComponent>, _: int32) => {
                const child = weak.deref();
                if (child) {
                    ExtendableComponentDFX.debugInfoViewHierarchy(child, depth + 1, isRecursive);
                }
            });
        }
    }

    private static debugInfoStateVars(component: ExtendableComponent, isRecursive: boolean): void {
        const isV2 = component instanceof CustomComponentV2;
        const componentName = Class.of(component).getName();
        const dumpInfo: DumpInfo = new DumpInfo();
        dumpInfo.viewinfo = {
            componentName: componentName,
            isV2: isV2
        };
        try {
            StateMgmtDFX.getDecoratedVariableInfo(component, dumpInfo, isV2, true);
            let result: string = `|--${componentName}[${component.getUniqueId()}]`;
            const observedProps = dumpInfo.observedPropertiesInfo as Array<DFXDecoratorInfo>;
            if (!observedProps || observedProps.length === 0) {
                result += '\n No State Variables';
                ArkUIAniModule._DumpLogPrint(0, result);
            } else {
                observedProps.forEach((info: DFXDecoratorInfo) => {
                    const decorator = info.decorator ?? '';
                    const varName = info.propertyName;
                    const varNameStr = varName instanceof Array ? varName.join(', ') : String(varName);
                    result += `\n  ${decorator} '${varNameStr}'[${info.id ?? -1}]`;
                    if (isV2) {
                        result += `\n  |--Owned by @ComponentV2 ${componentName}`;
                    } else {
                        result += `\n  |--Owned by @Component ${componentName}`;
                    }
                    const depIds = (info.dependentElementIds) as Array<ElementInfo>;
                    if (Array.isArray(depIds) && depIds.length > 0) {
                        let elements = '';
                        for (let i = 0; i < depIds.length; i++) {
                            if (i > 0) {
                                elements += ' ';
                            }
                            const elementInfo = depIds[i];
                            elements += `${elementInfo.elementName}[${elementInfo.elementId}]`;
                        }
                        result += `\n  |--DependentElements: ${elements}`;
                    } else {
                        result += '\n  |--DependentElements: none';
                    }
                });
                ArkUIAniModule._DumpLogPrint(0, result);
            }
        } catch (error) {
            ArkUIAniModule._DumpLogPrint(0, `Error dumping state variables: ${(error as Error).message}`);
        }
        if (isRecursive) {
            const childrenMap = component.__getChildrenWeakRefMap__Internal();
            childrenMap.forEach((weak: WeakRef<ExtendableComponent>, _: int32) => {
                const child = weak.deref();
                if (child) {
                    ExtendableComponentDFX.debugInfoStateVars(child, isRecursive);
                }
            });
        }
    }

    private static debugInfoRegisteredElementIds(component: ExtendableComponent, depth: number,
        isRecursive: boolean, counter: ElementCounter): void {
        const componentName = Class.of(component).getName();
        let output = `\n${StringUtils.repeat('  ', depth)}|--${componentName}[${component.getUniqueId()}]: {`;
        const childrenMap = component.__getChildrenWeakRefMap__Internal();
        childrenMap.forEach((weak: WeakRef<ExtendableComponent>, key: int32) => {
            const child = weak.deref();
            if (child) {
                output += `\n${StringUtils.repeat('  ', depth + 2)}${Class.of(child).getName()}[${key}]`;
            }
        });
        counter.total += childrenMap.size;
        output += `\n${StringUtils.repeat('  ', depth + 1)}}[${childrenMap.size}]`;
        ArkUIAniModule._DumpLogPrint(0, output);
        if (isRecursive) {
            childrenMap.forEach((weak: WeakRef<ExtendableComponent>, _: int32) => {
                const child = weak.deref();
                if (child) {
                    ExtendableComponentDFX.debugInfoRegisteredElementIds(child, depth + 1, isRecursive, counter);
                }
            });
        }
        if (isRecursive && depth === 0) {
            ArkUIAniModule._DumpLogPrint(0, `\nTotal: ${counter.total}`);
        }
    }

    private static collectInactiveComponents(component: ExtendableComponent,
        inactiveList: string[], isRecursive: boolean): void {
        const childrenMap = component.__getChildrenWeakRefMap__Internal();
        childrenMap.forEach((weak: WeakRef<ExtendableComponent>, _: int32) => {
            const child = weak.deref();
            if (child) {
                const isActive = child.__isViewActive__Internal();
                if (!isActive) {
                    const componentName = Class.of(child).getName();
                    inactiveList.push(`- ${componentName}[${child.getUniqueId()}]`);
                }
                if (isRecursive) {
                    ExtendableComponentDFX.collectInactiveComponents(child, inactiveList, isRecursive);
                }
            }
        });
    }

    private static debugInfoInactiveComponents(component: ExtendableComponent, isRecursive: boolean): void {
        const inactiveList: string[] = [];
        ExtendableComponentDFX.collectInactiveComponents(component, inactiveList, isRecursive);
        if (inactiveList.length === 0) {
            ArkUIAniModule._DumpLogPrint(0, '\nNo inactive components.\n');
        } else {
            ArkUIAniModule._DumpLogPrint(0, `\n${inactiveList.join('\n')}\n`);
        }
    }

    private static debugInfoView(component: ExtendableComponent, isRecursive: boolean): void {
        const componentName = Class.of(component).getName();
        const isV2 = component instanceof CustomComponentV2;
        const typeStr = isV2 ? '@ComponentV2' : '@Component';
        ArkUIAniModule._DumpLogPrint(0, `${typeStr}\n${componentName}[${component.getUniqueId()}]`);
        ArkUIAniModule._DumpLogPrint(0, '\nView Hierarchy:');
        ExtendableComponentDFX.debugInfoViewHierarchy(component, 0, isRecursive);
        ArkUIAniModule._DumpLogPrint(0, '\nState variables:');
        ExtendableComponentDFX.debugInfoStateVars(component, isRecursive);
        ArkUIAniModule._DumpLogPrint(0, '\nRegistered Element IDs:');
        ExtendableComponentDFX.debugInfoRegisteredElementIds(component, 0, isRecursive, { total: 0 });
    }
}
