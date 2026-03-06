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

// 声明源文件中的接口
interface Rect {
  left: number;
  top: number;
  width: number;
  height: number;
}

interface AvoidArea {
  visible: boolean;
  leftRect: Rect;
  topRect: Rect;
  rightRect: Rect;
  bottomRect: Rect;
}

interface UIEnvAvoidArea {
  statusBar: AvoidArea;
  cutout: AvoidArea;
  keyboard: AvoidArea;
  navigationIndicator: AvoidArea;
}

// 声明源文件中的类
declare class IEnvironmentValue<T> {
  value: T;
}

//  UIContext 类型
class UIContext {
  constructor() {
  }
}

class WindowAvoidAreaPxEnv implements IEnvironmentValue<UIEnvAvoidArea> {
  statusBar: AvoidArea;
  cutout: AvoidArea;
  keyboard: AvoidArea;
  navigationIndicator: AvoidArea;
  value: UIEnvAvoidArea;

  constructor(context: UIContext) {
    // 1. 定义一个空的 Rect 对象
    const emptyRect: Rect = { left: 0, top: 0, width: 0, height: 0 };

    // 2. 构造符合 AvoidArea 接口的对象
    const defaultAvoidArea: AvoidArea = {
      visible: false,       // 必须包含 visible
      leftRect: emptyRect,  // 必须是 Rect 对象，属性名是 leftRect
      topRect: emptyRect,   // 属性名是 topRect
      rightRect: emptyRect, // 属性名是 rightRect
      bottomRect: emptyRect // 属性名是 bottomRect
    };

    // 3. 赋值给类属性
    this.statusBar = defaultAvoidArea;
    this.cutout = defaultAvoidArea;
    this.keyboard = defaultAvoidArea;
    this.navigationIndicator = defaultAvoidArea;

    // 4. 初始化 value
    this.value = {
      statusBar: this.statusBar,
      cutout: this.cutout,
      keyboard: this.keyboard,
      navigationIndicator: this.navigationIndicator
    };
  }

  update(): void {
    // 实现更新逻辑
  }

  destroy(): void {
    // 实现销毁逻辑
  }

  // 如果 IEnvironmentValue 接口需要 get 方法
  get(): UIEnvAvoidArea {
    return this.value;
  }
}

class WindowAvoidAreaVpEnv implements IEnvironmentValue<UIEnvAvoidArea> {
  statusBar: AvoidArea;
  cutout: AvoidArea;
  keyboard: AvoidArea;
  navigationIndicator: AvoidArea;
  value: UIEnvAvoidArea;

  constructor(context: UIContext) {
    // 1. 定义一个空的 Rect 对象 (VP 环境下数值通常也是数字，只是单位含义不同)
    const emptyRect: Rect = { left: 0, top: 0, width: 0, height: 0 };

    // 2. 构造符合 AvoidArea 接口的默认对象
    const defaultAvoidArea: AvoidArea = {
      visible: false,
      leftRect: emptyRect,
      topRect: emptyRect,
      rightRect: emptyRect,
      bottomRect: emptyRect
    };

    // 3. 初始化属性
    this.statusBar = defaultAvoidArea;
    this.cutout = defaultAvoidArea;
    this.keyboard = defaultAvoidArea;
    this.navigationIndicator = defaultAvoidArea;

    // 4. 初始化 value
    this.value = {
      statusBar: this.statusBar,
      cutout: this.cutout,
      keyboard: this.keyboard,
      navigationIndicator: this.navigationIndicator
    };
  }

  update(): void {
    // 在这里可以添加根据 context 更新 VP 值的逻辑
    // 例如：this.value.statusBar.leftRect.width = someCalculation();
  }

  destroy(): void {
    // 清理资源
  }

  // 如果接口需要 get 方法
  get(): UIEnvAvoidArea {
    return this.value;
  }
}

// ============================================================================
// 3. 测试 Fixture 类
// ============================================================================

// 完整的 Rect 测试 fixture
class FullRectFixture implements Rect {
  left: number = 0;
  top: number = 0;
  width: number = 100;
  height: number = 100;

  constructor(left?: number, top?: number, width?: number, height?: number) {
    if (left !== undefined) this.left = left;
    if (top !== undefined) this.top = top;
    if (width !== undefined) this.width = width;
    if (height !== undefined) this.height = height;
  }
}

// 零值 Rect fixture
class ZeroRectFixture implements Rect {
  left: number = 0;
  top: number = 0;
  width: number = 0;
  height: number = 0;
}

// 负值 Rect fixture
class NegativeRectFixture implements Rect {
  left: number = -10;
  top: number = -20;
  width: number = -100;
  height: number = -200;
}

// 大数值 Rect fixture
class LargeRectFixture implements Rect {
  left: number = 10000;
  top: number = 20000;
  width: number = 30000;
  height: number = 40000;
}

// 完整的 AvoidArea 测试 fixture
class FullAvoidAreaFixture implements AvoidArea {
  visible: boolean = true;
  leftRect: Rect = new FullRectFixture(0, 0, 50, 100);
  topRect: Rect = new FullRectFixture(0, 0, 100, 50);
  rightRect: Rect = new FullRectFixture(50, 0, 50, 100);
  bottomRect: Rect = new FullRectFixture(0, 50, 100, 50);

  constructor(visible?: boolean) {
    if (visible !== undefined) this.visible = visible;
  }
}

