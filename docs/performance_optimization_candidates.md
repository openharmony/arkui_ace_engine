# ACE Engine 性能优化候选函数清单

> **生成日期**: 2026-07-16
> **范围**: OpenHarmony ace_engine（master 分支）
> **原则**: 不改变对外功能/语义，仅提升执行效率；聚焦调用率高与通用流程函数
> **方法**: KB 路由定位热点模块 → 实际源码逐行核查（行号、代码均经验证）

## 优先级定义

| 级别 | 含义 |
|------|------|
| **P0** | 每帧 / 每节点 / 每事件执行且问题明确，收益最高、风险最低 |
| **P1** | 通用热路径次重要，或改动需稍多调用方确认 |
| **P2** | 日志 / 调试路径（trace / dump 开启时高频） |

## 选择说明

每个候选表格最后一列为 **是否优化**，采用复选框：

- `[ ]` 不优化（默认）
- `[x]` 选择优化

请直接在文件中把要优化的行改为 `[x]`，我据此落地修改源码。

## 热点模块定位

依据知识库 `Layout_Framework_Knowledge_Base.md` / `Pipeline_Knowledge_Base.md`，核心热点路径为：

```
PipelineContext::FlushVsync          # 每帧触发
  └─ UITaskScheduler                  # 任务调度 + dirty 节点收集
       └─ FrameNode::CreateLayoutTask # 每节点
            ├─ Measure / Layout        # 每节点递归
            └─ LayoutAlgorithm / LayoutWrapper
                 └─ SyncGeometryNode  # 每节点几何同步
```

以下清单按模块分组，每项含：**文件:行号、函数、问题、调用频率、优化方案、是否优化**。

---

## 一、渲染管线 / 帧调度（每帧执行）

| 优先级 | 文件:行号 | 函数 | 问题 | 调用频率 | 优化方案 | 是否优化 |
|---|---|---|---|---|---|---|
| P0 | `frameworks/core/pipeline_ng/ui_task_scheduler.h:156-159` | `AddSyncGeometryNodeTask` | 参数为 `std::function<void()>&&`（右值引用），但具名右值引用是左值，`emplace_back(task)` 触发**拷贝**而非移动构造；同类 `AddAfterLayoutTask` 用了 `std::move` | 每节点每帧布局结束同步 | 改为 `emplace_back(std::move(task))`，消除每个 `std::function` 的拷贝（含 lambda 捕获的 WeakPtr/bool/struct） | [ ] |
| P0 | `frameworks/core/pipeline_ng/pipeline_context.cpp:4800-4803` | `ConsumeTouchEvents` | 同一 key 上 `operator[]` 三次哈希查找（insert 1 次 + 取值 2 次）；`history.insert(begin(),...)` 每次 O(n) 前移 | 每帧有触摸事件时（拖拽/滚动逐帧多次） | 用 `try_emplace` 一次查找拿迭代器，复用 `it->second` | [ ] |
| P0 | `frameworks/core/pipeline_ng/pipeline_context.cpp:4685-4693` | `CollectTouchEventsBeforeVsync` | `touchEvents_.emplace_back(*iter)` 深拷贝 `TouchEvent`（内含 3 个 vector），而两者都是 `std::list` | 每帧清队列 | 用 `std::list::splice` O(1) 转移节点，零拷贝 | [ ] |
| P0 | `frameworks/core/pipeline_ng/ui_task_scheduler.cpp:152-153, 82-83` | `FlushLayoutTask` / `SetLayoutNodeRect` | 用 `std::set<RefPtr<FrameNode>>`（N 次红黑树堆分配）仅为排序去重，之后只遍历不查询 | 每帧 FlushTask | 改 `vector` + `sort` + `unique`，连续内存、零逐元素堆分配 | [ ] |
| P0 | `frameworks/core/pipeline_ng/pipeline_context.cpp:7483, 7503` | `AddFrameNodeChangeListener` / `AddChangedFrameNode` | `std::list` 上 `std::find` 去重 → 每帧 O(N²) | 每个 geometry/transform 变化的节点每帧 | 换 `unordered_set` 按 nodeId 去重，O(1) | [ ] |
| P1 | `frameworks/core/pipeline_ng/ui_task_scheduler.h:185-194` | `NodeCompare::operator()` | `GetLayoutPriority/GetPageId/GetDepth` 每比较各调用 2 次（`!=` 一次、`</>` 一次），共 6 次成员调用 | 每帧 O(N log N) 次比较 | 各缓存到局部变量，3 次调用即可 | [ ] |
| P1 | `frameworks/core/pipeline_ng/ui_task_scheduler.cpp:383-421` | `FlushSafeAreaPaddingProcess` | 拷贝整个 `std::set`（N 次树节点分配）仅为安全迭代；三趟遍历可合并 | 每帧（涉安全区布局时） | 快照有效指针到 `vector`（带 reserve），单趟做 Process+Reset，原表 O(1) clear | [ ] |

