# 测试用例模板

本文档提供标准的 TDD 测试用例模板，确保所有测试用例遵循统一的格式和最佳实践。

## 完整测试用例模板

```cpp
/**
 * @tc.name: PatternClass_TestMethod_BranchName
 * @tc.desc: Test Description covering specific behavior (e.g., "when X happens, Y should occur")
 * @tc.type: FUNC
 */
HWTEST_F(ComponentPatternTestNg, ComponentPattern_TestBranchName, TestSize.Level1)
{
    // ========================================
    // 1. Environment Setup
    // ========================================
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;

    // ========================================
    // 2. Create Nodes
    // ========================================
    // 使用现有辅助方法创建节点
    auto wrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(wrapperNode, nullptr);

    auto targetNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(targetNode, nullptr);

    auto pattern = targetNode->GetPattern<TargetPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = targetNode->GetLayoutProperty<TargetLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto renderContext = targetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    // ========================================
    // 3. Set Test Data to Trigger Branch
    // ========================================
    TestDataType testData;
    testData.SetValue(...);  // 配置以触发特定分支
    layoutProperty->UpdateProperty(testData);

    // ========================================
    // 4. Reset Interfering State (CRITICAL!)
    // ========================================
    renderContext->ResetTargetProperty();

    // ========================================
    // 5. Call Target Method Directly
    // ========================================
    pattern->TargetMethod();

    // ========================================
    // 6. Verify Results Match Branch Expectation
    // ========================================
    auto result = renderContext->GetTargetProperty();
    EXPECT_TRUE(result.has_value());  // 或 false，基于分支预期
}
```

## 模板章节说明

### 1. Environment Setup（环境设置）

```cpp
// 初始化必要的全局状态
MockPipelineContext::GetCurrent()->SetMinPlatformVersion(...);
ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
```

**要点**：
- 设置平台版本
- 配置屏幕密度
- 初始化其他必要全局状态

### 2. Create Nodes（创建节点）

```cpp
// 使用辅助方法创建节点树
auto wrapperNode = GetPreviewMenuWrapper();
auto targetNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));

// 获取必要对象
auto pattern = targetNode->GetPattern<TargetPattern>();
auto layoutProperty = targetNode->GetLayoutProperty<TargetLayoutProperty>();
auto renderContext = targetNode->GetRenderContext();

// 验证所有对象创建成功
ASSERT_NE(pattern, nullptr);
ASSERT_NE(layoutProperty, nullptr);
ASSERT_NE(renderContext, nullptr);
```

**要点**：
- 使用现有的辅助方法（如 `GetPreviewMenuWrapper()`）
- 验证所有对象指针非空
- 按依赖顺序获取对象

### 3. Set Test Data（设置测试数据）

```cpp
// 创建测试数据
TestDataType testData;
testData.SetValue(...);

// 更新属性以触发特定分支
layoutProperty->UpdateProperty(testData);
```

**要点**：
- 数据配置必须能触发目标分支
- 使用正确的属性更新方法
- 确保 HasPercentUnit 等条件返回预期值

### 4. Reset State（重置状态）

```cpp
// 重置可能干扰的属性
renderContext->ResetTargetProperty();
```

**要点**：
- **关键步骤**，必须执行
- 重置整个属性组，而非单个属性
- 在调用目标方法前完成

### 5. Call Method（调用方法）

```cpp
// 直接调用目标方法
pattern->TargetMethod();
```

**要点**：
- 直接调用，不通过间接触发
- 不使用 FireBuilder 等间接方法
- 确保方法被正确执行

### 6. Verify Results（验证结果）

```cpp
// 获取结果并验证
auto result = renderContext->GetTargetProperty();
EXPECT_TRUE(result.has_value());  // 或 EXPECT_FALSE
```

**要点**：
- 断言必须符合分支预期
- 使用正确的断言类型（EXPECT_TRUE/EXPECT_FALSE/EXPECT_EQ 等）
- 验证关键状态变化

## 常用断言

```cpp
// 指针非空
ASSERT_NE(ptr, nullptr);
EXPECT_NE(ptr, nullptr);

// 布尔值
EXPECT_TRUE(condition);
EXPECT_FALSE(condition);

// 数值比较
EXPECT_EQ(actual, expected);
EXPECT_GT(actual, expected);
EXPECT_GE(actual, expected);
EXPECT_LT(actual, expected);
EXPECT_LE(actual, expected);

// 浮点数比较
EXPECT_FLOAT_EQ(actual, expected);

// 容器内容
EXPECT_THAT(container, SizeIs(expectedSize));
```

## 测试数据命名规范

```cpp
// 测试数据命名
TestData testData;
MenuProperty menuProperty;
BorderImageProperty borderRadius;

// 测试节点命名
auto menuNode = ...;
auto menuPattern = ...;
auto targetNode = ...;
```

**规则**：
- 使用描述性名称
- 优先使用小写驼峰命名
- 名称应反映数据类型或用途

## 测试用例命名规范

```cpp
// 格式：PatternClass_TestMethod_BranchName
HWTEST_F(MenuPatternTestNg, MenuPattern_OnModifyDone_UpdateBorderRadius, TestSize.Level1)
HWTEST_F(MenuPatternTestNg, MenuPattern_OnModifyDone_PercentBorderRadius, TestSize.Level1)

// 命名要素：
// - MenuPatternTestNg: 测试类名
// - MenuPattern: 被测试的 Pattern 类名
// - OnModifyDone: 被测试的方法名
// - UpdateBorderRadius: 分支场景描述
```

## TestSize 级别

```cpp
TestSize.Level0    // 烟 smoke 测试，极快
TestSize.Level1    // 基本功能测试，正常使用
TestSize.Level2    // 完整功能测试
TestSize.Level3    // 性能测试
```

**使用建议**：
- 大部分测试使用 `TestSize.Level1`
- 复杂场景使用 `TestSize.Level2`
- 性能测试使用 `TestSize.Level3`

## 参考示例

- Menu Pattern 测试：`test/unittest/core/pattern/menu/menu_pattern_test_ng.cpp:1482-1574`
- Checkbox Pattern 测试：`test/unittest/core/pattern/checkbox/`
- 更多示例请参考各组件的测试文件
