/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <common.h>
#include <utility>

using std::string, std::cout, std::endl, std::vector;

es2panda_Impl *es2pandaImplementation = nullptr;
static thread_local StageArena currentArena;

StageArena* StageArena::instance()
{
    return &currentArena;
}

void StageArena::add(void* pointer)
{
    if (pointer)
        allocated.push_back(pointer);
}

void StageArena::cleanup()
{
    if (totalSize > 0 && false)
        printf("cleanup %d objects %d bytes\n", (int)allocated.size(), (int)totalSize);
    for (auto it : allocated) {
        free(it);
    }
    totalSize = 0;
    allocated.clear();
}

StageArena::StageArena()
{
    totalSize = 0;
}

StageArena::~StageArena()
{
    cleanup();
}

char* StageArena::strdup(const char* string)
{
    auto* arena = StageArena::instance();
    auto size = strlen(string) + 1;
    char* memory = (char*)arena->alloc(size);
    memcpy_s(memory, size, string, size);
    return memory;
}

void* StageArena::alloc(size_t size)
{
    void* result = malloc(size);
    totalSize += size;
    add(result);
    return result;
}

#ifdef KOALA_WINDOWS
    #include <windows.h>
    #define PLUGIN_DIR "windows_host_tools"
    #define LIB_PREFIX "lib"
    #define LIB_SUFFIX ".dll"
#endif

#if defined(KOALA_LINUX) || defined(KOALA_MACOS)
    #include <dlfcn.h>

    #ifdef __x86_64__
        #define PLUGIN_DIR "linux_host_tools"
    #else
        #define PLUGIN_DIR "linux_arm64_host_tools"
    #endif

    #define LIB_PREFIX "lib"
    #define LIB_SUFFIX ".so"
#endif

const char* DEFAULT_SDK_PATH = "../../../incremental/tools/panda/node_modules/@panda/sdk" ;
const char* NAME = LIB_PREFIX "es2panda-public" LIB_SUFFIX;

const char* LIB_ES2PANDA_PUBLIC = LIB_PREFIX "es2panda_public" LIB_SUFFIX;
const char* IS_UI_FLAG = "IS_UI_FLAG";
const char* NOT_UI_FLAG = "NOT_UI_FLAG";
const string MODULE_SUFFIX = ".d.ets";
const string ARKUI = "arkui";

#ifdef KOALA_WINDOWS
    const char *SEPARATOR = "\\";
#else
    const char *SEPARATOR = "/";
#endif
const char *LIB_DIR = "lib";

static std::string ES2PANDA_LIB_PATH = "";

std::string joinPath(vector<string> &paths)
{
    std::string res;
    for (std::size_t i = 0; i < paths.size(); ++i) {
        if (i == 0) {
            res = paths[i];
        } else {
            res += SEPARATOR + paths[i];
        }
    }
    return res;
}

void impl_SetUpSoPath(KStringPtr &soPath)
{
    ES2PANDA_LIB_PATH = std::string(soPath.c_str());
}
KOALA_INTEROP_V1(SetUpSoPath, KStringPtr);

// Improve: simplify this
void* FindLibrary() {
    void *res = nullptr;
    std::vector<std::string> pathArray;
    
    // find by SetUpSoPath
    if (!ES2PANDA_LIB_PATH.empty()) {
        pathArray = {ES2PANDA_LIB_PATH, LIB_DIR, LIB_ES2PANDA_PUBLIC};
        res = loadLibrary(joinPath(pathArray));
        if (res) {
            return res;
        }
    }

    // find by set PANDA_SDK_PATH
    char* envValue = getenv("PANDA_SDK_PATH");
    if (envValue) {
        pathArray = {envValue, PLUGIN_DIR, LIB_DIR, NAME};
        res = loadLibrary(joinPath(pathArray));
        if (res) {
            return res;
        }
    }

    // find by set LD_LIBRARY_PATH
    pathArray = {LIB_ES2PANDA_PUBLIC};
    res = loadLibrary(joinPath(pathArray));
    if (res) {
        return res;
    }

    // find by DEFAULT_SDK_PATH
    pathArray = {DEFAULT_SDK_PATH, PLUGIN_DIR, LIB_DIR, NAME};
    res = loadLibrary(joinPath(pathArray));
    if (res) {
        return res;
    }

    return nullptr;
}

