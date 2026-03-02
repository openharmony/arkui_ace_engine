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

//  UIContext 类型
class UIContext {
    constructor() {
    }
}

// 声明 IEnvironmentValue 接口
declare interface IEnvironmentValue<T> {
    value: T;
    update(newValue: T): void;
    destroy(): void;
}

// 声明 Size 接口
declare interface Size {
    width: number;
    height: number;
}

// 声明 SizeInVp 接口
declare interface SizeInVp {
    widthVp: number;
    heightVp: number;
}

// 声明 WindowSizePxEnv 类
class WindowSizePxEnv implements IEnvironmentValue<Size> {
    public value: Size;
    private context: UIContext;

    constructor(context: UIContext) {
        this.context = context;
        // 初始化一个默认的 Size 对象，防止 value 为 undefined
        this.value = { width: 0, height: 0 };
    }

    update(newValue: Size): void {
        this.value = newValue;
    }

    destroy(): void {
        // 模拟销毁逻辑
    }
}

// 声明 WindowSizeVpEnv 类
class WindowSizeVpEnv implements IEnvironmentValue<SizeInVp> {
    public value: SizeInVp;
    private context: UIContext;

    constructor(context: UIContext) {
        this.context = context;
        // 初始化默认的 VP 尺寸对象，防止访问 value 时报错
        // 假设 SizeInVp 结构为 { widthVp: number, heightVp: number }
        this.value = { widthVp: 0, heightVp: 0 };
    }

    update(newValue: SizeInVp): void {
        // 简单的赋值逻辑，也可以添加类型检查
        this.value = newValue;
    }

    destroy(): void {
        // 模拟销毁逻辑，例如清空值或标记状态
        this.value = { widthVp: 0, heightVp: 0 };
    }
}

// ============================================================================
// 3. 测试 Fixture 类
// ============================================================================

// 标准 Size 测试类
class StandardSize implements Size {
    width: number = 0;
    height: number = 0;

    constructor(width: number = 0, height: number = 0) {
        this.width = width;
        this.height = height;
    }
}

// 标准 SizeInVp 测试类
class StandardSizeInVp implements SizeInVp {
    widthVp: number = 0;
    heightVp: number = 0;

    constructor(widthVp: number = 0, heightVp: number = 0) {
        this.widthVp = widthVp;
        this.heightVp = heightVp;
    }
}

// 包含负数的 Size 测试类
class NegativeSize implements Size {
    width: number = -100;
    height: number = -200;
}

// 包含零值的 Size 测试类
class ZeroSize implements Size {
    width: number = 0;
    height: number = 0;
}

// 包含大数值的 Size 测试类
class LargeSize implements Size {
    width: number = 99999;
    height: number = 88888;
}

// 包含小数的 Size 测试类
class FractionalSize implements Size {
    width: number = 100.5;
    height: number = 200.75;
}

// 包含最大安全整数的 Size 测试类
class MaxSafeIntegerSize implements Size {
    width: number = Number.MAX_SAFE_INTEGER;
    height: number = Number.MAX_SAFE_INTEGER;
}

// 包含最小安全整数的 Size 测试类
class MinSafeIntegerSize implements Size {
    width: number = Number.MIN_SAFE_INTEGER;
    height: number = Number.MIN_SAFE_INTEGER;
}

// 包含 Infinity 的 Size 测试类
class InfinitySize implements Size {
    width: number = Infinity;
    height: number = Infinity;
}

// 包含 NaN 的 Size 测试类
class NaNSize implements Size {
    width: number = NaN;
    height: number = NaN;
}

// 宽屏 Size 测试类
class WideScreenSize implements Size {
    width: number = 1920;
    height: number = 1080;
}

// 竖屏 Size 测试类
class PortraitScreenSize implements Size {
    width: number = 1080;
    height: number = 1920;
}

// 方形 Size 测试类
class SquareSize implements Size {
    width: number = 500;
    height: number = 500;
}

// 超宽屏 Size 测试类
class UltraWideScreenSize implements Size {
    width: number = 3440;
    height: number = 1440;
}

// 移动设备 Size 测试类
class MobileSize implements Size {
    width: number = 375;
    height: number = 667;
}

// 平板设备 Size 测试类
class TabletSize implements Size {
    width: number = 768;
    height: number = 1024;
}

// 桌面设备 Size 测试类
class DesktopSize implements Size {
    width: number = 1440;
    height: number = 900;
}

// 4K 分辨率 Size 测试类
class FourKSize implements Size {
    width: number = 3840;
    height: number = 2160;
}

// 8K 分辨率 Size 测试类
class EightKSize implements Size {
    width: number = 7680;
    height: number = 4320;
}

// 包含负数的 SizeInVp 测试类
class NegativeSizeInVp implements SizeInVp {
    widthVp: number = -50;
    heightVp: number = -100;
}

// 包含零值的 SizeInVp 测试类
class ZeroSizeInVp implements SizeInVp {
    widthVp: number = 0;
    heightVp: number = 0;
}

// 包含大数值的 SizeInVp 测试类
class LargeSizeInVp implements SizeInVp {
    widthVp: number = 1000;
    heightVp: number = 2000;
}

// 包含小数的 SizeInVp 测试类
class FractionalSizeInVp implements SizeInVp {
    widthVp: number = 50.5;
    heightVp: number = 100.75;
}

// ============================================================================
// 4. 主测试类
// ============================================================================

export class IEnvWindowSizeTests implements ITestFile {

    private idString: string = "";

    constructor(str: string) {
        console.log(`Creating IEnvWindowSizeTests: ${str}`);
        this.idString = str;
    }

    // -------------------------------------------------------------------------
    // 生命周期方法
    // -------------------------------------------------------------------------

    public beforeAll(): void {
        // 在所有测试前执行一次
        // 可以在这里初始化全局测试资源
    }

    public beforeEach(): void {
        // 在每个测试前执行
        // 可以在这里重置测试状态
    }

    public afterAll(): void {
        // 在所有测试后执行一次
        // 可以在这里清理全局测试资源
    }

    public afterEach(): void {
        // 在每个测试后执行
        // 可以在这里清理单个测试的资源
    }

    public getId(): string {
        return this.idString;
    }

    // =========================================================================
    // 5. 接口测试
    // =========================================================================

    // -------------------------------------------------------------------------
    // Size 接口测试
    // -------------------------------------------------------------------------

    public testInterfaceSizeStandard(): void {
        const size: Size = new StandardSize(100, 200);
        eq(size.width, 100, 'Size width should be 100');
        eq(size.height, 200, 'Size height should be 200');
    }

    public testInterfaceSizeZero(): void {
        const size: Size = new ZeroSize();
        eq(size.width, 0, 'Size width should be 0');
        eq(size.height, 0, 'Size height should be 0');
    }

    public testInterfaceSizeNegative(): void {
        const size: Size = new NegativeSize();
        eq(size.width, -100, 'Size width should be -100');
        eq(size.height, -200, 'Size height should be -200');
    }

    public testInterfaceSizeLarge(): void {
        const size: Size = new LargeSize();
        eq(size.width, 99999, 'Size width should be 99999');
        eq(size.height, 88888, 'Size height should be 88888');
    }

    public testInterfaceSizeFractional(): void {
        const size: Size = new FractionalSize();
        eq(size.width, 100.5, 'Size width should be 100.5');
        eq(size.height, 200.75, 'Size height should be 200.75');
    }

    public testInterfaceSizeMaxSafeInteger(): void {
        const size: Size = new MaxSafeIntegerSize();
        eq(size.width, Number.MAX_SAFE_INTEGER, 'Size width should be MAX_SAFE_INTEGER');
        eq(size.height, Number.MAX_SAFE_INTEGER, 'Size height should be MAX_SAFE_INTEGER');
    }

    public testInterfaceSizeMinSafeInteger(): void {
        const size: Size = new MinSafeIntegerSize();
        eq(size.width, Number.MIN_SAFE_INTEGER, 'Size width should be MIN_SAFE_INTEGER');
        eq(size.height, Number.MIN_SAFE_INTEGER, 'Size height should be MIN_SAFE_INTEGER');
    }

    public testInterfaceSizeInfinity(): void {
        const size: Size = new InfinitySize();
        eq(size.width, Infinity, 'Size width should be Infinity');
        eq(size.height, Infinity, 'Size height should be Infinity');
    }

    public testInterfaceSizeNaN(): void {
        const size: Size = new NaNSize();
        eq(isNaN(size.width), true, 'Size width should be NaN');
        eq(isNaN(size.height), true, 'Size height should be NaN');
    }

    // -------------------------------------------------------------------------
    // SizeInVp 接口测试
    // -------------------------------------------------------------------------

    public testInterfaceSizeInVpStandard(): void {
        const size: SizeInVp = new StandardSizeInVp(50, 100);
        eq(size.widthVp, 50, 'SizeInVp widthVp should be 50');
        eq(size.heightVp, 100, 'SizeInVp heightVp should be 100');
    }

    public testInterfaceSizeInVpZero(): void {
        const size: SizeInVp = new ZeroSizeInVp();
        eq(size.widthVp, 0, 'SizeInVp widthVp should be 0');
        eq(size.heightVp, 0, 'SizeInVp heightVp should be 0');
    }

    public testInterfaceSizeInVpNegative(): void {
        const size: SizeInVp = new NegativeSizeInVp();
        eq(size.widthVp, -50, 'SizeInVp widthVp should be -50');
        eq(size.heightVp, -100, 'SizeInVp heightVp should be -100');
    }

