#ifndef HEADLESS_RENDER_CAPTURE_FILE_UTILS_H
#define HEADLESS_RENDER_CAPTURE_FILE_UTILS_H

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/stat.h>

namespace rendercapture {

inline bool MkdirRecursive(const std::string& dir)
{
    if (dir.empty() || dir == "/") return true;
    if (mkdir(dir.c_str(), 0777) == 0) return true;
    if (errno == EEXIST) return true;
    if (errno != ENOENT) return false;
    auto slash = dir.rfind('/');
    if (slash == std::string::npos || slash == 0) return false;
    if (!MkdirRecursive(dir.substr(0, slash))) return false;
    return mkdir(dir.c_str(), 0777) == 0 || errno == EEXIST;
}

inline bool WriteFile(const std::string& path, const uint8_t* data, size_t size)
{
    auto pos = path.rfind('/');
    if (pos != std::string::npos) {
        std::string dir = path.substr(0, pos);
        if (!dir.empty() && dir != "/") {
            MkdirRecursive(dir);
        }
    }
    FILE* fp = fopen(path.c_str(), "wb");
    if (!fp) {
        fprintf(stderr, "[RenderCapture] WriteFile fopen failed: %s (errno=%d)\n",
                path.c_str(), errno);
        return false;
    }
    size_t written = fwrite(data, 1, size, fp);
    fclose(fp);
    return written == size;
}

}  // namespace rendercapture

#endif  // HEADLESS_RENDER_CAPTURE_FILE_UTILS_H
