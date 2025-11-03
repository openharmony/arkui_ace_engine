#include <cstddef>
#include <regex>
#include <ani_signature_builder.h>
#include "ani_utils.h"

namespace OHOS::Ace {
namespace {
    const std::regex RESOURCE_APP_STRING_PLACEHOLDER(R"(\%((\d+)(\$)){0,1}([dsf]))", std::regex::icase);
    constexpr int32_t DEFAULT_SCOPE = 60;
}

AniAsyncEvent::AniAsyncEvent(ani_env* env, ani_ref ref)
{
    env_ = env;
    env->GlobalReference_Create(ref, &ref_);
}

AniAsyncEvent::~AniAsyncEvent()
{
    env_->GlobalReference_Delete(ref_);
}

ani_status AniAsyncEvent::Call(ani_size argc, ani_ref *argv)
{
    auto status = env_->CreateLocalScope(DEFAULT_SCOPE);
    if (status != ANI_OK) {
        return status;
    }

    ani_ref result {};
    status = env_->FunctionalObject_Call(static_cast<ani_fn_object>(ref_), argc, argv, &result);
    if (status != ANI_OK) {}

    env_->DestroyLoaclScope();
    return status;
}

ani_env* AniAsyncEvent::GetEnv()
{
    return env_;
}
}