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

import { Assert, suite, test } from "@koalaui/harness"
import { asArray, int32 } from "@koalaui/common"
import { TestNode, testRoot, testTick, mutableState, GlobalStateManager, StateContext } from "@koalaui/runtime"
import { __id, __key, __context } from "@koalaui/runtime"

import {
    sharedMemoFunction,
} from "./main_test_module_to_import"
import { SharedLog } from "./test_module_to_import"
import * as ut from "./main_test_module_to_import"
import { isCompilerPlugin } from "../testUtils"

function assertResultArray<T>(actual: Array<T>, ...expected: T[]) {
    Assert.deepEqual(actual, asArray(expected))
}

class GlobalStateHolder {
    static globalState = GlobalStateManager.instance.mutableState<number>(0, true)
}

class Log {
    log = new Array<string>()
}

interface B {
    /** @memo */
    interfaceMethod(): void
    /** @memo */
    testInterfaceMethod(): void

    localLog: Array<string>
}

class A implements B {
    static staticLog = new Array<string>()

    /** @memo */
    static testStaticMethod(): void {
        GlobalStateHolder.globalState.value
        A.staticLog.push("staticMethod call")
        A.staticMethod()
    }

    /** @memo */
    static testGlobalFunction(): void {
        GlobalStateHolder.globalState.value
        globalLog.push("global function call")
        globalFunction()
    }

    localLog: Array<string> = new Array<string>()
    constructor(localLogValue: Array<string>) {
        this.localLog = localLogValue
    }

    /** @memo */
    testInterfaceMethod(): void {
        GlobalStateHolder.globalState.value
        this.localLog.push("interfaceMethod call")
        this.interfaceMethod()
    }

    /** @memo */
    static staticMethod(): void {
        A.staticLog.push("staticMethod")
    }

    /** @memo */
    interfaceMethod(): void {
        this.localLog.push("interfaceMethod")
    }

    /** @memo */
    testProp(): void {
        GlobalStateHolder.globalState.value
        this.localLog.push("propFunction call")
        this.propFunction()
    }

    /** @memo */
    propFunction =
    /** @memo */
    () => {
        this.localLog.push("propFunction")
    }

    static returnMemoMethod():
        /** @memo */
        (log: Array<string>, value: string) => void
    {
        return (
            /** @memo */
            (log: Array<string>, value: string) => {
                log.push("returnMemoMethod", value)
            }
        )
    }

}

type memoFunctionType =
/** @memo */
() => void

const globalLog = new Array<string>()
/** @memo */
function globalFunction(): void {
    globalLog.push("global function")
}

/** @memo */
function callMemoFunction(
    /** @memo */
    fun:
    () => void
): void {
    fun()
}

function returnGlobalMemoFunction():
    /** @memo */
    (log: Array<string>, value: string) => void
{
    return (
        /** @memo */
        (log: Array<string>, value: string) => {
            log.push("returnMemoFunction", value)
        }
    )
}

class TestReturnGlobalMemoFunction extends Log {
    /** @memo */
    test() {
        this.runReturnMemo(returnGlobalMemoFunction())
    }

    /** @memo */
    runReturnMemo(
        /** @memo */
        parameter: (log: Array<string>, value: string)=>void
    ) {
        GlobalStateHolder.globalState.value
        this.log.push("returnMemoFunction call")
        parameter(this.log, "arg")
    }
}

class TestReturnMethod extends Log {
    /** @memo */
    test() {
        this.runReturnMemo(A.returnMemoMethod())
    }

    /** @memo */
    runReturnMemo(
        /** @memo */
        parameter: (log: Array<string>, value: string)=>void
    ) {
        GlobalStateHolder.globalState.value
        this.log.push("returnMemoMethod call")
        parameter(this.log, "arg")
    }
}

function returnListMemoFunctions(): [
    /** @memo */
    () => void,
    /** @memo */
    () => void
] {
    return [
        /** @memo */
        () => {
            globalLog.push('hi')
        },
        /** @memo */
        () => {
            GlobalStateHolder.globalState.value
            globalLog.push('hello')
        }
    ]
}

class TestLambdaDeduce {
    static log = new Array<string>()

    /** @memo */
    static testLambdaDeduce() {
        TestLambdaDeduce.acceptsLambda(
            /** @memo */
            (): void => {
                TestLambdaDeduce.log.push("deduce lambda")
            }
        )
    }

