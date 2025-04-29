/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License,Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,software
 * distributed under the License is distributed on an "ASIS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 * @kit ArkUI
 */

/**
 * Enumerates the value TestCaseType.
 *
 * @enum {number}
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
declare enum TestCaseType {
  /**
   * FUNCTION.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  FUNCTION = 0,
  /**
   * PERFORMANCE.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  PERFORMANCE = 1,
  /**
   * POWER.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  POWER = 2,
  /**
   * RELIABILITY.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  RELIABILITY = 3,
  /**
   * SECURITY.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  SECURITY = 4,
  /**
   * GLOBAL.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  GLOBAL = 5,
  /**
   * COMPATIBILITY.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  COMPATIBILITY = 6,
  /**
   * USER.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  USER = 7,
  /**
   * STANDARD.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  STANDARD = 8,
  /**
   * SAFETY.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  SAFETY = 9,
  /**
   * RESILIENCE.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  RESILIENCE = 10
}

/**
 * Enumerates the value TestCaseSize.
 *
 * @enum {number}
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
declare enum TestCaseSize {
  /**
   * SMALLTEST.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  SMALLTEST = 0,
  /**
   * MEDIUMTEST.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  MEDIUMTEST = 1,
  /**
   * LARGETEST.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  LARGETEST = 2
}

/**
 * Enumerates the value TestCaseLevel.
 *
 * @enum {number}
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
declare enum TestCaseLevel {
  /**
   * LEVEL0.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  LEVEL0 = 0,
  /**
   * LEVEL1.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  LEVEL1 = 1,
  /**
   * LEVEL2.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  LEVEL2 = 2,
  /**
   * LEVEL3.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  LEVEL3 = 3,
  /**
   * LEVEL4.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  LEVEL4 = 4
}

/**
 * Represents the attribute of the test case.
 *
 * @typedef TestCaseAttribute
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
declare interface TestCaseAttribute {
  /**
   * test case type.
   *
   * @type {TestCaseType}
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  type?: TestCaseType;
  /**
   * test case size.
   *
   * @type {TestCaseSize}
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  size?: TestCaseSize;
  /**
   * test case level.
   *
   * @type {TestCaseLevel}
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  level: TestCaseLevel;
}

/**
 * Enumerates the string value match type.
 *
 * @enum {number}
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
declare enum MatchType {
  /**
   * Equals to a string.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  EQUALS = 0,
  /**
   * Contains a substring.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  CONTAINS = 1,
  /**
   * StartsWith a substring.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  STARTS_WITH = 2,
  /**
   * EndsWith a substring.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  ENDS_WITH = 3
}

/**
 * Represents the point on the device screen.
 *
 * @typedef Point
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
declare interface Point {
  /**
   * The x-coordinate of the coordinate point.
   *
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  readonly x: number;
  /**
   * The y-coordinate of the coordinate point.
   *
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  readonly y: number;
}

/**
 * Represents the rectangle area on the device screen.
 *
 * @typedef Rect
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
declare interface Rect {
  /**
   * The x-coordinate of the top left corner of the rectangle.
   *
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  readonly left: number;
  /**
   * The y-coordinate of the top left corner of the rectangle.
   *
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  readonly top: number;
  /**
   * The x-coordinate at the bottom right corner of the rectangle.
   *
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  readonly right: number;
  /**
   * The y-coordinate at the bottom right corner of the rectangle.
   *
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  readonly bottom: number;
}

/**
 * Enumerates the direction for the UI operation .
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
declare enum UiDirection {
  /**
   * Left.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  LEFT = 0,
  /**
   * Right.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  RIGHT = 1,
  /**
   * Up.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  UP = 2,
  /**
   * Down.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  DOWN = 3
}

/**
 * Describes the attribute requirements for the target Components.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
declare class Matcher {
  /**
   * Create an {@link Matcher} object.
   *
   * @returns { Matcher } the {@link Matcher} object.
   * @throws { BusinessError } 17000001 - if the test framework failed to initialize.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  static create(): Matcher;
  /**
   * Specifies the text for the target Component.
   *
   * @param { string } text - the text value.
   * @param { MatchType } [matchType] - the {@link MatchType} of the text value,Set it default {@link MatchType.EQUALS} if null or undefined.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  text(text: string, matchType?: MatchType): Matcher;
  /**
   * Specifies the id of the target Component.
   *
   * @param { string } id - the id value.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  id(id: string): Matcher;
  /**
   * Specifies the type of the target Component.
   *
   * @param { string } type - the type value.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  type(type: string): Matcher;
  /**
   * Specifies the clickable of the target Component.
   *
   * @param { boolean } b - the clickable status,default to true.Set it default if null or undefined.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  clickable(b?: boolean): Matcher;
  /**
   * Specifies the longPressable of the target Component.
   *
   * @param { boolean } b - the longPressable status,default to true.Set it default if null or undefined.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  longPressable(b?: boolean): Matcher;
  /**
   * Specifies the scrollable of the target Component.
   *
   * @param { boolean } b - the scrollable status,default to true.Set it default if null or undefined.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  scrollable(b?: boolean): Matcher;
  /**
   * Specifies the enabled of the target Component.
   *
   * @param { boolean } b - the enabled status,default to true.Set it default if null or undefined.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  enabled(b?: boolean): Matcher;
  /**
   * Specifies the focused of the target Component.
   *
   * @param { boolean } b - the focused status,default to true.Set it default if null or undefined.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  focused(b?: boolean): Matcher;
  /**
   * Specifies the selected of the target Component.
   *
   * @param { boolean } b - the selected status,default to true.Set it default if null or undefined.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  selected(b?: boolean): Matcher;
  /**
   * Specifies the checked of the target Component.
   *
   * @param { boolean } b - the checked status,default to false.Set it default if null or undefined.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  checked(b?: boolean): Matcher;
  /**
   * Specifies the checkable of the target Component.
   *
   * @param { boolean } b - the checkable status,default to false.Set it default if null or undefined.
   * @returns { Matcher } this {@link Matcher} object.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  checkable(b?: boolean): Matcher;
}

/**
 * Represents an Component of the ohos application,user can perform operations or query attributes on it.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 * @test
 */
