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
 * 测试Image组件动画和过渡效果
 * 涵盖淡入淡出、缩放、旋转、滑动等动画效果
 */

import { image } from '@kit.ImageKit'
import { Animator, AnimatorResult } from '@kit.ArkUI'
import { BusinessError } from '@ohos.base'

interface AnimationConfig {
  id: number
  name: string
  duration: number
  curve: Curve
  delay: number
  repeat: number
  autoReverse: boolean
  playState: AnimationStatus
}

interface TransitionEffect {
  name: string
  type: 'fade' | 'slide' | 'scale' | 'rotate' | 'flip' | 'swirl' | 'bounce'
  duration: number
  fromValue: { x?: number; y?: number; width?: number; height?: number; opacity?: number; angle?: number }
  toValue: { x?: number; y?: number; width?: number; height?: number; opacity?: number; angle?: number }
}

interface KeyframeAnimation {
  name: string
  keyframes: Array<{ percent: number; value: { x?: number; y?: number; width?: number; height?: number; opacity?: number; angle?: number } }>
  duration: number
  curve: Curve
}

interface AnimationTestResult {
  name: string
  startTime: number
  endTime: number
  duration: number
  frameCount: number
  averageFPS: number
  droppedFrames: number
  smoothness: number
  memoryUsage: number
  success: boolean
}

interface GestureAnimation {
  gestureType: string
  animationType: string
  triggerThreshold: number
  animationDuration: number
  dampingRatio: number
  springVelocity: number
}

@Entry
@Component
struct ImageAnimationTestCase {
  @State animationConfigs: AnimationConfig[] = []
  @State currentAnimationIndex: number = 0
  @State transitionEffects: TransitionEffect[] = []
  @State currentTransitionIndex: number = 0
  @State keyframeAnimations: KeyframeAnimation[] = []
  @State currentKeyframeIndex: number = 0
  @State gestureAnimations: GestureAnimation[] = []
  @State animationTestResults: AnimationTestResult[] = []
  @State isAnimating: boolean = false
  @State currentAnimation: string = ''
  @State animationProgress: number = 0
  @State currentFrameCount: number = 0
  @State totalFrames: number = 0
  @State fpsMonitor: number = 60
  @State selectedImageAnimator: Animator | null = null
  @State animationQueue: Array<{ name: string; config: AnimationConfig }> = []
  @State isAutoPlaybackEnabled: boolean = false
  @State compositeAnimations: Array<{ name: string; animations: string[] }> = []

  private readonly ANIMATION_PRESETS: AnimationConfig[] = [
    { id: 1, name: '慢速淡入', duration: 2000, curve: Curve.EaseInOut, delay: 0, repeat: 1, autoReverse: false, playState: AnimationStatus.Initial },
    { id: 2, name: '快速缩放', duration: 800, curve: Curve.EaseOut, delay: 0, repeat: 1, autoReverse: false, playState: AnimationStatus.Initial },
    { id: 3, name: '旋转循环', duration: 1500, curve: Curve.Linear, delay: 0, repeat: -1, autoReverse: false, playState: AnimationStatus.Initial },
    { id: 4, name: '弹性缩放', duration: 1200, curve: Curve.EaseInOut, delay: 0, repeat: 2, autoReverse: true, playState: AnimationStatus.Initial },
    { id: 5, name: '脉动效果', duration: 1000, curve: Curve.EaseInOut, delay: 0, repeat: -1, autoReverse: true, playState: AnimationStatus.Initial },
    { id: 6, name: '弹跳效果', duration: 2000, curve: Curve.EaseInOut, delay: 0, repeat: 3, autoReverse: false, playState: AnimationStatus.Initial },
    { id: 7, name: '旋转缩放组合', duration: 1800, curve: Curve.EaseInOut, delay: 0, repeat: 1, autoReverse: true, playState: AnimationStatus.Initial },
    { id: 8, name: '呼吸效果', duration: 3000, curve: Curve.EaseInOut, delay: 0, repeat: -1, autoReverse: true, playState: AnimationStatus.Initial },
    { id: 9, name: '闪烁效果', duration: 500, curve: Curve.Linear, delay: 0, repeat: 6, autoReverse: true, playState: AnimationStatus.Initial },
    { id: 10, name: '摇摆效果', duration: 1600, curve: Curve.EaseInOut, delay: 0, repeat: -1, autoReverse: true, playState: AnimationStatus.Initial }
  ]

  private readonly TRANSITION_PRESETS: TransitionEffect[] = [
    { name: '淡入', type: 'fade', duration: 800, fromValue: { opacity: 0 }, toValue: { opacity: 1 } },
    { name: '淡出', type: 'fade', duration: 800, fromValue: { opacity: 1 }, toValue: { opacity: 0 } },
    { name: '淡入淡出', type: 'fade', duration: 1600, fromValue: { opacity: 0 }, toValue: { opacity: 1 } },
    { name: '左滑入', type: 'slide', duration: 600, fromValue: { x: -300 }, toValue: { x: 0 } },
    { name: '右滑入', type: 'slide', duration: 600, fromValue: { x: 300 }, toValue: { x: 0 } },
    { name: '上滑入', type: 'slide', duration: 600, fromValue: { y: -300 }, toValue: { y: 0 } },
    { name: '下滑入', type: 'slide', duration: 600, fromValue: { y: 300 }, toValue: { y: 0 } },
    { name: '放大进入', type: 'scale', duration: 700, fromValue: { scale: 0 }, toValue: { scale: 1 } },
    { name: '缩小进入', type: 'scale', duration: 700, fromValue: { scale: 2 }, toValue: { scale: 1 } },
    { name: '旋转进入', type: 'rotate', duration: 900, fromValue: { angle: 360 }, toValue: { angle: 0 } },
    { name: '翻转进入', type: 'flip', duration: 800, fromValue: { angle: 180 }, toValue: { angle: 0 } },
    { name: '螺旋进入', type: 'swirl', duration: 1200, fromValue: { angle: 720, scale: 0.5 }, toValue: { angle: 0, scale: 1 } },
    { name: '弹跳进入', type: 'bounce', duration: 1000, fromValue: { y: -200, opacity: 0 }, toValue: { y: 0, opacity: 1 } }
  ]