    /** @memo */
    static acceptsLambda(
        /** @memo */
        parameter: () => void
    ): void {
        GlobalStateHolder.globalState.value
        TestLambdaDeduce.log.push("deduced lambda call")
        parameter()
    }
}

class TestPropertyInitializerDeduce extends Log {
    instance: TestPropertyInitializerDeduce|undefined = undefined

    /** @memo */
    initializedProperty =
    /** @memo */
    () => {
        this.log.push("parameter initializer deduce")
    }

    /** @memo */
    testInitializerDeduce() {
        GlobalStateHolder.globalState.value
        this.log.push("deduced parameter call")
        this.initializedProperty()
    }
}

/** @memo */
const initializedVariableGlobal =
(log: Array<string>) => {
    log.push("variable global initializer deduce")
}

class TestVariableInitializerDeduce extends Log {

    /** @memo */
    testInitializerDeduce() {
        GlobalStateHolder.globalState.value
        this.log.push("deduced variable call")

        /** @memo */
        const initializedVariable = (log: Array<string>) => {
            log.push("variable initializer deduce")
        }
        initializedVariable(this.log)
        initializedVariableGlobal(this.log)
    }
}

interface DataClass {
    value: number
    message: string
}
class TestObjectLiteralMemoization extends Log {
    /** @memo */
    test() {
        this.log.push("method with object parameter call")
        GlobalStateHolder.globalState.value
        this.methodWithObjectParameter({message: "hello", value: 47} as DataClass)
    }

    /** @memo */
    testWithParentheses() {
        this.log.push("method with object parameter call with parentheses")
        GlobalStateHolder.globalState.value
        this.methodWithObjectParameter(((({message: "hello", value: 47}))) as DataClass)
    }

    /** @memo */
    methodWithObjectParameter(data: DataClass) {
        this.log.push("method with object parameter", data.message)
    }
}

class TestLambdaLiteralMemoization extends Log {
    /** @memo */
    test(): void {
        this.log.push("method with lambda parameter call")
        GlobalStateHolder.globalState.value
        this.methodWithLambdaParameter((): void => {})
    }

    /** @memo */
    methodWithLambdaParameter(param: () => void) {
        param
        this.log.push("method with lambda parameter")
    }
}

class Unstable {
    /** @memo */
    method(log: Array<string>) {
        log.push("unstable class method")
    }
}

class UnstableUseReceiver {
    /** @memo */
    method(log: Array<string>) {
        log.push("unstable class method use this")
        const a = this
    }
}

/** @memo:stable */
class Stable {
    /** @memo */
    method(log: Array<string>) {
        log.push("stable class method")
    }
}

/** @memo:stable */
class StableUseReceiver {
    /** @memo */
    method(log: Array<string>) {
        log.push("stable class method use this")
        const b = this
    }
}

class TestMethodReceiver extends Log {

    /** @memo */
    testUnstable() {
        const unstableReceiver = new Unstable()
        this.log.push("unstable class method call")
        GlobalStateHolder.globalState.value
        unstableReceiver.method(this.log)
    }

    /** @memo */
    testUnstableUseReceiver() {
        const unstableReceiver = new UnstableUseReceiver()
        this.log.push("unstable class method use this call")
        GlobalStateHolder.globalState.value
        unstableReceiver.method(this.log)
    }

    /** @memo */
    testStable() {
        const stableReceiver = new Stable()
        this.log.push("stable class method call")
        GlobalStateHolder.globalState.value
        stableReceiver.method(this.log)
    }

    /** @memo */
    testStableUseReceiver() {
        const stableReceiver = new StableUseReceiver()
        this.log.push("stable class method use this call")
        GlobalStateHolder.globalState.value
        stableReceiver.method(this.log)
    }
}

class TestArrowFunction extends Log {
    /** @memo */
    test() {
        this.testArrow(

            (log: Array<string>): void => {
                log.push("arrow function")
            }
        )
    }
    /** @memo */
    testArrow(
        /** @memo */
        parameter: (log: Array<string>) => void
    ): void {
        this.log.push("arrow function call")
        GlobalStateHolder.globalState.value
        parameter(this.log)
    }
}

class TestOptionalProperties extends Log {

    constructor() {
        super()

        this.initializedProperty =
        /** @memo */
        () => {
            this.log.push("initialized property")
        }

        this.optionalInitializedProperty =
        /** @memo */
        () => {
            this.log.push("optional initialized property")
        }
    }

    /** @memo */
    initializedProperty:
    () => void

    /** @memo */
    testProperty() {
        GlobalStateHolder.globalState.value
        this.log.push("property call");
        this.initializedProperty()
    }

