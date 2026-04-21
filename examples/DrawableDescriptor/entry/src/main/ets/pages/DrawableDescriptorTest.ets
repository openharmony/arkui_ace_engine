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

import { image } from '@kit.ImageKit';
import { DrawableDescriptor, LayeredDrawableDescriptor, PixelMapDrawableDescriptor, AnimatedDrawableDescriptor } from '@kit.ArkUI';
import { photoAccessHelper } from '@kit.MediaLibraryKit';

interface TestCase {
  name: string;
  description: string;
  callback: () => void;
}

interface ImageTestConfig {
  width: number;
  height: number;
  autoResize: boolean;
  fit: ImageFit;
  repeat: ImageRepeat;
  interpolation: ImageInterpolation;
  smoothEdge: number;
  dynamicRange: DynamicRangeMode;
  matchTextDirection: boolean;
  hdrBrightness: number;
  antiAlias: boolean;
  renderMode: ImageRenderMode;
  colorFilter: number[];
}

@Entry
@Component
struct DrawableDescriptorTest {
  @State currentTabIndex: number = 0;
  @State testResults: string[] = [];
  @State isLoading: boolean = false;
  @State selectedIndex: number = 0;
  @State showAdvancedSettings: boolean = false;
  @State testConfig: ImageTestConfig = {
    width: 200,
    height: 200,
    autoResize: true,
    fit: ImageFit.Contain,
    repeat: ImageRepeat.NoRepeat,
    interpolation: ImageInterpolation.None,
    smoothEdge: 0,
    dynamicRange: DynamicRangeMode.STANDARD,
    matchTextDirection: false,
    hdrBrightness: 1.0,
    antiAlias: false,
    renderMode: ImageRenderMode.Original,
    colorFilter: []
  };

  @State animatedConfigs: AnimationOptions[] = [
    { iterations: 1, duration: 500 },
    { iterations: 1, duration: 1000 },
    { iterations: 1, duration: 2000 },
    { iterations: 1, duration: 3000 },
    { iterations: 1, duration: 5000 },
    { iterations: -1, duration: 1000 },
    { iterations: -1, duration: 2000 },
    { iterations: -1, duration: 3000 },
    { iterations: 2, duration: 1000 },
    { iterations: 3, duration: 1500 },
    { iterations: 5, duration: 2000 },
    { iterations: 10, duration: 3000 }
  ];

  @State layerConfigs: LayerConfig[] = [
    { hasForeground: true, hasBackground: true, hasMask: false },
    { hasForeground: true, hasBackground: false, hasMask: false },
    { hasForeground: false, hasBackground: true, hasMask: false },
    { hasForeground: true, hasBackground: true, hasMask: true },
    { hasForeground: false, hasBackground: false, hasMask: true }
  ];

  @State fitOptions: ImageFit[] = [
    ImageFit.Contain,
    ImageFit.Cover,
    ImageFit.Fill,
    ImageFit.None,
    ImageFit.ScaleDown,
    ImageFit.FitStart,
    ImageFit.FitEnd
  ];

  @State repeatOptions: ImageRepeat[] = [
    ImageRepeat.NoRepeat,
    ImageRepeat.X,
    ImageRepeat.Y,
    ImageRepeat.XY
  ];

  @State interpolationOptions: ImageInterpolation[] = [
    ImageInterpolation.None,
    ImageInterpolation.Low,
    ImageInterpolation.Medium,
    ImageInterpolation.High
  ];

  @State dynamicRangeOptions: DynamicRangeMode[] = [
    DynamicRangeMode.STANDARD,
    DynamicRangeMode.HIGH,
    DynamicRangeMode.CONSTRAINT
  ];

  @State renderModeOptions: ImageRenderMode[] = [
    ImageRenderMode.Original,
    ImageRenderMode.Template
  ];

