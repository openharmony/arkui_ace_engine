# 常见陷阱及解决方案

本文档列出编写 TDD 测试用例时的常见陷阱及其解决方案。

## 陷阱一览表

| 陷阱 | 症状 | 解决方案 |
|:---|:---|:---|
| **间接方法调用** | 测试不触发目标代码路径 | 直接调用目标方法 |
| **无状态重置** | 测试失败，返回意外值 | 在调用方法前重置所有干扰属性 |
| **API 名称猜测** | 编译错误或方法未找到 | 使用 Grep 验证方法名 |
| **测试数据污染** | 测试相互干扰 | 每个测试独立，重置所有状态 |
| **分支覆盖不足** | 代码覆盖率有缺口 | 为 if/else 分支编写成对测试 |
| **注释使用行号** | 注释随代码变更而过时 | 描述逻辑条件而非物理行位置 |
| **文档化测试** | 测试只包含注释和 `EXPECT_TRUE(true)` | 每个测试必须有真实断言和验证逻辑 |
| **魔鬼数字** | 硬编码数字难以理解 | 使用有语义的命名常量 |

## 详细说明

### 1. 间接方法调用

#### ❌ 错误示例

```cpp
HWTEST_F(MenuPatternTestNg, MenuPattern_TestOnModifyDone, TestSize.Level1)
{
    auto menuNode = GetPreviewMenuWrapper();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();

    // 错误：通过 FireBuilder 间接触发
    menuPattern->FireBuilder();  // 不会触发 OnModifyDone

    EXPECT_TRUE(SomeCondition);
}
```

#### ✅ 正确示例

```cpp
HWTEST_F(MenuPatternTestNg, MenuPattern_TestOnModifyDone, TestSize.Level1)
{
    auto menuNode = GetPreviewMenuWrapper();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();

    // 正确：直接调用目标方法
    menuPattern->OnModifyDone();

    EXPECT_TRUE(SomeCondition);
}
```

---

### 2. 无状态重置

#### ❌ 错误示例

```cpp
HWTEST_F(MenuPatternTestNg, MenuPattern_TestUpdateBorder, TestSize.Level1)
{
    auto menuNode = GetPreviewMenuWrapper();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    auto renderContext = menuNode->GetRenderContext();

    // 设置新的 border
    BorderImageProperty newBorder;
    newBorder.SetRadius(Dimension(10.0_vp));
    menuLayoutProperty->UpdateBorderImageProperty(newBorder);

    // 错误：未重置状态直接调用
    menuPattern->OnModifyDone();

    // 问题：如果之前已有 border 值，测试可能失败
}
```

#### ✅ 正确示例

```cpp
HWTEST_F(MenuPatternTestNg, MenuPattern_TestUpdateBorder, TestSize.Level1)
{
    auto menuNode = GetPreviewMenuWrapper();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    auto renderContext = menuNode->GetRenderContext();

    // 设置新的 border
    BorderImageProperty newBorder;
    newBorder.SetRadius(Dimension(10.0_vp));
    menuLayoutProperty->UpdateBorderImageProperty(newBorder);

    // 正确：重置整个属性组
    renderContext->ResetOuterBorder();

    // 然后调用目标方法
    menuPattern->OnModifyDone();

    EXPECT_TRUE(CheckBorderUpdated());
}
```

---

### 3. API 名称猜测

#### ❌ 错误示例

```cpp
// 猜测方法名
renderContext->ResetOuterBorderRadius();  // 错误！此方法不存在
```

#### ✅ 正确示例

```cpp
// 1. 使用 Grep 搜索方法定义
// grep -rn "Reset.*Border" frameworks/core/components_ng/render/render_context.h

// 2. 验证宏生成的方法
// grep -A 5 "ACE_DEFINE_PROPERTY_GROUP" frameworks/core/components_ng/property/property.h
// 发现：ACE_DEFINE_PROPERTY_GROUP(OuterBorder, OuterBorderProperty)
// 生成：GetOuterBorder(), ResetOuterBorder()

// 3. 使用正确的方法名
renderContext->ResetOuterBorder();  // 正确
```

---

### 4. 测试数据污染

#### ❌ 错误示例

```cpp
class MenuPatternTestNg : public testing::Test {
public:
    void SetUp() override {
        // 错误：多个测试共享状态，相互干扰
        menuNode = GetPreviewMenuWrapper();
    }

    void TearDown() override {}

protected:
    RefPtr<FrameNode> menuNode;
};

HWTEST_F(MenuPatternTestNg, Test1, TestSize.Level1) {
    menuNode->SetSomeProperty(true);  // 修改了共享状态
}

HWTEST_F(MenuPatternTestNg, Test2, TestSize.Level1) {
    // 问题：menuNode 已被 Test1 修改
    // 可能导致 Test2 失败
}
```

#### ✅ 正确示例