es2panda_Impl *GetImplSlow()
{
    if (es2pandaImplementation) {
        return es2pandaImplementation;
    }
    auto library = FindLibrary();
    if (!library) {
        printf("No library (es2panda_lib.cc)");
        abort();
    }
    auto symbol = findSymbol(library, "es2panda_GetImpl");
    if (!symbol) {
        printf("no entry point");
        abort();
    }
    es2pandaImplementation = reinterpret_cast<es2panda_Impl *(*)(int)>(symbol)(ES2PANDA_LIB_VERSION);
    return es2pandaImplementation;
}

es2panda_ContextState intToState(KInt state)
{
    return es2panda_ContextState(state);
}

string getString(KStringPtr ptr)
{
    return ptr.data();
}

char* getStringCopy(KStringPtr& ptr)
{
    return StageArena::strdup(ptr.c_str() ? ptr.c_str() : "");
}

KNativePointer impl_CreateConfig(KInt argc, KStringArray argvPtr) {
    const std::size_t headerLen = 4;

    const char** argv = StageArena::allocArray<const char*>(argc);
    std::size_t position = headerLen;
    std::size_t strLen;
    for (std::size_t i = 0; i < static_cast<std::size_t>(argc); ++i) {
        strLen = unpackUInt(argvPtr + position);
        position += headerLen;
        argv[i] = StageArena::strdup(std::string(reinterpret_cast<const char*>(argvPtr + position), strLen).c_str());
        position += strLen;
    }
    return GetImpl()->CreateConfig(argc, argv);
}
KOALA_INTEROP_2(CreateConfig, KNativePointer, KInt, KStringArray)

KNativePointer impl_DestroyConfig(KNativePointer configPtr) {
    auto config = reinterpret_cast<es2panda_Config*>(configPtr);
    GetImpl()->DestroyConfig(config);
    return nullptr;
}
KOALA_INTEROP_1(DestroyConfig, KNativePointer, KNativePointer)

void impl_DestroyContext(KNativePointer contextPtr) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    GetImpl()->DestroyContext(context);
    StageArena::instance()->cleanup();
}
KOALA_INTEROP_V1(DestroyContext, KNativePointer)

KNativePointer impl_UpdateCallExpression(
    KNativePointer contextPtr,
    KNativePointer nodePtr,
    KNativePointer calleePtr,
    KNativePointerArray argumentsPtr,
    KInt argumentsLen,
    KNativePointer typeParamsPtr,
    KBoolean optionalT,
    KBoolean trailingCommaT
) {
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto callee = reinterpret_cast<es2panda_AstNode*>(calleePtr);
    auto arguments = reinterpret_cast<es2panda_AstNode**>(argumentsPtr);
    auto typeParams = reinterpret_cast<es2panda_AstNode*>(typeParamsPtr);
    auto optional = static_cast<bool>(optionalT);
    auto trailingComma = static_cast<bool>(trailingCommaT);

    auto nn = GetImpl()->CreateCallExpression(
        context, callee, arguments, argumentsLen, typeParams, optional, trailingComma
    );
    GetImpl()->AstNodeSetOriginalNode(context, nn, node);
    return nn;
}
KOALA_INTEROP_8(UpdateCallExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KInt, KNativePointer, KBoolean, KBoolean)

KInt impl_IdentifierIdentifierFlags(KNativePointer contextPtr, KNativePointer nodePtr) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);

    return
        (GetImpl()->IdentifierIsOptionalConst(context, node) ? (1 << 0) : 0) |
        (GetImpl()->IdentifierIsReferenceConst(context, node) ? (1 << 1) : 0) |
        (GetImpl()->IdentifierIsTdzConst(context, node) ? (1 << 2) : 0);
}
KOALA_INTEROP_2(IdentifierIdentifierFlags, KInt, KNativePointer, KNativePointer)

/*
Improve: NOT FROM API (shouldn't be there)
-----------------------------------------------------------------------------------------------------------------------------
*/

es2panda_AstNode * cachedParentNode;
es2panda_Context * cachedContext;

static void changeParent(es2panda_AstNode *child)
{
    GetImpl()->AstNodeSetParent(cachedContext, child, cachedParentNode);
}