declare class Component {
  /**
   * Tap this {@link Component}.
   *
   * @returns { Promise<void> }
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  tap(): Promise<void>;
  /**
   * Double tap this {@link Component}.
   *
   * @returns { Promise<void> }
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  doubleTap(): Promise<void>;
  /**
   * Press this {@link Component}.
   *
   * @returns { Promise<void> }
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  press(duration?: number): Promise<void>;
  /**
   * Pinch enlarge this {@link Component} to the target scale.
   *
   * @param { number } scale - the scale of the pinch enlarge this {@link Component}'s size.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  pinchOut(scale: number): Promise<void>;
  /**
   * Pinch shrink this {@link Component} to the target scale.
   *
   * @param { number } scale - the scale of the pinch shrink this {@link Component}'s size.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  pinchIn(scale: number): Promise<void>;
  /**
   * Inject text to this {@link Component}, applicable to TextInput.
   *
   * @param { string } text - the text to inject.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  inputText(text: string): Promise<void>;
  /**
   * Clear text to this {@link Component}, applicable to TextInput.
   *
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  clearText(): Promise<void>;
  /**
   * Scroll on this {@link Component} to the top,applicable to scrollable one.
   *
   * @param { number } [speed] - the speed of swipe(pixels per second),ranges from 200 to 40000.Set it default 600 if out of range or null or undefined.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  scrollToTop(speed?: number): Promise<void>;
  /**
   * Scroll on this {@link Component} to the bottom,applicable to scrollable one.
   *
   * @param { number } [speed] - the speed of swipe(pixels per second),ranges from 200 to 40000. Set it default 600 if out of range or null or undefined.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  scrollToBottom(speed?: number): Promise<void>;
  /**
   * Get the id attribute value.
   *
   * @returns { Promise<string> } the id value.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  getId(): Promise<string>;
  /**
   * Get the text attribute value.
   *
   * @returns { Promise<string> } the text value.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  getText(): Promise<string>;
  /**
   * Get the type attribute value.
   *
   * @returns { Promise<string> } the type value.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  getType(): Promise<string>;
  /**
   * Get the clickable status of this {@link Component}.
   *
   * @returns { Promise<boolean> } the clickable status.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  isClickable(): Promise<boolean>;
  /**
   * Get the long pressable status of this {@link Component}.
   *
   * @returns { Promise<boolean> } the long pressable status.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  isLongPressable(): Promise<boolean>;
  /**
   * Get the isScrollable status of this {@link Component}.
   *
   * @returns { Promise<boolean> } the isScrollable status.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  isScrollable(): Promise<boolean>;
  /**
   * Get the isEnabled status of this {@link Component}.
   *
   * @returns { Promise<boolean> } the isEnabled status.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  isEnabled(): Promise<boolean>;
  /**
   * Get the isFocused status of this {@link Component}.
   *
   * @returns { Promise<boolean> } the isFocused status.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  isFocused(): Promise<boolean>;
  /**
   * Get the isSelected status of this {@link Component}.
   *
   * @returns { Promise<boolean> } the isSelected status.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  isSelected(): Promise<boolean>;
  /**
   * Get the isChecked status of this {@link Component}.
   *
   * @returns { Promise<boolean> } the isChecked status.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  isChecked(): Promise<boolean>;
  /**
   * Get the isCheckable status of this {@link Component}.
   *
   * @returns { Promise<boolean> } the isCheckable status.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  isCheckable(): Promise<boolean>;
  /**
   * Get the inspector info of this {@link Component}.
   *
   * @returns { Promise<string> } the inspector info value.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  getInspectorInfo(): Promise<string>;
  /**
   * Get the inspector tree of this {@link Component}.
   *
   * @returns { Promise<string> } the inspector tree value.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  getInspectorTree(): Promise<string>;
  /**
   * Get the child count of this {@link Component}.
   *
   * @returns { Promise<string> } the child count value.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  getChildCount(): Promise<number>;
  /**
   * Get the bounds rect of this {@link Component}.
   *
   * @returns { Promise<Rect> } the bounds rect object.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000004 - if the component is invisible or destroyed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  getBounds(): Promise<Rect>;
}

/**
 * The unified facade of UiTest framework,can be used to find {@link Component},trigger keyEvents,perform
 * coordinates-based UI actions,capture screen and so on.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 * @test
 */
declare class Tester {
  /**
   * Create an {@link Tester} object.
   *
   * @returns { Tester } the {@link Tester} object.
   * @throws { BusinessError } 17000001 - if the test framework failed to initialize.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  static create(): Tester;
  /**
   * Delay with specified duration.
   *
   * @param { number } duration - the delay duration in milliseconds.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  pump(delayMs?: number): Promise<void>;
  /**
   * Find the first matched {@link Component} on current UI.
   *
   * @param { Matcher } pattern The attribute requirements of the target {@link Component}.
   * @returns { Promise<Component> } the first matched {@link Component} or undefined.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  findComponent(pattern: Matcher): Promise<Component>;
  /**
   * Find all the matched {@link Component}s on current UI.
   *
   * @param { Matcher } pattern The attribute requirements of the target {@link Component}.
   * @returns { Promise<Array<Component>> } the matched {@link Component}s list.
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  findComponents(pattern: Matcher): Promise<Array<Component>>;
  /**
   * Assert t the matched {@link Component}s exists on current UI;if not,assertError will be raised.
   *
   * @param { Matcher } pattern The attribute requirements of the target {@link Component}.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @throws { BusinessError } 17000003 - if the assertion failed.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  assertComponentExist(pattern: Matcher): Promise<void>;
  /**
   * TODO
   *
   * @param pattern
   */
  scrollUntilExist(pattern: Matcher): Promise<Component>;
  /**
   * Press the specified key.
   *
   * @param { number } keyCode - the target keyCode.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  triggerkey(keyCode: number): Promise<void>;
  /**
   * Press two or three key combinations
   *
   * @param { Array<number> } [keys] - the target keyCodes.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  triggerCombineKeys(keys: Array<number>): Promise<void>;
  /**
   * Tap on the specified location on the screen.
   *
   * @param { number } x The x-coordinate.
   * @param { number } y The y-coordinate.
   * @returns { Promise<void> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 11
   */
  tap(x: number, y: number): Promise<void>;
  /**
   * DoubleTap on the specified location on the screen.
   *
   * @param { number } x The x-coordinate.
   * @param { number } y The y-coordinate.
   * @returns { Promise<void> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 11
   */
  doubleTap(x: number, y: number): Promise<void>;
  /**
   * Press on the specified location on the screen.
   *
   * @param { number } x The x-coordinate.
   * @param { number } y The y-coordinate.
   * @param { number } duration The press duration.
   * @returns { Promise<void> }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 11
   */
  press(x: number, y: number, duration?: number): Promise<void>;
  /**
   * TODO
   *
   * @param deltax
   * @param deltaY
   */
  scroll(deltax: number, deltaY: number): Promise<void>;
  /**
   * Drag on the screen between the specified points.
   *
   * @param { number } startx - the x-coordinate of the starting point.
   * @param { number } starty - the y-coordinate of the starting point.
   * @param { number } endx - the x-coordinate of the ending point.
   * @param { number } endy - the y-coordinate of the ending point.
   * @param { number } [speed] the speed of drag(pixels per second),ranges from 200 to 40000. Set it default 600 if out of range or null or undefined.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  drag(startx: number, starty: number, endx: number, endy: number, speed?: number): Promise<void>;
  /**
   * Inject fling on the device display.
   *
   * @param { Point } from - the coordinate point where the finger touches the screen.
   * @param { Point } to - the coordinate point where the finger leaves the screen.
   * @param { number } stepLen - the length of each step, in pixels.
   * @param { number } [speed] - the speed of fling(pixels per second),ranges from 200 to 40000. Set it default 600 if out of range or null or undefined.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  fling(from: Point, to: Point, steplen: number, speed: number): Promise<void>;
  /**
   * Inject fling on the device display.
   *
   * @param { UiDirection } direction - the direction of this action.
   * @param { number } speed - the speed of fling (pixels per second),default is 600,the value ranges from 200 to 40000,set it 600 if out of range.
   * @returns { Promise<void> }
   * @throws { BusinessError } 401 - if the input parameters are invalid.
   * @throws { BusinessError } 17000002 - if the async function was not called with await.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  fling(direction: UiDirection, speed: number): Promise<void>;
}

type allExpectType = Object | undefined | null;
type allActualType = Object | undefined | null;

// global functions
declare function loadComponentTestEntry(entry: () => void): void;

declare function defineTest(testName: string, attr: TestCaseAttribute, testBody: () => void, delayMs?: number): void;
declare function assertContain(expectValue: allExpectType, actualValue: allActualType): void;
declare function assertEqual(expectValue: allExpectType, actualValue: allActualType): void;
declare function assertFalse(actualValue: allExpectType): void;
declare function assertTrue(actualValue: allExpectType): void;

export {
  TestCaseType,
  TestCaseSize,
  TestCaseLevel,
  TestCaseAttribute,
  MatchType,
  Point,
  Rect,
  UiDirection,
  Matcher,
  Component,
  Tester,
  loadComponentTestEntry,
  defineTest,
  assertContain,
  assertEqual,
  assertFalse,
  assertTrue
};
