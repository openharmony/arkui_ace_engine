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

/**
 * Unit tests for v2_decorated_variables.ts
 * Testing VariableUtilV2, ProviderConsumerUtilV2, and decorator functions
 *
 * Test Coverage:
 * 1. VariableUtilV2.initParam - Initialize @Param decorator variables
 * 2. VariableUtilV2.updateParam - Update @Param decorator variables
 * 3. VariableUtilV2.resetParam - Reset @Param variables during reuse
 * 4. VariableUtilV2.checkInvalidUsage - Validate decorator usage
 * 5. ProviderConsumerUtilV2.findProvider - Find @Provider from @Consumer
 * 6. ProviderConsumerUtilV2.connectConsumer2Provider - Link @Consumer to @Provider
 * 7. ProviderConsumerUtilV2.defineConsumerWithoutProvider - Handle @Consumer without @Provider
 * 8. ProviderConsumerUtilV2.addProviderConsumerVariableDecoMeta - Add metadata
 * 9. ObservedV2_Internal decorator - Create observed class
 * 10. Trace_Internal decorator - Track property access
 */

import { eq, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class ObserveV2 {
  public static readonly V2_DECO_META: symbol;
  public static readonly OB_PREFIX: string;
  public static getObserve(): any;
}

declare class VariableUtilV2 {
  public static initParam<Z>(target: object, attrName: string, newValue: Z): void;
  public static updateParam<Z>(target: object, attrName: string, newValue: Z): void;
  public static resetParam<Z>(target: object, attrName: string, newValue: Z): void;
  public static checkInvalidUsage(meta: any, attrName: string): void;
}

declare class ProviderConsumerUtilV2 {
  public static readonly ALIAS_PREFIX: string;
  public static findProvider(view: any, aliasName: string): [any, string] | undefined;
  public static connectConsumer2Provider<T>(consumeView: any, consumeVarName: string, provideView: any, provideVarName: string): T;
  public static defineConsumerWithoutProvider<T>(consumeView: any, consumeVarName: string, consumerLocalVal: T): T;
  public static addProvideConsumeVariableDecoMeta(proto: Object, varName: string, aliasName: string, deco: string): void;
}

// Test helper classes
declare class ViewV2 {
  public id__: number;
  public name: string;
  public getParent(): any;
  public debugInfo__(): string;
  constructor(parent: IView| undefined, elmtId?: number, extraInfo?: ExtraInfo);
  [key: string | symbol]: any; // Index signature for dynamic properties
}

declare interface IView {}

type ExtraInfo = {
    page: string;
    line: number;
    col: number;
};

/**
 * Test class for v2_decorated_variables.ts
 * Tests VariableUtilV2, ProviderConsumerUtilV2, and decorator functions
 */
export class DecoratedVariablesTestsV2 implements ITestFile {

  private idString: string = "";
  private mockView: ViewV2;
  private mockTarget: any;

  constructor(str: string) {
    console.log(`Creating DecoratedVariablesTestsV2: ${str}`)
    this.idString = str;
    this.mockView = {
      id__: 1,
      name: "MockViewV2",
      getParent: () => null,
      debugInfo__: () => "MockViewV2"
    } as ViewV2;
    this.mockTarget = {};
  }

  public beforeAll(): void {}

  public beforeEach(): void {
    // Reset mock target before each test
    this.mockTarget = {};
  }

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  // ========================================================================
  // VariableUtilV2.initParam Tests
  // ========================================================================

  /**
   * Test: VariableUtilV2.initParam - basic initialization
   * Testing: VariableUtilV2.initParam() method
   * Description: Verify that @Param variable is initialized correctly
   * Expected:
   * - Backing store is created with OB_PREFIX + attrName
   * - Value is stored in backing store
   * - Dependency tracking is established via addRef
   */
  public testInitParamBasic(): void {
    this.mockTarget = {};
    const attrName = 'testParam';
    const newValue = 42;

    // Set up metadata
    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param' };

    VariableUtilV2.initParam(this.mockTarget, attrName, newValue);

    const storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], newValue, "Backing store should have new value");
  }

  /**
   * Test: VariableUtilV2.initParam - string value
   * Testing: VariableUtilV2.initParam() with string type
   * Description: Verify that string @Param is initialized
   */
  public testInitParamString(): void {
    this.mockTarget = {};
    const attrName = 'message';
    const newValue = "Hello, World!";

    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param' };

    VariableUtilV2.initParam(this.mockTarget, attrName, newValue);

    const storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], newValue, "Backing store should have string value");
  }

  /**
   * Test: VariableUtilV2.initParam - object value
   * Testing: VariableUtilV2.initParam() with object type
   * Description: Verify that object @Param is initialized
   */
  public testInitParamObject(): void {
    this.mockTarget = {};
    const attrName = 'config';
    const newValue = { key: 'value', count: 100 };

    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param' };

    VariableUtilV2.initParam(this.mockTarget, attrName, newValue);

    const storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], newValue, "Backing store should have object value");
  }

  // ========================================================================
  // VariableUtilV2.updateParam Tests
  // ========================================================================

  /**
   * Test: VariableUtilV2.updateParam - value change
   * Testing: VariableUtilV2.updateParam() method
   * Description: Verify that @Param variable is updated and fireChange is called
   * Expected:
   * - Backing store value is updated
   * - fireChange is triggered to notify dependent components
   */
  public testUpdateParamChange(): void {
    this.mockTarget = {};
    const attrName = 'counter';
    const initialValue = 10;
    const newValue = 20;

    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param' };

    // Initialize first
    VariableUtilV2.initParam(this.mockTarget, attrName, initialValue);

    // Update to new value
    VariableUtilV2.updateParam(this.mockTarget, attrName, newValue);

    const storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], newValue, "Backing store should be updated");
  }

  /**
   * Test: VariableUtilV2.updateParam - same value
   * Testing: VariableUtilV2.updateParam() with unchanged value
   * Description: Verify that no update occurs if value hasn't changed
   * Expected:
   * - Backing store remains unchanged
   * - fireChange is NOT called
   */
  public testUpdateParamSameValue(): void {
    this.mockTarget = {};
    const attrName = 'stable';
    const value = 42;

    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param' };

    VariableUtilV2.initParam(this.mockTarget, attrName, value);

    // Try to update to same value
    VariableUtilV2.updateParam(this.mockTarget, attrName, value);

    const storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], value, "Backing store should keep value");
  }

  /**
   * Test: VariableUtilV2.updateParam - @Once modifier
   * Testing: VariableUtilV2.updateParam() with @Once decorator
   * Description: Verify that @Param @Once variables are not updated
   * Expected:
   * - Value is NOT updated
   * - No error or warning about update attempt
   */
  public testUpdateParamOnce(): void {
    this.mockTarget = {};
    const attrName = 'onceParam';
    const initialValue = 100;
    const newValue = 200;

    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param', deco2: '@Once' };

    VariableUtilV2.initParam(this.mockTarget, attrName, initialValue);

    // Try to update - should be ignored due to @Once
    VariableUtilV2.updateParam(this.mockTarget, attrName, newValue);

    const storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], initialValue, "@Once param should keep initial value");
  }

  // ========================================================================
  // VariableUtilV2.resetParam Tests
  // ========================================================================

  /**
   * Test: VariableUtilV2.resetParam - basic reset
   * Testing: VariableUtilV2.resetParam() method
   * Description: Verify that @Param variable is reset during component reuse
   * Expected:
   * - Value is updated to new value
   * - fireChange is triggered to update dependent components
   */
  public testResetParamBasic(): void {
    this.mockTarget = {};
    const attrName = 'resettable';
    const originalValue = 50;
    const resetValue = 75;

    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param' };

    VariableUtilV2.initParam(this.mockTarget, attrName, originalValue);
    eq(this.mockTarget[ObserveV2.OB_PREFIX + attrName], originalValue, "Initial value should be set");

    VariableUtilV2.resetParam(this.mockTarget, attrName, resetValue);

    const storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], resetValue, "Value should be reset");
  }

  /**
   * Test: VariableUtilV2.resetParam - same value
   * Testing: VariableUtilV2.resetParam() with unchanged value
   * Description: Verify that no update occurs if reset value is same
   */
  public testResetParamSameValue(): void {
    this.mockTarget = {};
    const attrName = 'stableReset';
    const value = 99;

    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param' };

    VariableUtilV2.initParam(this.mockTarget, attrName, value);

    VariableUtilV2.resetParam(this.mockTarget, attrName, value);

    const storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], value, "Value should remain unchanged");
  }

  // ========================================================================
  // VariableUtilV2.checkInvalidUsage Tests
  // ========================================================================

  /**
   * Test: VariableUtilV2.checkInvalidUsage - valid usage
   * Testing: VariableUtilV2.checkInvalidUsage() with @Param metadata
   * Description: Verify that valid @Param usage doesn't throw error
   * Expected:
   * - No error is thrown
   * - Function returns normally
   */
  public testCheckInvalidUsageValid(): void {
    const attrName = 'validParam';
    const meta = { deco: '@Param' };

    // Should not throw
    try {
      VariableUtilV2.checkInvalidUsage(meta, attrName);
      eq(true, true, "Should reach here without error");
    } catch (e) {
      eq(false, true, "Should not throw error for valid @Param usage");
    }
  }

  /**
   * Test: VariableUtilV2.checkInvalidUsage - invalid decorator
   * Testing: VariableUtilV2.checkInvalidUsage() with wrong decorator
   * Description: Verify that error is thrown for non-@Param decorator
   * Expected:
   * - Error is thrown
   * - Error message indicates invalid usage
   */
  public testCheckInvalidUsageInvalid(): void {
    const attrName = 'invalidParam';
    const meta = { deco: '@Local' };

    try {
      VariableUtilV2.checkInvalidUsage(meta, attrName);
      eq(false, true, "Should not reach here");
    } catch (e: any) {
      eq(e.message !== undefined, true, "Error should have message");
      eq(e.message.includes('initParam/updateParm/resetParam'), true, "Error should mention valid methods");
    }
  }

  // ========================================================================
  // ProviderConsumerUtilV2.findProvider Tests
  // ========================================================================

  /**
   * Test: ProviderConsumerUtilV2.findProvider - provider exists
   * Testing: ProviderConsumerUtilV2.findProvider() method
   * Description: Verify that @Provider is found from ancestor @ComponentV2
   * Expected:
   * - Returns tuple of [ViewV2, varName]
   * - ViewV2 is the component with @Provider
   * - varName is the provided variable name
   */