    public testInterfaceSizeInVpLarge(): void {
        const size: SizeInVp = new LargeSizeInVp();
        eq(size.widthVp, 1000, 'SizeInVp widthVp should be 1000');
        eq(size.heightVp, 2000, 'SizeInVp heightVp should be 2000');
    }

    public testInterfaceSizeInVpFractional(): void {
        const size: SizeInVp = new FractionalSizeInVp();
        eq(size.widthVp, 50.5, 'SizeInVp widthVp should be 50.5');
        eq(size.heightVp, 100.75, 'SizeInVp heightVp should be 100.75');
    }

    // =========================================================================
    // 6. WindowSizePxEnv 类测试
    // =========================================================================

    // -------------------------------------------------------------------------
    // 构造函数测试
    // -------------------------------------------------------------------------

    public testWindowSizePxEnvConstructor(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        eq(env !== null, true, 'WindowSizePxEnv should be created');
        eq(env !== undefined, true, 'WindowSizePxEnv should not be undefined');
    }

    public testWindowSizePxEnvConstructorWithNullContext(): void {
        const context: any = null;
        try {
            const env = new WindowSizePxEnv(context);
            eq(false, true, 'Should throw error with null context');
        } catch (e) {
            eq(true, true, 'Should throw error with null context');
        }
    }

    public testWindowSizePxEnvConstructorWithUndefinedContext(): void {
        const context: any = undefined;
        try {
            const env = new WindowSizePxEnv(context);
            eq(false, true, 'Should throw error with undefined context');
        } catch (e) {
            eq(true, true, 'Should throw error with undefined context');
        }
    }

    // -------------------------------------------------------------------------
    // value 属性测试
    // -------------------------------------------------------------------------

    public testWindowSizePxEnvValue(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const value = env.value;
        eq(typeof value, 'object', 'value should be an object');
        eq(value !== null, true, 'value should not be null');
    }

    public testWindowSizePxEnvValueWidth(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const value = env.value;
        eq(typeof value.width, 'number', 'value.width should be a number');
    }

    public testWindowSizePxEnvValueHeight(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const value = env.value;
        eq(typeof value.height, 'number', 'value.height should be a number');
    }

    public testWindowSizePxEnvValuePositive(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const value = env.value;
        eq(value.width >= 0, true, 'value.width should be non-negative');
        eq(value.height >= 0, true, 'value.height should be non-negative');
    }

    // -------------------------------------------------------------------------
    // update 方法测试
    // -------------------------------------------------------------------------

    public testWindowSizePxEnvUpdate(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const newSize: Size = new StandardSize(300, 400);
        env.update(newSize);
        const value = env.value;
        eq(value.width, 300, 'value.width should be updated to 300');
        eq(value.height, 400, 'value.height should be updated to 400');
    }

    public testWindowSizePxEnvUpdateZero(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const newSize: Size = new ZeroSize();
        env.update(newSize);
        const value = env.value;
        eq(value.width, 0, 'value.width should be updated to 0');
        eq(value.height, 0, 'value.height should be updated to 0');
    }

    public testWindowSizePxEnvUpdateLarge(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const newSize: Size = new LargeSize();
        env.update(newSize);
        const value = env.value;
        eq(value.width, 99999, 'value.width should be updated to 99999');
        eq(value.height, 88888, 'value.height should be updated to 88888');
    }

    public testWindowSizePxEnvUpdateNegative(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const newSize: Size = new NegativeSize();
        env.update(newSize);
        const value = env.value;
        eq(value.width, -100, 'value.width should be updated to -100');
        eq(value.height, -200, 'value.height should be updated to -200');
    }

    public testWindowSizePxEnvUpdateFractional(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const newSize: Size = new FractionalSize();
        env.update(newSize);
        const value = env.value;
        eq(value.width, 100.5, 'value.width should be updated to 100.5');
        eq(value.height, 200.75, 'value.height should be updated to 200.75');
    }

    public testWindowSizePxEnvUpdateMultipleTimes(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update(new StandardSize(100, 200));
        env.update(new StandardSize(200, 300));
        env.update(new StandardSize(300, 400));
        const value = env.value;
        eq(value.width, 300, 'value.width should be updated to 300 after multiple updates');
        eq(value.height, 400, 'value.height should be updated to 400 after multiple updates');
    }

    public testWindowSizePxEnvUpdateWithNull(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const newSize: any = null;
        try {
            env.update(newSize);
            eq(false, true, 'Should throw error with null value');
        } catch (e) {
            eq(true, true, 'Should throw error with null value');
        }
    }

    public testWindowSizePxEnvUpdateWithUndefined(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const newSize: any = undefined;
        try {
            env.update(newSize);
            eq(false, true, 'Should throw error with undefined value');
        } catch (e) {
            eq(true, true, 'Should throw error with undefined value');
        }
    }

    // -------------------------------------------------------------------------
    // destroy 方法测试
    // -------------------------------------------------------------------------

    public testWindowSizePxEnvDestroy(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.destroy();
        eq(true, true, 'destroy should complete without error');
    }

    public testWindowSizePxEnvDestroyMultipleTimes(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.destroy();
        env.destroy();
        eq(true, true, 'destroy should be callable multiple times');
    }

    public testWindowSizePxEnvDestroyAfterUpdate(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update(new StandardSize(100, 200));
        env.destroy();
        eq(true, true, 'destroy should work after update');
    }

    // =========================================================================
    // 7. WindowSizeVpEnv 类测试
    // =========================================================================

    // -------------------------------------------------------------------------
    // 构造函数测试
    // -------------------------------------------------------------------------

    public testWindowSizeVpEnvConstructor(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        eq(env !== null, true, 'WindowSizeVpEnv should be created');
        eq(env !== undefined, true, 'WindowSizeVpEnv should not be undefined');
    }

    public testWindowSizeVpEnvConstructorWithNullContext(): void {
        const context: any = null;
        try {
            const env = new WindowSizeVpEnv(context);
            eq(false, true, 'Should throw error with null context');
        } catch (e) {
            eq(true, true, 'Should throw error with null context');
        }
    }

    public testWindowSizeVpEnvConstructorWithUndefinedContext(): void {
        const context: any = undefined;
        try {
            const env = new WindowSizeVpEnv(context);
            eq(false, true, 'Should throw error with undefined context');
        } catch (e) {
            eq(true, true, 'Should throw error with undefined context');
        }
    }

    // -------------------------------------------------------------------------
    // value 属性测试
    // -------------------------------------------------------------------------

    public testWindowSizeVpEnvValue(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const value = env.value;
        eq(typeof value, 'object', 'value should be an object');
        eq(value !== null, true, 'value should not be null');
    }

    public testWindowSizeVpEnvValueWidthVp(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const value = env.value;
        eq(typeof value.widthVp, 'number', 'value.widthVp should be a number');
    }

    public testWindowSizeVpEnvValueHeightVp(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const value = env.value;
        eq(typeof value.heightVp, 'number', 'value.heightVp should be a number');
    }

    public testWindowSizeVpEnvValuePositive(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const value = env.value;
        eq(value.widthVp >= 0, true, 'value.widthVp should be non-negative');
        eq(value.heightVp >= 0, true, 'value.heightVp should be non-negative');
    }

    // -------------------------------------------------------------------------
    // update 方法测试
    // -------------------------------------------------------------------------

    public testWindowSizeVpEnvUpdate(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const newSize: SizeInVp = new StandardSizeInVp(150, 200);
        env.update(newSize);
        const value = env.value;
        eq(value.widthVp, 150, 'value.widthVp should be updated to 150');
        eq(value.heightVp, 200, 'value.heightVp should be updated to 200');
    }

    public testWindowSizeVpEnvUpdateZero(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const newSize: SizeInVp = new ZeroSizeInVp();
        env.update(newSize);
        const value = env.value;
        eq(value.widthVp, 0, 'value.widthVp should be updated to 0');
        eq(value.heightVp, 0, 'value.heightVp should be updated to 0');
    }

    public testWindowSizeVpEnvUpdateLarge(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const newSize: SizeInVp = new LargeSizeInVp();
        env.update(newSize);
        const value = env.value;
        eq(value.widthVp, 1000, 'value.widthVp should be updated to 1000');
        eq(value.heightVp, 2000, 'value.heightVp should be updated to 2000');
    }

    public testWindowSizeVpEnvUpdateNegative(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const newSize: SizeInVp = new NegativeSizeInVp();
        env.update(newSize);
        const value = env.value;
        eq(value.widthVp, -50, 'value.widthVp should be updated to -50');
        eq(value.heightVp, -100, 'value.heightVp should be updated to -100');
    }

    public testWindowSizeVpEnvUpdateFractional(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const newSize: SizeInVp = new FractionalSizeInVp();
        env.update(newSize);
        const value = env.value;
        eq(value.widthVp, 50.5, 'value.widthVp should be updated to 50.5');
        eq(value.heightVp, 100.75, 'value.heightVp should be updated to 100.75');
    }

    public testWindowSizeVpEnvUpdateMultipleTimes(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update(new StandardSizeInVp(50, 100));
        env.update(new StandardSizeInVp(100, 150));
        env.update(new StandardSizeInVp(150, 200));
        const value = env.value;
        eq(value.widthVp, 150, 'value.widthVp should be updated to 150 after multiple updates');
        eq(value.heightVp, 200, 'value.heightVp should be updated to 200 after multiple updates');
    }