    /** @memo */
    optionalInitializedProperty?:
    () => void

    /** @memo */
    testOptionalProperty() {
        GlobalStateHolder.globalState.value
        this.log.push("optional property call")
        this.optionalInitializedProperty?.()
    }

    /** @memo */
    testOptionalWithParentheses() {
        GlobalStateHolder.globalState.value
        this.log.push("optional parentheses property call");
        ((this.optionalInitializedProperty))?.()
    }

    /** @memo */
    static foo() {

    }

    /** @memo */
    static testFoo() {
        TestOptionalProperties.foo()
    }
}

class TestTrackingParameters {
    static log: Array<string> = new Array<string>()

    static varValue: number = 10
    /** @memo */
    testParam() {
        GlobalStateHolder.globalState.value
        TestTrackingParameters.log.push(`methodWithParam: ${TestTrackingParameters.varValue} call`)
        this.methodWithParam(
            TestTrackingParameters.varValue
        )
    }

    /** @memo */
    testSkipParam() {
        GlobalStateHolder.globalState.value
        TestTrackingParameters.log.push(`methodWithSkipParam: ${TestTrackingParameters.varValue} call`)
        this.methodWithSkipParam(
            TestTrackingParameters.varValue
        )
    }

    static updateFlag: boolean = false
    static instanceA = new TestTrackingParameters()
    static instanceB = new TestTrackingParameters()

    /** @memo */
    testThisParam() {
        GlobalStateHolder.globalState.value
        TestTrackingParameters.log.push(`testThisParam call`)
        let instance = TestTrackingParameters.updateFlag ? TestTrackingParameters.instanceB : TestTrackingParameters.instanceA
        if (TestTrackingParameters.updateFlag) TestTrackingParameters.updateFlag = false
        instance.method()
    }

    /** @memo */
    testContentParam() {
        GlobalStateHolder.globalState.value
        TestTrackingParameters.log.push(`testContentParam call`)
        this.methodWithContentParam(
            TestTrackingParameters.updateFlag ? this.methodWithParamCopy : this.methodWithParam,
            TestTrackingParameters.varValue
        )
        if (TestTrackingParameters.updateFlag) TestTrackingParameters.updateFlag = false
    }

    /** @memo */
    method() {
        TestTrackingParameters.log.push(`method`)
        this
    }

    /** @memo */
    methodWithParam(
        value: number
    ) {
        TestTrackingParameters.log.push(`methodWithParam: ${value}`)
    }

    /** @memo */
    methodWithParamCopy(
        value: number
    ) {
        TestTrackingParameters.log.push(`methodWithParamCopy: ${value}`)
    }

    /** @memo */
    methodWithSkipParam(
        /** @skip:memo */
        value: number
    ) {
        TestTrackingParameters.log.push(`methodWithSkipParam: ${value}`)
    }

    /** @memo */
    methodWithContentParam(
        /** @memo */
        content: (value: number) => void,
        value: number
    ) {
        TestTrackingParameters.log.push(`methodWithContentParam`)
        content(value)
    }

}

// lala
export type Key = int32
export class MutableState<T> {
    public value: T
    constructor(value: T) {
        this.value = value
    }
}
export class Scope<T> {
    param<T>(index: number, value: T): MutableState<T> {
        return new MutableState<T>(value)
    }
    recache<T>(value: T) { return value }
    get cached(): T {
        throw new Error("")
    }
    unchanged = false
}

/** @memo */
function memoFunction(log: Array<string>) {
    log.push('memo function')
}

/** @memo:entry */
function functionMemoEntry(__memo_context: StateContext, __memo_id: Key, log: Array<string>): void {
    log.push('test entry')
    memoFunction(log)
}

class TestEntry extends Log {
    testEntry(): void {
        functionMemoEntry(GlobalStateManager.instance, 10, this.log)
    }
}

/** @memo:intrinsic */
function intrinsicFunction() {
    let id = __id()
    let context = __context()
    TestIntrinsic.log.push('intrinsicFunction', `${context.node?.kind}`)
}

class TestIntrinsic {
    static log: Array<string> = new Array<string>()


    /** @memo */
    static testIntrinsicMethod(): void {
        GlobalStateHolder.globalState.value
        TestIntrinsic.log.push('testIntrinsicMethod call')
        TestIntrinsic.intrinsicMethod()
    }

    /** @memo */
    static testIntrinsicFunction(): void {
        GlobalStateHolder.globalState.value
        TestIntrinsic.log.push('testIntrinsicFunction call')
        intrinsicFunction()
    }

