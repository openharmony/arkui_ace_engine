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
 * ========================================
 * drawableDescriptorStaticTest - DrawableDescriptor 静态接口用例 (API 23+)
 * ========================================
 *
 * 测试功能说明:
 * 基于 @ohos.arkui.drawableDescriptor.static.d.ets 静态声明接口
 * 验证 DrawableDescriptor 全系列静态接口功能
 *
 * 涉及的 API:
 * 1. DrawableDescriptorLoadedResult - 加载结果(imageWidth, imageHeight)
 * 2. DrawableDescriptor - constructor(), getPixelMap(), loadSync(), load()
 * 3. LayeredDrawableDescriptor - constructor(fg?, bg?, mask?), getForeground(),
 *    getBackground(), getMask(), static getMaskClipPath(), setBlendMode()
 * 4. PixelMapDrawableDescriptor - constructor(src?: image.PixelMap)
 * 5. AnimationStopMode - FIRST_FRAME(0), LAST_FRAME(1)
 * 6. AnimationOptions - duration?, iterations?, frameDurations?, autoPlay?, stopMode?
 * 7. AnimationController - start(), stop(), pause(), resume(), getStatus()
 * 8. AnimatedDrawableDescriptor - constructor(pixelMaps, options?),
 *    constructor(src, options?), getAnimationController(id?)
 */

import { image } from '@kit.ImageKit';
import { drawing } from '@kit.ArkGraphics2D';
import {
  DrawableDescriptor,
  LayeredDrawableDescriptor,
  PixelMapDrawableDescriptor,
  AnimatedDrawableDescriptor,
  AnimationStopMode,
  AnimationStatus
} from '@kit.ArkUI';

interface TestLog {
  time: string;
  msg: string;
  color: string;
}

@Entry
@Component
struct drawableDescriptorStaticTest {
  @State currentTab: number = 0;
  @State logs: TestLog[] = [];
  @State logCount: number = 0;

  // DrawableDescriptor 状态
  @State drawableDesc?: DrawableDescriptor = undefined;
  @State pixelMapResult?: image.PixelMap = undefined;
  @State loadSyncResultStr: string = '未测试';
  @State loadAsyncResultStr: string = '未测试';
  @State loadSyncImageWidth: string = '-';
  @State loadSyncImageHeight: string = '-';

  // LayeredDrawableDescriptor 状态
  @State layeredFromResource?: LayeredDrawableDescriptor = undefined;
  @State layeredFromPixelMap?: LayeredDrawableDescriptor = undefined;
  @State foregroundDesc?: DrawableDescriptor = undefined;
  @State backgroundDesc?: DrawableDescriptor = undefined;
  @State maskDesc?: DrawableDescriptor = undefined;
  @State maskClipPath: string = '';
  @State blendModeName: string = 'SRC_OVER';
  @State currentBlendMode: drawing.BlendMode = drawing.BlendMode.SRC_OVER;

  // PixelMapDrawableDescriptor 状态
  @State pixelMapDrawDesc?: PixelMapDrawableDescriptor = undefined;
  @State pixelMapDrawWithSrc?: PixelMapDrawableDescriptor = undefined;
  @State pixelMapDrawGetPixelMapResult?: image.PixelMap = undefined;

  // AnimatedDrawableDescriptor 状态
  @State animatedFromPixelMaps?: AnimatedDrawableDescriptor = undefined;
  @State animatedFromResource?: AnimatedDrawableDescriptor = undefined;
  @State animatedFromResourceStr?: AnimatedDrawableDescriptor = undefined;
  @State animControllerResult: string = '未测试';
  @State animControllerStatus: string = '未测试';
  @State animStopModeName: string = 'FIRST_FRAME';
  @State animAutoPlay: boolean = true;
  @State animDuration: number = 1000;
  @State animIterations: number = 1;
  @State animFrameDurationsStr: string = '';
  @State pixelMapList: image.PixelMap[] = [];

  // 测试用像素图数据
  private pixelMapData?: image.PixelMap = undefined;
  private resManager = this.getUIContext().getHostContext()?.resourceManager;

  aboutToAppear() {
    this.initTestData();
  }

  addLog(msg: string, color: string = '#333333') {
    const time = new Date().toLocaleTimeString();
    this.logs.unshift({ time, msg, color });
    this.logCount++;
    if (this.logs.length > 150) {
      this.logs.pop();
    }
  }

  async initTestData() {
    try {
      if (this.resManager) {
        this.drawableDesc = this.resManager.getDrawableDescriptor($r('app.media.icon').id);

        const layeredDraw = this.resManager.getDrawableDescriptor($r('app.media.layered_image').id);
        if (layeredDraw instanceof LayeredDrawableDescriptor) {
          this.layeredFromResource = layeredDraw;
        }
      }

      this.pixelMapDrawDesc = new PixelMapDrawableDescriptor();

      const creatingPixelMapOptions: image.PixelMapInitializationOptions = {
        size: { width: 100, height: 100 },
        pixelFormat: image.PixelMapFormat.BGRA_8888,
        editable: true,
      };
      this.pixelMapData = await image.createPixelMapSync(creatingPixelMapOptions);
      if (this.pixelMapData) {
        this.pixelMapDrawWithSrc = new PixelMapDrawableDescriptor(this.pixelMapData);
        this.pixelMapList = [this.pixelMapData];
      }

      this.maskClipPath = LayeredDrawableDescriptor.getMaskClipPath();

      this.addLog('初始化完成', '#4CAF50');
    } catch (e) {
      this.addLog(`初始化失败: ${e}`, '#F44336');
    }
  }

  // ===================== DrawableDescriptor 测试 =====================