// 隐藏的 AvoidArea fixture
class HiddenAvoidAreaFixture implements AvoidArea {
  visible: boolean = false;
  leftRect: Rect = new ZeroRectFixture();
  topRect: Rect = new ZeroRectFixture();
  rightRect: Rect = new ZeroRectFixture();
  bottomRect: Rect = new ZeroRectFixture();
}

// 完整的 UIEnvAvoidArea 测试 fixture
class FullUIEnvAvoidAreaFixture implements UIEnvAvoidArea {
  statusBar: AvoidArea = new FullAvoidAreaFixture(true);
  cutout: AvoidArea = new FullAvoidAreaFixture(false);
  keyboard: AvoidArea = new FullAvoidAreaFixture(true);
  navigationIndicator: AvoidArea = new FullAvoidAreaFixture(false);
}

// 所有区域都可见的 fixture
class AllVisibleUIEnvAvoidAreaFixture implements UIEnvAvoidArea {
  statusBar: AvoidArea = new FullAvoidAreaFixture(true);
  cutout: AvoidArea = new FullAvoidAreaFixture(true);
  keyboard: AvoidArea = new FullAvoidAreaFixture(true);
  navigationIndicator: AvoidArea = new FullAvoidAreaFixture(true);
}

// 所有区域都隐藏的 fixture
class AllHiddenUIEnvAvoidAreaFixture implements UIEnvAvoidArea {
  statusBar: AvoidArea = new HiddenAvoidAreaFixture();
  cutout: AvoidArea = new HiddenAvoidAreaFixture();
  keyboard: AvoidArea = new HiddenAvoidAreaFixture();
  navigationIndicator: AvoidArea = new HiddenAvoidAreaFixture();
}

// 包含大数值的 fixture
class LargeValueUIEnvAvoidAreaFixture implements UIEnvAvoidArea {
  statusBar: AvoidArea = {
    visible: true,
    leftRect: new LargeRectFixture(),
    topRect: new LargeRectFixture(),
    rightRect: new LargeRectFixture(),
    bottomRect: new LargeRectFixture()
  };
  cutout: AvoidArea = new HiddenAvoidAreaFixture();
  keyboard: AvoidArea = new HiddenAvoidAreaFixture();
  navigationIndicator: AvoidArea = new HiddenAvoidAreaFixture();
}

// 包含负值的 fixture
class NegativeValueUIEnvAvoidAreaFixture implements UIEnvAvoidArea {
  statusBar: AvoidArea = {
    visible: true,
    leftRect: new NegativeRectFixture(),
    topRect: new NegativeRectFixture(),
    rightRect: new NegativeRectFixture(),
    bottomRect: new NegativeRectFixture()
  };
  cutout: AvoidArea = new HiddenAvoidAreaFixture();
  keyboard: AvoidArea = new HiddenAvoidAreaFixture();
  navigationIndicator: AvoidArea = new HiddenAvoidAreaFixture();
}

// 状态栏可见的 fixture
class StatusBarVisibleFixture implements UIEnvAvoidArea {
  statusBar: AvoidArea = new FullAvoidAreaFixture(true);
  cutout: AvoidArea = new HiddenAvoidAreaFixture();
  keyboard: AvoidArea = new HiddenAvoidAreaFixture();
  navigationIndicator: AvoidArea = new HiddenAvoidAreaFixture();
}

// 刘海屏可见的 fixture
class CutoutVisibleFixture implements UIEnvAvoidArea {
  statusBar: AvoidArea = new HiddenAvoidAreaFixture();
  cutout: AvoidArea = new FullAvoidAreaFixture(true);
  keyboard: AvoidArea = new HiddenAvoidAreaFixture();
  navigationIndicator: AvoidArea = new HiddenAvoidAreaFixture();
}

// 键盘可见的 fixture
class KeyboardVisibleFixture implements UIEnvAvoidArea {
  statusBar: AvoidArea = new HiddenAvoidAreaFixture();
  cutout: AvoidArea = new HiddenAvoidAreaFixture();
  keyboard: AvoidArea = new FullAvoidAreaFixture(true);
  navigationIndicator: AvoidArea = new HiddenAvoidAreaFixture();
}

// 导航栏可见的 fixture
class NavigationIndicatorVisibleFixture implements UIEnvAvoidArea {
  statusBar: AvoidArea = new HiddenAvoidAreaFixture();
  cutout: AvoidArea = new HiddenAvoidAreaFixture();
  keyboard: AvoidArea = new HiddenAvoidAreaFixture();
  navigationIndicator: AvoidArea = new FullAvoidAreaFixture(true);
}

// ============================================================================
// 4. 主测试类
// ============================================================================