static void SetRightParent(es2panda_AstNode *node, void *arg)
{
    es2panda_Context *ctx = static_cast<es2panda_Context *>(arg);
    cachedContext = ctx;
    cachedParentNode = node;

    GetImpl()->AstNodeIterateConst(ctx, node, changeParent);
}

KNativePointer impl_AstNodeUpdateAll(KNativePointer contextPtr, KNativePointer programPtr) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto program = reinterpret_cast<es2panda_AstNode*>(programPtr);

    GetImpl()->AstNodeForEach(program, SetRightParent, context);
    return program;
}
KOALA_INTEROP_2(AstNodeUpdateAll, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_AstNodeSetChildrenParentPtr(KNativePointer contextPtr, KNativePointer nodePtr) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    cachedParentNode = node;

    GetImpl()->AstNodeIterateConst(context, node, changeParent);
    return node;
}
KOALA_INTEROP_2(AstNodeSetChildrenParentPtr, KNativePointer, KNativePointer, KNativePointer)

std::vector<void*> cachedChildren;

static void visitChild(es2panda_AstNode *node)
{
    cachedChildren.emplace_back(node);
}

KNativePointer impl_AstNodeChildren(
    KNativePointer contextPtr,
    KNativePointer nodePtr
) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    cachedContext = context;
    cachedChildren.clear();

    GetImpl()->AstNodeIterateConst(context, node, visitChild);
    return StageArena::clone(cachedChildren);
}
KOALA_INTEROP_2(AstNodeChildren, KNativePointer, KNativePointer, KNativePointer)

/*
-----------------------------------------------------------------------------------------------------------------------------
*/

// From koala-wrapper
// Improve: check if some code should be generated

void impl_MemInitialize()
{
    GetImpl()->MemInitialize();
}
KOALA_INTEROP_V0(MemInitialize)

void impl_MemFinalize()
{
    GetImpl()->MemFinalize();
}
KOALA_INTEROP_V0(MemFinalize)

static bool isUIHeaderFile(es2panda_Context* context, es2panda_Program* program)
{
    auto result = GetImpl()->ProgramFileNameWithExtensionConst(context, program);
    string fileNameWithExtension(result);
    result = GetImpl()->ProgramModuleNameConst(context, program);
    string moduleName(result);

    return fileNameWithExtension.length() >= MODULE_SUFFIX.length()
        && fileNameWithExtension.substr(fileNameWithExtension.length() - MODULE_SUFFIX.length()) == MODULE_SUFFIX
        && moduleName.find(ARKUI) != std::string::npos;
}

KBoolean impl_ProgramCanSkipPhases(KNativePointer context, KNativePointer program)
{
    KStringPtr isUiFlag(IS_UI_FLAG);
    KStringPtr notUiFlag(NOT_UI_FLAG);
    const auto _context = reinterpret_cast<es2panda_Context*>(context);
    const auto _program = reinterpret_cast<es2panda_Program*>(program);
    if (isUIHeaderFile(_context, _program)) {
        return false;
    }
    std::size_t sourceLen;
    const auto externalSources = reinterpret_cast<es2panda_ExternalSource **>
        (GetImpl()->ProgramExternalSources(_context, _program, &sourceLen));
    for (std::size_t i = 0; i < sourceLen; ++i) {
        std::size_t programLen;
        auto programs = GetImpl()->ExternalSourcePrograms(externalSources[i], &programLen);
        for (std::size_t j = 0; j < programLen; ++j) {
            if (isUIHeaderFile(_context, programs[j])) {
                return false;
            }
        }
    }
    return true;
}
KOALA_INTEROP_2(ProgramCanSkipPhases, KBoolean, KNativePointer, KNativePointer)

KNativePointer impl_AstNodeProgram(KNativePointer contextPtr, KNativePointer instancePtr)
{
    auto _context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto _receiver = reinterpret_cast<es2panda_AstNode*>(instancePtr);

    if (GetImpl()->AstNodeIsProgramConst(_context, _receiver)) {
        return GetImpl()->ETSModuleProgram(_context, _receiver);
    }
    return impl_AstNodeProgram(_context, GetImpl()->AstNodeParent(_context, _receiver));
}
KOALA_INTEROP_2(AstNodeProgram, KNativePointer, KNativePointer, KNativePointer)
