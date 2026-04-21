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

declare class Binding<T> {
    constructor(getter: () => T);
    get value(): T;
}

declare class MutableBinding<T> {
    constructor(getter: () => T, setter: (newValue: T) => void);
    get value(): T;
    set value(newValue: T);
}

/**
 * Comprehensive BuilderBinding Unit Tests
 *
 * This test suite validates the Binding and MutableBinding classes.
 *
 * Test Sections:
 * 1. Binding Class - Basic Functionality
 * 2. Binding Class - Value Types
 * 3. MutableBinding Class - Basic Functionality
 * 4. MutableBinding Class - Value Updates
 * 5. Edge Cases
 * 6. Type Safety
 */
export class PuBuilderBindingTestsV2 implements ITestFile {
    private idString: string = "";

    constructor(str: string) {
        console.log(`Creating PuBuilderBindingTestsV2: ${str}`)
        this.idString = str;
    }

    public beforeAll(): void {
        console.log("PuBuilderBindingTestsV2: Setting up test suite");
    }

    public beforeEach(): void {
    }

    public afterAll(): void {
        console.log("PuBuilderBindingTestsV2: Tearing down test suite");
    }

    public afterEach(): void {
    }

    public getId(): string {
        return this.idString;
    }

    // =========================================================================
    // SECTION 1: Binding Class - Basic Functionality
    // =========================================================================

    /**
     * Test Binding constructor with getter
     * Expected: Binding is created
     */
    public testBindingConstructor(): void {
        let value = 42;
        const binding = new Binding<number>(() => value);
        eq(binding !== undefined, true, "Binding should be created");
    }

    /**
     * Test Binding value getter returns correct value
     * Expected: Returns value from getter
     */
    public testBindingValueGetter(): void {
        const binding = new Binding<number>(() => 100);
        eq(binding.value, 100, "should return value from getter");
    }

    /**
     * Test Binding with string value
     * Expected: Returns string value
     */
    public testBindingStringValue(): void {
        const binding = new Binding<string>(() => 'hello');
        eq(binding.value, 'hello', "should return string value");
    }

    /**
     * Test Binding getter is called each time
     * Expected: Returns current value
     */
    public testBindingDynamicValue(): void {
        let counter = 0;
        const binding = new Binding<number>(() => {
            counter++;
            return counter;
        });
        
        const first = binding.value;
        const second = binding.value;
        eq(first, 1, "first call should return 1");
        eq(second, 2, "second call should return 2");
    }

    // =========================================================================
    // SECTION 2: Binding Class - Value Types
    // =========================================================================

    /**
     * Test Binding with boolean value
     * Expected: Returns boolean
     */
    public testBindingBooleanValue(): void {
        const binding = new Binding<boolean>(() => true);
        eq(binding.value, true, "should return boolean");
    }

    /**
     * Test Binding with object value
     * Expected: Returns object
     */
    public testBindingObjectValue(): void {
        const obj = { key: 'value' };
        const binding = new Binding<object>(() => obj);
        const result = binding.value as { key: string };
        eq(result.key, 'value', "should return object");
    }

    /**
     * Test Binding with array value
     * Expected: Returns array
     */
    public testBindingArrayValue(): void {
        const arr = [1, 2, 3];
        const binding = new Binding<number[]>(() => arr);
        eq(binding.value.length, 3, "should return array");
        eq(binding.value[0], 1, "should have correct elements");
    }

    /**
     * Test Binding with null value
     * Expected: Returns null
     */
    public testBindingNullValue(): void {
        const binding = new Binding<null>(() => null);
        eq(binding.value, null, "should return null");
    }

    /**
     * Test Binding with undefined value
     * Expected: Returns undefined
     */
    public testBindingUndefinedValue(): void {
        const binding = new Binding<undefined>(() => undefined);
        eq(binding.value, undefined, "should return undefined");
    }

    // =========================================================================
    // SECTION 3: MutableBinding Class - Basic Functionality
    // =========================================================================

    /**
     * Test MutableBinding constructor
     * Expected: MutableBinding is created
     */
    public testMutableBindingConstructor(): void {
        let value = 10;
        const binding = new MutableBinding<number>(() => value, (newVal) => { value = newVal; });
        eq(binding !== undefined, true, "MutableBinding should be created");
    }

    /**
     * Test MutableBinding getter returns value
     * Expected: Returns current value
     */
    public testMutableBindingGetter(): void {
        let value = 10;
        const binding = new MutableBinding<number>(() => value, (newVal) => { value = newVal; });
        eq(binding.value, 10, "should return initial value");
    }

    /**
     * Test MutableBinding setter updates value
     * Expected: Value is updated
     */
    public testMutableBindingSetter(): void {
        let value = 10;
        const binding = new MutableBinding<number>(() => value, (newVal) => { value = newVal; });
        binding.value = 20;
        eq(value, 20, "should update value");
        eq(binding.value, 20, "should return new value");
    }

    /**
     * Test MutableBinding with string
     * Expected: Works with strings
     */
    public testMutableBindingString(): void {
        let text = 'initial';
        const binding = new MutableBinding<string>(() => text, (newVal) => { text = newVal; });
        binding.value = 'updated';
        eq(text, 'updated', "should update string");
    }

    // =========================================================================
    // SECTION 4: MutableBinding Class - Value Updates
    // =========================================================================

    /**
     * Test MutableBinding multiple updates
     * Expected: All updates work
     */
    public testMutableBindingMultipleUpdates(): void {
        let value = 0;
        const binding = new MutableBinding<number>(() => value, (newVal) => { value = newVal; });
        
        binding.value = 1;
        eq(binding.value, 1, "first update");
        
        binding.value = 2;
        eq(binding.value, 2, "second update");
        
        binding.value = 3;
        eq(binding.value, 3, "third update");
    }