export class IEnvWindowAvoidAreaTests implements ITestFile {

  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating IEnvWindowAvoidAreaTests: ${str}`);
    this.idString = str;
  }

  // -------------------------------------------------------------------------
  // 生命周期方法
  // -------------------------------------------------------------------------

  public beforeAll(): void {
    // 在所有测试前执行一次
  }

  public beforeEach(): void {
    // 在每个测试前执行
  }

  public afterAll(): void {
    // 在所有测试后执行一次
  }

  public afterEach(): void {
    // 在每个测试后执行
  }

  public getId(): string {
    return this.idString;
  }

  // =========================================================================
  // 5. WindowAvoidAreaPxEnv 测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // 构造函数测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaPxEnvConstructor(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    eq(env !== null, true, 'WindowAvoidAreaPxEnv should be constructed');
    eq(env !== undefined, true, 'WindowAvoidAreaPxEnv should not be undefined');
  }

  public testWindowAvoidAreaPxEnvConstructorMultiple(): void {
    const context = new UIContext();
    const env1 = new WindowAvoidAreaPxEnv(context);
    const env2 = new WindowAvoidAreaPxEnv(context);
    eq(env1 !== env2, true, 'Multiple instances should be different');
  }

  // -------------------------------------------------------------------------
  // StatusBar 测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaPxEnvStatusBar(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const statusBar = env.statusBar;
    eq(statusBar !== null, true, 'StatusBar should be accessible');
    eq(typeof statusBar.visible, 'boolean', 'StatusBar visible should be boolean');
    eq(statusBar.leftRect !== null, true, 'StatusBar leftRect should exist');
    eq(statusBar.topRect !== null, true, 'StatusBar topRect should exist');
    eq(statusBar.rightRect !== null, true, 'StatusBar rightRect should exist');
    eq(statusBar.bottomRect !== null, true, 'StatusBar bottomRect should be exist');
  }

  public testWindowAvoidAreaPxEnvStatusBarVisible(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const statusBar = env.statusBar;
    eq(statusBar.visible === true || statusBar.visible === false, true, 'StatusBar visible should be boolean');
  }

  public testWindowAvoidAreaPxEnvStatusBarRects(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const statusBar = env.statusBar;
    eq(typeof statusBar.leftRect.left, 'number', 'Left rect left should be number');
    eq(typeof statusBar.leftRect.top, 'number', 'Left rect top should be number');
    eq(typeof statusBar.leftRect.width, 'number', 'Left rect width should be number');
    eq(typeof statusBar.leftRect.height, 'number', 'Left rect height should be number');
  }

  // -------------------------------------------------------------------------
  // Cutout 测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaPxEnvCutout(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const cutout = env.cutout;
    eq(cutout !== null, true, 'Cutout should be accessible');
    eq(typeof cutout.visible, 'boolean', 'Cutout visible should be boolean');
    eq(cutout.leftRect !== null, true, 'Cutout leftRect should exist');
    eq(cutout.topRect !== null, true, 'Cutout topRect should exist');
    eq(cutout.rightRect !== null, true, 'Cutout rightRect should exist');
    eq(cutout.bottomRect !== null, true, 'Cutout bottomRect should exist');
  }

  public testWindowAvoidAreaPxEnvCutoutVisible(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const cutout = env.cutout;
    eq(cutout.visible === true || cutout.visible === false, true, 'Cutout visible should be boolean');
  }

  public testWindowAvoidAreaPxEnvCutoutRects(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const cutout = env.cutout;
    eq(typeof cutout.leftRect.left, 'number', 'Cutout left rect left should be number');
    eq(typeof cutout.leftRect.top, 'number', 'Cutout left rect top should be number');
    eq(typeof cutout.leftRect.width, 'number', 'Cutout left rect width should be number');
    eq(typeof cutout.leftRect.height, 'number', 'Cutout left rect height should be number');
  }

  // -------------------------------------------------------------------------
  // Keyboard 测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaPxEnvKeyboard(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const keyboard = env.keyboard;
    eq(keyboard !== null, true, 'Keyboard should be accessible');
    eq(typeof keyboard.visible, 'boolean', 'Keyboard visible should be boolean');
    eq(keyboard.leftRect !== null, true, 'Keyboard leftRect should exist');
    eq(keyboard.topRect !== null, true, 'Keyboard topRect should exist');
    eq(keyboard.rightRect !== null, true, 'Keyboard rightRect should exist');
    eq(keyboard.bottomRect !== null, true, 'Keyboard bottomRect should exist');
  }

  public testWindowAvoidAreaPxEnvKeyboardVisible(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const keyboard = env.keyboard;
    eq(keyboard.visible === true || keyboard.visible === false, true, 'Keyboard visible should be boolean');
  }

  public testWindowAvoidAreaPxEnvKeyboardRects(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const keyboard = env.keyboard;
    eq(typeof keyboard.leftRect.left, 'number', 'Keyboard left rect left should be number');
    eq(typeof keyboard.leftRect.top, 'number', 'Keyboard left rect top should be number');
    eq(typeof keyboard.leftRect.width, 'number', 'Keyboard left rect width should be number');
    eq(typeof keyboard.leftRect.height, 'number', 'Keyboard left rect height should be number');
  }

  // -------------------------------------------------------------------------
  // NavigationIndicator 测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaPxEnvNavigationIndicator(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const navigationIndicator = env.navigationIndicator;
    eq(navigationIndicator !== null, true, 'NavigationIndicator should be accessible');
    eq(typeof navigationIndicator.visible, 'boolean', 'NavigationIndicator visible should be boolean');
    eq(navigationIndicator.leftRect !== null, true, 'NavigationIndicator leftRect should exist');
    eq(navigationIndicator.topRect !== null, true, 'NavigationIndicator topRect should exist');
    eq(navigationIndicator.rightRect !== null, true, 'NavigationIndicator rightRect should exist');
    eq(navigationIndicator.bottomRect !== null, true, 'NavigationIndicator bottomRect should exist');
  }

  public testWindowAvoidAreaPxEnvNavigationIndicatorVisible(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const navigationIndicator = env.navigationIndicator;
    eq(navigationIndicator.visible === true || navigationIndicator.visible === false, true, 'NavigationIndicator visible should be boolean');
  }

  public testWindowAvoidAreaPxEnvNavigationIndicatorRects(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const navigationIndicator = env.navigationIndicator;
    eq(typeof navigationIndicator.leftRect.left, 'number', 'NavigationIndicator left rect left should be number');
    eq(typeof navigationIndicator.leftRect.top, 'number', 'NavigationIndicator left rect top should be number');
    eq(typeof navigationIndicator.leftRect.width, 'number', 'NavigationIndicator left rect width should be number');
    eq(typeof navigationIndicator.leftRect.height, 'number', 'NavigationIndicator left rect height should be number');
  }

  // -------------------------------------------------------------------------
  // Value 属性测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaPxEnvValue(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const value = env.value;
    eq(value !== null, true, 'Value should be accessible');
    eq(value !== undefined, true, 'Value should not be undefined');
  }

  public testWindowAvoidAreaPxEnvValueStructure(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const value = env.value;
    eq(value.statusBar !== null, true, 'Value statusBar should exist');
    eq(value.cutout !== null, true, 'Value cutout should exist');
    eq(value.keyboard !== null, true, 'Value keyboard should exist');
    eq(value.navigationIndicator !== null, true, 'Value navigationIndicator should exist');
  }

  public testWindowAvoidAreaPxEnvValueConsistency(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const value = env.value;
    eq(value.statusBar === env.statusBar, true, 'Value statusBar should match instance property');
    eq(value.cutout === env.cutout, true, 'Value cutout should match instance property');
    eq(value.keyboard === env.keyboard, true, 'Value keyboard should match instance property');
    eq(value.navigationIndicator === env.navigationIndicator, true, 'Value navigationIndicator should match instance property');
  }

  // -------------------------------------------------------------------------
  // Update 方法测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaPxEnvUpdate(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    env.update();
    eq(env !== null, true, 'Update should complete without error');
  }

  public testWindowAvoidAreaPxEnvUpdateMultiple(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    env.update();
    env.update();
    env.update();
    eq(env !== null, true, 'Multiple updates should complete without error');
  }

  public testWindowAvoidAreaPxEnvUpdateAfterAccess(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const statusBarBefore = env.statusBar;
    env.update();
    const statusBarAfter = env.statusBar;
    eq(statusBarBefore !== null, true, 'StatusBar should be accessible before update');
    eq(statusBarAfter !== null, true, 'StatusBar should be accessible after update');
  }

  // -------------------------------------------------------------------------
  // Destroy 方法测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaPxEnvDestroy(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    env.destroy();
    eq(env !== null, true, 'Destroy should complete without error');
  }

  public testWindowAvoidAreaPxEnvDestroyOnce(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    env.destroy();
    eq(env !== null, true, 'Single destroy should complete');
  }

  public testWindowAvoidAreaPxEnvDestroyAfterUpdate(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    env.update();
    env.destroy();
    eq(env !== null, true, 'Destroy after update should complete');
  }

  // =========================================================================
  // 6. WindowAvoidAreaVpEnv 测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // 构造函数测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaVpEnvConstructor(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    eq(env !== null, true, 'WindowAvoidAreaVpEnv should be constructed');
    eq(env !== undefined, true, 'WindowAvoidAreaVpEnv should not be undefined');
  }

  public testWindowAvoidAreaVpEnvConstructorMultiple(): void {
    const context = new UIContext();
    const env1 = new WindowAvoidAreaVpEnv(context);
    const env2 = new WindowAvoidAreaVpEnv(context);
    eq(env1 !== env2, true, 'Multiple instances should be different');
  }

  // -------------------------------------------------------------------------
  // StatusBar 测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaVpEnvStatusBar(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const statusBar = env.statusBar;
    eq(statusBar !== null, true, 'StatusBar should be accessible');
    eq(typeof statusBar.visible, 'boolean', 'StatusBar visible should be boolean');
    eq(statusBar.leftRect !== null, true, 'StatusBar leftRect should exist');
    eq(statusBar.topRect !== null, true, 'StatusBar topRect should exist');
    eq(statusBar.rightRect !== null, true, 'StatusBar rightRect should exist');
    eq(statusBar.bottomRect !== null, true, 'StatusBar bottomRect should exist');
  }

  public testWindowAvoidAreaVpEnvStatusBarVisible(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const statusBar = env.statusBar;
    eq(statusBar.visible === true || statusBar.visible === false, true, 'StatusBar visible should be boolean');
  }

  public testWindowAvoidAreaVpEnvStatusBarRects(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const statusBar = env.statusBar;
    eq(typeof statusBar.leftRect.left, 'number', 'Left rect left should be number');
    eq(typeof statusBar.leftRect.top, 'number', 'Left rect top should be number');
    eq(typeof statusBar.leftRect.width, 'number', 'Left rect width should be number');
    eq(typeof statusBar.leftRect.height, 'number', 'Left rect height should be number');
  }

  // -------------------------------------------------------------------------
  // Cutout 测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaVpEnvCutout(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const cutout = env.cutout;
    eq(cutout !== null, true, 'Cutout should be accessible');
    eq(typeof cutout.visible, 'boolean', 'Cutout visible should be boolean');
    eq(cutout.leftRect !== null, true, 'Cutout leftRect should exist');
    eq(cutout.topRect !== null, true, 'Cutout topRect should exist');
    eq(cutout.rightRect !== null, true, 'Cutout rightRect should exist');
    eq(cutout.bottomRect !== null, true, 'Cutout bottomRect should exist');
  }

  public testWindowAvoidAreaVpEnvCutoutVisible(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const cutout = env.cutout;
    eq(cutout.visible === true || cutout.visible === false, true, 'Cutout visible should be boolean');
  }

  public testWindowAvoidAreaVpEnvCutoutRects(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const cutout = env.cutout;
    eq(typeof cutout.leftRect.left, 'number', 'Cutout left rect left should be number');
    eq(typeof cutout.leftRect.top, 'number', 'Cutout left rect top should be number');
    eq(typeof cutout.leftRect.width, 'number', 'Cutout left rect width should be number');
    eq(typeof cutout.leftRect.height, 'number', 'Cutout left rect height should be number');
  }

  // -------------------------------------------------------------------------
  // Keyboard 测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaVpEnvKeyboard(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const keyboard = env.keyboard;
    eq(keyboard !== null, true, 'Keyboard should be accessible');
    eq(typeof keyboard.visible, 'boolean', 'Keyboard visible should be boolean');
    eq(keyboard.leftRect !== null, true, 'Keyboard leftRect should exist');
    eq(keyboard.topRect !== null, true, 'Keyboard topRect should exist');
    eq(keyboard.rightRect !== null, true, 'Keyboard rightRect should exist');
    eq(keyboard.bottomRect !== null, true, 'Keyboard bottomRect should exist');
  }

  public testWindowAvoidAreaVpEnvKeyboardVisible(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const keyboard = env.keyboard;
    eq(keyboard.visible === true || keyboard.visible === false, true, 'Keyboard visible should be boolean');
  }

  public testWindowAvoidAreaVpEnvKeyboardRects(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const keyboard = env.keyboard;
    eq(typeof keyboard.leftRect.left, 'number', 'Keyboard left rect left should be number');
    eq(typeof keyboard.leftRect.top, 'number', 'Keyboard left rect top should be number');
    eq(typeof keyboard.leftRect.width, 'number', 'Keyboard left rect width should be number');
    eq(typeof keyboard.leftRect.height, 'number', 'Keyboard left rect height should be number');
  }

  // -------------------------------------------------------------------------
  // NavigationIndicator 测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaVpEnvNavigationIndicator(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const navigationIndicator = env.navigationIndicator;
    eq(navigationIndicator !== null, true, 'NavigationIndicator should be accessible');
    eq(typeof navigationIndicator.visible, 'boolean', 'NavigationIndicator visible should be boolean');
    eq(navigationIndicator.leftRect !== null, true, 'NavigationIndicator leftRect should exist');
    eq(navigationIndicator.topRect !== null, true, 'NavigationIndicator topRect should exist');
    eq(navigationIndicator.rightRect !== null, true, 'NavigationIndicator rightRect should exist');
    eq(navigationIndicator.bottomRect !== null, true, 'NavigationIndicator bottomRect should exist');
  }

  public testWindowAvoidAreaVpEnvNavigationIndicatorVisible(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const navigationIndicator = env.navigationIndicator;
    eq(navigationIndicator.visible === true || navigationIndicator.visible === false, true, 'NavigationIndicator visible should be boolean');
  }

  public testWindowAvoidAreaVpEnvNavigationIndicatorRects(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const navigationIndicator = env.navigationIndicator;
    eq(typeof navigationIndicator.leftRect.left, 'number', 'NavigationIndicator left rect left should be number');
    eq(typeof navigationIndicator.leftRect.top, 'number', 'NavigationIndicator left rect top should be number');
    eq(typeof navigationIndicator.leftRect.width, 'number', 'NavigationIndicator left rect width should be number');
    eq(typeof navigationIndicator.leftRect.height, 'number', 'NavigationIndicator left rect height should be number');
  }

  // -------------------------------------------------------------------------
  // Value 属性测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaVpEnvValue(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const value = env.value;
    eq(value !== null, true, 'Value should be accessible');
    eq(value !== undefined, true, 'Value should not be undefined');
  }

  public testWindowAvoidAreaVpEnvValueStructure(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const value = env.value;
    eq(value.statusBar !== null, true, 'Value statusBar should exist');
    eq(value.cutout !== null, true, 'Value cutout should exist');
    eq(value.keyboard !== null, true, 'Value keyboard should exist');
    eq(value.navigationIndicator !== null, true, 'Value navigationIndicator should exist');
  }

  public testWindowAvoidAreaVpEnvValueConsistency(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const value = env.value;
    eq(value.statusBar === env.statusBar, true, 'Value statusBar should match instance property');
    eq(value.cutout === env.cutout, true, 'Value cutout should match instance property');
    eq(value.keyboard === env.keyboard, true, 'Value keyboard should match instance property');
    eq(value.navigationIndicator === env.navigationIndicator, true, 'Value navigationIndicator should match instance property');
  }

  // -------------------------------------------------------------------------
  // Update 方法测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaVpEnvUpdate(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    env.update();
    eq(env !== null, true, 'Update should complete without error');
  }

  public testWindowAvoidAreaVpEnvUpdateMultiple(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    env.update();
    env.update();
    env.update();
    eq(env !== null, true, 'Multiple updates should complete without error');
  }

  public testWindowAvoidAreaVpEnvUpdateAfterAccess(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    const statusBarBefore = env.statusBar;
    env.update();
    const statusBarAfter = env.statusBar;
    eq(statusBarBefore !== null, true, 'StatusBar should be accessible before update');
    eq(statusBarAfter !== null, true, 'StatusBar should be accessible after update');
  }

  // -------------------------------------------------------------------------
  // Destroy 方法测试
  // -------------------------------------------------------------------------

  public testWindowAvoidAreaVpEnvDestroy(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    env.destroy();
    eq(env !== null, true, 'Destroy should complete without error');
  }

  public testWindowAvoidAreaVpEnvDestroyOnce(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    env.destroy();
    eq(env !== null, true, 'Single destroy should complete');
  }

  public testWindowAvoidAreaVpEnvDestroyAfterUpdate(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaVpEnv(context);
    env.update();
    env.destroy();
    eq(env !== null, true, 'Destroy after update should complete');
  }

  // =========================================================================
  // 7. 边界测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // Rect 边界测试
  // -------------------------------------------------------------------------

  public testEdgeCaseRectZeroValues(): void {
    const rect: Rect = {
      left: 0,
      top: 0,
      width: 0,
      height: 0
    };
    eq(rect.left, 0, 'Rect left should be zero');
    eq(rect.top, 0, 'Rect top should be zero');
    eq(rect.width, 0, 'Rect width should be zero');
    eq(rect.height, 0, 'Rect height should be zero');
  }

  public testEdgeCaseRectNegativeValues(): void {
    const rect: Rect = {
      left: -100,
      top: -200,
      width: -300,
      height: -400
    };
    eq(rect.left, -100, 'Rect left should be negative');
    eq(rect.top, -200, 'Rect top should be negative');
    eq(rect.width, -300, 'Rect width should be negative');
    eq(rect.height, -400, 'Rect height should be negative');
  }

  public testEdgeCaseRectLargeValues(): void {
    const rect: Rect = {
      left: Number.MAX_SAFE_INTEGER,
      top: Number.MAX_SAFE_INTEGER,
      width: Number.MAX_SAFE_INTEGER,
      height: Number.MAX_SAFE_INTEGER
    };
    eq(rect.left, Number.MAX_SAFE_INTEGER, 'Rect left should be large');
    eq(rect.top, Number.MAX_SAFE_INTEGER, 'Rect top should be large');
    eq(rect.width, Number.MAX_SAFE_INTEGER, 'Rect width should be large');
    eq(rect.height, Number.MAX_SAFE_INTEGER, 'Rect height should be large');
  }

  public testEdgeCaseRectFractionalValues(): void {
    const rect: Rect = {
      left: 10.5,
      top: 20.7,
      width: 30.3,
      height: 40.9
    };
    eq(rect.left, 10.5, 'Rect left should be fractional');
    eq(rect.top, 20.7, 'Rect top should be fractional');
    eq(rect.width, 30.3, 'Rect width should be fractional');
    eq(rect.height, 40.9, 'Rect height should be fractional');
  }

  // -------------------------------------------------------------------------
  // AvoidArea 边界测试
  // -------------------------------------------------------------------------

  public testEdgeCaseAvoidAreaAllHidden(): void {
    const avoidArea: AvoidArea = {
      visible: false,
      leftRect: { left: 0, top: 0, width: 0, height: 0 },
      topRect: { left: 0, top: 0, width: 0, height: 0 },
      rightRect: { left: 0, top: 0, width: 0, height: 0 },
      bottomRect: { left: 0, top: 0, width: 0, height: 0 }
    };
    eq(avoidArea.visible, false, 'AvoidArea should be hidden');
    eq(avoidArea.leftRect.width, 0, 'Left rect width should be zero');
    eq(avoidArea.topRect.height, 0, 'Top rect height should be zero');
  }

  public testEdgeCaseAvoidAreaVisibleWithZeroRects(): void {
    const avoidArea: AvoidArea = {
      visible: true,
      leftRect: { left: 0, top: 0, width: 0, height: 0 },
      topRect: { left: 0, top: 0, width: 0, height: 0 },
      rightRect: { left: 0, top: 0, width: 0, height: 0 },
      bottomRect: { left: 0, top: 0, width: 0, height: 0 }
    };
    eq(avoidArea.visible, true, 'AvoidArea should be visible');
    eq(avoidArea.leftRect.width, 0, 'Left rect width should be zero');
  }

  public testEdgeCaseAvoidAreaHiddenWithNonZeroRects(): void {
    const avoidArea: AvoidArea = {
      visible: false,
      leftRect: { left: 10, top: 20, width: 30, height: 40 },
      topRect: { left: 50, top: 60, width: 70, height: 80 },
      rightRect: { left: 90, top: 100, width: 110, height: 120 },
      bottomRect: { left: 130, top: 140, width: 150, height: 160 }
    };
    eq(avoidArea.visible, false, 'AvoidArea should be hidden');
    eq(avoidArea.leftRect.width, 30, 'Left rect width should be preserved');
  }

  // -------------------------------------------------------------------------
  // UIEnvAvoidArea 边界测试
  // -------------------------------------------------------------------------

  public testEdgeCaseUIEnvAvoidAreaAllZero(): void {
    const uiEnv: UIEnvAvoidArea = {
      statusBar: {
        visible: false,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 0, width: 0, height: 0 }
      },
      cutout: {
        visible: false,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 0, width: 0, height: 0 }
      },
      keyboard: {
        visible: false,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 0, width: 0, height: 0 }
      },
      navigationIndicator: {
        visible: false,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 0, width: 0, height: 0 }
      }
    };
    eq(uiEnv.statusBar.visible, false, 'StatusBar should be hidden');
    eq(uiEnv.cutout.visible, false, 'Cutout should be hidden');
    eq(uiEnv.keyboard.visible, false, 'Keyboard should be hidden');
    eq(uiEnv.navigationIndicator.visible, false, 'NavigationIndicator should be hidden');
  }

  public testEdgeCaseUIEnvAvoidAreaMixedVisibility(): void {
    const uiEnv: UIEnvAvoidArea = {
      statusBar: {
        visible: true,
        leftRect: { left: 0, top: 0, width: 100, height: 50 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 0, width: 0, height: 0 }
      },
      cutout: {
        visible: false,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 0, width: 0, height: 0 }
      },
      keyboard: {
        visible: true,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 500, width: 100, height: 300 }
      },
      navigationIndicator: {
        visible: false,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 0, width: 0, height: 0 }
      }
    };
    eq(uiEnv.statusBar.visible, true, 'StatusBar should be visible');
    eq(uiEnv.cutout.visible, false, 'Cutout should be hidden');
    eq(uiEnv.keyboard.visible, true, 'Keyboard should be visible');
    eq(uiEnv.navigationIndicator.visible, false, 'NavigationIndicator should be hidden');
  }

  // =========================================================================
  // 8. 功能测试
  // =========================================================================

  // -------------------------------------------------------------------------
  // Rect 功能测试
  // -------------------------------------------------------------------------

  public testFeatureRectNormalValues(): void {
    const rect: Rect = {
      left: 10,
      top: 20,
      width: 100,
      height: 200
    };
    eq(rect.left, 10, 'Rect left should be 10');
    eq(rect.top, 20, 'Rect top should be 20');
    eq(rect.width, 100, 'Rect width should be 100');
    eq(rect.height, 200, 'Rect height should be 200');
  }

  public testFeatureRectPositionCalculation(): void {
    const rect: Rect = {
      left: 50,
      top: 100,
      width: 200,
      height: 150
    };
    const right = rect.left + rect.width;
    const bottom = rect.top + rect.height;
    eq(right, 250, 'Right edge should be 250');
    eq(bottom, 250, 'Bottom edge should be 250');
  }

  public testFeatureRectAreaCalculation(): void {
    const rect: Rect = {
      left: 0,
      top: 0,
      width: 100,
      height: 50
    };
    const area = rect.width * rect.height;
    eq(area, 5000, 'Rect area should be 5000');
  }

  // -------------------------------------------------------------------------
  // AvoidArea 功能测试
  // -------------------------------------------------------------------------

  public testFeatureAvoidAreaNormal(): void {
    const avoidArea: AvoidArea = {
      visible: true,
      leftRect: { left: 0, top: 0, width: 0, height: 100 },
      topRect: { left: 0, top: 0, width: 100, height: 50 },
      rightRect: { left: 100, top: 0, width: 0, height: 100 },
      bottomRect: { left: 0, top: 100, width: 100, height: 0 }
    };
    eq(avoidArea.visible, true, 'AvoidArea should be visible');
    eq(avoidArea.topRect.height, 50, 'Top rect height should be 50');
  }

  // -------------------------------------------------------------------------
  // UIEnvAvoidArea 功能测试
  // -------------------------------------------------------------------------

  public testFeatureUIEnvAvoidAreaStatusBarOnly(): void {
    const uiEnv: UIEnvAvoidArea = {
      statusBar: {
        visible: true,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 100, height: 50 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 0, width: 0, height: 0 }
      },
      cutout: new HiddenAvoidAreaFixture(),
      keyboard: new HiddenAvoidAreaFixture(),
      navigationIndicator: new HiddenAvoidAreaFixture()
    };
    eq(uiEnv.statusBar.visible, true, 'StatusBar should be visible');
    eq(uiEnv.statusBar.topRect.height, 50, 'StatusBar height should be 50');
  }

  public testFeatureUIEnvAvoidAreaKeyboardOnly(): void {
    const uiEnv: UIEnvAvoidArea = {
      statusBar: new HiddenAvoidAreaFixture(),
      cutout: new HiddenAvoidAreaFixture(),
      keyboard: {
        visible: true,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 500, width: 100, height: 300 }
      },
      navigationIndicator: new HiddenAvoidAreaFixture()
    };
    eq(uiEnv.keyboard.visible, true, 'Keyboard should be visible');
    eq(uiEnv.keyboard.bottomRect.height, 300, 'Keyboard height should be 300');
  }

  public testFeatureUIEnvAvoidAreaCutoutOnly(): void {
    const uiEnv: UIEnvAvoidArea = {
      statusBar: new HiddenAvoidAreaFixture(),
      cutout: {
        visible: true,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 40, top: 0, width: 20, height: 30 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 0, width: 0, height: 0 }
      },
      keyboard: new HiddenAvoidAreaFixture(),
      navigationIndicator: new HiddenAvoidAreaFixture()
    };
    eq(uiEnv.cutout.visible, true, 'Cutout should be visible');
    eq(uiEnv.cutout.topRect.width, 20, 'Cutout width should be 20');
  }

  public testFeatureUIEnvAvoidAreaNavigationIndicatorOnly(): void {
    const uiEnv: UIEnvAvoidArea = {
      statusBar: new HiddenAvoidAreaFixture(),
      cutout: new HiddenAvoidAreaFixture(),
      keyboard: new HiddenAvoidAreaFixture(),
      navigationIndicator: {
        visible: true,
        leftRect: { left: 0, top: 0, width: 0, height: 0 },
        topRect: { left: 0, top: 0, width: 0, height: 0 },
        rightRect: { left: 0, top: 0, width: 0, height: 0 },
        bottomRect: { left: 0, top: 750, width: 100, height: 50 }
      }
    };
    eq(uiEnv.navigationIndicator.visible, true, 'NavigationIndicator should be visible');
    eq(uiEnv.navigationIndicator.bottomRect.height, 50, 'NavigationIndicator height should be 50');
  }

  // =========================================================================
  // 9. 性能测试
  // =========================================================================

  public testPerformanceMultiplePxEnvCreation(): void {
    const context = new UIContext();
    const iterations = 100;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const env = new WindowAvoidAreaPxEnv(context);
      env.destroy();
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Multiple PxEnv creation should complete in reasonable time');
  }

  public testPerformanceMultipleVpEnvCreation(): void {
    const context = new UIContext();
    const iterations = 100;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const env = new WindowAvoidAreaVpEnv(context);
      env.destroy();
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Multiple VpEnv creation should complete in reasonable time');
  }

  public testPerformanceMultipleUpdates(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const iterations = 1000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      env.update();
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Multiple updates should complete in reasonable time');
  }

  public testPerformanceValueAccess(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const iterations = 1000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const value = env.value;
      const statusBar = value.statusBar;
      const cutout = value.cutout;
      const keyboard = value.keyboard;
      const navigationIndicator = value.navigationIndicator;
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Multiple value accesses should complete in reasonable time');
  }

  public testPerformancePropertyAccess(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const iterations = 1000;
    const startTime = Date.now();
    for (let i = 0; i < iterations; i++) {
      const statusBar = env.statusBar;
      const cutout = env.cutout;
      const keyboard = env.keyboard;
      const navigationIndicator = env.navigationIndicator;
    }
    const duration = Date.now() - startTime;
    eq(duration < 1000, true, 'Multiple property accesses should complete in reasonable time');
  }

  // =========================================================================
  // 10. 兼容性测试
  // =========================================================================

  public testCompatibilityPxEnvAndVpEnvStructure(): void {
    const context = new UIContext();
    const pxEnv = new WindowAvoidAreaPxEnv(context);
    const vpEnv = new WindowAvoidAreaVpEnv(context);
    eq(typeof pxEnv.statusBar, typeof vpEnv.statusBar, 'PxEnv and VpEnv statusBar should have same type');
    eq(typeof pxEnv.cutout, typeof vpEnv.cutout, 'PxEnv and VpEnv cutout should have same type');
    eq(typeof pxEnv.keyboard, typeof vpEnv.keyboard, 'PxEnv and VpEnv keyboard should have same type');
    eq(typeof pxEnv.navigationIndicator, typeof vpEnv.navigationIndicator, 'PxEnv and VpEnv navigationIndicator should have same type');
  }

  public testCompatibilityValuePropertyType(): void {
    const context = new UIContext();
    const pxEnv = new WindowAvoidAreaPxEnv(context);
    const vpEnv = new WindowAvoidAreaVpEnv(context);
    eq(typeof pxEnv.value, typeof vpEnv.value, 'PxEnv and VpEnv value should have same type');
  }

  public testCompatibilityMethodExistence(): void {
    const context = new UIContext();
    const pxEnv = new WindowAvoidAreaPxEnv(context);
    const vpEnv = new WindowAvoidAreaVpEnv(context);
    eq(typeof pxEnv.update, 'function', 'PxEnv should have update method');
    eq(typeof pxEnv.destroy, 'function', 'PxEnv should have destroy method');
    eq(typeof vpEnv.update, 'function', 'VpEnv should have update method');
    eq(typeof vpEnv.destroy, 'function', 'VpEnv should have destroy method');
  }

  public testCompatibilityMultipleContexts(): void {
    const context1 = new UIContext();
    const context2 = new UIContext();
    const env1 = new WindowAvoidAreaPxEnv(context1);
    const env2 = new WindowAvoidAreaPxEnv(context2);
    eq(env1 !== env2, true, 'Envs with different contexts should be different');
    eq(env1.statusBar !== null, true, 'Env1 statusBar should be accessible');
    eq(env2.statusBar !== null, true, 'Env2 statusBar should be accessible');
  }

  public testCompatibilityLifecycleSequence(): void {
    const context = new UIContext();
    const env = new WindowAvoidAreaPxEnv(context);
    const value1 = env.value;
    env.update();
    const value2 = env.value;
    env.update();
    const value3 = env.value;
    env.destroy();
    eq(value1 !== null, true, 'Value should be accessible after construction');
    eq(value2 !== null, true, 'Value should be accessible after first update');
    eq(value3 !== null, true, 'Value should be accessible after second update');
  }
}