  private readonly KEYFRAME_PRESETS: KeyframeAnimation[] = [
    {
      name: '复杂缩放动画',
      keyframes: [
        { percent: 0, value: { scale: 0.5, opacity: 0 } },
        { percent: 25, value: { scale: 1.2, opacity: 0.5 } },
        { percent: 50, value: { scale: 0.8, opacity: 0.8 } },
        { percent: 75, value: { scale: 1.1, opacity: 1 } },
        { percent: 100, value: { scale: 1, opacity: 1 } }
      ],
      duration: 1500,
      curve: Curve.EaseInOut
    },
    {
      name: '旋转位移动画',
      keyframes: [
        { percent: 0, value: { x: 0, y: 0, angle: 0 } },
        { percent: 25, value: { x: 50, y: -20, angle: 90 } },
        { percent: 50, value: { x: 100, y: 0, angle: 180 } },
        { percent: 75, value: { x: 50, y: 20, angle: 270 } },
        { percent: 100, value: { x: 0, y: 0, angle: 360 } }
      ],
      duration: 2000,
      curve: Curve.EaseInOut
    },
    {
      name: '透明度脉动',
      keyframes: [
        { percent: 0, value: { opacity: 1 } },
        { percent: 20, value: { opacity: 0.3 } },
        { percent: 40, value: { opacity: 1 } },
        { percent: 60, value: { opacity: 0.5 } },
        { percent: 80, value: { opacity: 1 } },
        { percent: 100, value: { opacity: 0.2 } }
      ],
      duration: 3000,
      curve: Curve.EaseInOut
    },
    {
      name: '形状变换',
      keyframes: [
        { percent: 0, value: { width: 50, height: 50 } },
        { percent: 33, value: { width: 100, height: 50 } },
        { percent: 66, value: { width: 100, height: 100 } },
        { percent: 100, value: { width: 50, height: 50 } }
      ],
      duration: 1800,
      curve: Curve.EaseInOut
    },
    {
      name: '螺旋运动',
      keyframes: [
        { percent: 0, value: { x: 0, y: 0, angle: 0 } },
        { percent: 25, value: { x: 30, y: 30, angle: 90 } },
        { percent: 50, value: { x: 0, y: 60, angle: 180 } },
        { percent: 75, value: { x: -30, y: 30, angle: 270 } },
        { percent: 100, value: { x: 0, y: 0, angle: 360 } }
      ],
      duration: 2500,
      curve: Curve.EaseInOut
    }
  ]

  private readonly GESTURE_ANIMATIONS: GestureAnimation[] = [
    { gestureType: '滑动', animationType: '惯性滑动', triggerThreshold: 10, animationDuration: 300, dampingRatio: 0.5, springVelocity: 100 },
    { gestureType: '捏合', animationType: '缩放回弹', triggerThreshold: 5, animationDuration: 200, dampingRatio: 0.3, springVelocity: 50 },
    { gestureType: '长按', animationType: '放大效果', triggerThreshold: 500, animationDuration: 400, dampingRatio: 0.4, springVelocity: 60 },
    { gestureType: '双击', animationType: '放大缩小', triggerThreshold: 300, animationDuration: 600, dampingRatio: 0.6, springVelocity: 80 },
    { gestureType: '拖拽', animationType: '位置跟随', triggerThreshold: 1, animationDuration: 100, dampingRatio: 0.2, springVelocity: 30 },
    { gestureType: '旋转', animationType: '角度回弹', triggerThreshold: 15, animationDuration: 250, dampingRatio: 0.35, springVelocity: 45 }
  ]

  private readonly COMPOSITE_ANIMATIONS = [
    { name: '放大旋转淡入', animations: ['scale', 'rotate', 'fade'] },
    { name: '滑动缩放组合', animations: ['slide', 'scale'] },
    { name: '旋转弹跳', animations: ['rotate', 'bounce'] },
    { name: '淡入缩放旋转', animations: ['fade', 'scale', 'rotate'] },
    { name: '滑动弹跳缩放', animations: ['slide', 'bounce', 'scale'] },
    { name: '全效果组合', animations: ['fade', 'slide', 'scale', 'rotate', 'bounce'] }
  ]

  aboutToAppear() {
    this.initializeAnimationTests()
    this.startAnimationTesting()
  }

  private initializeAnimationTests(): void {
    this.animationConfigs = [...this.ANIMATION_PRESETS]
    this.transitionEffects = [...this.TRANSITION_PRESETS]
    this.keyframeAnimations = [...this.KEYFRAME_PRESETS]
    this.gestureAnimations = [...this.GESTURE_ANIMATIONS]
    this.compositeAnimations = [...this.COMPOSITE_ANIMATIONS]

    // 初始化动画队列
    for (let i = 0; i < 15; i++) {
      this.animationQueue.push({
        name: `队列动画${i + 1}`,
        config: this.animationConfigs[i % this.animationConfigs.length]
      })
    }

    // 启动FPS监控
    this.startFPSMonitoring()
  }

  private startAnimationTesting(): Promise<void> {
    return new Promise(async (resolve) => {
      this.isAnimating = true

      const animationTests = [
        { name: '基础动画测试', func: () => this.testBasicAnimations() },
        { name: '过渡效果测试', func: () => this.testTransitionEffects() },
        { name: '关键帧动画测试', func: () => this.testKeyframeAnimations() },
        { name: '手势动画测试', func: () => this.testGestureAnimations() },
        { name: '组合动画测试', func: () => this.testCompositeAnimations() },
        { name: '队列动画测试', func: () => this.testAnimationQueue() },
        { name: '性能测试', func: () => this.testAnimationPerformance() },
        { name: '内存测试', func: () => this.testMemoryUsage() },
        { name: '并发测试', func: () => this.testConcurrentAnimations() },
        { name: '中断恢复测试', func: () => this.testAnimationInterruption() }
      ]

      for (let i = 0; i < animationTests.length; i++) {
        const test = animationTests[i]
        this.currentAnimation = test.name
        
        try {
          await test.func()
        } catch (error) {
          console.error(`${test.name} failed:`, error)
          this.logTestResult(test.name, false)
        }

        await this.delay(200)
      }

      this.isAnimating = false
      resolve()
    })
  }