```cpp
class MenuPatternTestNg : public testing::Test {
public:
    void SetUp() override {}  // 不共享状态

    void TearDown() override {}
};

HWTEST_F(MenuPatternTestNg, Test1, TestSize.Level1) {
    // 每个测试创建自己的节点
    auto menuNode = GetPreviewMenuWrapper();
    menuNode->SetSomeProperty(true);
}

HWTEST_F(MenuPatternTestNg, Test2, TestSize.Level1) {
    // 独立创建新节点，不受 Test1 影响
    auto menuNode = GetPreviewMenuWrapper();
    // 测试逻辑...
}
```

---

### 5. 分支覆盖不足

#### ❌ 错误示例

```cpp
// 只测试了一个分支
HWTEST_F(MenuPatternTestNg, TestBorderUpdate, TestSize.Level1)
{
    borderRadius.SetRadius(Dimension(10.0_vp));  // 无 PERCENT
    menuPattern->OnModifyDone();
    EXPECT_TRUE(outerRadius.has_value());
}
// 缺少对 PERCENT 分支的测试
```

#### ✅ 正确示例

```cpp
// 测试分支 1：无 PERCENT 单位
HWTEST_F(MenuPatternTestNg, TestBorderUpdate_NoPercent, TestSize.Level1)
{
    borderRadius.SetRadius(Dimension(10.0_vp));
    renderContext->ResetOuterBorder();
    menuPattern->OnModifyDone();
    EXPECT_TRUE(outerRadius.has_value());
}

// 测试分支 2：有 PERCENT 单位
HWTEST_F(MenuPatternTestNg, TestBorderUpdate_WithPercent, TestSize.Level1)
{
    borderRadius.SetRadius(Dimension(50.0f, DimensionUnit::PERCENT));
    renderContext->ResetOuterBorder();
    menuPattern->OnModifyDone();
    EXPECT_FALSE(outerRadius.has_value());
}
```

---

### 6. 注释使用行号

#### ❌ 错误示例

```cpp
/**
 * @tc.steps: step1. Test OnModifyDone behavior at line 299
 */
```

#### ✅ 正确示例

```cpp
/**
 * @tc.steps: step1. Test OnModifyDone skips border update when borderRadius has PERCENT unit
 */
```

**原因**：代码会变更，行号会改变，注释会过时。

---

### 7. 文档化测试

#### ❌ 错误示例

```cpp
HWTEST_F(ComponentPatternTestNg, ComponentPattern_BranchDocumentation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Document branches
     * Branch 1: condition is true
     * Branch 2: condition is false
     */
    EXPECT_TRUE(true);  // 没有实际测试！
}
```

#### ✅ 正确示例

```cpp
// 为分支 1 编写实际测试
HWTEST_F(ComponentPatternTestNg, ComponentPattern_BranchTrue, TestSize.Level1)
{
    testData.SetValue(true);  // 触发分支 1
    pattern->TargetMethod();
    EXPECT_TRUE(result.has_value());
}

// 为分支 2 编写实际测试
HWTEST_F(ComponentPatternTestNg, ComponentPattern_BranchFalse, TestSize.Level1)
{
    testData.SetValue(false);  // 触发分支 2
    pattern->TargetMethod();
    EXPECT_FALSE(result.has_value());
}
```

---

### 8. 魔鬼数字

#### ❌ 错误示例

```cpp
HWTEST_F(ComponentPatternTestNg, ComponentPattern_TestBranch, TestSize.Level1)
{
    SystemProperties::InitDeviceInfo(720, 1280, 0, 3.0, false);
    auto size = GetSubWindowSize(100000, 0);
    EXPECT_GT(size.Width(), 0);
}
```

#### ✅ 正确示例

```cpp
namespace {
    const int32_t TEST_DEVICE_WIDTH = 720;
    const int32_t TEST_DEVICE_HEIGHT = 1280;
    const int32_t TEST_DEVICE_ORIENTATION = 0;
    const double TEST_DEVICE_RESOLUTION = 3.0;
    const bool TEST_DEVICE_IS_ROUND = false;
    const int32_t TEST_PARENT_CONTAINER_ID = 100000;
    const uint32_t DEFAULT_DISPLAY_ID = 0;
}

HWTEST_F(ComponentPatternTestNg, ComponentPattern_TestBranch, TestSize.Level1)
{
    SystemProperties::InitDeviceInfo(
        TEST_DEVICE_WIDTH, TEST_DEVICE_HEIGHT, TEST_DEVICE_ORIENTATION,
        TEST_DEVICE_RESOLUTION, TEST_DEVICE_IS_ROUND);
    auto size = GetSubWindowSize(TEST_PARENT_CONTAINER_ID, DEFAULT_DISPLAY_ID);
    EXPECT_GT(size.Width(), 0);
}
```

---

## 自检清单

编写测试后，请验证：

- [ ] 直接调用目标方法，未使用间接方法
- [ ] 调用前已重置所有干扰状态
- [ ] 使用 Grep/Read 验证了所有方法名
- [ ] 每个测试独立，无共享状态
- [ ] 为所有 if/else 分支编写了测试
- [ ] 注释描述逻辑行为，未使用行号
- [ ] 每个测试有真实断言，非文档化测试
- [ ] 所有数字使用命名常量，无魔鬼数字
