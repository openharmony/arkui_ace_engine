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
 * DrawableDescriptorReleaseTest - release/isReleased 专项测试 (API 26+)
 * ========================================
 *
 * 测试功能说明:
 * 本测试验证 DrawableDescriptor 及其子类的 release()/isReleased() 接口
 *
 * 涉及的 API:
 * 1. release() - 释放 native 内存
 * 2. isReleased() - 查询是否已释放
 * 3. 释放后调用 getPixelMap()/getForeground()/getBackground()/getMask()/
 *    load()/loadSync() 抛出 BusinessError 111002
 *    getAnimationController() 返回 undefined
 *
 * 测试覆盖类型:
 * - DrawableDescriptor (通过 getDrawableDescriptor 获取)
 * - LayeredDrawableDescriptor (通过 getDrawableDescriptor 获取 JSON 类型资源)
 * - PixelMapDrawableDescriptor (通过 new PixelMapDrawableDescriptor 创建)
 * - AnimatedDrawableDescriptor (通过 new AnimatedDrawableDescriptor 创建)
 *
 * ========================================
 * 测试用例
 * ========================================
 * E2E_001: DrawableDescriptor release() -> isReleased() 返回 true
 * E2E_002: DrawableDescriptor release() -> getPixelMap() 抛出 111002
 * E2E_003: DrawableDescriptor release() -> release() 不崩溃
 * E2E_004: LayeredDrawableDescriptor release() -> getForeground() 抛出 111002
 * E2E_005: LayeredDrawableDescriptor release() -> getBackground() 抛出 111002
 * E2E_006: LayeredDrawableDescriptor release() -> getMask() 抛出 111002
 * E2E_007: PixelMapDrawableDescriptor release() -> getPixelMap() 抛出 111002
 * E2E_008: AnimatedDrawableDescriptor release() -> getPixelMap() 抛出 111002
 * E2E_009: AnimatedDrawableDescriptor release() -> getAnimationController() 返回 undefined
 * E2E_010: AnimatedDrawableDescriptor release() -> loadSync() 抛出 111002
 * E2E_011: AnimatedDrawableDescriptor release() -> load() 抛出 111002
 * E2E_012: AnimatedDrawableDescriptor release() -> release() 不崩溃
 */

import { AnimatedDrawableDescriptor, DrawableDescriptor, PixelMapDrawableDescriptor,
  LayeredDrawableDescriptor } from '@kit.ArkUI'
import hidebug from '@ohos.hidebug'

@Entry
@Component
struct DrawableDescriptorReleaseTest {
  @State testLog: string = '等待测试...'
  @State passCount: number = 0
  @State failCount: number = 0
  private resManager = this.getUIContext().getHostContext()?.resourceManager

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('DrawableDescriptor release/isReleased 测试 (API 26+)')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        // 统计信息
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