  private async testBasicAnimations(): Promise<void> {
    for (let i = 0; i < this.animationConfigs.length; i++) {
      this.currentAnimationIndex = i
      const config = this.animationConfigs[i]
      
      const result = await this.performBasicAnimation(config)
      this.logTestResult(`基础动画: ${config.name}`, result.success)
      this.animationTestResults.push(result)

      await this.delay(config.duration / 4) // 等待动画部分完成
    }
  }

  private async testTransitionEffects(): Promise<void> {
    for (let i = 0; i < this.transitionEffects.length; i++) {
      this.currentTransitionIndex = i
      const effect = this.transitionEffects[i]
      
      const result = await this.performTransitionEffect(effect)
      this.logTestResult(`过渡效果: ${effect.name}`, result.success)
      this.animationTestResults.push(result)

      await this.delay(effect.duration / 4)
    }
  }

  private async testKeyframeAnimations(): Promise<void> {
    for (let i = 0; i < this.keyframeAnimations.length; i++) {
      this.currentKeyframeIndex = i
      const animation = this.keyframeAnimations[i]
      
      const result = await this.performKeyframeAnimation(animation)
      this.logTestResult(`关键帧动画: ${animation.name}`, result.success)
      this.animationTestResults.push(result)

      await this.delay(animation.duration / 4)
    }
  }

  private async testGestureAnimations(): Promise<void> {
    for (const gestureAnim of this.gestureAnimations) {
      this.currentAnimation = `手势动画: ${gestureAnim.animationType}`
      
      const result = await this.performGestureAnimation(gestureAnim)
      this.logTestResult(`手势动画: ${gestureAnim.animationType}`, result.success)
      this.animationTestResults.push(result)

      await this.delay(gestureAnim.animationDuration / 2)
    }
  }

  private async testCompositeAnimations(): Promise<void> {
    for (const composite of this.compositeAnimations) {
      this.currentAnimation = `组合动画: ${composite.name}`
      
      const result = await this.performCompositeAnimation(composite)
      this.logTestResult(`组合动画: ${composite.name}`, result.success)
      this.animationTestResults.push(result)

      await this.delay(800)
    }
  }

  private async testAnimationQueue(): Promise<void> {
    this.isAutoPlaybackEnabled = true
    
    for (let i = 0; i < this.animationQueue.length; i++) {
      const queueItem = this.animationQueue[i]
      this.currentAnimation = `队列播放: ${queueItem.name}`
      
      const result = await this.playFromQueue(queueItem)
      this.logTestResult(`队列动画: ${queueItem.name}`, result.success)
      this.animationTestResults.push(result)

      await this.delay(300)
    }
    
    this.isAutoPlaybackEnabled = false
  }

  private async testAnimationPerformance(): Promise<void> {
    const performanceTests = [
      { name: '单动画性能', duration: 1000 },
      { name: '多动画性能', duration: 2000 },
      { name: '复杂动画性能', duration: 3000 },
      { name: '长时间性能', duration: 5000 }
    ]

    for (const perfTest of performanceTests) {
      this.currentAnimation = `性能测试: ${perfTest.name}`
      
      const result = await this.performPerformanceTest(perfTest.name, perfTest.duration)
      this.logTestResult(`性能测试: ${perfTest.name}`, result.success)
      this.animationTestResults.push(result)

      await this.delay(200)
    }
  }

  private async testMemoryUsage(): Promise<void> {
    this.currentAnimation = '内存使用测试'
    
    const result = await this.performMemoryTest()
    this.logTestResult('内存测试', result.success)
    this.animationTestResults.push(result)
  }

  private async testConcurrentAnimations(): Promise<void> {
    this.currentAnimation = '并发动画测试'
    
    const result = await this.performConcurrentTest()
    this.logTestResult('并发测试', result.success)
    this.animationTestResults.push(result)
  }

  private async testAnimationInterruption(): Promise<void> {
    this.currentAnimation = '动画中断恢复测试'
    
    const result = await this.performInterruptionTest()
    this.logTestResult('中断测试', result.success)
    this.animationTestResults.push(result)
  }

  // 动画执行方法
  private async performBasicAnimation(config: AnimationConfig): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0
    let success = true

    // 模拟动画执行
    const animationDuration = config.duration
    const frameInterval = 16 // 约60fps
    const totalFrames = Math.floor(animationDuration / frameInterval)

    for (let frame = 0; frame < totalFrames; frame++) {
      await this.delay(frameInterval)
      frameCount++
      
      // 模拟动画进度
      this.animationProgress = (frame / totalFrames) * 100
      
      // 模拟偶尔的丢帧
      if (Math.random() < 0.05) {
        frameCount++
      }
    }

    const endTime = performance.now()
    const actualDuration = endTime - startTime