    /** @memo */
    static testKeyAccessor(): void {
        GlobalStateHolder.globalState.value
        TestIntrinsic.log.push('testKeyAccessor call')
        TestIntrinsic.intrinsicKeyAccessor()
    }

    /** @memo:intrinsic */
    static intrinsicMethod(): void {
        let id = __id()
        let context = __context()
        TestIntrinsic.log.push('intrinsicMethod', `${context.node?.kind}`)
    }

    /** @memo:intrinsic */
    static intrinsicKeyAccessor(): void {
        let key = __key()
        TestIntrinsic.log.push('intrinsicKeyAccessor')
    }
}

class TestImportedMemo {

    /** @memo */
    static testImportedFunction(): void {
        GlobalStateHolder.globalState.value
        SharedLog.log.push('testImportedFunction call')
        sharedMemoFunction()
        ut.sharedMemoFunction()
    }
}

/** @memo:stable */
class TestMemoStable extends Log {
    /** @memo */
    functionReturnsThis(): this {
        this.log.push(`function call`)
        return this
    }

    /** @memo */
    testFunctionReturnsThis(): void {
        GlobalStateHolder.globalState.value
        this.log.push(`test call`)
        this.functionReturnsThis()
    }

    /** @memo */
    functionReturnsString(): string {
        this.log.push(`function call`)
        return "a"
    }

    /** @memo */
    testFunctionReturnsString(): void {
        GlobalStateHolder.globalState.value
        this.log.push(`test call`)
        this.functionReturnsString()
    }
}

class RefType {
    public value: number

    constructor() {
        this.value = 0
    }
}

class TestEquality {
    static log: Array<string> = new Array<string>()

    static val: number = 0

    static ref: RefType = new RefType()

    /** @memo */
    static testFunction(): void {
        GlobalStateHolder.globalState.value
        TestEquality.log.push('testFunction call')
        TestEquality.methodWithParams(TestEquality.val, TestEquality.ref)
    }

    /** @memo */
    static methodWithParams(
        value: number,
        ref: RefType,
    ) {
        TestEquality.log.push(`methodWithParams: ${value} ${ref.value}`)
    }

}