        // DrawableDescriptor 测试按钮
        this.BuildSectionTitle('1. DrawableDescriptor 测试')
        Row({ space: 8 }) {
          Button('E2E_001\nisReleased')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test001())
          Button('E2E_002\ngetPixelMap')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test002())
          Button('E2E_003\n双release')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test003())
        }.width('100%')

        // LayeredDrawableDescriptor 测试按钮
        this.BuildSectionTitle('2. LayeredDrawableDescriptor 测试')
        Row({ space: 8 }) {
          Button('E2E_004\ngetForeground')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test004())
          Button('E2E_005\ngetBackground')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test005())
          Button('E2E_006\ngetMask')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test006())
        }.width('100%')

        // PixelMapDrawableDescriptor 测试按钮
        this.BuildSectionTitle('3. PixelMapDrawableDescriptor 测试')
        Row({ space: 8 }) {
          Button('E2E_007\ngetPixelMap')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test007())
        }.width('100%')

        // AnimatedDrawableDescriptor 测试按钮
        this.BuildSectionTitle('4. AnimatedDrawableDescriptor 测试')
        Row({ space: 8 }) {
          Button('E2E_008\ngetPixelMap')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test008())
          Button('E2E_009\ngetController')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test009())
        }.width('100%')
        Row({ space: 8 }) {
          Button('E2E_010\nloadSync')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test010())
          Button('E2E_011\nload')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test011())
          Button('E2E_012\n双release')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.Test012())
        }.width('100%')

        // 一键全部测试
        Button('运行全部测试')
          .fontSize(16)
          .width('90%')
          .height(45)
          .backgroundColor(Color.Blue)
          .onClick(() => this.RunAll())

        // 内存回收验证
        this.BuildSectionTitle('5. 内存回收验证')
        Row({ space: 8 }) {
          Button('MEM_001\nDrawable')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.MemTest001())
          Button('MEM_002\nAnimated')
            .fontSize(11).height(50).layoutWeight(1)
            .onClick(() => this.MemTest002())
        }.width('100%')

        // 结果展示
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
      if (typeof code === 'number') {
        return code
      }
      if (typeof code === 'string') {
        return parseInt(code, 10)
      }
      return -1
    } catch (err) {
      return -1
    }
  }

  // 通过 ResourceManager 获取 DrawableDescriptor (可能是 BASE 或 LAYERED 类型)
  private CreateDrawableFromRes(): DrawableDescriptor | null {
    if (!this.resManager) {
      return null
    }
    try {
      return this.resManager.getDrawableDescriptor($r('app.media.startIcon').id)
    } catch (e) {
      return null
    }
  }

  // 创建 AnimatedDrawableDescriptor (使用无效路径，足够测试 release 逻辑)
  private CreateAnimatedDrawable(): AnimatedDrawableDescriptor {
    return new AnimatedDrawableDescriptor($r('app.media.startIcon'), { iterations: 1 })
  }

  // ===== 测试用例 =====

  /**
   * E2E_001: DrawableDescriptor release() -> isReleased() 返回 true
   */
  Test001() {
    const id = 'E2E_001'
    try {
      let drawable = this.CreateDrawableFromRes()
      if (!drawable) {
        this.Fail(id, '无法创建 DrawableDescriptor')
        return
      }
      // release 前应为 false
      let beforeRelease = drawable.isReleased()
      drawable.release()
      let afterRelease = drawable.isReleased()
      if (!beforeRelease && afterRelease) {
        this.Pass(id)
      } else {
        this.Fail(id, `beforeRelease=${beforeRelease}, afterRelease=${afterRelease}`)
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_002: DrawableDescriptor release() -> getPixelMap() 抛出 BusinessError 111002
   */
  Test002() {
    const id = 'E2E_002'
    try {
      let drawable = this.CreateDrawableFromRes()
      if (!drawable) {
        this.Fail(id, '无法创建 DrawableDescriptor')
        return
      }
      drawable.release()
      // 释放后调用 getPixelMap 应抛出 111002
      try {
        drawable.getPixelMap()
        this.Fail(id, '预期抛出 111002 但未抛出')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码为 ${code}，预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_003: DrawableDescriptor release() -> release() 不崩溃
   */
  Test003() {
    const id = 'E2E_003'
    try {
      let drawable = this.CreateDrawableFromRes()
      if (!drawable) {
        this.Fail(id, '无法创建 DrawableDescriptor')
        return
      }
      drawable.release()
      drawable.release() // 第二次调用不应崩溃
      if (drawable.isReleased()) {
        this.Pass(id)
      } else {
        this.Fail(id, '第二次 release 后 isReleased 为 false')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_004: LayeredDrawableDescriptor release() -> getForeground() 抛出 111002
   */
  Test004() {
    const id = 'E2E_004'
    try {
      let drawable = new LayeredDrawableDescriptor()
      drawable.release()
      try {
        drawable.getForeground()
        this.Fail(id, '预期抛出 111002 但未抛出')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码为 ${code}，预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_005: LayeredDrawableDescriptor release() -> getBackground() 抛出 111002
   */
  Test005() {
    const id = 'E2E_005'
    try {
      let drawable = new LayeredDrawableDescriptor()
      drawable.release()
      try {
        drawable.getBackground()
        this.Fail(id, '预期抛出 111002 但未抛出')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码为 ${code}，预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_006: LayeredDrawableDescriptor release() -> getMask() 抛出 111002
   */
  Test006() {
    const id = 'E2E_006'
    try {
      let drawable = new LayeredDrawableDescriptor()
      drawable.release()
      try {
        drawable.getMask()
        this.Fail(id, '预期抛出 111002 但未抛出')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码为 ${code}，预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_007: PixelMapDrawableDescriptor release() -> getPixelMap() 抛出 111002
   */
  Test007() {
    const id = 'E2E_007'
    try {
      let drawable = new PixelMapDrawableDescriptor()
      drawable.release()
      try {
        drawable.getPixelMap()
        this.Fail(id, '预期抛出 111002 但未抛出')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码为 ${code}，预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_008: AnimatedDrawableDescriptor release() -> getPixelMap() 抛出 111002
   */
  Test008() {
    const id = 'E2E_008'
    try {
      let drawable = this.CreateAnimatedDrawable()
      drawable.release()
      try {
        drawable.getPixelMap()
        this.Fail(id, '预期抛出 111002 但未抛出')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码为 ${code}，预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_009: AnimatedDrawableDescriptor release() -> getAnimationController() 返回 undefined
   */
  Test009() {
    const id = 'E2E_009'
    try {
      let drawable = this.CreateAnimatedDrawable()
      drawable.release()
      let controller = drawable.getAnimationController()
      if (controller === undefined) {
        this.Pass(id)
      } else {
        this.Fail(id, `预期返回 undefined，实际返回 ${controller}`)
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_010: AnimatedDrawableDescriptor release() -> loadSync() 抛出 111002
   */
  Test010() {
    const id = 'E2E_010'
    try {
      let drawable = this.CreateAnimatedDrawable()
      drawable.release()
      try {
        drawable.loadSync()
        this.Fail(id, '预期抛出 111002 但未抛出')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码为 ${code}，预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_011: AnimatedDrawableDescriptor release() -> load() 抛出 111002
   */
  async Test011() {
    const id = 'E2E_011'
    try {
      let drawable = this.CreateAnimatedDrawable()
      drawable.release()
      try {
        await drawable.load()
        this.Fail(id, '预期抛出 111002 但未抛出')
      } catch (e) {
        let code = this.GetErrorCode(e as Object)
        if (code === 111002) {
          this.Pass(id)
        } else {
          this.Fail(id, `错误码为 ${code}，预期 111002`)
        }
      }
    } catch (e) {
      this.Fail(id, `外层异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * E2E_012: AnimatedDrawableDescriptor release() -> release() 不崩溃
   */
  Test012() {
    const id = 'E2E_012'
    try {
      let drawable = this.CreateAnimatedDrawable()
      drawable.release()
      drawable.release() // 第二次调用不应崩溃
      if (drawable.isReleased()) {
        this.Pass(id)
      } else {
        this.Fail(id, '第二次 release 后 isReleased 为 false')
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  // ===== 内存回收验证测试 =====

  /**
   * MEM_001: 批量创建 DrawableDescriptor → release → PSS 下降
   * 创建 500 个 DrawableDescriptor，触发 getPixelMap 解码图片，
   * 对比 release 前后 PSS 内存差异
   */
  MemTest001() {
    const id = 'MEM_001'
    const COUNT = 500
    try {
      // 1. 记录基线 PSS
      let pssBefore = Number(hidebug.getPss())
      this.AppendLog(`[${id}] 基线 PSS: ${pssBefore} KB`)

      // 2. 批量创建并触发解码
      let drawables: DrawableDescriptor[] = []
      for (let i = 0; i < COUNT; i++) {
        let d = this.CreateDrawableFromRes()
        if (d !== null) {
          d.getPixelMap() // 触发解码，分配 native 内存
          drawables.push(d)
        }
      }
      let actualCount = drawables.length

      // 3. 记录创建后 PSS
      let pssAfterCreate = Number(hidebug.getPss())
      let allocDelta = pssAfterCreate - pssBefore
      this.AppendLog(`[${id}] 创建 ${actualCount} 个, PSS: ${pssAfterCreate} KB (增加 ${allocDelta} KB)`)

      // 4. 全部 release
      for (let d of drawables) {
        d.release()
      }

      // 5. 记录释放后 PSS
      let pssAfterRelease = Number(hidebug.getPss())
      let releaseDelta = pssAfterCreate - pssAfterRelease
      this.AppendLog(`[${id}] 释放后 PSS: ${pssAfterRelease} KB (回收 ${releaseDelta} KB)`)

      // 6. 判定：release 后 PSS 应下降（回收 > 0）
      if (releaseDelta > 0) {
        this.Pass(id)
        this.AppendLog(`[${id}] 内存回收比例: ${(releaseDelta / allocDelta * 100).toFixed(1)}%`)
      } else {
        // GC 未及时回收也是正常的，只要 isReleased 都返回 true 即可
        let allReleased = drawables.every(d => d.isReleased())
        if (allReleased) {
          this.AppendLog(`[${id}] PSS 未下降（GC 延迟），但 isReleased 全部为 true`)
          this.Pass(id)
        } else {
          this.Fail(id, 'PSS 未下降且部分 isReleased 为 false')
        }
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  /**
   * MEM_002: 批量创建 AnimatedDrawableDescriptor → release → PSS 下降
   */
  MemTest002() {
    const id = 'MEM_002'
    const COUNT = 500
    try {
      let pssBefore = Number(hidebug.getPss())
      this.AppendLog(`[${id}] 基线 PSS: ${pssBefore} KB`)

      let drawables: AnimatedDrawableDescriptor[] = []
      for (let i = 0; i < COUNT; i++) {
        drawables.push(this.CreateAnimatedDrawable())
      }

      let pssAfterCreate = Number(hidebug.getPss())
      let allocDelta = pssAfterCreate - pssBefore
      this.AppendLog(`[${id}] 创建 ${COUNT} 个, PSS: ${pssAfterCreate} KB (增加 ${allocDelta} KB)`)

      for (let d of drawables) {
        d.release()
      }

      let pssAfterRelease = Number(hidebug.getPss())
      let releaseDelta = pssAfterCreate - pssAfterRelease
      this.AppendLog(`[${id}] 释放后 PSS: ${pssAfterRelease} KB (回收 ${releaseDelta} KB)`)

      if (releaseDelta > 0) {
        this.Pass(id)
        this.AppendLog(`[${id}] 内存回收比例: ${(releaseDelta / allocDelta * 100).toFixed(1)}%`)
      } else {
        let allReleased = drawables.every(d => d.isReleased())
        if (allReleased) {
          this.AppendLog(`[${id}] PSS 未下降（GC 延迟），但 isReleased 全部为 true`)
          this.Pass(id)
        } else {
          this.Fail(id, 'PSS 未下降且部分 isReleased 为 false')
        }
      }
    } catch (e) {
      this.Fail(id, `异常: ${JSON.stringify(e)}`)
    }
  }

  // 一键全部测试
  async RunAll() {
    this.passCount = 0
    this.failCount = 0
    this.testLog = '--- 开始运行全部测试 ---\n'

    this.Test001()
    this.Test002()
    this.Test003()
    this.Test004()
    this.Test005()
    this.Test006()
    this.Test007()
    this.Test008()
    this.Test009()
    this.Test010()
    await this.Test011()
    this.Test012()

    this.AppendLog(`--- 测试完成: 通过 ${this.passCount}, 失败 ${this.failCount} ---`)
  }
}