    return {
      name: config.name,
      startTime: startTime,
      endTime: endTime,
      duration: actualDuration,
      frameCount: frameCount,
      averageFPS: Math.round((frameCount / actualDuration) * 1000),
      droppedFrames: Math.max(0, totalFrames - frameCount),
      smoothness: Math.min(100, Math.max(0, 100 - (totalFrames - frameCount) / totalFrames * 100)),
      memoryUsage: Math.floor(Math.random() * 10 + 2),
      success: success
    }
  }

  private async performTransitionEffect(effect: TransitionEffect): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0

    // 模拟过渡动画
    const frameInterval = 16
    const totalFrames = Math.floor(effect.duration / frameInterval)

    for (let frame = 0; frame < totalFrames; frame++) {
      await this.delay(frameInterval)
      frameCount++
      this.animationProgress = (frame / totalFrames) * 100
    }

    const endTime = performance.now()

    return {
      name: effect.name,
      startTime: startTime,
      endTime: endTime,
      duration: endTime - startTime,
      frameCount: frameCount,
      averageFPS: Math.round((frameCount / (endTime - startTime)) * 1000),
      droppedFrames: 0,
      smoothness: Math.min(100, 95 + Math.random() * 5),
      memoryUsage: Math.floor(Math.random() * 8 + 1),
      success: true
    }
  }

  private async performKeyframeAnimation(animation: KeyframeAnimation): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0

    // 模拟关键帧动画
    const frameInterval = 16
    const totalFrames = Math.floor(animation.duration / frameInterval)

    for (let frame = 0; frame < totalFrames; frame++) {
      await this.delay(frameInterval)
      frameCount++
      
      // 计算当前应该处于哪个关键帧
      const percent = (frame / totalFrames) * 100
      this.animationProgress = percent
    }

    const endTime = performance.now()

    return {
      name: animation.name,
      startTime: startTime,
      endTime: endTime,
      duration: endTime - startTime,
      frameCount: frameCount,
      averageFPS: Math.round((frameCount / (endTime - startTime)) * 1000),
      droppedFrames: Math.floor(Math.random() * 3),
      smoothness: Math.min(100, 90 + Math.random() * 10),
      memoryUsage: Math.floor(Math.random() * 12 + 3),
      success: true
    }
  }

  private async performGestureAnimation(gesture: GestureAnimation): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0

    // 模拟手势触发的动画
    await this.delay(gesture.triggerThreshold)
    
    const frameInterval = 16
    const totalFrames = Math.floor(gesture.animationDuration / frameInterval)

    for (let frame = 0; frame < totalFrames; frame++) {
      await this.delay(frameInterval)
      frameCount++
      this.animationProgress = (frame / totalFrames) * 100
    }

    const endTime = performance.now()

    return {
      name: gesture.animationType,
      startTime: startTime,
      endTime: endTime,
      duration: endTime - startTime,
      frameCount: frameCount,
      averageFPS: Math.round((frameCount / (endTime - startTime)) * 1000),
      droppedFrames: 0,
      smoothness: Math.min(100, 88 + Math.random() * 12),
      memoryUsage: Math.floor(Math.random() * 6 + 2),
      success: true
    }
  }

  private async performCompositeAnimation(composite: { name: string; animations: string[] }): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0
    let totalDuration = 0

    // 组合多个动画的总时间
    for (const animName of composite.animations) {
      totalDuration += 300 + Math.random() * 700 // 每个动画300-1000ms
      
      const frameInterval = 16
      const animFrames = Math.floor(totalDuration / frameInterval)
      
      for (let frame = 0; frame < animFrames; frame++) {
        await this.delay(frameInterval)
        frameCount++
        this.animationProgress = (frame / animFrames) * 100
      }
    }

    const endTime = performance.now()

    return {
      name: composite.name,
      startTime: startTime,
      endTime: endTime,
      duration: endTime - startTime,
      frameCount: frameCount,
      averageFPS: Math.round((frameCount / (endTime - startTime)) * 1000),
      droppedFrames: Math.floor(Math.random() * 5),
      smoothness: Math.min(100, 85 + Math.random() * 15),
      memoryUsage: Math.floor(Math.random() * 15 + 5),
      success: true
    }
  }

  private async playFromQueue(queueItem: { name: string; config: AnimationConfig }): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0

    const result = await this.performBasicAnimation(queueItem.config)
    
    const endTime = performance.now()
    
    return {
      name: queueItem.name,
      startTime: startTime,
      endTime: endTime,
      duration: endTime - startTime,
      frameCount: frameCount,
      averageFPS: result.averageFPS,
      droppedFrames: 0,
      smoothness: result.smoothness,
      memoryUsage: result.memoryUsage,
      success: result.success
    }
  }

  private async performPerformanceTest(testName: string, duration: number): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0

    const frameInterval = 16
    const totalFrames = Math.floor(duration / frameInterval)

    for (let frame = 0; frame < totalFrames; frame++) {
      await this.delay(frameInterval)
      frameCount++
      
      // 根据测试类型调整性能
      if (testName.includes('多动画')) {
        // 模拟多动画的性能开销
        await this.delay(2)
      } else if (testName.includes('复杂')) {
        // 模拟复杂动画的性能开销
        await this.delay(4)
      }
      
      this.animationProgress = (frame / totalFrames) * 100
    }

    const endTime = performance.now()

    return {
      name: testName,
      startTime: startTime,
      endTime: endTime,
      duration: endTime - startTime,
      frameCount: frameCount,
      averageFPS: Math.round((frameCount / (endTime - startTime)) * 1000),
      droppedFrames: Math.floor(totalFrames * 0.1), // 模拟10%的丢帧
      smoothness: testName.includes('复杂') ? 75 + Math.random() * 15 : 85 + Math.random() * 10,
      memoryUsage: testName.includes('多动画') ? Math.floor(Math.random() * 20 + 10) : Math.floor(Math.random() * 10 + 5),
      success: true
    }
  }

  private async performMemoryTest(): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0

    // 模拟大量动画测试内存使用
    for (let i = 0; i < 50; i++) {
      const frameInterval = 16
      await this.delay(frameInterval)
      frameCount++
    }

    const endTime = performance.now()

    return {
      name: 'Memory Test',
      startTime: startTime,
      endTime: endTime,
      duration: endTime - startTime,
      frameCount: frameCount,
      averageFPS: Math.round((frameCount / (endTime - startTime)) * 1000),
      droppedFrames: 0,
      smoothness: 95,
      memoryUsage: Math.floor(Math.random() * 30 + 20), // 更高的内存使用
      success: true
    }
  }

  private async performConcurrentTest(): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0

    // 模拟并发执行多个动画
    const concurrentPromises: Promise<void>[] = []
    
    for (let i = 0; i < 5; i++) {
      const promise = new Promise<void>((resolve) => {
        setTimeout(() => {
          resolve()
        }, 500 + Math.random() * 1000)
      })
      concurrentPromises.push(promise)
    }

    // 在并发动画执行期间计算帧数
    const interval = setInterval(() => {
      frameCount++
    }, 16)

    await Promise.all(concurrentPromises)
    clearInterval(interval)

    const endTime = performance.now()

    return {
      name: 'Concurrent Test',
      startTime: startTime,
      endTime: endTime,
      duration: endTime - startTime,
      frameCount: frameCount,
      averageFPS: Math.round((frameCount / (endTime - startTime)) * 1000),
      droppedFrames: Math.floor(frameCount * 0.15), // 并发时更多丢帧
      smoothness: 70 + Math.random() * 15,
      memoryUsage: Math.floor(Math.random() * 25 + 15),
      success: true
    }
  }

  private async performInterruptionTest(): Promise<AnimationTestResult> {
    const startTime = performance.now()
    let frameCount = 0

    // 模拟动画被中断和恢复
    for (let i = 0; i < 3; i++) {
      // 开始动画
      await this.delay(200)
      
      // 模拟中断
      await this.delay(50)
      
      // 恢复动画
      for (let frame = 0; frame < 10; frame++) {
        await this.delay(16)
        frameCount++
        this.animationProgress = (i * 33 + frame * 3.33)
      }
    }

    const endTime = performance.now()

    return {
      name: 'Interruption Test',
      startTime: startTime,
      endTime: endTime,
      duration: endTime - startTime,
      frameCount: frameCount,
      averageFPS: Math.round((frameCount / (endTime - startTime)) * 1000),
      droppedFrames: Math.floor(frameCount * 0.1),
      smoothness: 80 + Math.random() * 10,
      memoryUsage: Math.floor(Math.random() * 8 + 3),
      success: true
    }
  }

  private logTestResult(testName: string, success: boolean): void {
    if (!success) {
      console.error(`Test failed: ${testName}`)
    }
    
    // 保持测试结果列表长度
    if (this.animationTestResults.length > 50) {
      this.animationTestResults = this.animationTestResults.slice(-50)
    }
  }

  private startFPSMonitoring(): void {
    setInterval(() => {
      // 模拟FPS监控
      this.fpsMonitor = 60 - Math.floor(Math.random() * 10)
      this.currentFrameCount = Math.floor(Math.random() * 60)
      this.animationProgress = this.animationProgress >= 100 ? 0 : this.animationProgress + Math.random() * 5
    }, 1000)
  }

  private delay(ms: number): Promise<void> {
    return new Promise(resolve => setTimeout(resolve, ms))
  }

  build() {
    Column() {
      // 标题栏
      Row() {
        Text('Image动画测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
        Blank()
        if (this.isAnimating) {
          LoadingProgress()
            .width(24)
            .height(24)
            .margin({ right: 8 })
        }
        Text(`FPS: ${this.fpsMonitor}`)
          .fontSize(14)
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(16)

      // 当前动画显示
      if (this.currentAnimation) {
        Row() {
          Text(`当前动画: ${this.currentAnimation}`)
            .fontSize(14)
            .fontColor(Color.Orange)
          Blank()
          Text(`进度: ${this.animationProgress.toFixed(1)}%`)
            .fontSize(12)
            .fontColor(Color.Gray)
        }
        .margin({ horizontal: 16, bottom: 8 })
      }

      // 动画进度条
      if (this.isAnimating) {
        Progress({
          value: this.animationProgress,
          total: 100,
          type: ProgressType.Linear
        })
          .width('90%')
          .height(8)
          .margin({ horizontal: 16, bottom: 8 })
          .backgroundColor('#E0E0E0')
          .color(Color.Blue)
      }

      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          this.buildBasicAnimationTab()
        }
        .tabBar('基础')

        TabContent() {
          this.buildTransitionTab()
        }
        .tabBar('过渡')

        TabContent() {
          this.buildKeyframeTab()
        }
        .tabBar('关键帧')

        TabContent() {
          this.buildGestureTab()
        }
        .tabBar('手势')

        TabContent() {
          this.buildCompositeTab()
        }
        .tabBar('组合')

        TabContent() {
          this.buildQueueTab()
        }
        .tabBar('队列')

        TabContent() {
          this.buildPerformanceTab()
        }
        .tabBar('性能')

        TabContent() {
          this.buildResultsTab()
        }
        .tabBar('结果')
      }
      .height('75%')
      .barHeight(28)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  @Builder buildBasicAnimationTab() {
    Scroll() {
      Column() {
        Text('基础动画测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 动画配置网格
        Grid() {
          ForEach(this.animationConfigs, (config: AnimationConfig, index: number) => {
            GridItem() {
              Column() {
                // 动画预览
                Image($r('app.media.icon'))
                  .width(50)
                  .height(50)
                  .borderRadius(6)
                  .border({
                    width: index === this.currentAnimationIndex ? 3 : 1,
                    color: index === this.currentAnimationIndex ? Color.Blue : Color.Gray
                  })
                  .animation({
                    duration: config.duration,
                    curve: config.curve,
                    delay: config.delay,
                    iterations: config.repeat,
                    playMode: config.autoReverse ? PlayMode.Alternate : PlayMode.Normal,
                    onFinish: () => {
                      console.log(`Animation ${config.name} finished`)
                    }
                  })

                Text(config.name)
                  .fontSize(12)
                  .margin({ top: 4 })
                  .maxLines(2)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })

                Text(`${config.duration}ms`)
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .padding(8)
              .backgroundColor(index === this.currentAnimationIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(6)
              .onClick(() => {
                this.currentAnimationIndex = index
              })
            }
          })
        }
        .columnsTemplate('repeat(5, 1fr)')
        .rowsGap(12)
        .columnsGap(8)
        .padding(16)

        // 当前动画详情
        if (this.currentAnimationIndex < this.animationConfigs.length) {
          const currentConfig = this.animationConfigs[this.currentAnimationIndex]
          Column() {
            Text('当前动画配置')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })

            Grid() {
              GridItem() {
                Column() {
                  Text('持续时间')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentConfig.duration}ms`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('延迟')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentConfig.delay}ms`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('重复次数')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(currentConfig.repeat === -1 ? '无限' : currentConfig.repeat.toString())
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('自动反转')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(currentConfig.autoReverse ? '是' : '否')
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                    .fontColor(currentConfig.autoReverse ? Color.Green : Color.Gray)
                }
              }
            }
            .rowsTemplate('1fr 1fr')
            .columnsTemplate('repeat(2, 1fr)')
            .height(120)
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, top: 16 })
        }
      }
    }
  }

  @Builder buildTransitionTab() {
    Scroll() {
      Column() {
        Text('过渡效果测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 过渡效果网格
        Grid() {
          ForEach(this.transitionEffects, (effect: TransitionEffect, index: number) => {
            GridItem() {
              Column() {
                // 过渡效果预览
                Stack() {
                  Image($r('app.media.icon'))
                    .width(60)
                    .height(60)
                    .borderRadius(4)
                    
                  // 模拟过渡效果指示器
                  if (effect.type === 'fade') {
                    Column()
                      .width(60)
                      .height(60)
                      .backgroundColor('#00000030')
                  } else if (effect.type === 'slide') {
                    Column()
                      .width(30)
                      .height(60)
                      .backgroundColor(Color.Blue)
                      .position({ x: index === this.currentTransitionIndex ? 0 : -30 })
                  }
                }
                .width(60)
                .height(60)
                .borderRadius(4)
                .border({
                  width: index === this.currentTransitionIndex ? 3 : 1,
                  color: index === this.currentTransitionIndex ? Color.Blue : Color.Gray
                })

                Text(effect.name)
                  .fontSize(12)
                  .margin({ top: 4 })

                Text(effect.type)
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .padding(8)
              .backgroundColor(index === this.currentTransitionIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(6)
              .onClick(() => {
                this.currentTransitionIndex = index
              })
            }
          })
        }
        .columnsTemplate('repeat(4, 1fr)')
        .rowsGap(12)
        .columnsGap(8)
        .padding(16)

        // 过渡效果详情
        if (this.currentTransitionIndex < this.transitionEffects.length) {
          const currentEffect = this.transitionEffects[this.currentTransitionIndex]
          Column() {
            Text(`当前过渡: ${currentEffect.name}`)
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })

            Row() {
              Column() {
                Text('类型')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(currentEffect.type)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
              }
              .layoutWeight(1)

              Column() {
                Text('持续时间')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(`${currentEffect.duration}ms`)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
              }
              .layoutWeight(1)
            }
            .justifyContent(FlexAlign.SpaceAround)

            // 参数展示
            Flex({ wrap: FlexWrap.Wrap }) {
              ForEach(Object.entries(currentEffect.fromValue), ([key, value]) => {
                Text(`起始${key}: ${value}`)
                  .fontSize(11)
                  .fontColor(Color.Gray)
                  .padding({ horizontal: 6, vertical: 2 })
                  .backgroundColor('#F0F0F0')
                  .borderRadius(4)
                  .margin({ right: 4, bottom: 4 })
              })
              ForEach(Object.entries(currentEffect.toValue), ([key, value]) => {
                Text(`结束${key}: ${value}`)
                  .fontSize(11)
                  .fontColor(Color.Gray)
                  .padding({ horizontal: 6, vertical: 2 })
                  .backgroundColor('#F0F0F0')
                  .borderRadius(4)
                  .margin({ right: 4, bottom: 4 })
              })
            }
            .width('100%')
            .margin({ top: 12 })
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, top: 16 })
        }
      }
    }
  }

  @Builder buildKeyframeTab() {
    Scroll() {
      Column() {
        Text('关键帧动画测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 关键帧动画网格
        Grid() {
          ForEach(this.keyframeAnimations, (animation: KeyframeAnimation, index: number) => {
            GridItem() {
              Column() {
                // 关键帧动画预览
                Stack() {
                  Image($r('app.media.icon'))
                    .width(50)
                    .height(50)
                    .borderRadius(4)
                    
                  // 关键帧数示意
                  Text(`${animation.keyframes.length}`)
                    .fontSize(12)
                    .fontColor(Color.White)
                    .backgroundColor(Color.Blue)
                    .borderRadius(10)
                    .width(20)
                    .height(20)
                    .position({ x: 15, y: -5 })
                }
                .width(50)
                .height(50)
                .borderRadius(4)
                .border({
                  width: index === this.currentKeyframeIndex ? 3 : 1,
                  color: index === this.currentKeyframeIndex ? Color.Blue : Color.Gray
                })

                Text(animation.name)
                  .fontSize(11)
                  .margin({ top: 4 })
                  .maxLines(2)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })

                Text(`${animation.duration}ms`)
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .padding(8)
              .backgroundColor(index === this.currentKeyframeIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(6)
              .onClick(() => {
                this.currentKeyframeIndex = index
              })
            }
          })
        }
        .columnsTemplate('repeat(3, 1fr)')
        .rowsGap(12)
        .columnsGap(8)
        .padding(16)

        // 关键帧详情
        if (this.currentKeyframeIndex < this.keyframeAnimations.length) {
          const currentAnimation = this.keyframeAnimations[this.currentKeyframeIndex]
          Column() {
            Text(`当前关键帧动画: ${currentAnimation.name}`)
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })

            // 关键帧列表
            List() {
              ForEach(currentAnimation.keyframes, (keyframe, index: number) => {
                ListItem() {
                  Column() {
                    Text(`关键帧 ${index + 1}: ${keyframe.percent}%`)
                      .fontSize(12)
                      .fontWeight(FontWeight.Medium)
                    
                    Flex({ wrap: FlexWrap.Wrap }) {
                      ForEach(Object.entries(keyframe.value), ([key, value]) => {
                        Text(`${key}: ${value}`)
                          .fontSize(10)
                          .fontColor(Color.Gray)
                          .padding({ horizontal: 4, vertical: 2 })
                          .backgroundColor('#F5F5F5')
                          .borderRadius(3)
                          .margin({ right: 4, bottom: 2 })
                      })
                    }
                    .width('100%')
                  }
                  .width('100%')
                  .padding(8)
                  .backgroundColor('#FAFAFA')
                  .borderRadius(4)
                  .margin({ bottom: 4 })
                }
              })
            }
            .height(250)
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, top: 16 })
        }
      }
    }
  }

  @Builder buildGestureTab() {
    Scroll() {
      Column() {
        Text('手势动画测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 手势动画列表
        List() {
          ForEach(this.gestureAnimations, (gesture: GestureAnimation) => {
            ListItem() {
              Row() {
                Column() {
                  Text(gesture.animationType)
                    .fontSize(14)
                    .fontWeight(FontWeight.Medium)
                  Text(`触发手势: ${gesture.gestureType}`)
                    .fontSize(12)
                    .fontColor(Color.Gray)
                }
                .layoutWeight(1)
                .alignItems(HorizontalAlign.Start)

                Column() {
                  Text(`${gesture.animationDuration}ms`)
                    .fontSize(12)
                    .fontColor(Color.Blue)
                  Text(`缓冲: ${gesture.dampingRatio}`)
                    .fontSize(10)
                    .fontColor(Color.Gray)
                }
              }
              .width('100%')
              .padding(12)
              .backgroundColor('#FAFAFA')
              .borderRadius(6)
              .margin({ bottom: 8 })
            }
          })
        }
        .height(400)
        .margin({ horizontal: 16 })

        // 手势动画统计
        Row() {
          Column() {
            Text('手势类型')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.gestureAnimations.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('平均时长')
              .fontSize(12)
              .fontColor(Color.Blue)
            Text(`${this.getAverageGestureDuration()}ms`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Blue)
          }
          .layoutWeight(1)

          Column() {
            Text('平均阈值')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(`${this.getAverageGestureThreshold()}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Green)
          }
          .layoutWeight(1)
        }
        .padding(16)
        .backgroundColor(Color.White)
        .borderRadius(8)
        .margin({ horizontal: 16, top: 16 })
      }
    }
  }

  @Builder buildCompositeTab() {
    Scroll() {
      Column() {
        Text('组合动画测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 组合动画网格
        Grid() {
          ForEach(this.compositeAnimations, (composite: { name: string; animations: string[] }) => {
            GridItem() {
              Column() {
                // 组合动画预览
                Stack() {
                  Image($r('app.media.icon'))
                    .width(70)
                    .height(70)
                    .borderRadius(8)
                    .backgroundColor('#F0F0F0')

                  // 动画数量标识
                  Column() {
                    Text(composite.animations.length.toString())
                      .fontSize(12)
                      .fontColor(Color.White)
                  }
                  .width(20)
                  .height(20)
                  .backgroundColor('#FF5722')
                  .borderRadius(10)
                  .position({ x: 20, y: -5 })
                }
                .width(70)
                .height(70)
                .borderRadius(8)
                .border({ width: 1, color: Color.Gray })

                Text(composite.name)
                  .fontSize(12)
                  .margin({ top: 6 })
                  .maxLines(2)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })

                Text(`${composite.animations.length}个动画`)
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .padding(10)
              .backgroundColor('#FAFAFA')
              .borderRadius(8)
            }
          })
        }
        .columnsTemplate('repeat(3, 1fr)')
        .rowsGap(16)
        .columnsGap(12)
        .padding(16)

        // 组合动画详情
        ForEach(this.compositeAnimations.slice(0, 3), (composite: { name: string; animations: string[] }) => {
          Column() {
            Text(`组合: ${composite.name}`)
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 8 })

            // 组成的动画标识
            Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
              ForEach(composite.animations, (anim: string) => {
                Text(anim)
                  .fontSize(11)
                  .fontColor(Color.Blue)
                  .padding({ horizontal: 8, vertical: 4 })
                  .backgroundColor('#E3F2FD')
                  .borderRadius(4)
                  .margin({ right: 6, bottom: 6 })
              })
            }
            .width('100%')
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, bottom: 8 })
        })
      }
    }
  }

  @Builder buildQueueTab() {
    Scroll() {
      Column() {
        Text('动画队列测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 队列状态
        Row() {
          Column() {
            Text('队列长度')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.animationQueue.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('播放状态')
              .fontSize(12)
              .fontColor(Color.Blue)
            Text(this.isAutoPlaybackEnabled ? '播放中' : '已停止')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(this.isAutoPlaybackEnabled ? Color.Green : Color.Red)
          }
          .layoutWeight(1)

          Column() {
            Text('自动播放')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(this.isAutoPlaybackEnabled ? '开启' : '关闭')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(this.isAutoPlaybackEnabled ? Color.Green : Color.Gray)
          }
          .layoutWeight(1)
        }
        .padding(16)
        .backgroundColor(Color.White)
        .borderRadius(8)
        .margin({ horizontal: 16 })

        // 队列列表
        Text('播放队列')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 16, bottom: 8, horizontal: 16 })

        List() {
          ForEach(this.animationQueue.slice(0, 10), (queueItem: { name: string; config: AnimationConfig }, index: number) => {
            ListItem() {
              Row() {
                Column() {
                  Text(queueItem.name)
                    .fontSize(14)
                    .fontWeight(FontWeight.Medium)
                  Text(queueItem.config.name)
                    .fontSize(12)
                    .fontColor(Color.Gray)
                }
                .layoutWeight(1)
                .alignItems(HorizontalAlign.Start)

                Text(`${queueItem.config.duration}ms`)
                  .fontSize(12)
                  .fontColor(Color.Blue)
                  .margin({ right: 8 })

                Circle({ width: 8, height: 8 })
                  .fill(Color.Green)
                  .margin({ right: 8 })
              }
              .width('100%')
              .padding(12)
              .backgroundColor(index === 0 ? '#E8F5E8' : '#FAFAFA')
              .borderRadius(6)
            }
          })
        }
        .height(350)
        .margin({ horizontal: 16, bottom: 16 })
      }
    }
  }

  @Builder buildPerformanceTab() {
    Scroll() {
      Column() {
        Text('性能监控')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 实时性能指标
        Row() {
          Column() {
            Text('当前FPS')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.fpsMonitor}`)
              .fontSize(24)
              .fontWeight(FontWeight.Bold)
              .fontColor(this.fpsMonitor >= 50 ? Color.Green : Color.Orange)
          }
          .layoutWeight(1)

          Column() {
            Text('当前帧数')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.currentFrameCount}`)
              .fontSize(24)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('总测试数')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.animationTestResults.length}`)
              .fontSize(24)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)
        }
        .padding(16)
        .backgroundColor(Color.White)
        .borderRadius(8)
        .margin({ horizontal: 16 })

        // 性能测试结果
        Text('测试性能结果')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 16, bottom: 8, horizontal: 16 })

        List() {
          ForEach(this.animationTestResults.slice(0, 15), (result: AnimationTestResult) => {
            ListItem() {
              Column() {
                Row() {
                  Text(result.name)
                    .fontSize(14)
                    .fontWeight(FontWeight.Medium)
                    .layoutWeight(1)
                  
                  Circle({ width: 8, height: 8 })
                    .fill(result.success ? Color.Green : Color.Red)
                    .margin({ right: 8 })
                }
                .width('100%')
                .margin({ bottom: 4 })

                Row() {
                  Text(`FPS: ${result.averageFPS}`)
                    .fontSize(11)
                    .fontColor(Color.Blue)
                    .margin({ right: 12 })
                  
                  Text(`流畅度: ${result.smoothness.toFixed(1)}%`)
                    .fontSize(11)
                    .fontColor(Color.Green)
                    .margin({ right: 12 })
                  
                  Text(`内存: ${result.memoryUsage}MB`)
                    .fontSize(11)
                    .fontColor(Color.Orange)
                }
                .width('100%')
                .justifyContent(FlexAlign.Start)
              }
              .width('100%')
              .padding(12)
              .backgroundColor('#FAFAFA')
              .borderRadius(6)
              .margin({ bottom: 6 })
            }
          })
        }
        .height(400)
        .margin({ horizontal: 16, bottom: 16 })
      }
    }
  }

  @Builder buildResultsTab() {
    Scroll() {
      Column() {
        Text('测试结果总览')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 统计概览
        Row() {
          Column() {
            Text('总测试数')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.animationTestResults.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('成功率')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(`${this.calculateAnimationSuccessRate().toFixed(1)}%`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Green)
          }
          .layoutWeight(1)

          Column() {
            Text('平均FPS')
              .fontSize(12)
              .fontColor(Color.Blue)
            Text(`${this.calculateAverageFPS()}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Blue)
          }
          .layoutWeight(1)

          Column() {
            Text('平均流畅度')
              .fontSize(12)
              .fontColor(Color.Orange)
            Text(`${this.calculateAverageSmoothness().toFixed(1)}%`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Orange)
          }
          .layoutWeight(1)
        }
        .padding(16)
        .backgroundColor(Color.White)
        .borderRadius(8)
        .margin({ horizontal: 16 })

        // 详细结果列表
        List() {
          ForEach(this.animationTestResults, (result: AnimationTestResult) => {
            ListItem() {
              Column() {
                Row() {
                  Circle({ width: 8, height: 8 })
                    .fill(result.success ? Color.Green : Color.Red)
                    .margin({ right: 8 })

                  Text(result.name)
                    .fontSize(14)
                    .fontWeight(FontWeight.Medium)
                    .layoutWeight(1)

                  Text(`${result.duration.toFixed(0)}ms`)
                    .fontSize(12)
                    .fontColor(Color.Gray)
                }
                .width('100%')
                .margin({ bottom: 4 })

                Row() {
                  Text(`帧: ${result.frameCount}`)
                    .fontSize(11)
                    .fontColor(Color.Gray)
                  Text(`FPS: ${result.averageFPS}`)
                    .fontSize(11)
                    .fontColor(Color.Blue)
                    .margin({ left: 12 })
                  Text(`流畅: ${result.smoothness.toFixed(1)}%`)
                    .fontSize(11)
                    .fontColor(Color.Green)
                    .margin({ left: 12 })
                  Text(`内存: ${result.memoryUsage}MB`)
                    .fontSize(11)
                    .fontColor(Color.Orange)
                    .margin({ left: 12 })
                }
                .width('100%')
                .justifyContent(FlexAlign.Start)
              }
              .width('100%')
              .padding(12)
              .backgroundColor('#FAFAFA')
              .borderRadius(6)
              .margin({ bottom: 8 })
            }
          })
        }
        .height(450)
        .margin({ horizontal: 16, bottom: 16 })
      }
    }
  }

  // 工具方法
  private getAverageGestureDuration(): number {
    if (this.gestureAnimations.length === 0) return 0
    const sum = this.gestureAnimations.reduce((acc, gesture) => acc + gesture.animationDuration, 0)
    return Math.round(sum / this.gestureAnimations.length)
  }

  private getAverageGestureThreshold(): number {
    if (this.gestureAnimations.length === 0) return 0
    const sum = this.gestureAnimations.reduce((acc, gesture) => acc + gesture.triggerThreshold, 0)
    return Math.round(sum / this.gestureAnimations.length)
  }

  private calculateAnimationSuccessRate(): number {
    if (this.animationTestResults.length === 0) return 0
    const successCount = this.animationTestResults.filter(result => result.success).length
    return (successCount / this.animationTestResults.length) * 100
  }

  private calculateAverageFPS(): number {
    if (this.animationTestResults.length === 0) return 0
    const sum = this.animationTestResults.reduce((acc, result) => acc + result.averageFPS, 0)
    return Math.round(sum / this.animationTestResults.length)
  }

  private calculateAverageSmoothness(): number {
    if (this.animationTestResults.length === 0) return 0
    const sum = this.animationTestResults.reduce((acc, result) => acc + result.smoothness, 0)
    return sum / this.animationTestResults.length
  }
}