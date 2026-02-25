# 一、前置知识
## 1.BUILD.gn基础结构
- 静态库：static_library("目标名")
- 动态库：ohos_shared_library("目标名")
- 可执行文件：ohos_executable("目标名")

## 2.关键配置项
- sources：源码文件列表，支持通配符（如["sample/input_compatible_policy.cpp"]）
- include_dirs：头文件搜索路径（如["$ace_root/frameworks/"]）
- deps：依赖关系，格式为"路径:目标名"（如["$ace_root/build:libace_compatible"]）
- part_name + subsystem_name：系统集成标识，必须与部件配置文件一致

## 3.基础结构模板
```
import("//build/ohos.gni")  # 导入构建系统模板

# 定义动态库
ohos_shared_library("my_lib") {
  sources = [
    "src/file1.cpp"  # 源文件
  ]
  include_dirs = [
    "//base/update/server_sample/include",  # 自定义头文件路径
    "//third_party/openssl/include",  # 第三方库头文件
  ]
  deps = [
    "//utils/native/base:utils",  # 依赖模块
  ]
  part_name = "update_service"  # 所属部件名
  subsystem_name = "graphic"    # 所属子系统名 (如果需要)
}
```

# 二、产品定制input compatible策略的实现方式
按照框架预定义好的接口，实现对应函数，并按照编译要求，将对应实现文件编译出的动态库预置到镜像 system/lib64 目录下即可。
当前要求动态库文件名必须为：libtransform_interaction_ext.z.so，因此gn文件中必须指定动态库名称为 libtransform_interaction_ext，如下：
```
ohos_shared_library("libtransform_interaction_ext")
```
## 1). 依赖的头文件
foundation/arkui/ace_engine/interfaces/inner_api/ace_kit/include/ui/event/input_compatible_policy.h

## 2). 如何实现cpp文件？
### InputCompatiblePolicy类为抽象类
1. 创建.cpp文件
2. 定义一个继承InputCompatiblePolicy的具体类，并实现头文件中声明的纯虚函数
```
class InputCompatiblePolicyImpl : public InputCompatiblePolicy {
public:
    InputCompatiblePolicyImpl() = default;
    ~InputCompatiblePolicyImpl() = default;

    bool IsInputCompatibleConvertingNeeded(InputCompatibleSource source) override
    {
        return false;
    }
};
```
3. 使用 extern "C" 导出必要符号，确保C链接，避免C++名称修饰
```
extern "C" ACE_FORCE_EXPORT Kit::InputCompatiblePolicy* GetInputCompatiblePolicyInstance()
{
    // 使用全局变量确保整个应用使用过程中的对象一直有效
    static OHOS::Ace::Kit::InputCompatiblePolicyImpl instance;
    return &instance;
}
```

# 三、如何编译出.so文件？
1. [编写对应cpp文件](#三如何实现cpp文件)
2. [编写动态库的BUILD.gn构建脚本](#一编写buildgn文件)
3. 将动态库加入目标 Kit 的依赖
   在对应位置的BUILD.gn文件中，在deps列表添加该动态库，格式为 "路径:目标名"
```
# 示例：
group("ace_packages") {
  deps = [
    # 已有的依赖
    "$ace_root/component_ext:component_ext",
    
    # 新增的动态库依赖
    "$ace_root/transform_interaction:libtransform_interaction_ext",
    # 替换为实际路径和目标名
    "$ace_root/your_path:your_lib_target_name",
  ]
}
```
4. 跟随目标Kit的编译命令执行构建，即可在输出目录中生成对应的.so动态库文件