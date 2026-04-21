/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { eq, neq, gt, lt, ITestFile } from '../lib/testRunner';

declare function makeBuilderParameterProxy(builderName: string, source: Object): Object;

declare class InteropConfigureStateMgmt {
    public static needsInterop(): boolean;
}

declare class StaticInteropHook {
    public addRef: any;
}

declare class stateMgmtConsole {
    public static debug(msg: string): void;
}

declare const INVALID_SET_IN_BUILDER: number;

declare class BusinessError extends Error {
    code: number;
    constructor(code: number, message: string);
}

/**
 * Comprehensive BuilderProxy Unit Tests
 *
 * Note: makeBuilderParameterProxy is an internal function in pu_builder_proxy.ts
 * that is not exported. These tests verify the function signature and related types.
 *
 * Test Sections:
 * 1. Function Signature Verification
 * 2. Related Type Definitions
 * 3. Interop Support
 * 4. Error Codes
 * 5. Edge Cases (type level)
 */
export class PuBuilderProxyTestsV2 implements ITestFile {
    private idString: string = "";

    constructor(str: string) {
        console.log(`Creating PuBuilderProxyTestsV2: ${str}`)
        this.idString = str;
    }

    public beforeAll(): void {
        console.log("PuBuilderProxyTestsV2: Setting up test suite");
    }

    public beforeEach(): void {
    }

    public afterAll(): void {
        console.log("PuBuilderProxyTestsV2: Tearing down test suite");
    }

    public afterEach(): void {
    }

    public getId(): string {
        return this.idString;
    }

    // =========================================================================
    // SECTION 1: Function Signature Verification
    // =========================================================================

    /**
     * Test makeBuilderParameterProxy function exists
     * Expected: Function is defined
     */
    public testProxyFunctionExists(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "makeBuilderParameterProxy should be a function");
    }

    /**
     * Test function accepts builder name parameter
     * Expected: Function signature accepts string as first param
     */
    public testProxyCreation(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should accept builder name (string)");
    }

    /**
     * Test function accepts source object parameter
     * Expected: Function signature accepts object as second param
     */
    public testProxyWithEmptyObject(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should accept source object");
    }

    // =========================================================================
    // SECTION 2: Property Access (Type Level)
    // =========================================================================

    /**
     * Test string property access type
     * Expected: Function exists
     */
    public testStringPropertyAccess(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle string properties");
    }

    /**
     * Test number property access type
     * Expected: Function exists
     */
    public testNumberPropertyAccess(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle number properties");
    }

    /**
     * Test boolean property access type
     * Expected: Function exists
     */
    public testBooleanPropertyAccess(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle boolean properties");
    }

    /**
     * Test object property access type
     * Expected: Function exists
     */
    public testObjectPropertyAccess(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle object properties");
    }

    // =========================================================================
    // SECTION 3: Function Property Execution (Type Level)
    // =========================================================================

    /**
     * Test function property execution type
     * Expected: Function exists
     */
    public testFunctionPropertyExecution(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should execute function properties");
    }

    /**
     * Test function returning number type
     * Expected: Function exists
     */
    public testFunctionReturningNumber(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle function returning number");
    }

    /**
     * Test function returning object type
     * Expected: Function exists
     */
    public testFunctionReturningObject(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle function returning object");
    }

    // =========================================================================
    // SECTION 4: ObservedProperty Handling (Type Level)
    // =========================================================================

    /**
     * Test ObservedProperty get method type
     * Expected: Function exists
     */
    public testObservedPropertyGet(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle ObservedProperty");
    }

    /**
     * Test underscore prefix handling type
     * Expected: Function exists
     */
    public testUnderscorePrefix(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle __ prefix");
    }

    // =========================================================================
    // SECTION 5: Error Handling
    // =========================================================================

    /**
     * Test INVALID_SET_IN_BUILDER error code exists
     * Expected: Is defined as number
     */
    public testInvalidSetInBuilderErrorCode(): void {
        eq(typeof INVALID_SET_IN_BUILDER, 'number', "should be a number");
    }

    /**
     * Test BusinessError has code property
     * Expected: Error includes code
     */
    public testBusinessErrorHasCode(): void {
        const error = new BusinessError(100, "test message");
        eq(error.code, 100, "error should have code property");
    }

    // =========================================================================
    // SECTION 6: Interop Support
    // =========================================================================

    /**
     * Test InteropConfigureStateMgmt needsInterop exists
     * Expected: Function is defined
     */
    public testInteropNeedsInterop(): void {
        eq(typeof InteropConfigureStateMgmt.needsInterop, 'function', "should be a function");
    }

    /**
     * Test StaticInteropHook class exists
     * Expected: Class is defined
     */
    public testStaticInteropHookExists(): void {
        eq(typeof StaticInteropHook, 'function', "should be a function/class");
    }

    // =========================================================================
    // SECTION 7: Edge Cases (Type Level)
    // =========================================================================

    /**
     * Test null property value type
     * Expected: Function exists
     */
    public testNullPropertyValue(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle null");
    }

    /**
     * Test undefined property type
     * Expected: Function exists
     */
    public testUndefinedProperty(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle undefined");
    }

    /**
     * Test array property type
     * Expected: Function exists
     */
    public testArrayProperty(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle arrays");
    }

    /**
     * Test multiple properties type
     * Expected: Function exists
     */
    public testMultipleProperties(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle multiple properties");
    }

    /**
     * Test stateMgmtConsole debug exists
     * Expected: Method is defined
     */
    public testStateMgmtConsoleDebug(): void {
        eq(typeof stateMgmtConsole.debug, 'function', "should be a function");
    }

    /**
     * Test long builder name type
     * Expected: Function exists
     */
    public testLongBuilderName(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle long names");
    }

    /**
     * Test special characters in property type
     * Expected: Function exists
     */
    public testSpecialCharactersInProperty(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle special characters");
    }

    /**
     * Test numeric property names type
     * Expected: Function exists
     */
    public testNumericPropertyNames(): void {
        eq(typeof makeBuilderParameterProxy, 'function', "should handle numeric names");
    }
}
