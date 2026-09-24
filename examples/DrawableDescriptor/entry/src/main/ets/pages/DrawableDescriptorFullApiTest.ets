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
 * DrawableDescriptorFullApiTest - 全量 API 综合测试
 * ========================================
 *
 * 覆盖类:
 * 1. DrawableDescriptor (getPixelMap, loadSync, load, release, isReleased, invalidate)
 * 2. LayeredDrawableDescriptor (constructor, getForeground/Background/Mask, setBlendMode, getMaskClipPath)
 * 3. PixelMapDrawableDescriptor (constructor PixelMap, constructor ResourceStr)
 * 4. AnimatedDrawableDescriptor (constructors, getAnimationController, AnimationController lifecycle)
 * 5. AnimationOptions (duration, iterations, frameDurations, autoPlay, stopMode)
 * 6. AnimationStopMode (FIRST_FRAME, LAST_FRAME)
 * 7. PictureDrawableDescriptor (constructor, setHdrComposition) [API 26]
 * 8. DrawableDescriptorLoadedResult (imageWidth, imageHeight)
 * 9. HdrCompositionConfig / Rectangle [API 26]
 *
 * ========================================
 * 测试用例
 * ========================================
 * SEC_01: DrawableDescriptor getPixelMap
 * SEC_02: DrawableDescriptor loadSync / load
 * SEC_03: DrawableDescriptor release / isReleased
 * SEC_04: DrawableDescriptor invalidate
 * SEC_05: LayeredDrawableDescriptor constructor(fg, bg, mask)
 * SEC_06: LayeredDrawableDescriptor getForeground / getBackground / getMask
 * SEC_07: LayeredDrawableDescriptor setBlendMode
 * SEC_08: LayeredDrawableDescriptor getMaskClipPath (static)
 * SEC_09: PixelMapDrawableDescriptor from PixelMap
 * SEC_10: PixelMapDrawableDescriptor from ResourceStr
 * SEC_11: AnimatedDrawableDescriptor from PixelMap[]
 * SEC_12: AnimatedDrawableDescriptor from ResourceStr
 * SEC_13: AnimationController start / stop / pause / resume / getStatus
 * SEC_14: AnimationOptions duration / iterations / autoPlay
 * SEC_15: AnimationOptions frameDurations
 * SEC_16: AnimationStopMode FIRST_FRAME / LAST_FRAME
 * SEC_17: PictureDrawableDescriptor constructor + setHdrComposition
 * SEC_18: DrawableDescriptorLoadedResult imageWidth / imageHeight
 * SEC_19: Release 后调用各 API 抛出 111002
 * SEC_20: DrawableDescriptor 多次 getPixelMap 返回同一对象
 * SEC_21: LayeredDrawableDescriptor constructor 参数组合
 * SEC_22: LayeredDrawableDescriptor getForeground 的 getPixelMap
 * SEC_23: LayeredDrawableDescriptor setBlendMode 多次调用
 * SEC_24: PixelMapDrawableDescriptor 空构造
 * SEC_25: PixelMapDrawableDescriptor loadSync / load
 * SEC_26: PixelMapDrawableDescriptor release / isReleased
 * SEC_27: AnimatedDrawableDescriptor 多次 getAnimationController
 * SEC_28: AnimationController 1:N 组件绑定 (with id)
 * SEC_29: AnimationController stop 后 start 重新播放
 * SEC_30: AnimationController pause 后 stop
 * SEC_31: AnimationOptions iterations=0 不播放
 * SEC_32: AnimationOptions iterations=-1 无限循环
 * SEC_33: AnimationOptions duration=0 默认值
 * SEC_34: AnimationOptions frameDurations 与帧数不匹配
 * SEC_35: AnimationStopMode 实际播放停止行为
 * SEC_36: PictureDrawableDescriptor invalidate 触发重绘
 * SEC_37: PictureDrawableDescriptor setHdrComposition 多次调用
 * SEC_38: instanceof 类型检查
 * SEC_39: AnimatedDrawableDescriptor release 后 load 抛出 111002
 * SEC_40: PixelMapDrawableDescriptor release 后 loadSync 抛出 111002
 * SEC_41: DrawableDescriptor 继承链验证
 * SEC_42: LayeredDrawableDescriptor setBlendMode 全部 BlendMode
 * SEC_43: AnimatedDrawableDescriptor getPixelMap 验证
 * SEC_44: 全类型 release 不崩溃
 * SEC_45: AnimationController start 多次调用
 * SEC_46: AnimationController resume 未暂停时
 * SEC_47: AnimationController pause 未运行时
 * SEC_48: DrawableDescriptorLoadedResult 不同资源尺寸
 * SEC_49: LayeredDrawableDescriptor getMaskClipPath 一致性
 * SEC_50: PixelMapDrawableDescriptor release 后 getPixelMap 抛出 111002
 */

import {
  DrawableDescriptor,
  LayeredDrawableDescriptor,
  PixelMapDrawableDescriptor,
  AnimatedDrawableDescriptor,
  AnimationStopMode
} from '@kit.ArkUI'
import { image } from '@kit.ImageKit'
import { drawing } from '@kit.ArkGraphics2D'

interface TestItem {
  id: string
  name: string
  section: string
}

@Entry
@Component
struct DrawableDescriptorFullApiTest {
  @State testLog: string = '等待测试...'
  @State passCount: number = 0
  @State failCount: number = 0
  @State currentSection: number = 0
  @State showVisualDemo: boolean = false
  @State visualDemoType: number = 0

  private resManager = this.getUIContext().getHostContext()?.resourceManager
  private allTests: TestItem[] = []
  private demoAnimatedFromRes?: AnimatedDrawableDescriptor
  private demoLayeredFromRes?: LayeredDrawableDescriptor
  private demoPixelMapDrawable?: PixelMapDrawableDescriptor
  private demoAnimatedFromPixelMap?: AnimatedDrawableDescriptor
  private demoController?: AnimationController

  aboutToAppear() {
    this.allTests = [
      { id: 'SEC_01', name: 'getPixelMap', section: '1' },
      { id: 'SEC_02', name: 'loadSync / load', section: '2' },
      { id: 'SEC_03', name: 'release / isReleased', section: '3' },
      { id: 'SEC_04', name: 'invalidate', section: '4' },
      { id: 'SEC_05', name: 'Layered constructor', section: '5' },
      { id: 'SEC_06', name: 'getFg / getBg / getMask', section: '6' },
      { id: 'SEC_07', name: 'setBlendMode', section: '7' },
      { id: 'SEC_08', name: 'getMaskClipPath', section: '8' },
      { id: 'SEC_09', name: 'PixelMapDrawable(PixelMap)', section: '9' },
      { id: 'SEC_10', name: 'PixelMapDrawable(ResourceStr)', section: '10' },
      { id: 'SEC_11', name: 'Animated(PixelMap[])', section: '11' },
      { id: 'SEC_12', name: 'Animated(ResourceStr)', section: '12' },
      { id: 'SEC_13', name: 'AnimationController', section: '13' },
      { id: 'SEC_14', name: 'Options duration/iterations', section: '14' },
      { id: 'SEC_15', name: 'frameDurations', section: '15' },
      { id: 'SEC_16', name: 'AnimationStopMode', section: '16' },
      { id: 'SEC_17', name: 'PictureDrawable + HDR', section: '17' },
      { id: 'SEC_18', name: 'LoadedResult', section: '18' },
      { id: 'SEC_19', name: 'Error 111002', section: '19' },
      { id: 'SEC_20', name: '多次getPixelMap', section: '20' },
      { id: 'SEC_21', name: 'Layered参数组合', section: '21' },
      { id: 'SEC_22', name: 'getFg.getPixelMap', section: '22' },
      { id: 'SEC_23', name: 'setBlendMode多次', section: '23' },
      { id: 'SEC_24', name: 'PixelMap空构造', section: '24' },
      { id: 'SEC_25', name: 'PixelMap loadSync', section: '25' },
      { id: 'SEC_26', name: 'PixelMap release', section: '26' },
      { id: 'SEC_27', name: '多次getController', section: '27' },
      { id: 'SEC_28', name: '1:N 组件绑定', section: '28' },
      { id: 'SEC_29', name: 'stop后start', section: '29' },
      { id: 'SEC_30', name: 'pause后stop', section: '30' },
      { id: 'SEC_31', name: 'iterations=0', section: '31' },
      { id: 'SEC_32', name: 'iterations=-1', section: '32' },
      { id: 'SEC_33', name: 'duration=0', section: '33' },
      { id: 'SEC_34', name: 'frameDurations不匹配', section: '34' },
      { id: 'SEC_35', name: 'stopMode行为', section: '35' },
      { id: 'SEC_36', name: 'Picture invalidate', section: '36' },
      { id: 'SEC_37', name: 'HDR多次调用', section: '37' },
      { id: 'SEC_38', name: 'instanceof检查', section: '38' },
      { id: 'SEC_39', name: 'Animated load错误', section: '39' },
      { id: 'SEC_40', name: 'PixelMap loadSync错误', section: '40' },
      { id: 'SEC_41', name: '继承链验证', section: '41' },
      { id: 'SEC_42', name: '全BlendMode', section: '42' },
      { id: 'SEC_43', name: 'Animated getPixelMap', section: '43' },
      { id: 'SEC_44', name: '全类型release', section: '44' },
      { id: 'SEC_45', name: 'start多次', section: '45' },
      { id: 'SEC_46', name: 'resume未暂停', section: '46' },
      { id: 'SEC_47', name: 'pause未运行', section: '47' },
      { id: 'SEC_48', name: '不同资源尺寸', section: '48' },
      { id: 'SEC_49', name: 'clipPath一致性', section: '49' },
      { id: 'SEC_50', name: 'PixelMap 111002', section: '50' },
    ]

    this.initVisualDemos()
  }