---

## 二、FrameNode 节点级（每节点每帧）

| 优先级 | 文件:行号 | 函数 | 问题 | 调用频率 | 优化方案 | 是否优化 |
|---|---|---|---|---|---|---|
| P0 | `frameworks/core/components_ng/base/frame_node.cpp:2998-3014` | `CreateLayoutTask` | 商用 Trace 无条件求值参数：`GetAncestorNodeOfFrame(false)` 调用 4 次（树遍历）、`layoutConstraint.ToString()` 每次堆分配 + 2 次 `vsnprintf` | 每脏节点每帧 | 缓存 `auto parent = GetAncestorNodeOfFrame(false);` 一次复用；将 ToString/树遍历置于 trace 开关后 | [ ] |
| P0 | `frameworks/core/components_ng/base/frame_node.cpp:5811-5828` | `UpdatePercentSensitive` | `GetAncestorNodeOfFrame(true)` 在宽/高两个分支各调一次，可合并 | 每节点每次 Measure 末尾 | 提到分支外取一次 parent，两个 Set 都复用 | [ ] |
| P0 | `frameworks/core/components_ng/base/frame_node.cpp:2307-2315` | `AdjustGridOffset` | `Claim(this)` 构造 RefPtr（原子 inc/dec）无条件构造，而 callee `UpdateGridOffset` 绝大多数节点立即返回 false（无 gridProperty_） | 每节点每帧 SyncGeometryNode | 先 `if(!HasGridProperty()) return;` 廉价守卫；或改 callee 接收 `FrameNode*` 不持所有权 | [ ] |
| P0 | `frameworks/core/components_ng/base/frame_node.cpp:6455-6457` | `OnLayoutFinish` | 两个 `OnDirtyLayoutWrapperSwap` 重载各 `Claim(this)` 一次，2 组原子 inc/dec | 每节点每次 Layout 完成 | 局部 `RefPtr self = Claim(this);` 一次，两个调用共用 | [ ] |
| P1 | `frameworks/core/components_ng/base/frame_node.cpp:6273, 6411-6413` | `Layout` / `OnLayoutFinish` | `SelfOrParentExpansive()`（含树遍历）同一布局流内调 2 次 | 每节点每帧 | 算一次后传入 OnLayoutFinish 复用 | [ ] |
| P1 | `frameworks/core/components_ng/base/frame_node.cpp:6252, 6274` | `Layout` | `GetContext()`（非平凡，含线程局部查找）被遮蔽局部重复调用 | 每节点每帧 | 复用 6252 的 pipeline，删 6274 重声明 | [ ] |
| P1 | `frameworks/core/components_ng/base/frame_node.cpp:6494-6523` | `SyncGeometryNode` | `GetLayoutConstraint()`/`GetBorderWidthProperty()` 各重复取值，`ScaleProperty::CreateScaleProperty()` if/else 各构造一次 | 每节点每帧（含边框时） | 缓存 `const auto& lc` / `const auto& bw`，`ScaleProperty sp` 提到 if 外 | [ ] |
| P1 | `frameworks/core/components_ng/base/frame_node.cpp:3274-3284` | `RebuildRenderContextTree` | `std::move` 后立即 `.clear()`（移动后容器本已有效且空），且 `oldFrameChildren.clear()` 紧接出作用域 | 每节点每帧（树 diff 帧） | 删两处冗余 `.clear()` | [ ] |
| P1 | `frameworks/core/components_ng/base/frame_node.cpp:6022-6023, 6190-6191` | `Measure` / `Layout`（trace 路径） | trace 三元式中 `GetAncestorNodeOfFrame(true)` 各调 2 次 | 每节点每帧（trace 开启时） | 取一次 parent 缓存 parentId；trace 时长本身被双重树遍历污染 | [ ] |

---

## 三、布局算法 / 属性计算（每节点每帧 Measure）