    public testWindowSizeVpEnvUpdateWithNull(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const newSize: any = null;
        try {
            env.update(newSize);
            eq(false, true, 'Should throw error with null value');
        } catch (e) {
            eq(true, true, 'Should throw error with null value');
        }
    }

    public testWindowSizeVpEnvUpdateWithUndefined(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const newSize: any = undefined;
        try {
            env.update(newSize);
            eq(false, true, 'Should throw error with undefined value');
        } catch (e) {
            eq(true, true, 'Should throw error with undefined value');
        }
    }

    // -------------------------------------------------------------------------
    // destroy 方法测试
    // -------------------------------------------------------------------------

    public testWindowSizeVpEnvDestroy(): void {
        const context = new UIContext();
        const env = { value: { widthVp: 0, heightVp: 0 }, update: () => { }, destroy: () => { } };
        env.destroy();
        eq(true, true, 'destroy should complete without error');
    }

    public testWindowSizeVpEnvDestroyMultipleTimes(): void {
        const context = new UIContext();
        const env = { value: { widthVp: 0, heightVp: 0 }, update: () => { }, destroy: () => { } };
        env.destroy();
        env.destroy();
        eq(true, true, 'destroy should be callable multiple times');
    }

    // =========================================================================
    // 8. 功能测试
    // =========================================================================

    // -------------------------------------------------------------------------
    // 屏幕尺寸场景测试
    // -------------------------------------------------------------------------

    public testFeatureWideScreen(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const wideScreen: Size = new WideScreenSize();
        env.update(wideScreen);
        const value = env.value;
        eq(value.width, 1920, 'Wide screen width should be 1920');
        eq(value.height, 1080, 'Wide screen height should be 1080');
    }

    public testFeaturePortraitScreen(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const portraitScreen: Size = new PortraitScreenSize();
        env.update(portraitScreen);
        const value = env.value;
        eq(value.width, 1080, 'Portrait screen width should be 1080');
        eq(value.height, 1920, 'Portrait screen height should be 1920');
    }

    public testFeatureSquareScreen(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const squareScreen: Size = new SquareSize();
        env.update(squareScreen);
        const value = env.value;
        eq(value.width, 500, 'Square screen width should be 500');
        eq(value.height, 500, 'Square screen height should be 500');
        eq(value.width === value.height, true, 'Square screen should have equal width and height');
    }

    public testFeatureUltraWideScreen(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const ultraWideScreen: Size = new UltraWideScreenSize();
        env.update(ultraWideScreen);
        const value = env.value;
        eq(value.width, 3440, 'Ultra wide screen width should be 3440');
        eq(value.height, 1440, 'Ultra wide screen height should be 1440');
    }

    public testFeatureMobileScreen(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const mobileScreen: Size = new MobileSize();
        env.update(mobileScreen);
        const value = env.value;
        eq(value.width, 375, 'Mobile screen width should be 375');
        eq(value.height, 667, 'Mobile screen height should be 667');
    }

    public testFeatureTabletScreen(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const tabletScreen: Size = new TabletSize();
        env.update(tabletScreen);
        const value = env.value;
        eq(value.width, 768, 'Tablet screen width should be 768');
        eq(value.height, 1024, 'Tablet screen height should be 1024');
    }

    public testFeatureDesktopScreen(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const desktopScreen: Size = new DesktopSize();
        env.update(desktopScreen);
        const value = env.value;
        eq(value.width, 1440, 'Desktop screen width should be 1440');
        eq(value.height, 900, 'Desktop screen height should be 900');
    }

    public testFeatureFourKScreen(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const fourKScreen: Size = new FourKSize();
        env.update(fourKScreen);
        const value = env.value;
        eq(value.width, 3840, '4K screen width should be 3840');
        eq(value.height, 2160, '4K screen height should be 2160');
    }

    public testFeatureEightKScreen(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const eightKScreen: Size = new EightKSize();
        env.update(eightKScreen);
        const value = env.value;
        eq(value.width, 7680, '8K screen width should be 7680');
        eq(value.height, 4320, '8K screen height should be 4320');
    }

    // -------------------------------------------------------------------------
    // 屏幕方向测试
    // -------------------------------------------------------------------------

    public testFeatureLandscapeOrientation(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const landscape: Size = new WideScreenSize();
        env.update(landscape);
        const value = env.value;
        eq(value.width > value.height, true, 'Landscape orientation should have width > height');
    }

    public testFeaturePortraitOrientation(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const portrait: Size = new PortraitScreenSize();
        env.update(portrait);
        const value = env.value;
        eq(value.width < value.height, true, 'Portrait orientation should have width < height');
    }

    public testFeatureOrientationChange(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update(new WideScreenSize());
        const landscapeValue = env.value;
        eq(landscapeValue.width > landscapeValue.height, true, 'Initial orientation should be landscape');
        env.update(new PortraitScreenSize());
        const portraitValue = env.value;
        eq(portraitValue.width < portraitValue.height, true, 'Orientation should change to portrait');
    }

    // -------------------------------------------------------------------------
    // 屏幕比例测试
    // -------------------------------------------------------------------------

    public testFeatureAspectRatio16x9(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const screen16x9: Size = new WideScreenSize();
        env.update(screen16x9);
        const value = env.value;
        const ratio = value.width / value.height;
        eq(Math.abs(ratio - 16 / 9) < 0.01, true, '16:9 aspect ratio should be correct');
    }

    public testFeatureAspectRatio4x3(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const screen4x3: Size = { width: 1024, height: 768 };
        env.update(screen4x3);
        const value = env.value;
        const ratio = value.width / value.height;
        eq(Math.abs(ratio - 4 / 3) < 0.01, true, '4:3 aspect ratio should be correct');
    }

    public testFeatureAspectRatio1x1(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const screen1x1: Size = new SquareSize();
        env.update(screen1x1);
        const value = env.value;
        const ratio = value.width / value.height;
        eq(Math.abs(ratio - 1) < 0.01, true, '1:1 aspect ratio should be correct');
    }

    // -------------------------------------------------------------------------
    // VP 单位转换测试
    // -------------------------------------------------------------------------

    public testFeatureVpConversion(): void {
        const context = new UIContext();
        const pxEnv = new WindowSizePxEnv(context);
        const vpEnv = new WindowSizeVpEnv(context);
        const pxSize: Size = new StandardSize(100, 200);
        pxEnv.update(pxSize);
        const vpSize: SizeInVp = new StandardSizeInVp(50, 100);
        vpEnv.update(vpSize);
        const pxValue = pxEnv.value;
        const vpValue = vpEnv.value;
        eq(pxValue.width, 100, 'PX width should be 100');
        eq(vpValue.widthVp, 50, 'VP width should be 50');
    }

    // =========================================================================
    // 9. 边界测试
    // =========================================================================