  testDrawableDescriptorConstructor() {
    this.addLog('=== Test: DrawableDescriptor constructor ===');
    try {
      const desc = new DrawableDescriptor();
      if (desc) {
        this.addLog('PASS: DrawableDescriptor() 构造成功', '#4CAF50');
      } else {
        this.addLog('FAIL: DrawableDescriptor() 构造返回 null', '#F44336');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testDrawableDescriptorGetPixelMap() {
    this.addLog('=== Test: DrawableDescriptor.getPixelMap() ===');
    try {
      if (this.drawableDesc) {
        const pixelMap = this.drawableDesc.getPixelMap();
        if (pixelMap) {
          this.pixelMapResult = pixelMap;
          this.addLog('PASS: getPixelMap() 返回 PixelMap', '#4CAF50');
        } else {
          this.addLog('INFO: getPixelMap() 返回 undefined', '#FF9800');
        }
      } else {
        this.addLog('INFO: DrawableDescriptor 未初始化', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testDrawableDescriptorLoadSync() {
    this.addLog('=== Test: DrawableDescriptor.loadSync() ===');
    try {
      if (this.drawableDesc) {
        const result = this.drawableDesc.loadSync();
        if (result) {
          this.loadSyncImageWidth = `${result.imageWidth}`;
          this.loadSyncImageHeight = `${result.imageHeight}`;
          this.loadSyncResultStr = `imageWidth=${result.imageWidth}, imageHeight=${result.imageHeight}`;
          this.addLog(`PASS: loadSync() 成功, ${this.loadSyncResultStr}`, '#4CAF50');
        } else {
          this.loadSyncResultStr = '返回 null';
          this.addLog('FAIL: loadSync() 返回 null', '#F44336');
        }
      } else {
        this.addLog('INFO: DrawableDescriptor 未初始化', '#FF9800');
      }
    } catch (e) {
      this.loadSyncResultStr = `错误: ${e}`;
      this.addLog(`ERROR: loadSync() 失败 - ${e}`, '#F44336');
    }
  }

  async testDrawableDescriptorLoad() {
    this.addLog('=== Test: DrawableDescriptor.load() ===');
    try {
      if (this.drawableDesc) {
        const result = await this.drawableDesc.load();
        if (result) {
          this.loadAsyncResultStr = `imageWidth=${result.imageWidth}, imageHeight=${result.imageHeight}`;
          this.addLog(`PASS: load() 成功, ${this.loadAsyncResultStr}`, '#4CAF50');
        } else {
          this.loadAsyncResultStr = '返回 null';
          this.addLog('FAIL: load() 返回 null', '#F44336');
        }
      } else {
        this.addLog('INFO: DrawableDescriptor 未初始化', '#FF9800');
      }
    } catch (e) {
      this.loadAsyncResultStr = `错误: ${e}`;
      this.addLog(`ERROR: load() 失败 - ${e}`, '#F44336');
    }
  }

  // ===================== LayeredDrawableDescriptor 测试 =====================

  testLayeredConstructorWithParams() {
    this.addLog('=== Test: LayeredDrawableDescriptor constructor(fg, bg, mask) ===');
    try {
      const fg = new PixelMapDrawableDescriptor();
      const bg = new PixelMapDrawableDescriptor();
      const mask = new PixelMapDrawableDescriptor();
      const layered = new LayeredDrawableDescriptor(fg, bg, mask);
      if (layered) {
        this.layeredFromPixelMap = layered;
        this.addLog('PASS: LayeredDrawableDescriptor(fg, bg, mask) 构造成功', '#4CAF50');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredConstructorForegroundOnly() {
    this.addLog('=== Test: LayeredDrawableDescriptor constructor(fg) ===');
    try {
      const fg = new PixelMapDrawableDescriptor();
      const layered = new LayeredDrawableDescriptor(fg);
      if (layered) {
        this.addLog('PASS: 仅前景参数构造成功', '#4CAF50');
        const foreground = layered.getForeground();
        this.addLog(`  foreground: ${foreground ? '可用' : 'undefined'}`, '#2196F3');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredConstructorBackgroundOnly() {
    this.addLog('=== Test: LayeredDrawableDescriptor constructor(bg) ===');
    try {
      const bg = new PixelMapDrawableDescriptor();
      const layered = new LayeredDrawableDescriptor(undefined, bg);
      if (layered) {
        this.addLog('PASS: 仅背景参数构造成功', '#4CAF50');
        const background = layered.getBackground();
        this.addLog(`  background: ${background ? '可用' : 'undefined'}`, '#2196F3');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredConstructorMaskOnly() {
    this.addLog('=== Test: LayeredDrawableDescriptor constructor(mask) ===');
    try {
      const mask = new PixelMapDrawableDescriptor();
      const layered = new LayeredDrawableDescriptor(undefined, undefined, mask);
      if (layered) {
        this.addLog('PASS: 仅蒙版参数构造成功', '#4CAF50');
        const maskResult = layered.getMask();
        this.addLog(`  mask: ${maskResult ? '可用' : 'undefined'}`, '#2196F3');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredConstructorAllUndefined() {
    this.addLog('=== Test: LayeredDrawableDescriptor constructor(undefined, undefined, undefined) ===');
    try {
      const layered = new LayeredDrawableDescriptor(undefined, undefined, undefined);
      if (layered) {
        this.addLog('PASS: 全 undefined 参数构造成功', '#4CAF50');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredGetForeground() {
    this.addLog('=== Test: LayeredDrawableDescriptor.getForeground() ===');
    try {
      if (this.layeredFromResource) {
        const fg = this.layeredFromResource.getForeground();
        this.foregroundDesc = fg;
        if (fg) {
          this.addLog('PASS: getForeground() 返回 DrawableDescriptor', '#4CAF50');
        } else {
          this.addLog('INFO: getForeground() 返回 undefined', '#FF9800');
        }
      } else if (this.layeredFromPixelMap) {
        const fg = this.layeredFromPixelMap.getForeground();
        this.foregroundDesc = fg;
        this.addLog(`foreground: ${fg ? '可用' : 'undefined'}`, '#2196F3');
      } else {
        this.addLog('INFO: LayeredDrawableDescriptor 未初始化', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredGetBackground() {
    this.addLog('=== Test: LayeredDrawableDescriptor.getBackground() ===');
    try {
      if (this.layeredFromResource) {
        const bg = this.layeredFromResource.getBackground();
        this.backgroundDesc = bg;
        if (bg) {
          this.addLog('PASS: getBackground() 返回 DrawableDescriptor', '#4CAF50');
        } else {
          this.addLog('INFO: getBackground() 返回 undefined', '#FF9800');
        }
      } else if (this.layeredFromPixelMap) {
        const bg = this.layeredFromPixelMap.getBackground();
        this.backgroundDesc = bg;
        this.addLog(`background: ${bg ? '可用' : 'undefined'}`, '#2196F3');
      } else {
        this.addLog('INFO: LayeredDrawableDescriptor 未初始化', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredGetMask() {
    this.addLog('=== Test: LayeredDrawableDescriptor.getMask() ===');
    try {
      if (this.layeredFromResource) {
        const mask = this.layeredFromResource.getMask();
        this.maskDesc = mask;
        if (mask) {
          this.addLog('PASS: getMask() 返回 DrawableDescriptor', '#4CAF50');
        } else {
          this.addLog('INFO: getMask() 返回 undefined', '#FF9800');
        }
      } else if (this.layeredFromPixelMap) {
        const mask = this.layeredFromPixelMap.getMask();
        this.maskDesc = mask;
        this.addLog(`mask: ${mask ? '可用' : 'undefined'}`, '#2196F3');
      } else {
        this.addLog('INFO: LayeredDrawableDescriptor 未初始化', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredGetMaskClipPath() {
    this.addLog('=== Test: LayeredDrawableDescriptor.getMaskClipPath() (static) ===');
    try {
      const clipPath = LayeredDrawableDescriptor.getMaskClipPath();
      this.maskClipPath = clipPath;
      if (clipPath && clipPath.length > 0) {
        this.addLog(`PASS: getMaskClipPath() 返回非空字符串, 长度=${clipPath.length}`, '#4CAF50');
      } else {
        this.addLog('INFO: getMaskClipPath() 返回空字符串', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredSetBlendMode(mode: drawing.BlendMode, name: string) {
    this.addLog(`=== Test: LayeredDrawableDescriptor.setBlendMode(${name}) ===`);
    try {
      if (this.resManager) {
        const drawable = this.resManager.getDrawableDescriptor($r('app.media.layered_image').id);
        if (drawable instanceof LayeredDrawableDescriptor) {
          drawable.setBlendMode(mode);
          this.layeredFromResource = drawable;
          this.blendModeName = name;
          this.currentBlendMode = mode;
          this.addLog(`PASS: setBlendMode(${name}) 设置成功`, '#4CAF50');
        }
      }
      if (this.layeredFromPixelMap) {
        this.layeredFromPixelMap.setBlendMode(mode);
        this.addLog(`PASS: PixelMap方式的 setBlendMode(${name}) 设置成功`, '#4CAF50');
      }
    } catch (e) {
      this.addLog(`ERROR: setBlendMode(${name}) - ${e}`, '#F44336');
    }
  }

  testLayeredSetBlendModeUndefined() {
    this.addLog('=== Test: LayeredDrawableDescriptor.setBlendMode(undefined) ===');
    try {
      if (this.layeredFromPixelMap) {
        this.layeredFromPixelMap.setBlendMode(undefined);
        this.addLog('PASS: setBlendMode(undefined) 调用成功', '#4CAF50');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testLayeredInheritance() {
    this.addLog('=== Test: LayeredDrawableDescriptor 继承 DrawableDescriptor ===');
    try {
      const layered = new LayeredDrawableDescriptor();
      const isDrawableDesc = layered instanceof DrawableDescriptor;
      this.addLog(`instanceof DrawableDescriptor: ${isDrawableDesc}`, '#2196F3');

      if (isDrawableDesc) {
        this.addLog('PASS: LayeredDrawableDescriptor 正确继承 DrawableDescriptor', '#4CAF50');
      }

      const pixelMap = layered.getPixelMap();
      this.addLog(`  getPixelMap(): ${pixelMap ? '可用' : 'undefined'}`, '#2196F3');

      try {
        const result = layered.loadSync();
        this.addLog(`  loadSync(): ${result ? `imageWidth=${result.imageWidth}, imageHeight=${result.imageHeight}` : 'undefined'}`, '#2196F3');
      } catch (e) {
        this.addLog(`  loadSync(): 报错 - ${e}`, '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  // ===================== PixelMapDrawableDescriptor 测试 =====================

  testPixelMapDrawDefaultConstructor() {
    this.addLog('=== Test: PixelMapDrawableDescriptor constructor() ===');
    try {
      const desc = new PixelMapDrawableDescriptor();
      this.pixelMapDrawDesc = desc;
      if (desc) {
        this.addLog('PASS: PixelMapDrawableDescriptor() 默认构造成功', '#4CAF50');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testPixelMapDrawConstructorWithPixelMap() {
    this.addLog('=== Test: PixelMapDrawableDescriptor constructor(pixelMap) ===');
    try {
      if (this.pixelMapData) {
        const desc = new PixelMapDrawableDescriptor(this.pixelMapData);
        this.pixelMapDrawWithSrc = desc;
        if (desc) {
          this.addLog('PASS: PixelMapDrawableDescriptor(pixelMap) 构造成功', '#4CAF50');
        }
      } else {
        this.addLog('INFO: PixelMap 数据未初始化', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testPixelMapDrawGetPixelMap() {
    this.addLog('=== Test: PixelMapDrawableDescriptor.getPixelMap() ===');
    try {
      if (this.pixelMapDrawWithSrc) {
        const pm = this.pixelMapDrawWithSrc.getPixelMap();
        this.pixelMapDrawGetPixelMapResult = pm;
        if (pm) {
          this.addLog('PASS: PixelMapDrawableDescriptor.getPixelMap() 返回 PixelMap', '#4CAF50');
        } else {
          this.addLog('INFO: getPixelMap() 返回 undefined', '#FF9800');
        }
      } else if (this.pixelMapDrawDesc) {
        const pm = this.pixelMapDrawDesc.getPixelMap();
        this.addLog(`默认构造getPixelMap(): ${pm ? '可用' : 'undefined'}`, '#2196F3');
      } else {
        this.addLog('INFO: PixelMapDrawableDescriptor 未初始化', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testPixelMapDrawLoadSync() {
    this.addLog('=== Test: PixelMapDrawableDescriptor.loadSync() ===');
    try {
      if (this.pixelMapDrawWithSrc) {
        const result = this.pixelMapDrawWithSrc.loadSync();
        if (result) {
          this.addLog(`PASS: loadSync() imageWidth=${result.imageWidth}, imageHeight=${result.imageHeight}`, '#4CAF50');
        } else {
          this.addLog('INFO: loadSync() 返回 null', '#FF9800');
        }
      }
    } catch (e) {
      this.addLog(`ERROR: loadSync() - ${e}`, '#F44336');
    }
  }

  async testPixelMapDrawLoad() {
    this.addLog('=== Test: PixelMapDrawableDescriptor.load() ===');
    try {
      if (this.pixelMapDrawWithSrc) {
        const result = await this.pixelMapDrawWithSrc.load();
        if (result) {
          this.addLog(`PASS: load() imageWidth=${result.imageWidth}, imageHeight=${result.imageHeight}`, '#4CAF50');
        } else {
          this.addLog('INFO: load() 返回 null', '#FF9800');
        }
      }
    } catch (e) {
      this.addLog(`ERROR: load() - ${e}`, '#F44336');
    }
  }

  testPixelMapDrawInheritance() {
    this.addLog('=== Test: PixelMapDrawableDescriptor 继承 DrawableDescriptor ===');
    try {
      const desc = new PixelMapDrawableDescriptor();
      const isDrawableDesc = desc instanceof DrawableDescriptor;
      this.addLog(`instanceof DrawableDescriptor: ${isDrawableDesc}`, '#2196F3');
      if (isDrawableDesc) {
        this.addLog('PASS: PixelMapDrawableDescriptor 正确继承 DrawableDescriptor', '#4CAF50');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  // ===================== AnimationStopMode 测试 =====================

  testAnimationStopModeValues() {
    this.addLog('=== Test: AnimationStopMode 枚举值 ===');
    this.addLog(`FIRST_FRAME = ${AnimationStopMode.FIRST_FRAME}`, '#2196F3');
    this.addLog(`LAST_FRAME = ${AnimationStopMode.LAST_FRAME}`, '#2196F3');
    if (AnimationStopMode.FIRST_FRAME === 0) {
      this.addLog('PASS: AnimationStopMode.FIRST_FRAME === 0', '#4CAF50');
    } else {
      this.addLog('FAIL: AnimationStopMode.FIRST_FRAME !== 0', '#F44336');
    }
    if (AnimationStopMode.LAST_FRAME === 1) {
      this.addLog('PASS: AnimationStopMode.LAST_FRAME === 1', '#4CAF50');
    } else {
      this.addLog('FAIL: AnimationStopMode.LAST_FRAME !== 1', '#F44336');
    }
  }

  testAnimationOptionsStopMode() {
    this.addLog('=== Test: AnimationOptions.stopMode ===');
    try {
      const optsFirstFrame: AnimationOptions = {
        duration: 1000,
        iterations: 1,
        stopMode: AnimationStopMode.FIRST_FRAME,
      };
      this.addLog('PASS: AnimationOptions stopMode=FIRST_FRAME 创建成功', '#4CAF50');

      const optsLastFrame: AnimationOptions = {
        duration: 1000,
        iterations: 1,
        stopMode: AnimationStopMode.LAST_FRAME,
      };
      this.addLog('PASS: AnimationOptions stopMode=LAST_FRAME 创建成功', '#4CAF50');

      const anim1 = new AnimatedDrawableDescriptor($r('app.media.flower'), optsFirstFrame);
      this.addLog('PASS: AnimatedDrawableDescriptor with FIRST_FRAME stopMode 创建成功', '#4CAF50');

      const anim2 = new AnimatedDrawableDescriptor($r('app.media.flower'), optsLastFrame);
      this.addLog('PASS: AnimatedDrawableDescriptor with LAST_FRAME stopMode 创建成功', '#4CAF50');
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  // ===================== AnimationOptions 测试 =====================

  testAnimationOptionsDuration() {
    this.addLog('=== Test: AnimationOptions.duration ===');
    const durations = [100, 500, 1000, 2000, 5000, 10000];
    for (const dur of durations) {
      try {
        const opts: AnimationOptions = { duration: dur };
        const anim = new AnimatedDrawableDescriptor($r('app.media.flower'), opts);
        this.addLog(`  duration=${dur}: 创建成功`, '#2196F3');
      } catch (e) {
        this.addLog(`  duration=${dur}: 失败 - ${e}`, '#F44336');
      }
    }
  }

  testAnimationOptionsIterations() {
    this.addLog('=== Test: AnimationOptions.iterations ===');
    const iterations = [-1, 0, 1, 2, 3, 5, 10];
    for (const iter of iterations) {
      try {
        const opts: AnimationOptions = { iterations: iter, duration: 1000 };
        const anim = new AnimatedDrawableDescriptor($r('app.media.flower'), opts);
        this.addLog(`  iterations=${iter}: 创建成功`, '#2196F3');
      } catch (e) {
        this.addLog(`  iterations=${iter}: 失败 - ${e}`, '#F44336');
      }
    }
  }

  testAnimationOptionsFrameDurations() {
    this.addLog('=== Test: AnimationOptions.frameDurations ===');
    try {
      const frameDurations: number[] = [50, 100, 150, 200, 250];
      const opts: AnimationOptions = {
        duration: 1000,
        iterations: 1,
        frameDurations: frameDurations,
      };
      this.animFrameDurationsStr = frameDurations.join(',');
      const anim = new AnimatedDrawableDescriptor($r('app.media.flower'), opts);
      this.addLog(`PASS: frameDurations=[${frameDurations.join(',')}] 创建成功`, '#4CAF50');
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimationOptionsAutoPlay() {
    this.addLog('=== Test: AnimationOptions.autoPlay ===');
    try {
      const optsTrue: AnimationOptions = { duration: 1000, autoPlay: true };
      const anim1 = new AnimatedDrawableDescriptor($r('app.media.flower'), optsTrue);
      this.addLog('PASS: autoPlay=true 创建成功', '#4CAF50');

      const optsFalse: AnimationOptions = { duration: 1000, autoPlay: false };
      const anim2 = new AnimatedDrawableDescriptor($r('app.media.flower'), optsFalse);
      this.addLog('PASS: autoPlay=false 创建成功', '#4CAF50');

      const optsDefault: AnimationOptions = { duration: 1000 };
      const anim3 = new AnimatedDrawableDescriptor($r('app.media.flower'), optsDefault);
      this.addLog('PASS: autoPlay默认(不设置) 创建成功', '#4CAF50');
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimationOptionsAllFields() {
    this.addLog('=== Test: AnimationOptions 全部字段组合 ===');
    try {
      const opts: AnimationOptions = {
        duration: 2000,
        iterations: 3,
        frameDurations: [100, 200, 300],
        autoPlay: true,
        stopMode: AnimationStopMode.LAST_FRAME,
      };
      const anim = new AnimatedDrawableDescriptor($r('app.media.flower'), opts);
      this.animDuration = opts.duration;
      this.animIterations = opts.iterations;
      this.animAutoPlay = opts.autoPlay;
      this.animStopModeName = 'LAST_FRAME';
      this.addLog('PASS: AnimationOptions 全字段组合创建成功', '#4CAF50');
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  // ===================== AnimationController 测试 =====================

  testGetAnimationControllerWithId() {
    this.addLog('=== Test: AnimatedDrawableDescriptor.getAnimationController(id) ===');
    try {
      const anim = new AnimatedDrawableDescriptor($r('app.media.flower'), {
        duration: 2000,
        iterations: 1,
        autoPlay: false,
      });
      this.animatedFromResource = anim;
      const controller = anim.getAnimationController('testAnimId');
      if (controller) {
        this.animControllerResult = '获取成功';
        this.addLog('PASS: getAnimationController("testAnimId") 返回 AnimationController', '#4CAF50');
      } else {
        this.animControllerResult = '返回 undefined';
        this.addLog('INFO: getAnimationController() 返回 undefined', '#FF9800');
      }
    } catch (e) {
      this.animControllerResult = `错误: ${e}`;
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testGetAnimationControllerWithoutId() {
    this.addLog('=== Test: AnimatedDrawableDescriptor.getAnimationController() (无参数) ===');
    try {
      const anim = new AnimatedDrawableDescriptor($r('app.media.flower'), {
        duration: 2000,
        iterations: 1,
        autoPlay: false,
      });
      const controller = anim.getAnimationController();
      if (controller) {
        this.addLog('PASS: getAnimationController() 无参数返回 AnimationController', '#4CAF50');
      } else {
        this.addLog('INFO: getAnimationController() 无参数返回 undefined', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimationControllerStart() {
    this.addLog('=== Test: AnimationController.start() ===');
    try {
      const controller = this.animatedFromResource?.getAnimationController('animControlTest');
      if (controller) {
        controller.start();
        this.animControllerStatus = 'Running';
        this.addLog('PASS: controller.start() 调用成功', '#4CAF50');
      } else {
        this.addLog('INFO: controller 未获取', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimationControllerPause() {
    this.addLog('=== Test: AnimationController.pause() ===');
    try {
      const controller = this.animatedFromResource?.getAnimationController('animControlTest');
      if (controller) {
        controller.pause();
        this.animControllerStatus = 'Paused';
        this.addLog('PASS: controller.pause() 调用成功', '#4CAF50');
      } else {
        this.addLog('INFO: controller 未获取', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimationControllerResume() {
    this.addLog('=== Test: AnimationController.resume() ===');
    try {
      const controller = this.animatedFromResource?.getAnimationController('animControlTest');
      if (controller) {
        controller.resume();
        this.animControllerStatus = 'Running';
        this.addLog('PASS: controller.resume() 调用成功', '#4CAF50');
      } else {
        this.addLog('INFO: controller 未获取', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimationControllerStop() {
    this.addLog('=== Test: AnimationController.stop() ===');
    try {
      const controller = this.animatedFromResource?.getAnimationController('animControlTest');
      if (controller) {
        controller.stop();
        this.animControllerStatus = 'Stopped';
        this.addLog('PASS: controller.stop() 调用成功', '#4CAF50');
      } else {
        this.addLog('INFO: controller 未获取', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimationControllerGetStatus() {
    this.addLog('=== Test: AnimationController.getStatus() ===');
    try {
      const controller = this.animatedFromResource?.getAnimationController('animControlTest');
      if (controller) {
        const status = controller.getStatus();
        this.animControllerStatus = this.statusToString(status);
        this.addLog(`PASS: getStatus() = ${this.animControllerStatus}`, '#4CAF50');
      } else {
        this.addLog('INFO: controller 未获取', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  statusToString(status?: AnimationStatus): string {
    switch (status) {
      case AnimationStatus.Initial:
        return 'Initial';
      case AnimationStatus.Running:
        return 'Running';
      case AnimationStatus.Paused:
        return 'Paused';
      case AnimationStatus.Stopped:
        return 'Stopped';
      default:
        return 'Unknown';
    }
  }

  // ===================== AnimatedDrawableDescriptor 测试 =====================

  testAnimatedConstructorPixelMaps() {
    this.addLog('=== Test: AnimatedDrawableDescriptor constructor(pixelMaps) ===');
    try {
      if (this.pixelMapList.length > 0) {
        const opts: AnimationOptions = { duration: 500, iterations: 1 };
        const anim = new AnimatedDrawableDescriptor(this.pixelMapList, opts);
        this.animatedFromPixelMaps = anim;
        this.addLog('PASS: AnimatedDrawableDescriptor(pixelMaps) 构造成功', '#4CAF50');
      } else {
        this.addLog('INFO: pixelMapList 为空', '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimatedConstructorResource() {
    this.addLog('=== Test: AnimatedDrawableDescriptor constructor(resource) ===');
    try {
      const opts: AnimationOptions = { duration: 1000, iterations: 1 };
      const anim = new AnimatedDrawableDescriptor($r('app.media.flower'), opts);
      this.animatedFromResource = anim;
      this.addLog('PASS: AnimatedDrawableDescriptor(resource) 构造成功', '#4CAF50');
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimatedConstructorResourceStr() {
    this.addLog('=== Test: AnimatedDrawableDescriptor constructor(resourceStr) ===');
    try {
      const opts: AnimationOptions = { duration: 1000, iterations: 1 };
      const anim = new AnimatedDrawableDescriptor('common/flower.png', opts);
      this.animatedFromResourceStr = anim;
      this.addLog('PASS: AnimatedDrawableDescriptor(resourceStr) 构造成功', '#4CAF50');
    } catch (e) {
      this.addLog(`ERROR(预期): ${e}`, '#FF9800');
    }
  }

  testAnimatedConstructorWithoutOptions() {
    this.addLog('=== Test: AnimatedDrawableDescriptor constructor(无 options) ===');
    try {
      const anim = new AnimatedDrawableDescriptor($r('app.media.flower'));
      this.addLog('PASS: 无 options 参数构造成功', '#4CAF50');
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  testAnimatedInheritance() {
    this.addLog('=== Test: AnimatedDrawableDescriptor 继承 DrawableDescriptor ===');
    try {
      const anim = new AnimatedDrawableDescriptor($r('app.media.flower'));
      const isDrawableDesc = anim instanceof DrawableDescriptor;
      this.addLog(`instanceof DrawableDescriptor: ${isDrawableDesc}`, '#2196F3');
      if (isDrawableDesc) {
        this.addLog('PASS: AnimatedDrawableDescriptor 正确继承 DrawableDescriptor', '#4CAF50');
      }

      const pixelMap = anim.getPixelMap();
      this.addLog(`  getPixelMap(): ${pixelMap ? '可用' : 'undefined'}`, '#2196F3');

      try {
        const result = anim.loadSync();
        this.addLog(`  loadSync(): ${result ? '可用' : '报错'}`, '#2196F3');
      } catch (e) {
        this.addLog(`  loadSync(): 报错 - ${e}`, '#FF9800');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  // ===================== DrawableDescriptorLoadedResult 测试 =====================

  testLoadedResultFromLoadSync() {
    this.addLog('=== Test: DrawableDescriptorLoadedResult from loadSync() ===');
    try {
      if (this.drawableDesc) {
        const result = this.drawableDesc.loadSync();
        if (result) {
          this.addLog(`PASS: loadSync() 返回 DrawableDescriptorLoadedResult`, '#4CAF50');
          this.addLog(`  imageWidth: ${result.imageWidth} (类型: ${typeof result.imageWidth})`, '#2196F3');
          this.addLog(`  imageHeight: ${result.imageHeight} (类型: ${typeof result.imageHeight})`, '#2196F3');
          this.loadSyncImageWidth = `${result.imageWidth}`;
          this.loadSyncImageHeight = `${result.imageHeight}`;
        }
      }
      if (this.pixelMapDrawWithSrc) {
        const result2 = this.pixelMapDrawWithSrc.loadSync();
        if (result2) {
          this.addLog(`PASS: PixelMapDrawableDescriptor.loadSync() 返回结果`, '#4CAF50');
          this.addLog(`  imageWidth: ${result2.imageWidth}`, '#2196F3');
          this.addLog(`  imageHeight: ${result2.imageHeight}`, '#2196F3');
        }
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  async testLoadedResultFromLoad() {
    this.addLog('=== Test: DrawableDescriptorLoadedResult from load() ===');
    try {
      if (this.drawableDesc) {
        const result = await this.drawableDesc.load();
        if (result) {
          this.addLog(`PASS: load() 返回 DrawableDescriptorLoadedResult`, '#4CAF50');
          this.addLog(`  imageWidth: ${result.imageWidth} (类型: ${typeof result.imageWidth})`, '#2196F3');
          this.addLog(`  imageHeight: ${result.imageHeight} (类型: ${typeof result.imageHeight})`, '#2196F3');
        }
      }
      if (this.pixelMapDrawWithSrc) {
        const result2 = await this.pixelMapDrawWithSrc.load();
        if (result2) {
          this.addLog(`PASS: PixelMapDrawableDescriptor.load() 返回结果`, '#4CAF50');
          this.addLog(`  imageWidth: ${result2.imageWidth}`, '#2196F3');
          this.addLog(`  imageHeight: ${result2.imageHeight}`, '#2196F3');
        }
      }
    } catch (e) {
      this.addLog(`ERROR: ${e}`, '#F44336');
    }
  }

  // ===================== 综合测试 =====================

  runAllDrawableDescriptorTests() {
    this.testDrawableDescriptorConstructor();
    this.testDrawableDescriptorGetPixelMap();
    this.testDrawableDescriptorLoadSync();
    this.testDrawableDescriptorLoad();
    this.testLoadedResultFromLoadSync();
    this.testLoadedResultFromLoad();
  }

  runAllLayeredTests() {
    this.testLayeredConstructorWithParams();
    this.testLayeredConstructorForegroundOnly();
    this.testLayeredConstructorBackgroundOnly();
    this.testLayeredConstructorMaskOnly();
    this.testLayeredConstructorAllUndefined();
    this.testLayeredGetForeground();
    this.testLayeredGetBackground();
    this.testLayeredGetMask();
    this.testLayeredGetMaskClipPath();
    this.testLayeredSetBlendMode(drawing.BlendMode.SRC_OVER, 'SRC_OVER');
    this.testLayeredSetBlendModeUndefined();
    this.testLayeredInheritance();
  }

  runAllPixelMapTests() {
    this.testPixelMapDrawDefaultConstructor();
    this.testPixelMapDrawConstructorWithPixelMap();
    this.testPixelMapDrawGetPixelMap();
    this.testPixelMapDrawLoadSync();
    this.testPixelMapDrawLoad();
    this.testPixelMapDrawInheritance();
  }

  runAllAnimatedTests() {
    this.testAnimationStopModeValues();
    this.testAnimationOptionsStopMode();
    this.testAnimationOptionsDuration();
    this.testAnimationOptionsIterations();
    this.testAnimationOptionsFrameDurations();
    this.testAnimationOptionsAutoPlay();
    this.testAnimationOptionsAllFields();
    this.testAnimatedConstructorPixelMaps();
    this.testAnimatedConstructorResource();
    this.testAnimatedConstructorResourceStr();
    this.testAnimatedConstructorWithoutOptions();
    this.testAnimatedInheritance();
    this.testGetAnimationControllerWithId();
    this.testGetAnimationControllerWithoutId();
    this.testAnimationControllerStart();
    this.testAnimationControllerPause();
    this.testAnimationControllerResume();
    this.testAnimationControllerStop();
    this.testAnimationControllerGetStatus();
  }

  // ===================== UI 构建 =====================

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentTab }) {
        TabContent() {
          this.buildDrawableDescriptorTab()
        }
        .tabBar('DrawableDescriptor')

        TabContent() {
          this.buildLayeredTab()
        }
        .tabBar('Layered')

        TabContent() {
          this.buildPixelMapTab()
        }
        .tabBar('PixelMap')

        TabContent() {
          this.buildAnimatedTab()
        }
        .tabBar('Animated')

        TabContent() {
          this.buildLoadedResultTab()
        }
        .tabBar('LoadedResult')

        TabContent() {
          this.buildLogTab()
        }
        .tabBar('Logs')
      }
      .onChange((index: number) => {
        this.currentTab = index;
      })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  buildDrawableDescriptorTab() {
    Scroll() {
      Column({ space: 15 }) {
        Text('DrawableDescriptor 静态接口用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x333333)
          .margin({ top: 15 })

        Column({ space: 10 }) {
          Text('API 清单')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Text('constructor()')
            .fontSize(13)
            .backgroundColor(0xE8F5E9)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('getPixelMap(): image.PixelMap | undefined')
            .fontSize(13)
            .backgroundColor(0xE3F2FD)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('loadSync(): DrawableDescriptorLoadedResult')
            .fontSize(13)
            .backgroundColor(0xFFF3E0)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('load(): Promise<DrawableDescriptorLoadedResult>')
            .fontSize(13)
            .backgroundColor(0xFCE4EC)
            .padding(8)
            .borderRadius(5)
            .width('100%')
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 10 }) {
          Text('测试按钮')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('1. constructor()')
            .width('90%')
            .onClick(() => this.testDrawableDescriptorConstructor())

          Button('2. getPixelMap()')
            .width('90%')
            .onClick(() => this.testDrawableDescriptorGetPixelMap())

          Button('3. loadSync()')
            .width('90%')
            .onClick(() => this.testDrawableDescriptorLoadSync())

          Button('4. load() (async)')
            .width('90%')
            .onClick(() => this.testDrawableDescriptorLoad())

          Button('运行全部 DrawableDescriptor 测试')
            .width('90%')
            .backgroundColor(0x4CAF50)
            .onClick(() => this.runAllDrawableDescriptorTests())
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('测试结果')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 10 }) {
            Text('loadSync结果:')
              .fontSize(13)
              .fontWeight(FontWeight.Bold)
            Text(this.loadSyncResultStr)
              .fontSize(13)
              .fontColor(0x2196F3)
          }

          Row({ space: 10 }) {
            Text('load结果:')
              .fontSize(13)
              .fontWeight(FontWeight.Bold)
            Text(this.loadAsyncResultStr)
              .fontSize(13)
              .fontColor(0xFF9800)
          }

          Row({ space: 10 }) {
            Text('imageWidth:')
              .fontSize(13)
            Text(this.loadSyncImageWidth)
              .fontSize(13)
              .fontColor(0x4CAF50)
            Text('imageHeight:')
              .fontSize(13)
            Text(this.loadSyncImageHeight)
              .fontSize(13)
              .fontColor(0x4CAF50)
          }
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 10 }) {
          Text('DrawableDescriptor 显示')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          if (this.drawableDesc) {
            Image(this.drawableDesc)
              .width(200)
              .height(200)
              .border({ width: 1, color: Color.Gray })
              .borderRadius(8)
          } else {
            Text('暂无 DrawableDescriptor')
              .fontSize(14)
              .fontColor(0x999999)
              .width(200)
              .height(200)
              .textAlign(TextAlign.Center)
              .backgroundColor(0xF0F0F0)
              .borderRadius(8)
          }
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)
      }
      .padding({ left: 15, right: 15, bottom: 15 })
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
  }

  @Builder
  buildLayeredTab() {
    Scroll() {
      Column({ space: 15 }) {
        Text('LayeredDrawableDescriptor 静态接口用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x333333)
          .margin({ top: 15 })

        Column({ space: 10 }) {
          Text('API 清单')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Text('constructor(fg?, bg?, mask?)')
            .fontSize(13)
            .backgroundColor(0xE8F5E9)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('getForeground(): DrawableDescriptor | undefined')
            .fontSize(13)
            .backgroundColor(0xE3F2FD)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('getBackground(): DrawableDescriptor | undefined')
            .fontSize(13)
            .backgroundColor(0xE3F2FD)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('getMask(): DrawableDescriptor | undefined')
            .fontSize(13)
            .backgroundColor(0xE3F2FD)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('static getMaskClipPath(): string')
            .fontSize(13)
            .backgroundColor(0xFFF3E0)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('setBlendMode(mode: drawing.BlendMode | undefined): void')
            .fontSize(13)
            .backgroundColor(0xFCE4EC)
            .padding(8)
            .borderRadius(5)
            .width('100%')
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 10 }) {
          Text('构造函数测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('1. constructor(fg, bg, mask)')
            .width('90%')
            .onClick(() => this.testLayeredConstructorWithParams())

          Button('2. constructor(fg) 仅前景')
            .width('90%')
            .onClick(() => this.testLayeredConstructorForegroundOnly())

          Button('3. constructor(bg) 仅背景')
            .width('90%')
            .onClick(() => this.testLayeredConstructorBackgroundOnly())

          Button('4. constructor(mask) 仅蒙版')
            .width('90%')
            .onClick(() => this.testLayeredConstructorMaskOnly())

          Button('5. constructor(undefined, undefined, undefined)')
            .width('90%')
            .onClick(() => this.testLayeredConstructorAllUndefined())
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('方法测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('6. getForeground()')
            .width('90%')
            .onClick(() => this.testLayeredGetForeground())

          Button('7. getBackground()')
            .width('90%')
            .onClick(() => this.testLayeredGetBackground())

          Button('8. getMask()')
            .width('90%')
            .onClick(() => this.testLayeredGetMask())

          Button('9. getMaskClipPath() (static)')
            .width('90%')
            .onClick(() => this.testLayeredGetMaskClipPath())

          Button('10. 继承关系验证')
            .width('90%')
            .onClick(() => this.testLayeredInheritance())
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('setBlendMode 测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Text(`当前模式: ${this.blendModeName}`)
            .fontSize(14)
            .fontColor(0x2196F3)
            .fontWeight(FontWeight.Bold)

          Flex({ wrap: FlexWrap.Wrap }) {
            Button('SRC_OVER')
              .fontSize(11)
              .margin(4)
              .onClick(() => this.testLayeredSetBlendMode(drawing.BlendMode.SRC_OVER, 'SRC_OVER'))

            Button('SRC')
              .fontSize(11)
              .margin(4)
              .onClick(() => this.testLayeredSetBlendMode(drawing.BlendMode.SRC, 'SRC'))

            Button('DST_OVER')
              .fontSize(11)
              .margin(4)
              .onClick(() => this.testLayeredSetBlendMode(drawing.BlendMode.DST_OVER, 'DST_OVER'))

            Button('MULTIPLY')
              .fontSize(11)
              .margin(4)
              .onClick(() => this.testLayeredSetBlendMode(drawing.BlendMode.MULTIPLY, 'MULTIPLY'))

            Button('SCREEN')
              .fontSize(11)
              .margin(4)
              .onClick(() => this.testLayeredSetBlendMode(drawing.BlendMode.SCREEN, 'SCREEN'))

            Button('undefined')
              .fontSize(11)
              .margin(4)
              .backgroundColor(Color.Orange)
              .onClick(() => this.testLayeredSetBlendModeUndefined())
          }
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 10 }) {
          Text('效果展示')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 15 }) {
            Column({ space: 5 }) {
              Text('资源方式')
                .fontSize(13)
                .fontColor(0x4CAF50)
              if (this.layeredFromResource) {
                Image(this.layeredFromResource)
                  .width(120)
                  .height(120)
                  .borderRadius(8)
                  .border({ width: 1, color: 0x4CAF50 })
              } else {
                Text('暂无')
                  .fontSize(12)
                  .width(120)
                  .height(120)
                  .textAlign(TextAlign.Center)
                  .backgroundColor(0xF0F0F0)
                  .borderRadius(8)
              }
            }

            Column({ space: 5 }) {
              Text('PixelMap方式')
                .fontSize(13)
                .fontColor(0xFF9800)
              if (this.layeredFromPixelMap) {
                Image(this.layeredFromPixelMap)
                  .width(120)
                  .height(120)
                  .borderRadius(8)
                  .border({ width: 1, color: 0xFF9800 })
              } else {
                Text('暂无')
                  .fontSize(12)
                  .width(120)
                  .height(120)
                  .textAlign(TextAlign.Center)
                  .backgroundColor(0xF0F0F0)
                  .borderRadius(8)
              }
            }
          }
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('getMaskClipPath 结果')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Text(this.maskClipPath)
            .fontSize(11)
            .fontColor(0x666666)
            .padding(10)
            .backgroundColor(0xF5F5F5)
            .borderRadius(8)
            .width('100%')
            .maxLines(5)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .copyOption(CopyOptions.LocalDevice)
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Button('运行全部 Layered 测试')
          .width('90%')
          .backgroundColor(0x4CAF50)
          .onClick(() => this.runAllLayeredTests())
      }
      .padding({ left: 15, right: 15, bottom: 15 })
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
  }

  @Builder
  buildPixelMapTab() {
    Scroll() {
      Column({ space: 15 }) {
        Text('PixelMapDrawableDescriptor 静态接口用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x333333)
          .margin({ top: 15 })

        Column({ space: 10 }) {
          Text('API 清单')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Text('constructor(src?: image.PixelMap)')
            .fontSize(13)
            .backgroundColor(0xE8F5E9)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('继承: getPixelMap(), loadSync(), load()')
            .fontSize(13)
            .backgroundColor(0xE3F2FD)
            .padding(8)
            .borderRadius(5)
            .width('100%')
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 10 }) {
          Text('测试按钮')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('1. constructor() 默认')
            .width('90%')
            .onClick(() => this.testPixelMapDrawDefaultConstructor())

          Button('2. constructor(pixelMap)')
            .width('90%')
            .onClick(() => this.testPixelMapDrawConstructorWithPixelMap())

          Button('3. getPixelMap()')
            .width('90%')
            .onClick(() => this.testPixelMapDrawGetPixelMap())

          Button('4. loadSync()')
            .width('90%')
            .onClick(() => this.testPixelMapDrawLoadSync())

          Button('5. load() (async)')
            .width('90%')
            .onClick(() => this.testPixelMapDrawLoad())

          Button('6. 继承关系验证')
            .width('90%')
            .onClick(() => this.testPixelMapDrawInheritance())
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('效果展示')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 15 }) {
            Column({ space: 5 }) {
              Text('默认构造')
                .fontSize(13)
                .fontColor(0x2196F3)
              if (this.pixelMapDrawDesc) {
                Image(this.pixelMapDrawDesc)
                  .width(120)
                  .height(120)
                  .borderRadius(8)
                  .border({ width: 1, color: 0x2196F3 })
              }
            }

            Column({ space: 5 }) {
              Text('带PixelMap构造')
                .fontSize(13)
                .fontColor(0xFF9800)
              if (this.pixelMapDrawWithSrc) {
                Image(this.pixelMapDrawWithSrc)
                  .width(120)
                  .height(120)
                  .borderRadius(8)
                  .border({ width: 1, color: 0xFF9800 })
              }
            }
          }
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Button('运行全部 PixelMap 测试')
          .width('90%')
          .backgroundColor(0x4CAF50)
          .onClick(() => this.runAllPixelMapTests())
      }
      .padding({ left: 15, right: 15, bottom: 15 })
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
  }

  @Builder
  buildAnimatedTab() {
    Scroll() {
      Column({ space: 15 }) {
        Text('AnimatedDrawableDescriptor 静态接口用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x333333)
          .margin({ top: 15 })

        Column({ space: 10 }) {
          Text('API 清单')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Text('constructor(pixelMaps: Array<PixelMap>, options?)')
            .fontSize(13)
            .backgroundColor(0xE8F5E9)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('constructor(src: ResourceStr | Array<PixelMap>, options?)')
            .fontSize(13)
            .backgroundColor(0xE3F2FD)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('getAnimationController(id?): AnimationController | undefined')
            .fontSize(13)
            .backgroundColor(0xFFF3E0)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('AnimationController: start(), stop(), pause(), resume(), getStatus()')
            .fontSize(13)
            .backgroundColor(0xFCE4EC)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('AnimationStopMode: FIRST_FRAME(0), LAST_FRAME(1)')
            .fontSize(13)
            .backgroundColor(0xF3E5F5)
            .padding(8)
            .borderRadius(5)
            .width('100%')
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 10 }) {
          Text('构造函数测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('1. constructor(pixelMaps, options)')
            .width('90%')
            .onClick(() => this.testAnimatedConstructorPixelMaps())

          Button('2. constructor(resource, options)')
            .width('90%')
            .onClick(() => this.testAnimatedConstructorResource())

          Button('3. constructor(resourceStr, options)')
            .width('90%')
            .onClick(() => this.testAnimatedConstructorResourceStr())

          Button('4. constructor(resource) 无options')
            .width('90%')
            .onClick(() => this.testAnimatedConstructorWithoutOptions())

          Button('5. 继承关系验证')
            .width('90%')
            .onClick(() => this.testAnimatedInheritance())
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('AnimationStopMode 测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('6. AnimationStopMode 枚举值')
            .width('90%')
            .onClick(() => this.testAnimationStopModeValues())

          Button('7. AnimationOptions.stopMode')
            .width('90%')
            .onClick(() => this.testAnimationOptionsStopMode())
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('AnimationOptions 测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('8. duration 各值')
            .width('90%')
            .onClick(() => this.testAnimationOptionsDuration())

          Button('9. iterations 各值')
            .width('90%')
            .onClick(() => this.testAnimationOptionsIterations())

          Button('10. frameDurations')
            .width('90%')
            .onClick(() => this.testAnimationOptionsFrameDurations())

          Button('11. autoPlay true/false')
            .width('90%')
            .onClick(() => this.testAnimationOptionsAutoPlay())

          Button('12. 全字段组合')
            .width('90%')
            .onClick(() => this.testAnimationOptionsAllFields())
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('AnimationController 测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('13. getAnimationController(id)')
            .width('90%')
            .onClick(() => this.testGetAnimationControllerWithId())

          Button('14. getAnimationController() 无参数')
            .width('90%')
            .onClick(() => this.testGetAnimationControllerWithoutId())

          Button('15. start()')
            .width('90%')
            .onClick(() => this.testAnimationControllerStart())

          Button('16. pause()')
            .width('90%')
            .onClick(() => this.testAnimationControllerPause())

          Button('17. resume()')
            .width('90%')
            .onClick(() => this.testAnimationControllerResume())

          Button('18. stop()')
            .width('90%')
            .onClick(() => this.testAnimationControllerStop())

          Button('19. getStatus()')
            .width('90%')
            .onClick(() => this.testAnimationControllerGetStatus())

          Text(`controller状态: ${this.animControllerStatus}`)
            .fontSize(14)
            .fontColor(0x2196F3)
            .fontWeight(FontWeight.Bold)
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('动画展示')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          if (this.animatedFromResource) {
            Image(this.animatedFromResource)
              .width(150)
              .height(150)
              .borderRadius(8)
              .id('animControlTest')
              .border({ width: 1, color: 0x9C27B0 })
          }

          if (this.animatedFromPixelMaps) {
            Image(this.animatedFromPixelMaps)
              .width(150)
              .height(150)
              .borderRadius(8)
              .border({ width: 1, color: 0x4CAF50 })
          }
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Button('运行全部 Animated 测试')
          .width('90%')
          .backgroundColor(0x4CAF50)
          .onClick(() => this.runAllAnimatedTests())
      }
      .padding({ left: 15, right: 15, bottom: 15 })
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
  }

  @Builder
  buildLoadedResultTab() {
    Scroll() {
      Column({ space: 15 }) {
        Text('DrawableDescriptorLoadedResult 静态接口用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x333333)
          .margin({ top: 15 })

        Column({ space: 10 }) {
          Text('API 清单')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Text('interface DrawableDescriptorLoadedResult { imageWidth: int; imageHeight: int; }')
            .fontSize(13)
            .backgroundColor(0xE8F5E9)
            .padding(8)
            .borderRadius(5)
            .width('100%')

          Text('由 loadSync() 和 load() 返回该接口对象')
            .fontSize(13)
            .fontColor(0x666666)
            .padding(8)
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 10 }) {
          Text('测试按钮')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('1. loadSync() → LoadedResult')
            .width('90%')
            .onClick(() => this.testLoadedResultFromLoadSync())

          Button('2. load() → LoadedResult (async)')
            .width('90%')
            .onClick(() => this.testLoadedResultFromLoad())

          Button('3. loadSync() DrawableDescriptor')
            .width('90%')
            .onClick(() => this.testDrawableDescriptorLoadSync())

          Button('4. load() DrawableDescriptor (async)')
            .width('90%')
            .onClick(() => this.testDrawableDescriptorLoad())

          Button('5. PixelMapDrawableDescriptor.loadSync()')
            .width('90%')
            .onClick(() => this.testPixelMapDrawLoadSync())

          Button('6. PixelMapDrawableDescriptor.load() (async)')
            .width('90%')
            .onClick(() => this.testPixelMapDrawLoad())
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('loadSync() 结果')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 10 }) {
            Text('imageWidth:')
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
            Text(this.loadSyncImageWidth)
              .fontSize(14)
              .fontColor(0x4CAF50)
          }

          Row({ space: 10 }) {
            Text('imageHeight:')
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
            Text(this.loadSyncImageHeight)
              .fontSize(14)
              .fontColor(0x4CAF50)
          }

          Text(this.loadSyncResultStr)
            .fontSize(13)
            .fontColor(0x2196F3)
            .padding(10)
            .backgroundColor(0xE8F5E9)
            .borderRadius(8)
            .width('100%')
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)

        Column({ space: 10 }) {
          Text('load() 结果')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Text(this.loadAsyncResultStr)
            .fontSize(13)
            .fontColor(0xFF9800)
            .padding(10)
            .backgroundColor(0xFFF3E0)
            .borderRadius(8)
            .width('100%')
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(12)
      }
      .padding({ left: 15, right: 15, bottom: 15 })
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
  }

  @Builder
  buildLogTab() {
    Column() {
      Row({ space: 10 }) {
        Button('运行全部测试')
          .onClick(() => {
            this.logs = [];
            this.runAllDrawableDescriptorTests();
            this.runAllLayeredTests();
            this.runAllPixelMapTests();
            this.runAllAnimatedTests();
          })
          .width('45%')
          .backgroundColor(0x4CAF50)

        Button('清除日志')
          .onClick(() => {
            this.logs = [];
            this.logCount = 0;
          })
          .width('45%')
      }
      .padding(10)
      .width('100%')

      Row({ space: 10 }) {
        Text(`日志数: ${this.logCount}`)
          .fontSize(13)
        Text(`总测试: ~40项`)
          .fontSize(13)
      }
      .padding(5)
      .width('100%')

      List() {
        ForEach(this.logs, (log: TestLog, index: number) => {
          ListItem() {
            Text(`[${log.time}] ${log.msg}`)
              .fontSize(11)
              .fontColor(log.color)
              .width('100%')
              .maxLines(3)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }
          .margin(1)
          .padding(3)
        })
      }
      .width('100%')
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
  }
}