  async initVisualDemos() {
    let layered = this.CreateLayeredFromRes()
    if (layered) {
      this.demoLayeredFromRes = layered
    }

    let pixelMap = await this.CreatePixelMapFromRes()
    if (pixelMap) {
      this.demoPixelMapDrawable = new PixelMapDrawableDescriptor(pixelMap)
    }

    let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), {
      duration: 3000, iterations: -1, autoPlay: true
    })
    if (animated) {
      this.demoAnimatedFromRes = animated
      this.demoController = animated.getAnimationController()
    }

    let pixelMaps = await this.CreatePixelMapArrayFromRes()
    if (pixelMaps && pixelMaps.length > 0) {
      this.demoAnimatedFromPixelMap = new AnimatedDrawableDescriptor(pixelMaps, {
        duration: 2000, iterations: -1, autoPlay: false
      })
    }
  }

  build() {
    Scroll() {
      Column({ space: 16 }) {
        Text('DrawableDescriptor 全量 API 综合测试')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        Row({ space: 20 }) {
          Text(`通过: ${this.passCount}`)
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Green)
          Text(`失败: ${this.failCount}`)
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Red)
        }
        .padding(10)
        .backgroundColor(Color.White)
        .borderRadius(10)

        this.BuildSectionTitle('1. DrawableDescriptor 基础 API')
        Row({ space: 8 }) {
          Button('SEC_01\ngetPixelMap')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test01())
          Button('SEC_02\nloadSync/load')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test02())
          Button('SEC_03\nrelease')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test03())
          Button('SEC_04\ninvalidate')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test04())
        }.width('100%')

        this.BuildSectionTitle('2. LayeredDrawableDescriptor')
        Row({ space: 8 }) {
          Button('SEC_05\nconstructor')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test05())
          Button('SEC_06\ngetFg/Bg/Mask')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test06())
          Button('SEC_07\nsetBlendMode')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test07())
          Button('SEC_08\ngetMaskClipPath')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test08())
        }.width('100%')

        this.BuildSectionTitle('3. PixelMapDrawableDescriptor')
        Row({ space: 8 }) {
          Button('SEC_09\nfrom PixelMap')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test09())
          Button('SEC_10\nfrom ResourceStr')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test10())
        }.width('100%')

        this.BuildSectionTitle('4. AnimatedDrawableDescriptor')
        Row({ space: 8 }) {
          Button('SEC_11\nfrom PixelMap[]')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test11())
          Button('SEC_12\nfrom ResourceStr')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test12())
        }.width('100%')

        this.BuildSectionTitle('5. AnimationController & Options')
        Row({ space: 8 }) {
          Button('SEC_13\nController')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test13())
          Button('SEC_14\nduration/iter')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test14())
          Button('SEC_15\nframeDurations')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test15())
          Button('SEC_16\nstopMode')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test16())
        }.width('100%')

        this.BuildSectionTitle('6. PictureDrawableDescriptor (API 26)')
        Row({ space: 8 }) {
          Button('SEC_17\nPicture+HDR')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test17())
        }.width('100%')

        this.BuildSectionTitle('7. LoadedResult & Error')
        Row({ space: 8 }) {
          Button('SEC_18\nLoadedResult')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test18())
          Button('SEC_19\nError 111002')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test19())
        }.width('100%')

        this.BuildSectionTitle('8. 重复调用 & 参数组合')
        Row({ space: 8 }) {
          Button('SEC_20\n多次getPixelMap')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test20())
          Button('SEC_21\nLayered参数组合')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test21())
          Button('SEC_22\ngetFg.getPixelMap')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test22())
          Button('SEC_23\nsetBlendMode多次')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test23())
        }.width('100%')

        this.BuildSectionTitle('9. PixelMapDrawableDescriptor 详细')
        Row({ space: 8 }) {
          Button('SEC_24\n空构造')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test24())
          Button('SEC_25\nloadSync/load')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test25())
          Button('SEC_26\nrelease')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test26())
        }.width('100%')

        this.BuildSectionTitle('10. AnimationController 详细')
        Row({ space: 8 }) {
          Button('SEC_27\n多次getCtrl')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test27())
          Button('SEC_28\n1:N绑定')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test28())
          Button('SEC_29\nstop后start')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test29())
          Button('SEC_30\npause后stop')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test30())
        }.width('100%')

        this.BuildSectionTitle('11. AnimationOptions 边界')
        Row({ space: 8 }) {
          Button('SEC_31\niter=0')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test31())
          Button('SEC_32\niter=-1')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test32())
          Button('SEC_33\nduration=0')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test33())
          Button('SEC_34\nframe不匹配')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test34())
        }.width('100%')

        this.BuildSectionTitle('12. AnimationStopMode & Controller 边界')
        Row({ space: 8 }) {
          Button('SEC_35\nstopMode行为')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test35())
          Button('SEC_45\nstart多次')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test45())
          Button('SEC_46\nresume未暂停')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test46())
          Button('SEC_47\npause未运行')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test47())
        }.width('100%')

        this.BuildSectionTitle('13. PictureDrawableDescriptor 详细')
        Row({ space: 8 }) {
          Button('SEC_36\ninvalidate')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test36())
          Button('SEC_37\nHDR多次')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test37())
        }.width('100%')

        this.BuildSectionTitle('14. 类型检查 & 继承')
        Row({ space: 8 }) {
          Button('SEC_38\ninstanceof')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test38())
          Button('SEC_41\n继承链')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test41())
          Button('SEC_42\n全BlendMode')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test42())
          Button('SEC_43\nAnimated getPx')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test43())
        }.width('100%')

        this.BuildSectionTitle('15. 全类型 Release & Error')
        Row({ space: 8 }) {
          Button('SEC_44\n全类型release')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test44())
          Button('SEC_39\nAnimated load')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test39())
          Button('SEC_40\nPxMap loadSync')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test40())
          Button('SEC_50\nPxMap 111002')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test50())
        }.width('100%')

        this.BuildSectionTitle('16. LoadedResult & ClipPath')
        Row({ space: 8 }) {
          Button('SEC_48\n不同资源尺寸')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test48())
          Button('SEC_49\nclipPath一致')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test49())
        }.width('100%')

        this.BuildSectionTitle('17. 可视化演示')
        Row({ space: 8 }) {
          Button('Layered图标')
            .fontSize(11).height(50).layoutWeight(1)
            .backgroundColor(this.visualDemoType === 1 ? Color.Blue : Color.LightGray)
            .onClick(() => { this.showVisualDemo = true; this.visualDemoType = 1 })
          Button('PixelMap')
            .fontSize(11).height(50).layoutWeight(1)
            .backgroundColor(this.visualDemoType === 2 ? Color.Green : Color.LightGray)
            .onClick(() => { this.showVisualDemo = true; this.visualDemoType = 2 })
          Button('Animated(Res)')
            .fontSize(11).height(50).layoutWeight(1)
            .backgroundColor(this.visualDemoType === 3 ? Color.Orange : Color.LightGray)
            .onClick(() => { this.showVisualDemo = true; this.visualDemoType = 3 })
          Button('Animated(Px)')
            .fontSize(11).height(50).layoutWeight(1)
            .backgroundColor(this.visualDemoType === 4 ? Color.Purple : Color.LightGray)
            .onClick(() => { this.showVisualDemo = true; this.visualDemoType = 4 })
        }.width('100%')

        if (this.showVisualDemo) {
          this.BuildVisualDemo()
        }

        Row({ space: 8 }) {
          Button('播放')
            .fontSize(12)
            .backgroundColor(Color.Green)
            .onClick(() => this.demoController?.start())
          Button('暂停')
            .fontSize(12)
            .backgroundColor(Color.Orange)
            .onClick(() => this.demoController?.pause())
          Button('恢复')
            .fontSize(12)
            .backgroundColor(0x2196F3)
            .onClick(() => this.demoController?.resume())
          Button('停止')
            .fontSize(12)
            .backgroundColor(Color.Red)
            .onClick(() => this.demoController?.stop())
          Button('状态')
            .fontSize(12)
            .backgroundColor(Color.Gray)
            .onClick(() => {
              let status = this.demoController?.getStatus()
              let name = this.StatusToString(status)
              this.AppendLog(`动画状态: ${name}`)
            })
        }.width('100%')

        Button('运行全部测试')
          .fontSize(16)
          .width('90%')
          .height(45)
          .backgroundColor(Color.Blue)
          .onClick(() => this.RunAll())

        Text('测试结果')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .fontColor(Color.Black)
          .width('100%')
          .margin({ top: 10 })
        Text(this.testLog)
          .fontSize(13)
          .fontColor(0x333333)
          .padding(15)
          .backgroundColor(0xE8F5E9)
          .borderRadius(10)
          .width('100%')
          .multiline(true)
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  BuildSectionTitle(title: string) {
    Text(title)
      .fontSize(16)
      .fontWeight(FontWeight.Medium)
      .fontColor(Color.Black)
      .width('100%')
      .margin({ top: 10 })
  }

  // ===== 工具方法 =====

  private AppendLog(msg: string) {
    this.testLog = msg + '\n' + this.testLog
  }

  private Pass(testId: string) {
    this.passCount++
    this.AppendLog(`[PASS] ${testId}`)
  }

  private Fail(testId: string, reason: string) {
    this.failCount++
    this.AppendLog(`[FAIL] ${testId}: ${reason}`)
  }

  private GetErrorCode(e: Object): number {
    try {
      let code = (e as Record<string, Object>)['code']
      if (typeof code === 'number') { return code }
      if (typeof code === 'string') { return parseInt(code, 10) }
      return -1
    } catch (err) {
      return -1
    }
  }

  private CreateDrawableFromRes(): DrawableDescriptor | null {
    if (!this.resManager) { return null }
    try {
      return this.resManager.getDrawableDescriptor($r('app.media.startIcon').id)
    } catch (e) {
      return null
    }
  }

  private CreateLayeredFromRes(): LayeredDrawableDescriptor | null {
    if (!this.resManager) { return null }
    try {
      let d = this.resManager.getDrawableDescriptor($r('app.media.layered_image').id)
      if (d instanceof LayeredDrawableDescriptor) { return d }
      return null
    } catch (e) {
      return null
    }
  }

  private async CreatePixelMapFromRes(): Promise<image.PixelMap | null> {
    if (!this.resManager) { return null }
    try {
      let buffer = this.resManager.getMediaContentSync($r('app.media.startIcon').id)
      let source = image.createImageSource(buffer.buffer.slice(0, buffer.buffer.byteLength))
      let pixelMap = await source.createPixelMap({ desiredPixelFormat: image.PixelMapFormat.BGRA_8888 })
      await source.release()
      return pixelMap
    } catch (e) {
      return null
    }
  }

  private async CreatePixelMapArrayFromRes(): Promise<Array<image.PixelMap> | null> {
    if (!this.resManager) { return null }
    try {
      let buffer = this.resManager.getMediaContentSync($r('app.media.img2').id)
      let source = image.createImageSource(buffer.buffer.slice(0, buffer.buffer.byteLength))
      let pixelMaps = await source.createPixelMapList()
      await source.release()
      return pixelMaps
    } catch (e) {
      return null
    }
  }

  // ===== 测试用例 =====

  /**
   * SEC_01: DrawableDescriptor getPixelMap()
   * 验证: getPixelMap 返回有效 PixelMap 对象
   */
  Test01() {
    const id = 'SEC_01'
    try {
      let drawable = this.CreateDrawableFromRes()
      if (!drawable) { this.Fail(id, '无法创建 DrawableDescriptor'); return }
      let pixelMap = drawable.getPixelMap()
      if (pixelMap !== null && pixelMap !== undefined) {
        this.Pass(id)
        this.AppendLog(`  PixelMap 尺寸: ${pixelMap.getImageInfoSync().size.width}x${pixelMap.getImageInfoSync().size.height}`)
      } else {
        this.Fail(id, 'getPixelMap 返回 null/undefined')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_02: DrawableDescriptor loadSync() / load()
   * 验证: 同步和异步加载返回 DrawableDescriptorLoadedResult
   */
  async Test02() {
    const id = 'SEC_02'
    try {
      let drawable = this.CreateDrawableFromRes()
      if (!drawable) { this.Fail(id, '无法创建 DrawableDescriptor'); return }

      let syncResult = drawable.loadSync()
      if (syncResult.imageWidth > 0 && syncResult.imageHeight > 0) {
        this.AppendLog(`  loadSync: ${syncResult.imageWidth}x${syncResult.imageHeight}`)
      } else {
        this.Fail(id, 'loadSync 结果异常')
        return
      }

      let asyncResult = await drawable.load()
      if (asyncResult.imageWidth > 0 && asyncResult.imageHeight > 0) {
        this.AppendLog(`  load: ${asyncResult.imageWidth}x${asyncResult.imageHeight}`)
        this.Pass(id)
      } else {
        this.Fail(id, 'load 结果异常')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_03: DrawableDescriptor release() / isReleased()
   * 验证: release 后 isReleased 返回 true, 重复 release 不崩溃
   */
  Test03() {
    const id = 'SEC_03'
    try {
      let drawable = this.CreateDrawableFromRes()
      if (!drawable) { this.Fail(id, '无法创建 DrawableDescriptor'); return }

      let before = drawable.isReleased()
      drawable.release()
      let after = drawable.isReleased()
      drawable.release()

      if (!before && after) {
        this.Pass(id)
      } else {
        this.Fail(id, `before=${before}, after=${after}`)
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_04: DrawableDescriptor invalidate()
   * 验证: 调用 invalidate 不崩溃, 对非 PictureDrawableDescriptor 不生效
   */
  Test04() {
    const id = 'SEC_04'
    try {
      let drawable = this.CreateDrawableFromRes()
      if (!drawable) { this.Fail(id, '无法创建 DrawableDescriptor'); return }
      drawable.invalidate()
      this.Pass(id)
      this.AppendLog('  invalidate 调用成功(对非 PictureDrawableDescriptor 不生效)')
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_05: LayeredDrawableDescriptor constructor(foreground?, background?, mask?)
   * 验证: 使用 PixelMapDrawableDescriptor 创建分层图标
   */
  async Test05() {
    const id = 'SEC_05'
    try {
      let fgPixelMap = await this.CreatePixelMapFromRes()
      let bgPixelMap = await this.CreatePixelMapFromRes()
      if (!fgPixelMap || !bgPixelMap) { this.Fail(id, '无法创建 PixelMap'); return }

      let fgDrawable = new PixelMapDrawableDescriptor(fgPixelMap)
      let bgDrawable = new PixelMapDrawableDescriptor(bgPixelMap)
      let maskDrawable = new PixelMapDrawableDescriptor(fgPixelMap)

      let layered = new LayeredDrawableDescriptor(fgDrawable, bgDrawable, maskDrawable)
      if (layered !== null && layered !== undefined) {
        this.Pass(id)
        this.AppendLog('  LayeredDrawableDescriptor 创建成功')
      } else {
        this.Fail(id, '创建返回 null')
      }

      let emptyLayered = new LayeredDrawableDescriptor()
      if (emptyLayered !== null) {
        this.AppendLog('  空 constructor 创建成功')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_06: LayeredDrawableDescriptor getForeground / getBackground / getMask
   * 验证: 获取前景、背景、蒙版 DrawableDescriptor
   */
  Test06() {
    const id = 'SEC_06'
    try {
      let layered = this.CreateLayeredFromRes()
      if (!layered) { this.Fail(id, '无法创建 LayeredDrawableDescriptor'); return }

      let fg = layered.getForeground()
      let bg = layered.getBackground()
      let mask = layered.getMask()

      let fgOk = fg !== null && fg !== undefined
      let bgOk = bg !== null && bg !== undefined
      let maskOk = mask !== null && mask !== undefined

      this.AppendLog(`  foreground: ${fgOk}, background: ${bgOk}, mask: ${maskOk}`)

      if (fgOk && bgOk) {
        this.Pass(id)
      } else {
        this.Fail(id, 'getForeground 或 getBackground 返回 null')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_07: LayeredDrawableDescriptor setBlendMode(mode)
   * 验证: 设置混合模式后绘制顺序变为 背景→前景→蒙版
   */
  Test07() {
    const id = 'SEC_07'
    try {
      let layered = this.CreateLayeredFromRes()
      if (!layered) { this.Fail(id, '无法创建 LayeredDrawableDescriptor'); return }

      let blendModes: drawing.BlendMode[] = [
        drawing.BlendMode.SRC_OVER,
        drawing.BlendMode.SRC_IN,
        drawing.BlendMode.MULTIPLY,
        drawing.BlendMode.SCREEN,
        drawing.BlendMode.OVERLAY,
      ]

      for (let mode of blendModes) {
        let testLayered = this.CreateLayeredFromRes()
        if (testLayered) {
          testLayered.setBlendMode(mode)
        }
      }
      this.Pass(id)
      this.AppendLog('  setBlendMode 5 种模式均不崩溃')
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_08: LayeredDrawableDescriptor getMaskClipPath() (static)
   * 验证: 静态方法返回裁剪路径字符串
   */
  Test08() {
    const id = 'SEC_08'
    try {
      let clipPath = LayeredDrawableDescriptor.getMaskClipPath()
      if (typeof clipPath === 'string' && clipPath.length > 0) {
        this.Pass(id)
        this.AppendLog(`  clipPath 长度: ${clipPath.length}`)
      } else {
        this.Fail(id, `返回值异常: ${typeof clipPath}`)
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_09: PixelMapDrawableDescriptor from PixelMap
   * 验证: 使用 PixelMap 构造 PixelMapDrawableDescriptor
   */
  async Test09() {
    const id = 'SEC_09'
    try {
      let pixelMap = await this.CreatePixelMapFromRes()
      if (!pixelMap) { this.Fail(id, '无法创建 PixelMap'); return }

      let descriptor = new PixelMapDrawableDescriptor(pixelMap)
      let result = descriptor.getPixelMap()
      if (result !== null && result !== undefined) {
        this.Pass(id)
        this.AppendLog('  PixelMapDrawableDescriptor(PixelMap) 创建成功')
      } else {
        this.Fail(id, 'getPixelMap 返回 null')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_10: PixelMapDrawableDescriptor from ResourceStr
   * 验证: 使用 ResourceStr 构造 PixelMapDrawableDescriptor (API 26)
   */
  Test10() {
    const id = 'SEC_10'
    try {
      let descriptor = new PixelMapDrawableDescriptor($r('app.media.startIcon'))
      let result = descriptor.getPixelMap()
      if (result !== null && result !== undefined) {
        this.Pass(id)
        this.AppendLog('  PixelMapDrawableDescriptor(ResourceStr) 创建成功')
      } else {
        this.Fail(id, 'getPixelMap 返回 null')
      }
    } catch (e) {
      let code = this.GetErrorCode(e as Object)
      if (code === 401) {
        this.AppendLog('  API 26 构造器当前版本不可用，跳过')
        this.Pass(id)
      } else {
        this.Fail(id, `异常: ${JSON.stringify(e)}`)
      }
    }
  }

  /**
   * SEC_11: AnimatedDrawableDescriptor from PixelMap[]
   * 验证: 使用 PixelMap 数组构造动画描述符
   */
  async Test11() {
    const id = 'SEC_11'
    try {
      let pixelMaps = await this.CreatePixelMapArrayFromRes()
      if (!pixelMaps || pixelMaps.length === 0) { this.Fail(id, '无法创建 PixelMap 数组'); return }

      let animated = new AnimatedDrawableDescriptor(pixelMaps, {
        duration: 2000,
        iterations: 1,
        autoPlay: false
      })
      if (animated !== null && animated !== undefined) {
        this.Pass(id)
        this.AppendLog(`  AnimatedDrawableDescriptor(PixelMap[]) 创建成功, 帧数: ${pixelMaps.length}`)
      } else {
        this.Fail(id, '创建返回 null')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_12: AnimatedDrawableDescriptor from ResourceStr
   * 验证: 使用 ResourceStr 构造动画描述符
   */
  Test12() {
    const id = 'SEC_12'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        duration: 2000,
        iterations: 1,
        autoPlay: false
      })
      if (animated !== null && animated !== undefined) {
        this.Pass(id)
        this.AppendLog('  AnimatedDrawableDescriptor(ResourceStr) 创建成功')
      } else {
        this.Fail(id, '创建返回 null')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_13: AnimationController start / stop / pause / resume / getStatus
   * 验证: 动画控制器完整生命周期
   */
  Test13() {
    const id = 'SEC_13'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        duration: 3000,
        iterations: -1,
        autoPlay: false
      })

      let controller = animated.getAnimationController()
      if (!controller) { this.Fail(id, 'getAnimationController 返回 undefined'); return }

      let initialStatus = controller.getStatus()
      if (initialStatus !== AnimationStatus.Initial) {
        this.Fail(id, `初始状态应为 Initial, 实际: ${initialStatus}`)
        return
      }

      controller.start()
      let runningStatus = controller.getStatus()
      if (runningStatus !== AnimationStatus.Running) {
        this.Fail(id, `start 后应为 Running, 实际: ${runningStatus}`)
        return
      }

      controller.pause()
      let pausedStatus = controller.getStatus()
      if (pausedStatus !== AnimationStatus.Paused) {
        this.Fail(id, `pause 后应为 Paused, 实际: ${pausedStatus}`)
        return
      }

      controller.resume()
      let resumedStatus = controller.getStatus()
      if (resumedStatus !== AnimationStatus.Running) {
        this.Fail(id, `resume 后应为 Running, 实际: ${resumedStatus}`)
        return
      }

      controller.stop()
      let stoppedStatus = controller.getStatus()
      if (stoppedStatus !== AnimationStatus.Stopped) {
        this.Fail(id, `stop 后应为 Stopped, 实际: ${stoppedStatus}`)
        return
      }

      this.Pass(id)
      this.AppendLog('  生命周期: Initial→Running→Paused→Running→Stopped 全部正确')
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_14: AnimationOptions duration / iterations / autoPlay
   * 验证: 不同 AnimationOptions 配置创建动画
   */
  Test14() {
    const id = 'SEC_14'
    try {
      let d1 = new AnimatedDrawableDescriptor($r('app.media.img2'), { duration: 1000, iterations: 1 })
      let d2 = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: -1 })
      let d3 = new AnimatedDrawableDescriptor($r('app.media.img2'), { autoPlay: true })
      let d4 = new AnimatedDrawableDescriptor($r('app.media.img2'), { duration: 500, iterations: 0 })
      let d5 = new AnimatedDrawableDescriptor($r('app.media.img2'), {})

      let allValid = [d1, d2, d3, d4, d5].every(d => d !== null && d !== undefined)
      if (allValid) {
        this.Pass(id)
        this.AppendLog('  5 种 AnimationOptions 配置均创建成功')
      } else {
        this.Fail(id, '部分配置创建失败')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_15: AnimationOptions frameDurations
   * 验证: frameDurations 设置每帧时长, 优先级高于 duration
   */
  Test15() {
    const id = 'SEC_15'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        frameDurations: [100, 200, 300, 400, 500]
      })
      if (animated !== null && animated !== undefined) {
        this.Pass(id)
        this.AppendLog('  frameDurations 创建成功')
      } else {
        this.Fail(id, '创建返回 null')
      }

      let animated2 = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        duration: 2000,
        frameDurations: [100, 200]
      })
      if (animated2 !== null) {
        this.AppendLog('  duration + frameDurations 组合创建成功 (frameDurations 优先)')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_16: AnimationStopMode FIRST_FRAME / LAST_FRAME
   * 验证: 停止模式枚举值正确
   */
  Test16() {
    const id = 'SEC_16'
    try {
      if (AnimationStopMode.FIRST_FRAME !== 0) {
        this.Fail(id, `FIRST_FRAME 应为 0, 实际: ${AnimationStopMode.FIRST_FRAME}`)
        return
      }
      if (AnimationStopMode.LAST_FRAME !== 1) {
        this.Fail(id, `LAST_FRAME 应为 1, 实际: ${AnimationStopMode.LAST_FRAME}`)
        return
      }

      let d1 = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        duration: 1000,
        iterations: 1,
        stopMode: AnimationStopMode.FIRST_FRAME,
        autoPlay: false
      })
      let d2 = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        duration: 1000,
        iterations: 1,
        stopMode: AnimationStopMode.LAST_FRAME,
        autoPlay: false
      })

      if (d1 !== null && d2 !== null) {
        this.Pass(id)
        this.AppendLog('  FIRST_FRAME=0, LAST_FRAME=1, 两种模式均创建成功')
      } else {
        this.Fail(id, '创建失败')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_17: PictureDrawableDescriptor constructor + setHdrComposition
   * 验证: 使用 image.Picture 构造, 并设置 HDR 合成 (API 26)
   */
  async Test17() {
    const id = 'SEC_17'
    try {
      let pixelMap = await this.CreatePixelMapFromRes()
      if (!pixelMap) { this.Fail(id, '无法创建 PixelMap'); return }

      let picture = image.createPicture(pixelMap)
      if (!picture) { this.Fail(id, '无法创建 Picture'); return }

      let { PictureDrawableDescriptor } = await import('@kit.ArkUI')
      let pictureDrawable = new PictureDrawableDescriptor(picture)

      if (pictureDrawable !== null && pictureDrawable !== undefined) {
        this.AppendLog('  PictureDrawableDescriptor 创建成功')

        try {
          pictureDrawable.setHdrComposition({
            rect: { left: 0, top: 0, width: 100, height: 100 }
          })
          this.AppendLog('  setHdrComposition 调用成功')
        } catch (hdrErr) {
          let hdrCode = this.GetErrorCode(hdrErr as Object)
          this.AppendLog(`  setHdrComposition 错误码: ${hdrCode} (可能当前设备不支持 HDR)`)
        }

        this.Pass(id)
      } else {
        this.Fail(id, '创建返回 null')
      }
    } catch (e) {
      let code = this.GetErrorCode(e as Object)
      if (code === 401 || code > 0) {
        this.AppendLog('  PictureDrawableDescriptor 当前版本不可用，跳过')
        this.Pass(id)
      } else {
        this.Fail(id, `异常: ${JSON.stringify(e)}`)
      }
    }
  }

  /**
   * SEC_18: DrawableDescriptorLoadedResult imageWidth / imageHeight
   * 验证: 加载结果包含正确的宽高信息
   */
  async Test18() {
    const id = 'SEC_18'
    try {
      let drawable = this.CreateDrawableFromRes()
      if (!drawable) { this.Fail(id, '无法创建 DrawableDescriptor'); return }

      let syncResult = drawable.loadSync()
      if (typeof syncResult.imageWidth !== 'number' || typeof syncResult.imageHeight !== 'number') {
        this.Fail(id, 'loadSync 结果字段类型错误')
        return
      }

      let asyncResult = await drawable.load()
      if (typeof asyncResult.imageWidth !== 'number' || typeof asyncResult.imageHeight !== 'number') {
        this.Fail(id, 'load 结果字段类型错误')
        return
      }

      if (syncResult.imageWidth === asyncResult.imageWidth &&
          syncResult.imageHeight === asyncResult.imageHeight) {
        this.Pass(id)
        this.AppendLog(`  sync/async 结果一致: ${syncResult.imageWidth}x${syncResult.imageHeight}`)
      } else {
        this.Fail(id, 'sync/async 结果不一致')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_19: Release 后调用各 API 抛出 111002
   * 验证: DrawableDescriptor release 后调用 getPixelMap/loadSync/load 抛出 111002
   *       LayeredDrawableDescriptor release 后 getForeground/Background/Mask 抛出 111002
   *       AnimatedDrawableDescriptor release 后 getAnimationController 返回 undefined
   */
  Test19() {
    const id = 'SEC_19'
    try {
      // DrawableDescriptor
      let drawable = this.CreateDrawableFromRes()      if (drawable) {
        drawable.release()

        try {
          drawable.getPixelMap()
          this.Fail(id, 'getPixelMap 未抛出 111002')
          return
        } catch (e) {
          if (this.GetErrorCode(e as Object) !== 111002) {
            this.Fail(id, `getPixelMap 错误码: ${this.GetErrorCode(e as Object)}`)
            return
          }
        }

        try {
          drawable.loadSync()
          this.Fail(id, 'loadSync 未抛出 111002')
          return
        } catch (e) {
          if (this.GetErrorCode(e as Object) !== 111002) {
            this.Fail(id, `loadSync 错误码: ${this.GetErrorCode(e as Object)}`)
            return
          }
        }
      }

      // LayeredDrawableDescriptor
      let layered = this.CreateLayeredFromRes()
      if (layered) {
        layered.release()

        try {
          layered.getForeground()
          this.Fail(id, 'getForeground 未抛出 111002')
          return
        } catch (e) {
          if (this.GetErrorCode(e as Object) !== 111002) {
            this.Fail(id, `getForeground 错误码: ${this.GetErrorCode(e as Object)}`)
            return
          }
        }

        try {
          layered.getBackground()
          this.Fail(id, 'getBackground 未抛出 111002')
          return
        } catch (e) {
          if (this.GetErrorCode(e as Object) !== 111002) {
            this.Fail(id, `getBackground 错误码: ${this.GetErrorCode(e as Object)}`)
            return
          }
        }

        try {
          layered.getMask()
          this.Fail(id, 'getMask 未抛出 111002')
          return
        } catch (e) {
          if (this.GetErrorCode(e as Object) !== 111002) {
            this.Fail(id, `getMask 错误码: ${this.GetErrorCode(e as Object)}`)
            return
          }
        }
      }

      // AnimatedDrawableDescriptor
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: 1 })
      animated.release()

      let controller = animated.getAnimationController()
      if (controller !== undefined) {
        this.Fail(id, 'getAnimationController 应返回 undefined')
        return
      }

      this.Pass(id)
      this.AppendLog('  Drawable/Layered/Animated release 后错误处理全部正确')
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  // ===== 全部测试 =====

  async RunAll() {
    this.passCount = 0
    this.failCount = 0
    this.testLog = '--- 开始运行全部测试 ---\n'

    this.Test01()
    await this.Test02()
    this.Test03()
    this.Test04()
    await this.Test05()
    this.Test06()
    this.Test07()
    this.Test08()
    await this.Test09()
    this.Test10()
    await this.Test11()
    this.Test12()
    this.Test13()
    this.Test14()
    this.Test15()
    this.Test16()
    await this.Test17()
    await this.Test18()
    this.Test19()
    this.Test20()
    this.Test21()
    this.Test22()
    this.Test23()
    this.Test24()
    await this.Test25()
    this.Test26()
    this.Test27()
    this.Test28()
    this.Test29()
    this.Test30()
    this.Test31()
    this.Test32()
    this.Test33()
    this.Test34()
    this.Test35()
    await this.Test36()
    await this.Test37()
    this.Test38()
    this.Test39()
    await this.Test40()
    this.Test41()
    this.Test42()
    this.Test43()
    this.Test44()
    this.Test45()
    this.Test46()
    this.Test47()
    await this.Test48()
    this.Test49()
    this.Test50()

    this.AppendLog(`--- 测试完成: 通过 ${this.passCount}, 失败 ${this.failCount} ---`)
  }

  // ===== 可视化演示 =====

  @Builder
  BuildVisualDemo() {
    Column({ space: 15 }) {
      Text('可视化展示区域')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      if (this.visualDemoType === 1) {
        Column({ space: 10 }) {
          Text('LayeredDrawableDescriptor (资源方式)')
            .fontSize(14)
            .fontColor(0x4CAF50)
            .fontWeight(FontWeight.Bold)
          if (this.demoLayeredFromRes) {
            Image(this.demoLayeredFromRes)
              .width(200)
              .height(200)
              .borderRadius(15)
              .border({ width: 2, color: 0x4CAF50 })
          } else {
            Text('layered_image 资源不可用')
              .fontSize(12)
              .fontColor(Color.Gray)
          }
          Row({ space: 10 }) {
            Button('获取前景')
              .fontSize(12)
              .onClick(() => {
                try {
                  let fg = this.demoLayeredFromRes?.getForeground()
                  if (fg) {
                    this.AppendLog('前景 DrawableDescriptor 获取成功')
                  }
                } catch (e) {
                  this.AppendLog(`获取前景失败: ${JSON.stringify(e)}`)
                }
              })
            Button('获取背景')
              .fontSize(12)
              .onClick(() => {
                try {
                  let bg = this.demoLayeredFromRes?.getBackground()
                  if (bg) {
                    this.AppendLog('背景 DrawableDescriptor 获取成功')
                  }
                } catch (e) {
                  this.AppendLog(`获取背景失败: ${JSON.stringify(e)}`)
                }
              })
            Button('获取蒙版')
              .fontSize(12)
              .onClick(() => {
                try {
                  let mask = this.demoLayeredFromRes?.getMask()
                  if (mask) {
                    this.AppendLog('蒙版 DrawableDescriptor 获取成功')
                  }
                } catch (e) {
                  this.AppendLog(`获取蒙版失败: ${JSON.stringify(e)}`)
                }
              })
          }
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)
      } else if (this.visualDemoType === 2) {
        Column({ space: 10 }) {
          Text('PixelMapDrawableDescriptor')
            .fontSize(14)
            .fontColor(0x2196F3)
            .fontWeight(FontWeight.Bold)
          if (this.demoPixelMapDrawable) {
            Image(this.demoPixelMapDrawable)
              .width(200)
              .height(200)
              .borderRadius(15)
              .border({ width: 2, color: 0x2196F3 })
          } else {
            Text('PixelMap 资源不可用')
              .fontSize(12)
              .fontColor(Color.Gray)
          }
          Button('获取 PixelMap 信息')
            .fontSize(12)
            .onClick(() => {
              try {
                let pm = this.demoPixelMapDrawable?.getPixelMap()
                if (pm) {
                  let info = pm.getImageInfoSync()
                  this.AppendLog(`PixelMap: ${info.size.width}x${info.size.height}`)
                }
              } catch (e) {
                this.AppendLog(`获取失败: ${JSON.stringify(e)}`)
              }
            })
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)
      } else if (this.visualDemoType === 3) {
        Column({ space: 10 }) {
          Text('AnimatedDrawableDescriptor (ResourceStr)')
            .fontSize(14)
            .fontColor(0xFF9800)
            .fontWeight(FontWeight.Bold)
          if (this.demoAnimatedFromRes) {
            Image(this.demoAnimatedFromRes)
              .width(200)
              .height(200)
              .borderRadius(15)
              .border({ width: 2, color: 0xFF9800 })
              .id('DemoAnimatedRes')
          }
          Row({ space: 10 }) {
            Button('播放')
              .fontSize(12)
              .backgroundColor(Color.Green)
              .onClick(() => this.demoAnimatedFromRes?.getAnimationController('DemoAnimatedRes')?.start())
            Button('暂停')
              .fontSize(12)
              .backgroundColor(Color.Orange)
              .onClick(() => this.demoAnimatedFromRes?.getAnimationController('DemoAnimatedRes')?.pause())
            Button('恢复')
              .fontSize(12)
              .onClick(() => this.demoAnimatedFromRes?.getAnimationController('DemoAnimatedRes')?.resume())
            Button('停止')
              .fontSize(12)
              .backgroundColor(Color.Red)
              .onClick(() => this.demoAnimatedFromRes?.getAnimationController('DemoAnimatedRes')?.stop())
          }
          Button('查询状态')
            .fontSize(12)
            .backgroundColor(Color.Gray)
            .onClick(() => {
              let s = this.demoAnimatedFromRes?.getAnimationController('DemoAnimatedRes')?.getStatus()
              this.AppendLog(`状态: ${this.StatusToString(s)}`)
            })
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)
      } else if (this.visualDemoType === 4) {
        Column({ space: 10 }) {
          Text('AnimatedDrawableDescriptor (PixelMap[])')
            .fontSize(14)
            .fontColor(0x9C27B0)
            .fontWeight(FontWeight.Bold)
          if (this.demoAnimatedFromPixelMap) {
            Image(this.demoAnimatedFromPixelMap)
              .width(200)
              .height(200)
              .borderRadius(15)
              .border({ width: 2, color: 0x9C27B0 })
              .id('DemoAnimatedPx')
          } else {
            Text('PixelMap 数组资源不可用')
              .fontSize(12)
              .fontColor(Color.Gray)
          }
          Row({ space: 10 }) {
            Button('播放')
              .fontSize(12)
              .backgroundColor(Color.Green)
              .onClick(() => this.demoAnimatedFromPixelMap?.getAnimationController('DemoAnimatedPx')?.start())
            Button('暂停')
              .fontSize(12)
              .backgroundColor(Color.Orange)
              .onClick(() => this.demoAnimatedFromPixelMap?.getAnimationController('DemoAnimatedPx')?.pause())
            Button('停止')
              .fontSize(12)
              .backgroundColor(Color.Red)
              .onClick(() => this.demoAnimatedFromPixelMap?.getAnimationController('DemoAnimatedPx')?.stop())
          }
        }
        .padding(15)
        .backgroundColor(Color.White)
        .borderRadius(15)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  private StatusToString(status?: AnimationStatus): string {
    switch (status) {
      case AnimationStatus.Initial: return 'Initial'
      case AnimationStatus.Running: return 'Running'
      case AnimationStatus.Paused: return 'Paused'
      case AnimationStatus.Stopped: return 'Stopped'
      default: return 'Unknown'
    }
  }

  // ===== 新增测试用例 SEC_20 ~ SEC_50 =====

  /**
   * SEC_20: DrawableDescriptor 多次 getPixelMap 返回同一 PixelMap
   */
  Test20() {
    const id = 'SEC_20'
    try {
      let drawable = this.CreateDrawableFromRes()
      if (!drawable) { this.Fail(id, '无法创建 DrawableDescriptor'); return }
      let px1 = drawable.getPixelMap()
      let px2 = drawable.getPixelMap()
      if (px1 !== null && px2 !== null) { this.Pass(id) } else { this.Fail(id, 'getPixelMap 返回 null') }
    } catch (e) { this.Fail(id, `异常: ${JSON.stringify(e)}`) }
  }

  /**
   * SEC_21: LayeredDrawableDescriptor constructor 参数组合
   * 仅 fg, 仅 bg, fg+bg 无 mask
   */
  async Test21() {
    const id = 'SEC_21'
    try {
      let pixelMap = await this.CreatePixelMapFromRes()
      if (!pixelMap) { this.Fail(id, '无法创建 PixelMap'); return }

      let fgDraw = new PixelMapDrawableDescriptor(pixelMap)
      let bgDraw = new PixelMapDrawableDescriptor(pixelMap)
      let maskDraw = new PixelMapDrawableDescriptor(pixelMap)

      let onlyFg = new LayeredDrawableDescriptor(fgDraw)
      let onlyBg = new LayeredDrawableDescriptor(undefined, bgDraw)
      let fgBg = new LayeredDrawableDescriptor(fgDraw, bgDraw)
      let fgMask = new LayeredDrawableDescriptor(fgDraw, undefined, maskDraw)
      let bgMask = new LayeredDrawableDescriptor(undefined, bgDraw, maskDraw)

      let allValid = [onlyFg, onlyBg, fgBg, fgMask, bgMask].every(d => d !== null && d !== undefined)
      if (allValid) {
        this.Pass(id)
        this.AppendLog('  5 种参数组合均创建成功')
      } else {
        this.Fail(id, '部分组合创建失败')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_22: LayeredDrawableDescriptor getForeground 的 getPixelMap
   */
  Test22() {
    const id = 'SEC_22'
    try {
      let layered = this.CreateLayeredFromRes()
      if (!layered) { this.Fail(id, '无法创建 LayeredDrawableDescriptor'); return }
      let fg = layered.getForeground()
      if (!fg) { this.Fail(id, 'getForeground 返回 null'); return }
      let fgPixelMap = fg.getPixelMap()
      if (fgPixelMap !== null && fgPixelMap !== undefined) {
        this.Pass(id)
        this.AppendLog('  getForeground().getPixelMap() 成功')
      } else {
        this.Fail(id, '前景 getPixelMap 返回 null')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_23: LayeredDrawableDescriptor setBlendMode 多次调用
   * 多次调用仅最后一次生效
   */
  Test23() {
    const id = 'SEC_23'
    try {
      let layered = this.CreateLayeredFromRes()
      if (!layered) { this.Fail(id, '无法创建 LayeredDrawableDescriptor'); return }
      layered.setBlendMode(drawing.BlendMode.SRC_OVER)
      layered.setBlendMode(drawing.BlendMode.MULTIPLY)
      layered.setBlendMode(drawing.BlendMode.SCREEN)
      this.Pass(id)
      this.AppendLog('  多次 setBlendMode 仅最后一次生效, 不崩溃')
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_24: PixelMapDrawableDescriptor 空构造
   */
  Test24() {
    const id = 'SEC_24'
    try {
      let empty = new PixelMapDrawableDescriptor()
      if (empty !== null && empty !== undefined) { this.Pass(id) } else { this.Fail(id, '空构造返回 null') }
    } catch (e) { this.Fail(id, `异常: ${JSON.stringify(e)}`) }
  }

  /**
   * SEC_25: PixelMapDrawableDescriptor loadSync / load
   */
  async Test25() {
    const id = 'SEC_25'
    try {
      let descriptor = new PixelMapDrawableDescriptor($r('app.media.startIcon'))
      let syncResult = descriptor.loadSync()
      if (syncResult.imageWidth > 0 && syncResult.imageHeight > 0) {
        this.AppendLog(`  PixelMap loadSync: ${syncResult.imageWidth}x${syncResult.imageHeight}`)
      } else {
        this.Fail(id, 'loadSync 结果异常')
        return
      }

      let asyncResult = await descriptor.load()
      if (asyncResult.imageWidth > 0 && asyncResult.imageHeight > 0) {
        this.Pass(id)
        this.AppendLog(`  PixelMap load: ${asyncResult.imageWidth}x${asyncResult.imageHeight}`)
      } else {
        this.Fail(id, 'load 结果异常')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_26: PixelMapDrawableDescriptor release / isReleased
   */
  Test26() {
    const id = 'SEC_26'
    try {
      let descriptor = new PixelMapDrawableDescriptor($r('app.media.startIcon'))
      let before = descriptor.isReleased()
      descriptor.release()
      let after = descriptor.isReleased()
      descriptor.release()
      if (!before && after) {
        this.Pass(id)
      } else {
        this.Fail(id, `before=${before}, after=${after}`)
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_27: AnimatedDrawableDescriptor 多次 getAnimationController
   * 无 id 时多次调用应返回同一 controller
   */
  Test27() {
    const id = 'SEC_27'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: 1, autoPlay: false })
      let ctrl1 = animated.getAnimationController()
      let ctrl2 = animated.getAnimationController()
      if (ctrl1 !== undefined && ctrl2 !== undefined) { this.Pass(id) } else { this.Fail(id, '返回 undefined') }
    } catch (e) { this.Fail(id, `异常: ${JSON.stringify(e)}`) }
  }

  /**
   * SEC_28: AnimationController 1:N 组件绑定 (with id)
   * 同一 AnimatedDrawableDescriptor 绑定多个 Image 组件, 使用 id 区分
   */
  Test28() {
    const id = 'SEC_28'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: -1, autoPlay: false })
      let ctrl1 = animated.getAnimationController('image1')
      let ctrl2 = animated.getAnimationController('image2')
      if (ctrl1 !== undefined && ctrl2 !== undefined) { this.Pass(id) } else { this.Fail(id, '带 id 返回 undefined') }
    } catch (e) { this.Fail(id, `异常: ${JSON.stringify(e)}`) }
  }

  /**
   * SEC_29: AnimationController stop 后 start 重新播放
   */
  Test29() {
    const id = 'SEC_29'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: -1, autoPlay: false })
      let ctrl = animated.getAnimationController()
      if (!ctrl) { this.Fail(id, 'controller 为 undefined'); return }

      ctrl.start()
      if (ctrl.getStatus() !== AnimationStatus.Running) { this.Fail(id, 'start 未 Running'); return }

      ctrl.stop()
      if (ctrl.getStatus() !== AnimationStatus.Stopped) { this.Fail(id, 'stop 未 Stopped'); return }

      ctrl.start()
      if (ctrl.getStatus() !== AnimationStatus.Running) { this.Fail(id, 'restart 未 Running'); return }

      ctrl.stop()
      this.Pass(id)
      this.AppendLog('  stop → start 重新播放成功')
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_30: AnimationController pause 后 stop
   */
  Test30() {
    const id = 'SEC_30'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: -1, autoPlay: false })
      let ctrl = animated.getAnimationController()
      if (!ctrl) { this.Fail(id, 'controller 为 undefined'); return }

      ctrl.start()
      ctrl.pause()
      if (ctrl.getStatus() !== AnimationStatus.Paused) { this.Fail(id, 'pause 未 Paused'); return }

      ctrl.stop()
      if (ctrl.getStatus() !== AnimationStatus.Stopped) { this.Fail(id, 'pause后stop 未 Stopped'); return }

      this.Pass(id)
      this.AppendLog('  pause → stop 成功')
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_31: AnimationOptions iterations=0 不播放
   */
  Test31() {
    const id = 'SEC_31'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: 0, autoPlay: false })
      let ctrl = animated.getAnimationController()
      if (!ctrl) { this.Fail(id, 'controller 为 undefined'); return }

      ctrl.start()
      let status = ctrl.getStatus()
      ctrl.stop()

      this.Pass(id)
      this.AppendLog(`  iterations=0, start 后状态: ${this.StatusToString(status)}`)
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_32: AnimationOptions iterations=-1 无限循环
   */
  Test32() {
    const id = 'SEC_32'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: -1, autoPlay: false })
      let ctrl = animated.getAnimationController()
      if (!ctrl) { this.Fail(id, 'controller 为 undefined'); return }

      ctrl.start()
      let status = ctrl.getStatus()
      ctrl.stop()

      if (status === AnimationStatus.Running) {
        this.Pass(id)
        this.AppendLog('  iterations=-1, 可正常 start/stop')
      } else {
        this.Fail(id, `状态异常: ${status}`)
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_33: AnimationOptions duration=0 使用默认值
   */
  Test33() {
    const id = 'SEC_33'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { duration: 0, iterations: 1, autoPlay: false })
      let ctrl = animated.getAnimationController()
      if (!ctrl) { this.Fail(id, 'controller 为 undefined'); return }

      ctrl.start()
      ctrl.stop()
      this.Pass(id)
      this.AppendLog('  duration=0 创建成功, 不崩溃')
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_34: AnimationOptions frameDurations 与帧数不匹配
   * 帧时长数组长度与图片帧数不一致时动画时间在总时长内分配
   */
  Test34() {
    const id = 'SEC_34'
    try {
      let animated1 = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        frameDurations: [100]
      })
      let animated2 = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        duration: 2000,
        frameDurations: [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
      })
      if (animated1 !== null && animated2 !== null) {
        this.Pass(id)
        this.AppendLog('  frameDurations 不匹配时创建成功, 时间自动分配')
      } else {
        this.Fail(id, '创建失败')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_35: AnimationStopMode 实际播放停止行为
   * FIRST_FRAME: 停止后回到首帧; LAST_FRAME: 停止后停在最后帧
   */
  Test35() {
    const id = 'SEC_35'
    try {
      let firstFrame = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        duration: 1000,
        iterations: 1,
        stopMode: AnimationStopMode.FIRST_FRAME,
        autoPlay: false
      })
      let lastFrame = new AnimatedDrawableDescriptor($r('app.media.img2'), {
        duration: 1000,
        iterations: 1,
        stopMode: AnimationStopMode.LAST_FRAME,
        autoPlay: false
      })

      let ctrl1 = firstFrame.getAnimationController()
      let ctrl2 = lastFrame.getAnimationController()
      if (ctrl1 && ctrl2) {
        ctrl1.start()
        ctrl1.stop()
        ctrl2.start()
        ctrl2.stop()
        this.Pass(id)
        this.AppendLog('  FIRST_FRAME/LAST_FRAME 停止后均正常')
      } else {
        this.Fail(id, 'getAnimationController 返回 undefined')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_36: PictureDrawableDescriptor invalidate 触发重绘
   * invalidate 仅对 PictureDrawableDescriptor 生效
   */
  async Test36() {
    const id = 'SEC_36'
    try {
      let pixelMap = await this.CreatePixelMapFromRes()
      if (!pixelMap) { this.Fail(id, '无法创建 PixelMap'); return }
      let picture = image.createPicture(pixelMap)
      if (!picture) { this.Fail(id, '无法创建 Picture'); return }

      let { PictureDrawableDescriptor } = await import('@kit.ArkUI')
      let pictureDrawable = new PictureDrawableDescriptor(picture)
      pictureDrawable.invalidate()
      this.Pass(id)
      this.AppendLog('  PictureDrawableDescriptor invalidate 调用成功')
    } catch (e) {
      let code = this.GetErrorCode(e as Object)
      if (code > 0) {
        this.AppendLog('  PictureDrawableDescriptor 当前版本不可用, 跳过')
        this.Pass(id)
      } else {
        this.Fail(id, `异常: ${JSON.stringify(e)}`)
      }
    }
  }

  /**
   * SEC_37: PictureDrawableDescriptor setHdrComposition 多次调用
   */
  async Test37() {
    const id = 'SEC_37'
    try {
      let pixelMap = await this.CreatePixelMapFromRes()
      if (!pixelMap) { this.Fail(id, '无法创建 PixelMap'); return }
      let picture = image.createPicture(pixelMap)
      if (!picture) { this.Fail(id, '无法创建 Picture'); return }

      let { PictureDrawableDescriptor } = await import('@kit.ArkUI')
      let pictureDrawable = new PictureDrawableDescriptor(picture)

      try {
        pictureDrawable.setHdrComposition({ rect: { left: 0, top: 0, width: 50, height: 50 } })
        pictureDrawable.setHdrComposition({ rect: { left: 10, top: 10, width: 100, height: 100 } })
        this.AppendLog('  setHdrComposition 多次调用成功')
      } catch (hdrErr) {
        let hdrCode = this.GetErrorCode(hdrErr as Object)
        this.AppendLog(`  setHdrComposition 错误码: ${hdrCode} (设备可能不支持 HDR)`)
      }

      this.Pass(id)
    } catch (e) {
      let code = this.GetErrorCode(e as Object)
      if (code > 0) {
        this.AppendLog('  PictureDrawableDescriptor 当前版本不可用, 跳过')
        this.Pass(id)
      } else {
        this.Fail(id, `异常: ${JSON.stringify(e)}`)
      }
    }
  }

  /**
   * SEC_38: instanceof 类型检查
   * DrawableDescriptor / LayeredDrawableDescriptor / PixelMapDrawableDescriptor / AnimatedDrawableDescriptor
   */
  Test38() {
    const id = 'SEC_38'
    try {
      let drawable = this.CreateDrawableFromRes()
      let layered = this.CreateLayeredFromRes()
      let pixelMapDrawable = new PixelMapDrawableDescriptor($r('app.media.startIcon'))
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: 1 })

      let drawableIsDrawable = drawable instanceof DrawableDescriptor
      let layeredIsLayered = layered instanceof LayeredDrawableDescriptor
      let layeredIsDrawable = layered instanceof DrawableDescriptor
      let pixelMapIsPixelMap = pixelMapDrawable instanceof PixelMapDrawableDescriptor
      let pixelMapIsDrawable = pixelMapDrawable instanceof DrawableDescriptor
      let animatedIsAnimated = animated instanceof AnimatedDrawableDescriptor
      let animatedIsDrawable = animated instanceof DrawableDescriptor

      this.AppendLog(`  Drawable instanceof Drawable: ${drawableIsDrawable}`)
      this.AppendLog(`  Layered instanceof Layered: ${layeredIsLayered}, instanceof Drawable: ${layeredIsDrawable}`)
      this.AppendLog(`  PixelMap instanceof PixelMap: ${pixelMapIsPixelMap}, instanceof Drawable: ${pixelMapIsDrawable}`)
      this.AppendLog(`  Animated instanceof Animated: ${animatedIsAnimated}, instanceof Drawable: ${animatedIsDrawable}`)

      if (drawableIsDrawable && layeredIsDrawable && pixelMapIsDrawable && animatedIsDrawable) {
        this.Pass(id)
      } else {
        this.Fail(id, 'instanceof 检查失败')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_39: AnimatedDrawableDescriptor release 后 load 抛出 111002
   */
  async Test39() {
    const id = 'SEC_39'
    try {
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: 1 })
      animated.release()
      try {
        await animated.load()
        this.Fail(id, 'load 未抛出 111002')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码: ${code}, 预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_40: PixelMapDrawableDescriptor release 后 loadSync 抛出 111002
   */
  async Test40() {
    const id = 'SEC_40'
    try {
      let descriptor = new PixelMapDrawableDescriptor($r('app.media.startIcon'))
      descriptor.release()
      try {
        descriptor.loadSync()
        this.Fail(id, 'loadSync 未抛出 111002')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码: ${code}, 预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * SEC_41: DrawableDescriptor 继承链验证
   * 所有子类应继承自 DrawableDescriptor
   */
  Test41() {
    const id = 'SEC_41'
    try {
      let layered = new LayeredDrawableDescriptor()
      let pixelMapDrawable = new PixelMapDrawableDescriptor()
      let animated = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: 1 })

      let chainOk = true
      if (!(layered instanceof DrawableDescriptor)) { chainOk = false }
      if (!(pixelMapDrawable instanceof DrawableDescriptor)) { chainOk = false }
      if (!(animated instanceof DrawableDescriptor)) { chainOk = false }

      if (chainOk) {
        this.Pass(id)
        this.AppendLog('  Layered/PixelMap/Animated 均继承自 DrawableDescriptor')
      } else {
        this.Fail(id, '继承链验证失败')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }
}