| 优先级 | 文件:行号 | 函数 | 问题 | 调用频率 | 优化方案 | 是否优化 |
|---|---|---|---|---|---|---|
| P0 | `frameworks/core/components_ng/layout/layout_property.cpp:646-692` | `LayoutProperty::CheckCalcLayoutConstraint` | `GetLayoutPolicyProperty()` 返回 `optional` 按值共拷贝 6 次；`ConvertToSize`（含表达式计算）重复算 2 次 | 每节点每帧 | 局部缓存 `layoutPolicy` 与 `ConvertToSize` 结果各一次复用 | [ ] |
| P0 | `frameworks/core/components_ng/layout/box_layout_algorithm.cpp:130-158` | `BoxLayoutAlgorithm::PerformMeasureSelfWithChildList` | 循环不变量 `hostLayoutProperty->CreateChildConstraint()`（拷贝 + 改 5 字段）在每子节点循环内重算 | 每容器每子节点每帧 | 提到循环前算一次 childConstraint 复用 | [ ] |
| P0 | `frameworks/core/components_ng/layout/box_layout_algorithm.cpp:266-282` | `BoxLayoutAlgorithm::PerformLayout` | 循环不变量 `layoutWrapper->GetHostNode()`（weak upgrade + 原子计数）在每子节点循环内调用 | 每容器每子节点每帧 | 提到循环前取一次 host | [ ] |
| P0 | `frameworks/core/components_ng/layout/layout_property.cpp:1042-1124` | `CreatePaddingAndBorderInner` 等 5 兄弟函数 | 每次重新 `ScaleProperty::CreateScaleProperty(pipeline)`（线程局部查找 + 3 getter），而 `layoutConstraint_->scaleProperty` 已缓存（同文件 `CreateMargin` 正确用了缓存值） | 每节点每帧多次 | 在 `layoutConstraint_.has_value()` 分支用 `scaleProperty` 缓存值 | [ ] |
| P1 | `frameworks/core/components_ng/property/measure_utils.cpp:551-579` | `UpdateOptionSizeByMaxOrMinCalcLayoutConstraint` | 无参 `CreateScaleProperty()` 每调一次管线查找，父调用 `UpdateOptionSizeByCalcLayoutConstraint` 调它 2 次 | calc 节点每帧 | 增参 `const ScaleProperty&`，复用调用方已有的 scaleProperty | [ ] |
| P1 | `frameworks/core/components_ng/property/layout_constraint.h:54` | `LayoutConstraintT` 默认初始化器 | `scaleProperty = CreateScaleProperty()` 致每次默认构造都做管线查找（`value_or(LayoutConstraintF())` 在 `CreateContentConstraint` 节点为空时每帧构造） | 每节点每帧（content 约束空时） | 移除默认初始化器，改为构造后显式赋值 | [ ] |
| P2 | `frameworks/base/utils/string_expression.h:34` (.cpp:192) | `StringExpression::ConvertDal2Rpn` | `std::string formula` 按值传（堆拷贝），而 `CalcValue()` 返回 `const std::string&` | calc 值变化时 | 签名改 `const std::string& formula` | [ ] |

---

## 四、base 通用工具（全代码库高频）

