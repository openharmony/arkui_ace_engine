#include <iostream>

#include "dynamic-loader.h"
#include "es2panda_lib.h"

#ifdef __x86_64__
    #define PLUGIN_DIR "linux_host_tools"
#else
    #define PLUGIN_DIR "linux_arm64_host_tools"
#endif

const char* libpath = "../../incremental/tools/panda/node_modules/@panda/sdk/" PLUGIN_DIR "/lib/libes2panda-public.so";

static es2panda_Impl *impl = nullptr;

es2panda_Impl *GetImpl() {
    if (impl) {
        return impl;
    }
    auto library =  loadLibrary(libpath);
    if (!library) {
        throw std::runtime_error("No library");
    }
    auto symbol = findSymbol(library, "es2panda_GetImpl");
    if (!symbol) {
        throw std::runtime_error("No entry point");
    }
    impl = reinterpret_cast<es2panda_Impl *(*)(int)>(symbol)(ES2PANDA_LIB_VERSION);
    return impl;
}

static const char* source =
"export class XXX {}"
;
static es2panda_AstNode* newStatements[1];

int main() {
    impl = GetImpl();
    const char* args[] = {
        // command with which the program is invoked (ignored)
        "",
        "--arktsconfig",
        // path to config
        "./arktsconfig.json",
        // path to source
        "./plugins/input/main.sts",
        "--stdlib",
        "../../incremental/tools/panda/node_modules/@panda/sdk/ets/stdlib"
    };

    auto config = GetImpl()->CreateConfig(6, args);
    auto context = GetImpl()->CreateContextFromString(config, source, args[3]);

    GetImpl()->ProceedToState(context, ES2PANDA_STATE_PARSED);
    if(GetImpl()->ContextState(context) == ES2PANDA_STATE_ERROR)
    {
        std::cout << "PROCEED TO PARSE ERROR" << std::endl;
        std::cout << GetImpl()->ContextErrorMessage(context) << std::endl;
    }
    else {
        std::cout << "PROCEED TO PARSE SUCCESS" << std::endl;
    }

    auto ast = GetImpl()->ProgramAst(context, GetImpl()->ContextProgram(context));

    std::cout << GetImpl()->AstNodeDumpEtsSrcConst(context, ast) << std::endl;

    std::size_t count = 0;
    auto statements = impl->BlockStatementStatements(context, ast, &count);
    auto oldClass = statements[0];
    auto oldDef = GetImpl()->ClassDeclarationDefinition(context, oldClass);

    std::cout << "statement count: " << count << std::endl;

    auto *identifier = impl->CreateIdentifier1(context, (char *)"XXX");
    auto *newDef = impl->CreateClassDefinition1(
        context,
       // oldDef,
        identifier, nullptr, 0, Es2pandaClassDefinitionModifiers::CLASS_DEFINITION_MODIFIERS_CLASS_DECL,
        Es2pandaModifierFlags::MODIFIER_FLAGS_DECLARE
    );
    auto *newClazz = impl->CreateClassDeclaration(context, newDef);
    newStatements[0] = newClazz;

    impl->BlockStatementSetStatements(context, ast, newStatements, 1);
    impl->AstNodeSetParent(context, newDef, newClazz);
    impl->AstNodeSetParent(context, identifier, newDef);

    impl->BlockStatementSetStatements(context, ast, newStatements, 1);

    (void)impl->BlockStatementStatements(context, ast, &count);
    std::cout << "new statement count: " << count << std::endl;

    std::cout << GetImpl()->AstNodeDumpEtsSrcConst(context, ast) << std::endl;

    GetImpl()->ProceedToState(context, ES2PANDA_STATE_BOUND);
    if(GetImpl()->ContextState(context) == ES2PANDA_STATE_ERROR)
    {
        std::cout << "PROCEED TO BOUND ERROR" << std::endl;
        std::cout << GetImpl()->ContextErrorMessage(context) << std::endl;
    }
    else {
        std::cout << "PROCEED TO BOUND SUCCESS" << std::endl;
    }

    GetImpl()->ProceedToState(context, ES2PANDA_STATE_CHECKED);
    if(GetImpl()->ContextState(context) == ES2PANDA_STATE_ERROR)
    {
        std::cout << "PROCEED TO CHECKED ERROR" << std::endl;
        std::cout << GetImpl()->ContextErrorMessage(context) << std::endl;
    }
    else {
        std::cout << "PROCEED TO CHECKED SUCCESS" << std::endl;
    }

    GetImpl()->ProceedToState(context, ES2PANDA_STATE_LOWERED);
    if(GetImpl()->ContextState(context) == ES2PANDA_STATE_ERROR)
    {
        std::cout << "PROCEED TO LOWERED ERROR" << std::endl;
        std::cout << GetImpl()->ContextErrorMessage(context) << std::endl;
    }
    else {
        std::cout << "PROCEED TO LOWERED SUCCESS" << std::endl;
    }

    GetImpl()->ProceedToState(context, ES2PANDA_STATE_ASM_GENERATED);
    if(GetImpl()->ContextState(context) == ES2PANDA_STATE_ERROR)
    {
        std::cout << "PROCEED TO ASM ERROR" << std::endl;
        std::cout << GetImpl()->ContextErrorMessage(context) << std::endl;
    }
    else {
        std::cout << "PROCEED TO ASM SUCCESS" << std::endl;
    }

    GetImpl()->ProceedToState(context, ES2PANDA_STATE_BIN_GENERATED);
    if(GetImpl()->ContextState(context) == ES2PANDA_STATE_ERROR)
    {
        std::cout << "PROCEED TO BIN ERROR" << std::endl;
        std::cout << GetImpl()->ContextErrorMessage(context) << std::endl;
    }
    else {
        std::cout << "PROCEED TO BIN SUCCESS" << std::endl;
    }
}