suite("Basic memo semantic", () => {
    test("Method declaration in class. Static method is not reinvoked", () => {
        const root = testRoot(A.testStaticMethod)
        assertResultArray(A.staticLog,
            "staticMethod call",
            "staticMethod"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(A.staticLog,
            "staticMethod call",
            "staticMethod",
            "staticMethod call"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(A.staticLog,
            "staticMethod call",
            "staticMethod",
            "staticMethod call",
            "staticMethod call"
        )
    })
    test("File scope function declaration. Function is not reinvoked", () => {
        const root = testRoot(A.testGlobalFunction)
        assertResultArray(globalLog,
            "global function call",
            "global function"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(globalLog,
            "global function call",
            "global function",
            "global function call",
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(globalLog,
            "global function call",
            "global function",
            "global function call",
            "global function call",
        )
    })

    test("Property of functional type in class", () => {
        const instance: A = new A(new Array<string>())
        const root = testRoot(
            /** @memo */
            () => {instance.testProp()}
        )
        assertResultArray(instance.localLog,
            "propFunction call",
            "propFunction"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(instance.localLog,
            "propFunction call",
            "propFunction",
            "propFunction call",
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(instance.localLog,
            "propFunction call",
            "propFunction",
            "propFunction call",
            "propFunction call",
        )

    })

    test("Method declaration in interface", () => {
        const instance: B = new A(new Array<string>())
        const root = testRoot(
            /** @memo */
            () => { instance.testInterfaceMethod() }
        )
        assertResultArray(instance.localLog,
            "interfaceMethod call",
            "interfaceMethod"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(instance.localLog,
            "interfaceMethod call",
            "interfaceMethod",
            "interfaceMethod call"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(instance.localLog,
            "interfaceMethod call",
            "interfaceMethod",
            "interfaceMethod call",
            "interfaceMethod call"
        )
    })
    test("Type alias of function type", () => {
        let fun: memoFunctionType =
        /** @memo */
        () => {
            GlobalStateHolder.globalState.value
            globalLog.push("typeAlias")
        }

        globalLog.length = 0
        const root = testRoot(fun)
        assertResultArray(globalLog, "typeAlias")
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(globalLog, "typeAlias", "typeAlias")
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(globalLog, "typeAlias", "typeAlias", "typeAlias")
    })
    test("Arrow function", () => {
        const instance = new TestArrowFunction()
        const root = testRoot(
            /** @memo */
            () => { instance.test() }
        )
        assertResultArray(instance.log,
            "arrow function call",
            "arrow function"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.log,
            "arrow function call",
            "arrow function",
            "arrow function call",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.log,
            "arrow function call",
            "arrow function",
            "arrow function call",
            "arrow function call",
        )
    })

    test("Return type of functional type in function", () => {
        const instance = new TestReturnGlobalMemoFunction()
        const root = testRoot(
            /** @memo */
            () => { instance.test() }
        )
        assertResultArray(instance.log,
            "returnMemoFunction call",
            "returnMemoFunction",
            "arg"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.log,
            "returnMemoFunction call",
            "returnMemoFunction",
            "arg",
            "returnMemoFunction call",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.log,
            "returnMemoFunction call",
            "returnMemoFunction",
            "arg",
            "returnMemoFunction call",
            "returnMemoFunction call",
        )
    })

    test("Return type of functional type in method", () => {
        const instance = new TestReturnMethod()
        const root = testRoot(
            /** @memo */
            () => { instance.test() }
        )
        assertResultArray(instance.log,
            "returnMemoMethod call",
            "returnMemoMethod",
            "arg"
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.log,
            "returnMemoMethod call",
            "returnMemoMethod",
            "arg",
            "returnMemoMethod call",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(instance.log,
            "returnMemoMethod call",
            "returnMemoMethod",
            "arg",
            "returnMemoMethod call",
            "returnMemoMethod call",
        )
    })

    test.expectFailure("Description of the problem", "Return type of functional type in lambda", () => {
        Assert.fail('implement me')
    })

    test("Parameter of function type", () => {
        globalLog.length = 0
        const root = testRoot(
            /** @memo */
            () => {
                callMemoFunction(
                /** @memo */
                (): void => {
                    GlobalStateHolder.globalState.value
                    globalLog.push("functionParam")
                })
            }
        )

        assertResultArray(globalLog, "functionParam")

        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(globalLog, "functionParam", "functionParam")

        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(globalLog, "functionParam", "functionParam", "functionParam")
    })

    test("Return array of memo functional type", () => {
        globalLog.length = 0
        const functions = returnListMemoFunctions()
        const root = testRoot(
            functions[1]
        )
        assertResultArray(globalLog, "hello")
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(globalLog, "hello", "hello")
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(globalLog, "hello", "hello", "hello")
    })
})

suite("Auto-deducing memo annotation", () => {
    test("memo is assumed when pasing a lambda argument to a memo parameter", () => {
        const root = testRoot(TestLambdaDeduce.testLambdaDeduce)
        assertResultArray(TestLambdaDeduce.log,
            "deduced lambda call",
            "deduce lambda"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestLambdaDeduce.log,
            "deduced lambda call",
            "deduce lambda",
            "deduced lambda call",
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestLambdaDeduce.log,
            "deduced lambda call",
            "deduce lambda",
            "deduced lambda call",
            "deduced lambda call",
        )
    })
    test("memo is assumed when initializing a property", () => {
        const test = new TestPropertyInitializerDeduce()
        const root = testRoot(
            /** @memo */
            () => { test.testInitializerDeduce() }
        )
        assertResultArray(test.log,
            "deduced parameter call",
            "parameter initializer deduce"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "deduced parameter call",
            "parameter initializer deduce",
            "deduced parameter call"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "deduced parameter call",
            "parameter initializer deduce",
            "deduced parameter call",
            "deduced parameter call"
        )
    })
    test("memo is assumed when initializing a variable of functional type", () => {
        const test = new TestVariableInitializerDeduce()
        const root = testRoot(
            /** @memo */
            () => { test.testInitializerDeduce() }
        )
        assertResultArray(test.log,
            "deduced variable call",
            "variable initializer deduce",
            "variable global initializer deduce"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "deduced variable call",
            "variable initializer deduce",
            "variable global initializer deduce",
            "deduced variable call"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "deduced variable call",
            "variable initializer deduce",
            "variable global initializer deduce",
            "deduced variable call",
            "deduced variable call"
        )
    })
    test.expectFailure("Description of the problem", "memo is assumed when pasing a TRAILING lambda argument to a memo parameter", () => {
        Assert.fail("implement me")
    })
})

suite("Calls are eligible to memo transformation if...", () => {
    test("property access refers to a memo entity", () => {
        const test = new TestOptionalProperties()
        const root = testRoot(
            /** @memo */
            () => { test.testProperty() }
        )
        assertResultArray(test.log,
            "property call",
            "initialized property"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "property call",
            "initialized property",
            "property call"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "property call",
            "initialized property",
            "property call",
            "property call"
        )
    })
    test("nullable property access `bar.foo?.()` refers to a memo entity", () => {
        const test = new TestOptionalProperties()
        const root = testRoot(
            /** @memo */
            () => { test.testOptionalProperty() }
        )
        assertResultArray(test.log,
            "optional property call",
            "optional initialized property"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "optional property call",
            "optional initialized property",
            "optional property call"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "optional property call",
            "optional initialized property",
            "optional property call",
            "optional property call"
        )
    })
    test("parenthesized expression of the above", () => {
        const test = new TestOptionalProperties()
        const root = testRoot(
            /** @memo */
            () => { test.testOptionalWithParentheses() }
        )
        assertResultArray(test.log,
            "optional parentheses property call",
            "optional initialized property"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "optional parentheses property call",
            "optional initialized property",
            "optional parentheses property call"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "optional parentheses property call",
            "optional initialized property",
            "optional parentheses property call",
            "optional parentheses property call"
        )
    })
    test("the memo entity can be of type:\n\tfunction\n\tfunction|undefined\n\tparenthesized function|undefined", () => {
        /** @memo */
        const x1:
        () => void
        = TestOptionalProperties.testFoo

        /** @memo */
        const x2:
        () => void
        =
        () => { console.log('test') }

        /** @memo */
        const x3:
        (/** @memo */ (() => void)) | undefined
        = undefined

        /** @memo */
        const x4:
        (/** @memo */ () => void) | undefined
        = TestOptionalProperties.testFoo

        /** @memo */
        const x5:
        ((/** @memo */ (() => void)))
        = TestOptionalProperties.testFoo
    })
})

suite("Tracking parameters", () => {
    test("Parameters of memo functions trigger recomputation", () => {
        const test = new TestTrackingParameters()
        const root = testRoot(
            /** @memo */
            () => { test.testParam() }
        )
        assertResultArray(TestTrackingParameters.log,
            `methodWithParam: 10 call`,
            `methodWithParam: 10`
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestTrackingParameters.log,
            `methodWithParam: 10 call`,
            `methodWithParam: 10`,
            `methodWithParam: 10 call`,
        )
        TestTrackingParameters.varValue = 50
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestTrackingParameters.log,
            `methodWithParam: 10 call`,
            `methodWithParam: 10`,
            `methodWithParam: 10 call`,
            `methodWithParam: 50 call`,
            `methodWithParam: 50`,
        )
    })
    test("Class receiver `this` is included among parameters", () => {
        TestTrackingParameters.log.length = 0
        const test = new TestTrackingParameters()
        const root = testRoot(
            /** @memo */
            () => { test.testThisParam() }
        )
        assertResultArray(TestTrackingParameters.log,
            `testThisParam call`,
            `method`
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestTrackingParameters.log,
            `testThisParam call`,
            `method`,
            `testThisParam call`,
        )
        TestTrackingParameters.updateFlag = true
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestTrackingParameters.log,
            `testThisParam call`,
            `method`,
            `testThisParam call`,
            `testThisParam call`,
            `method`,
        )
    })
    test("@skip:memo excludes parameter from the list of tracked", () => {
        TestTrackingParameters.log.length = 0
        TestTrackingParameters.varValue = 10
        const test = new TestTrackingParameters()
        const root = testRoot(
            /** @memo */
            () => { test.testSkipParam() }
        )
        assertResultArray(TestTrackingParameters.log,
            `methodWithSkipParam: 10 call`,
            `methodWithSkipParam: 10`
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestTrackingParameters.log,
            `methodWithSkipParam: 10 call`,
            `methodWithSkipParam: 10`,
            `methodWithSkipParam: 10 call`,
        )
        TestTrackingParameters.varValue = 50
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestTrackingParameters.log,
            `methodWithSkipParam: 10 call`,
            `methodWithSkipParam: 10`,
            `methodWithSkipParam: 10 call`,
            `methodWithSkipParam: 50 call`,
        )
    })
    test("Parameters (same as states) are compared as ===", () => {
        const root = testRoot(TestEquality.testFunction)
        assertResultArray(TestEquality.log,
            "testFunction call",
            "methodWithParams: 0 0",
        )
        TestEquality.val = 1
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestEquality.log,
            "testFunction call",
            "methodWithParams: 0 0",
            "testFunction call",
            "methodWithParams: 1 0",
        )
        TestEquality.ref.value = 1
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(TestEquality.log,
            "testFunction call",
            "methodWithParams: 0 0",
            "testFunction call",
            "methodWithParams: 1 0",
            "testFunction call",
        )
    })
    test.expectFailure("Description of the problem", "By convention a lambda parameter with name `content` is not tracked", () => {
        // This is to be addressed later when the compiler provides ability to compare
        // lambdas by code, not by closure object equality.

        TestTrackingParameters.log.length = 0
        TestTrackingParameters.varValue = 10
        TestTrackingParameters.updateFlag = false
        const test = new TestTrackingParameters()
        const root = testRoot(
            /** @memo */
            () => { test.testContentParam() }
        )
        assertResultArray(TestTrackingParameters.log,
            `testContentParam call`,
            `methodWithContentParam`,
            `methodWithParam: 10`
        )
        GlobalStateHolder.globalState.value ++
        TestTrackingParameters.updateFlag = true
        testTick(root)
        assertResultArray(TestTrackingParameters.log,
            `testContentParam call`,
            `methodWithContentParam`,
            `methodWithParam: 10`,
            `testContentParam call`,
            `methodWithContentParam`,
        )
        GlobalStateHolder.globalState.value ++
        TestTrackingParameters.varValue = 50
        testTick(root)
        assertResultArray(TestTrackingParameters.log,
            `testContentParam call`,
            `methodWithContentParam`,
            `methodWithParam: 10`,
            `testContentParam call`,
            `methodWithContentParam`,
            `testContentParam call`,
            `methodWithContentParam`,
            `methodWithParam: 50`
        )
    })
})

suite("Memoizing non-primitive arguments", () => {
    test("Object literal memoization", () => {
        const test = new TestObjectLiteralMemoization()
        const root = testRoot(
            /** @memo */
            () => { test.test() }
        )
        assertResultArray(test.log,
            "method with object parameter call",
            "method with object parameter",
            "hello",
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "method with object parameter call",
            "method with object parameter",
            "hello",
            "method with object parameter call"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "method with object parameter call",
            "method with object parameter",
            "hello",
            "method with object parameter call",
            "method with object parameter call"
        )
    })
    test("Lambda literal memoization", () => {
        const test = new TestLambdaLiteralMemoization()
        const root = testRoot(
            /** @memo */
            () => { test.test() }
        )
        assertResultArray(test.log,
            "method with lambda parameter call",
            "method with lambda parameter"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "method with lambda parameter call",
            "method with lambda parameter",
            "method with lambda parameter call"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "method with lambda parameter call",
            "method with lambda parameter",
            "method with lambda parameter call",
            "method with lambda parameter call"
        )
    })
})

suite("Method receivers", () => {
    test("Non used method receiver does not trigger recomputation by default", () => {
        const test = new TestMethodReceiver()
        const root = testRoot(
            /** @memo */
            () => { test.testUnstable() })
        assertResultArray(test.log,
            "unstable class method call",
            "unstable class method"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "unstable class method call",
            "unstable class method",
            "unstable class method call",
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "unstable class method call",
            "unstable class method",
            "unstable class method call",
            "unstable class method call",
        )
    })
    test("Used method receiver triggers recomputation by default", () => {
        const test = new TestMethodReceiver()
        const root = testRoot(
            /** @memo */
            () => { test.testUnstableUseReceiver() })
        assertResultArray(test.log,
            "unstable class method use this call",
            "unstable class method use this"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "unstable class method use this call",
            "unstable class method use this",
            "unstable class method use this call",
            "unstable class method use this"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "unstable class method use this call",
            "unstable class method use this",
            "unstable class method use this call",
            "unstable class method use this",
            "unstable class method use this call",
            "unstable class method use this",
        )
    })
    test("Non used method receiver doesn't trigger recomputation if class is stable", () => {
        const test = new TestMethodReceiver()
        const root = testRoot(
            /** @memo */
            () => { test.testStable() })
        assertResultArray(test.log,
            "stable class method call",
            "stable class method"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "stable class method call",
            "stable class method",
            "stable class method call",
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "stable class method call",
            "stable class method",
            "stable class method call",
            "stable class method call",
        )
    })
    test("Used method receiver doesn't trigger recomputation if class is stable", () => {
        const test = new TestMethodReceiver()
        const root = testRoot(
            /** @memo */
            () => { test.testStableUseReceiver() })
        assertResultArray(test.log,
            "stable class method use this call",
            "stable class method use this"
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "stable class method use this call",
            "stable class method use this",
            "stable class method use this call",
        )
        GlobalStateHolder.globalState.value ++
        testTick(root)
        assertResultArray(test.log,
            "stable class method use this call",
            "stable class method use this",
            "stable class method use this call",
            "stable class method use this call",
        )
    })

    test.expectFailure("Description of the problem", "lambda with receiver (ArkTS)", () => {
        Assert.fail('implement me')
    })
})

suite("Regular code is allowed to enter memo realm with @memo:entry annotation", () => {
    test("Memo entry", () => {
        const instance = new TestEntry()
        const root = testRoot(
            /** @memo */
            () => {
                instance.testEntry()
            })
        assertResultArray(instance.log,
            "test entry",
            "memo function",
        )
    })
})
suite("Functions marked with @memo:intrinsic", () => {
    test("File scope @memo:intrinsic function declaration", () => {
        TestIntrinsic.log.length = 0
        const root = testRoot(TestIntrinsic.testIntrinsicFunction)
        assertResultArray(TestIntrinsic.log,
            "testIntrinsicFunction call",
            "intrinsicFunction", "1",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(TestIntrinsic.log,
            "testIntrinsicFunction call",
            "intrinsicFunction", "1",
            "testIntrinsicFunction call",
            "intrinsicFunction", "1",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(TestIntrinsic.log,
            "testIntrinsicFunction call",
            "intrinsicFunction", "1",
            "testIntrinsicFunction call",
            "intrinsicFunction", "1",
            "testIntrinsicFunction call",
            "intrinsicFunction", "1",
        )
    })

    test("Class @memo:intrinsic method declaration", () => {
        TestIntrinsic.log.length = 0
        const root = testRoot(TestIntrinsic.testIntrinsicMethod)
        assertResultArray(TestIntrinsic.log,
            "testIntrinsicMethod call",
            "intrinsicMethod", "1",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(TestIntrinsic.log,
            "testIntrinsicMethod call",
            "intrinsicMethod", "1",
            "testIntrinsicMethod call",
            "intrinsicMethod", "1",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(TestIntrinsic.log,
            "testIntrinsicMethod call",
            "intrinsicMethod", "1",
            "testIntrinsicMethod call",
            "intrinsicMethod", "1",
            "testIntrinsicMethod call",
            "intrinsicMethod", "1",
        )
    })
    test("__key() function expanded by the plugin during compilation", () => {
        TestIntrinsic.log.length = 0
        const root = testRoot(TestIntrinsic.testKeyAccessor)
        assertResultArray(TestIntrinsic.log,
            "testKeyAccessor call",
            "intrinsicKeyAccessor",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(TestIntrinsic.log,
            "testKeyAccessor call",
            "intrinsicKeyAccessor",
            "testKeyAccessor call",
            "intrinsicKeyAccessor",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(TestIntrinsic.log,
            "testKeyAccessor call",
            "intrinsicKeyAccessor",
            "testKeyAccessor call",
            "intrinsicKeyAccessor",
            "testKeyAccessor call",
            "intrinsicKeyAccessor",
        )
    })
})

suite("Memo functions with all kinds of import and export statements", () => {
    test("Named import and qualified import with `*` of memo function", () => {
        SharedLog.log.length = 0
        const root = testRoot(TestImportedMemo.testImportedFunction)
        assertResultArray(SharedLog.log,
            "testImportedFunction call",
            "sharedMemoFunction", "sharedMemoFunction",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(SharedLog.log,
            "testImportedFunction call",
            "sharedMemoFunction", "sharedMemoFunction",
            "testImportedFunction call",
        )
        GlobalStateHolder.globalState.value++
        testTick(root)
        assertResultArray(SharedLog.log,
            "testImportedFunction call",
            "sharedMemoFunction", "sharedMemoFunction",
            "testImportedFunction call",
            "testImportedFunction call",
        )
    })
})

// suite("@memo_stable annotation", () => {
//     test("method returns string", () => {
//        const instance: TestMemoStable = new TestMemoStable()
//        const root = testRoot(instance.testFunctionReturnsString)
//        assertResultArray(instance.log,
//            "test call",
//            "function call"
//        )
//        GlobalStateHolder.globalState.value ++
//        testTick(root)
//        assertResultArray(instance.log,
//            "test call",
//            "function call",
//            "test call",
//        )
//    })
// })

export const __ARKTEST__ = "common/basic.test"