| 优先级 | 文件:行号 | 函数 | 问题 | 调用频率 | 优化方案 | 是否优化 |
|---|---|---|---|---|---|---|
| P0 | `frameworks/base/json/json_util.cpp:79-85, 107-114, 146-152, 595-629` | `JsonValue::GetBool/GetDouble/GetObject/GetInt/GetUInt/GetInt64/GetString(key,default)` | `Contains` + `GetValue` + 再 `GetValue`：同一 key 对 cJSON 兄弟链表 3 次 O(N) 线性扫描 | 622 文件用，属性/主题/资源解析热路径 | `GetValue` 取一次迭代器复用，3 次扫描降到 1 次 | [ ] |
| P0 | `frameworks/base/utils/string_expression.cpp:127-174` | `PushOpStack` | 每次 `std::map<string,int>` 重建（6 次树堆分配）；`ops.find(i)` 逐字符线性；`opMapping[curOp]`（char）隐式造 string 临时对象 | 每次 calc() 表达式求值（布局热路径） | 改 `static constexpr int8_t opPriority[128]` 下标直查，零分配 O(1) | [ ] |
| P0 | `frameworks/base/utils/string_expression.cpp:34-69` | `CheckCalcIsValid` | 每次构造 3 个 `std::regex` + `regex_replace` + 嵌套 `regex_search` 循环 | 每次 calc() 求值 | 去 regex：`remove_if` 去空格 + `std::count` 数括号 + `string::find` 找 calc，单趟扫描 | [ ] |
| P1 | `frameworks/base/utils/string_expression.cpp:71-125` | `ReplaceSignNumber` / `ReplaceSignNumberWithUnit` | 每次构造 `std::regex`；`mergeStr` 无 reserve 增长；`operator+` 多次临时 string | 每次 calc() 求值 | `mergeStr.reserve(formula.size()*2)` + `append` 链，去临时 | [ ] |
| P1 | `frameworks/base/utils/string_expression.cpp:291-310` | `CalculateExp` | 即便有缓存 RPN，仍 `rpnexp = lengthString` 整体拷贝 vector；`result` 无 reserve | 每 calc() 维度每帧 | 直接传 `lengthString` 给 `CalculateExpImpl`（取 const&），`result.reserve(rpnexp.size())` | [ ] |
| P1 | `frameworks/base/utils/string_utils.cpp:664-687` | `StringSplitter`（数值重载） | 每个分隔符 `source.substr()` 堆分配 string 喂给只需 `c_str()` 的 `strtod/strtol`；out 无 reserve | 字体族 / transform 列表解析每帧 | 加 string_view / `const char*,len` 重载直传；`out.reserve(分隔符数+1)` | [ ] |
| P1 | `frameworks/base/geometry/matrix4.cpp:234-237` | `Matrix4::IsIdentityMatrix` | `*this == CreateIdentity()` 每次构造 16 double 临时矩阵 + `std::equal` 不短路 | 变换组件每帧 + `Determinant`/`Invert` 路径 | 直接逐元素对常量做 `IsEqual` 比较，短路退出，保 0.0001 epsilon 语义 | [ ] |
| P2 | `frameworks/base/geometry/matrix4.cpp:571-582` | `Matrix4::ToString` | `std::to_string(double)` ×16（慢 snprintf + locale）+ out 无 reserve | 日志 / inspector 路径 | `reserve(384)` + `snprintf` 到栈 buf 再 `append` | [ ] |
| P2 | `offset.h:154-160`, `size.h:213-231`, `rect.h:364-402` | `Offset/Size/Rect::ToString` / `Rect::ToBounds` | `std::stringstream` 仅为格式化 2-4 个 double（locale/stringbuf 开销大） | 几何最常用类型，日志 / inspector 高频 | 改 `snprintf` 到栈 `char[64]` 再构造 string | [ ] |
| P2 | `frameworks/base/utils/string_utils.cpp:148-165` | `IsFloat` | `all_of` 全扫后再 `any_of` 全扫第二遍 | 数值校验 | 在 `all_of` lambda 内记 `has_digit`，去掉第二遍 | [ ] |
| P2 | `frameworks/base/utils/time_util.cpp:75-89` | `ConvertTimestampToStr` | `strftime` 已写完日期，却用 `std::stringstream` 仅为追加 3 位毫秒 | 日志 / trace 格式化 | `snprintf(buf, size, "%s.%03d", timeStr, ms)` 一次完成 | [ ] |

---

## 汇总统计

| 模块 | P0 | P1 | P2 | 小计 |
|------|----|----|----|----|
| 渲染管线 / 帧调度 | 5 | 2 | 0 | 7 |
| FrameNode 节点级 | 4 | 4 | 1 | 9 |
| 布局算法 / 属性计算 | 4 | 2 | 1 | 7 |
| base 通用工具 | 3 | 4 | 3 | 10 |
| **合计** | **16** | **12** | **5** | **33** |

## 落地建议

1. **先做 P0**：收益最高、风险最低，多为局部重构（加 `std::move`、`reserve`、`try_emplace`、循环不变量外提、`Claim(this)` 复用 / 守卫）。
2. **逐项验证**：每改一项跑相关单测（`text_pattern_test`、布局相关测试、`linux_unittest_capi`）。
3. **签名变更需确认调用方**：涉及内部辅助函数签名（`measure_utils.cpp` 加参数、`string_expression.h::ConvertDal2Rpn` 改 const&）属内部函数，非 `interfaces/native|napi` 公共 API，落地前需确认全部调用方。
4. **公共 API 边界**：不触碰 `interfaces/native/` 与 `interfaces/napi/` 下公共签名。
5. **Trace 项注意**：`CreateLayoutTask` / `Measure` / `Layout` 的 trace 优化既省产线开销，也避免 trace 测量本身被双重树遍历污染。
