# List / ListItemGroup 泛化设计：支持任意子组件

> **文档版本**: v3.0（最终方案）
> **更新时间**: 2026-07-09
> **源码版本**: OpenHarmony ace_engine (master 分支)
> **目的**: 记录 List/ListItemGroup 支持任意类型子组件的泛化设计，基于 `LazyContainerItemHelper` 子组件持有方案。

---

## 目录

1. [背景与目标](#1-背景与目标)
2. [问题分析：ListItem 特化处理](#2-问题分析listitem-特化处理)
3. [最终方案：LazyContainerItemHelper](#3-最终方案lazycontaineritemhelper)
4. [架构设计](#4-架构设计)
5. [改动清单](#5-改动清单)
6. [关键技术决策](#6-关键技术决策)
7. [已兼容的部分（无需改动）](#7-已兼容的部分无需改动)
8. [测试覆盖](#8-测试覆盖)

---

## 1. 背景与目标

### 现状

List 组件体系包含三个组件：List（虚拟化滚动容器）、ListItemGroup（分组容器）、ListItem（单个列表项）。

当前实现隐含契约：**List 的子节点只能是 ListItem 或 ListItemGroup；ListItemGroup 的子节点只能是 ListItem**。代码中通过 `DynamicCast<ListItemPattern>` 或标签判断隐式假设非 group 子节点就是 ListItem，导致通用组件（Text/Row/Button/...）无法参与 `scrollToIndex`、`onScrollIndex`、方向键焦点导航。

### 目标

1. List 和 ListItemGroup 支持任意类型子组件。
2. 通用组件能测量、布局、滚动、`scrollToIndex`、可见索引回调。
3. 通用组件支持方向键焦点导航。
4. ListItem 特有能力（swipeAction、selectable、编辑复选框）继续只对真 ListItem 生效。
5. 索引能力通过 `LazyContainerItemHelper` 统一管理，组件销毁时无脏数据。

---

## 2. 问题分析：ListItem 特化处理

### 核心模式

代码中所有针对 ListItem 的特化处理归结为**一个二元判断**：

```cpp
bool isGroup = wrapper->GetHostTag() == V2::LIST_ITEM_GROUP_ETS_TAG;
if (isGroup) { /* group 专属 */ }
else { /* 隐式当作 ListItem */ }
```

### 特化点分类

| 类别 | 位置 | 命中数 |
|------|------|--------|
| 标签字符串判断（布局热路径） | list_layout_algorithm.cpp 等 | ~30 处 |
| DynamicCast / GetPattern 类型转换 | list_pattern.cpp 等 | ~65 处 |
| ListItemGroup 纯位置取子节点 | list_item_group_layout_algorithm.cpp | 整个布局算法 |
| 位置映射与高度估算 | list_position_map.cpp / list_height_offset_calculator.cpp | ~10 处 |

### 焦点导航是真正的缺口

List 装了自定义 scope-focus 算法（`GetCurrentFocusIndex`/`FindChildFocusNodeByIndex`/`ScrollToNode`），纯 index-based 且只认 ListItemPattern/ListItemGroupPattern，通用组件在方向键/Tab 遍历时被跳过。

---

## 3. 最终方案：LazyContainerItemHelper

### 设计核心

新建 `LazyContainerItemHelper` 类，作为**子组件的索引载体**，由**基类 Pattern** 以 `RefPtr` 持有（默认 nullptr，懒创建）。

```
子组件销毁 → helper 随之销毁 → 无脏数据（解决容器侧映射的脏数据问题）
```

### Helper 类定义

**文件**：`frameworks/core/components_ng/pattern/lazy_container_item_helper.{h,cpp}`

```cpp
class LazyContainerItemHelper : public virtual AceType {
    DECLARE_ACE_TYPE(LazyContainerItemHelper, AceType);
public:
    // 索引读写（迁移自 ListItemPattern 的裸成员）
    int32_t GetIndexInList() const;            // 默认 0
    void SetIndexInList(int32_t index);
    int32_t GetIndexInListItemGroup() const;   // 默认 -1（哨兵：不在 group 内）
    void SetIndexInListItemGroup(int32_t index);

    // HOME/END 焦点跳转（迁移自 ListItemPattern，纯 FocusHub 操作）
    bool FindHeadOrTailChild(const RefPtr<FocusHub>&, FocusStep, WeakPtr<FocusHub>&);

private:
    int32_t indexInList_ = 0;
    int32_t indexInListItemGroup_ = -1;
};
```

- **头文件前向声明** `FocusHub`/`FocusStep`，不 include `focus_hub.h`（减少传递依赖）。
- `FindHeadOrTailChild` 实现在 .cpp（需要 FocusHub 完整类型）。

---

## 4. 架构设计

### 4.1 基类 Pattern 持有 helper

**文件**：`pattern.h`

```cpp
class Pattern : public virtual AceType {
    // ...
    const RefPtr<LazyContainerItemHelper>& GetOrCreateLazyContainerItemHelper();
    const RefPtr<LazyContainerItemHelper>& GetLazyContainerItemHelper() const;
protected:
    RefPtr<LazyContainerItemHelper> lazyContainerItemHelper_;  // nullptr 默认，零成本
};
```

- `GetOrCreate` 懒创建，返回 const 引用（避免智能指针拷贝）。
- 普通组件（不在容器内）的 helper 保持 nullptr。

### 4.2 ListItem 索引迁移

`ListItemPattern` 删除原裸成员 `indexInList_`/`indexInListItemGroup_`，改为转发：

```cpp
int32_t GetIndexInList() const {
    const auto& helper = GetLazyContainerItemHelper();
    return helper ? helper->GetIndexInList() : 0;  // 默认值与原成员一致
}
void SetIndexInList(int32_t index) {
    GetOrCreateLazyContainerItemHelper()->SetIndexInList(index);
}
```

`ListItemGroupPattern` 的 `indexInList_` 同理迁移。外部 API 不变，~30 个调用点零改动。

`FindHeadOrTailChild` 同样转发给 helper。

### 4.3 SetListItemIndex 写入子组件 helper

布局算法在 `SetListItemIndex` 漏斗点写入**子组件自己的 helper**：

```cpp
// ListLayoutAlgorithm::SetListItemIndex
auto pattern = host->GetPattern();
const auto& helper = pattern->GetOrCreateLazyContainerItemHelper();
helper->SetIndexInList(index);  // 覆盖 ListItem + 通用组件
```

Group 层同理，写入 `indexInListItemGroup` 和 `indexInList`。

### 4.4 焦点路径通用回退

焦点方法在 ListPattern 上下文运行（`this` = List），读取子组件的 helper：

```cpp
int32_t ListPattern::GetCurrentFocusIndex(const RefPtr<Pattern>& curPattern) {
    auto listItem = DynamicCast<ListItemPattern>(curPattern);
    if (listItem) return listItem->GetIndexInList();        // ListItem 快速路径
    auto group = DynamicCast<ListItemGroupPattern>(curPattern);
    if (group) return group->GetIndexInList();              // Group 快速路径
    const auto& helper = curPattern->GetLazyContainerItemHelper();  // 通用回退
    return helper ? helper->GetIndexInList() : -1;
}
```

`ScrollToNode`/`FindChildFocusNodeByIndex`/`GetChildFocusNodeByIndex` 同理。

---

## 5. 改动清单

| 文件 | 改动 |
|------|------|
| **新增** `lazy_container_item_helper.{h,cpp}` | helper 类（索引标量 + FindHeadOrTailChild） |
| `pattern.h` | 持有 RefPtr + GetOrCreate/Get 方法 |
| `list_item_pattern.{h,cpp}` | 索引成员迁移到 helper（转发），FindHeadOrTailChild 转发 |
| `list_item_group_pattern.{h,cpp}` | indexInList 迁移到 helper |
| `list_item_layout_algorithm.h` | 清理死代码（从未读写的 indexInList_/indexInListItemGroup_） |
| `list_pattern.{h,cpp}` | 焦点路径通用组件回退 |
| `list_layout_algorithm.cpp` | SetListItemIndex 写子组件 helper |
| `list_item_group_layout_algorithm.cpp` | SetListItemIndex 写子组件 helper |
| `pattern/BUILD.gn` | 注册 helper.cpp |
| `.gitcode/CODEOWNERSA` | helper 的 reviewer |
| **测试** `lazy_container_item_helper_test_ng.cpp` | 25 个 TDD 用例 |
| `test/unittest/BUILD.gn` | helper.cpp 加入共享测试库 |
| `focus_hub_test_ng_branch_coverage.cpp` | 适配迁移成员 |
| `list/BUILD.gn`（测试） | 注册测试文件 |

---

## 6. 关键技术决策

| 决策 | 原因 |
|------|------|
| helper 放子组件（基类 Pattern 持有） | 组件销毁即销毁，无脏数据；通用组件通过继承获得 |
| 标量成员而非 map | 每个子组件一个 helper，无需 id→index 映射 |
| 保留 GetNextFocusNode | 避免影响 TDD，保持最小修改 |
| FindHeadOrTailChild 迁移到 helper | 纯 FocusHub 操作，与 ListItem 类型无关 |
| Get 方法返回 const 引用 | 避免智能指针引用计数拷贝 |
| `indexInListItemGroup_` 默认 -1 | ClickJudge/HandleFocusEvent 依赖此哨兵值判断是否在 group 内 |

---

## 7. 已兼容的部分（无需改动）

| 模块 | 原因 |
|------|------|
| `scrollToIndex`（jump + smooth） | 基于 `itemPosition_`（按 index 记录所有子节点），无 ListItem 依赖 |
| `onScrollIndex` 回调 | `GetStartIndex/GetEndIndex` 读 `itemPosition_` keys |
| `ListPositionMap`（posMap_） | `isGroup` 标签对通用组件记 false，语义正确 |
| `GetItemRect` / `GetItemRectInGroup` | 基于 `GetChildByIndex` + 几何，无类型检查 |
| `list_height_offset_calculator` | 非 ListItem 走几何尺寸路径 |
| swipe/select/checkbox | cast 失败安全降级（no-op），天然只对 ListItem 生效 |

---

## 8. 测试覆盖

25 个 TDD 用例，分 6 组：

| 组 | 覆盖点 | 用例数 |
|----|--------|--------|
| A：helper 纯单元 | 索引读写、默认值（0/-1）、负值 | 3 |
| B：FindHeadOrTailChild | null 输入、非 END 步骤、HOME/TAIL 分支、命中 | 5 |
| C：基类 Pattern 持有 | 默认 nullptr、懒创建、幂等、const 引用 | 4 |
| D：ListItem/Group 转发 | 默认值、Set/Get、覆盖、FindHeadOrTailChild 转发 | 6 |
| E：SetListItemIndex 集成 | 布局后 helper 携带正确索引（含通用组件） | 2 |
| F：GetCurrentFocusIndex 回退 | ListItem/Group/通用/无 helper/null | 5 |

---

**文档结束**

> 本文档基于 OpenHarmony ace_engine 源码最终方案（v3）编写。
