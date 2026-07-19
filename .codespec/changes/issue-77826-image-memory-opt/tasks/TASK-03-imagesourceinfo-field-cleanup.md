# TASK-03: ImageSourceInfo 内部字段精简

**ADR:** ADR-3
**优先级:** 中
**预估节省:** ~60-80B/实例

## 目标

移除或按需分配 ImageSourceInfo 中不常用字段，减少单个 ImageSourceInfo 实例的基础大小。

## 改动范围

### 1. 移除 fillColor_（image_source_info.h:~163）
- `std::optional<Color> fillColor_` (~56B) — 已标记 `[[deprecated("in NG")]]`
- 确认 NG 代码路径不再使用：grep `fillColor_` 在 image_ng/ 目录下的引用
- 如果确认未使用，直接移除及相关的 getter/setter

### 2. reloadKey_ 改为按需分配（image_source_info.h:~175）
- `std::optional<std::string> reloadKey_` (~48B) → `std::unique_ptr<std::string>`
- 只在需要 reload 时分配（grep 确认使用场景）

### 3. 移除 pixmapBuffer_（image_source_info.h:~165）
- `const uint8_t* pixmapBuffer_` (8B) — 确认是否有使用场景
- 如果仅用于已废弃的代码路径，移除

### 4. srcRef_ 评估
- `std::shared_ptr<std::string> srcRef_` (8B) — 确认与 src_ 的关系
- 如果 src_ 已持有字符串副本，srcRef_ 是否还有独立存在的必要

## 验证方法

1. grep 确认移除字段在 NG 路径下无引用
2. 编译通过
3. sizeof 对比
