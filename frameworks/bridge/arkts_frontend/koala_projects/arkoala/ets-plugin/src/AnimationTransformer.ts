/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import * as ts from '@koalaui/ets-tsc'
import { AbstractVisitor } from "./AbstractVisitor"
import { id } from './ApiUtils'

function log(...strings: string[]) {
    if (true) console.log("AnimationTransformer:", ...strings)
}

function isAnimationCall(access: ts.PropertyAccessExpression): boolean {
    return "animation" === ts.idText(access.name)
}

function isStylingWithAnimation(call: ts.CallExpression, found = false): boolean {
    const access = call.expression
    if (ts.isPropertyAccessExpression(access) && ts.isIdentifier(access.name)) {
        if (!found) found = isAnimationCall(access)
        const target = access.expression
        if (ts.isEtsComponentExpression(target)) return found // works before ETS replaced
        if (ts.isCallExpression(target)) return isStylingWithAnimation(target, found)
        if (ts.isIdentifier(target)) {
            const name = ts.idText(target)
            if (found) log("found", name)
            return found //? && (name === "CommonInstance")
        }
    }
    return false
}

function create(target: ts.Expression, name: string, args: ReadonlyArray<ts.Expression>): ts.CallExpression {
    log("create", name)
    return ts.factory.createCallExpression(
        ts.factory.createPropertyAccessExpression(target, name),
        undefined,
        args)
}

function update(call: ts.CallExpression, access: ts.PropertyAccessExpression, target: ts.Expression): ts.CallExpression {
    log("update", ts.idText(access.name))
    return ts.factory.updateCallExpression(
        call,
        ts.factory.updatePropertyAccessExpression(access, target, access.name),
        call.typeArguments,
        call.arguments)
}

function replace(call: ts.CallExpression, access: ts.PropertyAccessExpression, target: ts.Expression, name: string): ts.CallExpression {
    log("replace", ts.idText(access.name), "with", name)
    return ts.factory.updateCallExpression(
        call,
        ts.factory.updatePropertyAccessExpression(access, target, id(name)),
        undefined,
        [])
}

export class AnimationTransformer extends AbstractVisitor {
    constructor(sourceFile: ts.SourceFile, ctx: ts.TransformationContext, private disabled: boolean) {
        super(sourceFile, ctx)
    }

    visitor(node: ts.Node): ts.Node {
        if (this.disabled) return node // when animationStart/animationStop is not implemented
        return ts.isCallExpression(node) && isStylingWithAnimation(node)
            ? this.visitStyleWithAnimation(node)
            : this.visitEachChild(node)
    }

    private visitStyleWithAnimation(call: ts.CallExpression, args?: ReadonlyArray<ts.Expression>): ts.CallExpression {
        const access = call.expression as ts.PropertyAccessExpression
        let target = access.expression // left hand side to process recursively
        if (isAnimationCall(access)) {
            // visit recursively with arguments of the current "animation" call
            if (ts.isCallExpression(target)) target = this.visitStyleWithAnimation(target, call.arguments)
            // replace "animation" call with "animationStop"
            call = replace(call, access, target, "animationStop")
            //  insert "animationStart" before "animationStop" if arguments are provided
            return args ? create(call, "animationStart", args) : call
        }
        // visit recursively with arguments of the last "animation" call if not finished
        if (ts.isCallExpression(target)) return update(call, access, this.visitStyleWithAnimation(target, args))
        //  insert "animationStart" in the very beginning if arguments are provided
        if (args) return update(call, access, create(target, "animationStart", args))
        log("skip", ts.idText(access.name))
        return call
    }
}