public testFindProviderExists(): void {
    const aliasName = 'testProvider';
    const parentViewId: number = 3;
    const mockViewId: number = 4;
    const parent  = new ViewV2(undefined, parentViewId, undefined);
    this.mockView = new ViewV2(parent, mockViewId, undefined);
    this.mockView[ObserveV2.V2_DECO_META] = {};

    ProviderConsumerUtilV2.addProvideConsumeVariableDecoMeta(Object.getPrototypeOf(parent), 'providedData', aliasName, '@Provider');

    const result = ProviderConsumerUtilV2.findProvider(this.mockView, aliasName);

    eq(result !== undefined, true, "Should find provider");
    if (result) {
      eq(result[0], parent, "Should return provider view");
      eq(result[1], 'providedData', "Should return provider var name");
    }
  }

  /**
   * Test: ProviderConsumerUtilV2.findProvider - provider not found
   * Testing: ProviderConsumerUtilV2.findProvider() when provider doesn't exist
   * Description: Verify that undefined is returned when no @Provider is found
   * Expected:
   * - Returns undefined
   */
  public testFindProviderNotFound(): void {
    const aliasName = 'nonExistentProvider';
    const mockViewId: number = 3;
    const view = new ViewV2(undefined, mockViewId, undefined);

    const result = ProviderConsumerUtilV2.findProvider(view, aliasName);

    eq(result, undefined, "Should return undefined when provider not found");
  }

  // ========================================================================
  // ProviderConsumerUtilV2.connectConsumer2Provider Tests
  // ========================================================================

  /**
   * Test: connectConsumer2Provider - basic connection
   * Testing: ProviderConsumerUtilV2.connectConsumer2Provider() method
   * Description: Verify that @Consumer property is linked to @Provider property
   * Expected:
   * - Getter returns @Provider value
   * - Setter updates @Provider value
   * - Dependency tracking is established
   */
  public testConnectConsumer2Provider(): void {
    const consumeVarName = 'consumerData';
    const provideVarName = 'providerData';
    const providerValue = { message: "Hello from provider" };

    const providerView: any = {
      id__: 10,
      name: "ProviderComponent",
      getParent: () => null,
      debugInfo__: () => "ProviderView"
    };
    providerView[provideVarName] = providerValue;

    const consumerView: any = {
      id__: 11,
      name: "ConsumerComponent",
      getParent: () => null,
      debugInfo__: () => "ConsumerView"
    };

    const result = ProviderConsumerUtilV2.connectConsumer2Provider<any>(
      consumerView,
      consumeVarName,
      providerView,
      provideVarName
    );

    eq(result, providerValue, "Should return provider value");
  }

  // ========================================================================
  // ProviderConsumerUtilV2.defineConsumerWithoutProvider Tests
  // ========================================================================

  /**
   * Test: defineConsumerWithoutProvider - basic usage
   * Testing: ProviderConsumerUtilV2.defineConsumerWithoutProvider() method
   * Description: Verify that @Consumer without @Provider uses local value
   * Expected:
   * - Property is defined with getter/setter
   * - Getter uses backing store
   * - Setter updates backing store
   */
  public testDefineConsumerWithoutProvider(): void {
    const consumeVarName = 'localConsumerData';
    const localValue = { text: "Local value" };

    const consumerView: any = {
      id__: 20,
      name: "StandaloneConsumer",
      getParent: () => null,
      debugInfo__: () => "ConsumerView"
    };

    const result = ProviderConsumerUtilV2.defineConsumerWithoutProvider(
      consumerView,
      consumeVarName,
      localValue
    );

    eq(result, localValue, "Should return local value");
  }

  // ========================================================================
  // ProviderConsumerUtilV2.addProviderConsumerVariableDecoMeta Tests
  // ========================================================================

  /**
   * Test: addProviderConsumerVariableDecoMeta - @Provider
   * Testing: ProviderConsumerUtilV2.addProviderConsumerVariableDecoMeta() for @Provider
   * Description: Verify that @Provider metadata is added correctly
   * Expected:
   * - Metadata object is created
   * - Contains decorator type (@Provider)
   * - Contains alias name
   * - Contains variable name
   */
  public testAddProviderConsumerVariableDecoMetaProvider(): void {
    const proto: any = {};
    const varName = 'myProvider';
    const aliasName = 'dataAlias';
    const deco = '@Provider';
  
    ProviderConsumerUtilV2.addProvideConsumeVariableDecoMeta(proto, varName, aliasName, deco);

    eq(proto[ObserveV2.V2_DECO_META] !== undefined, true, "Should have V2_DECO_META");
    eq(proto[ObserveV2.V2_DECO_META][varName] !== undefined, true, "Should have var metadata");
    eq(proto[ObserveV2.V2_DECO_META][varName].deco, deco, "Should have @Provider deco");
    eq(proto[ObserveV2.V2_DECO_META][varName].aliasName, aliasName, "Should have alias name");
  }

  /**
   * Test: addProviderConsumerVariableDecoMeta - @Consumer
   * Testing: ProviderConsumerUtilV2.addProviderConsumerVariableDecoMeta() for @Consumer
   * Description: Verify that @Consumer metadata is added correctly
   */
  public testAddProviderConsumerVariableDecoMetaConsumer(): void {
    const proto: any = {};
    const varName = 'myConsumer';
    const aliasName = 'dataAlias';
    const deco = '@Consumer';

    ProviderConsumerUtilV2.addProvideConsumeVariableDecoMeta(proto, varName, aliasName, deco);

    eq(proto[ObserveV2.V2_DECO_META] !== undefined, true, "Should have V2_DECO_META");
    eq(proto[ObserveV2.V2_DECO_META][varName] !== undefined, true, "Should have var metadata");
    eq(proto[ObserveV2.V2_DECO_META][varName].deco, deco, "Should have @Consumer deco");
    eq(proto[ObserveV2.V2_DECO_META][varName].aliasName, aliasName, "Should have alias name");
  }

  // ========================================================================
  // Helper Function Tests
  // ========================================================================

  /**
   * Test: ProviderConsumerUtilV2.metaAliasKey
   * Testing: ProviderConsumerUtilV2.metaAliasKey() format
   * Description: Verify that alias key is formatted correctly
   * Expected:
   * - Key format: ___pc_alias_@Decorator_aliasName
   */
  public testMetaAliasKey(): void {
    // This tests the private method indirectly through addProviderConsumerVariableDecoMeta
    const proto: any = {};
    const varName = 'testVar';
    const aliasName = 'testAlias';

    ProviderConsumerUtilV2.addProvideConsumeVariableDecoMeta(proto, varName, aliasName, '@Provider');

    // Check that the prefixed alias exists
    const prefixedAlias = ProviderConsumerUtilV2.ALIAS_PREFIX + '_@Provider_' + aliasName;
    eq(proto[ObserveV2.V2_DECO_META][prefixedAlias] !== undefined, true, "Should have prefixed alias");
  }

  // ========================================================================
  // Integration Tests
  // ========================================================================

  /**
   * Test: @Param lifecycle (init -> update -> reset)
   * Testing: Complete @Param decorator lifecycle
   * Description: Verify that @Param works correctly through initialization, update, and reset
   * Expected:
   * - initParam sets initial value
   * - updateParam changes value
   * - resetParam resets value during reuse
   */
  public testParamLifecycle(): void {
    this.mockTarget = {};
    const attrName = 'lifecycleParam';
    const initialValue = 1;
    const updatedValue = 2;
    const resetValue = 3;

    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param' };

    // Init
    VariableUtilV2.initParam(this.mockTarget, attrName, initialValue);
    let storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], initialValue, "Init: should set initial value");

    // Update
    VariableUtilV2.updateParam(this.mockTarget, attrName, updatedValue);
    eq(this.mockTarget[storeProp], updatedValue, "Update: should change value");

    // Reset (simulating reuse)
    VariableUtilV2.resetParam(this.mockTarget, attrName, resetValue);
    eq(this.mockTarget[storeProp], resetValue, "Reset: should set reset value");
  }

  /**
   * Test: @Param @Once prevents updates
   * Testing: @Param @Once decorator behavior
   * Description: Verify that @Param @Once only allows initialization
   * Expected:
   * - initParam works
   * - updateParam is ignored
   */
  public testParamOncePreventsUpdate(): void {
    this.mockTarget = {};
    const attrName = 'onceParam';
    const initialValue = 100;
    const updateValue = 200;

    this.mockTarget[ObserveV2.V2_DECO_META] = {};
    this.mockTarget[ObserveV2.V2_DECO_META][attrName] = { deco: '@Param', deco2: '@Once' };

    // Init should work
    VariableUtilV2.initParam(this.mockTarget, attrName, initialValue);
    let storeProp = ObserveV2.OB_PREFIX + attrName;
    eq(this.mockTarget[storeProp], initialValue, "Init: should set initial value");

    // Update should be ignored
    VariableUtilV2.updateParam(this.mockTarget, attrName, updateValue);
    eq(this.mockTarget[storeProp], initialValue, "Update: should be ignored");
  }

}