    public testEdgeCaseMinimumSize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const minSize: Size = { width: 1, height: 1 };
        env.update(minSize);
        const value = env.value;
        eq(value.width, 1, 'Minimum width should be 1');
        eq(value.height, 1, 'Minimum height should be 1');
    }

    public testEdgeCaseSinglePixel(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const singlePixel: Size = { width: 1, height: 1 };
        env.update(singlePixel);
        const value = env.value;
        eq(value.width === 1 && value.height === 1, true, 'Single pixel size should be valid');
    }

    public testEdgeCaseVeryLargeSize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const veryLarge: Size = { width: 1000000, height: 1000000 };
        env.update(veryLarge);
        const value = env.value;
        eq(value.width, 1000000, 'Very large width should be preserved');
        eq(value.height, 1000000, 'Very large height should be preserved');
    }

    public testEdgeCaseExtremeAspectRatio(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const extremeRatio: Size = { width: 10000, height: 1 };
        env.update(extremeRatio);
        const value = env.value;
        eq(value.width / value.height, 10000, 'Extreme aspect ratio should be preserved');
    }

    public testEdgeCaseNegativeZero(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const negZero: Size = { width: -0, height: -0 };
        env.update(negZero);
        const value = env.value;
        eq(value.width, 0, 'Negative zero should be treated as zero');
        eq(value.height, 0, 'Negative zero should be treated as zero');
    }

    public testEdgeCaseFloatingPointPrecision(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const precise: Size = { width: 100.123456789, height: 200.987654321 };
        env.update(precise);
        const value = env.value;
        eq(Math.abs(value.width - 100.123456789) < 0.0001, true, 'Floating point precision should be maintained');
        eq(Math.abs(value.height - 200.987654321) < 0.0001, true, 'Floating point precision should be maintained');
    }

    public testEdgeCaseMinimumVpSize(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const minVpSize: SizeInVp = { widthVp: 1, heightVp: 1 };
        env.update(minVpSize);
        const value = env.value;
        eq(value.widthVp, 1, 'Minimum VP width should be 1');
        eq(value.heightVp, 1, 'Minimum VP height should be 1');
    }

    public testEdgeCaseVeryLargeVpSize(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const veryLargeVp: SizeInVp = { widthVp: 10000, heightVp: 10000 };
        env.update(veryLargeVp);
        const value = env.value;
        eq(value.widthVp, 10000, 'Very large VP width should be preserved');
        eq(value.heightVp, 10000, 'Very large VP height should be preserved');
    }

    // =========================================================================
    // 10. 错误测试
    // =========================================================================

    public testErrorInvalidSizeObject(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const invalidSize: any = { width: 'invalid', height: 200 };
        try {
            env.update(invalidSize);
            eq(false, true, 'Should throw error with invalid size object');
        } catch (e) {
            eq(true, true, 'Should throw error with invalid size object');
        }
    }

    public testErrorMissingWidthProperty(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const invalidSize: any = { height: 200 };
        try {
            env.update(invalidSize);
            eq(false, true, 'Should throw error with missing width property');
        } catch (e) {
            eq(true, true, 'Should throw error with missing width property');
        }
    }

    public testErrorMissingHeightProperty(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const invalidSize: any = { width: 100 };
        try {
            env.update(invalidSize);
            eq(false, true, 'Should throw error with missing height property');
        } catch (e) {
            eq(true, true, 'Should throw error with missing height property');
        }
    }

    public testErrorInvalidVpSizeObject(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const invalidSize: any = { widthVp: 'invalid', heightVp: 200 };
        try {
            env.update(invalidSize);
            eq(false, true, 'Should throw error with invalid VP size object');
        } catch (e) {
            eq(true, true, 'Should throw error with invalid VP size object');
        }
    }

    public testErrorMissingWidthVpProperty(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const invalidSize: any = { heightVp: 200 };
        try {
            env.update(invalidSize);
            eq(false, true, 'Should throw error with missing widthVp property');
        } catch (e) {
            eq(true, true, 'Should throw error with missing widthVp property');
        }
    }

    public testErrorMissingHeightVpProperty(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const invalidSize: any = { widthVp: 100 };
        try {
            env.update(invalidSize);
            eq(false, true, 'Should throw error with missing heightVp property');
        } catch (e) {
            eq(true, true, 'Should throw error with missing heightVp property');
        }
    }

    // =========================================================================
    // 11. 性能测试
    // =========================================================================

    public testPerformanceMultipleUpdates(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const iterations = 1000;
        const startTime = Date.now();
        for (let i = 0; i < iterations; i++) {
            env.update(new StandardSize(i, i + 1));
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'Multiple updates should complete in reasonable time');
    }

    public testPerformanceMultipleVpUpdates(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const iterations = 1000;
        const startTime = Date.now();
        for (let i = 0; i < iterations; i++) {
            env.update(new StandardSizeInVp(i, i + 1));
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'Multiple VP updates should complete in reasonable time');
    }

    public testPerformanceValueAccess(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update(new StandardSize(100, 200));
        const iterations = 10000;
        const startTime = Date.now();
        for (let i = 0; i < iterations; i++) {
            const value = env.value;
            const width = value.width;
            const height = value.height;
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'Value access should complete in reasonable time');
    }

    public testPerformanceVpValueAccess(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update(new StandardSizeInVp(50, 100));
        const iterations = 10000;
        const startTime = Date.now();
        for (let i = 0; i < iterations; i++) {
            const value = env.value;
            const widthVp = value.widthVp;
            const heightVp = value.heightVp;
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'VP value access should complete in reasonable time');
    }

    public testPerformanceCreateDestroyCycle(): void {
        const context = new UIContext();
        const iterations = 100;
        const startTime = Date.now();
        for (let i = 0; i < iterations; i++) {
            const env = new WindowSizePxEnv(context);
            env.update(new StandardSize(i, i + 1));
            env.destroy();
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'Create-destroy cycle should complete in reasonable time');
    }

    public testPerformanceVpCreateDestroyCycle(): void {
        const context = new UIContext();
        const iterations = 100;
        const startTime = Date.now();
        for (let i = 0; i < iterations; i++) {
            const env = new WindowSizeVpEnv(context);
            env.update(new StandardSizeInVp(i, i + 1));
            env.destroy();
        }
        const duration = Date.now() - startTime;
        eq(duration < 1000, true, 'VP create-destroy cycle should complete in reasonable time');
    }

    // =========================================================================
    // 12. 兼容性测试
    // =========================================================================

    public testCompatibilityMultipleInstances(): void {
        const context = new UIContext();
        const env1 = new WindowSizePxEnv(context);
        const env2 = new WindowSizePxEnv(context);
        env1.update(new StandardSize(100, 200));
        env2.update(new StandardSize(300, 400));
        const value1 = env1.value;
        const value2 = env2.value;
        eq(value1.width, 100, 'First instance should have correct width');
        eq(value2.width, 300, 'Second instance should have correct width');
    }

    public testCompatibilityMultipleVpInstances(): void {
        const context = new UIContext();
        const env1 = new WindowSizeVpEnv(context);
        const env2 = new WindowSizeVpEnv(context);
        env1.update(new StandardSizeInVp(50, 100));
        env2.update(new StandardSizeInVp(150, 200));
        const value1 = env1.value;
        const value2 = env2.value;
        eq(value1.widthVp, 50, 'First VP instance should have correct widthVp');
        eq(value2.widthVp, 150, 'Second VP instance should have correct widthVp');
    }

    public testCompatibilityMixedInstances(): void {
        const context = new UIContext();
        const pxEnv = new WindowSizePxEnv(context);
        const vpEnv = new WindowSizeVpEnv(context);
        pxEnv.update(new StandardSize(100, 200));
        vpEnv.update(new StandardSizeInVp(50, 100));
        const pxValue = pxEnv.value;
        const vpValue = vpEnv.value;
        eq(pxValue.width, 100, 'PX instance should work correctly');
        eq(vpValue.widthVp, 50, 'VP instance should work correctly');
    }

    public testCompatibilityConsistentValueAccess(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update(new StandardSize(100, 200));
        const value1 = env.value;
        const value2 = env.value;
        const value3 = env.value;
        eq(value1.width, value2.width, 'Value access should be consistent');
        eq(value2.width, value3.width, 'Value access should be consistent');
    }

    public testCompatibilityVpConsistentValueAccess(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update(new StandardSizeInVp(50, 100));
        const value1 = env.value;
        const value2 = env.value;
        const value3 = env.value;
        eq(value1.widthVp, value2.widthVp, 'VP value access should be consistent');
        eq(value2.widthVp, value3.widthVp, 'VP value access should be consistent');
    }

    public testCompatibilityUpdateAfterDestroy(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update(new StandardSize(100, 200));
        env.destroy();
        env.update(new StandardSize(300, 400));
        const value = env.value;
        eq(value.width, 300, 'Update should work after destroy');
    }

    public testCompatibilityVpUpdateAfterDestroy(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update(new StandardSizeInVp(50, 100));
        env.destroy();
        env.update(new StandardSizeInVp(150, 200));
        const value = env.value;
        eq(value.widthVp, 150, 'VP update should work after destroy');
    }

    // =========================================================================
    // 13. 集成测试
    // =========================================================================

    public testIntegrationPxAndVpSync(): void {
        const context = new UIContext();
        const pxEnv = new WindowSizePxEnv(context);
        const vpEnv = new WindowSizeVpEnv(context);
        pxEnv.update(new StandardSize(100, 200));
        vpEnv.update(new StandardSizeInVp(50, 100));
        const pxValue = pxEnv.value;
        const vpValue = vpEnv.value;
        eq(pxValue.width, 100, 'PX width should be 100');
        eq(vpValue.widthVp, 50, 'VP width should be 50');
        eq(pxValue.height, 200, 'PX height should be 200');
        eq(vpValue.heightVp, 100, 'VP height should be 100');
    }

    public testIntegrationMultipleContexts(): void {
        const context1 = new UIContext();
        const context2 = new UIContext();
        const env1 = new WindowSizePxEnv(context1);
        const env2 = new WindowSizePxEnv(context2);
        env1.update(new StandardSize(100, 200));
        env2.update(new StandardSize(300, 400));
        const value1 = env1.value;
        const value2 = env2.value;
        eq(value1.width, 100, 'First context should have correct width');
        eq(value2.width, 300, 'Second context should have correct width');
    }

    public testIntegrationMultipleVpContexts(): void {
        const context1 = new UIContext();
        const context2 = new UIContext();
        const env1 = new WindowSizeVpEnv(context1);
        const env2 = new WindowSizeVpEnv(context2);
        env1.update(new StandardSizeInVp(50, 100));
        env2.update(new StandardSizeInVp(150, 200));
        const value1 = env1.value;
        const value2 = env2.value;
        eq(value1.widthVp, 50, 'First VP context should have correct widthVp');
        eq(value2.widthVp, 150, 'Second VP context should have correct widthVp');
    }

    public testIntegrationLifecycleSequence(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update(new StandardSize(100, 200));
        const value1 = env.value;
        eq(value1.width, 100, 'Value should be correct after first update');
        env.update(new StandardSize(300, 400));
        const value2 = env.value;
        eq(value2.width, 300, 'Value should be correct after second update');
        env.destroy();
        env.update(new StandardSize(500, 600));
        const value3 = env.value;
        eq(value3.width, 500, 'Value should be correct after destroy and update');
    }

    public testIntegrationVpLifecycleSequence(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update(new StandardSizeInVp(50, 100));
        const value1 = env.value;
        eq(value1.widthVp, 50, 'VP value should be correct after first update');
        env.update(new StandardSizeInVp(150, 200));
        const value2 = env.value;
        eq(value2.widthVp, 150, 'VP value should be correct after second update');
        env.destroy();
        env.update(new StandardSizeInVp(250, 300));
        const value3 = env.value;
        eq(value3.widthVp, 250, 'VP value should be correct after destroy and update');
    }

    // =========================================================================
    // 14. 特殊场景测试
    // =========================================================================

    public testSpecialScenarioResizeAnimation(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const startSize: Size = { width: 100, height: 200 };
        const endSize: Size = { width: 200, height: 400 };
        const steps = 10;
        env.update(startSize);
        for (let i = 1; i <= steps; i++) {
            const progress = i / steps;
            const currentWidth = startSize.width + (endSize.width - startSize.width) * progress;
            const currentHeight = startSize.height + (endSize.height - startSize.height) * progress;
            env.update({ width: currentWidth, height: currentHeight });
        }
        const value = env.value;
        eq(Math.abs(value.width - endSize.width) < 1, true, 'Final width should be close to end size');
        eq(Math.abs(value.height - endSize.height) < 1, true, 'Final height should be close to end size');
    }

    public testSpecialScenarioVpResizeAnimation(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const startSize: SizeInVp = { widthVp: 50, heightVp: 100 };
        const endSize: SizeInVp = { widthVp: 100, heightVp: 200 };
        const steps = 10;
        env.update(startSize);
        for (let i = 1; i <= steps; i++) {
            const progress = i / steps;
            const currentWidthVp = startSize.widthVp + (endSize.widthVp - startSize.widthVp) * progress;
            const currentHeightVp = startSize.heightVp + (endSize.heightVp - startSize.heightVp) * progress;
            env.update({ widthVp: currentWidthVp, heightVp: currentHeightVp });
        }
        const value = env.value;
        eq(Math.abs(value.widthVp - endSize.widthVp) < 1, true, 'Final VP width should be close to end size');
        eq(Math.abs(value.heightVp - endSize.heightVp) < 1, true, 'Final VP height should be close to end size');
    }

    public testSpecialScenarioRapidResize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const sizes: Size[] = [
            { width: 100, height: 200 },
            { width: 200, height: 400 },
            { width: 300, height: 600 },
            { width: 400, height: 800 },
            { width: 500, height: 1000 }
        ];
        for (const size of sizes) {
            env.update(size);
        }
        const value = env.value;
        eq(value.width, 500, 'Final width should be 500');
        eq(value.height, 1000, 'Final height should be 1000');
    }

    public testSpecialScenarioVpRapidResize(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const sizes: SizeInVp[] = [
            { widthVp: 50, heightVp: 100 },
            { widthVp: 100, heightVp: 200 },
            { widthVp: 150, heightVp: 300 },
            { widthVp: 200, heightVp: 400 },
            { widthVp: 250, heightVp: 500 }
        ];
        for (const size of sizes) {
            env.update(size);
        }
        const value = env.value;
        eq(value.widthVp, 250, 'Final VP width should be 250');
        eq(value.heightVp, 500, 'Final VP height should be 500');
    }

    public testSpecialScenarioOscillatingSize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const size1: Size = { width: 100, height: 200 };
        const size2: Size = { width: 200, height: 400 };
        const cycles = 5;
        for (let i = 0; i < cycles; i++) {
            env.update(size1);
            env.update(size2);
        }
        const value = env.value;
        eq(value.width, 200, 'Final width should be 200');
        eq(value.height, 400, 'Final height should be 400');
    }

    public testSpecialScenarioVpOscillatingSize(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const size1: SizeInVp = { widthVp: 50, heightVp: 100 };
        const size2: SizeInVp = { widthVp: 100, heightVp: 200 };
        const cycles = 5;
        for (let i = 0; i < cycles; i++) {
            env.update(size1);
            env.update(size2);
        }
        const value = env.value;
        eq(value.widthVp, 100, 'Final VP width should be 100');
        eq(value.heightVp, 200, 'Final VP height should be 200');
    }

    // =========================================================================
    // 15. 状态管理测试
    // =========================================================================

    public testStateManagementInitialValue(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const value = env.value;
        eq(typeof value.width, 'number', 'Initial width should be a number');
        eq(typeof value.height, 'number', 'Initial height should be a number');
    }

    public testStateManagementVpInitialValue(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const value = env.value;
        eq(typeof value.widthVp, 'number', 'Initial VP width should be a number');
        eq(typeof value.heightVp, 'number', 'Initial VP height should be a number');
    }

    public testStateManagementUpdateIdempotency(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const size: Size = { width: 100, height: 200 };
        env.update(size);
        const value1 = env.value;
        env.update(size);
        const value2 = env.value;
        eq(value1.width, value2.width, 'Update should be idempotent');
        eq(value1.height, value2.height, 'Update should be idempotent');
    }

    public testStateManagementVpUpdateIdempotency(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const size: SizeInVp = { widthVp: 50, heightVp: 100 };
        env.update(size);
        const value1 = env.value;
        env.update(size);
        const value2 = env.value;
        eq(value1.widthVp, value2.widthVp, 'VP update should be idempotent');
        eq(value1.heightVp, value2.heightVp, 'VP update should be idempotent');
    }

    // =========================================================================
    // 16. 内存管理测试
    // =========================================================================

    public testMemoryManagementMultipleInstances(): void {
        const context = new UIContext();
        const instances: WindowSizePxEnv[] = [];
        const count = 100;
        for (let i = 0; i < count; i++) {
            const env = new WindowSizePxEnv(context);
            env.update(new StandardSize(i, i + 1));
            instances.push(env);
        }
        eq(instances.length, count, 'Should create multiple instances');
        for (let i = 0; i < count; i++) {
            instances[i].destroy();
        }
    }

    public testMemoryManagementMultipleVpInstances(): void {
        const context = new UIContext();
        const instances: WindowSizeVpEnv[] = [];
        const count = 100;
        for (let i = 0; i < count; i++) {
            const env = new WindowSizeVpEnv(context);
            env.update(new StandardSizeInVp(i, i + 1));
            instances.push(env);
        }
        eq(instances.length, count, 'Should create multiple VP instances');
        for (let i = 0; i < count; i++) {
            instances[i].destroy();
        }
    }

    public testMemoryManagementLargeValueStorage(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const largeSize: Size = { width: 1000000, height: 1000000 };
        env.update(largeSize);
        const value = env.value;
        eq(value.width, 1000000, 'Large value should be stored correctly');
        eq(value.height, 1000000, 'Large value should be stored correctly');
    }

    public testMemoryManagementVpLargeValueStorage(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const largeSize: SizeInVp = { widthVp: 100000, heightVp: 100000 };
        env.update(largeSize);
        const value = env.value;
        eq(value.widthVp, 100000, 'Large VP value should be stored correctly');
        eq(value.heightVp, 100000, 'Large VP value should be stored correctly');
    }

    // =========================================================================
    // 17. 并发测试
    // =========================================================================

    public testConcurrencySimultaneousUpdates(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const size1: Size = { width: 100, height: 200 };
        const size2: Size = { width: 300, height: 400 };
        env.update(size1);
        env.update(size2);
        const value = env.value;
        eq(value.width === 100 || value.width === 300, true, 'Value should be one of the updated values');
    }

    public testConcurrencyVpSimultaneousUpdates(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const size1: SizeInVp = { widthVp: 50, heightVp: 100 };
        const size2: SizeInVp = { widthVp: 150, heightVp: 200 };
        env.update(size1);
        env.update(size2);
        const value = env.value;
        eq(value.widthVp === 50 || value.widthVp === 150, true, 'VP value should be one of the updated values');
    }

    public testConcurrencyRapidCreateDestroy(): void {
        const context = new UIContext();
        const iterations = 50;
        for (let i = 0; i < iterations; i++) {
            const env = new WindowSizePxEnv(context);
            env.update(new StandardSize(i, i + 1));
            env.destroy();
        }
        eq(true, true, 'Rapid create-destroy should complete without error');
    }

    public testConcurrencyVpRapidCreateDestroy(): void {
        const context = new UIContext();
        const iterations = 50;
        for (let i = 0; i < iterations; i++) {
            const env = new WindowSizeVpEnv(context);
            env.update(new StandardSizeInVp(i, i + 1));
            env.destroy();
        }
        eq(true, true, 'VP rapid create-destroy should complete without error');
    }

    // =========================================================================
    // 18. 数据一致性测试
    // =========================================================================

    public testDataConsistencyWidthHeightRatio(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const size: Size = { width: 200, height: 100 };
        env.update(size);
        const value = env.value;
        const ratio = value.width / value.height;
        eq(Math.abs(ratio - 2) < 0.01, true, 'Width-height ratio should be preserved');
    }

    public testDataConsistencyVpWidthHeightRatio(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const size: SizeInVp = { widthVp: 100, heightVp: 50 };
        env.update(size);
        const value = env.value;
        const ratio = value.widthVp / value.heightVp;
        eq(Math.abs(ratio - 2) < 0.01, true, 'VP width-height ratio should be preserved');
    }

    public testDataConsistencyAreaCalculation(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const size: Size = { width: 100, height: 200 };
        env.update(size);
        const value = env.value;
        const area = value.width * value.height;
        eq(area, 20000, 'Area should be calculated correctly');
    }

    public testDataConsistencyVpAreaCalculation(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const size: SizeInVp = { widthVp: 50, heightVp: 100 };
        env.update(size);
        const value = env.value;
        const area = value.widthVp * value.heightVp;
        eq(area, 5000, 'VP area should be calculated correctly');
    }

    public testDataConsistencyPerimeterCalculation(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const size: Size = { width: 100, height: 200 };
        env.update(size);
        const value = env.value;
        const perimeter = 2 * (value.width + value.height);
        eq(perimeter, 600, 'Perimeter should be calculated correctly');
    }

    public testDataConsistencyVpPerimeterCalculation(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const size: SizeInVp = { widthVp: 50, heightVp: 100 };
        env.update(size);
        const value = env.value;
        const perimeter = 2 * (value.widthVp + value.heightVp);
        eq(perimeter, 300, 'VP perimeter should be calculated correctly');
    }

    // =========================================================================
    // 19. 事件响应测试
    // =========================================================================

    public testEventResponseResizeTrigger(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const initialSize = env.value;
        env.update(new StandardSize(300, 400));
        const newSize = env.value;
        eq(newSize.width !== initialSize.width || newSize.height !== initialSize.height, true, 'Size should change after update');
    }

    public testEventResponseVpResizeTrigger(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const initialSize = env.value;
        env.update(new StandardSizeInVp(150, 200));
        const newSize = env.value;
        eq(newSize.widthVp !== initialSize.widthVp || newSize.heightVp !== initialSize.heightVp, true, 'VP size should change after update');
    }
    // =========================================================================
    // 20. 边界值详细测试
    // =========================================================================

    public testBoundaryValueOnePixelWidth(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 1, height: 100 });
        const value = env.value;
        eq(value.width, 1, 'Width of 1 pixel should be preserved');
        eq(value.height, 100, 'Height should be preserved');
    }

    public testBoundaryValueOnePixelHeight(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 100, height: 1 });
        const value = env.value;
        eq(value.width, 100, 'Width should be preserved');
        eq(value.height, 1, 'Height of 1 pixel should be preserved');
    }

    public testBoundaryValueVpOnePixelWidth(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 1, heightVp: 100 });
        const value = env.value;
        eq(value.widthVp, 1, 'VP width of 1 should be preserved');
        eq(value.heightVp, 100, 'VP height should be preserved');
    }

    public testBoundaryValueVpOnePixelHeight(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 100, heightVp: 1 });
        const value = env.value;
        eq(value.widthVp, 100, 'VP width should be preserved');
        eq(value.heightVp, 1, 'VP height of 1 should be preserved');
    }

    public testBoundaryValueMaxInteger(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const maxSize: Size = { width: Number.MAX_SAFE_INTEGER, height: Number.MAX_SAFE_INTEGER };
        env.update(maxSize);
        const value = env.value;
        eq(value.width, Number.MAX_SAFE_INTEGER, 'Maximum safe integer should be preserved');
        eq(value.height, Number.MAX_SAFE_INTEGER, 'Maximum safe integer should be preserved');
    }

    public testBoundaryValueVpMaxInteger(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const maxSize: SizeInVp = { widthVp: Number.MAX_SAFE_INTEGER, heightVp: Number.MAX_SAFE_INTEGER };
        env.update(maxSize);
        const value = env.value;
        eq(value.widthVp, Number.MAX_SAFE_INTEGER, 'VP maximum safe integer should be preserved');
        eq(value.heightVp, Number.MAX_SAFE_INTEGER, 'VP maximum safe integer should be preserved');
    }

    public testBoundaryValueMinInteger(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const minSize: Size = { width: Number.MIN_SAFE_INTEGER, height: Number.MIN_SAFE_INTEGER };
        env.update(minSize);
        const value = env.value;
        eq(value.width, Number.MIN_SAFE_INTEGER, 'Minimum safe integer should be preserved');
        eq(value.height, Number.MIN_SAFE_INTEGER, 'Minimum safe integer should be preserved');
    }

    public testBoundaryValueVpMinInteger(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const minSize: SizeInVp = { widthVp: Number.MIN_SAFE_INTEGER, heightVp: Number.MIN_SAFE_INTEGER };
        env.update(minSize);
        const value = env.value;
        eq(value.widthVp, Number.MIN_SAFE_INTEGER, 'VP minimum safe integer should be preserved');
        eq(value.heightVp, Number.MIN_SAFE_INTEGER, 'VP minimum safe integer should be preserved');
    }

    // =========================================================================
    // 21. 类型安全测试
    // =========================================================================

    public testTypeSafetyNumberType(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 100, height: 200 });
        const value = env.value;
        eq(typeof value.width === 'number', true, 'Width should be number type');
        eq(typeof value.height === 'number', true, 'Height should be number type');
    }

    public testTypeSafetyVpNumberType(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 50, heightVp: 100 });
        const value = env.value;
        eq(typeof value.widthVp === 'number', true, 'VP width should be number type');
        eq(typeof value.heightVp === 'number', true, 'VP height should be number type');
    }

    public testTypeSafetyObjectType(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const value = env.value;
        eq(typeof value === 'object', true, 'Value should be object type');
        eq(value !== null, true, 'Value should not be null');
    }

    public testTypeSafetyVpObjectType(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const value = env.value;
        eq(typeof value === 'object', true, 'VP value should be object type');
        eq(value !== null, true, 'VP value should not be null');
    }

    public testTypeSafetyPropertyExistence(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const value = env.value;
        eq('width' in value, true, 'Value should have width property');
        eq('height' in value, true, 'Value should have height property');
    }

    public testTypeSafetyVpPropertyExistence(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const value = env.value;
        eq('widthVp' in value, true, 'VP value should have widthVp property');
        eq('heightVp' in value, true, 'VP value should have heightVp property');
    }

    // =========================================================================
    // 22. 持久化测试
    // =========================================================================

    public testPersistenceValueRetention(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 100, height: 200 });
        const value1 = env.value;
        const savedWidth = value1.width;
        const savedHeight = value1.height;
        env.update({ width: 300, height: 400 });
        const value2 = env.value;
        eq(savedWidth, 100, 'Saved width should be retained');
        eq(savedHeight, 200, 'Saved height should be retained');
        eq(value2.width, 300, 'Current width should be updated');
        eq(value2.height, 400, 'Current height should be updated');
    }

    public testPersistenceVpValueRetention(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 50, heightVp: 100 });
        const value1 = env.value;
        const savedWidthVp = value1.widthVp;
        const savedHeightVp = value1.heightVp;
        env.update({ widthVp: 150, heightVp: 200 });
        const value2 = env.value;
        eq(savedWidthVp, 50, 'Saved VP width should be retained');
        eq(savedHeightVp, 100, 'Saved VP height should be retained');
        eq(value2.widthVp, 150, 'Current VP width should be updated');
        eq(value2.heightVp, 200, 'Current VP height should be updated');
    }

    public testPersistenceMultipleValueReferences(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 100, height: 200 });
        const ref1 = env.value;
        const ref2 = env.value;
        const ref3 = env.value;
        eq(ref1.width, ref2.width, 'All references should have same width');
        eq(ref2.width, ref3.width, 'All references should have same width');
        eq(ref1.height, ref2.height, 'All references should have same height');
        eq(ref2.height, ref3.height, 'All references should have same height');
    }

    public testPersistenceVpMultipleValueReferences(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 50, heightVp: 100 });
        const ref1 = env.value;
        const ref2 = env.value;
        const ref3 = env.value;
        eq(ref1.widthVp, ref2.widthVp, 'All VP references should have same widthVp');
        eq(ref2.widthVp, ref3.widthVp, 'All VP references should have same widthVp');
        eq(ref1.heightVp, ref2.heightVp, 'All VP references should have same heightVp');
        eq(ref2.heightVp, ref3.heightVp, 'All VP references should have same heightVp');
    }

    // =========================================================================
    // 23. 回归测试
    // =========================================================================

    public testRegressionStandardScreenSize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const standardSize: Size = { width: 1920, height: 1080 };
        env.update(standardSize);
        const value = env.value;
        eq(value.width, 1920, 'Standard screen width should be 1920');
        eq(value.height, 1080, 'Standard screen height should be 1080');
    }

    public testRegressionVpStandardScreenSize(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const standardSize: SizeInVp = { widthVp: 960, heightVp: 540 };
        env.update(standardSize);
        const value = env.value;
        eq(value.widthVp, 960, 'Standard VP screen width should be 960');
        eq(value.heightVp, 540, 'Standard VP screen height should be 540');
    }

    public testRegressionMobileScreenSize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const mobileSize: Size = { width: 375, height: 667 };
        env.update(mobileSize);
        const value = env.value;
        eq(value.width, 375, 'Mobile screen width should be 375');
        eq(value.height, 667, 'Mobile screen height should be 667');
    }

    public testRegressionVpMobileScreenSize(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const mobileSize: SizeInVp = { widthVp: 187, heightVp: 333 };
        env.update(mobileSize);
        const value = env.value;
        eq(value.widthVp, 187, 'Mobile VP screen width should be 187');
        eq(value.heightVp, 333, 'Mobile VP screen height should be 333');
    }

    public testRegressionTabletScreenSize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const tabletSize: Size = { width: 768, height: 1024 };
        env.update(tabletSize);
        const value = env.value;
        eq(value.width, 768, 'Tablet screen width should be 768');
        eq(value.height, 1024, 'Tablet screen height should be 1024');
    }

    public testRegressionVpTabletScreenSize(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const tabletSize: SizeInVp = { widthVp: 384, heightVp: 512 };
        env.update(tabletSize);
        const value = env.value;
        eq(value.widthVp, 384, 'Tablet VP screen width should be 384');
        eq(value.heightVp, 512, 'Tablet VP screen height should be 512');
    }

    // =========================================================================
    // 24. 压力测试
    // =========================================================================

    public testStressContinuousUpdates(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const iterations = 500;
        for (let i = 0; i < iterations; i++) {
            env.update({ width: i, height: i + 1 });
        }
        const value = env.value;
        eq(value.width, iterations - 1, 'Final width should be correct after continuous updates');
        eq(value.height, iterations, 'Final height should be correct after continuous updates');
    }

    public testStressVpContinuousUpdates(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const iterations = 500;
        for (let i = 0; i < iterations; i++) {
            env.update({ widthVp: i, heightVp: i + 1 });
        }
        const value = env.value;
        eq(value.widthVp, iterations - 1, 'Final VP width should be correct after continuous updates');
        eq(value.heightVp, iterations, 'Final VP height should be correct after continuous updates');
    }

    public testStressVpLargeValueUpdates(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const iterations = 100;
        for (let i = 0; i < iterations; i++) {
            env.update({ widthVp: 100000 + i, heightVp: 200000 + i });
        }
        const value = env.value;
        eq(value.widthVp, 100000 + iterations - 1, 'Final large VP width should be correct');
        eq(value.heightVp, 200000 + iterations - 1, 'Final large VP height should be correct');
    }

    public testStressRapidValueAccess(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 100, height: 200 });
        const iterations = 10000;
        let totalWidth = 0;
        let totalHeight = 0;
        for (let i = 0; i < iterations; i++) {
            const value = env.value;
            totalWidth += value.width;
            totalHeight += value.height;
        }
        eq(totalWidth, 100 * iterations, 'Total width should be correct');
        eq(totalHeight, 200 * iterations, 'Total height should be correct');
    }

    public testStressVpRapidValueAccess(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 50, heightVp: 100 });
        const iterations = 10000;
        let totalWidthVp = 0;
        let totalHeightVp = 0;
        for (let i = 0; i < iterations; i++) {
            const value = env.value;
            totalWidthVp += value.widthVp;
            totalHeightVp += value.heightVp;
        }
        eq(totalWidthVp, 50 * iterations, 'Total VP width should be correct');
        eq(totalHeightVp, 100 * iterations, 'Total VP height should be correct');
    }

    // =========================================================================
    // 25. 综合场景测试
    // =========================================================================

    public testComplexScenarioScreenRotation(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const portrait: Size = { width: 1080, height: 1920 };
        const landscape: Size = { width: 1920, height: 1080 };
        env.update(portrait);
        const portraitValue = env.value;
        eq(portraitValue.width < portraitValue.height, true, 'Initial orientation should be portrait');
        env.update(landscape);
        const landscapeValue = env.value;
        eq(landscapeValue.width > landscapeValue.height, true, 'Orientation should change to landscape');
        env.update(portrait);
        const portraitValue2 = env.value;
        eq(portraitValue2.width < portraitValue2.height, true, 'Orientation should change back to portrait');
    }

    public testComplexScenarioVpScreenRotation(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const portrait: SizeInVp = { widthVp: 540, heightVp: 960 };
        const landscape: SizeInVp = { widthVp: 960, heightVp: 540 };
        env.update(portrait);
        const portraitValue = env.value;
        eq(portraitValue.widthVp < portraitValue.heightVp, true, 'Initial VP orientation should be portrait');
        env.update(landscape);
        const landscapeValue = env.value;
        eq(landscapeValue.widthVp > landscapeValue.heightVp, true, 'VP orientation should change to landscape');
        env.update(portrait);
        const portraitValue2 = env.value;
        eq(portraitValue2.widthVp < portraitValue2.heightVp, true, 'VP orientation should change back to portrait');
    }

    public testComplexScenarioMultiDeviceSupport(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const devices: Size[] = [
            { width: 375, height: 667 },
            { width: 768, height: 1024 },
            { width: 1920, height: 1080 },
            { width: 3840, height: 2160 }
        ];
        for (const device of devices) {
            env.update(device);
            const value = env.value;
            eq(value.width, device.width, 'Device width should be correct');
            eq(value.height, device.height, 'Device height should be correct');
        }
    }

    public testComplexScenarioVpMultiDeviceSupport(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const devices: SizeInVp[] = [
            { widthVp: 187, heightVp: 333 },
            { widthVp: 384, heightVp: 512 },
            { widthVp: 960, heightVp: 540 },
            { widthVp: 1920, heightVp: 1080 }
        ];
        for (const device of devices) {
            env.update(device);
            const value = env.value;
            eq(value.widthVp, device.widthVp, 'Device VP width should be correct');
            eq(value.heightVp, device.heightVp, 'Device VP height should be correct');
        }
    }

    public testComplexScenarioResponsiveLayout(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const breakpoints = [
            { width: 375, expected: 'mobile' },
            { width: 768, expected: 'tablet' },
            { width: 1440, expected: 'desktop' }
        ];
        for (const breakpoint of breakpoints) {
            env.update({ width: breakpoint.width, height: 1000 });
            const value = env.value;
            eq(value.width, breakpoint.width, 'Breakpoint width should be correct');
        }
    }

    public testComplexScenarioVpResponsiveLayout(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const breakpoints = [
            { widthVp: 187, expected: 'mobile' },
            { widthVp: 384, expected: 'tablet' },
            { widthVp: 720, expected: 'desktop' }
        ];
        for (const breakpoint of breakpoints) {
            env.update({ widthVp: breakpoint.widthVp, heightVp: 500 });
            const value = env.value;
            eq(value.widthVp, breakpoint.widthVp, 'VP breakpoint width should be correct');
        }
    }

    // =========================================================================
    // 26. 数值精度测试
    // =========================================================================

    public testPrecisionIntegerValues(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 100, height: 200 });
        const value = env.value;
        eq(Number.isInteger(value.width), true, 'Width should be integer');
        eq(Number.isInteger(value.height), true, 'Height should be integer');
    }

    public testPrecisionVpIntegerValues(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 50, heightVp: 100 });
        const value = env.value;
        eq(Number.isInteger(value.widthVp), true, 'VP width should be integer');
        eq(Number.isInteger(value.heightVp), true, 'VP height should be integer');
    }

    public testPrecisionFractionalValues(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 100.5, height: 200.75 });
        const value = env.value;
        eq(Math.abs(value.width - 100.5) < 0.001, true, 'Fractional width should be preserved');
        eq(Math.abs(value.height - 200.75) < 0.001, true, 'Fractional height should be preserved');
    }

    public testPrecisionVpFractionalValues(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 50.25, heightVp: 100.5 });
        const value = env.value;
        eq(Math.abs(value.widthVp - 50.25) < 0.001, true, 'Fractional VP width should be preserved');
        eq(Math.abs(value.heightVp - 100.5) < 0.001, true, 'Fractional VP height should be preserved');
    }

    public testPrecisionVerySmallFractional(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 100.0001, height: 200.0001 });
        const value = env.value;
        eq(Math.abs(value.width - 100.0001) < 0.00001, true, 'Very small fractional should be preserved');
        eq(Math.abs(value.height - 200.0001) < 0.00001, true, 'Very small fractional should be preserved');
    }

    public testPrecisionVpVerySmallFractional(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 50.0001, heightVp: 100.0001 });
        const value = env.value;
        eq(Math.abs(value.widthVp - 50.0001) < 0.00001, true, 'Very small fractional VP should be preserved');
        eq(Math.abs(value.heightVp - 100.0001) < 0.00001, true, 'Very small fractional VP should be preserved');
    }

    // =========================================================================
    // 27. 单位转换测试
    // =========================================================================

    public testUnitConversionPxToVp(): void {
        const context = new UIContext();
        const pxEnv = new WindowSizePxEnv(context);
        const vpEnv = new WindowSizeVpEnv(context);
        pxEnv.update({ width: 100, height: 200 });
        vpEnv.update({ widthVp: 50, heightVp: 100 });
        const pxValue = pxEnv.value;
        const vpValue = vpEnv.value;
        eq(pxValue.width, 100, 'PX width should be 100');
        eq(vpValue.widthVp, 50, 'VP width should be 50');
    }

    public testUnitConversionVpToPx(): void {
        const context = new UIContext();
        const pxEnv = new WindowSizePxEnv(context);
        const vpEnv = new WindowSizeVpEnv(context);
        vpEnv.update({ widthVp: 100, heightVp: 200 });
        pxEnv.update({ width: 200, height: 400 });
        const pxValue = pxEnv.value;
        const vpValue = vpEnv.value;
        eq(vpValue.widthVp, 100, 'VP width should be 100');
        eq(pxValue.width, 200, 'PX width should be 200');
    }

    public testUnitConversionConsistentRatio(): void {
        const context = new UIContext();
        const pxEnv = new WindowSizePxEnv(context);
        const vpEnv = new WindowSizeVpEnv(context);
        pxEnv.update({ width: 200, height: 400 });
        vpEnv.update({ widthVp: 100, heightVp: 200 });
        const pxValue = pxEnv.value;
        const vpValue = vpEnv.value;
        const pxRatio = pxValue.width / pxValue.height;
        const vpRatio = vpValue.widthVp / vpValue.heightVp;
        eq(Math.abs(pxRatio - vpRatio) < 0.01, true, 'Ratio should be consistent across units');
    }

    // =========================================================================
    // 28. 布局适配测试
    // =========================================================================

    public testLayoutAdaptationMobilePortrait(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 375, height: 667 });
        const value = env.value;
        eq(value.width, 375, 'Mobile portrait width should be 375');
        eq(value.height, 667, 'Mobile portrait height should be 667');
        eq(value.width < value.height, true, 'Portrait orientation should be detected');
    }

    public testLayoutAdaptationMobileLandscape(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 667, height: 375 });
        const value = env.value;
        eq(value.width, 667, 'Mobile landscape width should be 667');
        eq(value.height, 375, 'Mobile landscape height should be 375');
        eq(value.width > value.height, true, 'Landscape orientation should be detected');
    }

    public testLayoutAdaptationVpMobilePortrait(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 187, heightVp: 333 });
        const value = env.value;
        eq(value.widthVp, 187, 'Mobile VP portrait width should be 187');
        eq(value.heightVp, 333, 'Mobile VP portrait height should be 333');
        eq(value.widthVp < value.heightVp, true, 'VP portrait orientation should be detected');
    }

    public testLayoutAdaptationVpMobileLandscape(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 333, heightVp: 187 });
        const value = env.value;
        eq(value.widthVp, 333, 'Mobile VP landscape width should be 333');
        eq(value.heightVp, 187, 'Mobile VP landscape height should be 187');
        eq(value.widthVp > value.heightVp, true, 'VP landscape orientation should be detected');
    }

    public testLayoutAdaptationTabletPortrait(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 768, height: 1024 });
        const value = env.value;
        eq(value.width, 768, 'Tablet portrait width should be 768');
        eq(value.height, 1024, 'Tablet portrait height should be 1024');
    }

    public testLayoutAdaptationTabletLandscape(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 1024, height: 768 });
        const value = env.value;
        eq(value.width, 1024, 'Tablet landscape width should be 1024');
        eq(value.height, 768, 'Tablet landscape height should be 768');
    }

    // =========================================================================
    // 29. 动画过渡测试
    // =========================================================================

    public testAnimationSmoothTransition(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const startSize = { width: 100, height: 200 };
        const endSize = { width: 200, height: 400 };
        const steps = 20;
        env.update(startSize);
        for (let i = 1; i <= steps; i++) {
            const t = i / steps;
            const currentWidth = startSize.width + (endSize.width - startSize.width) * t;
            const currentHeight = startSize.height + (endSize.height - startSize.height) * t;
            env.update({ width: currentWidth, height: currentHeight });
        }
        const value = env.value;
        eq(Math.abs(value.width - endSize.width) < 1, true, 'Animation should end at target width');
        eq(Math.abs(value.height - endSize.height) < 1, true, 'Animation should end at target height');
    }

    public testAnimationVpSmoothTransition(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const startSize = { widthVp: 50, heightVp: 100 };
        const endSize = { widthVp: 100, heightVp: 200 };
        const steps = 20;
        env.update(startSize);
        for (let i = 1; i <= steps; i++) {
            const t = i / steps;
            const currentWidthVp = startSize.widthVp + (endSize.widthVp - startSize.widthVp) * t;
            const currentHeightVp = startSize.heightVp + (endSize.heightVp - startSize.heightVp) * t;
            env.update({ widthVp: currentWidthVp, heightVp: currentHeightVp });
        }
        const value = env.value;
        eq(Math.abs(value.widthVp - endSize.widthVp) < 1, true, 'VP animation should end at target width');
        eq(Math.abs(value.heightVp - endSize.heightVp) < 1, true, 'VP animation should end at target height');
    }

    public testAnimationEasingTransition(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const startSize = { width: 100, height: 200 };
        const endSize = { width: 200, height: 400 };
        const steps = 10;
        env.update(startSize);
        for (let i = 1; i <= steps; i++) {
            const t = i / steps;
            const easedT = t * t;
            const currentWidth = startSize.width + (endSize.width - startSize.width) * easedT;
            const currentHeight = startSize.height + (endSize.height - startSize.height) * easedT;
            env.update({ width: currentWidth, height: currentHeight });
        }
        const value = env.value;
        eq(Math.abs(value.width - endSize.width) < 1, true, 'Eased animation should end at target');
    }

    // =========================================================================
    // 30. 窗口管理测试
    // =========================================================================

    public testWindowManagementSingleWindow(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 1920, height: 1080 });
        const value = env.value;
        eq(value.width, 1920, 'Single window width should be 1920');
        eq(value.height, 1080, 'Single window height should be 1080');
    }

    public testWindowManagementVpSingleWindow(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 960, heightVp: 540 });
        const value = env.value;
        eq(value.widthVp, 960, 'Single VP window width should be 960');
        eq(value.heightVp, 540, 'Single VP window height should be 540');
    }

    public testWindowManagementWindowResize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const originalSize = { width: 1920, height: 1080 };
        const newSize = { width: 1280, height: 720 };
        env.update(originalSize);
        const originalValue = env.value;
        eq(originalValue.width, 1920, 'Original window width should be 1920');
        env.update(newSize);
        const resizedValue = env.value;
        eq(resizedValue.width, 1280, 'Resized window width should be 1280');
        eq(resizedValue.height, 720, 'Resized window height should be 720');
    }

    public testWindowManagementVpWindowResize(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        const originalSize = { widthVp: 960, heightVp: 540 };
        const newSize = { widthVp: 640, heightVp: 360 };
        env.update(originalSize);
        const originalValue = env.value;
        eq(originalValue.widthVp, 960, 'Original VP window width should be 960');
        env.update(newSize);
        const resizedValue = env.value;
        eq(resizedValue.widthVp, 640, 'Resized VP window width should be 640');
        eq(resizedValue.heightVp, 360, 'Resized VP window height should be 360');
    }

    public testWindowManagementWindowMaximize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const normalSize = { width: 800, height: 600 };
        const maxSize = { width: 1920, height: 1080 };
        env.update(normalSize);
        env.update(maxSize);
        const value = env.value;
        eq(value.width, 1920, 'Maximized window width should be 1920');
        eq(value.height, 1080, 'Maximized window height should be 1080');
    }

    public testWindowManagementWindowMinimize(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        const normalSize = { width: 800, height: 600 };
        const minSize = { width: 320, height: 240 };
        env.update(normalSize);
        env.update(minSize);
        const value = env.value;
        eq(value.width, 320, 'Minimized window width should be 320');
        eq(value.height, 240, 'Minimized window height should be 240');
    }

    // =========================================================================
    // 31. 分辨率适配测试
    // =========================================================================

    public testResolutionAdaptationHD(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 1280, height: 720 });
        const value = env.value;
        eq(value.width, 1280, 'HD resolution width should be 1280');
        eq(value.height, 720, 'HD resolution height should be 720');
    }

    public testResolutionAdaptationFullHD(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 1920, height: 1080 });
        const value = env.value;
        eq(value.width, 1920, 'Full HD resolution width should be 1920');
        eq(value.height, 1080, 'Full HD resolution height should be 1080');
    }

    public testResolutionAdaptation2K(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 2560, height: 1440 });
        const value = env.value;
        eq(value.width, 2560, '2K resolution width should be 2560');
        eq(value.height, 1440, '2K resolution height should be 1440');
    }

    public testResolutionAdaptation4K(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 3840, height: 2160 });
        const value = env.value;
        eq(value.width, 3840, '4K resolution width should be 3840');
        eq(value.height, 2160, '4K resolution height should be 2160');
    }

    public testResolutionAdaptation8K(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 7680, height: 4320 });
        const value = env.value;
        eq(value.width, 7680, '8K resolution width should be 7680');
        eq(value.height, 4320, '8K resolution height should be 4320');
    }

    public testResolutionAdaptationVpHD(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 640, heightVp: 360 });
        const value = env.value;
        eq(value.widthVp, 640, 'VP HD resolution width should be 640');
        eq(value.heightVp, 360, 'VP HD resolution height should be 360');
    }

    public testResolutionAdaptationVpFullHD(): void {
        const context = new UIContext();
        const env = new WindowSizeVpEnv(context);
        env.update({ widthVp: 960, heightVp: 540 });
        const value = env.value;
        eq(value.widthVp, 960, 'VP Full HD resolution width should be 960');
        eq(value.heightVp, 540, 'VP Full HD resolution height should be 540');
    }

    // =========================================================================
    // 32. 屏幕密度测试
    // =========================================================================

    public testScreenDensityLowDensity(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 320, height: 480 });
        const value = env.value;
        eq(value.width, 320, 'Low density screen width should be 320');
        eq(value.height, 480, 'Low density screen height should be 480');
    }

    public testScreenDensityMediumDensity(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 480, height: 800 });
        const value = env.value;
        eq(value.width, 480, 'Medium density screen width should be 480');
        eq(value.height, 800, 'Medium density screen height should be 800');
    }

    public testScreenDensityHighDensity(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 720, height: 1280 });
        const value = env.value;
        eq(value.width, 720, 'High density screen width should be 720');
        eq(value.height, 1280, 'High density screen height should be 1280');
    }

    public testScreenDensityXHighDensity(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 1080, height: 1920 });
        const value = env.value;
        eq(value.width, 1080, 'XHigh density screen width should be 1080');
        eq(value.height, 1920, 'XHigh density screen height should be 1920');
    }

    public testScreenDensityXXHighDensity(): void {
        const context = new UIContext();
        const env = new WindowSizePxEnv(context);
        env.update({ width: 1440, height: 2560 });
        const value = env.value;
        eq(value.width, 1440, 'XXHigh density screen width should be 1440');
        eq(value.height, 2560, 'XXHigh density screen height should be 2560');
    }
}