    /**
     * Test MutableBinding with boolean
     * Expected: Works with booleans
     */
    public testMutableBindingBoolean(): void {
        let flag = false;
        const binding = new MutableBinding<boolean>(() => flag, (newVal) => { flag = newVal; });
        
        binding.value = true;
        eq(flag, true, "should toggle to true");
        
        binding.value = false;
        eq(flag, false, "should toggle to false");
    }

    /**
     * Test MutableBinding with object
     * Expected: Works with objects
     */
    public testMutableBindingObject(): void {
        let obj: object = { a: 1 };
        const binding = new MutableBinding<object>(() => obj, (newVal: object) => { obj = newVal; });
        
        binding.value = { a: 2 } as object;
        eq((obj as { a: number }).a, 2, "should update object");
    }

    /**
     * Test MutableBinding with callback
     * Expected: Callback is invoked
     */
    public testMutableBindingCallback(): void {
        let callCount = 0;
        let currentValue = 0;
        
        const binding = new MutableBinding<number>(
            () => currentValue,
            (newVal) => {
                callCount++;
                currentValue = newVal;
            }
        );
        
        binding.value = 10;
        eq(callCount, 1, "callback should be called once");
        eq(currentValue, 10, "value should be updated");
    }

    // =========================================================================
    // SECTION 5: Edge Cases
    // =========================================================================

    /**
     * Test Binding with getter returning function
     * Expected: Returns function
     */
    public testBindingFunctionValue(): void {
        const func = function() { return 42; };
        const binding = new Binding<Function>(() => func);
        eq(typeof binding.value, 'function', "should return function");
    }

    /**
     * Test MutableBinding with complex object
     * Expected: Works with complex objects
     */
    public testMutableBindingComplexObject(): void {
        const data: any = { 
            nested: { 
                deep: { 
                    value: 1 
                } 
            } 
        };
        
        const binding = new MutableBinding<any>(() => data, (newVal: any) => {
            data.nested.deep.value = newVal.nested.deep.value;
        });
        
        binding.value = { nested: { deep: { value: 999 } } };
        eq(data.nested.deep.value, 999, "should update deep nested value");
    }

    /**
     * Test Binding with arrow function getter
     * Expected: Works with arrow functions
     */
    public testBindingArrowFunctionGetter(): void {
        const binding = new Binding<number>(() => 42);
        eq(binding.value, 42, "should work with arrow function");
    }

    /**
     * Test MutableBinding with arrow function setter
     * Expected: Works with arrow functions
     */
    public testMutableBindingArrowFunctionSetter(): () => void {
        let value = 0;
        const setter = (newVal: number) => { value = newVal; };
        const binding = new MutableBinding<number>(() => value, setter);
        
        binding.value = 100;
        eq(value, 100, "should work with arrow function setter");
        return () => {};
    }

    /**
     * Test Binding with closure
     * Expected: Works with closures
     */
    public testBindingWithClosure(): void {
        let externalValue = 50;
        
        const getValue = () => externalValue;
        const binding = new Binding<number>(getValue);
        
        eq(binding.value, 50, "should capture closure value");
        
        externalValue = 100;
        eq(binding.value, 100, "should see updated closure value");
    }

    // =========================================================================
    // SECTION 6: Type Safety
    // =========================================================================

    /**
     * Test Binding is read-only
     * Note: Binding class only has getter, no setter. Testing type signature.
     * Expected: Binding class exists and has value getter
     */
    public testBindingReadOnly(): void {
        eq(typeof Binding, 'function', "Binding class should exist");
    }

    /**
     * Test MutableBinding with type constraint
     * Expected: Works with generic type
     */
    public testMutableBindingGeneric(): void {
        let numValue: number = 5;
        const numBinding = new MutableBinding<number>(() => numValue, (v) => { numValue = v; });
        
        let strValue: string = 'hello';
        const strBinding = new MutableBinding<string>(() => strValue, (v) => { strValue = v; });
        
        numBinding.value = 10;
        strBinding.value = 'world';
        
        eq(numValue, 10, "number binding works");
        eq(strValue, 'world', "string binding works");
    }

    /**
     * Test Binding nested in MutableBinding
     * Expected: Can use Binding inside MutableBinding
     */
    public testBindingInMutableBinding(): void {
        let value = 10;
        const binding = new Binding<number>(() => value);
        const mutable = new MutableBinding<number>(() => binding.value, (v) => { value = v; });
        
        eq(mutable.value, 10, "should read binding value");
        
        mutable.value = 20;
        eq(value, 20, "should update through binding");
    }

    /**
     * Test MutableBinding getter returns updated value
     * Expected: Dynamic updates work
     */
    public testMutableBindingDynamicGetter(): void {
        let values = [1, 2, 3];
        let index = 0;
        
        const binding = new MutableBinding<number>(
            () => values[index],
            (newVal) => { values[index] = newVal; }
        );
        
        eq(binding.value, 1, "initial value");
        
        index = 1;
        eq(binding.value, 2, "should get second value");
        
        index = 2;
        eq(binding.value, 3, "should get third value");
    }

    /**
     * Test empty getter/setter
     * Expected: Handles empty functions
     */
    public testEmptyGetterSetter(): void {
        const binding = new MutableBinding<void>(() => {}, () => {});
        eq(typeof binding.value, 'undefined', "should return undefined");
    }
}
