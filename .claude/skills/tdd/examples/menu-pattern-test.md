# Menu Pattern TDD 测试示例

本文档展示如何为 Menu Pattern 方法编写符合 TDD 规范的测试用例。

## 示例场景

测试 MenuPattern 的 `OnModifyDone()` 方法在不同场景下的行为。

## 测试用例 1：基本调用测试

```cpp
/**
 * @tc.name: MenuPatternTest_OnModifyDone_BasicCall
 * @tc.desc: Test OnModifyDone basic execution
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPattern_OnModifyDone_BasicCall, TestSize.Level1)
{
    /**
     * @tc.steps: step1. 创建 Menu 节点和 Pattern
     */
    auto menuNode = CreateMenuNode();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    /**
     * @tc.steps: step2. 调用 OnModifyDone 方法
     * @tc.expected: 方法正常执行，无崩溃
     */
    menuPattern->OnModifyDone();

    /**
     * @tc.steps: step3. 验证执行结果
     * @tc.expected: 菜单状态正确更新
     */
    EXPECT_TRUE(MenuPatternTestUtils::CheckMenuState(menuNode));
}
```

## 测试用例 2：分支覆盖 - BorderRadius 有无 PERCENT 单位

### 分支 1：BorderRadius 无 PERCENT 单位

```cpp
/**
 * @tc.name: MenuPatternTest_OnModifyDone_UpdateBorderRadius
 * @tc.desc: Test OnModifyDone updates border radius when not PERCENT unit
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPattern_OnModifyDone_UpdateBorderRadius, TestSize.Level1)
{
    /**
     * @tc.steps: step1. 环境准备
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;

    /**
     * @tc.steps: step2. 创建 Menu 节点
     */
    auto menuNode = MenuView::Create();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. 设置测试数据触发目标分支
     * @tc.expected: borderRadius 没有 PERCENT 单位
     */
    BorderImageProperty borderRadiusVP;
    borderRadiusVP.SetRadius(Dimension(10.0_vp));  // 无 PERCENT 单位
    menuLayoutProperty->UpdateBorderImageProperty(borderRadiusVP);

    /**
     * @tc.steps: step4. 重置干扰状态（关键！）
     */
    renderContext->ResetOuterBorder();

    /**
     * @tc.steps: step5. 直接调用目标方法
     */
    menuPattern->OnModifyDone();

    /**
     * @tc.steps: step6. 验证结果符合分支预期
     * @tc.expected: outerRadius 有值
     */
    auto outerRadius = renderContext->GetOuterBorderRadius();
    EXPECT_TRUE(outerRadius.has_value());
}
```

### 分支 2：BorderRadius 有 PERCENT 单位

```cpp
/**
 * @tc.name: MenuPatternTest_OnModifyDone_PercentBorderRadius
 * @tc.desc: Test OnModifyDone skips update when borderRadius has PERCENT unit
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTestNg, MenuPattern_OnModifyDone_PercentBorderRadius, TestSize.Level1)
{
    /**
     * @tc.steps: step1. 环境准备
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;

    /**
     * @tc.steps: step2. 创建 Menu 节点
     */
    auto menuNode = MenuView::Create();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. 设置测试数据触发目标分支
     * @tc.expected: borderRadius 有 PERCENT 单位
     */
    BorderImageProperty borderRadiusPercent;
    borderRadiusPercent.SetRadius(Dimension(50.0f, DimensionUnit::PERCENT));  // PERCENT 单位
    menuLayoutProperty->UpdateBorderImageProperty(borderRadiusPercent);

    /**
     * @tc.steps: step4. 重置干扰状态（关键！）
     */
    renderContext->ResetOuterBorder();

    /**
     * @tc.steps: step5. 直接调用目标方法
     */
    menuPattern->OnModifyDone();

    /**
     * @tc.steps: step6. 验证结果符合分支预期
     * @tc.expected: outerRadius 无值（跳过更新）
     */
    auto outerRadius = renderContext->GetOuterBorderRadius();
    EXPECT_FALSE(outerRadius.has_value());
}
```

## 关键要点说明

### 1. 使用命名常量，避免魔鬼数字

```cpp
// ❌ 错误：使用硬编码数字
SystemProperties::InitDeviceInfo(720, 1280, 0, 3.0, false);
auto size = GetSubWindowSize(100000, 0);

// ✅ 正确：使用命名常量
namespace {
    const int32_t TEST_DEVICE_WIDTH = 720;
    const int32_t TEST_DEVICE_HEIGHT = 1280;
    const int32_t TEST_DEVICE_ORIENTATION = 0;
    const double TEST_DEVICE_RESOLUTION = 3.0;
    const bool TEST_DEVICE_IS_ROUND = false;
    const int32_t TEST_PARENT_CONTAINER_ID = 100000;
    const uint32_t DEFAULT_DISPLAY_ID = 0;
}
SystemProperties::InitDeviceInfo(
    TEST_DEVICE_WIDTH, TEST_DEVICE_HEIGHT, TEST_DEVICE_ORIENTATION,
    TEST_DEVICE_RESOLUTION, TEST_DEVICE_IS_ROUND);
auto size = GetSubWindowSize(TEST_PARENT_CONTAINER_ID, DEFAULT_DISPLAY_ID);
```

### 2. 注释描述逻辑行为，不使用行号

```cpp
// ❌ 错误：引用物理行号
/**
 * @tc.steps: step2. OnModifyDone should skip UpdateBorderRadius at line 299
 */

// ✅ 正确：描述逻辑条件
/**
 * @tc.steps: step2. OnModifyDone should skip UpdateBorderRadius when borderRadius has PERCENT unit
 */
```

### 3. 状态重置

```cpp
// 在调用目标方法前，必须重置可能干扰的状态
renderContext->ResetOuterBorder();  // 重置整个属性组

// 然后调用目标方法
menuPattern->OnModifyDone();
```

### 4. 直接调用方法

```cpp
// ❌ 错误：通过间接触发
menuPattern->FireBuilder();  // 不会触发 OnModifyDone

// ✅ 正确：直接调用
menuPattern->OnModifyDone();  // 直接调用目标方法
```

## 实际测试文件位置

完整工作示例请参考：
- `test/unittest/core/pattern/menu/menu_pattern_test_ng.cpp:1482-1574`

## 自检验证清单

编写完测试后，请验证：

- [ ] 所有调用的方法都存在（通过 Grep/Read 验证）
- [ ] 调用目标方法前已重置状态
- [ ] 测试数据触发正确的分支
- [ ] 断言符合分支行为
- [ ] 所有 API 签名与源码定义匹配
- [ ] 测试遵循现有测试文件结构和命名约定
- [ ] 注释描述逻辑行为，不使用行号
- [ ] 每个测试用例都有实际测试逻辑（不是仅文档）
- [ ] 没有魔鬼数字，所有数值都使用命名常量