  private resManager = this.getUIContext().getHostContext()?.resourceManager;
  private testCases: TestCase[] = [
    { name: 'Basic DrawableDescriptor', description: 'Create basic DrawableDescriptor from resource', callback: () => this.testBasicDrawableDescriptor() },
    { name: 'Get PixelMap', description: 'Test getPixelMap() method', callback: () => this.testGetPixelMap() },
    { name: 'LayeredDrawable from Resource', description: 'Create LayeredDrawableDescriptor from JSON resource', callback: () => this.testLayeredDrawableFromResource() },
    { name: 'LayeredDrawable Get Layers', description: 'Test getForeground/getBackground methods', callback: () => this.testLayeredGetLayers() },
    { name: 'PixelMapDrawableDescriptor Create', description: 'Create PixelMapDrawableDescriptor', callback: () => this.testPixelMapDrawableDescriptor() },
    { name: 'LayeredDrawable with PixelMap', description: 'Create LayeredDrawableDescriptor with PixelMap', callback: () => this.testLayeredWithPixelMap() },
    { name: 'AnimatedDrawable Basic', description: 'Create basic AnimatedDrawableDescriptor', callback: () => this.testAnimatedDrawableBasic() },
    { name: 'AnimatedDrawable Iterations', description: 'Test different iteration values', callback: () => this.testAnimatedDrawableIterations() },
    { name: 'AnimatedDrawable Duration', description: 'Test different duration values', callback: () => this.testAnimatedDrawableDuration() },
    { name: 'AnimatedDrawable Play Mode', description: 'Test Normal and Reverse play modes', callback: () => this.testAnimatedDrawablePlayMode() },
    { name: 'ImageFit Contain', description: 'Test ImageFit.Contain', callback: () => this.testImageFitContain() },
    { name: 'ImageFit Cover', description: 'Test ImageFit.Cover', callback: () => this.testImageFitCover() },
    { name: 'ImageFit Fill', description: 'Test ImageFit.Fill', callback: () => this.testImageFitFill() },
    { name: 'ImageFit None', description: 'Test ImageFit.None', callback: () => this.testImageFitNone() },
    { name: 'ImageFit ScaleDown', description: 'Test ImageFit.ScaleDown', callback: () => this.testImageFitScaleDown() },
    { name: 'ImageRepeat NoRepeat', description: 'Test ImageRepeat.NoRepeat', callback: () => this.testImageRepeatNoRepeat() },
    { name: 'ImageRepeat X', description: 'Test ImageRepeat.X', callback: () => this.testImageRepeatX() },
    { name: 'ImageRepeat Y', description: 'Test ImageRepeat.Y', callback: () => this.testImageRepeatY() },
    { name: 'ImageRepeat XY', description: 'Test ImageRepeat.XY', callback: () => this.testImageRepeatXY() },
    { name: 'Interpolation None', description: 'Test ImageInterpolation.None', callback: () => this.testInterpolationNone() },
    { name: 'Interpolation Low', description: 'Test ImageInterpolation.Low', callback: () => this.testInterpolationLow() },
    { name: 'Interpolation Medium', description: 'Test ImageInterpolation.Medium', callback: () => this.testInterpolationMedium() },
    { name: 'Interpolation High', description: 'Test ImageInterpolation.High', callback: () => this.testInterpolationHigh() },
    { name: 'SmoothEdge 0', description: 'Test smoothEdge 0', callback: () => this.testSmoothEdge0() },
    { name: 'SmoothEdge 1', description: 'Test smoothEdge 1', callback: () => this.testSmoothEdge1() },
    { name: 'SmoothEdge 2', description: 'Test smoothEdge 2', callback: () => this.testSmoothEdge2() },
    { name: 'DynamicRange Standard', description: 'Test DynamicRangeMode.STANDARD', callback: () => this.testDynamicRangeStandard() },
    { name: 'DynamicRange High', description: 'Test DynamicRangeMode.HIGH', callback: () => this.testDynamicRangeHigh() },
    { name: 'DynamicRange Constraint', description: 'Test DynamicRangeMode.CONSTRAINT', callback: () => this.testDynamicRangeConstraint() },
    { name: 'MatchTextDirection False', description: 'Test matchTextDirection false', callback: () => this.testMatchTextDirectionFalse() },
    { name: 'MatchTextDirection True', description: 'Test matchTextDirection true', callback: () => this.testMatchTextDirectionTrue() },
    { name: 'HdrBrightness 0.5', description: 'Test hdrBrightness 0.5', callback: () => this.testHdrBrightnessLow() },
    { name: 'HdrBrightness 1.0', description: 'Test hdrBrightness 1.0', callback: () => this.testHdrBrightnessNormal() },
    { name: 'HdrBrightness 1.5', description: 'Test hdrBrightness 1.5', callback: () => this.testHdrBrightnessHigh() },
    { name: 'AntiAlias False', description: 'Test antiAlias false', callback: () => this.testAntiAliasFalse() },
    { name: 'AntiAlias True', description: 'Test antiAlias true', callback: () => this.testAntiAliasTrue() },
    { name: 'RenderMode Original', description: 'Test ImageRenderMode.Original', callback: () => this.testRenderModeOriginal() },
    { name: 'RenderMode Template', description: 'Test ImageRenderMode.Template', callback: () => this.testRenderModeTemplate() },
    { name: 'Layer Foreground Only', description: 'Test LayeredDrawable with foreground only', callback: () => this.testLayeredForegroundOnly() },
    { name: 'Layer Background Only', description: 'Test LayeredDrawable with background only', callback: () => this.testLayeredBackgroundOnly() },
    { name: 'Layer With Mask', description: 'Test LayeredDrawable with mask', callback: () => this.testLayeredWithMask() },
    { name: 'Multiple Drawables 10', description: 'Create 10 drawables', callback: () => this.testMultipleDrawables10() },
    { name: 'Multiple Drawables 50', description: 'Create 50 drawables', callback: () => this.testMultipleDrawables50() },
    { name: 'Multiple Drawables 100', description: 'Create 100 drawables', callback: () => this.testMultipleDrawables100() },
    { name: 'Resource ID Types', description: 'Test different resource ID types', callback: () => this.testResourceIdTypes() },
    { name: 'PixelMap Creation', description: 'Test PixelMap creation', callback: () => this.testPixelMapCreation() },
    { name: 'Error Handling Invalid', description: 'Test error handling with invalid input', callback: () => this.testErrorHandling() },
    { name: 'Performance 100', description: 'Performance test 100 drawables', callback: () => this.testPerformance100() },
    { name: 'Performance 500', description: 'Performance test 500 drawables', callback: () => this.testPerformance500() },
    { name: 'State Changes', description: 'Test drawable state changes', callback: () => this.testDrawableStateChanges() },
    { name: 'Animation Options Combo 1', description: 'Test animation with iterations:1,duration:500', callback: () => this.testAnimationCombo1() },
    { name: 'Animation Options Combo 2', description: 'Test animation with iterations:-1,duration:2000', callback: () => this.testAnimationCombo2() },
    { name: 'Animation Options Combo 3', description: 'Test animation with iterations:3,duration:1500', callback: () => this.testAnimationCombo3() }
  ];

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.testResults.unshift(`[${timestamp}] ${message}`);
    if (this.testResults.length > 200) {
      this.testResults.pop();
    }
  }

  async testBasicDrawableDescriptor(): Promise<void> {
    try {
      this.addLog('=== Test: Basic DrawableDescriptor ===');
      let drawable: DrawableDescriptor = null;
      if (this.resManager) {
        drawable = this.resManager.getDrawableDescriptor($r('app.media.icon').id) as DrawableDescriptor;
      }
      if (drawable) {
        this.addLog('SUCCESS: Basic DrawableDescriptor created');
        this.addLog(`  - Resource ID: ${$r('app.media.icon').id}`);
      } else {
        this.addLog('INFO: DrawableDescriptor not available in this context');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testGetPixelMap(): Promise<void> {
    try {
      this.addLog('=== Test: Get PixelMap ===');
      if (this.resManager) {
        const drawable = this.resManager.getDrawableDescriptor($r('app.media.icon').id) as DrawableDescriptor;
        if (drawable && drawable.getPixelMap) {
          const pixelMap = drawable.getPixelMap();
          if (pixelMap) {
            this.addLog('SUCCESS: getPixelMap() returned PixelMap');
          } else {
            this.addLog('INFO: PixelMap is null');
          }
        } else {
          this.addLog('INFO: getPixelMap not available');
        }
      } else {
        this.addLog('INFO: Resource manager not available');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testLayeredDrawableFromResource(): Promise<void> {
    try {
      this.addLog('=== Test: LayeredDrawable from Resource ===');
      if (this.resManager) {
        const layeredDrawable = this.resManager.getDrawableDescriptor($r('app.media.layered_image').id) as LayeredDrawableDescriptor;
        if (layeredDrawable) {
          this.addLog('SUCCESS: LayeredDrawableDescriptor created from resource');
          this.addLog(`  - Resource ID: ${$r('app.media.layered_image').id}`);
        } else {
          this.addLog('INFO: LayeredDrawableDescriptor is null');
        }
      } else {
        this.addLog('INFO: Resource manager not available');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testLayeredGetLayers(): Promise<void> {
    try {
      this.addLog('=== Test: LayeredDrawable Get Layers ===');
      if (this.resManager) {
        const layeredDrawable = this.resManager.getDrawableDescriptor($r('app.media.layered_image').id) as LayeredDrawableDescriptor;
        if (layeredDrawable) {
          const foreground = layeredDrawable.getForeground();
          const background = layeredDrawable.getBackground();
          const mask = layeredDrawable.getMask ? layeredDrawable.getMask() : null;
          this.addLog('SUCCESS: LayeredDrawable layers retrieved');
          this.addLog(`  - Foreground: ${foreground ? 'available' : 'null'}`);
          this.addLog(`  - Background: ${background ? 'available' : 'null'}`);
          this.addLog(`  - Mask: ${mask ? 'available' : 'null'}`);
        } else {
          this.addLog('INFO: LayeredDrawableDescriptor is null');
        }
      } else {
        this.addLog('INFO: Resource manager not available');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testPixelMapDrawableDescriptor(): Promise<void> {
    try {
      this.addLog('=== Test: PixelMapDrawableDescriptor Create ===');
      const pixelMapDrawable = new PixelMapDrawableDescriptor();
      if (pixelMapDrawable) {
        this.addLog('SUCCESS: PixelMapDrawableDescriptor created');
        this.addLog('  - Default constructor');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testLayeredWithPixelMap(): Promise<void> {
    try {
      this.addLog('=== Test: LayeredDrawable with PixelMap ===');
      const foregroundDrawable = new PixelMapDrawableDescriptor();
      const backgroundDrawable = new PixelMapDrawableDescriptor();
      const layeredDrawable = new LayeredDrawableDescriptor(foregroundDrawable, backgroundDrawable, null);
      if (layeredDrawable) {
        this.addLog('SUCCESS: LayeredDrawableDescriptor created with PixelMap');
        this.addLog('  - Foreground: PixelMapDrawableDescriptor');
        this.addLog('  - Background: PixelMapDrawableDescriptor');
        this.addLog('  - Mask: null');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testAnimatedDrawableBasic(): Promise<void> {
    try {
      this.addLog('=== Test: AnimatedDrawable Basic ===');
      const animatedDrawable = new AnimatedDrawableDescriptor($r('app.media.flower'), { iterations: 1, duration: 1000 });
      if (animatedDrawable) {
        this.addLog('SUCCESS: AnimatedDrawableDescriptor created');
        this.addLog('  - iterations: 1');
        this.addLog('  - duration: 1000ms');
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testAnimatedDrawableIterations(): Promise<void> {
    try {
      this.addLog('=== Test: AnimatedDrawable Iterations ===');
      const iterations = [-1, 0, 1, 2, 3, 5, 10];
      for (const iter of iterations) {
        const animated = new AnimatedDrawableDescriptor($r('app.media.flower'), { iterations: iter, duration: 1000 });
        this.addLog(`  - iterations: ${iter} (${iter === -1 ? 'infinite' : iter === 0 ? 'no play' : iter + ' times'})`);
      }
      this.addLog('SUCCESS: All iteration values tested');
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testAnimatedDrawableDuration(): Promise<void> {
    try {
      this.addLog('=== Test: AnimatedDrawable Duration ===');
      const durations = [100, 200, 500, 1000, 2000, 3000, 5000, 10000];
      for (const dur of durations) {
        this.addLog(`  - duration: ${dur}ms`);
      }
      this.addLog('SUCCESS: All duration values logged');
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testAnimatedDrawablePlayMode(): Promise<void> {
    try {
      this.addLog('=== Test: AnimatedDrawable Play Mode ===');
      const playModeNormal = new AnimatedDrawableDescriptor($r('app.media.flower'), { 
        iterations: 1, 
        duration: 1000,
        playMode: PlayMode.Normal 
      });
      const playModeReverse = new AnimatedDrawableDescriptor($r('app.media.flower'), { 
        iterations: 1, 
        duration: 1000,
        playMode: PlayMode.Reverse 
      });
      this.addLog('SUCCESS: Both play modes created');
      this.addLog('  - PlayMode.Normal');
      this.addLog('  - PlayMode.Reverse');
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testImageFitContain(): Promise<void> {
    this.addLog('=== Test: ImageFit Contain ===');
    this.testConfig.fit = ImageFit.Contain;
    this.addLog('SUCCESS: Set ImageFit.Contain');
  }

  async testImageFitCover(): Promise<void> {
    this.addLog('=== Test: ImageFit Cover ===');
    this.testConfig.fit = ImageFit.Cover;
    this.addLog('SUCCESS: Set ImageFit.Cover');
  }

  async testImageFitFill(): Promise<void> {
    this.addLog('=== Test: ImageFit Fill ===');
    this.testConfig.fit = ImageFit.Fill;
    this.addLog('SUCCESS: Set ImageFit.Fill');
  }

  async testImageFitNone(): Promise<void> {
    this.addLog('=== Test: ImageFit None ===');
    this.testConfig.fit = ImageFit.None;
    this.addLog('SUCCESS: Set ImageFit.None');
  }

  async testImageFitScaleDown(): Promise<void> {
    this.addLog('=== Test: ImageFit ScaleDown ===');
    this.testConfig.fit = ImageFit.ScaleDown;
    this.addLog('SUCCESS: Set ImageFit.ScaleDown');
  }

  async testImageRepeatNoRepeat(): Promise<void> {
    this.addLog('=== Test: ImageRepeat NoRepeat ===');
    this.testConfig.repeat = ImageRepeat.NoRepeat;
    this.addLog('SUCCESS: Set ImageRepeat.NoRepeat');
  }

  async testImageRepeatX(): Promise<void> {
    this.addLog('=== Test: ImageRepeat X ===');
    this.testConfig.repeat = ImageRepeat.X;
    this.addLog('SUCCESS: Set ImageRepeat.X');
  }

  async testImageRepeatY(): Promise<void> {
    this.addLog('=== Test: ImageRepeat Y ===');
    this.testConfig.repeat = ImageRepeat.Y;
    this.addLog('SUCCESS: Set ImageRepeat.Y');
  }

  async testImageRepeatXY(): Promise<void> {
    this.addLog('=== Test: ImageRepeat XY ===');
    this.testConfig.repeat = ImageRepeat.XY;
    this.addLog('SUCCESS: Set ImageRepeat.XY');
  }

  async testInterpolationNone(): Promise<void> {
    this.addLog('=== Test: ImageInterpolation None ===');
    this.testConfig.interpolation = ImageInterpolation.None;
    this.addLog('SUCCESS: Set ImageInterpolation.None');
  }

  async testInterpolationLow(): Promise<void> {
    this.addLog('=== Test: ImageInterpolation Low ===');
    this.testConfig.interpolation = ImageInterpolation.Low;
    this.addLog('SUCCESS: Set ImageInterpolation.Low');
  }

  async testInterpolationMedium(): Promise<void> {
    this.addLog('=== Test: ImageInterpolation Medium ===');
    this.testConfig.interpolation = ImageInterpolation.Medium;
    this.addLog('SUCCESS: Set ImageInterpolation.Medium');
  }

  async testInterpolationHigh(): Promise<void> {
    this.addLog('=== Test: ImageInterpolation High ===');
    this.testConfig.interpolation = ImageInterpolation.High;
    this.addLog('SUCCESS: Set ImageInterpolation.High');
  }

  async testSmoothEdge0(): Promise<void> {
    this.addLog('=== Test: SmoothEdge 0 ===');
    this.testConfig.smoothEdge = 0;
    this.addLog('SUCCESS: Set smoothEdge = 0');
  }

  async testSmoothEdge1(): Promise<void> {
    this.addLog('=== Test: SmoothEdge 1 ===');
    this.testConfig.smoothEdge = 1;
    this.addLog('SUCCESS: Set smoothEdge = 1');
  }

  async testSmoothEdge2(): Promise<void> {
    this.addLog('=== Test: SmoothEdge 2 ===');
    this.testConfig.smoothEdge = 2;
    this.addLog('SUCCESS: Set smoothEdge = 2');
  }

  async testDynamicRangeStandard(): Promise<void> {
    this.addLog('=== Test: DynamicRange Standard ===');
    this.testConfig.dynamicRange = DynamicRangeMode.STANDARD;
    this.addLog('SUCCESS: Set DynamicRangeMode.STANDARD');
  }

  async testDynamicRangeHigh(): Promise<void> {
    this.addLog('=== Test: DynamicRange High ===');
    this.testConfig.dynamicRange = DynamicRangeMode.HIGH;
    this.addLog('SUCCESS: Set DynamicRangeMode.HIGH');
  }

  async testDynamicRangeConstraint(): Promise<void> {
    this.addLog('=== Test: DynamicRange Constraint ===');
    this.testConfig.dynamicRange = DynamicRangeMode.CONSTRAINT;
    this.addLog('SUCCESS: Set DynamicRangeMode.CONSTRAINT');
  }

  async testMatchTextDirectionFalse(): Promise<void> {
    this.addLog('=== Test: MatchTextDirection False ===');
    this.testConfig.matchTextDirection = false;
    this.addLog('SUCCESS: Set matchTextDirection = false');
  }

  async testMatchTextDirectionTrue(): Promise<void> {
    this.addLog('=== Test: MatchTextDirection True ===');
    this.testConfig.matchTextDirection = true;
    this.addLog('SUCCESS: Set matchTextDirection = true');
  }

  async testHdrBrightnessLow(): Promise<void> {
    this.addLog('=== Test: HdrBrightness Low ===');
    this.testConfig.hdrBrightness = 0.5;
    this.addLog('SUCCESS: Set hdrBrightness = 0.5');
  }

  async testHdrBrightnessNormal(): Promise<void> {
    this.addLog('=== Test: HdrBrightness Normal ===');
    this.testConfig.hdrBrightness = 1.0;
    this.addLog('SUCCESS: Set hdrBrightness = 1.0');
  }

  async testHdrBrightnessHigh(): Promise<void> {
    this.addLog('=== Test: HdrBrightness High ===');
    this.testConfig.hdrBrightness = 1.5;
    this.addLog('SUCCESS: Set hdrBrightness = 1.5');
  }

  async testAntiAliasFalse(): Promise<void> {
    this.addLog('=== Test: AntiAlias False ===');
    this.testConfig.antiAlias = false;
    this.addLog('SUCCESS: Set antiAlias = false');
  }

  async testAntiAliasTrue(): Promise<void> {
    this.addLog('=== Test: AntiAlias True ===');
    this.testConfig.antiAlias = true;
    this.addLog('SUCCESS: Set antiAlias = true');
  }

  async testRenderModeOriginal(): Promise<void> {
    this.addLog('=== Test: RenderMode Original ===');
    this.testConfig.renderMode = ImageRenderMode.Original;
    this.addLog('SUCCESS: Set ImageRenderMode.Original');
  }

  async testRenderModeTemplate(): Promise<void> {
    this.addLog('=== Test: RenderMode Template ===');
    this.testConfig.renderMode = ImageRenderMode.Template;
    this.addLog('SUCCESS: Set ImageRenderMode.Template');
  }

  async testLayeredForegroundOnly(): Promise<void> {
    try {
      this.addLog('=== Test: LayeredDrawable with foreground only ===');
      const foregroundDrawable = new PixelMapDrawableDescriptor();
      const layeredDrawable = new LayeredDrawableDescriptor(foregroundDrawable, null, null);
      if (layeredDrawable) {
        const fg = layeredDrawable.getForeground();
        this.addLog('SUCCESS: Foreground only layer created');
        this.addLog(`  - Foreground: ${fg ? 'available' : 'null'}`);
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testLayeredBackgroundOnly(): Promise<void> {
    try {
      this.addLog('=== Test: LayeredDrawable with background only ===');
      const backgroundDrawable = new PixelMapDrawableDescriptor();
      const layeredDrawable = new LayeredDrawableDescriptor(null, backgroundDrawable, null);
      if (layeredDrawable) {
        const bg = layeredDrawable.getBackground();
        this.addLog('SUCCESS: Background only layer created');
        this.addLog(`  - Background: ${bg ? 'available' : 'null'}`);
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testLayeredWithMask(): Promise<void> {
    try {
      this.addLog('=== Test: LayeredDrawable with mask ===');
      const foregroundDrawable = new PixelMapDrawableDescriptor();
      const backgroundDrawable = new PixelMapDrawableDescriptor();
      const maskDrawable = new PixelMapDrawableDescriptor();
      const layeredDrawable = new LayeredDrawableDescriptor(foregroundDrawable, backgroundDrawable, maskDrawable);
      if (layeredDrawable) {
        const mask = layeredDrawable.getMask ? layeredDrawable.getMask() : null;
        this.addLog('SUCCESS: Layer with mask created');
        this.addLog(`  - Mask: ${mask ? 'available' : 'null'}`);
      }
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testMultipleDrawables10(): Promise<void> {
    try {
      this.addLog('=== Test: Multiple Drawables 10 ===');
      const drawables: DrawableDescriptor[] = [];
      for (let i = 0; i < 10; i++) {
        const drawable = new PixelMapDrawableDescriptor();
        drawables.push(drawable);
      }
      this.addLog(`SUCCESS: Created ${drawables.length} drawables`);
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testMultipleDrawables50(): Promise<void> {
    try {
      this.addLog('=== Test: Multiple Drawables 50 ===');
      const drawables: DrawableDescriptor[] = [];
      for (let i = 0; i < 50; i++) {
        const drawable = new PixelMapDrawableDescriptor();
        drawables.push(drawable);
      }
      this.addLog(`SUCCESS: Created ${drawables.length} drawables`);
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testMultipleDrawables100(): Promise<void> {
    try {
      this.addLog('=== Test: Multiple Drawables 100 ===');
      const drawables: DrawableDescriptor[] = [];
      for (let i = 0; i < 100; i++) {
        const drawable = new PixelMapDrawableDescriptor();
        drawables.push(drawable);
      }
      this.addLog(`SUCCESS: Created ${drawables.length} drawables`);
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testResourceIdTypes(): Promise<void> {
    try {
      this.addLog('=== Test: Resource ID Types ===');
      const resourceIds = [
        { id: $r('app.media.icon').id, name: 'app.media.icon' },
        { id: $r('app.media.flower').id, name: 'app.media.flower' },
        { id: $r('app.media.background').id, name: 'app.media.background' },
        { id: $r('app.media.foreground').id, name: 'app.media.foreground' }
      ];
      for (const res of resourceIds) {
        this.addLog(`  - ${res.name}: ${res.id}`);
      }
      this.addLog('SUCCESS: All resource ID types logged');
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testPixelMapCreation(): Promise<void> {
    try {
      this.addLog('=== Test: PixelMap Creation ===');
      const pixelMap = new image.ImageSource('').createPixelMap();
      if (pixelMap) {
        this.addLog('SUCCESS: PixelMap created');
      } else {
        this.addLog('INFO: PixelMap creation requires valid image source');
      }
    } catch (e) {
      this.addLog(`INFO: ${e.message}`);
    }
  }

  async testErrorHandling(): Promise<void> {
    try {
      this.addLog('=== Test: Error Handling ===');
      try {
        const invalidDrawable = new LayeredDrawableDescriptor(null as any, null as any, null as any);
        this.addLog('INFO: Created with null parameters');
      } catch (e) {
        this.addLog('  - Caught expected error');
      }
      this.addLog('SUCCESS: Error handling tested');
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testPerformance100(): Promise<void> {
    try {
      this.addLog('=== Test: Performance 100 ===');
      const startTime = Date.now();
      for (let i = 0; i < 100; i++) {
        const drawable = new PixelMapDrawableDescriptor();
      }
      const elapsed = Date.now() - startTime;
      this.addLog(`SUCCESS: Created 100 drawables in ${elapsed}ms`);
      this.addLog(`  - Average: ${(elapsed / 100).toFixed(2)}ms per drawable`);
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testPerformance500(): Promise<void> {
    try {
      this.addLog('=== Test: Performance 500 ===');
      const startTime = Date.now();
      for (let i = 0; i < 500; i++) {
        const drawable = new PixelMapDrawableDescriptor();
      }
      const elapsed = Date.now() - startTime;
      this.addLog(`SUCCESS: Created 500 drawables in ${elapsed}ms`);
      this.addLog(`  - Average: ${(elapsed / 500).toFixed(2)}ms per drawable`);
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testDrawableStateChanges(): Promise<void> {
    try {
      this.addLog('=== Test: Drawable State Changes ===');
      let drawable = new PixelMapDrawableDescriptor();
      this.addLog('  - Initial state created');
      drawable = new PixelMapDrawableDescriptor();
      this.addLog('  - After first recreate');
      drawable = new PixelMapDrawableDescriptor();
      this.addLog('  - After second recreate');
      this.addLog('SUCCESS: State changes tested');
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testAnimationCombo1(): Promise<void> {
    try {
      this.addLog('=== Test: Animation Combo 1 ===');
      const animated = new AnimatedDrawableDescriptor($r('app.media.flower'), { iterations: 1, duration: 500 });
      this.addLog('SUCCESS: Animation with iterations:1,duration:500 created');
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testAnimationCombo2(): Promise<void> {
    try {
      this.addLog('=== Test: Animation Combo 2 ===');
      const animated = new AnimatedDrawableDescriptor($r('app.media.flower'), { iterations: -1, duration: 2000 });
      this.addLog('SUCCESS: Animation with iterations:-1,duration:2000 created');
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  async testAnimationCombo3(): Promise<void> {
    try {
      this.addLog('=== Test: Animation Combo 3 ===');
      const animated = new AnimatedDrawableDescriptor($r('app.media.flower'), { iterations: 3, duration: 1500 });
      this.addLog('SUCCESS: Animation with iterations:3,duration:1500 created');
    } catch (e) {
      this.addLog(`ERROR: ${e.message}`);
    }
  }

  runTest(index: number) {
    if (index >= 0 && index < this.testCases.length) {
      this.addLog(`========================================`);
      this.addLog(`Running: ${this.testCases[index].name}`);
      this.addLog(`Description: ${this.testCases[index].description}`);
      this.addLog(`========================================`);
      this.testCases[index].callback();
    }
  }

  runAllTests() {
    this.testResults = [];
    this.addLog('========================================');
    this.addLog('Starting all DrawableDescriptor tests');
    this.addLog(`Total tests: ${this.testCases.length}`);
    this.addLog('========================================');
    for (let i = 0; i < this.testCases.length; i++) {
      this.runTest(i);
    }
    this.addLog('========================================');
    this.addLog('All tests completed');
    this.addLog('========================================');
  }

  runCategoryTests(startIndex: number, endIndex: number) {
    for (let i = startIndex; i < endIndex && i < this.testCases.length; i++) {
      this.runTest(i);
    }
  }

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentTabIndex }) {
        TabContent() {
          this.buildDrawableTestsTab()
        }
        .tabBar('Basic Tests')

        TabContent() {
          this.buildImagePropertiesTab()
        }
        .tabBar('Image Props')

        TabContent() {
          this.buildLayeredTestsTab()
        }
        .tabBar('Layered')

        TabContent() {
          this.buildAnimatedTestsTab()
        }
        .tabBar('Animated')

        TabContent() {
          this.buildPerformanceTestsTab()
        }
        .tabBar('Performance')

        TabContent() {
          this.buildLogTab()
        }
        .tabBar('Logs')
      }
      .onChange((index: number) => {
        this.currentTabIndex = index;
      })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  buildDrawableTestsTab() {
    Column() {
      List() {
        ListItem() {
          Button('Test 1: Basic DrawableDescriptor')
            .width('90%')
            .onClick(() => this.runTest(0))
        }
        .margin(3)

        ListItem() {
          Button('Test 2: Get PixelMap')
            .width('90%')
            .onClick(() => this.runTest(1))
        }
        .margin(3)

        ListItem() {
          Button('Test 3: LayeredDrawable from Resource')
            .width('90%')
            .onClick(() => this.runTest(2))
        }
        .margin(3)

        ListItem() {
          Button('Test 4: Get Layers')
            .width('90%')
            .onClick(() => this.runTest(3))
        }
        .margin(3)

        ListItem() {
          Button('Test 5: PixelMapDrawableDescriptor')
            .width('90%')
            .onClick(() => this.runTest(4))
        }
        .margin(3)

        ListItem() {
          Button('Test 6: Layered with PixelMap')
            .width('90%')
            .onClick(() => this.runTest(5))
        }
        .margin(3)

        ListItem() {
          Button('Run Basic Tests (1-6)')
            .width('90%')
            .onClick(() => this.runCategoryTests(0, 6))
        }
        .margin(3)
      }
      .width('100%')
      .height('100%')
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  buildImagePropertiesTab() {
    Scroll() {
      Column({ space: 15 }) {
        Column({ space: 10 }) {
          Text('Image Size Configuration')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)

          Row({ space: 10 }) {
            Text('Width:').width(80)
            TextInput({ text: this.testConfig.width.toString() })
              .width(120)
              .onChange((value: string) => {
                this.testConfig.width = parseInt(value) || 200;
              })
          }

          Row({ space: 10 }) {
            Text('Height:').width(80)
            TextInput({ text: this.testConfig.height.toString() })
              .width(120)
              .onChange((value: string) => {
                this.testConfig.height = parseInt(value) || 200;
              })
          }

          Row({ space: 10 }) {
            Text('AutoResize:').width(80)
            Toggle({ isOn: this.testConfig.autoResize, type: ToggleType.Switch })
              .onChange((isOn: boolean) => {
                this.testConfig.autoResize = isOn;
              })
          }
        }
        .padding(10)
        .backgroundColor('#F0F0F0')
        .borderRadius(10)

        Column({ space: 10 }) {
          Text('ImageFit')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.fitOptions, (fit: ImageFit, index: number) => {
              Button(fit.toString())
                .margin(5)
                .onClick(() => {
                  this.testConfig.fit = fit;
                  this.addLog(`Set ImageFit: ${fit}`);
                })
            })
          }
        }
        .padding(10)

        Column({ space: 10 }) {
          Text('ImageRepeat')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.repeatOptions, (repeat: ImageRepeat, index: number) => {
              Button(repeat.toString())
                .margin(5)
                .onClick(() => {
                  this.testConfig.repeat = repeat;
                  this.addLog(`Set ImageRepeat: ${repeat}`);
                })
            })
          }
        }
        .padding(10)

        Column({ space: 10 }) {
          Text('ImageInterpolation')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.interpolationOptions, (interp: ImageInterpolation, index: number) => {
              Button(interp.toString())
                .margin(5)
                .onClick(() => {
                  this.testConfig.interpolation = interp;
                  this.addLog(`Set ImageInterpolation: ${interp}`);
                })
            })
          }
        }
        .padding(10)

        Column({ space: 10 }) {
          Text('DynamicRangeMode')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.dynamicRangeOptions, (mode: DynamicRangeMode, index: number) => {
              Button(mode.toString())
                .margin(5)
                .onClick(() => {
                  this.testConfig.dynamicRange = mode;
                  this.addLog(`Set DynamicRangeMode: ${mode}`);
                })
            })
          }
        }
        .padding(10)

        Column({ space: 10 }) {
          Text('ImageRenderMode')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.renderModeOptions, (mode: ImageRenderMode, index: number) => {
              Button(mode.toString())
                .margin(5)
                .onClick(() => {
                  this.testConfig.renderMode = mode;
                  this.addLog(`Set ImageRenderMode: ${mode}`);
                })
            })
          }
        }
        .padding(10)

        Column({ space: 10 }) {
          Text('SmoothEdge')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 10 }) {
            Text('Value:').width(60)
            TextInput({ text: this.testConfig.smoothEdge.toString() })
              .width(100)
              .onChange((value: string) => {
                this.testConfig.smoothEdge = parseFloat(value) || 0;
              })
          }
        }
        .padding(10)

        Column({ space: 10 }) {
          Text('HdrBrightness')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 10 }) {
            Text('Value:').width(60)
            TextInput({ text: this.testConfig.hdrBrightness.toString() })
              .width(100)
              .onChange((value: string) => {
                this.testConfig.hdrBrightness = parseFloat(value) || 1.0;
              })
          }
        }
        .padding(10)

        Column({ space: 10 }) {
          Text('Other Options')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 10 }) {
            Text('MatchTextDir:').width(100)
            Toggle({ isOn: this.testConfig.matchTextDirection, type: ToggleType.Switch })
              .onChange((isOn: boolean) => {
                this.testConfig.matchTextDirection = isOn;
              })
          }

          Row({ space: 10 }) {
            Text('AntiAlias:').width(100)
            Toggle({ isOn: this.testConfig.antiAlias, type: ToggleType.Switch })
              .onChange((isOn: boolean) => {
                this.testConfig.antiAlias = isOn;
              })
          }
        }
        .padding(10)

        Button('Run All Image Property Tests (10-40)')
          .width('90%')
          .onClick(() => this.runCategoryTests(10, 40))
          .margin(10)
      }
      .padding(10)
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
  }

  @Builder
  buildLayeredTestsTab() {
    Column({ space: 10 }) {
      Button('Test 41: Foreground Only')
        .width('90%')
        .onClick(() => this.runTest(40))
        .margin(5)

      Button('Test 42: Background Only')
        .width('90%')
        .onClick(() => this.runTest(41))
        .margin(5)

      Button('Test 43: With Mask')
        .width('90%')
        .onClick(() => this.runTest(42))
        .margin(5)

      Button('Run All Layered Tests (38-43)')
        .width('90%')
        .onClick(() => this.runCategoryTests(38, 44))
        .margin(5)
    }
    .width('100%')
    .height('100%')
    .padding(10)
  }

  @Builder
  buildAnimatedTestsTab() {
    Scroll() {
      Column({ space: 15 }) {
        Text('AnimatedDrawableDescriptor Tests')
          .fontSize(18)
          .fontWeight(FontWeight.Bold)

        Column({ space: 10 }) {
          Text('Basic Animation Tests')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Button('Test 7: AnimatedDrawable Basic')
            .width('90%')
            .onClick(() => this.runTest(6))

          Button('Test 8: Iterations')
            .width('90%')
            .onClick(() => this.runTest(7))

          Button('Test 9: Duration')
            .width('90%')
            .onClick(() => this.runTest(8))

          Button('Test 10: Play Mode')
            .width('90%')
            .onClick(() => this.runTest(9))
        }
        .padding(10)
        .backgroundColor('#F0F0F0')
        .borderRadius(10)

        Column({ space: 10 }) {
          Text('Animation Combinations')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          ForEach(this.animatedConfigs, (config: AnimationOptions, index: number) => {
            Button(`Combo ${index + 1}: iter:${config.iterations}, dur:${config.duration}`)
              .width('90%')
              .margin(3)
              .onClick(() => {
                this.addLog(`Testing animation config: ${JSON.stringify(config)}`);
              })
          })
        }
        .padding(10)

        Button('Run All Animated Tests (6-10, 47-49)')
          .width('90%')
          .onClick(() => {
            this.runCategoryTests(6, 10);
            this.runCategoryTests(47, 50);
          })
          .margin(10)
      }
      .padding(10)
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
  }

  @Builder
  buildPerformanceTestsTab() {
    Column({ space: 10 }) {
      Text('Performance Tests')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Button('Test 44: Multiple Drawables 10')
        .width('90%')
        .onClick(() => this.runTest(43))
        .margin(5)

      Button('Test 45: Multiple Drawables 50')
        .width('90%')
        .onClick(() => this.runTest(44))
        .margin(5)

      Button('Test 46: Multiple Drawables 100')
        .width('90%')
        .onClick(() => this.runTest(45))
        .margin(5)

      Button('Test 50: Performance 100')
        .width('90%')
        .onClick(() => this.runTest(49))
        .margin(5)

      Button('Test 51: Performance 500')
        .width('90%')
        .onClick(() => this.runTest(50))
        .margin(5)

      Button('Test 52: State Changes')
        .width('90%')
        .onClick(() => this.runTest(51))
        .margin(5)

      Divider()

      Button('Run All Performance Tests')
        .width('90%')
        .onClick(() => this.runCategoryTests(43, 52))
        .margin(5)
    }
    .width('100%')
    .height('100%')
    .padding(10)
  }

  @Builder
  buildLogTab() {
    Column() {
      Row({ space: 10 }) {
        Button('Run All Tests')
          .onClick(() => this.runAllTests())
          .width('40%')

        Button('Clear Logs')
          .onClick(() => {
            this.testResults = [];
          })
          .width('40%')
      }
      .padding(10)
      .width('100%')

      Row({ space: 10 }) {
        Text(`Total Tests: ${this.testCases.length}`)
          .fontSize(14)
        Text(`Logs: ${this.testResults.length}`)
          .fontSize(14)
      }
      .padding(5)
      .width('100%')

      List() {
        ForEach(this.testResults, (log: string, index: number) => {
          ListItem() {
            Text(log)
              .fontSize(11)
              .width('100%')
              .maxLines(2)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }
          .margin(1)
          .padding(2)
        })
      }
      .width('100%')
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
  }
}

interface LayerConfig {
  hasForeground: boolean;
  hasBackground: boolean;
  hasMask: boolean;
}

interface ExtendedTestCase {
  name: string;
  category: string;
  description: string;
  callback: () => void;
}

@Component
struct ExtendedDrawableTests {
  @Link testResults: string[];
  private addLog: (message: string) => void = (message: string) => {};

  build() {
    Column() {
      Text('Extended Drawable Tests')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
    }
    .width('100%')
    .height('100%')
  }
}

@Component
struct ImageDisplayDemo {
  @Link drawableDescriptor: DrawableDescriptor | null;
  @Link config: ImageTestConfig;

  build() {
    Column() {
      if (this.drawableDescriptor) {
        Image(this.drawableDescriptor)
          .width(this.config.width)
          .height(this.config.height)
          .autoResize(this.config.autoResize)
          .imageFit(this.config.fit)
          .imageRepeat(this.config.repeat)
          .interpolation(this.config.interpolation)
          .smoothEdge(this.config.smoothEdge)
          .dynamicRangeMode(this.config.dynamicRange)
          .matchTextDirection(this.config.matchTextDirection)
          .hdrBrightness(this.config.hdrBrightness)
          .antiAlias(this.config.antiAlias)
          .renderMode(this.config.renderMode)
      } else {
        Text('No Drawable')
          .width(this.config.width)
          .height(this.config.height)
          .backgroundColor('#CCCCCC')
          .textAlign(TextAlign.Center)
      }
    }
  }
}

@Component
struct LayeredImageDemo {
  @Link layeredDrawable: LayeredDrawableDescriptor | null;
  widthValue: number = 200;
  heightValue: number = 200;

  build() {
    Column() {
      if (this.layeredDrawable) {
        Image(this.layeredDrawable)
          .width(this.widthValue)
          .height(this.heightValue)
      } else {
        Text('No Layered Drawable')
          .width(this.widthValue)
          .height(this.heightValue)
          .backgroundColor('#CCCCCC')
          .textAlign(TextAlign.Center)
      }
    }
  }
}

@Component
struct AnimatedImageDemo {
  @Link animatedDrawable: AnimatedDrawableDescriptor | null;
  widthValue: number = 200;
  heightValue: number = 200;
  autoPlay: boolean = true;

  build() {
    Column() {
      if (this.animatedDrawable) {
        Image(this.animatedDrawable)
          .width(this.widthValue)
          .height(this.heightValue)
          .autoPlay(this.autoPlay)
      } else {
        Text('No Animated Drawable')
          .width(this.widthValue)
          .height(this.heightValue)
          .backgroundColor('#CCCCCC')
          .textAlign(TextAlign.Center)
      }
    }
  }
}

@Builder
export function DrawableDescriptorDemoPage() {
  Column() {
    Text('DrawableDescriptor API Demo')
      .fontSize(24)
      .fontWeight(FontWeight.Bold)
      .margin(20)

    Scroll() {
      Column({ space: 20 }) {
        Text('1. DrawableDescriptor')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('Description:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('DrawableDescriptor is the base class for drawable resources. ' +
               'It supports PNG, JPG, BMP, SVG, GIF, WEBP, ASTC, and SUT formats.')
            .fontSize(12)
            .backgroundColor('#F5F5F5')
            .padding(10)

          Text('API:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('getPixelMap(): image.PixelMap')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(10)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Text('2. LayeredDrawableDescriptor')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('Description:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('LayeredDrawableDescriptor is used for layered images with foreground, ' +
               'background, and optional mask layers. The drawable.json file defines the layers.')
            .fontSize(12)
            .backgroundColor('#F5F5F5')
            .padding(10)

          Text('JSON Format:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('{"layered-image": {"background": "$media:background", "foreground": "$media:foreground"}}')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(10)

          Text('APIs:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('getForeground(): DrawableDescriptor')
            .fontSize(12)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('getBackground(): DrawableDescriptor')
            .fontSize(12)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('getMask(): DrawableDescriptor')
            .fontSize(12)
            .backgroundColor('#E3F2FD')
            .padding(5)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Text('3. PixelMapDrawableDescriptor')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('Description:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('PixelMapDrawableDescriptor can be created by passing in a PixelMap object. ' +
               'It inherits from DrawableDescriptor.')
            .fontSize(12)
            .backgroundColor('#F5F5F5')
            .padding(10)

          Text('Constructor:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('constructor(src?: image.PixelMap)')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(10)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Text('4. AnimatedDrawableDescriptor')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('Description:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('AnimatedDrawableDescriptor is used for animated images (GIF, WebP, etc.). ' +
               'It supports various animation options.')
            .fontSize(12)
            .backgroundColor('#F5F5F5')
            .padding(10)

          Text('Constructor:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('constructor(src: Resource, options: AnimationOptions)')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(10)

          Text('AnimationOptions:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('- iterations: number (default: 1, -1 for infinite)')
            .fontSize(12)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('- duration: number (default: 0)')
            .fontSize(12)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('- playMode: PlayMode (default: Normal)')
            .fontSize(12)
            .backgroundColor('#E3F2FD')
            .padding(5)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Text('Usage Example')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('Import:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text("import { DrawableDescriptor, LayeredDrawableDescriptor, PixelMapDrawableDescriptor, AnimatedDrawableDescriptor } from '@kit.ArkUI';")
            .fontSize(11)
            .backgroundColor('#FFF3E0')
            .padding(10)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Text('Resource Manager Usage')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('Code:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('let resManager = this.getUIContext().getHostContext()?.resourceManager;')
            .fontSize(12)
            .backgroundColor('#FFF3E0')
            .padding(10)
          Text('let drawable = resManager?.getDrawableDescriptor($r("app.media.icon").id) as DrawableDescriptor;')
            .fontSize(12)
            .backgroundColor('#FFF3E0')
            .padding(10)
          Text('let pixelMap = drawable.getPixelMap();')
            .fontSize(12)
            .backgroundColor('#FFF3E0')
            .padding(10)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)
      }
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}

@Builder
export function ImagePropertiesDemoPage() {
  Column() {
    Text('Image Component Properties Demo')
      .fontSize(24)
      .fontWeight(FontWeight.Bold)
      .margin(20)

    Scroll() {
      Column({ space: 20 }) {
        Text('ImageFit')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 5 }) {
          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .imageFit(ImageFit.Contain)
            Text('Contain').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .imageFit(ImageFit.Cover)
            Text('Cover').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .imageFit(ImageFit.Fill)
            Text('Fill').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .imageFit(ImageFit.None)
            Text('None').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .imageFit(ImageFit.ScaleDown)
            Text('ScaleDown').fontSize(12)
          }
        }
        .padding(10)

        Text('ImageRepeat')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 5 }) {
          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(150)
              .height(150)
              .imageRepeat(ImageRepeat.NoRepeat)
            Text('NoRepeat').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(150)
              .height(150)
              .imageRepeat(ImageRepeat.X)
            Text('X').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(150)
              .height(150)
              .imageRepeat(ImageRepeat.Y)
            Text('Y').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(150)
              .height(150)
              .imageRepeat(ImageRepeat.XY)
            Text('XY').fontSize(12)
          }
        }
        .padding(10)

        Text('ImageInterpolation')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 5 }) {
          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .interpolation(ImageInterpolation.None)
            Text('None').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .interpolation(ImageInterpolation.Low)
            Text('Low').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .interpolation(ImageInterpolation.Medium)
            Text('Medium').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .interpolation(ImageInterpolation.High)
            Text('High').fontSize(12)
          }
        }
        .padding(10)

        Text('RenderMode')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 5 }) {
          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .renderMode(ImageRenderMode.Original)
            Text('Original').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .renderMode(ImageRenderMode.Template)
            Text('Template').fontSize(12)
          }
        }
        .padding(10)

        Text('DynamicRangeMode')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 5 }) {
          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .dynamicRangeMode(DynamicRangeMode.STANDARD)
            Text('STANDARD').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .dynamicRangeMode(DynamicRangeMode.HIGH)
            Text('HIGH').fontSize(12)
          }

          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .dynamicRangeMode(DynamicRangeMode.CONSTRAINT)
            Text('CONSTRAINT').fontSize(12)
          }
        }
        .padding(10)
      }
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}

@Builder
export function LayeredDrawableDemoPage() {
  Column() {
    Text('LayeredDrawableDescriptor Demo')
      .fontSize(24)
      .fontWeight(FontWeight.Bold)
      .margin(20)

    Scroll() {
      Column({ space: 20 }) {
        Text('Creating LayeredDrawableDescriptor')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('Method 1: From Resource Manager')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('let resManager = this.getUIContext().getHostContext()?.resourceManager;')
            .fontSize(11)
            .backgroundColor('#FFF3E0')
            .padding(10)
          Text('let layeredDrawable = resManager?.getDrawableDescriptor($r("app.media.layered_image").id) as LayeredDrawableDescriptor;')
            .fontSize(11)
            .backgroundColor('#FFF3E0')
            .padding(10)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Column({ space: 10 }) {
          Text('Method 2: Using PixelMapDrawableDescriptor')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('let foreground = new PixelMapDrawableDescriptor(forePixelMap);')
            .fontSize(11)
            .backgroundColor('#E8F5E9')
            .padding(10)
          Text('let background = new PixelMapDrawableDescriptor(backPixelMap);')
            .fontSize(11)
            .backgroundColor('#E8F5E9')
            .padding(10)
          Text('let mask = new PixelMapDrawableDescriptor(maskPixelMap);')
            .fontSize(11)
            .backgroundColor('#E8F5E9')
            .padding(10)
          Text('let layered = new LayeredDrawableDescriptor(foreground, background, mask);')
            .fontSize(11)
            .backgroundColor('#E8F5E9')
            .padding(10)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Column({ space: 10 }) {
          Text('Method 3: With Partial Layers')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('// Only foreground')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('new LayeredDrawableDescriptor(foreground, null, null);')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('')
            .fontSize(11)
          Text('// Only background')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('new LayeredDrawableDescriptor(null, background, null);')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Text('Getting Layer Information')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('let foreground = layeredDrawable.getForeground();')
            .fontSize(11)
            .backgroundColor('#FFF3E0')
            .padding(10)
          Text('let background = layeredDrawable.getBackground();')
            .fontSize(11)
            .backgroundColor('#FFF3E0')
            .padding(10)
          Text('let mask = layeredDrawable.getMask();')
            .fontSize(11)
            .backgroundColor('#FFF3E0')
            .padding(10)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)
      }
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}

@Builder
export function AnimatedDrawableDemoPage() {
  Column() {
    Text('AnimatedDrawableDescriptor Demo')
      .fontSize(24)
      .fontWeight(FontWeight.Bold)
      .margin(20)

    Scroll() {
      Column({ space: 20 }) {
        Text('Creating AnimatedDrawableDescriptor')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('Basic Creation')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('let animated = new AnimatedDrawableDescriptor($r("app.media.flower"), { iterations: 1, duration: 1000 });')
            .fontSize(11)
            .backgroundColor('#FFF3E0')
            .padding(10)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Text('AnimationOptions')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('iterations: number')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('- 1: Play once')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(5)
          Text('- -1: Play infinitely')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(5)
          Text('- N: Play N times')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(5)

          Text('duration: number')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('Duration in milliseconds (default: 0)')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(5)

          Text('playMode: PlayMode')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text('- PlayMode.Normal: Forward play')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(5)
          Text('- PlayMode.Reverse: Reverse play')
            .fontSize(12)
            .backgroundColor('#E8F5E9')
            .padding(5)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)

        Text('Examples')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('// Play once, 1 second')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('new AnimatedDrawableDescriptor($r("app.media.flower"), { iterations: 1, duration: 1000 });')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)

          Text('// Loop forever, 2 seconds')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('new AnimatedDrawableDescriptor($r("app.media.flower"), { iterations: -1, duration: 2000 });')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)

          Text('// Play 3 times, 1.5 seconds')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('new AnimatedDrawableDescriptor($r("app.media.flower"), { iterations: 3, duration: 1500 });')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)

          Text('// Reverse play')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)
          Text('new AnimatedDrawableDescriptor($r("app.media.flower"), { iterations: 1, duration: 1000, playMode: PlayMode.Reverse });')
            .fontSize(11)
            .backgroundColor('#E3F2FD')
            .padding(5)
        }
        .padding(10)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)
      }
      .padding(20)
    }
    .width('100%')
    .height('100%')
  }
}
